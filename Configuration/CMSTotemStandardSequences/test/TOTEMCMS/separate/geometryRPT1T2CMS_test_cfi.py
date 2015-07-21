import FWCore.ParameterSet.Config as cms

XMLIdealGeometryESSource = cms.ESSource("XMLIdealGeometryESSource",
    geomXMLFiles = cms.vstring(* ('Geometry/CMSCommonData/data/materials.xml',
        'Geometry/CMSCommonData/data/rotations.xml', 
        'Geometry/CMSCommonData/data/normal/cmsextent.xml',  # DIFF: TOTEM uses normal, CMS uses extend
        'Geometry/CMSCommonData/data/cms.xml',
        'Geometry/CMSCommonData/data/cmsMother.xml',
       # 'Geometry/CMSCommonData/data/cmsTracker.xml',
       # 'Geometry/CMSCommonData/data/caloBase.xml',
        #'Geometry/CMSCommonData/data/cmsCalo.xml',
       # 'Geometry/CMSCommonData/data/muonBase.xml',
      #  'Geometry/CMSCommonData/data/cmsMuon.xml',
    #    'Geometry/CMSCommonData/data/mgnt.xml',
   #     'Geometry/CMSCommonData/data/PhaseI/beampipe.xml',
     #   'Geometry/CMSCommonData/data/cmsBeam.xml',
 #       'Geometry/CMSCommonData/data/muonMB.xml',
#        'Geometry/CMSCommonData/data/muonMagnet.xml',
  #      'Geometry/CMSCommonData/data/cavern.xml',
        'Geometry/ForwardCommonData/data/forward.xml',
        'Geometry/ForwardCommonData/data/totemMaterials.xml',
        'Geometry/ForwardCommonData/data/totemRotations.xml',
        'Geometry/ForwardCommonData/data/totemt1.xml',
        'Geometry/ForwardCommonData/data/totemt2.xml',
        'Geometry/ForwardCommonData/data/ionpump.xml',
'Geometry/TotemRPData/data/TotemRPGlobal.xml',                                  
'Geometry/TotemRPData/data/RP_Materials.xml',
                                  'Geometry/TotemRPData/data/RP_Transformations.xml',
                                  'Geometry/TotemRPData/data/RP_Device.xml',
                                   'Geometry/PPSCommonData/data/PPS_Transformations.xml',                      
                                'Geometry/PPSCommonData/data/Cylindrical_pot.xml', 
                               'Geometry/PPSCommonData/data/RP_Timing_Lbar.xml',
                               'Geometry/PPSCommonData/data/RP_Timing_Box_Left.xml',
                               'Geometry/PPSCommonData/data/RP_Timing_Box_Right.xml',
                               'Geometry/PPSCommonData/data/RP_215_Left_Detector_Assembly.xml',
                               'Geometry/PPSCommonData/data/RP_215_Right_Detector_Assembly.xml',
                               'Geometry/PPSCommonData/data/RP_215_Right_Station.xml',
                               'Geometry/PPSCommonData/data/RP_215_Left_Station.xml',
                               'Geometry/PPSCommonData/data/PPS_Stations_Assembly.xml'
                                  )),  # DIFF: TOTEM only
                                        #    rootNodeName = cms.string('cms:OCMS')
                                        rootNodeName = cms.string('TotemRPGlobal:OTOTEM')

)

TotemRPGeometryESModule = cms.ESProducer("TotemRPGeometryESModule") # DIFF: TOTEM only
