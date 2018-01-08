## **BlueDot Arduino Libraries**

This library allows the user to program and read the outputs of the BME280 Sensor with an Arduino Board.
It can also be used for the BMP280 (no humidity support) by configuring the CHIP ID parameter.
- BME280 = 0x60
- BMP280 = 0x58

I have added an additional example showing 3x BMP280 caclulating the mean pressure of the closest pair
and converting QFE (station pressure) to sea-level pressure (QNH). NB - 08-01-2017.


## **Repository Contents**

* Source Files (.cpp and .h)
* Example Sketch: BME280_WeatherStation.ino
* Example Sketch: BME280_MultipleSensorsI2C.ino
* Example Sketch: BME280_MultipleSensorsSPI.ino
* Example Sketch: BMP280_triple_SPI.ino
* library.properties File


## **Version History**

* V1.0.0 - Public Release Version
* V1.0.1 - New sketch for reading two sensors through I2C communication
* V1.0.2 - New sketch for reading multiple sensors through SPI communication
* V1.0.3 - Minor correction on BME280_WeatherStation.ino sketch
* V1.0.4 - Minor corrections on all sketches
* V1.0.5 - Minor correction on BME280_WeatherStation.ino sketch
* V1.0.6 - Minor correction on BME280_WeatherStation.ino sketch
* V1.0.7_NB - Forked and added BMP280 example. 


## **License Information**

This licence is released under the [Creative Commons ShareAlike 4.0 International](https://creativecommons.org/licenses/by-sa/4.0/) license.

This Library is distributed as-is and no warranty is given.
