#ifndef ACTION_HH
#define ACTION_HH
//research build

#include "G4VUserActionInitialization.hh"

#include "generator.hh"
#include "run.hh"

// ----------------------------------------------------------------------------
// File: action.hh
// What this file does:
//   This header file defines the `MyActionInitialization` class, which is responsible 
//   for setting up user-defined actions in the Geant4 simulation. These actions are 
//   responsible for managing various parts of the simulation, such as particle 
//   generation, event processing, and run actions.
//
// Key Components:
//   - `MyActionInitialization`: The main class responsible for initializing all user 
//     actions needed during the simulation, including primary particle generation, 
//     event actions, and run actions.
//
// Declared Methods and Functions:
//   - `MyActionInitialization()`: Constructor for the `MyActionInitialization` class.
//     It initializes the object, but no specific setup is performed in this constructor.
//   - `~MyActionInitialization()`: Destructor for the `MyActionInitialization` class.
//     It performs cleanup tasks when the object is destroyed.
//   - `Build()`: This method is part of the Geant4 `G4VUserActionInitialization` interface.
//     It sets up all user actions, such as generating primary particles, processing 
//     events, and managing run-level data.
//   
// Purpose:
//   - This header file declares the interface for the `MyActionInitialization` class, 
//     which is used to initialize user-defined actions for particle generation, event 
//     handling, and run-level processing in a Geant4 simulation.
//
// When it's used:
//   - This file is included during the simulation setup to initialize user actions.
//     The `Build()` method will be called at the initialization stage to configure 
//     the actions that should be executed during the simulation, such as setting up 
//     the particle gun, run actions, and event actions.
//
// Additional Notes:
//   - This class inherits from `G4VUserActionInitialization`, which is a Geant4 base 
//     class used for setting up and initializing user actions at the beginning of the simulation.
// ----------------------------------------------------------------------------


class MyActionInitialization : public G4VUserActionInitialization
{
	public:
		MyActionInitialization();
		~MyActionInitialization();
		// Build() runs particle gun, computes stepping and so on
		virtual void Build() const;
};

#endif