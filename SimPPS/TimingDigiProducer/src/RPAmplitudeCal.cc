#include "SimPPS/TimingDigiProducer/interface/RPAmplitudeCal.h"
#include "Geometry/TotemRPDetTopology/interface/RPHepPDTWrapper.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "DataFormats/GeometryVector/interface/LocalVector.h"
#include "Geometry/TotemRPDetTopology/interface/RPTopology.h"
#include "TRandom3.h"


RPAmplitudeCal::RPAmplitudeCal(const edm::ParameterSet &params,  CLHEP::HepRandomEngine& eng, 
    TimingId det_id) : params_(params), rndEngine(eng) , _det_id(det_id)
{
  verbosity_ = params.getParameter<int>("RPVerbosity");

  PhotonRefEff_ = params.getParameter<double>("RPPhotonReflectionEfficiency");

  PhotomultiplierGain_ = params.getParameter<double>("RPPhotomultiplierGain");

  PhotonAmplRes_ = params.getParameter<double>("RPPhotonAmplRes");

  fluctuate = new SiG4UniversalFluctuation(rndEngine);

    // Run APV in peak instead of deconvolution mode, which degrades the 
  // time resolution.
  //SimpleConfigurable<bool> SiLinearChargeDivider::peakMode(false,"SiStripDigitizer:APVpeakmode");

  // Enable interstrip Landau fluctuations within a cluster.
  //SimpleConfigurable<bool> SiLinearChargeDivider::fluctuateCharge(true,"SiStripDigitizer:LandauFluctuations");
  fluctuateCharge_ = params.getParameter<bool>("RPLandauFluctuations");
  
  // Number of segments per strip into which charge is divided during
  // simulation. If large, precision of simulation improves.
  //SimpleConfigurable<int> SiLinearChargeDivider::chargeDivisionsPerStrip(10,"SiStripDigitizer:chargeDivisionsPerStrip");
  chargedivisionsPerStrip_ = params.getParameter<int>("RPChargeDivisionsPerStrip");
  chargedivisionsPerThickness_ = params.getParameter<int>("RPChargeDivisionsPerThickness");
 
  // delta cutoff in MeV, has to be same as in OSCAR (0.120425 MeV corresponding // to 100um range for electrons)
  //SimpleConfigurable<double>  SiLinearChargeDivider::deltaCut(0.120425,
  deltaCut_ = params.getParameter<double>("RPDeltaProductionCut");
  
  RPTopology rp_det_topol;
  pitch_ = rp_det_topol.DetPitch();
  thickness_ = rp_det_topol.DetThickness();
}

RPAmplitudeCal::~RPAmplitudeCal(){
  delete fluctuate;
}

double RPAmplitudeCal::HitToAmplitude(const PSimHit& hit)
{

  double eLoss = hit.energyLoss();  // Eloss in GeV

  double ReflectedEff = RPAmplitudeCal::GetPhotonEfficiency(eLoss)*PhotonRefEff_;

  double RandomAmp = gRandom->Rndm();

  if (ReflectedEff < RandomAmp) photoelectron_amplitude = 0.0;
  else photoelectron_amplitude = PhotomultiplierGain_*(1 + PhotonAmplRes_*(gRandom->Gaus()));

  if(verbosity_)
  {
    std::cout<<"Energy Loss : "<<eLoss<<", PhotonEfficiency : "<<RPAmplitudeCal::GetPhotonEfficiency(eLoss)<<
    ", ReflectedEff : "<<ReflectedEff<<", RandomAmp: "<<RandomAmp<<" and the_photoelectron_amplitude_ is: "<<
photoelectron_amplitude<<std::endl;
  }

   std::cout<<"Energy Loss : "<<eLoss<<", PhotonEfficiency : "<<RPAmplitudeCal::GetPhotonEfficiency(eLoss)<<
    ", ReflectedEff : "<<ReflectedEff<<", RandomAmp: "<<RandomAmp<<" and the_photoelectron_amplitude_ is: "<<
   photoelectron_amplitude<<std::endl;

  return photoelectron_amplitude;
}

double RPAmplitudeCal::GetPhotonEfficiency(double eloss)
{

  const int NrCoef = 5;
  double Coef[NrCoef] = {3.68088, -6.68451, 4.26945, -1.06876, 0.0900437};
  double Efficiency = 0.;

  if (eloss < 1.5 || eloss > 3.8) Efficiency=0.;
  else
  {
    for (int i=0; i<NrCoef; i++) Efficiency+=Coef[i]*pow(eloss, i);
  }

  return Efficiency;

}

