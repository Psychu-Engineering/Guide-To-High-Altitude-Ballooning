#include <Wire.h>
#include <Adafruit_MPL115A2.h>

Adafruit_MPL115A2 baro;

void setup() {
  Serial.begin(9600);

  baro.begin();
}

void loop() {
    Serial.println( baro.getPressure() );
    delay(500);
}
