/*
  Author: berhanozturk
  Date: 09/25/2023

*/



#include <LiquidCrystal.h>

const int buttonPin = 3;  // Menu button
const int actionButtonPin = 2; // select button
int buttonState = 0;     // (click/non-click)
int lastButtonState = 0; // last button state
int actionButtonState = 0; // select buton state
int lastActionButtonState = 0; // last select button state
int menuIndex = 0;       
int maxMenuIndex = 1;    // Total menu options (subtracting 1 because we start from 0)

// LED pins
const int redLedPin = 10;
const int yellowLedPin = 8;

// LCD 
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

void setup() {
  // Set the button pins INPUT PULLUP mode
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(actionButtonPin, INPUT_PULLUP);

  // Set the button pins OUTPUT mode
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);

  // Start the LCD
  lcd.begin(16, 2);

  // Show the first menu option
  showMenu();
}

void loop() {
  // Read the menu button state
  buttonState = digitalRead(buttonPin);

  // Read the select button state
  actionButtonState = digitalRead(actionButtonPin);

  // if menu button state change
  if (buttonState != lastButtonState) {
    delay(50); // 

    // If the menu button is pressed
    if (buttonState == LOW) {
      menuIndex++; // Increase the menu option

      // Make the menu options looping
      if (menuIndex > maxMenuIndex) {
        menuIndex = 0;
      }

      // Display the new menu option
      showMenu();
    }
  }

  // If the select button state has changed
    if (actionButtonState != lastActionButtonState) {
    delay(50); // Debounce delay time

    // If the select button is pressed and the option is 1
    if (actionButtonState == LOW && menuIndex == 0) {
      digitalWrite(redLedPin, !digitalRead(redLedPin)); // Red LED on/off
    }

    // If the select button is pressed and the option is 2
    if (actionButtonState == LOW && menuIndex == 1) {
      digitalWrite(yellowLedPin, !digitalRead(yellowLedPin)); // Yellow LED on/off
    }
  }

  // Update button states
  lastButtonState = buttonState;
  lastActionButtonState = actionButtonState;
}

void showMenu() {

  lcd.setCursor(0, 0);

  if (menuIndex == 0) {
    lcd.print("> Red LED");
  } else {
    lcd.print("  Red LED");
  }

  lcd.setCursor(0, 1);

  if (menuIndex == 1) {
    lcd.print("> Yellow LED");
  } else {
    lcd.print("  Yellow LED");
  }
}
