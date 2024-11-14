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
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
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



  G4double theta =sqrt(G4UniformRand())* CLHEP::pi/32; // иілесний кут конуса/2
  G4double phi =  G4UniformRand()* CLHEP::pi*2; // це не трогати це щоб малювати конус від 0 до 360

   // Define the angles in radians
  // G4double theta_world = CLHEP::pi / 2.0*0;
  // G4double phi_world = CLHEP::pi / 2.0*0;
  G4double theta_world = CLHEP::pi / 4;  //цим крутити конус
  G4double phi_world = CLHEP::pi / 4;    //цим теж

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

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

}


