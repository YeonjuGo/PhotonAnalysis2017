#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

#include "TSystem.h"
#include "TTree.h"
#include "TKey.h"
#include "TH1.h"
#include "TH2.h"
#include "TPave.h"
#include "TText.h"

#include "TROOT.h"
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TF1.h"

#include "RooFit.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooArgSet.h"

#include "TStyle.h"
#include "TLatex.h"
#include "TDirectory.h"
#include "TCollection.h"
#include "TPostScript.h"
#include "TMath.h"

//#include "toyStudy.h"

using namespace RooFit;
using namespace std;

/////////////////////////////////////////////////
//              P A R A M E T E R S            //
/////////////////////////////////////////////////


// pp or PbPb?
bool isPbPb = false;
TString collTag = "pp"; // isPbPb ? "PbPb" : "pp";

// do the toy study for the correction factors?
bool doToys = false;

// Location of the files
const char* fDataName = "tnp_Ana_data_pp_BWResCBExp_L1.root";
const char* fMCName = "tnp_Ana_mc_pp_BWResCBExp_L1.root";


//////////////////////////////////////////////////////////////////////////

// Other parameters
TString etaTag("recoIDPho_abseta");
TString ptTag("recoIDPho_1bin");
TString allTag("recoIDPho_1bin");

// Automatic parameters (shouldn't require modification by the user)
const int nAbsEtaBins = 1;
TString cutTag("phoTree"); 
TString cutLegend("pho L1");
TString absetaTag("recoIDPho_abseta");
TString absetaVar("probe_abseta");
ofstream file_sfs("correction_functions.txt");

const double effmin = 0.;
const double sfrange = 0.1;

// Function Define
TH2F *plotEff2D(RooDataSet *a, TString b);
vector<TGraphAsymmErrors*> plotEff_Nbins(RooDataSet *a, int aa, const char* varx, const char* var2);
TGraphAsymmErrors *plotEff_1bin(RooDataSet *a, int aa, const char* varx);
void formatTH1F(TH1* a, int b, int c, int d);
void formatTGraph(TGraph* a, int b, int c, int d);
void formatTLeg(TLegend* a);
void CalEffErr(TGraph *a, double *b);
void CalEffErr(vector<TGraphAsymmErrors*> a, double **b);

