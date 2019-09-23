// drawUnfoldingFigures.C 
// Author: Yeonju Go 
// Written at 2019 Feb 12
// Modified : 2019 Feb 12

#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TCut.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "TLatex.h"
#include "stdio.h"
#include <iostream>
#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"

const TString LABEL = "PbPb #sqrt{s}_{_{NN}}=5.02 TeV";
const int colHere[]={2,4,8,kYellow+2,kCyan+1,kOrange+7,kViolet-7,kGreen+1,kBlue-2,kRed+3,2,4,8,kYellow+2,kCyan+1,kOrange+7,kViolet-7,kGreen+1,kBlue-2,kRed+3,2,4,8,kYellow+2,kCyan+1,kOrange+7,kViolet-7,kGreen+1,kBlue-2,kRed+3};
const int markerStyle[]={24,33,26,23,29,22,24,33,26,23,29,22,24,33,26,23,29,22,24,33,26,23,29,22,24,33,26,23,29,22,24,33,26,23,29,22,24};

//const int colHere[]={1,2,4,kGreen+1,kYellow+1,kOrange+7,kViolet-7};
//const int markerHere[]={22,28,24,28,33,26};
//const int markerHere_closed[]={20,33,33,33,33};

void drawUnfoldingIterationPlot(TString ver="190703_temp_v31", bool isSVD = false, TString sample = "MC", bool doHighIter= false)
{
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0000);
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/";
    TString cap ="";
    if(isSVD) cap +="_svd";
    if(sample=="splitMC" || sample=="data") cap = cap+"_"+sample;
    if(doHighIter) cap +="_highIter";

    const int nIter = 30;
    const int dev = 4;
    const int highIter = 100;
    TString legst = "iter";
    if(isSVD) legst = "par";

    TFile* f_in[nIter];
    TH1D* h1D_reco_unfolded[nCentBinIF][nIter];
    TH1D* h1D_ratio_reco_unfolded_gen[nCentBinIF][nIter];
    TH1D* h1D_den[nCentBinIF];
    TH1D* h1D_reco_unfolded_pp[nIter];
    TH1D* h1D_ratio_reco_unfolded_gen_pp[nIter];
    TH1D* h1D_den_pp;

    cout << "High enough iteration = " << highIter << " for denominator" << endl;
    TString denfname = "";
    if(isSVD) {
        denfname = Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/Unfold_%s_sys_unfolding_svd%d.root",ver.Data(),highIter);
        if(sample=="splitMC") denfname = Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/Unfold_%s_sys_unfolding_svd%d_splitMC.root",ver.Data(),highIter);
    } else {
        denfname = Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/Unfold_%s_sys_unfolding_iterative%d.root",ver.Data(),highIter);
        if(sample=="splitMC") denfname = Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/Unfold_%s_sys_unfolding_iterative%d_splitMC.root",ver.Data(),highIter);
    }
    TFile* f_den = new TFile(Form("%s",denfname.Data()));
    if(sample=="data"){
        for(int j=0;j<nCentBinIF;++j){
            h1D_den[j] = (TH1D*) f_den->Get(Form("roounfold_res_%d_rd",j));
            h1D_den[j]->SetName(Form("roounfold_res_%d_rd_den",j));
            h1D_den[j]->Scale(1.,"width");
        }
        h1D_den_pp = (TH1D*) f_den->Get("roounfold_res_pp_rd_pp");
        h1D_den_pp->SetName("roounfold_res_pp_rd_den");
        h1D_den_pp->Scale(1.,"width");
    } else if(sample!="data" && doHighIter){
        for(int j=0;j<nCentBinIF;++j){
            h1D_den[j] = (TH1D*) f_den->Get(Form("roounfold_res_%d_mc",j));
            h1D_den[j]->SetName(Form("roounfold_res_%d_mc_den",j));
            h1D_den[j]->Scale(1.,"width");
        }
        h1D_den_pp = (TH1D*) f_den->Get("roounfold_res_pp_mc_pp");
        h1D_den_pp->SetName("roounfold_res_pp_mc_pp_den");
        h1D_den_pp->Scale(1.,"width");
    } else{
        for(int j=0;j<nCentBinIF;++j){
            h1D_den[j] = (TH1D*) f_den->Get(Form("h1D_pt_gen_%d",j));
            h1D_den[j]->Scale(1.,"width");
        }
        h1D_den_pp = (TH1D*) f_den->Get("h1D_pt_gen_pp");
        h1D_den_pp->Scale(1.,"width");
    }

    for(int i=0;i<nIter;++i){
        TString infname = Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/Unfold_%s_sys_unfolding_iterative%d.root",ver.Data(),i+1);
        if(sample=="splitMC") infname = Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/Unfold_%s_sys_unfolding_iterative%d_splitMC.root",ver.Data(),i+1);
        f_in[i] = new TFile(Form("%s",infname.Data()));

        if(sample=="data"){

            //pbpb
            for(int j=0;j<nCentBinIF;++j){
                h1D_reco_unfolded[j][i] =  (TH1D*) f_in[i]->Get(Form("roounfold_res_%d_rd",j));      
                h1D_reco_unfolded[j][i]->SetName(Form("roounfold_res_%d_rd_iter%d",j,i));      
                h1D_reco_unfolded[j][i]->Scale(1.,"width");
                h1D_ratio_reco_unfolded_gen[j][i] = (TH1D*) h1D_reco_unfolded[j][i]->Clone(Form("ratio_cent%d_iter%d",j,i));      
                h1D_ratio_reco_unfolded_gen[j][i]->Divide(h1D_den[j]);
            }
            //pp
            h1D_reco_unfolded_pp[i] = (TH1D*) f_in[i]->Get("roounfold_res_pp_rd_pp");      
            h1D_reco_unfolded_pp[i]->SetName(Form("roounfold_res_pp_rd_pp_iter%d",i));      
            h1D_reco_unfolded_pp[i]->Scale(1.,"width");
            h1D_ratio_reco_unfolded_gen_pp[i] = (TH1D*) h1D_reco_unfolded_pp[i]->Clone(Form("ratio_pp_iter%d",i));      
            h1D_ratio_reco_unfolded_gen_pp[i]->Divide(h1D_den_pp);

        } else{

            //pbpb
            for(int j=0;j<nCentBinIF;++j){
                h1D_reco_unfolded[j][i] =  (TH1D*) f_in[i]->Get(Form("roounfold_res_%d_mc",j));      
                h1D_reco_unfolded[j][i]->SetName(Form("roounfold_res_%d_mc_iter%d",j,i));      
                h1D_reco_unfolded[j][i]->Scale(1.,"width");
                h1D_ratio_reco_unfolded_gen[j][i] = (TH1D*) h1D_reco_unfolded[j][i]->Clone(Form("ratio_cent%d_iter%d",j,i));      
                h1D_ratio_reco_unfolded_gen[j][i]->Divide(h1D_den[j]);
            }
            //pp
            h1D_reco_unfolded_pp[i] = (TH1D*) f_in[i]->Get("roounfold_res_pp_mc_pp");      
            h1D_reco_unfolded_pp[i]->SetName(Form("roounfold_res_pp_mc_iter%d",i));      
            h1D_reco_unfolded_pp[i]->Scale(1.,"width");
            h1D_ratio_reco_unfolded_gen_pp[i] = (TH1D*) h1D_reco_unfolded_pp[i]->Clone(Form("ratio_pp_iter%d",i));      
            h1D_ratio_reco_unfolded_gen_pp[i]->Divide(h1D_den_pp);

        }
    }

    /////////////////////////////////////////////////////////
    // Draw plots : PbPb 
    cout << "DRAW PbPb..." <<endl;
    float ratiomin = 0.95; 
    float ratiomax = 1.05; 
    //float ratiomin = 0.99; 
    //float ratiomax = 1.01; 
    if(sample=="splitMC"){ 
        ratiomin = 0.90; 
        ratiomax = 1.10; 
    }
    TCanvas* ctot[nCentBinIF];
    //pbpb

    TLegend* l1[nCentBinIF];
    for(int j=0;j<nCentBinIF;++j){
        cout << "Centrality bin = " << j << endl;
        l1[j] = new TLegend(0.4742479,0.4763028,0.9351224,0.8916344);
        for(int i=0;i<nIter;i+=dev){
            legStyle(l1[j]);
            if(i==0){
               if(doHighIter) l1[j]->AddEntry(h1D_den[j],Form("%s = %d",legst.Data(),highIter), "pl");
               else l1[j]->AddEntry(h1D_den[j],"GEN", "pl");
            }
            float tempchi2 = chi2(h1D_reco_unfolded[j][i],h1D_den[j],20,200);
            string tempst = float2string(tempchi2);
            cout << "chi2 for iteration " << i+1 << " = " << tempchi2 << endl;
            l1[j]->AddEntry(h1D_reco_unfolded[j][i], Form("%s = %d, #chi^{2} = %.8f",legst.Data(),i+1,tempchi2), "pl");
            //l1[j]->AddEntry(h1D_reco_unfolded[j][i], Form("iter = %d, #chi^{2} = %s",i+1,tempst.data()), "pl");
            //if(!doSplitMC) l1[j]->AddEntry(h1D_reco_unfolded[j][i], Form("iter = %d, #chi^{2} = %s",i+1,tempst.data()), "pl");
            //else l1[j]->AddEntry(h1D_reco_unfolded[j][i], Form("iter = %d, #chi^{2} = %.4f",i+1,tempchi2), "pl");
            //l1[j]->AddEntry(h1D_reco_unfolded[j][i], Form("iter = %d, #chi^{2} = %f",i+1,tempchi2), "pl");
        }
    }

    for(int j=0;j<nCentBinIF;++j){
        // rebin ptbins for each centrality bins since we have less bins for peripheral region
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];
        double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
            ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
        }
        ctot[j] = new TCanvas(Form("ctot%d",j),"",400,600);
        ratioPanelCanvas(ctot[j]);

        ctot[j]->cd(1); // Dist 
        gPad->SetLogy();
        //gPad->SetLogx();
        SetHistTextSize(h1D_den[j]);
        h1D_den[j]->SetMarkerStyle(24);
        h1D_den[j]->SetMarkerColor(1);
        h1D_den[j]->SetLineColor(1);
        h1D_den[j]->SetTitle(";p_{T}^{#gamma} (GeV); Entires");
        h1D_den[j]->DrawCopy("p");
        for(int i=0;i<nIter;i+=dev){
            h1D_reco_unfolded[j][i]->SetMarkerStyle(markerStyle[i/dev]);
            h1D_reco_unfolded[j][i]->SetMarkerColor(colHere[i/dev]);
            h1D_reco_unfolded[j][i]->SetLineColor(colHere[i/dev]);
            h1D_reco_unfolded[j][i]->DrawCopy("same p");
        }
        l1[j]->Draw("same");
        drawText(Form("%s PbPb",sample.Data()),0.2,0.2+0.05);
        drawText(Form("%d%s-%d%s",centBins_i[j]/2,"%",centBins_f[j]/2,"%"),0.2,0.2);
        //drawText(Form("%s",ver.Data()),0.2,0.2-0.05);
        jumSun(ptBins_unfolding_centDep[1],ratiomin,ptBins_unfolding_centDep[1],ratiomax);
        jumSun(ptBins_unfolding_centDep[nPtBin_unfolding_centDep-1],ratiomin,ptBins_unfolding_centDep[nPtBin_unfolding_centDep-1],ratiomax);

        ctot[j]->cd(2); // Ratio
        //gPad->SetLogx();
        for(int i=0;i<nIter;i+=dev){
            SetHistTextSize(h1D_ratio_reco_unfolded_gen[j][i]);
            h1D_ratio_reco_unfolded_gen[j][i]->SetMarkerStyle(markerStyle[i/dev]);
            h1D_ratio_reco_unfolded_gen[j][i]->SetMarkerColor(colHere[i/dev]);
            h1D_ratio_reco_unfolded_gen[j][i]->SetLineColor(colHere[i/dev]);
            removeHistError(h1D_ratio_reco_unfolded_gen[j][i]);
            if(i==0){ 
                if(doHighIter) h1D_ratio_reco_unfolded_gen[j][i]->SetTitle(Form(";p_{T}^{#gamma} (GeV);Ratio (w.r.t %s%d)",legst.Data(),highIter));
                else h1D_ratio_reco_unfolded_gen[j][i]->SetTitle(";p_{T}^{#gamma} (GeV);Ratio (RECO/GEN)");
                h1D_ratio_reco_unfolded_gen[j][i]->GetYaxis()->SetRangeUser(ratiomin,ratiomax);
                h1D_ratio_reco_unfolded_gen[j][i]->SetTitleOffset(2.5,"X");
                h1D_ratio_reco_unfolded_gen[j][i]->SetTitleOffset(2.6,"Y");
                h1D_ratio_reco_unfolded_gen[j][i]->DrawCopy("p");
            } else{ h1D_ratio_reco_unfolded_gen[j][i]->DrawCopy("same p");}
        }
        jumSun(ptBins_unfolding_centDep[0],1,ptBins_unfolding_centDep[nPtBin_unfolding_centDep],1);
        jumSun(ptBins_unfolding_centDep[1],ratiomin,ptBins_unfolding_centDep[1],ratiomax);
        jumSun(ptBins_unfolding_centDep[nPtBin_unfolding_centDep-1],ratiomin,ptBins_unfolding_centDep[nPtBin_unfolding_centDep-1],ratiomax);

        ctot[j]->SaveAs(Form("%sfigures/unfoldingIterationFigures_%s_cent%dto%d%s.pdf",dir.Data(),ver.Data(),centBins_i[j]/2,centBins_f[j]/2,cap.Data()));
    }

    /////////////////////////////////////////////////////////
    // Draw plots : pp 
    cout << "DRAW pp..." <<endl;
    TCanvas* ctot_pp = new TCanvas("ctot_pp","",400,600);
    ratioPanelCanvas(ctot_pp);

    TLegend* l1_pp = new TLegend(0.4742479,0.4763028,0.9351224,0.8916344);
    for(int i=0;i<nIter;i+=dev){
        legStyle(l1_pp);
        if(i==0){
            if(doHighIter) l1_pp->AddEntry(h1D_den_pp,Form("%s = %d",legst.Data(),highIter), "pl");
            else l1_pp->AddEntry(h1D_den_pp,"GEN", "pl");
        }
        double tempchi2 = chi2(h1D_reco_unfolded_pp[i],h1D_den_pp,20,200);
        l1_pp->AddEntry(h1D_reco_unfolded_pp[i], Form("%s = %d, #chi^{2} = %.8f",legst.Data(),i+1,tempchi2), "pl");
    }
    ctot_pp->cd(1); // Dist 
    gPad->SetLogy();
    //gPad->SetLogx();
    SetHistTextSize(h1D_den_pp);
    h1D_den_pp->SetTitle(";p_{T}^{#gamma} (GeV); Entires");
    h1D_den_pp->SetMarkerStyle(24);
    h1D_den_pp->SetMarkerColor(1);
    h1D_den_pp->SetLineColor(1);
    h1D_den_pp->DrawCopy("p");
    for(int i=0;i<nIter;i+=dev){
        //cout << "iteration = " << i << ", color = " << colHere[i/dev] << endl;
        h1D_reco_unfolded_pp[i]->SetMarkerStyle(markerStyle[i/dev]);
        h1D_reco_unfolded_pp[i]->SetMarkerColor(colHere[i/dev]);
        h1D_reco_unfolded_pp[i]->SetLineColor(colHere[i/dev]);
        h1D_reco_unfolded_pp[i]->DrawCopy("same p");
    }
    l1_pp->Draw("same");
    drawText(Form("%s pp",sample.Data()),0.2,0.2+0.05);
    //drawText(Form("%s",ver.Data()),0.2,0.2-0.05);
    jumSun(ptBins_unfolding[1],ratiomin,ptBins_unfolding[1],ratiomax);
    jumSun(ptBins_unfolding[nPtBin_unfolding-1],ratiomin,ptBins_unfolding[nPtBin_unfolding-1],ratiomax);

    ctot_pp->cd(2); // Ratio
    //gPad->SetLogx();
    for(int i=0;i<nIter;i+=dev){
        SetHistTextSize(h1D_ratio_reco_unfolded_gen_pp[i]);
        h1D_ratio_reco_unfolded_gen_pp[i]->SetMarkerStyle(markerStyle[i/dev]);
        h1D_ratio_reco_unfolded_gen_pp[i]->SetMarkerColor(colHere[i/dev]);
        h1D_ratio_reco_unfolded_gen_pp[i]->SetLineColor(colHere[i/dev]);
        removeHistError(h1D_ratio_reco_unfolded_gen_pp[i]);
        if(i==0){
            if(doHighIter) h1D_ratio_reco_unfolded_gen_pp[i]->SetTitle(Form(";p_{T}^{#gamma} (GeV);Ratio (w.r.t %s%d)",legst.Data(),highIter));
            else h1D_ratio_reco_unfolded_gen_pp[i]->SetTitle(";p_{T}^{#gamma} (GeV);Ratio (RECO/GEN)");
            //cout << " x offset : " <<  h1D_ratio_reco_unfolded_gen_pp[i]->GetTitleOffset("X") << endl;;
            //cout << " y offset : " <<  h1D_ratio_reco_unfolded_gen_pp[i]->GetTitleOffset("Y") << endl;;
            h1D_ratio_reco_unfolded_gen_pp[i]->SetTitleOffset(2.5,"X");
            h1D_ratio_reco_unfolded_gen_pp[i]->SetTitleOffset(2.6,"Y");
            h1D_ratio_reco_unfolded_gen_pp[i]->GetYaxis()->SetRangeUser(ratiomin,ratiomax);
            h1D_ratio_reco_unfolded_gen_pp[i]->DrawCopy("p");
        }else{ 
            h1D_ratio_reco_unfolded_gen_pp[i]->DrawCopy("same p");
        }
    }
    jumSun(ptBins_unfolding[0],1,ptBins_unfolding[nPtBin_unfolding],1);
    jumSun(ptBins_unfolding[1],ratiomin,ptBins_unfolding[1],ratiomax);
    jumSun(ptBins_unfolding[nPtBin_unfolding-1],ratiomin,ptBins_unfolding[nPtBin_unfolding-1],ratiomax);

    ctot_pp->SaveAs(Form("%sfigures/unfoldingIterationFigures_%s_pp%s.pdf",dir.Data(),ver.Data(),cap.Data()));

}
