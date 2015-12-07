#include "SimPPS/TimingDigiProducer/interface/PPSAmplitudeCal.h"
#include "Geometry/TotemRPDetTopology/interface/RPHepPDTWrapper.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "DataFormats/GeometryVector/interface/LocalVector.h"
#include "Geometry/TotemRPDetTopology/interface/RPTopology.h"
#include "TRandom3.h"
#include "TGraph.h"


PPSAmplitudeCal::PPSAmplitudeCal(const edm::ParameterSet &params,  CLHEP::HepRandomEngine& eng, 
    TimingId det_id) : params_(params), rndEngine(eng) , _det_id(det_id)
{
  verbosity_ = params.getParameter<int>("PPSVerbosity");

  PhotonRefEff_ = params.getParameter<double>("PPSPhotonReflectionEfficiency");

  PhotomultiplierGain_ = params.getParameter<double>("PPSPhotomultiplierGain");

  PhotonAmplRes_ = params.getParameter<double>("PPSPhotonAmplRes");

  fluctuate = new SiG4UniversalFluctuation(rndEngine);

  fluctuateCharge_ = params.getParameter<bool>("PPSLandauFluctuations");
}
  
PPSAmplitudeCal::~PPSAmplitudeCal(){
  delete fluctuate;
}

double PPSAmplitudeCal::HitToAmplitude(const PSimHit& hit)
{

  double eLoss = hit.energyLoss();  // Eloss in GeV
  double ReflectedEff = 0.0;

  ReflectedEff = PPSAmplitudeCal::GetPhotonEfficiency2(eLoss)*PhotonRefEff_;

  double RandomAmp = gRandom->Rndm();

  photoelectron_amplitude = PhotomultiplierGain_*(1 + PhotonAmplRes_*(gRandom->Gaus()));

  if(verbosity_)
  {
    std::cout<<"Energy Loss : "<<eLoss<<", PhotonEfficiency : "<<PPSAmplitudeCal::GetPhotonEfficiency(eLoss)<<
    ", ReflectedEff : "<<ReflectedEff<<", RandomAmp: "<<RandomAmp<<" and the_photoelectron_amplitude_ is: "<<
photoelectron_amplitude<<std::endl;
  }
  return photoelectron_amplitude;
}

double PPSAmplitudeCal::GetPhotonEfficiency(double eloss)
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

double PPSAmplitudeCal::GetPhotonEfficiency2(double eloss)
{

float photonWavelength[11] = {250,300,350,400,450,500,550,600,650,700,750};  //nm
//float PDE_MCP[11] = {0.206,0.191,0.186,0.138,0.143,0.094,0.082,0.078,0.073,0.02,0.008};
float PDE_SiPM[11] = {0,0.05,0.38,0.48,0.50,0.47,0.40,0.30,0.24,0.18,0.13};  //5% -> 0.05

TGraph *E_PDE = new TGraph(11,photonWavelength,PDE_SiPM);

//double Efficiency = E_PDE->Eval(1.23984193e-06 /eloss); //E=PC = hc/lambda ->  lambda= 1.23984193e-6 GeV nm / eloss GeV
double Efficiency = E_PDE->Eval(1.23984193e3/eloss); //E=PC = hc/lambda ->  lambda= 1.23984193e3 GeV nm / eloss ev

//TSpline3 *s3 = new TSpline3("spline3",E_PDE);
//TSpline5 *s5 = new TSpline5("spline5",E_PDE);

return Efficiency;

}

