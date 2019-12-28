// Assume the power level is at 5V
float railVoltage = 5.00;

// Setup executes first and can use variables declared before here
void setup() {
    // Start the serial port at 9600 BAUD
    Serial.begin(9600);
}

// After setup, loop executes repeatedly
void loop() {
    // Read the analog pin 0 and convert to voltage
    float voltage = (railVoltage / 1023) * analogRead(A0);
    // Print the voltage 2 positions past the decimal point
    Serial.println(voltage, 2);
}
