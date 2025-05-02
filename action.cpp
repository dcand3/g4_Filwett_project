#include "action.hh"
#include "generator.hh"
#include "event.hh"

#include <iostream>

MyActionInitialization::MyActionInitialization() {}

MyActionInitialization::~MyActionInitialization() {}

void MyActionInitialization::Build() const
{
    PrimaryGenerator* generator = new PrimaryGenerator();
    SetUserAction(generator);

    MyRunAction* runAction = new MyRunAction();
    SetUserAction(runAction);
	
	MyEventAction* eventAction = new MyEventAction(runAction);
	SetUserAction(eventAction);
}
