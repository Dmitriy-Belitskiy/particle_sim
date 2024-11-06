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
/// \file B1/src/DetectorConstruction.cc
/// \brief Implementation of the B1::DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4AssemblyVolume.hh"
#include "G4Tubs.hh"
#include "G4RotationMatrix.hh"
#include "G4SubtractionSolid.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4GenericMessenger.hh"

namespace B1
{


DetectorConstruction::DetectorConstruction()

{

  DefineCommands();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{

  delete fMessenger;
}






G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();




  // Envelope parameters
  G4double env_sizeXY = 5*m, env_sizeZ = 5*m;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");
  //G4Material* env2_mat = nist->FindOrBuildMaterial("G4_WATER");
  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = true;

  //
  // World
  //
  G4double world_sizeXY = 1.0*env_sizeXY;
  G4double world_sizeZ  = 1.0*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");

  auto solidWorld = new G4Box("World", 1.2 * world_sizeXY, 1 * world_sizeXY, 1.2 * world_sizeZ);
  auto logicWorld = new G4LogicalVolume(solidWorld, world_mat, "World");

  auto physWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "World", nullptr, false, 0, checkOverlaps);

  //
  // Envelope 
  
  //auto solidEnv = new G4Box("Envelope", 1.0 * env_sizeXY, 0.3 * env_sizeXY, 1.0 * env_sizeZ);
  //auto logicEnv = new G4LogicalVolume(solidEnv, env_mat, "Envelope");

  //new G4PVPlacement(nullptr, G4ThreeVector(), logicEnv, "Envelope", logicWorld, false, 0, checkOverlaps);

  // Envelope 2 as Soil
  /* // Create soil material
  G4double soilDensity = 1.6 * g / cm3; // density of soil
  G4Material* soil = new G4Material("Soil", soilDensity, 3); // 3 components

  // Define elements for soil
  G4double a;  // atomic mass
  G4double z;  // atomic number
  */
   

    // Створення матеріалу грунту
    G4double soilDensity = 1.6 * g / cm3; // щільність грунту
    G4Material* soil = new G4Material("Soil", soilDensity, 8); // 8 компонентів

    G4Element* Si = nist->FindOrBuildElement("Si");
    G4Element* O = nist->FindOrBuildElement("O");
    G4Element* Al = nist->FindOrBuildElement("Al");
    G4Element* Fe = nist->FindOrBuildElement("Fe");
    G4Element* Ca = nist->FindOrBuildElement("Ca");
    G4Element* Mg = nist->FindOrBuildElement("Mg");
    G4Element* Na = nist->FindOrBuildElement("Na");
    G4Element* K = nist->FindOrBuildElement("K");
    // Додавання елементів до матеріалу грунту
    soil->AddElement(Si, 0.4);  // 40% кремнію
    soil->AddElement(O, 0.4);   // 40% кисню
    soil->AddElement(Al, 0.05); // 5% алюмінію
    soil->AddElement(Fe, 0.1);  // 10% заліза
    soil->AddElement(Ca, 0.025); // 2.5% кальцію
    soil->AddElement(Mg, 0.015); // 1.5% магнію
    soil->AddElement(Na, 0.005); // 0.5% натрію
    soil->AddElement(K, 0.005);  // 0.5% калію
  /*
  // Silicon (Si)
  z = 14; a = 28.0855 * g / mole;
  G4Element* elSi = new G4Element("Silicon", "Si", z, a);

  // Oxygen (O)
  z = 8; a = 16.00 * g / mole;
  G4Element* elO = new G4Element("Oxygen", "O", z, a);

  // Iron (Fe)
  z = 26; a = 55.845 * g / mole;
  G4Element* elFe = new G4Element("Iron", "Fe", z, a);

  // Add elements to soil material
  soil->AddElement(elSi, 0.4);  // 40% silicon
  soil->AddElement(elO, 0.4);   // 40% oxygen
  soil->AddElement(elFe, 0.2);   // 20% iron
  */


    G4Material* steel = new G4Material("Steel", 7.8 * g/cm3, 5); // density ~ 7.8 g/cm3




    G4Element* elFe = nist->FindOrBuildElement("Fe");
    G4Element* elC  = nist->FindOrBuildElement("C");
    G4Element* elMn = nist->FindOrBuildElement("Mn");
    G4Element* elCr = nist->FindOrBuildElement("Cr");
    G4Element* elNi = nist->FindOrBuildElement("Ni");
      // Define the composition (weight fractions)
    steel->AddElement(elFe, 0.70); // Iron ~ 70%
    steel->AddElement(elC,  0.002); // Carbon ~ 0.2%
    steel->AddElement(elMn, 0.01);  // Manganese ~ 1%
    steel->AddElement(elCr, 0.19);  // Chromium ~ 19%
    steel->AddElement(elNi, 0.10);  // Nickel ~ 10%


