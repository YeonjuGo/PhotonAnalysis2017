// drawRaaXsec_v7_beforeUnfolding.C 
// This version gets photon raw distributions from the output/rawDist.root, while version 1 calculate these in that code. 
// Author: Yeonju Go 
// Written at 2017 Mar 17
// Modified : 2019 June 26
//
// It's modified to be used from phoRaaCuts_v23.h 
// from v10, efficiency macro has been changed to divide efficiency into reco & iso seperately.  
//
// It's modified to be used from phoRaaCuts_v29.h 
// 2019June25) different unfolding binning depending on centrality bin
// 2019June25) apply trigger efficiency which is derived using DATA to here but not draw in canvas
// 2019June25) unfolding binning (20 GeV to 300 GeV) 
// 2019Sep11) v8 : when applying purity, bin by bin correction for pt < 100 GeV, fit correction for pt > 100 GeV

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
const int markerHere[]={20,33,34,29,24,29};
const int markerHere_closed[]={20,33,33,33,33};
void drawRaaXsec_v8_beforeUnfolding_withTnP(TString ver="180731_temp_v19_nominal", bool doSplitPD = true, bool usePurityFit = true)
{
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0000);
    //SetyjPadStyle();
    //SetHistTitleStyle(0.05);
    // http://dde.web.cern.ch/dde/glauber_lhc.htm

    // nCentBin+1 : 0th array is for inclusive[0-100%]
    TString cap = "";
    if(doSplitPD) cap += "_splitPD"; 
    TFile* f_eff_iso = new TFile(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/output/pbpb_iso_efficiency_%s.root",ver.Data()));
    TFile* f_eff_isopp = new TFile(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/output/pp_iso_efficiency_%s.root",ver.Data()));
    TFile* f_pur = new TFile(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/purity/output/purity_withFunc_pbpb_%s%s_noPreScale.root",ver.Data(),cap.Data()));
    TFile* f_purpp = new TFile(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/purity/output/purity_withFunc_pp_%s%s_noPreScale.root",ver.Data(),cap.Data()));
    TFile* f_raw = new TFile(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/rawDist_%s%s.root",ver.Data(),cap.Data()));

    TFile* f_eff_reco;
    TFile* f_eff_recopp; 
    f_eff_reco = new TFile(Form("%s",pbpb_recoEfficiency.Data()));
    f_eff_recopp = new TFile(Form("%s",pp_recoEfficiency.Data()));

    TH1D* h1D_eff_reco[nCentBinIF];
    TH1D* h1D_eff_reco_temp[nCentBinIF];
    TH1D* h1D_eff_recopp;
    TH1D* h1D_eff_iso[nCentBinIF];
    TH1D* h1D_eff_isopp;
    TH1D* h1D_eff[nCentBinIF];
    TH1D* h1D_effpp;
    TH1D* h1D_pur[nCentBinIF];
    TH1D* h1D_purpp;
    TF1* fit_pur[nCentBinIF];
    TF1* fit_purpp;
    TH1D* h1D_raw_tp[nCentBinIF];
    TH1D* h1D_rawpp_tp;
    TH1D* h1D_raw[nCentBinIF];
    TH1D* h1D_rawpp;
    Int_t nCor = 3;
    TH1D* h1D_corr[nCor][nCentBinIF]; // corrected yield 1. purity, 2. efficiency 
    TH1D* h1D_corrpp[nCor]; // corrected yield 1. purity, 2. efficiency 
    TH1D* h1D_corrpp_temp[nCentBinIF]; 
    TH1D* h1D_Raa[nCentBinIF]; // total Raa!!
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////// 
    /// Get efficiency & purity hist. 
    cout << "get efficiency and purity histograms from the input files..." <<endl;
    TCanvas* ctemp[nCentBinIF];
    for(int j=0;j<nCentBinIF;++j)
    {
        // rebin ptbins for each centrality bins since we have less bins for peripheral region
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];
        double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
            ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
        }

        cout << "cent "<< j << endl; 
        //h1D_raw[j] = (TH1D*) h1D_raw_tp[j]->Clone(Form("h1D_raw_cent%d",j)); 
        h1D_raw[j] = (TH1D*) f_raw->Get(Form("h1D_raw_cent%d",j));
        
        cout << " : raw dist done" <<endl;
        h1D_eff_reco[j] = (TH1D*) f_eff_reco->Get(Form("reco_eff_cent%d",j));
        h1D_eff_reco_temp[j] = new TH1D(Form("reco_eff_temp_cent%d",j),Form(";p_{T}^{#gamma} (GeV);Reconstruction Efficiency"),nPtBin_unfolding_centDep,ptBins_unfolding_centDep); 
        for(int i=0;i<nPtBin_unfolding_centDep;i++){
            h1D_eff_reco_temp[j]->SetBinContent(i+1,h1D_eff_reco[j]->GetBinContent(i+1));
            h1D_eff_reco_temp[j]->SetBinError(i+1,h1D_eff_reco[j]->GetBinError(i+1));
        }
        cout << " : reco eff done" <<endl;
        h1D_eff_iso[j] = (TH1D*) f_eff_iso->Get(Form("sig_eff_cent%d_tot",j));
        cout << " : iso eff done" <<endl;
        h1D_eff[j] = (TH1D*) h1D_eff_reco_temp[j]->Clone(Form("h1D_eff_cent%d",j));
        h1D_eff[j]->Multiply(h1D_eff_iso[j]);
       //  ctemp[j]->cd(4);
       // h1D_eff[j]->Draw();
        h1D_pur[j] = (TH1D*) f_pur->Get(Form("h1D_purity_cent%d",j));
        fit_pur[j] = (TF1*) f_pur->Get(Form("purity_pbpb_cent%d",j));

       //  ctemp[j]->cd(5);
       // h1D_pur[j]->Draw();
        cout << " : purity done" <<endl;
       
        h1D_Raa[j] = new TH1D(Form("h1D_Raa_cent%d",j),Form(";p_{T}^{#gamma} (GeV);R_{AA}"),nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
        h1D_corrpp_temp[j] = new TH1D(Form("h1D_corrpp_temp_cent%d",j),Form(";p_{T}^{#gamma} (GeV);R_{AA}"),nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
       
        // 
    }
    if(centDepTnP){
        cout << "Applying TnP for PbPb in terms of centrality" << endl;
        int nTnPbin = 0;
        int tempCentSec = pbpb_tnp_cent_sec[0];
        double tempTnP = pbpb_tnp_cent[0];
        for(int j=0;j<nCentBinIF;++j){
            if(centBins_i[j]>=tempCentSec){
                nTnPbin+=1;
                tempCentSec = pbpb_tnp_cent_sec[nTnPbin];
                tempTnP = pbpb_tnp_cent[nTnPbin];
            }
            h1D_eff[j]->Scale(tempTnP);
            cout << "cent " << centBins_i[j] << " - " << centBins_f[j] << " : " << tempTnP << endl;
        }
    }
    if(ptDepTnP){
        cout << "Applying TnP for PbPb in terms of pT" << endl;
        for(int j=0;j<nCentBinIF;++j){
            int nTnPbin = 0;
            int tempPtSec = pbpb_tnp_pt_sec[0];
            double tempTnP = pbpb_tnp_pt[0];
            int nbinsx = h1D_eff[j]->GetNbinsX();
            for(int i=0; i<nbinsx;++i){
                double bincenter = h1D_eff[j]->GetBinCenter(i+1);
                double bincontent = h1D_eff[j]->GetBinContent(i+1);
                if(bincenter>=tempPtSec){
                    nTnPbin += 1;
                    tempPtSec = pbpb_tnp_pt_sec[nTnPbin];
                    tempTnP = pbpb_tnp_pt[nTnPbin];
                }
                h1D_eff[j]->SetBinContent(i+1,bincontent*tempTnP);
                cout << "pbpb ptBin " << ptBins_unfolding[i] << " - " << ptBins_unfolding[i+1] << " : " << tempTnP << endl;
            }
        }
    }

    h1D_rawpp = (TH1D*) f_raw->Get("h1D_raw_pp");
    if(h1D_rawpp->IsZombie()) cout << "[ERROR] pp : raw dist wasn't imported" <<endl;
    else cout << "pp : raw dist done" <<endl;
    
    h1D_eff_recopp = (TH1D*) f_eff_recopp->Get("reco_eff_cent0");
    if(h1D_eff_recopp->IsZombie()) cout << "[ERROR] pp : reco eff wasn't imported" <<endl;
    else cout << "pp : reco eff done" <<endl;

    h1D_eff_isopp = (TH1D*) f_eff_isopp->Get("sig_eff_cent0_tot");
    if(h1D_eff_isopp->IsZombie()) cout << "[ERROR] pp : iso eff wasn't imported" <<endl;
    else cout << "pp : iso eff done" <<endl;

    h1D_effpp = (TH1D*) h1D_eff_recopp->Clone("h1D_eff_cent0_tot_pp");
    h1D_effpp->Multiply(h1D_eff_isopp);
    cout << "pp : tot eff done" <<endl;

    fit_purpp = (TF1*) f_purpp->Get("purity_temp_pp_cent0");
    h1D_purpp = (TH1D*) f_purpp->Get("h1D_purity_pp");
    //if(h1D_purpp->IsZombie()) cout << "[ERROR] pp : pur wasn't imported" <<endl;
    cout << "pp : purity done" <<endl;

    cout << fit_purpp->Eval(24) << endl;
    cout << fit_pur[2]->Eval(24) << endl;
    cout << "all histgorams were imported successfully" <<endl;

    if(ptDepTnP_pp){
        cout << "Applying TnP for pp in terms of pT" << endl;
        int nTnPbin = 0;
        int tempPtSec = pp_tnp_pt_sec[0];
        double tempTnP = pp_tnp_pt[0];
        int nbinsx = h1D_effpp->GetNbinsX();
        for(int i=0; i<nbinsx;++i){
            double bincenter = h1D_effpp->GetBinCenter(i+1);
            double bincontent = h1D_effpp->GetBinContent(i+1);
            if(bincenter>=tempPtSec){
                nTnPbin += 1;
                tempPtSec = pp_tnp_pt_sec[nTnPbin];
                tempTnP = pp_tnp_pt[nTnPbin];
            }
            h1D_effpp->SetBinContent(i+1,bincontent*tempTnP);
            cout << "pp ptBin " << ptBins_unfolding[i] << " - " << ptBins_unfolding[i+1] << " : " << tempTnP << endl;
        }
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Purity TEST

    // 0-100% 30-100% 0-10% 10-30% 30-50% 50-100%
    Double_t purity_fromBiRan[nPtBin][nCentBin+1] = 
    { {0.692733,      0.654991, 0.700615,0.730031},
    {0.707091,   0.672784, 0.722749,0.748273},
    {0.719437,   0.676977, 0.721539,0.785353},
     {0.722065,  0.67868, 0.725783, 0.787935},
    {0.758906, 0.700252, 0.792531,  0.799366}};

    ////////////////////////////////////////////////////////////////////////////////////////////////////////// 
    /// Get corrected distributions
    for(int j=0;j<nCentBinIF;j++)
    {
        // rebin ptbins for each centrality bins since we have less bins for peripheral region
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];
        double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
            ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
        }


        //h1D_raw[j]->Scale(1.,"width");//for dN/dpT
        for(int ii=0;ii<nCor;ii++){ // corrected yield 0th:raw 1st:purity 2nd:purity and efficiency
            h1D_corr[ii][j] = new TH1D(Form("h1D_dNdpt_corr%d_cent%d",ii,j),";p_{T}^{#gamma} (GeV); dN/dp_{T} (GeV^{-1})",nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
            if(j==0){ 
                h1D_corrpp[ii] = new TH1D(Form("h1D_dNdpt_corr%d_pp",ii),";p_{T}^{#gamma} (GeV); dN/dp_{T} (GeV^{-1})",nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
            }
        }
        for(int ipt=0;ipt<nPtBin_unfolding_centDep;++ipt){
            Double_t vEff, vPur, vRaw, vRawErr;
            if(j==0) vEff = h1D_eff[j]->GetBinContent(ipt+1)-0.1;
            else vEff = h1D_eff[j]->GetBinContent(ipt+1);
            //if(ipt<6){ // pt < 100 GeV
            if(ipt<20){ // pt < 100 GeV
                vPur = h1D_pur[j]->GetBinContent(ipt+1);
            } else {// pt > 100 GeV
                if(usePurityFit) vPur = fit_pur[j]->Eval(ptBins_mean_unfolding_pbpb[ipt]);
                else vPur = h1D_pur[j]->GetBinContent(ipt+1);
            }
            vRaw = h1D_raw[j]->GetBinContent(ipt+1);
            vRawErr = h1D_raw[j]->GetBinError(ipt+1);

            cout << centBins_i[j]/2<<"%-"<<centBins_f[j]/2<<"% : " << ptBins_unfolding_centDep[ipt] << "<pt<"<< ptBins_unfolding_centDep[ipt+1]<<" :: \traw=\t" << vRaw << "\teff\t" << vEff << "\tpur\t" << vPur << endl; 
            h1D_corr[0][j]->SetBinContent(ipt+1, vRaw); 
            h1D_corr[1][j]->SetBinContent(ipt+1, vRaw*vPur); 
            h1D_corr[2][j]->SetBinContent(ipt+1, vRaw*vPur/vEff); 
            h1D_corr[0][j]->SetBinError(ipt+1, vRawErr); 
            h1D_corr[1][j]->SetBinError(ipt+1, vRawErr*vPur); 
            h1D_corr[2][j]->SetBinError(ipt+1, vRawErr*vPur/vEff); 
        }
        if(j==0) {
            //h1D_rawpp->Scale(1.,"width");
            for(int ipt=0;ipt<nPtBin_unfolding_centDep;++ipt){
                Double_t vEff, vPur, vRaw, vRawErr;
                vEff = h1D_effpp->GetBinContent(ipt+1);
                //if(ipt<6){ // pt < 100 GeV
                if(ipt<20){ // pt < 100 GeV
                    vPur = h1D_purpp->GetBinContent(ipt+1);
                } else { // pt > 100 GeV
                    if(usePurityFit) vPur = fit_purpp->Eval(ptBins_mean_unfolding_pp[ipt]);
                    else vPur = h1D_purpp->GetBinContent(ipt+1);
                }
                vRaw = h1D_rawpp->GetBinContent(ipt+1);
                vRawErr = h1D_rawpp->GetBinError(ipt+1);
                
                cout <<"PP : " << ptBins_unfolding_centDep[ipt] << "<pt<"<< ptBins_unfolding_centDep[ipt+1] <<" :: \traw=\t" << vRaw << "\teff\t" << vEff << "\tpur\t" << vPur << endl; 
                h1D_corrpp[0]->SetBinContent(ipt+1, vRaw); 
                h1D_corrpp[1]->SetBinContent(ipt+1, vRaw*vPur); 
                h1D_corrpp[2]->SetBinContent(ipt+1, vRaw*vPur/vEff); 
                h1D_corrpp[0]->SetBinError(ipt+1, vRawErr); 
                h1D_corrpp[1]->SetBinError(ipt+1, vRawErr*vPur); 
                h1D_corrpp[2]->SetBinError(ipt+1, vRawErr*vPur/vEff); 
            }
        }
    }
    

    /////////////////////////////////////////////////////////////////////////// 
    /// Set Global Values 
    cout << "Define Global Values..." <<endl;

    double lumi_pp = 27.4*1e12; //25.775 pb-1 systematic 2.3%
    //double lumi_pbpb = 404.0*1e6; // 0.56 nb-1, 404ub-1
    //double nColl[nCentBin+1] = {392.5,1079, 98.36};//0-100,0-30,30-100//provided centrality group AN-15-080 
    const double nMBTot = 2.722608696*1e9; 
    //const double nMB[nCentBin+1] = {nMBTot,nMBTot*0.3,nMBTot*0.7}; // ?*pbpb lumi?
    double nMB[nCentBin+1];
    nMB[0] = nMBTot;
    for(int j=1;j<nCentBin+1;j++){
        nMB[j] = nMBTot*(centBins_f[j]-centBins_i[j])/2./100.;
    }
    //const double nMB[nCentBin+1] = {7750*lumi_pbpb,7750*lumi_pbpb*0.3,7750*lumi_pbpb*0.7}; // ?*pbpb lumi?
    //const double TA[nCentBin+1] = {5.607*1000,15.41*1000,1.405*1000};//provided centrality group AN-15-080 in the unit of [mb-1] 

    for(int j=0;j<nCentBin+1;j++){
        cout << "cent "<<centBins_i[j]/2<<"%-"<<centBins_f[j]/2<<"% TA = " << TA[j] << endl;
        cout << "cent "<<centBins_i[j]/2<<"%-"<<centBins_f[j]/2<<"\% nMB = " << nMB[j] << endl;
        cout << "cent "<<centBins_i[j]/2<<"%-"<<centBins_f[j]/2<<"\% lumipp/TA/nMB = " << lumi_pp/TA[j]/nMB[j] << endl;
    }

    ///////////////////////////////////////////////////////////////////////////
    // temp pp cross section with different pt bins according to centrality ranges
       for(int j=0;j<nCentBinIF;j++){
        // rebin ptbins for each centrality bins since we have less bins for peripheral region
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];
        double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
            ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
        }

        for(int i=0;i<nPtBin_unfolding_centDep;i++){
            h1D_corrpp_temp[j]->SetBinContent(i+1,h1D_corrpp[2]->GetBinContent(i+1));
            h1D_corrpp_temp[j]->SetBinError(i+1,h1D_corrpp[2]->GetBinError(i+1));
        }
    }
 
    /////////////////////////////////////////////////////////////////////////////////////////////
    /// Calulate 0-100 % bin &&
    ///
    cout << "Calculate 0-100 \% bin... " << endl;
    TH1D* h1D_corr_noCal = (TH1D*) h1D_corr[2][0]->Clone(Form("%s_noCal",h1D_corr[2][0]->GetName()));// 0-100% from eff. pur. copied
    TH1D* h1D_Raa_noCal = (TH1D*) h1D_Raa[0]->Clone(Form("%s_noCal",h1D_Raa[0]->GetName())); //

    double weight[nCentBinIF];
    double entries[nCentBinIF]; 
    double tempBinVal[nCentBinIF][nPtBin_unfolding];
    double tempBinErr[nCentBinIF][nPtBin_unfolding];
    double finalVal[nPtBin_unfolding];
    double finalErr[nPtBin_unfolding];
    for(int j=1;j<nCentBinIF;j++)
        entries[j] = h1D_corr[2][j]->Integral();

    double totEntries = (entries[1]+entries[2]+entries[3]+entries[4]);
    for(int j=1;j<nCentBinIF;j++){
        weight[j] = entries[j]/totEntries;
        cout << "weight for cent : " << centBins_i[j] << "\% to " << centBins_f[j] << "\% = " <<entries[j]<<"/"<<totEntries<<" = " <<  weight[j] << endl;
    }
    
    for(int j=1;j<nCentBinIF;j++){
        // rebin ptbins for each centrality bins since we have less bins for peripheral region
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];

        for(int i=0;i<nPtBin_unfolding_centDep;i++){
            tempBinVal[j][i] = h1D_corr[2][j]->GetBinContent(i+1);
            tempBinErr[j][i] = h1D_corr[2][j]->GetBinError(i+1);
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
        h1D_corr[2][0]->SetBinContent(i+1,finalVal[i]);
        h1D_corr[2][0]->SetBinError(i+1,finalErr[i]);
    }
    
    //h1D_Raa[0] = (TH1D*) h1D_corr[2][0]->Clone(Form("%s",h1D_Raa[0]->GetName()));
    //h1D_Raa[0]->Divide(h1D_corrpp[2]);

    /////////////////////////////////////////////////////////////////////////// 
    /// Draw Raa 
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/";
    cout << "!!DRAW RAA!!" << endl;

    TLegend* l1 = new TLegend(0.6,0.65,0.8,0.89);
    legStyle(l1);

    TCanvas* c1 = new TCanvas("craa","",400,400);
    gPad->SetLogx();
    for(int j=0;j<nCentBinIF;j++){
        //SetHistTextSize(h1D_Raa[j]);
        h1D_Raa[j]->Divide(h1D_corr[2][j],h1D_corrpp_temp[j]);
        h1D_Raa[j]->Scale(lumi_pp/(TA[j])/(nMB[j]));

        h1D_Raa[j]->SetMarkerColor(colHere[j]);
        h1D_Raa[j]->SetMarkerStyle(markerHere[j]);
        h1D_Raa[j]->SetMarkerSize(1);
        h1D_Raa[j]->GetYaxis()->SetRangeUser(0.5,1.5);
        h1D_Raa[j]->GetYaxis()->CenterTitle();
        h1D_Raa[j]->GetXaxis()->CenterTitle();
        h1D_Raa[j]->SetTitle(";isolated p_{T}^{#gamma} (GeV);R_{AA}");
        if(j==1) h1D_Raa[j]->Draw("pel");
        else h1D_Raa[j]->Draw("pel same");
        l1->AddEntry(h1D_Raa[j],Form("%d%s-%d%s",centBins_i[j]/2,"%",centBins_f[j]/2,"%")); 
    }
    jumSun(ptBins_unfolding[0],1,ptBins_unfolding[nPtBin_unfolding],1);
    jumSun(ptBins_unfolding[1],0.5,ptBins_unfolding[1],1.5);
    jumSun(ptBins_unfolding[nPtBin_unfolding-1],0.5,ptBins_unfolding[nPtBin_unfolding-1],1.5);
    l1->Draw("same");
    if(!usePurityFit) c1->SaveAs(Form("%sfigures/phoRaa_beforeUnfolding_%s_noPurityFit.pdf",dir.Data(),ver.Data()));
    else c1->SaveAs(Form("%sfigures/phoRaa_beforeUnfolding_%s.pdf",dir.Data(),ver.Data()));
    
    TCanvas* c1_each[nCentBinIF];
    for(int j=0;j<nCentBinIF;j++){
        c1_each[j] = new TCanvas(Form("craa_each_cent%d",j),"",400,400);
        h1D_Raa[j]->Draw("pel");
        jumSun(ptBins_unfolding[0],1,ptBins_unfolding[nPtBin_unfolding],1);
        jumSun(ptBins_unfolding[1],0.5,ptBins_unfolding[1],1.5);
        jumSun(ptBins_unfolding[nPtBin_unfolding-1],0.5,ptBins_unfolding[nPtBin_unfolding-1],1.5);
        if(!usePurityFit) c1_each[j]->SaveAs(Form("%sfigures/phoRaa_beforeUnfolding_%s_noPurityFit_cent%d.pdf",dir.Data(),ver.Data(),j));
        else c1_each[j]->SaveAs(Form("%sfigures/phoRaa_beforeUnfolding_%s_cent%d.pdf",dir.Data(),ver.Data(),j));
    }
   
    /////////////////////////////////////////////////////////////////////////// 
    /// Draw cross section

    TLegend* l2 = new TLegend(0.6,0.65,0.8,0.89);
    legStyle(l2);

    TCanvas* c2 = new TCanvas("cXsec","",400,400);
    c2->cd();
    c2->SetLogy();
    //SetHistTextSize(h1D_corrpp[2]);
    h1D_corrpp[2]->Scale(1./lumi_pp);
    h1D_corrpp[2]->Scale(1e12);
    h1D_corrpp[2]->Scale(1./2.88); //eta range (-1.44 ~ 1.44).
    h1D_corrpp[2]->SetMarkerStyle(21);
    h1D_corrpp[2]->SetMarkerColor(kGreen+1);
    h1D_corrpp[2]->SetTitle(";p_{T}^{#gamma} (GeV); #frac{1}{T_{AA}} #frac{dN}{dp_{T}} (pb/GeV)");
    h1D_corrpp[2]->GetYaxis()->CenterTitle();
    h1D_corrpp[2]->GetXaxis()->CenterTitle();
    float ymin = 0.008;
    float ymax = 10000;
    h1D_corrpp[2]->GetYaxis()->SetRangeUser(ymin,ymax);
    h1D_corrpp[2]->Draw("pe");
    l2->AddEntry(h1D_corrpp[2],"pp"); 
    for(int j=0;j<nCentBinIF;j++){
        //SetHistTextSize(h1D_corr[2][j]);
        h1D_corr[2][j]->Scale(1./TA[j]/nMB[j]);
        h1D_corr[2][j]->Scale(1e12);
        h1D_corr[2][j]->Scale(1./2.88);
        h1D_corr[2][j]->SetMarkerStyle(markerHere[j]);
        h1D_corr[2][j]->SetMarkerColor(colHere[j]);
        h1D_corr[2][j]->SetTitle(";p_{T}^{#gamma} (GeV); #frac{1}{T_{AA}} #frac{dN}{dp_{T}} (pb/GeV)");
        h1D_corr[2][j]->GetYaxis()->SetRangeUser(ymin,ymax);
        h1D_corr[2][j]->Draw("pe same");
        l2->AddEntry(h1D_corr[2][j],Form("%d%s-%d%s",centBins_i[j]/2,"%",centBins_f[j]/2,"%")); 
    }
    jumSun(ptBins_unfolding[1],ymin,ptBins_unfolding[1],ymax);
    jumSun(ptBins_unfolding[nPtBin_unfolding-1],ymin,ptBins_unfolding[nPtBin_unfolding-1],ymax);
    l2->Draw("same");
    if(!usePurityFit) c2->SaveAs(Form("%sfigures/phoXsec_beforeUnfolding_%s_noPurityFit.pdf",dir.Data(),ver.Data()));
    else c2->SaveAs(Form("%sfigures/phoXsec_beforeUnfolding_%s.pdf",dir.Data(),ver.Data()));
    
    TCanvas* c2_each[nCentBinIF];
    for(int j=0;j<nCentBinIF;j++){
        c2_each[j] = new TCanvas(Form("cXsec_each_cent%d",j),"",400,400);
        c2_each[j]->SetLogy();
        h1D_corr[2][j]->Draw("pel");
        jumSun(ptBins_unfolding[1],ymin,ptBins_unfolding[1],ymax);
        jumSun(ptBins_unfolding[nPtBin_unfolding-1],ymin,ptBins_unfolding[nPtBin_unfolding-1],ymax);
        if(!usePurityFit) c2_each[j]->SaveAs(Form("%sfigures/phoXsec_beforeUnfolding_%s_noPurityFit_cent%d.pdf",dir.Data(),ver.Data(),j));
        else c2_each[j]->SaveAs(Form("%sfigures/phoXsec_beforeUnfolding_%s_cent%d.pdf",dir.Data(),ver.Data(),j));
    }
    TCanvas* c2_pp = new TCanvas(Form("craa_each_%s","pp"),"",400,400);
    c2_pp->SetLogy();
    h1D_corrpp[2]->Draw("pe");
    jumSun(ptBins_unfolding[1],ymin,ptBins_unfolding[1],ymax);
    jumSun(ptBins_unfolding[nPtBin_unfolding-1],ymin,ptBins_unfolding[nPtBin_unfolding-1],ymax);
    if(!usePurityFit) c2_pp->SaveAs(Form("%sfigures/phoXsec_beforeUnfolding_%s_noPurityFit_pp.pdf",dir.Data(),ver.Data()));
    else c2_pp->SaveAs(Form("%sfigures/phoXsec_beforeUnfolding_%s_pp.pdf",dir.Data(),ver.Data()));

    ///////////////////////////////////////////////////////////////////////////////////////////
    /// Store histograms in output file 
    TString outName = Form("%soutput/phoRaa_%s_beforeUnfolding.root",dir.Data(),ver.Data());
    if(!usePurityFit) outName = Form("%soutput/phoRaa_%s_noPurityFit_beforeUnfolding.root",dir.Data(),ver.Data());
    
    TFile* outf = new TFile(Form("%s",outName.Data()),"recreate");
    outf->cd();
    for(int j=0;j<nCentBinIF;j++){
        h1D_raw[j]->Write();
        h1D_eff[j]->Write();
        h1D_pur[j]->Write();
        fit_pur[j]->Write();
        h1D_Raa[j]->Write();
        for(int ii=0;ii<3;ii++){
            h1D_corr[ii][j]->Write();
        }
    }
    h1D_corr_noCal->Write();
    h1D_Raa_noCal->Write();
    h1D_rawpp->Write();
    h1D_effpp->Write();
    h1D_purpp->Write();
    fit_purpp->Write();
    for(int ii=0;ii<3;ii++){
        h1D_corrpp[ii]->Write();
    }
    c1->Write();
    c2->Write();

}
