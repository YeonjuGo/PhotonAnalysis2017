// Created : 2017 April 11
// Modified : 2018 Feb 15
// Author : Yeonju Go
// 
// To compare two datasets (ex. allqcdphoton and emenricheddijet) 

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"

int compareTwo(TTree* t1=0 ,TTree* t2=0,TString var="pt", int nBins=10, double xMin=0, double xMax=10, TCut cut1="",TCut cut2="", const char* cap="");
void compare_PDs(int run= 263406, int lumi = 89){

    const char* fname_1="0";
    const char* fname_2="0";
    fname_1=Form("/home/goyeonju/CMS/Files/photon2016/temp/HiForest_HIHardProbes_run%d_lumi%d.root",run,lumi);
    fname_2=Form("/home/goyeonju/CMS/Files/photon2016/temp/HiForest_HIHardProbesPhotons_run%d_lumi%d.root",run,lumi);

    TFile* f1 = new TFile(fname_1);
    TTree* t1 = (TTree*) f1 -> Get("ggHiNtuplizer/EventTree");
    TTree* t1_hi = (TTree*) f1 -> Get("hiEvtAnalyzer/HiTree");
    TTree* t1_evt = (TTree*) f1 -> Get("hiEvtAnalyzer/HltTree");
    TTree* t1_hlt= (TTree*) f1 -> Get("hltanalysis/HltTree");
    t1->AddFriend(t1_hi);
    t1->AddFriend(t1_evt);
    t1->AddFriend(t1_hlt);
    TFile* f2 = new TFile(fname_2);
    TTree* t2 = (TTree*) f2 -> Get("ggHiNtuplizer/EventTree");
    TTree* t2_hi = (TTree*) f2 -> Get("hiEvtAnalyzer/HiTree");
    TTree* t2_evt = (TTree*) f2 -> Get("hiEvtAnalyzer/HltTree");
    TTree* t2_hlt= (TTree*) f2 -> Get("hltanalysis/HltTree");
    t2->AddFriend(t2_hi);
    t2->AddFriend(t2_evt);
    t2->AddFriend(t2_hlt);

    TString cap = Form("HIHardProbes_vs_HIHardProbesPhotons_run%d_lumi%d",run,lumi);
    TCut cut1 = "(1==1)";
    TCut cut2 = "(1==1)";

    int nBins = 100;
    TCut trigCut_ = "HLT_HISinglePhoton20_Eta1p5_v2==1";
    compareTwo(t1, t2, "phoEt",nBins, 0, 100.0,trigCut_,trigCut_,cap);

} // main function

int compareTwo(TTree* t1, TTree* t2, TString var, int nBins, double xMin, double xMax, TCut cut1, TCut cut2, const char* cap)  {
    gStyle->SetOptStat(0);
    TH1::SetDefaultSumw2();
    int i = 1;
    //static int i = 1;
    TCanvas* c =new TCanvas(Form("c_%s_%s",var.Data(),cap),"", 400,600);
    ratioPanelCanvas(c);
    c->cd(1);

    TLegend* l1 = new TLegend(0.4,0.750,0.92,0.95);
    l1->SetName(Form("l1_%s_%s",var.Data(),cap));
    legStyle(l1);

    TH1D* h1;
    h1 = new TH1D(Form("h1_%s_%s",var.Data(),cap), Form(";%s;",var.Data()), nBins,xMin,xMax);
    TH1D* h2 = (TH1D*)h1->Clone(Form("h2_%s_%s",var.Data(),cap));

    h1->Sumw2();
    h2->Sumw2();
    t1->Draw(Form("%s>>%s",var.Data(),h1->GetName()), Form("(%s)",cut1.GetTitle()));
    h1=(TH1D*)gDirectory->Get(h1->GetName());
    t2->Draw(Form("%s>>%s",var.Data(),h2->GetName()), Form("(%s)",cut2.GetTitle()));	
    h2=(TH1D*)gDirectory->Get(h2->GetName());
   // h1->Scale( 1. / h1->Integral(),"width");
   // h2->Scale( 1. / h2->Integral(),"width");
    //cout << cut1.GetTitle() << endl;	
    //////////////////////////////////
    // Cosmetics
    h1->SetMarkerStyle(20);
    h1->SetMarkerSize(0.6);
    h1->SetMarkerColor(2);
    h1->SetLineColor(1);
    h1->SetTitleSize(13);
    h2->SetFillColor(38);
    h2->SetFillStyle(3001);
    h2->SetLineColor(9);
    double YminVal;
    YminVal = cleverRange(h1,h2,1.2);
    h2->SetTitle(";;dN/dE_{T}");
    SetHistTextSize(h2);
    if(YminVal!=0) c->GetPad(1)->SetLogy();

    l1->AddEntry(h1,"HIHardProbes","pl");
    l1->AddEntry(h2,"HIHardProbesPhotons","F");	
    //h2->GetXaxis()->SetTitleMargin(0.4);
    h2->DrawCopy("hist e");
    h1->DrawCopy("hist e same");
    l1->Draw("same");
    //drawText("PbPb 5 TeV",0.91,0.76,1);
    drawText("|#eta|<1.44",0.91,0.70,1);
    drawText(Form("%s",cut1.GetTitle()),0.91,0.64,1);

    c->cd(2);
    h1->Divide(h2);
    h1->SetTitle(Form(";%s;Ratio",var.Data()));
    //double ratioRange = getCleverRange(h1);
    h1->SetAxisRange(0,2,"Y");
    SetHistTextSize(h1);
    h1->DrawCopy("le1");
    jumSun(xMin,1,xMax,1);
    drawText(cap,0.2,c->GetPad(2)->GetBottomMargin()+0.04);
    
    TLegend* l2 = new TLegend(0.4,0.70,0.99,0.95);
    legStyle(l2);
    l2->AddEntry(h1,"HIHardProbes / HIHardProbesPhotons","pl");
    l2->Draw("same");

    //fitting 
    //TF1* f1 = new TF1("f1", "pol1",0.005,0.02);
    //h1->Fit(f1,"Q R");
    //c->GetPad(1)->SetLogy();
    c->SaveAs(Form("figures/compare_%s_%s.pdf",var.Data(),cap));
    i++;
   // delete c;
    delete h1;
    delete h2;
   // delete l1;
    return 1;
}