    G4RotationMatrix* rotation = new G4RotationMatrix();
    rotation->rotateX(90 * deg);

    G4ThreeVector position=G4ThreeVector(0, -2.70*m, 0);

    G4double outerRadius = 20 * cm;
    G4double wallThickness = 1 * cm;
    G4double innerRadius = outerRadius - wallThickness;
    G4double height = 60 * cm;





    G4Tubs* steelCylinderSolid = new G4Tubs("SteelCylinder", 0, outerRadius, height / 2, 0, 360 * deg);
    G4LogicalVolume* steelCylinderLog = new G4LogicalVolume(steelCylinderSolid, steel, "SteelCylinderLog");

    new G4PVPlacement(rotation, position, steelCylinderLog, "SteelCylinderPhys", logicWorld, false, 0, true);


    G4Tubs* airCylinderSolid = new G4Tubs("AirCylinder", 0, innerRadius, height / 2-wallThickness*2, 0, 360 * deg);
    G4LogicalVolume* airCylinderLog = new G4LogicalVolume(airCylinderSolid,world_mat, "AirCylinderLog");

    // Place the inner air cylinder inside the steel cylinder to create a hollow space
    new G4PVPlacement(0, G4ThreeVector(0, 0, 0), airCylinderLog, "AirCylinderPhys", steelCylinderLog, false, 0, true);




  // Create Envelope 2 using soil
  auto solidEnv2 = new G4Box("Envelope1", 1.2 * env_sizeXY, 0.2 * env_sizeXY, 1.2 * env_sizeZ);

  auto logicEnv2 = new G4LogicalVolume(solidEnv2, soil , "Envelope1");

  new G4PVPlacement(nullptr, G4ThreeVector(0, -4*m, 0), logicEnv2, "Envelope1", logicWorld, false, 0, checkOverlaps);

  // Shape 1
  G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
  //G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_BGO");
  G4ThreeVector pos1 = G4ThreeVector(0, -2*m, 0);

  // Shape 1
  int scale =100;
  G4double shape1_a = scale*3.78*mm;
  G4double shape1_b = scale*3.78*mm;
  G4double shape1_hz = 18.9*mm;





  auto solidShape1 = new G4Box("Shape1", shape1_a, shape1_hz, shape1_b);

  auto logicShape1 = new G4LogicalVolume(solidShape1, shape1_mat, "Shape1");

  fDetector = new G4PVPlacement(nullptr,G4ThreeVector(fP_X,fP_Y,fP_Z), logicShape1, "Shape1", logicWorld, false, 0, checkOverlaps);

  // Set Shape2 as scoring volume
  fScoringVolume = logicShape1;

  // always return the physical World
  return physWorld;
}


// In DetectorConstruction.cc
void DetectorConstruction::SetPos_X(G4double val_X)
{
    if (!fDetector) {
        G4cerr << "Detector has not yet been constructed." << G4endl;
        return;
    }

    fP_X = val_X;
    fDetector->SetTranslation(G4ThreeVector(fP_X, fP_Y, fP_Z));

    // Inform G4RunManager that we changed the geometry
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

void DetectorConstruction::SetPos_Y(G4double val_Y)
{
    if (!fDetector) {
        G4cerr << "Detector has not yet been constructed." << G4endl;
        return;
    }

    fP_Y = val_Y;
    fDetector->SetTranslation(G4ThreeVector(fP_X, fP_Y, fP_Z));

    // Inform G4RunManager that we changed the geometry
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

void DetectorConstruction::SetPos_Z(G4double val_Z)
{
    if (!fDetector) {
        G4cerr << "Detector has not yet been constructed." << G4endl;
        return;
    }
    fP_Z = val_Z;
    fDetector->SetTranslation(G4ThreeVector(fP_X, fP_Y, fP_Z));

    // Inform G4RunManager that we changed the geometry
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::DefineCommands()
{
    // Define /B5/detector command directory using generic messenger class
    fMessenger = new G4GenericMessenger(this,
                                        "/B5/detector/",
                                        "Detector control");

    // setPosition command with G4ThreeVector
    auto& setPositionX
        = fMessenger->DeclareMethodWithUnit("setPositionX", "m",
                                            &DetectorConstruction::SetPos_X,
                                            "Set position of the detector.");
    setPositionX.SetParameterName("fP_X", true);


     auto& setPositionY
        = fMessenger->DeclareMethodWithUnit("setPositionY", "m",
                                            &DetectorConstruction::SetPos_Y,
                                            "Set position of the detector.");
    setPositionY.SetParameterName("fP_Y", true);

    auto& setPositionZ
        = fMessenger->DeclareMethodWithUnit("setPositionZ", "m",
                                            &DetectorConstruction::SetPos_Z,
                                            "Set position of the detector.");
    setPositionY.SetParameterName("fP_Z", true);

}








} // namespace B1
