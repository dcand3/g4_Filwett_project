#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"  
#include "G4ParticleGun.hh"                 
#include "G4ParticleDefinition.hh"          
#include "globals.hh"                     
#include <vector>
#include <string>

// Structure to hold particle data from file
struct ParticleData {
    G4ThreeVector position;  // Particle position (x, y, z)
    G4ThreeVector momentum;  // Particle momentum (px, py, pz)
	G4double mass_u;	     // Atomic mass (in atmoic mass units)
	G4int charge; 			 // Charge of particle in e
	G4double kineticEnergy_MeV; //kinetic energy of particle
};

// Define the PrimaryGenerator class, which generates particles based on file input
class PrimaryGenerator : public G4VUserPrimaryGeneratorAction 
{
public:
    // Constructor (no filename needed)
    PrimaryGenerator();

    // Destructor
    ~PrimaryGenerator();

    // Geant4 method that generates primary particles for an event
    void GeneratePrimaries(G4Event* anEvent) override;

private:
    // Method to read particle data from the default file
    void LoadParticleData();

    G4ParticleGun* fParticleGun;            // Particle gun to create particles
    std::vector<ParticleData> particles;    // Vector to store loaded particles
    size_t currentIndex;                    // Keeps track of the current particle being used
};

#endif
