
#include <Wire.h>
#include "BlueDot_BME280.h"

// Site altitude AMSL in metres
// Change to suit your location.
const float altitudeM = 93.30;

float qfe1;
float qfe2;
float qfe3;

// Calculate the QNH from site altitude and QFE
float qnh(float altitude, float qfe)
{
  return (qfe / pow(1.0 - (altitude/44330.0), 5.255));
}

// Find the smallest difference between qfe1 qfe2 and qfe3
// Then calculate and return the mean of the pair.
// An attempt to eliminate the worst errors in a random
// batch of Ebay BMP280 sensors.
// Some additional checking  required 
// to ensure they are initially
// within 2hPa(?) of each other. 
//
// Should we fail if only two sensors available?

// find the smallest absolute (ignore the +/-) difference.
// fabs() is floating-point abs()
float qfe (float qfe1, float qfe2, float qfe3)
{
    if (fabs(qfe1 - qfe2) <= fabs(qfe1 - qfe3))
  {
    if (fabs(qfe1 - qfe2) <= fabs(qfe2 - qfe3))
    {
      return ((qfe1 + qfe2) / 2.0); 
    }
    else
    {
      return ((qfe2 + qfe3) / 2.0);
    }
  }
  else
  {
    if (fabs(qfe1 - qfe3) <= fabs(qfe2 - qfe3))
    {
      return ((qfe1 + qfe3) / 2.0);
    }
    else
    {
      return ((qfe2 + qfe3) / 2.0);
    }
  }
 
  
  //return (fabs(qfe3 - qfe1));
  //float avg = ((qfe3 + qfe1) / 2.0 );
  //return (avg); 
}


BlueDot_BME280 bme1;                                     //Object for Sensor 1
BlueDot_BME280 bme2;                                     //Object for Sensor 2
BlueDot_BME280 bme3;                                     //Object for Sensor 3

