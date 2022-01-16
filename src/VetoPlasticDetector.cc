/************************************************************************
 * \file VetoPlasticDetector.hh
 *
 * \class VetoPlasticDetector   
 * \brief Design of a VetoPlastic detector
 *
 * \author R. Lica
 *
 *************************************************************************/
//R. Lica on 01.03.2016 - adding it as sensitive detector. everything seems to work


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
#include "VetoPlasticDetector.hh"
#include "G4NistManager.hh"
#include "G4UserLimits.hh"
#include "G4SystemOfUnits.hh"
#include "CADMesh.hh"

using namespace std;

VetoPlasticDetector::VetoPlasticDetector(G4VPhysicalVolume* p_mother, G4double p_rho, G4double p_theta, G4double p_phi, G4double p_spin, G4int p_det_nb)
 : mother(p_mother), rho(p_rho), phi(p_phi), theta(p_theta), spin(p_spin), det_nb(p_det_nb)

{
	G4cout	<<"\nVetoPlastic DETECTOR#######################\n"	<<flush
		<<"\nRho =\t\t"		<<rho/mm	<< " mm"	<<flush
		<<"\nTheta =\t\t"	<<theta/deg	<< " deg" 	<<flush
		<<"\nPhi =\t\t"		<<phi/deg	<< " deg"   <<flush
		<<"\nSpin =\t\t"	<<spin/deg	<< " deg"   <<flush
		<<"\nDet Nb =\t\t"	<<det_nb                <<flush<<G4endl;
}

VetoPlasticDetector::~VetoPlasticDetector()
{
}


G4VPhysicalVolume* VetoPlasticDetector::Construct(){

    // Naming
    //
    G4String name = "/VetoPlastic";


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



  
  G4double detsize_y    = 101.*mm;
  G4double detsize_z    = 6*mm;
  G4double detsize_x    = 101.*mm;
  
  
  G4VisAttributes* VetoPlasticVisAtt = new G4VisAttributes(G4Colour(0.0,0.0,1.0));
  VetoPlasticVisAtt->SetVisibility(true);
  det_vis_att = VetoPlasticVisAtt;

  //G4VisAttributes* BTape_vis_att   = new G4VisAttributes(G4Colour(0.0,0.9,0.9));
  //BTape_vis_att->SetVisibility(true);


  CADMesh *mesh_VetoPlastic	  = NULL; 
  //CADMesh *mesh_VetoPlastic_BTape = NULL; 
  mesh_VetoPlastic		= new CADMesh(const_cast<char*>("../STL_export/Bucharest_VetoPlastic/VETOPLASTIC.stl")    , mm,  G4ThreeVector(0*cm, 0*cm, 0*cm), false);
  //mesh_VetoPlastic_BTape	= new CADMesh(const_cast<char*>("../STL_export/IDS_5/IDS_5_Black_Tape_Fast_Plastic_173.stl"), mm,  G4ThreeVector(109.41*cm, 42.58*cm, -50.305*cm), false);
  VetoPlastic_sol		= mesh_VetoPlastic->TessellatedMesh();
  //VetoPlastic_BTape_sol		= mesh_VetoPlastic_BTape->TessellatedMesh();

  VetoPlastic_log 		= new G4LogicalVolume(VetoPlastic_sol, PlastScint, "/VetoPlastic_log");
  VetoPlastic_log		->SetVisAttributes(VetoPlasticVisAtt);
  //VetoPlastic_BTape_log		= new G4LogicalVolume(VetoPlastic_BTape_sol, BTape_mat, "/VetoPlastic_BTape_log");
  //VetoPlastic_BTape_log		->SetVisAttributes(BTape_vis_att);



  //////////////////////////////////////
  // DETECTOR PLACEMENT

	rho = - (rho + detsize_z);
	
		//ROTATION and TRANSLATION
		//Spherical coordinates: rho, theta, phi
		 
      G4RotationMatrix rotation = G4RotationMatrix();
 
      if(0 != spin) rotation.rotateZ(spin);
      rotation.rotateY(phi);
      rotation.rotateX(theta);   
         

      G4ThreeVector translation(0., 0., rho);
      if(0 != spin) translation.rotateZ(spin);
      translation.rotateY(phi);
      translation.rotateX(theta);   
                 
      G4Transform3D transformation(rotation, translation);


  VetoPlastic_det		= new G4PVPlacement(transformation, name+"/Plastic", VetoPlastic_log        , mother, false, 0);
  //VetoPlastic_BTape		= new G4PVPlacement(transformation, name+"/BTape"  , VetoPlastic_BTape_log  , mother, false, 0);



// ------------------------- END OF VOLUMES ---------------------------------------
///////////////////////////////////////////////////////////////////////////////////

  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  VPSD= new VetoPlasticSD(Form("VetoPlastic_SD_%i", det_nb));
  SDman->AddNewDetector(VPSD);
  VetoPlastic_log->SetSensitiveDetector(VPSD);
  VPSD->SetVetoPlasticDetectorID(det_nb);
  G4cout << "VetoPlastic Sensitive Detector Name = " << VPSD->GetName() << flush << G4endl;
  
  return(mother);

}

/*
G4int VetoPlasticDetector::GetVetoPlasticDetectorID()
{
  if(VetoPlasticSD)
    return(VetoPlasticSD->GetVetoPlasticDetectorID());                                                                                                                                                                               
  else
    return(-1);
}
*/







