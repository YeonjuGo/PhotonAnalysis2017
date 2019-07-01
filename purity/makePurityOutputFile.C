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

void makePurityOutputFile(const TString coll="pp", const TString ver="190625_temp_v29_nominal", bool doSplitPD=true, bool doPreScale=1, bool usePurHist=true){
    cout << "Purity Calculation" << endl;
    cout << "::: version = " << ver << endl; 
    cout << "::: doSplitPD = " << doSplitPD << endl; 
    cout << "::: doPreScale = " << doPreScale << endl; 
    gStyle->SetOptStat(0);
    //TH1::SetDefaultSumw2();
    SetyjPadStyle();


    TString outfName=Form("purity_withFunc_%s_%s",coll.Data(),ver.Data());
    TString infName=Form("purity_%s_%s",coll.Data(),ver.Data());
    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1;

    const int function_number = 1;
    TString func_label = "";
    if(function_number==0) func_label="erf";
    if(function_number==1) func_label="pol0";

    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/purity/";
    TFile* outFile = new TFile(Form("%soutput/%s.root",dir.Data(), outfName.Data()), "RECREATE");
    TH1D* h1D_pur[nCENTBINS];
    if(usePurHist){
        TFile* inFile = new TFile(Form("%soutput/%s.root",dir.Data(), infName.Data()), "READ");
        if(coll=="pbpb"){
        for (Int_t j = 0; j < nCENTBINS; j++) 
            h1D_pur[j] = (TH1D*) inFile->Get(Form("h1D_purity_cent%d",j));
        } else {
            h1D_pur[0] = (TH1D*) inFile->Get(Form("h1D_purity_pp%s",""));
        }

    } else {

        for (Int_t j = 0; j < nCENTBINS; j++) {
            // rebin ptbins for each centrality bins since we have less bins for peripheral region
            int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];
            double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
            for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
                ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
            }
            if(coll=="pp") h1D_pur[j] = new TH1D("h1D_purity_pp",";p_{T}^{#gamma} (GeV);Purity",nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
            else h1D_pur[j] = new TH1D(Form("h1D_purity_cent%d",j),";p_{T}^{#gamma} (GeV);Purity",nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
        }

        TString dir_log = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/log/backup/";

        string search = ">>>>Purity:";
        string searchError = ">>>>PurityError:";
        ifstream txt_file ( Form("%syj_quickPhotonPurity_v3_%s_%s.log",dir_log.Data(),coll.Data(),ver.Data()) );
        string line;
        size_t pos;
        size_t pos2;
        vector<float> v_purityNum;
        vector<float> v_purityErr;

        while(txt_file.good())
        {
            getline(txt_file,line); // get line from file:w
            pos=line.find(search); // search
            pos2=line.find(searchError);
            if(pos!=string::npos) // string::npos is returned if string is not found
            {
                string temp_st = line.substr(pos+12);
                //cout << temp_st << endl;
                float temp_purityNum = ::atof(temp_st.c_str()); 
                v_purityNum.push_back(temp_purityNum);
                cout << " purity : " << temp_purityNum << endl; 
            }
            if(pos2!=string::npos) // string::npos is returned if string is not found
            {
                string temp_st = line.substr(pos+17);
                //cout << temp_st << endl;
                float temp_purityErr = ::atof(temp_st.c_str()); 
                v_purityErr.push_back(temp_purityErr);
                cout << " purity Error : " << temp_purityErr << endl; 
            }
        }

        int nValue = 0;
        for (Int_t j = 0; j < nCENTBINS; j++) {
            if(coll=="pbpb" && j==0) continue;        
            // rebin ptbins for each centrality bins since we have less bins for peripheral region
            int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];
            double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
            for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
                ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
            }

            for (Int_t i = 0; i < nPtBin_unfolding_centDep; ++i) {
                h1D_pur[j]->SetBinContent(i+1,v_purityNum.at(nValue));
                h1D_pur[j]->SetBinError(i+1,v_purityErr.at(nValue));
                nValue++; 
            }
        }

    }

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
        SetHistTextSize(h1D_pur[j]);
        h1D_pur[j]->GetYaxis()->SetRangeUser(0.0,1.0);
        h1D_pur[j]->SetMarkerStyle(20);
        h1D_pur[j]->SetMarkerColor(1);
        h1D_pur[j]->SetLineColor(1);
        h1D_pur[j]->Draw("p hist e");
        float xpos = 0.75;
        float dy = 0.05;
        if(coll=="pbpb") drawText(Form("%.0f - %.0f%c", centBins_i[j]/2., centBins_f[j]/2., '%'), xpos, 0.40);
        drawText(Form("%s",coll.Data()), xpos, 0.40+dy);
    }

    /////////////////////////////////////////////////////////
    // FIT
    TF1* f_temp[nCENTBINS];
    TF1* f[nCENTBINS];
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
            f_temp[j] = new TF1(Form("purity_temp_%s_cent%d",coll.Data(),j), "[0]*TMath::Erf((x-[1])/[2])", ptBins_unfolding_centDep[0], ptBins_unfolding_centDep[nPtBin_unfolding_centDep-1]); //nominal
            f[j] = new TF1(Form("purity_%s_cent%d",coll.Data(),j), "[0]*TMath::Erf((x-[1])/[2])", ptBins_unfolding_centDep[0], ptBins_unfolding_centDep[nPtBin_unfolding_centDep]); //nominal
            f_temp[j]->SetParameters(7.18606e-01,-1.72893e+02,1.83041e+02);
        } else if(function_number==1){
            f_temp[j] = new TF1(Form("purity_temp_%s_cent%d",coll.Data(),j), "pol1", ptBins_unfolding_centDep[0], ptBins_unfolding_centDep[nPtBin_unfolding_centDep-1]); //nominal
            f[j] = new TF1(Form("purity_%s_cent%d",coll.Data(),j), "pol1", ptBins_unfolding_centDep[0], ptBins_unfolding_centDep[nPtBin_unfolding_centDep]); //nominal
            f_temp[j]->SetParameters(6.20059e-01,2.93156e-03);
        }
        f_temp[j]->SetNpx(1000);
        h1D_pur[j]->Fit(f_temp[j], "LL R"); 
        h1D_pur[j]->Fit(f_temp[j], "LL R"); 
        //h1D_pur[j]->Fit(f_temp[j], "RME"); 
        
        f[j]->SetParameter(0,f_temp[j]->GetParameter(0));
        f[j]->SetParameter(1,f_temp[j]->GetParameter(1));
        if(function_number==0) f[j]->SetParameter(2,f_temp[j]->GetParameter(2));
        f[j]->Draw("same");
    }

    if(coll=="pbpb") h1D_pur[0] = (TH1D*) h1D_pur[1]->Clone(Form("h1D_purity_cent%d",0));
    TString outputPdfName=Form("purity_vs_pt_%s_%s",coll.Data(),ver.Data());
    cPurity->SaveAs(Form("%sfigures/%s_%s.pdf",dir.Data(), outputPdfName.Data(),func_label.Data()));

    /////////////////////////////////////
    // Write Output File 
    outFile->cd();
    cPurity->Write();
    for (Int_t j = 0; j < nCENTBINS; ++j) {
        h1D_pur[j]->Write();
        f[j]->Write();
    }
    //outFile->Close();
}
