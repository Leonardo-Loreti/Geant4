#include "SteppingAction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include <fstream>
#include <iostream>

SteppingAction::SteppingAction()
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{

  // Whatever information you may need that is inside the G4step, for example:

  auto volume = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName();
  auto edep = step->GetTotalEnergyDeposit();

  if(edep != 0){
    
    std::cout << "There was a deposit of energy on the volume: " << volume << std::endl;

  }
}