// From here you need to set up your environments.
void TnPEffDraw() {

  // gROOT->Macro("~/logon.C");
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  gStyle->SetTitle(0);
  gStyle->SetPadLeftMargin(0.11);
  gStyle->SetPadBottomMargin(0.13);
  gStyle->SetTitleYOffset(1.0);

  
  //data and MC root files as well as single bin for integrated efficiency
  TFile *f9 = new TFile(fMCName);
  TFile *f10 = new TFile(fDataName);

  cout << "here1" << endl;

  TCanvas *c1 = new TCanvas("c1","",700,600);

  vector<RooDataSet*> daPtData0, daPtData1;

  if (nAbsEtaBins==1)
  {
     cout << "here2" << endl;
     daPtData0.push_back((RooDataSet*)f9->Get(cutTag + "/" + ptTag + "/fit_eff")); 
     daPtData1.push_back((RooDataSet*)f10->Get(cutTag + "/" + ptTag + "/fit_eff")); 
  }
  else
  {
     for (int i=0; i<nAbsEtaBins; i++)
     {
        cout << "here2.1" << endl;
        daPtData0.push_back((RooDataSet*)f9->Get(cutTag + "/" + ptTag + Form("%i/fit_eff",i))); 
        daPtData1.push_back((RooDataSet*)f10->Get(cutTag + "/" + ptTag + Form("%i/fit_eff",i))); 
     }
  }

  vector<TGraphAsymmErrors*> ComPt0, ComPt1;
  
  cout << "daPtData0.size() =  " << daPtData0.size() << endl;
  for (unsigned int i=0; i<daPtData0.size(); i++)
  {
     cout << "here3.0" << endl;
     ComPt0.push_back(plotEff_1bin(daPtData0[i], 1, "probe_pt"));
     ComPt1.push_back(plotEff_1bin(daPtData1[i], 1, "probe_pt"));
  }

  cout << "here3" << endl;

  /*
  RooDataSet *daEtaData0 = (RooDataSet*)f9->Get(cutTag + "/" + etaTag + "/fit_eff"); 
  RooDataSet *daEtaData1 = (RooDataSet*)f10->Get(cutTag + "/" + etaTag + "/fit_eff"); 

  TGraphAsymmErrors *ComEta0 = plotEff_1bin(daEtaData0, 1, "probe_abseta");
  TGraphAsymmErrors *ComEta1 = plotEff_1bin(daEtaData1, 1, "probe_abseta");

  RooDataSet *daPtMC1Bin0 = (RooDataSet*)f9->Get(cutTag + "/" + allTag + "/fit_eff"); 
  RooDataSet *daPtData1Bin0 = (RooDataSet*)f10->Get(cutTag + "/" + allTag + "/fit_eff"); 
  RooDataSet *daAbsEtaMC1 = (RooDataSet*)f9->Get(cutTag + "/" + absetaTag + "/fit_eff"); 
  RooDataSet *daAbsEtaData1 = (RooDataSet*)f10->Get(cutTag + "/" + absetaTag + "/fit_eff"); 
  */
  /*
  TGraphAsymmErrors* Com0Pt0 = plotEff_1bin(daPtMC1Bin0,0,"probe_abseta");
  TGraphAsymmErrors* Com0Pt1 = plotEff_1bin(daPtData1Bin0,0,"probe_abseta");
  vector<TGraphAsymmErrors*> Com0AbsEta0 = plotEff_Nbins(daAbsEtaMC1,0,"probe_pt",absetaVar);
  vector<TGraphAsymmErrors*> Com0AbsEta1 = plotEff_Nbins(daAbsEtaData1,0,"probe_pt",absetaVar);
  */

  cout << "here4" << endl;

  int nbins_abseta = ComPt0.size();
  cout << "nbins_abseta = " << nbins_abseta << endl;
  for (int i=0; i<nbins_abseta; i++)
  {
     ComPt0[i]->SetMarkerStyle(20);
     ComPt0[i]->SetMarkerSize(1.4);
     ComPt0[i]->SetMarkerColor(kRed+1);
     ComPt0[i]->SetLineColor(kRed+1);
     ComPt1[i]->SetMarkerStyle(25);
     ComPt1[i]->SetMarkerSize(1.4);
     ComPt1[i]->SetMarkerColor(kBlue+1);
     ComPt1[i]->SetLineColor(kBlue+1);
  }

  /*
  ComEta0->SetMarkerStyle(20);
  ComEta0->SetMarkerSize(1.4);
  ComEta0->SetMarkerColor(kRed+1);
  ComEta0->SetLineColor(kRed+1);
  ComEta1->SetMarkerStyle(25);
  ComEta1->SetMarkerSize(1.4);
  ComEta1->SetMarkerColor(kBlue+1);
  ComEta1->SetLineColor(kBlue+1);
  */

  cout << "here 4.1" << endl;

  // 1 Bin
  double Trk0[4];
  double Trk1[4];
  double** TrkAbsEta0 = new double*[nbins_abseta];
  double** TrkAbsEta1 = new double*[nbins_abseta];
  for (int i=0; i<nbins_abseta; i++) 
  {
    cout << "i = " << i << endl;
     TrkAbsEta0[i] = new double[4];
     TrkAbsEta1[i] = new double[4];
  }

  //CalEffErr(Com0Pt0, Trk0);
  //CalEffErr(Com0Pt1, Trk1);
  //CalEffErr(Com0AbsEta0, TrkAbsEta0);
  //CalEffErr(Com0AbsEta1, TrkAbsEta1);

  cout << "all errors counted, going to canvas" << endl;

  c1->cd();
  TPad *pad1 = new TPad("pad1","pad1",0, 0.26 ,1,1);
  c1->cd();
  TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.3*0.96);
  pad1->SetBottomMargin(0.04);
  pad2->SetTopMargin(0);
  pad2->SetFillColor(0);
  pad2->SetFillStyle(0);
  pad2->SetBottomMargin(gStyle->GetPadBottomMargin()/0.3);
  pad1->SetTopMargin(gStyle->GetPadTopMargin()/0.7);
  // pad2->SetGridy();
  pad1->Draw();
  pad1->cd();

  // // adapt text size
  // lTextSize *= 1./0.7;

  cout << "creating TH1F" << endl;

  TH1F *hPad = new TH1F("hPad",";p^{#gamma}_{T} [GeV/c]; Efficiency",1,40,130);
  TH1F *hPad1 = new TH1F("hPad1",";#eta^{#gamma} ; Efficiency",1,0,1.5);
  hPad->GetXaxis()->CenterTitle();
  hPad1->GetXaxis()->CenterTitle();
  hPad->GetXaxis()->SetLabelSize(0.);
  hPad->GetXaxis()->SetTitleSize(0.);
  hPad->GetXaxis()->SetTitleOffset(1.2);
  hPad->GetYaxis()->SetLabelSize(0.05);
  hPad->GetYaxis()->SetTitleSize(0.05);
  hPad->GetYaxis()->SetTitleOffset(1.);
  hPad1->GetXaxis()->SetLabelSize(0.);
  hPad1->GetXaxis()->SetTitleSize(0.);
  hPad1->GetXaxis()->SetTitleOffset(1.2);
  hPad1->GetYaxis()->SetLabelSize(0.05);
  hPad1->GetYaxis()->SetTitleSize(0.05);
  hPad1->GetYaxis()->SetTitleOffset(1.);

  hPad->GetYaxis()->SetRangeUser(effmin,1.05);
  hPad1->GetYaxis()->SetRangeUser(effmin,1.05);

  cout << "here 5!" << endl;

  pad2->cd();
  pad2->SetGridy();
  double tsize = (1./0.36)*hPad->GetYaxis()->GetTitleSize(); // 1./0.36
  cout << "tsize = " << tsize << endl;
  cout << "sfrange = " << sfrange << endl;
  hPad->Draw();
  TH1F *hPadr = (TH1F*) hPad->Clone("hPadr"); 
  cout << "after clone" << endl;
  hPadr->GetYaxis()->SetRangeUser(1.-sfrange,1.+sfrange);
  hPadr->GetYaxis()->SetTitle("Scale Factor");
  hPadr->GetXaxis()->SetTitleSize(tsize);
  hPadr->GetXaxis()->SetLabelSize(tsize);
  hPadr->GetYaxis()->SetTitleSize(tsize);
  hPadr->GetYaxis()->SetLabelSize(tsize);
  hPadr->GetYaxis()->SetNdivisions(504,kTRUE);
  cout << "hPadr->GetYaxis()->SetNdivisions(504,kTRUE)" << endl;
  TH1F *hPad1r = (TH1F*) hPad1->Clone("hPad1r"); hPad1r->GetYaxis()->SetRangeUser(1.-sfrange,1.+sfrange);
  hPad1r->GetYaxis()->SetTitle("Scale Factor");
  hPad1r->GetXaxis()->SetTitleSize(tsize);
  hPad1r->GetXaxis()->SetLabelSize(tsize);
  hPad1r->GetYaxis()->SetTitleSize(tsize);
  hPad1r->GetYaxis()->SetLabelSize(tsize);
  hPad1r->GetYaxis()->SetNdivisions(504,kTRUE);

  cout << "before  pad1->cd(); " << endl;

  pad1->cd();

  cout << "here 6!" << endl;

  for (int i=0; i<nbins_abseta; i++)
  {
    cout << "here 7!" << endl;
    cout << " i = " << i << endl;
     pad1->cd();
     hPad->Draw();
     TLatex *lt1 = new TLatex();
     lt1->SetNDC();

     char legs[512];
     TLegend *leg1 = new TLegend(0.43,0.05,0.66,0.43);
     leg1->SetFillStyle(0);
     leg1->SetFillColor(0);
     leg1->SetBorderSize(0);
     leg1->SetTextSize(0.035);
     double ptmin = ((RooRealVar*) daPtData0[i]->get()->find("probe_pt"))->getBinning().binLow(0);
     double etamin, etamax;
     if (daPtData0[i]->get()->find("probe_abseta"))
     {
       cout << "probe_abseta found" << endl;
        etamin = ((RooRealVar*) daPtData0[i]->get()->find("probe_abseta"))->getBinning().binLow(0);
        etamax = ((RooRealVar*) daPtData0[i]->get()->find("probe_abseta"))->getBinning().binHigh(0);
        leg1->SetHeader(TString("#splitline{") + cutLegend + Form(" Efficiency}{(p^{#gamma}_{T}>%.1f, |#eta| #in [%.1f, %.1f])}",ptmin,etamin,etamax));
     }
     else
     {
       cout << "probe_abseta not found, looking for eta" << endl;
        etamin = ((RooRealVar*) daPtData0[i]->get()->find("eta"))->getBinning().binLow(0);
        etamax = ((RooRealVar*) daPtData0[i]->get()->find("eta"))->getBinning().binHigh(0);
        leg1->SetHeader(TString("#splitline{") + cutLegend + Form(" Efficiency}{(p^{#gamma}_{T}>%.1f, #eta #in [%.1f, %.1f])}",ptmin,etamin,etamax));
     }
     sprintf(legs,"MC eff: %.4f^{ + %.3f}_{ - %.3f}", ComPt0[i]->Eval(50), ComPt0[i]->GetErrorYhigh(0), ComPt0[i]->GetErrorYlow(0));
     leg1->AddEntry(ComPt0[i],legs,"pl");
     sprintf(legs,"Data eff: %.4f^{ + %.3f}_{ - %.3f}", ComPt1[i]->Eval(50), ComPt1[i]->GetErrorYhigh(0), ComPt1[i]->GetErrorYlow(0));
     leg1->AddEntry(ComPt1[i],legs,"pl");
     leg1->Draw("same");

     ComPt0[i]->Draw("pz same");
     ComPt1[i]->Draw("pz same");

     lt1->SetTextSize(0.05);
     lt1->DrawLatex(0.43,0.80,"CMS Preliminary");
     lt1->DrawLatex(0.43,0.74,collTag + "  #sqrt{s} = 5.02 TeV");

     // now take care of the data/mc ratio panel
     c1->cd();
     // pad2->SetFrameFillStyle(4000);
     pad2->Draw();
     pad2->cd();
     hPadr->Draw();

     int nbins = ComPt0[i]->GetN();
     double *xr = new double[nbins];
     double *yr = new double[nbins];
     double *xrlo = new double[nbins];
     double *yrlo = new double[nbins];
     double *xrhi = new double[nbins];
     double *yrhi = new double[nbins];

     // here we assume that the mc uncertainty is negligible compared to the data one: simply scale everything by the central value.
     for (int j=0; j<nbins; j++)
     {
        xr[j] = ComPt1[i]->GetX()[j];
        xrlo[j] = ComPt1[i]->GetErrorXlow(j);
        xrhi[j] = ComPt1[i]->GetErrorXhigh(j);
        yr[j] = ComPt1[i]->GetY()[j]/ComPt0[i]->GetY()[j];
        yrlo[j] = ComPt1[i]->GetErrorYlow(j)/ComPt0[i]->GetY()[j];
        yrhi[j] = ComPt1[i]->GetErrorYhigh(j)/ComPt0[i]->GetY()[j];
     }
     TGraphAsymmErrors *gratio = new TGraphAsymmErrors(nbins,xr,yr,xrlo,xrhi,yrlo,yrhi);
     gratio->SetMarkerStyle(20);
     gratio->SetMarkerColor(kBlack);
     gratio->SetMarkerSize(1.0);
     gratio->SetLineColor(kBlack);
     gratio->SetLineWidth(1);
     gratio->Draw("pz same");

     // save
     c1->SaveAs(cutTag + Form("Eff%i_",i) + collTag + "_RD_MC_PT_L1.root");
     c1->SaveAs(cutTag + Form("Eff%i_",i) + collTag + "_RD_MC_PT_L1.pdf");

     break;

     // in case we are looking at muon Id + trigger: get the scale factor at the same time
#ifdef MUIDTRG
     pad1->cd();
     double ptmax = ((RooRealVar*) daPtData0[i]->get()->find("pt"))->getMax();
     TLatex tchi; tchi.SetNDC();
     tchi.SetTextSize(0.035);
     double chi2, pval; int dof;

     // fit data
     TF1 *fdata = new TF1("fdata","[0]*TMath::Erf((x-[1])/[2])",ptmin,ptmax);
     fdata->SetParNames("eff0","x0","m");
     // Initialize the normalization to the efficiency in the last point
     fdata->SetParameters(ComPt1[i]->GetX()[ComPt1[i]->GetN()-1],0.1,1.0);
     fdata->SetParLimits(0,0,1);
     fdata->SetParLimits(1,0.,10.);
     fdata->SetParLimits(2,0,10.);
     fdata->SetLineWidth(2);
     fdata->SetLineColor(kBlue);
     ComPt1[i]->Fit(fdata,"WRME");
     leg1->AddEntry(fdata,Form("%0.2f*TMath::Erf((x-%0.2f)/%0.2f)",fdata->GetParameter(0),fdata->GetParameter(1),fdata->GetParameter(2)),"pl");

     chi2 = ComPt1[i]->Chisquare(fdata);
     dof = ComPt1[i]->GetN() - fdata->GetNpar();
     pval = TMath::Prob(chi2,dof);
     tchi.SetTextColor(kBlue);
     tchi.DrawLatex(0.6,0.92,Form("#chi^{2}/dof = %.1f/%d (p-value: %.2f)",chi2,dof,pval));

     // fit mc
     TF1 *fmc = (TF1*) fdata->Clone("fmc");;
     // Initialize the normalization to the efficiency in the last point
     if (isPbPb) fmc->SetParameters(ComPt0[i]->GetX()[ComPt0[i]->GetN()-1],0.5,2.4); 
     else fmc->SetParameters(ComPt0[i]->GetX()[ComPt0[i]->GetN()-1],2.2,1.5); 
     fmc->SetLineColor(kRed);
     ComPt0[i]->Fit(fmc,"WRME");
     leg1->AddEntry(fmc,Form("%0.2f*TMath::Erf((x-%0.2f)/%0.2f)",fmc->GetParameter(0),fmc->GetParameter(1),fmc->GetParameter(2)),"pl");

     chi2 = ComPt0[i]->Chisquare(fmc);
     dof = ComPt0[i]->GetN() - fmc->GetNpar();
     pval = TMath::Prob(chi2,dof);
     tchi.SetTextColor(kRed);
     tchi.DrawLatex(0.6,0.88,Form("#chi^{2}/dof = %.1f/%d (p-value: %.2f)",chi2,dof,pval));

     leg1->Draw();

     // now the bottom panel
     pad2->cd();
     // hPadr->Draw();
     TF1 *fratio = new TF1("fratio","[0]*TMath::Erf((x-[1])/[2])/([3]*TMath::Erf((x-[4])/[5]))",ptmin,ptmax);
     fratio->SetParameters(
           fdata->GetParameter(0),fdata->GetParameter(1),fdata->GetParameter(2),
           fmc->GetParameter(0),fmc->GetParameter(1),fmc->GetParameter(2)
           );
     fratio->Draw("same");

     chi2 = gratio->Chisquare(fratio);
     dof = gratio->GetN() - fratio->GetNpar();
     pval = TMath::Prob(chi2,dof);
     tchi.SetTextColor(kBlack);
     tchi.SetTextSize(0.035*0.7/0.3);
     tchi.DrawLatex(0.6,0.8,Form("#chi^{2}/dof = %.1f/%d (p-value: %.2f)",chi2,dof,pval));

     // save
     c1->SaveAs(cutTag + Form("SF%i_",i) + collTag + "_RD_MC_PT.root");
     c1->SaveAs(cutTag + Form("SF%i_",i) + collTag + "_RD_MC_PT.pdf");

     // print the fit results to file
     file_sfs << "Data " << etamin << " " << etamax << endl;
     file_sfs << Form("%0.4f*TMath::Erf((x-%0.4f)/%0.4f)",fdata->GetParameter(0),fdata->GetParameter(1),fdata->GetParameter(2)) << endl;
     file_sfs << "MC " << etamin << " " << etamax << endl;
     file_sfs << Form("%0.4f*TMath::Erf((x-%0.4f)/%0.4f)",fmc->GetParameter(0),fmc->GetParameter(1),fmc->GetParameter(2)) << endl;
     file_sfs << endl;

     // toys study
     if (doToys) toyStudy(ComPt1[i], ComPt0[i], fdata, fmc, cutTag + Form("toys%i_",i) + collTag + "_RD_MC_PT");
#endif // ifdef MUIDTRG
  }

   //---------- This is for eta dependence
  //pad1->cd();
  //hPad1->Draw();

  /*
  ComEta0->Draw("pz same");
  ComEta1->Draw("pz same");
  */

  TLatex *lt1 = new TLatex();
  lt1->SetNDC();
  char legs[512];
  TLegend *leg1 = new TLegend(0.43,0.21,0.66,0.43);
  leg1->SetFillStyle(0);
  leg1->SetFillColor(0);
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.035);
  //  double ptmin = ((RooRealVar*) daEtaData0->get()->find("pt"))->getBinning().binLow(0);
  double ptmin =  0;
  leg1->SetHeader(TString("#splitline{") + cutLegend + Form(" Efficiency}{(p^{e}_{T}>%.1f)}",ptmin));
  sprintf(legs,"MC STARLIGHT: %.4f^{ + %.3f}_{ - %.3f}", Trk0[0], Trk0[1], Trk0[2]);
  leg1->AddEntry(ComPt0[0],legs,"pl");
  sprintf(legs,"Data: %.4f^{ + %.3f}_{ - %.3f}", Trk1[0], Trk1[1], Trk1[2]);
  leg1->AddEntry(ComPt1[0],legs,"pl");
  leg1->Draw("same");
  leg1->Draw("same");

  lt1->SetTextSize(0.05);
  lt1->DrawLatex(0.43,0.60,"CMS Preliminary");
  //lt1->DrawLatex(0.43,0.54,"pp  #sqrt{s} = 5.02 TeV");
  lt1->DrawLatex(0.43,0.54,collTag + "  #sqrt{s_{NN}} = 5.02 TeV");

  // now take care of the data/mc ratio panel
  c1->cd();
  // pad2->SetFrameFillStyle(4000);
  pad2->Draw();
  pad2->cd();
  hPad1r->Draw();

  /*
  int nbins = ComEta0->GetN();
  double *xr = new double[nbins];
  double *yr = new double[nbins];
  double *xrlo = new double[nbins];
  double *yrlo = new double[nbins];
  double *xrhi = new double[nbins];
  double *yrhi = new double[nbins];

  // here we assume that the mc uncertainty is negligible compared to the data one: simply scale everything by the central value.
  for (int j=0; j<nbins; j++)
  {
     xr[j] = ComEta1->GetX()[j];
     xrlo[j] = ComEta1->GetErrorXlow(j);
     xrhi[j] = ComEta1->GetErrorXhigh(j);
     yr[j] = ComEta1->GetY()[j]/ComEta0->GetY()[j];
     yrlo[j] = ComEta1->GetErrorYlow(j)/ComEta0->GetY()[j];
     yrhi[j] = ComEta1->GetErrorYhigh(j)/ComEta0->GetY()[j];
  }
  TGraphAsymmErrors *gratio1 = new TGraphAsymmErrors(nbins,xr,yr,xrlo,xrhi,yrlo,yrhi);
  gratio1->SetMarkerStyle(20);
  gratio1->SetMarkerColor(kBlack);
  gratio1->SetMarkerSize(1.0);
  gratio1->SetLineColor(kBlack);
  gratio1->SetLineWidth(1);
  gratio1->Draw("pz same");

  c1->SaveAs(cutTag + "Eff_" + collTag + "_RD_MC_Eta.root");
  c1->SaveAs(cutTag + "Eff_" + collTag + "_RD_MC_Eta.pdf");
  
  */

  file_sfs.close();
}

