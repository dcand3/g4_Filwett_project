#ifndef ACTION_HH
#define ACTION_HH
//research build

#include "G4VUserActionInitialization.hh"
#include "generator.hh"
#include "run.hh"

class MyActionInitialization : public G4VUserActionInitialization
{
	public:
		MyActionInitialization();
		~MyActionInitialization();
		// Build() runs particle gun, computes stepping and so on
		virtual void Build() const;
};

#endif