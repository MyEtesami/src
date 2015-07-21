import FWCore.ParameterSet.Config as cms

XMLIdealGeometryESSource = cms.ESSource("XMLIdealGeometryESSource",
    geomXMLFiles = cms.vstring('Geometry/CMSCommonData/data/materials.xml',
                              'Geometry/CMSCommonData/data/rotations.xml',
                              'Geometry/CMSCommonData/data/extend/cmsextent.xml',
                               'Geometry/CMSCommonData/data/cms.xml',
#                               'Geometry/CMSCommonData/data/cmsMother.xml',
#                               'Geometry/ForwardCommonData/data/forward.xml'
                               'Geometry/TotemRPData/data/RP_Transformations.xml',
                               'Geometry/XMLTutorial/data/PPS_Transformations.xml',
                               'Geometry/TotemRPData/data/TotemRPGlobal.xml',
                               'Geometry/XMLTutorial/data/CtppsRPGlobal.xml',
                               'Geometry/TotemRPData/data/RP_Box.xml',
                               'Geometry/TotemRPData/data/RP_Materials.xml',
                               'Geometry/TotemRPData/data/RP_Device.xml',
                               'Geometry/PPSCommonData/data/Cylindrical_pot.xml',
                               'Geometry/PPSCommonData/data/RP_Timing_Lbar.xml',
                               'Geometry/PPSCommonData/data/RP_Timing_Box_Left.xml',
                               'Geometry/PPSCommonData/data/RP_Timing_Box_Right.xml',
                               'Geometry/PPSCommonData/data/RP_215_Left_Detector_Assembly.xml',
                               'Geometry/PPSCommonData/data/RP_215_Right_Detector_Assembly.xml',
                               'Geometry/PPSCommonData/data/RP_215_Right_Station.xml',
                               'Geometry/PPSCommonData/data/RP_215_Left_Station.xml',
                               'Geometry/PPSCommonData/data/PPS_Stations_Assembly.xml'
),
   rootNodeName = cms.string('cms:OCMS')
#    rootNodeName = cms.string('TotemRPGlobal:OTOTEM')


)
