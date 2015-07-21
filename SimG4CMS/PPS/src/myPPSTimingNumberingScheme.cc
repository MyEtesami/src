#include "SimG4CMS/PPS/interface/myPPSTimingNumberingScheme.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include <iostream>
// #define debug

myPPSTimingNumberingScheme::myPPSTimingNumberingScheme(int i)
{
  edm::LogInfo("TotemRP") << " Creating myPPSTimingNumberingScheme" << std::endl;
}

myPPSTimingNumberingScheme::~myPPSTimingNumberingScheme()
{
  edm::LogInfo("TotemRP") << " Deleting myPPSTimingNumberingScheme" << std::endl;
}
