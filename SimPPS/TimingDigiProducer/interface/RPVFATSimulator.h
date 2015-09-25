#ifndef RP_VFAT_SIMULATION_H
#define RP_VFAT_SIMULATION_H

#include <set>

#include "DataFormats/TotemRPDataTypes/interface/RPStripDigi.h"
//#include "DataFormats/TotemRPDataTypes/interface/RPDetTrigger.h"
#include "DataFormats/PPSTimingDataTypes/interface/RPLBarDigi.h"
#include "DataFormats/PPSTimingDataTypes/interface/RPTimingTrigger.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
//#include "SimTotem/RPDigiProducer/interface/RPSimTypes.h"
#include "SimPPS/TimingDigiProducer/interface/RPSimTypes.h"

class RPVFATSimulator
{
  public:
//    RPVFATSimulator(const edm::ParameterSet &params, RPDetId det_id);
   // void ConvertChargeToHits(const SimRP::strip_charge_map &signals, 
        //  SimRP::strip_charge_map_links_type &theSignalProvenance, 
      //    std::vector<RPStripDigi> &output_digi, 
    //      std::vector<RPDetTrigger> &output_trig, 
  //        SimRP::DigiPrimaryMapType &output_digi_links, 
//          SimRP::TriggerPrimaryMapType &output_trig_links);
 
          RPVFATSimulator(const edm::ParameterSet &params, TimingId det_id);
          void ConvertChargeToHits(const SimRP::strip_charge_map &signals,
          SimRP::strip_charge_map_links_type &theSignalProvenance,
          std::vector<RPLBarDigi> &output_digi,
          std::vector<RPTimingTrigger> &output_trig,
          SimRP::DigiPrimaryMapType &output_digi_links,
          SimRP::TriggerPrimaryMapType &output_trig_links);

  private:
    typedef std::set<unsigned short, std::less<unsigned short> > dead_strip_set;
    void SetDeadStrips();
    const edm::ParameterSet &params_;
    //RPDetId det_id_;
    TimingId det_id_;
    double dead_strip_probability_;
    bool dead_strips_simulation_on_;
    dead_strip_set dead_strips_;
    int verbosity_;
    
    int trigger_mode_;
    unsigned short strips_no_;
    double threshold_;
    short strips_per_section_;
    SimRP::TriggerContainer the_trig_cont_;
    SimRP::TriggerContainerLinkMap the_trig_cont_links_;
    bool links_persistence_;
};

#endif

