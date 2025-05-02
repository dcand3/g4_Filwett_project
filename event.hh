#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"

#include "run.hh"
#include <map>

class MyEventAction : public G4UserEventAction
{
public:
	MyEventAction(MyRunAction*);
	~MyEventAction();
	
	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);
	
	// Add energy deposited in a particular detector by a given track
	void AddEnergyDep(G4int trackID, G4int copyNo, G4double energyDep) { 
		fTrackEnergyDepMap[trackID][copyNo] += energyDep; }
		// This line says:
		//	for this trackID (i.e. particle), increment the energy deposited
		//	in this detector (copyNo) by energyDep.
	
	// store detector position (y, z) associated with a copy number
	std::map<G4int, std::pair<G4double, G4double>> fDetectorPosition;
	
private:
	// Nested map: trackID -> (copyNo - total energy dep)
	// A std::map is a data structure that stores key-value pairs.
	// The keys are unique and maps to exactly one value.
	//	For example: 
	//		std::map<int, double> energyDep;
	//		energyDep[42] = 3.7
	//		Here, this means "Detector 42 had 3.7 units of energy deposited"
	//		The key is 42, and the value is 3.7
	//		You can retrieve a value by its key:
	//			double energy = energyDep[42] = 3.7
	//
	// the outer map uses trackID (each unique particle) as the key
	// the inner map uses copyNo (each unique detector ID) as the key and stores the
	// total energy deposited (G4double) as the value. 
	//
	std::map<G4int, std::map<G4int, G4double>> fTrackEnergyDepMap;
	
	G4double fEnergyDep;
};

#endif