///////////////////////////////////////////////////////////
//                        bassMeasure.h                      //
///////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////

//MIDI Channel 1 for Melody
//MIDI Channel 2 for Harmony
//MIDI Channel 10 Drumset

//#ifndef Measure_h
//#define Measure_h

#include "pitches.h"
#include "Arduino.h"
#include "Note.h"
#include <MIDIUSB.h>

const unsigned int freqScale[] = {NOTE_D3, NOTE_A2, NOTE_C2, NOTE_D2,
NOTE_A3}; //15 values


const byte midiScale[] = {38, 45, 48, 50, 57};

const byte syncPin = 7;
const byte ledPinA = 10;
const byte ledPinC = 11;
const byte ledPinD = 12;
const byte bPin = 8;  //Pin for buzzer
const byte resetPin = 2;
const byte modPin = A0;

class bassMeasure
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
  bassMeasure();
  bassMeasure(byte,byte);
  void makeMeasure(byte,byte);
  void playMeasure();
  byte getLastPitch(); 
  byte getLastRhythm();
  void shuffle(byte);
  void printSim();    //For debugging use: Prints out the notes instead of playing them

  //Groove makers
  friend void makeRBGrooveA(bassMeasure&);
  friend void makeRBGrooveB(bassMeasure&);
  friend void makeFunkGrooveA(bassMeasure&);
  friend void makeFunkGrooveB(bassMeasure&);

};//end class Measure

//#endif
