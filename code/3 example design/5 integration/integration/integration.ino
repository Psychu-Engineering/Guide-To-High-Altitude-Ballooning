#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AM2320.h>
#include <Adafruit_MPL115A2.h>
#include <SPI.h>
#include <SD.h>

Adafruit_MPL115A2 baro; // I2C

Adafruit_AM2320 hSensor = Adafruit_AM2320();

int lightPin = A0, ledPin = 2;

File logFile;
char fileName[] = "logFile.csv";
const uint8_t logSelect = 10;
const uint8_t cardDetect = 9;
bool alreadyBegan = false;

unsigned long timestamp = 0;
int lightLvl, logPeriod = 50;
float pressure, bTemp, hTemp, aveTemp, humidity;



void setup() {
    Serial.begin(9600);

    pinMode(lightPin, INPUT);
    pinMode(cardDetect, INPUT);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    baro.begin();
    hSensor.begin();

    initializeCard();
    logFile = SD.open(fileName, FILE_WRITE);
    if(logFile) {
        logFile.println("pressure,bTemp,humidity,hTemp,aveTemp,lightLvl,milliseconds");
        logFile.close();
    }
    else {
        Serial.println("Failed to open file");
    }
}



void loop() {
    if (!digitalRead(cardDetect)){
        initializeCard();
    }

    pressure = baro.getPressure();
    bTemp = baro.getTemperature();

    humidity = hSensor.readHumidity();
    hTemp = hSensor.readTemperature();

    aveTemp = ( bTemp + hTemp ) / 2.0;

    lightLvl = analogRead(lightPin);

    logFile = SD.open(fileName, FILE_WRITE);
    if(logFile) {
        digitalWrite(ledPin, HIGH);
        logFile.print(pressure);
        logFile.print(',');
        logFile.print(bTemp);
        logFile.print(',');
        logFile.print(humidity);
        logFile.print(',');
        logFile.print(hTemp);
        logFile.print(',');
        logFile.print(aveTemp);
        logFile.print(',');
        logFile.print(lightLvl);
        logFile.print(',');
        logFile.println( millis() );
        logFile.close();
        digitalWrite(ledPin, LOW);
    }
    else {
        Serial.println("Failed to open file");
    }
    delay(logPeriod);
}





void initializeCard(void){
    Serial.print(F("Initializing SD card..."));

    // Is there even a card?
    if (!digitalRead(cardDetect)){
        Serial.println(F("No card detected. Waiting for card."));
        while (!digitalRead(cardDetect));
        delay(250); // 'Debounce insertion'
    }

    // Card seems to exist.  begin() returns failure
    // even if it worked if it's not the first call.
    if (!SD.begin(logSelect) && !alreadyBegan){  // begin uses half-speed...
        Serial.println(F("Initialization failed!"));
        initializeCard(); // Possible infinite retry loop is as valid as anything
    }
    else{
        alreadyBegan = true;
    }
    Serial.println(F("Initialization done."));

    Serial.print(fileName);
    if (SD.exists(fileName)){
        Serial.println(F(" exists."));
    }
    else{
        Serial.println(F(" doesn't exist. Creating."));
    }

    Serial.print("Opening file: ");
    Serial.println(fileName);
}
