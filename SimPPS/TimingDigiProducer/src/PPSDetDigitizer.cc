#include <vector>
#include <iostream>
#include <math.h>

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimPPS/TimingDigiProducer/interface/PPSDetDigitizer.h"
#include "Geometry/TotemRPDetTopology/interface/RPTopology.h"


PPSDetDigitizer::PPSDetDigitizer(const edm::ParameterSet &params, CLHEP::HepRandomEngine& eng, TimingId det_id)
  : params_(params), det_id_(det_id)

{
  verbosity_ = params.getParameter<int>("PPSVerbosity");
  _links_persistence = params.getParameter<bool>("PPSDigiSimHitRelationsPresistence");

  thePPSPhotoelectronArrTime = new PPSPhotoelectronArrTime(params_, eng, det_id_);
  thePPSNINOSimulator = new PPSNINOSimulator(params_, det_id_);
}

PPSDetDigitizer::~PPSDetDigitizer()
{
  delete thePPSPhotoelectronArrTime;
  delete thePPSNINOSimulator;
}

void PPSDetDigitizer::run(const std::vector<PSimHit> &input, const std::vector<int> &input_links,
    std::vector<PPSTimingLBarDigi> &output_digi, std::vector<PPSTimingTrigger> &output_trig,
    SimPPSTiming::TimingDigiPrimaryMapType &output_digi_links,
    SimPPSTiming::TimingTriggerPrimaryMapType &output_trig_links)

{

  the_PhotoElectron_ArrTime_vec.clear();
  the_PhotoElectron_ArrTime_map_links_type.clear();

  bool links_persistence_checked = _links_persistence && input_links.size()==input.size();
  
  int input_size = input.size();

//  std::cout<<"input_size: "<<input_size<<", the_PhotoElectron_ArrTime_vec.size(): "<<the_PhotoElectron_ArrTime_vec.size()<<std::endl;

  for (int i=0; i<input_size; ++i)
  {

    if (links_persistence_checked)
       thePPSPhotoelectronArrTime->processHit(input[i], input_links[i], the_PhotoElectron_ArrTime_vec, the_PhotoElectron_ArrTime_map_links_type);
    else
       thePPSPhotoelectronArrTime->processHit(input[i], 0, the_PhotoElectron_ArrTime_vec, the_PhotoElectron_ArrTime_map_links_type);

  }

  std::cout<<"For His on LBarNumber: "<<PPSDetDigitizer::GetLBarNumber(det_id_)<<" , the number of photoelectron is: "<<the_PhotoElectron_ArrTime_vec.size()<<" and charge is: "<<(the_PhotoElectron_ArrTime_vec.size())*1.6*0.0001<<" fC"<<std::endl;

  const SimPPSTiming::PhotoElectron_ArrTime_vec theSignal1 = the_PhotoElectron_ArrTime_vec;
  SimPPSTiming::PhotoElectron_ArrTime_map_links_type theSignalProvenance1 = the_PhotoElectron_ArrTime_map_links_type;

  SimPPSTiming::PhotoElectron_ArrTime_vec afterNoise1;
//  if(noNoise)
    afterNoise1 = theSignal1;
//  else
//    afterNoise = theRPGaussianTailNoiseAdder->addNoise(theSignal1);

//  std::cout<<"the number of photoelectron is: "<<afterNoise1.size()<<std::endl;

  thePPSNINOSimulator->ConvertTimeToHits(afterNoise1, theSignalProvenance1,
        output_digi, output_trig, output_digi_links, output_trig_links);

}

int PPSDetDigitizer::GetLBarNumber(uint32_t decimal)
{
        int rem=0, iterator=0, LBar=0;
        char bin32[32];

         while (decimal!=0)
         {
               rem=decimal%2;
               decimal/=2;
               bin32[31-iterator]=rem;
               iterator+=1;
         }

         for (int i=13; i<19; i++) LBar+=((int)bin32[i])*(std::pow(2, 18-i));

         return LBar;
}

