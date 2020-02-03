///////////////////////////////////////////////////////////
//                      Measure.cpp                      //
///////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////

#include "bassMeasure.h"

bool beatToggle = true;  //Whether or not to play backbeat
int incomingMod = 0;  //Modulation value from analog
midiEventPacket_t instr = {0x0C, 0xC0 | 1, 32, 32};

//Measure() default constructor
bassMeasure::bassMeasure(){}

//Measure(byte, byte) constructor
bassMeasure::bassMeasure(byte startPitch, byte startRhythm)
{
  makeMeasure(startPitch, startRhythm);
}//end Measure::Measure(int startNote)

void bassMeasure::makeMeasure(byte startPitch, byte startRhythm)
{
  int randomInt = random(8) + 4;
  byte measureCapacity = 0;    //Current capacity of measure
  byte nextNoteRhythm = startRhythm;    //Rhythm value of next note
  byte nextNotePitch = startPitch;  //Pitch index of next note
  byte nextNoteVelocity = 127;  //Velocity of next note
  Note* newNote;  //Store pointer of new notes here

  //Fill measure with pitched notes
  while (measureCapacity < 16)
  {
    nextNoteRhythm = getNextRhythm(nextNoteRhythm);
    nextNotePitch = getNextPitch(nextNotePitch);
    
    //Rhythm values should not exceed 16
    if (measureCapacity + nextNoteRhythm > 16)
    {
      //Get a rhythm value that can fit in measure
      //TODO: The default value is 1/16 note
      nextNoteRhythm = 4;
    }

    //Create new Note object and initialize values
    newNote = new Note();
    newNote->initRhythm = nextNoteRhythm;
    newNote->rhythmLeft = nextNoteRhythm;
    newNote->pitchIndex = nextNotePitch;
    if (nextNotePitch == 0)
    {
      newNote->velocity = 0;
      newNote->pitch = 0;
      newNote->frequency = 0;
    }
    else
    {
      newNote->velocity= nextNoteVelocity;
      newNote->pitch = midiScale[nextNotePitch];
      newNote->frequency = freqScale[nextNotePitch];
    }
    newNote->channel = 1;

    //Place note in the appropriate spaces within the measure
    for (byte i = measureCapacity; i < measureCapacity + nextNoteRhythm; i++)
      melodyNote[i] = newNote;

    measureCapacity += nextNoteRhythm;
  }//end loop while (measureCapacity < 16)

}//end member function int Measure::makeNextNote(int noteIndex)

// Plays the measure by going through all notes and sending them to USB or buzzer
void bassMeasure::playMeasure()
{
  midiEventPacket_t event;
  int synchedState = 0;
  MidiUSB.sendMIDI(instr);

  byte serialValue = 0;
  //Check to see if the backbeat should be played
  if (Serial1.available() > 0)
  {
    serialValue = Serial1.read();
    if (serialValue  == 2)
      beatToggle = true;
    else
      beatToggle = false;
  }
  
   while (synchedState == LOW)
    {
      synchedState = digitalRead(syncPin);
    }
  
  for (byte thisNote = 0; thisNote < 16; thisNote++)
  {
    incomingMod = analogRead(modPin)/4;
    //Change modulation wave
    event = {0x0B, 0xB0 | 1, 1, incomingMod};
    MidiUSB.sendMIDI(event);
    //Play send note commands
    noteOn(melodyNote[thisNote]);

    if (beatToggle == true)
    {
      noteOn(drumNote[thisNote]);
      noteOn(cymbalNote[thisNote]);
    }


    //Tempo is adjusted by potentiometer value
    while (synchedState == HIGH)
    {
      synchedState = digitalRead(syncPin);
    }
    
    MidiUSB.flush();

     while (synchedState == LOW)
    {
      synchedState = digitalRead(syncPin);
    }
    
    //Send command to turn off notes
    noteOff(melodyNote[thisNote]);
    if (beatToggle == true)
    {
      noteOff(drumNote[thisNote]);
      noteOff(cymbalNote[thisNote]);
    }

    while (synchedState == HIGH)
    {
      synchedState = digitalRead(syncPin);
    }
    
    MidiUSB.flush();

     while (synchedState == LOW)
    {
      synchedState = digitalRead(syncPin);
    }
  }//end for (byte thisNote = 0; thisNote < 16; thisNote++)

    
}//end member function void Measure::playMeasure()

