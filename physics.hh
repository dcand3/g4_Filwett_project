#ifndef PHYSICS_HH
#define PHYSICS_HH
//research build

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"

class MyPhysicsList : public G4VModularPhysicsList
{
	public:
		MyPhysicsList();
		~MyPhysicsList();
};

#endif