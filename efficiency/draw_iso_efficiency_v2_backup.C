// Created : 2017 April 18
// Modified : 2019 June 26
// Author : Yeonju Go
// (deprecated) iso_efficiency_withSkimFile_v2 : unfolding binning (15 GeV to 300 GeV)
// (deprecated) trigger efficiency will be calculated by MC here in this code
// 2019June25) different unfolding binning depending on centrality bin 
// 2019June25) apply trigger efficiency which is derived using DATA to here but not draw in canvas
// 2019June25) unfolding binning (20 GeV to 300 GeV) 

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"

bool isConsBin = false;
const int colHere[]={kBlack,kPink-5,kGreen+3,kBlue-3,kOrange+4,kBlack};
//const int colHere[]={2,4,8,kYellow+2,kCyan+1,kOrange+7,kViolet-7};
const int markerStyle[]={24,33,26,34,29,22,24,33};
void draw_iso_efficiency_v2(TString coll="pbpb", TString ver="190703_temp_v31_nominal", bool doWeight=true, bool doBkg=false, bool doSeparation=true){

    cout << " :::::: draw_iso_efficiency_v2.C :::::: " << endl;
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);
    SetyjPadStyle();
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/";

    TString fname;

    if(coll=="pp"){
        fname = Form("./output/pp_iso_efficiency_%s.root",ver.Data());
    } else if(coll=="pbpb"){
        fname = Form("./output/pbpb_iso_efficiency_%s.root",ver.Data());
    }
    TFile* f1 = new TFile(Form("%s",fname.Data()));
    //TFile* f1 = new TFile(Form("%s",fname.Data()));
    //TFile* f1 = new TFile(fname,"read");

    //define constants and histograms
    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1;
    Int_t nEff = 6;//0(tot,trigEff):noiseCut && hoeCut && sigmaCut && isoCut && eleRej && trigEff, 0(electron rejection):noiseCut && hoeCut && sigmaCut && isoCut && eleRej, 1(iso):noiseCut && hoeCut && sigmaCut && isoCut, 2(sigma):noiseCut && hoeCut && sigmaCut, 3(hoe):noiseCut && hoeCut, 4(noise):noise//
    Int_t nEffloop = nEff;
    if(doSeparation==0) nEffloop = 1;
    TString effSt[] = {"tot","eleRej","iso","sigma","hoe","noise"};
    TString effSt_legend[] = {"total(noise & H/E & #sigma_{i#etai#eta} & sumIso & eleRej & trig)","noise & H/E & #sigma_{i#etai#eta} & sumIso & eleRej","noise & H/E & #sigma_{i#etai#eta} & sumIso","noise & H/E & #sigma_{i#etai#eta}","noise & H/E","noise"};
    //TString effSt[] = {"tot","trig","iso","sigma","hoe","noise"};
    //TString effSt_legend[] = {"total(noise & H/E & #sigma_{i#etai#eta} & sumIso & eleRej & trig)","noise & H/E & #sigma_{i#etai#eta} & sumIso & eleRej","noise & H/E & #sigma_{i#etai#eta} & sumIso","noise & H/E & #sigma_{i#etai#eta}","noise & H/E","noise"};
    TH1D* sig_eff[nCENTBINS][nEff];
    //TH1D* h_temp_trig[nCENTBINS][2]; //[Centrality][0:20-40GeV, 1: over 40GeV]

    TH1D* h1D_eff[nCENTBINS][nEff];
    for(Int_t icent=0;icent<nCENTBINS;++icent){
        for(Int_t j=0;j<nEffloop;++j){
            h1D_eff[icent][j] = (TH1D*) f1->Get(Form("sig_eff_cent%d_%s",icent,effSt[j].Data()));
        }
    }

    /////////////////////////////////////////////////////////////////////
    // DRAWING 
    cout << " SET HISTS " << endl;
    TLegend* l1 = new TLegend(0.5,0.2,0.8,0.4);
    legStyle(l1);

    TH1D* sig_eff_draw[nCENTBINS][nEff];
    for(Int_t i=0;i<nCENTBINS;++i){
        // rebin ptbins for each centrality bins since we have less bins for peripheral region
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[i];
        double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
            ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
        } 

        for(Int_t j=nEffloop-1;j>-1;--j){
            sig_eff_draw[i][j] = new TH1D(Form("sig_eff_draw_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);Efficiency",nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
            int temp_nPtBin_unfolding_centDep = nPtBin_unfolding_centDep;
            //if(isConsBin) temp_nPtBin_unfolding_centDep = nConstPtBin;
            //else temp_nPtBin_unfolding_centDep = nPtBin_unfolding_centDep;
            for(int k=0;k<temp_nPtBin_unfolding_centDep;++k){
                sig_eff_draw[i][j]->SetBinContent(k+1,sig_eff[i][j]->GetBinContent(k+1));
                sig_eff_draw[i][j]->SetBinError(k+1,sig_eff[i][j]->GetBinError(k+1));
            }
        }
    }

    /////////////////////////////////////////////////////////////////////
    // DRAWING : Centrality Dependence (Total Efficiency) 
    cout << " DRAWING STARTS " << endl;
    cout << " Total efficiency vs. pT " << endl;
    TCanvas* c1 =new TCanvas(Form("c%d",2),"", 400,400);
    c1->SetLogx(); 
    for(Int_t i=0;i<nCENTBINS;++i){
        SetHistTextSize(sig_eff_draw[i][1]);
        // if(i==0) {
        //     sig_eff_draw[i][0]->SetMarkerStyle(33);
        //     sig_eff_draw[i][0]->SetMarkerSize(1.4);
        // } else{
        //     sig_eff_draw[i][0]->SetMarkerStyle(20);
        // }
        sig_eff_draw[i][1]->SetMarkerColor(colHere[i]);
        sig_eff_draw[i][1]->SetMarkerStyle(markerStyle[i]);
        sig_eff_draw[i][1]->GetYaxis()->SetRangeUser(0,1);
        sig_eff_draw[i][1]->GetXaxis()->CenterTitle();
        sig_eff_draw[i][1]->GetYaxis()->CenterTitle();
        if(i==0) sig_eff_draw[i][1]->DrawCopy("p");
        else sig_eff_draw[i][1]->DrawCopy("same p");
        if(coll=="pbpb") l1->AddEntry(sig_eff_draw[i][1], Form("%d%s-%d%s",centBins_i[i]/2,"%",centBins_f[i]/2,"%"));
    } 
    if(coll=="pbpb") l1->Draw("same");
    drawText(Form("%s Total Isolation Efficiency",coll.Data()),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
    c1->SaveAs(Form("%sfigures/efficiency_%s_totEff_centDep_%s.pdf",dir.Data(),coll.Data(),ver.Data()));

    /////////////////////////////////////////////////////////////////////
    // DRAWING : Centrality Dependence and Isolation Cut Dependence (each centrality bin separately)

    cout << "Each efficiency vs. pT in different centrality bins" << endl;
    TLegend* l2 = new TLegend(0.25,0.2,0.9,0.4);
    legStyle(l2);
    TCanvas* c2[nCENTBINS];
    for(Int_t i=0;i<nCENTBINS;++i){
        c2[i] = new TCanvas(Form("c_effDep_cent%d",i),"", 400,400);

        for(Int_t j=1;j<nEffloop;++j){
            SetHistTextSize(sig_eff_draw[i][j]);
            sig_eff_draw[i][j]->SetLineColor(colHere[j]);
            sig_eff_draw[i][j]->SetMarkerColor(colHere[j]);
            sig_eff_draw[i][j]->SetMarkerStyle(markerStyle[j]);
            sig_eff_draw[i][j]->GetYaxis()->SetRangeUser(0,1);
            sig_eff_draw[i][j]->GetXaxis()->CenterTitle();
            sig_eff_draw[i][j]->GetYaxis()->CenterTitle();
            if(j==1) sig_eff_draw[i][j]->DrawCopy("p");
            else sig_eff_draw[i][j]->DrawCopy("same p");
        } 
        for(Int_t j=nEff-1;j>0;--j){
            if(i==0) l2->AddEntry(sig_eff_draw[i][j], Form("%s",effSt_legend[j].Data()));
        }
        l2->Draw("same");
        if(coll=="pbpb") drawText(Form("%s %d%s-%d%s",coll.Data(),centBins_i[i]/2,"%",centBins_f[i]/2,"%"),0.7,1.0-c1->GetBottomMargin()+0.4,0,kBlack,16);
        else drawText(Form("%s",coll.Data()),0.7,1.0-c1->GetBottomMargin()+0.4,0,kBlack,16);
        //else drawText(Form("%s",coll.Data()),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
        if(coll=="pbpb") c2[i]->SaveAs(Form("%sfigures/efficiency_%s_effDep_%s_cent%d%s-%d%s.pdf",dir.Data(),coll.Data(),ver.Data(),centBins_i[i]/2,"%",centBins_f[i]/2,"%"));
        else c2[i]->SaveAs(Form("%sfigures/efficiency_%s_effDep_%s.pdf",dir.Data(),coll.Data(),ver.Data()));
    }

    /////////////////////////////////////////////////////////////////////
    // DRAWING : Centrality Dependence (Total Efficiency including trigger efficiency) 
    cout << "Total efficiency including trigger vs. pT " << endl;
    TCanvas* c3 =new TCanvas(Form("c%d",3),"", 400,400);
    for(Int_t i=0;i<nCENTBINS;++i){
        SetHistTextSize(sig_eff_draw[i][0]);
        sig_eff_draw[i][0]->SetMarkerColor(colHere[i]);
        sig_eff_draw[i][0]->SetMarkerStyle(markerStyle[i]);
        sig_eff_draw[i][0]->GetYaxis()->SetRangeUser(0,1);
        sig_eff_draw[i][0]->GetXaxis()->CenterTitle();
        sig_eff_draw[i][0]->GetYaxis()->CenterTitle();
        if(i==0) sig_eff_draw[i][0]->DrawCopy("p");
        else sig_eff_draw[i][0]->DrawCopy("same p");
    } 
    if(coll=="pbpb") l1->Draw("same");
    //drawText(Form("%s Total Isolation Efficiency",coll.Data()),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
    c3->SaveAs(Form("%sfigures/efficiency_withTrigEff_%s_tot_centDep_%s.pdf",dir.Data(),coll.Data(),ver.Data()));

}
