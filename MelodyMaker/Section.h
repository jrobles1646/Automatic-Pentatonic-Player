///////////////////////////////////////////////////////////
//                        Section.h                      //
///////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////

//Section.h

#ifndef Section_h
#define Section_h

#include "Measure.h"

class Section
{
  private:
  Measure motif1;
  Measure motif2;
  Measure expansion1;
  Measure expansion2;
  public:
  Section();
  void playSection();
  void shuffleMelodies();
};//end class Section

#endif
