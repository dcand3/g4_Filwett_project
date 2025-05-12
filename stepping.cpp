#include "stepping.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4Vtouchable.hh"
#include "G4TouchableHandle.hh"
#include "G4LogicalVolume.hh"

// ----------------------------------------------------------------------------
// File: stepping.cpp
// What this file does:
//   This file defines the `MySteppingAction` class, which is responsible for handling 
//   the actions that occur at each step of the particle in the simulation. It processes 
//   the energy deposition for each step and sends this information to the event action.
//
// Key Components:
//   - `MySteppingAction`: The class that handles the actions to be performed at each 
//     step during the simulation. It processes the energy deposited during each step 
//     and records it for later analysis.
//
// Declared Methods and Functions:
//   - `MySteppingAction(MyEventAction* eventAction)`: Constructor that initializes the 
//     stepping action with a reference to the `MyEventAction` class, allowing it to 
//     report energy deposition data to the event action.
//   - `~MySteppingAction()`: Destructor for cleaning up the `MySteppingAction` instance.
//   - `UserSteppingAction(const G4Step* step)`: This method is called by Geant4 during 
//     the simulation step. It checks the energy deposition in the current step and, if 
//     there is energy deposited, it reports this data to the `MyEventAction` class.
//
// Purpose:
//   - The purpose of this file is to define the behavior at each simulation step, 
//     particularly tracking energy deposition by particles and reporting it for further 
//     analysis. It plays a role in accumulating data for later output.
//
// When it's used:
//   - This file is used during the simulation to process each particle step. The 
//     `UserSteppingAction` method is invoked automatically by Geant4 at each step of 
//     the simulation to record energy deposition and send it to the event action.
//
// Additional Notes:
//   - The class relies on the `MyEventAction` instance to report energy deposition 
//     per track and per detector copy number.
//   - Only steps where energy is deposited (non-zero energy) are processed to 
//     avoid unnecessary actions.

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