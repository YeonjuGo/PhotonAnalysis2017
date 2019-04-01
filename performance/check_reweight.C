// comparison isolation variables between DATA and MC 
// Author : Yeonju Go

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
bool doEmEnrSample = false;
bool isDrum = false;
void compareTwo(TTree* t1=0 ,TTree* t2=0,TString var="pt", int nBins=10, double xMin=0, double xMax=10, TCut cut1="(1)", TCut cut2="(1)", const string cap = "");
void comparePthat(TTree* t1=0, TString var="pthat", int nBins=100, double xMin=10, double xMax=300, TCut cut1="(1)", const string cap=""); 
void check_reweight(TString coll="pbpb"){
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);
    SetyjPadStyle();


    //set file location
    const char* fname[2];
    if(coll=="pp"){
        fname[0]=Form("%s",ppDatafname.Data());
        if(doEmEnrSample)    fname[1]=Form("%s",ppMCEmEnrfname.Data());
        else                 fname[1]=Form("%s",ppMCfname.Data());
    } else if(coll=="pbpb"){
        fname[0]=Form("%s",pbpbDatafname.Data());
        if(doEmEnrSample)    fname[1]=Form("%s",pbpbMCEmEnrfname.Data());
        else                 fname[1]=Form("%s",pbpbMCfname.Data());
    }
    if(isDrum)
        fname[1]="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-06-11-nominal/PbPb_MC_photonRaaSkim_Drum_v1_and_ext1.root";
 
    //DATA
    TChain* t1 = new TChain("EventTree");
    TChain* t1_skim = new TChain("skim");
    TChain* t1_evt = new TChain("HiEvt");
    TChain* t1_hlt = new TChain("hltTree");
    for(Int_t j=0;j<1;++j){
        t1->Add(fname[j]);
        t1_skim->Add(fname[j]);
        t1_evt->Add(fname[j]);
        t1_hlt->Add(fname[j]);
    }
    t1->AddFriend(t1_skim);
    t1->AddFriend(t1_evt);
    t1->AddFriend(t1_hlt);
   
    //MC 
    TChain* t2 = new TChain("EventTree");
    TChain* t2_skim = new TChain("skim");
    TChain* t2_evt = new TChain("HiEvt");
    TChain* t2_hlt = new TChain("hltTree");
    for(Int_t j=1;j<2;++j){
        t2->Add(fname[j]);
        t2_skim->Add(fname[j]);
        t2_evt->Add(fname[j]);
        t2_hlt->Add(fname[j]);
    }
    t2->AddFriend(t2_skim);
    t2->AddFriend(t2_evt);
    t2->AddFriend(t2_hlt);

    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1;

    // Cuts   
    TCut dataCut_ = phoSignalCut_woTrig && trigCut_low ; 
    TCut mcCut_ = hoeCut && isoCut && sigmaCut && electronCut; 
    //TCut mcCut_ =  trigCut_mc && evtSelFilterCut && noiseCut && hoeCut && isoCut && sigmaCut && electronCut; 
    //TCut dataCut_ =  trigCut && evtSelFilterCut && noiseCut;
    //TCut mcCut_ = trigCut_mc && evtSelFilterCut && noiseCut;
    if(coll=="pp"){
        dataCut_ = phoSignalCut_woTrig_pp && trigCut_pp_low ;
        mcCut_ = hoeCut_pp && isoCut_pp && sigmaCut_pp && electronCut;
        //mcCut_ = trigCut_mc_pp && evtSelFilterCut_pp && noiseCut && hoeCut_pp && isoCut_pp && sigmaCut_pp && electronCut;
       // dataCut_ =  trigCut && evtSelFilterCut_pp && noiseCut;
       // mcCut_ = trigCut_mc_pp && evtSelFilterCut_pp && noiseCut;
    } 
    string cap = "trig_evtSel_noise_hoe_sig_iso_eleRej";
    cap+=Form("_%s",coll.Data());
    if(doEmEnrSample) cap+="_EmEnrchedDijet";
    else cap+="_AllQCDPhotons";

    if(isDrum) cap+="_Drum";

    double hiBinMin=0;
    double hiBinMax=200;
    double vzMin=-15;
    double vzMax=15;
    double pthatMin=15;
    double pthatMax=200;
    int nBin = 50;
    if(coll!="pp") compareTwo(t1, t2, "hiBin",nBin,hiBinMin,hiBinMax,     dataCut_,mcCut_,cap);
    compareTwo(t1, t2, "vz",nBin,vzMin,vzMax,                             dataCut_,mcCut_,cap);
    comparePthat(t2, "pthat",nBin,pthatMin,pthatMax,                      mcCut_,cap);

} // main function

