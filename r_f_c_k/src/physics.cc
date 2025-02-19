#include "physics.hh"
#include "G4EmDNAPhysics.hh"
#include "G4EmLivermorePhysics.hh"

MyPhysicsList::MyPhysicsList()
{
    //auto emPhysics = new G4EmLivermorePhysics();
   // RegisterPhysics(emPhysics);


    //auto emPhysics = new G4EmDNAPhysics();
    //RegisterPhysics(emPhysics);
    RegisterPhysics (new G4EmStandardPhysics());
    //RegisterPhysics (new G4OpticalPhysics());
    //RegisterPhysics(new G4DecayPhysics());
    //RegisterPhysics(new G4RadioactiveDecayPhysics());
}

MyPhysicsList::~MyPhysicsList()
{}
