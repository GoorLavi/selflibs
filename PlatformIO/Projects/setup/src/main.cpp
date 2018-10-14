
#include <Arduino.h>
#include <EEPROM.h>

int inPin = 0;
//
// int addr = 0;
// float defaulMaxVal = 1900, defaulMinVal = 1200;
// float maxVal =0, minVal = 255;
//
//
// int getRandom(int max, int min){
//     return rand()%(max-min + 1) + min;
// }
//
//
// int generateTransmitterSignal(){
//   return getRandom(defaulMaxVal, defaulMinVal);
// }
//
// float mapTransmitterSignal(int signalNumber){
//   return map(signalNumber, defaulMinVal, defaulMaxVal, 0, 255);
// }
//
// float getNormalizedSignal(){
//   return mapTransmitterSignal(generateTransmitterSignal());
// }

void setup() {
  // pinMode(analogPin, OUTPUT);
  pinMode(inPin, INPUT);
  Serial.begin(9600);
  //
  // while (!Serial) {
  //   ; // wait for serial port to connect. Needed for native USB port only
  // }

  // int read = EEPROM.read(addr);


   // Serial.println(read);
}

int val;

void loop() {
//
// float ranSignal = getNormalizedSignal();
//
// if(ranSignal > maxVal)
//   maxVal = ranSignal;
//   // EEPROM.write(addr, val);
// if(ranSignal < minVal)
//   minVal = ranSignal;
//
//
//   Serial.print("min: ");
//   Serial.print( minVal);
//   Serial.print(" max: ");
//   Serial.print(maxVal);
//   Serial.println();


  // val = ;     // read the input pin
  Serial.println(analogRead(inPin));
  delay(50);
}
