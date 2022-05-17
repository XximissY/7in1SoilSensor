#ifndef _SOILD_SENSOR_H
#define _SOILD_SENSOR_H

#ifndef ARDUINO
#include <stdint.h>
#elif ARDUINO >= 100
#include "Arduino.h"
#include "Print.h"
#else
#include "WProgram.h"
#endif
#include <SoftwareSerial.h>

class soildSensor{
    private:
        uint8_t RX_pin;
        uint8_t TX_pin;
        uint8_t Driver_Receiver_Enable_Pin;
        uint8_t readDataCommand[8] ;
        int combine();
        uint32_t lastReadData;
    public:
        uint8_t values[20];
        soildSensor(uint8_t RX_pin,uint8_t TX_pin);
        void init();
        void readSoildData();
        float getMoist();
        float getTemp();
        float getConductivity();
        float getPH();
        float getNitrogen();
        float getPhosphorus();
        float getPotassium(); 
}


#endif
