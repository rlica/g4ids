//hSum->Print("all"); > IS590_hSum.ascii


void tree2hist(char *FileName){
	

  cout<<"Oppening file: "<<FileName<<endl;

  TFile *_file0 = TFile::Open(FileName,"update");

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
  
  


}