void formatTH1F(TH1* a, int b, int c, int d){
  a->SetLineWidth(2);
  a->SetLineStyle(c);
  a->SetMarkerSize(2);
  a->SetLineColor(b);
  a->SetMarkerColor(b);
  a->GetYaxis()->SetTitle("Efficiency");
  if(d == 1){
    a->GetXaxis()->SetTitle("p_{T} [GeV/c]");
  }else if(d == 2){
    a->GetXaxis()->SetTitle("#eta");
  }else if(d == 3){
    a->GetXaxis()->SetTitle("rapidity");
  }else if(d == 4){
    a->GetXaxis()->SetTitle("Centrality");
  }
  a->GetXaxis()->CenterTitle(true);
  a->GetXaxis()->SetLabelSize(0.05);
  a->GetXaxis()->SetTitleSize(0.05);
  a->GetXaxis()->SetTitleOffset(0.9);
  a->GetYaxis()->SetLabelSize(0.05);
  a->GetYaxis()->SetTitleSize(0.05);
  a->GetYaxis()->SetTitleOffset(0.8);

}

void formatTLeg(TLegend* a){

  a->SetFillStyle(0);
  a->SetFillColor(0);
  a->SetBorderSize(0);
  a->SetTextSize(0.03);

}


void formatTGraph(TGraph* a, int b, int c, int d)
{

  a->SetMarkerStyle(c);
  a->SetMarkerColor(b);
  a->SetMarkerSize(1.0);
  a->SetLineColor(b);
  a->SetLineWidth(1);
  a->GetXaxis()->SetLabelSize(0.05);
  a->GetXaxis()->SetTitleSize(0.06);
  a->GetXaxis()->SetTitleOffset(0.9);
  a->GetYaxis()->SetTitle("Efficiency");
  a->GetXaxis()->CenterTitle();
  if(d == 1){ 
    a->GetXaxis()->SetTitle("p_{T} (GeV/c)"); 
  }else if(d == 2){ 
    a->GetXaxis()->SetTitle("eta"); 
  }else if(d == 3){ 
    a->GetXaxis()->SetTitle("rapidity"); 
  }else if(d == 4){
    a->GetXaxis()->SetTitle("Centrality");
  }   
  a->GetYaxis()->SetRangeUser(0,1);
  a->GetXaxis()->SetRangeUser(0,10);
  a->GetYaxis()->SetLabelSize(0.05);
  a->GetYaxis()->SetTitleSize(0.05);
  a->GetYaxis()->SetTitleOffset(0.9);


}

