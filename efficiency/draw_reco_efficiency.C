// Created : 2017 April 18
// Modified : 2017 May18
// Author : Yeonju Go
// 

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
const int colHere[]={2,4,8,kYellow+2,kCyan+1};
const int markerStyle[]={20,33,22,23,22,29};
void draw_reco_efficiency(TString coll="pbpb", TString ver="Drum_v1_and_ext1", bool doSeparation=true){
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);
    SetyjPadStyle();
    const char* fname;
    if(coll=="pp"){ 
        fname = Form("./output/pp_reco_efficiency_%s.root",ver.Data());
    } else if(coll=="pbpb"){
        fname = Form("./output/pbpb_reco_efficiency_%s.root",ver.Data());
    }
    fname = "output/pbpb_reco_efficiency_HydjetDrum_v1_and_ext1.root";
    TFile* f1 = new TFile(fname,"read");

    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1;
    
    TH1D* h1D_eff[nCENTBINS];
    for(Int_t icent=0;icent<nCENTBINS;++icent){
        h1D_eff[icent] = (TH1D*) f1->Get(Form("reco_eff_cent%d",icent));
    }
    
    /////////////////////////////////////////////////////////////////////
    // Fill the histograms  
    cout << " DRAWING STARTS " << endl;
    TLegend* l1 = new TLegend(0.6,0.2,0.9,0.5,Form("%s",coll.Data()));
    legStyle(l1);

    TH1D* sig_eff_draw[nCENTBINS];
    for(Int_t i=0;i<nCENTBINS;++i){
        sig_eff_draw[i] = new TH1D(Form("reco_eff_draw_cent%d",i),";p_{T}^{#gamma} (GeV);Reconstruction Efficiency",nPtBin,ptBins_draw);
        for(int k=0;k<nPtBin;++k){
            sig_eff_draw[i]->SetBinContent(k+1,h1D_eff[i]->GetBinContent(k+1));
            sig_eff_draw[i]->SetBinError(k+1,h1D_eff[i]->GetBinError(k+1));
        }
    }

    /////////////////////////////////////////////////////////////////////
    // DRAWING : Centrality Dependence (Total Efficiency) 
    TCanvas* c1 =new TCanvas(Form("c%d",2),"", 400,400);
    for(Int_t i=0;i<nCENTBINS;++i){
        SetHistTextSize(sig_eff_draw[i]);
        if(i==0) {
            sig_eff_draw[i]->SetMarkerStyle(33);
            sig_eff_draw[i]->SetMarkerSize(1.4);
        } else{
            sig_eff_draw[i]->SetMarkerStyle(markerStyle[i]);
        }
        sig_eff_draw[i]->SetMarkerColor(colHere[i]);
        sig_eff_draw[i]->GetYaxis()->SetRangeUser(0.95,1);
        sig_eff_draw[i]->GetXaxis()->CenterTitle();
        sig_eff_draw[i]->GetYaxis()->CenterTitle();
        if(i==0) sig_eff_draw[i]->Draw("p");
        else sig_eff_draw[i]->Draw("same p");
        if(coll=="pbpb") l1->AddEntry(sig_eff_draw[i], Form("%d%s-%d%s",centBins_i[i]/2,"%",centBins_f[i]/2,"%"));
    } 
    if(coll=="pbpb") l1->Draw("same");
    drawText(Form("%s",ver.Data()),0.2,c1->GetBottomMargin()+0.06,0,kBlack,16);
    //drawText(Form("%s",ver.Data()),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/";
    c1->SaveAs(Form("%sfigures/efficiency_reconstruction_%s_centDep_%s.pdf",dir.Data(),coll.Data(),ver.Data()));

    /////////////////////////////////////////////////////////////////////
    // DRAWING : Centrality Dependence and Isolation Cut Dependence (Seperately)
/*
    TLegend* l2 = new TLegend(0.2,0.2,0.9,0.4);
    legStyle(l2);
    TCanvas* c2[nCENTBINS];
    for(Int_t i=0;i<nCENTBINS;++i){
        c2[i] = new TCanvas(Form("c_isoDep_cent%d",i),"", 400,400);

            SetHistTextSize(sig_eff_draw[i]);
                sig_eff_draw[i][j]->SetMarkerStyle(33);
                bkg_eff_draw[i][j]->SetMarkerStyle(33);
            } else{
                sig_eff_draw[i][j]->SetMarkerStyle(20);
                bkg_eff_draw[i][j]->SetMarkerStyle(20);
            }
            sig_eff_draw[i][j]->SetMarkerColor(colHere[j]);
            bkg_eff_draw[i][j]->SetMarkerColor(colHere[j]);
            sig_eff_draw[i][j]->GetYaxis()->SetRangeUser(0,1);
            sig_eff_draw[i][j]->GetXaxis()->CenterTitle();
            sig_eff_draw[i][j]->GetYaxis()->CenterTitle();
            if(j==0) sig_eff_draw[i][j]->Draw("p");
            else sig_eff_draw[i][j]->Draw("same p");
        } 
        for(Int_t j=3;j>-1;--j){
            if(i==0) l2->AddEntry(sig_eff_draw[i][j], Form("%s",effSt_legend[j].Data()));
        }
        l2->Draw("same");
        if(coll=="pbpb") drawText(Form("%s %d%s-%d%s",coll.Data(),centBins_i[i]/2,"%",centBins_f[i]/2,"%"),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
        else drawText(Form("%s",coll.Data()),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
        if(coll=="pbpb") c2[i]->SaveAs(Form("%sfigures/%s_iso_efficiency_isoDep_%s_cent%d%s-%d%s.pdf",dir.Data(),coll.Data(),ver.Data(),centBins_i[i]/2,"%",centBins_f[i]/2,"%"));
        else c2[i]->SaveAs(Form("%sfigures/%s_iso_efficiency_isoDep_%s.pdf",dir.Data(),coll.Data(),ver.Data()));
    }
*/
}
