#ifndef SimPPS_TimingDigiProducer_PPSTimingDigiProducer_h
#define SimPPS_TimingDigiProducer_PPSTimingDigiProducer_h

// -*- C++ -*-
//
// Package:    PPSTimingDigiProducer
// Class:      PPSTimingDigiProducer
// 
/**\class PPSTimingDigiProducer PPSTimingDigiProducer.cc SimPPS/TimingDigiProducer/src/PPSTimingDigiProducer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Hubert NIEWIADOMSKI
//         Created:  Tue Mar 27 11:57:03 CEST 2007
// $Id: PPSTimingDigiProducer.h,v 1.6 2008/09/12 17:26:25 lgrzanka Exp $
//
//

#include "boost/shared_ptr.hpp"

// system include files
#include <memory>
#include <vector>
#include <map>
#include <string>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/Common/interface/EDProduct.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/TotemRPDataTypes/interface/RPStripDigi.h"
//#include "DataFormats/TotemRPDataTypes/interface/RPDetTrigger.h"
#include "DataFormats/PPSTimingDataTypes/interface/PPSTimingLBarDigi.h"
#include "DataFormats/PPSTimingDataTypes/interface/PPSTimingTrigger.h"
#include "SimPPS/TimingDigiProducer/interface/PPSSimTypes.h"

#include "SimPPS/TimingDigiProducer/interface/PPSDetDigitizer.h"
#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"

#include "DataFormats/Common/interface/DetSet.h"
//#include "SimPPS/TimingDigiProducer/interface/DeadChannelsManager.h"

//
// class decleration
//


namespace CLHEP {
  class HepRandomEngine;
}


class PPSTimingDigiProducer : public edm::EDProducer {
   public:
      explicit PPSTimingDigiProducer(const edm::ParameterSet&);
      ~PPSTimingDigiProducer();

   private:
      virtual void beginRun(edm::Run&, edm::EventSetup const&);
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
      std::vector<std::string> RP_hit_containers_;
      typedef std::map<unsigned int, std::vector<PSimHit> > simhit_map;
      typedef simhit_map::iterator simhit_map_iterator;
      simhit_map SimHitMap;
      
      edm::ParameterSet conf_;
//      std::map<RPDetId, boost::shared_ptr<RPDetDigitizer> > theAlgoMap;
      std::map<TimingId, boost::shared_ptr<PPSDetDigitizer> > theAlgoMap;
//      std::vector<edm::DetSet<RPStripDigi> > theDigiVector;
      std::vector<edm::DetSet<PPSTimingLBarDigi> > theDigiVector;
 //     std::vector<edm::DetSet<RPDetTrigger> > theTriggerVector;
      std::vector<edm::DetSet<PPSTimingTrigger> > theTriggerVector;
 
      CLHEP::HepRandomEngine* rndEngine;
      int verbosity_;

      /**
       * this variable answers the question whether given channel is dead or not
       */
//      DeadChannelsManager deadChannelsManager;

      /**
       * this variable indicates whether we take into account dead channels or simulate as if all
       * channels work ok (by default we do not simulate dead channels)
       */
      bool simulateDeadChannels;
};


#endif  //SimPPS_TimingDigiProducer_PPSTimingDigiProducer_h
