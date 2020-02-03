///////////////////////////////////////////////////////////
//                      Measure.cpp                      //
///////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////

#include "Measure.h"

bool beatToggle = false;  //Whether or not to play backbeat
int incomingMod = 0;  //Modulation value from analog

//Measure() default constructor
Measure::Measure(){}
/*
Measure::~Measure()
{
    for (int i = 0; i < 16; i++)
  {
    delete melodyNote[i];
    delete drumNote[i];
    delete cymbalNote[i];
  }
}*/

//Measure(int,int) constructor
Measure::Measure(byte startPitch, byte startRhythm)
{    int randomInt = random(8) + 4;
  int measureCapacity = 0;    //Current capacity of measure
  int nextNoteRhythm = startRhythm;    //Rhythm value of next note
  int nextNotePitch = startPitch;  //Pitch index of next note
  byte nextNoteVelocity = getNextVelocity((byte)(100));  //Velocity of next note
  Note* newNote;  //Store pointer of new notes here

  //Fill measure with pitched notes
  while (measureCapacity < 16)
  {
    nextNoteRhythm = getNextRhythm(nextNoteRhythm);
    nextNotePitch = getNextPitch(nextNotePitch);
    nextNoteVelocity = 127; //getNextVelocity(nextNoteVelocity);
    
    //Rhythm values should not exceed 16
    if (measureCapacity + nextNoteRhythm > 16)
    {
      //Get a rhythm value that can fit in measure
      //TODO: The default value is 1/16 note
      nextNoteRhythm = 1;
    }

    //Create new Note object and initialize values
    newNote = new Note();
    newNote->initRhythm = nextNoteRhythm;
    newNote->rhythmLeft = nextNoteRhythm;
    newNote->pitchIndex = nextNotePitch;
    newNote->pitch = midiScale[nextNotePitch];
    newNote->frequency = freqScale[nextNotePitch];
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
    newNote->channel = 0;

    //Place note in the appropriate spaces within the measure
    for (int i = measureCapacity; i < measureCapacity + nextNoteRhythm; i++)
      melodyNote[i] = newNote;

    measureCapacity += nextNoteRhythm;
  }//end loop while (measureCapacity < 16)

}//end Measure::Measure(int startNote)

void Measure::makeMeasure(byte startPitch, byte startRhythm)
{
    int randomInt = random(8) + 4;
  int measureCapacity = 0;    //Current capacity of measure
  int nextNoteRhythm = startRhythm;    //Rhythm value of next note
  int nextNotePitch = startPitch;  //Pitch index of next note
  byte nextNoteVelocity = getNextVelocity((byte)(100));  //Velocity of next note
  Note* newNote;  //Store pointer of new notes here

  //Fill measure with pitched notes
  while (measureCapacity < 16)
  {
    nextNoteRhythm = getNextRhythm(nextNoteRhythm);
    nextNotePitch = getNextPitch(nextNotePitch);
    nextNoteVelocity = 127; //getNextVelocity(nextNoteVelocity);
    
    //Rhythm values should not exceed 16
    if (measureCapacity + nextNoteRhythm > 16)
    {
      //Get a rhythm value that can fit in measure
      //TODO: The default value is 1/16 note
      nextNoteRhythm = 1;
    }

    //Create new Note object and initialize values
    newNote = new Note();
    newNote->initRhythm = nextNoteRhythm;
    newNote->rhythmLeft = nextNoteRhythm;
    newNote->pitchIndex = nextNotePitch;
    newNote->pitch = midiScale[nextNotePitch];
    newNote->frequency = freqScale[nextNotePitch];
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
    newNote->channel = 0;

    //Place note in the appropriate spaces within the measure
    for (int i = measureCapacity; i < measureCapacity + nextNoteRhythm; i++)
      melodyNote[i] = newNote;

    measureCapacity += nextNoteRhythm;
  }//end loop while (measureCapacity < 16)

}

// Plays the measure by going through all notes and sending them to USB or buzzer
void Measure::playMeasure()
{
  
  midiEventPacket_t event;
  int synchedState = 0;
  byte serialValue = 0;
    //Check to see if the backbeat should be played (also clears buffer)
  if (Serial1.available() > 0)
  {
    serialValue = Serial1.read();
    if (serialValue == 1)
      beatToggle = true;
    else
      beatToggle = false;
  }
  
  while (synchedState == LOW)
    {
      synchedState = digitalRead(syncPin);
    }
  
  for (int thisNote = 0; thisNote < 16; thisNote++)
  {
    incomingMod = analogRead(modPin)/4;
    //Change modulation wave
    event = {0x0B, 0xB0 | 0, 1, incomingMod};
    MidiUSB.sendMIDI(event);

    //Play send note commands
    noteOn(melodyNote[thisNote]);

    if (beatToggle == true)
    {
      noteOn(drumNote[thisNote]);
      noteOn(cymbalNote[thisNote]);
    }
    //Send notes to MIDI Device to play at the same time
    
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
    
  }//end for (int thisNote = 0; thisNote < 16; thisNote++)
    
}//end member function void Measure::playMeasure()


