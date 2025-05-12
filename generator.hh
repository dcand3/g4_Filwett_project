#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"  
#include "G4ParticleGun.hh"                 
#include "G4ParticleDefinition.hh"          
#include "globals.hh"                     
#include <vector>
#include <string>

// ----------------------------------------------------------------------------
// File: generator.hh
// What this file does:
//   This file defines the PrimaryGenerator class, which is responsible for 
//   generating primary particles in the simulation based on particle data loaded 
//   from a file. It declares the necessary methods and structures for the particle 
//   generation process.
//
// Key Components:
//   - ParticleData: A structure that holds the properties of a particle, including 
//     its position, momentum, mass, charge, and kinetic energy. This structure is 
//     used to store the parsed data for each particle from the input file.
//   - PrimaryGenerator: A class that inherits from G4VUserPrimaryGeneratorAction 
//     and is used to generate primary particles in a Geant4 event. It contains 
//     methods for loading particle data from a file and generating the primary particles 
//     based on that data.
//
// Declared Methods:
//   - `PrimaryGenerator()`: Constructor to initialize the particle gun and prepare 
//     for loading particle data from the file.
//   - `~PrimaryGenerator()`: Destructor that handles any necessary cleanup, including 
//     cleaning up the particle gun.
//   - `GeneratePrimaries(G4Event* anEvent)`: Geant4 method that is overridden to generate 
//     all primary particles for a given event, using the data loaded from the file.
//   - `LoadParticleData()`: A helper method that reads the particle data from a default file 
//     ("particle_data.txt") and stores it in the `particles` vector.
//
// Declared Member Variables:
//   - `G4ParticleGun* fParticleGun`: A Geant4 particle gun used to create and configure 
//     particles for the simulation events.
//   - `std::vector<ParticleData> particles`: A vector that holds the loaded particle data.
//   - `size_t currentIndex`: An index used to keep track of which particle is being used 
//     for generation in the event.
//
// Dependencies:
//   - `G4VUserPrimaryGeneratorAction`: Geant4 base class that this class inherits from 
//     to create and manage primary particle generation for events.
//   - `G4ParticleGun`: Geant4 class used to specify and create particles for events.
//   - `G4ParticleDefinition`: Geant4 class that holds the physical properties of a particle.
//   - `G4ThreeVector`: Geant4 class for 3D vectors (used to store position and momentum).
//   - `globals.hh`: Includes common Geant4 types and definitions.
//
// Purpose:
//   - This file is used for setting up particle generation in the simulation, 
//     reading particle properties from a file and using that data to generate 
//     particles for the event.
//
// When it's used:
//   - This file is part of the simulation's event generation, used when setting up 
//     the primary particles that are injected into the Geant4 simulation environment.
// ----------------------------------------------------------------------------

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
