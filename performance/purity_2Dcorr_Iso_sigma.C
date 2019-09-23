// 
// Author : Yeonju Go

#include "../phoRaaCuts/yjUtility.h"
#include "TF1.h" 
#include "../phoRaaCuts/phoRaaCuts_temp.h"

void purity_2Dcorr_Iso_sigma(TString coll="pbpb", TString ver = "190703_temp_v31", TString var = "pho_sumIsoCorrected", double pt_i=20, double pt_f=40, int cent_i=0, int cent_f=100, bool isBkg = true){
    

    // pho_sumIsoCorrected 
    // pho_ecalClusterIsoR4
    // pho_hcalRechitIsoR4
    // pho_trackIsoR4PtCut20
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);
    SetyjPadStyle();

    TString cap = ver+"_"+coll+Form("_pt%dto%d",(int)pt_i,(int)pt_f);
    if(coll=="pbpb") cap+= Form("_cent%dto%d", (int)cent_i, (int)cent_f);

    const char* fname;
    fname = pbpbMCEmEnrfname;
    if(coll=="pbpb"){
        if(isBkg) fname = pbpbMCEmEnrfname;
        else fname = pbpbMCfname;
    } else{
        if(isBkg) fname = ppMCEmEnrfname;
        else fname = ppMCfname;
    }

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

    TCut centCut_ = Form("hiBin>=%f && hiBin<=%f", (double)cent_i,(double)cent_f);
    if(coll=="pp") centCut_ = "hiBin < 10000";
    TCut ptCut_ = Form("phoEtCorrected>%f && phoEtCorrected<%f",pt_i,pt_f);
    double ymax = 0.05;
    TH2D* h2D = new TH2D("h2D",Form(";%s (GeV);photon #sigma_{i#etai#eta}",var.Data()),200,-20,50,180,0.0,0.03);
    //TString var = "pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20";

    //for MC Bkg
    t1->Draw(Form("phoSigmaIEtaIEta_2012:%s>>h2D",var.Data()),Form("(1.)*(%s && %s && %s && %s && %s && %s)",mcBkgIsolation.GetTitle(),noiseCut.GetTitle(), hoeCut.GetTitle(),etaCut.GetTitle(), ptCut_.GetTitle(),centCut_.GetTitle()));
    //pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20
    //
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

    c1->SaveAs(Form("figures/2D_corr_%s_vs_phoSigmaIEtaIEta_%s.pdf",var.Data(),cap.Data()));

} // main function
