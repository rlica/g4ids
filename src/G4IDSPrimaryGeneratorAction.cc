#include "global.hh"
#include "G4IDSPrimaryGeneratorAction.hh"
#include "G4IDSCounter.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

using namespace std;

  G4int n_particle;
  G4ParticleGun* particleGun;
  G4ParticleTable* particleTable;
  G4String particleName;

  G4IDSCounter events;


//  isom_38Cl  :::::::::::::::::::::::::::::::
  G4IDSCounter N_beta, gamma_671, gamma_106, gamma_669, gamma_775,
  	      gamma_1642, gamma_2167, gamma_1293; 
//  ::::::::::::::::::::::::::::::::::::::


//  133Ba  :::::::::::::::::::::::::::::::
  G4IDSCounter gamma_53, gamma_79, gamma_80, gamma_160, gamma_223,
  	      gamma_276, gamma_302, gamma_356, gamma_383, 
	      elec_53, elec_79, elec_80, elec_160; 
//  ::::::::::::::::::::::::::::::::::::::


//  152Eu  :::::::::::::::::::::::::::::::
  G4IDSCounter gamma_121, gamma_244, gamma_295, gamma_344, gamma_367, gamma_411, 
  	      gamma_443, gamma_678, gamma_688, gamma_778, gamma_810, gamma_867,
	      gamma_964, gamma_1005, gamma_1085, gamma_1089, gamma_1112, gamma_1249,
	      gamma_1299, gamma_1408; 
//  ::::::::::::::::::::::::::::::::::::::


//  207Bi  :::::::::::::::::::::::::::::::
  G4IDSCounter gamma_328, gamma_569, gamma_897, gamma_1063,
  	      gamma_1442, gamma_1770,
	      elec_481, elec_553, elec_565, 
	      elec_975, elec_1047, elec_1059, 
	      XrK_72_8keV, XrK_74_9keV, XrK_84_4keV, XrK_84_9keV, XrK_87_3keV, XrL_10_6keV;

//  32Al  :::::::::::::::::::::::::::::::
  G4IDSCounter gamma_222;
  G4IDSCounter gamma_735; 
  G4IDSCounter elec_222; 
//  ::::::::::::::::::::::::::::::::::::::


//  Generic Source :::::::::::::::::::::::::::::::
  G4IDSCounter 	generic_10, 
				generic_30, 
				generic_60, 
				generic_80, 
				generic_100, 
				generic_120, 
				generic_170, 
				generic_220, 
				generic_300, 
				generic_400, 
				generic_600, 
				generic_800, 
				generic_1000, 
				generic_1200, 
				generic_1600, 
				generic_2000, 
				generic_2800, 
				generic_4000,
				generic_5000, 
				generic_7000, 
				generic_9000;
//  ::::::::::::::::::::::::::::::::::::::

G4IDSCounter gamma_mono[100], elec_rand[100]; 



G4IDSPrimaryGeneratorAction::G4IDSPrimaryGeneratorAction(G4String p_fFileName)
	:fFileName(p_fFileName)
{

  n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);
  particleTable = G4ParticleTable::GetParticleTable();

  	G4int seed=CLHEP::HepRandom::getTheSeed();
	cout<<"\n\n\t *** OLD seed = " << seed << "\n\n" ;


	time_t systime = time(NULL);
	long Nseed = (long) systime;
	CLHEP::HepRandom::setTheSeed(Nseed);
	cout<<"\n\n\t *** NEW seed = " << Nseed << "\n\n" ;


//___total_nb_of_events:::::___________
  events.InitialiseCounter(0);


//______isom_38Cl__________________________
  N_beta.InitialiseCounter(0);	
  gamma_671.InitialiseCounter(0);	
  gamma_106.InitialiseCounter(0);	
  gamma_669.InitialiseCounter(0);	
  gamma_775.InitialiseCounter(0);
  gamma_1642.InitialiseCounter(0);
  gamma_2167.InitialiseCounter(0);
  gamma_1293.InitialiseCounter(0);


/*
//______133Ba__________________________
  gamma_53.InitialiseCounter(0);		elec_53.InitialiseCounter(0);
  gamma_79.InitialiseCounter(0);		elec_79.InitialiseCounter(0);
  gamma_80.InitialiseCounter(0);		elec_80.InitialiseCounter(0);
  gamma_160.InitialiseCounter(0);		elec_160.InitialiseCounter(0);
  gamma_223.InitialiseCounter(0);
  gamma_276.InitialiseCounter(0);
  gamma_302.InitialiseCounter(0);
  gamma_356.InitialiseCounter(0);
  gamma_383.InitialiseCounter(0);
//_____________________________________
*/


//______152Eu__________________________
  gamma_121.InitialiseCounter(0);
  gamma_244.InitialiseCounter(0);
  gamma_295.InitialiseCounter(0);
  gamma_344.InitialiseCounter(0);	// from Gd - level 1 to level 0 (g.s.)
  gamma_367.InitialiseCounter(0);	// from Gd - level 7 to level 3
  gamma_411.InitialiseCounter(0);	// from Gd - level 3 to level 1
  gamma_443.InitialiseCounter(0);
  gamma_678.InitialiseCounter(0);	// from Gd - level 11 to level 3
  gamma_688.InitialiseCounter(0);
  gamma_778.InitialiseCounter(0);	// from Gd - level 7 to level 1
  gamma_810.InitialiseCounter(0);
  gamma_867.InitialiseCounter(0);
  gamma_964.InitialiseCounter(0);
  gamma_1005.InitialiseCounter(0);
  gamma_1085.InitialiseCounter(0);
  gamma_1089.InitialiseCounter(0);	// from Gd - level 11 to level 1
  gamma_1112.InitialiseCounter(0);
  gamma_1249.InitialiseCounter(0);
  gamma_1299.InitialiseCounter(0);	// from Gd - level 14 to level 1
  gamma_1408.InitialiseCounter(0);
//_____________________________________  


/*
//______207Bi__________________________
  gamma_328.InitialiseCounter(0);		elec_481.InitialiseCounter(0);
  gamma_569.InitialiseCounter(0);		elec_553.InitialiseCounter(0);
  gamma_897.InitialiseCounter(0);		elec_565.InitialiseCounter(0);
  gamma_1063.InitialiseCounter(0);		elec_975.InitialiseCounter(0);
  gamma_1442.InitialiseCounter(0);		elec_1047.InitialiseCounter(0);
  gamma_1770.InitialiseCounter(0);		elec_1059.InitialiseCounter(0);
  XrK_72_8keV.InitialiseCounter(0);
  XrK_74_9keV.InitialiseCounter(0);
  XrK_84_4keV.InitialiseCounter(0);
  XrK_84_9keV.InitialiseCounter(0);
  XrK_87_3keV.InitialiseCounter(0);
  XrL_10_6keV.InitialiseCounter(0);
//_____________________________________


//______32Al___________________________
  gamma_222.InitialiseCounter(0);
  gamma_735.InitialiseCounter(0);
  elec_222.InitialiseCounter(0);
//_____________________________________
*/


