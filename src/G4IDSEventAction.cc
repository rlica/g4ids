#include "G4RunManager.hh"
#include "G4IDSEventAction.hh"
#include "G4IDSDetectorConstruction.hh"
#include "G4LogLogInterpolator.hh"
#include "G4DataVector.hh"
#include <cmath>
#include <time.h>
#include "G4SystemOfUnits.hh"


#include "global.hh"



using namespace std;

 TFile	*G4IDSEventAction::fRootFile	= NULL;
 TTree	*G4IDSEventAction::fTree	= NULL;
 static clock_t t1,t2;

G4IDSEventAction::G4IDSEventAction(G4IDSDetectorConstruction* p_G4IDS_DC, G4String p_fFileName): G4IDS_DC(p_G4IDS_DC)
{

    fRootFile = new TFile(p_fFileName,"recreate");
    G4cout<<"**************   ROOT File opened: " << p_fFileName << "   **************";
    fRootFile->cd();
    fTree = new TTree("idstree","idstree"); 
    
//    // Detector indexing
    G4int nb_ClKU;						nb_ClKU	    = 		GLOB_nb_ClKU;
    G4int nb_ClBuch;					nb_ClBuch   = 		GLOB_nb_ClBuch;	 
    G4int nb_LaBr3;						nb_LaBr3    = 		GLOB_nb_LaBr3;	 
    G4int nb_FPlastic;					nb_FPlastic = 		GLOB_nb_FPlastic;	 
    G4int nb_FrontPlasticKU;	  nb_FrontPlasticKU = 		GLOB_nb_FrontPlasticKU;	 
    G4int nb_LeftPlasticKU;		   nb_LeftPlasticKU = 		GLOB_nb_LeftPlasticKU;	 
    G4int nb_RightPlasticKU;	  nb_RightPlasticKU = 		GLOB_nb_RightPlasticKU;
    G4int nb_VetoPlastic;		     nb_VetoPlastic = 		GLOB_nb_VetoPlastic;	 

//
    Cl_Cr_KU_En		= new double*[nb_ClKU];
    Cl_Cr_Buch_En	= new double*[nb_ClBuch];
    Cl_Cr_KU_EnAb		= new double*[nb_ClKU];
    Cl_Cr_Buch_EnAb	= new double*[nb_ClBuch];

    for(int yup=0; yup<nb_ClKU;yup++){     //... why yup? yup -> i :D keep the code clean  
      Cl_Cr_KU_En[yup]	= new double[4];
      Cl_Cr_KU_EnAb[yup]	= new double[4];
    }
    
    for(int yup=0; yup<nb_ClBuch;yup++){
      Cl_Cr_Buch_En[yup] = new double[4];
      Cl_Cr_Buch_EnAb[yup] = new double[4];
    }
      
    LaBr3_En = new double[nb_LaBr3];
    VetoPlastic_En = new double[nb_VetoPlastic];

    // Tree Branching 
    //
    // LaBr3 Bucharest and Madrid
    for(int lb = 0; lb<nb_LaBr3; lb++){
      fTree -> Branch (Form("LaBr3%i_En",lb) ,&LaBr3_En[lb] ,Form("LaBr3%i_En/D",lb));
      G4cout << Form("\nLaBr3%i_En",lb) << flush << G4endl;
    }


    // CloverQuad KU Leuven
    for(int cl = 0; cl<nb_ClKU ; cl++){
      for(int cr = 0 ; cr<4; cr++){
        fTree -> Branch (Form("Cl%i_Cr%i_KU_En",cl,cr)    ,&Cl_Cr_KU_En[cl][cr]   ,Form("Cl%i_Cr%i_KU_En/D"   ,cl,cr));
        fTree -> Branch (Form("Cl%i_Cr%i_KU_EnAb",cl,cr)  ,&Cl_Cr_KU_EnAb[cl][cr] ,Form("Cl%i_Cr%i_KU_EnAb/D" ,cl,cr));
	G4cout << Form("\nCl%i_Cr%i_KU_EnAb",cl,cr) << flush << G4endl;
      }
    }

    // CloverQuad Bucharest
    for(int cl = 0; cl<nb_ClBuch ; cl++){
      for(int cr = 0 ; cr<4; cr++){
        fTree -> Branch (Form("Cl%i_Cr%i_Buch_En",cl,cr)    ,&Cl_Cr_Buch_En[cl][cr]   ,Form("Cl%i_Cr%i_Buch_En/D"   ,cl,cr));
        fTree -> Branch (Form("Cl%i_Cr%i_Buch_EnAb",cl,cr)  ,&Cl_Cr_Buch_EnAb[cl][cr] ,Form("Cl%i_Cr%i_Buch_EnAb/D" ,cl,cr));
	G4cout << Form("\nCl%i_Cr%i_Buch_EnAb",cl,cr) << flush << G4endl;
      }
    }

    // Fast Plastic
    if(0 != nb_FPlastic){
      fTree -> Branch ("FPlastic_En" ,&FPlastic_En ,"FPlastic_En/D");
      G4cout << "FPlastic_En" << flush << G4endl;
    }

    // Front Plastic (KU Leuven)
    if(0 != nb_FrontPlasticKU){
      fTree -> Branch ("FrontPlasticKU_En" ,&FrontPlasticKU_En ,"FrontPlasticKU_En/D");
      G4cout << "FrontPlasticKU_En" << flush << G4endl;
    }

    // Left Plastic (KU Leuven)
    if(0 != nb_LeftPlasticKU){
      fTree -> Branch ("LeftPlasticKU_En" ,&LeftPlasticKU_En ,"LeftPlasticKU_En/D");
      G4cout << "LeftPlasticKU_En" << flush << G4endl;
    }

    // Right Plastic (KU Leuven)
    if(0 != nb_RightPlasticKU){
      fTree -> Branch ("RightPlasticKU_En" ,&RightPlasticKU_En ,"RightPlasticKU_En/D");
      G4cout << "RightPlasticKU_En" << flush << G4endl;
    }

    // Veto Plastic
    for(int vp = 0; vp<nb_VetoPlastic; vp++){
      fTree -> Branch (Form("VetoPlastic%i_En",vp) ,&VetoPlastic_En[vp] ,Form("VetoPlastic%i_En/D",vp));
      G4cout << Form("\nVetoPlastic%i_En",vp) << flush << G4endl;
    }
    
    
    
    



    // Ready !!!!
    G4cout << flush << G4endl <<"Finished building ROOT trees -  G4IDSEventAction.cc"  << G4endl << flush;

}


