
#ifndef tndge_DetectorConstruction_H
#define tndge_DetectorConstruction_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material; 

#include "G4VUserDetectorConstruction.hh"
//#include "PhysicsList.hh"
//#include "tndge_PrimaryGeneratorAction.hh"
#include "tndge_TrackerHit.hh"
#include "tndge_TrackerSD.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"

#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4Torus.hh"
#include "G4Polyhedra.hh"
#include "G4Polycone.hh"
#include "G4Orb.hh"
#include "G4Trd.hh"
#include "G4Trap.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4ThreeVector.hh"

#include "G4UImanager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "globals.hh"


class tndge_DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    tndge_DetectorConstruction(G4VPhysicalVolume* p_mother, G4double p_rho, G4double p_theta, G4double p_phi, G4double p_spin);
    ~tndge_DetectorConstruction();

    G4VPhysicalVolume* Construct();

  private:
    // Logical volumes
    //
    G4LogicalVolume* logicSmallAGe1;
    G4LogicalVolume* logicSmallHole1; 
    
    // Position of the detectors
    //
    G4double rho;
    G4double phi;
    G4double theta;
    G4double spin;
    G4RotationMatrix zRot90deg;
    G4RotationMatrix zRotMinus90deg;
    G4RotationMatrix zRot180deg2;
    G4RotationMatrix zRot270deg;
    

    // Physical volumes
    //
    G4VPhysicalVolume* mother;
    G4VPhysicalVolume* CloverCan;
    G4VPhysicalVolume* CrA;
    G4VPhysicalVolume* CrB;
    G4VPhysicalVolume* CrC;
    G4VPhysicalVolume* CrD;
};

#endif

