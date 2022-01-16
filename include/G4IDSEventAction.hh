#ifndef G4IDSEventAction_h
#define G4IDSEventAction_h 1

#include "globals.hh"
#include "G4UserEventAction.hh"
#include "G4Run.hh"
#include "G4Event.hh"
#include "G4Track.hh"
#include "G4TrajectoryContainer.hh"
#include "G4SteppingManager.hh"
#include "G4SteppingVerbose.hh"
#include "tndge_SteppingVerbose.hh"
#include "G4IDSPrimaryGeneratorAction.hh"
#include "G4IDSDetectorConstruction.hh"
#include "G4SDManager.hh"
#include "G4THitsCollection.hh"
#include "G4HCofThisEvent.hh"
#include "G4Timer.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"

#include "TTimeStamp.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TKey.h"
#include "TArrayD.h"
#include "TArrayI.h"
#include "TH1F.h"
#include "TRandom2.h"

#include "tndge_TrackerHit.hh"
#include "tndge_TrackingAction.hh"
#include "tndge_TrackerSD.hh"
#include "LaBr3Hit.hh"
#include "LaBr3TrackingAction.hh"
#include "LaBr3SensitiveDetector.hh"
#include "FastPlasticHit.hh"
#include "FastPlasticTrackingAction.hh"
#include "FastPlasticSD.hh"
#include "FrontPlasticKUHit.hh"
#include "FrontPlasticKUTrackingAction.hh"
#include "FrontPlasticKUSD.hh"
#include "LeftPlasticKUHit.hh"
#include "LeftPlasticKUTrackingAction.hh"
#include "LeftPlasticKUSD.hh"
#include "RightPlasticKUHit.hh"
#include "RightPlasticKUTrackingAction.hh"
#include "RightPlasticKUSD.hh"
#include "CloverSingleHit.hh"
#include "CloverSingleSD.hh"
#include "CloverSingleTrackingAction.hh"
#include "CloverSingleBuchHit.hh"
#include "CloverSingleBuchSD.hh"
#include "CloverSingleBuchTrackingAction.hh"
#include "VetoPlasticHit.hh"
#include "VetoPlasticTrackingAction.hh"
#include "VetoPlasticSD.hh"


class G4Event;

class G4IDSEventAction : public G4UserEventAction
{
public:
	G4IDSEventAction(G4IDSDetectorConstruction* p_G4IDS_DC, G4String p_fFileName);
	//G4IDSEventAction();
	~G4IDSEventAction();

public:
	void BeginOfEventAction(const G4Event*);
	void EndOfEventAction(const G4Event*);
	//void SetSaveThreshold(G4int save);
	//void SetEventVerbose(G4int v){fVerbose=v;}
	//G4double Interpolator(G4double x, int size, G4double *ArrayX, G4double *ArrayY) ;
        //void GetNbLaBr3(G4IDSDetectorConstruction*);

// private:
	//G4int				fEdep[1000];
	//G4int				fSaveThreshold;
	//G4int				fVerbose;
	G4IDSDetectorConstruction*	G4IDS_DC;


// TTree...
	int		current_det_nb, crys_nb; 
	double		Cl_Cr_En[4][4];
	
	double**	Cl_Cr_KU_En;
	double**	Cl_Cr_Buch_En;
	double**	Cl_Cr_KU_EnAb;
	double**	Cl_Cr_Buch_EnAb;
	double*		LaBr3_En;
	double*		VetoPlastic_En;
	double		FPlastic_En;
	double		FrontPlasticKU_En;
	double		LeftPlasticKU_En;
	double		RightPlasticKU_En;
    
	

	int		fNPoints;	
	int		fNPoints_lb;	
	int		fNPoints_KU;	
	int		fNPoints_Buch;	
	int		fNPoints_FPlastic;
	int		fNPoints_FrontPlasticKU;
	int		fNPoints_LeftPlasticKU;
	int		fNPoints_RightPlasticKU;
	int		fNPoints_VetoPlastic;	
	G4int		evNb; 


// ROOT data saving stuff
	static TFile		*fRootFile;
	static TTree		*fTree;
	TString			fFileName;
	
};

#endif
