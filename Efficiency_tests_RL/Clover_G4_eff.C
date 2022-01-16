// Program to analyse 152Eu, 60Co or 133Ba data.
//
// It fits the major lines of EuBa and compares them to literature
// intensities to determine the efficiency which is fitted by:
// 
// log(eff) = a + b * E + c * E^2 + d * E^3 + e * E^4
// 
// Compile with: make -jN
// 		 make clean (to clean)
//
// Author(s): C. Sotty
//            email: csotty@gmail.com
//
// Changes (RL):
//
//   19.02.2015  - Integrating peaks instead of GaussFit 
//               - Adding generic source
//   24.02.2014  - Changing the fit function for efficiency
//
//
//
#include <TROOT.h>
#include <TApplication.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TText.h>
#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <TMath.h>
#include <TMultiGraph.h>
#include <TGraphErrors.h>
#include <TTree.h>
#include <TH2.h>
#include <TLegend.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
//#include <stdio.h>
//#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <sstream>

#include <vector>
#include <string>
#include <iostream>
#include <iomanip> 
#include <sstream>
#include <fstream>
#include <istream>
#include <ostream>
#include <streambuf>
#include <algorithm>
#include <unistd.h> //for getopt

//#include <boost/regex.hpp>
//#include <boost/algorithm/string/regex.hpp>
//#include <boost/algorithm/string/split.hpp>

#include "Terminator.hh"

//using namespace std;

char *det_cable[] ={(char*)"Clover103_1",(char*)"Clover103_2",(char*)"Clover103_3",(char*)"Clover103_4",(char*)"Clover103_5",(char*)"Clover103_6",(char*)"Clover103_7",(char*)"Clover103_8",(char*)"Clover103_9",(char*)"Clover103_10",(char*)"Clover103_11",(char*)"Clover103_12",(char*)"Clover103_13",(char*)"Clover103_14"};

typedef struct {
	double E;
	double I;
	double norm;
} peak;

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
  time_t     now = time(0);
  struct tm  tstruct;
  char       buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
  return buf;
}


/*int countWords(std::string str) {
  std::vector<std::string> result;
  boost::algorithm::split_regex(result, str, boost::regex( "\\s+" ));
  return result.size();
}*/


// These are the absolute activities of the two sources in Bq. The values are
// taken from the source list and should be corrected for the date of the
// measurement! The -a option allows you to do this from the command line and the
// -t option allows you to specify the date of the source activity.
#define NB_COUNTS 1000000	// Number of counts
#define NB_DETECTORS 4		// Number of detectors
#define MAXPEAK 21
#define LN2 0.6931471 		// log_e(2)

//-----------------------------------------------------------------------------
// Calculates the corrected intensity due to the decay between times then and
// now (unix times since 1970) for the half life Thalf (in years).
double decay(double I, double Thalf, time_t then, time_t now) {
	return(I * exp(-LN2 / Thalf / 365.25 / 24. / 3600. * (now - then)));
}

Double_t gBinW;

Double_t gaus_lbg(Double_t *x, Double_t *par)                                                                                                   
{
/*
  par[0]   background constant
  par[1]   background slope
  par[2]   gauss width
  par[3]   gauss0 constant
  par[4]   gauss0 mean
*/
  static Float_t sqrt2pi = TMath::Sqrt(2*TMath::Pi()), sqrt2 = TMath::Sqrt(2.);
  Double_t arg;
  if (par[2] == 0) par[2]=1;                 //  force widths /= 0
  arg = (x[0] - par[4])/(sqrt2*par[2]);
  Double_t fitval = par[0] + x[0]*par[1]
                    + gBinW/(sqrt2pi*par[2]) * par[3] * exp(-arg*arg);
  return fitval;
}


