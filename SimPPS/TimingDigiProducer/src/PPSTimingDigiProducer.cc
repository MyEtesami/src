#include "SimPPS/TimingDigiProducer/interface/PPSTimingDigiProducer.h"

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimDataFormats/CrossingFrame/interface/CrossingFrame.h"
#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"
#include <cstdlib> // I need it for random numbers
//needed for the geometry:
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/TotemRPDataTypes/interface/RPStripDigi.h"
//#include "DataFormats/TotemRPDataTypes/interface/RPDetTrigger.h"
#include "DataFormats/PPSTimingDataTypes/interface/PPSTimingLBarDigi.h"
#include "DataFormats/PPSTimingDataTypes/interface/PPSTimingTrigger.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/TotemRPDetId/interface/TotRPDetId.h"

//Random Number
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "CLHEP/Random/RandomEngine.h"
#include "TotemCondFormats/DAQInformation/interface/AnalysisMask.h"
#include "TotemCondFormats/DataRecord/interface/TotemDAQMappingRecord.h"

PPSTimingDigiProducer::PPSTimingDigiProducer(const edm::ParameterSet& conf) :
	conf_(conf) {
	//register your products
	/* Examples
	 produces<ExampleData2>();

	 //if do put with a label
	 produces<ExampleData2>("label");
	 */
	//now do what ever other initialization is needed
	//  std::string strip_digi_label ( conf.getParameter<std::string>("StripDigiLabel") );
	//  std::string strip_trigger_label ( conf.getParameter<std::string>("StripTriggerLabel") );

        produces<edm::DetSetVector<PPSTimingLBarDigi> > ();
        produces<edm::DetSetVector<PPSTimingTrigger> > ();

	
        RP_hit_containers_.clear();
	RP_hit_containers_ = conf.getParameter<std::vector<std::string> > ("ROUList");
	verbosity_ = conf.getParameter<int> ("PPSVerbosity");

	edm::Service < edm::RandomNumberGenerator > rng;
	if (!rng.isAvailable()) {
		throw cms::Exception("Configuration") << "This class requires the RandomNumberGeneratorService\n"
			"which is not present in the configuration file.  You must add the service\n"
			"in the configuration file or remove the modules that require it.";
	}

	rndEngine = &(rng->getEngine());
}

PPSTimingDigiProducer::~PPSTimingDigiProducer() {

	// do anything here that needs to be done at desctruction time
	// (e.g. close files, deallocate resources etc.)

}

//
// member functions
//

// ------------ method called to produce the data  ------------
void PPSTimingDigiProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
	using namespace edm;
	/* This is an event example
	 //Read 'PSimHit' from the Event
	 Handle<PSimHit> pIn;
	 iEvent.getByLabel("TotemHitsRP",pIn);

	 //Use the ExampleData to create an ExampleData2 which
	 // is put into the Event
	 std::auto_ptr<ExampleData2> pOut(new ExampleData2(*pIn));
	 iEvent.put(pOut);
	 */

	/* this is an EventSetup example
	 //Read SetupData from the SetupRecord in the EventSetup
	 ESHandle<SetupData> pSetup;
	 iSetup.get<SetupRecord>().get(pSetup);
	 */

	// Step A: Get Inputs
	edm::Handle<CrossingFrame<PSimHit> > cf;
	//    iEvent.getByType(cf);
	const std::string subdet("g4SimHitsPPSTimingHits");
	iEvent.getByLabel("mix", subdet, cf);

        std::cout << "\n\n=================== Starting SimHit access, subdet " << subdet
                        << "  ===================" << std::endl;

	if (verbosity_) {
		std::cout << "\n\n=================== Starting SimHit access, subdet " << subdet
		        << "  ===================" << std::endl;

		std::auto_ptr<MixCollection<PSimHit> > col(
		        new MixCollection<PSimHit> (cf.product(), std::pair<int, int>(-0, 0)));
		std::cout << *(col.get()) << std::endl;
		MixCollection<PSimHit>::iterator cfi;
		int count = 0;
		for (cfi = col->begin(); cfi != col->end(); cfi++) {
			std::cout << " Hit " << count << " has tof " << cfi->timeOfFlight() << " trackid "
			        << cfi->trackId() << " bunchcr " << cfi.bunch() << " trigger " << cfi.getTrigger()
			        << ", from EncodedEventId: " << cfi->eventId().bunchCrossing() << " "
			        << cfi->eventId().event() << " bcr from MixCol " << cfi.bunch() << std::endl;
			std::cout << " Hit: " << (*cfi) << std::endl;
			count++;
		}
	}

	//std::auto_ptr<MixCollection<PSimHit> > allRPHits(new MixCollection<PSimHit>(cf.product(),RP_hit_containers_));
	std::auto_ptr<MixCollection<PSimHit> > allPPSHits(
	        new MixCollection<PSimHit> (cf.product(), std::pair<int, int>(0, 0)));

