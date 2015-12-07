#ifndef SimPPS_PPSTiming_PPS_PHOTOELECTRON_ARRTIME_H
#define SimPPS_PPSTiming_PPS_PHOTOELECTRON_ARRTIME_H

#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimTracker/Common/interface/SiG4UniversalFluctuation.h"
#include "SimPPS/TimingDigiProducer/interface/PPSSimTypes.h"
#include "SimPPS/TimingDigiProducer/interface/PPSAmplitudeCal.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

namespace CLHEP{
	class HepRandomEngine;
}

class PPSPhotoelectronArrTime
{
  public:
    PPSPhotoelectronArrTime(const edm::ParameterSet &params, CLHEP::HepRandomEngine& eng, TimingId det_id);
    ~PPSPhotoelectronArrTime();
    void reset(SimPPSTiming::PhotoElectron_ArrTime_vec &the_PhotoElectron_ArrTime_vec_, SimPPSTiming::PhotoElectron_ArrTime_map_links_type &the_PhotoElectron_ArrTime_map_links_type_);
    void processHit(const PSimHit& hit, int PSimHitIndex, SimPPSTiming::PhotoElectron_ArrTime_vec &the_PhotoElectron_ArrTime_vec_, SimPPSTiming::PhotoElectron_ArrTime_map_links_type &the_PhotoElectron_ArrTime_map_links_type_);

  private:
    const edm::ParameterSet &params_;
    CLHEP::HepRandomEngine& rndEngine;
    TimingId _det_id;
    double tof_;
    double tts_;
    double the_photoelectron_amplitude;
    bool links_persistence_;
    PPSAmplitudeCal* thePPSAmplitudeCal;

    int verbosity_;
};

#endif  //SimPPS_TimingDigiProducer_PPS_PHOTOELECTRON_ARRTIME_H
