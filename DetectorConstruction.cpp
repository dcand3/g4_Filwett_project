#include "DetectorConstruction.hh"
#include "event.hh"

#include "G4Track.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4TouchableHistory.hh"
#include "G4VTouchable.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

// This file defines the MySensitiveDetector class, responsible for processing
// individual particle hits in sensitive detector volumes. DetectorConstruction
// reacts immediately to each particle step inside a sensitive volume (a "hit")
// Scope: step-by-step /  per particle step 
//
//What happens here?
// Every time a particle takes a step inside a sensitive volume, ProcessHits() is called.
// It checks if the particle is a primary, and if any energy was deposited.
// It gets the energy deposited in this single step.
// It knows which detector was hit (copyNo) and where it is (y, z, position).
// It reports this small piece of information to MyEventAction.
// Similar to how a sensitive detector "notices" a hit and immediately reports that information
//	to someone else (EventAction). It does not store much itself - it just relays information per step
//
// Purpose:
// - Record energy deposited by each primary particle in each detector per step.
// - Identify which specific detector volume (copy number) was hit.
// - Record the (y, z) position of each detector volume for output.
//
// Summary:
// - Ignores hits from secondary particles (non-primary).
// - Ignores steps with no energy deposit.
// - Sends energy deposit and detector position information to the EventAction.
//
// Note:
// The actual accumulation and writing of data happens in the EventAction class.
//


// Constructor: initializes the sensitive detector with a given name
MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

// Destructor
MySensitiveDetector::~MySensitiveDetector()
{}

// Main function called when a particle step occurs in a sensitive volume
G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();
	
	// only continue if this is a primary paritcle (one of the initial particles)
	// may need to adjust this if our detectors are sensitive enough to pick up electrons and so forth
	if (track->GetParentID() != 0) return false;
	
	// Energy deposited in this step
	G4double energyDep = aStep->GetTotalEnergyDeposit();
	
	// Ignore steps with zero energy deposition (e.g., optical photons)
	if (energyDep == 0) return false;
	
	// Get information about which detector volume was hit
	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
	// copyNo is defined in VolumeConstruction (i + stackIndex * numDetectors)
	// unique ID for the detector hit
	G4int copyNo = touchable ->GetCopyNumber();
	G4VPhysicalVolume *physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation();
	
	G4double y = posDetector[1];
	G4double z = posDetector[2];
	
	// this is now done in event.cpp
	G4cout <<"Detector position: " << posDetector << G4endl;
	G4cout <<"Deposited Energy: " << energyDep << G4endl;
	
	// Get the EventAction instance to record the energy deposition
	auto eventAction = const_cast<MyEventAction*>(
		static_cast<const MyEventAction*>(G4RunManager::GetRunManager()->GetUserEventAction()));
	
	
	// Accumulate energy deposit per particle (track ID) and detector (copy number)
	eventAction->AddEnergyDep(track->GetTrackID(), copyNo, energyDep);
	
	//Record detector position (y, z) once per copyNo
	eventAction->fDetectorPosition[copyNo] = std::make_pair(y, z);
	
	return true;	
}