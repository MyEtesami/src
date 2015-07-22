#   For all possibilities that are not here (like some of the input collections),
#   please look at all parameters retrieved in src/GetParameters.cc
#   All the parameters have anyway a default value !

import FWCore.ParameterSet.Config as cms

# Standard Parameters For UABaseTree Process   ----------------------------------------
uabasetree = cms.EDAnalyzer('UABaseTree',
  filterEvents = cms.untracked.bool(False),		#filterEvents for data. Switched Off for MC
  storeEvtId = cms.untracked.bool(True),		
  storeFwdGap = cms.untracked.bool(False),
  storeL1Trig = cms.untracked.bool(False),
  storeL1TrigOld = cms.untracked.bool(True),		#old simple version. Deprecated.
  #hlt_paths = cms.untracked.vstring( 'HLT_DoubleMu3_v3',
  #                                   'HLT_Ele8_v2' ,
  #                                   'HLT_Jet20_v1' ,
  #                                   'HLT_Jet40_v1' ,
  #                                   'HLT_Jet60_v1' ,
  #                                   'HLT_L1DoubleForJet32_EtaOpp_v1' ,
  #                                   'HLT_L1DoubleForJet8_EtaOpp_v1' ,
  #                                   'HLT_L1DoubleMu0_v1' ,
  #                                   'HLT_L2DoubleMu0_v2' ,
  #                                   'HLT_L1SingleEG12_v1',
  #                                   "HLT_L1SingleEG5_v1",
  #                                   "HLT_L1SingleJet36_v1",
  #                                   "HLT_L1SingleMuOpen_AntiBPTX_v1",
  #                                   "HLT_L1SingleMuOpen_DT_v1",
  #                                   "HLT_L1SingleMuOpen_v1" ,
  #                                   'HLT_L1BscMinBiasORBptxPlusANDMinus_v1' ,
  #                                   'HLT_Mu0_v3' ,
  #                                   'HLT_Mu3_v3' ,
  #                                   'HLT_Mu5_v3' ,
  #                                   'HLT_Photon10_CaloIdVL_v1' ,
  #                                   'HLT_Photon15_CaloIdVL_v1' ,
  #                                   'HLT_PixelTracks_Multiplicity50_Loose' ,
  #                                   'HLT_PixelTracks_Multiplicity60_Loose' ,
  #                                   'HLT_PixelTracks_Multiplicity70_Loose' ,
  #                                   'HLT_ZeroBiasPixel_SingleTrack_v1' ,
  #                                   'HLT_ZeroBias_v1',
  #                                   'HLT_L1Tech53_MB_1_v1',
  #                                   'HLT_L1Tech53_MB_2_v1')
  #hlt_paths = cms.untracked.vstring( 'HLT_ZeroBias_v6',
  #                                   'HLT_L1Tech54_ZeroBias_v1',
  #                                   'HLT_L1Tech40_BPTXAND_1_v1',
  #                                   'HLT_L1Tech53_MB_1_v1',
  #                                   'HLT_L1Tech40_BPTXAND_2_v1',
  #                                   'HLT_L1Tech53_MB_2_v1', 
  #                                   'HLT_SingleJetC5_BHC_v1',
  #                                   'HLT_SingleJetC5_HF_v1',
  #                                   'HLT_TripleTrack02_BHC_v1',
  #                                   'LT_TripleTrack02_HF_v1',
  #                                   'HLT_L1RomanPots_OR_v1',
  #                                   'HLT_SingleForJet15_BHC_v1',
  #                                   'HLT_SingleForJet15_HF_v1' )  
  #hlt_paths = cms.untracked.vstring( 'HLT_L1DoubleEG3_FwdVeto_v1',
  #                                   'HLT_L1DoubleMu0_v1',
  #                                   'HLT_L1DoubleJet20_RomanPotsOR_v1',
  #                                   'HLT_L1DoubleJet20part1_v1',
  #                                   'HLT_L1DoubleJet24_v1',
  #                                   'HLT_L1DoubleJet20part2_v1',
  #                                   'HLT_L1Tech40_BPTXAND_v1',
  #                                   'HLT_L1Tech53_MB_1_v1',
  #                                   'HLT_L1Tech_HF9OR10_v1',
  #                                   'HLT_T1minbias_Tech55_v1',
  #                                   'HLT_L1Tech53_MB_2_v1',
  #                                   'HLT_L1Tech53_MB_3_v1',
  #                                   'HLT_RomanPots_Tech52_v1',
  #                                   'HLT_L1Tech54_ZeroBias_v1',
  #                                   'HLT_ZeroBias_v7'
  #                                   ) 
  hlt_paths = cms.untracked.vstring(
    'HLT_PADimuon0_NoVertexing_v1',
    'HLT_PADoubleJet20_ForwardBackward_v1', 
    'HLT_PADoubleMu4_Acoplanarity03_v1', 
    'HLT_PAExclDijet35_HFAND_v1',
    'HLT_PAExclDijet35_HFOR_v1',
    'HLT_PAL1DoubleEG3_FwdVeto_v1',
    'HLT_PAL1DoubleEG5_TotemDiffractive_v1',
    'HLT_PAL1DoubleJet20_TotemDiffractive_v1',
    'HLT_PAL1DoubleJetC36_TotemDiffractive_v1',
    'HLT_PAL1DoubleMu0_v1', 
    'HLT_PAL1DoubleMu5_TotemDiffractive_v1',
    'HLT_PAL1SingleEG20_TotemDiffractive_v1',
    'HLT_PAL1SingleJet16_v1', 
    'HLT_PAL1SingleJet36_v1', 
    'HLT_PAL1SingleJet52_TotemDiffractive_v1',
    'HLT_PAL1SingleMu20_TotemDiffractive_v1',
    'HLT_PAMu7_Ele7_CaloIdT_CaloIsoVL_v1', 
    'HLT_PARomanPots_Tech52_v1', 
    'HLT_PASingleForJet15_v1', 
    'HLT_PASingleForJet25_v1', 
    'HLT_PPL1DoubleJetC36_v1', 
    'HLT_PABptxMinusNotBptxPlus_v1', 
    'HLT_PABptxPlusNotBptxMinus_v1', 
    'HLT_PACastorEmNotHfCoincidencePm_v1', 
    'HLT_PACastorEmNotHfSingleChannel_v1', 
    'HLT_PACastorEmTotemLowMultiplicity_v1', 
    'HLT_PAHFOR_SingleTrack_v1', 
    'HLT_PAL1CastorTotalTotemLowMultiplicity_v1', 
    'HLT_PAL1Tech53_MB_SingleTrack_v1', 
    'HLT_PAL1Tech53_MB_v1', 
    'HLT_PAL1Tech54_ZeroBias_v1', 
    'HLT_PAMinBiasBHC_OR_v1', 
    'HLT_PAMinBiasBHC_v1', 
    'HLT_PAMinBiasHF_OR_v1', 
    'HLT_PAMinBiasHF_v1', 
    'HLT_PAMinBiasHfOrBHC_v1', 
    'HLT_PARandom_v1', 
    'HLT_PAT1minbias_Tech55_v1', 
    'HLT_PAZeroBiasPixel_DoubleTrack_v1', 
    'HLT_PAZeroBiasPixel_SingleTrack_v1', 
    'HLT_PAZeroBias_v1', 
    'HLT_PAJet20_NoJetID_v1', 
    'HLT_PAJet40_NoJetID_v1', 
    'HLT_PAJet60_NoJetID_v1', 
    'HLT_PAJet80_NoJetID_v1', 
    'HLT_PAJet100_NoJetID_v1', 
    'HLT_PAJet120_NoJetID_v1', 
    'HLT_PAL1DoubleMu0_HighQ_v1', 
    'HLT_PAL1DoubleMuOpen_v1', 
    'HLT_PAL2DoubleMu3_v1', 
    'HLT_PAMu12_v1', 
    'HLT_PAMu3_v1', 
    'HLT_PAMu7_v1' 
    )
)