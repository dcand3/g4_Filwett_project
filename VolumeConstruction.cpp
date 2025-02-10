#include "VolumeConstruction.hh"
#include "DetectorConstruction.hh"
#include "ElectricField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

//research build1

VolumeConstruction::VolumeConstruction()
{}
VolumeConstruction::~VolumeConstruction()
{}
G4VPhysicalVolume* VolumeConstruction::Construct()
{
	    
    // Every volume in G4 must contain 3 parts:
    // 1. Solid: Defines size, for example
    // 2. Logical volume: Defines material
    // 3. Physical volume: Orientation, rotation, translation of volume. Allows for interactions
	//class* variable name = definition

    G4NistManager* nist = G4NistManager::Instance();
	
	//-------Build world (mother volume)------------
	// G4_Galactic is a very low density near vacuum material
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_Galactic");

	//Creating solid volume
    // Create box 1 m long in x, y, z. Tells G4 size of volume
	G4double worldSizeX = 400*mm;
	G4double worldSizeY = 400*mm;
	G4double worldSizeZ = 600*mm;
    G4Box* solidWorld = new G4Box("solidWorld", worldSizeX/2, worldSizeY/2, worldSizeZ/2);

	//Creating logical volume
    // Make our volume (box) of some material
	//args: physical volume name, material to be built from, name of logical volume
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

    // Creating physical volume for interactions, 
	// args: rotation, translation vector, logical vol, name, mother vol,
    // boolean operation, copy number (in case of using volume multiple times) basically an index for each copy of the volume, check for overlaps
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, 
	"physWorld", 0, false, 0, true);
	
	//-------Defining Electric Field Volume------
	
	// Creating solid volume of field region
	G4double fieldRegionSizeX = 49.5;
	G4double fieldRegionSizeY = 49.5;
	G4double fieldRegionSizeZ = 100;
	G4Box *electricField = new G4Box("electricField", fieldRegionSizeX/2*mm, fieldRegionSizeY/2*mm, fieldRegionSizeZ/2*mm);
	
	// Creating logical volume of field region
	logicField = new G4LogicalVolume(electricField, worldMat, "logicField");
	
	// Creating physical volume of field region
	G4double fieldZ0 = -10*cm;
	G4VPhysicalVolume *physField = new G4PVPlacement(0, G4ThreeVector(0., 0., fieldZ0), logicField, 
	"physField", logicWorld, false, 0, true);
	
	//-------Defining Detector Volume------------
	G4double detectorThickness = 40*micrometer;
	G4double detectorThicknessTwo = 300*micrometer; //thickness for two thicker detectors
	G4double detectorSizeX = 49.5*mm;
	G4double detectorSizeY = 49.5/16*mm;

	G4Box *solidDetector = new G4Box("solidDetector", detectorSizeX/2, detectorSizeY/2, detectorThickness/2);
	G4Box *solidDetectorTwo = new G4Box("solidDetectorTwo", detectorSizeX/2, detectorSizeY/2, detectorThicknessTwo/2);
	
	// ~~Defining detector material
	G4Material* detectorMat = nist->FindOrBuildMaterial("G4_Si");
	
	//Creating logical volume of detector
	// the sensitive volume we will define must refer to this logical volume
	// this means we must access that outside of DetectorConstruction.cpp
	// (in DetectorConstruction.hh)
	logicDetector = new G4LogicalVolume(solidDetector, detectorMat, "logicDetector");
	logicDetectorTwo = new G4LogicalVolume(solidDetectorTwo, detectorMat, "logicDetectorTwo");
		
	//logicDetector->SetVisAttributes(new G4VisAttributes(G4Colour(0.0, 0.0, 1.0))); // Blue for thin
	logicDetectorTwo->SetVisAttributes(new G4VisAttributes(G4Colour(1.0, 0.0, 0.0))); // Red for thick
	
	//Now creating physical instances of detector
	// Distance to first stack of detectors
	G4double d0 = 15*cm;
	// Distance between the stacks
	G4double d = 1*cm; 

	// Number of detectors per stack
	G4int numDetectors = 16;

	// Spacing between detectors in the y-axis
	G4double spacingY = detectorSizeY;
	
	// Loop to create four identical stacks
	for(G4int stackIndex = 0; stackIndex < 6; stackIndex++)
	{
		// Calculate the z-position for each stack
		G4double posZ = -1.5 * d + stackIndex * d + d0; // Positioning the stacks along the x-axis

		for(G4int i = 0; i < numDetectors; i++)
		{
			// Calculate the y-position for each detector within the stack
			G4double posY = -0.5 * numDetectors * spacingY + (i + 0.5) * spacingY;
			G4ThreeVector position(0, posY, posZ); // Stacks along x-axis, detectors along y-axis
			
			// Choosing appropriate detector
			G4LogicalVolume* selectedLogicDetector = (stackIndex<4) ? logicDetector : logicDetectorTwo;

			// Place the detector at the calculated position
			G4VPhysicalVolume *physDetector = new G4PVPlacement(0, 
                                                           position, 
                                                           selectedLogicDetector, 
                                                           "physDetector", 
                                                           logicWorld, 
                                                           false, 
                                                           i + stackIndex * numDetectors, 
                                                           true);
		}
	}
	
    return physWorld;
}

void VolumeConstruction::ConstructSDandField()
{
	//std::cout << "		***********ConstructSDandField called"  << std::endl;
	//G4cout << "		***********ConstructSDandField called" << G4endl;
	//G4Exception("Debugging Message", "Debugging", JustWarning, "		***********ConstructSDandField called");
	
	// Create and assign sensitive detector to logicDetector
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
	logicDetector->SetSensitiveDetector(sensDet);	
	
	// Setting up electric field
	G4ThreeVector fieldVector(0.0, 10.0/49.5 * megavolt/m, 0.0);
	ElectricField *eField = new ElectricField(fieldVector);
	
	// Create a field manager and set the electric field
	
	// Create a field manager
    G4FieldManager* fieldManager = new G4FieldManager();

	// Set the field in the field logical volume
	//true value applies field effects to particles
	logicField->SetFieldManager(eField->GetGlobalFieldManager(), true);

}
