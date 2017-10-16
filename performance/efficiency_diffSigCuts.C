// Created : 2017 April 18
// Modified : 2017 April 18
// Author : Yeonju Go
// 

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"

const int colHere[]={2,4,8};
void efficiency_diffSigCuts(int cent_i=0, int cent_f=20){
    TString coll="pbpb";
    const char* fname_1="0";
    const char* fname_2="0";
    if(coll=="pp"){ 
        fname_1=Form("%s",ppMCfname.Data());
        fname_2=Form("%s",ppMCEmEnrfname.Data());
    } else if(coll=="pbpb"){
        fname_1=Form("%s",pbpbMCfname.Data());
        fname_2=Form("%s",pbpbMCEmEnrfname.Data());
    }

    TFile* f1 = new TFile(fname_1);
    TTree* t1 = (TTree*) f1 -> Get("EventTree");
    TTree* t1_hi = (TTree*) f1 -> Get("skim");
    TTree* t1_evt = (TTree*) f1 -> Get("HiEvt");
    TTree* t1_hlt= (TTree*) f1 -> Get("hltTree");
    t1->AddFriend(t1_hi);
    t1->AddFriend(t1_evt);
    t1->AddFriend(t1_hlt);
    TFile* f2 = new TFile(fname_2);
    TTree* t2 = (TTree*) f2 -> Get("EventTree");
    TTree* t2_hi = (TTree*) f2 -> Get("skim");
    TTree* t2_evt = (TTree*) f2 -> Get("HiEvt");
    TTree* t2_hlt= (TTree*) f2 -> Get("hltTree");
    t2->AddFriend(t2_hi);
    t2->AddFriend(t2_evt);
    t2->AddFriend(t2_hlt);


    const int nCuts = 3;
    TH1D* bkg_den[nCuts];
    TH1D* bkg_num[nCuts];
    TH1D* bkg_eff[nCuts];
    TH1D* sig_den[nCuts];
    TH1D* sig_num[nCuts];
    TH1D* sig_eff[nCuts];
    for(Int_t i=0;i<nCuts;++i){
        bkg_den[i] = new TH1D(Form("bkg_den%d",i),";p_{T}^{#gamma} (GeV);dN/d(hiBin)",17,30,200);
        bkg_num[i] = new TH1D(Form("bkg_num%d",i),";p_{T}^{#gamma} (GeV);dN/d(hiBin)",17,30,200);
        bkg_eff[i] = new TH1D(Form("bkg_eff%d",i),";p_{T}^{#gamma} (GeV);Efficiency",17,30,200);
        sig_den[i] = new TH1D(Form("sig_den%d",i),";p_{T}^{#gamma} (GeV);dN/d(hiBin)",17,30,200);
        sig_num[i] = new TH1D(Form("sig_num%d",i),";p_{T}^{#gamma} (GeV);dN/d(hiBin)",17,30,200);
        sig_eff[i] = new TH1D(Form("sig_eff%d",i),";p_{T}^{#gamma} (GeV);Efficiency",17,30,200);
        
      //  bkg_den[i] = new TH1D(Form("bkg_den%d",i),";p_{T}^{#gamma} (GeV);dN/d(hiBin)",nPtBin,ptBins);
      //  bkg_num[i] = new TH1D(Form("bkg_num%d",i),";p_{T}^{#gamma} (GeV);dN/d(hiBin)",nPtBin,ptBins);
      //  bkg_eff[i] = new TH1D(Form("bkg_eff%d",i),";p_{T}^{#gamma} (GeV);Efficiency",nPtBin,ptBins);
      //  sig_den[i] = new TH1D(Form("sig_den%d",i),";p_{T}^{#gamma} (GeV);dN/d(hiBin)",nPtBin,ptBins);
      //  sig_num[i] = new TH1D(Form("sig_num%d",i),";p_{T}^{#gamma} (GeV);dN/d(hiBin)",nPtBin,ptBins);
      //  sig_eff[i] = new TH1D(Form("sig_eff%d",i),";p_{T}^{#gamma} (GeV);Efficiency",nPtBin,ptBins);
        
       // bkg_den[i] = new TH1D(Form("bkg_den%d",i),";hiBin;dN/d(hiBin)",10,,200);
       // bkg_num[i] = new TH1D(Form("bkg_num%d",i),";hiBin;dN/d(hiBin)",10,0,200);
       // bkg_eff[i] = new TH1D(Form("bkg_eff%d",i),";hiBin;Efficiency",10,0,200);
       // sig_den[i] = new TH1D(Form("sig_den%d",i),";hiBin;dN/d(hiBin)",10,0,200);
       // sig_num[i] = new TH1D(Form("sig_num%d",i),";hiBin;dN/d(hiBin)",10,0,200);
       // sig_eff[i] = new TH1D(Form("sig_eff%d",i),";hiBin;Efficiency",10,0,200);
    }

    TCut sumisoCut[nCuts];//new variables : pho_sumIsoCorrected, phoEtCorrected
    sumisoCut[0] = "pho_sumIsoCorrected<1.0";
    sumisoCut[1] = "pho_sumIsoCorrected<3.0";
    sumisoCut[2] = "pho_sumIsoCorrected<5.0";
   // sumisoCut[0] = "(pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20)<(1.815479-0.0111385*hiBin+3.36732e-05*hiBin*hiBin)";
   // sumisoCut[1] = "(pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20)<(7.47579-0.0638925*hiBin+0.000165199*hiBin*hiBin)";
   // sumisoCut[2] = "(pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20)<(16.7202-0.154349*hiBin+0.00040613*hiBin*hiBin)";
    //sumisoCut[0] = "(pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20)<(0.815479-0.0111385*hiBin+3.36732e-05*hiBin*hiBin)";
    //sumisoCut[1] = "(pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20)<(6.47579-0.0638925*hiBin+0.000165199*hiBin*hiBin)";
    //sumisoCut[2] = "(pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20)<(15.7202-0.154349*hiBin+0.00040613*hiBin*hiBin)";
    int j=1; 
    TCut centCut = Form("(hiBin>=%d)&&(hiBin<%d)",centBins_i[j],centBins_f[j] );
    TCut commonCut = trigCut_mc_pbpb && etaCut && centCut;
    TCut numCut = sigmaCut && hoeCut;
    
    
    for(Int_t i=0;i<nCuts;++i){
        cout << i << "TH CUT STARTS :: " << endl;
        t1->Draw(Form("phoEt>>%s",sig_den[i]->GetName()),mcIsolation && commonCut);
        sig_den[i]=(TH1D*)gDirectory->Get(sig_den[i]->GetName());
        t1->Draw(Form("phoEt>>%s",sig_num[i]->GetName()),mcIsolation && commonCut && numCut && sumisoCut[i]); 
        sig_num[i]=(TH1D*)gDirectory->Get(sig_num[i]->GetName());
        t2->Draw(Form("phoEt>>%s",bkg_den[i]->GetName()),mcBkgIsolation && commonCut);
        bkg_den[i]=(TH1D*)gDirectory->Get(bkg_den[i]->GetName());
        t2->Draw(Form("phoEt>>%s",bkg_num[i]->GetName()),mcBkgIsolation && commonCut && numCut && sumisoCut[i]); 
        bkg_num[i]=(TH1D*)gDirectory->Get(bkg_num[i]->GetName());
        
       // t1->Draw(Form("hiBin>>%s",sig_den[i]->GetName()),mcIsolation && commonCut);
       // sig_den[i]=(TH1D*)gDirectory->Get(sig_den[i]->GetName());
       // t1->Draw(Form("hiBin>>%s",sig_num[i]->GetName()),mcIsolation && commonCut && numCut && sumisoCut[i]); 
       // sig_num[i]=(TH1D*)gDirectory->Get(sig_num[i]->GetName());
       // t2->Draw(Form("hiBin>>%s",bkg_den[i]->GetName()),mcBkgIsolation && commonCut);
       // bkg_den[i]=(TH1D*)gDirectory->Get(bkg_den[i]->GetName());
       // t2->Draw(Form("hiBin>>%s",bkg_num[i]->GetName()),mcBkgIsolation && commonCut && numCut && sumisoCut[i]); 
       // bkg_num[i]=(TH1D*)gDirectory->Get(bkg_num[i]->GetName());
    }
    cout << " DRAWING STARTS " << endl;
    TLegend* l1 = new TLegend(0.6,0.6,0.9,0.9);

    TCanvas* c2 =new TCanvas(Form("c%d",2),"", 500,500); 
    for(Int_t i=0;i<nCuts;++i){
        sig_eff[i]->Divide(sig_num[i],sig_den[i],1,1,"B");
        bkg_eff[i]->Divide(bkg_num[i],bkg_den[i],1,1,"B");
        sig_eff[i]->SetMarkerStyle(20);
        bkg_eff[i]->SetMarkerStyle(20);
        sig_eff[i]->SetMarkerColor(colHere[i]);
        bkg_eff[i]->SetMarkerColor(colHere[i]);
        sig_eff[i]->GetYaxis()->SetRangeUser(0,1);
        if(i==0) sig_eff[i]->Draw("p");
        else sig_eff[i]->Draw("same p");
        bkg_eff[i]->Draw("same p");
        //const char* tempName = ;
        l1->AddEntry(sig_eff[i], Form("%s",sumisoCut[i].GetTitle()));
        //l1->AddEntry(sig_eff[i], Form("%s",tempName.Data()));
    } 
    l1->Draw("same");
    drawText(Form("%s",coll.Data()),0.6,1.0-c2->GetTopMargin()-0.04);
    drawText(Form("%d<hiBin<%d",centBins_i[j],centBins_f[j]),0.2,1.0-c2->GetTopMargin()-0.04);
    c2->SaveAs(Form("figures/efficiency_diffSumIsoCuts_hiBin%dto%d_plus1.pdf",centBins_i[j],centBins_f[j]));
    //TLegend* l1 = new TLegend(0.5,0.5,0.9,0.9);
     
    //h1->SetTitleSize(13);
    //jumSun(xMin,1,xMax,1);
}
