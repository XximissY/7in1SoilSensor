#include "7in1SoilSensor.h"

soildSensor::soildSensor(uint8_t RX_pin,uint8_t TX_pin){
  this->RX_pin = RX_pin;
  this->TX_pin = TX_pin;
  this->Driver_Receiver_Enable_Pin = Driver_Receiver_Enable_Pin;
  init();
}

void soildSensor::init(){
  pinMode(Driver_Receiver_Enable_Pin,OUTPUT);
  digitalWrite(Driver_Receiver_Enable_Pin, LOW);
  SoftwareSerial mySerial (RX_pin, TX_pin);
  mySerial.begin(4800,SERIAL_8N1);
}

void soildSensor::readSoildData(){
  this->readDataCommand[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x07, 0x04, 0x08};
  if ((millis() - this->lastReadData) >= 2000) {
    this->lastReadData = millis();
    digitalWrite(Driver_Receiver_Enable_Pin, HIGH); 
    if (mySerial.write( this->readDataCommand, sizeof( this->readDataCommand)) == 8) {
      for (byte i = 0; i < 20; i++) { 
         this->values[i] = Serial2.read();
      }
    }
    digitalWrite(Driver_Receiver_Enable_Pin, LOW);
  }
}

int combine(byte a,byte b){
  return int(a*256) + int(b);
}

float soildSensor::getMoist() {
  uint16_t input = combine(this->values[3],this->values[4]);
  return input / 10;
}

float soildSensor::getTemp() {
  uint16_t input = combine(this->values[5],this->values[6]);
  return input / 10;
}

float soildSensor::getConductivity() {
  uint16_t input = combine(this->values[7],this->values[8]);
  return input;
}

float soildSensor::getPH() {
  uint16_t input = combine(this->values[9],this->values[10]);
  return input/10;
}

float soildSensor::getNitrogen() {
  uint16_t input = combine(this->values[11],this->values[12]);
  return input;
}

float soildSensor::getPhosphorus() {
  uint16_t input = combine(this->values[13],this->values[14]);
  return input;
}

float soildSensor::getPotassium() {
  uint16_t input = combine(this->values[15],this->values[16]);
  return input;
}

/*
const byte readDataCommand[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x07, 0x04, 0x08};
uint8_t values[20];
uint32_t lastReadData = 0;

void modbusInti() {
  Serial2.begin(4800, SERIAL_8N1);
}


void readSoildData() {
  if ((millis() - lastReadData) >= 2000) {
    lastReadData = millis();
    if (Serial2.write(readDataCommand, sizeof(readDataCommand)) == 8) {
      Serial.print("Return Data => ");
      for (byte i = 0; i < 20; i++) { 
        values[i] = Serial2.read();
        Serial.print(" ");
        Serial.print(values[i], HEX);
      }
      Serial.println();
    }
  }

}

int combine(byte a,byte b){
  return int(a*256) + int(b);
}

float getMoist() {
  uint16_t input = combine(this->values[3],this->values[4]);
  return input / 10;
}

float getTemp() {
  uint16_t input = combine(this->values[5],this->values[6]);
  return input / 10;
}

float getConductivity() {
  uint16_t input = combine(this->values[7],this->values[8]);
  return input;
}

float getPH() {
  uint16_t input = combine(this->values[9],this->values[10]);
  return input/10;
}

float getNitrogen() {
  uint16_t input = combine(this->values[11],this->values[12]);
  return input;
}

float getPhosphorus() {
  uint16_t input = combine(this->values[13],this->values[14]);
  return input;
}

float getPotassium() {
  uint16_t input = combine(this->values[15],this->values[16]);
  return input;
}

*/