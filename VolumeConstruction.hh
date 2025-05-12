#ifndef VOLUMECONSTRUCTION_HH
#define VOLUMECONSTRUCTION_HH
//research build

#include "G4SystemOfUnits.hh" //allows us to use metric system in volume construction
#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
//#include "DetectorConstruction.hh"
//#include "ElectricField.hh"

// ----------------------------------------------------------------------------
// File: VolumeConstruction.hh
// What this file does:
//   This header file declares the `VolumeConstruction` class, which is responsible 
//   for setting up and constructing the physical and logical volumes in the Geant4 
//   detector simulation. It also manages sensitive detectors, the electric field region, 
//   and links these elements to the simulation environment.
//
// Key Components:
//   - `VolumeConstruction`: A class that inherits from `G4VUserDetectorConstruction`
//     and implements the `Construct()` method to define and build the geometry for 
//     detectors, including the setup for volumes and sensitive detector regions.
//   
// Declared Methods and Functions:
//   - `VolumeConstruction()`: Constructor that initializes the necessary parameters 
//     and volumes for the detector construction.
//   - `~VolumeConstruction()`: Destructor for cleaning up resources.
//   - `Construct()`: A method that creates the world volume and detector volumes, 
//     placing them correctly in the simulation environment. It returns the root physical volume.
//   - `ConstructSDandField()`: This method is used to define and initialize sensitive 
//     detectors as well as electric field regions in the simulation. It handles the logic for 
//     creating regions for the electric field and associating detectors with the appropriate regions.
//
// Purpose:
//   - The purpose of this file is to define the geometry, sensitive detectors, and electric 
//     field regions that will be used in the Geant4 simulation. The `VolumeConstruction` class 
//     manages the entire structure of the detector system and its interaction with the 
//     electric field, making it a crucial component of the simulation setup.
//
// When it's used:
//   - This file is part of the setup phase of a Geant4 simulation. The `VolumeConstruction` 
//     class is instantiated and used when the simulation is initialized. The `Construct()` method 
//     is called to build the detector geometry, and `ConstructSDandField()` configures sensitive 
//     detectors and fields before the actual simulation begins.

// create detector class inherited from G4UserDetectorConstruction class implimented in G4
class VolumeConstruction : public G4VUserDetectorConstruction
{
	public:
		VolumeConstruction();
		~VolumeConstruction();
		
		virtual G4VPhysicalVolume *Construct();
	
	//Declaring detector and field logical volumes
	private:
		G4LogicalVolume *logicDetector; // 50 micron detectors
		G4LogicalVolume * logicDetectorThick; // 300 micron detectors
		G4LogicalVolume *logicalFieldVolume;
		//ConstructSD is for sensitive detectors
		
		// Electric field region parameters need to be defined here so we can use them in both Construct() and ConstructSDandField()
		G4double fieldRegionSizeX;
		G4double fieldRegionSizeY;
		G4double fieldRegionSizeZ;
		G4double fieldZ0;

		virtual void ConstructSDandField();
};	

#endif