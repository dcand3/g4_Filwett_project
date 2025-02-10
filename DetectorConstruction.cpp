#include "DetectorConstruction.hh"
//"name" is the name of detector
MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	
	G4Track *track = aStep->GetTrack();
	// when particle enters sensitive volume, it has beginning and end
	// so now define two step points (PreStepPoint when enters sens vol)
	G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
	G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
	
	// Without the following function, photons can enter detector from the side (for ex)
	// and positions will be within the detector. (upper surface of det should be 480 in z)
	// This does not allow photon to propogate any further into the detector
	//track->SetTrackStatus(fStopAndKill);
	
	// To get position of particle
	G4ThreeVector posParticle = preStepPoint->GetPosition();
	
	// To display position
	//G4cout << "		Particle position: " << posParticle << G4endl;
	
	// To have access to detector positions that particles hit
	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
	// below gives position of detector as defined in VolumeConstruction (j+i*100)
	G4int copyNo = touchable ->GetCopyNumber();
	
	// If instead we want the position of that detector
	G4VPhysicalVolume *physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation();
	G4cout <<"Detector position: " << posDetector << G4endl;
	
	// Defining event ID number
	G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	// Now we fill the created columns
	// evt is event number
	// First arg in Fill..Column tells you which column we are filling.
	// if we add/remove columns in run.cpp, we must also change integers here
	man->FillNtupleIColumn(0, evt);
	man->FillNtupleDColumn(1, posDetector[1]);
	man->FillNtupleDColumn(2, posDetector[2]);
	// Below we have "0" since it is the zeroeth Ntuple.
	man->AddNtupleRow(0);
	
	return true;	
}