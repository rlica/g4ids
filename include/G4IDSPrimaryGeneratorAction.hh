
#ifndef G4IDSPrimaryGeneratorAction_h
#define G4IDSPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "globals.hh"
#include "G4Event.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"
#include "G4RandomDirection.hh"
#include "Randomize.hh"

#include "TArrayD.h"
#include <TRandom2.h>
#include <TF1.h>
#include "TGraph2D.h"
#include "TH2D.h"

#include <stdlib.h>
#include <cmath>

class G4ParticleGun;
class G4Event;


class G4IDSPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{

  public:
    G4IDSPrimaryGeneratorAction(G4String p_fFileName);
    ~G4IDSPrimaryGeneratorAction();


  public:
    void GeneratePrimaries	(G4Event* anEvent);
    void isom38Cl			(G4Event* anEvent);
    void gs38Cl				(G4Event* anEvent);
    void gs41Ar				(G4Event* anEvent);
    void Europium152 		(G4Event* anEvent);
    void Barium133   		(G4Event* anEvent);
    void Bismuth207  		(G4Event* anEvent);
	void GenericSource 		(G4Event* anEvent);
	
//  private:
//    G4ParticleGun		*particleGun;
//  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
//  G4String particleName;
  
  
  
	TF1*			dNdBeta_41Ar; 
	TF1*			dNdBeta_is38Cl; 
	TF1*			dNdBeta_gs38Cl; 
	TF1*			dNdBeta_gs38Cl2;
	double			beta_en; 
	double 			r1,
				r2,	// uniform distributed in (0,1)
				ro,
				psi,	// 
				y,
				z,
				y0,
				z0,
				x_foil;
//	double			p0, p1, p2, p3, p4, p5, p6;
//	TF1*			y_distrib; 	// function to approximate Y distribution on XY detector
//	TFile*			rootfile;
//	TTree*			tree;
	float			X_in,
				Y_in,
				Z_in;

    private:
	G4String fFileName;

};

#endif
