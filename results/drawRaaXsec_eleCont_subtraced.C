// drawRaaXsec_eleCont_subtraced.C 
// to remove remaining electrons after the rejection, by using electron rejection efficiency
// Author: Yeonju Go 
// Written at 2019 July 26
// Modified : 2019 July 26

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
TH1D* subtract2HistUsingEff(TH1D* h1D_nom, TH1D* h1D_sys, TH1D* h1D_eff);
void drawRaaXsec_eleCont_subtraced(TString ver="190703_temp_v31_sys_eleCont", bool doSplitPD = true, bool usePurityFit = true)
{
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0000);
    //SetyjPadStyle();
    //SetHistTitleStyle(0.05);

    TString cap = "";
    if(doSplitPD) cap += "_splitPD"; 
    TString subver = ver(0,16);
    cout << subver << endl;
    
    TString fname_nominal = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/phoRaa_"+subver+"nominal_beforeUnfolding.root"; 
    TString fname_eleCont = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/phoRaa_"+ver+"_beforeEffCorrection_beforeUnfolding.root"; 
    TString outfname_eleCont = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/phoRaa_"+ver+"_beforeUnfolding.root"; 

    TFile* f_nominal = new TFile(Form("%s",fname_nominal.Data()));
    TFile* f_eleCont = new TFile(Form("%s",fname_eleCont.Data()));


    TFile* f_eleEff_corr_pp = new TFile("/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/electronRejectionEfficiency_pp.root");
    TFile* f_eleEff_corr_pbpb = new TFile("/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/electronRejectionEfficiency_pbpb.root");

    TH1D* h1D_eff[nCentBinIF];
    TH1D* h1D_effpp;
    TH1D* h1D_pur[nCentBinIF];
    TH1D* h1D_purpp;
    TH1D* h1D_raw[nCentBinIF];
    TH1D* h1D_rawpp;

    TH1D* h1D_xSec[nCentBinIF]; 
    TH1D* h1D_xSecpp; 
    TH1D* h1D_Raa[nCentBinIF]; 

    TH1D* h1D_xSec_beforeEffCorrection[nCentBinIF]; 
    TH1D* h1D_xSecpp_beforeEffCorrection; 
    TH1D* h1D_Raa_beforeEffCorrection[nCentBinIF];

    TH1D* h1D_xSec_nominal[nCentBinIF]; 
    TH1D* h1D_xSecpp_nominal; 
    TH1D* h1D_Raa_nominal[nCentBinIF]; 
    
    TH1D* h1D_correction_effpp = (TH1D*) f_eleEff_corr_pp->Get("eleRej_eff_cent0"); 
    h1D_correction_effpp->SetName("eleRej_eff_pp"); 
    TH1D* h1D_correction_eff[nCentBinIF]; 
    for(int j=0;j<nCentBinIF;++j)
        h1D_correction_eff[j] = (TH1D*) f_eleEff_corr_pbpb->Get(Form("eleRej_eff_cent%d",j)); 
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////// 
    /// Get all the hists from  
    cout << "get efficiency, purity, raw, xSec, Raa histograms from the input systematic files..." <<endl;
    TCanvas* ctemp[nCentBinIF];
    for(int j=0;j<nCentBinIF;++j)
    {
        cout << "cent "<< j << endl; 
        h1D_xSec_nominal[j] = (TH1D*) f_nominal->Get(Form("h1D_dNdpt_corr2_cent%d",j));
        h1D_xSec_nominal[j]->SetName(Form("h1D_dNdpt_corr2_cent%d_nominal",j));
        h1D_Raa_nominal[j] = (TH1D*) f_nominal->Get(Form("h1D_Raa_cent%d",j));
        h1D_Raa_nominal[j]->SetName(Form("h1D_Raa_cent%d_nominal",j));

        h1D_raw[j] = (TH1D*) f_eleCont->Get(Form("h1D_raw_cent%d",j));
        h1D_eff[j] = (TH1D*) f_eleCont->Get(Form("h1D_eff_cent%d",j));
        h1D_pur[j] = (TH1D*) f_eleCont->Get(Form("h1D_purity_cent%d",j));
        h1D_xSec_beforeEffCorrection[j] = (TH1D*) f_eleCont->Get(Form("h1D_dNdpt_corr2_cent%d",j));
        h1D_Raa_beforeEffCorrection[j] = (TH1D*) f_eleCont->Get(Form("h1D_Raa_cent%d",j));
        h1D_xSec[j] = subtract2HistUsingEff(h1D_xSec_nominal[j],h1D_xSec_beforeEffCorrection[j],h1D_correction_eff[j]);
        h1D_Raa[j] = subtract2HistUsingEff(h1D_Raa_nominal[j],h1D_Raa_beforeEffCorrection[j],h1D_correction_eff[j]);
    }

    cout << "done pbpb" << endl;
    h1D_xSecpp_nominal = (TH1D*) f_nominal->Get("h1D_dNdpt_corr2_pp");
    h1D_xSecpp_nominal->SetName("h1D_dNdpt_corr2_pp_nominal");
    h1D_rawpp = (TH1D*) f_eleCont->Get("h1D_raw_pp");
    h1D_effpp = (TH1D*) f_eleCont->Get("h1D_eff_cent0_tot_pp");
    h1D_purpp = (TH1D*) f_eleCont->Get("h1D_purity_pp");
    h1D_xSecpp_beforeEffCorrection = (TH1D*) f_eleCont->Get("h1D_dNdpt_corr2_pp");
    h1D_xSecpp = subtract2HistUsingEff(h1D_xSecpp_nominal,h1D_xSecpp_beforeEffCorrection,h1D_correction_effpp);
    cout << "done pp" << endl;

    ///////////////////////////////////////////////////////////////////////////////////////////
    /// Store histograms in output file 
    
    TFile* outf = new TFile(Form("%s",outfname_eleCont.Data()),"recreate");
    outf->cd();
    for(int j=0;j<nCentBinIF;j++){
        h1D_raw[j]->Write();
        h1D_eff[j]->Write();
        h1D_pur[j]->Write();
        h1D_xSec[j]->Write();
        h1D_Raa[j]->Write();
    }
    //h1D_corr_noCal->Write();
    //h1D_Raa_noCal->Write();
    h1D_rawpp->Write();
    h1D_effpp->Write();
    h1D_purpp->Write();
    h1D_xSecpp->Write();
    //c1->Write();
    //c2->Write();

}

TH1D* subtract2HistUsingEff(TH1D* h1D_nom, TH1D* h1D_sys, TH1D* h1D_eff){
    TString tempName = h1D_sys->GetName();
    h1D_sys->SetName(Form("%s_beforeEffCorrection",h1D_sys->GetName()));
    TH1D* h_corrected = (TH1D*) h1D_nom->Clone(Form("%s",tempName.Data()));

    for(int ibin=1; ibin<h1D_nom->GetNbinsX(); ++ibin){
        double delta = abs(h1D_sys->GetBinContent(ibin)-h1D_nom->GetBinContent(ibin));     
        double eff = h1D_eff->GetBinContent(ibin);
        double additionalSubFactor = abs(delta * (1-eff)/eff); 
        double tempCont = h1D_nom->GetBinContent(ibin)-additionalSubFactor;
        h_corrected->SetBinContent(ibin,tempCont);
        h_corrected->SetBinError(ibin,h1D_nom->GetBinError(ibin));
    }
    return h_corrected;
}
