#include "B1PrimaryGeneratorAction.hh"

#include "G4ios.hh"
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"

B1PrimaryGeneratorAction::B1PrimaryGeneratorAction()
{
  particleSource = new G4GeneralParticleSource();
}  

B1PrimaryGeneratorAction::~B1PrimaryGeneratorAction()
{
  delete particleSource;
}


void B1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  particleSource->GeneratePrimaryVertex(anEvent);
} 
