#include "PhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4OpticalPhysics.hh"

PhysicsList::PhysicsList() 
: G4VModularPhysicsList(){    				

  // Default physics
  RegisterPhysics(new G4DecayPhysics());

  // EM physics
  RegisterPhysics(new G4EmStandardPhysics());

  // Radioactive decay
  RegisterPhysics(new G4RadioactiveDecayPhysics());

  // Optical properties
  RegisterPhysics(new G4OpticalPhysics());
}


PhysicsList::~PhysicsList()
{ 
}

void PhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
} 