//______Generic Source__________________________
  generic_10.InitialiseCounter(0);
  generic_30.InitialiseCounter(0);
  generic_60.InitialiseCounter(0);
  generic_80.InitialiseCounter(0);	
  generic_100.InitialiseCounter(0);	
  generic_120.InitialiseCounter(0);	
  generic_170.InitialiseCounter(0);
  generic_220.InitialiseCounter(0);	
  generic_300.InitialiseCounter(0);
  generic_400.InitialiseCounter(0);	
  generic_600.InitialiseCounter(0);
  generic_800.InitialiseCounter(0);
  generic_1000.InitialiseCounter(0);
  generic_1200.InitialiseCounter(0);
  generic_1600.InitialiseCounter(0);
  generic_2000.InitialiseCounter(0);
  generic_2800.InitialiseCounter(0);
  generic_4000.InitialiseCounter(0);
  generic_5000.InitialiseCounter(0);
  generic_7000.InitialiseCounter(0);
  generic_9000.InitialiseCounter(0);
//_____________________________________  


//  gamma_mono.InitialiseCounter(0);
//  elec_rand.InitialiseCounter(0);



/*
// parameters to approximate XY distribution of 32Al beam
  p0 = 7.10999e+02; 
  p1 = -2.79622e+04; 
  p2 = 5.25298e+04; 
  p3 = 5.39627e+00; 
  p4 = 4.35843e+00; 
  p5 = 3.70781e+04; 
  p6 = 1.44125e+01; 
*/

/*
rootfile = new TFile("positions.root","recreate");	
rootfile->cd();
	tree = new TTree("positions","positions");
	tree -> Branch ("X_in"		,&X_in  ,"X_in/F"	); 
	tree -> Branch ("Y_in"		,&Y_in  ,"Y_in/F"	); 
	tree -> Branch ("Z_in"		,&Z_in  ,"Z_in/F"	); 


y_distrib = new TF1( "y_distrib",
	" 7.10999e+02*x+-2.79622e+04+5.25298e+04*exp(-0.5*((x-5.39627e+00)/4.35843e+00)**2)+3.70781e+04*exp(-0.5*((x-1.44125e+01)/4.35843e+00)**2) ",
	1., 19. );		// shape of Y distribution on XY detector 
*/

/*
  dNdBeta_41Ar   = new TF1("dNdBeta_41Ar"   , "sqrt(x*x+2*x*511)*(1200-x)*(1200-x)*(x+511) ", 0, 1200 );
  dNdBeta_is38Cl = new TF1("dNdBeta_is38Cl" , "sqrt(x*x+2*x*511)*(1100-x)*(1100-x)*(x+511) ", 0, 1100 );
  dNdBeta_gs38Cl = new TF1("dNdBeta_gs38Cl" , "sqrt(x*x+2*x*511)*(4900-x)*(4900-x)*(x+511) ", 0, 4900 );
  dNdBeta_gs38Cl2= new TF1("dNdBeta_gs38Cl2", "sqrt(x*x+2*x*511)*(2700-x)*(2700-x)*(x+511) ", 0, 2700 );
*/

}


