#include "DataFormats/Common/interface/Wrapper.h"
#include "DataFormats/Common/interface/DetSet.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/TotemRPDataTypes/interface/RPStripDigi.h"
#include "DataFormats/PPSTimingDataTypes/interface/PPSTimingLBarDigi.h"
#include "DataFormats/TotemRPDataTypes/interface/RPDetTrigger.h"
#include "DataFormats/PPSTimingDataTypes/interface/PPSTimingTrigger.h"
#include "DataFormats/TotemRPDataTypes/interface/RPDigCluster.h"
#include "DataFormats/TotemRPDataTypes/interface/RPRecoHit.h"

#include <vector>

namespace {
  namespace {
    RPStripDigi rp_str_dig;
    edm::DetSet<RPStripDigi> ds_rp_str_dig;
    std::vector<RPStripDigi> vec_rp_str_dig;
    edm::DetSetVector<RPStripDigi> dsv_rp_str_dig;
    std::vector<edm::DetSet<RPStripDigi> > vec_ds_rp_str_dig;
    edm::Wrapper<edm::DetSet<RPStripDigi> > wds_rp_str_dig;
    edm::Wrapper<edm::DetSetVector<RPStripDigi> > wdsv_rp_str_dig;

    PPSTimingLBarDigi rp_lbar_dig;
    edm::DetSet<PPSTimingLBarDigi> ds_rp_lbar_dig;
    std::vector<PPSTimingLBarDigi> vec_rp_lbar_dig;
    edm::DetSetVector<PPSTimingLBarDigi> dsv_rp_lbar_dig;
    std::vector<edm::DetSet<PPSTimingLBarDigi> > vec_ds_rp_lbar_dig;
    edm::Wrapper<edm::DetSet<PPSTimingLBarDigi> > wds_rp_lbar_dig;
    edm::Wrapper<edm::DetSetVector<PPSTimingLBarDigi> > wdsv_rp_lbar_dig;


	RPRecoHit rp_reco_hit;
    edm::DetSet<RPRecoHit> ds_rp_reco_hit;
    edm::DetSetVector<RPRecoHit> dsv_rp_reco_hit;
    std::vector<edm::DetSet<RPRecoHit> > sv_dsw_rp_reco_hit;
    edm::Wrapper<edm::DetSetVector<RPRecoHit> > w_dsv_rp_reco_hit;
	std::vector<RPRecoHit> sv_rp_reco_hit;
	std::vector<const RPRecoHit*> sv_cp_rp_reco_hit;
    
	// TODO: these needed?
    std::pair<__gnu_cxx::__normal_iterator<const RPRecoHit*,std::vector<RPRecoHit> >,__gnu_cxx::__normal_iterator<const RPRecoHit*,std::vector<RPRecoHit> > > pni;
    __gnu_cxx::__normal_iterator<const RPRecoHit*,std::vector<RPRecoHit> > d1;
    
    PPSTimingTrigger rp_lbar_tri;
    edm::DetSet<PPSTimingTrigger> ds_rp_lbar_tri;
    std::vector<PPSTimingTrigger> vec_rp_lbar_tri;
    std::vector<edm::DetSet<PPSTimingTrigger> > vec_ds_rp_lbar_tri;
    edm::DetSetVector<PPSTimingTrigger> dsv_rp_lbar_tri;
    edm::Wrapper<edm::DetSet<PPSTimingTrigger> > wds_rp_lbar_tri;
    edm::Wrapper<edm::DetSetVector<PPSTimingTrigger> > wdsv_rp_lbar_tri;

    RPDetTrigger rp_str_tri;
    edm::DetSet<RPDetTrigger> ds_rp_str_tri;
    std::vector<RPDetTrigger> vec_rp_str_tri;
    std::vector<edm::DetSet<RPDetTrigger> > vec_ds_rp_str_tri;
    edm::DetSetVector<RPDetTrigger> dsv_rp_str_tri;
    edm::Wrapper<edm::DetSet<RPDetTrigger> > wds_rp_str_tri;
    edm::Wrapper<edm::DetSetVector<RPDetTrigger> > wdsv_rp_str_tri;


    
    RPDigCluster dc;
    edm::DetSet<RPDigCluster> dsdc;
    std::vector<RPDigCluster> svdc;
    std::vector<edm::DetSet<RPDigCluster> > svdsdc;
    edm::DetSetVector<RPDigCluster> dsvdc;
    edm::Wrapper<edm::DetSetVector<RPDigCluster> > wdsvdc;
  }
}