void compareTwo(TTree* t1, TTree* t2, TString var, int nBins, double xMin, double xMax, TCut cut1, TCut cut2, const string cap)  {
    SetHistTitleStyle();
    SetyjPadStyle();
    gStyle->SetOptStat(0); 
    static int j = 0;
    TCanvas* c=  new TCanvas(Form("c_%s_%d",var.Data(),j),"", 400,600);
    ratioPanelCanvas(c);
	//c->Divide(1,2);
	c->cd(1);
	//gPad->SetLogy();
	TH1D* h1 = new TH1D(Form("h1_%s_%d",var.Data(),j), Form(";%s;Arbitrary Normalization",var.Data()), nBins,xMin,xMax);
	TH1D* h2 = (TH1D*)h1->Clone(Form("h2_%s_%d",var.Data(),j));
	TH1D* h3 = (TH1D*)h1->Clone(Form("h3_%s_%d",var.Data(),j));
	h1->Sumw2();
	h2->Sumw2();
	h3->Sumw2();
	t1->Draw(Form("%s>>%s",var.Data(),h1->GetName()), cut1);
	t2->Draw(Form("%s>>%s",var.Data(),h2->GetName()), cut2);	
	t2->Draw(Form("%s>>%s",var.Data(),h3->GetName()), Form("(%s)*(%s)","weight",cut2.GetTitle()));	
//	t2->Draw(Form("%s>>%s",var.Data(),h3->GetName()),"weight");	
//	t2->Draw(Form("%s>>%s",var.Data(),h2->GetName()), cut2);	
	h1->Scale( 1. / h1->Integral("width"));
	h2->Scale( 1. / h2->Integral("width"));
	h3->Scale( 1. / h3->Integral("width"));
	//h1->Scale( 1. / t1->GetEntries(cut1));
    SetHistColor(h1,1);
    SetHistColor(h2,4);
    SetHistColor(h3,2);
    h1->SetMarkerStyle(20);
	h1->SetMarkerSize(0.8);
    h1->SetNdivisions(505);
    SetHistTextSize(h1);
    TString sampleName = "AllQCDPhotons";
    if(doEmEnrSample) sampleName = "EmEnrichedDijet";
    TLegend* l1 = new TLegend(0.4,0.7,0.90,0.92);
    legStyle(l1);
    l1->AddEntry(h1, "Data", "p");
    //l1->AddEntry(h2, Form("%s before weight",sampleName.Data()), "l");
    l1->AddEntry(h3, Form("%s after weight",sampleName.Data()), "l");

    double range = cleverRange(h1,h2,1.5,1.e-4);
	h1->DrawCopy("L");
	//h2->DrawCopy("hist same");
	h3->DrawCopy("hist same");
    l1->Draw("same");
   
    // RATIO 
    c->cd(2);
	TH1D* h2_ratio = (TH1D*)h1->Clone(Form("h2_ratio_%s_%d",var.Data(),j));
	TH1D* h3_ratio = (TH1D*)h1->Clone(Form("h3_ratio_%s_%d",var.Data(),j));
	h2_ratio->Divide(h2);
	h3_ratio->Divide(h3);
    SetHistColor(h2_ratio,4);
    SetHistColor(h3_ratio,2);
    h2_ratio->SetMarkerStyle(20);
	h2_ratio->SetMarkerSize(0.8);
	
    h2_ratio->SetTitle(Form(";%s;DATA / MC",var.Data()));
	h2_ratio->GetYaxis()->SetRangeUser(0.0,2.0);
    h3_ratio->SetTitle(Form(";%s;DATA / MC",var.Data()));
	h3_ratio->GetYaxis()->SetRangeUser(0.0,2.0);
    SetHistTextSize(h2_ratio);
    SetHistTextSize(h3_ratio);
	//h2_ratio->DrawCopy("");
	h3_ratio->DrawCopy();
	//h2->DrawCopy("le1");
	jumSun(xMin,1,xMax,1);
    if(cap!="") drawText(cap.data(),0.2,0.2+0.7);
    //drawText(cut1.GetTitle(),0.2,0.2);
   // drawText("HLT_HIL1MinimumBiasHF1AND_v1",0.2,0.2+0.06);
   // drawText("pcollisionEventSelection",0.2,0.2);
	c-> SaveAs(Form("figures/compare_weight_%s_%s.pdf",var.Data(),cap.data()));
    j++;
}

void comparePthat(TTree* t1, TString var, int nBins, double xMin, double xMax, TCut cut1, const string cap)  {
    SetHistTitleStyle();
    SetyjPadStyle();
    gStyle->SetOptStat(0); 
    static int j = 0;
    TCanvas* c=  new TCanvas(Form("c_%s_%d",var.Data(),j),"", 400,400);
//	c->Divide(1,2);
//	c->cd(1);
	gPad->SetLogy();
	TH1D* h1 = new TH1D(Form("h1_%s_%d",var.Data(),j), Form(";%s;",var.Data()), nBins,xMin,xMax);
	TH1D* h2 = (TH1D*)h1->Clone(Form("h2_%s_%d",var.Data(),j));
	h1->Sumw2();
	h2->Sumw2();
	t1->Draw(Form("%s>>%s",var.Data(),h1->GetName()), cut1);
	t1->Draw(Form("%s>>%s",var.Data(),h2->GetName()), Form("(%s)*(%s)","weight",cut1.GetTitle()));	
	//t2->Draw(Form("%s>>%s",var.Data(),h2->GetName()),"weight");	
	h1->Scale( 1. / h1->Integral("width"));
	h2->Scale( 1. / h2->Integral("width"));
	//h1->Scale( 1. / t1->GetEntries(cut1));
    SetHistColor(h1,1);
    SetHistColor(h2,2);
    h1->SetMarkerStyle(20);
	h1->SetMarkerSize(0.8);
    h1->SetNdivisions(505);
    SetHistTextSize(h1);
    TString sampleName = "AllQCDPhotons";
    if(doEmEnrSample) sampleName = "EmEnrichedDijet";
    TLegend* l1 = new TLegend(0.2,0.3,0.70,0.5);
    legStyle(l1);
    l1->AddEntry(h1, Form("%s before weight",sampleName.Data()), "p");
    l1->AddEntry(h2, Form("%s after weight",sampleName.Data()), "l");
    //drawText(Form("%s",cap.data()),0.18,0.9);
    double range = cleverRange(h1,h2,1.5,1.e-4);
	h1->DrawCopy("L");
	h2->DrawCopy("hist same");
	//h3->DrawCopy("hist same");
    l1->Draw("same");
    if(cap!="") drawText(cap.data(),0.2,0.2);
   
    j++;
	c-> SaveAs(Form("figures/compare_weight_%s_%s.pdf",var.Data(),cap.data()));
}
