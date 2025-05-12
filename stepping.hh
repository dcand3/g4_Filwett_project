#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"

#include "VolumeConstruction.hh"
#include "event.hh"

// ----------------------------------------------------------------------------
// File: stepping.hh
// What this file does:
//   This header file declares the `MySteppingAction` class, which inherits from 
//   Geant4's `G4UserSteppingAction`. It is responsible for processing actions 
//   at each simulation step, specifically related to energy deposition in the 
//   detector. This class works by utilizing the event action class (`MyEventAction`) 
//   to record and report the energy deposition during each step in the simulation.
//
// Key Components:
//   - `MySteppingAction`: A class that overrides the `UserSteppingAction` method 
//     to track and process energy deposition information at each simulation step. 
//     It communicates the energy deposition to the event action class for accumulation.
// 
// Declared Methods and Functions:
//   - `MySteppingAction(MyEventAction* eventAction)`: Constructor that takes a pointer 
//     to an `MyEventAction` object, which is used to report energy deposition data.
//   - `~MySteppingAction()`: Destructor for cleaning up the object.
//   - `UserSteppingAction(const G4Step*)`: This method is called at each simulation 
//     step to handle energy deposition during that step and forwards the information 
//     to the `MyEventAction` class.
// 
// Purpose:
//   - The purpose of this file is to declare the interface of the `MySteppingAction` class. 
//     This class serves as the core of step-level actions, specifically focusing on energy 
//     deposition and reporting this data to the event action. The functionality is implemented 
//     in the corresponding `stepping.cpp` file.
// 
// When it's used:
//   - This file is used during the simulation steps in Geant4 when the `UserSteppingAction` 
//     method is invoked. The class is initialized and tied into the simulation via the event 
//     action system to track energy deposition events across the run.

class MySteppingAction : public G4UserSteppingAction
{
	
	public:
		MySteppingAction(MyEventAction* eventAction);
		~MySteppingAction();
		
		virtual void UserSteppingAction(const G4Step*);
		
	private:
		MyEventAction *fEventAction;
		
};

#endif