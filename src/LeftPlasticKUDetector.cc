/************************************************************************
 * \file LeftPlasticKUDetector.hh
 *
 * \class LeftPlasticKUDetector   
 * \brief Design of a LeftPlasticKU detector
 *
 * \author Christophe Sotty : csotty@gmail.com
 *                            Christophe.Sotty@fys.kuleuven.be
 *
 *************************************************************************/

#include <TText.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <istream>
#include <ostream>
#include <streambuf>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "LeftPlasticKUDetector.hh"
#include "G4NistManager.hh"
#include "G4UserLimits.hh"
#include "G4SystemOfUnits.hh"
#include "CADMesh.hh"

using namespace std;

LeftPlasticKUDetector::LeftPlasticKUDetector(G4VPhysicalVolume* p_mother, G4double p_rho, G4double p_theta, G4double p_phi, G4double p_spin)
 : mother(p_mother), rho(p_rho), phi(p_phi), theta(p_theta), spin(p_spin)

{
	G4cout	<<"\nLeftPlasticKU DETECTOR#######################\n"	<<flush
		<<"\nRho =\t\t"		<<rho/mm	<< " mm"	<<flush
		<<"\nTheta =\t\t"	<<theta/deg	<< " deg" 	<<flush
		<<"\nPhi =\t\t"		<<phi/deg	<< " deg"       <<flush
		<<"\nSpin =\t\t"	<<spin/deg	<< " deg"       <<flush<<G4endl;
}

LeftPlasticKUDetector::~LeftPlasticKUDetector()
{
}


