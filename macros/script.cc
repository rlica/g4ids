
{

TH1F *a = new TH1F("a","a",1500,0,15);
TH1F *ap = new TH1F("ap","ap",1500,0,15);
a->SetLineColor(2);

TH1F *b = new TH1F("b","b",1500,0,15);
TH1F *bp = new TH1F("bp","bp",1500,0,15);
b->SetLineColor(2);

TH1F *c = new TH1F("c","c",1500,0,15);
TH1F *cp = new TH1F("cp","cp",1500,0,15);
c->SetLineColor(2);

TH1F *d = new TH1F("d","d",1500,0,15);
TH1F *dp = new TH1F("dp","dp",1500,0,15);
d->SetLineColor(2);

tv__tree->Draw("Ge1a>>a","Ge1a>0","");
tv__tree->Draw("Ge1a>>ap","Ge1a>0 && Esc1==0","");

tv__tree->Draw("Ge1b>>b","Ge1b>0","");
tv__tree->Draw("Ge1b>>bp","Ge1b>0 && Esc1==0","");

tv__tree->Draw("Ge1c>>c","Ge1c>0","");
tv__tree->Draw("Ge1c>>cp","Ge1c>0 && Esc1==0","");

tv__tree->Draw("Ge1d>>d","Ge1d>0","");
tv__tree->Draw("Ge1d>>dp","Ge1d>0 && Esc1==0","");

TCanvas *tc = new TCanvas; 
tc->Divide(2,2); 
tc->cd(1);
a->Draw();
ap->Draw("same");
tc->cd(2);
b->Draw();
bp->Draw("same");
tc->cd(3);
c->Draw();
cp->Draw("same");
tc->cd(4);
d->Draw();
dp->Draw("same");

}
