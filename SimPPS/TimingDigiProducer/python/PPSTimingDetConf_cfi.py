import FWCore.ParameterSet.Config as cms

PPSTimingDigitizer = cms.EDProducer("PPSTimingDigiProducer",

    # all distances in [mm]
    # PPSTimingDigiProducer
    ROUList = cms.vstring('PPSTimingHits'),
    PPSVerbosity = cms.int32(0),
    RPVerbosity = cms.int32(0),
    PPSDigiSimHitRelationsPresistence = cms.bool(False), # save links betweend digi, clusters and OSCAR/Geant4 hits

    # PPSDetDigitizer
#   RPEquivalentNoiseCharge300um = cms.double(1000.0),
#   RPNoNoise = cms.bool(False),

    # PPSPhotoelectronArrTime 
    PPSPhotoElectronTOF = cms.double(1.5),
    PPSPhotoElectronTTS = cms.double(0.25),

    # PPSAmplitudeCal
    PPSPhotonReflectionEfficiency = cms.double(0.8),
    PPSPhotomultiplierGain = cms.double(1000.0), # ***DUE TO SLOW VECTOR FILLING, THE GAIN VALUE WAS SET TO 10^3, THE VALUE MUST BE 10^6***
    PPSPhotonAmplRes = cms.double(0.3),

    # PPSNINOSimulator
    PPSNINOThreshold = cms.double(50.0),
    PPSNINOTriggerMode = cms.int32(2),

    # RPLinearChargeDivider
    PPSLandauFluctuations = cms.bool(True),
#    RPChargeDivisionsPerStrip = cms.int32(15),
#    RPChargeDivisionsPerThickness = cms.int32(5),
#    RPDeltaProductionCut = cms.double(0.120425),    # [MeV]

    # RPLinearInduceChargeOnStrips
#    RPInterStripCoupling = cms.double(1.0), # fraction of charge going to the strip, the missing part is taken by its neighbours

    # RPSimTopology
    RPSharingSigmas = cms.double(5.0), # how many sigmas taken into account for the edges and inter strips
    RPTopEdgeSmearing = cms.double(0.011),
    RPBottomEdgeSmearing = cms.double(0.011),
    RPActiveEdgeSmearing = cms.double(0.013),
    RPActiveEdgePosition = cms.double(0.034),   # from the physical edge
    RPTopEdgePosition = cms.double(1.5),
    RPBottomEdgePosition = cms.double(1.5)
)


