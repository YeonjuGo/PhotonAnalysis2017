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

#include "../phoRaaCuts/phoRaaCuts_temp.h"
#include "../phoRaaCuts/yjUtility.h"
Double_t effFunctionTest(Double_t *x, Double_t *par)
{
    Double_t xx = x[0];
    Double_t fitVal;
    fitVal = par[0]*TMath::Erf((xx-par[1])/par[2]); 
    return fitVal;
}

void test(const TString coll="pp", const TString ver="190625_temp_v29_nominal", bool doSplitPD=true, bool doPreScale=1){
    cout << "Purity Calculation" << endl;
    cout << "::: version = " << ver << endl; 
    cout << "::: doSplitPD = " << doSplitPD << endl; 
    cout << "::: doPreScale = " << doPreScale << endl; 
    gStyle->SetOptStat(0);
    //TH1::SetDefaultSumw2();
    SetyjPadStyle();


    TString outfName=Form("purity_withFunc_%s_%s_splitPD",coll.Data(),ver.Data());
    TString infName=Form("purity_%s_%s_splitPD",coll.Data(),ver.Data());
    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1;
    bool drawGraph = true;

    const int function_number = 0;
    TString func_label = "";
    if(function_number==0) func_label="erf";
    if(function_number==1) func_label="pol0";

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
    double purityErr[] = {0.00537754,0.00784533,0.00929191,0.00406089,0.00641795,0.00779047,0.0145724,0.0221101,0.0338031};
    double pp_nominal[] = {0.873714,0.0325394};
    double pp_purUp[] = {0.884819,0.0314071};
    double pp_purDown[] = {0.864754,0.0326039};
    double pp_eleCont[] = {0.851015,0.0337046};
    double pp_phoEscale[] = {0.874046,0.0322272};
    double pp_phoEresol[] = {0.873715,0.0325392};

    double pbpb_nominal[5][2] =  {{0.703676,0.0880971},{0.703676,0.0880971},{0.799694,0.0705666},{0.836932,0.0651625},{0.870844,0.0737219}};
    double pbpb_purUp[5][2] =  {{0.827784,0.0647807},{0.827784,0.0647807},{0.879431,0.0573088},{0.857561,0.0631881},{0.902371,0.0709122}};
    double pbpb_purDown[5][2] =  {{0.702724,0.0838351},{0.702724,0.0838351},{0.789195,0.0715462},{0.809286,0.0679158},{0.798681,0.0859657}};
    double pbpb_eleCont[5][2] =  {{0.690731,0.0839711},{0.690731,0.0839711},{0.78339,0.0702098},{0.814806,0.0682313},{0.858094,0.0766839}};
    double pbpb_phoEscale[5][2] = {{0.701673,0.0849697},{0.701673,0.0849697},{0.804427,0.068678},{0.847309,0.0618378},{0.874598,0.070359}};
    double pbpb_phoEresol[5][2] =  {{0.705229,0.087715},{0.705229,0.087715},{0.799694,0.0705666},{0.836337,0.0653631},{0.866152,0.0752582}};


    TFile* inFile = new TFile(Form("%soutput/%s.root",dir.Data(), infName.Data()), "READ");
    if(coll=="pbpb"){
        for (Int_t j = 0; j < nCENTBINS; j++) 
            h1D_pur[j] = (TH1D*) inFile->Get(Form("h1D_purity_cent%d",j));
    } else {
        h1D_pur[0] = (TH1D*) inFile->Get(Form("h1D_purity_pp%s",""));
    }

    for (Int_t j = 0; j < nCENTBINS; j++) {
        //if(coll=="pbpb" && j==0) continue;        
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];
        double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu)
            ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];

        htemp[j] = new TH1D(Form("htemp%d",j),";p_{T}^{#gamma} (GeV);Purity",nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
        gr_pur[j] = new TGraphAsymmErrors(nPtBin_unfolding_centDep);
        gr_pur[j]->SetName(Form("gr_pur_cent%d",j));

        for(int ipt=0; ipt<nPtBin_unfolding_centDep-1;++ipt){
            if(ipt<nPtBin_unfolding_centDep-2){
                tempVal[j][ipt] = h1D_pur[j]->GetBinContent(ipt+1);
                //tempErr[j][ipt] = 0.0;
                //tempErr[j][ipt] = 0.05*tempVal[j][ipt]; 
                //if(ver=="190625_temp_v29_nominal") tempErr[j][ipt] = purityErr[ipt]; 
                //else tempErr[j][ipt] = h1D_pur[j]->GetBinError(ipt+1);
                tempErr[j][ipt] = h1D_pur[j]->GetBinError(ipt+1);
                gr_pur[j]->SetPoint(ipt, purityPtBins[ipt], tempVal[j][ipt]);
                gr_pur[j]->SetPointError(ipt, purityPtBinsErr[ipt], purityPtBinsErr[ipt], tempErr[j][ipt], tempErr[j][ipt]);

            } else {
                if(coll=="pp"){
                    if(ver=="190625_temp_v29_nominal"){
                        gr_pur[j]->SetPoint(ipt, purityPtBins[ipt], pp_nominal[0]);
                        gr_pur[j]->SetPointError(ipt, purityPtBinsErr[ipt], purityPtBinsErr[ipt], pp_nominal[1], pp_nominal[1]);
                    } else if(ver=="190625_temp_v29_sys_purUp"){
                        gr_pur[j]->SetPoint(ipt, purityPtBins[ipt], pp_purUp[0]);
                        gr_pur[j]->SetPointError(ipt, purityPtBinsErr[ipt], purityPtBinsErr[ipt], pp_purUp[1], pp_purUp[1]);
                    } else if(ver=="190625_temp_v29_sys_purDown"){
                        gr_pur[j]->SetPoint(ipt, purityPtBins[ipt], pp_purDown[0]);
                        gr_pur[j]->SetPointError(ipt, purityPtBinsErr[ipt], purityPtBinsErr[ipt], pp_purDown[1], pp_purDown[1]);
                    } else if(ver=="190625_temp_v29_sys_phoEscale"){
                        gr_pur[j]->SetPoint(ipt, purityPtBins[ipt], pp_phoEscale[0]);
                        gr_pur[j]->SetPointError(ipt, purityPtBinsErr[ipt], purityPtBinsErr[ipt], pp_phoEscale[1], pp_phoEscale[1]);
                    } else if(ver=="190625_temp_v29_sys_phoEresol"){
                        gr_pur[j]->SetPoint(ipt, purityPtBins[ipt], pp_phoEresol[0]);
                        gr_pur[j]->SetPointError(ipt, purityPtBinsErr[ipt], purityPtBinsErr[ipt], pp_phoEresol[1], pp_phoEresol[1]);
                    } else if(ver=="190625_temp_v29_sys_eleCont"){
                        gr_pur[j]->SetPoint(ipt, purityPtBins[ipt], pp_eleCont[0]);
                        gr_pur[j]->SetPointError(ipt, purityPtBinsErr[ipt], purityPtBinsErr[ipt], pp_eleCont[1], pp_eleCont[1]);
                    }
                } else{
                    if(ver=="190625_temp_v29_nominal"){
                        gr_pur[j]->SetPoint(ipt, purityPtBins[ipt], pbpb_nominal[j][0]);
                        gr_pur[j]->SetPointError(ipt, purityPtBinsErr[ipt], purityPtBinsErr[ipt], pbpb_nominal[j][1], pbpb_nominal[j][1]);
                    } else if(ver=="190625_temp_v29_sys_purUp"){
                        gr_pur[j]->SetPoint(ipt, purityPtBins[ipt], pbpb_purUp[j][0]);
                        gr_pur[j]->SetPointError(ipt, purityPtBinsErr[ipt], purityPtBinsErr[ipt], pbpb_purUp[j][1], pbpb_purUp[j][1]);
                    } else if(ver=="190625_temp_v29_sys_purDown"){
                        gr_pur[j]->SetPoint(ipt, purityPtBins[ipt], pbpb_purDown[j][0]);
                        gr_pur[j]->SetPointError(ipt, purityPtBinsErr[ipt], purityPtBinsErr[ipt], pbpb_purDown[j][1], pbpb_purDown[j][1]);
                    } else if(ver=="190625_temp_v29_sys_phoEscale"){
                        gr_pur[j]->SetPoint(ipt, purityPtBins[ipt], pbpb_phoEscale[j][0]);
                        gr_pur[j]->SetPointError(ipt, purityPtBinsErr[ipt], purityPtBinsErr[ipt], pbpb_phoEscale[j][1], pbpb_phoEscale[j][1]);
                    } else if(ver=="190625_temp_v29_sys_phoEresol"){
                        gr_pur[j]->SetPoint(ipt, purityPtBins[ipt], pbpb_phoEresol[j][0]);
                        gr_pur[j]->SetPointError(ipt, purityPtBinsErr[ipt], purityPtBinsErr[ipt], pbpb_phoEresol[j][1], pbpb_phoEresol[j][1]);
                    } else if(ver=="190625_temp_v29_sys_eleCont"){
                        gr_pur[j]->SetPoint(ipt, purityPtBins[ipt], pbpb_eleCont[j][0]);
                        gr_pur[j]->SetPointError(ipt, purityPtBinsErr[ipt], purityPtBinsErr[ipt], pbpb_eleCont[j][1], pbpb_eleCont[j][1]);
                    }

                }//pp? or pbpb?
            }//if it is the last bin
            double tempx, tempy;
            gr_pur[j]->GetPoint(ipt,tempx,tempy);
            cout << tempx << ", " << tempy << ", " << tempErr[j][ipt] << endl;
        }//pt loop
    }//cent loop

    // //test
    // for (Int_t j = 0; j < nCENTBINS; j++) {
    //     for(int ipt=0; ipt<nPtBin_unfolding-1;++ipt){
    //         double tempx, tempy;
    //         gr_pur[j]->GetPoint(ipt,tempx,tempy);
    //         cout << tempx << ", " << tempy << endl;
    //         cout << tempVal[j][ipt] << ",," << tempErr[j][ipt] << endl;
    //     }
    // }


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
            f_temp[j] = new TF1(Form("purity_temp_%s_cent%d",coll.Data(),j), effFunctionTest, ptBins_unfolding_centDep[0], ptBins_unfolding_centDep[nPtBin_unfolding_centDep],3); //nominal
            //f_temp[j] = new TF1(Form("purity_temp_%s_cent%d",coll.Data(),j), "[0]*TMath::Erf((x-[1])/[2])", ptBins_unfolding_centDep[0], ptBins_unfolding_centDep[nPtBin_unfolding_centDep]); //nominal
            //f_temp[j] = new TF1(Form("purity_temp_%s_cent%d",coll.Data(),j), "[0]*TMath::Erf((x-[1])/[2])", ptBins_unfolding_centDep[0], ptBins_unfolding_centDep[nPtBin_unfolding_centDep-1]); //nominal
            f[j] = new TF1(Form("purity_%s_cent%d",coll.Data(),j), "[0]*TMath::Erf((x-[1])/[2])", ptBins_unfolding_centDep[0], ptBins_unfolding_centDep[nPtBin_unfolding_centDep]); //nominal
            f_temp[j]->SetParameters(7.18606e-01,-1.72893e+02,1.83041e+02);
        } else if(function_number==1){
            f_temp[j] = new TF1(Form("purity_temp_%s_cent%d",coll.Data(),j), "pol1", ptBins_unfolding_centDep[0], ptBins_unfolding_centDep[nPtBin_unfolding_centDep-1]); //nominal
            f[j] = new TF1(Form("purity_%s_cent%d",coll.Data(),j), "pol1", ptBins_unfolding_centDep[0], ptBins_unfolding_centDep[nPtBin_unfolding_centDep]); //nominal
            f_temp[j]->SetParameters(6.20059e-01,2.93156e-03);
        }
         f_temp[j]->SetNpx(1000);
         if(drawGraph){
             gr_pur[j]->Fit(f_temp[j]); 
             gr_pur[j]->Fit(f_temp[j]); 
         } else{
             h1D_pur[j]->Fit(f_temp[j], "LL R"); 
             h1D_pur[j]->Fit(f_temp[j], "LL R"); 
         }
         f_temp[j]->Draw("same");

        f[j]->SetParameter(0,8.47006e-01);
        f[j]->SetParameter(1,-1.83658e+01);
        if(function_number==0) f[j]->SetParameter(2,4.08015e+01);
        f[j]->Draw("same");
    }
    if(coll=="pbpb") f[0] = (TF1*) f[1]->Clone("purity_pbpb_cent0");


    if(coll=="pbpb") h1D_pur[0] = (TH1D*) h1D_pur[1]->Clone(Form("h1D_purity_cent%d",0));
    TString outputPdfName=Form("purity_vs_pt_%s_%s",coll.Data(),ver.Data());
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
