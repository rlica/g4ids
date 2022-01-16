#define root2ascii_cxx
// The class definition in root2ascii.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("root2ascii.C")
// Root > T->Process("root2ascii.C","some options")
// Root > T->Process("root2ascii.C+")
//

using namespace std; 
#include "Riostream.h"

#include "root2ascii.h"
#include <TH2.h>
#include <TStyle.h>
#include <fstream>


TH1F *det[21]; 
char name[20], title[30]; 
int nbins; 
int counter; 

fstream writeit; 
char out_file[100]; 


void root2ascii::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void root2ascii::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

nbins = 8000; 
for ( int i=0; i<21; i++ )
  {
   sprintf(name,"detector_%i", i); 
   sprintf(title,"energy, 0.5 keV/bin"); 
   det[i] = new TH1F(name, title, nbins,0,4); 
  }
counter = 0; 

}

Bool_t root2ascii::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either root2ascii::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

if ( counter%1000000 == 0 ) 
   cout << "\nevent nb. " << counter << "\n";	// std::endl << std::flush; 


fChain->GetTree()->GetEntry(entry);  // this loads the whole TTree

for ( int m=0; m<mult; m++ )
  {
   if ( det_nb[m] > 20 || det_nb[m] < 0 )  
	cout << "\n\tentry" << entry << "\tM=" << m << "\tLOOK!!! wrong detector number::: " << det_nb[m] << "\n"; 	// std::endl << std::flush; 
   det[det_nb[m]]->Fill( energy[m] ); 
  }

counter++; 

   return kTRUE;
}

void root2ascii::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

  cout << "\n\n\toutput filename ???\t"; 
  cin  >> out_file; 
//  writeit.open( "positions990_ch0.dat", ios::out | ios::app ); 
  writeit.open( out_file, ios::out ); 

  for ( int bn = 0; bn < nbins; bn++ )
    {
     for ( int cr=0; cr < 21; cr++ )
       {
        int bincont = det[cr]->GetBinContent(bn); 
	writeit << bincont << "  "; 
       } 
     writeit << "\n"; 
    }

  writeit.close(); 

}

void root2ascii::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
