#include <7in1SoilSensor.h>
#define RX_Pin 2
#define TX_Pin 3
// Using TTL to RS485
#define Driver_Receiver_Enable_Pin  4
// 
soildSensor Sensor(RX_Pin, TX_Pin,Driver_Receiver_Enable_Pin);

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        delay(10);
    Serial.println();
}

void loop()
{
    digitalWrite(DI_DE, HIGH);
    Sensor.readSoildData();
    digitalWrite(DI_DE, LOW);

    if (!isnan(Sensor.getMoist()))
    {
        Serial.print("Moist: ");
        Serial.println(Sensor.getMoist());
        Serial.print("Temp: ");
        Serial.println(Sensor.getTemp());
        Serial.print("Conductivity: ");
        Serial.println(Sensor.getConductivity());
        Serial.print("pH: ");
        Serial.println(Sensor.getPH());
        Serial.print("Nitrogen(N): ");
        Serial.println(Sensor.getNitrogen());
        Serial.print("Phosphorus(P): ");
        Serial.println(Sensor.getPhosphorus());
        Serial.print("Potassium(K): ");
        Serial.printlnSensor.getPotassium());
    }else{
        Serial.println("Fail to Read Sensor Check Wiring"); 
    }
    delay(2000);
}
