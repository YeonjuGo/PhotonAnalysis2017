// getRawDist.C
// Author: Yeonju Go 
// First produced at 2017 Mar 17 

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
TH1D* reBinS(TH1D* h1=0);

void getRawDist(TString ver="temp")
{
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0000);
    //http://dde.web.cern.ch/dde/glauber_lhc.htm
    TFile *f1 = TFile::Open(pbpbDatafname);
    TTree *tpbpb = (TTree*)f1->Get("EventTree");
    TTree *tpbpb_hi = (TTree*)f1->Get("HiEvt");
    TTree *tpbpb_hlt = (TTree*)f1->Get("hltTree");
    TTree *tpbpb_skim = (TTree*)f1->Get("skim");
    tpbpb->AddFriend(tpbpb_hi);
    tpbpb->AddFriend(tpbpb_hlt);
    tpbpb->AddFriend(tpbpb_skim);

    TFile *f2 = TFile::Open(ppDatafname);
    TTree *tpp = (TTree*)f2->Get("EventTree");
    TTree *tpp_hi = (TTree*)f2->Get("HiEvt");
    TTree *tpp_hlt = (TTree*)f2->Get("hltTree");
    TTree *tpp_skim = (TTree*)f2->Get("skim");
    tpp->AddFriend(tpp_hi);
    tpp->AddFriend(tpp_hlt);
    tpp->AddFriend(tpp_skim);

    TH1D* h1D_raw[nCentBin+1];
    TH1D* h1D_rawpp;
    TH1D* hdummy = new TH1D("hdummy","hdummy",nPtBin,ptBins); 
    ////// Define RAW histograms.
    for(int j=0;j<nCentBinIF;j++)
    {
        h1D_raw[j] = (TH1D*) hdummy->Clone(Form("h1D_raw_cent%d",j)); 
        if(j==0) h1D_rawpp = (TH1D*) hdummy->Clone(Form("h1D_raw_pp"));
    } 

    ////// DRAW RAW DATA
    for(int j=0;j<nCentBinIF;j++)
    {
        TCut centCut;
        centCut = Form("hiBin>=%d && hiBin < %d",centBins_i[j],centBins_f[j]);
        cout << centCut.GetTitle() << endl; 
        tpbpb->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw[j]->GetName()), phoSignalCut && centCut && etaCut);
        if(j==0){
            tpp->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_rawpp->GetName()), phoSignalCut_pp && etaCut); 
            //cout << "################ pp done ################"<< endl;
        }
    }
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/";  
    TFile* outf = new TFile(Form("%soutput/rawDist_%s.root",dir.Data(),ver.Data()),"recreate");
    outf->cd();
    for(int j=0;j<nCentBinIF;j++){
        h1D_raw[j]->Write();
    }
    h1D_rawpp->Write();
}
