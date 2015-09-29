#ifndef _CLOCK_OUTPUT_H_
#define _CLOCK_OUTPUT_H_
#include "Adafruit_NeoPixel.h"


class ClcokOutput {
private:

  void led_strip_init();

public:
  Adafruit_NeoPixel pixels;
  ClcokOutput();
  void begin();
  void set_number(uint8_t index, uint8_t num);
  void set_clock_dot(bool on_off);
  void set_number_off(uint8_t index);

  void set_brightness(uint8_t brightness);
  void set_color(uint8_t index, uint8_t num, uint32_t color);
};


#endif //_CLOCK_OUTPUT_H_
