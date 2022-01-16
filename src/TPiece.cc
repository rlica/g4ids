/************************************************************************
 * \file TPiece.hh
 *
 * \class TPiece   
 * \brief Design of the TPiece (Implantation Chamber for the Fast Timing and
 *                              Standard beta-decay configurations) 
 *
 * \author Christophe Sotty : csotty@gmail.com
 *                            Christophe.Sotty@fys.kuleuven.be
 *
 *************************************************************************/

#include "TPiece.hh"
#include "CADMesh.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include <TText.h>

using namespace std;



TPiece::TPiece(G4VPhysicalVolume* p_mother, G4double p_rho, G4double p_theta, G4double p_phi, G4double p_spin)
  :mother(p_mother), rho(p_rho), theta(p_theta), phi(p_phi), spin(p_spin)
{
	G4cout	<<"\nTPiece (Implantation Chamber) #######################\n"	<<flush
		<<"\nRho =\t\t"		<<rho/mm	<< " mm"	<<flush
		<<"\nTheta =\t\t"	<<theta/deg	<< " deg" 	<<flush
		<<"\nPhi =\t\t"		<<phi/deg	<< " deg"       <<flush
		<<"\nSpin =\t\t"	<<spin/deg	<< " deg"       <<flush<<G4endl;
}

TPiece::~TPiece()
{;}


