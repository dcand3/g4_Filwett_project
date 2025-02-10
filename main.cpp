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

int main(int argc, char** argv)
{
	G4RunManager *runManager = new G4RunManager();
	
	runManager->SetUserInitialization(new VolumeConstruction());
	runManager->SetUserInitialization(new MyPhysicsList());
	runManager->SetUserInitialization(new MyActionInitialization());
	
	runManager->Initialize();
	
	G4UIExecutive *ui = new G4UIExecutive(argc, argv);
	
	G4VisManager *visManager = new G4VisExecutive();
	visManager ->Initialize();
	
	G4UImanager *uiManager = G4UImanager::GetUIpointer();
	//To see volumes
	uiManager->ApplyCommand("/vis/initialize");
	uiManager->ApplyCommand("/vis/open TSG");
	uiManager->ApplyCommand("/vis/drawVolume");
	
	//To see particles
	uiManager->ApplyCommand("/vis/scene/add/trajectories smooth");
	
	//To update everytime we create an event
	uiManager->ApplyCommand("vis/viewer/set/autoRefresh true");
	
	//To accumulate all sequential events into a single run
	uiManager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
	
	//To visualize the electric field
	uiManager->ApplyCommand("/vis/scene/add/electricField");
	
	ui ->SessionStart();
	
	return 0;
}