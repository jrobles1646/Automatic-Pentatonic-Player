
#include "bassMeasure.h"

//Creates a measure for the first half the R&B v1 groove.
//This should only be used for even measures
void makeRBGrooveA(bassMeasure& m)
{
  Note* rideCymbal;
  Note* drum;

  //Create 16 ride cymbal beats
  for (byte i = 0; i < 16; i++)
  {
    rideCymbal = new Note();
    rideCymbal->velocity =  84;
    rideCymbal->initRhythm = 1;
    rideCymbal->rhythmLeft = 1;
    rideCymbal->frequency = 0;
    rideCymbal->pitch = 42;
    rideCymbal->channel = 9;  //Set to channel 10
    m.cymbalNote[i] = rideCymbal;
  }

  //Create a bass drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 4;
    drum->rhythmLeft = 4;
    drum->frequency = 0;
    drum->pitch = 35;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[0] = drum;
  m.drumNote[1] = drum;
  m.drumNote[2] = drum;
  m.drumNote[3] = drum;

  //Create a snare drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 3;
    drum->rhythmLeft = 3;
    drum->frequency = 0;
    drum->pitch = 38;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[4] = drum;
  m.drumNote[5] = drum;
  m.drumNote[6] = drum;

  //Create a bass drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 1;
    drum->rhythmLeft = 1;
    drum->frequency = 0;
    drum->pitch = 35;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[7] = drum;
  
  //Create a bass drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 4;
    drum->rhythmLeft = 4;
    drum->frequency = 0;
    drum->pitch = 35;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[8] = drum;
  m.drumNote[9] = drum;
  m.drumNote[10] = drum;
  m.drumNote[11] = drum;

  
  //Create a snare drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 4;
    drum->rhythmLeft = 4;
    drum->frequency = 0;
    drum->pitch = 38;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[12] = drum;
  m.drumNote[13] = drum;
  m.drumNote[14] = drum;
  m.drumNote[15] = drum;
  

  //Set beats to match pulse
  m.cymbalNote[0]->velocity+=6;
  m.cymbalNote[4]->velocity+=2;
  m.cymbalNote[8]->velocity+=4;
  m.cymbalNote[12]->velocity+=2;

  m.drumNote[0]->velocity+=6;
  m.drumNote[4]->velocity+=2;
  m.drumNote[8]->velocity+=4;
  m.drumNote[12]->velocity+=2;
}//end void Measure::makeRBGroove1 a()

//Creates a measure for the second half the R&B v1 groove.
//This should only be used for odd measures.
void makeRBGrooveB(bassMeasure& m)
{
  Note* rideCymbal;
  Note* drum;

  //Create 14 ride cymbal beats
  for (byte i = 0; i < 14; i++)
  {
    rideCymbal = new Note();
    rideCymbal->velocity =  84;
    rideCymbal->initRhythm = 1;
    rideCymbal->rhythmLeft = 1;
    rideCymbal->frequency = 0;
    rideCymbal->pitch = 42;
    rideCymbal->channel = 9;  //Set to channel 10
    m.cymbalNote[i] = rideCymbal;
  }

  //Create an open hi-hat beat
  rideCymbal = new Note();
    rideCymbal->velocity =  84;
    rideCymbal->initRhythm = 2;
    rideCymbal->rhythmLeft = 2;
    rideCymbal->frequency = 0;
    rideCymbal->pitch = 46;
    rideCymbal->channel = 9;  //Set to channel 10
  m.cymbalNote[14] = rideCymbal;
  m.cymbalNote[15] = rideCymbal;
  
  //Create a bass drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 4;
    drum->rhythmLeft = 4;
    drum->frequency = 0;
    drum->pitch = 35;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[0] = drum;
  m.drumNote[1] = drum;
  m.drumNote[2] = drum;
  m.drumNote[3] = drum;

  //Create a snare drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 3;
    drum->rhythmLeft = 3;
    drum->frequency = 0;
    drum->pitch = 38;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[4] = drum;
  m.drumNote[5] = drum;
  m.drumNote[6] = drum;

  //Create a bass drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 1;
    drum->rhythmLeft = 1;
    drum->frequency = 0;
    drum->pitch = 35;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[7] = drum;
  
  //Create a bass drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 4;
    drum->rhythmLeft = 4;
    drum->frequency = 0;
    drum->pitch = 35;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[8] = drum;
  m.drumNote[9] = drum;
  m.drumNote[10] = drum;
  m.drumNote[11] = drum;

  
  //Create a snare drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 4;
    drum->rhythmLeft = 4;
    drum->frequency = 0;
    drum->pitch = 38;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[12] = drum;
  m.drumNote[13] = drum;
  m.drumNote[14] = drum;
  m.drumNote[15] = drum;
  
  //Set beats to match pulse
  m.cymbalNote[0]->velocity+=6;
  m.cymbalNote[4]->velocity+=2;
  m.cymbalNote[8]->velocity+=4;
  m.cymbalNote[12]->velocity+=2;

  m.drumNote[0]->velocity+=6;
  m.drumNote[4]->velocity+=2;
  m.drumNote[8]->velocity+=4;
  m.drumNote[12]->velocity+=2;
}//end class function void Measure::makeRBGroove1b()

