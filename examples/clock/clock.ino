// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <Wire.h>
#include "DS1307.h"

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      82

#define RED 0
#define GREEN 128
#define BLUE 128
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
DS1307 clock;//define a object of DS1307 class

int delayval = 500; // delay for half a second

//  ___
// |___|
// |___|

#define EVERY_PIXEL 4

// Number_index, stroke, pixel_index
#define  PIXEL_INDEX  stroke
#define NUMBER number

#if (EVERY_PIXEL == 5)
int stroke[4][7][5] = {
  {//first number
    {16,  1,  2,  3,  4}, //0
    { 4,  5,  6,  7,  8}, //1
    { 8,  9, 10, 11, 12}, //2
    {12, 13, 14, 15, 16}, //3
    {16, 17, 18, 19, 20}, //4
    {20, 21, 22, 23, 24}, //5
    {24, 25, 26, 27,  4}  //6
  },

  {//second number
    {43, 28, 29, 30, 31},
    {31, 32, 33, 34, 35},
    {35, 36, 37, 38, 39},
    {39, 40, 41, 42, 43},
    {43, 44, 45, 46, 47},
    {47, 48, 49, 50, 51},
    {51, 52, 53, 54, 31}
  },

  {//third number
    {72, 57, 58, 59, 60},
    {60, 61, 62, 63, 64},
    {64, 65, 66, 67, 68},
    {68, 69, 70, 71, 72},
    {72, 73, 74, 75, 76},
    {76, 77, 78, 79, 80},
    {80, 81, 82, 83, 60}
  },

  {//fouth number
    { 99,  84,  85,  86,  87},
    { 87,  88,  89,  90,  91},
    { 91,  92,  93,  94,  95},
    { 95,  96,  97,  98,  99},
    { 99, 100, 101, 102, 103},
    {103, 104, 105, 106, 107},
    {107, 108, 109, 110,  87}
  },

};

#else if (EVERY_PIXEL == 4)
int stroke[4][7][5] = {
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
#endif

int number[10][7] = {
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

void setNumber(int index, int num) {
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
    Serial.println();
    for(int j=0; j<EVERY_PIXEL; j++) {
      int stroke_number = NUMBER[num][i];
      pixels.setPixelColor(PIXEL_INDEX[index-1][stroke_number][j]-1, pixels.Color(RED,GREEN, BLUE));
      // Serial.print(PIXEL_INDEX[index-1][stroke_number][j], DEC);Serial.print(" ");
    }
  }

  // pixels.setPixelColor(0, pixels.Color(RED,GREEN, BLUE));
}

void setDot(bool a) {
  pixels.setPixelColor(40, pixels.Color(RED, GREEN, BLUE));
  pixels.setPixelColor(41, pixels.Color(RED, GREEN, BLUE));
}

void setup() {
  Serial.begin(115200);
  Serial.println("Hello!");

  clock.begin();
	// clock.fillByYMD(2015,8,9);//Jan 19,2013
	// clock.fillByHMS(16,44,00);//15:28 30"
	// clock.fillDayOfWeek(SUN);//Saturday
	// clock.setTime();//write time to the RTC chip

  clock.fillByYMD(2015,7,27);//Jan 19,2013
	clock.fillByHMS(10,00,30);//15:28 30"
	clock.fillDayOfWeek(SAT);//Saturday
	clock.setTime();//write time to the RTC chip

// delay(1000);
//   Serial.println(clock.hour, DEC);
// 	Serial.println(clock.minute, DEC);
//
//   int hour = clock.hour;
//   int minute = clock.minute;
//
//   Serial.println((hour/10),DEC);
//   Serial.println(hour%10,DEC);
//
  pixels.begin();
//
//   setNumber(1, hour/10);
//   setNumber(2, hour%10);
//   setDot(true);
//   setNumber(3, minute/10);
//   setNumber(4, minute%10);
//   pixels.show();
  // display(1);

}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  // for(int i=0;i<NUMPIXELS;i++){

  //   // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
  //   pixels.setPixelColor(i, pixels.Color(150,150,0)); // Î bright green color.

  //   pixels.show(); // This sends the updated pixel color to the hardware.

  //   delay(delayval); // Delay for a period of time (in milliseconds).

  // }

  // for (int i=0; i<10; i++) {
  //   display(i);
  //   delay(1000);
  // }
  // for (int i=0; i < 100; i++)
  //   pixels.setPixelColor(i, 0);
  // setNumber(1, 2);
  // pixels.show();
  //
  // delay(2000);
  // for (int i=0; i < 100; i++)
  //   pixels.setPixelColor(i, 0);
  // setNumber(1, 4);
  // pixels.show();
  // delay(2000);



  clock.getTime();
  int hour = clock.hour;
  int minute = clock.minute;

  Serial.println(hour,DEC);
  Serial.println(minute,DEC);

  for (int i=0; i < 82; i++){
    pixels.setPixelColor(i, 0);
  }
  setNumber(1, hour/10);
  setNumber(2, hour%10);
  setDot(true);
  setNumber(3, minute/10);
  setNumber(4, minute%10);
  pixels.show();

  delay(1000);

}
