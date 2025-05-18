/* Original Code: https://github.com/DzikuVx/attiny_rc_switch */
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <PinChangeInterrupt.h>

#define SLEEP_MODE_PWR_SAVE     (_BV(SM0) | _BV(SM1))
#define adc_disable() (ADCSRA &= ~(1<<ADEN)) // disable ADC (before power-off)
#define adc_enable()  (ADCSRA |=  (1<<ADEN)) // re-enable ADC
#define CHANNEL_PIN 0
#define OUTPUT_PIN 3
#define LPF_FACTOR 0.5
#define PULSE_THRESHOLD 1700

volatile unsigned long rising_start = 0;
volatile long channel_length = 0;
volatile long channel_raw = 0;
bool state = false;

void enterSleep(void) {
  set_sleep_mode(SLEEP_MODE_PWR_SAVE); // sleep mode is set here
  sleep_enable();
  sleep_mode();                        // System sleeps here
  sleep_disable();
}

/*
 * Start watchdog timer
 * 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
 * 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
 */
void setup_watchdog(int ii) {
  byte bb;
  int ww;
  if (ii > 9 ) ii = 9;
  bb = ii & 7;
  if (ii > 7) bb |= (1 << 5);
  bb |= (1 << WDCE);
  ww = bb;
  MCUSR &= ~(1 << WDRF);
  WDTCR |= (1 << WDCE) | (1 << WDE); // start timed sequence
  WDTCR = bb; // set new watchdog timeout value
  WDTCR |= _BV(WDIE);
}

/*
 * Watchdog interrupt function
 * Actually, we can do absolutely nothing here...
 */
ISR(WDT_vect) {}

void setup() {
  adc_disable();
  pinMode(CHANNEL_PIN, INPUT);
  pinMode(OUTPUT_PIN, OUTPUT);
  digitalWrite(OUTPUT_PIN, HIGH);
  delay(3000);
  digitalWrite(OUTPUT_PIN, LOW);
  attachPinChangeInterrupt(CHANNEL_PIN, onChange, CHANGE);
  setup_watchdog(2); //Set watchdog to wakeup every 128ms to enable/diable output
}

int smooth(int data, float filterVal, float smoothedVal){
  if (filterVal > 1){      // check to make sure param's are within range
    filterVal = .99;
  } else if (filterVal <= 0){
    filterVal = 0;
  }

  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);
  return (int)smoothedVal;
}

void onChange(void) {
  uint8_t trigger = getPinChangeInterruptTrigger(CHANNEL_PIN);

  if (trigger == RISING) {
    rising_start = micros();
  } else if (trigger == FALLING) {
    channel_raw = micros() - rising_start;
    channel_length = smooth(channel_raw, LPF_FACTOR, channel_length); //Add smoothing to prevent input jitters
  }
}

void loop() {
  if (channel_length > PULSE_THRESHOLD) {
    digitalWrite(OUTPUT_PIN, HIGH);
  } else {
    digitalWrite(OUTPUT_PIN, LOW);
  }
  enterSleep();
}