G4VPhysicalVolume* TPiece::Construct()
{
    // Naming
    //
    G4String name="/TPiece";
    
    // Material
    //
    G4NistManager* NISTmgr = G4NistManager::Instance();

    G4Material* Vacuum          = NISTmgr->FindOrBuildMaterial("G4_Galactic");
    G4Material* Air             = NISTmgr->FindOrBuildMaterial("G4_AIR");
    G4Material* Al_mat          = NISTmgr->FindOrBuildMaterial("G4_Al");
    
    G4Element*  H = new G4Element("Hydrogen" ,  "H",  1 ,   1.01*g/mole);
    G4Element*  C = new G4Element("Carbone"  ,  "C",  6 ,  12.01*g/mole);
    G4Element*  O = new G4Element("Oxygene"  ,  "O",  8 ,  16.00*g/mole);
    G4Element* Cu = new G4Element("Copper"   , "Cu", 29.,  63.54*g/mole); 
    G4Element* Zn = new G4Element("Zinc"     , "Zn", 30.,  65.39*g/mole);
    G4Element* Mn = new G4Element("Manganse" , "Mn", 25., 54.938*g/mole);

    G4Material* Mylar = new G4Material("Mylar",1.365*g/cm3,3); //
    Mylar->AddElement(H, 8);
    Mylar->AddElement(C,10);
    Mylar->AddElement(O, 4);

    G4Material* Brass = new G4Material("Brass", 8.87*g/cm3, 3); 
    Brass->AddElement(Cu, 70.0*perCent);
    Brass->AddElement(Zn, 28.8*perCent);
    Brass->AddElement(Mn,  1.2*perCent);

    vector<G4Material* > Mat;
    Mat.push_back(Brass);
    Mat.push_back(Mylar);


    // Visualisation
    // 
    vector<G4VisAttributes*> CrysVisAttM;
    CrysVisAttM.push_back(new G4VisAttributes(G4Colour(0.0,0.0,1.0)));
    CrysVisAttM.push_back(new G4VisAttributes(G4Colour(0.0,1.0,0.0)));
    CrysVisAttM.push_back(new G4VisAttributes(G4Colour(1.0,0.0,0.0)));
    CrysVisAttM.push_back(new G4VisAttributes(G4Colour(0.0,1.0,1.0)));

    // Visualisation
    //
    vector<G4VisAttributes*> VisAttM;
    TPiece_vis_att			= new G4VisAttributes(G4Colour(0.7, 0.4, 0.1));		// Brown
    G4VisAttributes* Al_vis_att 	= new G4VisAttributes(G4Colour(0.65,0.65,0.65));	// Grey
    VisAttM.push_back(new G4VisAttributes(G4Colour(0.7, 0.4, 0.1)));		// Brown
    VisAttM.push_back(new G4VisAttributes(G4Colour(1.0, 1.0, 0.0,0.1)));		// Yellow


    // Position and Orientation
    //
    G4ThreeVector TPiece_translation(0., 0., 0.);
    TPiece_rotation.rotateY(90.*deg);
    TPiece_transformation     = new G4Transform3D(TPiece_rotation, TPiece_translation);
    
    if(TPiece_transformation==NULL){ 
      //HPGeCloverQuad_rotation.rotateX(M_PI);
      TPiece_rotation.rotateY(theta);
      TPiece_rotation.rotateZ(phi);
      
      ////distance from the origin to the center of the detector
      //G4double trans_mag = rho + MoveToDetectorFrontClover();
      //G4double trans_mag = rho + (7.5 - 0.2548)*cm;
      G4double trans_mag = 0.*cm;

      //G4ThreeVector HPGeCloverQuad_translation(0., 0., trans_mag);
      G4ThreeVector TPiece_translation(0., 0., trans_mag);
      TPiece_translation.rotateY(theta);
      TPiece_translation.rotateZ(phi);
      
      TPiece_transformation     = new G4Transform3D(TPiece_rotation, TPiece_translation);
    }
    if(spin != 0){
      TPiece_rotation = TPiece_transformation->getRotation();
      G4ThreeVector TPiece_translation = TPiece_transformation->getTranslation();
      G4RotationMatrix spinTPiece_rotation;
      spinTPiece_rotation.rotateX(spin);
      
      TPiece_rotation *= spinTPiece_rotation;
      
      TPiece_transformation = new G4Transform3D(TPiece_rotation, TPiece_translation);
    }

    // Environnement
    G4double detsize_y	= 450.*mm;
    G4double detsize_z	= 450.*mm;
    G4double detsize_x	= 450.*mm;
    G4Box* det_env_sol	= new G4Box(name+"/det_env", detsize_x, detsize_y, detsize_z);
    //det_env_log		= new G4LogicalVolume(det_env_sol, Vacuum, name+"/det_env_log");
    //det_env_log		-> SetVisAttributes(G4VisAttributes::Invisible);
    //det_env		= new G4PVPlacement(*TPiece_transformation, name+"/env", det_env_log, mother, false, 0);
    

    // Detector Construction
    //
    vector<char* > TPiece_name;
    TPiece_name.push_back("../STL_export/IDS_5/IDS_5_TPiece_60.stl");
    TPiece_name.push_back("../STL_export/IDS_5/IDS_5_Mylar_foils_TPiece_63.stl");

    // Meshing and Logical Volumes
    for(int i = 0; i<TPiece_name.size(); i++){ 
      G4cout<< TPiece_name.at(i) << G4endl;
      mesh_TPiece_current.push_back( new CADMesh(TPiece_name.at(i), mm, G4ThreeVector(109.41*cm, 42.58*cm, -50.305*cm), false));
      //G4cout << "mesh_TPiece_current" << G4endl;
      TPiece_current_sol.push_back( mesh_TPiece_current.at(i)->TessellatedMesh());
      //G4cout << "TPiece_current_sol" << G4endl;
      TPiece_current_log.push_back( new G4LogicalVolume(TPiece_current_sol.at(i), Mat.at(i), name+Form("TPiece_%i_log", i )));
      //G4cout << "TPiece_current_log" << G4endl;
      TPiece_current_log.at(i)	->SetVisAttributes(VisAttM.at(i));
      //G4cout << "SetVisAttributes" << G4endl;
      //TPiece_current_phys.push_back( new G4PVPlacement(0, G4ThreeVector(0, 0, 0), name+Form("/TPiece_%i_phys",i), TPiece_current_log.at(i), det_env, false, 0));
      TPiece_current_phys.push_back( new G4PVPlacement(*TPiece_transformation, name+Form("/TPiece_%i_phys",i), TPiece_current_log.at(i), mother, false, 0));
      //TPiece_current_phys.push_back( new G4PVPlacement(0, G4ThreeVector(0, 0, 0), name+Form("/TPiece_%i_phys",i), TPiece_current_log.at(i), mother, false, 0));
      //G4cout << "TPiece_current_phys" << G4endl;
    }

    return(mother);

}






















