// Takes a momantary footswitch up and down and turns it into
// a MIDI signal for a Digitech Whammy.
static const byte versionMajor = 0;
static const byte versionMinor = 1;

// Libraries
#include <MIDI.h>
#include <Bounce.h>

// User definitions
#include "pins.h"
#include "buttons.h"
#include "midiSettings.h"

/* *****************************************
 * Run once upon boot of Teensy
 * *****************************************/
void setup() {
  Serial.print("Whammy MIDI: Version: ");
  Serial.print(versionMajor);
  Serial.print(".");
  Serial.println(versionMinor);

  // Set Pin modes
  pinMode(onLedPin, OUTPUT);
  pinMode(programChangeUpPin, INPUT_PULLUP);
  pinMode(programChangeDownPin, INPUT_PULLUP);

  // Set MIDI to begin and enable on LED
  MIDI.begin();
  digitalWrite(onLedPin, HIGH);
} // setup

/* *****************************************
 * Loop when Teensy is running
 * *****************************************/
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

/* *****************************************
 * Send a Program Change via MIDI
 * *****************************************/
void sendProgramChange(byte changeDirection) {
  // Change the current program up or down (not to exceed min or max)
  if (changeDirection >= 0) {
    // Up
    currentProgram = (currentProgram < maxProgram) ? currentProgram + 1 : minProgram;
  } else {
    // Down
    currentProgram = (currentProgram > minProgram) ? currentProgram - 1 : maxProgram;
  } // changeDirection

  // Send the program change via MIDI
  MIDI.sendProgramChange(currentProgram, midiChannel);
  Serial.println("MIDI Change sent.");
} // sendProgramChange

