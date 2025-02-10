#include "ElectricField.hh"

// various field types and managers
#include "G4UniformElectricField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4EqMagElectricField.hh"
#include "G4ChordFinder.hh"
#include "G4ClassicalRK4.hh"
#include "G4MagIntegratorDriver.hh"

#include "G4SystemOfUnits.hh"

// Constructor: Initializes the electric field with a specific vector
ElectricField::ElectricField(G4ThreeVector fieldVector)
{
  // Create a uniform electric field in the specified direction
  fElectricField = new G4UniformElectricField(fieldVector);
  fEquation = new G4EqMagElectricField(fElectricField);

  // Get the global field manager
  fFieldManager = GetGlobalFieldManager();

  // Create a stepper and chord finder
  fStepper = new G4ClassicalRK4(fEquation, 8); // Using ClassicalRK4 as the default stepper
  auto* integrDriver = new G4MagInt_Driver(0.01 * mm, fStepper, fStepper->GetNumberOfVariables());
  fChordFinder = new G4ChordFinder(integrDriver);

  // Set up the field manager with the chord finder and electric field
  fFieldManager->SetChordFinder(fChordFinder);
  fFieldManager->SetDetectorField(fElectricField);
}

// Destructor: Clean up the integrator components
ElectricField::~ElectricField()
{
  delete fChordFinder;
  delete fStepper;
  delete fEquation;
  delete fElectricField;
}

// Get the global field manager that handles the transportation of particles in the simulation
G4FieldManager* ElectricField::GetGlobalFieldManager()
{
  return G4TransportationManager::GetTransportationManager()->GetFieldManager();
}