TGraphAsymmErrors *plotEff_1bin(RooDataSet *a, int aa, const char* varx){
  cout << "in plotEff_1bin" << endl;
  const RooArgSet *set = a->get();
  cout << "varx = " << varx << endl;
  RooRealVar *xAx = (RooRealVar*)set->find(varx);
  cout << "pt found" << endl;
  RooRealVar *eff = (RooRealVar*)set->find("efficiency");

  cout << "efficiency found" << endl;

  const int nbins = xAx->getBinning().numBins();

  cout << "nbins = " << nbins << endl;

  double tx[nbins], txhi[nbins], txlo[nbins];
  double ty[nbins], tyhi[nbins], tylo[nbins];

  for (int i=0; i<nbins; i++) {
    a->get(i);
    ty[i] = eff->getVal();
    tx[i] = xAx->getVal();
    txhi[i] = fabs(xAx->getErrorHi());
    txlo[i] = fabs(xAx->getErrorLo()); 
    tyhi[i] = fabs(eff->getErrorHi());
    tylo[i] = fabs(eff->getErrorLo()); 
  }

  cout<<"NBins : "<<nbins<<endl;

  const double *x = tx;
  const double *xhi = txhi;
  const double *xlo = txlo;
  const double *y = ty;
  const double *yhi = tyhi;
  const double *ylo = tylo;


  TGraphAsymmErrors *b = new TGraphAsymmErrors();
  if(aa == 1) {*b = TGraphAsymmErrors(nbins,x,y,xlo,xhi,ylo,yhi);}
  if(aa == 0) {*b = TGraphAsymmErrors(nbins,x,y,0,0,ylo,yhi);}
  b->SetMaximum(1.1);
  b->SetMinimum(0.0);
  b->SetMarkerStyle(20);
  b->SetMarkerColor(kRed+2);
  b->SetMarkerSize(1.0);
  b->SetTitle("");
  b->GetXaxis()->SetTitleSize(0.1);
  b->GetYaxis()->SetTitleSize(0.1);
  b->GetXaxis()->SetTitle("#eta");
  b->GetYaxis()->SetTitle("Efficiency");
  b->GetXaxis()->CenterTitle();
  //b->Draw("apz");

  for (int i=0; i<nbins; i++) {
    cout << x[i] << " " << y[i] << " " << yhi[i] << " " << ylo[i] << endl;
  }

  return b;

}

