#include "PrimaryGeneratorAction.hh"

#include "globals.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "Randomize.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(0)								
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle("opticalphoton");

  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.0, 0.0, 0.0));
  fParticleGun->SetParticleEnergy(9.68*eV); 
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{       
	// Random Momentum Direction

	G4double theta = CLHEP::RandFlat::shoot(0.0, CLHEP::pi)*rad;
  	G4double phi = CLHEP::RandFlat::shoot(0.0, CLHEP::twopi)*rad;
  	G4double ux, uy, uz;
  	ux = cos(phi)*sin(theta);
  	uy = sin(phi)*sin(theta);
  	uz = cos(theta);

  	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux, uy, uz));

        fParticleGun->GeneratePrimaryVertex(anEvent);
}

