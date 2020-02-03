#include "bassMeasure.h"

class bassSection
{
  private:
  bassMeasure motif1;
  bassMeasure motif2;
  bassMeasure expansion1;
  bassMeasure expansion2;
  
  public:
  bassSection();
  void playSection();
  void shuffleHarmonies();
};//end class Section