vector<TGraphAsymmErrors*> plotEff_Nbins(RooDataSet *a, int aa, const char* varx, const char* var2){
  const RooArgSet *set = a->get();
  RooRealVar *xAx = (RooRealVar*)set->find(varx);
  RooRealVar *abseta = (RooRealVar*)set->find(var2);
  RooRealVar *eff = (RooRealVar*)set->find("efficiency");

  const int nbins = xAx->getBinning().numBins();
  const int nbins2 = abseta->getBinning().numBins();
  cout << nbins << " " << nbins2 << endl;

  double **tx = new double*[nbins2], **txhi = new double*[nbins2], **txlo = new double*[nbins2];
  double **ty = new double*[nbins2], **tyhi = new double*[nbins2], **tylo = new double*[nbins2];
  for (int i=0; i<nbins2; i++)
  {
     tx[i] = new double[nbins];
     txlo[i] = new double[nbins];
     txhi[i] = new double[nbins];
     ty[i] = new double[nbins];
     tylo[i] = new double[nbins];
     tyhi[i] = new double[nbins];
  }

  for (int i=0; i<nbins*nbins2; i++) {
    a->get(i);
    int bin1 = xAx->getBinning().binNumber(xAx->getVal());
    int bin2 = abseta->getBinning().binNumber(abseta->getVal());
    ty[bin2][bin1] = eff->getVal();
    tx[bin2][bin1] = xAx->getVal();
    txhi[bin2][bin1] = fabs(xAx->getErrorHi());
    txlo[bin2][bin1] = fabs(xAx->getErrorLo()); 
    tyhi[bin2][bin1] = fabs(eff->getErrorHi());
    tylo[bin2][bin1] = fabs(eff->getErrorLo()); 
  }

  cout<<"NBins pt: "<<nbins<<endl;


  vector<TGraphAsymmErrors*> result;
  for (int i=0; i<nbins2; i++)
  {
     const double *x = tx[i];
     const double *xhi = txhi[i];
     const double *xlo = txlo[i];
     const double *y = ty[i];
     const double *yhi = tyhi[i];
     const double *ylo = tylo[i];
     TGraphAsymmErrors *b = new TGraphAsymmErrors();
     if(aa == 1) {*b = TGraphAsymmErrors(nbins,x,y,xlo,xhi,ylo,yhi);}
     if(aa == 0) {*b = TGraphAsymmErrors(nbins,x,y,0,0,ylo,yhi);}
     b->SetMaximum(1.1);
     b->SetMinimum(0.0);
     b->SetMarkerStyle(20);
     b->SetMarkerColor(kRed+2);
     b->SetMarkerSize(1.0);
     b->SetTitle("");
     b->GetXaxis()->SetTitleSize(0.05);
     b->GetYaxis()->SetTitleSize(0.05);
     b->GetXaxis()->SetTitle("p_{T} [GeV/c]");
     b->GetYaxis()->SetTitle("Efficiency");
     b->GetXaxis()->CenterTitle();
     //b->Draw("apz");
     result.push_back(b);
  }

  // for (int i=0; i<nbins; i++) {
  //   cout << x[i] << " " << y[i] << " " << yhi[i] << " " << ylo[i] << endl;
  // }

  return result;

}


