// Created : 2017 April 18
// Modified : 2017 May18
// Author : Yeonju Go
// 

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
bool isConstBin = false;
const int colHere[]={2,4,8,kYellow+2,kCyan+1};
const int markerStyle[]={20,33,22,23,34,29};
void draw_iso_efficiency(TString coll="pbpb", TString ver="180619_temp_v17_nominal", bool doWeight=true, bool doBkg=false, bool doSeparation=true){
    
    cout << " :::::: iso_efficiency_withSkimFile.C :::::: " << endl;
    if(doSeparation) cout << " :::::: Isolation Separation will be processed :::::: " << endl;
    else cout << " :::::: Only total efficiency will be calculated :::::: " << endl;
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);
    SetyjPadStyle();

    const char* fname;
    if(coll=="pp"){
        fname = Form("./output/pp_iso_efficiency_%s.root",ver.Data());
    } else if(coll=="pbpb"){
        fname = Form("./output/pbpb_iso_efficiency_%s.root",ver.Data());
    }
    TFile* f1 = new TFile(fname,"read");

    ///////////////////////////////////////////////////////////
    //
    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1;
    Int_t nConstPtBin = 50;
    
    Int_t nEff = 5;//1(tot):noiseCut && hoeCut && sigmaCut && isoCut && eleRej, 1(iso):noiseCut && hoeCut && sigmaCut && isoCut, 2(sigma):noiseCut && hoeCut && sigmaCut, 3(hoe):noiseCut && hoeCut, 4(noise):noise//
    Int_t nEffloop = nEff;
    if(doSeparation==0) nEffloop = 1;
    TString effSt[] = {"tot","iso","sigma","hoe","noise"};
    TString effSt_legend[] = {"total(noise & H/E & #sigma_{i#etai#eta} & sumIso & eleRej)","noise & H/E & #sigma_{i#etai#eta} & sumIso","noise & H/E & #sigma_{i#etai#eta}","noise & H/E","noise"};
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/";

    TH1D* h1D_eff[nCENTBINS][nEff];
    for(Int_t icent=0;icent<nCENTBINS;++icent){
        for(Int_t j=0;j<nEffloop;++j){
            h1D_eff[icent][j] = (TH1D*) f1->Get(Form("sig_eff_cent%d_%s",icent,effSt[j].Data()));
        }
    }


    /////////////////////////////////////////////////////////////////////
    // DRAWING 
    cout << " DRAWING STARTS " << endl;
    TH1D* sig_eff_draw[nCENTBINS][nEff];
    for(Int_t i=0;i<nCENTBINS;++i){
        for(Int_t j=0;j<nEffloop;++j){
            sig_eff_draw[i][j] = new TH1D(Form("sig_eff_draw_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);Efficiency",nPtBin,ptBins_draw);
            int temp_nPtBin = -1;
            if(isConstBin) temp_nPtBin = nConstPtBin;
            else temp_nPtBin = nPtBin;
            for(int k=0;k<temp_nPtBin;++k){
                sig_eff_draw[i][j]->SetBinContent(k+1,h1D_eff[i][j]->GetBinContent(k+1));
                sig_eff_draw[i][j]->SetBinError(k+1,h1D_eff[i][j]->GetBinError(k+1));
            }
        }
    }

    /////////////////////////////////////////////////////////////////////
    // DRAWING : Centrality Dependence (Total Efficiency) 
    TCanvas* c1 =new TCanvas(Form("c%d",2),"", 400,400);
    TLegend* l1 = new TLegend(0.5,0.2,0.8,0.4);
    legStyle(l1);

    //c1->SetLogx(); 
    for(Int_t i=0;i<nCENTBINS;++i){
        SetHistTextSize(sig_eff_draw[i][0]);
       // if(i==0) {
       //     sig_eff_draw[i][0]->SetMarkerStyle(33);
       //     sig_eff_draw[i][0]->SetMarkerSize(1.4);
       // } else{
       //     sig_eff_draw[i][0]->SetMarkerStyle(20);
       // }
        sig_eff_draw[i][0]->SetMarkerColor(colHere[i]);
        sig_eff_draw[i][0]->SetMarkerStyle(markerStyle[i]);
        sig_eff_draw[i][0]->GetYaxis()->SetRangeUser(0,1);
        sig_eff_draw[i][0]->GetXaxis()->CenterTitle();
        sig_eff_draw[i][0]->GetYaxis()->CenterTitle();
        if(i==0) sig_eff_draw[i][0]->DrawCopy("p");
        else sig_eff_draw[i][0]->DrawCopy("same p");
        if(coll=="pbpb") l1->AddEntry(sig_eff_draw[i][0], Form("%d%s-%d%s",centBins_i[i]/2,"%",centBins_f[i]/2,"%"));
    } 
    if(coll=="pbpb") l1->Draw("same");
    drawText(Form("%s Total Isolation Efficiency",coll.Data()),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
    c1->SaveAs(Form("%sfigures/efficiency_iso_%s_tot_centDep_%s.pdf",dir.Data(),coll.Data(),ver.Data()));

    /////////////////////////////////////////////////////////////////////
    // DRAWING : Centrality Dependence and Isolation Cut Dependence (Seperately)

    TLegend* l2 = new TLegend(0.15,0.2,0.9,0.4);
    legStyle(l2);
    TCanvas* c2[nCENTBINS];
    for(Int_t i=0;i<nCENTBINS;++i){
        c2[i] = new TCanvas(Form("c_isoDep_cent%d",i),"", 400,400);

        for(Int_t j=0;j<nEffloop;++j){
            SetHistTextSize(sig_eff_draw[i][j]);
           // if(j==0) {
           //     sig_eff_draw[i][j]->SetMarkerStyle(33);
           // } else{
           //     sig_eff_draw[i][j]->SetMarkerStyle(20);
           // }
            sig_eff_draw[i][j]->SetMarkerColor(colHere[j]);
            sig_eff_draw[i][j]->SetMarkerStyle(markerStyle[j]);
            sig_eff_draw[i][j]->GetYaxis()->SetRangeUser(0,1);
            sig_eff_draw[i][j]->GetXaxis()->CenterTitle();
            sig_eff_draw[i][j]->GetYaxis()->CenterTitle();
            if(j==0) sig_eff_draw[i][j]->DrawCopy("p");
            else sig_eff_draw[i][j]->DrawCopy("same p");
        } 
        for(Int_t j=nEff-1;j>-1;--j){
            if(i==0) l2->AddEntry(sig_eff_draw[i][j], Form("%s",effSt_legend[j].Data()));
        }
        l2->Draw("same");
        if(coll=="pbpb") drawText(Form("%s %d%s-%d%s",coll.Data(),centBins_i[i]/2,"%",centBins_f[i]/2,"%"),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
        else drawText(Form("%s",coll.Data()),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
        if(coll=="pbpb") c2[i]->SaveAs(Form("%sfigures/efficiency_iso_%s_isoDep_%s_cent%d%s-%d%s.pdf",dir.Data(),coll.Data(),ver.Data(),centBins_i[i]/2,"%",centBins_f[i]/2,"%"));
        else c2[i]->SaveAs(Form("%sfigures/efficiency_iso_%s_isoDep_%s.pdf",dir.Data(),coll.Data(),ver.Data()));
    }
}
