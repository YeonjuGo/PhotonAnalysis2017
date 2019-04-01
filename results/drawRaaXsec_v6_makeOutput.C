// drawRaaXsec.C 
// This version gets photon raw distributions from the output/rawDist.root, while version 1 calculate these in that code. 
// Author: Yeonju Go 
// Written at 2017 Mar 17
// Modified : 2018 Aug 22
// It's modified to be used from phoRaaCuts_v23.h 
// from v10, efficiency macro has been changed to divide efficiency into reco & iso seperately.  

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
//#include "../ElectroWeak-Jet-Track-Analyses/Histogramming/PhotonPurity.C"
//#include "../ElectroWeak-Jet-Track-Analyses/Utilities/interface/CutConfigurationParser.h"
//#include "../ElectroWeak-Jet-Track-Analyses/TreeHeaders/CutConfigurationTree.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"

const TString LABEL = "PbPb #sqrt{s}_{_{NN}}=5.02 TeV";
const int colHere[]={1,2,4,kGreen+1,kYellow+1};
//const int markerHere[]={24,28,28,28,28,28};
//const int colHere[]={kBlack,kPink-6,kGreen+3,kBlue-3,kOrange+4};
const int markerHere[]={20,33,34,29,24,29};
const int markerHere_closed[]={20,33,33,33,33};
//TH1D* removeUnderOverBin(TH1D *h1);
void drawRaaXsec_v6_makeOutput(TString ver="190303_temp_v28_nominal", bool doSplitPD = true,  bool purityTest = false)
{
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0000);
    TFile* f_in = new TFile(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/Unfold_%s.root",ver.Data()));
    TFile* f_in_2 = new TFile(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/phoRaa_%s_beforeUnfolding.root",ver.Data()));

    TH1D* h1D_corr[nCentBinIF]; // corrected yield 1. purity, 2. efficiency 
    TH1D* h1D_corrpp; // corrected yield 1. purity, 2. efficiency 
    TH1D* h1D_Raa[nCentBinIF]; // total Raa!!
    TH1D* h1D_raw[nCentBinIF];
    TH1D* h1D_rawpp;
    
    for(int j=0;j<nCentBinIF;++j)
    {
        cout << "cent "<< j << endl; 
        h1D_corr[j] = (TH1D*) f_in->Get(Form("roounfold_res_%d_rd",j));
        h1D_corr[j]->SetName(Form("h1D_dNdpt_corr2_cent%d",j));
        h1D_raw[j] = (TH1D*) f_in_2->Get(Form("h1D_raw_cent%d",j));
        h1D_Raa[j] = new TH1D(Form("h1D_Raa_cent%d",j),Form(";p_{T}^{#gamma} (GeV);R_{AA}"),nPtBin_unfolding,ptBins_unfolding);
    }

    h1D_corrpp = (TH1D*) f_in->Get("roounfold_res_pp_rd_pp");
    h1D_corrpp->SetName("h1D_dNdpt_corr2_pp");
   // /////////////////////////////////////////////////////////////////////////////////////////////////////////// 
   // /// Get & Calculate & Set statistical errors
   // cout << "Get statistical error part..." <<endl;
   // TH1D* h1D_corr_forErr[nCor][nCentBinIF]; // corrected yield 1. purity, 2. efficiency 
   // TH1D* h1D_corrpp_forErr[nCor]; // corrected yield 1. purity, 2. efficiency 
   // TH1D* h1D_Raa_forErr[nCentBinIF]; // total Raa!!
   // 
   // for(int j=0;j<nCentBinIF;++j)
   // {
   //     for(int ii=0;ii<nCor;ii++){ // corrected yield 0th:raw 1st:purity 2nd:purity and efficiency
   //         h1D_corr_forErr[ii][j] = (TH1D*) h1D_corr[ii][j]->Clone(Form("%s_forErr", h1D_corr[ii][j]->GetName()));
   //         if(j==0)
   //             h1D_corrpp_forErr[ii] = (TH1D*) h1D_corrpp[ii]->Clone(Form("%s_forErr", h1D_corrpp[ii]->GetName()));
   //     }
   //     h1D_Raa_forErr[j] = (TH1D*) h1D_Raa[j]->Clone(Form("%s_forErr", h1D_Raa[j]->GetName()));
   // } 

   // for(int j=0;j<nCentBinIF;++j)
   // {
   //    // h1D_corr_forErr[0][j]->SetBinContent(ipt+1, vRaw); 
   //    // h1D_corr_forErr[1][j]->SetBinContent(ipt+1, vRaw*vPur); 
   //     h1D_corr_forErr[2][j]->Divide(h1D_raw[j],h1D_eff[j]);
   // }

   // h1D_corrpp_forErr[2]->Divide(h1D_rawpp,h1D_effpp);
   //  
   // for(int j=0;j<nCentBin+1;j++)
   // {
   //     for(int ipt=0;ipt<nPtBin;++ipt){
   //         Double_t err;
   //         err = h1D_corr_forErr[2][j]->GetBinError(ipt+1);
   //         h1D_corr[2][j]->SetBinError(ipt+1, err); 
   //     }
   //     if(j==0) {
   //         for(int ipt=0;ipt<nPtBin;++ipt){
   //             Double_t err;
   //             err = h1D_corrpp_forErr[2]->GetBinError(ipt+1);
   //             h1D_corrpp[2]->SetBinError(ipt+1, err); 
   //         }
   //     }
   // }

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
    /////////////////////////////////////////////////////////////////////////// 
    /// Draw Raa 
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/";
    cout << "!!DRAW RAA!!" << endl;

    TLegend* l1 = new TLegend(0.6,0.65,0.8,0.89);
    legStyle(l1);

    TCanvas* c1 = new TCanvas("craa","",400,400);
    for(int j=0;j<nCentBin+1;j++)
    {
        h1D_Raa[j]->Divide(h1D_corr[j],h1D_corrpp);
        removeHistLastBins(h1D_Raa[j],rejectPtBins[j]);
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
        jumSun(ptBins_unfolding[0],1,ptBins_unfolding[nPtBin_unfolding],1);
        l1->AddEntry(h1D_Raa[j],Form("%d%s-%d%s",centBins_i[j]/2,"%",centBins_f[j]/2,"%")); 
    }
    l1->Draw("same");
    if(purityTest) c1->SaveAs(Form("%sfigures/phoRaa_%s_purityTest.pdf",dir.Data(),ver.Data()));
    else c1->SaveAs(Form("%sfigures/phoRaa_%s.pdf",dir.Data(),ver.Data()));
   
    /////////////////////////////////////////////////////////////////////////// 
    /// Draw cross section

    TLegend* l2 = new TLegend(0.6,0.65,0.8,0.89);
    legStyle(l2);

    TCanvas* c2 = new TCanvas("cXsec","",400,400);
    c2->cd();
    c2->SetLogy();
    //SetHistTextSize(h1D_corrpp[2]);
   // h1D_corrpp->Scale(1./lumi_pp);
   // h1D_corrpp->Scale(1e12);
   // h1D_corrpp->Scale(1./2.88);
    h1D_corrpp->SetMarkerStyle(21);
    h1D_corrpp->SetMarkerColor(kGreen+1);
    h1D_corrpp->SetTitle(";p_{T}^{#gamma} (GeV); #frac{1}{T_{AA}} #frac{dN}{dp_{T}} (pb/GeV)");
    h1D_corrpp->GetYaxis()->CenterTitle();
    h1D_corrpp->GetXaxis()->CenterTitle();
    h1D_corrpp->Draw("pe");
    l2->AddEntry(h1D_corrpp,"pp"); 
    for(int j=0;j<nCentBinIF;j++){
        //SetHistTextSize(h1D_corr[2][j]);
       // h1D_corr[j]->Scale(1./TA[j]/nMB[j]);
       // h1D_corr[j]->Scale(1e12);
       // h1D_corr[j]->Scale(1./2.88);
        removeHistLastBins(h1D_corr[j],rejectPtBins[j]);
        h1D_corr[j]->SetMarkerStyle(markerHere[j]);
        h1D_corr[j]->SetMarkerColor(colHere[j]);
        h1D_corr[j]->SetLineColor(colHere[j]);
        h1D_corr[j]->Draw("pe same");
        l2->AddEntry(h1D_corr[j],Form("%d%s-%d%s",centBins_i[j]/2,"%",centBins_f[j]/2,"%")); 
    }
    l2->Draw("same");
    if(purityTest) c2->SaveAs(Form("%sfigures/phoXsec_%s_purityTest.pdf",dir.Data(),ver.Data()));
    else c2->SaveAs(Form("%sfigures/phoXsec_%s.pdf",dir.Data(),ver.Data()));
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    /// Calulate 0-100 % bin &&
    ///
    cout << "Calculate 0-100 \% bin... " << endl;
    TH1D* h1D_corr_noCal = (TH1D*) h1D_corr[0]->Clone(Form("%s_noCal",h1D_corr[0]->GetName()));// 0-100% from eff. pur. copied
    TH1D* h1D_Raa_noCal = (TH1D*) h1D_Raa[0]->Clone(Form("%s_noCal",h1D_Raa[0]->GetName())); //

    double weight[nCentBinIF];
    double entries[nCentBinIF]; 
    for(int j=0;j<nCentBinIF;j++){
        entries[j] = h1D_raw[j]->Integral(2,6);
        if(j!=0) weight[j] = entries[j]/entries[0];
        cout << "weight for cent : " << centBins_i[j] << "\% to " << centBins_f[j] << "\% = " <<entries[j]<<"/"<<entries[0]<<" = " <<  weight[j] << endl;
    }

    for(int j=1;j<nCentBinIF;j++){
        if(j==1){
            h1D_Raa[0] = (TH1D*) h1D_Raa[j]->Clone(Form("%s",h1D_Raa[0]->GetName())); //
            h1D_Raa[0]->Scale(weight[j]);
        } else{
            h1D_Raa[0]->Add(h1D_Raa[j],weight[j]);
        }
    }
    
    for(int j=1;j<nCentBinIF;j++){
        if(j==1){
            h1D_corr[0] = (TH1D*) h1D_corr[j]->Clone(Form("%s",h1D_corr[0]->GetName())); //
            h1D_corr[0]->Scale(weight[j]);
        } else{
            h1D_corr[0]->Add(h1D_corr[j],weight[j]);
        }
    }

/////////////////// weight based on minbias centrality distribution /////////////////////////
//   for(int j=1;j<nCentBinIF;j++){
//   double centWeight = (centBins_f[j]-centBins_i[j])/2./100.;
//   if(j==1){
//   h1D_Raa[0] = (TH1D*) h1D_Raa[j]->Clone(Form("%s",h1D_Raa[0]->GetName())); //
//   } else{
//   h1D_Raa[0]->Multiply(h1D_Raa[j]);
//   }
//   h1D_Raa[0]->Scale(centWeight);
//   }
//   for(int j=1;j<nCentBinIF;j++){
//   double centWeight = (centBins_f[j]-centBins_i[j])/2./100.;
//   if(j==1){
//   h1D_corr[2][0] = (TH1D*) h1D_corr[2][j]->Clone(Form("%s",h1D_corr[2][0]->GetName())); //
//
//   } else{
//   h1D_corr[2][0]->Multiply(h1D_corr[2][j]);
//   }
//   h1D_corr[2][0]->Scale(centWeight);
//   }


    ///////////////////////////////////////////////////////////////////////////////////////////
    /// Store histograms in output file 
    TString outName = Form("%soutput/phoRaa_%s.root",dir.Data(),ver.Data());
    if(purityTest) outName = Form("%soutput/phoRaa_%s_purityTest.root",dir.Data(),ver.Data());
    
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

//TH1D* removeUnderOverBin(TH1D *h1){
//    //cout << "removeUnderOverBin"<< j << endl; 
//    Int_t nBins_org = h1->GetNbinsX();
//    Int_t nBins = nBins_org-2; 
//    double newPtBins[nBins_org-2];
//    for(Int_t ix=1; ix<=nBins_org; ++ix){
//        double ptBins_org = h1->GetBinLowEdge(ix);
//        if(ix==1) continue;
//        else newPtBins[ix-1] = ptBins_org; 
//    }
//    cout << "Original Bins >>>> " << endl; 
//    for(Int_t ix=1; ix<=nBins_org; ++ix){
//        if(ix==nBins_org){
//            cout << h1->GetBinLowEdge(ix) << endl;
//            cout << h1->GetBinLowEdge(ix)+h1->GetBinWidth(ix) << endl;
//        } else{
//            cout << h1->GetBinLowEdge(ix) << endl;
//        }
//    }
//    cout << "New Bins >>>> " << endl; 
//    for(Int_t ix=0; ix<=nBins; ++ix)
//        cout << newPtBins[ix] << endl;
//    
//    TH1D* hn = new TH1D(Form("%s_AN",h1->GetName()), Form("%s",h1->GetTitle()), nBins,newPtBins);
//    for(Int_t ix=1; ix<=nBins; ++ix){
//        double x = h1->GetBinContent(ix+1);
//        double xerr = h1->GetBinError(ix+1);
//        hn->SetBinContent(ix,x); 
//        hn->SetBinError(ix,xerr); 
//    }
//    return hn;
//}
