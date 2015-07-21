#ifndef PPS_myPPSTimingNumberingScheme_h
#define PPS_myPPSTimingNumberingScheme_h

#include "SimG4CMS/PPS/interface/myPPSTimingOrganization.h"

class myPPSTimingNumberingScheme : public myPPSTimingOrganization {

public:
  myPPSTimingNumberingScheme(int i);
  ~myPPSTimingNumberingScheme();
	 
//  virtual unsigned int GetUnitID(const G4Step* aStep) const ;

};

#endif  //PPS_myPPSTimingNumberingScheme_h
