#include <MIDI.h>
#include <Bounce.h>

#include "pins.h"
#include "buttons.h"
#include "midiSettings.h"

// Takes a footswitch up and down and turns it into
// a MIDI signal for a Digitech Whammy
static const byte version = 1;

/* *****************************************
 * Run once upon boot of Teensy
 * *****************************************/
void setup() {
  Serial.print("Whammy MIDI: Version: ");
  Serial.println(version);

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
  // Change the current program up or down
  if (changeDirection >= 0) {
    currentProgram = (currentProgram < maxProgram) ? currentProgram++ : minProgram;
  } else {
    currentProgram = (currentProgram > minProgram) ? currentProgram-- : maxProgram;
  } // changeDirection

  // Send the program change via MIDI
  MIDI.sendProgramChange(currentProgram, midiChannel);
  Serial.println("MIDI Change sent.");
} // sendProgramChange

