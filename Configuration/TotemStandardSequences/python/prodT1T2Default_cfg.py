import FWCore.ParameterSet.Config as cms

process = cms.Process("T1T2pythiaMBbeta11energy1100GeV")

# Specify the maximum events to simulate
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5)
)

# Configure the output module (save the result in a file)
process.o1 = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring('keep *', 'drop *_*mix*_*_*','drop *_*_*TrackerHits*_*', 'drop *_*_*Muon*_*', 'drop *_*_*Ecal*_*', 'drop *_*_*Hcal*_*', 'drop *_*_*Calo*_*', 'drop *_*_*Castor*_*', 'drop *_*_*FP420SI_*', 'drop *_*_*ZDCHITS_*', 'drop *_*_*BSCHits_*', 'drop *_*_*ChamberHits_*', 'drop *_*_*FibreHits_*', 'drop *_*_*WedgeHits_*'),
    fileName = cms.untracked.string('file:prodT1T2pythiaMBbeta11energy1.1TeV.root')
)

# Configure if you want to detail or simple log information.
# LoggerMax -- detail log info output including: errors.log, warnings.log, infos.log, debugs.log
# LoggerMin -- simple log info output to the standard output (e.g. screen)
process.load("Configuration.TotemCommon.LoggerMin_cfi")

# Use particle table
process.load("SimGeneral.HepPDTESSource.pdt_cfi")


# raw to digi conversion
process.load('TotemCondFormats/DAQInformation/DAQMappingSourceXML_cfi')
process.DAQMappingSourceXML.mappingFileNames.append('TotemCondFormats/DAQInformation/data/t1_all_run1.xml')
process.DAQMappingSourceXML.mappingFileNames.append('TotemCondFormats/DAQInformation/data/t2_4quarters.xml')


################## STEP 0 - empty source

process.source = cms.Source("EmptySource")

################## STEP 1 - process.generator

# Use random number generator service
process.load("Configuration.TotemCommon.RandomNumbers_cfi")

# Pythia source labeled as "process.generator" @ CMSSW_4_2_4
process.load("Configuration.TotemCommon.PythiaMB_cfi")
process.generator.comEnergy = cms.double(2360)

################## STEP 2 process.SmearingGenerator

# declare optics parameters
#process.load("Configuration.TotemOpticsConfiguration.OpticsConfig_1180GeV_11_cfi")

# Smearing
process.load("IOMC.SmearingGenerator.SmearingGenerator_cfi")

################## STEP 3 process.g4SimHits

# Geometry
process.load("Configuration.TotemCommon.geometryT1T2_cfi")

# Magnetic Field, by default we have 3.8T
process.load("Configuration.StandardSequences.MagneticField_cff")

# G4 simulation & proton transport
process.load("Configuration.TotemCommon.g4SimHits_cfi")
process.g4SimHits.Generator.HepMCProductLabel = 'generator'
process.g4SimHits.Physics.type = cms.string('SimG4Core/Physics/QGSP_BERT_EML')
process.g4SimHits.Watchers = cms.VPSet()
process.g4SimHits.Generator.LeaveScatteredProtons = cms.untracked.bool(False)

################## STEP 4 process.mix*process.T1Digis*process.t1cluster*process.t1rechit*process.t1roads*process.t1tracks

process.load("Configuration.TotemStandardSequences.T1_Digi_and_TrackReconstruction_cfi")

################## STEP 5 process.mix*process.T2Digis*process.T2MCl*process.T2Hits*process.T2RoadColl*process.T2TrackColl2

process.load("Configuration.TotemStandardSequences.T2_Digi_and_TrackReconstruction_cfi")

################## STEP 6 process.T2CC

process.load("L1TriggerTotem.CoincidenceChip.T2CoincidenceProducer_cfi")


#process.p1 = cms.Path(process.generator*process.SmearingGenerator*process.g4SimHits*process.mix*process.T1Digis*process.t1cluster*process.t1rechit*process.t1roads*process.t1tracks2*process.T2Digis*process.T2MCl*process.T2Hits*process.T2RoadPadFinder*process.T2TrackColl3*process.T2CC)

process.outpath = cms.EndPath(process.o1)