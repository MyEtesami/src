#include "SimPPS/TimingDigiProducer/interface/RPPhotoelectronArrTime.h"
#include "SimPPS/TimingDigiProducer/interface/RPAmplitudeCal.h"
#include "Geometry/TotemRPDetTopology/interface/RPHepPDTWrapper.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "DataFormats/GeometryVector/interface/LocalVector.h"
#include "Geometry/TotemRPDetTopology/interface/RPTopology.h"
#include "TRandom3.h"


RPPhotoelectronArrTime::RPPhotoelectronArrTime(const edm::ParameterSet &params,  CLHEP::HepRandomEngine& eng, 
    TimingId det_id) : params_(params), rndEngine(eng) , _det_id(det_id)
{
  verbosity_ = params.getParameter<int>("RPVerbosity");

  theRPAmplitudeCal = new RPAmplitudeCal(params, eng, det_id);

  tof_ = params.getParameter<double>("RPPhotoElectronTOF");

  tts_ = params.getParameter<double>("RPPhotoElectronTTS");

  links_persistence_ = params.getParameter<bool>("RPDigiSimHitRelationsPresistence");

}

RPPhotoelectronArrTime::~RPPhotoelectronArrTime(){
  delete theRPAmplitudeCal;
}

void RPPhotoelectronArrTime::processHit(const PSimHit& hit, int PSimHitIndex)
{

  the_photoelectron_amplitude = theRPAmplitudeCal->HitToAmplitude(hit);

std::cout<<"**************the_photoelectron_amplitude is: "<<the_photoelectron_amplitude<<std::endl;
std::cout<<"PSimHitIndex: "<<PSimHitIndex<<std::endl;

  for (int Rnd_It = 0; Rnd_It < int(the_photoelectron_amplitude); Rnd_It++){

      the_PhotoElectron_ArrTime_vec_.push_back(hit.timeOfFlight() + tof_ + tts_*(gRandom->Gaus()));

      if(links_persistence_)

        the_PhotoElectron_ArrTime_map_links_type_[PSimHitIndex].push_back(hit.timeOfFlight() + tof_ + tts_*(gRandom->Gaus()));

//      std::cout<<"For His on Det_id("<<_det_id<<"), the_photoelectron_amplitude is: "<<the_photoelectron_amplitude<<" and the_PhotoElectron_ArrTime_map_ is: "<<(hit.timeOfFlight() + tof_ + tts_*(gRandom->Gaus()))<<std::endl;

  }

  typedef SimRP::PhotoElectron_ArrTime_map_links_type::iterator PhotoElectron_ArrTime_map_links_type_iterator;

  for (PhotoElectron_ArrTime_map_links_type_iterator it = the_PhotoElectron_ArrTime_map_links_type_.begin(); it != the_PhotoElectron_ArrTime_map_links_type_.end(); ++it)
  {
      std::cout<<"the_PhotoElectron_ArrTime_map_links_type_ size for PSimHitIndex("<<(it->first)<<") is: "<<(the_PhotoElectron_ArrTime_map_links_type_[it->first]).size()<<std::endl;

  }

//  return the_PhotoElectron_ArrTime_map_;
}

