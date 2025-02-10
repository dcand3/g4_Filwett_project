#ifndef VOLUMECONSTRUCTION_HH
#define VOLUMECONSTRUCTION_HH
//research build

#include "G4SystemOfUnits.hh" //allows us to use metric system in volume construction
#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
//#include "DetectorConstruction.hh"
//#include "ElectricField.hh"



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
		G4LogicalVolume * logicDetectorTwo; // 300 micron detectors
		G4LogicalVolume *logicField;
		//ConstructSD is for sensitive detectors
		//if we had fields we would also need to include them here (?)
		virtual void ConstructSDandField();
};	

#endif