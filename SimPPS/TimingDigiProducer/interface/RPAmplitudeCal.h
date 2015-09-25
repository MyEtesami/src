#ifndef SimPPS_TimingDigiProducer_RP_AMPLITUDE_CAL_H
#define SimPPS_TimingDigiProducer_RP_AMPLITUDE_CAL_H

#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimTracker/Common/interface/SiG4UniversalFluctuation.h"
#include "SimPPS/TimingDigiProducer/interface/RPSimTypes.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

namespace CLHEP{
	class HepRandomEngine;
}


class RPAmplitudeCal
{
  public:
    RPAmplitudeCal(const edm::ParameterSet &params, CLHEP::HepRandomEngine& eng, TimingId det_id);
    ~RPAmplitudeCal();
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

    bool fluctuateCharge_;
    int chargedivisionsPerStrip_;
    int chargedivisionsPerThickness_;
    double deltaCut_;
    double pitch_;
    double thickness_;
    SimRP::energy_path_distribution the_energy_path_distribution_;
    SiG4UniversalFluctuation * fluctuate; 
    int verbosity_;
    
    void FluctuateEloss(int pid, double particleMomentum, 
        double eloss, double length, int NumberOfSegs, 
        SimRP::energy_path_distribution &elossVector);
};

#endif  //SimPPS_TimingDigiProducer_RP_AMPLITUDE_CAL_H
