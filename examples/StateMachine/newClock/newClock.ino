#include "Arduino.h"
#include "Wire.h"
#include "DS1307.h"
#include "clock_output.h"

#define STATE_NORMAL  0x00
#define STATE_SETTING 0x01

#define SETTING_NONE    0x00
#define SETTING_FIRST   0x01
#define SETTING_SECOND  0x02
#define SETTING_THRID   0x03
#define SETTING_FORTH   0x04

int state = STATE_NORMAL;
int setting_state = SETTING_NONE;

bool button_one_press = false;
bool button_two_press = false;

int setting_pin = 2;
int plus_pin = 3;

int hour = 19;
int minute = 30;

ClcokOutput clock;
DS1307 time;

void setup() {
  Serial.begin(115200);
  time.begin();
  get_time();

  clock.begin();
  clock.set_brightness(20);
  clock_init();

  attachInterrupt(digitalPinToInterrupt(setting_pin), button_one, RISING); //button P
  attachInterrupt(digitalPinToInterrupt(plus_pin), button_two, RISING);
}

void loop() {
  if (button_one_press) {
    if (button_one_confirm()) {
      setting_state_change();
      if (state == STATE_NORMAL) {
        clock_init();
        save_time();
      }
    }
  }

  if (button_two_press) {
    if (button_two_confirm()) {
      time_change();
    }
  }

  if (delay_no_block(1000)) {
    Serial.print("state = ");Serial.println(state);
    Serial.print("setting_state = ");Serial.println(setting_state);
    Serial.print("time = ");Serial.print(hour);Serial.print(":");Serial.println(minute); 
  }

  switch (state) {
    case STATE_NORMAL:
      time_refresh();
      dot_refresh();
      break;
    case STATE_SETTING:
      switch (setting_state) {
        case SETTING_FIRST:
          blink_number(1);
          break;
        case SETTING_SECOND:
          blink_number(2);
          break;
        case SETTING_THRID:
          blink_number(3);
          break;
        case SETTING_FORTH:
          blink_number(4);
          break;
      }
      break;
  }
}

void button_one() {
  button_one_press = true;
}

void button_two() {
  button_two_press = true;
}

void setting_state_change(){
  if (state == STATE_NORMAL) {
    state = STATE_SETTING;
    setting_state = SETTING_FIRST;
  }
  else if (state == STATE_SETTING) {
    if (setting_state == SETTING_FIRST)
      setting_state = SETTING_SECOND;
    else if (setting_state == SETTING_SECOND)
      setting_state = SETTING_THRID;
    else if (setting_state == SETTING_THRID)
      setting_state = SETTING_FORTH;
    else if (setting_state == SETTING_FORTH) {
      setting_state = SETTING_NONE;
      state = STATE_NORMAL;
    }
  }
}

bool delay_no_block(long ms) {
  static unsigned long previousMillis = 0;
  long interval = ms;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}

bool button_one_confirm() {
  static unsigned long previousMillis = 0;
  long interval = 20;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    button_one_press = false;
    if (digitalRead(setting_pin) == HIGH)
      return true;
  }
  return false;
}

bool button_two_confirm() {
  static unsigned long previousMillis = 0;
  long interval = 20;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    button_two_press = false;
    if (digitalRead(plus_pin) == HIGH)
      return true;
  }
  return false;
}

void blink_number(int pos) {
  static int state = HIGH;
  static unsigned long previousMillis = 0;
  long interval = 500;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (state == HIGH) {
      state = LOW;
      clock.set_number_off(pos);
    } else {
      state = HIGH;
      clock.set_number(1, hour/10);
      clock.set_number(2, hour%10);
      clock.set_number(3, minute/10);
      clock.set_number(4, minute%10);
    }
  }
}

void time_refresh() {
  // static int state = HIGH;
  static unsigned long previousMillis = 0;
  long interval = 60000;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    get_time();
    clock.set_number(1, hour/10);
    clock.set_number(2, hour%10);
    clock.set_number(3, minute/10);
    clock.set_number(4, minute%10);
  }
}

void dot_refresh() {
  static int state = HIGH;
  static unsigned long previousMillis = 0;
  long interval = 1000;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (state == HIGH) {
      state = LOW;
      clock.set_clock_dot(true);
    } else {
      state = HIGH;
      clock.set_clock_dot(false);
    }
  }
}

void time_change() {
  if (state == STATE_SETTING) {
    switch (setting_state) {
      case SETTING_FIRST:
        plus_number(1);
        break;
      case SETTING_SECOND:
        plus_number(2);
        break;
      case SETTING_THRID:
        plus_number(3);
        break;
      case SETTING_FORTH:
        plus_number(4);
        break;
    }
  }
}

void plus_number(int pos) {
  int number_one = hour/10;
  int number_two = hour%10;
  int number_three = minute/10;
  int number_four = minute%10;
  switch (pos) {
    case 1:
      number_one += 1;
      if (number_one == 3)
        number_one = 0;
      break;
    case 2:
      number_two += 1;
      if (number_two == 10)
        number_two = 0;
      break;
    case 3:
      number_three += 1;
      if (number_three == 6)
        number_three = 0;
      break;
    case 4:
      number_four += 1;
      if (number_four == 10)
        number_four = 0;
      break;
  }
  hour = number_one*10 + number_two;
  minute = number_three*10 + number_four;
}

void get_time() {
  time.getTime();
  hour = time.hour;
  minute = time.minute;
  if (hour < 0 || hour > 23) 
    hour = 12;
  if (minute < 0 || minute > 59)
    minute = 30;
}

void save_time() {
  time.fillByHMS(hour,minute,00);//15:28 30"
  time.setTime();  
}

void clock_init() {
  clock.set_number(1, hour/10);
  clock.set_number(2, hour%10);
  clock.set_clock_dot(true);
  clock.set_number(3, minute/10);
  clock.set_number(4, minute%10);
}