//-----------------------------------------------------------------------------
void analyse_peak(TH1F *hist, double E, double *A, double *dA, double *fwhm, double *dfwhm) {
	
	Double_t gLowX  = E - (2.+E*0.008), gUpX = E + (2.+E*0.008), tmp;
	//Double_t gLowX  = E - (3.+E*0.006), gUpX = E + (3.+E*0.006), tmp;   //RL: We get better fit results like this
	
	Double_t gSigma;
	Double_t gBgConstant = 0.;
	Double_t gBgSlope;
	Double_t gContent;
	Double_t gMean = E;
	Double_t gChi2pNDF = 1.;
	Double_t gFWHM;
	Double_t gFWHM_error; 
	Double_t gMean_error; 
	Double_t gSigma_error;
	Double_t gContent_error;

	hist->GetXaxis()->SetRangeUser(gLowX,gUpX);
	gBinW = hist->GetBinWidth(1);

	if(gLowX < gUpX)
	{   
	   // *** Creating the function of the form 'gaus_lbg' defined above ***
	   TF1 fitfunc("gauss_linbg",gaus_lbg, 0, 1, 5);
	   // *** Obtaining and specifying the start values for the fit ***
	   gContent = gBinW * (hist->Integral(hist->FindBin(gLowX),hist->FindBin(gUpX)));
	   gSigma = 0.32 * ( gUpX  - gLowX);
	   fitfunc.SetParameters(0, 0, gSigma, gContent, gMean);
	   fitfunc.SetRange(gLowX, gUpX);

	   fitfunc.SetParName(0,"BgConstant");
	   fitfunc.SetParName(1,"BgSlope   ");
	   fitfunc.SetParName(2,"Sigma     ");
	   fitfunc.SetParName(3,"Content   ");
	   fitfunc.SetParName(4,"Mean      ");
	   fitfunc.SetLineColor(2);

	   // *** Fitting: 'R' means within the range specified above ***
	   hist->Fit("gauss_linbg", "R", "SAME");
	   
	   gBgConstant = fitfunc.GetParameter(0);
	   gBgSlope    = fitfunc.GetParameter(1);
	   gSigma      = fitfunc.GetParameter(2);
	   gContent    = fitfunc.GetParameter(3);
	   gMean       = fitfunc.GetParameter(4);
	   gChi2pNDF   = fitfunc.GetChisquare() / fitfunc.GetNDF();
	   gFWHM = 2*gSigma*sqrt(2*log(2));
	   gFWHM_error = 2*sqrt(2*log(2))*fitfunc.GetParError(2);
	   gMean_error = fitfunc.GetParError(4);
	   gSigma_error = fitfunc.GetParError(2);
	   gContent_error = fitfunc.GetParError(3);
	   printf("      Chi Square/NDF: %f , FWHM: %f(%f) , \n", gChi2pNDF, gFWHM, gFWHM_error);
	} else std::cout << "Couldn't fit! Error: The Lower Limit is larger than the Upper Limit!" << std::endl;

	Double_t iWidth		= 4.; // in keV
	Double_t peakbins 	= hist->FindBin(E+iWidth) - hist->FindBin(E-iWidth);
	Double_t peakInt	= hist->Integral(hist->FindBin(E-iWidth),hist->FindBin(E+iWidth)) ;
	Double_t BackL		= hist->Integral(hist->FindBin(E-iWidth*2)-1 , hist->FindBin(E-iWidth)-1 );
	Double_t BackR		= hist->Integral(hist->FindBin(E+iWidth)+1 , hist->FindBin(E+iWidth*2)+1 );
	Double_t Ai 		= peakInt - BackL -BackR;
	Double_t dAi		= sqrt(peakInt + BackL + BackR) + sqrt(5.0)/100.0*Ai; // 5% out of the total number of generated events
	
	// Get result
	//*A	= gContent;
	//*dA	= gContent_error;
	//*fwhm	= gFWHM;
	//*dfwhm	= gFWHM_error;
	*A	= Ai;
	*dA	= dAi;
	*fwhm	= gFWHM;
	*dfwhm	= gFWHM_error;
/*
	Int_t max_bin = h->FindBin(E);
	Float_t content_binmax = h->GetBinContent(max_bin);
	// Get integral
	*A = h->Integral((Int_t)lo, (Int_t)hi);
	*dA = sqrt(*A);
	
	// If it is too small, don't fit
	if (*A < 10) return;
	while(h->GetBinContent(max_bin++)>content_binmax/2 && max_bin<h->GetNbinsX());
	TF1 *fit = new TF1(h->GetName(), "gaus(0)+pol2(3)", lo, hi);
	fit->SetParName(0, "height");
	fit->SetParName(1, "energy");
	fit->SetParName(2, "sigma");
	fit->SetParName(3, "bck_off");
	fit->SetParName(4, "bck_slope");
	fit->SetParName(5, "bck_quad");
	fit->SetParameter(0,content_binmax);
	fit->SetParLimits(1, lo, hi);
	fit->SetParameter(1, E);
	fit->SetParLimits(2, 0.1, 10);
	fit->SetParameter(2, h->GetBinWidth(max_bin)*(max_bin-h->FindBin(E))/2.3548);
	fit->SetLineWidth(1);
	if (*A < 100) {
		fit->FixParameter(4,0);
		fit->FixParameter(5,0);
	}
	
	// Fit
	h->Fit(fit);
	*fwhm=0;
	*fwhm+=2.3548*fit->GetParameter(2);
	*dfwhm=0;
	*dfwhm+=TMath::Power(fit->GetParError(2) / fit->GetParameter(2),2);

	// Get result
	*A = sqrt(TMath::Pi() * 2) * fit->GetParameter(0) * fit->GetParameter(2);
	*dA = 0;
	tmp = fit->GetParError(0) / fit->GetParameter(0);
	*dA += tmp * tmp;
	tmp = fit->GetParError(2) / fit->GetParameter(2);
	*dA += tmp * tmp;
	*dA = sqrt(*dA) * *A;
*/	
	std::cout << "A     = " << std::setw(20) << *A     << std::endl
		  << "Ai    = " << std::setw(20) << Ai    << std::endl
		  << "dA    = " << std::setw(20) << *dA    << std::endl
		  << "dAi   = " << std::setw(20) << dAi   << std::endl
		  << "fwhm  = " << std::setw(20) << *fwhm  << std::endl
		  << "dfwhm = " << std::setw(20) << *dfwhm << std::endl;
	return;
}

