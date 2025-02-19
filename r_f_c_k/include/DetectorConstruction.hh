#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4GenericMessenger;

namespace B1
{

/// Detector construction class to define materials and geometry.
class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    ~DetectorConstruction() override;

    // Override Construct method to define geometry
    G4VPhysicalVolume* Construct() override;

    // Get the scoring volume
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

    // Method to set the detector position (now takes a G4ThreeVector)
    void SetPos_X (const G4double fP_X);
    void SetPos_Y (const G4double fP_Y);
    void SetPos_Z (const G4double fP_Z);

    void SetRot_X(const G4double fA_X);
    void SetRot_Y(const G4double fA_Y);
    void SetRot_Z(const G4double fA_Z);



protected:
    // Define commands for modifying the detector position
    void DefineCommands();

    // Member variables for detector position
    G4double fP_X = 0.0;
    G4double fP_Y = 0.0;
    G4double fP_Z = 0.0;


    G4double fA_X = 0.0;
    G4double fA_Y = 0.0;
    G4double fA_Z = 0.0;
    // Scoring volume
    G4LogicalVolume* fScoringVolume = nullptr;

    // Messenger for UI commands
    G4GenericMessenger* fMessenger = nullptr;

    // Pointer to the detector physical volume
    G4VPhysicalVolume* fDetector = nullptr;
};

}

#endif
