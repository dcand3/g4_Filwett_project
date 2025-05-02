#include "VolumeConstruction.hh"
#include "DetectorConstruction.hh"

#include "G4UniformElectricField.hh"
#include "G4UniformMagField.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SystemOfUnits.hh"
#include "G4FieldBuilder.hh"
#include "G4Material.hh"

//research build

// this version of VolumeConstruction will take position and momentum values from simIon, and model the particles through the detectors
// simIon will model the particles through the potential and create a csv file to be read by generator in geant4


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
	
	//-------Creating colored boxes to help with knowing the cartesian coordinates in world volume------------
	// define small colored boxes in world volume to indicate coordinate axes
	G4double axisLength = 50 * mm;
	G4double axisThickness = 2 * mm;
	
	// Create solid volumes for indicators
	G4Box* xIndicator = new G4Box("xIndicator", axisLength / 2, axisThickness / 2, axisThickness / 2);
	G4Box* yIndicator = new G4Box("yIndicator", axisThickness / 2, axisLength / 2, axisThickness / 2);
	G4Box* zIndicator = new G4Box("zIndicator", axisThickness / 2, axisThickness / 2, axisLength / 2);
	
	// Logical volumes
	G4LogicalVolume* logicXInd = new G4LogicalVolume(xIndicator, worldMat, "logicXInd");
	G4LogicalVolume* logicYInd = new G4LogicalVolume(yIndicator, worldMat, "logicYInd");
	G4LogicalVolume* logicZInd = new G4LogicalVolume(zIndicator, worldMat, "logicZInd");
	
	// Set colors for visualization
	logicXInd->SetVisAttributes(new G4VisAttributes(G4Colour(1.0, 0.0, 0.0))); //Red for x-axis
	logicYInd->SetVisAttributes(new G4VisAttributes(G4Colour(0.0, 1.0, 0.0))); //Green for y-axis
	logicZInd->SetVisAttributes(new G4VisAttributes(G4Colour(0.0, 0.0, 1.0))); //Blue for z-axis
	
	// Place indivators in the (+x, +y, +z) corner (physical volumes)
	G4ThreeVector cornerPos(-worldSizeX / 2 + axisLength / 2, -worldSizeY / 2 + axisLength/2, -worldSizeZ / 2 + axisLength / 2);
	
	new G4PVPlacement(0, cornerPos + G4ThreeVector(axisLength / 2, 0, 0), logicXInd, "physXind", logicWorld, false, 0, true);
	new G4PVPlacement(0, cornerPos + G4ThreeVector(0, axisLength / 2, 0), logicYInd, "physYind", logicWorld, false, 0, true);
	new G4PVPlacement(0, cornerPos + G4ThreeVector(0, 0, axisLength / 2), logicZInd, "physZind", logicWorld, false, 0, true);
	
	//-------Defining Electric Field Volume------
	
	// Creating solid volume of field region
	fieldRegionSizeX = 49.5 * mm;
	fieldRegionSizeY = 49.5 * mm;
	fieldRegionSizeZ = 100 * mm;
	G4Box *eFieldVolume = new G4Box("eFieldVolume", fieldRegionSizeX/2, fieldRegionSizeY/2, fieldRegionSizeZ/2);
	
	// Creating logical volume of field region
	logicalFieldVolume = new G4LogicalVolume(eFieldVolume, worldMat, "logicalFieldVolume");
	
	// Creating physical volume of field region
	fieldZ0 = -10*cm;
	G4VPhysicalVolume *physFieldVolume = new G4PVPlacement(0, G4ThreeVector(0., 0., fieldZ0), logicalFieldVolume, 
	"physFieldVolume", logicWorld, false, 0, true);
	
	//-------Defining Detector Volume------------
	G4double detectorThickness = 40*micrometer;
	G4double detectorThicknessThick = 300*micrometer; //thickness for two thicker detectors
	G4double detectorSizeX = 49.5*mm;
	G4double detectorSizeY = 49.5/16*mm;

	G4Box *solidDetector = new G4Box("solidDetector", detectorSizeX/2, detectorSizeY/2, detectorThickness/2);
	G4Box *solidDetectorThick = new G4Box("solidDetectorThick", detectorSizeX/2, detectorSizeY/2, detectorThicknessThick/2);
	
	// Defining detector material
	G4Material* detectorMat = nist->FindOrBuildMaterial("G4_Si");
	
	//Creating logical volume of detector
	// the sensitive volume we will define must refer to this logical volume
	// this means we must access that outside of VolumeConstruction.cpp
	// (in DetectorConstruction.hh)
	logicDetector = new G4LogicalVolume(solidDetector, detectorMat, "logicDetector");
	logicDetectorThick = new G4LogicalVolume(solidDetectorThick, detectorMat, "logicDetectorThick");
		
	logicDetector->SetVisAttributes(new G4VisAttributes(G4Colour(0.0, 0.0, 1.0))); // Blue for thin
	logicDetectorThick->SetVisAttributes(new G4VisAttributes(G4Colour(1.0, 0.0, 0.0))); // Red for thick
	
	//Now creating physical instances of detector
	// Distance to first detector
	G4double d0 = 15*cm;
	// Distance between the detectors
	G4double d = 1*cm; 

	// Number of strips per detector
	G4int numDetectors = 16;

	// Spacing between strips in the y-axis
	G4double spacingY = detectorSizeY;
	
	// Loop to create four thin detectors and two thick detectors
	for(G4int stackIndex = 0; stackIndex < 6; stackIndex++)
	{
		// Calculate the z-position for each stack
		G4double posZ = -1.5 * d + stackIndex * d + d0; // Positioning the detectors along the x-axis

		for(G4int i = 0; i < numDetectors; i++)
		{
			// Calculate the y-position for each detector strip within the stack
			G4double posY = -0.5 * numDetectors * spacingY + (i + 0.5) * spacingY;
			G4ThreeVector position(0, posY, posZ); // Stacks along x-axis, detectors along y-axis
			
			// Choosing appropriate detector (thin or thick)
			G4LogicalVolume* selectedLogicDetector = (stackIndex<4) ? logicDetector : logicDetectorThick;

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

//void VolumeConstruction::SetLocalFieldValue(G4ThreeVector value)
//{
//  fLocalFieldVector = value;
//
//  //G4UniformElectricField* eField = nullptr;
//  G4UniformMagField* magField = nullptr;
//  if (fLocalFieldVector != G4ThreeVector(0.,0.,0.)) {
//    //eField = new G4UniformElectricField(fLocalFieldVector);
//	magField = new G4UniformMagField(fLocalFieldVector);
//  }

//  // Set field to the field builder
//  auto fieldBuilder = G4FieldBuilder::Instance();
//  //fieldBuilder->SetLocalField(eField, logicalFieldVolume);
//  fieldBuilder->SetLocalField(magField, logicalFieldVolume);
//}

void VolumeConstruction::ConstructSDandField()
{
  // Create and assign sensitive detector to logicDetector
  MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");
  
  //Assign to both thin and thick detector logical volumes
  logicDetector->SetSensitiveDetector(sensDet);	
  logicDetectorThick->SetSensitiveDetector(sensDet);

  // Create detector fields
//  SetLocalFieldValue(fLocalFieldVector);

  // Construct all Geant4 field objects
//  auto fieldBuilder = G4FieldBuilder::Instance();
  //fieldBuilder->SetFieldType(kElectroMagnetic);
//  fieldBuilder->ConstructFieldSetup();
}