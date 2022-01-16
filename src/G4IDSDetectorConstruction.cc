/************************************************************************
 *
 *  Main detector construction
 *
 ************************************************************************/
//R. Lica on 01.03.2016 - Added VetoPlastic (IS530), cleaned a bit the code 


#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Cons.hh"
#include "G4VSolid.hh"
#include "G4VUserDetectorConstruction.hh"
#include "CADMesh.hh"
#include "G4NistManager.hh"

#include "Tape.hh"
#include "FrontPlasticKUDetector.hh"
#include "LeftPlasticKUDetector.hh"
#include "RightPlasticKUDetector.hh"
#include "FastPlasticDetector.hh"
#include "TPiece.hh"
#include "Cubic_Chamber.hh"
#include "IS530_Chamber.hh"
#include "IS530_Plastic.hh"
#include "VetoPlasticDetector.hh"
#include "Polyhedron.hh"
#include "LaBr3Detector.hh"
#include "CloverSingleDetector.hh"
#include "CloverQuadDetector.hh"
#include "CloverSingleBuchDetector.hh"
#include "CloverQuadBuchDetector.hh"
#include "tndge_DetectorConstruction.hh"
#include "math.h"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Cons.hh"
#include "G4VSolid.hh"
#include "G4IDSDetectorConstruction.hh"
#include "CADMesh.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"

#include "CADMesh.hh"

#include "global.hh"



using namespace std;

// Constructor
G4IDSDetectorConstruction::G4IDSDetectorConstruction(){;}


// Destructor
G4IDSDetectorConstruction::~G4IDSDetectorConstruction(){;}