G4IDSEventAction::~G4IDSEventAction()
{
    
    fRootFile->cd();
    fTree->Write();	fRootFile->Close();
    //cout<<"\n\t**************   ROOT File closed   **************\t\t by EventAction :) \n";	

}


void G4IDSEventAction::BeginOfEventAction(const G4Event* anEvent)
{
	//fEvNo = anEvent->GetEventID();
	//if ( fEvNo%10000 == 0 ) G4cout << "\rbegin event.... "<<fEvNo << G4endl << flush;
	
	double oula=G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEvent();
        double oulatot=G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
	if(0==oula){t1=clock();}
        if((((int) oula) % 1000 == 0 ) && (oula>0)){
	  t2=clock();
	  int diff = (t2-t1)/1000000;
          int sec  = diff%60;
          int min_tot  = (diff-sec)/60;
          int min = min_tot%60;
	  int hour_tot = (min_tot - min)/60;
	  
	  int rdiff = (t2-t1)/1000000./(oula)*(oulatot-oula);
          int rsec  = rdiff%60;
          int rmin_tot  = (rdiff-rsec)/60;
          int rmin = rmin_tot%60;
	  int rhour_tot = (rmin_tot - rmin)/60;
	  //G4cout<<setw(100)<<"\r "<<std::flush;
          G4cout<<"\r Progress :"
                <<setw(4)<<""<<"["<<setw(10) <<(oula)<<"/"<<setw(10)<<(int)oulatot<<"] "<<setw(6.3)<< (oula)*100./oulatot<<"%"<<"\tSpent Time: "<<setw(2) <<hour_tot<<"h "<<setw(2)<<min<<"min "<<setw(2)<<sec<<"s"<<"          Estimated remaining time: "<<setw(2) <<rhour_tot<<"h "<<setw(2)<<rmin<<"min "<<setw(2)<<rsec<<"s"
                <<std::flush;
        }
}