G4IDSPrimaryGeneratorAction::~G4IDSPrimaryGeneratorAction()
{
//	rootfile->cd();
//	tree->Write();	rootfile->Close();


  cout<<"\n\n\t CLOSING THE PrimaryGeneratorAction() \n\n"<<flush; 
  cout<<"\n\n\t Output written in "<< fFileName.c_str() << "\n"<<flush; 
  cout<<"\n\n\t Check "<< fFileName.c_str() << ".txt for Counter values\n\n"<<flush; 
  
  freopen(Form("%s.txt",fFileName.c_str()),"w",stdout);
 
  cout << "\n\nnumber of events: " << events.GetCounterValue() <<"\n\n";

for (int i = 0; i<GLOB_source_nb; i++) {


/*
// isom_38Cl:::::::::::_______________________________________________________
<< "from fus-evap 36S ( 7Li, X ) Y  :::::::::::::::::::::::\n"
  	 << "\ttotal betas:::   " << N_beta.GetCounterValue()     <<"\n"
	 << "\tgamma 671keV:::  " << gamma_671.GetCounterValue()  <<"\n"
	 << "\tgamma 106keV:::  " << gamma_106.GetCounterValue()  <<"\n"
	 << "\tgamma 669keV::   " << gamma_669.GetCounterValue()  <<"\n"
	 << "\tgamma 775keV::   " << gamma_775.GetCounterValue()  <<"\n"
	 << "\tgamma 1642keV::  " << gamma_1642.GetCounterValue() <<"\n"
	 << "\tgamma 2167keV::  " << gamma_2167.GetCounterValue() <<"\n"
	 << "\tgamma 1293keV::  " << gamma_1293.GetCounterValue() <<"\n\n\n"; 
*/
/*
// 133Ba:::::::::::_______________________________________________________
<< "from 133Ba decay:::::::::::::::::::::::\n"
  	 << "\tgamma 53keV:::  " <<  gamma_53.GetCounterValue() <<"\n"
	 << "\tgamma 79keV:::  " <<  gamma_79.GetCounterValue() <<"\n"
	 << "\tgamma 80keV:::  " <<  gamma_80.GetCounterValue() <<"\n"
	 << "\tgamma 160keV::  " << gamma_160.GetCounterValue() <<"\n"
	 << "\tgamma 223keV::  " << gamma_223.GetCounterValue() <<"\n"
	 << "\tgamma 276keV::  " << gamma_276.GetCounterValue() <<"\n"
	 << "\tgamma 302keV::  " << gamma_302.GetCounterValue() <<"\n"
	 << "\tgamma 356keV::  " << gamma_356.GetCounterValue() <<"\n"
	 << "\tgamma 383keV::  " << gamma_383.GetCounterValue() <<"\n\n"		
*/


if (GLOB_source_type[i] == 1) {
// 152Eu::::::::::________________________________________________________
cout << "from 152Eu decay:::::::::::::::::::::::\n"
  	 << "\tgamma 121keV:::  " <<  gamma_121.GetCounterValue() <<"\n"
	 << "\tgamma 244keV:::  " <<  gamma_244.GetCounterValue() <<"\n"
	 << "\tgamma 295keV:::  " <<  gamma_295.GetCounterValue() <<"\n"
	 << "\tgamma 344keV:::  " <<  gamma_344.GetCounterValue() <<"\n"
	 << "\tgamma 367keV:::  " <<  gamma_367.GetCounterValue() <<"\n"
	 << "\tgamma 411keV:::  " <<  gamma_411.GetCounterValue() <<"\n"
	 << "\tgamma 443keV:::  " <<  gamma_443.GetCounterValue() <<"\n"
	 << "\tgamma 678keV:::  " <<  gamma_678.GetCounterValue() <<"\n"
	 << "\tgamma 688keV:::  " <<  gamma_688.GetCounterValue() <<"\n"
	 << "\tgamma 778keV:::  " <<  gamma_778.GetCounterValue() <<"\n"
	 << "\tgamma 810keV:::  " <<  gamma_810.GetCounterValue() <<"\n"
	 << "\tgamma 867keV:::  " <<  gamma_867.GetCounterValue() <<"\n"
	 << "\tgamma 964keV:::  " <<  gamma_964.GetCounterValue() <<"\n"
	 << "\tgamma 1005keV::  " << gamma_1005.GetCounterValue() <<"\n"
	 << "\tgamma 1085keV::  " << gamma_1085.GetCounterValue() <<"\n"
	 << "\tgamma 1089keV::  " << gamma_1089.GetCounterValue() <<"\n"
	 << "\tgamma 1112keV::  " << gamma_1112.GetCounterValue() <<"\n"
	 << "\tgamma 1249keV::  " << gamma_1249.GetCounterValue() <<"\n"
	 << "\tgamma 1299keV::  " << gamma_1299.GetCounterValue() <<"\n"
	 << "\tgamma 1408keV::  " << gamma_1408.GetCounterValue() <<"\n\n";
}
if (GLOB_source_type[i] == 2) {
// Generic Source::::::::::________________________________________________________
cout << "from Generic Source decay:::::::::::::::::::::::\n"
  	 << "\tgamma 10   keV:::  " <<  generic_10.GetCounterValue() <<"\n"
	 << "\tgamma 30   keV:::  " <<  generic_30.GetCounterValue() <<"\n"
	 << "\tgamma 60   keV:::  " <<  generic_60.GetCounterValue() <<"\n"
	 << "\tgamma 80   keV:::  " <<  generic_80.GetCounterValue() <<"\n"
	 << "\tgamma 100  keV:::  " <<  generic_100.GetCounterValue() <<"\n"
	 << "\tgamma 120  keV:::  " <<  generic_120.GetCounterValue() <<"\n"
	 << "\tgamma 170  keV:::  " <<  generic_170.GetCounterValue() <<"\n"
	 << "\tgamma 220  keV:::  " <<  generic_220.GetCounterValue() <<"\n"
	 << "\tgamma 300  keV:::  " <<  generic_300.GetCounterValue() <<"\n"
	 << "\tgamma 400  keV:::  " <<  generic_400.GetCounterValue() <<"\n"
	 << "\tgamma 600  keV:::  " <<  generic_600.GetCounterValue() <<"\n"
	 << "\tgamma 800  keV:::  " <<  generic_800.GetCounterValue() <<"\n"
	 << "\tgamma 1000 keV:::  " <<  generic_1000.GetCounterValue() <<"\n"
	 << "\tgamma 1200 keV:::  " <<  generic_1200.GetCounterValue() <<"\n"
	 << "\tgamma 1600 keV:::  " <<  generic_1600.GetCounterValue() <<"\n"
	 << "\tgamma 2000 keV:::  " <<  generic_2000.GetCounterValue() <<"\n"
	 << "\tgamma 2800 keV:::  " <<  generic_2800.GetCounterValue() <<"\n"
	 << "\tgamma 4000 keV:::  " <<  generic_4000.GetCounterValue() <<"\n"
	 << "\tgamma 5000 keV:::  " <<  generic_5000.GetCounterValue() <<"\n"
 	 << "\tgamma 7000 keV:::  " <<  generic_7000.GetCounterValue() <<"\n"
	 << "\tgamma 9000 keV:::  " <<  generic_9000.GetCounterValue() <<"\n\n";
}
	
/*
// 207Bi:::::::::::_______________________________________________________
<< "from 207Bi decay:::::::::::::::::::::::\n"
  	 << "\tgamma 328keV:::  " <<  gamma_328.GetCounterValue() <<"\n"
	 << "\tgamma 569keV:::  " <<  gamma_569.GetCounterValue() <<"\n"
	 << "\tgamma 897keV:::  " <<  gamma_897.GetCounterValue() <<"\n"
	 << "\tgamma 1063keV::  " << gamma_1063.GetCounterValue() <<"\n"
	 << "\tgamma 1442keV::  " << gamma_1442.GetCounterValue() <<"\n"
	 << "\tgamma 1770keV::  " << gamma_1770.GetCounterValue() <<"\n"
	 << "\tCE_K  481keV::   " <<   elec_481.GetCounterValue() <<"\n"
	 << "\tCE_L  553keV::   " <<   elec_553.GetCounterValue() <<"\n"
	 << "\tCE_M  565keV::   " <<   elec_565.GetCounterValue() <<"\n"
	 << "\tCE_K  975keV::   " <<   elec_975.GetCounterValue() <<"\n"
	 << "\tCE_L 1047keV::   " <<  elec_1047.GetCounterValue() <<"\n"
	 << "\tCE_M 1059keV::   " <<  elec_1059.GetCounterValue() <<"\n"
	 << "\tXrK_72_8keV ::   " <<XrK_72_8keV.GetCounterValue() <<"\n"
	 << "\tXrK_74_9keV ::   " <<XrK_74_9keV.GetCounterValue() <<"\n"
	 << "\tXrK_84_4keV ::   " <<XrK_84_4keV.GetCounterValue() <<"\n"
	 << "\tXrK_84_9keV ::   " <<XrK_84_9keV.GetCounterValue() <<"\n"
	 << "\tXrK_87_3keV ::   " <<XrK_87_3keV.GetCounterValue() <<"\n"
	 << "\tXrL_10_6keV ::   " <<XrL_10_6keV.GetCounterValue() <<"\n\n"

<< "from 32Al (isomeric state) decay:::::::::::::::::::::::\n"
  	 << "\tgamma 222keV:::  " <<  gamma_222.GetCounterValue() <<"\n"
	 << "\telect 222keV:::  " <<  elec_222.GetCounterValue() <<"\n"
	 << "\tgamma 735keV:::  " <<  gamma_735.GetCounterValue() <<"\n\n";
*/
if (GLOB_source_type[i] == 3) {
cout << "from Monoenergetic Gamma decay :::::::::::::::::::::::\n"
  	 << "\tGamma " << GLOB_source_energy[i] << " keV:::  " <<  gamma_mono[i].GetCounterValue() <<"\n\n";
}

if (GLOB_source_type[i] == 4) {
cout << "from Beta decay :::::::::::::::::::::::\n"
  	 << "\tBeta <" << GLOB_source_energy[i] << " keV :::  " <<  elec_rand[i].GetCounterValue() <<"\n\n";
	}
	
	
}


//Saving the details about the detection setup in the .txt file:
cout << "System Configuration: \n ";
cout << "Type	|Distance[mm]	|Theta[deg]	|Phi[deg]	|Spin[deg] \n";
for(int i=0;i<gLines;i++){		
		for(int j=0;j<5;j++){
			if(0==j) cout << gType[i]		<< "\t\t";
			if(1==j) cout << gDistance[i]	<< "\t\t";
			if(2==j) cout << gTheta[i]		<< "\t\t";
			if(3==j) cout << gPhi[i]		<< "\t\t";
			if(4==j) cout << gSpin[i]		<< endl;
		}
		
	}
 
  


delete particleGun;	
}