//Sends the note to play through the buzzer and/or USB MIDI device. If the note is sustained
//(still playing) from the previous time it was called, it will not play again so that it will
//simulate its intended rhythm value.
void Measure::noteOn(Note* note)
{
  //Make sure not to play the same note when its already playing
  if (note->rhythmLeft < note->initRhythm)
  {
    //Deduct rhythm time and leave function
    note->rhythmLeft--;
    return;
  }//End conditional if


  //Send command through USB Midi
  if (note->pitch!=0)
  {
    midiEventPacket_t noteOn = {0x09, 0x90 | note->channel, note->pitch, note->velocity};
    MidiUSB.sendMIDI(noteOn);
  }

  //Send command to buzzer only if it is a pitched note
  if (note->frequency != 0)
  {
    tone(buzzerPin, freqScale[note->pitchIndex]);
      
    //Flash the bulb corresponding to this note
    writeToLEDs(note->pitchIndex);
  }

  
  note->rhythmLeft--;
}//end private class function void Measure::noteOn(byte pitch, byte velocity)

//Commands the note to stop playing through the buzzer and/or USB MIDI device. If the note is sustained
//(still playing) from the previous time it was called, the note will not turn off so that it
//simulates the full rhythm value.
void Measure::noteOff(Note* note)
{
  //If the note should still be playing, we don't want to turn it off 
  if (note->rhythmLeft > 0)
  {
    return;
  }

  //Send command through USB MIDI
    if (note->pitch!=0)
  {
  midiEventPacket_t noteOff = {0x08, 0x80 |note->channel, midiScale[note->pitchIndex], note->velocity};
  MidiUSB.sendMIDI(noteOff);
  }
  
  //Send command to buzzer only if it is a pitched note
  if (note->frequency != 0)
  {
    noTone(buzzerPin);
    
    //Turn all LEDs off
    clearLEDs();
  }


  //Reset rhythmLeft to initial value for when it plays again
  note->rhythmLeft = note->initRhythm;

}//end private class method void Measure::noteOff(byte pitch, byte velocity)

//Flashes a bulb depending on the index of a note
void Measure::writeToLEDs(byte index)
{
  
  if (index == 2 || index == 7 || index == 12)
  {
    digitalWrite(ledPinA, HIGH);
    return;
  }
  
  else if (index == 5 || index == 10)
  {
     digitalWrite(ledPinF, HIGH);
     return;
  }

  else if (index == 1 || index == 6 || index == 11)
  {
    digitalWrite(ledPinG, HIGH);
    return;
  }

  else if (index == 3 || index == 8 || index == 13)
  {
    digitalWrite(ledPinC, HIGH);
    return;
  }

  //if (index == 4 || index == 9 || index == 14)
  else
  {
    digitalWrite(ledPinD, HIGH);
    return;
  }

}//end void Measure::writeToLEDs(int index)

//Turn off all LEDs
void Measure::clearLEDs()
{
  digitalWrite(ledPinC, LOW);
  digitalWrite(ledPinD, LOW);
  digitalWrite(ledPinF, LOW);
  digitalWrite(ledPinG, LOW);
  digitalWrite(ledPinA, LOW);
}//end void Measure::clearLEDs()

//Returns the pitchIndex of the last note of the measure
byte Measure::getLastPitch()
{
  return melodyNote[15]->pitchIndex;
}//end class function int Measure::getLastPitch()

//Returns the initial rhythm of the last note of the measure
byte Measure::getLastRhythm()
{
  return melodyNote[15]->initRhythm;
}//end class function int Measure::getLastRhythm()

