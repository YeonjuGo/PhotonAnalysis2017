// yj_quickPhotonPurity_floatSig.C
// Author: Yeonju Go
// Modifired : 2017 December 14 
// Created : 2017 April 10 
// Cobbled together from code written by Alex

// Calculates and plots the photon purity using a sideband estimation
// of the background and a MC calculation of the signal. This info is
// used to do a template fit in the sigmaIetaIeta variable.

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

#include "PhotonPurity_floatSig.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
#include "../ElectroWeak-Jet-Track-Analyses/Utilities/interface/CutConfigurationParser.h"
#include "../ElectroWeak-Jet-Track-Analyses/Utilities/interface/InputConfigurationParser.h"
#include "../ElectroWeak-Jet-Track-Analyses/Plotting/commonUtility.h"

int yj_quickPhotonPurity_floatSig(const TString coll="pbpb", const TString ver="170523_temp_v1_NewPurityMethod", bool useSBcorr=1, bool noCentDepCorr=1, bool useMCSB=0){
    gStyle->SetOptStat(0);
    TH1::SetDefaultSumw2();

    TString configFile=""; 
    TString inputData=""; 
    TString inputMC=""; 
    TString inputBkgMC ="";
    TString outputName=Form("%s_purity_%s_floatSig",coll.Data(),ver.Data());
    if(coll=="pbpb"){
        configFile = pbpbData_config;
        inputData = pbpbDatafname;
        inputMC = pbpbMCfname;
        inputBkgMC = pbpbMCEmEnrfname; 
    } else if(coll=="pp"){
        configFile = ppData_config;
        inputData = ppDatafname;
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
    const int collisionType = configInput.proc[INPUT::kSKIM].i[INPUT::k_collisionType];
    const TString collisionTypeName = getCollisionTypeName((COLL::TYPE)collisionType).c_str();
    TString LABEL = "PbPb Data";
    if(collisionType==2) LABEL = "pp Data";
    
    cout << "collisionType = " << collisionType << ", collisionTypeName = " << collisionTypeName << endl;

    Int_t nCENTBINS = nCentBinIF;
    if(collisionType==2) nCENTBINS=1;

    std::string trigger = configCuts.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].s[CUTS::PHO::k_trigger_gammaJet].c_str();
    TFile* input = TFile::Open(inputData);
    TTree* tHlt = (TTree*)input->Get("hltTree");
    TTree* tPho = (TTree*)input->Get("EventTree");    // photons
    TTree* tHiEvt = (TTree*)input->Get("HiEvt");       // HiEvt tree will be placed in PP forest as well.
    TTree* tSkim = (TTree*)input->Get("skim");       // HiEvt tree will be placed in PP forest as well.

    TFile* inputMCFile = TFile::Open(inputMC);
    TTree* tmcHlt = (TTree*)inputMCFile->Get("hltTree");
    TTree* tmcPho = (TTree*)inputMCFile->Get("EventTree");    // photons
    TTree* tmcHiEvt = (TTree*)inputMCFile->Get("HiEvt");       // HiEvt tree will be placed in PP forest as well
    TTree* tmcSkim = (TTree*)inputMCFile->Get("skim");       // HiEvt tree will be placed in PP forest as well

    tPho->AddFriend(tHlt, "Hlt");
    tPho->AddFriend(tPho, "Pho");
    tPho->AddFriend(tHiEvt, "HiEvt");
    tPho->AddFriend(tSkim, "skim");

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
    TH1D* h1D_pur[nCENTBINS];
    for (Int_t j = 0; j < nCENTBINS; j++) {
        if(collisionType==2) h1D_pur[j] = new TH1D("h1D_purity_pp",";p_{T}^#gamma (GeV);",nPtBin,ptBins_draw);
        else h1D_pur[j] = new TH1D(Form("h1D_purity_cent%d",j),";p_{T}^#gamma (GeV);",nPtBin,ptBins_draw);
    }

    TCanvas* cPurity = new TCanvas("c1", "c1", 400*nPtBin, 400*nCENTBINS);
    makeMultiPanelCanvas(cPurity, nPtBin, nCENTBINS, 0.0, 0.0 , 0.2, 0.15, 0.005);
    for (Int_t i = 0; i < nPtBin; ++i) {
        for (Int_t j = 0; j < nCENTBINS; ++j) {
            for (Int_t k = 0; k < 1; ++k) {
                TString ptCut = Form("(%s>= %f) && (%s< %f)",
                        phoEtVar.Data(), ptBins[i], phoEtVar.Data(), ptBins[i+1]);
                TString centCut = Form("(hiBin>=%i) && (hiBin<%i)",
                        centBins_i[j], centBins_f[j]);
                if(collisionType==2) centCut = "hiBin<10000";

                //TCut sampleIsolation = "(pho_sumIsoCorrected < (16.7202-0.154349*hiBin+0.00040613*hiBin*hiBin)) && phoHoverE<0.1"; //for PbPb
                TCut dataCandidateCut = sampleIsolation && etaCut && ptCut && centCut;
                if(collisionType==2) dataCandidateCut = sampleIsolation_pp && etaCut && ptCut;

                TCut sidebandCut = ""; 
                if(useMCSB==0 && collisionType==0) sidebandCut = sidebandIsolation && etaCut && ptCut && centCut;
                else if(useMCSB==0 && collisionType==2) sidebandCut = sidebandIsolation_pp && etaCut && ptCut;
                else if(useMCSB==1 && collisionType==0) sidebandCut = mcBkgIsolation && mcCut && hoeCut && isoCut && etaCut && ptCut && centCut;
                else if(useMCSB==1 && collisionType==2) sidebandCut = mcBkgIsolation && mcCut_pp && hoeCut_pp && isoCut_pp && etaCut && ptCut;
                else cout << "something's wrong" << endl; 

                TCut mcSignalCut = mcSignalCut_woKine && etaCut && ptCut && centCut;
                if(collisionType==2) mcSignalCut = mcSignalCut_woKine_pp && etaCut && ptCut;

                TString fname_SBcorr = "";
                if(useSBcorr==1 && coll=="pbpb" && noCentDepCorr==1) fname_SBcorr=Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/output/BKG_Iso_nonIso_%s_%s_pt%dto%d_cent0to100.root",ver.Data(),coll.Data(),(int)ptBins[i],(int)ptBins[i+1]);
                if(useSBcorr==1 && coll=="pbpb" && noCentDepCorr==0) fname_SBcorr=Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/output/BKG_Iso_nonIso_%s_%s_pt%dto%d_cent%dto%d.root",ver.Data(),coll.Data(),(int)ptBins[i],(int)ptBins[i+1],(int)centBins_i[j]/2,(int)centBins_f[j]/2);
                if(useSBcorr==1 && coll=="pp") fname_SBcorr=Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/output/BKG_Iso_nonIso_%s_%s_pt%dto%d.root",ver.Data(),coll.Data(),(int)ptBins[i],(int)ptBins[i+1]);

                //PhotonPurity fitr;
                Purity* fitr;
                if(useMCSB==0 && useSBcorr==0){
                    fitr = getPurity(coll, configCuts, tPho, tmcPho,
                            dataCandidateCut, sidebandCut,
                            mcSignalCut);
                } else if(useMCSB==0 && useSBcorr==1){
                    fitr = getPurity(coll, configCuts, tPho, tmcPho,
                            dataCandidateCut, sidebandCut,
                            mcSignalCut, fname_SBcorr);
                } else if(useMCSB==1 && useSBcorr==0){
                    fitr = getPurity(coll, configCuts, tPho, tmcPho,
                            dataCandidateCut, sidebandCut,
                            mcSignalCut, "",tmcBkgPho);
                } else if(useMCSB==1 && useSBcorr==1){
                    std::cout << "ERROR ::: Can't correct isolated Bkg distribution from MC :::" << std::endl;
                    return 1;
                }
                cPurity->cd((k+j)*nPtBin+i+1);

                TH1D* hSigPdf = fitr->htotal_fit;
                TH1D* hBckPdf = fitr->hbkg_fit;
                TH1D* hData1  = fitr->hdata;
               // TH1F* hSigPdf = fitr.sigPdf;
               // TH1F* hBckPdf = fitr.bckPdf;
               // TH1D* hData1  = fitr.data;
                //hSigPdf->Add(hBckPdf);

                TString name = "mcfit_total_ptbin";
                name += i;

                // outFile->cd();
                // hSigPdf->SetName(name);
                // hSigPdf->Write();

                // TH1D* err = (TH1D*)hSigPdf->Clone("error");
                // TH1D* tempErr[4];
                // err->Reset();
                // for (int s = 0; s < 4; s++) {
                //   if (s == 0)
                //     tempErr[s] = (TH1D*)TFile::Open("photonPurity_sys_loose.root")->Get(name);
                //   else if (s == 1)
                //     tempErr[s] = (TH1D*)TFile::Open("photonPurity_sys_tight.root")->Get(name);
                //   else if (s == 2)
                //     tempErr[s] = (TH1D*)TFile::Open("photonPurity_sys_sigshift.root")->Get(name);
                //   else if (s == 3)
                //     tempErr[s] = (TH1D*)TFile::Open("photonPurity_sys_bkgshift.root")->Get(name);
                //   tempErr[s]->Divide(hSigPdf);
                //   for (Int_t l=1; l<=tempErr[s]->GetNbinsX(); l++) {
                //     tempErr[s]->SetBinContent(l, TMath::Abs(tempErr[s]->GetBinContent(l))-1);
                //   }
                // }
                // for (Int_t l=1; l<=err->GetNbinsX(); l++) {
                //   Double_t errVal = TMath::Sqrt(
                //     tempErr[0]->GetBinContent(l) * tempErr[0]->GetBinContent(l) +
                //     tempErr[1]->GetBinContent(l) * tempErr[1]->GetBinContent(l) +
                //     tempErr[2]->GetBinContent(l) * tempErr[2]->GetBinContent(l) +
                //     tempErr[3]->GetBinContent(l) * tempErr[3]->GetBinContent(l)
                //   );
                //   err->SetBinContent(l, errVal);
                // }

                // plot stacked histos
                handsomeTH1(hSigPdf);
                mcStyle(hSigPdf);
                sbStyle(hBckPdf);
                cleverRange(hSigPdf, 1.5);

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

                hSigPdf->DrawCopy("hist");
                // drawSys(hSigPdf, err, kRed, -1, 0.001);
                hBckPdf->DrawCopy("same hist");
                hData1->DrawCopy("same");

                Float_t xpos = 0.48;
                //if (2*(k+j)*nPtBin+i+1 == 1) xpos = 0.6;
                if (i == 0) xpos = 0.6;

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
                    drawText(Form("%.0f GeV/c < p_{T}^{#gamma} < %.0f GeV/c", ptBins[i], ptBins[i+1]), 0.25, 0.80, 1, 27);
                } else if (i != 0 && i != nPtBin-1) {
                    drawText(Form("%.0f GeV/c < p_{T}^{#gamma} < %.0f GeV/c", ptBins[i], ptBins[i+1]), 0.15, 0.90, 1, 27);
                } else {
                    drawText(Form("p_{T}^{#gamma} > %.0f GeV/c", ptBins[i]), 0.24, 0.90, 1, 27);
                }
                if (i == 0) {
                    drawText(Form("Purity : %.2f", (Float_t)fitr->purity), xpos, 0.70, 1, 27);
                } else {
                    drawText(Form("Purity : %.2f", (Float_t)fitr->purity), xpos, 0.80, 1, 27);
                }
                if (i == 0) {
                    drawText(Form("#chi^{2}/ndf : %.2f", (Float_t)fitr->chisq/fitr->ndf), xpos, 0.60, 1, 27);
                } else {
                    drawText(Form("#chi^{2}/ndf : %.2f", (Float_t)fitr->chisq/fitr->ndf), xpos, 0.70, 1, 27);
                }

                h1D_pur[j]->SetBinContent(i+1,(Float_t)fitr->purity);
            }
        }
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
    for (Int_t j = 0; j < nCENTBINS; ++j) {
        h1D_pur[j]->Write();
    }
    outFile->Close();
    cPurity->SaveAs(Form("%sfigures/%s.pdf",dir.Data(), outputName.Data()));

    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 3)
        return yj_quickPhotonPurity_floatSig(argv[1], argv[2]);
    if (argc == 4)
        return yj_quickPhotonPurity_floatSig(argv[1], argv[2], atoi(argv[3]));
    if (argc == 5)
        return yj_quickPhotonPurity_floatSig(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]));
    if (argc == 6)
        return yj_quickPhotonPurity_floatSig(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
    return 1;
}
