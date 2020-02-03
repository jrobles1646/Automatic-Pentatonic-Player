///////////////////////////////////////////////////////////
//                        Measure.h                      //
///////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////

//MIDI Channel 1 for Melody
//MIDI Channel 2 for Harmony
//MIDI Channel 10 Drumset

#ifndef Measure_h
#define Measure_h

#include "pitches.h"
#include "Arduino.h"
#include "Note.h"
#include <MIDIUSB.h>

//Pentatonic C scale
const unsigned int freqScale[] = {0, NOTE_G3, NOTE_A3, NOTE_C4,
                                  NOTE_D4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_C5, NOTE_D5, NOTE_F5, NOTE_G5,
                                  NOTE_A5, NOTE_C6, NOTE_D6
                                 }; //15 values

const byte midiScale[] = {53, 55, 57, 60,
                          62, 65, 67, 69, 72, 74, 77, 79,
                          81, 84, 86
                         }; //15 values pentatonic

//TODO: Change pins so they are synced up

const byte ledPinA =  4;      //LED pin used for an A
const byte ledPinC =  5;      //LED pin used for a C
const byte ledPinD =  6;      //LED pin used for a D
const byte ledPinF =  7;      //LED pin used for an F
const byte ledPinG =  8;      //LED pin used for a G
const byte buzzerPin = 12;  //
const byte modPin = A0;
const byte syncPin = 9;
const byte resetPin = 2;

/*
  //Minor blues scale
  const int freqScale[] = {0, NOTE_G3, NOTE_AS3, NOTE_C4,
  NOTE_DS4, NOTE_F4, NOTE_FS4, NOTE_G4, NOTE_AS4, NOTE_C5, NOTE_DS5, NOTE_F5,
  NOTE_FS5, NOTE_G5, NOTE_AS5}; //15 values

  const byte midiScale[] = {53, 55, 58, 60,
  63, 65, 66, 67, 68, 72, 75, 77,
  78, 79, 80}; //15 values blues*/

/*Storage structure:
   2B x 16
   2B x 16
   2B x 16
   2B,
*/

class Measure
{
  private:
    Note* melodyNote[16];
    Note* drumNote[16];
    Note* cymbalNote[16];

    byte getNextRhythm(byte); //Carefully selects what the next rhythm value should be
    byte getNextVelocity(byte); //Carefully selects what the next velocity should be
    byte getNextPitch(byte);  //Carefully selects what the next pitch should be (returns an index to use for freqScale[] and midiScale[])


    //MIDI Functions
    void noteOn(Note*);
    void noteOff(Note*);

  public:
    Measure();
    Measure(byte, byte);
    //~Measure();
    void makeMeasure(byte, byte);
    void playMeasure();
    byte getLastPitch();
    byte getLastRhythm();
    void printSim();    //For debugging use: Prints out the notes instead of playing them
    bool isSynched();
    void setOctaveUp();
    void setOctaveDown();
    void shuffle(byte);

    //Groove makers
    friend void makeRBGrooveA(Measure&);
    friend void makeRBGrooveB(Measure&);
    friend void makeFunkGrooveA(Measure&);
    friend void makeFunkGrooveB(Measure&);

    //Functions for external hardware
    void writeToLEDs(byte);
    void clearLEDs();

};//end class Measure

#endif
