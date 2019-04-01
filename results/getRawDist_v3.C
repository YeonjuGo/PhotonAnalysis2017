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
//#include "../ElectroWeak-Jet-Track-Analyses/Histogramming/PhotonPurity.h"
#include "../ElectroWeak-Jet-Track-Analyses/Utilities/interface/CutConfigurationParser.h"
#include "../ElectroWeak-Jet-Track-Analyses/TreeHeaders/CutConfigurationTree.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"

const TString LABEL = "PbPb #sqrt{s}_{_{NN}}=5.02 TeV";
TH1D* reBinS(TH1D* h1=0);

//void getRawDist_v3(TString ver="180805_temp_v21_sys_sumIso", bool doPreScale=true, bool doSplitPD=true)
void getRawDist_v3(TString ver="180805_temp_v21_noEnergyCorr", bool doPreScale=true, bool doSplitPD=true)
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

    TH1D* h1D_raw[nCentBin+1];
    TH1D* h1D_rawpp;
    TH1D* h1D_raw_temp[nCentBin+1][2];//0: low, 1: high
    TH1D* h1D_raw_temp_early[nCentBin+1]; //only for pbpb low
    TH1D* h1D_raw_temp_late[nCentBin+1];//only for pbpb low
    TH1D* h1D_rawpp_temp[2];//0: low, 1: high
    TH1D* hdummy = new TH1D("hdummy","hdummy",nPtBin,ptBins); 
    
    ////// When doSplitPD = 1 //////
    TCut ptSplitCut[2];
    ptSplitCut[0]  = Form("%s<40",phoEtVar.Data()); 
    ptSplitCut[1] = Form("%s>=40",phoEtVar.Data());

    ////// Define RAW histograms.
    for(int j=0;j<nCentBinIF;j++){
        h1D_raw[j] = (TH1D*) hdummy->Clone(Form("h1D_raw_cent%d",j)); 
        if(j==0) h1D_rawpp = (TH1D*) hdummy->Clone(Form("h1D_raw_pp"));
                h1D_raw_temp_early[j] = (TH1D*) hdummy->Clone(Form("h1D_raw_cent%d_early",j)); 
                h1D_raw_temp_late[j] = (TH1D*) hdummy->Clone(Form("h1D_raw_cent%d_late",j)); 
        
        if(doSplitPD){
            for(int i=0;i<2;i++){
                h1D_raw_temp[j][i] = (TH1D*) hdummy->Clone(Form("h1D_raw_cent%d_split%d",j,i)); 
                if(j==0) h1D_rawpp_temp[i] = (TH1D*) hdummy->Clone(Form("h1D_raw_pp_split%d",i));
            }
        }
    } 

    ////// DRAW RAW DATA for PP 
    if(doSplitPD){
        if(doPreScale){
            //tpp->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_rawpp_temp[0]->GetName()), Form("HLT_HISinglePhoton20_Eta1p5_v1_Prescl*(%s && %s && %s && %s)",trigCut_pp_low.GetTitle(), phoSignalCut_woTrig_pp.GetTitle(), etaCut.GetTitle(), ptSplitCut[0].GetTitle())); 
            tpp->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_rawpp_temp[0]->GetName()), Form("HLT_HISinglePhoton20_Eta1p5_v1_Prescl * L1_SingleEG5_BptxAND_Prescl*(%s && %s && %s && %s)",trigCut_pp_low.GetTitle(), phoSignalCut_woTrig_pp.GetTitle(), etaCut.GetTitle(), ptSplitCut[0].GetTitle())); 
            tpp_high->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_rawpp_temp[1]->GetName()), Form("(%s && %s && %s && %s)", trigCut_pp_high.GetTitle(), phoSignalCut_woTrig_pp.GetTitle(), etaCut.GetTitle(), ptSplitCut[1].GetTitle())); 
            //tpp->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_rawpp_temp[0]->GetName()), Form("phoPreScale*(%s && %s && %s && %s)",trigCut_pp_low.GetTitle(), phoSignalCut_woTrig_pp.GetTitle(), etaCut.GetTitle(), ptSplitCut[0].GetTitle())); 
            //tpp_high->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_rawpp_temp[1]->GetName()), Form("phoPreScale*(%s && %s && %s && %s)", trigCut_pp_high.GetTitle(), phoSignalCut_woTrig_pp.GetTitle(), etaCut.GetTitle(), ptSplitCut[1].GetTitle())); 
        } else{
            tpp->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_rawpp_temp[0]->GetName()), trigCut_pp_low && phoSignalCut_woTrig_pp && etaCut && ptSplitCut[0]); 
            tpp_high->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_rawpp_temp[1]->GetName()), trigCut_pp_high && phoSignalCut_woTrig_pp && etaCut && ptSplitCut[1]); 
        }
    } else {
        if(doPreScale){
            tpp->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_rawpp->GetName()), Form("HLT_HISinglePhoton20_Eta1p5_v1_Prescl*L1_SingleEG5_BptxAND_Prescl*(%s && %s && %s)", trigCut_pp_low.GetTitle(), phoSignalCut_woTrig_pp.GetTitle(), etaCut.GetTitle())); 
            //tpp->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_rawpp->GetName()), Form("phoPreScale*(%s && %s && %s)", trigCut_pp_low.GetTitle(), phoSignalCut_woTrig_pp.GetTitle(), etaCut.GetTitle())); 
        }else{
            tpp->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_rawpp->GetName()), trigCut_pp_low && phoSignalCut_woTrig_pp && etaCut); 
        }
    }
    

    if(doSplitPD){
        h1D_rawpp->Add(h1D_rawpp_temp[0]); 
        h1D_rawpp->Add(h1D_rawpp_temp[1]); 
    }
    // Print the number of photons bin by bin  
    for(int ipt=0;ipt<nPtBin;++ipt){
        double vRaw = h1D_rawpp->GetBinContent(ipt+1);
        cout <<"pp collision : " << ptBins[ipt] << "<pt<"<< ptBins[ipt+1]<<" :: \traw=\t" << vRaw << endl;
    }
    
    ////// DRAW RAW DATA for PbPb
    for(int j=0;j<nCentBinIF;j++){
        TCut centCut;
        centCut = Form("hiBin>=%d && hiBin < %d",centBins_i[j],centBins_f[j]);
        cout << centCut.GetTitle() << endl; 
        if(doSplitPD){
            if(doPreScale){
                
                //tpbpb->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw_temp_early[j]->GetName()), Form("HLT_HISinglePhoton20_Eta1p5_v1_Prescl*(HLT_HISinglePhoton20_Eta1p5_v1 && (run >=262620 && run <=263035) && %s && %s && %s && %s)", phoSignalCut_woTrig.GetTitle(), centCut.GetTitle(), etaCut.GetTitle(), ptSplitCut[0].GetTitle()));
                //tpbpb->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw_temp_late[j]->GetName()), Form("HLT_HISinglePhoton20_Eta1p5_v2_Prescl*(HLT_HISinglePhoton20_Eta1p5_v2 && (run >= 263233 && run <= 263614) && %s && %s && %s && %s)", phoSignalCut_woTrig.GetTitle(), centCut.GetTitle(), etaCut.GetTitle(), ptSplitCut[0].GetTitle()));
                tpbpb->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw_temp_early[j]->GetName()), Form("HLT_HISinglePhoton20_Eta1p5_v1_Prescl * L1_MinimumBiasHF1_AND_Prescl*(L1_MinimumBiasHF1_AND_Prescl<99 && HLT_HISinglePhoton20_Eta1p5_v1 && (run >=262620 && run <=263035) && %s && %s && %s && %s)", phoSignalCut_woTrig.GetTitle(), centCut.GetTitle(), etaCut.GetTitle(), ptSplitCut[0].GetTitle()));
                tpbpb->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw_temp_late[j]->GetName()), Form("HLT_HISinglePhoton20_Eta1p5_v2_Prescl * L1_MinimumBiasHF2_AND_Prescl*(L1_MinimumBiasHF2_AND_Prescl<99 && HLT_HISinglePhoton20_Eta1p5_v2 && (run >= 263233 && run <= 263614) && %s && %s && %s && %s)", phoSignalCut_woTrig.GetTitle(), centCut.GetTitle(), etaCut.GetTitle(), ptSplitCut[0].GetTitle()));
                
                tpbpb_high->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw_temp[j][1]->GetName()), Form("(%s && %s && %s && %s && %s)", trigCut_high.GetTitle(), phoSignalCut_woTrig.GetTitle(), centCut.GetTitle(), etaCut.GetTitle(), ptSplitCut[1].GetTitle()));
                //tpbpb->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw_temp[j][0]->GetName()), Form("phoPreScale*(%s && %s && %s && %s && %s)", trigCut_low.GetTitle(), phoSignalCut_woTrig.GetTitle(), centCut.GetTitle(), etaCut.GetTitle(), ptSplitCut[0].GetTitle()));
                //tpbpb_high->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw_temp[j][1]->GetName()), Form("phoPreScale*(%s && %s && %s && %s && %s)", trigCut_high.GetTitle(), phoSignalCut_woTrig.GetTitle(), centCut.GetTitle(), etaCut.GetTitle(), ptSplitCut[1].GetTitle()));
            } else{
                tpbpb->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw_temp[j][0]->GetName()), trigCut_low && phoSignalCut_woTrig && centCut && etaCut && ptSplitCut[0]);
                tpbpb_high->Draw(Form("%s>>+%s",phoEtVar.Data(),h1D_raw_temp[j][1]->GetName()), trigCut_high && phoSignalCut_woTrig && centCut && etaCut && ptSplitCut[1]);
            }
        } else{
            if(doPreScale){
                //tpbpb->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw_temp_early[j]->GetName()), Form("HLT_HISinglePhoton20_Eta1p5_v1_Prescl*(HLT_HISinglePhoton20_Eta1p5_v1 && (run >=262620 && run <=263035) && %s && %s && %s)", phoSignalCut_woTrig.GetTitle(), centCut.GetTitle(), etaCut.GetTitle()));
                //tpbpb->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw_temp_late[j]->GetName()), Form("HLT_HISinglePhoton20_Eta1p5_v2_Prescl*(HLT_HISinglePhoton20_Eta1p5_v2 &&  (run >=263233 && run <=263614) && %s && %s && %s)", phoSignalCut_woTrig.GetTitle(), centCut.GetTitle(), etaCut.GetTitle()));
                tpbpb->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw_temp_early[j]->GetName()), Form("HLT_HISinglePhoton20_Eta1p5_v1_Prescl * L1_MinimumBiasHF1_AND_Prescl*(L1_MinimumBiasHF1_AND_Prescl<99 && HLT_HISinglePhoton20_Eta1p5_v1 && (run >=262620 && run <=263035) && %s && %s && %s)", phoSignalCut_woTrig.GetTitle(), centCut.GetTitle(), etaCut.GetTitle()));
                tpbpb->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw_temp_late[j]->GetName()), Form("HLT_HISinglePhoton20_Eta1p5_v2_Prescl * L1_MinimumBiasHF2_AND_Prescl*(L1_MinimumBiasHF2_AND_Prescl<99 && HLT_HISinglePhoton20_Eta1p5_v2 &&  (run >=263233 && run <=263614) && %s && %s && %s)", phoSignalCut_woTrig.GetTitle(), centCut.GetTitle(), etaCut.GetTitle()));
                //tpbpb->Draw(Form("%s>>%s",phoEtVar.Data(),h1D_raw[j]->GetName()), Form("phoPreScale*(%s && %s && %s && %s)",trigCut_low.GetTitle(), phoSignalCut_woTrig.GetTitle(), centCut.GetTitle(), etaCut.GetTitle()));
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
                h1D_raw_temp[j][0]->Add(h1D_raw_temp_early[j]);
                h1D_raw_temp[j][0]->Add(h1D_raw_temp_late[j]);
            } else{
                h1D_raw[j]->Add(h1D_raw_temp_early[j]);
                h1D_raw[j]->Add(h1D_raw_temp_late[j]);
            }
        }
    }

    if(doSplitPD){
        for(int j=0;j<nCentBinIF;j++){
            h1D_raw[j]->Add(h1D_raw_temp[j][0]);
            h1D_raw[j]->Add(h1D_raw_temp[j][1]);
        }
       // h1D_rawpp->Add(h1D_rawpp_temp[0]); 
       // h1D_rawpp->Add(h1D_rawpp_temp[1]); 
    }

    // Print the number of photons bin by bin  
    
   // for(int ipt=0;ipt<nPtBin;++ipt){
   //     double vRaw = h1D_rawpp->GetBinContent(ipt+1);
   //     cout <<"pp collision : " << ptBins[ipt] << "<pt<"<< ptBins[ipt+1]<<" :: \traw=\t" << vRaw << endl;
   // }

    for(int j=0;j<nCentBinIF;j++)
    {
        for(int ipt=0;ipt<nPtBin;++ipt){
            Double_t vRaw;
            vRaw = h1D_raw[j]->GetBinContent(ipt+1);
            cout << centBins_i[j]/2<<"%-"<<centBins_f[j]/2<<"% : " << ptBins[ipt] << "<pt<"<< ptBins[ipt+1]<<" :: \traw=\t" << vRaw << endl;
        }
    }
   
    // Save Raw dist in output file 
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/";  
    TString cap = "";
    if(doSplitPD) cap+="_splitPD";
    TFile* outf = new TFile(Form("%soutput/rawDist_%s%s.root",dir.Data(),ver.Data(),cap.Data()),"recreate");
    outf->cd();
    for(int j=0;j<nCentBinIF;j++){
        h1D_raw[j]->Write();
        if(doSplitPD){
            h1D_raw_temp[j][0]->Write();
            h1D_raw_temp[j][1]->Write();
        }
    }
    h1D_rawpp->Write();
    if(doSplitPD){
        h1D_rawpp_temp[0]->Write();
        h1D_rawpp_temp[1]->Write();
    }
}