void G4IDSPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{


 
    particleGun->SetParticlePosition(G4ThreeVector( .0*mm, .0*mm, 0.*mm) );	

for (int i = 0; i< GLOB_source_nb; i++) {

   if (GLOB_source_type[i] == 1)  Europium152(anEvent);
   if (GLOB_source_type[i] == 2)  GenericSource(anEvent);
   
   
   ////////////// Monoenergetic gamma source
   if (GLOB_source_type[i] == 3) {
     particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
     particleGun->SetParticleEnergy(GLOB_source_energy[i]*keV); 
     particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
     particleGun->GeneratePrimaryVertex(anEvent);
     gamma_mono[i].IncrementCounter();  
     events.IncrementCounter();
   
   }   
   
   ////////////// Monoenergetic beta source
   if (GLOB_source_type[i] == 4) {
     particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
     particleGun->SetParticleEnergy(GLOB_source_energy[i]*keV); 
     particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
     particleGun->GeneratePrimaryVertex(anEvent); 
     elec_rand[i].IncrementCounter();
     events.IncrementCounter();
     
   }
   
   ////////////// Random energy beta source
   if (GLOB_source_type[i] == 5) {
     particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
     particleGun->SetParticleEnergy(G4UniformRand()*GLOB_source_energy[i]*keV); 
     particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
     particleGun->GeneratePrimaryVertex(anEvent); 
     elec_rand[i].IncrementCounter();
     events.IncrementCounter();
     
   }
   
   ////////////// Random energy beta source
   if (GLOB_source_type[i] == 6) {
     particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
     particleGun->SetParticleEnergy(G4UniformRand()*GLOB_source_energy[i]*keV); 
     particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
     particleGun->GeneratePrimaryVertex(anEvent); 
     elec_rand[i].IncrementCounter();
     events.IncrementCounter();
     
   }
   
   
}


//  Barium133(anEvent);
//  Bismuth207(anEvent);


}


void State_2plus_38Ar(G4Event* anEvent) 
	{
	particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	particleGun->SetParticleEnergy(2167*keV);
	particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	particleGun->GeneratePrimaryVertex(anEvent); 
	gamma_2167.IncrementCounter(); 
	}


void State_3min_38Ar(G4Event* anEvent) 
	{
	particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	particleGun->SetParticleEnergy(1642*keV);
	particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	particleGun->GeneratePrimaryVertex(anEvent); 
	gamma_1642.IncrementCounter(); 
	State_2plus_38Ar(anEvent); 
	}


void State_4min_38Ar(G4Event* anEvent) 
	{
	particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	particleGun->SetParticleEnergy(669.7*keV);
	particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	particleGun->GeneratePrimaryVertex(anEvent); 
	gamma_669.IncrementCounter(); 
	State_3min_38Ar(anEvent);
	}


void State_5min_38Ar(G4Event* anEvent) 
	{
	G4double dice4 = G4UniformRand(); 
	if ( dice4 <= .9 )
		{
		particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 	particleGun->SetParticleEnergy(105.9*keV);
	 	particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 	particleGun->GeneratePrimaryVertex(anEvent); 
	 	gamma_106.IncrementCounter(); 
		State_4min_38Ar(anEvent);
		}
	else	
		{
		particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 	particleGun->SetParticleEnergy(775.7*keV);
	 	particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 	particleGun->GeneratePrimaryVertex(anEvent); 
	 	gamma_775.IncrementCounter(); 
		State_3min_38Ar(anEvent);
		}
	}



void G4IDSPrimaryGeneratorAction::isom38Cl(G4Event* anEvent)
{
events.IncrementCounter();
G4double dice2 = G4UniformRand();
G4double nb2 = dice2*10000; 

if ( nb2 <= 1 )
	{
	 particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
	 beta_en = ( dNdBeta_is38Cl->GetRandom() ); 
	 particleGun -> SetParticleEnergy( beta_en * keV ); 
	 particleGun -> SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 particleGun -> GeneratePrimaryVertex(anEvent); 
	 N_beta.IncrementCounter(); 
	 State_5min_38Ar(anEvent);	
	}
else
	{
	 particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 particleGun->SetParticleEnergy(671.4*keV);
	 particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 particleGun->GeneratePrimaryVertex(anEvent); 
	 gamma_671.IncrementCounter(); 
	}
}


void G4IDSPrimaryGeneratorAction::gs38Cl(G4Event* anEvent)
{
events.IncrementCounter();
G4double dice3 = G4UniformRand();
if ( dice3 <= .55 )
	{
	particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
	beta_en = ( dNdBeta_gs38Cl->GetRandom() ); 
	particleGun -> SetParticleEnergy( beta_en * keV ); 
	particleGun -> SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	particleGun -> GeneratePrimaryVertex(anEvent); 
	N_beta.IncrementCounter(); 
	}
else if ( dice3 <= .66 )
	{
	particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
	beta_en = ( dNdBeta_gs38Cl2->GetRandom() ); 
	particleGun -> SetParticleEnergy( beta_en * keV ); 
	particleGun -> SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	particleGun -> GeneratePrimaryVertex(anEvent); 
	N_beta.IncrementCounter(); 
	State_2plus_38Ar(anEvent); 
	}
else
	{
	particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
	beta_en = ( dNdBeta_is38Cl->GetRandom() ); 
	particleGun -> SetParticleEnergy( beta_en * keV ); 
	particleGun -> SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	particleGun -> GeneratePrimaryVertex(anEvent); 
	N_beta.IncrementCounter(); 
	State_3min_38Ar(anEvent); 
	}
}


void G4IDSPrimaryGeneratorAction::gs41Ar(G4Event* anEvent)
{
events.IncrementCounter();
  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
  beta_en = ( dNdBeta_41Ar->GetRandom() ); 
  particleGun -> SetParticleEnergy( beta_en * keV ); 
  particleGun -> SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
  particleGun -> GeneratePrimaryVertex(anEvent); 
N_beta.IncrementCounter(); 
  
  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
  particleGun->SetParticleEnergy(1293.*keV);
  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
  particleGun->GeneratePrimaryVertex(anEvent); 
gamma_1293.IncrementCounter(); 
}


