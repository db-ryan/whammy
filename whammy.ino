/* ******************************************************************
 * Takes two momantary footswitches (up and down) and turns it into
 * a MIDI signal for a Digitech Whammy. Displays the exact
 * Whammy settings on the 16x2 LCD.
 * ******************************************************************/

static const byte versionMajor = 0;
static const byte versionMinor = 1;

// Libraries
#include <MIDI.h>
#include <Bounce.h>
#include <LiquidCrystal.h>

// User definitions
#include "pins.h"
#include "buttons.h"
#include "midiSettings.h"

// Initializations
LiquidCrystal lcd(lcdRsPin, lcdEnablePin, lcdD4Pin, lcdD5Pin, lcdD6Pin, lcdD7Pin);
MidiSettings midiSettings;

/* ******************************************************************
 * Run once upon boot of Teensy
 * ******************************************************************/
void setup() {
  Serial.print("Whammy MIDI: Version: ");
  Serial.print(versionMajor);
  Serial.print(".");
  Serial.println(versionMinor);

  // Set Pin modes
  pinMode(programChangeUpPin, INPUT_PULLUP);
  pinMode(programChangeDownPin, INPUT_PULLUP);
  pinMode(onLedPin, OUTPUT);
  pinMode(lcdRsPin, OUTPUT);
  pinMode(lcdEnablePin, OUTPUT);
  pinMode(lcdD4Pin, OUTPUT);
  pinMode(lcdD5Pin, OUTPUT);
  pinMode(lcdD6Pin, OUTPUT);
  pinMode(lcdD7Pin, OUTPUT);

  // Set MIDI to begin and create Midi Settings
  MIDI.begin();
  /*Serial.print(midiSettings.programNumber[0]);*/
  /*Serial.print(midiSettings.lcdDisplayFirstLine[0]);*/

  // Set LCD Pins and Enable
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Whammy MIDI: Version:");
  lcd.setCursor(0,1); // 2nd Line
  lcd.print(versionMajor);

  // Set LED to on
  digitalWrite(onLedPin, HIGH);
} // setup

/* ******************************************************************
 * Loop when Teensy is running
 * ******************************************************************/
void loop() {
  // Look for falling edge of buttons (low true)
  bool buttonUpPressed   = buttonUp.update() && buttonUp.fallingEdge();
  bool buttonDownPressed = buttonDown.update() && buttonDown.fallingEdge();

  // If Up button is pressed
  if (buttonUpPressed) {
    Serial.println("Button Up pressed.");
    sendProgramChange(1);
  } // if buttonUp

  // If Down button is pressed
  else if (buttonDownPressed) {
    Serial.println("Button Down pressed.");
    sendProgramChange(-1);
  } // if buttonDown

} // loop

/* ******************************************************************
 * Send a Program Change via MIDI
 * ******************************************************************/
void sendProgramChange(byte changeDirection) {
  // Change the current program up or down (not to exceed min or max)
  if (changeDirection >= 0) {
    // Up
    currentProgram = (currentProgram < maxProgram) ? currentProgram + 1 : minProgram;
  } else {
    // Down
    currentProgram = (currentProgram > minProgram) ? currentProgram - 1 : maxProgram;
  } // changeDirection

  // Set the LCD to display the current setting
  Serial.println("Sending text to LCD.");
  lcd.setCursor(0, 0);
  lcd.print(midiSettings.lcdDisplayFirstLine[currentProgram]);
  lcd.setCursor(0, 1);
  lcd.print(midiSettings.lcdDisplaySecondLine[currentProgram]);

  // Send the program change via MIDI
  MIDI.sendProgramChange(midiSettings.programNumber[currentProgram], midiChannel);
  Serial.println("MIDI Change sent.");
} // sendProgramChange

