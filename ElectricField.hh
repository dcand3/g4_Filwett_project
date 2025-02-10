#ifndef ELECTRICFIELD_HH
#define ELECTRICFIELD_HH

#include "G4SystemOfUnits.hh"
#include "G4UniformElectricField.hh"
#include "G4FieldManager.hh"
#include "G4EqMagElectricField.hh"
#include "G4ChordFinder.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4ClassicalRK4.hh"

class ElectricField
{
  public:
    // Constructor that initializes the electric field with a specified vector value.
    ElectricField(G4ThreeVector fieldVector);
    virtual ~ElectricField();
	
	// Method to get the global field manager
    G4FieldManager* GetGlobalFieldManager(); // Add this method declaration

  private:
    // Initialize the electric field and relevant components
    void InitializeField(G4ThreeVector fieldVector);

    G4FieldManager* fFieldManager;
    G4ChordFinder* fChordFinder;
    G4EqMagElectricField* fEquation;
    G4UniformElectricField* fElectricField;
    G4MagIntegratorStepper* fStepper;
};

#endif