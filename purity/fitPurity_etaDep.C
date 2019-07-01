// yj_quickPhotonPurity.C
// Author: Yeonju Go
// Modified : 2019 June 25 
// Created : 2017 April 10 
// Cobbled together from code written by Alex

// Calculates and plots the photon purity using a sideband estimation
// of the background and a MC calculation of the signal. This info is
// used to do a template fit in the sigmaIetaIeta variable.
// Modified 2019June25) unfolding binning (20 GeV to 300 GeV)
// Modified 2019June25) do NOT calculate purity 0-100% and high pt bins for peripheral events (centrality dependent pt ranges) 

#include "TStyle.h"
#include "TFile.h"
#include "TMath.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCut.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TString.h"
#include "TLatex.h"
#include "stdio.h"
#include <iostream>

#include "PhotonPurity_SBcorrection_v2.h"
#include "../phoRaaCuts/phoRaaCuts_190625_temp_v29_purityEtaDep.h"
//#include "../phoRaaCuts/phoRaaCuts_purity_forPaper.h"
//#include "../phoRaaCuts/phoRaaCuts_temp.h"
#include "../phoRaaCuts/yjUtility.h"

Double_t errFunc(Double_t *x, Double_t *par)
{
    Double_t xx = x[0];
    Double_t fitVal;
    fitVal = par[0]*TMath::Erf((xx-par[1])/par[2]);
    return fitVal;
}