//-----------------------------------------------------------------------------
void Clover_G4_eff(char *inputfile = (char *)"./Photopeak_efficiency.root",
				  std::string outfile = "analyse_clover_exp_eff.dat",
				  double norm_1408 = 1, int nb_counts = 1000000,
				  int Nb_detector = NB_DETECTORS) {
	
	double norm_rela_1408 = 1;


  //// 152Eu
	
	//peak peaks[] = {
////		{80.9971, 34.11, activity_133Ba}, // Energy, intensity per 100 decays, activity in Bq
		//{121.7817, 28.670, 1},
		//{244.6975,  7.583, 1},
////		{276.3997,  7.147, activity_133Ba},
////		{302.8510, 18.300, activity_133Ba},
		//{344.2785, 26.500, 1},
////		{356.0134, 61.940, activity_133Ba},
////              {383.8480,  8.905, activity_133Ba},
////		{411.1165,  2.238, 1},
////		{443.9650,  3.125, 1},
		//{778.9040, 12.960, 1},
		//{867.3780,  4.260, 1},
		//{964.0790, 14.630, 1},
////		{1085.836, 10.130, activity_152Eu},
////		{1089.737,  1.731, activity_152Eu},
		//{1112.069, 13.690, 1},
////		{1212.948,  1.412, 1},
////		{1299.140,  1.626, 1},
		//{1408.006, 21.070, 1},
////		{1173.228, 99.857, activity_60Co},
////		{1332.490, 99.983, activity_60Co},
////		{0, 0}
	//};
	
	// Generic Source: Energy, Intensity, Norm(?)
	peak peaks[] = {
		{  10,  4.7619, 1},
		{  30,  4.7619, 1},
		{  60,  4.7619, 1},
		{  80,  4.7619, 1},
		{ 100,  4.7619, 1},
		{ 120,  4.7619, 1},
		{ 170,  4.7619, 1},
        	{ 220,  4.7619, 1},
		{ 300,  4.7619, 1},
		{ 400,  4.7619, 1},
		{ 600,  4.7619, 1},
		{ 800,  4.7619, 1},
		{1000,  4.7619, 1},
		{1200,  4.7619, 1},
		{1600,  4.7619, 1},
		{2000,  4.7619, 1},
		{2800,  4.7619, 1},
		{4000,  4.7619, 1},
		{5000,  4.7619, 1},
		{7000,  4.7619, 1},
		{9000,  4.7619, 1}
	};
	
	
	
	//std::cout << "Nb of peaks = " << sizeof(peaks)/sizeof(peak) << std::endl;
	//std::cout << "Nb_detector = " << Nb_detector << std::endl;
	int nb_peak = sizeof(peaks)/sizeof(peak);
	ofstream fp;
	int i, k, npeaks = 0;
	TGraphErrors **g_abso  = new TGraphErrors* [Nb_detector];
	TGraphErrors **g_rela  = new TGraphErrors* [Nb_detector];
	TGraphErrors **ge_resolution = new TGraphErrors* [Nb_detector];

	double A[Nb_detector][nb_peak], dA[Nb_detector][nb_peak], norm = 1;
	double fwhm[Nb_detector][nb_peak], dfwhm[Nb_detector][nb_peak];
	// Make a new canvas
	TCanvas **c1 = new TCanvas*[Nb_detector];	
	TCanvas *c2 = new TCanvas("Absolute_efficiency","Absolute efficiency", 1400, 1500);
	TCanvas *c3 = new TCanvas("Relative_efficiency","Relative efficiency",1400,1500);
	TCanvas *c4 = new TCanvas("Resolution","Resolution",1400,1500);
	
	// Create two multigraphs
	TMultiGraph *mg_abso = new TMultiGraph();
	TMultiGraph *mg_rela = new TMultiGraph();
	TMultiGraph *mg_reso = new TMultiGraph();

	// Open input file
	TFile *f = TFile::Open(inputfile, "read");
	if (!f) {
	    std::cerr << "Error ! File does not exist: "<< inputfile << std::endl;
	    exit(1);
	}

	// Open output file
	fp.open(outfile, std::ofstream::out | std::ofstream::ate);
	fp << "***************************************************\n"
	   << "* Creation date: " << currentDateTime() <<"       *\n"
	   << "*                                                 *\n"
	   << "*       Produced by clover_exp_eff                *\n"
	   << "*       Author(s): C. Sotty                       *\n"
	   << "*                email: csotty@gmail.com          *\n"
	   << "***************************************************\n";

	// Just show integral
	gStyle->SetOptStat("111111");
	TH1F **h = new TH1F*[Nb_detector]; 
	

	for (k = 0; k < Nb_detector; k++) {
		c1[k] = new TCanvas(Form("Fit Ge_%i",k+1),Form("Fit Ge_%i",k+1),1400,1500);
		c1[k]->Divide(4,4);	
/*		std::cout << "POUIC"<<std::endl;	
//		id_energy_ge->ProjectionY(Form("Ge_%i",k),k+1,k+1);
//		h[k]=dynamic_cast<TH1F*>(gDirectory->FindObject(Form("hEn_%i",k)));
		//h[k]=dynamic_cast<TH1F*>(gDirectory->Get(Form("hEn_%i",k)));	
		if(0==k){
			//continue;
			std::cout<<Form("\nhLaBr3Sum")<<std::endl;
			h[k]=dynamic_cast<TH1F*>(gDirectory->Get(Form("hLaBr3Sum")));	
		}
		if(1==k){
			//continue;
			std::cout<<Form("\nhSumAB")<<std::endl;
			h[k]=dynamic_cast<TH1F*>(gDirectory->Get(Form("hSumAB")));	
		}
		if(1<k && 4>k){
			std::cout<<Form("\nhClKUSum_%d",k-2)<<std::endl;
			h[k]=dynamic_cast<TH1F*>(gDirectory->Get(Form("hClKUSum_%d",k-2)));	
		}
		if(3<k && 6>k){
			std::cout<<Form("\nhClBuchSum_%d",k-4)<<std::endl;
			h[k]=dynamic_cast<TH1F*>(gDirectory->Get(Form("hClBuchSum_%d",k-4)));	
		}
		if(5<k && 8>k){
			std::cout<<Form("\nhClKUSumAB_%d",k-6)<<std::endl;
			h[k]=dynamic_cast<TH1F*>(gDirectory->Get(Form("hClKUSumAB_%d",k-6)));	
		}
		if(7<k && 10>k){
			std::cout<<Form("\nhClBuchSumAB_%d",k-8)<<std::endl;
			h[k]=dynamic_cast<TH1F*>(gDirectory->Get(Form("hClBuchSumAB_%d",k-8)));	
		}
		if(9<k && 18>k){
			std::cout<<Form("\nhCl%d_Cr%d_KU_En",(k-10)/4,(k-10)%4)<<std::endl;
			h[k]=dynamic_cast<TH1F*>(gDirectory->Get(Form("hCl%d_Cr%d_KU_En",(k-10)/4,(k-10)%4)));	
		}
		if(17<k && 26>k){
			std::cout<<Form("\nhCl%d_Cr%d_Buch_En",(k-18)/4,(k-18)%4)<<std::endl;
			h[k]=dynamic_cast<TH1F*>(gDirectory->Get(Form("hCl%d_Cr%d_Buch_En",(k-18)/4,(k-18)%4)));	
		}
		if(25<k && 34>k){
			std::cout<<Form("\nhCl%d_Cr%d_KU_EnAb",(k-26)/4,(k-26)%4)<<std::endl;
			h[k]=dynamic_cast<TH1F*>(gDirectory->Get(Form("hCl%d_Cr%d_KU_EnAb",(k-26)/4,(k-26)%4)));	
		}
		if(33<k && 42>k){
			std::cout<<Form("\nhCl%d_Cr%d_Buch_EnAb",(k-34)/4,(k-34)%4)<<std::endl;
			h[k]=dynamic_cast<TH1F*>(gDirectory->Get(Form("hCl%d_Cr%d_Buch_EnAb",(k-34)/4,(k-34)%4)));	
		}

		//h[k]=dynamic_cast<TH1F*>(gDirectory->Get(Form("hsum%i",k)));
		//h[k]=dynamic_cast<TH1F*>(gDirectory->Get(Form("hrKU_Sum",k)));
	*/	
		if (k == 0) h[k]=dynamic_cast<TH1F*>(gDirectory->Get("hSum"));
		if (k == 1) h[k]=dynamic_cast<TH1F*>(gDirectory->Get("hSumAB"));
		
		
		
		if(!(int)h[k]->Integral()){
		    std::cout << "oula"<<std::endl;
		    continue;
		}
		std::cout << "POUIC"<<std::endl;	

		// Set color
		h[k]->SetLineColor(2);
		// Make graphs
		g_rela[k] = new TGraphErrors(npeaks);
		g_abso[k] = new TGraphErrors(npeaks);
		ge_resolution[k] = new TGraphErrors(npeaks);
//		fprintf(fp, "Fits for Ge %i \n", k);
		std::cout << "POUIC"<<std::endl;	

//		for (i = 0; peaks[i].E > 0; i++) {
		for (i = 0; i < nb_peak; i++){
			std::cout << "POUICL"<<std::endl;	
			TH1F* h2 = (TH1F*) h[k]->Clone();
			
			// Select pad
			c1[k]->cd(i + 1);
			
			// Set range
			h2->GetXaxis()->SetRangeUser(peaks[i].E - (2.+peaks[i].E*0.005), peaks[i].E + (2.+peaks[i].E*0.005));
			
			// Draw histogram
			h2->Draw();
			
			// Analyse the peak
			analyse_peak(h2, peaks[i].E, A[k] + i, dA[k] + i, fwhm[k] +i, dfwhm[k] +i);
//			analyse_peak(h2, peaks[i].E, &A[k][i], &dA[k][i], &fwhm[k][i], &dfwhm[k][i]);
                        ge_resolution[k]->SetPoint(i,peaks[i].E,fwhm[k][i]);
                        ge_resolution[k]->SetPointError(i,0,dfwhm[k][i]);
			std::cout << fwhm[k][i] << std::endl;
			if(0==i){
				fp << "Fit for Ge detector #" << k << std::endl;
				fp << std::setw(12) << "Energy[keV]" << std::setw(16) << "I [Cts]" << std::setw(16) << "I Err. [Cts]" << std::setw(20) << "Resolution [keV]" << std::setw(20) << "Resol. Err. [keV]" << std::endl;
			}
			fp << std::setw(12) << peaks[i].E << std::setw(16) << A[k][i] << std::setw(16) << dA[k][i] << std::setw(20) << fwhm[k][i] << std::setw(20) << dfwhm[k][i] <<std::endl;
			//std::cout << std::setw(15) << peaks[i].E << std::setw(15) << A[k][i] << std::setw(15) << dA[k][i] << std::setw(15) << A[k][i] / peaks[i].I * 100 / peaks[i].norm << std::setw(15) << dA[k][i] / peaks[i].I * 100 /peaks[i].norm << std::endl;
/*			fprintf(fp, "%-12.3lf %-12.3lf %-12.3lf %-12.3lf %-12.3lf\n",
					peaks[i].E, A[k][i], dA[k][i],
					A[k][i] / peaks[i].I * 100 / peaks[i].norm,
					dA[k][i] / peaks[i].I * 100 /peaks[i].norm);
*/			
			// Get Normalisation parameter
			if (peaks[i].E==1408.006){
				norm_rela_1408=A[k][i]/(peaks[i].I/100.);				
			}

		}
		
//		fprintf(fp, "\n");
		fp << std::endl;

		npeaks = i;
		for (i=0; i<npeaks;i++){
			g_rela[k]->SetPoint(i, peaks[i].E,A[k][i]/ peaks[i].I * 100. / norm_rela_1408);
			g_rela[k]->SetPointError(i, 0, dA[k][i] / peaks[i].I * 100. / norm_rela_1408);
			g_abso[k]->SetPoint(i, peaks[i].E, A[k][i]/ peaks[i].I * 100. / nb_counts *100);    //std::cout<<"peaks[i].E = "<< peaks[i].E <<"  A[k][i] = "<< A[k][i] << "  peaks[i].I/100. = "<<peaks[i].I/100.<<"   duration = " << duration << std::endl << "   | peaks[i].norm = " << peaks[i].norm << std::endl;
			g_abso[k]->SetPointError(i, 0, dA[k][i] / peaks[i].I * 100. / nb_counts *100);
			if(0==i){
				fp << std::setw(12) << "Energy[keV]" << std::setw(20) << "Abs. Eff.[%]" << std::setw(20) << "Abs. Eff. Err.[%]" << std::endl;
			}
				fp << std::setw(12) << peaks[i].E << std::setw(20) << A[k][i]/ peaks[i].I * 100. / nb_counts *100 << std::setw(20) << dA[k][i] / peaks[i].I * 100. / nb_counts *100 << std::endl;
//			g_abso[k]->SetPoint(i, peaks[i].E,A[k][i] / peaks[i].I * 100 / (peaks[i].norm * norm_1408));
		//	g_abso[k]->SetPointError(i, 0, dA[k][i] / peaks[i].I * 100 / (peaks[i].norm * norm_1408));
		}
		
		g_abso[k]->SetMarkerSize(2);
		g_abso[k]->SetMarkerStyle(2);
		g_abso[k]->SetMarkerColor(1 + k);
		g_abso[k]->SetLineColor(1 + k);
		g_rela[k]->SetMarkerSize(2);
		g_rela[k]->SetMarkerStyle(2);
		g_rela[k]->SetMarkerColor(1 + k);
		g_rela[k]->SetLineColor(1 + k);
		ge_resolution[k]->SetMarkerSize(2);
		ge_resolution[k]->SetMarkerStyle(2);

		ge_resolution[k]->SetMarkerColor(1 + k);
		ge_resolution[k]->SetLineColor(1 + k);
		mg_rela->Add(g_rela[k]);
		mg_abso->Add(g_abso[k]);
		mg_reso->Add(ge_resolution[k]);
		
		// Fit function for the efficiency (CS)
		//TF1 *fit_rela = new TF1("rela_eff", "[0] + [1] * log(x) + [2] * log(x) * log(x) + [3] * log(x) * log(x) * log(x) + [4] * log(x) * log(x) * log(x) * log(x)", 200, 1500);
		//TF1 *fit_abso = new TF1("abso_eff", "[0] + [1] * log(x) + [2] * log(x) * log(x) + [3] * log(x) * log(x) * log(x) + [4] * log(x) * log(x) * log(x) * log(x)", 200, 1500);
		
		// New fit function (RL)
		// Geraldo, L.P., Smith, D.L., 1990. “Covariance analysis and fitting of germanium gamma-ray detector efficiency calibration data” Nucl. Instrum. Methods A 290, 499.

		TF1 *fit_rela = new TF1("rela_eff", "( [0] + [1] * log(x) + [2] * log(x) * log(x) + [3] * log(x) * log(x) * log(x) + [4] * log(x) * log(x) * log(x) * log(x) * log(x) + [5] * log(x) * log(x) * log(x) * log(x) * log(x)* log(x) * log(x))/x", 10, 700);
		TF1 *fit_abso = new TF1("abso_eff", "( [0] + [1] * log(x) + [2] * log(x) * log(x) + [3] * log(x) * log(x) * log(x) + [4] * log(x) * log(x) * log(x) * log(x) * log(x) + [5] * log(x) * log(x) * log(x) * log(x) * log(x)* log(x) * log(x))/x", 10, 700);
		
		
				
		TF1 *fit_resolution = new TF1("resolution", "TMath::Sqrt(TMath::Power([0],2)*x+TMath::Power([1],2))", 200, 1500);
		fit_rela->SetLineColor(1 + k);
		fit_abso->SetLineColor(1 + k);
		fit_resolution->SetLineColor(1 + k);

		// Fit the efficiency and resolution
		
		std::cout << "Fit relative efficiency" << std::endl;
		//fit_rela->SetParameter(0,21.5);    // CS
		//fit_rela->SetParameter(1,-1.29);
		//fit_rela->SetParameter(2,-0.4);
		//fit_rela->SetParameter(3,-0.0284);
		//fit_rela->SetParameter(4,0.0075);
		
		fit_rela->SetParameter(0,-92);      // RL
		fit_rela->SetParameter(1,49);
		fit_rela->SetParameter(2,-8.65);
		fit_rela->SetParameter(3,0.54);
		fit_rela->SetParameter(4,0.05);
		fit_rela->SetParameter(5,0.005);
		
		g_rela[k]->Fit(fit_rela);

		std::cout << "Fit absolute efficiency" << std::endl;
		//fit_abso->SetParameter(0,3.559);    // CS
        //fit_abso->SetParameter(1,-0.214);
        //fit_abso->SetParameter(2,-0.06596);
        //fit_abso->SetParameter(3,-0.0047);
        //fit_abso->SetParameter(4,0.0012);
        
        fit_abso->SetParameter(0,-92.9);      //RL
        fit_abso->SetParameter(1,49.8);
        fit_abso->SetParameter(2,-8.65);
        fit_abso->SetParameter(3,0.54);
        fit_abso->SetParameter(4,0.05);
        fit_abso->SetParameter(5,0.005);
        
        g_abso[k]->Fit(fit_abso);


		std::cout << "Fit resolution" << std::endl;
		ge_resolution[k]->Fit(fit_resolution);


		// Label axes (for some reason this doesn't work if we do it earlier)
		g_rela[k]->GetXaxis()->SetRangeUser(80,1500);
		g_rela[k]->GetYaxis()->SetRangeUser(0, 5);
		g_rela[k]->SetTitle(Form("Ge_%i ",k, det_cable[k-1]));
		g_rela[k]->GetYaxis()->SetTitle("Relative efficiency");  
		
		// Label axes (for some reason this doesn't work if we do it earlier)
		g_abso[k]->GetXaxis()->SetRangeUser(80,1500);
		g_abso[k]->GetYaxis()->SetRangeUser(0.625 * norm, 5.0 * norm);
		g_abso[k]->SetTitle(Form("Ge_%i ",k, det_cable[k-1]));
		g_abso[k]->GetYaxis()->SetTitle("Absolute efficiency");      
		
		// Label axes (for some reason this doesn't work if we do it earlier)
		ge_resolution[k]->GetXaxis()->SetRangeUser(80,1500);
		ge_resolution[k]->GetYaxis()->SetRangeUser(0.625 * norm, 5.0 * norm);
		ge_resolution[k]->SetTitle(Form("Ge_%i ",k, det_cable[k-1]));
		ge_resolution[k]->GetYaxis()->SetTitle("Resolution"); 

		// Write the fit calibration equation
/*		fprintf(fp, "Relative Efficiency for Ge detector # %i:\n", k+1);
		fprintf(fp, "eff = a0 + a1 * ln(E) + a2 * (ln(E))^2 + a3 * (ln(E))^3 + a4 * (ln(E))^4\n\n");
		fprintf(fp, "with\n\ta0=%lg; a1=%lg; a2=%lg; a3=%lg; a4=%lg;\n",
				fit_rela->GetParameter(0), fit_rela->GetParameter(1),
				fit_rela->GetParameter(2), fit_rela->GetParameter(3),
				fit_rela->GetParameter(4));
*/
		fp << "\n Relative Efficiency for Ge detector # "<<k<<" :\n"
		   //<< "eff = a0 + a1 * ln(E) + a2 * (ln(E))^2 + a3 * (ln(E))^3 + a4 * (ln(E))^4\n"   // CS
		   << "eff = (a0 + a1 * ln(E) + a2 * (ln(E))^2 + a3 * (ln(E))^3 + a4 * (ln(E))^5 + a5 * (ln(E))^7)/E\n"     // RL
		   << "\twith \ta0="  << fit_rela->GetParameter(0)
		   << "; a1="       << fit_rela->GetParameter(1)
		   << "; a2="       << fit_rela->GetParameter(2)
		   << "; a3="       << fit_rela->GetParameter(3)
		   << "; a4="       << fit_rela->GetParameter(4)
		   << "; a5="       << fit_rela->GetParameter(5)   
                   << ";" << std::endl;
		
		// Write the fit calibration equation
/*		fprintf(fp, "Absolute Efficiency for Ge detector # %i:\n", k+1);
		fprintf(fp, "eff = a0 + a1 * ln(E) + a2 * (ln(E))^2 + a3 * (ln(E))^3 + a4 * (ln(E))^4\n\n");
		fprintf(fp, "with\n\ta0=%lg; a1=%lg; a2=%lg; a3=%lg; a4=%lg;\n",
				fit_abso->GetParameter(0), fit_abso->GetParameter(1),
				fit_abso->GetParameter(2), fit_abso->GetParameter(3),
				fit_abso->GetParameter(4));
*/

		fp << "\n Absolute Efficiency for Ge detector # "<<k<<" :\n"
		   //<< "eff = a0 + a1 * ln(E) + a2 * (ln(E))^2 + a3 * (ln(E))^3 + a4 * (ln(E))^4\n"   // CS
		   << "eff = (a0 + a1 * ln(E) + a2 * (ln(E))^2 + a3 * (ln(E))^3 + a4 * (ln(E))^5 + a5 * (ln(E))^7)/E\n"     // RL
		   << "  a0=\t"  << fit_abso->GetParameter(0) << "\n"
		   << "  a1=\t"       << fit_abso->GetParameter(1)<< "\n"
		   << "  a2=\t"       << fit_abso->GetParameter(2)<< "\n"
		   << "  a3=\t"       << fit_abso->GetParameter(3)<< "\n"
		   << "  a4=\t"       << fit_abso->GetParameter(4)<< "\n"
		   << "  a5=\t"       << fit_abso->GetParameter(5)<< "\n"
           << std::endl;
		fp << "***************************************************************************************************\n"
		   << "***************************************************************************************************\n";

	}
	//c1->Close();

	c2->cd();
	// Draw multigraph for absolute efficiency
	mg_abso->Draw("AP");
	mg_abso->SetTitle("Absolute Efficiency");
	mg_abso->GetXaxis()->SetTitle("Energy [keV]");
	mg_abso->GetYaxis()->SetTitle("Absolute efficiency [%]");
	
	// Write some legend to TGraph
	TLegend *leg = new TLegend();
	leg->SetFillColor(0);
/*	for (Int_t j=0; j<Nb_detector; j++) {
		leg->AddEntry(g_abso[k],Form("Detector #%i",j+1),"lp");
	}
	leg->Draw();
*/	
	c2->SaveAs("./efficiency/Absolute_efficiency_G4.root");
	
	TFile* _file0 = new TFile("./efficiency/Absolute_efficiency_ALL.root","update");
	_file0->cd();
	for(int kk=0; kk<Nb_detector; kk++){
		std::stringstream ss;
		ss<<"Ge_"<<kk<<"_simulated";
		std::cout<<ss.str().c_str()<<std::endl;
		g_abso[kk]->SetName(ss.str().c_str());
		g_abso[kk]->SetTitle(ss.str().c_str());
		g_abso[kk]->Write(ss.str().c_str());
//		g_rela[kk]->Write();
//		ge_resolution[kk]->Write();
	}
	
	// Draw multigraph for relative efficiency
	c3->cd();
	mg_rela->Draw("AP");
	mg_rela->SetTitle("Relative Efficiency to 1408.006");
	mg_rela->GetXaxis()->SetTitle("Energy [keV]");
	mg_rela->GetYaxis()->SetTitle("Relative efficiency to 1408");
	
	// Write some legend to TGraph
	//leg->Draw();
	//c3->SaveAs("./efficiency/Relative_efficiency_G4.root");

	c4->cd();
	mg_reso->Draw("AP");
	mg_reso->SetTitle("Resolution");
	mg_reso->GetXaxis()->SetTitle("Energy [keV]");
	mg_reso->GetYaxis()->SetTitle("FWHM [keV]");
	//leg->Draw();
	//c4->SaveAs("./efficiency/Resolution.root");
	// Save canvas
	//c4->SaveAs("./efficiency/Resolution_G4.root");
	// c2->SaveAs("analyse_EuBa_eff.png");
	
	// Create a terminator
	Terminator *myterm = new Terminator();
	
	// Set up signal
	TQObject::Connect("TCanvas", "Closed()", "Terminator", myterm,"Terminate()");
	
	// Close output file
	fp.close();
}

