// Created : 2017 April 18
// Modified : 2017 May18
// Author : Yeonju Go
// 

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"

const int colHere[]={2,4,8,kYellow+2,kCyan+1};
void efficiency_withSkimFile(TString coll="pbpb", TString ver="170523_temp_v1"){
    cout << " efficiency_withSkimFile.C " << endl;
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);
    SetyjPadStyle();

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
    
    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1;

    TH1D* bkg_den[nCENTBINS];
    TH1D* bkg_num[nCENTBINS];
    TH1D* bkg_eff[nCENTBINS];
    TH1D* sig_den[nCENTBINS];
    TH1D* sig_num[nCENTBINS];
    TH1D* sig_eff[nCENTBINS];
    
    for(Int_t i=0;i<nCENTBINS;++i){
        bkg_den[i] = new TH1D(Form("bkg_den%d",i),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nPtBin,ptBins);
        bkg_num[i] = new TH1D(Form("bkg_num%d",i),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nPtBin,ptBins);
        bkg_eff[i] = new TH1D(Form("bkg_eff%d",i),";p_{T}^{#gamma} (GeV);Efficiency",nPtBin,ptBins);
        sig_den[i] = new TH1D(Form("sig_den%d",i),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nPtBin,ptBins);
        sig_num[i] = new TH1D(Form("sig_num%d",i),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nPtBin,ptBins);
        sig_eff[i] = new TH1D(Form("sig_eff%d",i),";p_{T}^{#gamma} (GeV);Efficiency",nPtBin,ptBins);
    }

    TCut centCut[nCENTBINS];
    TCut commonCut[nCENTBINS];
    TCut numCut = evtSelFilterCut && noiseCut && hoeCut && isoCut && sigmaCut; 
    for(Int_t i=0;i<nCENTBINS;++i){
        centCut[i] = Form("(hiBin>=%d)&&(hiBin<%d)",centBins_i[i],centBins_f[i]);
        commonCut[i] = trigCut_mc && etaCut && centCut[i];
    } 

    if(coll=="pp") {
        commonCut[0] = trigCut_mc_pp && etaCut; 
        numCut = evtSelFilterCut_pp && noiseCut && hoeCut_pp && isoCut_pp && sigmaCut_pp; 
    }
    for(Int_t i=0;i<nCENTBINS;++i){
        t1->Draw(Form("%s>>%s",phoEtVar.Data(),sig_den[i]->GetName()),Form("(%s)*((%s) && (%s))","weight",mcIsolation.GetTitle(),commonCut[i].GetTitle()));
        //t1->Draw(Form("%s>>%s",phoEtVar.Data(),sig_den[i]->GetName()),Form("(%s)*(%s && %s)","weight",mcIsolation && commonCut[i]);
        sig_den[i]=(TH1D*)gDirectory->Get(sig_den[i]->GetName());
        t1->Draw(Form("%s>>%s",phoEtVar.Data(),sig_num[i]->GetName()),Form("(%s)*((%s) && (%s) && (%s))","weight",mcIsolation.GetTitle(), commonCut[i].GetTitle(), numCut.GetTitle())); 
        //t1->Draw(Form("%s>>%s",phoEtVar.Data(),sig_num[i]->GetName()),mcIsolation && commonCut[i] && numCut); 
        sig_num[i]=(TH1D*)gDirectory->Get(sig_num[i]->GetName());
        t2->Draw(Form("%s>>%s",phoEtVar.Data(),bkg_den[i]->GetName()),mcBkgIsolation && commonCut[i]);
        bkg_den[i]=(TH1D*)gDirectory->Get(bkg_den[i]->GetName());
        t2->Draw(Form("%s>>%s",phoEtVar.Data(),bkg_num[i]->GetName()),mcBkgIsolation && commonCut[i] && numCut); 
        bkg_num[i]=(TH1D*)gDirectory->Get(bkg_num[i]->GetName());
    }
    for(Int_t i=0;i<nCENTBINS;++i){
        sig_eff[i]->Divide(sig_num[i],sig_den[i],1.,1.,"B");
        bkg_eff[i]->Divide(bkg_num[i],bkg_den[i],1.,1.,"B");
    }

    cout << " DRAWING STARTS " << endl;
    TLegend* l1 = new TLegend(0.5,0.2,0.8,0.4);
    legStyle(l1);
    
    TH1D* bkg_eff_draw[nCENTBINS];
    TH1D* sig_eff_draw[nCENTBINS];
    for(Int_t i=0;i<nCENTBINS;++i){
        bkg_eff_draw[i] = new TH1D(Form("bkg_eff_draw%d",i),";p_{T}^{#gamma} (GeV);Efficiency",nPtBin,ptBins_draw);
        sig_eff_draw[i] = new TH1D(Form("sig_eff_draw%d",i),";p_{T}^{#gamma} (GeV);Efficiency",nPtBin,ptBins_draw);
        for(int j=0;j<nPtBin;++j){
            bkg_eff_draw[i]->SetBinContent(j+1,bkg_eff[i]->GetBinContent(j+1));
            bkg_eff_draw[i]->SetBinError(j+1,bkg_eff[i]->GetBinError(j+1));
            sig_eff_draw[i]->SetBinContent(j+1,sig_eff[i]->GetBinContent(j+1));
            sig_eff_draw[i]->SetBinError(j+1,sig_eff[i]->GetBinError(j+1));
        }
    }
    TCanvas* c1 =new TCanvas(Form("c%d",2),"", 400,400);
    //c1->SetLogx(); 
    for(Int_t i=0;i<nCENTBINS;++i){
        SetHistTextSize(sig_eff_draw[i]);
        if(i==0) {
            sig_eff_draw[i]->SetMarkerStyle(33);
            sig_eff_draw[i]->SetMarkerSize(1.4);
            bkg_eff_draw[i]->SetMarkerStyle(33);
        } else{
            sig_eff_draw[i]->SetMarkerStyle(20);
            bkg_eff_draw[i]->SetMarkerStyle(20);
        }
        sig_eff_draw[i]->SetMarkerColor(colHere[i]);
        bkg_eff_draw[i]->SetMarkerColor(colHere[i]);
        sig_eff_draw[i]->GetYaxis()->SetRangeUser(0,1);
        sig_eff_draw[i]->GetXaxis()->CenterTitle();
        sig_eff_draw[i]->GetYaxis()->CenterTitle();
        if(i==0) sig_eff_draw[i]->Draw("p");
        else sig_eff_draw[i]->Draw("same p");
        //bkg_eff[i]->Draw("same p");
        if(coll=="pbpb") l1->AddEntry(sig_eff_draw[i], Form("%d%s-%d%s",centBins_i[i]/2,"%",centBins_f[i]/2,"%"));
    } 
    if(coll=="pbpb") l1->Draw("same");
    drawText(Form("%s",coll.Data()),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/";
    c1->SaveAs(Form("%sfigures/%s_efficiency_%s.pdf",dir.Data(),coll.Data(),ver.Data()));

    TFile* fout = new TFile(Form("%soutput/%s_efficiency_%s.root",dir.Data(),coll.Data(),ver.Data()),"RECREATE");
    fout->cd();
    for(Int_t i=0;i<nCENTBINS;++i){
        sig_eff[i]->Write();
        bkg_eff[i]->Write();
        c1->Write();
    }
}
