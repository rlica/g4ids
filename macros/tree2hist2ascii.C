#include <iostream>
// C libraries
#include <stdio.h>
#include <stdlib.h>

#include <TApplication.h>
#include <TBox.h>
#include <TFile.h>
#include <TH1.h>
#include <TLatex.h>
#include <TPaveStats.h>


using namespace std;


int main (){


  
  TFile *_file0 = TFile::Open("IS579_152Eu_20kk.root","update");

  _file0->Delete("hSumAB;1");
  _file0->Delete("hSum;1");

  

  TH1F *hTemp = new TH1F("hTemp","",          40000,1,10000);
  TH1F *hSum    = new TH1F("hSum" ,"Clover Sum noAB",40000,1,10000);
  TH1F *hSumAB  = new TH1F("hSumAB" ,"Clover Sum AB",40000,1,10000);
  
  char *branch; 
  
  gROOT->Reset();
  gStyle->SetOptStat(1000000);
  TCanvas *Can1;
  Can1 = new TCanvas("Can1","Can1",800,800); 
  //Can1->Divide(1,2);

    
  //TPad *p1 = (TPad *)(Can1->cd(1)); 
  //const char *gate = "E_Beta>0";
  
  
  //NO ADDBACK
 
 for (int i=0; i<=1; i++)
	for (int j=0; j<=3; j++) {
		branch = Form("Cl%d_Cr%d_KU_En",i,j);
		cout << "Reading Clover " << branch << endl;
		idstree->Draw(Form("%s>>hTemp",branch),"","");
		hSum->Add(hTemp);
	}
	
 for (int i=0; i<=2; i++)
	for (int j=0; j<=3; j++) {
		branch = Form("Cl%d_Cr%d_Buch_En",i,j);
		cout << "Reading Clover " << branch << endl;
		idstree->Draw(Form("%s>>hTemp",branch),"","");
		hSum->Add(hTemp);
	}
	
	 
  
  printf("Finished drawing beta gated Clover Sum\n\n");
  
  
  
  //WITH ADDBACK
  
  for (int i=0; i<=1; i++)
	for (int j=0; j<=3; j++) {
		branch = Form("Cl%d_Cr%d_KU_EnAb",i,j);
		cout << "Reading Clover " << branch << endl;
		idstree->Draw(Form("%s>>hTemp",branch),"","");
		hSumAB->Add(hTemp);
	}
	
 for (int i=0; i<=2; i++)
	for (int j=0; j<=3; j++) {
		branch = Form("Cl%d_Cr%d_Buch_EnAb",i,j);
		cout << "Reading Clover " << branch << endl;
		idstree->Draw(Form("%s>>hTemp",branch),"","");
		hSumAB->Add(hTemp);
	}
	
	
  printf("Finished drawing beta gated Clover Sum with Addback\n\n");
  
  
  
  
  hSumAB->Draw();
  hSum->SetLineColor(2);
  hSum->Draw("same");
   
  hSum->Write();
  hSumAB->Write();
  
  
  
  char out_file_name[500];
  snprintf(out_file_name, sizeof(out_file_name), "%s.hist", hist->GetName());
  FILE *out_file;
  out_file = fopen(out_file_name, "w");
  cout << "Making output file: " << out_file_name << endl;
  fprintf(out_file, "%s\t%s\t%d\n",
   	  file_name, hist_name, hist -> GetNbinsX());
  for (int i = 1; i <= hist -> GetNbinsX(); i++) {
    fprintf(out_file, "%g\t%g\n",
	    hist -> GetBinCenter(i), hist -> GetBinContent(i));
  }
  fclose(out_file);
  cout << "Output complete" << endl;
  return 0;


}
