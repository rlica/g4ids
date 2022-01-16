//hSum->Print("all"); > IS590_hSum.ascii


void tree2hist(char *FileName){
	

  cout<<"Oppening file: "<<FileName<<endl;
  int nbKU=2;
  int nbBuch=2;

  TFile *_file0 = TFile::Open(FileName,"update");
//  TH1F** histoKU;  
//  histoKU = new TH1F*[4*2];
//  TH1F** histoBuch;  
//  histoBuch = new TH1F*[4*2];

  _file0->Delete("hSumAB;1");
  _file0->Delete("hSum;1");
  for(int cl=0; cl<3; cl++ ){
    _file0->Delete(Form("hClKUSum_%d;1", cl));
    _file0->Delete(Form("hClKUSumAB_%d;1", cl));
    _file0->Delete(Form("hClBuchSum_%d;1", cl));
    _file0->Delete(Form("hClBuchSumAB_%d;1", cl));
    for(int cr=0; cr<4; cr++){
      _file0->Delete(Form("hCl%d_Cr%d_KU_En;1", cl, cr));
      _file0->Delete(Form("hCl%d_Cr%d_Buch_En;1", cl, cr));
      _file0->Delete(Form("hCl%d_Cr%d_KU_EnAb;1", cl, cr));
      _file0->Delete(Form("hCl%d_Cr%d_Buch_EnAb;1", cl, cr));
//      histoKU[cl*4+cr] = new TH1F("","",40000,1,10000);
    }
  }
  

  TH1F *hTemp = new TH1F("hTemp","",          40000,1,10000);
  TH1F *hSum    = new TH1F("hSum" ,"Clover Sum noAB",40000,1,10000);
  TH1F *hSumAB  = new TH1F("hSumAB" ,"Clover Sum AB",40000,1,10000);
  TH1F **hClKUSum;
  hClKUSum = new TH1F*[3];
  TH1F **hClBuchSum;
  hClBuchSum = new TH1F*[3];
  TH1F **hClKUSumAB;
  hClKUSumAB = new TH1F*[3];
  TH1F **hClBuchSumAB;
  hClBuchSumAB = new TH1F*[3];

  for(int cl=0;cl<3;cl++){
    hClKUSum[cl]	= new TH1F(Form("hClKUSum_%d",cl)	,"Crystal Sum noAB",40000,1,10000);
    hClKUSumAB[cl]	= new TH1F(Form("hClKUSumAB_%d",cl)	,"Crystal Sum AB"  ,40000,1,10000);
    hClBuchSum[cl]	= new TH1F(Form("hClBuchSum_%d",cl)	,"Crystal Sum noAB",40000,1,10000);
    hClBuchSumAB[cl]	= new TH1F(Form("hClBuchSumAB_%d",cl)	,"Crystal Sum AB"  ,40000,1,10000);
  }

  char *branch; 
  
  gROOT->Reset();
  gStyle->SetOptStat(1000000);
  TCanvas *Can1;
  Can1 = new TCanvas("Can1","Can1",800,800); 
  //Can1->Divide(1,2);

    
  //TPad *p1 = (TPad *)(Can1->cd(1)); 
  //const char *gate = "E_Beta>0";
  
  
  //NO ADDBACK
 
 for (int i=0; i<=2; i++)
	for (int j=0; j<=3; j++) {
		branch = Form("Cl%d_Cr%d_KU_En",i,j);
		cout << "Reading Clover " << branch << endl;
		idstree->Draw(Form("%s>>h%s(40000,1,10000)",branch,branch),"","");
		gROOT->ProcessLine(Form("h%s->Write();",branch));
		idstree->Draw(Form("%s>>hTemp",branch),"","");
		hSum->Add(hTemp);
		hClKUSum[i]->Add(hTemp);
	}
	
 for (int i=0; i<=2; i++)
	for (int j=0; j<=3; j++) {
		branch = Form("Cl%d_Cr%d_Buch_En",i,j);
		cout << "Reading Clover " << branch << endl;
		idstree->Draw(Form("%s>>h%s(40000,1,10000)",branch,branch),"","");
		gROOT->ProcessLine(Form("h%s->Write();",branch));
		idstree->Draw(Form("%s>>hTemp",branch),"","");
		hSum->Add(hTemp);
		hClBuchSum[i]->Add(hTemp);
	}
	
	 
  
  printf("Finished drawing beta gated Clover Sum\n\n");
  
  
  
  //WITH ADDBACK
  
  for (int i=0; i<=2; i++)
	for (int j=0; j<=3; j++) {
		branch = Form("Cl%d_Cr%d_KU_EnAb",i,j);
		cout << "Reading Clover " << branch << endl;
		idstree->Draw(Form("%s>>h%s(40000,1,10000)",branch,branch),"","");
		gROOT->ProcessLine(Form("h%s->Write();",branch));
		idstree->Draw(Form("%s>>hTemp",branch),"","");
		hSumAB->Add(hTemp);
		hClKUSumAB[i]->Add(hTemp);
	}
	
 for (int i=0; i<=2; i++)
	for (int j=0; j<=3; j++) {
		branch = Form("Cl%d_Cr%d_Buch_EnAb",i,j);
		cout << "Reading Clover " << branch << endl;
		idstree->Draw(Form("%s>>h%s(40000,1,10000)",branch,branch),"","");
		gROOT->ProcessLine(Form("h%s->Write();",branch));
		idstree->Draw(Form("%s>>hTemp",branch),"","");
		hSumAB->Add(hTemp);
		hClBuchSumAB[i]->Add(hTemp);
	}
	
	
  printf("Finished drawing beta gated Clover Sum with Addback\n\n");
  
  
  
  hSumAB->Draw();
  hSum->SetLineColor(2);
  hSum->Draw("same");
   
  hSum->Write();
  hSumAB->Write();
  
  for(int cl=0;cl<3;cl++){
    hClKUSum[cl]->Write(); 
    hClKUSumAB[cl]->Write(); 
    hClBuchSum[cl]->Write(); 
    hClBuchSumAB[cl]->Write(); 
  }

}
