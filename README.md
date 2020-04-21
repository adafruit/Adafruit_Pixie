# Adafruit Pixie library [![Build Status](https://github.com/adafruit/Adafruit_Pixie/workflows/Arduino%20Library%20CI/badge.svg)](https://github.com/adafruit/Adafruit_Pixie/actions)[![Documentation](https://github.com/adafruit/ci-arduino/blob/master/assets/doxygen_badge.svg)](http://adafruit.github.io/Adafruit_Pixie/html/index.html)

<a href="https://www.adafruit.com/products/2741"><img src="assets/pixie.jpg?raw=true" width="500px"></a>

Arduino library for controlling Pixie - a 3W chainable LED. Uses one serial pin, "NeoPixel" library compatible.

Check it out over at 

* [https://www.adafruit.com/products/2741](https://www.adafruit.com/products/2741)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Ytai Ben-Tsvi/Limor Fried for Adafruit Industries.  
BSD license, check license.txt for more information
All text above must be included in any redistribution

To download. click the DOWNLOADS button in the top right corner, rename the uncompressed folder Adafruit_Pixie. Check that the Adafruit_Pixie folder contains Adafruit_Pixie.cpp and Adafruit_Pixie.h

Place the Adafruit_Pixie library folder your arduinosketchfolder/libraries/ folder. You may need to create the libraries subfolder if its your first library. Restart the IDE.

USERS OF PREVIOUS VERSIONS OF LIBRARY PLEASE NOTE: strip.begin() no longer exists. Instead, in setup(), call serial.begin(115200) for the hardware or software serial port being used for output, e.g. Serial1.begin(115200) or pixieSerial.begin(115200); see strandtest.ino example for use.