void makeFunkGrooveA(bassMeasure& m)
{
  Note* rideCymbal;
  Note* drum;

  for (byte i = 0; i < 16; i = i + 2)
  {
    rideCymbal = new Note();
    if (i%2 == 0)
      rideCymbal->velocity =  105;
    else
      rideCymbal->velocity =  84;
    rideCymbal->initRhythm = 2;
    rideCymbal->rhythmLeft = 2;
    rideCymbal->frequency = 0;
    rideCymbal->pitch = 42;
    rideCymbal->channel = 9;  //Set to channel 10
    m.cymbalNote[i] = rideCymbal;
    m.cymbalNote[i+1] = rideCymbal;
  }//end loop for (byte i = 0; i < 8; i++)

  //Create a bass drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 2;
    drum->rhythmLeft = 2;
    drum->frequency = 0;
    drum->pitch = 35;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[0] = drum;
  m.drumNote[1] = drum;

  //Create a bass drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 2;
    drum->rhythmLeft = 2;
    drum->frequency = 0;
    drum->pitch = 35;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[2] = drum;
  m.drumNote[3] = drum;

  //Rest note
    drum = new Note();
    drum->velocity =  0;
    drum->initRhythm = 1;
    drum->rhythmLeft = 1;
    drum->frequency = 0;
    drum->pitch = 37; //Rimshot
    drum->channel = 9;  //Set to channel 10
  m.drumNote[4] = drum;

    
  //Create a snare ghost drum
  drum = new Note();
    drum->velocity =  38;
    drum->initRhythm = 2;
    drum->rhythmLeft = 2;
    drum->frequency = 0;
    drum->pitch = 38;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[5] = drum;
  m.drumNote[6] = drum;

    
  //Create a snare drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 1;
    drum->rhythmLeft = 1;
    drum->frequency = 0;
    drum->pitch = 38;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[7] = drum;

  //Rest note
    drum = new Note();
    drum->velocity =  0;
    drum->initRhythm = 1;
    drum->rhythmLeft = 1;
    drum->frequency = 0;
    drum->pitch = 37; //Rimshot
    drum->channel = 9;  //Set to channel 10
  m.drumNote[8] = drum;

  //Create a snare drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 1;
    drum->rhythmLeft = 1;
    drum->frequency = 0;
    drum->pitch = 38;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[9] = drum;
  
  //Create a bass drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 2;
    drum->rhythmLeft = 2;
    drum->frequency = 0;
    drum->pitch = 35;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[10] = drum;
  m.drumNote[11] = drum;

  //Create a rimshot
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 1;
    drum->rhythmLeft = 1;
    drum->frequency = 0;
    drum->pitch = 37; //Rimshot
    drum->channel = 9;  //Set to channel 10
  m.drumNote[12] = drum;

  //Create a bass drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 2;
    drum->rhythmLeft = 2;
    drum->frequency = 0;
    drum->pitch = 35;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[13] = drum;
  m.drumNote[14] = drum;

  
  //Create a snare drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 1;
    drum->rhythmLeft = 1;
    drum->frequency = 0;
    drum->pitch = 38;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[15] = drum;
}//end class function void makeFunkGrooveA()