int bme1Detected = 0;                                    //Checks if Sensor 1 is available
int bme2Detected = 0;                                    //Checks if Sensor 2 is available
int bme3Detected = 0;                                    //Checks if Sensor 3 is available

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.println(F("BMP Pressure Sensors"));

   //bme1.parameter.communication = 0;                    //I2C communication for Sensor 1 (bme1)

   //bme1.parameter.I2CAddress = 0x76;                    //I2C Address for Sensor 1 (bme1)

   bme1.parameter.communication = 1;                    //Hardware SPI for Sensor 1 (bme1)
   bme2.parameter.communication = 1;                    //Hardware SPI for Sensor 2 (bme2)
   bme3.parameter.communication = 1;                    //Hardware SPI for Sensor 3 (bme3)

   bme1.parameter.SPI_cs = 4;                          //Chip Select Pin for Sensor 1
   bme2.parameter.SPI_cs = 5;                          //Chip Select Pin for Sensor 2
   bme3.parameter.SPI_cs = 6;                          //Chip Select Pin for Sensor 3


   bme1.parameter.SPI_mosi = 13;                       //The MOSI signal must be connected to the same pin for all sensors
   bme2.parameter.SPI_mosi = 13;                       //The MOSI signal must be connected to the same pin for all sensors
   bme3.parameter.SPI_mosi = 13;                       //The MOSI signal must be connected to the same pin for all sensors

   bme1.parameter.SPI_miso = 11;                       //The MISO signal must be connected to the same pin for all sensors
   bme2.parameter.SPI_miso = 11;                       //The MISO signal must be connected to the same pin for all sensors
   bme3.parameter.SPI_miso = 11;                       //The MISO signal must be connected to the same pin for all sensors

   bme1.parameter.SPI_sck = 12;                       //The SCK signal must be connected to the same pin for all sensors
   bme2.parameter.SPI_sck = 12;                       //The SCK signal must be connected to the same pin for all sensors
   bme3.parameter.SPI_sck = 12;                       //The SCK signal must be connected to the same pin for all sensors

   bme1.parameter.sensorMode = 0b11;                    //Setup Sensor mode for Sensor 1
   bme1.parameter.IIRfilter = 0b100;                    //IIR Filter for Sensor 1
   bme1.parameter.humidOversampling = 0b101;            //Humidity Oversampling for Sensor 1
   bme1.parameter.tempOversampling = 0b010;             //Temperature Oversampling for Sensor 1
   bme1.parameter.pressOversampling = 0b101;            //Pressure Oversampling for Sensor 1
   bme1.parameter.pressureSeaLevel = 1013.25;           //default value of 1013.25 hPa (Sensor 1)
   bme1.parameter.tempOutsideCelsius = 15;              //default value of 15°C
   bme1.parameter.tempOutsideFahrenheit = 59;            //default value of 59°F
   
   bme2.parameter.sensorMode = 0b11;                    //Setup Sensor mode for Sensor 2
   bme2.parameter.IIRfilter = 0b100;                    //IIR Filter for Sensor 2
   bme2.parameter.humidOversampling = 0b101;            //Humidity Oversampling for Sensor 2
   bme2.parameter.tempOversampling = 0b010;             //Temperature Oversampling for Sensor 2
   bme2.parameter.pressOversampling = 0b101;            //Pressure Oversampling for Sensor 2
   bme2.parameter.pressureSeaLevel = 1013.25;           //default value of 1013.25 hPa (Sensor 2)
   bme2.parameter.tempOutsideCelsius = 15;              //default value of 15°C
   bme2.parameter.tempOutsideFahrenheit = 59;            //default value of 59°F

   bme3.parameter.sensorMode = 0b11;                    //Setup Sensor mode for Sensor 3
   bme3.parameter.IIRfilter = 0b100;                    //IIR Filter for Sensor 3
   bme3.parameter.humidOversampling = 0b101;            //Humidity Oversampling for Sensor 3
   bme3.parameter.tempOversampling = 0b010;             //Temperature Oversampling for Sensor 3
   bme3.parameter.pressOversampling = 0b101;            //Pressure Oversampling for Sensor 3
   bme3.parameter.pressureSeaLevel = 1013.25;           //default value of 1013.25 hPa (Sensor 3)
   bme3.parameter.tempOutsideCelsius = 15;              //default value of 15°C
   bme3.parameter.tempOutsideFahrenheit = 59;            //default value of 59°F
   
   
   //wdt_enable(WDTO_8S);                                 //Watchdog Timer counts for 8 seconds before starting the reset sequence

   // Check the chip ID BME280=0x60 BMP280=0x58
   if (bme1.init() != 0x58)
  {    
    Serial.println(F("BME280 #1 Sensor not found!"));
    bme1Detected = 0;
  }

  else
  {
    Serial.println(F("BME280 #1 Sensor detected!"));
    bme1Detected = 1;
  }

  if (bme2.init() != 0x58)
  {    
    Serial.println(F("BME280 #2 Sensor not found!"));
    bme2Detected = 0;
  }

  else
  {
    Serial.println(F("BME280 #2 Sensor detected!"));
    bme2Detected = 1;
  }

  if (bme3.init() != 0x58)
  {    
    Serial.println(F("BME280 #3 Sensor not found!"));
    bme3Detected = 0;
  }

  else
  {
    Serial.println(F("BME280 #3 Sensor detected!"));
    bme3Detected = 1;
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  if(bme1Detected)
  {
    qfe1 = bme1.readPressure();
    Serial.print(F("Pressure Sensor 1 [hPa]:\t\t"));
    Serial.print(qfe1);
    Serial.print(F("\t"));
    Serial.println(qnh(altitudeM, qfe1));
  }

  if(bme2Detected)
  {
    qfe2 = bme2.readPressure();
    Serial.print(F("Pressure Sensor 2 [hPa]:\t\t"));
    Serial.print(qfe2);
    Serial.print(F("\t"));
    Serial.println(qnh(altitudeM, qfe2));
  }

  if(bme3Detected)
  {
    qfe3 = bme3.readPressure();
    Serial.print(F("Pressure Sensor 3 [hPa]:\t\t"));
    Serial.print(qfe3);
    Serial.print(F("\t"));
    Serial.println(qnh(altitudeM, qfe3));
  }

  // Select best qnh just returns a test number for now.
  Serial.print(F("Mean of closest pair [hPa]:\t\t"));
  Serial.print(qfe(qfe1, qfe2, qfe3));
  Serial.print(F("\t"));
  Serial.println(qnh(altitudeM, qfe(qfe1, qfe2, qfe3)));

  Serial.println();
  
  // QNH returned as an integer rounded down
  // floor() the qnh 
  Serial.print(F("QNH rounded down  [hPa]:\t\t\t"));
  Serial.println(int(floor(qnh(altitudeM, qfe(qfe1, qfe2, qfe3)))));
  
  Serial.println();
  Serial.println();
  delay(5000);

}
