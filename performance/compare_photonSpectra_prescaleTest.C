// Created : 2017 April 11
// Modified : 2018 Feb 15
// Author : Yeonju Go
// 
// To compare two datasets (ex. allqcdphoton and emenricheddijet) 

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"

int compareTwo(TTree* t1=0 ,TTree* t2=0,TString var="pt", int nBins=10, double xMin=0, double xMax=10, TCut cut1="",TCut cut2="", const char* cap="", bool doPreScale=true);
void compare_photonSpectra_prescaleTest(int run= 263406, int lumi = 89){

    const char* fname_1="0";
    const char* fname_2="0";
    //fname_1="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-07-17-nominal/pp_Data_photonRaaSkim.root";
    //fname_1="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-07-17-nominal/pp_Data_photonRaaSkim_HighPtLowerPhotons.root";
    //fname_2="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-07-17-nominal/pp_Data_photonRaaSkim_HighPtLowerPhotons.root";
    fname_1="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-06-11-nominal/PbPb_Data_photonRaaSkim.root";
    fname_2="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-07-17-nominal/PbPb_Data_photonRaaSkim_HIPhoton40AndZ.root";
    fname_1="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-07-17-nominal/PbPb_Data_photonRaaSkim_HIHardProbes_HIHardProbesPhotons.root";
    fname_2="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-07-17-nominal/PbPb_Data_photonRaaSkim_HIHardProbes_HIHardProbesPhotons.root";
    fname_1="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-07-17-nominal/pp_Data_photonRaaSkim_HighPtPhoton30AndZ.root";
    fname_2="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-07-17-nominal/pp_Data_photonRaaSkim_HighPtPhoton30AndZ.root";
    fname_1="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-07-17-nominal/PbPb_Data_photonRaaSkim_HIPhoton40AndZ.root";
    fname_2="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-07-17-nominal/PbPb_Data_photonRaaSkim_HIPhoton40AndZ.root";
    fname_1="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-07-17-nominal/pp_Data_photonRaaSkim_HISinglePhoton40.root";
    fname_2="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-07-17-nominal/pp_Data_photonRaaSkim_HighPtLowerPhotons.root";

    TFile* f1 = new TFile(fname_1);
    TTree* t1 = (TTree*) f1 -> Get("EventTree");
    TTree* t1_hi = (TTree*) f1 -> Get("HiEvt");
    TTree* t1_evt = (TTree*) f1 -> Get("skim");
    TTree* t1_hlt= (TTree*) f1 -> Get("hltTree");
    t1->AddFriend(t1_hi);
    t1->AddFriend(t1_evt);
    t1->AddFriend(t1_hlt);
    TFile* f2 = new TFile(fname_2);
    TTree* t2 = (TTree*) f2 -> Get("EventTree");
    TTree* t2_hi = (TTree*) f2 -> Get("HiEvt");
    TTree* t2_evt = (TTree*) f2 -> Get("skim");
    TTree* t2_hlt= (TTree*) f2 -> Get("hltTree");
    t2->AddFriend(t2_hi);
    t2->AddFriend(t2_evt);
    t2->AddFriend(t2_hlt);

    TCut cut1 = "(1==1)";
    TCut cut2 = "(1==1)";

    TCut commonCut = noiseCut && evtSelFilterCut_pp && hoeCut_pp && isoCut_pp && sigmaCut_pp && electronCut;
    //TCut trigCut1 = "HLT_HISinglePhoton40_Eta1p5_v1";
    //TCut trigCut2 = "HLT_HISinglePhoton40_Eta1p5_v1";
    //TCut trigCut1 = "HLT_HISinglePhoton15_Eta1p5_v1";
    //TCut trigCut2 = "HLT_HISinglePhoton30_Eta1p5_v1 || HLT_HISinglePhoton40_Eta1p5_v1";
    //TCut trigCut1 = "HLT_HISinglePhoton15_Eta1p5_v1 || HLT_HISinglePhoton20_Eta1p5_v1 || HLT_HISinglePhoton30_Eta1p5_v1";
    //TCut trigCut2 = "HLT_HISinglePhoton10_Eta1p5_v1 || HLT_HISinglePhoton15_Eta1p5_v1 || HLT_HISinglePhoton20_Eta1p5_v1";
    TCut trigCut1 = "HLT_HISinglePhoton15_Eta1p5_v1 || HLT_HISinglePhoton20_Eta1p5_v1 || HLT_HISinglePhoton30_Eta1p5_v1 || HLT_HISinglePhoton40_Eta1p5_v1";
    TCut trigCut2 = "HLT_HISinglePhoton15_Eta1p5_v1 || HLT_HISinglePhoton20_Eta1p5_v1 || HLT_HISinglePhoton30_Eta1p5_v1 || HLT_HISinglePhoton40_Eta1p5_v1";
    //TCut trigCut2 = "HLT_HISinglePhoton15_Eta1p5_v1 || HLT_HISinglePhoton20_Eta1p5_v1 || HLT_HISinglePhoton30_Eta1p5_v1 || HLT_HISinglePhoton40_Eta1p5_v1";
    //TString cap = "pbpb_HIPhoton40AndZ_OldSkim0611_vs_NewSkim0717";

    //TString cap = "pbpb_HIHardProbes_HIHardProbesPhotons_15or20or30_vs_15or20or30or40";
    TString cap = "pp_HighPtLowerPhotons_PrescaleTest_15or20or30or40_twoDiffFiles";
    //TString cap = "pbpb_HIPhoton40AndZ_40_vs_15or20or30or40";
    //TString cap = "pp_HighPtPhoton30AndZ_40_vs_15or20or30or40";
    //TString cap = "pp_HighPtLowerPhotons_15withHltPrescale_vs_15withSkimPrescale";
    //TString cap = "pp_HighPtLowerPhotons_15or20_vs_10or15or20";
    //TString cap = "HighPtLowerPhotons_NewPD_pp_phoPreScaleComparison";
    
    //TCut trig40Cut = "HLT_HISinglePhoton15_Eta1p5_v1 || HLT_HISinglePhoton20_Eta1p5_v1 || HLT_HISinglePhoton30_Eta1p5_v1 || HLT_HISinglePhoton40_Eta1p5_v1";
    int nBins = 100;
    //compareTwo(t1, t2, "phoEt",nBins, 0, 100.0,commonCut && trigCut1,commonCut && trigCut2,cap,0);
    compareTwo(t1, t2, "phoEt",nBins, 0, 100.0,commonCut && trigCut1,commonCut && trigCut2,cap);
    //compareTwo(t1, t2, "phoEt",nBins, 0, 200.0,phoSignalCut_pp,phoSignalCut_pp || trig40Cut,cap);

} // main function

