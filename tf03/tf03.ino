// This code runs the TF03 Sensor of the X-Ray Wall for Otsuka.
// It reads the TF03 value into a moving average and then
// transmits the result over serial to a connected PC.

// contact: info@devicist.com


#include <SoftwareSerial.h>
#include "TFMini.h"
#include <movingAvg.h>          // https://github.com/JChristensen/movingAvg

const int numReadings = 6;
movingAvg sensorAvg(numReadings);

// Setup software serial port
SoftwareSerial mySerial(A5, A4);      // Uno RX (TFMINI TX), Uno TX (TFMINI RX)
TFMini tfmini;

void setup() {
  Serial.begin(115200);

  mySerial.begin(TFMINI_BAUDRATE);
  tfmini.begin(&mySerial);

  sensorAvg.begin();
  for (int i = 0; i < numReadings; i++) {
    sensorAvg.reading(tfmini.getDistance());
  }  
}


void loop() {
  static long timeStamp = millis();
  sensorAvg.reading(tfmini.getDistance());
  delay(2);

  if(millis() - timeStamp > 25) {
    Serial.println(sensorAvg.reading(tfmini.getDistance()));    
    timeStamp = millis();
  }
}
