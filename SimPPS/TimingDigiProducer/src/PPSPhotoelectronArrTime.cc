#include "SimPPS/TimingDigiProducer/interface/PPSPhotoelectronArrTime.h"
#include "SimPPS/TimingDigiProducer/interface/PPSAmplitudeCal.h"
#include "Geometry/TotemRPDetTopology/interface/RPHepPDTWrapper.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "DataFormats/GeometryVector/interface/LocalVector.h"
#include "Geometry/TotemRPDetTopology/interface/RPTopology.h"
#include "TRandom3.h"


PPSPhotoelectronArrTime::PPSPhotoelectronArrTime(const edm::ParameterSet &params,  CLHEP::HepRandomEngine& eng, 
    TimingId det_id) : params_(params), rndEngine(eng) , _det_id(det_id)
{
  verbosity_ = params.getParameter<int>("PPSVerbosity");

  thePPSAmplitudeCal = new PPSAmplitudeCal(params, eng, det_id);

  tof_ = params.getParameter<double>("PPSPhotoElectronTOF");

  tts_ = params.getParameter<double>("PPSPhotoElectronTTS");

  links_persistence_ = params.getParameter<bool>("PPSDigiSimHitRelationsPresistence");

}

PPSPhotoelectronArrTime::~PPSPhotoelectronArrTime(){
  delete thePPSAmplitudeCal;
}

void PPSPhotoelectronArrTime::reset(SimPPSTiming::PhotoElectron_ArrTime_vec &the_PhotoElectron_ArrTime_vec_, SimPPSTiming::PhotoElectron_ArrTime_map_links_type &the_PhotoElectron_ArrTime_map_links_type_)
{
     the_PhotoElectron_ArrTime_vec_.clear();
     the_PhotoElectron_ArrTime_map_links_type_[0].clear();
}

void PPSPhotoelectronArrTime::processHit(const PSimHit& hit, int PSimHitIndex, SimPPSTiming::PhotoElectron_ArrTime_vec &the_PhotoElectron_ArrTime_vec_, SimPPSTiming::PhotoElectron_ArrTime_map_links_type &the_PhotoElectron_ArrTime_map_links_type_)

{

  the_photoelectron_amplitude = thePPSAmplitudeCal->HitToAmplitude(hit);

  for (int Rnd_It = 0; Rnd_It < int(the_photoelectron_amplitude); Rnd_It++){

      the_PhotoElectron_ArrTime_vec_.push_back(hit.timeOfFlight() + tof_ + tts_*(gRandom->Gaus()));

      if(links_persistence_)

        the_PhotoElectron_ArrTime_map_links_type_[PSimHitIndex].push_back(hit.timeOfFlight() + tof_ + tts_*(gRandom->Gaus()));
  }

}

