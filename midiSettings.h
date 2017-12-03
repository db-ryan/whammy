#pragma once

/*
   MIDI/Footswitch Settings
*/
MIDI_CREATE_DEFAULT_INSTANCE();
static const byte midiChannel = 1; // MIDI Channgel to use
Bounce buttonUp = Bounce(programChangeUpPin, 10); // 10ms debounce
Bounce buttonDown = Bounce(programChangeDownPin, 10); // 10ms debounce
unsigned int currentProgram = 43;
