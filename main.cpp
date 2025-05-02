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