#pragma once

/*
   MIDI/Footswitch Settings
*/

MIDI_CREATE_DEFAULT_INSTANCE();

// Select MIDI Channel
static const byte midiChannel = 1; // MIDI Channel to use

// Set the current channel
const unsigned int maxProgram = 20;
const unsigned int minProgram = 0;
unsigned int currentProgram   = minProgram;

struct MidiSettings {
  //int programNumber[21];
  const int programNumber[21] = {
    43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63
  }; // programNumber

  const char* lcdDisplayFirstLine[21] = {
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "_/ Up 2nd",
    "_/ Up b3rd",
    "_/ Up 3rd",
    "_/ Up 4th",
    "_/ Up 5th",
    "_/ Up 5th",
    "_/ Down 4th",
    "_/ Down 5th",
    "_/ Down OCT"
  }; // lcdDisplayFirstLine

  const char* lcdDisplaySecondLine[21] = {
    "__ Up 2 OCT",
    "__ Up OCT",
    "__ Up 5th",
    "__ Up 4th",
    "__ Down 2nd",
    "__ Down 4th",
    "__ Down 5th",
    "__ Down OCT",
    "__ Down 2 OCT",
    "__ Dive Bomb",
    "Deep",
    "Shallow",
    "__ Up 3rd",
    "__ Up 3rd",
    "__ Up 4th",
    "__ Up 5th",
    "__ Up 6th",
    "__ Up 7th",
    "__ Down 3rd",
    "__ Down 4th",
    "__ Up OCT"
  }; // lcdDisplaySecondLine
}; // MidiSettings
