// Created : 2017 April 11
// Modified : 2018 Feb 15
// Author : Yeonju Go
// 
// To compare two datasets (ex. allqcdphoton and emenricheddijet) 

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"

void compare_unfolding(TString coll="pbpb", TString ver="180822_temp_v24_nominal"){

    TFile* f = new TFile(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/Unfold_%s.root",ver.Data()));
    gStyle->SetOptStat(0);
    TH1::SetDefaultSumw2();


    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1;

    TH1D* h_gen[nCENTBINS];
    TH1D* h_reco[nCENTBINS];
    TH1D* h_reco_uf[nCENTBINS];
    TH1D* h_reco_nm[nCENTBINS];
    TH1D* h_reco_nm_uf[nCENTBINS];

    TCanvas* c[nCentBinIF];
    TLegend* l1 = new TLegend(0.4,0.750,0.92,0.95);
    l1->SetName("l1");
    legStyle(l1);
    
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/";
    for(int j=0;j<nCENTBINS;++j)
    {
        c[j] =new TCanvas(Form("c_%d",j),"", 400,600);
        ratioPanelCanvas(c[j]);
        c[j]->cd(1);

        h_gen[j] = (TH1D*) f->Get(Form("h1D_pt_gen_%d",j));
        h_reco[j] = (TH1D*) f->Get(Form("h1D_pt_reco_%d",j));
        h_reco_uf[j] = (TH1D*) f->Get(Form("roounfold_res_%d_mc",j));
        h_reco_nm[j] = (TH1D*) f->Get(Form("h1D_pt_reco_nm_%d",j));
        h_reco_nm_uf[j] = (TH1D*) f->Get(Form("roounfold_res_%d_mc_nm",j));

    //////////////////////////////////
    // Cosmetics
        //h_gen[j]->SetMarkerStyle(20);
        //h_gen[j]->SetMarkerSize(0.6);
        //h_gen[j]->SetMarkerColor(1);
        h_gen[j]->SetLineColor(1);
        h_gen[j]->SetTitleSize(13);
       // h_gen[j]->SetFillColor(38);
       // h_gen[j]->SetFillStyle(3001);
        h_gen[j]->SetLineColor(9);
        h_reco[j]->SetMarkerStyle(24);
        h_reco[j]->SetMarkerSize(0.8);
        h_reco[j]->SetMarkerColor(4);
        //h_reco[j]->SetLineColor(4);
        h_reco_uf[j]->SetMarkerStyle(26);
        h_reco_uf[j]->SetMarkerSize(0.8);
        h_reco_uf[j]->SetMarkerColor(2);
        //h_reco_uf[j]->SetLineColor(2);


        c[j]->GetPad(1)->SetLogy();
   // double YminVal;
   // YminVal = cleverRange(h1,h2,1.2);
   // h2->SetTitle(";;dN/dE_{T}");
   // SetHistTextSize(h2);
   // if(YminVal!=0) c->GetPad(1)->SetLogy();
        if(j==0){
            l1->AddEntry(h_gen[j],"GEN","pl");
            l1->AddEntry(h_reco[j],"RECO","pl");	
            l1->AddEntry(h_reco_uf[j],"RECO Unfolded","pl");	
        }
    //h2->GetXaxis()->SetTitleMargin(0.4);
    h_gen[j]->DrawCopy("hist e");
    h_reco[j]->DrawCopy("p e same");
    h_reco_uf[j]->DrawCopy("p e same");
    l1->Draw("same");
    drawText(Form("Centrality %d - %d %%",centBins_i[j]/2,centBins_f[j]/2),0.2,c[j]->GetPad(1)->GetBottomMargin()+0.04);
    //drawText("|#eta|<1.44",0.91,0.70,1);
    //drawText(Form("%s",cut1.GetTitle()),0.91,0.64,1);

    c[j]->cd(2);
    h_reco[j]->Divide(h_gen[j]);
    h_reco_uf[j]->Divide(h_gen[j]);
    h_reco[j]->SetTitle(Form(";%s;Ratio","p_{T}^{#gamma}"));

    //double ratioRange = getCleverRange(h1);
   // h1->SetAxisRange(0,2,"Y");
   // SetHistTextSize(h1);
    h_reco[j]->GetYaxis()->SetRangeUser(0.90,1.1);
    h_reco[j]->DrawCopy("p");
    h_reco_uf[j]->DrawCopy("p same");
    jumSun(20,1,40,1);
    
   // TLegend* l2 = new TLegend(0.4,0.70,0.99,0.95);
   // legStyle(l2);
   // l2->AddEntry(h1,"HIHardProbes / HIHardProbesPhotons","pl");
   // l2->Draw("same");

    //fitting 
    //TF1* f1 = new TF1("f1", "pol1",0.005,0.02);
    //h1->Fit(f1,"Q R");
    //c->GetPad(1)->SetLogy();

    c[j]->SaveAs(Form("%sfigures/Unfolding_closure_%s_%s_cent%d.pdf",dir.Data(),coll.Data(),ver.Data(),j));
    }
}
