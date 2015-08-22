#ifndef SimG4Core_StackingAction_H
#define SimG4Core_StackingAction_H

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "G4UserStackingAction.hh"
#include "G4Region.hh"
#include "G4Track.hh"
#include "G4LogicalVolume.hh"

#include <string>
#include <vector>

class EventAction;
class NewTrackAction;
//PPA added
class TrackingAction;

class StackingAction : public G4UserStackingAction {

public:
  StackingAction(EventAction* e, const edm::ParameterSet & ps);
  virtual ~StackingAction();

  virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track * aTrack);

  void NewStage();
  void PrepareNewEvent();

private:
  void   initPointer();
  bool   isThisVolume(const G4VTouchable*, std::vector<G4LogicalVolume*>&) const;
  int    isItPrimaryDecayProductOrConversion(const G4Track*, const G4Track &) const;
  bool   rrApplicable(const G4Track*, const G4Track&) const;  
  bool   isItLongLived(const G4Track*) const;

private:
  EventAction                   *eventAction_;
  bool                          savePDandCinTracker, savePDandCinCalo;
  bool                          savePDandCinMuon, saveFirstSecondary;
  bool                          killInCalo, killInCaloEfH;
  bool                          killHeavy, trackNeutrino, killDeltaRay;
  double                        kmaxIon, kmaxNeutron, kmaxProton;
  double                        maxTrackTime;
  std::vector<double>           maxTrackTimes;
  std::vector<std::string>      maxTimeNames;
  std::vector<G4Region*>        maxTimeRegions;
  std::vector<G4LogicalVolume*> tracker, calo, muon;

//PPS added
// const TrackingAction* trackAction;

  NewTrackAction*               newTA;

  // Russian roulette regions
  G4Region*                     regionEcal;
  G4Region*                     regionHcal;
  G4Region*                     regionMuonIron;
  G4Region*                     regionPreShower;
  G4Region*                     regionCastor;
  G4Region*                     regionWorld;

  // Russian roulette energy limits
  double                        gRusRoEnerLim;
  double                        nRusRoEnerLim;
  double                        pRusRoEnerLim;

  // Russian roulette factors
  double                        gRusRoEcal;
  double                        nRusRoEcal;
  double                        pRusRoEcal;
  double                        gRusRoHcal;
  double                        nRusRoHcal;
  double                        pRusRoHcal;
  double                        gRusRoMuonIron;
  double                        nRusRoMuonIron;
  double                        pRusRoMuonIron;
  double                        gRusRoPreShower;
  double                        nRusRoPreShower;
  double                        pRusRoPreShower;
  double                        gRusRoCastor;
  double                        nRusRoCastor;
  double                        pRusRoCastor;
  double                        gRusRoWorld;
  double                        nRusRoWorld;
  double                        pRusRoWorld;
  // flags
  bool                          gRRactive;
  bool                          nRRactive;
  bool                          pRRactive;
};

#endif