//  *******************************************************************************************
//					152Eu SOURCE
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void Level_1Gd(G4Event* anEvent) 
	{ G4double conversion_coeff_344 = G4UniformRand(); 
	  if ( conversion_coeff_344 <= 0.961631 ) 
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(344.278*keV);
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent); 
	  gamma_344.IncrementCounter(); }	}
void Level_3Gd(G4Event* anEvent) 
	{ G4double conversion_coeff_411 = G4UniformRand(); 
	  if ( conversion_coeff_411 <= 0.976658 ) 
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(411.116*keV); 
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent);
	  gamma_411.IncrementCounter();
	  Level_1Gd(anEvent);	}	}
void Level_7Gd(G4Event* anEvent) 
	{ G4double branching_level7 = G4UniformRand(); 
	  if ( branching_level7 <= 0.9367 ) 
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(778.90*keV); 
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent);
	  gamma_778.IncrementCounter();
	  Level_1Gd(anEvent);  }
	  else if ( branching_level7 <= 0.999484 )
	  { G4double conversion_coeff_367 = G4UniformRand(); 
	  if ( conversion_coeff_367 <= 0.9904 )
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(367.79*keV);
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent); 
	  gamma_367.IncrementCounter();
	  Level_3Gd(anEvent);  }	}	}
void Level_11Gd(G4Event* anEvent) 
	{ G4double branching_level11 = G4UniformRand(); 
	  if ( branching_level11 <= 0.71153 )
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(1089.737*keV); 
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent);
	  gamma_1089.IncrementCounter();
	  Level_1Gd(anEvent);  }
	  else if ( branching_level11 <= 0.90644 )
	  {  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(678.62*keV); 
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent);
	  gamma_678.IncrementCounter();
	  Level_3Gd(anEvent);  }	}
void Level_14Gd(G4Event* anEvent) 
	{ G4double branching_level14 = G4UniformRand();
	  if ( branching_level14 <= 0.89317 ) 
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(1299.14*keV); 
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent);
	  gamma_1299.IncrementCounter();
	  Level_1Gd(anEvent);  }	}

void Level_1Sm(G4Event* anEvent) 
	{ G4double conversion_coeff_121 = G4UniformRand(); 
	  if ( conversion_coeff_121 <= 0.460829 )	// alpha = 1.17  
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(121.78*keV); 
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent);
	  gamma_121.IncrementCounter(); }	}
void Level_2Sm(G4Event* anEvent) 
	{ G4double conversion_coeff_244 = G4UniformRand(); 
	  if ( conversion_coeff_244 <= 0.902527 )	// alpha = 0,108 
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(244.69*keV); 
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent);
	  gamma_244.IncrementCounter();
	  Level_1Sm(anEvent); }	}
void Level_5Sm(G4Event* anEvent) 
	{ G4double branching_level5 = G4UniformRand();
	  if ( branching_level5 <= 0.56566 )
	  { G4double conversion_coeff_688 = G4UniformRand(); 
	  if ( conversion_coeff_688 <= 0.9584 )		// alpha = 0,0434
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(688.67*keV); 
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent);
	  gamma_688.IncrementCounter();
	  Level_1Sm(anEvent);  }	}
	  else if (branching_level5 <= 0.77589 )
	  { G4double conversion_coeff_443 = G4UniformRand(); 
	  if ( conversion_coeff_443 <= 0.9825 )		// alpha = 0,0178
	  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(443.965*keV); 
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent);
	  gamma_443.IncrementCounter();
	  Level_2Sm(anEvent); }	
	  else if (branching_level5 <= 0.97917 )
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(810.45*keV); 
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent);
	  gamma_810.IncrementCounter();}	}
void Level_9Sm(G4Event* anEvent) 
	{ G4double branching_level9 = G4UniformRand();
	  if ( branching_level9 <= 0.40605 ) 
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(1085.87*keV); 
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent);
	  gamma_1085.IncrementCounter(); }
	  else if ( branching_level9 <= 0.98742 )
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(964.08*keV); 
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent);
	  gamma_964.IncrementCounter();
	  Level_1Sm(anEvent); }	}
void Level_10Sm(G4Event* anEvent) 
	{ G4double branching_level10 = G4UniformRand();
	  if ( branching_level10 <= 0.75988 ) 
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(1112.07*keV); 
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent);
	  gamma_1112.IncrementCounter();
	  Level_1Sm(anEvent); }
	  else if ( branching_level10 <= 0.99655 )
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(867.37*keV); 
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent);
	  gamma_867.IncrementCounter();
	  Level_2Sm(anEvent); }	}
void Level_12Sm(G4Event* anEvent) 
	{ G4double branching_level12 = G4UniformRand(); 
	  if ( branching_level12 <= 0.21663 )
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(1249.94*keV); 
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent);
	  gamma_1249.IncrementCounter();
	  Level_1Sm(anEvent); }
	  else if ( branching_level12 <= 0.9605 )
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(1005.27*keV); 
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent);
	  gamma_1005.IncrementCounter();
	  Level_2Sm(anEvent);  }	}
void Level_13Sm(G4Event* anEvent) 
	{ G4double branching_level13 = G4UniformRand(); 
	  if ( branching_level13 <= 0.84326 )
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(1408.00*keV); 
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent);
	  gamma_1408.IncrementCounter();
	  Level_1Sm(anEvent);  }
	  else if ( branching_level13 <= 0.95715 ) 
	  {  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(443.965*keV); 
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent);
	  gamma_443.IncrementCounter();
	  Level_9Sm(anEvent);  }
	  else if ( branching_level13 <= 0.97535 )
	  {  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(295.94*keV); 
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent);
	  gamma_295.IncrementCounter();
	  Level_10Sm(anEvent);  }	}


