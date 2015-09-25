#ifndef DataFormats_PPSTimingDataTypes_RP_LBARDIGI_H
#define DataFormats_PPSTimingDataTypes_RP_LBARDIGI_H

#include "DataFormats/PPSTimingDataTypes/interface/PPSTimingTypes.h"
//#include "DataFormats/TotemRPDataTypes/interface/RPTypes.h"

//#include "DataFormats/PPSDetId/interface/PPSTimingDetId.h"

class RPLBarDigi {
 public:
//  RPLBarDigi (RPDetId det_id=0,// unsigned short lbar_no=0,
    RPLBarDigi (TimingId det_id=0, double leadingTime =-1, double trailingTime=-1, unsigned short strip_no=0)
    {
      det_id_=det_id; 
      strip_no_=strip_no;
      leadingTime_ =leadingTime;  
      trailingTime_ =trailingTime; 
    };
  inline  TimingId GetDetId() const {return det_id_;}
  inline unsigned short GetStripNo() const {return strip_no_;}
  double GetLeadingTime() const {return leadingTime_;}
  double GetTrailingTime() const {return trailingTime_;}

 private:
  TimingId det_id_;
  unsigned short strip_no_;
  double leadingTime_; 
  double trailingTime_;
};

// Comparison operators
inline bool operator<( const RPLBarDigi& one, const RPLBarDigi& other) {
  if(one.GetDetId() < other.GetDetId())
    return true;
   else if(one.GetDetId() == other.GetDetId())
    return one.GetStripNo() < other.GetStripNo();
  else 
    return false;
}

#endif