void fitPurity_etaDep(const TString coll="pp", const TString ver="190625_temp_v29_purityEtaDep", bool doSplitPD=true, bool drawGraph = true){
    cout << "Purity Calculation" << endl;
    cout << "::: version = " << ver << endl; 
    cout << "::: doSplitPD = " << doSplitPD << endl; 
    cout << "::: drawGraph = " << drawGraph << endl; 
    gStyle->SetOptStat(0);
    SetyjPadStyle();

    TString outfName=Form("purity_withFunc_%s_%s_splitPD",coll.Data(),ver.Data());
    TString infName=Form("purity_%s_%s_splitPD",coll.Data(),ver.Data());
    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1;

    const int function_number = 0;
    TString func_label = "";
    if(function_number==0) func_label="erf";
    if(function_number==1) func_label="pol0";

    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/purity/";
    TFile* outFile = new TFile(Form("%soutput/%s.root",dir.Data(), outfName.Data()), "RECREATE");
    TH1D* h1D_pur[nCENTBINS][nEtaBin];
    double tempVal[5][20][3];
    double tempErr[5][20][3];
    TH1D* htemp[nCENTBINS][nEtaBin];
    TGraphAsymmErrors* gr_pur[nCENTBINS][nEtaBin];
    TF1* f_temp[nCENTBINS][nEtaBin];
    TF1* f[nCENTBINS][nEtaBin];

    double purityPtBins[] = {24.8528,34.0872, 44.1777,54.243, 67.977, 103.058};
    double purityPtBinsErr[] = {0.0135248,0.0149424,0.0260087,0.0417296,0.0984396,0.585896};
    //double purityPtBins[] = {22.035,27.1233,33.7975,44.1448,54.3516,68.0108,88.7239,111.387,166.239};
    //double purityPtBinsErr[] = {0.00527241,0.00902116,0.0222023,0.0436468,0.0745094,0.180516,0.352182,0.771632,4.80612};
    double purityErr[] = {0.00537754,0.00784533,0.00929191,0.00406089,0.00641795,0.00779047,0.0145724,0.0221101,0.0338031};

    TFile* inFile = new TFile(Form("%soutput/%s.root",dir.Data(), infName.Data()), "READ");
    for(int k=0; k < nEtaBin; ++k){
        if(coll=="pbpb"){
            for (Int_t j = 0; j < nCENTBINS; j++) 
                h1D_pur[j][k] = (TH1D*) inFile->Get(Form("h1D_purity_cent%d_eta%d",j,k));
        } else {
            h1D_pur[0][k] = (TH1D*) inFile->Get(Form("h1D_purity_pp_eta%d",k));
        }
    }

    for(int k=0; k < nEtaBin; ++k){
    for (Int_t j = 0; j < nCENTBINS; j++) {
        htemp[j][k] = new TH1D(Form("htemp%d_%d",j,k),";p_{T}^{#gamma} (GeV);Purity",nPtBin,ptBins);
        gr_pur[j][k] = new TGraphAsymmErrors(nPtBin);
        gr_pur[j][k]->SetName(Form("gr_pur_cent%d_eta%d",j,k));

        for(int ipt=0; ipt<nPtBin;++ipt){
            tempVal[j][ipt][k] = h1D_pur[j][k]->GetBinContent(ipt+1);
            tempErr[j][ipt][k] = h1D_pur[j][k]->GetBinError(ipt+1);
            gr_pur[j][k]->SetPoint(ipt, purityPtBins[ipt], tempVal[j][ipt][k]);
            gr_pur[j][k]->SetPointError(ipt, purityPtBinsErr[ipt], purityPtBinsErr[ipt], tempErr[j][ipt][k], tempErr[j][ipt][k]);
            double tempx, tempy;
            gr_pur[j][k]->GetPoint(ipt,tempx,tempy);
            cout << tempx << ", " << tempy << ", " << tempErr[j][ipt] << endl;
        }//pt loop
    }//cent loop
    }//eta loop

    TCanvas* cPurity;
    TLegend* l1 = new TLegend(0.2,0.3,0.5,0.6);
    legStyle(l1);
    if(coll=="pbpb"){
        cPurity = new TCanvas("c1", "c1", 300*(nCENTBINS), 300);
        makeMultiPanelCanvas(cPurity, (nCENTBINS), 1, 0.0, 0.0 , 0.2, 0.15, 0.005);
    } else{
        cPurity = new TCanvas("c1", "c1", 400, 400);
    }

    for (Int_t j = 0; j < nCENTBINS; j++) {
            cPurity->cd();
        htemp[j][0]->Draw();
    for(int k=0; k < nEtaBin; ++k){
        SetHistTextSize(htemp[j][k]);
        if(drawGraph){
            gr_pur[j][k]->GetYaxis()->SetRangeUser(0.0,1.0);
            gr_pur[j][k]->SetMarkerStyle(20+k);
            gr_pur[j][k]->SetMarkerColor(1+k*2);
            gr_pur[j][k]->SetLineColor(1+k*2);
            gr_pur[j][k]->Draw("P");
            if(j==0) l1->AddEntry(gr_pur[j][k],Form("%.2f < |#eta| < %.2f",etaBins_i[k],etaBins_f[k]),"p"); 
        } else{
            SetHistTextSize(h1D_pur[j][k]);
            h1D_pur[j][k]->GetYaxis()->SetRangeUser(0.0,1.0);
            h1D_pur[j][k]->SetMarkerStyle(20);
            h1D_pur[j][k]->SetMarkerColor(1);
            h1D_pur[j][k]->SetLineColor(1);
            h1D_pur[j][k]->Draw("p hist e same");
        }
    }
        float xpos = 0.75;
        float dy = 0.05;
        if(coll=="pbpb") drawText(Form("%.0f - %.0f%c", centBins_i[j]/2., centBins_f[j]/2., '%'), xpos, 0.40);
        drawText(Form("%s",coll.Data()), xpos, 0.40+dy);
        l1->Draw("same");
        //drawText(Form("%.0f < |#eta| <%.0f", etaBins_i[k], etaBins_f[k]), xpos, 0.40+dy*2);
    }
    //if(coll=="pbpb") gr_pur[0] = (TGraphAsymmErrors*) gr_pur[1]->Clone("gr_pur_cent0");

    /////////////////////////////////////////////////////////
    // FIT
    //
    for (Int_t j = 0; j < nCENTBINS; j++) {
    for(int k=0; k < nEtaBin; ++k){
        //if(coll=="pbpb" && j==0) continue;        
        //if(coll=="pbpb") 
        //    cPurity->cd(j);
        //else
            cPurity->cd();
        
        if(function_number==0){
            f_temp[j][k] = new TF1(Form("purity_temp_%s_cent%d",coll.Data(),j), errFunc, ptBins[0], ptBins[nPtBin],3); //nominal
            f[j][k] = new TF1(Form("purity_%s_cent%d",coll.Data(),j), errFunc, ptBins[0], ptBins[nPtBin],3); //nominal
            f_temp[j][k]->SetParameters(7.18606e-01,-1.72893e+02,1.83041e+02);
        } else if(function_number==1){
            f_temp[j][k] = new TF1(Form("purity_temp_%s_cent%d",coll.Data(),j), "pol1", ptBins[0], ptBins[nPtBin-1]); //nominal
            f[j][k] = new TF1(Form("purity_%s_cent%d",coll.Data(),j), "pol1", ptBins[0], ptBins[nPtBin]); //nominal
            f_temp[j][k]->SetParameters(6.20059e-01,2.93156e-03);
        }
        f_temp[j][k]->SetNpx(1000);
        f[j][k]->SetNpx(1000);
        if(drawGraph){
            gr_pur[j][k]->Fit(f_temp[j][k]); 
            gr_pur[j][k]->Fit(f_temp[j][k]); 
        } else{
            h1D_pur[j][k]->Fit(f_temp[j][k], "LL R"); 
            h1D_pur[j][k]->Fit(f_temp[j][k], "LL R"); 
        }
        f_temp[j][k]->Draw("same");
        //f_temp[j][k]->SetMarkerStyle(20+k);
        //f_temp[j][k]->SetMarkerColor(1+k*2);
        f_temp[j][k]->SetLineColor(1+k*2);

        f[j][k]->SetParameter(0,f_temp[j][k]->GetParameter(0));
        f[j][k]->SetParameter(1,f_temp[j][k]->GetParameter(1));
        if(function_number==0) f[j][k]->SetParameter(2,f_temp[j][k]->GetParameter(2));
        //f[j][k]->Draw("same");
    }
    }
    //if(coll=="pbpb") f[0] = (TF1*) f[1]->Clone("purity_pbpb_cent0");
    //if(coll=="pbpb") f_temp[0] = (TF1*) f_temp[1]->Clone("purity_pbpb_cent0");

    //if(coll=="pbpb") h1D_pur[0] = (TH1D*) h1D_pur[1]->Clone(Form("h1D_purity_cent%d",0));
    TString outputPdfName=Form("purity_vs_pt_etaDep_%s_%s",coll.Data(),ver.Data());
    cPurity->SaveAs(Form("%sfigures/%s_%s.pdf",dir.Data(), outputPdfName.Data(),func_label.Data()));

    /////////////////////////////////////
    // Write Output File 
    outFile->cd();
    cPurity->Write();
    for(int k=0; k < nEtaBin; ++k){
    for (Int_t j = 0; j < nCENTBINS; ++j) {
        h1D_pur[j][k]->Write();
        if(drawGraph) gr_pur[j][k]->Write(); 
        f_temp[j][k]->Write();
        f[j][k]->Write();
    }
    }
   // outFile->Close();

}
