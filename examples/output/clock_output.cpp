#include "clock_output.h"
#define NUMPIXELS 82
#define PIN 6

#define RED 0
#define GREEN 255
#define BLUE 255
#define EVERY_PIXEL 4

int PIXEL_INDEX[4][7][5] = {
  {//first number
    {12,  1,  2,  3}, //0
    { 3,  4,  5,  6}, //1
    { 6,  7,  8,  9}, //2
    { 9, 10, 11, 12}, //3
    {12, 13, 14, 15}, //4
    {15, 16, 17, 18}, //5
    {18, 19, 20,  3}  //6
  },
  {//second number
    {32, 21, 22, 23}, //0
    {23, 24, 25, 26}, //1
    {26, 27, 28, 29}, //2
    {29, 30, 31, 32}, //3
    {32, 33, 34, 35}, //4
    {35, 36, 37, 38}, //5
    {38, 39, 40, 23}  //6
  },
  {//third numbe2
    {54, 43, 44, 45}, //0
    {45, 46, 47, 48}, //1
    {48, 49, 50, 51}, //2
    {51, 52, 53, 54}, //3
    {54, 55, 56, 57}, //4
    {57, 58, 59, 60}, //5
    {60, 61, 62, 45}  //6
  },
  {//forth number
    {74, 63, 64, 65}, //0
    {65, 66, 67, 68}, //1
    {68, 69, 70, 71}, //2
    {71, 72, 73, 74}, //3
    {74, 75, 76, 77}, //4
    {77, 78, 79, 80}, //5
    {80, 81, 82, 65}  //6
  }
};

// #define PIXEL_INDEX  stroke
// #define NUMBER number

int NUMBER[10][7] = {
  {1, 2, 3, 4, 5, 6}, //0
  {1, 6}, // 1
  {0, 1, 2, 4, 5}, //   2
  {0, 1, 2, 5, 6}, //   3
  {0, 1, 3, 6}, //   4
  {0, 2, 3, 5, 6}, //   5
  {0, 2, 3, 4, 5, 6}, //   6
  {1, 2, 6},  //  7
  {0, 1, 2, 3, 4, 5, 6}, //   8
  {0, 1, 2, 3, 5, 6} //   9s
};

Pixel_Clock::Pixel_Clock() {

}

void Pixel_Clock::begin() {
  led_strip_init();
}

void Pixel_Clock::led_strip_init() {
  pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
  pixels.begin();
}

void Pixel_Clock::set_number(uint8_t index, uint8_t num) {
  set_number_off(index);
  if (index < 1 || index > 4)
    return;
  if (num < 0 || num > 9)
    return;

  int mbreak;
  mbreak = false;

  for (int i=0;i<7;i++) {
    if(mbreak)
      break;
    if (NUMBER[num][i] == 6)
      mbreak = true;
    for(int j=0; j<EVERY_PIXEL; j++) {
      int stroke_number = NUMBER[num][i];
      pixels.setPixelColor(PIXEL_INDEX[index-1][stroke_number][j]-1, pixels.Color(RED, GREEN, BLUE));
    }
  }

  pixels.show();
}

void Pixel_Clock::set_clock_dot(bool on_off) {
  if(on_off) {
    pixels.setPixelColor(40, pixels.Color(RED, GREEN, BLUE));
    pixels.setPixelColor(41, pixels.Color(RED, GREEN, BLUE));
  } else {
    pixels.setPixelColor(40, 0);
    pixels.setPixelColor(41, 0);
  }
  pixels.show();
}

void Pixel_Clock::set_number_off(uint8_t index) {
  int num = 8;
  int mbreak;
  mbreak = false;

  for (int i=0;i<7;i++) {
    if(mbreak)
      break;
    if (NUMBER[num][i] == 6)
      mbreak = true;
    for(int j=0; j<EVERY_PIXEL; j++) {
      int stroke_number = NUMBER[num][i];
      pixels.setPixelColor(PIXEL_INDEX[index-1][stroke_number][j]-1, 0);
    }
  }

  pixels.show();
}

void Pixel_Clock::set_brightness(uint8_t brightness) {
  pixels.setBrightness(brightness);
}

void Pixel_Clock::set_color(uint8_t index, uint8_t num, uint32_t color) {
  if (index < 1 || index > 4)
    return;
  if (num < 0 || num > 9)
    return;

  int mbreak;
  mbreak = false;

  for (int i=0;i<7;i++) {
    if(mbreak)
      break;
    if (NUMBER[num][i] == 6)
      mbreak = true;
    for(int j=0; j<EVERY_PIXEL; j++) {
      int stroke_number = NUMBER[num][i];
      pixels.setPixelColor(PIXEL_INDEX[index-1][stroke_number][j]-1, color);
    }
  }

  pixels.show();
}
