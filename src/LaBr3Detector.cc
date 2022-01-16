/************************************************************************
 * \file LaBr3Detector.hh
 *
 * \class LaBr3Detector   
 * \brief Design of a LaBr3 detector crystal 
 *
 * \author Christophe Sotty : csotty@gmail.com
 *                            Christophe.Sotty@fys.kuleuven.be
 *
 *************************************************************************/
//R. Lica on 01.03.2016 - Removed environment, cleaned the code 

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
#include "LaBr3Detector.hh"
#include "G4NistManager.hh"
#include "G4UserLimits.hh"
#include "G4SystemOfUnits.hh"
#include "CADMesh.hh"

using namespace std;

LaBr3Detector::LaBr3Detector(G4VPhysicalVolume* p_mother, G4double p_rho, G4double p_theta, G4double p_phi, G4double p_spin, G4int p_lb_nb)
 : mother(p_mother), rho(p_rho), phi(p_phi), theta(p_theta), spin(p_spin), lb_nb(p_lb_nb)

{
	G4cout	<<"\nLaBr3 DETECTOR#######################\n"	<<flush
		<<"\nRho =\t\t"		<<rho/mm	<< " mm"	<<flush
		<<"\nTheta =\t\t"	<<theta/deg	<< " deg" 	<<flush
		<<"\nPhi =\t\t"		<<phi/deg	<< " deg"       <<flush
		<<"\nSpin =\t\t"	<<spin/deg	<< " deg"       <<flush
		<<"\nLaBr3 Nb =\t"	<<lb_nb 			<<G4endl;
}

LaBr3Detector::~LaBr3Detector()
{
}


