// Define the pin numbers for the LED and the button
#define ledPin 3
#define buttonPin 4

void setup() {
  // Initialize the digital pins
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Read the state of the button
  int buttonState = digitalRead(buttonPin);

  // If the button is pressed (HIGH), turn on the LED
  if (buttonState == HIGH) {
    digitalWrite(ledPin, HIGH); // Turn on LED
  } else {
    digitalWrite(ledPin, LOW); // Turn off LED
  }
}


