#include "generator.hh"
#include "G4RandomTools.hh"
//research build

MyPrimaryGenerator::MyPrimaryGenerator()
{
	//How many particles per run? We choose to have 1 particle per run
	//and can run the program many times to have many particles
	fParticleGun = new G4ParticleGun(1);

}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	//Define what kind of particles we want to create
	//all info about particles stored in table (like Nist material manager)
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	//Create particle variable called "proton"
	G4String particleName="proton";
	G4ParticleDefinition *particle = particleTable->FindParticle("proton");
	
	//defining random position where particle is created
	// Generate random position within the range (-25 mm < x, y < 25 mm) (range of detector)
    G4double x = (G4UniformRand() * 50. - 25.) * mm;
    G4double y = (G4UniformRand() * 50. - 25.) * mm;
    G4double z = -190. * mm;  // Assuming we want z to be 0
	
	G4ThreeVector pos(x,y,z);
	
	//defining particles random (positive) momentum direction
    //G4double theta = G4UniformRand() * CLHEP::pi;  // Random angle in [0, pi]
    //G4double phi = G4UniformRand() * CLHEP::pi;  // Random angle in [0, pi]
    
    //G4ThreeVector momDir(std::sin(theta) * std::cos(phi), 
    //                     std::sin(theta) * std::sin(phi), 
    //                     std::cos(theta));
	
	// defining particles momentum direction
	G4ThreeVector momDir(0.,0.,1.);
	
	// defining random momentum magnitude with energy between 1 MeV and 100 MeV
	G4double momentum = (1. + 90. * G4UniformRand()) * MeV;
	G4cout << "		***********The momentum is " << momentum/MeV << "MeV/c" << G4endl;
	
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(momDir);
	fParticleGun->SetParticleMomentum(momentum);
	fParticleGun->SetParticleDefinition(particle);
	
	fParticleGun->GeneratePrimaryVertex(anEvent);
	
}

 