///////////////////////////////////////////////////////////
//                       BassSection.cpp                     //
///////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////

#include "bassSection.h"

//Section() constructor
bassSection::bassSection()
{
  motif1 = bassMeasure(1, 8); //start at root note
  makeFunkGrooveA(motif1);

  motif2 = bassMeasure(motif1.getLastPitch(), motif1.getLastRhythm());
  makeFunkGrooveB(motif2);

  expansion1 = bassMeasure(motif2.getLastPitch(), motif2.getLastRhythm());
  makeFunkGrooveA(expansion1);

  expansion2 = bassMeasure(expansion1.getLastPitch(), expansion1.getLastRhythm());
  makeFunkGrooveB(expansion2);
}//end constructor Section::Section()

void bassSection::playSection()
{
  
  motif1.playMeasure();
  motif2.playMeasure();
  motif1.playMeasure();
  motif2.playMeasure();

  expansion1.playMeasure();
  expansion2.playMeasure();
  
}//end member function Section::playSection()


void bassSection::shuffleHarmonies()
{
  motif1.shuffle(12);
  motif2.shuffle(motif1.getLastPitch());
  expansion1.shuffle(motif2.getLastPitch());
  expansion2.shuffle(expansion1.getLastPitch());
}
