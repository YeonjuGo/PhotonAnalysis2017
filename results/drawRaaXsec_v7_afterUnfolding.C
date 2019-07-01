// drawRaaXsec_v7_aftereUnfolding.C 
// This version gets photon raw distributions from the output/rawDist.root, while version 1 calculate these in that code. 
// Author: Yeonju Go 
// Written at 2017 Mar 17
// Modified : 2019 June 26
// It's modified to be used from phoRaaCuts_v23.h 
// from v10, efficiency macro has been changed to divide efficiency into reco & iso seperately.  
//
// // It's modified to be used from phoRaaCuts_v29.h
// // 2019June25) different unfolding binning depending on centrality bin
// // 2019June25) apply trigger efficiency which is derived using DATA to here but not draw in canvas
// // 2019June25) unfolding binning (20 GeV to 300 GeV)

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
const int colHere[]={1,2,4,kGreen+1,kYellow+1};
//const int markerHere[]={24,28,28,28,28,28};
//const int colHere[]={kBlack,kPink-6,kGreen+3,kBlue-3,kOrange+4};
const int markerHere[]={20,33,34,29,24,29};
const int markerHere_closed[]={20,33,33,33,33};

void drawRaaXsec_v7_afterUnfolding(TString ver="190303_temp_v28_nominal", bool doSplitPD = true,  bool usePurityFit = true)
{
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0000);
    TFile* f_in = new TFile(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/Unfold_%s.root",ver.Data()));
    TFile* f_in_2 = new TFile(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/phoRaa_%s_beforeUnfolding.root",ver.Data()));

    TH1D* h1D_corr[nCentBinIF]; // corrected yield 1. purity, 2. efficiency 
    TH1D* h1D_corrpp; // corrected yield 1. purity, 2. efficiency 
    TH1D* h1D_corrpp_temp[nCentBinIF]; // corrected yield 1. purity, 2. efficiency 
    TH1D* h1D_Raa[nCentBinIF]; // total Raa!!
    TH1D* h1D_raw[nCentBinIF];
    TH1D* h1D_rawpp;
    
    for(int j=0;j<nCentBinIF;++j)
    {
        // rebin ptbins for each centrality bins since we have less bins for peripheral region
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];
        double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
            ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
        }
        cout << "cent "<< j << endl; 
        h1D_corr[j] = (TH1D*) f_in->Get(Form("roounfold_res_%d_rd",j));
        h1D_corr[j]->SetName(Form("h1D_dNdpt_corr2_cent%d",j));
        h1D_raw[j] = (TH1D*) f_in_2->Get(Form("h1D_raw_cent%d",j));
        h1D_Raa[j] = new TH1D(Form("h1D_Raa_cent%d",j),Form(";p_{T}^{#gamma} (GeV);R_{AA}"),nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
        h1D_corrpp_temp[j] = new TH1D(Form("h1D_dNdpt_corr2_pp_temp_cent%d",j),Form(";p_{T}^{#gamma} (GeV);R_{AA}"),nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
    }

    h1D_corrpp = (TH1D*) f_in->Get("roounfold_res_pp_rd_pp");
    h1D_corrpp->SetName("h1D_dNdpt_corr2_pp");

    /////////////////////////////////////////////////////////////////////////// 
    /// Set Global Values 
    cout << "Define Global Values..." <<endl;

    double lumi_pp = 27.4*1e12; //25.775 pb-1 systematic 2.3%
    const double nMBTot = 2.722608696*1e9; 
    double nMB[nCentBin+1];
    nMB[0] = nMBTot;
    for(int j=1;j<nCentBin+1;j++){
        nMB[j] = nMBTot*(centBins_f[j]-centBins_i[j])/2./100.;
    }

    for(int j=0;j<nCentBin+1;j++){
        cout << "cent "<<centBins_i[j]/2<<"%-"<<centBins_f[j]/2<<"% TA = " << TA[j] << endl;
        cout << "cent "<<centBins_i[j]/2<<"%-"<<centBins_f[j]/2<<"\% nMB = " << nMB[j] << endl;
        cout << "cent "<<centBins_i[j]/2<<"%-"<<centBins_f[j]/2<<"\% lumipp/TA/nMB = " << lumi_pp/TA[j]/nMB[j] << endl;
    }

    for(int j=0;j<nCentBin+1;j++)
        h1D_corr[j]->Scale(1.,"width");

    h1D_corrpp->Scale(1.,"width");

    for(int j=0;j<nCentBinIF;j++){
        // rebin ptbins for each centrality bins since we have less bins for peripheral region
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];
        double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
            ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
        }

        for(int i=0;i<nPtBin_unfolding_centDep;i++){
            h1D_corrpp_temp[j]->SetBinContent(i+1,h1D_corrpp->GetBinContent(i+1));     
            h1D_corrpp_temp[j]->SetBinError(i+1,h1D_corrpp->GetBinError(i+1));     
        }
    }

    
    /////////////////////////////////////////////////////////////////////////////////////////////
    /// Calulate 0-100 % bin &&
    ///
    cout << "Calculate 0-100 \% bin... " << endl;
    TH1D* h1D_corr_noCal = (TH1D*) h1D_corr[0]->Clone(Form("%s_noCal",h1D_corr[0]->GetName()));// 0-100% from eff. pur. copied
    TH1D* h1D_Raa_noCal = (TH1D*) h1D_Raa[0]->Clone(Form("%s_noCal",h1D_Raa[0]->GetName())); //

    double weight[nCentBinIF];
    double entries[nCentBinIF];
    double tempBinVal[nCentBinIF][nPtBin_unfolding];
    double tempBinErr[nCentBinIF][nPtBin_unfolding];
    double finalVal[nPtBin_unfolding];
    double finalErr[nPtBin_unfolding];
    for(int j=1;j<nCentBinIF;j++)
        entries[j] = h1D_corr[j]->Integral();
    
    double totEntries = (entries[1]+entries[2]+entries[3]+entries[4]);
    for(int j=1;j<nCentBinIF;j++){
        if(j!=0) weight[j] = entries[j]/totEntries;
        cout << "weight for cent : " << centBins_i[j] << "\% to " << centBins_f[j] << "\% = " <<entries[j]<<"/"<<totEntries<<" = " <<  weight[j] << endl;
    }

    for(int j=1;j<nCentBinIF;j++){
        // rebin ptbins for each centrality bins since we have less bins for peripheral region
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];

        for(int i=0;i<nPtBin_unfolding_centDep;i++){
            tempBinVal[j][i] = h1D_corr[j]->GetBinContent(i+1);
            tempBinErr[j][i] = h1D_corr[j]->GetBinError(i+1);
            if(j==1) finalVal[i]=0.0;
            if(j==1) finalErr[i]=0.0;
        }
    }

    for(int i=0;i<nPtBin_unfolding;i++){
        if(i<nPtBin_unfolding-2){
            for(int j=1;j<nCentBinIF;j++){
                finalVal[i] += tempBinVal[j][i]*weight[j];
                finalErr[i] += tempBinErr[j][i]*weight[j];
            }
        } else if(i>=nPtBin_unfolding-2 && i<nPtBin_unfolding-1){
            for(int j=1;j<nCentBinIF-1;j++){
                finalVal[i] += tempBinVal[j][i]*entries[j]/(entries[1]+entries[2]+entries[3]);
                finalErr[i] += tempBinErr[j][i]*entries[j]/(entries[1]+entries[2]+entries[3]);
            }
        } else if(i>=nPtBin_unfolding-1 && i<nPtBin_unfolding){
            for(int j=1;j<nCentBinIF-2;j++){
                finalVal[i] += tempBinVal[j][i]*entries[j]/(entries[1]+entries[2]);
                finalErr[i] += tempBinErr[j][i]*entries[j]/(entries[1]+entries[2]);
            }
        }
    }
    for(int i=0;i<nPtBin_unfolding;i++){
        h1D_corr[0]->SetBinContent(i+1,finalVal[i]);
        h1D_corr[0]->SetBinError(i+1,finalErr[i]);
    }

    h1D_Raa[0] = (TH1D*) h1D_corr[0]->Clone(Form("%s",h1D_Raa[0]->GetName()));
    h1D_Raa[0]->Divide(h1D_corrpp);
 

    /////////////////////////////////////////////////////////////////////////// 
    /// Draw Raa 
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/";
    cout << "!!DRAW RAA!!" << endl;

    TLegend* l1 = new TLegend(0.6,0.65,0.8,0.89);
    legStyle(l1);

    TCanvas* c1 = new TCanvas("craa","",400,400);
    gPad->SetLogx();
    for(int j=0;j<nCentBinIF;j++)
    {
        // rebin ptbins for each centrality bins since we have less bins for peripheral region
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];
        double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
            ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
        }

        h1D_Raa[j]->Divide(h1D_corr[j],h1D_corrpp_temp[j]);
        //removeHistLastBins(h1D_Raa[j],rejectPtBins[j]);
        //h1D_Raa[j]->Scale(lumi_pp/(TA[j])/(nMB[j]));
        h1D_Raa[j]->SetMarkerColor(colHere[j]);
        h1D_Raa[j]->SetLineColor(colHere[j]);
        h1D_Raa[j]->SetMarkerStyle(markerHere[j]);
        //h1D_Raa[j]->SetMarkerStyle(markerHere_closed[j]);
        h1D_Raa[j]->SetMarkerSize(1);
        //h1D_Raa[j]->GetYaxis()->SetRangeUser(0.5,2.0);
        h1D_Raa[j]->GetYaxis()->SetRangeUser(0.5,1.5);
        if(ver.SubString("sys_eff")=="sys_eff") h1D_Raa[j]->GetYaxis()->SetRangeUser(0.5,2.0);
        h1D_Raa[j]->GetYaxis()->CenterTitle();
        h1D_Raa[j]->GetXaxis()->CenterTitle();
        h1D_Raa[j]->SetTitle(";isolated p_{T}^{#gamma} (GeV);R_{AA}");
        if(j==0) h1D_Raa[j]->Draw("pel");
        else h1D_Raa[j]->Draw("pel same");
        l1->AddEntry(h1D_Raa[j],Form("%d%s-%d%s",centBins_i[j]/2,"%",centBins_f[j]/2,"%")); 
    }
    jumSun(ptBins_unfolding[0],1,ptBins_unfolding[nPtBin_unfolding],1);
    jumSun(ptBins_unfolding[1],0.5,ptBins_unfolding[1],1.5);
    jumSun(ptBins_unfolding[nPtBin_unfolding-1],0.5,ptBins_unfolding[nPtBin_unfolding-1],1.5);
    l1->Draw("same");
    if(!usePurityFit) c1->SaveAs(Form("%sfigures/phoRaa_afterUnfolding_%s_noPurityFit.pdf",dir.Data(),ver.Data()));
    else c1->SaveAs(Form("%sfigures/phoRaa_afterUnfolding_%s.pdf",dir.Data(),ver.Data()));
   
    /////////////////////////////////////////////////////////////////////////// 
    /// Draw cross section

    TLegend* l2 = new TLegend(0.6,0.65,0.8,0.89);
    legStyle(l2);

    TCanvas* c2 = new TCanvas("cXsec","",400,400);
    c2->cd();
    c2->SetLogy();
    h1D_corrpp->SetMarkerStyle(21);
    h1D_corrpp->SetMarkerColor(kGreen+1);
    h1D_corrpp->SetTitle(";p_{T}^{#gamma} (GeV); #frac{1}{T_{AA}} #frac{dN}{dp_{T}} (pb/GeV)");
    h1D_corrpp->GetYaxis()->CenterTitle();
    h1D_corrpp->GetXaxis()->CenterTitle();
    h1D_corrpp->Draw("pe");
    l2->AddEntry(h1D_corrpp,"pp"); 
    for(int j=0;j<nCentBinIF;j++){
        //removeHistLastBins(h1D_corr[j],rejectPtBins[j]);
        h1D_corr[j]->SetMarkerStyle(markerHere[j]);
        h1D_corr[j]->SetMarkerColor(colHere[j]);
        h1D_corr[j]->SetLineColor(colHere[j]);
        h1D_corr[j]->Draw("pe same");
        l2->AddEntry(h1D_corr[j],Form("%d%s-%d%s",centBins_i[j]/2,"%",centBins_f[j]/2,"%")); 
    }
    l2->Draw("same");
    if(!usePurityFit) c2->SaveAs(Form("%sfigures/phoXsec_afterUnfolding_%s_noPurityFit.pdf",dir.Data(),ver.Data()));
    else c2->SaveAs(Form("%sfigures/phoXsec_afterUnfolding_%s.pdf",dir.Data(),ver.Data()));

    ///////////////////////////////////////////////////////////////////////////////////////////
    /// Store histograms in output file 
    TString outName = Form("%soutput/phoRaa_afterUnfolding_%s.root",dir.Data(),ver.Data());
    if(!usePurityFit) outName = Form("%soutput/phoRaa_afterUnfolding_%s_noPurityFit.root",dir.Data(),ver.Data());
    
    TFile* outf = new TFile(Form("%s",outName.Data()),"recreate");
    outf->cd();
    for(int j=0;j<nCentBinIF;j++){
        h1D_Raa[j]->Write();
        h1D_corr[j]->Write();
    }
    h1D_corr_noCal->Write();
    h1D_Raa_noCal->Write();
    h1D_corrpp->Write();
    c1->Write();
    c2->Write();

}
