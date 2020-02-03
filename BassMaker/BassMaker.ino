//MelodyMaker.ino

///////////////////////////////////////////////////////////
//                                    //
///////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////

#include "bassSection.h"

bool resetFlag = false;

void setup() {
    //Buzzer
   // Serial.begin(9600);

    //MIDI
    Serial.begin(115200);
    Serial1.begin(9600);

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(13));
  pinMode(syncPin, INPUT);
  pinMode(syncPin, INPUT);
  pinMode(ledPinA, OUTPUT);
  pinMode(ledPinC, OUTPUT);
  pinMode(ledPinD, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(resetPin), reset, CHANGE);
 
  //Wait until Beat Chooser is ready
  while (Serial1.available() < 1)
  {
    random(0,100);
  }
}

void loop()
{

  bassSection test;
  //stall();
  while (true)
  {
    test.playSection();
    if (resetFlag == true)
    {
      test.shuffleHarmonies();
      resetFlag = false;
      //stall();
    }
  }
  
}//end void loop()

void reset()
{
  resetFlag = true;
    digitalWrite(ledPinA,HIGH);
    digitalWrite(ledPinC,HIGH);
    digitalWrite(ledPinD,HIGH);
}

void stall()
{
  int synchedState = 0;
  
  for (byte i = 0 ; i < 4; i++)
  {
    while (synchedState == HIGH)
    {
      synchedState = digitalRead(syncPin);
    }
    digitalWrite(ledPinA,HIGH);
    digitalWrite(ledPinC,HIGH);
    digitalWrite(ledPinD,HIGH);

    while (synchedState == LOW)
    {
      synchedState = digitalRead(syncPin);
    }
    digitalWrite(ledPinA,LOW);
    digitalWrite(ledPinC,LOW);
    digitalWrite(ledPinD,LOW);
  }
}
