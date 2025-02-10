#include "run.hh"
//research build

// for this to be called, we include it in action files
MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}
//create file and write info to file
void MyRunAction::BeginOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->OpenFile("output.root");
	
	// records hits, and x, y, z location
	man->CreateNtuple("Hits", "Hits");
	man->CreateNtupleIColumn("fEvent");
	//DColumn specifies we are filling with double
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	man->FinishNtuple(0);
	//zeroeth N tuple created (why FinishNtuple is given 0 as input
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->Write();
	man->CloseFile();
}
