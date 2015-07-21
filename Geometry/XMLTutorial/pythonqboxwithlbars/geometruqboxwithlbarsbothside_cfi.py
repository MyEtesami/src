import FWCore.ParameterSet.Config as cms

XMLIdealGeometryESSource = cms.ESSource("XMLIdealGeometryESSource",
    geomXMLFiles = cms.vstring('Geometry/CMSCommonData/data/materials.xml',
                              'Geometry/CMSCommonData/data/rotations.xml',
                              'Geometry/CMSCommonData/data/extend/cmsextent.xml',
                               'Geometry/CMSCommonData/data/cms.xml',
                               'Geometry/CMSCommonData/data/cmsMother.xml',
#                               'Geometry/ForwardCommonData/data/forward.xml',
 #                             'Geometry/ForwardCommonData/data/totemRotations.xml',
  #                           'Geometry/ForwardCommonData/data/totemMaterials.xml',
   #                         'Geometry/ForwardCommonData/data/totemt1.xml',
    #                        'Geometry/ForwardCommonData/data/totemt2.xml',
     #'Geometry/ForwardCommonData/data/ionpump.xml',
                                  'Geometry/TotemRPData/data/RP_Materials.xml',
                                  'Geometry/TotemRPData/data/RP_Transformations.xml',
                                  'Geometry/TotemRPData/data/RP_Device.xml',
#                                 'Geometry/TotemRPData/data/TotemRPGlobal.xml', 
#                                  'Geometry/TotemRPData/data/RP_Param_Beam_Region.xml',
                                  'Geometry/TotemRPData/data/RP_Beta_90/RP_Dist_Beam_Cent.xml',
 'Geometry/PPSCommonData/data/PPS_Materials.xml',
                                   'Geometry/PPSCommonData1qboxwithlbars/data/PPS_Transformations.xml',
                                'Geometry/PPSCommonData1qboxwithlbars/data/Cylindrical_pot.xml',
                               'Geometry/PPSCommonData1qboxwithlbars/data/RP_Timing_Lbar.xml',
'Geometry/PPSCommonData1qboxwithlbars/data/RP_Timing_Lbar/RP_Timing_Lbar_A13.xml',
'Geometry/PPSCommonData1qboxwithlbars/data/RP_Timing_Lbar/RP_Timing_Lbar_A24.xml',
'Geometry/PPSCommonData1qboxwithlbars/data/RP_Timing_Lbar/RP_Timing_Lbar_B13.xml',
'Geometry/PPSCommonData1qboxwithlbars/data/RP_Timing_Lbar/RP_Timing_Lbar_B24.xml',
'Geometry/PPSCommonData1qboxwithlbars/data/RP_Timing_Lbar/RP_Timing_Lbar_C13.xml',
'Geometry/PPSCommonData1qboxwithlbars/data/RP_Timing_Lbar/RP_Timing_Lbar_C24.xml',
'Geometry/PPSCommonData1qboxwithlbars/data/RP_Timing_Lbar/RP_Timing_Lbar_D13.xml',
'Geometry/PPSCommonData1qboxwithlbars/data/RP_Timing_Lbar/RP_Timing_Lbar_D24.xml',
'Geometry/PPSCommonData1qboxwithlbars/data/RP_Timing_Lbar/RP_Timing_Lbar_E13.xml',
'Geometry/PPSCommonData1qboxwithlbars/data/RP_Timing_Lbar/RP_Timing_Lbar_E24.xml',
                               'Geometry/PPSCommonData1qboxwithlbars/data/RP_Timing_Box_Left.xml',
                               'Geometry/PPSCommonData1qboxwithlbars/data/RP_Timing_Box_Right.xml',
                               'Geometry/PPSCommonData1qboxwithlbars/data/RP_215_Left_Detector_Assembly.xml',
                               'Geometry/PPSCommonData1qboxwithlbars/data/RP_215_Right_Detector_Assembly.xml',
#                               'Geometry/PPSCommonData/data/RP_215_Right_Station.xml',
#                               'Geometry/PPSCommonData/data/RP_215_Left_Station.xml',
#                               'Geometry/PPSCommonData/data/PPS_Stations_Assembly.xml',
#                               'Geometry/PPSCommonData1qboxwithlbars/data/PPS_timing_Sensitive_Dets.xml'
        

),
    rootNodeName = cms.string('cms:CMSE')
#rootNodeName=cms.string('forward:TotemT1')
#rootNodeName=cms.string('TotemRPGlobal:OTOTEM')
)
