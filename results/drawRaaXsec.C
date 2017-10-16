// drawRaaXsec.C 
// This version gets photon raw distributions from the output/rawDist.root, while version 1 calculate these in that code. 
// Author: Yeonju Go 
// Written at 2017 Mar 17
// Written at 2017 Mar 17

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
#include "../ElectroWeak-Jet-Track-Analyses/Histogramming/PhotonPurity.h"
#include "../ElectroWeak-Jet-Track-Analyses/Utilities/interface/CutConfigurationParser.h"
#include "../ElectroWeak-Jet-Track-Analyses/TreeHeaders/CutConfigurationTree.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"

const TString LABEL = "PbPb #sqrt{s}_{_{NN}}=5.02 TeV";
const int colHere[]={1,2,4,kGreen+1,kYellow+1};
const int markerHere[]={24,28,28,28,28,28};
const int markerHere_closed[]={20,33,33,33,33};
void drawRaaXsec(TString ver="170601_temp_v3")
{
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0000);
    SetyjPadStyle();
    //SetHistTitleStyle(0.05);
    // http://dde.web.cern.ch/dde/glauber_lhc.htm

    // nCentBin+1 : 0th array is for inclusive[0-100%]
    TFile* f_eff = new TFile(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/output/pbpb_efficiency_%s.root",ver.Data()));
    TFile* f_effpp = new TFile(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/output/pp_efficiency_%s.root",ver.Data()));;
    TFile* f_pur = new TFile(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/purity/output/pbpb_purity_%s.root",ver.Data()));
    TFile* f_purpp = new TFile(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/purity/output/pp_purity_%s.root",ver.Data()));;
    TFile* f_raw = new TFile(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/rawDist_%s.root",ver.Data()));

    TH1D* h1D_eff[nCentBinIF];
    TH1D* h1D_effpp;
    TH1D* h1D_pur[nCentBinIF];
    TH1D* h1D_purpp;
    TH1D* h1D_raw[nCentBinIF];
    TH1D* h1D_rawpp;

    Int_t nCor = 3;
    TH1D* h1D_corr[nCor][nCentBinIF]; // corrected yield 1. purity, 2. efficiency 
    TH1D* h1D_corrpp[nCor]; // corrected yield 1. purity, 2. efficiency 
    TH1D* h1D_Raa[nCentBinIF]; // total Raa!!

    /////////////////////////////////////////////////////////////////////////// 
    /// Get efficiency & purity hist. 
    for(int j=0;j<nCentBinIF;++j)
    {
        h1D_raw[j] = (TH1D*) f_raw->Get(Form("h1D_raw_cent%d",j));
        h1D_eff[j] = (TH1D*) f_eff->Get(Form("sig_eff%d",j));
        //h1D_eff[j] = (TH1D*) f_eff->Get(Form("h1D_efficiency_cent%d",j));
        h1D_pur[j] = (TH1D*) f_pur->Get(Form("h1D_purity_cent%d",j));
       
        h1D_Raa[j] = new TH1D(Form("h1D_Raa_cent%d",j),Form(";p_{T}^{#gamma} (GeV);R_{AA}"),nPtBin,ptBins_draw);
        
        if(j==0){
            h1D_rawpp = (TH1D*) f_raw->Get("h1D_raw_pp");
            h1D_effpp = (TH1D*) f_effpp->Get("sig_eff0");
            //h1D_effpp = (TH1D*) f_effpp->Get("h1D_effciency_pp");
            h1D_purpp = (TH1D*) f_purpp->Get("h1D_purity_pp");
        }
    }


    /////////////////////////////////////////////////////////////////////////// 
    /// Get corrected distributions
    for(int j=0;j<nCentBin+1;j++)
    {
        h1D_raw[j]->Scale(1.,"width");
        for(int ii=0;ii<nCor;ii++){ // corrected yield 0th:raw 1st:purity 2nd:purity and efficiency
            h1D_corr[ii][j] = new TH1D(Form("h1D_dNdpt_corr%d_cent%d",ii,j),";p_{T}^{#gamma} (GeV); dN/dp_{T} (GeV^{-1})",nPtBin,ptBins_draw);
            if(j==0){ 
                h1D_corrpp[ii] = new TH1D(Form("h1D_dNdpt_corr%d_pp",ii),";p_{T}^{#gamma} (GeV); dN/dp_{T} (GeV^{-1})",nPtBin,ptBins_draw);
            }
        }
        for(int ipt=0;ipt<nPtBin;++ipt){
            Double_t vEff, vPur, vRaw;
            vEff = h1D_eff[j]->GetBinContent(ipt+1);
            vPur = h1D_pur[j]->GetBinContent(ipt+1);
            vRaw = h1D_raw[j]->GetBinContent(ipt+1);

            cout << centBins_i[j]/2<<"%-"<<centBins_f[j]/2<<"% : " << ptBins[ipt] << "<pt<"<< ptBins[ipt+1]<<" :: \traw=\t" << vRaw << "\teff\t" << vEff << "\tpur\t" << vPur << endl; 
            h1D_corr[0][j]->SetBinContent(ipt+1, vRaw); 
            h1D_corr[1][j]->SetBinContent(ipt+1, vRaw*vPur); 
            h1D_corr[2][j]->SetBinContent(ipt+1, vRaw*vPur/vEff); 
        }
        if(j==0) {
            h1D_rawpp->Scale(1.,"width");
            for(int ipt=0;ipt<nPtBin;++ipt){
                Double_t vEff, vPur, vRaw;
                vEff = h1D_effpp->GetBinContent(ipt+1);
                vPur = h1D_purpp->GetBinContent(ipt+1);
                vRaw = h1D_rawpp->GetBinContent(ipt+1);
                
                cout <<"PP : " << ptBins[ipt] << "<pt<"<< ptBins[ipt+1] <<" :: \traw=\t" << vRaw << "\teff\t" << vEff << "\tpur\t" << vPur << endl; 
                h1D_corrpp[0]->SetBinContent(ipt+1, vRaw); 
                h1D_corrpp[1]->SetBinContent(ipt+1, vRaw*vPur); 
                h1D_corrpp[2]->SetBinContent(ipt+1, vRaw*vPur/vEff); 
            }
        }

    }


    /////////////////////////////////////////////////////////////////////////// 
    /// Set Global Values 

    double lumi_pp = 25.775*1e12; //25.775 pb-1
    //double lumi_pp = 27.87*1e12; //27.87 pb-1
    double lumi_pbpb = 404.0*1e6; // 0.56 nb-1, 404ub-1
    double nColl[nCentBin+1] = {392.5,1079, 98.36};//0-100,0-30,30-100//provided centrality group AN-15-080 
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
    /// Draw Raa 
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/";
    cout << "!!DRAW RAA!!" << endl;

    TLegend* l1 = new TLegend(0.6,0.65,0.8,0.89);
    legStyle(l1);

    TCanvas* c1 = new TCanvas("craa","",400,400);
    for(int j=0;j<nCentBin+1;j++)
    {
        SetHistTextSize(h1D_Raa[j]);
        h1D_Raa[j]->Divide(h1D_corr[2][j],h1D_corrpp[2]);
        h1D_Raa[j]->Scale(lumi_pp/(TA[j])/(nMB[j]));
        h1D_Raa[j]->SetMarkerColor(colHere[j]);
        h1D_Raa[j]->SetMarkerStyle(markerHere_closed[j]);
        h1D_Raa[j]->SetMarkerSize(1);
        h1D_Raa[j]->GetYaxis()->SetRangeUser(0.5,1.5);
        h1D_Raa[j]->GetYaxis()->CenterTitle();
        h1D_Raa[j]->GetXaxis()->CenterTitle();
        h1D_Raa[j]->SetTitle(";isolated p_{T}^{#gamma} (GeV);R_{AA}");
        if(j==0) h1D_Raa[j]->Draw("pel");
        else h1D_Raa[j]->Draw("pel same");
        jumSun(40,1,120,1);
        l1->AddEntry(h1D_Raa[j],Form("%d%s-%d%s",centBins_i[j]/2,"%",centBins_f[j]/2,"%")); 
    }
    l1->Draw("same");
    c1->SaveAs(Form("%sfigures/phoRaa_%s.pdf",dir.Data(),ver.Data()));
   
    /////////////////////////////////////////////////////////////////////////// 
    /// Draw cross section

    TLegend* l2 = new TLegend(0.6,0.65,0.8,0.89);
    legStyle(l2);

    TCanvas* c2 = new TCanvas("cXsec","",400,400);
    c2->cd();
    c2->SetLogy();
    SetHistTextSize(h1D_corrpp[2]);
    h1D_corrpp[2]->Scale(1./lumi_pp);
    h1D_corrpp[2]->Scale(1e12);
    h1D_corrpp[2]->SetMarkerStyle(21);
    h1D_corrpp[2]->SetMarkerColor(kGreen+1);
    h1D_corrpp[2]->SetTitle(";p_{T}^{#gamma} (GeV); #frac{1}{T_{AA}} #frac{dN}{dp_{T}} (pb/GeV)");
    h1D_corrpp[2]->GetYaxis()->CenterTitle();
    h1D_corrpp[2]->GetXaxis()->CenterTitle();
    h1D_corrpp[2]->Draw("pe");
    l2->AddEntry(h1D_corrpp[2],"pp"); 
    for(int j=0;j<nCentBinIF;j++){
        h1D_corr[2][j]->Scale(1./TA[j]/nMB[j]);
        h1D_corr[2][j]->Scale(1e12);
        h1D_corr[2][j]->SetMarkerStyle(markerHere[j]);
        h1D_corr[2][j]->SetMarkerColor(colHere[j]);
        h1D_corr[2][j]->Draw("pe same");
        l2->AddEntry(h1D_corr[2][j],Form("%d%s-%d%s",centBins_i[j]/2,"%",centBins_f[j]/2,"%")); 
    }
    l2->Draw("same");
    c2->SaveAs(Form("%sfigures/phoXsec_%s.pdf",dir.Data(),ver.Data()));

    TFile* outf = new TFile(Form("%soutput/phoRaa_%s.root",dir.Data(),ver.Data()),"recreate");
    outf->cd();
    for(int j=0;j<nCentBinIF;j++){
        h1D_raw[j]->Write();
        h1D_eff[j]->Write();
        h1D_pur[j]->Write();
        h1D_Raa[j]->Write();
        for(int ii=0;ii<3;ii++){
            h1D_corr[ii][j]->Write();
        }
    }
    h1D_rawpp->Write();
    h1D_effpp->Write();
    h1D_purpp->Write();
    for(int ii=0;ii<3;ii++){
        h1D_corrpp[ii]->Write();
    }
    c1->Write();
    c2->Write();

}
