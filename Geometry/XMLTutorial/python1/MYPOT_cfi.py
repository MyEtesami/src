import FWCore.ParameterSet.Config as cms

XMLIdealGeometryESSource = cms.ESSource("XMLIdealGeometryESSource",
    geomXMLFiles = cms.vstring('Geometry/CMSCommonData/data/materials.xml', 
        'Geometry/CMSCommonData/data/rotations.xml', 
        'Geometry/CMSCommonData/data/normal/cmsextent.xml', 
        'Geometry/CMSCommonData/data/cms.xml', 
        'Geometry/TotemRPData/data/RP_Transformations.xml',
        'Geometry/TotemRPData/data/RP_Box.xml',
        'Geometry/TotemRPData/data/RP_Materials.xml',
        'Geometry/TotemRPData/data/RP_Device.xml',
        'Geometry/XMLTutorial/data/CtppsRPGlobal.xml',
        'Geometry/CMSCommonData/data/beampipe.xml',
        'Geometry/TotemRPData/data/OneRPTestBeam/RP_220_Right_Station.xml',
),
#    rootNodeName = cms.string('TotemRPGlobal:OTOTEM')
    rootNodeName = cms.string('cms:CMSE')

)

