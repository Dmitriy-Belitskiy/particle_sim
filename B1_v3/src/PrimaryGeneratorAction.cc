//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1/src/PrimaryGeneratorAction.cc
/// \brief Implementation of the B1::PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4RandomDirection.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"
#include <cmath>
#include "G4GenericMessenger.hh"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace B1
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="gamma");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4RandomDirection());
  fParticleGun->SetParticleEnergy(0.662*MeV);
  DefineCommands();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of ecah event
  //

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get Envelope volume
  // from G4LogicalVolumeStore.


  G4double x0 = 0;
  G4double y0 = -2.7*m;
  G4double z0 = 0;

  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  // Генерація випадкового напрямку в додатньому Y
 //G4double theta = G4UniformRand()* M_PI/2; // Кут від 0 до 180 градусів
 //G4double phi = G4UniformRand() * (2 * M_PI);
  PrimaryGeneratorAction::set_direction(f_tetha,f_phi,f_view);

  fParticleGun->GeneratePrimaryVertex(anEvent);

}


void PrimaryGeneratorAction::Set_tetha(G4double val_tetha)
{
  f_tetha=val_tetha;

  PrimaryGeneratorAction::set_direction(f_tetha,f_phi,f_view);

}

void PrimaryGeneratorAction::Set_phi(G4double val_phi)
{
  f_phi=val_phi;

  PrimaryGeneratorAction::set_direction(f_tetha,f_phi,f_view);

}

void PrimaryGeneratorAction::Set_view_angle (G4double val_view)
{
  f_view=val_view;

  PrimaryGeneratorAction::set_direction(f_tetha,f_phi,f_view);

}

void PrimaryGeneratorAction::DefineCommands()
{
    // Define /B5/detector command directory using generic messenger class
    fMessenger = new G4GenericMessenger(this,
                                        "/B5/gun/",
                                        "Gun control");
    auto& set_dir_tetha
        = fMessenger->DeclareMethodWithUnit("set_dir_tetha", "rad",
                                            &PrimaryGeneratorAction::Set_tetha,
                                            "Set position of the detector.");
    set_dir_tetha.SetParameterName("f_tetha", true);

    auto& set_dir_phi
        = fMessenger->DeclareMethodWithUnit("set_dir_phi", "rad",
                                            &PrimaryGeneratorAction::Set_phi,
                                            "Set position of the detector.");
    set_dir_phi.SetParameterName("f_phi", true);

     auto& set_dir_view
        = fMessenger->DeclareMethodWithUnit("set_dir_view", "rad",
                                            &PrimaryGeneratorAction::Set_view_angle ,
                                            "Set position of the detector.");
    set_dir_view.SetParameterName("f_view", true);




}



void  PrimaryGeneratorAction::set_direction(G4double val_tetha,G4double val_phi,G4double val_view)
{
  G4double theta =sqrt(G4UniformRand()) * f_view; // тілесний кут конуса/2
  G4double phi =  G4UniformRand()* CLHEP::pi*2; // це не трогати це щоб малювати конус від 0 до 360

   // Define the angles in radians
  // G4double theta_world = CLHEP::pi / 2.0*0;
  // G4double phi_world = CLHEP::pi / 2.0*0;
  G4double theta_world = f_tetha;  //цим крутити конус
  G4double phi_world = f_phi;    //цим теж

  // Create rotation matrices for z-axis and y-axis rotations
  G4RotationMatrix R_z;
  R_z.rotateZ(phi_world);

  G4RotationMatrix R_y;
  R_y.rotateY(theta_world);

  // Combine the rotations: equivalent to R = R_z * R_y in your Python code
  G4RotationMatrix R = R_z * R_y;

  // Обчислення компонентів напрямку
  G4double zDirection = sin(theta) * cos(phi);
  G4double yDirection = cos(theta);
  G4double xDirection = sin(theta) * sin(phi);

  G4ThreeVector vector(zDirection , xDirection,yDirection);

  G4ThreeVector vector_rot = R * vector;

  fParticleGun->SetParticleMomentumDirection(vector_rot);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}


