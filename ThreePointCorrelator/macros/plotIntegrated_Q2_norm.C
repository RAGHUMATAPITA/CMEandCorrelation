#include "RiceStyle.h"

using namespace std;

const int MAXTRACKS = 40000;
//double etabins[] = {-2.4,-2.35,-2.3,-2.25,-2.2,-2.15,-2.1,-2.05,-2,-1.95,-1.9,-1.85,-1.8,-1.75,-1.7,-1.65,-1.6,-1.55,-1.5,-1.45,-1.4,-1.35,-1.3,-1.25,-1.2,-1.15,-1.1,-1.05,-1,-0.95,-0.9,-0.85,-0.8,-0.75,-0.7,-0.65,-0.6,-0.55,-0.5,-0.45,-0.4,-0.35,-0.3,-0.25,-0.2,-0.15,-0.1,-0.05,0.0,0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45,0.5,0.55,0.6,0.65,0.7,0.75,0.8,0.85,0.9,0.95,1,1.05,1.1,1.15,1.2,1.25,1.3,1.35,1.4,1.45,1.5,1.55,1.6,1.65,1.7,1.75,1.8,1.85,1.9,1.95,2,2.05,2.1,2.15,2.2,2.25,2.3,2.35,2.4};
double etabins[] = {-2.4,-2.3,-2.2,-2.1,-2,-1.9,-1.8,-1.7,-1.6,-1.5,-1.4,-1.3,-1.2,-1.1,-1,-0.9,-0.8,-0.7,-0.6,-0.5,-0.4,-0.3,-0.2,-0.1,0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2,2.1,2.2,2.3,2.4};
const int Nbins = sizeof(etabins) / sizeof(etabins[0]) - 1;
double dEtaBins[] = {0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1.0,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.2,2.4,2.6,2.8,3.0,3.4,3.8,4.2,4.8};
const int NdEtaBins = sizeof(dEtaBins) / sizeof(dEtaBins[0]) - 1;
double ntrkBins[] = {0,35,60,90,120,150,185,220,260};
const int NntrkBins = sizeof(ntrkBins) / sizeof(ntrkBins[0]) - 1;
int ntrkBinCenter[] = {17.5, 47.5, 75, 105, 135, 167.5, 202.5, 240};

double xbinwidth[] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0};
double pPb_ntrkBinCenter[] = {16.29,46.1,74.22,101.7,131.3,162.1,196.7,231.5};
double PbPb_ntrkBinCenter[] ={13.8,46.15,73.67,103.9,134,167,202,239.1};
double PbPb_5TeV_ntrkBinCenter[] = {103.921, 134.061, 166.539, 201.615, 239.096, 279.13, 324.044, 374.081, 448.17};

double PbPb_ntrkCentralityBinCenter[] = {625.275, 811.118, 1025.79, 1257.64};

double PbPb_centralityBinCenter[] = {57.5, 52.5, 47.5, 42.5, 37.5, 32.5};

const int Nmults = 11;

double total_systematics_pPb = 0.0000;
double total_systematics_PbPb = 0.0000;

