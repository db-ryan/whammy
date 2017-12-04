#pragma once

/*
   MIDI/Footswitch Settings
*/

MIDI_CREATE_DEFAULT_INSTANCE();

// Select MIDI Channel
static const byte midiChannel = 1; // MIDI Channel to use

// Set the current channel
const unsigned int maxProgram = 63;
const unsigned int minProgram = 43;
unsigned int currentProgram   = minProgram;

struct MidiSettings {
  //int programNumber[21];
  const int programNumber[21] = {
    43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63
  }; // programNumber

  const char* lcdDisplay[21] = {
    "UP 2 OCT",
    "UP OCT",
    "UP 5th",
    "UP 4th",
    "DOWN 2nd",
    "DOWN 4th",
    "DOWN 5th",
    "DOWN OCT",
    "DOWN 2OCT",
    "DIVE BOMB",
    "DEEP",
    "SHALOW",
    "UP 2nd\nUP 3rd",
    "UP b3rd\nUP 3rd",
    "UP 3rd\nUP 4th",
    "UP 4th\nUP 5th",
    "UP 5th\nUP 6th",
    "UP 5th\nUP 7th",
    "DOWN 4th\nDOWN 3rd",
    "DOWN 5th\nDOWN 4th",
    "DOWN OCT\nUP OCT"
  }; // lcdDisplay
  //char* lcdDisplay[21];
}; // MidiSettings