void G4IDSPrimaryGeneratorAction::Europium152(G4Event* anEvent)
{

events.IncrementCounter();
G4double rnd = G4UniformRand();
	G4double number = rnd*94884;  // number=1000;

// Numerical conditions coresponding to feeding ratios of Gd & Sm levels
// by the decay of 152Eu; intensities available @:::::::::::::::::::
	// http://www.nndc.bnl.gov/useroutput/AR152GD-152064002.html
	// http://www.nndc.bnl.gov/useroutput/AR152SM-152062006.html
// Levels are counted starting with GroundState=0
	
		if (number <=  1819) {  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
	   			particleGun->SetParticleEnergy( (1864.*G4UniformRand())*keV ); 
	   			particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	   			particleGun->GeneratePrimaryVertex(anEvent);				
				Level_14Gd(anEvent); }
else 	if (number <=  4245) {  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
	   			particleGun->SetParticleEnergy( (1864.*G4UniformRand())*keV ); 
	   			particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	   			particleGun->GeneratePrimaryVertex(anEvent);	
				Level_11Gd(anEvent); }
else 	if (number <= 18025) {  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
	   			particleGun->SetParticleEnergy( (1864.*G4UniformRand())*keV ); 
	   			particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	   			particleGun->GeneratePrimaryVertex(anEvent);				
				Level_7Gd(anEvent) ; }
else 	if (number <= 18925) {  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
	   			particleGun->SetParticleEnergy( (1864.*G4UniformRand())*keV ); 
	   			particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	   			particleGun->GeneratePrimaryVertex(anEvent);				
				Level_3Gd(anEvent) ; }
else 	if (number <= 27025) {  particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
	   			particleGun->SetParticleEnergy( (1864.*G4UniformRand())*keV ); 
	   			particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	   			particleGun->GeneratePrimaryVertex(anEvent);				
				Level_1Gd(anEvent) ; }
else 	if (number <= 51945) { Level_13Sm(anEvent); }
else 	if (number <= 69355) { Level_10Sm(anEvent); }
else 	if (number <= 91085) { Level_9Sm(anEvent) ; }
else 	if (number <= 92385) { Level_5Sm(anEvent) ; }
else 	if (number <= 93285) { Level_2Sm(anEvent) ; }
else 	if (number <= 94025) { Level_1Sm(anEvent) ; }
else 			     { Level_12Sm(anEvent); }

}
//	************************  END OF 152Eu  ************************************
//	****************************************************************************






//  *******************************************************************************************
//					133Ba SOURCE
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


void Level_1Cs(G4Event* anEvent) 
	{ G4double conversion_coeff_81 = G4UniformRand(); 
	  if ( conversion_coeff_81 <= 0.367647 )
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	  particleGun->SetParticleEnergy(80.99*keV); 
	  particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	  particleGun->GeneratePrimaryVertex(anEvent);
	  gamma_80.IncrementCounter(); }
	  else
	  {particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
	   particleGun->SetParticleEnergy(80.99*keV); 
	   particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	   particleGun->GeneratePrimaryVertex(anEvent);
	   elec_80.IncrementCounter(); }	}
void Level_2Cs(G4Event* anEvent) 
	{ G4double branching_level2 = G4UniformRand(); 
	  if ( branching_level2 <= 0.89466 )
	  { G4double conversion_coeff_79 = G4UniformRand(); 
	    if ( conversion_coeff_79 <= 0.3703704)
	    { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	    particleGun->SetParticleEnergy(79.61*keV); 
	    particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	    particleGun->GeneratePrimaryVertex(anEvent);
	    gamma_79.IncrementCounter();
	    Level_1Cs(anEvent);  }	
	    else
	    { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
	    particleGun->SetParticleEnergy(79.0*keV); 
	    particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	    particleGun->GeneratePrimaryVertex(anEvent);
	    elec_79.IncrementCounter();
	    Level_1Cs(anEvent);  }	}
	  else  
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	    particleGun->SetParticleEnergy(160.61*keV); 
	    particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	    particleGun->GeneratePrimaryVertex(anEvent);
	    gamma_160.IncrementCounter();}	}
void Level_3Cs(G4Event* anEvent) 
	{ G4double branching_level3 = G4UniformRand();
	  if ( branching_level3 <= 0.31728 ) 
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	    particleGun->SetParticleEnergy(383.85*keV); 
	    particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	    particleGun->GeneratePrimaryVertex(anEvent);
	    gamma_383.IncrementCounter(); }	
	  else if ( branching_level3 <= 0.98281 )
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	    particleGun->SetParticleEnergy(302.85*keV); 
	    particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	    particleGun->GeneratePrimaryVertex(anEvent);
	    gamma_302.IncrementCounter(); 
	    Level_1Cs(anEvent);  }	
	  else
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	    particleGun->SetParticleEnergy(223.24*keV); 
	    particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	    particleGun->GeneratePrimaryVertex(anEvent);
	    gamma_223.IncrementCounter(); 
	    Level_2Cs(anEvent);  }	}
void Level_4Cs(G4Event* anEvent) 
	{ G4double branching_level4 = G4UniformRand();
	  if ( branching_level4 <= 0.73476 )
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	    particleGun->SetParticleEnergy(356.01*keV); 
	    particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	    particleGun->GeneratePrimaryVertex(anEvent);
	    gamma_356.IncrementCounter(); 
	    Level_1Cs(anEvent);  }
	  else if ( branching_level4 <= 0.912588 )
	  { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	    particleGun->SetParticleEnergy(276.4*keV); 
	    particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	    particleGun->GeneratePrimaryVertex(anEvent);
	    gamma_276.IncrementCounter(); 
	    Level_2Cs(anEvent);  }
	  else
	  { G4double conversion_coeff_53 = G4UniformRand(); 
	    if ( conversion_coeff_53 <= 0.142857)
	    { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	    particleGun->SetParticleEnergy(53.16*keV); 
	    particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	    particleGun->GeneratePrimaryVertex(anEvent);
	    gamma_53.IncrementCounter(); 
	    Level_3Cs(anEvent);  }
	    else
	    { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
	    particleGun->SetParticleEnergy(53.16*keV); 
	    particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	    particleGun->GeneratePrimaryVertex(anEvent);
	    elec_53.IncrementCounter(); 
	    Level_3Cs(anEvent);  }	}	}



void G4IDSPrimaryGeneratorAction::Barium133(G4Event* anEvent)
{

events.IncrementCounter();
G4double rnd = G4UniformRand();

// Numerical conditions coresponding to feeding ratios of Cs levels
// by Electron Capture Decay of 133Ba; intensities available @:::::::::::::::::::
	// http://www.nndc.bnl.gov/useroutput/AR133CS-133055003.html
// Levels are counted starting with GroundState=0
	
	if ( rnd <= 0.86 ) { Level_4Cs(anEvent); }
	else 		   { Level_3Cs(anEvent); }

}
//	************************  END OF 133Ba  ************************************
//	****************************************************************************