void plotIntegrated_Q2_norm(){

	gStyle->SetErrorX(0);

	TFile* file1[7];
	file1[0] = new TFile("../dataPoints/pPb_norm_v2_Pb_data.root");
    //file1[0] = new TFile("../dataPoints/pPb_norm_v2_Pb_5Q2_data.root");

	TGraphErrors* gr1[4];
	for(int i = 0; i < 4; i++){

		gr1[i] = (TGraphErrors*) file1[0]->Get(Form("Graph;%d", i+1));
	}

//start plotting

	TGaxis::SetMaxDigits(3);

	TH1D* base1 = makeHist("base1", "Pb-going", "v_{2,tracker}", "#LTcos(#phi_{#alpha}+#phi_{#beta}-2#phi_{c})#GT/v_{2,c}", 1000,0,1.0,kBlack);
	base1->GetYaxis()->SetRangeUser(-0.002, 0.002);
	base1->GetXaxis()->SetRangeUser(0.05, 0.1);
	base1->GetXaxis()->SetTitleColor(kBlack);
	
	fixedFontHist1D(base1,1.1,1.25);

	base1->GetYaxis()->SetTitleOffset(1.3);
	base1->GetYaxis()->SetTitleSize(base1->GetYaxis()->GetTitleSize()*1.6);
	base1->GetXaxis()->SetTitleSize(base1->GetXaxis()->GetTitleSize()*1.6);
	base1->GetYaxis()->SetLabelSize(base1->GetYaxis()->GetLabelSize()*1.6);
	base1->GetXaxis()->SetLabelSize(base1->GetXaxis()->GetLabelSize()*1.6);
	base1->GetXaxis()->SetNdivisions(4,6,0);
	base1->GetYaxis()->SetNdivisions(4,6,0);

	//TCanvas* c1 = new TCanvas("c1","c1",1,1,1300,650);
	//c1->Divide(2,1,0.01,0.01);
	//c1->cd(1);
	TCanvas* c1 = new TCanvas("c1","c1",1,1,700,700);
	gPad->SetTicks();
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.13);
	gStyle->SetPadBorderMode(0.1);
	gStyle->SetOptTitle(0);
	//gPad->SetLogx(1);

	base1->Draw();

    TBox *box1[50];
    TBox *box2[50];
    TBox *box3[50];
    TBox *box4[50];
    TBox *box5[50];
    TBox *box6[50];

    double xe[Nmults];

    for(int mult = 0; mult < Nmults; mult++){

    	xe[mult] = 0.0005;
    	double ye = total_systematics_pPb;

    	double x1;
    	double value1;
    	gr1[0]->GetPoint(mult, x1, value1);

    	double x2;
    	double value2;
    	gr1[1]->GetPoint(mult, x2, value2);


    	box1[mult] = new TBox(x1-xe[mult],value1-ye,x1+xe[mult],value1+ye);
		box1[mult]->SetFillColor(kRed);
	 	box1[mult]->SetFillColorAlpha(kGray+1,0.3);
        box1[mult]->SetFillStyle(1001);
    	box1[mult]->SetLineWidth(0);
    	box1[mult]->SetLineColor(kRed);
        box1[mult]->Draw("SAME");

		box2[mult] = new TBox(x2-xe[mult],value2-ye,x2+xe[mult],value2+ye);
		box2[mult]->SetFillColor(kBlue);
	 	box2[mult]->SetFillColorAlpha(kGray+1,0.3);
        box2[mult]->SetFillStyle(1001);
    	box2[mult]->SetLineWidth(0);
    	box2[mult]->SetLineColor(kBlue);
        box2[mult]->Draw("SAME");

    }

    double xe[Nmults];

    for(int mult = 0; mult < Nmults; mult++){

    	xe[mult] = 0.0005;
    	double ye = total_systematics_pPb;

    	double x1;
    	double value1;
    	gr1[2]->GetPoint(mult, x1, value1);

    	double x2;
    	double value2;
    	gr1[3]->GetPoint(mult, x2, value2);


    	box3[mult] = new TBox(x1-xe[mult],value1-ye,x1+xe[mult],value1+ye);
		box3[mult]->SetFillColor(kRed);
	 	box3[mult]->SetFillColorAlpha(kGray+1,0.3);
        box3[mult]->SetFillStyle(1001);
    	box3[mult]->SetLineWidth(0);
    	box3[mult]->SetLineColor(kRed);
        box3[mult]->Draw("SAME");

		box4[mult] = new TBox(x2-xe[mult],value2-ye,x2+xe[mult],value2+ye);
		box4[mult]->SetFillColor(kBlue);
	 	box4[mult]->SetFillColorAlpha(kGray+1,0.3);
        box4[mult]->SetFillStyle(1001);
    	box4[mult]->SetLineWidth(0);
    	box4[mult]->SetLineColor(kBlue);
        box4[mult]->Draw("SAME");

    }

	gr1[0]->SetMarkerStyle(20);
	gr1[0]->SetMarkerSize(1.4);
	gr1[0]->SetMarkerColor(kRed);
	gr1[0]->SetLineColor(kRed);
	gr1[0]->Draw("Psame");

	gr1[1]->SetMarkerStyle(21);
	gr1[1]->SetMarkerSize(1.4);
	gr1[1]->SetMarkerColor(kBlue);
	gr1[1]->SetLineColor(kBlue);
	gr1[1]->Draw("Psame");

	gr1[2]->SetMarkerStyle(24);
	gr1[2]->SetMarkerColor(kRed);
	gr1[2]->SetLineColor(kRed);
	gr1[2]->SetMarkerSize(1.4);
	gr1[2]->Draw("Psame");

	gr1[3]->SetMarkerStyle(25);
	gr1[3]->SetMarkerColor(kBlue);
	gr1[3]->SetLineColor(kBlue);
	gr1[3]->SetMarkerSize(1.4);
	gr1[3]->Draw("Psame");

	TLegend *w1 = new TLegend(0.3,0.14,0.65,0.24);
    w1->SetLineColor(kWhite);
    w1->SetFillColor(0);
    w1->SetTextSize(18);
    w1->SetTextFont(43);
    //w1->SetHeader("CMS");

    w1->SetNColumns(2);

    w1->AddEntry(gr1[0], "  ", "P");
    w1->AddEntry(gr1[1], "  #Psi_{EP}(Pb-going)", "P");
    w1->AddEntry(gr1[2], "  ", "P");
    w1->AddEntry(gr1[3], "  #Psi_{EP}(p-going)", "P");


    w1->Draw("same");

    TLatex* r4 = new TLatex(0.18, 0.78, "pPb #sqrt{s_{NN}} = 5.02 TeV");
    r4->SetNDC();
    r4->SetTextSize(23);
    r4->SetTextFont(43);
    r4->SetTextColor(kBlack);

    TLatex* lmult = new TLatex(0.18, 0.72, "185 #leq N^{offline}_{trk} < 260");
    lmult->SetNDC();
    lmult->SetTextSize(23);
    lmult->SetTextFont(43);
    lmult->SetTextColor(kBlack);

	TLatex* latex1 = new TLatex(0.29, 0.25, "same");
    latex1->SetNDC();
    latex1->SetTextSize(20);
    latex1->SetTextFont(43);
    latex1->SetTextColor(kBlack);
    latex1->Draw("same");
    TLatex* latex2 = new TLatex(0.36, 0.25, "oppo");
    latex2->SetNDC();
    latex2->SetTextSize(20);
    latex2->SetTextFont(43);
    latex2->SetTextColor(kBlack);
    latex2->Draw("same");


   	TLatex* r11 = new TLatex(0.18,0.84, "CMS");
    r11->SetNDC();
    r11->SetTextSize(0.04);

    TLatex* r22 = new TLatex(0.27,0.84, "Preliminary");
    r22->SetNDC();
    r22->SetTextSize(24);
    r22->SetTextFont(53);
    
    r4->Draw("same");
    lmult->Draw("same");
    r11->Draw("same");
    r22->Draw("same");

	TH1D* base2 = makeHist("base2", "Pb-going", "v_{2,tracker}", "#LTcos(#phi_{#alpha}+#phi_{#beta}-2#phi_{c})#GT/v_{2,c} (oppo-same)", 1000,0,1.0,kBlack);
	base2->GetYaxis()->SetRangeUser(-0.000, 0.0015);
	base2->GetXaxis()->SetRangeUser(0.055, 0.095);
	base2->GetXaxis()->SetTitleColor(kBlack);
	
	fixedFontHist1D(base2,1.1,1.25);

	base2->GetYaxis()->SetTitleOffset(1.3);
	base2->GetYaxis()->SetTitleSize(base2->GetYaxis()->GetTitleSize()*1.6);
	base2->GetXaxis()->SetTitleSize(base2->GetXaxis()->GetTitleSize()*1.6);
	base2->GetYaxis()->SetLabelSize(base2->GetYaxis()->GetLabelSize()*1.6);
	base2->GetXaxis()->SetLabelSize(base2->GetXaxis()->GetLabelSize()*1.6);
	base2->GetXaxis()->SetNdivisions(4,6,0);
	base2->GetYaxis()->SetNdivisions(4,6,0);


    TCanvas* c3 = new TCanvas("c3","c3",700,700);
    gPad->SetTicks();
	gPad->SetLeftMargin(0.15);
	gPad->SetBottomMargin(0.13);
	gStyle->SetPadBorderMode(0.1);
	gStyle->SetOptTitle(0);

    TGraphErrors* gr_new1 = new TGraphErrors(Nmults);
    TGraphErrors* gr_new2 = new TGraphErrors(Nmults);


	for(int mult = 0; mult < Nmults; mult++){

    	double ye = total_systematics_pPb;

    	double x1;
    	double value1;
    	double value1_error;
    	gr1[0]->GetPoint(mult, x1, value1);
    	value1_error = gr1[0]->GetErrorY(mult);

    	double x2;
    	double value2;
    	double value2_error;
    	gr1[1]->GetPoint(mult, x2, value2);
		value2_error = gr1[1]->GetErrorY(mult);

    	double x = x1;
    	double y = value2 - value1;
    	double ey = sqrt(value1_error*value1_error + value2_error*value2_error);

    	gr_new1->SetPoint(mult, x, y);
    	gr_new1->SetPointError(mult, 0, ey);


        double x1;
        double value1;
        double value1_error;
        gr1[2]->GetPoint(mult, x1, value1);
        value1_error = gr1[2]->GetErrorY(mult);

        double x2;
        double value2;
        double value2_error;
        gr1[3]->GetPoint(mult, x2, value2);
        value2_error = gr1[3]->GetErrorY(mult);

        double x = x1;
        double y = value2 - value1;
        double ey = sqrt(value1_error*value1_error + value2_error*value2_error);

        gr_new2->SetPoint(mult, x, y);
        gr_new2->SetPointError(mult, 0, ey);

    }

	gStyle->SetErrorX(0);


    base2->Draw();
    gr_new1->SetMarkerStyle(34);
    gr_new1->SetMarkerSize(1.5);
    gr_new1->SetLineColor(kRed);
    gr_new1->SetMarkerColor(kRed);
    gr_new1->Draw("Psame");

    gr_new1->Fit("pol1");
    TF1 * myFunc1 = gr_new1->GetFunction("pol1");
    myFunc1->SetLineStyle(2);
    double intersect_1 = myFunc1->GetParameter(0);
    double intersect_1_error = myFunc1->GetParError(0);
    double slope_1 = myFunc1->GetParameter(1);
    double slope_1_error = myFunc1->GetParError(1);

    TLatex* latex3 = new TLatex(0.18, 0.66, Form("slope: %.4f +/- %.4f",slope_1, slope_1_error ));
    latex3->SetNDC();
    latex3->SetTextSize(20);
    latex3->SetTextFont(43);
    latex3->SetTextColor(kRed);
    latex3->Draw("same");

    TLatex* latex4 = new TLatex(0.18, 0.63, Form("intersect: %.4f +/- %.4f",intersect_1, intersect_1_error ));
    latex4->SetNDC();
    latex4->SetTextSize(20);
    latex4->SetTextFont(43);
    latex4->SetTextColor(kRed);
    latex4->Draw("same");


    gr_new2->SetMarkerStyle(28);
    gr_new2->SetMarkerSize(1.5);
    gr_new2->SetLineColor(kBlue);
    gr_new2->SetMarkerColor(kBlue);
    gr_new2->Draw("Psame");

    gr_new2->Fit("pol1");

    TF1 * myFunc2 = gr_new2->GetFunction("pol1");
    myFunc2->SetLineColor(kBlue);
    myFunc2->SetLineStyle(2);
    double intersect_2 = myFunc2->GetParameter(0);
    double intersect_2_error = myFunc2->GetParError(0);
    double slope_2 = myFunc2->GetParameter(1);
    double slope_2_error = myFunc2->GetParError(1);

    TLatex* latex5 = new TLatex(0.18, 0.59, Form("slope: %.4f +/- %.4f",slope_2, slope_2_error ));
    latex5->SetNDC();
    latex5->SetTextSize(20);
    latex5->SetTextFont(43);
    latex5->SetTextColor(kBlue);
    latex5->Draw("same");

    TLatex* latex6 = new TLatex(0.18, 0.56, Form("intersect: %.4f +/- %.4f",intersect_2, intersect_2_error ));
    latex6->SetNDC();
    latex6->SetTextSize(20);
    latex6->SetTextFont(43);
    latex6->SetTextColor(kBlue);
    latex6->Draw("same");



    r4->Draw("same");
    lmult->Draw("same");
    r11->Draw("same");
    r22->Draw("same");

    TLegend *w2 = new TLegend(0.6,0.14,0.8,0.24);
    w2->SetLineColor(kWhite);
    w2->SetFillColor(0);
    w2->SetTextSize(22);
    w2->SetTextFont(43);
    w2->AddEntry(gr_new1, "#Psi_{EP}(Pb-going)", "P");
    w2->AddEntry(gr_new2, "#Psi_{EP}(p-going)", "P");
    w2->Draw("same");







}