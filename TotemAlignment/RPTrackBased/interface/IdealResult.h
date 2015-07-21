/****************************************************************************
*
* This is a part of TOTEM offline software.
* Authors: 
*  Jan Kašpar (jan.kaspar@gmail.com) 
*    
* $Id: IdealResult.h 9977 2015-01-12 14:00:26Z tsodzawi $
* $Revision: 9977 $
* $Date: 2015-01-12 15:00:26 +0100 (Mon, 12 Jan 2015) $
*
****************************************************************************/


#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "Geometry/TotemRPGeometryBuilder/interface/TotemRPGeometry.h"
#include "TotemAlignment/RPTrackBased/interface/AlignmentAlgorithm.h"
#include "TotemAlignment/RPDataFormats/interface/RPAlignmentCorrections.h"

#include <vector>

class AlignmentTask;


/**
 *\brief Calculates the ideal result of the StraightTrackAlignment.
 **/
class IdealResult : public AlignmentAlgorithm
{
  protected:
    edm::ESHandle<TotemRPGeometry> gReal, gMisaligned;

    bool useExtendedConstraints;

  public:
    /// dummy constructor (not to be used)
    IdealResult() {}

    /// normal constructor
    IdealResult(const edm::ParameterSet& ps, AlignmentTask *_t);

    virtual ~IdealResult() {}

    virtual std::string GetName()
      { return "Ideal"; }

    virtual bool HasErrorEstimate()
      { return false; }

    virtual void Begin(const edm::EventSetup&);
    virtual void Feed(const HitCollection&, const LocalTrackFit&, const LocalTrackFit&) {}
    virtual void SaveDiagnostics(TDirectory *) {}
    virtual std::vector<SingularMode> Analyze();
    virtual unsigned int Solve(const std::vector<AlignmentConstraint>&,
      RPAlignmentCorrections &result, TDirectory *dir);
    virtual void End() {}
};