int compareTwo(TTree* t1, TTree* t2, TString var, int nBins, double xMin, double xMax, TCut cut1, TCut cut2, const char* cap, bool doPreScale)  {
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
        //t1->Draw(Form("%s>>%s",var.Data(),h1->GetName()), Form("phoPreScale*(%s)",cut1.GetTitle()));
        //t1->Draw(Form("%s>>%s",var.Data(),h1->GetName()), Form("(HLT_HISinglePhoton15_Eta1p5_v1_Prescl*L1_SingleEG5_BptxAND_Prescl)*(%s)",cut1.GetTitle()));
        //t1->Draw(Form("%s>>%s",var.Data(),h1->GetName()), Form("(%s)",cut1.GetTitle()));
    if(doPreScale)
        t1->Draw(Form("%s>>%s",var.Data(),h1->GetName()), Form("phoPreScale*(%s)",cut1.GetTitle()));
    else 
        t1->Draw(Form("%s>>%s",var.Data(),h1->GetName()), Form("(%s)",cut1.GetTitle()));
    h1=(TH1D*)gDirectory->Get(h1->GetName());
    if(doPreScale)
        t2->Draw(Form("%s>>%s",var.Data(),h2->GetName()), Form("phoPreScale*(%s)",cut2.GetTitle()));	
    else 
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
    //if(YminVal!=0) c->GetPad(1)->SetLogy();

    l1->AddEntry(h1,"_HISinglePhoton40","pl");
    l1->AddEntry(h2,"_HighPtLowerPhotons","F");	
    //l1->AddEntry(h1,"trig1","pl");
    //l1->AddEntry(h2,"trig2","F");	
    //h2->GetXaxis()->SetTitleMargin(0.4);
    h2->DrawCopy("hist e");
    h1->DrawCopy("hist e same");
    l1->Draw("same");
    //drawText("PbPb 5 TeV",0.91,0.76,1);
    drawText("|#eta|<1.44",0.91,0.70,1);
    drawText(Form("%s",cut1.GetTitle()),0.91,0.64,1);
    jumSun(10,0,10,10000000);
    jumSun(20,0,20,10000000);
    jumSun(30,0,30,10000000);
    jumSun(40,0,40,10000000);
    jumSun(50,0,50,10000000);

    c->cd(2);
    h1->Divide(h2);
    h1->SetTitle(Form(";%s;Ratio",var.Data()));
    //double ratioRange = getCleverRange(h1);
    h1->SetAxisRange(0,2,"Y");
    SetHistTextSize(h1);
    h1->DrawCopy("le1");
    jumSun(xMin,1,xMax,1);
    drawText(cap,0.2,c->GetPad(2)->GetBottomMargin()+0.04);
    if(doPreScale) drawText("Prescaled",0.2,c->GetPad(2)->GetBottomMargin()+0.1);
    
    TLegend* l2 = new TLegend(0.4,0.70,0.99,0.95);
    legStyle(l2);
    l2->AddEntry(h1,"_HISinglePhoton40 / _HighPtLowerPhotons","pl");
    //l2->AddEntry(h1,"No selection / HISinglePhoton40 ","pl");
    //l2->AddEntry(h1,"HIHardProbes / HIHardProbesPhotons","pl");
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
