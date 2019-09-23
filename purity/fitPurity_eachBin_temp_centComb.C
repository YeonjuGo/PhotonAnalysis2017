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

void fitPurity_eachBin_temp_centComb(const TString coll="pp", const TString ver="190703_temp_v31_pur_SBcorr_centDep", const int function_number = 0, int Niter = 0, bool doSplitPD=true, bool doPreScale=false, bool drawGraph = true){
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

    TString outfName=Form("purity_withFunc_%s_%s%s",coll.Data(),ver.Data(),cap.Data());
    TString infName=Form("purity_%s_%s%s",coll.Data(),ver.Data(),cap.Data());
    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1;

    //const int function_number = 1;
    TString func_label = "";
    if(function_number==0) func_label="erf";
    if(function_number==1) func_label="pol2";
    if(function_number==2) func_label="erfPlusPol1";

    int maxIter = 5;
    double ptBins_[]={20,30,40,50,60,80,130};
    //double ptBins_[]={20,40,60,130};
    //double ptBins_[]={20,30,40,50,60,80,130};
    //double ptBins_[]={20,25,30,40,50,60,80,130};
    //double ptBins_[]={20,30,40,50,60,80,130};
    //double ptBins_[]={20,25,30,40,50,60,80,100,300};
    const int nPtBins_ = sizeof(ptBins_)/sizeof(double)-1; 
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/purity/";
    TFile* outFile = new TFile(Form("%soutput/%s.root",dir.Data(), outfName.Data()), "RECREATE");

    TH1D* h1D_pur[nCENTBINS];
    TH1D* h1D_pur_iter[nCENTBINS][nPtBins_];
    double tempVal[5][20] ={{0}};
    double tempErr[5][20] ={{0}};
    TH1D* htemp[nCENTBINS];
    TGraphAsymmErrors* gr_pur[nCENTBINS];
    TF1* f_temp[nCENTBINS];
    TF1* f[nCENTBINS];


    double purityPtBins[] ={24.8,34,44.2,54.3,68.0,95.6}; 
    //double purityPtBins[] = {25,35,45,55,70,100};
    //double purityPtBins[] = {30,50,100};
    //double purityPtBins[] = {24.8,34,44.2,54.3,68.0,95.6};
    //double purityPtBins[] = {22,24.8,33.7975,44.1448,54.3516,68.0108,95.6408};
    //double purityPtBins[] = {22.035,27.1233,33.7975,44.1448,54.3516,68.0108,88.7239,111.387,166.239};
    double purityPtBinsErr[] = {0.00527241,0.00902116,0.0222023,0.0436468,0.0745094,0.180516,0.352182,0.771632,4.80612};
    double purityErr[] = {0.00537754,0.00784533,0.00929191,0.00406089,0.00641795,0.00779047,0.0145724,0.0221101,0.0338031};
    //pbpb: 20 <= pt < 30; mean = 24.8528, mean error = 0.0135248
    //pbpb: 30 <= pt < 40; mean = 34.0872, mean error = 0.0149424
    //pbpb: 40 <= pt < 50; mean = 44.1777, mean error = 0.0260087
    //pbpb: 50 <= pt < 60; mean = 54.243, mean error = 0.0417296
    //pbpb: 60 <= pt < 80; mean = 67.977, mean error = 0.0984396
    //pbpb: 80 <= pt < 130; mean = 95.6408, mean error = 0.346034
    //pbpb: 80 <= pt < 200; mean = 103.058, mean error = 0.585896

        cout << "coll = " << coll << endl;
    for (Int_t j = 0; j < nCENTBINS; j++) {
        if(coll=="pbpb" && j==0) continue;
        cout << "cent " << j << endl;
        //int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];
        //double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        //for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu)
        //    ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
        if(coll=="pbpb") h1D_pur[j] = new TH1D(Form("h1D_purity_cent%d",j),";p_{T}^{#gamma} (GeV); Purity", nPtBins_, ptBins_);
        else h1D_pur[j] = new TH1D(Form("h1D_purity_pp%s",""),";p_{T}^{#gamma} (GeV); Purity", nPtBins_, ptBins_);
        htemp[j] = new TH1D(Form("htemp%d",j),";p_{T}^{#gamma} (GeV);Purity",nPtBins_,ptBins_);
        gr_pur[j] = new TGraphAsymmErrors(nPtBins_);
        gr_pur[j]->SetName(Form("gr_pur_cent%d",j));
        // gr_pur[j]->SetName(Form("gr_pur_cent%d",j));

        for (Int_t i = 0; i < nPtBins_; i++) {
            cout << "sgsdf" << endl;
            TString cap_bin = "";
            if(coll=="pp"){ cap_bin += Form("pt%dto%d_maxIter%d",(int)ptBins_[i],(int)ptBins_[i+1],(int)maxIter); }
            else{ 
                //else cap_bin += Form("cent%dto%d_pt%dto%d_maxIter%d",(int)centBins_i[j]/2,(int)centBins_f[j]/2,(int)ptBins_[i],(int)ptBins_[i+1],(int)maxIter);
                //cap_bin += Form("cent%dto%d_pt%dto%d_maxIter%d",(int)centBins_i[j]/2,(int)centBins_f[j]/2,(int)ptBins_[i],(int)ptBins_[i+1],(int)maxIter);
                if(centBins_i[j]/2==0 || centBins_i[j]/2==10) 
                    cap_bin += Form("cent%dto%d_pt%dto%d_maxIter%d",0,30,(int)ptBins_[i],(int)ptBins_[i+1],(int)maxIter);
                else 
                    cap_bin += Form("cent%dto%d_pt%dto%d_maxIter%d",(int)centBins_i[j]/2,(int)centBins_f[j]/2,(int)ptBins_[i],(int)ptBins_[i+1],(int)maxIter);
                    //cap_bin += Form("cent%dto%d_pt%dto%d_maxIter%d",30,100,(int)ptBins_[i],(int)ptBins_[i+1],(int)maxIter);
            }

            TFile* inFile = new TFile(Form("%soutput/%s_%s.root",dir.Data(), infName.Data(),cap_bin.Data()), "READ");
            h1D_pur_iter[j][i] = (TH1D*) inFile->Get(Form("h1D_purity_iter%s",""));
            
        
            double val = h1D_pur_iter[j][i]->GetBinContent(Niter+1);
            double err = h1D_pur_iter[j][i]->GetBinError(Niter+1);
            double val0 = h1D_pur_iter[j][i]->GetBinContent(1);
            double errIter = abs(val-val0);
            if(err<errIter) err=errIter;
            h1D_pur[j]->SetBinContent(i+1,val);
            h1D_pur[j]->SetBinError(i+1,err);

            tempVal[j][i] = h1D_pur[j]->GetBinContent(i+1);
            tempErr[j][i] = h1D_pur[j]->GetBinError(i+1);
            gr_pur[j]->SetPoint(i, purityPtBins[i], tempVal[j][i]);
            gr_pur[j]->SetPointError(i, purityPtBinsErr[i], purityPtBinsErr[i], tempErr[j][i], tempErr[j][i]);
            double tempx, tempy;
            gr_pur[j]->GetPoint(i,tempx,tempy);
            cout << tempx << ", " << tempy << ", " << tempErr[j][i] << endl;
        }//pt loop
    }//cent loop

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
        //int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];

        if(coll=="pbpb") 
            cPurity->cd(j);
        else
            cPurity->cd();
        SetHistTextSize(htemp[j]);
        htemp[j]->GetYaxis()->SetRangeUser(0.0,1.0);
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
        //int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];
        //double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        //for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
        //    ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
        //}
        double xmax = 300;
        //double xmax = ptBins_[nPtBins_];
        if(function_number==0){
            if(j==4){
                f_temp[j] = new TF1(Form("purity_temp_%s_cent%d",coll.Data(),j), errFuncPol1, ptBins_[0], xmax,5); 
                f[j] = new TF1(Form("purity_%s_cent%d",coll.Data(),j), errFuncPol1, ptBins_[0], xmax,5); 
                f_temp[j]->SetParameters(7.89747e+00,-4.16335e+01,3.64089e+01,5.68576e-04,-7.09492e+00);
                f_temp[j]->SetParLimits(1,-99,0.0);//turn on point
                f_temp[j]->SetParLimits(2,0,100);
                f_temp[j]->SetParLimits(3,0,0.001);//slope of pol1
            } else{
                f_temp[j] = new TF1(Form("purity_temp_%s_cent%d",coll.Data(),j), errFunc, ptBins_[0],xmax ,3); //nominal
                f[j] = new TF1(Form("purity_%s_cent%d",coll.Data(),j), errFunc, ptBins_[0], xmax,3); //nominal
                f_temp[j]->SetParameters(7.18606e-01,-1.72893e+02,1.83041e+02);
                if(coll=="pbpb" && j!=1){
                    f_temp[j]->SetParLimits(0,0.65,0.85);
                    f_temp[j]->SetParLimits(1,-400,-50);
                    f_temp[j]->SetParLimits(2,100,300);
                    //f_temp[j]->SetParLimits(0,0.65,0.90);
                    //f_temp[j]->SetParLimits(0,0.65,0.95);
                } else if(coll=="pbpb" && j==1){
                    //f_temp[j]->SetParLimits(0,0.65,0.85);
                    //f_temp[j]->SetParLimits(1,-400,0);
                    //f_temp[j]->SetParLimits(2,100,300);
                    f_temp[j]->SetParameters(1.15223e+03 ,-8.10737e+01,3.12465e+05);
                }
            }
        } else if(function_number==1){
            f_temp[j] = new TF1(Form("purity_temp_%s_cent%d",coll.Data(),j), "pol2", ptBins_[0], xmax); 
            f[j] = new TF1(Form("purity_%s_cent%d",coll.Data(),j), "pol2", ptBins_[0], xmax); 
            
            f_temp[j]->SetParameters(7.61881e-01,1.50332e-03,-6.38109e-06);
            f_temp[j]->SetParLimits(3,-999,0);
            //f_temp[j]->SetParameters(6.20059e-01,2.93156e-03,0.1);
        } else if(function_number==2){
            f_temp[j] = new TF1(Form("purity_temp_%s_cent%d",coll.Data(),j), errFuncPol1, ptBins_[0], xmax,5); 
            f[j] = new TF1(Form("purity_%s_cent%d",coll.Data(),j), errFuncPol1, ptBins_[0], xmax,5); 
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
    if(coll=="pbpb") f_temp[0] = (TF1*) f_temp[1]->Clone("purity_temp_pbpb_cent0");

    if(coll=="pbpb") h1D_pur[0] = (TH1D*) h1D_pur[1]->Clone(Form("h1D_purity_cent%d",0));
    TString outputPdfName=Form("purity_vs_pt_%s_%s",coll.Data(),ver.Data());
    cPurity->SaveAs(Form("%sfigures/%s_%s_iter%d.pdf",dir.Data(), outputPdfName.Data(),func_label.Data(),Niter));

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
