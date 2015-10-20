#include "Adafruit_Pixie.h"
#include "SoftwareSerial.h"

Adafruit_Pixie::Adafruit_Pixie(uint16_t n, SoftwareSerial *ser) :
  numLEDs(n), numBytes(n * 3), brightness(0), pixels(NULL), endTime(0),
  pixieSwSerial(ser), pixieHwSerial(NULL)
{
  if((pixels = (uint8_t *)malloc(numBytes))) {
    memset(pixels, 0, numBytes);
  }
}

Adafruit_Pixie::Adafruit_Pixie(uint16_t n, HardwareSerial *ser) :
  numLEDs(n), numBytes(n * 3), brightness(0), pixels(NULL), endTime(0),
  pixieHwSerial(ser), pixieSwSerial(NULL)
 
{
  if((pixels = (uint8_t *)malloc(numBytes))) {
    memset(pixels, 0, numBytes);
  }
}

Adafruit_Pixie::~Adafruit_Pixie() {
  if(pixels) free(pixels);
}

void Adafruit_Pixie::begin(void) {
   if(pixieSwSerial) pixieSwSerial->begin(115200);
   else            pixieHwSerial->begin(115200);
}

void Adafruit_Pixie::show(void) {

  if(!pixels) return;

  while(!canShow());
  
  for (uint16_t x=0; x<(numLEDs*3); x++) {
    if (pixieSwSerial) {
	pixieSwSerial->write(pixels[x]);
    }
    if (pixieHwSerial) {
	pixieHwSerial->write(pixels[x]);
    }
  }

  endTime = micros(); // Save EOD time for latch on next call
}

// Set pixel color from separate R,G,B components:
void Adafruit_Pixie::setPixelColor(
 uint16_t n, uint8_t r, uint8_t g, uint8_t b) {
  if(n < numLEDs) {
    if(brightness) { // See notes in setBrightness()
      r = (r * brightness) >> 8;
      g = (g * brightness) >> 8;
      b = (b * brightness) >> 8;
    }
    uint8_t *p = &pixels[n * 3];
    p[0] = r;
    p[1] = g;
    p[2] = b;
  }
}

// Set pixel color from 'packed' 32-bit RGB color:
void Adafruit_Pixie::setPixelColor(uint16_t n, uint32_t c) {
  if(n < numLEDs) {
    uint8_t
      r = (uint8_t)(c >> 16),
      g = (uint8_t)(c >>  8),
      b = (uint8_t)c;
    if(brightness) { // See notes in setBrightness()
      r = (r * brightness) >> 8;
      g = (g * brightness) >> 8;
      b = (b * brightness) >> 8;
    }
    uint8_t *p = &pixels[n * 3];
    p[0] = r;
    p[1] = g;
    p[2] = b;
  }
}

// Convert separate R,G,B into packed 32-bit RGB color.
// Packed format is always RGB, regardless of LED strand color order.
uint32_t Adafruit_Pixie::Color(uint8_t r, uint8_t g, uint8_t b) {
  return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

// Query color from previously-set pixel (returns packed 32-bit RGB value)
uint32_t Adafruit_Pixie::getPixelColor(uint16_t n) const {
  if(n >= numLEDs) {
    // Out of bounds, return no color.
    return 0;
  }
  uint8_t *p = &pixels[n * 3];
  uint32_t c = ((uint32_t)p[0] << 16) |
               ((uint32_t)p[1] <<  8) |
                (uint32_t)p[2];
  // Adjust this back up to the true color, as setting a pixel color will
  // scale it back down again.
  if(brightness) { // See notes in setBrightness()
    //Cast the color to a byte array
    uint8_t * c_ptr =reinterpret_cast<uint8_t*>(&c);
    c_ptr[0] = (c_ptr[0] << 8)/brightness;
    c_ptr[1] = (c_ptr[1] << 8)/brightness;
    c_ptr[2] = (c_ptr[2] << 8)/brightness;
  }
  return c; // Pixel # is out of bounds
}

// Returns pointer to pixels[] array.  Pixel data is stored in device-
// native format and is not translated here.  Application will need to be
// aware whether pixels are RGB vs. GRB and handle colors appropriately.
uint8_t *Adafruit_Pixie::getPixels(void) const {
  return pixels;
}

uint16_t Adafruit_Pixie::numPixels(void) const {
  return numLEDs;
}

void Adafruit_Pixie::setBrightness(uint8_t b) {
  // Note for Pixie we can actually do this dynimcally! TODO!

  uint8_t newBrightness = b + 1;
  if(newBrightness != brightness) { // Compare against prior value
    // Brightness has changed -- re-scale existing data in RAM
    uint8_t  c,
            *ptr           = pixels,
             oldBrightness = brightness - 1; // De-wrap old brightness value
    uint16_t scale;
    if(oldBrightness == 0) scale = 0; // Avoid /0
    else if(b == 255) scale = 65535 / oldBrightness;
    else scale = (((uint16_t)newBrightness << 8) - 1) / oldBrightness;
    for(uint16_t i=0; i<numBytes; i++) {
      c      = *ptr;
      *ptr++ = (c * scale) >> 8;
    }
    brightness = newBrightness;
  }
}

//Return the brightness value
uint8_t Adafruit_Pixie::getBrightness(void) const {
  return brightness - 1;
}

void Adafruit_Pixie::clear() {
  memset(pixels, 0, numBytes);
}
