#include "ActionInitialization.hh"
#include "SteppingAction.hh"
#include "PrimaryGeneratorAction.hh"

ActionInitialization::ActionInitialization()
 : G4VUserActionInitialization()
{}


ActionInitialization::~ActionInitialization()
{}


void ActionInitialization::Build() const
{
  SetUserAction(new PrimaryGeneratorAction);
  SetUserAction(new SteppingAction);
}