void G4IDSEventAction::EndOfEventAction(const G4Event* anEvent)
{
    G4int nb_ClKU	= G4IDS_DC -> GetNbClKU();				nb_ClKU	    = 		GLOB_nb_ClKU;
    G4int nb_ClBuch	= G4IDS_DC -> GetNbClBuch();			nb_ClBuch   = 		GLOB_nb_ClBuch;	 
    G4int nb_LaBr3	= G4IDS_DC -> GetNbLaBr3();				nb_LaBr3    = 		GLOB_nb_LaBr3;	 
    G4int nb_FPlastic;										nb_FPlastic = 		GLOB_nb_FPlastic;	 
    G4int nb_FrontPlasticKU;								nb_FrontPlasticKU = 	GLOB_nb_FrontPlasticKU;	 
    G4int nb_LeftPlasticKU;									nb_LeftPlasticKU  = 	GLOB_nb_LeftPlasticKU;	 
    G4int nb_RightPlasticKU;								nb_RightPlasticKU = 	GLOB_nb_RightPlasticKU;	 
    G4int nb_VetoPlastic;								nb_VetoPlastic = 	GLOB_nb_VetoPlastic;	 

    G4int event_id = anEvent->GetEventID();
 
    G4int mult = 0;
    
    G4HCofThisEvent* HCE = anEvent->GetHCofThisEvent();
    G4SDManager* SDman = G4SDManager::GetSDMpointer();

    evNb = anEvent->GetEventID();

    if(!HCE) return;



/*************************************************************************************
 *
 *                               LaBr3 Detector
 *
 *********************************** START *******************************************/
// Initialisation of the ROOT Tree branches
for(int lb=0; lb<G4IDS_DC->GetNbLaBr3(); lb++){
  LaBr3_En[lb] =0;
}

if(0!=nb_LaBr3){
    LaBr3HitsCollection* LaBr3_HC;
    for(int lb=0; lb<G4IDS_DC->GetNbLaBr3(); lb++){
      if(HCE){
        LaBr3_HC = (LaBr3HitsCollection*)(HCE->GetHC(SDman->GetCollectionID(Form("LaBr3_SD_%i/LaBr3", lb))));
      }
      fNPoints_lb = LaBr3_HC->entries();
      for(int i=0; i<fNPoints_lb; i++){
        LaBr3_En[lb] +=  (*LaBr3_HC)[i]->GetEdep();
      }
      if(LaBr3_En[lb] > 0) mult++;
    }
    // Resolution
    for( int lb=0; lb<G4IDS_DC->GetNbLaBr3(); lb++ ){
      if(LaBr3_En[lb]<=0) continue;
//      LaBr3_En[lb] = gRandom->Gaus(LaBr3_En[lb], 0.005*LaBr3_En[lb]);
      LaBr3_En[lb] = gRandom->Gaus(LaBr3_En[lb],(0.00462*LaBr3_En[lb] + 5.756*keV)/2.3548);	// realistic FWHM - 2keV @ 1MeV for Ge
      LaBr3_En[lb] = LaBr3_En[lb]/keV; // calibration in keV
    }
}    
/**************************************** STOP ***************************************
 *
 *                                 LaBr3 Detector
 *
 *************************************************************************************/
 
 
 
 
 
 
 
 
/*************************************************************************************
 *
 *                		 Clover KULeuven
 *
 *********************************** START *******************************************/
// Initialisation of the ROOT Tree branches
for(int cl = 0; cl<G4IDS_DC->GetNbClKU() ; cl++){
  for(int cr = 0 ; cr<4 ; cr++){
    Cl_Cr_KU_En[cl][cr]=0.;
    Cl_Cr_KU_EnAb[cl][cr]=0.;
  }
}

if(0!=nb_ClKU){
    CloverSingleHitsCollection* ClKU_HC;
    int NbCrAb=0;
    double EnCrAb=0.;
    for(int cl=0; cl<G4IDS_DC->GetNbClKU();cl++){
      NbCrAb=0;
      EnCrAb=0.;

      for(int cr = 0 ; cr<4 ; cr++){
        if(HCE){
          ClKU_HC = (CloverSingleHitsCollection*)(HCE->GetHC(SDman->GetCollectionID(Form("Clover%i_Crystal%i_SD/CloverSingle",cl,cr))));
        }
        fNPoints_KU = ClKU_HC->entries();

        for(int i=0; i<fNPoints_KU; i++){
          Cl_Cr_KU_En[cl][cr] += (*ClKU_HC)[i]->GetEdep();
          }
          if(Cl_Cr_KU_En[cl][cr] > 0) {
            mult++;
            Cl_Cr_KU_En[cl][cr] = gRandom->Gaus(Cl_Cr_KU_En[cl][cr],(0.000462*Cl_Cr_KU_En[cl][cr] + 1.056*keV)/2.3548);	// realistic FWHM - 2keV @ 1MeV for Ge
            Cl_Cr_KU_En[cl][cr] = Cl_Cr_KU_En[cl][cr]/keV;  // calibration in keV
            EnCrAb += Cl_Cr_KU_En[cl][cr];
          }
      }
      
      // Checking which crystal has maximum energy deposit
      for (int cr = 0 ; cr<4 ; cr++) {
        if(Cl_Cr_KU_En[cl][cr] > Cl_Cr_KU_En[cl][NbCrAb])
          NbCrAb = cr;
        }
      
      Cl_Cr_KU_EnAb[cl][NbCrAb] = EnCrAb;
      
    }

}
/**************************************** STOP ***************************************
 *
 *                 		    Clover KULeuven
 *
 *************************************************************************************/
 
 
 
 
 
 
/*************************************************************************************
 *
 *                		 Clover Bucharest
 *
 *********************************** START *******************************************/
// Initialisation of the ROOT Tree branches
for(int cl = 0; cl<G4IDS_DC->GetNbClBuch() ; cl++){
  for(int cr = 0 ; cr<4 ; cr++){
    Cl_Cr_Buch_En[cl][cr]=0.;
    Cl_Cr_Buch_EnAb[cl][cr]=0.;
  }
}

if(0!=nb_ClBuch){
    CloverSingleBuchHitsCollection* ClBuch_HC;
    int NbCrAb=0;
    double EnCrAb=0.;
    for(int cl=0; cl<G4IDS_DC->GetNbClBuch();cl++){

      NbCrAb=0;
      EnCrAb=0.;
      
      for(int cr = 0 ; cr<4 ; cr++){
        if(HCE){
          ClBuch_HC = (CloverSingleBuchHitsCollection*)(HCE->GetHC(SDman->GetCollectionID(Form("Clover%i_Crystal%i_Buch_SD/CloverSingleBuch",cl,cr))));
       }
        fNPoints_Buch = ClBuch_HC->entries();

      for(int i=0; i<fNPoints_Buch; i++){
        Cl_Cr_Buch_En[cl][cr] += (*ClBuch_HC)[i]->GetEdep();
        }
        if(Cl_Cr_Buch_En[cl][cr] > 0) {
          mult++;
          Cl_Cr_Buch_En[cl][cr] = gRandom->Gaus(Cl_Cr_Buch_En[cl][cr],(0.000462*Cl_Cr_Buch_En[cl][cr] + 1.056*keV)/2.3548);	// FWHM - 2keV @ 1MeV for Ge
          Cl_Cr_Buch_En[cl][cr] = Cl_Cr_Buch_En[cl][cr]/keV;
          EnCrAb += Cl_Cr_Buch_En[cl][cr];
        }
        
      }
      
       // Checking which crystal has maximum energy deposit
      for (int cr = 0 ; cr<4 ; cr++) {
        if(Cl_Cr_Buch_En[cl][cr] > Cl_Cr_Buch_En[cl][NbCrAb])
          NbCrAb = cr;
        }
      
      Cl_Cr_Buch_EnAb[cl][NbCrAb] = EnCrAb;
           
    }
    
}
/**************************************** STOP ***************************************
 *
 *                 		    Clover Bucharest
 *
 *************************************************************************************/
/*************************************************************************************
 *
 *                		 Fast Plastic
 *
 *********************************** START *******************************************/
// Initialisation of the ROOT Tree branch
FPlastic_En=0.;

if(0!=nb_FPlastic){
    FastPlasticHitsCollection* FPlastic_HC;
    if(HCE){
      FPlastic_HC = (FastPlasticHitsCollection*)(HCE->GetHC(SDman->GetCollectionID("FastPlastic_SD/FastPlastic")));
      //G4cout<<"FastPlastic_SD/FastPlastic"<<G4endl;
    }
    fNPoints_FPlastic = FPlastic_HC->entries();
//    if(ClBuch_HC->entries() >0){
//    	G4cout<<"fNPoints_Buch = "<<fNPoints_Buch<<G4endl;
//    	G4cout<<"ClBuch_HC->entries() = "<<ClBuch_HC->entries()<<G4endl;
//        G4cout<<Form("Clover%i_Crystal%i_Buch_SD/CloverSingleBuch",cl,cr)<<G4endl;
//    }
    for(int i=0; i<fNPoints_FPlastic; i++){
      FPlastic_En += (*FPlastic_HC)[i]->GetEdep();
    }
    if(FPlastic_En > 0) mult++;

    if(0 < FPlastic_En){
      FPlastic_En = gRandom->Gaus(FPlastic_En,0.00128*FPlastic_En);	// FWHM - 3keV @ 1MeV for Ge
    }
}
/**************************************** STOP ***************************************
 *
 *                 		    Fast Plastic
 *
 *************************************************************************************/
/*************************************************************************************
 *
 *                		 Front Plastic (KU Leuven)
 *
 *********************************** START *******************************************/
// Initialisation of the ROOT Tree branch
FrontPlasticKU_En=0.;

if(0!=nb_FrontPlasticKU){
    FrontPlasticKUHitsCollection* FrontPlasticKU_HC;
    if(HCE){
      FrontPlasticKU_HC = (FrontPlasticKUHitsCollection*)(HCE->GetHC(SDman->GetCollectionID("FrontPlasticKU_SD/FrontPlasticKU")));
      //G4cout<<"FrontPlasticKU_SD/FrontPlasticKU"<<G4endl;
    }
    fNPoints_FrontPlasticKU = FrontPlasticKU_HC->entries();
//    if(ClBuch_HC->entries() >0){
//    	G4cout<<"fNPoints_Buch = "<<fNPoints_Buch<<G4endl;
//    	G4cout<<"ClBuch_HC->entries() = "<<ClBuch_HC->entries()<<G4endl;
//        G4cout<<Form("Clover%i_Crystal%i_Buch_SD/CloverSingleBuch",cl,cr)<<G4endl;
//    }
    for(int i=0; i<fNPoints_FrontPlasticKU; i++){
      FrontPlasticKU_En += (*FrontPlasticKU_HC)[i]->GetEdep();
    }
    if(FrontPlasticKU_En > 0) mult++;

    if(0 < FrontPlasticKU_En){
      FrontPlasticKU_En = gRandom->Gaus(FrontPlasticKU_En,0.00128*FrontPlasticKU_En);	// FWHM - 3keV @ 1MeV for Ge
    }
}
/**************************************** STOP ***************************************
 *
 *                 		    Front Plastic (KU Leuven)
 *
 *************************************************************************************/
/*************************************************************************************
 *
 *                		 Left Plastic (KU Leuven)
 *
 *********************************** START *******************************************/
// Initialisation of the ROOT Tree branch
LeftPlasticKU_En=0.;

if(0!=nb_LeftPlasticKU){
    LeftPlasticKUHitsCollection* LeftPlasticKU_HC;
    if(HCE){
      LeftPlasticKU_HC = (LeftPlasticKUHitsCollection*)(HCE->GetHC(SDman->GetCollectionID("LeftPlasticKU_SD/LeftPlasticKU")));
      //G4cout<<"LeftPlasticKU_SD/LeftPlasticKU"<<G4endl;
    }
    fNPoints_LeftPlasticKU = LeftPlasticKU_HC->entries();
//    if(ClBuch_HC->entries() >0){
//    	G4cout<<"fNPoints_Buch = "<<fNPoints_Buch<<G4endl;
//    	G4cout<<"ClBuch_HC->entries() = "<<ClBuch_HC->entries()<<G4endl;
//        G4cout<<Form("Clover%i_Crystal%i_Buch_SD/CloverSingleBuch",cl,cr)<<G4endl;
//    }
    for(int i=0; i<fNPoints_LeftPlasticKU; i++){
      LeftPlasticKU_En += (*LeftPlasticKU_HC)[i]->GetEdep();
    }
    if(LeftPlasticKU_En > 0) mult++;
    
    if(0 < LeftPlasticKU_En){
      LeftPlasticKU_En = gRandom->Gaus(LeftPlasticKU_En,0.00128*LeftPlasticKU_En);	// FWHM - 3keV @ 1MeV for Ge
    }
}
/**************************************** STOP ***************************************
 *
 *                 		    Left Plastic (KU Leuven)
 *
 *************************************************************************************/
/*************************************************************************************
 *
 *                		 Right Plastic (KU Leuven)
 *
 *********************************** START *******************************************/
// Initialisation of the ROOT Tree branch
RightPlasticKU_En=0.;

if(0!=nb_RightPlasticKU){
    RightPlasticKUHitsCollection* RightPlasticKU_HC;
    if(HCE){
      RightPlasticKU_HC = (RightPlasticKUHitsCollection*)(HCE->GetHC(SDman->GetCollectionID("RightPlasticKU_SD/RightPlasticKU")));
      //G4cout<<"RightPlasticKU_SD/RightPlasticKU"<<G4endl;
    }
    fNPoints_RightPlasticKU = RightPlasticKU_HC->entries();
//    if(ClBuch_HC->entries() >0){
//    	G4cout<<"fNPoints_Buch = "<<fNPoints_Buch<<G4endl;
//    	G4cout<<"ClBuch_HC->entries() = "<<ClBuch_HC->entries()<<G4endl;
//        G4cout<<Form("Clover%i_Crystal%i_Buch_SD/CloverSingleBuch",cl,cr)<<G4endl;
//    }
    for(int i=0; i<fNPoints_RightPlasticKU; i++){
      RightPlasticKU_En += (*RightPlasticKU_HC)[i]->GetEdep();
    }
    if(RightPlasticKU_En > 0) mult++;
    
    if(0 < RightPlasticKU_En){
      RightPlasticKU_En = gRandom->Gaus(RightPlasticKU_En,0.00128*RightPlasticKU_En);	// FWHM - 3keV @ 1MeV for Ge
    }
}
/**************************************** STOP ***************************************
 *
 *                 		    Left Plastic (KU Leuven)
 *
 *************************************************************************************/




/*************************************************************************************
 *
 *                               Veto Plastic
 *
 *********************************** START *******************************************/
// Initialisation of the ROOT Tree branches
for(int vp=0; vp<G4IDS_DC->GetNbVetoPlastic(); vp++){
  VetoPlastic_En[vp] =0;
}

if(0!=nb_VetoPlastic){
    VetoPlasticHitsCollection* VetoPlastic_HC;
    for(int vp=0; vp<G4IDS_DC->GetNbVetoPlastic(); vp++){
      if(HCE){
        VetoPlastic_HC = (VetoPlasticHitsCollection*)(HCE->GetHC(SDman->GetCollectionID(Form("VetoPlastic_SD_%i/VetoPlastic", vp))));
      }
      fNPoints_VetoPlastic = VetoPlastic_HC->entries();
      for(int i=0; i<fNPoints_VetoPlastic; i++){
        VetoPlastic_En[vp] +=  (*VetoPlastic_HC)[i]->GetEdep();
      }
      if(VetoPlastic_En[vp] > 0) mult++;
    }
    // Resolution and Calibration
    for( int vp=0; vp<G4IDS_DC->GetNbVetoPlastic(); vp++ ){
      if(VetoPlastic_En[vp]<=0) continue;
      //VetoPlastic_En[vp] = gRandom->Gaus(VetoPlastic_En[vp], (0.005*VetoPlastic_En[vp] + 5.*keV)/2.3548);
      VetoPlastic_En[vp] = VetoPlastic_En[vp]/keV; // calibration in keV
     }
}    
/**************************************** STOP ***************************************

 *
 *************************************************************************************/
 
 
 
 
 




 
      if( mult > 0 ) fTree->Fill(); 



}


//////   void G4IDSEventAction::SetSaveThreshold(G4int save)
//////   {
//////   
//////   }
//////   
//////   G4double G4IDSEventAction::Interpolator(G4double x, int size, G4double *ArrayX, G4double *ArrayY)
//////   
//////   {
//////   double value=0.;
//////   x=log(x);
//////   int idx=0;
//////   if (x < ArrayX[0] || x > ArrayX[size-1]) {
//////   	return value;
//////   }
//////   else {
//////   	while (x > ArrayX[idx]) {idx++;}
//////   	value=ArrayY[idx-1] + (x-ArrayX[idx-1])*(ArrayY[idx]-ArrayY[idx-1])/(ArrayX[idx]-ArrayX[idx-1]);
//////   }
//////   return exp(value);
//////   }
