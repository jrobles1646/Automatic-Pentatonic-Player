
///////////////////////////////////////////////////////////
//                    MelodyMaker.ino                    //
///////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////

#include "Section.h"

bool resetFlag = false;

void setup()
{
    //MIDI
    Serial.begin(115200);
    //Serial1.begin(115200);
    Serial1.begin(9600);

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(A1));
  pinMode(ledPinC, OUTPUT);
  pinMode(ledPinD, OUTPUT);
  pinMode(ledPinF, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinA, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(syncPin, INPUT);
  pinMode(resetPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(resetPin), reset, CHANGE);

  //Wait until Beat Chooser is ready
  while (Serial1.available() < 1);
  
  
}//end void setup()

void loop()
{
  
  Section test;

  //stall();
  while (true)
  {
    test.playSection();
    if (resetFlag)
    {
      test.shuffleMelodies();
      resetFlag = false;
      //stall();
    }
  }
  

 // midiEventPacket_t modulation = {0x0B, 0xB0 | 0, 1, 127};
 // midiEventPacket_t instr = {0x0C, 0xC0 | 0, 1, 0};

  
}//end void loop()

void reset()
{
  resetFlag = true;
  digitalWrite(ledPinC, HIGH);
  digitalWrite(ledPinD, HIGH);
  digitalWrite(ledPinF, HIGH);
  digitalWrite(ledPinG, HIGH);
  digitalWrite(ledPinA, HIGH);
}

void stall()
{
  int synchedState = 0;
  
  for (byte i = 0 ; i < 8; i++)
  {
  digitalWrite(ledPinC, HIGH);
  digitalWrite(ledPinD, HIGH);
  digitalWrite(ledPinF, HIGH);
  digitalWrite(ledPinG, HIGH);
  digitalWrite(ledPinA, HIGH);
  delay(70);
  digitalWrite(ledPinC, LOW);
  digitalWrite(ledPinD, LOW);
  digitalWrite(ledPinF, LOW);
  digitalWrite(ledPinG, LOW);
  digitalWrite(ledPinA, LOW);
  delay(70);
  }
}
