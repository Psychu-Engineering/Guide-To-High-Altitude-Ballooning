// Declare my pins in a nice readable way. This works as long as the variables are seperated by commas and the statement ends with a semicolon
int potPinA = A0,
    potPinD = 2,
    potPinOut = 4,
    btnPin = 3,
    btnOut = 5;

// Standard variable declaration
float railVoltage = 5.00;

void setup() {
  // Setup serial port at 9600 baud
  Serial.begin(9600);

  // Declare what pins are inputs and outputs
  // Pot pins
  pinMode(potPinA, INPUT);
  pinMode(potPinD, INPUT);
  pinMode(potPinOut, OUTPUT);

  // Button pins
  pinMode(btnPin, INPUT);
  pinMode(btnOut, OUTPUT);
}


// This loop uses a couple custom functions defined below the loop function.
// These help to simplify program functionality and readability.
// Since these functions are defined below the loop function, their names and content can be changed as long as they are referred to using the correct capital sensitive name
void loop() {
    // Take an averaged the potentiometer output from the analog pin, calculate to voltage and display. Follow up by printing a "tab" character to visually organize the data when it shows up in a serial monitor.
    Serial.print( calcVolt( averageAnalogRead( potPinA ) ), 2 );
    Serial.print('\t');

    // Read the potentiometer output from a digital pin, and light its led
    Serial.print( digitalRead(potPinD) );
    digitalWrite(potPinOut, digitalRead(potPinD) );
    Serial.print('\t');

    // Read the button from a digital pin, and light its led.
    Serial.print( digitalRead(btnPin) );
    digitalWrite(btnOut, digitalRead(btnPin) );
    Serial.println();
}





// Convert "analog to digital" value to voltage
float calcVolt(int adcLvl){
    return (railVoltage / 1023) * adcLvl;
}




//Takes an average of readings on a given pin
//Returns the average
int averageAnalogRead(int pinToRead){
  byte numberOfReadings = 8;
  unsigned int runningValue = 0;

  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead);
  runningValue /= numberOfReadings;

  return(runningValue);
}