//Returns the pitchIndex of the last note of the measure
byte bassMeasure::getLastPitch()
{
  return melodyNote[15]->pitchIndex;
  //return 10;
}//end class function byte Measure::getLastPitch()

//Returns the initial rhythm of the last note of the measure
byte bassMeasure::getLastRhythm()
{
  return melodyNote[15]->initRhythm;
}//end class function byte Measure::getLastRhythm()

//Sends the note to play through the buzzer and/or USB MIDI device. If the note is sustained
//(still playing) from the previous time it was called, it will not play again so that it will
//simulate its intended rhythm value.
void bassMeasure::noteOn(Note* note)
{
  //Make sure not to play the same note when its already playing
  if (note->rhythmLeft < note->initRhythm)
  {
    //Deduct rhythm time and leave function
    note->rhythmLeft--;
    return;
  }//End conditional if

  
  byte notePitchIndex = note->pitchIndex;
  unsigned int noteFrequency = note->frequency;

  //Send command through USB Midi
    if (note->pitch!=0)
  {
    midiEventPacket_t noteOn = {0x09, 0x90 | note->channel, note->pitch, note->velocity};
    MidiUSB.sendMIDI(noteOn);
  }

  //Send command to buzzer only if it is a pitched note
  if (noteFrequency != 0)
  {
    tone(bPin, noteFrequency);
  
    if(notePitchIndex == 1 || notePitchIndex == 4)
      digitalWrite(ledPinA,HIGH);
    else if(notePitchIndex == 2)
      digitalWrite(ledPinC,HIGH);
    else
      digitalWrite(ledPinD,HIGH);
  }
  
  note->rhythmLeft--;
}//end private class function void Measure::noteOn(byte pitch, byte velocity)

//Commands the note to stop playing through the buzzer and/or USB MIDI device. If the note is sustained
//(still playing) from the previous time it was called, the note will not turn off so that it
//simulates the full rhythm value.
void bassMeasure::noteOff(Note* note)
{
  //If the note should still be playing, we don't want to turn it off 
  if (note->rhythmLeft > 0)
  {
    return;
  }

  //Send command through USB MIDI
    if (note->pitch!=0)
  {
    midiEventPacket_t noteOff = {0x08, 0x80 |note->channel, note->pitch, note->velocity};
    MidiUSB.sendMIDI(noteOff);
  }

  //Send command to buzzer only if it is a pitched note
  if (note->frequency != 0)
  {
    noTone(bPin);
    
    digitalWrite(ledPinA,LOW);
    digitalWrite(ledPinC,LOW);
    digitalWrite(ledPinD,LOW);
  }

  //Reset rhythmLeft to initial value for when it plays again
  note->rhythmLeft = note->initRhythm;

}//end private class method void Measure::noteOff(byte pitch, byte velocity)

//Carefully selects what the next rhythm value should be
byte bassMeasure::getNextRhythm(byte previousVal)
{
  //Get random value
  int randNum = random(100);

  //--If the previous value was a 1/16 note--//
  if(previousVal == 16)
  {
    //50% Choosing whole note again
    if (randNum < 50)
      return 16;

    //25% choosing 1/2 note next
    else if (randNum < 75)
      return 8;

    //25% choosing 1/4 note next
    else
      return 4;
  }//end conditional if(previousVal == 0)

  //--If the previous value was a 1/2 note--//
  else if (previousVal ==  8)
  {
    //50% Choosing 1/2 note again
    if (randNum < 50)
      return 8;

    //25% choosing whole note next
    else if (randNum < 75)
      return 16;

    //25% choosing quarter note next
    else if (randNum < 90)
      return 4;
      
  }//end conditional if (previousVal ==  8)

  //--If the previous value was a 1/4 note--//
  else if (previousVal ==  4)
  {
    //50% Choosing 1/4 note again
    if (randNum < 50)
      return 4;

    //25% choosing 1/2 note next
    else if (randNum < 75)
      return 8;
      
    //10% choosing whole note next
    else
      return 16;
  }//end conditional if (previousVal ==  2)

  //--An unknown value was passed so we default it to 1/4--//
  else
    return 4;
}//end class function byte Measure::getNextRhythm(byte previousVal)

