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
//#include "../phoRaaCuts/phoRaaCuts_purity_forPaper.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
#include "../phoRaaCuts/yjUtility.h"

Double_t errFunc(Double_t *x, Double_t *par)
{
    Double_t xx = x[0];
    Double_t fitVal;
    fitVal = par[0]*TMath::Erf((xx-par[1])/par[2]);
    return fitVal;
}

Double_t errFuncPol1(Double_t *x, Double_t *par)
{
    Double_t xx = x[0];
    Double_t fitVal;
    fitVal = par[0]*TMath::Erf((xx-par[1])/par[2])+par[3]*xx+par[4];
    return fitVal;
}

void fitPurity_separateCent(const TString coll="pp", const TString ver="190703_temp_v31_pur_SBcorr_centDep", const int function_number = 0, int nIter = 3, bool doSplitPD=true, bool doPreScale=false, bool drawGraph = true){
    cout << "Purity Calculation" << endl;
    cout << "::: version = " << ver << endl; 
    cout << "::: doSplitPD = " << doSplitPD << endl; 
    cout << "::: doPreScale = " << doPreScale << endl; 
    cout << "::: drawGraph = " << drawGraph << endl; 
    gStyle->SetOptStat(0);
    SetyjPadStyle();

    TString cap = "";
    if(doSplitPD) cap+="_splitPD";
    if(!doPreScale) cap+="_noPreScale";
    //if(useMCSB) cap+="_bkgMC";

    TString outfName=Form("purity_withFunc_%s_%s%s_iter%d",coll.Data(),ver.Data(),cap.Data(),nIter);
    TString infName=Form("purity_%s_%s%s",coll.Data(),ver.Data(),cap.Data());
    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1;

    //const int function_number = 1;
    TString func_label = "";
    if(function_number==0) func_label="erf";
    if(function_number==1) func_label="pol2";
    if(function_number==2) func_label="erfPlusPol1";

    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/purity/";
    TFile* outFile = new TFile(Form("%soutput/%s.root",dir.Data(), outfName.Data()), "RECREATE");
    TH1D* h1D_pur[nCENTBINS];
    double tempVal[5][20] ={{0}};
    double tempErr[5][20] ={{0}};
    TH1D* htemp[nCENTBINS];
    TGraphAsymmErrors* gr_pur[nCENTBINS];
    TF1* f_temp[nCENTBINS];
    TF1* f[nCENTBINS];

    double purityPtBins[] = {22.035,27.1233,33.7975,44.1448,54.3516,68.0108,88.7239,111.387,166.239};
    double purityPtBinsErr[] = {0.00527241,0.00902116,0.0222023,0.0436468,0.0745094,0.180516,0.352182,0.771632,4.80612};
    //double purityErr[] = {0.00537754,0.00784533,0.00929191,0.00406089,0.00641795,0.00779047,0.0145724,0.0221101,0.0338031};

    TFile* inFile[nCENTBINS];

    for (Int_t j = 1; j < nCENTBINS; j++) {
        inFile[j] = new TFile(Form("%soutput/purity_%s_%s_cent%d%s.root",dir.Data(),coll.Data(),ver.Data(),j,cap.Data()), "READ");
        if(coll=="pp") 
            h1D_pur[j] = (TH1D*) inFile[j]->Get(Form("h1D_purity_pp_iter%d",nIter));
        else 
            h1D_pur[j] = (TH1D*) inFile[j]->Get(Form("h1D_purity_cent%d_iter%d",j,nIter));
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];
        double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu)
            ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];

        htemp[j] = new TH1D(Form("htemp%d",j),";p_{T}^{#gamma} (GeV);Purity",nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
        gr_pur[j] = new TGraphAsymmErrors(nPtBin_unfolding_centDep);
        gr_pur[j]->SetName(Form("gr_pur_cent%d",j));

        for(int ipt=0; ipt<nPtBin_unfolding_centDep-1;++ipt){
            tempVal[j][ipt] = h1D_pur[j]->GetBinContent(ipt+1);
            tempErr[j][ipt] = h1D_pur[j]->GetBinError(ipt+1);
            gr_pur[j]->SetPoint(ipt, purityPtBins[ipt], tempVal[j][ipt]);
            gr_pur[j]->SetPointError(ipt, purityPtBinsErr[ipt], purityPtBinsErr[ipt], tempErr[j][ipt], tempErr[j][ipt]);
            double tempx, tempy;
            gr_pur[j]->GetPoint(ipt,tempx,tempy);
            cout << tempx << ", " << tempy << ", " << tempErr[j][ipt] << endl;
        }//pt loop
    }//cent loop
    if(coll=="pbpb") h1D_pur[0] = (TH1D*) h1D_pur[1]->Clone("h1D_purity_cent0");

    TCanvas* cPurity;
    if(coll=="pbpb"){
        cPurity = new TCanvas("c1", "c1", 300*(nCENTBINS-1), 300);
        makeMultiPanelCanvas(cPurity, (nCENTBINS-1), 1, 0.0, 0.0 , 0.2, 0.15, 0.005);
    } else{
        cPurity = new TCanvas("c1", "c1", 400, 400);
    }

    for (Int_t j = 0; j < nCENTBINS; j++) {
        if(coll=="pbpb" && j==0) continue;        

        // rebin ptbins for each centrality bins since we have less bins for peripheral region
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];

        if(coll=="pbpb") 
            cPurity->cd(j);
        else
            cPurity->cd();
        SetHistTextSize(htemp[j]);
        htemp[j]->Draw();
        if(drawGraph){
            gr_pur[j]->GetYaxis()->SetRangeUser(0.0,1.0);
            gr_pur[j]->SetMarkerStyle(20);
            gr_pur[j]->SetMarkerColor(1);
            gr_pur[j]->SetLineColor(1);
            gr_pur[j]->Draw("P");
        } else{
            SetHistTextSize(h1D_pur[j]);
            h1D_pur[j]->GetYaxis()->SetRangeUser(0.0,1.0);
            h1D_pur[j]->SetMarkerStyle(20);
            h1D_pur[j]->SetMarkerColor(1);
            h1D_pur[j]->SetLineColor(1);
            h1D_pur[j]->Draw("p hist e same");
        }
        float xpos = 0.75;
        float dy = 0.05;
        if(coll=="pbpb") drawText(Form("%.0f - %.0f%c", centBins_i[j]/2., centBins_f[j]/2., '%'), xpos, 0.40);
        drawText(Form("%s",coll.Data()), xpos, 0.40+dy);
    }
    if(coll=="pbpb") gr_pur[0] = (TGraphAsymmErrors*) gr_pur[1]->Clone("gr_pur_cent0");

    /////////////////////////////////////////////////////////
    // FIT
    for (Int_t j = 0; j < nCENTBINS; j++) {
        if(coll=="pbpb" && j==0) continue;        
        if(coll=="pbpb") 
            cPurity->cd(j);
        else
            cPurity->cd();
        // rebin ptbins for each centrality bins since we have less bins for peripheral region
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];
        double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
            ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
        }
        if(function_number==0){
            f_temp[j] = new TF1(Form("purity_temp_%s_cent%d",coll.Data(),j), errFunc, ptBins_unfolding_centDep[0], ptBins_unfolding_centDep[nPtBin_unfolding_centDep],3); //nominal
            f[j] = new TF1(Form("purity_%s_cent%d",coll.Data(),j), errFunc, ptBins_unfolding_centDep[0], ptBins_unfolding_centDep[nPtBin_unfolding_centDep],3); //nominal
            f_temp[j]->SetParameters(7.18606e-01,-1.72893e+02,1.83041e+02);
            if(coll=="pbpb" && j!=1){
                f_temp[j]->SetParLimits(0,0.65,0.85);
                f_temp[j]->SetParLimits(1,-400,-50);
                f_temp[j]->SetParLimits(2,100,300);
                //f_temp[j]->SetParLimits(0,0.65,0.90);
                //f_temp[j]->SetParLimits(0,0.65,0.95);
            } else if(coll=="pbpb" && j==1){
                //f_temp[j]->SetParLimits(0,0.65,0.85);
                f_temp[j]->SetParLimits(1,-400,0);
                //f_temp[j]->SetParLimits(2,100,300);
            }
        } else if(function_number==1){
            f_temp[j] = new TF1(Form("purity_temp_%s_cent%d",coll.Data(),j), "pol2", ptBins_unfolding_centDep[0], ptBins_unfolding_centDep[nPtBin_unfolding_centDep]); 
            f[j] = new TF1(Form("purity_%s_cent%d",coll.Data(),j), "pol2", ptBins_unfolding_centDep[0], ptBins_unfolding_centDep[nPtBin_unfolding_centDep]); 
            
            f_temp[j]->SetParameters(7.61881e-01,1.50332e-03,-6.38109e-06);
            f_temp[j]->SetParLimits(3,-999,0);
            //f_temp[j]->SetParameters(6.20059e-01,2.93156e-03,0.1);
        } else if(function_number==2){
            f_temp[j] = new TF1(Form("purity_temp_%s_cent%d",coll.Data(),j), errFuncPol1, ptBins_unfolding_centDep[0], ptBins_unfolding_centDep[nPtBin_unfolding_centDep],5); 
            f[j] = new TF1(Form("purity_%s_cent%d",coll.Data(),j), errFuncPol1, ptBins_unfolding_centDep[0], ptBins_unfolding_centDep[nPtBin_unfolding_centDep],5); 
            //if(coll=="pbpb" && (j==1 || j==2) ){
            //    f_temp[j]->SetParameters(7.89747e+00,70,3.64089e+01,5.68576e-04,-7.09492e+00);
            //    //f_temp[j]->SetParameters(7.89747e+00,-4.16335e+01,3.64089e+01,5.68576e-04,-7.09492e+00);
            //    f_temp[j]->SetParLimits(1,50,120.0);//turn on point
            //    f_temp[j]->SetParLimits(2,0,100);
            //    f_temp[j]->SetParLimits(3,0,0.001);//slope of pol1

            //} else {
                f_temp[j]->SetParameters(7.89747e+00,-4.16335e+01,3.64089e+01,5.68576e-04,-7.09492e+00);
                f_temp[j]->SetParLimits(1,-99,0.0);//turn on point
                f_temp[j]->SetParLimits(2,0,100);
                f_temp[j]->SetParLimits(3,0,0.001);//slope of pol1
            //}
            //f_temp[j]->SetParameters(7.18606e-01,-1.72893e+02,1.83041e+02,0.1,0);
        }
        f_temp[j]->SetNpx(1000);
        f[j]->SetNpx(1000);
        if(drawGraph){
            gr_pur[j]->Fit(f_temp[j]); 
            gr_pur[j]->Fit(f_temp[j]); 
            gr_pur[j]->Fit(f_temp[j]); 
        } else{
            h1D_pur[j]->Fit(f_temp[j], "LL R"); 
            h1D_pur[j]->Fit(f_temp[j], "LL R"); 
            h1D_pur[j]->Fit(f_temp[j], "LL R"); 
        }
        f_temp[j]->Draw("same");

        f[j]->SetParameter(0,f_temp[j]->GetParameter(0));
        f[j]->SetParameter(1,f_temp[j]->GetParameter(1));
        if(function_number==0) f[j]->SetParameter(2,f_temp[j]->GetParameter(2));
        if(function_number==2 ){
            f[j]->SetParameter(2,f_temp[j]->GetParameter(2));
            f[j]->SetParameter(3,f_temp[j]->GetParameter(3));
            f[j]->SetParameter(4,f_temp[j]->GetParameter(4));
        }
        //f[j]->Draw("same");
    }
    if(coll=="pbpb") f[0] = (TF1*) f[1]->Clone("purity_pbpb_cent0");
    if(coll=="pbpb") f_temp[0] = (TF1*) f_temp[1]->Clone("purity_pbpb_cent0");

    if(coll=="pbpb") h1D_pur[0] = (TH1D*) h1D_pur[1]->Clone(Form("h1D_purity_cent%d",0));
    TString outputPdfName=Form("purity_vs_pt_%s_%s_iter%d",coll.Data(),ver.Data(),nIter);
    cPurity->SaveAs(Form("%sfigures/%s_%s.pdf",dir.Data(), outputPdfName.Data(),func_label.Data()));

    /////////////////////////////////////
    // Write Output File 
    outFile->cd();
    cPurity->Write();
    for (Int_t j = 0; j < nCENTBINS; ++j) {
        h1D_pur[j]->Write();
        if(drawGraph) gr_pur[j]->Write(); 
        f_temp[j]->Write();
        f[j]->Write();
    }
    outFile->Close();

}
