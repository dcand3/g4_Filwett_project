#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "VolumeConstruction.hh"
#include "physics.hh"
#include "action.hh"
#include "generator.hh"
//research build

// ----------------------------------------------------------------------------
// File: main.cpp
// What this file does:
//   This file contains the main entry point for the Geant4 simulation. It sets 
//   up and initializes the Geant4 environment, including the run manager, the 
//   user-defined components (such as detector construction, physics list, and actions), 
//   and the visualization system. Depending on whether the program is running in 
//   batch mode or interactive mode, it will either process a macro file or open 
//   a graphical user interface (GUI) to allow the user to interact with the simulation.
//
// Key Components:
//   - G4UIExecutive: Used to handle the interactive user interface if no arguments 
//     are passed (indicating interactive mode).
//   - G4RunManager: Manages the overall flow of the Geant4 simulation, including 
//     initializing and running the simulation.
//   - G4VisManager & G4VisExecutive: Manage the visualization system, initializing 
//     it and applying commands to visualize different elements of the simulation.
//   - G4UImanager: Used to apply Geant4 UI commands, such as visualizing volumes, 
//     running macro files, and managing user commands.
//
// Declared Methods and Functions:
//   - `main(int argc, char** argv)`: The main function that initializes the Geant4 
//     simulation environment, sets up the user-defined actions, and runs the simulation. 
//     It also handles the initialization of the user interface (UI) and visualization 
//     based on whether the program is running in interactive or batch mode.
//
// Key Functionality:
//   - Initializes the Geant4 run manager, sets user-defined actions, and starts the simulation.
//   - Initializes the visualization system, which allows the user to view volumes, 
//     visualize the electric field, and manage UI commands.
//   - Depending on command-line arguments, either runs in batch mode or opens a GUI for user interaction.
//     - In batch mode, the program executes a macro file.
//     - In interactive mode, it starts an interactive session and allows for visualization and 
//       manual control of the simulation.
//
// Dependencies:
//   - `G4RunManager`: Manages the Geant4 simulation process.
//   - `G4UIExecutive`: Handles the user interface in interactive mode.
//   - `G4VisManager` and `G4VisExecutive`: Handle visualization commands and the visualization session.
//   - `G4UImanager`: Handles the execution of UI commands like opening volumes and running macros.
//   - `VolumeConstruction`, `MyPhysicsList`, `MyActionInitialization`: User-defined classes 
//     that initialize the simulation's physical components, actions, and geometry.
//   - `generator.hh`, `physics.hh`, `action.hh`: Headers for user-defined components like 
//     particle generation, physics list, and action initialization.
//   
// Purpose:
//   - This file serves as the entry point for the Geant4 simulation, managing 
//     the initialization and execution of the simulation, including setup of the user interface 
//     and visualization, as well as running in batch or interactive mode.
//
// When it's used:
//   - This file is executed when starting the Geant4 simulation, either in batch mode 
//     (via command-line arguments) or in interactive mode (with a UI).
//
// Additional Notes:
//   - In batch mode, a macro file specified by the user is executed to control the simulation.
//   - In interactive mode, the user can interact with the simulation, visualize its components, 
//     and use the GUI to modify settings or view results in real time.
// ----------------------------------------------------------------------------

int main(int argc, char** argv)
{	
// Instantiate G4UIExecutive if there are no arguments (interactive mode)
	G4UIExecutive* ui = nullptr;
	if (argc == 1) {
		ui = new G4UIExecutive(argc, argv);
	}
	
	G4RunManager *runManager = new G4RunManager();
	
	runManager->SetUserInitialization(new VolumeConstruction());
	runManager->SetUserInitialization(new MyPhysicsList());
	runManager->SetUserInitialization(new MyActionInitialization());
	
	runManager->Initialize();
	
	//G4UIExecutive *ui = new G4UIExecutive(argc, argv);
	
	G4VisManager *visManager = new G4VisExecutive();
	visManager ->Initialize();
	
	G4UImanager *uiManager = G4UImanager::GetUIpointer();
	//To see volumes
	uiManager->ApplyCommand("/vis/initialize");
	uiManager->ApplyCommand("/vis/open TSG");
	uiManager->ApplyCommand("/vis/drawVolume");
	
	//To run mac files
  if (!ui)  // batch mode
  {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    uiManager->ApplyCommand(command + fileName);
  }
  else {
    uiManager->ApplyCommand("/control/execute init_vis.mac");
    uiManager->ApplyCommand("/control/execute gui.mac");
    ui->SessionStart();
    delete ui;
  }
	
	//To see volumes
//	uiManager->ApplyCommand("/vis/initialize");
//	uiManager->ApplyCommand("/vis/open TSG");
	
	//To visualize the electric field
//	uiManager->ApplyCommand("/vis/scene/add/electricField");

	delete visManager;
	delete runManager;
	
	return 0;
}