//-----------------------------------------------------------------------------
// Code to make it possible to compile this script as a program
#ifndef __CINT__
int main(int argc, char **argv) {
	char *inputfile = (char *)"./Photopeak_efficiency.root";
	std::string outfile = "analyse_Clover_exp_eff.dat";
	extern char *optarg;
	char c;
	double norm = 1;
	int batch_mode = 0;
	int nb_counts = NB_COUNTS;
	int Nb_detector = NB_DETECTORS;
	
	// Handle arguments
	while(1) {
		c = getopt(argc, argv, "r:b:i:n:o:N:");
		if (c == -1) break;
		switch(c) {
			case 'r': // Activity
				sscanf(optarg, "%d", &nb_counts);
				break;
			case 'b': // Batch mode
				batch_mode = 1;
				break;
			case 'i': // Set input file
				inputfile = optarg; std::cout<<"inputfile: "<<inputfile<<std::endl;
				break;
			case 'n': // Set normalisation
				norm = atof(optarg);
				break;
			case 'o': // Set output file
				outfile = std::string(optarg);
				break;
			case 'N': // Set number of detectors
				Nb_detector = (int)atoi(optarg);
				break;
			default:
				fprintf(stderr, "Usage: %s [-r number_of_counts] [-b] [-i inputfile] [-n normalisation] [-o outputfile] [-N number_of_detectors]\n",
						argv[0]);
				fprintf(stderr, "\nBy default the program assumes 1000000 events generated by the Geant4 code.\n");
				fprintf(stderr, "Using the switch:\n");
				fprintf(stderr, "  -r [number_of_counts], enter the number of counts\n");
				fprintf(stderr,	"  -b for batch mode\n");
				fprintf(stderr,	"  -i [name],  set the input file name (in.root)\n");
				fprintf(stderr, "  -n switch is used to normalize the relative efficiency to the 1408.006-keV transition for each crystal\n");
				fprintf(stderr, "  -o [name], set the output file name (.dat)\n");
				fprintf(stderr, "  -N [int], set the number of detectors (crystals)\n");
				return(-1);
				break;
		}
	}
	
	// Create an application for root
	TApplication theApp("tapp", &argc, argv);
	
	// If we are in batch mode tell root, so it doesn't open TCanvases
	if (batch_mode) gROOT->SetBatch();
	
	// Perform the analysis
	Clover_G4_eff(inputfile, outfile, norm, nb_counts, Nb_detector);
	
	// If we are not in batch mode, run the application
	if (!batch_mode) theApp.Run();
	return(0);
}
#endif



