///////////////////////////////////////////////////////////
//                       Section.cpp                     //
///////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////

#include "Section.h"

//Section() constructor
Section::Section()
{
  //Get random value for a rhythm value
  int randInt1 = random(5,13), randInt2 =  random(2, 5);
  //Set first measure as A4 and random rhythm value
  motif1 = Measure(randInt1, randInt2);
  makeRBGrooveA(motif1);

  motif2 = Measure(motif1.getLastPitch(), motif1.getLastRhythm());
  makeRBGrooveB(motif2);

  expansion1 = Measure(motif2.getLastPitch(), motif2.getLastRhythm());
  makeRBGrooveA(expansion1);

  expansion2 = Measure(expansion1.getLastPitch(), expansion1.getLastRhythm());
  makeRBGrooveB(expansion2);
}//end constructor Section::Section()

//Play the section by calling all of its Measure's playMeasure() functions
void Section::playSection()
{
  int randInt = random(0,2);
  motif1.playMeasure();
  motif2.playMeasure();

  if (randInt == 0)
  {
    motif1.setOctaveUp();
    motif2.setOctaveUp();
    motif1.playMeasure();
    motif2.playMeasure();
    motif1.setOctaveDown();
    motif2.setOctaveDown();
  }
  else
  {
    motif1.setOctaveDown();
    motif2.setOctaveDown();
    motif1.playMeasure();
    motif2.playMeasure();
    motif1.setOctaveUp();
    motif2.setOctaveUp();
  }

  expansion1.playMeasure();
  expansion2.playMeasure();
}//end member function Section::playSection()


void Section::shuffleMelodies()
{
  int randInt1 = random(6,12);
  motif1.shuffle(randInt1);
  motif2.shuffle(motif1.getLastPitch());
  expansion1.shuffle(motif2.getLastPitch());
  expansion2.shuffle(expansion1.getLastPitch());
}
