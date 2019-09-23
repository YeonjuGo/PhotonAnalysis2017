// getRawDist_v7.C
// Author: Yeonju Go 
// Modified : 2019 June 26
// Modification : NOT using 30 GeV trigger path(HLT_HISinglePhoton30_Eta1p5_v1) for 30-40 GeV pt bin. 
//              : the other is the same with getRawDist_v5.C 
// 2019June25) unfolding binning (20 GeV to 300 GeV)
// 2019June25) different unfolding binning depending on centrality bin

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
#include "../phoRaaCuts/phoRaaCuts_190625_temp_v29_uncorrectedEt.h"

const TString LABEL = "PbPb #sqrt{s}_{_{NN}}=5.02 TeV";

void getRawDist_v7_test2(TString ver="190625_temp_v29_uncorrectedEt", bool doPreScale=true, bool doSplitPD=true)
{
    cout << "::: version = " << ver << endl;
    cout << "::: doPreScale = " << doPreScale<< endl;
    cout << "::: doSplitPD = " << doSplitPD<< endl;
    cout << "PP skim file : " << ppDatafname << endl;
    cout << "PbPb skim file : " << pbpbDatafname << endl;
    cout << "PP skim file for high pt photons : " << ppDatafname_high << endl;
    cout << "PbPb skim file for high pt photons : " << pbpbDatafname_high << endl;

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
    cout << "set all trees for pp and pbpb" << endl;

    TFile *f2 = TFile::Open(ppDatafname);
    TTree *tpp = (TTree*)f2->Get("EventTree");
    TTree *tpp_hi = (TTree*)f2->Get("HiEvt");
    TTree *tpp_hlt = (TTree*)f2->Get("hltTree");
    TTree *tpp_skim = (TTree*)f2->Get("skim");
    tpp->AddFriend(tpp_hi);
    tpp->AddFriend(tpp_hlt);
    tpp->AddFriend(tpp_skim);
    cout << "set all trees for pp and pbpb" << endl;
    
    TFile *f1_high = TFile::Open(pbpbDatafname_high);
    TTree *tpbpb_high = (TTree*)f1_high->Get("EventTree");
    TTree *tpbpb_hi_high = (TTree*)f1_high->Get("HiEvt");
    TTree *tpbpb_hlt_high = (TTree*)f1_high->Get("hltTree");
    TTree *tpbpb_skim_high = (TTree*)f1_high->Get("skim");
    tpbpb_high->AddFriend(tpbpb_hi_high);
    tpbpb_high->AddFriend(tpbpb_hlt_high);
    tpbpb_high->AddFriend(tpbpb_skim_high);
    cout << "set all trees for pp and pbpb" << endl;

    TFile *f2_high = TFile::Open(ppDatafname_high);
    TTree *tpp_high = (TTree*)f2_high->Get("EventTree");
    TTree *tpp_hi_high = (TTree*)f2_high->Get("HiEvt");
    TTree *tpp_hlt_high = (TTree*)f2_high->Get("hltTree");
    TTree *tpp_skim_high = (TTree*)f2_high->Get("skim");
    tpp_high->AddFriend(tpp_hi_high);
    tpp_high->AddFriend(tpp_hlt_high);
    tpp_high->AddFriend(tpp_skim_high);
    cout << "set all trees for pp and pbpb" << endl;
    
    ////// When doSplitPD = 1 //////
    const int nSplit = 3;
    TCut ptSplitCut[nSplit];
    ptSplitCut[0]  = Form("%s<20",phoEtVar.Data()); 
    ptSplitCut[1]  = Form("%s>=20 && %s<40",phoEtVar.Data(),phoEtVar.Data()); 
    //ptSplitCut[2]  = Form("%s>=30 && %s<40",phoEtVar.Data(),phoEtVar.Data()); 
    ptSplitCut[2] = Form("%s>=40",phoEtVar.Data());
    cout << "set nSplit pt cuts" << endl;

    TH1D* h1D_raw[nCentBin+1];
    TH1D* h1D_rawpp;
    TH1D* h1D_raw_temp[nCentBin+1][nSplit];//0: low PD, 1: high PD
    TH1D* h1D_raw_temp_early[nCentBin+1][nSplit-1]; //only for pbpb low PD // 3 ptbins : 15-20,20-30,30-40 
    TH1D* h1D_raw_temp_late[nCentBin+1][nSplit-1];//only for pbpb low PD // 3 ptbins : 15-20,20-30,30-40
    TH1D* h1D_rawpp_temp[nSplit];//0: low PD, 1: high PD
    TH1D* hdummy[nCentBin+1];
    TH1D* hdummy_pp;
    cout << "defined histograms" << endl;
    
    ////// Define RAW histograms.
    for(int j=0;j<nCentBinIF;j++){
        // rebin ptbins for each centrality bins since we have less bins for peripheral region
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];
        double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
            ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
        }

        hdummy[j] = new TH1D(Form("hdummy_cent%d",j),"hdummy",nPtBin_unfolding_centDep,ptBins_unfolding_centDep); 

        h1D_raw[j] = (TH1D*) hdummy[j]->Clone(Form("h1D_raw_cent%d",j)); 
        if(j==0) h1D_rawpp = (TH1D*) hdummy[j]->Clone(Form("h1D_raw_pp"));
        for(int k=0;k<nSplit-1;++k){
            h1D_raw_temp_early[j][k] = (TH1D*) hdummy[j]->Clone(Form("h1D_raw_cent%d_early_%d",j,k)); 
            h1D_raw_temp_late[j][k] = (TH1D*) hdummy[j]->Clone(Form("h1D_raw_cent%d_late_%d",j,k)); 
        }

        if(doSplitPD){
            for(int i=0;i<nSplit;i++){
                h1D_raw_temp[j][i] = (TH1D*) hdummy[j]->Clone(Form("h1D_raw_cent%d_split%d",j,i)); //early+late
                if(j==0) hdummy_pp = new TH1D(Form("hdummy_pp_split%d",i),"hdummy",nPtBin_unfolding,ptBins_unfolding); 
                if(j==0) h1D_rawpp_temp[i] = (TH1D*) hdummy_pp->Clone(Form("h1D_raw_pp_split%d",i));
            }
        }
    } 
    cout << "set histograms" << endl;

    ////// DRAW RAW DATA for PP 
    TCut trigCut_pp_low_15GeV = "HLT_HISinglePhoton15_Eta1p5_v1";
    if(doSplitPD){
        if(doPreScale){
            tpp->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_rawpp_temp[0]->GetName()), Form("HLT_HISinglePhoton15_Eta1p5_v1_Prescl * L1_SingleEG5_BptxAND_Prescl*(%s && %s && %s && %s)","HLT_HISinglePhoton15_Eta1p5_v1", phoSignalCut_woTrig_pp.GetTitle(), etaCut.GetTitle(), ptSplitCut[0].GetTitle())); 
            cout << "pp 15-20 GeV done"<<endl;
            tpp->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_rawpp_temp[1]->GetName()), Form("HLT_HISinglePhoton20_Eta1p5_v1_Prescl * L1_SingleEG5_BptxAND_Prescl*(%s && %s && %s && (%s))",trigCut_pp_low.GetTitle(), phoSignalCut_woTrig_pp.GetTitle(), etaCut.GetTitle(), ptSplitCut[1].GetTitle())); 
            cout << "pp 20-40 GeV done"<<endl;
            tpp_high->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_rawpp_temp[2]->GetName()), Form("(%s && %s && %s && %s)", trigCut_pp_high.GetTitle(), phoSignalCut_woTrig_pp.GetTitle(), etaCut.GetTitle(), ptSplitCut[2].GetTitle())); 
            cout << "pp over 40 GeV done"<<endl;
        } else{
            tpp->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_rawpp_temp[0]->GetName()), trigCut_pp_low_15GeV && phoSignalCut_woTrig_pp && etaCut && ptSplitCut[0]); 
            tpp->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_rawpp_temp[1]->GetName()), trigCut_pp_low && phoSignalCut_woTrig_pp && etaCut && ptSplitCut[1]); 
            //tpp->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_rawpp_temp[2]->GetName()), trigCut_pp_low && phoSignalCut_woTrig_pp && etaCut && ptSplitCut[2]); 
            tpp_high->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_rawpp_temp[2]->GetName()), trigCut_pp_high && phoSignalCut_woTrig_pp && etaCut && ptSplitCut[2]); 
        }
    } else {
        if(doPreScale){
            tpp->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_rawpp->GetName()), Form("HLT_HISinglePhoton15_Eta1p5_v1_Prescl*L1_SingleEG5_BptxAND_Prescl*(%s && %s && %s)", trigCut_pp_low.GetTitle(), phoSignalCut_woTrig_pp.GetTitle(), etaCut.GetTitle())); 
        }else{
            tpp->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_rawpp->GetName()), trigCut_pp_low && phoSignalCut_woTrig_pp && etaCut); 
        }
    }

    //Add up all different pt range spectra  
    if(doSplitPD){
        for(int i=0;i<nSplit;i++) h1D_rawpp->Add(h1D_rawpp_temp[i]); 
    }
    // Print the number of photons bin by bin  
    for(int ipt=0;ipt<nPtBin_unfolding;++ipt){
        double vRaw = h1D_rawpp->GetBinContent(ipt+1);
        cout <<"pp collision : " << ptBins_unfolding[ipt] << "<pt<"<< ptBins_unfolding[ipt+1]<<" :: \traw=\t" << vRaw << endl;
    }
    
    ////// DRAW RAW DATA for PbPb
    for(int j=0;j<nCentBinIF;j++){
        TCut centCut;
        centCut = Form("hiBin>=%d && hiBin < %d",centBins_i[j],centBins_f[j]);
        cout << centCut.GetTitle() << endl; 
        if(doSplitPD){
            if(doPreScale){
                tpbpb->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw_temp_early[j][0]->GetName()), Form("HLT_HISinglePhoton15_Eta1p5_v1_Prescl*L1_MinimumBiasHF1_AND_Prescl*(L1_MinimumBiasHF1_AND_Prescl<99 && L1_MinimumBiasHF1_AND_Prescl>0 && HLT_HISinglePhoton15_Eta1p5_v1 && (run >=262620 && run <=263035) && %s && %s && %s && %s)", phoSignalCut_woTrig.GetTitle(), centCut.GetTitle(), etaCut.GetTitle(), ptSplitCut[0].GetTitle()));
                cout << "pbpb early 15-20 GeV done" << endl;
                tpbpb->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw_temp_early[j][1]->GetName()), Form("HLT_HISinglePhoton20_Eta1p5_v1_Prescl*L1_MinimumBiasHF1_AND_Prescl*(L1_MinimumBiasHF1_AND_Prescl<99 && L1_MinimumBiasHF1_AND_Prescl>0 && HLT_HISinglePhoton20_Eta1p5_v1 && (run >=262620 && run <=263035) && %s && %s && %s && %s)", phoSignalCut_woTrig.GetTitle(), centCut.GetTitle(), etaCut.GetTitle(), ptSplitCut[1].GetTitle()));
                cout << "pbpb early 20-40 GeV done" << endl;
                tpbpb->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw_temp_late[j][0]->GetName()), Form("HLT_HISinglePhoton15_Eta1p5_v2_Prescl*L1_MinimumBiasHF2_AND_Prescl*(L1_MinimumBiasHF2_AND_Prescl<99 && L1_MinimumBiasHF2_AND_Prescl>0 && HLT_HISinglePhoton15_Eta1p5_v2 && (run >= 263233 && run <= 263614) && %s && %s && %s && %s)", phoSignalCut_woTrig.GetTitle(), centCut.GetTitle(), etaCut.GetTitle(), ptSplitCut[0].GetTitle()));
                cout << "pbpb late 15-20 GeV done" << endl;
                tpbpb->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw_temp_late[j][1]->GetName()), Form("HLT_HISinglePhoton20_Eta1p5_v2_Prescl*L1_MinimumBiasHF2_AND_Prescl*(L1_MinimumBiasHF2_AND_Prescl<99 && L1_MinimumBiasHF2_AND_Prescl>0 && HLT_HISinglePhoton20_Eta1p5_v2 && (run >= 263233 && run <= 263614) && %s && %s && %s && %s)", phoSignalCut_woTrig.GetTitle(), centCut.GetTitle(), etaCut.GetTitle(), ptSplitCut[1].GetTitle()));
                cout << "pbpb late 20-40 GeV done" << endl;
                tpbpb_high->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw_temp[j][1]->GetName()), Form("(%s && %s && %s && %s && %s)", trigCut_high.GetTitle(), phoSignalCut_woTrig.GetTitle(), centCut.GetTitle(), etaCut.GetTitle(), ptSplitCut[2].GetTitle()));
                cout << "pbpb late over 40 GeV done" << endl;
            } else{
                tpbpb->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw_temp[j][0]->GetName()), trigCut_low && phoSignalCut_woTrig && centCut && etaCut && ptSplitCut[0]);
                tpbpb_high->Draw(Form("%s>>+%s",phoEtVar.Data(),h1D_raw_temp[j][1]->GetName()), trigCut_high && phoSignalCut_woTrig && centCut && etaCut && ptSplitCut[1]);
            }
        } else{
            if(doPreScale){
                tpbpb->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw_temp_early[j][0]->GetName()), Form("HLT_HISinglePhoton15_Eta1p5_v1_Prescl * L1_MinimumBiasHF1_AND_Prescl*(L1_MinimumBiasHF1_AND_Prescl<99 && L1_MinimumBiasHF1_AND_Prescl>0 && HLT_HISinglePhoton15_Eta1p5_v1 && (run >=262620 && run <=263035) && %s && %s && %s)", phoSignalCut_woTrig.GetTitle(), centCut.GetTitle(), etaCut.GetTitle()));
                tpbpb->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw_temp_late[j][0]->GetName()), Form("HLT_HISinglePhoton15_Eta1p5_v2_Prescl * L1_MinimumBiasHF2_AND_Prescl*(L1_MinimumBiasHF2_AND_Prescl<99 && L1_MinimumBiasHF2_AND_Prescl>0 && HLT_HISinglePhoton15_Eta1p5_v2 &&  (run >=263233 && run <=263614) && %s && %s && %s)", phoSignalCut_woTrig.GetTitle(), centCut.GetTitle(), etaCut.GetTitle()));
            }else {
                tpbpb->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw[j]->GetName()), trigCut_low && phoSignalCut_woTrig && centCut && etaCut);
            }
        }

    }
    
    if(!doPreScale) cout << "This is without prescale correction to count the real signal photons" << endl; 
    else cout << "This is with prescale correction" << endl; 


    ////// when doSplitPD =1 ///////
    if(doPreScale){
        for(int j=0;j<nCentBinIF;j++){
            if(doSplitPD){
                h1D_raw_temp[j][0]->Add(h1D_raw_temp_early[j][0]);//low PD, early run, 15 to 20GeV
                h1D_raw_temp[j][0]->Add(h1D_raw_temp_early[j][1]);//low PD, early run, 20 to 40GeV
                //h1D_raw_temp[j][0]->Add(h1D_raw_temp_early[j][2]);//low PD, early run, 30 to 40GeV
                h1D_raw_temp[j][0]->Add(h1D_raw_temp_late[j][0]);//low PD, late run, 15 to 20GeV
                h1D_raw_temp[j][0]->Add(h1D_raw_temp_late[j][1]);//low PD, late run, 20 to 40GeV
                //h1D_raw_temp[j][0]->Add(h1D_raw_temp_late[j][2]);//low PD, late run, 30 to 40GeV
            } else{
                h1D_raw[j]->Add(h1D_raw_temp_early[j][0]);
                h1D_raw[j]->Add(h1D_raw_temp_late[j][0]);
            }
        }
    }

    if(doSplitPD){
        for(int j=0;j<nCentBinIF;j++){
            h1D_raw[j]->Add(h1D_raw_temp[j][0]);
            h1D_raw[j]->Add(h1D_raw_temp[j][1]);
        }
    }

    for(int j=0;j<nCentBinIF;j++){
        if(j==nPtBin_unfolding-rejectPtBins[j]) continue;
        for(int ipt=0;ipt<nPtBin_unfolding;++ipt){
            Double_t vRaw;
            vRaw = h1D_raw[j]->GetBinContent(ipt+1);
            cout << centBins_i[j]/2<<"%-"<<centBins_f[j]/2<<"% : " << ptBins_unfolding[ipt] << "<pt<"<< ptBins_unfolding[ipt+1]<<" :: \traw=\t" << vRaw << endl;
        }
    }
   
    // Save Raw dist in output file 
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/";  
    TString cap = "";
    if(doSplitPD) cap+="_splitPD";
    TFile* outf = new TFile(Form("%soutput/rawDist_%s%s.root",dir.Data(),ver.Data(),cap.Data()),"recreate");
    outf->cd();
    h1D_rawpp->Write();
    if(doSplitPD){
        h1D_rawpp_temp[0]->Write();
        h1D_rawpp_temp[1]->Write();
        h1D_rawpp_temp[2]->Write();
    }
    for(int j=0;j<nCentBinIF;j++){
        h1D_raw[j]->Write();
        if(doSplitPD){
            h1D_raw_temp[j][0]->Write();
            h1D_raw_temp[j][1]->Write();
        }
    }
}