void makeFunkGrooveB(bassMeasure& m)
{
    Note* rideCymbal;
  Note* drum;

  for (byte i = 0; i < 16; i = i + 2)
  {
    rideCymbal = new Note();
    if (i%2 == 0)
      rideCymbal->velocity =  105;
    else
      rideCymbal->velocity =  84;
    rideCymbal->initRhythm = 2;
    rideCymbal->rhythmLeft = 2;
    rideCymbal->frequency = 0;
    rideCymbal->pitch = 42;
    rideCymbal->channel = 9;  //Set to channel 10
    m.cymbalNote[i] = rideCymbal;
    m.cymbalNote[i+1] = rideCymbal;
  }//end loop for (byte i = 0; i < 8; i++)

  //Create a bass drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 2;
    drum->rhythmLeft = 2;
    drum->frequency = 0;
    drum->pitch = 35;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[0] = drum;
  m.drumNote[1] = drum;

  //Create a bass drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 2;
    drum->rhythmLeft = 2;
    drum->frequency = 0;
    drum->pitch = 35;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[2] = drum;
  m.drumNote[3] = drum;

  //Rest note
    drum = new Note();
    drum->velocity =  0;
    drum->initRhythm = 1;
    drum->rhythmLeft = 1;
    drum->frequency = 0;
    drum->pitch = 37; //Rimshot
    drum->channel = 9;  //Set to channel 10
  m.drumNote[4] = drum;

    
  //Create a snare ghost drum
  drum = new Note();
    drum->velocity =  38;
    drum->initRhythm = 2;
    drum->rhythmLeft = 2;
    drum->frequency = 0;
    drum->pitch = 38;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[5] = drum;
  m.drumNote[6] = drum;

    
  //Create a snare drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 1;
    drum->rhythmLeft = 1;
    drum->frequency = 0;
    drum->pitch = 38;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[7] = drum;

  //Rest note
    drum = new Note();
    drum->velocity =  0;
    drum->initRhythm = 1;
    drum->rhythmLeft = 1;
    drum->frequency = 0;
    drum->pitch = 37; //Rimshot
    drum->channel = 9;  //Set to channel 10
  m.drumNote[8] = drum;

  //Create a snare drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 1;
    drum->rhythmLeft = 1;
    drum->frequency = 0;
    drum->pitch = 38;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[9] = drum;
  
  //Create a bass drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 2;
    drum->rhythmLeft = 2;
    drum->frequency = 0;
    drum->pitch = 35;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[10] = drum;
  m.drumNote[11] = drum;

  //Create a rimshot
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 3;
    drum->rhythmLeft = 3;
    drum->frequency = 0;
    drum->pitch = 37; //Rimshot
    drum->channel = 9;  //Set to channel 10
  m.drumNote[12] = drum;
  m.drumNote[13] = drum;
  m.drumNote[14] = drum;
  
  //Create a snare drum
  drum = new Note();
    drum->velocity =  84;
    drum->initRhythm = 1;
    drum->rhythmLeft = 1;
    drum->frequency = 0;
    drum->pitch = 38;
    drum->channel = 9;  //Set to channel 10
  m.drumNote[15] = drum;
}//end class function void makeFunkGrooveB()
