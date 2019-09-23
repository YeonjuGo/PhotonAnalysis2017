// yj_quickPhotonPurity.C
// Author: Yeonju Go
// Modified : 2019 Sep 19 
// Created : 2017 April 10 
// Cobbled together from code written by Alex

// Calculates and plots the photon purity using a sideband estimation
// of the background and a MC calculation of the signal. This info is
// used to do a template fit in the sigmaIetaIeta variable.
// Modified 2019June25) unfolding binning (20 GeV to 300 GeV)
// Modified 2019June25) do NOT calculate purity 0-100% and high pt bins for peripheral events (centrality dependent pt ranges) 
// yj_quickPhotonPurity_v7_iteration_eachBin_v2_impurity) Calculate purity only for one bin with several iteration! 

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

#include "PhotonPurity_sigSub_iteration_v2_impurity.h"
//#include "../phoRaaCuts/phoRaaCuts_purity_forPaper.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
#include "../ElectroWeak-Jet-Track-Analyses/Utilities/interface/CutConfigurationParser.h"
#include "../ElectroWeak-Jet-Track-Analyses/Utilities/interface/InputConfigurationParser.h"
#include "../ElectroWeak-Jet-Track-Analyses/Plotting/commonUtility.h"

int yj_quickPhotonPurity_v7_iteration_eachBin_v2_impurity(const TString coll="pp", const TString ver="phoRaaCuts_purity_forPaper", bool doSplitPD=true, bool doPreScale=0, double pt_i=20, double pt_f=25, int cent_i=0, int cent_f=10, int maxIter=10, double sideband_i=1, double sideband_f=3){
    cout << "Purity Calculation using yj_quickPhotonPurity_v7_iteration_eachBin_v2_impurity.C" << endl;
    cout << "::: version = " << ver << endl; 
    cout << "::: doSplitPD = " << doSplitPD << endl; 
    cout << "::: doPreScale = " << doPreScale << endl; 

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
    TString cap_bin = "";
    if(coll=="pp") cap_bin += Form("pt%dto%d_maxIter%d",(int)pt_i,(int)pt_f,(int)maxIter);
    else cap_bin += Form("cent%dto%d_pt%dto%d_maxIter%d",(int)cent_i,(int)cent_f,(int)pt_i,(int)pt_f,(int)maxIter);

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
    TString LABEL = "PbPb Data";
    if(coll=="pp") LABEL = "pp Data";
    cout << "collisionTypeName = " << coll << endl;

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

    //TFile* inputBkgMCFile = TFile::Open(inputBkgMC);
    //TTree* tmcBkgHlt = (TTree*)inputBkgMCFile->Get("hltTree");
    //TTree* tmcBkgPho = (TTree*)inputBkgMCFile->Get("EventTree");    // photons
    //TTree* tmcBkgHiEvt = (TTree*)inputBkgMCFile->Get("HiEvt");       // HiEvt tree will be placed in PP forest as well
    //TTree* tmcBkgSkim = (TTree*)inputBkgMCFile->Get("skim");       // HiEvt tree will be placed in PP forest as well
    //tmcBkgPho->AddFriend(tmcBkgHlt, "Hlt");
    //tmcBkgPho->AddFriend(tmcBkgPho, "Pho");
    //tmcBkgPho->AddFriend(tmcBkgHiEvt, "HiEvt");
    //tmcBkgPho->AddFriend(tmcBkgSkim, "skim");

    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/purity/";
    TFile* outFile = new TFile(Form("%soutput/%s_%s.root",dir.Data(), outputName.Data(),cap_bin.Data()), "RECREATE");

    /////////////////////////////////////////
    //Text File 
    //ofstream outTxtFile(Form("%stxt/purity_%s_LastBinsMerged.txt",dir.Data(), outputName.Data()), ios::app);
    //outTxtFile << "cent_i" << "\t" << "cent_f" << "\t" << "pT_i" << "\t" << "pT_f" << "\t" << "Purity" << "\t" << "PurityErr"  << endl;
    //outTxtFile << run << "\t" << setprecision(4) <<eff*100 << "\t" << chi2s[ibest] << endl;
    //outTxtFile.close();

    TH1D* h1D_pur_iter = new TH1D("h1D_purity_iter","; # of iteration; Purity",maxIter,0,maxIter);
    TH1D* htemp = new TH1D(Form("htemp%d",1),";#sigma_{#eta#eta};Entries",100,0.001,0.024);

    TCanvas* cPurity;
    cPurity = new TCanvas("c1", "c1", 300*maxIter, 300);
    makeMultiPanelCanvas(cPurity, maxIter, 1, 0.0, 0.0 , 0.2, 0.15, 0.005);
    TCanvas* cPurity_each[maxIter];

    cout << " Centrality ::: " << cent_i << " to " << cent_f << endl;
    cout << " pT         ::: " << pt_i << " to " << pt_f << endl;

    TString ptCut_ = Form("(%s>= %f) && (%s< %f)", phoEtVar.Data(), (double)pt_i, phoEtVar.Data(), (double)pt_f);
    TString centCut_ = Form("(hiBin>=%i) && (hiBin<%i)", cent_i*2, cent_f*2);
    if(coll=="pp") centCut_ = "hiBin<10000";

    TCut trigCut_ = "1==0"; 
    TCut preScaleLabel = "phoPreScale";
    TCut preScaleCut = "";

    //////////////////////////////////////////////////////////////////////////////////////
    // Trigger part 
    // TCut sampleIsolation = "(pho_sumIsoCorrected < (16.7202-0.154349*hiBin+0.00040613*hiBin*hiBin)) && phoHoverE<0.1"; //for PbPb
    if(doSplitPD){
        if(pt_i>=40){ // high pt
            if(coll=="pp"){ 
                trigCut_ = trigCut_pp_high;
                preScaleLabel = "1";
                preScaleCut = "1"; 
            } else if(coll=="pbpb"){ 
                trigCut_ = trigCut_high;
                preScaleLabel = "1";
                preScaleCut = "1"; 
            } else{ cout << "[ERROR] : There is no this kind of collision" << endl; }
        } else{ 
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
        }
    } else{
        if(coll=="pp") trigCut_ = "HLT_HISinglePhoton20_Eta1p5_v1"; 
        else if(coll=="pbpb") trigCut_ = "HLT_HISinglePhoton20_Eta1p5_v1 || HLT_HISinglePhoton20_Eta1p5_v2"; 
        else cout << "[ERROR] : There is no this kind of collision" << endl;
    }
    cout << " Trigger   ::: " << trigCut_.GetTitle() << endl; 

    TCut dataCandidateCut = trigCut_ && preScaleCut && sampleIsolation_woTrig && etaCut && ptCut_ && centCut_;
    if(coll=="pp") dataCandidateCut = trigCut_ && preScaleCut && sampleIsolation_woTrig_pp && etaCut && ptCut_;

    TCut mcSignalCut = mcSignalCut_woKine && etaCut && ptCut_ && centCut_;
    if(coll=="pp") mcSignalCut = mcSignalCut_woKine_pp && etaCut && ptCut_;

    TCut nonIsoSBCut_here = Form("pho_sumIsoCorrected > %f && pho_sumIsoCorrected < %f",(double)sideband_i,(double)sideband_f);  
    cout << " Sideband Range    ::: " << nonIsoSBCut.GetTitle() << endl; 

    TCut sidebandCut = ""; 
    if(coll=="pbpb") sidebandCut = trigCut_ && preScaleCut && noiseCut && hoeCut && nonIsoSBCut_here && electronCut && etaCut && ptCut_ && centCut_;
    else if(coll=="pp") sidebandCut = trigCut_ && preScaleCut && noiseCut && hoeCut_pp && nonIsoSBCut_here && electronCut && etaCut && ptCut_;
    else cout << "something's wrong" << endl; 

    TCut mcSignalSBCut = mcIsolation && mcCut && hoeCut && nonIsoSBCut_here && etaCut && ptCut_ && centCut_;
    if(coll=="pp") mcSignalSBCut = mcIsolation && hoeCut_pp && nonIsoSBCut_here && etaCut && ptCut_ && centCut_;



    /////////////////////////////////////////////////////////////////////////////////
    // For loop start in iteration 

    double purityResult[maxIter];
    double nevResult[maxIter];
    double ratioResult[maxIter];
    for (Int_t it = 0; it < maxIter; ++it) {

        cout << " Iteration    ::: " << it << endl; 
        PhotonPurity fitr;

        double tempInputPurity = 0.0;
        double tempnev= 0.0;
        double tempratio= 0.0;
        if(it!=0){
            tempInputPurity = purityResult[it-1];
            tempnev = nevResult[it-1];    
            tempratio = ratioResult[it-1];    
        }
        cout << " Input nev    ::: " << tempnev << endl; 
        cout << " Input ratio    ::: " << tempratio << endl; 

        TString tempOutputName = outputName;
        if(coll=="pbpb") tempOutputName+=Form("_cPurity_cent%dto%d_pt%dto%d_maxIter%d_iter%d",(int)cent_i,(int)cent_f,(int)pt_i,(int)pt_f,maxIter,it);
        else tempOutputName+=Form("_cPurity_pt%dto%d_maxIter%d_iter%d",(int)pt_i,(int)pt_f,maxIter,it);
        if(doSplitPD && pt_i>=40){
            fitr = getPurity(coll, configCuts, tPho_high, tmcPho,
                    dataCandidateCut, sidebandCut,
                    mcSignalCut, preScaleLabel,tempnev,tempratio,it,mcSignalSBCut,tempOutputName);
        } else{
            fitr = getPurity(coll, configCuts, tPho, tmcPho,
                    dataCandidateCut, sidebandCut,
                    mcSignalCut, preScaleLabel,tempnev,tempratio,it,mcSignalSBCut,tempOutputName);
        }

        cPurity->cd(it+1);

        TH1F* hSigPdf = fitr.sigPdf;
        TH1F* hBckPdf = fitr.bckPdf;
        TH1D* hData1  = fitr.data;
        hSigPdf->Add(hBckPdf);

        TString name = "mcfit_total_ptbin";
        name += it;

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
        hData1->SetMarkerSize(0.5);
        hData1->SetMarkerStyle(20);

        hSigPdf->DrawCopy("hist");
        hBckPdf->DrawCopy("same hist");
        hData1->DrawCopy("same p");

        Float_t xpos = 0.45;
        if (it == 0) xpos = 0.57;

        if (it == 0) {
            TLatex* latexCMS = new TLatex();
            latexCMS->SetTextFont(63);
            latexCMS->SetTextSize(32);
            latexCMS->DrawLatexNDC(0.24, 0.9, "CMS");

            TLatex* latexPrelim = new TLatex();
            latexPrelim->SetTextFont(53);
            latexPrelim->SetTextSize(28);
            latexPrelim->DrawLatexNDC(0.4, 0.9, "Preliminary");

            drawText(LABEL, xpos, 0.50, 1, 27);
            drawText(Form("%.0f GeV/c < p_{T}^{#gamma} < %.0f GeV/c", (double)pt_i, (double)pt_f), 0.25, 0.90, 1, 27);
            if(coll=="pbpb") drawText(Form("%.0f - %.0f%c", (double)cent_i, (double)cent_f, '%'), xpos, 0.80, 1, 27);
        }

        drawText(Form("Iteration = %d", it), xpos, 0.70, 1, 27);
        drawText(Form("Purity : %.2f", (Float_t)fitr.purity), xpos, 0.60, 1, 27);
        drawText(Form("#chi^{2}/ndf : %.2f", (Float_t)fitr.chisq/(double)fitr.ndf), xpos, 0.50, 1, 27);
        drawText(Form("Sig. Cont. in SB : %.2f", (Float_t)fitr.impurity), xpos, 0.40, 1, 27);

        //outTxtFile << (int)centBins_i[j]/2 << "\t" << (int)centBins_f[j]/2 << "\t" << (int)ptBins_unfolding[i] << "\t" << (int)ptBins_unfolding[i+1] << "\t" << (Float_t)fitr.purity << "\t" << (Float_t)fitr.purityErr  << endl;

        cPurity_each[it] = new TCanvas(Form("cPurity_%s_iter%d",cap_bin.Data(),it),"cPurity_eachBin",300, 300);
        htemp->Draw();
        hSigPdf->DrawCopy("same hist");
        hBckPdf->DrawCopy("same hist");
        hData1->DrawCopy("same p");
        xpos = 0.45;
        drawText(LABEL, xpos, 0.60);
        drawText(Form("%.0f GeV/c < p_{T}^{#gamma} < %.0f GeV/c", pt_i, pt_f), 0.15, 0.90);                
        drawText(Form("Purity : %.2f", (Float_t)fitr.purity), xpos, 0.80);
        drawText(Form("#chi^{2}/ndf : %.2f", (Float_t)fitr.chisq/(double)fitr.ndf), xpos, 0.70);
        drawText(Form("Sig. Cont. in SB : %.2f", (Float_t)fitr.impurity), xpos, 0.60);
        if(coll=="pbpb") drawText(Form("%.0f - %.0f%c", (double)cent_i, (double)cent_f, '%'), xpos, 0.50);

        cPurity_each[it]->SaveAs(Form("%sfigures/%s_%s_iter%d.pdf",dir.Data(),outputName.Data(),cap_bin.Data(),it));
        h1D_pur_iter->SetBinContent(it+1,(Float_t)fitr.purity);
        h1D_pur_iter->SetBinError(it+1,(Float_t)fitr.purityErr);
        purityResult[it] = fitr.purity;
        nevResult[it] = fitr.nev;
        ratioResult[it] = fitr.ratio;
    }

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
    h1D_pur_iter->Write();
    outFile->Close();
    cPurity->SaveAs(Form("%sfigures/%s_%s.pdf",dir.Data(), outputName.Data(),cap_bin.Data()));

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 3)
        return yj_quickPhotonPurity_v7_iteration_eachBin_v2_impurity(argv[1], argv[2]);
    if (argc == 4)
        return yj_quickPhotonPurity_v7_iteration_eachBin_v2_impurity(argv[1], argv[2], atoi(argv[3]));
    if (argc == 5)
        return yj_quickPhotonPurity_v7_iteration_eachBin_v2_impurity(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]));
    if (argc == 6)
        return yj_quickPhotonPurity_v7_iteration_eachBin_v2_impurity(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    return 1;
}