G4VPhysicalVolume* LeftPlasticKUDetector::Construct(){

    // Naming
    //
    G4String name = "/LeftPlasticKU";


//________MATERIALS DEFINITION:::___________________
//                     see G4NistMaterialBuilder.cc for definitions
//__________________________________________________

    G4NistManager* NISTmgr = G4NistManager::Instance();
    
    G4Material* Vacuum 		= NISTmgr->FindOrBuildMaterial("G4_Galactic"); 
    G4Material* Air    		= NISTmgr->FindOrBuildMaterial("G4_AIR"); 
    G4Material* Cu_mat 		= NISTmgr->FindOrBuildMaterial("G4_Cu");
    G4Material* Al_mat 		= NISTmgr->FindOrBuildMaterial("G4_Al");
    G4Material* Pb_mat 		= NISTmgr->FindOrBuildMaterial("G4_Pb"); 
    G4Material* Gd_mat 		= NISTmgr->FindOrBuildMaterial("G4_Gd"); 
    G4Material* HPGe   		= NISTmgr->FindOrBuildMaterial("G4_Ge"); 
    G4Material* LaBr   		= NISTmgr->FindOrBuildMaterial("G4_LANTHANUM_OXYBROMIDE"); 
    G4Material* PlastScint 	= NISTmgr->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"); 
    G4Material* Fe_mat 		= NISTmgr->FindOrBuildMaterial("G4_Fe"); 
    G4Material* Nb_mat 		= NISTmgr->FindOrBuildMaterial("G4_Nb"); 
    G4Material* Concrete 	= NISTmgr->FindOrBuildMaterial("G4_CONCRETE"); 
    G4Material* Paraffin 	= NISTmgr->FindOrBuildMaterial("G4_PARAFFIN"); 

    G4Element* Cu = new G4Element("Copper"   , "Cu", 29, 63.546*g/mole);
    G4Element* Zn = new G4Element("Zinc"     , "Zn", 30, 65.380*g/mole);
    G4Element*  H = new G4Element("Hydrogen" ,  "H", 1 ,   1.01*g/mole);
    G4Element*  C = new G4Element("Carbone"  ,  "C", 6 ,  12.01*g/mole);
    G4Element*  O = new G4Element("Oxygene"  ,  "O", 8 ,  16.00*g/mole);
    G4Element* Cl = new G4Element("Chlorine" , "Cl", 17, 35.453*g/mole);

    G4Material * myPVC    = new G4Material("C2_H3_CL", 1.44*g/cm3, 3);
    myPVC->AddElement(C,   2); //12.011x2/Total
    myPVC->AddElement(H,   3); //1.008x3/Total
    myPVC->AddElement(Cl,  1); //35.453x1/Total

    G4Material* ne104a = new G4Material("NE104A",1.023*g/cm3,2); // 
    ne104a->AddElement(H, 52.4*perCent);
    ne104a->AddElement(C, 47.6*perCent);

    G4Material* BTape_mat	= myPVC; // ????????????????????????????? CS YOU NEED TO CHANGE THIS MATERIAL !!!!!!!!!!!!!!!!!

//______ END OF MATERIALS DEFINITION _______________________________________
////////////////////////////////////////////////////////////////////////////
 
////////////////////////////////////////////////////////////////////////////////
// ______________________________ COLOURS ______________________________________

    G4Colour red	(1.,0.,0.);		// Define red color
    G4Colour green	(0.,1.,0.);		// Define green color
    G4Colour blue	(0.,0.,1.);		// Define blue color
    G4Colour violet	(1.,0.,1.);
    G4Colour turquoise	(0.,1.,1.);
    G4Colour white	(1.,1.,1.);
    G4Colour yellow	(1.,1.,0.);
    G4Colour orange	(1.,0.5,0.);
    G4Colour grey	(0.5,0.5,0.5);
    G4VisAttributes attred(red);        	// Define a red visualization attribute
    G4VisAttributes attgreen(green);
    G4VisAttributes attblue(blue);
    G4VisAttributes attviolet(violet);
    G4VisAttributes attturq(turquoise);
    G4VisAttributes attwhite(white);
    G4VisAttributes attyellow(yellow);
    G4VisAttributes attorange(orange);
    G4VisAttributes attgrey(grey);
///////////////////////////////////////////////////////////////////////////////////
// ------------------------------- VOLUMES ----------------------------------------

  G4VisAttributes* LeftPlasticKUVisAtt = new G4VisAttributes(G4Colour(0.0,0.0,1.0));
  LeftPlasticKUVisAtt->SetVisibility(true);
  det_vis_att = LeftPlasticKUVisAtt;

  G4VisAttributes* BTape_vis_att   = new G4VisAttributes(G4Colour(0.0,0.9,0.9));
  BTape_vis_att->SetVisibility(true);

  G4VisAttributes* Al_vis_att   = new G4VisAttributes(G4Colour(0.5,0.5,0.5));
  Al_vis_att->SetVisibility(true);


  CADMesh *mesh_LeftPlasticKU		= NULL; 
  CADMesh *mesh_LeftPlasticKU_Alsheet	= NULL; 
  CADMesh *mesh_LeftPlasticKU_BTape	= NULL; 
  mesh_LeftPlasticKU		= new CADMesh(const_cast<char*>("../STL_export/IDS_5/IDS_5_SidePlastics_64.stl")          , mm,  G4ThreeVector(109.41*cm, 42.58*cm, -50.305*cm), false);
  mesh_LeftPlasticKU_Alsheet	= new CADMesh(const_cast<char*>("../STL_export/IDS_5/IDS_5_SidePlastics_AlSheet_65.stl")  , mm,  G4ThreeVector(109.41*cm, 42.58*cm, -50.305*cm), false);
  mesh_LeftPlasticKU_BTape	= new CADMesh(const_cast<char*>("../STL_export/IDS_5/IDS_5_SidePlastics_BlackTape_66.stl"), mm,  G4ThreeVector(109.41*cm, 42.58*cm, -50.305*cm), false);
  LeftPlasticKU_sol		= mesh_LeftPlasticKU->TessellatedMesh();
  LeftPlasticKU_Alsheet_sol	= mesh_LeftPlasticKU_Alsheet->TessellatedMesh();
  LeftPlasticKU_BTape_sol	= mesh_LeftPlasticKU_BTape->TessellatedMesh();

  LeftPlasticKU_log 		= new G4LogicalVolume(LeftPlasticKU_sol, ne104a, "/LeftPlasticKU_log");
  LeftPlasticKU_log		->SetVisAttributes(LeftPlasticKUVisAtt);
  LeftPlasticKU_Alsheet_log 	= new G4LogicalVolume(LeftPlasticKU_Alsheet_sol, Al_mat, "/LeftPlasticKU_Alsheet_log");
  LeftPlasticKU_Alsheet_log	->SetVisAttributes(Al_vis_att);
  LeftPlasticKU_BTape_log	= new G4LogicalVolume(LeftPlasticKU_BTape_sol, BTape_mat, "/LeftPlasticKU_BTape_log");
  LeftPlasticKU_BTape_log	->SetVisAttributes(BTape_vis_att);

    G4ThreeVector LeftPlasticKU_translation(0., 0., 0.);
    G4RotationMatrix LeftPlasticKU_rotation;
    LeftPlasticKU_rotation.rotateY(90.*deg);
    LeftPlasticKU_transformation     = new G4Transform3D(LeftPlasticKU_rotation, LeftPlasticKU_translation);

  // Set position of the detector in the mother volume
  if(LeftPlasticKU_transformation == NULL){
    G4RotationMatrix LeftPlasticKU_rotation;
    LeftPlasticKU_rotation.rotateX(-90.*deg);
    LeftPlasticKU_rotation.rotateZ(spin);
    LeftPlasticKU_rotation.rotateX(M_PI);
    LeftPlasticKU_rotation.rotateY(theta-0.*deg);
    LeftPlasticKU_rotation.rotateZ(phi);
      
  //      //distance from the origin to the center of the detector
  //      //      G4double trans_mag = rho + MoveToDetectorLeftClover();
    G4double trans_mag = rho ;
    G4ThreeVector LeftPlasticKU_translation(0., 0., trans_mag);
    LeftPlasticKU_translation.rotateY(theta);
    LeftPlasticKU_translation.rotateZ(phi);

    LeftPlasticKU_transformation      = new G4Transform3D(LeftPlasticKU_rotation, LeftPlasticKU_translation);
  }
  else if(spin != 0){
    G4RotationMatrix LeftPlasticKU_rotation = LeftPlasticKU_transformation->getRotation();
    G4ThreeVector LeftPlasticKU_translation = LeftPlasticKU_transformation->getTranslation();
    G4RotationMatrix spinLeftPlasticKU_rotation;
    spinLeftPlasticKU_rotation.rotateZ(spin);
      
    LeftPlasticKU_rotation *= spinLeftPlasticKU_rotation;
      
    LeftPlasticKU_transformation = new G4Transform3D(LeftPlasticKU_rotation, LeftPlasticKU_translation);
  }
  G4double detsize_y    = 55.*mm;
  G4double detsize_z    = 26.*mm;
  G4double detsize_x    = 26.*mm;

  G4Box* det_env_sol		= new G4Box(name+"/det_env", detsize_x, detsize_y, detsize_z);
  //G4LogicalVolume* det_env_log	= new G4LogicalVolume(det_env_sol, Vacuum, name+"/det_env_log");
  //det_env_log			-> SetVisAttributes(G4VisAttributes::Invisible);
  //G4PVPlacement* det_env	= new G4PVPlacement(*LeftPlasticKU_transformation, name+"/env", det_env_log, mother, false, 0);

  LeftPlasticKU_det		= new G4PVPlacement(*LeftPlasticKU_transformation, name+"/Plastic", LeftPlasticKU_log        , mother, false, 0);
  LeftPlasticKU_Alsheet	= new G4PVPlacement(*LeftPlasticKU_transformation, name+"/Alsheet", LeftPlasticKU_Alsheet_log, mother, false, 0);
  LeftPlasticKU_BTape		= new G4PVPlacement(*LeftPlasticKU_transformation, name+"/BTape"  , LeftPlasticKU_BTape_log  , mother, false, 0);



// ------------------------- END OF VOLUMES ---------------------------------------
///////////////////////////////////////////////////////////////////////////////////

  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  LeftPKUSD= new LeftPlasticKUSD("LeftPlasticKU_SD");
  SDman->AddNewDetector(LeftPKUSD);
  LeftPlasticKU_log->SetSensitiveDetector(LeftPKUSD);
  //LeftPlasticKUSD->SetLeftPlasticKUDetectorID(lb_nb);
  G4cout << "LeftPlasticKU Sensitive Detector Name = " << LeftPKUSD->GetName() << flush << G4endl;
  
  return(mother);

}

/*
G4int LeftPlasticKUDetector::GetLeftPlasticKUDetectorID()
{
  if(LeftPlasticKUSD)
    return(LeftPlasticKUSD->GetLeftPlasticKUDetectorID());                                                                                                                                                                               
  else
    return(-1);
}
*/







