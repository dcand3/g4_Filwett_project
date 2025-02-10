#include "action.hh"
#include "generator.hh"
//research build

MyActionInitialization::MyActionInitialization()
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::Build() const
{
	MyPrimaryGenerator *generator = new MyPrimaryGenerator();
	SetUserAction(generator);
	
	MyRunAction *runAction = new MyRunAction();
	SetUserAction(runAction);
}