//  *******************************************************************************************
//					207Bi SOURCE
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void X_Rays_K_orbital (G4Event* anEvent)
	{ G4double k_x_ray = G4UniformRand();
	 if ( k_x_ray <= 0.29436 )		//	XR kAlpha2	E=72.805keV	I=21.4 %
	 	{ particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 	particleGun->SetParticleEnergy(72.805*keV); 
	 	particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 	particleGun->GeneratePrimaryVertex(anEvent);	}
	 else if ( k_x_ray <= 0.78542 )	//	XR kAlpha1	E=74.969keV	I=35.7 %
	 	{ particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 	particleGun->SetParticleEnergy(74.969*keV); 
	 	particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 	particleGun->GeneratePrimaryVertex(anEvent);	}
	 else if ( k_x_ray <= 0.8447 )	//	XR kBeta3	E=84.45keV	I=4.31 %
	 	{ particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
		particleGun->SetParticleEnergy(84.45*keV); 
		particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 	particleGun->GeneratePrimaryVertex(anEvent);	}
	 else if ( k_x_ray <= 0.95846 )	//	XR kAlpha1	E=84.938keV	I=8.27 % 
	 	{ particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 	particleGun->SetParticleEnergy(84.938*keV); 
	 	particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 	particleGun->GeneratePrimaryVertex(anEvent);	}
	 else				//	XR kAlpha2	E=87.3keV	I=3.02 %
	 	{ particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 	particleGun->SetParticleEnergy(87.3*keV); 
	 	particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 	particleGun->GeneratePrimaryVertex(anEvent);	}
	}

void Level_1Pb (G4Event* anEvent)
	{ G4double conversion_coeff_569 = G4UniformRand();
	 if ( conversion_coeff_569 <= 0.9789706 )		// alpha=0.0215
	 { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 particleGun->SetParticleEnergy(569.7*keV); 
	 particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 particleGun->GeneratePrimaryVertex(anEvent);
	 gamma_569.IncrementCounter(); }
	 else if ( conversion_coeff_569 <= 0.9941418 )		// alpha_K=0.0155
	 { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
	 particleGun->SetParticleEnergy(481.7*keV); 
	 particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 particleGun->GeneratePrimaryVertex(anEvent);
	 elec_481.IncrementCounter(); 
		  G4double k_x_ray = G4UniformRand();
		  if ( k_x_ray <= 0.29436 )		//	XR kAlpha2	E=72.805keV	I=21.4 %
	 		 { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 		 particleGun->SetParticleEnergy(72.805*keV); 
	 		 particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 		 particleGun->GeneratePrimaryVertex(anEvent);
			 XrK_72_8keV.IncrementCounter();	}
		  else if ( k_x_ray <= 0.78542 )	//	XR kAlpha1	E=74.969keV	I=35.7 %
	 		 { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 		 particleGun->SetParticleEnergy(74.969*keV); 
	 		 particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 		 particleGun->GeneratePrimaryVertex(anEvent);	
			 XrK_74_9keV.IncrementCounter();	}
		  else if ( k_x_ray <= 0.8447 )	//	XR kBeta3	E=84.45keV	I=4.31 %
	 		 { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
			 particleGun->SetParticleEnergy(84.45*keV); 
			 particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 		 particleGun->GeneratePrimaryVertex(anEvent);
			 XrK_84_4keV.IncrementCounter();	}
		  else if ( k_x_ray <= 0.95846 )	//	XR kAlpha1	E=84.938keV	I=8.27 % 
	 		 { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 		 particleGun->SetParticleEnergy(84.938*keV); 
	 		 particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 		 particleGun->GeneratePrimaryVertex(anEvent);
			 XrK_84_9keV.IncrementCounter();	}
		  else				//	XR kAlpha2	E=87.3keV	I=3.02 %
	 		 { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 		 particleGun->SetParticleEnergy(87.3*keV); 
	 		 particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 		 particleGun->GeneratePrimaryVertex(anEvent);
			 XrK_87_3keV.IncrementCounter();	} 
	}
	 else if ( conversion_coeff_569 <= 0.9985279 )		// alpha_L=0.00448
	 { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
	 particleGun->SetParticleEnergy(553.8*keV); 
	 particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 particleGun->GeneratePrimaryVertex(anEvent);
	 elec_553.IncrementCounter(); 
	 //	XR L	E=10.6keV	I=33.2 %
	 		 particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 		 particleGun->SetParticleEnergy(10.6*keV); 
	 		 particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 		 particleGun->GeneratePrimaryVertex(anEvent);
			 XrL_10_6keV.IncrementCounter(); 	}
	 else 							// alpha_M=0.0015
	 { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
	 particleGun->SetParticleEnergy(565.9*keV); 
	 particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 particleGun->GeneratePrimaryVertex(anEvent);
	 elec_565.IncrementCounter();  }	}
void Level_2Pb (G4Event* anEvent)
	{ G4double branching_level2pb = G4UniformRand();
	if ( branching_level2pb <= 0.992446 ) 
	{ particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 particleGun->SetParticleEnergy(897.8*keV); 
	 particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 particleGun->GeneratePrimaryVertex(anEvent);
	 gamma_897.IncrementCounter(); }
	else
	{ particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 particleGun->SetParticleEnergy(328.1*keV); 
	 particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 particleGun->GeneratePrimaryVertex(anEvent);
	 gamma_328.IncrementCounter(); 
	 Level_1Pb(anEvent);   }	}
void Level_3Pb (G4Event* anEvent)
	{ G4double conversion_coeff_1063 = G4UniformRand();
	if ( conversion_coeff_1063 <= 0.887989 )		// alpha=0.126
	{ particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 particleGun->SetParticleEnergy(1063.7*keV); 
	 particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 particleGun->GeneratePrimaryVertex(anEvent);
	 gamma_1063.IncrementCounter();
	 Level_1Pb(anEvent); }
	else if ( conversion_coeff_1063 <= 0.97167 )		// alpha_K=0.0942
	{ particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
	 particleGun->SetParticleEnergy(975.7*keV); 
	 particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 particleGun->GeneratePrimaryVertex(anEvent);
	 elec_975.IncrementCounter();
 		    G4double k_x_ray = G4UniformRand();
		    if ( k_x_ray <= 0.29436 )		//	XR kAlpha2	E=72.805keV	I=21.4 %
	 		   { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 		   particleGun->SetParticleEnergy(72.805*keV); 
	 		   particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 		   particleGun->GeneratePrimaryVertex(anEvent);
			   XrK_72_8keV.IncrementCounter();	}
		    else if ( k_x_ray <= 0.78542 )	//	XR kAlpha1	E=74.969keV	I=35.7 %
	 		   { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 		   particleGun->SetParticleEnergy(74.969*keV); 
	 		   particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 		   particleGun->GeneratePrimaryVertex(anEvent);	
			   XrK_74_9keV.IncrementCounter();	}
		    else if ( k_x_ray <= 0.8447 )	//	XR kBeta3	E=84.45keV	I=4.31 %
	 		   { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
			   particleGun->SetParticleEnergy(84.45*keV); 
			   particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 		   particleGun->GeneratePrimaryVertex(anEvent);
			   XrK_84_4keV.IncrementCounter();	}
		    else if ( k_x_ray <= 0.95846 )	//	XR kAlpha1	E=84.938keV	I=8.27 % 
	 		   { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 		   particleGun->SetParticleEnergy(84.938*keV); 
	 		   particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 		   particleGun->GeneratePrimaryVertex(anEvent);
			   XrK_84_9keV.IncrementCounter();	}
		    else				//	XR kAlpha2	E=87.3keV	I=3.02 %
	 		   { particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 		   particleGun->SetParticleEnergy(87.3*keV); 
	 		   particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 		   particleGun->GeneratePrimaryVertex(anEvent);
			   XrK_87_3keV.IncrementCounter();	}
	 Level_1Pb(anEvent); }
	else if ( conversion_coeff_1063 <= 0.993572 )		// alpha_L=0.0247
	{ particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
	 particleGun->SetParticleEnergy(1047.8*keV); 
	 particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 particleGun->GeneratePrimaryVertex(anEvent);
	 elec_1047.IncrementCounter();
	  //	XR L	E=10.6keV	I=33.2 %
	 		 particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 		 particleGun->SetParticleEnergy(10.6*keV); 
	 		 particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 		 particleGun->GeneratePrimaryVertex(anEvent);
			 XrL_10_6keV.IncrementCounter(); 
	 Level_1Pb(anEvent); }
	else 							// alpha_M=0.0247
	{ particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="e-"));
	 particleGun->SetParticleEnergy(1059.8*keV); 
	 particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 particleGun->GeneratePrimaryVertex(anEvent);
	 elec_1059.IncrementCounter();
	 Level_1Pb(anEvent);   }	}
