//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun 24 13:47:06 2014 by ROOT version 5.34/08
// from TTree is530/is530
// found on file: Eu152_center_10mm_plastic.root
//////////////////////////////////////////////////////////

#ifndef root2ascii_h
#define root2ascii_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class root2ascii : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           evNo;
   Int_t           nPoints;
   Int_t           mult;
   Int_t           det_nb[15];   //[mult]
   Double_t        energy[15];   //[mult]

   // List of branches
   TBranch        *b_evNo;   //!
   TBranch        *b_nPoints;   //!
   TBranch        *b_mult;   //!
   TBranch        *b_det_nb;   //!
   TBranch        *b_energy;   //!

   root2ascii(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~root2ascii() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(root2ascii,0);
};

#endif

#ifdef root2ascii_cxx
void root2ascii::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("evNo", &evNo, &b_evNo);
   fChain->SetBranchAddress("nPoints", &nPoints, &b_nPoints);
   fChain->SetBranchAddress("mult", &mult, &b_mult);
   fChain->SetBranchAddress("det_nb", det_nb, &b_det_nb);
   fChain->SetBranchAddress("energy", energy, &b_energy);
}

Bool_t root2ascii::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef root2ascii_cxx
