// 2016 Mar . comparing two datasets (ex. allqcdphoton and emenricheddijet) 
// Created : 31 May 2017
// Modified : 01 June 2017
// Author : Yeonju Go

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"

void ROCcurve_sumIso(TString coll="pp", TString ver="190703_temp_v31"){

    const char* fname_1 ="";
    const char* fname_2 ="";
    if(coll=="pp"){ 
        fname_1=ppMCfname;
        fname_2=ppMCEmEnrfname;
    } else if(coll=="pbpb"){
        fname_1=pbpbMCfname;
        fname_2=pbpbMCEmEnrfname;
    }

    TFile* f1 = new TFile(fname_1);
    TTree* t1 = (TTree*) f1 -> Get("EventTree");
    TTree* t1_hi = (TTree*) f1 -> Get("skim");
    TTree* t1_hlt = (TTree*) f1 -> Get("hltTree");
    TTree* t1_evt = (TTree*) f1 -> Get("HiEvt");
    t1->AddFriend(t1_hi);
    t1->AddFriend(t1_evt);
    t1->AddFriend(t1_hlt);

    TFile* f2 = new TFile(fname_2);
    TTree* t2 = (TTree*) f2 -> Get("EventTree");
    TTree* t2_hi = (TTree*) f2 -> Get("skim");
    TTree* t2_evt = (TTree*) f2 -> Get("HiEvt");
    TTree* t2_hlt = (TTree*) f2 -> Get("hltTree");
    t2->AddFriend(t2_hi);
    t2->AddFriend(t2_evt);
    t2->AddFriend(t2_hlt);

    //const int centBins_i_[] = {0};
    //const int centBins_f_[] = {20};
    //const int centBins_i_[] = {0};
    //const int centBins_f_[] = {200};
    const int centBins_i_[] = {0,0,20,60,100};
    const int centBins_f_[] = {200,20,60,100,200};
    int nCentBinIF_ = sizeof(centBins_i_)/sizeof(int);
    if(coll=="pp") nCentBinIF_=1;
    //const double ptBins_i_[] = {20};
    //const double ptBins_f_[] = {200};
    const double ptBins_i_[] = {20,20,25,30,40,50,60,80,100};
    const double ptBins_f_[] = {30,25,30,40,50,60,80,100,200};
    //const double ptBins_i_[] = {20,25,30,40,50,60,80,100,130};
    //const double ptBins_f_[] = {25,30,40,50,60,80,100,130,200};
    int nPtBinIF_ = sizeof(ptBins_i_)/sizeof(double);
    
    const double sumIsoBins[] = {1,3,5,7,10,15,20,25,30,40,50,60};
    //const double sumIsoBins[] = {0.1,0.2,0.3,0.4,0.5,0.8,1.0,1.2,1.4,1.6,2.0,2.5,3.0,3.5,4.0,4.5,5.0,6.0,7.0,10.0};
    int nSumIso = sizeof(sumIsoBins)/sizeof(double);

    TGraphAsymmErrors* roc[nPtBinIF_][nCentBinIF_];

    Int_t nCENTBINS = nCentBinIF_;
    if(coll=="pp") nCENTBINS=1;

    for(Int_t i = 0; i < nPtBinIF_; ++i) 
    {
        TCut ptCut_ = Form("(phoEtCorrected >= %f) && (phoEtCorrected < %f)", ptBins_i_[i], ptBins_f_[i]);
        for(Int_t k = 0; k < nCENTBINS; ++k){ 
            roc[i][k] = new TGraphAsymmErrors(nSumIso);
            roc[i][k]->SetName(Form("roc_pt%d_cent%d",i,k));
            roc[i][k]->SetTitle(";Signal efficiency;Background rejection");
            TCanvas* c1 = new TCanvas("c1","",500,400);
            
            TCut centCut = Form("(hiBin >= %d) && (hiBin < %d)", centBins_i_[k], centBins_f_[k]);    
            if(coll=="pp") centCut = "hiBin<10000";

            TCut bkgMCCut = mcBkgIsolation && ptCut_ && etaCut && centCut;
            TCut sigMCCut = mcIsolation && ptCut_ && etaCut && centCut;

            TString cap = Form("%s_%s_pt%dto%d_cent%dto%d",ver.Data(),coll.Data(),(int)ptBins_i_[i],(int)ptBins_f_[i],(int)centBins_i_[k]/2,(int)centBins_f_[k]/2);
            if(coll=="pp") cap = Form("%s_%s_pt%dto%d",ver.Data(),coll.Data(),(int)ptBins_i_[i],(int)ptBins_f_[i]);
            cap+= "_sumIsoScan1to60_den_hoe_sigma";
            cout << cap << endl; 
                
            int Nden_sig = t1->GetEntries(Form("%s && %s && %s",sigMCCut.GetTitle(),hoeCut.GetTitle(),sigmaCut.GetTitle()));
            int Nden_bkg = t2->GetEntries(Form("%s && %s && %s",bkgMCCut.GetTitle(),hoeCut.GetTitle(),sigmaCut.GetTitle()));

            for(Int_t j = 0; j < nSumIso; ++j){ 
                TCut sumIsoCut = Form("pho_sumIsoCorrected < %f", sumIsoBins[j]);
                int Nnum_sig = t1->GetEntries(Form("%s && %s && %s && %s",sigMCCut.GetTitle(),hoeCut.GetTitle(),sigmaCut.GetTitle(),sumIsoCut.GetTitle()));
                int Nnum_bkg = t2->GetEntries(Form("%s && %s && %s && %s",bkgMCCut.GetTitle(),hoeCut.GetTitle(),sigmaCut.GetTitle(),sumIsoCut.GetTitle()));
                
                double eff_sig = (double)Nnum_sig/(double)Nden_sig; 
                double eff_bkg = (double)Nnum_bkg/(double)Nden_bkg; 

                cout << sumIsoCut.GetTitle() ;
                cout << "\t Sig Efficiency = " << Nnum_sig << "/" << Nden_sig << " = " << eff_sig;   
                cout << "\t Bkg Efficiency = " << Nnum_bkg << "/" << Nden_bkg << " = " << eff_bkg << endl;   

                roc[i][k]->SetPointError(j, 0.000001, 0.00001, 0.0000001, 0.000001);
                roc[i][k]->SetPoint(j, eff_sig, 1-eff_bkg);
            }
            c1->cd();
            roc[i][k]->Draw();
            drawText(Form("%s",cap.Data()),0.2,0.2);
            TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/";
            c1->SaveAs(Form("%sfigures/ROC_sumIso_%s.pdf",dir.Data(),cap.Data()));
            delete c1;
        }
    }





    //drawText(cap,0.2,0.2);
    //drawText(cap2,0.2,0.26);
    //if(Nfunc==0) drawText(Form("f(x)=%.2fx+%.2f",f1->GetParameter(1),f1->GetParameter(0)),0.3,0.9);
    //c->SaveAs(Form("%sfigures/compareBKG_%s_%s_%s_function%d.pdf",dir.Data(),var.Data(),cap.Data(),cap2.Data(),Nfunc));
    //TFile* fout = new TFile(Form("%soutput/SigmaIEtaIEta_Iso_nonIso_%s_%s_function%d.root",dir.Data(),cap.Data(),cap2.Data(),Nfunc),"RECREATE");
    //f1->Write();
    //c->Write();
    //h1->Write();
    //h2->Write();
    //fout->Close();
    //delete fout;
    //delete f1;
    //delete c;
    //delete h1;
    //delete h2;
} // main function
