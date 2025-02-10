#ifndef DETECTOR_HH
#define DETECTOR_HH
//research build

#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"

class MySensitiveDetector : public G4VSensitiveDetector
{
	public:
		MySensitiveDetector(G4String);
		~MySensitiveDetector();
	//Now the main component of the detector
	//This is needed to detect hits on sensor
	private:
		virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
	
};

#endif