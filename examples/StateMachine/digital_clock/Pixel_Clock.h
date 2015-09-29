#ifndef _PIXEL_CLOCK_H_
#define _PIXEL_CLOCK_H_
#include "Adafruit_NeoPixel.h"


class Pixel_Clock {
private:
	uint32_t color;

  void led_strip_init();

public:
  Adafruit_NeoPixel pixels;
  Pixel_Clock();
  void begin();
  void start_show();
  void set_number(uint8_t index, uint8_t num);
  void set_clock_dot(bool on_off);
  void set_number_off(uint8_t index);

  void set_brightness(uint8_t brightness);
  void set_color(uint32_t r);
};


#endif //_PIXEL_CLOCK_H_
