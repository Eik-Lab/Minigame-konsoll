#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  
  // Print a welcome message
  lcd.setCursor(0, 0);
  lcd.print("Hello, Arduino!");
  lcd.setCursor(0, 1);
  lcd.print("LCD over I2C");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Move the cursor to the beginning of the second line
  lcd.setCursor(0, 1);
  
  // Print the current time
  lcd.print("Time: ");
  lcd.print(millis() / 1000); // Print the number of seconds since reset
  
  // Delay for a second
  delay(1000);
}