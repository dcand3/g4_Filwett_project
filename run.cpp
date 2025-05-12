#include "run.hh"
//research build

// ----------------------------------------------------------------------------
// File: run.cpp
// What this file does:
//   This file defines the `MyRunAction` class, which handles the actions to 
//   be taken at the start and end of each run in a Geant4 simulation. It 
//   uses the Geant4 `G4AnalysisManager` to manage data analysis, including 
//   creating and writing ntuples (data structures used for storing results) 
//   during the simulation's execution. Specifically, the file sets up the 
//   analysis output (such as event data and energy deposition information), 
//   opens a file for output, and writes data to it during the simulation.
//
// Key Components:
//   - `MyRunAction`: The class that defines actions to be taken at the beginning 
//     and end of a run. This includes managing data collection and output.
//   - `G4AnalysisManager`: The Geant4 class responsible for managing data 
//     analysis tasks, including creating and filling ntuples and writing output files.
//
// Declared Methods and Functions:
//   - `MyRunAction()`: Constructor for the `MyRunAction` class. Initializes the 
//     `G4AnalysisManager` and sets up an ntuple for storing hit information (event 
//     number, energy deposited, and detector positions).
//   - `~MyRunAction()`: Destructor for the `MyRunAction` class. No specific 
//     action is required here in this case, but it's defined for proper cleanup.
//   - `BeginOfRunAction(const G4Run* run)`: This function is called at the start 
//     of each run. It initializes the output file for storing results (e.g., "output.csv").
//   - `EndOfRunAction(const G4Run*)`: This function is called at the end of each run. 
//     It writes all accumulated data to the output file and closes the file.
//
// Key Functionality:
//   - **Constructor (`MyRunAction()`)**: Initializes the analysis manager and 
//     creates an ntuple named "Hits" to store event-related data such as event ID 
//     (`fEvent`), energy deposition (`fEnergyDep`), and positions (`fY`, `fZ`).
//   - **BeginOfRunAction**: Opens the output file (e.g., "output.csv") to record 
//     simulation results. This file will be written during the simulation.
//   - **EndOfRunAction**: Finalizes the data collection by writing the contents 
//     of the ntuple to the output file and closes the file when the run finishes.
//
// Dependencies:
//   - `G4Run`: The Geant4 class that represents a single run of the simulation.
//   - `G4AnalysisManager`: The class responsible for managing data analysis tasks 
//     like creating and writing ntuples.
//   - `G4RunManager`: Manages the overall simulation process, including the run actions.
//
// Purpose:
//   - The purpose of this file is to manage the beginning and end of the simulation run, 
//     setting up the data collection (ntuple creation) and writing the results (such as 
//     energy deposition and position information) to a file (e.g., CSV or ROOT format).
//
// When it's used:
//   - This file is used during the simulation run. Specifically, it is triggered 
//     by the `G4RunManager` as part of the simulation process. The functions 
//     `BeginOfRunAction` and `EndOfRunAction` are automatically called at the 
//     start and end of each run, respectively.
//
// Additional Notes:
//   - The file is configured to create a new output file ("output.csv") for each run. 
//     This can be modified to create files with dynamic names (e.g., using the run ID).
//   - The ntuple format is used to store hit information, which can later be analyzed 
//     to study the simulation results.
// ----------------------------------------------------------------------------

// for this to be called, we include it in action files
MyRunAction::MyRunAction()
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	// records hits, and x, y, z location
	man->CreateNtuple("Hits", "Hits");
	man->CreateNtupleIColumn("fEvent");
	//DColumn specifies we are filling with double
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	man->CreateNtupleDColumn("fEnergyDep");
	man->FinishNtuple(0);
	//zeroeth N tuple created (why FinishNtuple is given 0 as input
	
}

MyRunAction::~MyRunAction()
{}
//create file and write info to file
void MyRunAction::BeginOfRunAction(const G4Run* run)
{	
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	//man->SetDefaultFileType("csv");
	man->OpenFile("output.csv");
	//To create a new output file for each run
	//G4int runID = run->GetRunID();
	//std::stringstream strRunID;
	//strRunID << runID;
	//man->OpenFile("output"+strRunID.str()+".root");
	
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->Write();
	man->CloseFile();
}
