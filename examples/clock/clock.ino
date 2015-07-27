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
#define NUMPIXELS      20

#define RED 0
#define GREEN 255
#define BLUE 255
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
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

  for (int i=0; i<10; i++) {
    display(i);
    delay(1000);
  }
}

void display(int num) {
  for (int i=0; i < pixels.numPixels(); i++)
    pixels.setPixelColor(i, 0);   
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
