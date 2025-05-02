#include "stepping.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4Vtouchable.hh"
#include "G4TouchableHandle.hh"
#include "G4LogicalVolume.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
	fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
	G4double energyDep = step->GetTotalEnergyDeposit();
	
	if (energyDep == 0.)
		return;
	
	G4int trackID = step->GetTrack()->GetTrackID();
	const G4VTouchable* touchable = step->GetPreStepPoint()->GetTouchable();
	G4int copyNo = touchable->GetCopyNumber();
	
	fEventAction->AddEnergyDep(trackID, copyNo, energyDep);
}