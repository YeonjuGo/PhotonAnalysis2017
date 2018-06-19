// comparison isolation variables between DATA and MC 
// Author : Yeonju Go

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
bool isData = false;
bool doEmEnrSample = false;
void compareTwo(TTree* t1=0 ,TTree* t2=0,TString var="pt", int nBins=10, double xMin=0, double xMax=10, TCut cut1="(1)", TCut cut2="(1)", const string cap = "");
void compare_isolationVar(){
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);
    SetyjPadStyle();

    //set file location
    const char* fname_pbpb[2];
    const char* fname_pp[2];
    fname_pp[0]=Form("%s",ppMCfname.Data());
    fname_pp[1]=Form("%s",ppMCEmEnrfname.Data());
    fname_pbpb[0]=Form("%s",pbpbMCfname.Data());
    fname_pbpb[1]=Form("%s",pbpbMCEmEnrfname.Data());

    //////////////// NEW ELECTRON REJECTION /////////////////
    fname_pp[0]="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-04-06-nominal/pp_MC_photonRaaSkim_eleRejNew.root";
    fname_pp[1]="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-04-06-nominal/pp_EmEnrMC_photonRaaSkim_eleRejNew.root";
    fname_pbpb[0]="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-04-06-nominal/PbPb_MC_photonRaaSkim_v14_eleRejNew.root";
    fname_pbpb[1]="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-04-06-nominal/PbPb_EmEnrMC_photonRaaSkim_v14_eleRejNew.root";
    int nSAMPLE = 1;
    if(doEmEnrSample) nSAMPLE = 2;
    //pbpb
    TChain* t1 = new TChain("EventTree");
    TChain* t1_skim = new TChain("skim");
    TChain* t1_evt = new TChain("HiEvt");
    TChain* t1_hlt = new TChain("hltTree");
    for(Int_t j=0;j<nSAMPLE;++j){
        t1->Add(fname_pbpb[j]);
        t1_skim->Add(fname_pbpb[j]);
        t1_evt->Add(fname_pbpb[j]);
        t1_hlt->Add(fname_pbpb[j]);
    }
    t1->AddFriend(t1_skim);
    t1->AddFriend(t1_evt);
    t1->AddFriend(t1_hlt);
   
    //pp 
    TChain* t2 = new TChain("EventTree");
    TChain* t2_skim = new TChain("skim");
    TChain* t2_evt = new TChain("HiEvt");
    TChain* t2_hlt = new TChain("hltTree");
    for(Int_t j=0;j<nSAMPLE;++j){
        t2->Add(fname_pp[j]);
        t2_skim->Add(fname_pp[j]);
        t2_evt->Add(fname_pp[j]);
        t2_hlt->Add(fname_pp[j]);
    }
    t2->AddFriend(t2_skim);
    t2->AddFriend(t2_evt);
    t2->AddFriend(t2_hlt);

    // Cuts
    Int_t nCENTBINS = nCentBinIF;

    TCut centCut[nCENTBINS];
    TCut commonCut_pbpb[nCENTBINS];
    TCut commonCut_pp = trigCut_mc_pp && evtSelFilterCut_pp && noiseCut && etaCut && ptCut && sigmaCut && hoeCut; 
    for(Int_t i=0;i<nCENTBINS;++i){
        centCut[i] = Form("(hiBin>=%d)&&(hiBin<%d)",centBins_i[i],centBins_f[i]);
        commonCut_pbpb[i] = trigCut_mc && evtSelFilterCut && noiseCut && etaCut && ptCut && sigmaCut && hoeCut && centCut[i];
    }
    string cap = "trig_evtSel_pt40_eta1p44_noise_hoe_sigma_shortXrange";
    if(!doEmEnrSample) cap += "_noEmEnrSample";

    double sumIsoMax = 50;
    double sumIsoMin = -20;
    double eIsoMax = 50;
    double eIsoMin = -20;
    double hIsoMax = 50;
    double hIsoMin = -20;
    double tIsoMax = 50;
    double tIsoMin = -20;
    int nBin = 50;
    for(Int_t i=0;i<nCENTBINS;++i){
        string tempCap = cap;
        tempCap += Form("_cent%dto%d",(int)(centBins_i[i]/2.),(int)(centBins_f[i]/2.));
        compareTwo(t1, t2, "pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20",nBin,sumIsoMin,sumIsoMax,commonCut_pbpb[i],commonCut_pp, tempCap);
        compareTwo(t1, t2, "pho_ecalClusterIsoR4",nBin,eIsoMin,eIsoMax,commonCut_pbpb[i],commonCut_pp, tempCap);
        compareTwo(t1, t2, "pho_hcalRechitIsoR4",nBin,hIsoMin,hIsoMax,commonCut_pbpb[i],commonCut_pp, tempCap);
        compareTwo(t1, t2, "pho_trackIsoR4PtCut20",nBin,tIsoMin,tIsoMax,commonCut_pbpb[i],commonCut_pp, tempCap);
    }

} // main function

