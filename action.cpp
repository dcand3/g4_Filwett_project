#include "action.hh"
#include "generator.hh"
#include "event.hh"

#include <iostream>

// ----------------------------------------------------------------------------
// File: action.cpp
// What this file does:
//   This file defines the `MyActionInitialization` class, which sets up 
//   user actions for a Geant4 simulation. These actions control various aspects 
//   of the simulation, including particle generation, event handling, and data 
//   collection. The file initializes these actions and associates them with the 
//   simulation through the `SetUserAction()` method.
//
// Key Components:
//   - `MyActionInitialization`: The class responsible for setting up all the user 
//     actions needed for the simulation, including primary particle generation, 
//     run actions, and event actions.
//   - `PrimaryGenerator`: The class responsible for generating primary particles.
//   - `MyRunAction`: The class responsible for actions at the start and end of a run, 
//     including managing data output (e.g., ntuples).
//   - `MyEventAction`: The class responsible for actions at the start and end of an event, 
//     such as recording hit information.
//
// Declared Methods and Functions:
//   - `MyActionInitialization()`: Constructor for the `MyActionInitialization` class.
//     It initializes the object but does not perform any setup.
//   - `~MyActionInitialization()`: Destructor for the `MyActionInitialization` class.
//     No specific cleanup is necessary for this class.
//   - `Build()`: This method sets up the user actions for the simulation. It initializes 
//     the primary generator, run action, and event action, and associates them with 
//     the simulation using `SetUserAction()`.
//
// Key Functionality:
//   - **Constructor (`MyActionInitialization()`)**: Initializes the `MyActionInitialization` 
//     class object, but no specific actions are taken here.
//   - **Destructor (`~MyActionInitialization()`)**: The destructor is defined but does not 
//     perform any explicit cleanup in this case.
//   - **Build**: This method creates instances of `PrimaryGenerator`, `MyRunAction`, and 
//     `MyEventAction`. It then associates these actions with the Geant4 simulation 
//     using `SetUserAction()`. These actions will be triggered at appropriate times 
//     during the simulation (e.g., event generation, run actions, and event handling).
//
// Purpose:
//   - The purpose of this file is to initialize and set up all necessary user actions 
//     required for running a Geant4 simulation. These actions include generating primary 
//     particles, handling run-level data output, and processing event-specific information.
//
// When it's used:
//   - This file is used during the initialization phase of the simulation. The `Build()` 
//     method is called by the Geant4 `G4VUserActionInitialization` interface to initialize 
//     user-defined actions such as generating primary particles, handling event data, and 
//     managing run-level information.
//
// Additional Notes:
//   - This file serves as a central point for managing all user actions in the simulation. 
//     By calling `SetUserAction()`, it ensures that each action is appropriately connected 
//     to the simulation pipeline (e.g., primary particle generation, event processing).
// ----------------------------------------------------------------------------

MyActionInitialization::MyActionInitialization() {}

MyActionInitialization::~MyActionInitialization() {}

void MyActionInitialization::Build() const
{
    PrimaryGenerator* generator = new PrimaryGenerator();
    SetUserAction(generator);

    MyRunAction* runAction = new MyRunAction();
    SetUserAction(runAction);
	
	MyEventAction* eventAction = new MyEventAction(runAction);
	SetUserAction(eventAction);
}
