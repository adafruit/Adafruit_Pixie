/*
  Pixie reads data in at 115.2k serial, 8N1.
  Byte order is R1, G1, B1, R2, G2, B2, ... where the first triplet is the color of the LED that's closest to the controller. 1ms of silence causes a latch.
  2 seconds of silence causes everything off (safety) as does overheating.

  Do not look into Pixie with remaining eye!
*/

#include "SoftwareSerial.h"
#include "Adafruit_Pixie.h"

#define NUMPIXELS 3 // Number of Pixies in the strip
#define PIXIEPIN  6

SoftwareSerial pixieSerial(-1, PIXIEPIN);

Adafruit_Pixie strip = Adafruit_Pixie(NUMPIXELS, &pixieSerial);

void setup() {
  int i;
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Ready to Pixie!");

  pixieSerial.begin(115200); // pixie needs this baud rate
  strip.begin();

  strip.setBrightness(200);  // adjust as necessary to avoid blinding

  Serial.println("Red!");
  for(i=0; i< NUMPIXELS; i++)
    strip.setPixelColor(i, strip.Color(0xFF, 0, 0));
  strip.show();
  delay(300);

  Serial.println("Green!");
  for(i=0; i< NUMPIXELS; i++)
    strip.setPixelColor(i, strip.Color(0, 0xFF, 0));
  strip.show();
  delay(300);

  Serial.println("Blue!");
  for(i=0; i< NUMPIXELS; i++)
    strip.setPixelColor(i, strip.Color(0,0, 0xFF));
  strip.show();
  delay(300);
}

void loop() {
  Serial.println("Rainbow!");
  rainbowCycle(10);
}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUMPIXELS; i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}