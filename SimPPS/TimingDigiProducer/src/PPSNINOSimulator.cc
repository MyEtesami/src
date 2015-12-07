#include "SimPPS/TimingDigiProducer/interface/PPSNINOSimulator.h"
//#include "SimTotem/RPDigiProducer/interface/RPVFATSimulator.h"
#include "Geometry/TotemRPDetTopology/interface/RPTopology.h"
#include <vector>
#include "TRandom.h"
#include <iostream>


PPSNINOSimulator::PPSNINOSimulator(const edm::ParameterSet &params, TimingId det_id)
 : params_(params), det_id_(det_id)
{
  trigger_mode_ = params_.getParameter<int>("PPSNINOTriggerMode");
  NINOthreshold_ = params.getParameter<double>("PPSNINOThreshold"); // unit:fC
  verbosity_ = params.getParameter<int>("PPSVerbosity");
  links_persistence_ = params.getParameter<bool>("PPSDigiSimHitRelationsPresistence");
}

void PPSNINOSimulator::ConvertTimeToHits(const SimPPSTiming::PhotoElectron_ArrTime_vec &signals,
    SimPPSTiming::PhotoElectron_ArrTime_map_links_type &theSignalProvenance,
    std::vector<PPSTimingLBarDigi> &output_digi, std::vector<PPSTimingTrigger> &output_trig,
    SimPPSTiming::TimingDigiPrimaryMapType &output_digi_links,
    SimPPSTiming::TimingTriggerPrimaryMapType &output_trig_links)
{
  the_trig_cont_.clear();
  the_trig_cont_links_.clear();

  double CollectedCharge = (signals.size())*1.6*0.0001; //Unit:fC **GAIN WAS SET TO 10^3, MUST BE MULTIPLIED BY 1000 DUE TO THE REAL GAIN 10^6**
  double PulseWidth = 0.0;
  double leadingTime = 0.0;
  double trailingTime = 0.0;
//std::cout<<"CollectedCharge: "<<CollectedCharge<<std::endl;
  if (CollectedCharge > NINOthreshold_)
  {

     PulseWidth = PPSNINOSimulator::PulseWidthFunc(CollectedCharge);
     leadingTime = PPSNINOSimulator::LeadingEdgeFunc(CollectedCharge);   
     trailingTime = leadingTime + PulseWidth;
std::cout<<"leadingTime: "<<leadingTime<<", trailingTime: "<<trailingTime<<std::endl;
//      leadingTime = LBarNumber;
//      trailingTime = LBarCharge;
     output_digi.push_back(PPSTimingLBarDigi(det_id_, leadingTime ,  trailingTime));

     if (links_persistence_)
     {
        output_digi_links.push_back(theSignalProvenance[0]);
        if (verbosity_)
        {
            std::cout<<"digi links size="<<theSignalProvenance[0].size()<<std::endl;
        }
     }

     the_trig_cont_.insert(PPSNINOSimulator::LBarNr(det_id_));

     if (links_persistence_)
     {
//        std::vector<double>::const_iterator j=theSignalProvenance[0].begin();
//        std::vector<double>::const_iterator end=theSignalProvenance[0].end();
//        for (; j!=end; ++j)
//        {
            the_trig_cont_links_[PPSNINOSimulator::LBarNr(det_id_)]=theSignalProvenance.at(0);
//        }
      }

   }

   for (SimPPSTiming::TriggerContainer::const_iterator j=the_trig_cont_.begin();
       j!=the_trig_cont_.end(); ++j)
   {
        output_trig.push_back(PPSTimingTrigger(det_id_, *j));
        if (links_persistence_)
        {
//           std::map<int, double>::const_iterator k=the_trig_cont_links_[*j].begin();
//           std::map<int, double>::const_iterator end=the_trig_cont_links_[*j].end();
//           std::vector<std::pair<int, double> > links_vector(k, end);
//           output_trig_links.push_back(links_vector);
           output_trig_links.push_back(theSignalProvenance[0]);
/*
           if (verbosity_)
           {
              std::cout<<"trigger links size="<<links_vector.size()<<std::endl;
              for (unsigned int u=0; u<links_vector.size(); ++u)
              {
                  std::cout<<"   trigger: particle="<<links_vector[u].first<<" energy [electrons]="<<links_vector[u].second<<std::endl;
              }
              std::cout<<std::endl;
           }
*/
         }
    }

//    cout << "detID "<< det_id_ << "   output_digi.size()      " << output_digi.size() <<endl;
//    cout << "detID "<< det_id_ << "   output_trig.size()      " << output_trig.size() <<endl;
    if (verbosity_)
       {
       for (unsigned int i=0; i<output_digi.size(); ++i)
       {
           std::cout<<"NINO Simulator "<<output_digi[i].GetDetId()<<", PPS leading time: " <<output_digi[i].GetLeadingTime()<<", Trailing ti                me:  "<<output_digi[i].GetTrailingTime()<<std::endl;

        }
     }
}

double PPSNINOSimulator::PulseWidthFunc(double InputCharge)
{
       if (InputCharge < 200.0) return 0.02925*InputCharge-0.77155;
       else return 2.381*pow(InputCharge, 0.16125);
}

 
double PPSNINOSimulator::TimeWalkFunc(double pulse_width)
{
       return 2.91265-0.43279*pulse_width;
}

double PPSNINOSimulator::LeadingEdgeFunc(double InputCharge)
{
       if (InputCharge < 100.0) return 1.6;
       else return 2.2;
}

int PPSNINOSimulator::LBarNr(TimingId DetId)
{
/*
    if (DetId < 20) return 1;
    else return 2;
*/
    return 1;
}