void compareTwo(TTree* t1, TTree* t2, TString var, int nBins, double xMin, double xMax, TCut cut1, TCut cut2, const string cap)  {
    SetHistTitleStyle();
    SetyjPadStyle();
    gStyle->SetOptStat(0); 
    static int j = 0;
    TCanvas* c=  new TCanvas(Form("c_%s_%d",var.Data(),j),"", 400,800);
	c->Divide(1,2);
	c->cd(1);
	gPad->SetLogy();
    TString xTitle = var;
    if(var=="pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20") xTitle = "sumIso";
	TH1D* h1 = new TH1D(Form("h1_%s_%d",var.Data(),j), Form(";%s;",xTitle.Data()), nBins,xMin,xMax);
	TH1D* h2 = (TH1D*)h1->Clone(Form("h2_%s_%d",var.Data(),j));
	h1->Sumw2();
	h2->Sumw2();
	t1->Draw(Form("%s>>%s",var.Data(),h1->GetName()), cut1);
	t2->Draw(Form("%s>>%s",var.Data(),h2->GetName()), cut2);	
	h1->Scale( 1. / t1->GetEntries(cut1));
	h2->Scale( 1. / t2->GetEntries(cut2));
    SetHistColor(h1,2);
    SetHistColor(h2,1);
    h1->SetMarkerStyle(20);
	h1->SetMarkerSize(0.8);
    h1->SetNdivisions(505);
    h2->SetNdivisions(505);
    SetHistTextSize(h1);
    SetHistTextSize(h2);
    TLegend* l1 = new TLegend(0.7,0.8,0.9,0.9);
    legStyle(l1);
    l1->AddEntry(h1, "PbPb", "p");
    l1->AddEntry(h2, "pp", "l");

    double range = cleverRange(h1,h2,1.5,1.e-4);
	h1->DrawCopy("L");
	h2->DrawCopy("hist same");
    l1->Draw("same");
    
    c->cd(2);
	h1->Divide(h2);
	h1->SetYTitle("PbPb / pp");
	h1->GetYaxis()->SetRangeUser(0.0,2.0);
    SetHistColor(h1,2);
    h1->SetMarkerStyle(20);
	h1->SetMarkerSize(0.8);
    SetHistTextSize(h1);
	h1->DrawCopy("");
	//h2->DrawCopy("le1");
	jumSun(xMin,1,xMax,1);
    drawText(cap.data(),0.2,0.2+0.7);
    std::size_t found = cap.find("cent");
    string centSt = cap.substr(found); 
    cout << centSt << endl;
    drawText(Form("%s",centSt.data()),0.2,0.2+0.06);
    //drawText("pcollisionEventSelection",0.2,0.2);
	c-> SaveAs(Form("figures/compare_isoVar_pbpb_pp_%s_CutList_%s.pdf",xTitle.Data(),cap.data()));
    j++;
}
