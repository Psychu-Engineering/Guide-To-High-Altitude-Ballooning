#include "Adafruit_Sensor.h"
#include "Adafruit_AM2320.h"

Adafruit_AM2320 hSensor = Adafruit_AM2320();

void setup() {
  Serial.begin(9600);

  hSensor.begin();
}

void loop() {
  delay(200);
  float humidity = hSensor.readHumidity();


  Serial.println(humidity,1);
}
