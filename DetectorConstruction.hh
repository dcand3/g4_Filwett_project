#ifndef DETECTOR_HH
#define DETECTOR_HH
//research build

#include "G4VSensitiveDetector.hh"
#include "G4Step.hh"
#include "G4TouchableHistory.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"

// ----------------------------------------------------------------------------
// File: DetectorConstruction.hh
// What this file does:
// This file defines the MySensitiveDetector class, which inherits from the
// G4VSensitiveDetector class. It sets up the basic structure for detecting
// and processing particle hits inside a sensitive volume (detector).
//
// Purpose:
// - MySensitiveDetector is responsible for detecting when a particle steps inside
// a sensitive detector volume and handling the data related to that hit.
// - The main function to handle this is ProcessHits(), which is overridden from
// the base class to define what happens when a hit occurs in a detector.
//
// Key Components:
// - ProcessHits(): the core function that is called whenever a particle interacts
// with the sensitive detector. It processes information about the particle hit,
// like energy deposition and position in the detector.
// - LogHitDetails(): a helper function that logs the hit information from
// a particle step (used for debugging or detailed analysis).
//
// Dependencies:
// - G4VSensitiveDetector: Geant4 base class for handling sensitive detector actions.
// - G4Step, G4TouchableHistory: Geant4 classes used to handle information about
// particle steps and the detector's geometry during hits.
// - G4AnalysisManager, G4RunManager, G4SDManager: Geant4 classes used for
// data management and storing information during the simulation.
//
// When it's used:
// This file is included in the main simulation setup, specifically in defining
// how hits are processed in each sensitive volume (like a detector or sensor).
// ----------------------------------------------------------------------------

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