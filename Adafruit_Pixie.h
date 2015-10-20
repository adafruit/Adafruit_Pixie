#ifndef ADAFRUIT_PIXIE_H
#define ADAFRUIT_PIXIE_H
#include <Arduino.h>
#include "SoftwareSerial.h"

class Adafruit_Pixie {

 public:

  // Constructor: number of LEDs, serial port
  Adafruit_Pixie(uint16_t n, SoftwareSerial *ser);
  Adafruit_Pixie(uint16_t n, HardwareSerial *ser);

  ~Adafruit_Pixie();

  void
    begin(void),
    show(void),
    setPin(uint8_t p),
    setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b),
    setPixelColor(uint16_t n, uint32_t c),
    setBrightness(uint8_t),
    clear();
  uint8_t
   *getPixels(void) const,
    getBrightness(void) const;
  uint16_t
    numPixels(void) const;
  static uint32_t
    Color(uint8_t r, uint8_t g, uint8_t b);
  uint32_t
    getPixelColor(uint16_t n) const;
  inline bool
    canShow(void) { return (micros() - endTime) >= 50L; }

 private:

  const uint16_t
    numLEDs,       // Number of RGB LEDs in strip
    numBytes;      // Size of 'pixels' buffer below
  uint8_t
    brightness,
    *pixels;        // Holds LED color values (3 bytes each)
  uint32_t
    endTime;       // Latch timing reference

  SoftwareSerial *pixieSwSerial;
  HardwareSerial *pixieHwSerial;
};

#endif // ADAFRUIT_PIXIE_H
