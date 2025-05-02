#ifndef DETECTOR_HH
#define DETECTOR_HH
//research build

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"

class MySensitiveDetector : public G4VSensitiveDetector
{
	public:
		MySensitiveDetector(G4String name);
		virtual ~MySensitiveDetector();
	//Now the main component of the detector
	//This is needed to detect hits on sensor
	
		virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history) override;
	
	private:
		// Helper function to extract hit info
		void LogHitDetails(const G4Step* step) const;
		
	
};

#endif