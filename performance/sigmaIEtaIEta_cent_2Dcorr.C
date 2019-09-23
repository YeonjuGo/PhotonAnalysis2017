// 
// Author : Yeonju Go

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
void sigmaIEtaIEta_cent_2Dcorr(TString ver = "190703_temp_v31"){
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);
    SetyjPadStyle();

    TString cap = ver+"";
    //set file location
    const char* fname;
    //fname = pbpbDatafname_high;
    fname = pbpbDatafname;

    TFile* f1 = new TFile(fname);
    TChain* t1 = new TChain("EventTree");
    TChain* t1_evt = new TChain("HiEvt");
    TChain* t1_skim = new TChain("skim");
    TChain* t1_hlt = new TChain("hltTree");
    t1->Add(fname);
    t1_evt->Add(fname);
    //t1_skim->Add(fname);
    t1_hlt->Add(fname);
    t1->AddFriend(t1_evt);
    //t1->AddFriend(t1_skim);
    t1->AddFriend(t1_hlt);
    TCanvas* c1 = new TCanvas("c1","",500,400);

    //TCut centCut_ = "hiBin>=0 && hiBin<=200";
    TCut ptCut_ = "phoEtCorrected>20";
    //TCut ptCut_ = "phoEt>20 && phoEt<40";
    //TCut ptCut_ = "phoEt>100";
    double ymax = 0.012;
    TH2D* h2D = new TH2D("h2D",";Centrality;#sigma_{i#etai#eta}",200,0,100,200,0,ymax);
    t1->Draw("phoSigmaIEtaIEta_2012:hiBin/2.>>h2D",Form("(1.)*(%s && %s && %s && %s && %s && %s)","1==1",noiseCut.GetTitle(), hoeCut.GetTitle(),etaCut.GetTitle(), ptCut_.GetTitle(),sigmaCut.GetTitle()));
    //t1->Draw("phoSigmaIEtaIEta_2012:hiBin/2.>>h2D",Form("(1.)*(%s && %s && %s && %s && %s && %s)",trigCut_low.GetTitle(),noiseCut.GetTitle(), hoeCut.GetTitle(),etaCut.GetTitle(), ptCut_.GetTitle(),sigmaCut.GetTitle()));
    //t1->Draw("phoSigmaIEtaIEta_2012:hiBin/2.>>h2D",Form("(1.)*(%s && %s && %s && %s && %s && %s)",trigCut_low.GetTitle(),noiseCut.GetTitle(), hoeCut.GetTitle(),etaCut.GetTitle(), ptCut_.GetTitle(),sigmaCut.GetTitle()));
    //t1->Draw("phoSigmaIEtaIEta_2012:hiBin/2.>>h2D",Form("(1.)*(%s && %s && %s && %s && %s)",trigCut_low.GetTitle(),noiseCut.GetTitle(), hoeCut.GetTitle(),etaCut.GetTitle(), ptCut_.GetTitle()));
    //t1->Draw("phoSigmaIEtaIEta_2012:hiBin/2.>>h2D",Form("(1.)*(%s && %s && %s && %s)",noiseCut.GetTitle(), hoeCut.GetTitle(),etaCut.GetTitle(), ptCut_.GetTitle()));
    //t1->Draw("phoSigmaIEtaIEta_2012:hiBin/2.>>h2D",Form("(1.)*(%s && %s && %s && %s && %s)",noiseCut.GetTitle(), hoeCut.GetTitle(),sigmaCut.GetTitle(),etaCut.GetTitle(), ptCut_.GetTitle()));
    c1->SetRightMargin(0.15);
    c1->SetTopMargin(0.07);
    h2D->GetXaxis()->CenterTitle();
    h2D->GetYaxis()->CenterTitle();
    h2D->GetYaxis()->SetTitleSize(0.050);
    h2D->GetYaxis()->SetTitleOffset(1.3);
    h2D->GetXaxis()->SetTitleSize(0.055);
    h2D->GetXaxis()->SetTitleOffset(1.2);
    h2D->GetXaxis()->SetTitleFont(42);
    h2D->GetYaxis()->SetTitleFont(42);
    h2D->GetXaxis()->SetTitleColor(1);
    h2D->GetYaxis()->SetTitleColor(1);
    h2D->GetXaxis()->SetLabelSize(0.041);
    h2D->GetYaxis()->SetLabelSize(0.041);
    //h2D->GetYaxis()->SetLabelSize(0.045);
    TH1D* proj_pt = new TH1D("proj_pt",";Centrality;",200,0,100);
    proj_pt = h2D->ProfileX(); 
    proj_pt->SetTitle(";Centrality;<#Delta#phi_{SC}>");
    proj_pt->SetMarkerStyle(20);
    proj_pt->SetMarkerColor(1);

    h2D->Draw("colz");
    proj_pt->Draw("same pe");
    c1->SaveAs(Form("figures/2D_corr_sigmaIEtaIEta_cent_%s.pdf",cap.Data()));

} // main function
