
#ifndef FrontPlasticKUDetector_H
#define FrontPlasticKUDetector_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material; 

#include "G4VUserDetectorConstruction.hh"
#include "FrontPlasticKUSD.hh"

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


class FrontPlasticKUDetector : public G4VUserDetectorConstruction
{
  public:

    FrontPlasticKUDetector(G4VPhysicalVolume* p_mother, G4double p_rho, G4double p_theta, G4double p_phi, G4double p_spin);
    ~FrontPlasticKUDetector();

    //G4int GetFrontPlasticKUDetectorID();

    G4VPhysicalVolume*	Construct();

  private:
    
    // Solid and Logical volumes
    //
    G4VSolid*		FrontPlasticKU_sol;
    G4LogicalVolume*	FrontPlasticKU_log;
    G4VSolid*		FrontPlasticKU_Alsheet_sol;
    G4LogicalVolume*	FrontPlasticKU_Alsheet_log;
    G4VSolid*		FrontPlasticKU_BTape_sol;
    G4LogicalVolume*	FrontPlasticKU_BTape_log;
    FrontPlasticKUSD*	FrontPKUSD;

    
    // Physical volumes
    //
    G4VPhysicalVolume*	mother;
    G4VPhysicalVolume*	FrontPlasticKU_det;
    G4VPhysicalVolume*	FrontPlasticKU_Alsheet;
    G4VPhysicalVolume*	FrontPlasticKU_BTape;

    // Position and Orientation
    //
    G4double		rho;
    G4double		phi;
    G4double		theta;
    G4double		spin;
    G4Transform3D*	FrontPlasticKU_transformation;

    // Visualisation
    //
    G4VisAttributes*	det_vis_att;
    G4VisAttributes*	BTape_vis_att;

};

#endif

