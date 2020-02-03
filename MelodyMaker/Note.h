///////////////////////////////////////////////////////////
//                        Note.h                         //
///////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////

#ifndef NOTE_H
#define NOTE_H

struct Note
{
  byte initRhythm; //4 = 1/4, 2 = 1/8, 1 = 1/16, 6 = dotted 1/4
  byte rhythmLeft; //Decrements by one after a 1/16 time passed
  byte pitchIndex; //Index of pitch for use in freqScale[] or midiScale[]
  byte pitch; //MIDI note number (0-127)
  byte channel; //MIDI Channel (0-15 corresponds to channels 1-16)
  byte velocity;  //Note velocity (0-127)
  unsigned int frequency;  //Frequency of note for buzzer to play
};//end struct Note

#endif

/*Storage structure:
 * 1B, 1B,
 * 1B, 1B,
 * 1B, 1B,
 * 2B,
 */
