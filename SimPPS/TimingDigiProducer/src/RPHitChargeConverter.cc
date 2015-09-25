//#include "SimTotem/RPDigiProducer/interface/RPHitChargeConverter.h"
//#include "DataFormats/GeometryVector/interface/LocalPoint.h"
//#include "SimTotem/RPDigiProducer/interface/RPLinearChargeDivider.h"
//#include "SimTotem/RPDigiProducer/interface/RPLinearChargeCollectionDrifter.h"
//#include "SimTotem/RPDigiProducer/interface/RPLinearInduceChargeOnStrips.h"
#include "SimPPS/TimingDigiProducer/interface/RPHitChargeConverter.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "SimPPS/TimingDigiProducer/interface/RPLinearChargeDivider.h"
#include "SimPPS/TimingDigiProducer/interface/RPLinearChargeCollectionDrifter.h"
#include "SimPPS/TimingDigiProducer/interface/RPLinearInduceChargeOnStrips.h"


//RPHitChargeConverter::RPHitChargeConverter(const edm::ParameterSet &params, CLHEP::HepRandomEngine& eng, RPDetId det_id)
RPHitChargeConverter::RPHitChargeConverter(const edm::ParameterSet &params, CLHEP::HepRandomEngine& eng, TimingId det_id)
  : params_(params), det_id_(det_id)
{
  verbosity_ = params.getParameter<int>("RPVerbosity");
  theRPChargeDivider = new RPLinearChargeDivider(params, eng, det_id);
std::cout<<"6666666666666666666"<<std::endl;
  theRPChargeCollectionDrifter = new RPLinearChargeCollectionDrifter(params, det_id);
std::cout<<"7777777777777777777"<<std::endl;
  theRPInduceChargeOnStrips = new RPLinearInduceChargeOnStrips(params, det_id);
std::cout<<"888888888888888888"<<std::endl;
}

RPHitChargeConverter::~RPHitChargeConverter()
{
  delete theRPChargeDivider;
  delete theRPChargeCollectionDrifter;
  delete theRPInduceChargeOnStrips;
}


SimRP::strip_charge_map RPHitChargeConverter::processHit(const PSimHit &hit)
{  
  SimRP::energy_path_distribution ions_along_path = theRPChargeDivider->divide(hit);
  if(verbosity_)
    std::cout<<"HitChargeConverter "<<det_id_<<" clouds no generated on the path="<<ions_along_path.size()<<std::endl;
  return theRPInduceChargeOnStrips->Induce(theRPChargeCollectionDrifter->Drift(ions_along_path));
}

