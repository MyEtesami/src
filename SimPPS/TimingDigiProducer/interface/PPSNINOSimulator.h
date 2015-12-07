#ifndef PPS_NINO_SIMULATION_H
#define PPS_NINO_SIMULATION_H

#include <set>

#include "DataFormats/TotemRPDataTypes/interface/RPStripDigi.h"
//#include "DataFormats/TotemRPDataTypes/interface/RPDetTrigger.h"
#include "DataFormats/PPSTimingDataTypes/interface/PPSTimingLBarDigi.h"
#include "DataFormats/PPSTimingDataTypes/interface/PPSTimingTrigger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
//#include "SimTotem/RPDigiProducer/interface/RPSimTypes.h"
#include "SimPPS/TimingDigiProducer/interface/PPSSimTypes.h"

class PPSNINOSimulator
{
  public:
 
          PPSNINOSimulator(const edm::ParameterSet &params, TimingId det_id);

          void ConvertTimeToHits(const SimPPSTiming::PhotoElectron_ArrTime_vec &signals,
          SimPPSTiming::PhotoElectron_ArrTime_map_links_type &theSignalProvenance,
          std::vector<PPSTimingLBarDigi> &output_digi,
          std::vector<PPSTimingTrigger> &output_trig,
          SimPPSTiming::TimingDigiPrimaryMapType &output_digi_links,
          SimPPSTiming::TimingTriggerPrimaryMapType &output_trig_links);

  private:
    typedef std::set<unsigned short, std::less<unsigned short> > dead_strip_set;
    const edm::ParameterSet &params_;
    TimingId det_id_;
    int verbosity_;

    double PulseWidthFunc(double InputCharge);
    double TimeWalkFunc(double pulse_width);
    double LeadingEdgeFunc(double InputCharge);
    int LBarNr(TimingId DetId);
    
    int trigger_mode_;
    double NINOthreshold_;
    SimPPSTiming::TriggerContainer the_trig_cont_;
    SimPPSTiming::TimingTriggerContainerLinkMap the_trig_cont_links_;
    bool links_persistence_;
};

#endif

