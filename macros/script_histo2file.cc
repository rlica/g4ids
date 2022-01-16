
int main()
{


is530->StartViewer(); 

TH1F *det[21]; 
char name[20], title[30]; 
const char blabla[50]; 



for ( int i=0; i<21; i++ )
  {
   sprintf(name,"detector_%i", i); 
   sprintf(title,"energy, 0.5 keV/bin"); 
   det[i] = new TH1F(name, title, 4000,0,2000); 
  }

tv__tree->Draw("energy*1000>>det[0]","det_nb==0",""); 
tv__tree->Draw("energy*1000>>det[1]","det_nb==1",""); 
tv__tree->Draw("energy*1000>>det[2]","det_nb==2",""); 
tv__tree->Draw("energy*1000>>det[3]","det_nb==3",""); 
tv__tree->Draw("energy*1000>>det[4]","det_nb==4",""); 
tv__tree->Draw("energy*1000>>det[5]","det_nb==5",""); 
tv__tree->Draw("energy*1000>>det[6]","det_nb==6",""); 
tv__tree->Draw("energy*1000>>det[7]","det_nb==7",""); 
tv__tree->Draw("energy*1000>>det[8]","det_nb==8",""); 
tv__tree->Draw("energy*1000>>det[9]","det_nb==9",""); 
tv__tree->Draw("energy*1000>>det[10]","det_nb==10",""); 
tv__tree->Draw("energy*1000>>det[11]","det_nb==11",""); 
tv__tree->Draw("energy*1000>>det[12]","det_nb==12",""); 
tv__tree->Draw("energy*1000>>det[13]","det_nb==13",""); 
tv__tree->Draw("energy*1000>>det[14]","det_nb==14",""); 
tv__tree->Draw("energy*1000>>det[15]","det_nb==15",""); 
tv__tree->Draw("energy*1000>>det[16]","det_nb==16",""); 
tv__tree->Draw("energy*1000>>det[17]","det_nb==17",""); 
tv__tree->Draw("energy*1000>>det[18]","det_nb==18",""); 
tv__tree->Draw("energy*1000>>det[19]","det_nb==19",""); 
tv__tree->Draw("energy*1000>>det[20]","det_nb==20",""); 
tv__tree->Draw("energy*1000>>det[21]","det_nb==21",""); 



}
