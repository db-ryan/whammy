#include <MIDI.h>
#include <Bounce.h>

// Takes a footswitch up and down and turns it into
// a MIDI signal for a Digitech Whammy
static const byte version = 1;
static const byte programChangeUp = 1;
static const byte programChangeDown = -1;

/*
   Pin Definitions
*/
const int onLedPin = 13; // LED on Teensy
static const byte programChangeUpPin = 2; // footswitch up pin
static const byte programChangeDownPin = 3; // footswitch down pin

/*
   MIDI/Footswitch Settings
*/
MIDI_CREATE_DEFAULT_INSTANCE();
static const byte midiChannel = 1; // MIDI Channgel to use
Bounce buttonUp = Bounce(programChangeUpPin, 10); // 10ms debounce
Bounce buttonDown = Bounce(programChangeDownPin, 10); // 10ms debounce
unsigned byte currentProgram = 43;

/*
   Run once upon boot of the Teensy
*/
void setup() {
  Serial.print("Whammy MIDI: Version: ");
  Serial.println(version);

  /*
   * Set Pin Modes
   */
  pinMode(ledPin, OUTPUT);
  pinMode(programChangeUpPin, INPUT_PULLUP);
  pinMode(programChangeDownPin, INPUT_PULLUP);

  /*
   * Set MIDI to begin and enable on LED
   */
  MIDI.begin();
  digitalWrite(onLedPin, HIGH);
} // setup

/*
   Loop when Teensy is running
*/
void loop() {
  bool buttonUpPressed = buttonUp.update() && buttonUp.fallingEdge();
  bool buttonDownPressed = buttonDown.update() && buttonDown.fallingEdge();

  // If Up button is pressed
  if (buttonUpPressed) {
    Serial.println("Button Up pressed.");
    sendProgramChange(1);
  } // if buttonUp

  // If Down button is pressed
  if (buttonDownPressed) {
    Serial.println("Button Down pressed.");
    sendProgramChange(-1);
  } // if buttonDown

} // loop

/*
 * Send a Program Change via MIDI
 */
void sendProgramChange(int changeDirection) {
  if (changeDirection >= 0) {
    currentProgram++;
  } else {
    currentProgram--;
  } // changeDirection

  MIDI.sendProgramChange(currentProgram, midiChannel);
  Serial.println("MIDI Change sent.");
} // sendProgramChange