TH2F *plotEff2D(RooDataSet *a, TString b){
  const RooArgSet *set = a->get();
  RooRealVar *yAx = (RooRealVar*)set->find("pt");
  RooRealVar *xAx = (RooRealVar*)set->find("eta");
  RooRealVar *eff = (RooRealVar*)set->find("efficiency");

  //const int xnbins = xAx->getBinning().numBins();
  //const int ynbins = yAx->getBinning().numBins();

  const double *xvbins = xAx->getBinning().array();
  const double *yvbins = yAx->getBinning().array();

  TH2F* h = new TH2F(b, "", xAx->getBinning().numBins(), xvbins, yAx->getBinning().numBins(), yvbins);

  gStyle->SetPaintTextFormat("5.2f");
  gStyle->SetPadRightMargin(0.12);
  gStyle->SetPalette(1);
  h->SetOption("colztexte");
  h->GetZaxis()->SetRangeUser(-0.001,1.001);
  h->SetStats(kFALSE);
  h->GetYaxis()->SetTitle("p_{T} [GeV/c]");
  h->GetXaxis()->SetTitle("#eta");
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
  h->GetXaxis()->SetTitleSize(0.05);
  h->GetYaxis()->SetTitleSize(0.05);
  h->GetYaxis()->SetTitleOffset(0.8);
  h->GetXaxis()->SetTitleOffset(0.9);
  for(int i=0; i<a->numEntries(); i++){
    a->get(i);
    h->SetBinContent(h->FindBin(xAx->getVal(), yAx->getVal()), eff->getVal());
    h->SetBinError(h->FindBin(xAx->getVal(), yAx->getVal()), (eff->getErrorHi()-eff->getErrorLo())/2.);
  }

  return h;

}