// Construction of Detectors
//
G4VPhysicalVolume* G4IDSDetectorConstruction::Construct()
{
   
    G4NistManager* NISTmgr = G4NistManager::Instance();
    G4Material* Air    		= NISTmgr->FindOrBuildMaterial("G4_AIR"); 

//_________________________________ MOTHER VOLUME  ______________________________


   G4VisAttributes* Crystal0_vis_att = new G4VisAttributes(G4Colour(0.0,0.0,1.0));   
   G4VisAttributes* Crystal1_vis_att = new G4VisAttributes(G4Colour(0.0,1.0,0.0));   
   G4VisAttributes* Crystal2_vis_att = new G4VisAttributes(G4Colour(1.0,0.0,0.0));   
   G4VisAttributes* Crystal3_vis_att = new G4VisAttributes(G4Colour(0.0,1.0,1.0));   


  G4double mother_x 	= 1500.0*cm;
  G4double mother_y 	= 1500.0*cm;
  G4double mother_z 	= 1500.0*cm;
  G4Box*   mother_box 	= new G4Box("mother_box", mother_x,  mother_y,  mother_z);
  G4LogicalVolume* mother_log = new G4LogicalVolume (mother_box, Air, "mother_log", 0, 0, 0); 
  mother_log->SetVisAttributes(G4VisAttributes::Invisible); 
  G4PVPlacement* mother = new G4PVPlacement	(0, G4ThreeVector(0.,0.,0.), mother_log, "mother", 0, false, 0);

// __________________________ END OF MOTHER VOLUME  ______________________________


  vector<CloverQuadDetector*> 		clquad_array;
  vector<CloverQuadBuchDetector*> 	clquadbuch_array;
  vector<LaBr3Detector*> 			labr3_array;
  vector<RightPlasticKUDetector*>	Rplastic_array;
  vector<LeftPlasticKUDetector*>	Lplastic_array;
  vector<FrontPlasticKUDetector*>	Fplastic_array;
  vector<FastPlasticDetector*>		Fastplastic_array;
  vector<Tape*>						tape_array;
  vector<TPiece*>					tpiece_array;
  vector<Polyhedron*>				poly_array;
  vector<Cubic_Chamber*>			cubic_chamber_array;
  vector<IS530_Chamber*>			IS530_chamber_array;
  vector<IS530_Plastic*>			IS530_plastic_array;
  vector<VetoPlasticDetector*>		VetoPlastic_array;


// ___________________________ DETECTORS and PARTS _________________________________
// defined in the "config.dat" file


	for(int l=0;l<gLines;l++){
		
		
		if(1==gType[l]){   																	// Clover KU
			clquad_array.push_back(		new CloverQuadDetector(	mother,
																(G4double) gDistance[l]*mm,
																(G4double) (gTheta[l]*deg),
																(G4double) (gPhi[l]*deg),
																(G4double) (gSpin[l]*deg),
																clquad_array.size()));
			
		}
		if(2==gType[l]){  																	// Clover Buch
			clquadbuch_array.push_back(	new CloverQuadBuchDetector(	mother,
																	(G4double) gDistance[l]*mm,
																	(G4double) (gTheta[l]*deg),
																	(G4double) (gPhi[l]*deg),
																	(G4double) (gSpin[l]*deg),
																	clquadbuch_array.size()));
		}
		if(3==gType[l]){  																	// LaBr3
			labr3_array.push_back(		new LaBr3Detector( mother,
														   (G4double) gDistance[l]*mm,
														   (G4double) (gTheta[l]*deg),
														   (G4double) (gPhi[l]*deg),
														   (G4double) (gSpin[l]*deg), 
														   labr3_array.size()));
		}			
		if(4==gType[l]){  																	// Right KU Leuven Plastic - Obsolete, we should remove them to cleanup the code (RL)
			Rplastic_array.push_back(	new RightPlasticKUDetector( mother,
																	(G4double) gDistance[l]*mm,
																	(G4double) (gTheta[l]*deg),
																	(G4double) (gPhi[l]*deg),
																	(G4double) (gSpin[l]*deg)));
			if(1<Rplastic_array.size()){
				cout<<"\nYou can only contruct the Right Plastic one time!!!\n";
				exit(0);
			}
		}
		if(5==gType[l]){  		// Left KU Leuven Plastic
			Lplastic_array.push_back(	new LeftPlasticKUDetector(mother,
			(G4double) gDistance[l]*mm,
			(G4double) (gTheta[l]*deg) ,
			(G4double) (gPhi[l]*deg),
			(G4double) (gSpin[l]*deg)));
			if(1<Lplastic_array.size()){
				cout<<"\nYou can only contruct the Left Plastic one time!!!\n";
				exit(0);
			}
			//Lplastic_array.at(Lplastic_array.size()-1)->Construct();
		}
		if(6==gType[l]){  // Front KU Leuven Plastic
			Fplastic_array.push_back(	new FrontPlasticKUDetector(mother,
			(G4double) gDistance[l]*mm,
			(G4double) (gTheta[l]*deg) ,
			(G4double) (gPhi[l]*deg),
			(G4double) (gSpin[l]*deg)));
			if(1<Fplastic_array.size()){
				cout<<"\nYou can only contruct the Front Plastic one time!!!\n";
				exit(0);
			}
			//Fplastic_array.at(Fplastic_array.size()-1)->Construct();
		}
		
		
		if(7==gType[l]){  																	// Fast Plastic MADRID
			Fastplastic_array.push_back(new FastPlasticDetector(mother,
																(G4double) gDistance[l]*mm,
																(G4double) (gTheta[l]*deg),
																(G4double) (gPhi[l]*deg),
																(G4double) (gSpin[l]*deg)));
			if(1<Fastplastic_array.size()){
				cout<<"\nYou can only contruct the Fast Plastic one time!!!\n";
				exit(0);
			}
		}
		if(8==gType[l]){  																	// Tape
			tape_array.push_back(new Tape(mother));
			if(1<tape_array.size()){
				cout<<"\nYou can only contruct the tape one time!!!\n";
				exit(0);
			}
			tape_array.at(tape_array.size()-1)->Construct();
		}
		if(9==gType[l]){  																	// Implantation Chamber
			tpiece_array.push_back(new TPiece(mother,
											  (G4double) gDistance[l]*mm,
											  (G4double) (gTheta[l]*deg),
											  (G4double) (gPhi[l]*deg),
											  (G4double) (gSpin[l]*deg)));
			if(1<tpiece_array.size()){
				cout<<"\nYou can only contruct the TPiece chamber one time!!!\n";
				exit(0);
			}
		}
		if(10==gType[l]){  													// Polyhedron 
			poly_array.push_back(new Polyhedron(mother,
												(G4double) gDistance[l]*mm,
												(G4double) (gTheta[l]*deg),
												(G4double) (gPhi[l]*deg),
												(G4double) (gSpin[l]*deg)));
			if(1<poly_array.size()){
				cout<<"\nYou can only contruct the Polyhedron frame one time!!!\n";
				exit(0);
			}
		}		
		if(11==gType[l]){  													// Cubic Chamber
			cubic_chamber_array.push_back(new Cubic_Chamber(mother,
															(G4double) gDistance[l]*mm,
															(G4double) (gTheta[l]*deg),
															(G4double) (gPhi[l]*deg),
															(G4double) (gSpin[l]*deg)));
			if(1<cubic_chamber_array.size()){
				cout<<"\nYou can only contruct the Cubic chamber one time!!!\n";
				exit(0);
			}
			
		}		
		if(12==gType[l]){  													// IS530 Chamber 
			IS530_chamber_array.push_back(new IS530_Chamber(mother,
															(G4double) gDistance[l]*mm,
															(G4double) (gTheta[l]*deg),
															(G4double) (gPhi[l]*deg),
															(G4double) (gSpin[l]*deg)));
			if(1<IS530_chamber_array.size()){
				cout<<"\nYou can only contruct the IS530 chamber frame one time!!!\n"; 
				exit(0);
			}
			
		}
		if(13==gType[l]){  													// IS530 Plastic - non-sensitive detector 
			IS530_plastic_array.push_back(new IS530_Plastic(mother,
															(G4double) gDistance[l]*mm,
															(G4double) (gTheta[l]*deg),
															(G4double) (gPhi[l]*deg),
															(G4double) (gSpin[l]*deg)));
			if(1<IS530_plastic_array.size()){
				cout<<"\nYou can only contruct the IS530 Plastic one time!!!\n"; 
				exit(0);
			}
		}
		
		if(14==gType[l]){  													// IS530 VetoPlastic - sensitive detector 
			
			VetoPlastic_array.push_back(new VetoPlasticDetector(mother,
																(G4double) gDistance[l]*mm,
																(G4double) (gTheta[l]*deg),
																(G4double) (gPhi[l]*deg),
																(G4double) (gSpin[l]*deg),
																VetoPlastic_array.size()));
			
		}		

	}

  //Construction

  // 1. Clover KU Leuven
  for (int clq=0; clq<clquad_array.size(); clq++){
    clquad_array.at(clq)->Construct();
  }
  // 2. Clover Bucharest
  for (int clq=0; clq<clquadbuch_array.size(); clq++){
    clquadbuch_array.at(clq)->Construct();
  }
  // 3. LaBr3
  for (int lb=0; lb<labr3_array.size(); lb++){
    labr3_array.at(lb)->Construct();
  }
  // 4. Right plastic KU LEuven
  for (int rp=0; rp<Rplastic_array.size(); rp++){
    Rplastic_array.at(rp)->Construct();
  }
  // 5. Left plastic KU Leuven
  for (int lp=0; lp<Lplastic_array.size(); lp++){
    Lplastic_array.at(lp)->Construct();
  }
  // 6. Front plastic KU Leuven
  for (int fp=0; fp<Fplastic_array.size(); fp++){
    Fplastic_array.at(fp)->Construct();
  }
  // 7. Fast plastic Madrid
  for (int fastp=0; fastp<Fastplastic_array.size(); fastp++){
    Fastplastic_array.at(fastp)->Construct();
  }
  // 8. Tape
  for (int t=0; t<tape_array.size(); t++){
    tape_array.at(t)->Construct();
  }
  // 9. TPiece chamber
  for (int tp=0; tp<tpiece_array.size(); tp++){
    tpiece_array.at(tp)->Construct();
  }
  // 10. OSIRIS chamber
  for (int pl=0; pl<poly_array.size(); pl++){
    poly_array.at(pl)->Construct();
  }
  // 11. Cubic chamber
  for (int cc=0; cc<cubic_chamber_array.size(); cc++){
    cubic_chamber_array.at(cc)->Construct();
  }
  // 12. IS530 chamber
  for (int is=0; is<IS530_chamber_array.size(); is++){
    IS530_chamber_array.at(is)->Construct();
  }
  // 13. IS530 plastic - non sensitive detector
  for (int is=0; is<IS530_plastic_array.size(); is++){
    IS530_plastic_array.at(is)->Construct();
  }
  // 14. Vetoplastic - sensitive detector
  for (int vp=0; vp<VetoPlastic_array.size(); vp++){
    VetoPlastic_array.at(vp)->Construct();
  }
 
 
  cout << "G4IDSDetectorConstruction - DONE" <<endl;
  SetNbLaBr3(labr3_array.size());
  G4cout << "labr3_array.size() = " << GetNbLaBr3() << G4endl;

  SetNbClKU(clquad_array.size());
  G4cout << "clquad_array.size() = " << GetNbClKU() << G4endl;

  SetNbClBuch(clquadbuch_array.size());
  G4cout << "clquadbuch_array.size() = " << GetNbClBuch() << G4endl;

  SetNbVetoPlastic(VetoPlastic_array.size());
  G4cout << "VetoPlastic_array.size() = " << GetNbVetoPlastic() << G4endl;





  G4Element*  H = new G4Element("Hydrogen" ,  "H", 1 ,   1.01*g/mole);                                                                                                                                                                                
  G4Element*  C = new G4Element("Carbone"  ,  "C", 6 ,  12.01*g/mole);
  G4Element*  O = new G4Element("Oxygene"  ,  "O", 8 ,  16.00*g/mole);
          
  G4Material* ne104a = new G4Material("NE104A",1.023*g/cm3,2); // 
  ne104a->AddElement(H, 52.4*perCent);
  ne104a->AddElement(C, 47.6*perCent);

  G4Material* mylar = new G4Material("Mylar",1.365*g/cm3,3); //
  mylar->AddElement(H, 8);
  mylar->AddElement(C,10);
  mylar->AddElement(O, 4);

  G4VisAttributes* AlVisAtt = new G4VisAttributes(G4Colour::Blue());
  AlVisAtt->SetVisibility(true);
  G4VisAttributes* MylarVisAtt = new G4VisAttributes(G4Colour::Green());
  MylarVisAtt->SetVisibility(true);
  G4VisAttributes* NE104AVisAtt = new G4VisAttributes(G4Colour::Red());
  NE104AVisAtt->SetVisibility(true);


  G4VSolid*              CenterPoint_sol;
  G4LogicalVolume*       CenterPoint_log;
  G4VPhysicalVolume*     CenterPoint;
  CADMesh *mesh_CenterPoint      = new CADMesh(const_cast<char*>("../STL_export/IDS_5/IDS_5_CenterPoint_63.stl"), mm,  G4ThreeVector(109.41*cm, 42.58*cm, -50.305*cm), false);
  CenterPoint_sol                = mesh_CenterPoint->TessellatedMesh();
  CenterPoint_log = new G4LogicalVolume(CenterPoint_sol       , mylar    , "CenterPoint_log"           );
  CenterPoint_log->SetVisAttributes(AlVisAtt);
  //CenterPoint    = new G4PVPlacement(0, G4ThreeVector(0, 0, 0), "CenterPoint", CenterPoint_log, mother, false, 0);

  return mother;

}


void G4IDSDetectorConstruction::Print()
{   	
}




