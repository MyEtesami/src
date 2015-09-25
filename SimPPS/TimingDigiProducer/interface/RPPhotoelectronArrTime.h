#ifndef SimPPS_PPSTiming_PPS_PHOTOELECTRON_ARRTIME_H
#define SimPPS_PPSTiming_PPS_PHOTOELECTRON_ARRTIME_H

#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimTracker/Common/interface/SiG4UniversalFluctuation.h"
#include "SimPPS/TimingDigiProducer/interface/RPSimTypes.h"
#include "SimPPS/TimingDigiProducer/interface/RPAmplitudeCal.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

namespace CLHEP{
	class HepRandomEngine;
}

class RPPhotoelectronArrTime
{
  public:
    RPPhotoelectronArrTime(const edm::ParameterSet &params, CLHEP::HepRandomEngine& eng, TimingId det_id);
    ~RPPhotoelectronArrTime();
    void processHit(const PSimHit& hit, int PSimHitIndex);
    inline const SimRP::PhotoElectron_ArrTime_vec &dumpSignal()
          {return the_PhotoElectron_ArrTime_vec_;}
    inline SimRP::PhotoElectron_ArrTime_map_links_type &dumpLinks()
          {return the_PhotoElectron_ArrTime_map_links_type_;}
  private:
    const edm::ParameterSet &params_;
    CLHEP::HepRandomEngine& rndEngine;
    TimingId _det_id;
    double tof_;
    double tts_;
    double the_photoelectron_amplitude;
    bool links_persistence_;

    RPAmplitudeCal* theRPAmplitudeCal;
    SimRP::PhotoElectron_ArrTime_vec the_PhotoElectron_ArrTime_vec_;
    SimRP::PhotoElectron_ArrTime_map_links_type the_PhotoElectron_ArrTime_map_links_type_;

    int verbosity_;
};

#endif  //SimPPS_TimingDigiProducer_RP_PHOTOELECTRON_ARRTIME_H
