// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      40

#define RED 0
#define GREEN 128
#define BLUE 128
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

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
    {22, 21, 22, 23}, //0
    {23, 24, 25, 26}, //1
    {26, 27, 28, 29}, //2
    {29, 30, 31, 32}, //3
    {32, 33, 34, 35}, //4
    {35, 36, 37, 38}, //5
    {38, 39, 40, 23}  //6
  },
  {//third numbe2
    {52, 41, 42, 43}, //0
    {43, 44, 45, 46}, //1
    {46, 47, 48, 49}, //2
    {49, 50, 51, 52}, //3
    {52, 53, 54, 55}, //4
    {55, 56, 57, 58}, //5
    {58, 59, 60, 43}  //6
  },
  {//forth number
    {72, 61, 62, 63}, //0
    {63, 64, 65, 66}, //1
    {66, 67, 68, 69}, //2
    {69, 70, 71, 72}, //3
    {72, 73, 74, 75}, //4
    {75, 76, 77, 78}, //5
    {78, 79, 80, 63}  //6
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
  {0, 1, 2, 3, 5, 6} //   9
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

void setup() {

  // pixels.begin(); // This initializes the NeoPixel library.
  // pixels.show();

  Serial.begin(115200); 
  pixels.begin();
  setNumber(1, 2);
  pixels.show();


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

  // delay(2000);
  // for (int i=0; i < 100; i++)
  //   pixels.setPixelColor(i, 0); 
  // setNumber(1, 4);
  // pixels.show();
  // delay(2000);
  for (int i=0; i<10; i++) {
    for (int i=0; i < pixels.numPixels(); i++)
      pixels.setPixelColor(i, 0); 
    setNumber(1, i);
    setNumber(2, i);
    pixels.show();
    delay(1000);
  }
}
/*
void display(int num) {
  for (int i=0; i < pixels.numPixels(); i++)
    pixels.setPixelColor(i, 0);   
  delay(1000);
  switch (num) {
    case 0:
      displayBihua(2);
      displayBihua(3);
      displayBihua(4);
      displayBihua(5);
      displayBihua(6);
      displayBihua(7);
    break;
    case 1:
      displayBihua(2);
      displayBihua(7);
      break;
    case 2:
      displayBihua(3);
      displayBihua(2);
      displayBihua(1);
      displayBihua(5);
      displayBihua(6);
      break;
    case 3:
      displayBihua(3);
      displayBihua(2);
      displayBihua(1);
      displayBihua(7);
      displayBihua(6);
      break;
    case 4:
      displayBihua(4);
      displayBihua(1);
      displayBihua(2);
      displayBihua(7);
      break;
    case 5:
      displayBihua(3);
      displayBihua(4);
      displayBihua(1);
      displayBihua(7);
      displayBihua(6);
      break;
    case 6:
      displayBihua(3);
      displayBihua(4);
      displayBihua(5);
      displayBihua(6);
      displayBihua(7);
      displayBihua(1);
      break;
    case 7:
      displayBihua(3);
      displayBihua(2);
      displayBihua(7);
      break;
    case 8:
      displayBihua(1);
      displayBihua(2);
      displayBihua(3);
      displayBihua(4);
      displayBihua(5);
      displayBihua(6);
      displayBihua(7);
      break;
    case 9:
      displayBihua(1);
      displayBihua(2);
      displayBihua(3);
      displayBihua(4);
      displayBihua(7);
      displayBihua(6);
      break;
  }


  pixels.show();
}

void displayBihua(int index) {
  switch(index) {
    case 1:
      pixels.setPixelColor(0, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(1, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(2, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(11, pixels.Color(RED,GREEN, BLUE));
      break; 
    case 2:
      pixels.setPixelColor(2, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(3, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(4, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(5, pixels.Color(RED,GREEN, BLUE));
      break;
    case 3:
      pixels.setPixelColor(5, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(6, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(7, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(8, pixels.Color(RED,GREEN, BLUE));
      break;
    case 4:
      pixels.setPixelColor(8, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(9, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(10, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(11, pixels.Color(RED,GREEN, BLUE));
      break;
    case 5:
      pixels.setPixelColor(11, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(12, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(13, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(14, pixels.Color(RED,GREEN, BLUE));
      break;
    case 6:
      pixels.setPixelColor(14, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(15, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(16, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(17, pixels.Color(RED,GREEN, BLUE));
      break;
    case 7:
      pixels.setPixelColor(2, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(17, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(18, pixels.Color(RED,GREEN, BLUE));
      pixels.setPixelColor(19, pixels.Color(RED,GREEN, BLUE));
      break;
  }
}
*/