G4VPhysicalVolume* LaBr3Detector::Construct(){

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
    G4Material* Teflon		= NISTmgr->FindOrBuildMaterial("G4_TEFLON"); 
    G4Material* Glass		= NISTmgr->FindOrBuildMaterial("G4_SILICON_DIOXIDE"); 

    G4Element* La_el		= new G4Element("Lanthanum"     , "La_el", 57,138.90547*g/mole);
    G4Element* Br_el		= new G4Element("Bromium"       , "Br_el", 35,   79.904*g/mole);
    G4Element* Ce_el		= new G4Element("Cerium"        , "Ce_el", 58,  140.116*g/mole);
      
    G4Element*  H_el = new G4Element("Hydrogen" ,  "H_el", 1 ,   1.01*g/mole);
    G4Element*  C_el = new G4Element("Carbone"  ,  "C_el", 6 ,  12.01*g/mole);
    G4Element* Cl_el = new G4Element("Chlorine" , "Cl_el", 17, 35.453*g/mole);

    G4Material* LaBr3		= new G4Material("LaBr3_Ce", 5.07*g/cm3,2);
    LaBr3 -> AddElement(La_el, 1);
    LaBr3 -> AddElement(Br_el, 3);
    
    G4Material* LaBr3_Ce	= new G4Material("LaBr3_Ce", 5.08*g/cm3,2);
    LaBr3_Ce -> AddMaterial(LaBr3, 99.5*perCent);
    LaBr3_Ce -> AddElement( Ce_el,  0.5*perCent);

    G4Material * myPVC    = new G4Material("C2_H3_CL", 1.44*g/cm3, 3);
    myPVC->AddElement( C_el,   2); //12.011x2/Total
    myPVC->AddElement( H_el,   3); //1.008x3/Total
    myPVC->AddElement(Cl_el,  1); //35.453x1/Total

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
//////////////////////////////////////////////////////////////////////////////////
// My Limits to cut the neutron at low energy, see also tndge_PhysicsList

//  double maxStep=DBL_MAX; 	// 1min10sec with cuts SET...
  double maxStep=100*m; 	// 1min10sec with cuts SET...
  double maxTrackLength = 50*m; // no difference between 100m and 50m .....
  double maxTime = 1*ms; 	// no difference between 1ms and 0.1ms .....
  double minEkin = 30*keV;	// from 50 keV to 150 keV you gain about 8 sec for 10.000 events 
  // logicTracker->SetUserLimits(new G4UserLimits(maxStep,maxLength,maxTime,
  //                                               minEkin))
  G4UserLimits* myNeutronLimits=new G4UserLimits(maxStep, maxTrackLength, maxTime, minEkin);


///////////////////////////////////////////////////////////////////////////////////
// ------------------------------- VOLUMES ----------------------------------------


  G4double detsize_y    = 25.*mm;
  G4double detsize_z    = 30.*mm;
  G4double detsize_x    = 26.*mm;
  
  
  G4VisAttributes* LaBr3VisAtt = new G4VisAttributes(G4Colour(0.0,0.0,1.0));
  LaBr3VisAtt->SetVisibility(true);
  det_vis_att = LaBr3VisAtt;

  G4VisAttributes* Al_vis_att   = new G4VisAttributes(G4Colour(0.65,0.65,0.65));
  Capsule_vis_att = Al_vis_att;
  Capsule_vis_att->SetVisibility(true);
  
  CADMesh *mesh_LaBr3_crystal		= NULL; 
  CADMesh *mesh_LaBr3_optical_disk	= NULL; 
  CADMesh *mesh_LaBr3_resin			= NULL;
  CADMesh *mesh_LaBr3_capsule		= NULL; 
  CADMesh *mesh_LaBr3_glass_pmt		= NULL; 
  CADMesh *mesh_LaBr3_capsule_pmt	= NULL; 
  CADMesh *mesh_LaBr3_tape			= NULL; 
  CADMesh *mesh_LaBr3_Al_layer		= NULL; 
  
  mesh_LaBr3_crystal		= new CADMesh(const_cast<char*>("../STL_export/LaBr3/wTape/gap3mm/Assembly_LaBr3_modif2_RefZero_LaBr3_Crystal_4.stl")	, mm,  G4ThreeVector(0*cm, 0*cm, -detsize_z), false);
  cout << "../STL_export/LaBr3/wTape/gap3mm/Assembly_LaBr3_modif2_RefZero_LaBr3_Crystal_4.stl" << endl;

  mesh_LaBr3_optical_disk	= new CADMesh(const_cast<char*>("../STL_export/LaBr3/wTape/AssemblyTape_ZeroRef_OPTICAL_DISK_4.stl")					, mm,  G4ThreeVector(0*cm, 0*cm, -detsize_z), false);
  cout << "../STL_export/LaBr3/wTape/AssemblyTape_ZeroRef_OPTICAL_DISK_4.stl" << endl;

  mesh_LaBr3_resin			= new CADMesh(const_cast<char*>("../STL_export/LaBr3/wTape/gap3mm/Assembly_LaBr3_modif2_RefZero_Resin_full_5.stl")		, mm,  G4ThreeVector(0*cm, 0*cm, -detsize_z), false);
  cout << "../STL_export/LaBr3/wTape/gap3mm/Assembly_LaBr3_modif2_RefZero_Resin_full_5.stl" << endl;

  mesh_LaBr3_glass_pmt  	= new CADMesh(const_cast<char*>("../STL_export/LaBr3/wTape/AssemblyTape_ZeroRef_GLASS_PMT_5.stl")						, mm,  G4ThreeVector(0*cm, 0*cm, -detsize_z), false);
  cout << "../STL_export/LaBr3/wTape/AssemblyTape_ZeroRef_GLASS_PMT_5.stl" << endl;

  mesh_LaBr3_capsule		= new CADMesh(const_cast<char*>("../STL_export/LaBr3/wTape/gap3mm/Assembly_LaBr3_modif2_RefZero_Capsule_Al_2.stl")		, mm,  G4ThreeVector(0*cm, 0*cm, -detsize_z), false);
  cout << "../STL_export/LaBr3/wTape/gap3mm/Assembly_LaBr3_modif2_RefZero_Capsule_Al_2.stl" << endl;

  mesh_LaBr3_capsule_pmt	= new CADMesh(const_cast<char*>("../STL_export/LaBr3/wTape/AssemblyTape_ZeroRef_CAPSULE_PMT_6.stl")						, mm,  G4ThreeVector(0*cm, 0*cm, -detsize_z), false);
  cout << "../STL_export/LaBr3/wTape/AssemblyTape_ZeroRef_CAPSULE_PMT_6.stl" << endl;

  mesh_LaBr3_tape			= new CADMesh(const_cast<char*>("../STL_export/LaBr3/wTape/gap3mm/Assembly_LaBr3_modif2_RefZero_TAPE_1.stl")			, mm,  G4ThreeVector(0*cm, 0*cm, -detsize_z), false);
  cout << "../STL_export/LaBr3/wTape/gap3mm/Assembly_LaBr3_modif2_RefZero_TAPE_1.stl" << endl;

  mesh_LaBr3_Al_layer		= new CADMesh(const_cast<char*>("../STL_export/LaBr3/wTape/gap3mm/Assembly_LaBr3_modif2_RefZero_ADDITIONAL_AL_LAYER_3.stl")	, mm,  G4ThreeVector(0*cm, 0*cm, -detsize_z), false);
  cout << "../STL_export/LaBr3/wTape/gap3mm/Assembly_LaBr3_modif2_RefZero_ADDITIONAL_AL_LAYER_3.stl" << endl;

  
  
  
  
  
  
  
  LaBr3_crystal_sol			= mesh_LaBr3_crystal		->TessellatedMesh();
  LaBr3_optical_disk_sol	= mesh_LaBr3_optical_disk	->TessellatedMesh();
  LaBr3_resin_sol			= mesh_LaBr3_resin			->TessellatedMesh();
  LaBr3_capsule_sol			= mesh_LaBr3_capsule		->TessellatedMesh();
  LaBr3_glass_pmt_sol		= mesh_LaBr3_glass_pmt		->TessellatedMesh();
  LaBr3_capsule_pmt_sol 	= mesh_LaBr3_capsule_pmt	->TessellatedMesh();
  LaBr3_tape_sol			= mesh_LaBr3_tape			->TessellatedMesh();
  LaBr3_Al_layer_sol		= mesh_LaBr3_Al_layer		->TessellatedMesh();

  LaBr3_crystal_log			= new G4LogicalVolume (LaBr3_crystal_sol,   	LaBr3_Ce, "/LaBr3_crystal_log");
  LaBr3_optical_disk_log	= new G4LogicalVolume (LaBr3_optical_disk_sol,  Glass, "/LaBr3_optical_disk_log");
  LaBr3_resin_log			= new G4LogicalVolume (LaBr3_resin_sol,	        Teflon, "/LaBr3_resin_log");
  LaBr3_capsule_log			= new G4LogicalVolume (LaBr3_capsule_sol,	    Al_mat, "/LaBr3_capsule_log");
  LaBr3_glass_pmt_log		= new G4LogicalVolume (LaBr3_glass_pmt_sol,  	Glass, "/LaBr3_glass_pmt_log");
  LaBr3_capsule_pmt_log 	= new G4LogicalVolume (LaBr3_capsule_pmt_sol, 	Al_mat, "/LaBr3_capsule_pmt_log");
  LaBr3_tape_log			= new G4LogicalVolume (LaBr3_tape_sol, 			myPVC, "/LaBr3_tape_log");
  LaBr3_Al_layer_log		= new G4LogicalVolume (LaBr3_Al_layer_sol, 		Al_mat, "/LaBr3_Al_layer_log");
  
  LaBr3_crystal_log			->SetVisAttributes(attgreen);
  LaBr3_optical_disk_log	->SetVisAttributes(attturq);
  LaBr3_resin_log			->SetVisAttributes(attwhite);
  LaBr3_capsule_log			->SetVisAttributes(Al_vis_att);
  LaBr3_glass_pmt_log		->SetVisAttributes(attyellow);
  LaBr3_capsule_pmt_log	->SetVisAttributes(Al_vis_att);
  LaBr3_tape_log			->SetVisAttributes(attviolet);
  LaBr3_Al_layer_log		->SetVisAttributes(Al_vis_att);

  
  //////////////////////////////////////
  // DETECTOR PLACEMENT

  
    rho = rho + detsize_z;
    
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
  
  
  LaBr3_crystal		= new G4PVPlacement(transformation,  "/LaBr3_crystal"	, LaBr3_crystal_log		, mother, false, 0);
  LaBr3_resin		= new G4PVPlacement(transformation,  "/LaBr3_resin"		, LaBr3_resin_log		, mother, false, 0);
  LaBr3_capsule		= new G4PVPlacement(transformation,  "/LaBr3_capsule"	, LaBr3_capsule_log		, mother, false, 0);
  LaBr3_tape		= new G4PVPlacement(transformation,  "/LaBr3_tape"		, LaBr3_tape_log		, mother, false, 0);
  LaBr3_Al_layer	= new G4PVPlacement(transformation,  "/LaBr3_Al_layer"	, LaBr3_Al_layer_log	, mother, false, 0);


  LaBr3_glass_pmt		= new G4PVPlacement(transformation, "/LaBr3_glass_pmt",		LaBr3_glass_pmt_log,	mother, false, 0);
  LaBr3_capsule_pmt		= new G4PVPlacement(transformation, "/LaBr3_capsule_pmt",	LaBr3_capsule_pmt_log,	mother, false, 0);
  LaBr3_optical_disk	= new G4PVPlacement(transformation, "/LaBr3_optical_disk",	LaBr3_optical_disk_log, mother, false, 0);


// ------------------------- END OF VOLUMES ---------------------------------------
///////////////////////////////////////////////////////////////////////////////////

  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  LaBr3SD = new LaBr3SensitiveDetector(Form("LaBr3_SD_%i",lb_nb));
  SDman->AddNewDetector(LaBr3SD);
  LaBr3_crystal_log->SetSensitiveDetector(LaBr3SD);
  LaBr3SD->SetLaBr3DetectorID(lb_nb);
  G4cout << "LaBr3 Sensitive Detector Name = " << LaBr3SD->GetName() << flush << G4endl;
  
  return(mother);

}

/*
G4int LaBr3Detector::GetLaBr3DetectorID()
{
  if(LaBr3SD)
    return(LaBr3SD->GetLaBr3DetectorID());                                                                                                                                                                               
  else
    return(-1);
}
*/







