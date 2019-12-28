#include <SPI.h>
#include <SD.h>

int lightPin = A0;

File logFile;
char fileName[] = "logFile.csv";
const uint8_t logSelect = 10;
const uint8_t cardDetect = 9;
bool alreadyBegan = false;

unsigned long timestamp = 0;
int lightLvl, logPeriod = 20; //milliseconds

void setup() {
    Serial.begin(9600);
    pinMode(lightPin, INPUT);
    pinMode(cardDetect, INPUT);
    initializeCard();

    logFile = SD.open(fileName, FILE_WRITE);
    if(logFile) {
        logFile.println("light,milliseconds");
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

    lightLvl = analogRead(lightPin);
    timestamp = millis();

    logFile = SD.open(fileName, FILE_WRITE);
    if(logFile) {
        logFile.print(lightLvl);
        logFile.print(',');
        logFile.print(timestamp);
        logFile.print('\n');
        logFile.close();
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