//Carefully selects what the next rhythm value should be
byte Measure::getNextRhythm(byte previousVal)
{
  //Get random value
  int randNum = random(100);

  //--If the previous value was a 1/16 note--//
  if(previousVal == 1)
  {
    //50% Choosing 1/16 note again
    if (randNum < 50)
      return 1;

    //30% choosing 1/8 note next
    else if (randNum < 80)
      return 2;

    //15% choosing 1/4 note next
    else if (randNum < 95)
      return 4;

    //5% choosing dotted 1/4 note next
    else
      return 6;
  }//end conditional if(previousVal == 0)

  //--If the previous value was a 1/8 note--//
  else if (previousVal ==  2)
  {
    //30% Choosing 1/8 note again
    if (randNum < 30)
      return 2;

    //30% choosing 1/4 note next
    else if (randNum < 60)
      return 4;

    //30% choosing  note next
    else if (randNum < 90)
      return 1;

    //10% choosing note next
    else
      return 6;
  }//end conditional if (previousVal ==  1)

  //--If the previous value was a 1/4 note--//
  else if (previousVal ==  4)
  {
    //30% Choosing 1/4 note again
    if (randNum < 30)
      return 4;

    //30% choosing 1/8 note next
    else if (randNum < 60)
      return 2;

    //30% choosing dotted 1/4 note next
    else if (randNum < 90)
      return 6;

    //10% choosing 1/16 note next
    else
      return 1;
  }//end conditional if (previousVal ==  2)

  //--If the previous value was a dotted 1/4 note--//
  else if (previousVal ==  6)
  {
    //10% Choosing dotted 1/14 note again
    if (randNum < 10)
      return 6;

    //45% choosing 1/8 note next
    else if (randNum < 55)
      return 2;

    //40% choosing 1/4 note next
    else if (randNum < 95)
      return 4;

    //5% choosing 1/16 note next
    else
      return 1;
  }//end conditional if (previousVal ==  3)

  //--An unknown value was passed so we default it to 1/16--//
  else
    return 1;
}//end class function int Measure::getNextRhythm(int previousVal)

//Carefully selects what the next velocity should be
byte Measure::getNextVelocity(byte previousVal)
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

//Carefully selects what the next pitch should be (returns an index to use for freqScale[] and midiScale[])
byte Measure::getNextPitch(byte previousVal)
{
  randomSeed(analogRead(0));
  int randomNum = random(100);
  byte nextPitch = previousVal;  //Index of next pitch is stored here

  //30% of going one note above
  if (randomNum < 30)
    nextPitch += 1;

  //30% of going one note below
  else if (randomNum < 60)
    nextPitch -= 1;

  // 10% of going two notes above
  else if (randomNum < 70)
    nextPitch += 2;

  //10% of going two notes below
  else if (randomNum < 80)
    nextPitch -= 2;

  //5% of going 3 notes above
  else if (randomNum < 85)
    nextPitch += 3;

  //5% of going 3 notes below
  else if (randomNum < 90)
    nextPitch -= 3;

  //5% of being a rest note
  else if (randomNum < 95)
    nextPitch = 0;

  //5% of being the same note;
  else
    nextPitch;

  //If the next selected pitch is out of bounds, choose a random index
  if (nextPitch > 14 || nextPitch < 0)
  {
    int randInt = random(0,3);
    //Make next pitch a rest note
    if (randInt == 0)
      nextPitch = 0;
    //Make next pitch A4
    else
      nextPitch = 7;
  }

  return nextPitch;
}//end member function int Measure::getNextPitch(int previousVal)


void Measure::setOctaveUp()
{
  Note* previousNote = melodyNote[0];
  melodyNote[0]->pitch+=12;
  for (byte i = 1; i < 16; i++)
  {
    if(previousNote != melodyNote[i])
    {
      previousNote = melodyNote[i];
      melodyNote[i]->pitch+=12;
    }
  }
}
void Measure::setOctaveDown()
{
    Note* previousNote = melodyNote[0];
  melodyNote[0]->pitch-=12;
  for (byte i = 1; i < 16; i++)
  {
    if(previousNote != melodyNote[i])
    {
      previousNote = melodyNote[i];
      melodyNote[i]->pitch-=12;
    }
  }
}

void Measure::shuffle(byte startPitch)
{
  byte startIndex = 0;
  byte endIndex = 15;
  int randInt = random(0,2);
  Note* temp = NULL;
  byte nextNotePitch = getNextPitch(startPitch);  //Pitch index of next note

   //1/2 chance to reverse rhythm order
  if (true)
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
  if (true)
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

//For debugging use: Prints out the notes to serial monitor instead of playing them
void Measure::printSim()
{
  for (int i = 0; i < 16; i++)
  {
    Serial.print("ADDRESS: ");
    Serial.println((int)melodyNote[i]);
    
    Serial.print("RHYTHM: ");
    Serial.print(melodyNote[i]->initRhythm);
    Serial.print(", ");
    Serial.println(melodyNote[i]->rhythmLeft);
    melodyNote[i]->rhythmLeft--;

    Serial.print("FREQUENCY: ");
    Serial.print(melodyNote[i]->pitchIndex);
    Serial.print(", PITCH: ");
    Serial.println(melodyNote[i]->pitch);
    Serial.print("VELOCITY: ");
    Serial.println(melodyNote[i]->velocity);
  }//end loop for (int i = 0; i < 16; i++)
}//end class function void Measure::printSim()
