#include "Adafruit_Sensor.h"
#include "Adafruit_AM2320.h"
Adafruit_AM2320 hSensor = Adafruit_AM2320();


#include <Wire.h>
#include <Adafruit_MPL115A2.h>
Adafruit_MPL115A2 baro;


void setup() {
    Serial.begin(9600);

    hSensor.begin();
    baro.begin();
}



void loop() {
    float humidTemp = hSensor.readTemperature();
    float baroTemp = baro.getTemperature();
    float averageTemp = ( humidTemp + baroTemp ) / 2;

    Serial.print( humidTemp, 2);
    Serial.print('\t');
    Serial.print( baroTemp, 2);
    Serial.print('\t');
    Serial.print( averageTemp, 2);
    Serial.print('\n');
    delay(200);
}