void CalEffErr(TGraph *a, double *b){
    const int nbins = 100;
    double x[nbins], y[nbins];
    double sum = 0, errHighSum = 0, errLowSum = 0, sqSumHigh = 0, sqSumLow = 0;
    //double b[3] = 0;
    
    int nBins = a->GetN();
    for(int i=0;i<a->GetN();i++){
        a->GetPoint(i,x[i],y[i]);
        //cout<<"Eff x = "<<x[i]<<" y = "<<y[i]<<endl;
        double eHigh = a->GetErrorYhigh(i);
        double eLow = a->GetErrorYlow(i);
        //cout<<"Err high = "<<eHigh<<" low = "<<eLow<<endl;
        sum += y[i];
        errHighSum += eHigh;
        sqSumHigh += eHigh*eHigh;
        errLowSum += eLow;
        sqSumLow += eLow*eLow;
    }
    b[0] = sum/nBins;
    b[1] = sqrt(sqSumHigh)/nBins;
    b[2] = sqrt(sqSumLow)/nBins;
    //cout<<"b1 : "<<b[0]<<", b2 : "<<b[1]<<", b3 : "<<b[2]<<endl;
    
    cout<<b[0]<<"^{"<<b[1]<<"}_{"<<b[2]<<"}"<<endl;
    //return b[3];
}

