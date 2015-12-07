#ifndef SimPPS_TimingDigiProducer_PPS_DET_DIGITIZER_H
#define SimPPS_TimingDigiProducer_PPS_DET_DIGITIZER_H

//#ifndef SimTotem_RPDigiProducer_RP_DET_DIGITIZER_H
//#define SimTotem_RPDigiProducer_RP_DET_DIGITIZER_H

#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include <vector>
#include <string>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

//#include "SimGeneral/HepPDT/interface/HepPDTable.h"
#include "SimTracker/Common/interface/SiG4UniversalFluctuation.h"
#include "SimGeneral/NoiseGenerators/interface/GaussianTailNoiseGenerator.h"

//#include "SimTotem/RPDigiProducer/interface/RPSimTypes.h"
#include "SimPPS/TimingDigiProducer/interface/PPSSimTypes.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/PPSTimingDataTypes/interface/PPSTimingTrigger.h"
#include "DataFormats/PPSTimingDataTypes/interface/PPSTimingLBarDigi.h"

#include "DataFormats/TotemRPDataTypes/interface/RPStripDigi.h"
#include "DataFormats/TotemRPDataTypes/interface/RPDetTrigger.h"

#include "SimPPS/TimingDigiProducer/interface/PPSPhotoelectronArrTime.h"
#include "SimPPS/TimingDigiProducer/interface/PPSNINOSimulator.h"


namespace CLHEP{
        class HepRandomEngine;
}


class PPSDetDigitizer
{
  public:
 PPSDetDigitizer(const edm::ParameterSet &params, CLHEP::HepRandomEngine& eng, TimingId det_id);
void run(const std::vector<PSimHit> &input, const std::vector<int> &input_links,
        std::vector<PPSTimingLBarDigi> &output_digi, std::vector<PPSTimingTrigger> &output_trig,
        SimPPSTiming::TimingDigiPrimaryMapType &output_digi_links,
        SimPPSTiming::TimingTriggerPrimaryMapType &output_trig_links);

    ~PPSDetDigitizer();
      
  private:
    PPSPhotoelectronArrTime *thePPSPhotoelectronArrTime;
    PPSNINOSimulator *thePPSNINOSimulator;

  private:
    const edm::ParameterSet &params_;

    TimingId det_id_; 
    int verbosity_;
    bool  _links_persistence;

    int GetLBarNumber(uint32_t decimal_value);

    SimPPSTiming::PhotoElectron_ArrTime_vec the_PhotoElectron_ArrTime_vec;

    SimPPSTiming::PhotoElectron_ArrTime_map_links_type the_PhotoElectron_ArrTime_map_links_type;
};

#endif  //SimPPS_TimingDigiProducer_PPS_DET_DIGITIZER_H
