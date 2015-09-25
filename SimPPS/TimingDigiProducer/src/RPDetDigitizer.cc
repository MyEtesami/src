#include <vector>
#include <iostream>

#include "FWCore/ParameterSet/interface/ParameterSet.h"
//#include "SimTotem/RPDigiProducer/interface/RPDetDigitizer.h"
#include "SimPPS/TimingDigiProducer/interface/RPDetDigitizer.h"
#include "Geometry/TotemRPDetTopology/interface/RPTopology.h"


//RPDetDigitizer::RPDetDigitizer(const edm::ParameterSet &params, CLHEP::HepRandomEngine& eng, RPDetId det_id, const edm::EventSetup& iSetup)
RPDetDigitizer::RPDetDigitizer(const edm::ParameterSet &params, CLHEP::HepRandomEngine& eng, TimingId det_id)
  : params_(params), det_id_(det_id)

{
  verbosity_ = params.getParameter<int>("RPVerbosity");
  numStrips = RPTopology().DetStripNo();
  theNoiseInElectrons = params.getParameter<double>("RPEquivalentNoiseCharge300um");
  theStripThresholdInE = params.getParameter<double>("RPVFATThreshold");
  noNoise = params.getParameter<bool>("RPNoNoise");
  misalignment_simulation_on_ = params_.getParameter<bool>("RPDisplacementOn");
  _links_persistence = params.getParameter<bool>("RPDigiSimHitRelationsPresistence");

std::cout<<"verbosity_ "<<verbosity_<<" numStrips "<<numStrips<<" theNoiseInElectrons "<<theNoiseInElectrons<<" theStripThresholdInE "<<theStripThresholdInE<<" noNoise "<<noNoise<<" misalignment_simulation_on_ "<<misalignment_simulation_on_<<" _links_persistence "<<_links_persistence<<std::endl;

  theRPPhotoelectronArrTime = new RPPhotoelectronArrTime(params_, eng, det_id_);
std::cout<<"$$$$$$$$$$$$$$$$$$"<<std::endl;
  theRPGaussianTailNoiseAdder = new RPGaussianTailNoiseAdder(numStrips, 
      theNoiseInElectrons, theStripThresholdInE, verbosity_);
std::cout<<"1111111111111111111111"<<std::endl;
  theRPPileUpSignals = new RPPileUpSignals(params_, det_id_);
std::cout<<"2222222222222222222"<<std::endl;
  theRPVFATSimulator = new RPVFATSimulator(params_, det_id_);
std::cout<<"3333333333333333333"<<std::endl;
  theRPHitChargeConverter = new RPHitChargeConverter(params_, eng, det_id_);
std::cout<<"4444444444444444444"<<std::endl;
//  theRPDisplacementGenerator = new RPDisplacementGenerator(params_, det_id_, iSetup);
}

RPDetDigitizer::~RPDetDigitizer()
{
  delete theRPPhotoelectronArrTime;
  delete theRPGaussianTailNoiseAdder;
  delete theRPPileUpSignals;
  delete theRPVFATSimulator;
  delete theRPHitChargeConverter;
//  delete theRPDisplacementGenerator;
}

// void RPDetDigitizer::run(const std::vector<PSimHit> &input, const std::vector<int> &input_links, 
  //  std::vector<RPStripDigi> &output_digi, std::vector<RPDetTrigger> &output_trig, 
  //  SimRP::DigiPrimaryMapType &output_digi_links, 
//    SimRP::TriggerPrimaryMapType &output_trig_links)
void RPDetDigitizer::run(const std::vector<PSimHit> &input, const std::vector<int> &input_links,
    std::vector<RPLBarDigi> &output_digi, std::vector<RPTimingTrigger> &output_trig,
    SimRP::DigiPrimaryMapType &output_digi_links,
    SimRP::TriggerPrimaryMapType &output_trig_links)

{
  if(verbosity_)
    std::cout<<"RPDetDigitizer "<<det_id_<<" received input.size()="<<input.size()<<std::endl;
  theRPPileUpSignals->reset();
  
  bool links_persistence_checked = _links_persistence && input_links.size()==input.size();
  
  int input_size = input.size();
  for (int i=0; i<input_size; ++i)
  {
    SimRP::strip_charge_map the_strip_charge_map;
    the_strip_charge_map = theRPHitChargeConverter->processHit(input[i]); 
/*
    if(misalignment_simulation_on_)
      the_strip_charge_map = theRPHitChargeConverter->processHit(
            theRPDisplacementGenerator->Displace(input[i]));
    else
      the_strip_charge_map = theRPHitChargeConverter->processHit(input[i]);
*/      
    if(verbosity_)
      std::cout<<"RPHitChargeConverter "<<det_id_<<" returned hits="<<the_strip_charge_map.size()<<std::endl;
    if(links_persistence_checked)
      theRPPileUpSignals->add(the_strip_charge_map, input_links[i]);
    else
      theRPPileUpSignals->add(the_strip_charge_map, 0);

/*
    SimRP::PhotoElectron_ArrTime_vec the_PhotoElectron_ArrTime_vec;

    SimRP::PhotoElectron_ArrTime_map_links_type the_PhotoElectron_ArrTime_map_links_type;
*/

    if(links_persistence_checked)
      theRPPhotoelectronArrTime->processHit(input[i], input_links[i]);
    else
      theRPPhotoelectronArrTime->processHit(input[i], 0);
  }

  const SimRP::strip_charge_map &theSignal = theRPPileUpSignals->dumpSignal();
  SimRP::strip_charge_map_links_type &theSignalProvenance = theRPPileUpSignals->dumpLinks();

      std::cout<<"########PPSTiming for "<<det_id_<<" returned hits= "<<theSignal.size()<<std::endl;
      std::cout<<"$$$$$$$$PPSTiming for "<<det_id_<<" returned hits= "<<theSignalProvenance.size()<<std::endl;

  SimRP::strip_charge_map afterNoise;
  if(noNoise)
    afterNoise = theSignal;
  else
    afterNoise = theRPGaussianTailNoiseAdder->addNoise(theSignal);

  theRPVFATSimulator->ConvertChargeToHits(afterNoise, theSignalProvenance,
        output_digi, output_trig, output_digi_links, output_trig_links);

/*
  const SimRP::PhotoElectron_ArrTime_vec &theSignal1 = theRPPhotoelectronArrTime->dumpSignal();
  SimRP::PhotoElectron_ArrTime_map_links_type &theSignalProvenance1 = theRPPhotoelectronArrTime->dumpLinks();

  if (verbosity_){
     std::cout<<"*****PPSTiming for DetId("<<det_id_<<") returned number of photoelectrons: "<<theSignal1.size()<<std::endl;
     std::cout<<"$$$$$PPSTiming for DetId("<<det_id_<<") returned number of photoelectrons: "<<theSignalProvenance1.size()<<std::endl;
  }

  std::cout<<"*****PPSTiming for DetId("<<det_id_<<") returned number of photoelectrons: "<<theSignal1.size()<<std::endl;
  std::cout<<"$$$$$PPSTiming for DetId("<<det_id_<<") returned number of photoelectrons: "<<theSignalProvenance1.size()<<std::endl;

  SimRP::PhotoElectron_ArrTime_vec afterNoise1;
//  if(noNoise)
    afterNoise1 = theSignal1;
//  else
//    afterNoise = theRPGaussianTailNoiseAdder->addNoise(theSignal);


  theRPNINOSimulator->ConvertChargeToHits(afterNoise1, theSignalProvenance1,
        output_digi, output_trig, output_digi_links, output_trig_links);
*/


}
