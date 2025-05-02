#include "run.hh"
//research build

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
