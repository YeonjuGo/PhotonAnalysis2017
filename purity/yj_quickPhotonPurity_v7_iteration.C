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

#include "PhotonPurity_sigSub_iteration.h"
//#include "../phoRaaCuts/phoRaaCuts_purity_forPaper.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
#include "../ElectroWeak-Jet-Track-Analyses/Utilities/interface/CutConfigurationParser.h"
#include "../ElectroWeak-Jet-Track-Analyses/Utilities/interface/InputConfigurationParser.h"
#include "../ElectroWeak-Jet-Track-Analyses/Plotting/commonUtility.h"

int yj_quickPhotonPurity_v7_iteration(const TString coll="pp", const TString ver="phoRaaCuts_purity_forPaper", bool doSplitPD=true, bool doPreScale=0, bool useSBcorr=0, bool centDepCorr=0, int ptDepCorrThr=0, int Nfunc=0, bool useMCSB=0, bool use30trig=0){
    cout << "Purity Calculation using yj_quickPhotonPurity_v7_iteration.C" << endl;
    cout << "::: version = " << ver << endl; 
    cout << "::: doSplitPD = " << doSplitPD << endl; 
    cout << "::: doPreScale = " << doPreScale << endl; 
    cout << "::: useSBcorr = " << useSBcorr << endl; 
    cout << "::: centDepCorr = " << centDepCorr << endl; 
    cout << "::: ptDepCorrThr = " << ptDepCorrThr << endl; 
    cout << "::: Nfunc = " << Nfunc << endl; 
    cout << "::: useMCSB = " << useMCSB << endl; 
    cout << "::: use30trig = " << use30trig << endl; 
    gStyle->SetOptStat(0);
    TH1::SetDefaultSumw2();

    TString configFile=""; 
    TString inputData=""; 
    TString inputData_high=""; 
    TString inputMC=""; 
    TString inputBkgMC ="";
    TString outputName=Form("purity_%s_%s",coll.Data(),ver.Data());
    if(doSplitPD) outputName+="_splitPD";
    if(!doPreScale) outputName+="_noPreScale";
    if(useMCSB) outputName+="_bkgMC";
    //if(useSBcorr) outputName+="_SBcorr";
    //if(noCentDepCorr) outputName+="_noCentDepCorr";
    if(coll=="pbpb"){
        configFile = pbpbData_config;
        inputData = pbpbDatafname;
        inputData_high = pbpbDatafname_high;
        inputMC = pbpbMCfname;
        inputBkgMC = pbpbMCEmEnrfname; 
    } else if(coll=="pp"){
        configFile = ppData_config;
        inputData = ppDatafname;
        inputData_high = ppDatafname_high;
        inputMC = ppMCfname;
        inputBkgMC = ppMCEmEnrfname; 
    } else {
        std::cout << "Invaild collision type : " << coll << std::endl;
        return 1;
    }


    const InputConfiguration configInput = InputConfigurationParser::Parse(configFile.Data());
    CutConfiguration configCuts = CutConfigurationParser::Parse(configFile.Data());
    if (!configCuts.isValid) {
        std::cout << "Invalid configfile, terminating." << std::endl;
        return 1;
    }

    //0:HI 1:HIMC 2:PP 3:PPMC
    // const int collisionType = configInput.proc[INPUT::kSKIM].i[INPUT::k_collisionType];
    // const TString collisionTypeName = getCollisionTypeName((COLL::TYPE)collisionType).c_str();
    TString LABEL = "PbPb Data";
    if(coll=="pp") LABEL = "pp Data";

    cout << "collisionTypeName = " << coll << endl;
    //cout << "collisionType = " << collisionType << ", collisionTypeName = " << collisionTypeName << endl;

    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1;

    // std::string trigger = configCuts.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].s[CUTS::PHO::k_trigger_gammaJet].c_str();
    TFile* input = TFile::Open(inputData);
    TTree* tHlt = (TTree*)input->Get("hltTree");
    TTree* tPho = (TTree*)input->Get("EventTree");    // photons
    TTree* tHiEvt = (TTree*)input->Get("HiEvt");       // HiEvt tree will be placed in PP forest as well.
    TTree* tSkim = (TTree*)input->Get("skim");       // HiEvt tree will be placed in PP forest as well.

    TFile* input_high = TFile::Open(inputData_high);
    TTree* tHlt_high = (TTree*)input_high->Get("hltTree");
    TTree* tPho_high = (TTree*)input_high->Get("EventTree");    // photons
    TTree* tHiEvt_high = (TTree*)input_high->Get("HiEvt");       // HiEvt tree will be placed in PP forest as well.
    TTree* tSkim_high = (TTree*)input_high->Get("skim");       // HiEvt tree will be placed in PP forest as well.

    TFile* inputMCFile = TFile::Open(inputMC);
    TTree* tmcHlt = (TTree*)inputMCFile->Get("hltTree");
    TTree* tmcPho = (TTree*)inputMCFile->Get("EventTree");    // photons
    TTree* tmcHiEvt = (TTree*)inputMCFile->Get("HiEvt");       // HiEvt tree will be placed in PP forest as well
    TTree* tmcSkim = (TTree*)inputMCFile->Get("skim");       // HiEvt tree will be placed in PP forest as well

    tPho->AddFriend(tHlt, "Hlt");
    tPho->AddFriend(tPho, "Pho");
    tPho->AddFriend(tHiEvt, "HiEvt");
    tPho->AddFriend(tSkim, "skim");

    tPho_high->AddFriend(tHlt_high, "Hlt");
    tPho_high->AddFriend(tPho_high, "Pho");
    tPho_high->AddFriend(tHiEvt_high, "HiEvt");
    tPho_high->AddFriend(tSkim_high, "skim");

    tmcPho->AddFriend(tmcHlt, "Hlt");
    tmcPho->AddFriend(tmcPho, "Pho");
    tmcPho->AddFriend(tmcHiEvt, "HiEvt");
    tmcPho->AddFriend(tmcSkim, "skim");

    TFile* inputBkgMCFile = TFile::Open(inputBkgMC);
    TTree* tmcBkgHlt = (TTree*)inputBkgMCFile->Get("hltTree");
    TTree* tmcBkgPho = (TTree*)inputBkgMCFile->Get("EventTree");    // photons
    TTree* tmcBkgHiEvt = (TTree*)inputBkgMCFile->Get("HiEvt");       // HiEvt tree will be placed in PP forest as well
    TTree* tmcBkgSkim = (TTree*)inputBkgMCFile->Get("skim");       // HiEvt tree will be placed in PP forest as well
    tmcBkgPho->AddFriend(tmcBkgHlt, "Hlt");
    tmcBkgPho->AddFriend(tmcBkgPho, "Pho");
    tmcBkgPho->AddFriend(tmcBkgHiEvt, "HiEvt");
    tmcBkgPho->AddFriend(tmcBkgSkim, "skim");

    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/purity/";
    TFile* outFile = new TFile(Form("%soutput/%s.root",dir.Data(), outputName.Data()), "RECREATE");
   
    /////////////////////////////////////////
    //Text File 
    ofstream outTxtFile(Form("%stxt/purity_%s_LastBinsMerged.txt",dir.Data(), outputName.Data()), ios::app);
    outTxtFile << "cent_i" << "\t" << "cent_f" << "\t" << "pT_i" << "\t" << "pT_f" << "\t" << "Purity" << "\t" << "PurityErr"  << endl;

    //outTxtFile << run << "\t" << setprecision(4) <<eff*100 << "\t" << chi2s[ibest] << endl;
    //outTxtFile.close();

    TH1D* h1D_pur[nCENTBINS];
    TH1D* htemp = new TH1D(Form("htemp%d",1),";#sigma_{#eta#eta};Entries",100,0.001,0.024);
    for (Int_t j = 0; j < nCENTBINS; j++) {
        // rebin ptbins for each centrality bins since we have less bins for peripheral region
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];
        double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
            ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
        }
        if(coll=="pp") h1D_pur[j] = new TH1D("h1D_purity_pp",";p_{T}^#gamma (GeV);",nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
        else h1D_pur[j] = new TH1D(Form("h1D_purity_cent%d",j),";p_{T}^#gamma (GeV);",nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
    }

    cout << "nPtBin_unfolding = " << nPtBin_unfolding << " , nCentBins = " << nCENTBINS << endl;
    TCanvas* cPurity;
    if(coll=="pbpb"){
        cPurity = new TCanvas("c1", "c1", 300*(nPtBin_unfolding-1), 300*(nCENTBINS-1));
        makeMultiPanelCanvas(cPurity,(nPtBin_unfolding-1) , nCENTBINS-1, 0.0, 0.0 , 0.2, 0.15, 0.005);
    } else if(coll=="pp"){
        cPurity = new TCanvas("c1", "c1", 300*(nPtBin_unfolding-1), 300);
        makeMultiPanelCanvas(cPurity,(nPtBin_unfolding-1), 1, 0.0, 0.0 , 0.2, 0.15, 0.005);
    }
    TCanvas* cPurity_each[nCENTBINS][nPtBin_unfolding];

    for (Int_t j = 0; j < nCENTBINS; ++j) {
        if(coll=="pbpb" && j==0) continue;
        // rebin ptbins for each centrality bins since we have less bins for peripheral region
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];
        double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
            ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
        }

        cout << "START_CENTBIN_" << centBins_i[j] << "_to_" << centBins_f[j] << endl;
        for (Int_t i = 0; i < nPtBin_unfolding_centDep-1; ++i) {
            for (Int_t k = 0; k < 1; ++k) {
                TString ptCut_ = Form("(%s>= %f) && (%s< %f)",
                        phoEtVar.Data(), ptBins_unfolding[i], phoEtVar.Data(), ptBins_unfolding[i+1]);
                if(i==nPtBin_unfolding_centDep-2){
                    ptCut_ = Form("(%s>= %f) && (%s< %f)",
                        phoEtVar.Data(), ptBins_unfolding[i], phoEtVar.Data(), ptBins_unfolding[i+2]);
                } 

                TString centCut = Form("(hiBin>=%i) && (hiBin<%i)",
                        centBins_i[j], centBins_f[j]);
                if(coll=="pp") centCut = "hiBin<10000";
                //TCut sampleIsolation = "(pho_sumIsoCorrected < (16.7202-0.154349*hiBin+0.00040613*hiBin*hiBin)) && phoHoverE<0.1"; //for PbPb
                TCut trigCut_ = "1==0"; 
                TCut preScaleLabel = "phoPreScale";
                TCut preScaleCut = "";
                if(doSplitPD){
                    if(ptBins_unfolding[i]>=40){ // high pt
                        if(coll=="pp"){ 
                            trigCut_ = trigCut_pp_high;
                            preScaleLabel = "1";
                            preScaleCut = "1"; 
                        } else if(coll=="pbpb"){ 
                            trigCut_ = trigCut_high;
                            preScaleLabel = "1";
                            preScaleCut = "1"; 
                        } else{ cout << "[ERROR] : There is no this kind of collision" << endl; }
                    } else if(ptBins_unfolding[i]>=30 && ptBins_unfolding[i]<40){ // 30-40 GeV, lower pt 
                        if(coll=="pp"){// pp use 20 GeV trigger for 30-40 GeV bin because 20 GeV trigger's prescale is 1 
                            trigCut_ = trigCut_pp_low; 
                            preScaleLabel = "HLT_HISinglePhoton20_Eta1p5_v1_Prescl * L1_SingleEG5_BptxAND_Prescl";
                            preScaleCut = "1"; 
                        } else if(coll=="pbpb"){// there's no v2 trigger for 30GeV (no different trigger name during whole run)
                            if(use30trig){
                                trigCut_ = "HLT_HISinglePhoton30_Eta1p5_v1"; 
                                preScaleLabel = "HLT_HISinglePhoton30_Eta1p5_v1_Prescl * L1_SingleEG7_BptxAND_Prescl";
                                preScaleCut = "L1_SingleEG7_BptxAND_Prescl>=0 && L1_SingleEG7_BptxAND_Prescl<99"; 
                            } else{
                                trigCut_ = trigCut_low; 
                                preScaleLabel = "phoPreScale";
                                preScaleCut = "1";
                            }
                        } else{ cout << "[ERROR] : There is no this kind of collision" << endl; }
                    } else if(ptBins_unfolding[i]>=20 && ptBins_unfolding[i]<30){ // 20-30 GeV, lower pt 
                        if(coll=="pp"){ 
                            trigCut_ = trigCut_pp_low; 
                            preScaleLabel = "HLT_HISinglePhoton20_Eta1p5_v1_Prescl * L1_SingleEG5_BptxAND_Prescl";
                            preScaleCut = "1"; 
                        } else if(coll=="pbpb"){ 
                            trigCut_ = trigCut_low; 
                            preScaleLabel = "phoPreScale";
                            preScaleCut = "1";
                            //preScaleLabel = "HLT_HISinglePhoton20_Eta1p5_v1_Prescl * L1_SingleEG5_BptxAND_Prescl";
                            //preScaleCut = "(run >= 263233 && run <= 263614) && L1_MinimumBiasHF2_AND_Prescl<99"; 
                        } else{ cout << "[ERROR] : There is no this kind of collision" << endl; }
                    } else{ // 15 to 20 GeV
                        if(coll=="pp"){ 
                            trigCut_ = "HLT_HISinglePhoton15_Eta1p5_v1"; 
                            preScaleLabel = "HLT_HISinglePhoton15_Eta1p5_v1_Prescl * L1_SingleEG5_BptxAND_Prescl";
                            preScaleCut = "1"; 
                        } else if(coll=="pbpb"){ 
                            trigCut_ = "HLT_HISinglePhoton15_Eta1p5_v1 || HLT_HISinglePhoton15_Eta1p5_v2"; 
                            preScaleLabel = "phoPreScale";
                            preScaleCut = "1";
                            //trigCut_ = "HLT_HISinglePhoton15_Eta1p5_v2"; 
                            //preScaleLabel = "HLT_HISinglePhoton15_Eta1p5_v2_Prescl * L1_MinimumBiasHF2_AND_Prescl";
                            //preScaleCut = "(run >= 263233 && run <= 263614) && L1_MinimumBiasHF2_AND_Prescl>=0 && L1_MinimumBiasHF2_AND_Prescl<99"; 
                        } else{ cout << "[ERROR] : There is no this kind of collision" << endl; }
                    }
                } else{
                    if(coll=="pp") trigCut_ = "HLT_HISinglePhoton20_Eta1p5_v1"; 
                    else if(coll=="pbpb") trigCut_ = "HLT_HISinglePhoton20_Eta1p5_v1 || HLT_HISinglePhoton20_Eta1p5_v2"; 
                    else cout << "[ERROR] : There is no this kind of collision" << endl;
                }

                cout << " Range ::: " << ptCut_ << ", " << centCut << endl; 
                cout << " Trigger ::: " << trigCut_.GetTitle() << endl; 

                TCut dataCandidateCut = trigCut_ && preScaleCut && sampleIsolation_woTrig && etaCut && ptCut_ && centCut;
                if(coll=="pp") dataCandidateCut = trigCut_ && preScaleCut && sampleIsolation_woTrig_pp && etaCut && ptCut_;

                TCut sidebandCut = ""; 
                if(useMCSB==0 && coll=="pbpb") sidebandCut = trigCut_ && preScaleCut && sidebandIsolation_woTrig && etaCut && ptCut_ && centCut;
                else if(useMCSB==0 && coll=="pp") sidebandCut = trigCut_ && preScaleCut && sidebandIsolation_woTrig_pp && etaCut && ptCut_;
                else if(useMCSB==1 && coll=="pbpb") sidebandCut = mcBkgIsolation && mcCut && hoeCut && isoCut && etaCut && ptCut_ && centCut;
                else if(useMCSB==1 && coll=="pp") sidebandCut = mcBkgIsolation && mcCut_pp && hoeCut_pp && isoCut_pp && etaCut && ptCut_;
                else cout << "something's wrong" << endl; 

                cout << "Sideband Range :: " << sidebandIsolation_woTrig.GetTitle() << endl;
                TCut mcSignalCut = mcSignalCut_woKine && etaCut && ptCut_ && centCut;
                if(coll=="pp") mcSignalCut = mcSignalCut_woKine_pp && etaCut && ptCut_;
                TCut mcSignalSBCut = mcIsolation && mcCut && hoeCut && nonIsoSBCut && etaCut && ptCut_ && centCut;
                if(coll=="pp") mcSignalSBCut = mcIsolation && hoeCut_pp && nonIsoSBCut && etaCut && ptCut_ && centCut;
                cout << "Signal MC Sideband Cut :: " << mcSignalSBCut.GetTitle() << endl;

                ////////////////////////////////////////////////////////////////
                // SB correction file part 
                TString fname_SBcorr = "";
                TString cap_Nfunc = "";
                if(Nfunc>=1) cap_Nfunc = Form("_function%d",Nfunc);
                TString temp_SBcorr = "";

                if(useSBcorr==1 && coll=="pbpb"){
                    if(centDepCorr==0){
                        if(ptDepCorrThr==0) temp_SBcorr=Form("SigmaIEtaIEta_Iso_nonIso_190703_temp_v31_pbpb_pt20to200_cent0to100_bkgPhotons_%s%s.root",purCap.Data(),cap_Nfunc.Data()); 
                        else if(ptDepCorrThr!=0 && (ptBins_unfolding[i]<ptDepCorrThr)) temp_SBcorr=Form("SigmaIEtaIEta_Iso_nonIso_190703_temp_v31_pbpb_pt20to%d_cent0to100_bkgPhotons_%s%s.root",ptDepCorrThr,purCap.Data(),cap_Nfunc.Data());
                        else if(ptDepCorrThr!=0 && (ptBins_unfolding[i]>=ptDepCorrThr)) temp_SBcorr=Form("SigmaIEtaIEta_Iso_nonIso_190703_temp_v31_pbpb_pt%dto200_cent0to100_bkgPhotons_%s%s.root",ptDepCorrThr,purCap.Data(),cap_Nfunc.Data());
                    } else{//cent dep
                        if(ptDepCorrThr==0) temp_SBcorr=Form("SigmaIEtaIEta_Iso_nonIso_190703_temp_v31_pbpb_pt20to200_cent%dto%d_bkgPhotons_%s%s.root",(int)centBins_i[j]/2,(int)centBins_f[j]/2,purCap.Data(),cap_Nfunc.Data()); 
                        else if(ptDepCorrThr!=0 && (ptBins_unfolding[i]<ptDepCorrThr)) temp_SBcorr=Form("SigmaIEtaIEta_Iso_nonIso_190703_temp_v31_pbpb_pt20to%d_cent%dto%d_bkgPhotons_%s%s.root",ptDepCorrThr,(int)centBins_i[j]/2,(int)centBins_f[j]/2,purCap.Data(),cap_Nfunc.Data());
                        else if(ptDepCorrThr!=0 && (ptBins_unfolding[i]>=ptDepCorrThr)) temp_SBcorr=Form("SigmaIEtaIEta_Iso_nonIso_190703_temp_v31_pbpb_pt%dto200_cent%dto%d_bkgPhotons_%s%s.root",ptDepCorrThr,(int)centBins_i[j]/2,(int)centBins_f[j]/2,purCap.Data(),cap_Nfunc.Data());
                    }   
                } 

                if(useSBcorr==1 && coll=="pp"){
                    if(ptDepCorrThr==0) temp_SBcorr=Form("SigmaIEtaIEta_Iso_nonIso_190703_temp_v31_pp_pt20to200_bkgPhotons_%s%s.root",purCap.Data(),cap_Nfunc.Data()); 
                    else if(ptDepCorrThr!=0 && (ptBins_unfolding[i]<ptDepCorrThr)) temp_SBcorr=Form("SigmaIEtaIEta_Iso_nonIso_190703_temp_v31_pp_pt20to%d_bkgPhotons_%s%s.root",ptDepCorrThr,purCap.Data(),cap_Nfunc.Data());
                    else if(ptDepCorrThr!=0 && (ptBins_unfolding[i]>=ptDepCorrThr)) temp_SBcorr=Form("SigmaIEtaIEta_Iso_nonIso_190703_temp_v31_pp_pt%dto200_bkgPhotons_%s%s.root",ptDepCorrThr,purCap.Data(),cap_Nfunc.Data());
                }
                if(useSBcorr==1) fname_SBcorr = Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/output/%s",temp_SBcorr.Data()); 

                // && centDepCorr==0) fname_SBcorr=Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/output/SigmaIEtaIEta_Iso_nonIso_190703_temp_v31_pbpb_pt20to200_cent0to100%s.root","");
                // if(useSBcorr==1 && coll=="pbpb" && centDepCorr==0) fname_SBcorr=Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/output/SigmaIEtaIEta_Iso_nonIso_190703_temp_v31_pbpb_pt20to200_cent0to100%s.root","");
                // 
                // //if(useSBcorr==1 && coll=="pbpb" && noCentDepCorr==1) fname_SBcorr=Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/output/BKG_Iso_nonIso_%s_%s_pt%dto%d_cent0to100.root",ver.Data(),coll.Data(),(int)ptBins_unfolding[i],(int)ptBins_unfolding[i+1]);
                // if(useSBcorr==1 && coll=="pbpb" && centDepCorr==1) fname_SBcorr=Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/output/SigmaIEtaIEta_Iso_nonIso_190703_temp_v31_pbpb_pt20to200_cent%dto%d.root",(int)centBins_i[j]/2,(int)centBins_f[j]/2);
                // if(useSBcorr==1 && coll=="pp") fname_SBcorr=Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/output/SigmaIEtaIEta_Iso_nonIso_190703_temp_v31_pp_pt20to200%s.root","");


                double purityResult[maxPurIter[j]];
                for (Int_t it = 0;it < maxPurIter[j]; ++it) {

                PhotonPurity fitr;

                double tempInputPurity = 0.0;
                if(it!=0)  tempInputPurity = purityResult[it-1];

                if(doSplitPD && ptBins_unfolding[i]>=40){
                    if(useMCSB==0 && useSBcorr==0){
                        fitr = getPurity(coll, configCuts, tPho_high, tmcPho,
                                dataCandidateCut, sidebandCut,
                                mcSignalCut, preScaleLabel,tempInputPurity,it,mcSignalSBCut);
                    } else if(useMCSB==0 && useSBcorr==1){
                        fitr = getPurity(coll, configCuts, tPho_high, tmcPho,
                                dataCandidateCut, sidebandCut,
                                mcSignalCut, preScaleLabel, fname_SBcorr);
                    } else if(useMCSB==1 && useSBcorr==0){
                        fitr = getPurity(coll, configCuts, tPho_high, tmcPho,
                                dataCandidateCut, sidebandCut,
                                mcSignalCut, preScaleLabel, "",tmcBkgPho);
                    } else if(useMCSB==1 && useSBcorr==1){
                        std::cout << "ERROR ::: Can't correct isolated Bkg distribution from MC :::" << std::endl;
                        return 1;
                    }
                } else{
                    if(useMCSB==0 && useSBcorr==0){
                        fitr = getPurity(coll, configCuts, tPho, tmcPho,
                                dataCandidateCut, sidebandCut,
                                mcSignalCut, preScaleLabel,tempInputPurity,it,mcSignalSBCut);
                    } else if(useMCSB==0 && useSBcorr==1){
                        fitr = getPurity(coll, configCuts, tPho, tmcPho,
                                dataCandidateCut, sidebandCut,
                                mcSignalCut, preScaleLabel, fname_SBcorr);
                    } else if(useMCSB==1 && useSBcorr==0){
                        fitr = getPurity(coll, configCuts, tPho, tmcPho,
                                dataCandidateCut, sidebandCut,
                                mcSignalCut, preScaleLabel, "",tmcBkgPho);
                    } else if(useMCSB==1 && useSBcorr==1){
                        std::cout << "ERROR ::: Can't correct isolated Bkg distribution from MC :::" << std::endl;
                        return 1;
                    }
                }

                //if(coll=="pbpb") cPurity->cd((k+j-1)*(nPtBin_unfolding)+i+1);
                if(coll=="pbpb") cPurity->cd((k+j-1)*(nPtBin_unfolding-1)+i+1); //when merging the last two pt bins, you should use (nPtBin_unfolding-1)
                else if(coll=="pp") cPurity->cd(i+1);

                TH1F* hSigPdf = fitr.sigPdf;
                TH1F* hBckPdf = fitr.bckPdf;
                TH1D* hData1  = fitr.data;
                hSigPdf->Add(hBckPdf);

                TString name = "mcfit_total_ptbin";
                name += i;

                // plot stacked histo
                handsomeTH1(hSigPdf);
                mcStyle(hSigPdf);
                sbStyle(hBckPdf);
                float range = cleverRange(hSigPdf, 1.5);
                htemp->SetAxisRange(0, range, "Y");
                htemp->SetNdivisions(505);
                htemp->GetYaxis()->SetTitleOffset(1.30);

                hSigPdf->SetAxisRange(0.001, 0.024, "X");
                hSigPdf->SetNdivisions(505);
                hSigPdf->GetYaxis()->SetTitleOffset(1.30);
                hSigPdf->SetYTitle("Entries");
                hSigPdf->SetXTitle("#sigma_{#eta#eta}");
                hSigPdf->SetLabelFont(43);
                hSigPdf->SetLabelSize(27);
                hSigPdf->SetTitleFont(63);
                hSigPdf->SetTitleSize(32);
                //hSigPdf->SetTitleFont(43);
                //hSigPdf->SetTitleSize(27);
                hSigPdf->GetYaxis()->SetLabelFont(43);
                hSigPdf->GetYaxis()->SetLabelSize(27);
                hSigPdf->GetYaxis()->SetTitleFont(43);
                hSigPdf->GetYaxis()->SetTitleSize(27);
                hSigPdf->GetYaxis()->SetLabelOffset(0.005);
                hSigPdf->GetYaxis()->SetTitleOffset(3);
                hSigPdf->GetXaxis()->SetTitleOffset(3);
                //hSigPdf->GetXaxis()->SetTitleOffset(2);
                hData1->SetMarkerSize(0.5);
                hData1->SetMarkerStyle(20);

                hSigPdf->DrawCopy("hist");
                // drawSys(hSigPdf, err, kRed, -1, 0.001);
                hBckPdf->DrawCopy("same hist");
                hData1->DrawCopy("same p");

                Float_t xpos = 0.45;
                //if (2*(k+j)*nPtBin_unfolding+i+1 == 1) xpos = 0.6;
                if (i == 0) xpos = 0.57;
                //Float_t xpos = 0.48;
                //if (i == 0) xpos = 0.6;

                if (i == 0) {
                    // drawText("CMS Preliminary", 0.225, 0.90, 1, 27);

                    TLatex* latexCMS = new TLatex();
                    latexCMS->SetTextFont(63);
                    latexCMS->SetTextSize(32);
                    if(j==0 && k==0) latexCMS->DrawLatexNDC(0.24, 0.9, "CMS");

                    TLatex* latexPrelim = new TLatex();
                    latexPrelim->SetTextFont(53);
                    latexPrelim->SetTextSize(28);
                    if(j==0 && k==0) latexPrelim->DrawLatexNDC(0.4, 0.9, "Preliminary");

                    if(j==0 && k==0) drawText(LABEL, xpos, 0.50, 1, 27);
                    if(coll=="pbpb") drawText(Form("%.0f - %.0f%c", centBins_i[j]/2., centBins_f[j]/2., '%'), xpos, 0.40, 1, 27);
                }

                if (i == 0) {
                    drawText(Form("%.0f GeV/c < p_{T}^{#gamma} < %.0f GeV/c", ptBins_unfolding[i], ptBins_unfolding[i+1]), 0.25, 0.80, 1, 27);
                } else if (i != 0 && i != nPtBin_unfolding_centDep-2) {
                    drawText(Form("%.0f GeV/c < p_{T}^{#gamma} < %.0f GeV/c", ptBins_unfolding[i], ptBins_unfolding[i+1]), 0.15, 0.90, 1, 27);
                } else if (i == nPtBin_unfolding_centDep-2) {
                    drawText(Form("%.0f GeV/c < p_{T}^{#gamma} < %.0f GeV/c", ptBins_unfolding[i], ptBins_unfolding[i+2]), 0.15, 0.90, 1, 27);
                } else {
                    drawText(Form("%.0f GeV/c < p_{T}^{#gamma} < %.0f GeV/c", ptBins_unfolding[i], ptBins_unfolding[i+1]), 0.15, 0.90, 1, 27);
                    //drawText(Form("p_{T}^{#gamma} > %.0f GeV/c", ptBins_unfolding[i]), 0.24, 0.90, 1, 27);
                }
                if (i == 0) {
                    drawText(Form("Purity : %.2f", (Float_t)fitr.purity), xpos, 0.70, 1, 27);
                } else {
                    drawText(Form("Purity : %.2f", (Float_t)fitr.purity), xpos, 0.80, 1, 27);
                }
                if (i == 0) {
                    drawText(Form("#chi^{2}/ndf : %.2f/%d", (Float_t)fitr.chisq,(Int_t)fitr.ndf), xpos, 0.60, 1, 27);
                } else {
                    drawText(Form("#chi^{2}/ndf : %.2f/%d", (Float_t)fitr.chisq,(Int_t)fitr.ndf), xpos, 0.70, 1, 27);
                }
                // if (i == 0) {
                //     drawText(Form("sig. shift : %.5f", (Float_t)fitr.sigMeanShift), xpos, 0.50, 1, 27);
                // } else {
                //     drawText(Form("sig. shift : %.5f", (Float_t)fitr.sigMeanShift), xpos, 0.60, 1, 27);
                // }

                outTxtFile << (int)centBins_i[j]/2 << "\t" << (int)centBins_f[j]/2 << "\t" << (int)ptBins_unfolding[i] << "\t" << (int)ptBins_unfolding[i+1] << "\t" << (Float_t)fitr.purity << "\t" << (Float_t)fitr.purityErr  << endl;

                TString canName = Form("cPurity_cent%dto%d_pt%dto%d",(int)centBins_i[j]/2,(int)centBins_f[j]/2,(int)ptBins_unfolding[i],(int)ptBins_unfolding[i+1]);
                if(i==nPtBin_unfolding_centDep-2) 
                    canName = Form("cPurity_cent%dto%d_pt%dto%d",(int)centBins_i[j]/2,(int)centBins_f[j]/2,(int)ptBins_unfolding[i],(int)ptBins_unfolding[i+2]);

                cPurity_each[j][i] = new TCanvas(Form("%s",canName.Data()),"cPurity_eachBin",300, 300);
                htemp->Draw();
                hSigPdf->DrawCopy("same hist");
                hBckPdf->DrawCopy("same hist");
                hData1->DrawCopy("same p");
                xpos = 0.45;
                drawText(LABEL, xpos, 0.60);
                drawText(Form("%.0f - %.0f%c", centBins_i[j]/2., centBins_f[j]/2., '%'), xpos, 0.50);
                //if (i != 0 && i != nPtBin_unfolding_centDep-2) {
                if (i != nPtBin_unfolding_centDep-2) {
                    drawText(Form("%.0f GeV/c < p_{T}^{#gamma} < %.0f GeV/c", ptBins_unfolding[i], ptBins_unfolding[i+1]), 0.15, 0.90);                
                } else if (i == nPtBin_unfolding_centDep-2) {
                    drawText(Form("%.0f GeV/c < p_{T}^{#gamma} < %.0f GeV/c", ptBins_unfolding[i], ptBins_unfolding[i+2]), 0.15, 0.90);
                }
                drawText(Form("Purity : %.2f", (Float_t)fitr.purity), xpos, 0.80);
                drawText(Form("#chi^{2}/ndf : %.2f/%d", (Float_t)fitr.chisq,(Int_t)fitr.ndf), xpos, 0.70);

                cPurity_each[j][i]->SaveAs(Form("%sfigures/%s_%s.pdf",dir.Data(),outputName.Data(),canName.Data()));

                h1D_pur[j]->SetBinContent(i+1,(Float_t)fitr.purity);
                h1D_pur[j]->SetBinError(i+1,(Float_t)fitr.purityErr);
            //} // remove pt bins  

            }
        }
    }
    if(coll=="pbpb") h1D_pur[0] = (TH1D*) h1D_pur[1]->Clone(Form("h1D_purity_cent%d",0));
    outTxtFile.close();

    TH1D* permaCopy[3];
    permaCopy[0] = new TH1D("copy0", "", 1, 0, 1);
    permaCopy[1] = new TH1D("copy1", "", 1, 0, 1);
    permaCopy[2] = new TH1D("copy2", "", 1, 0, 1);
    handsomeTH1(permaCopy[0]);
    mcStyle(permaCopy[0]);
    sbStyle(permaCopy[1]);

    TLegend* t3 = new TLegend(0.44, 0.30, 0.92, 0.60);
    TLegendEntry* ent1 = t3->AddEntry(permaCopy[2], LABEL, "pl");
    TLegendEntry* ent2 = t3->AddEntry(permaCopy[0], "Signal", "lf");
    TLegendEntry* ent3 = t3->AddEntry(permaCopy[1], "Background", "lf");

    ent1->SetMarkerStyle(20);
    ent2->SetLineColor(kPink);
    ent2->SetFillColor(kOrange+7);
    ent2->SetFillStyle(3004);
    ent3->SetLineColor(kGreen+4);
    ent3->SetFillColor(kGreen+1);
    ent3->SetFillStyle(3001);

    t3->SetFillColor(0);
    t3->SetBorderSize(0);
    t3->SetFillStyle(0);
    t3->SetTextFont(43);
    t3->SetTextSize(27);
    t3->Draw();

    outFile->cd();
    cPurity->Write();
    for (Int_t j = 0; j < nCENTBINS; ++j) {
        h1D_pur[j]->Write();
    }
    outFile->Close();
    cPurity->SaveAs(Form("%sfigures/%s.pdf",dir.Data(), outputName.Data()));

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 3)
        return yj_quickPhotonPurity_v7_iteration(argv[1], argv[2]);
    if (argc == 4)
        return yj_quickPhotonPurity_v7_iteration(argv[1], argv[2], atoi(argv[3]));
    if (argc == 5)
        return yj_quickPhotonPurity_v7_iteration(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]));
    if (argc == 6)
        return yj_quickPhotonPurity_v7_iteration(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    return 1;
}
