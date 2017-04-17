// yj_quickPhotonPurity.C
// Author: Yeonju Go
// Modifired : 2017 April 17 
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

#include "PhotonPurity.h"

#include "../phoRaaCuts/phoRaaCuts_v1.h"
#include "../ElectroWeak-Jet-Track-Analyses/Utilities/interface/CutConfigurationParser.h"
#include "../ElectroWeak-Jet-Track-Analyses/Utilities/interface/InputConfigurationParser.h"
#include "../ElectroWeak-Jet-Track-Analyses/Plotting/commonUtility.h"


//const Double_t PTBINS[] = {40, 50, 60, 80, 9999};
//const Int_t nPTBINS = sizeof(PTBINS)/sizeof(Double_t) -1;

int yj_quickPhotonPurity(const TString configFile, const TString inputData, const TString inputMC, const TString outputName) {
  gStyle->SetOptStat(0);

  TH1::SetDefaultSumw2();
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
  
  Int_t nCENTBINS = nCentBinIF;
  if(collisionType==2) nCENTBINS==1;

  std::string trigger = configCuts.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].s[CUTS::PHO::k_trigger_gammaJet].c_str();
  // trigger is named differently in MC, hardcode for now :(
  std::string triggerMC_forPurity = "(HLT_HISinglePhoton40_Eta1p5_v2)";//HIMC
  if(collisionType==2) triggerMC_forPurity = "(HLT_HISinglePhoton40_Eta1p5ForPPRef_v1)"; // PPMC

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

  TFile* outFile = new TFile(Form("output/%s.root", outputName.Data()), "RECREATE");

  const TCut sidebandIsolation = "((pho_sumIsoCorrected)>10) && ((pho_sumIsoCorrected)<20) && phoHoverE<0.1";
  const TCut mcIsolation = "(pho_genMatchedIndex!= -1) && mcCalIsoDR04[pho_genMatchedIndex]<5 && abs(mcPID[pho_genMatchedIndex])<=22";

  TH1D* h1D_pur[nCENTBINS];
  for (Int_t j = 0; j < nCENTBINS; ++j) {
      h1D_pur[j] = new TH1D(Form("h1D_purity_cent%d",j),";p_{T}^#gamma (GeV);",nPtBin,ptBins_draw);
  }

  TCanvas* cPurity = new TCanvas("c1", "c1", 400*nPtBin, 400*nCENTBINS);
  makeMultiPanelCanvas(cPurity, nPtBin, nCENTBINS, 0.0, 0.0 , 0.2, 0.15, 0.005);
  for (Int_t i = 0; i < nPtBin; ++i) {
    for (Int_t j = 0; j < nCENTBINS; ++j) {
      for (Int_t k = 0; k < 1; ++k) {
        TString ptCut = Form("(phoEtCorrected >= %f) && (phoEtCorrected < %f)",
                             ptBins[i], ptBins[i+1]);
        TString centCut = Form("(hiBin >= %i) && (hiBin < %i)",
                               centBins_i[j], centBins_f[j]);
        if(collisionType==2) centCut == "(1)";
        TString etaCut = "(abs(phoEta) < 1.44)";

        std::cout << ptBins[i] << " < pt < " << ptBins[i+1] << ", " << centCut.GetTitle() << endl;
        TCut triggerCut = Form("%s == 1", trigger.c_str());
        TCut triggerCutMC =  Form("%s == 1", triggerMC_forPurity.c_str());

        TCut sampleIsolation = "(pho_sumIsoCorrected) < 1.0 && phoHoverE<0.1"; //for PbPb
        if(collisionType==2) sampleIsolation = "((pfcIso4<=1.37) && (pfnIso4<=1.06+0.014*phoEt+0.000019*phoEt*phoEt) && pfpIso4<=(0.28+0.0053*phoEt)) && phoHoverE<0.05"; //for pp

        TCut extraCut = evtSelFilterCut && spikeRejection;
        if(collisionType==2) extraCut == evtSelFilterCut_pp && spikeRejection; 
        TCut dataCandidateCut = sampleIsolation && etaCut && ptCut && centCut && hotspotCut && triggerCut && extraCut;
        TCut sidebandCut =  sidebandIsolation && etaCut && ptCut && centCut && hotspotCut && triggerCut && extraCut;
        TCut mcSignalCut =  mcIsolation && etaCut && ptCut && centCut && triggerCutMC;

        PhotonPurity fitr = getPurity(configCuts, tPho, tmcPho,
                                      dataCandidateCut, sidebandCut,
                                      mcSignalCut);

        cPurity->cd((k+j)*nPtBin+i+1);

        TH1F* hSigPdf = fitr.sigPdf;
        TH1F* hBckPdf = fitr.bckPdf;
        TH1D* hData1  = fitr.data;
        hSigPdf->Add(hBckPdf);

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
        hSigPdf->SetTitleFont(43);
        hSigPdf->SetTitleSize(27);
        hSigPdf->GetYaxis()->SetLabelFont(43);
        hSigPdf->GetYaxis()->SetLabelSize(27);
        hSigPdf->GetYaxis()->SetTitleFont(43);
        hSigPdf->GetYaxis()->SetTitleSize(27);
        hSigPdf->GetYaxis()->SetLabelOffset(0.005);
        hSigPdf->GetXaxis()->SetTitleOffset(1);

        hSigPdf->DrawCopy("hist");
        // drawSys(hSigPdf, err, kRed, -1, 0.001);
        hBckPdf->DrawCopy("same hist");
        hData1->DrawCopy("same");

        Float_t xpos = 0.48;
        if (2*(k+j)*nPtBin+i+1 == 1)
          xpos = 0.6;

        if (i == 0) {
          // drawText("CMS Preliminary", 0.225, 0.90, 1, 27);

          TLatex* latexCMS = new TLatex();
          latexCMS->SetTextFont(63);
          latexCMS->SetTextSize(32);
          latexCMS->DrawLatexNDC(0.24, 0.9, "CMS");

          TLatex* latexPrelim = new TLatex();
          latexPrelim->SetTextFont(53);
          latexPrelim->SetTextSize(28);
          latexPrelim->DrawLatexNDC(0.4, 0.9, "Preliminary");

          drawText(LABEL, xpos, 0.50, 1, 27);
          drawText(Form("%.0f - %.0f%c", centBins_i[j]/2., centBins_f[j]/2., '%'), xpos, 0.40, 1, 27);
        }

        if (i == 0) {
          drawText(Form("%.0f GeV/c < p_{T}^{#gamma} < %.0f GeV/c", ptBins[i], ptBins[i+1]), 0.25, 0.80, 1, 27);
        } else if (i != 0 && i != 4) {
          drawText(Form("%.0f GeV/c < p_{T}^{#gamma} < %.0f GeV/c", ptBins[i], ptBins[i+1]), 0.15, 0.90, 1, 27);
        } else {
          drawText(Form("p_{T}^{#gamma} > %.0f GeV/c", ptBins[i]), 0.24, 0.90, 1, 27);
        }
        if (i == 0) {
          drawText(Form("Purity : %.2f", (Float_t)fitr.purity), xpos, 0.70, 1, 27);
        } else {
          drawText(Form("Purity : %.2f", (Float_t)fitr.purity), xpos, 0.80, 1, 27);
        }
        if (i == 0) {
          drawText(Form("#chi^{2}/ndf : %.2f", (Float_t)fitr.chisq), xpos, 0.60, 1, 27);
        } else {
          drawText(Form("#chi^{2}/ndf : %.2f", (Float_t)fitr.chisq), xpos, 0.70, 1, 27);
        }

        h1D_pur[j]->SetBinContent(i+1,(Float_t)fitr.purity);
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
  // cPurity->SaveAs(Form("%s.png", outputName.Data()));
  cPurity->SaveAs(Form("output/%s.pdf", outputName.Data()));

  return 0;
}

int main(int argc, char* argv[]) {
  if (argc == 5)
    return yj_quickPhotonPurity(argv[1], argv[2], argv[3], argv[4]);

  return 1;
}
