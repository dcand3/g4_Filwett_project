#ifndef RUN_HH
#define RUN_HH
//research build

#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4Run.hh"

// ----------------------------------------------------------------------------
// File: generator.hh
// What this file does:
//   This file defines the MyRunAction class, which is responsible for actions 
//   performed at the beginning and end of each simulation run. It provides hooks 
//   for handling run-specific initialization and finalization tasks, such as 
//   opening and closing files, and processing results after the simulation run.
//
// What happens here:
//   - The MyRunAction class inherits from G4UserRunAction, which is a Geant4 base 
//     class for handling run-level actions.
//   - The BeginOfRunAction() function is called automatically by Geant4 at the 
//     start of each run. This function is where you would initialize things 
//     specific to each run, such as opening a file to save results.
//   - The EndOfRunAction() function is called automatically by Geant4 at the 
//     end of each run. This function is where you can handle finalization tasks, 
//     such as closing files and processing run-level data.
//
// Key Components:
//   - MyRunAction: a user-defined class that overrides the BeginOfRunAction() 
//     and EndOfRunAction() methods to customize the behavior of the simulation 
//     run, such as opening and closing files and managing run-specific data.
//   - BeginOfRunAction(): the function called at the start of each run to 
//     initialize run-level actions.
//   - EndOfRunAction(): the function called at the end of each run to finalize 
//     actions and perform cleanup tasks.
//
// When it's used:
//   This file is used during the simulation to define what actions should be 
//   taken at the beginning and end of each run. It is included in the simulation 
//   setup and linked to the run management of Geant4.
//
// ----------------------------------------------------------------------------

class MyRunAction : public G4UserRunAction
{
	public:
		MyRunAction();
		~MyRunAction();
	
		virtual void BeginOfRunAction(const G4Run*);
		virtual void EndOfRunAction(const G4Run*);
};

#endif