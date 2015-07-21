import FWCore.ParameterSet.Config as cms

XMLIdealGeometryESSource = cms.ESSource("XMLIdealGeometryESSource",
    geomXMLFiles = cms.vstring('Geometry/CMSCommonData/data/materials.xml',
                              'Geometry/CMSCommonData/data/rotations.xml',
                              'Geometry/CMSCommonData/data/normal/cmsextent.xml',
                               'Geometry/CMSCommonData/data/cms.xml',
#                               'Geometry/CMSCommonData/data/cmsMother.xml',
#                               'Geometry/ForwardCommonData/data/forward.xml'
                               'Geometry/XMLTutorial/data/RP_Transformations.xml',
                               'Geometry/XMLTutorial/data/CtppsRPGlobal.xml',
                               'Geometry/TotemRPData/data/RP_Box.xml',
                               'Geometry/TotemRPData/data/RP_Materials.xml',
                               'Geometry/TotemRPData/data/RP_Device.xml',
                               'Geometry/XMLTutorial/data/RP_215_Right_Station.xml',
                               'Geometry/XMLTutorial/data/Cylindrical_pot.xml',
                               'Geometry/XMLTutorial/data/timingLbar.xml'
),
    rootNodeName = cms.string('cms:CMSE')
#    rootNodeName = cms.string('TotemRPGlobal:OTOTEM')

)