//Carefully selects what the next velocity should be
byte bassMeasure::getNextVelocity(byte previousVal)
{
  int randomNum = random(100);
  byte nextVelocity;  //Value of next velocity is stored here

  //If the previous value was a rest note, make it random
  if (previousVal == 0)
    nextVelocity = random(40,127);
  //Otherwise, temporarily set next velocity as the previous value
  else
    nextVelocity = previousVal;  //Value of next velocity is stored here

  //--Start random selection--//
  //80% of staying in the same velocity
  if (randomNum < 80)
    nextVelocity;

  //5% of going +10
  else if (randomNum < 85)
    nextVelocity += 10;

  //5% of going -10
  else if (randomNum < 90)
    nextVelocity -= 10;
    
  //%10 of being a rest note
  else
    nextVelocity = 0;

  //If the next selected value is above 127, select another high value
  if (nextVelocity > 127)
    nextVelocity = (byte)random(80,127);

  //If the next selected value is below 40, select a different low value
  if (nextVelocity < 40 && nextVelocity != 0)
    nextVelocity = (byte)random(40,80);

  //--end random selection--//
  return nextVelocity;   
}//end class function byte Measure::getNextVelocity(byte previousVal)

void bassMeasure::shuffle(byte startPitch)
{
  byte startIndex = 0;
  byte endIndex = 15;
  int randInt = random(0,2);
  Note* temp = NULL;
  byte nextNotePitch = getNextPitch(startPitch);  //Pitch index of next note

   //1/2 chance to reverse rhythm order
  if (randInt == 0)
    while (startIndex < endIndex) 
    { 
      temp = melodyNote[startIndex];  
      melodyNote[startIndex] = melodyNote[endIndex]; 
      melodyNote[endIndex] = temp; 
      startIndex++; 
      endIndex--; 
    }  

  randInt = random(0,2);
  //1/2 chance to re-arrange pitches
  if (randInt == 0)
  {
    temp = melodyNote[0];
    melodyNote[0]->pitchIndex = nextNotePitch;
    melodyNote[0]->pitch = midiScale[nextNotePitch];
    melodyNote[0]->frequency = freqScale[nextNotePitch];
    for (byte i = 1; i < 16; i++)
    {
       if (temp != melodyNote[i])
       {
          nextNotePitch = getNextPitch(nextNotePitch);
          temp = melodyNote[i];
          melodyNote[i]->pitchIndex = nextNotePitch;

          if (nextNotePitch == 0)
          {
            melodyNote[i]->velocity = 0;
            melodyNote[i]->pitch = 0;
            melodyNote[i]->frequency = 0;
          }
          else
          {     
            melodyNote[i]->velocity = 127;
            melodyNote[i]->pitch = midiScale[nextNotePitch];
            melodyNote[i]->frequency = freqScale[nextNotePitch];
          }
       }//end if (temp != melodyNote[i])
    }//end for (byte i = 1; i < 16; i++)
  }//end if (randInt == 0)
}

//Carefully selects what the next pitch should be (returns an index to use for freqScale[] and midiScale[])
byte bassMeasure::getNextPitch(byte previousVal)
{
  randomSeed(analogRead(0));
  int randomNum = random(100);
  byte nextPitch = previousVal;  //Index of next pitch is stored here

  //40% of going one note above
  if (randomNum < 40)
    nextPitch += 1;

  //40% of going one note below
  else if (randomNum < 80)
    nextPitch -= 1;

  // 10% of going two notes above
  else if (randomNum < 90)
    nextPitch += 2;

  //10% of going 2 notes below;
  else
    nextPitch -=2;

  //If the next selected pitch is out of bounds, choose a random index
  if (nextPitch > 4 || nextPitch < 0)
    nextPitch = random(5);

  return nextPitch;
}//end member function byte Measure::getNextPitch(int previousVal)
