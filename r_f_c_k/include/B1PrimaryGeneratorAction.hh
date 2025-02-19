#ifndef B1PrimaryGeneratorAction_h
#define B1PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4GeneralParticleSource;
class G4Event;

class B1PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  B1PrimaryGeneratorAction();    
  ~B1PrimaryGeneratorAction();
  
public:
  void GeneratePrimaries(G4Event*);

private:
  G4GeneralParticleSource* particleSource;
};

#endif