void CalEffErr(vector<TGraphAsymmErrors*> a, double **b){
    const int nbins = 100;
    const int vsize = a.size();

    for (int vbin=0; vbin<vsize; vbin++)
    {
       double x[nbins], y[nbins];
       double sum = 0, errHighSum = 0, errLowSum = 0, sqSumHigh = 0, sqSumLow = 0;
       //double b[3] = 0;

       int nBins = a[vbin]->GetN();
       for(int i=0;i<a[vbin]->GetN();i++){
          a[vbin]->GetPoint(i,x[i],y[i]);
          //cout<<"Eff x = "<<x[i]<<" y = "<<y[i]<<endl;
          double eHigh = a[vbin]->GetErrorYhigh(i);
          double eLow = a[vbin]->GetErrorYlow(i);
          //cout<<"Err high = "<<eHigh<<" low = "<<eLow<<endl;
          sum += y[i];
          errHighSum += eHigh;
          sqSumHigh += eHigh*eHigh;
          errLowSum += eLow;
          sqSumLow += eLow*eLow;
       }
       b[vbin][0] = sum/nBins;
       b[vbin][1] = sqrt(sqSumHigh)/nBins;
       b[vbin][2] = sqrt(sqSumLow)/nBins;
       //cout<<"b1 : "<<b[0]<<", b2 : "<<b[1]<<", b3 : "<<b[2]<<endl;

       cout<<b[vbin][0]<<"^{"<<b[vbin][1]<<"}_{"<<b[vbin][2]<<"}"<<endl;
    }
    //return b[3];
}