void Level_4Pb (G4Event* anEvent)
	{ G4double branching_level4pb = G4UniformRand();
	if ( branching_level4pb <= 0.98131 ) 
	{ particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 particleGun->SetParticleEnergy(1770.2*keV); 
	 particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 particleGun->GeneratePrimaryVertex(anEvent);
	 gamma_1770.IncrementCounter();
	 Level_1Pb(anEvent); }
	else
	{ particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	 particleGun->SetParticleEnergy(1442.2*keV); 
	 particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	 particleGun->GeneratePrimaryVertex(anEvent);
	 gamma_1442.IncrementCounter();
	 Level_2Pb(anEvent);   }	}


void G4IDSPrimaryGeneratorAction::Bismuth207(G4Event* anEvent)
{

events.IncrementCounter();
G4double rnd = G4UniformRand();

// Numerical conditions coresponding to feeding ratios of 207Pb levels
// by Electron Capture Decay of 207Bi; intensities available @:::::::::::::::::::
	// http://www.nndc.bnl.gov/......................you'll find it!
// Levels are counted starting with GroundState=0
	
	if 	( rnd <= 0.07 ) { Level_4Pb(anEvent); }
	else if ( rnd <= 0.91 ) { Level_3Pb(anEvent); }
	else			{ Level_1Pb(anEvent); }
}
//	*******************************  END OF 207Bi  ************************************
//	***********************************************************************************




//	************************ Generic Source ************************************
//	****************************21 gamma rays***********************************


void G4IDSPrimaryGeneratorAction::GenericSource(G4Event* anEvent)
{

	events.IncrementCounter();
	G4double rnd  = G4UniformRand()*21.0;
	
	
	particleGun->SetParticleDefinition(particleTable->FindParticle(particleName="gamma"));
	
	if (rnd < 1) {
		particleGun->SetParticleEnergy(10.0*keV); 
		generic_10.IncrementCounter();
	}
	
	else if (rnd < 2) {
		particleGun->SetParticleEnergy(30.0*keV); 
		generic_30.IncrementCounter();
	}
	
	else if (rnd < 3) {
		particleGun->SetParticleEnergy(60.0*keV); 
		generic_60.IncrementCounter();
	}
	
	else if (rnd < 4) {
		particleGun->SetParticleEnergy(80.0*keV); 
		generic_80.IncrementCounter();
	}
	
	else if (rnd < 5) {
		particleGun->SetParticleEnergy(100.0*keV); 
		generic_100.IncrementCounter();
	}
	
	else if (rnd < 6) {
		particleGun->SetParticleEnergy(120.0*keV); 
		generic_120.IncrementCounter();
	}
	
	else if (rnd < 7) {
		particleGun->SetParticleEnergy(170.0*keV); 
		generic_170.IncrementCounter();
	}
	
	else if (rnd < 8) {
		particleGun->SetParticleEnergy(220.0*keV); 
		generic_220.IncrementCounter();
	}
	
	else if (rnd < 9) {
		particleGun->SetParticleEnergy(300.0*keV); 
		generic_300.IncrementCounter();
	}
	
	else if (rnd < 10) {
		particleGun->SetParticleEnergy(400.0*keV); 
		generic_400.IncrementCounter();
	}
	
	else if (rnd < 11) {
		particleGun->SetParticleEnergy(600.0*keV); 
		generic_600.IncrementCounter();
	}
	
	else if (rnd < 12) {
		particleGun->SetParticleEnergy(800.0*keV); 
		generic_800.IncrementCounter();
	}
	
	else if (rnd < 13) {
		particleGun->SetParticleEnergy(1000.0*keV); 
		generic_1000.IncrementCounter();
	}
	
	else if (rnd < 14) {
		particleGun->SetParticleEnergy(1200.0*keV); 
		generic_1200.IncrementCounter();
	}
	
	else if (rnd < 15) {
		particleGun->SetParticleEnergy(1600.0*keV); 
		generic_1600.IncrementCounter();
	}
	
	else if (rnd < 16) {
		particleGun->SetParticleEnergy(2000.0*keV); 
		generic_2000.IncrementCounter();
	}
	
	else if (rnd < 17) {
		particleGun->SetParticleEnergy(2800.0*keV); 
		generic_2800.IncrementCounter();
	}
	
	else if (rnd < 18) {
		particleGun->SetParticleEnergy(4000.0*keV); 
		generic_4000.IncrementCounter();
	}
	
	else if (rnd < 19) {
		particleGun->SetParticleEnergy(5000.0*keV); 
		generic_5000.IncrementCounter();
	}
	
	else if (rnd < 20) {
		particleGun->SetParticleEnergy(7000.0*keV); 
		generic_7000.IncrementCounter();
	}
	
	else if (rnd < 21) {
		particleGun->SetParticleEnergy(9000.0*keV); 
		generic_9000.IncrementCounter();
	}
	
	
	
	particleGun->SetParticleMomentumDirection( G4ThreeVector() = G4RandomDirection() );
	particleGun->GeneratePrimaryVertex(anEvent); 
	
	
		
		
		

}
//	************************  END OF Generic Source ************************************
//	****************************************************************************







