#pragma once

/* *****************************************
 * MIDI/Footswitch Settings
 * *****************************************/
MIDI_CREATE_DEFAULT_INSTANCE();

// Select MIDI Channel
static const byte midiChannel = 1; // MIDI Channel to use

// Set the current program, min and max programs
const unsigned int maxProgram = 63;
const unsigned int minProgram = 43;
unsigned int currentProgram   = minProgram;