//                std::cout << "Input MixCollection size = " << allRPHits->size() << " *(allRPHits.get()): " << *(allRPHits.get()) << std::endl;
                MixCollection<PSimHit>::iterator cfi;

	if (verbosity_)
		std::cout << "Input MixCollection size = " << allPPSHits->size() << std::endl;

	//Loop on PSimHit
	SimHitMap.clear();

	MixCollection<PSimHit>::iterator isim;
	for (isim = allPPSHits->begin(); isim != allPPSHits->end(); ++isim) {
		SimHitMap[(*isim).detUnitId()].push_back((*isim));
	}

	// Step B: LOOP on hits in event
	theDigiVector.reserve(400);
	theDigiVector.clear();
	theTriggerVector.reserve(240);
	theTriggerVector.clear();

	for (simhit_map_iterator it = SimHitMap.begin(); it != SimHitMap.end(); ++it) {

                edm::DetSet<PPSTimingLBarDigi> digi_collector(it->first);
                edm::DetSet<PPSTimingTrigger> trigger_collector(it->first);
		if (theAlgoMap.find(it->first) == theAlgoMap.end()) {
			theAlgoMap[it->first] = boost::shared_ptr<PPSDetDigitizer>(
			      new PPSDetDigitizer(conf_, *rndEngine, it->first));
		}
		std::vector<int> input_links;
		SimPPSTiming::TimingDigiPrimaryMapType output_digi_links;
		SimPPSTiming::TimingTriggerPrimaryMapType output_trig_links;
		(theAlgoMap.find(it->first)->second)->run(SimHitMap[it->first], input_links, digi_collector.data,
		        trigger_collector.data, output_digi_links, output_trig_links);

		std::vector<PPSTimingLBarDigi>::iterator stripIterator = digi_collector.data.begin();

		if (digi_collector.data.size() > 0) {
			theDigiVector.push_back(digi_collector);
		}
		if (trigger_collector.data.size() > 0) {
			theTriggerVector.push_back(trigger_collector);
		}
	}

	// Step C: create empty output collection

	std::auto_ptr<edm::DetSetVector<PPSTimingLBarDigi> > digi_output(
	        new edm::DetSetVector<PPSTimingLBarDigi>(theDigiVector));

        std::auto_ptr<edm::DetSetVector<PPSTimingTrigger> > trigger_output(
                new edm::DetSetVector<PPSTimingTrigger>(theTriggerVector));


	if (verbosity_) {
		std::cout << "digi_output->size()=" << digi_output->size() << std::endl;
		std::cout << "trigger_output->size()=" << trigger_output->size() << std::endl;
	}
	
//                std::cout << "digi_output->size() in digitizer.cc=  " << digi_output->size() << std::endl;
//                std::cout << "trigger_output->size() in digitizer.cc =  " << trigger_output->size() << std::endl;


     // Step D: write output to file
	iEvent.put(digi_output);
	iEvent.put(trigger_output);

}

// ------------ method called once each job just before starting event loop  ------------
void PPSTimingDigiProducer::beginRun(edm::Run&, edm::EventSetup const& es){
	// get analysis mask to mask channels
//	if (simulateDeadChannels) {
//		edm::ESHandle<AnalysisMask> analysisMask;
//		es.get<TotemDAQMappingRecord> ().get(analysisMask);
//		deadChannelsManager = DeadChannelsManager(analysisMask); //set analysisMask in deadChannelsManager
//	}
}

// ------------ method called once each job just after ending the event loop  ------------
void PPSTimingDigiProducer::endJob() {
}

DEFINE_FWK_MODULE( PPSTimingDigiProducer);
