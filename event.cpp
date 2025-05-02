#include "event.hh"

#include "G4SystemOfUnits.hh"

//
// This file defines the MyEventAction class, which manages actions taken at the 
// beginning and end of each event. This is where the total number of hits are gathered
// after the event ends. Event.cpp collects all the information from hits
// and processes it for output.
//
//What happens here?
// When an event starts, it clears any previous data (BeginOfEventAction).
// As detector hits are reported during the event (via AddEnergyDep()),
//		- it adds up all the energy deposited per particle per detector.
//		- it keeps track of each hits position as a strip location coordinate (y, z).
// When the event ends (EndOfAction):
//		- it loops through the accumulated data and writes it out to ntuples
// 
// The purpose of event.cpp is to:
// - Collects the total energy deposited per particle (trackID) per detector (copyNo) over the whole event.
// - Record the (y, z) position of each detector hit.
// - At the end of the event, output the energy deposition results and fill them into an ntuple
//   for later analysis.
//
// Summary:
// - Energy deposits are collected by track ID and detector ID.
// - Detector positions are stored once per unique detector copy number.
// - All relevant data are saved using the G4AnalysisManager at the end of each event.
//
// Note:
// The actual recording of energy deposits happens inside the sensitive detector
// (MySensitiveDetector::ProcessHits), which calls AddEnergyDep() in this class.
//


MyEventAction::MyEventAction(MyRunAction*)
{
	fEnergyDep = 0.;
}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event*)
{
	// Reset energy dep and clear maps at the beginning of each event
	fEnergyDep = 0.;
	fTrackEnergyDepMap.clear(); 
	fDetectorPosition.clear();
}

void MyEventAction::EndOfEventAction(const G4Event* evt)
{
	G4int eventID = evt->GetEventID();
	G4cout << "End of Event " << eventID << G4endl;
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	// Loop over all tracks that deposited energy
	for (const auto& [trackID, detectorMap] : fTrackEnergyDepMap)
	{
		// For each track, loop over the detectors (copy number) it interacted with
		for (const auto& [copyNo, energy] : detectorMap)
		{
			// Look up the (y, z) position of the detector with this copy number
			auto i_position = fDetectorPosition.find(copyNo);
			// check if we have a stored (y, z) position for this detector
			if (i_position != fDetectorPosition.end())
			{
				//if found, extract y and z positions
				G4double fY = fDetectorPosition[copyNo].first;
				G4double fZ = fDetectorPosition[copyNo].second;
				
				//print out the information about energy deposition per particle per detector
				G4cout << " Particle (track ID) " << trackID
					   << " deposited " << energy / MeV << " MeV"
					   << " in detector copyNo: " << copyNo
					   << " at (y, z) = (" << fY/mm << "mm, " << fZ/mm << " mm)"
					   << G4endl;
	
				man->FillNtupleIColumn(0, eventID);
				man->FillNtupleDColumn(1, fY);
				man->FillNtupleDColumn(2, fZ);
				man->FillNtupleDColumn(3, energy / MeV);
				man->AddNtupleRow(0);
			}
			
			else {
				// if no position is found for this detector copy  number, print a warning
				G4cerr << "---------- Warning: Detector position not found for copyNo " << copyNo << G4endl;
			}
			
		}
	}
}