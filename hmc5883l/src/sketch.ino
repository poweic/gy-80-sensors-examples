#include <Wire.h>
#include "HMC5883L.h"

HMC5883L compass;

// Macro for checking compass error
#define CCE(e) { if(e != 0) Serial.println(compass.GetErrorText(e)); } 

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  compass = HMC5883L(); //new instance of HMC5883L library
  setupHMC5883L(); //setup the HMC5883L
}

// Our main program loop.
void loop() {
  // Serial.println(getHeading());
  printMagnetoRaw();
  delay(100); //only here to slow down the serial print
}

void setupHMC5883L() {
  //Setup the HMC5883L, and check for errors
  int error;  
  CCE(compass.SetScale(1.3)); //Set the scale of the compass.
  CCE(compass.SetMeasurementMode(Measurement_Continuous)); // Set the measurement mode to Continuous
}

void printMagnetoRaw() {
  MagnetometerScaled scaled = compass.ReadScaledAxis(); //scaled values from compass.
  Serial.printf("(x, y, z) = (");
  Serial.print(scaled.XAxis); Serial.print(", ");
  Serial.print(scaled.YAxis); Serial.print(", ");
  Serial.print(scaled.ZAxis); Serial.println(")");
}

float getHeading() {
  //Get the reading from the HMC5883L and calculate the heading
  MagnetometerScaled scaled = compass.ReadScaledAxis(); //scaled values from compass.
  float heading = atan2(scaled.YAxis, scaled.XAxis);

  // Correct for when signs are reversed.
  if(heading < 0) heading += 2*PI;
  if(heading > 2*PI) heading -= 2*PI;

  return heading * RAD_TO_DEG; //radians to degrees
}
