#include "generator.hh"      
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4Event.hh"         
#include "G4SystemOfUnits.hh" 
#include <fstream>            
#include <sstream>           
#include <iostream> 
#include <cmath>

// ----------------------------------------------------------------------------
// File: generator.cpp
// What this file does:
// This file defines the PrimaryGenerator class, which is responsible for
// generating primary particles in the simulation. It sets up the particle gun
// and loads particle data from a file to create particles with specific properties.
//
// What happens here:
// - The constructor initializes the particle gun and loads particle data from
// the file "particle_data.txt".
// - The LoadParticleData() function reads data from the file and stores information
// about each particle (e.g., mass, charge, position, momentum, and energy).
// - The GeneratePrimaries() function is responsible for generating all the particles
// in a single event, using the loaded particle data. It configures the particle gun
// with each particle's properties (charge, position, momentum, and energy) and
// generates the particle for the event.
//
// Key Components:
// - PrimaryGenerator constructor: initializes the particle gun and loads data from
// the file.
// - LoadParticleData(): reads the particle information from the "particle_data.txt"
// file, parses it, and stores it in the particles vector.
// - GeneratePrimaries(): creates the primary particles for a Geant4 event based on
// the data loaded and configures the particle gun to generate them.
//
// What is the particle data format:
// The file "particle_data.txt" contains particle properties, one particle per line,
// with the following format:
// mass_u charge x y z vx vy vz kineticEnergy
// Where:
// - mass_u: mass of the particle in atomic mass units (amu)
// - charge: charge of the particle (in e)
// - x, y, z: position of the particle (in mm)
// - vx, vy, vz: velocity components of the particle (in km/s)
// - kineticEnergy: particle's kinetic energy (in eV)
// The file is read line by line, and the data is parsed and converted into Geant4
// units (mm, MeV, etc.).
//
// When it's used:
// This file is used during the simulation setup to generate the initial set of
// particles in each event based on the provided data file.
// ----------------------------------------------------------------------------

// Constructor: Initializes the particle gun and loads particle data from file
PrimaryGenerator::PrimaryGenerator()
    : fParticleGun(new G4ParticleGun(1)) {
    LoadParticleData();
}

// Destructor: Cleans up dynamically allocated memory
PrimaryGenerator::~PrimaryGenerator() {
    delete fParticleGun;
}

// Helper function to get Z from A for known ion types
bool GetZfromA(int A, int& Z) {
    switch (A) {
        case 1: Z = 1; return true;     // Proton
        case 3: Z = 2; return true;     // He3
        case 4: Z = 2; return true;     // He4
        case 56: Z = 26; return true;   // Fe56
        default: return false;          // Unknown
    }
}

// Load particle data from file
void PrimaryGenerator::LoadParticleData() {
    std::ifstream file("particle_data.txt");
    if (!file) {
        G4cerr << "-----------------------Error: Unable to open particle_data.txt" << G4endl;
        return;
    }
    G4cout << "-----------------------Opened particle_data.txt successfully" << G4endl;

    std::string line;
    while (std::getline(file, line)) {
        G4cout << "-----------------------Reading line: " << line << G4endl;
        std::stringstream iss(line);
		
        double mass_u, charge, x, y, z, vx, vy, vz, kineticEnergy;
        if (iss >> mass_u >> charge >> x >> y >> z >> vx >> vy >> vz >> kineticEnergy) {
            ParticleData particle;
            particle.mass_u = mass_u;
            particle.charge = charge;
            particle.position = G4ThreeVector(x * mm, (y - 25) * mm, (z - 151) * mm); 
			//change in y and z are to account for origin difference between simion and g4
			
            // Convert mass from amu to MeV/c^2 (1 amu ≈ 931.494 MeV) (c = 1 in G4)
            double mass_MeV = mass_u * 931.368 * MeV;
			
            // Construct velocity vector and normalize it
            G4ThreeVector velocity(vx, vy, vz);
            G4ThreeVector direction = velocity.unit();
			
            // Compute magnitude of momentum: p = sqrt((E/c)^2 - (mc^2)^2)
			particle.kineticEnergy_MeV = kineticEnergy / 1e6 * MeV; // convert KE from eV to MeV 
			double totalEnergy = (mass_MeV + particle.kineticEnergy_MeV);
            double momentum_mag = std::sqrt(totalEnergy * totalEnergy - mass_MeV * mass_MeV);
            particle.momentum = momentum_mag * direction;

            particles.push_back(particle);
			
        } else {
            G4cerr << "-----------------------Failed to parse line: " << line << G4endl;
        }
    }
    G4cout << "-----------------------Loaded " << particles.size() << " particles from file" << G4endl;
}

// Generate all particles in a single event
void PrimaryGenerator::GeneratePrimaries(G4Event* anEvent) {
    if (particles.empty()) {
        G4cerr << "-----------------------No particles loaded!" << G4endl;
        return;
    }

    for (const auto& p : particles) {
        G4int A = std::round(p.mass_u);
        G4int Z;

        if (!GetZfromA(A, Z)) {
            G4cerr << "-----------------------Unknown mass: " << p.mass_u << G4endl;
            continue;
        }

        G4ParticleDefinition* ion = G4IonTable::GetIonTable()->GetIon(Z, A, 0.0);
        if (!ion) {
            G4cerr << "-----------------------Failed to create ion Z=" << Z << " A=" << A << G4endl;
            continue;
        }

        fParticleGun->SetParticleDefinition(ion);
        fParticleGun->SetParticleCharge(p.charge * eplus);
        fParticleGun->SetParticlePosition(p.position);
        fParticleGun->SetParticleMomentumDirection(p.momentum.unit());
        fParticleGun->SetParticleEnergy(p.kineticEnergy_MeV);

        fParticleGun->GeneratePrimaryVertex(anEvent);
    }
}
