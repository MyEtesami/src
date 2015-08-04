import FWCore.ParameterSet.Config as cms

XMLIdealGeometryESSource = cms.ESSource("XMLIdealGeometryESSource",
    geomXMLFiles = cms.vstring('Geometry/CMSCommonData/data/materials.xml', 
        'Geometry/CMSCommonData/data/rotations.xml', 
        'Geometry/CMSCommonData/data/extend/cmsextent.xml', 
  
        'Geometry/CMSCommonData/data/cms.xml',
 #       'Geometry/CMSCommonData/data/cmsMother.xml',
#        'Geometry/CMSCommonData/data/beampipe.xml', 
 #       'Geometry/CMSCommonData/data/mgnt.xml', 
   #     'Geometry/ForwardCommonData/data/forward.xml', 
  #      'Geometry/ForwardCommonData/data/totemRotations.xml', 
 #       'Geometry/ForwardCommonData/data/totemMaterials.xml', 
#        'Geometry/ForwardCommonData/data/totemt1.xml', 
#        'Geometry/ForwardCommonData/data/totemt2.xml'
#         'Geometry/ForwardCommonData/data/ionpump.xml'
), 
#    rootNodeName = cms.string('TotemRPGlobal:OTOTEM')
     rootNodeName = cms.string('cms:CMSE')

)


