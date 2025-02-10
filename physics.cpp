#include "physics.hh"
//research build

//Define what physics list we want to use inside here
//Use only physics that has impact on measurement.
//Here we will use E&M physics and optical
MyPhysicsList::MyPhysicsList()
{
	RegisterPhysics (new G4EmStandardPhysics());
}

MyPhysicsList::~MyPhysicsList()
{}