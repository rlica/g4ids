
#ifndef LaBr3Detector_H
#define LaBr3Detector_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material; 

#include "G4VUserDetectorConstruction.hh"
//#include "PhysicsList.hh"
//#include "tndge_PrimaryGeneratorAction.hh"
//#include "tndge_TrackerHit.hh"
//#include "tndge_TrackerSD.hh"
#include "LaBr3SensitiveDetector.hh"

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


class LaBr3Detector : public G4VUserDetectorConstruction
{
  public:

    LaBr3Detector(G4VPhysicalVolume* p_mother, G4double p_rho, G4double p_theta, G4double p_phi, G4double p_spin, G4int p_lb_nb);
    ~LaBr3Detector();

    //G4int GetLaBr3DetectorID();

    G4VPhysicalVolume* Construct();

  private:
    
    // Solid and Logical volumes
    //
    G4VSolid*        LaBr3_crystal_sol;
    G4VSolid*        LaBr3_optical_disk_sol;
    G4VSolid*        LaBr3_resin_sol;
    G4VSolid*        LaBr3_capsule_sol;
    G4VSolid*        LaBr3_glass_pmt_sol;
    G4VSolid*        LaBr3_capsule_pmt_sol;
    G4VSolid*        LaBr3_tape_sol;
    G4VSolid*        LaBr3_Al_layer_sol;
    G4LogicalVolume* LaBr3_crystal_log;
    G4LogicalVolume* LaBr3_optical_disk_log;
    G4LogicalVolume* LaBr3_resin_log;
    G4LogicalVolume* LaBr3_capsule_log;
    G4LogicalVolume* LaBr3_glass_pmt_log;
    G4LogicalVolume* LaBr3_capsule_pmt_log;
    G4LogicalVolume* LaBr3_tape_log;
    G4LogicalVolume* LaBr3_Al_layer_log;
    
    // Physical volumes
    //
    G4VPhysicalVolume* mother;
    G4VPhysicalVolume* LaBr3_crystal;
    G4VPhysicalVolume* LaBr3_optical_disk;
    G4VPhysicalVolume* LaBr3_resin;
    G4VPhysicalVolume* LaBr3_capsule;
    G4VPhysicalVolume* LaBr3_glass_pmt;
    G4VPhysicalVolume* LaBr3_capsule_pmt;
    G4VPhysicalVolume* LaBr3_tape;
    G4VPhysicalVolume* LaBr3_Al_layer;

    // Sensitive Volume
    //
    LaBr3SensitiveDetector* LaBr3SD;


    // Position and Orientation
    //
    G4double rho;
    G4double phi;
    G4double theta;
    G4double spin;
    G4int    lb_nb;
 
    // Visualisation
    //
    G4VisAttributes* det_vis_att;
    G4VisAttributes* Capsule_vis_att;

};

#endif

