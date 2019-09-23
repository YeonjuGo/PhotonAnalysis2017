// 
// Author : Yeonju Go

#include "../phoRaaCuts/yjUtility.h"
#include "TF1.h" 
#include "../phoRaaCuts/phoRaaCuts_temp.h"
void purity_2Dcorr_sumIso_sigma(TString ver = "190703_temp_v31"){
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);
    SetyjPadStyle();

    TString cap = ver+"";
    //set file location
    const char* fname;
    //fname = pbpbDatafname_high;
    //fname = pbpbDatafname;
    fname = pbpbMCfname;
    //fname = pbpbMCEmEnrfname;

    TFile* f1 = new TFile(fname);
    TChain* t1 = new TChain("EventTree");
    TChain* t1_evt = new TChain("HiEvt");
    TChain* t1_skim = new TChain("skim");
    //TChain* t1_hlt = new TChain("hltTree");
    t1->Add(fname);
    t1_evt->Add(fname);
    //t1_skim->Add(fname);
    //t1_hlt->Add(fname);
    t1->AddFriend(t1_evt);
    //t1->AddFriend(t1_skim);
    //t1->AddFriend(t1_hlt);
    TCanvas* c1 = new TCanvas("c1","",500,400);

    //TCut centCut_ = "hiBin>=0 && hiBin<=200";
    //TCut ptCut_ = "phoEt>20 && phoEt<40";
    TCut ptCut_ = "phoEtCorrected>20 && phoEtCorrected<40";
    //TCut ptCut_ = "phoEtCorrected>40 && phoEtCorrected<80";
    //TCut ptCut_ = "phoEtCorrected>80 && phoEtCorrected<200";
    //TCut ptCut_ = "phoEtCorrected>40";
    double ymax = 0.05;
    //double ymax = 0.3;
    TH2D* h2D = new TH2D("h2D",";sumIso (GeV);photon #sigma_{i#etai#eta}",200,-20,50,180,0.0,0.03);
    //TH2D* h2D = new TH2D("h2D",";photon #sigma_{i#etai#eta};sumIso (GeV)",180,0.0,0.03,300,-100,200);
    //TH2D* h2D = new TH2D("h2D",";sumIso;photon E_{T}",300,-100,200,180,20,200);
    //for MC Bkg
    t1->Draw("phoSigmaIEtaIEta_2012:pho_sumIsoCorrected>>h2D",Form("(1.)*(%s && %s && %s && %s && %s)",mcBkgIsolation_PRpho_nonGenIso.GetTitle(),noiseCut.GetTitle(), hoeCut.GetTitle(),etaCut.GetTitle(), ptCut_.GetTitle()));
    //t1->Draw("phoSigmaIEtaIEta_2012:pho_sumIsoCorrected>>h2D",Form("(1.)*(%s && %s && %s && %s && %s)",mcBkgIsolation_onlyNM.GetTitle(),noiseCut.GetTitle(), hoeCut.GetTitle(),etaCut.GetTitle(), ptCut_.GetTitle()));
    //t1->Draw("phoSigmaIEtaIEta_2012:pho_sumIsoCorrected>>h2D",Form("(1.)*(%s && %s && %s && %s && %s)",mcBkgIsolation.GetTitle(),noiseCut.GetTitle(), hoeCut.GetTitle(),etaCut.GetTitle(), ptCut_.GetTitle()));
    //t1->Draw("pho_sumIsoCorrected:phoSigmaIEtaIEta_2012>>h2D",Form("(1.)*(%s && %s && %s && %s && %s && %s)",mcBkgIsolation.GetTitle(),noiseCut.GetTitle(), hoeCut.GetTitle(),sigmaCut.GetTitle(),etaCut.GetTitle(), ptCut_.GetTitle()));
   // //for MC
   // t1->Draw("phoSigmaIEtaIEta_2012:pho_sumIsoCorrected>>h2D",Form("(1.)*(%s && %s && %s && %s && %s)",mcIsolation.GetTitle(),noiseCut.GetTitle(), hoeCut.GetTitle(),etaCut.GetTitle(), ptCut_.GetTitle()));
    //for DATA
    //t1->Draw("pho_sumIsoCorrected:phoSigmaIEtaIEta_2012>>h2D",Form("(1.)*(%s && %s && %s && %s && %s)",noiseCut.GetTitle(), hoeCut.GetTitle(),sigmaCut.GetTitle(),etaCut.GetTitle(), ptCut_.GetTitle()));
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
    TH1D* proj_pt = new TH1D("proj_pt",";photon E_{T};",200,0,100);
    proj_pt = h2D->ProfileX(); 
    proj_pt->SetTitle(";photon E_{T};<sumIso>");
    proj_pt->SetMarkerStyle(20);
    proj_pt->SetMarkerColor(1);

    h2D->Draw("colz");
    proj_pt->Draw("same pe");

   //fitting
   // TF1* f_pol = new TF1("f_pol", "pol1",10,50);
   // f_pol->SetParameters(1.73284,-91.6665);
   // proj_pt->Fit(f_pol,"R");
   // proj_pt->Fit(f_pol,"R");
    
    //jumSun(xMin,1,xMax,1);

    c1->SaveAs(Form("figures/2D_corr_sumIso_pt_%s.pdf",cap.Data()));

} // main function
