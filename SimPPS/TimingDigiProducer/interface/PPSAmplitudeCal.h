#ifndef SimPPS_TimingDigiProducer_PPS_AMPLITUDE_CAL_H
#define SimPPS_TimingDigiProducer_PPS_AMPLITUDE_CAL_H

#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimTracker/Common/interface/SiG4UniversalFluctuation.h"
#include "SimPPS/TimingDigiProducer/interface/PPSSimTypes.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

namespace CLHEP{
	class HepRandomEngine;
}


class PPSAmplitudeCal
{
  public:
    PPSAmplitudeCal(const edm::ParameterSet &params, CLHEP::HepRandomEngine& eng, TimingId det_id);
    ~PPSAmplitudeCal();
    double HitToAmplitude(const PSimHit& hit);
  private:
    const edm::ParameterSet &params_;
    CLHEP::HepRandomEngine& rndEngine;
    TimingId _det_id;

    double PhotonRefEff_;
    double PhotomultiplierGain_;
    double PhotonAmplRes_;
    double photoelectron_amplitude;

    double GetPhotonEfficiency(double eloss);
    double GetPhotonEfficiency2(double eloss);

    bool fluctuateCharge_;
    SimPPSTiming::energy_path_distribution the_energy_path_distribution_;
    SiG4UniversalFluctuation * fluctuate; 
    int verbosity_;
    
    void FluctuateEloss(int pid, double particleMomentum, 
        double eloss, double length, int NumberOfSegs, 
        SimPPSTiming::energy_path_distribution &elossVector);
};

#endif  //SimPPS_TimingDigiProducer_PPS_AMPLITUDE_CAL_H
