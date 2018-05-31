#ifndef PhotonPurity_h
#define PhotonPurity_h

#include <TH1.h>
#include <TNtuple.h>
#include <TCut.h>
#include <TF1.h>
#include <string>
#include "../phoRaaCuts/phoRaaCuts_temp.h"

#include "../ElectroWeak-Jet-Track-Analyses/Utilities/interface/CutConfigurationParser.h"
#include "../ElectroWeak-Jet-Track-Analyses/Histogramming/Purity.h"

Purity* getPurity(const TString coll, CutConfiguration config, TTree *dataTree, TTree *mcTree,
		       TCut dataCandidateCut, TCut sidebandCut,
		       TCut mcSignalCut, TString fname_SBcorr="", TTree *bkgmcTree=0)
{
  Float_t signalShift = config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_puritySignalShift];
  Float_t backgroundShift = config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_purityBackgroundShift];
  const Int_t nSIGMABINS = config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].i[CUTS::PHO::k_puritySieieBins];
  const Float_t maxSIGMA = config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_puritySieieHistMax];
  const std::string mcWeightLabel_s = config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].s[CUTS::PHO::k_monteCarloWeightLabel];
  TCut mcWeightLabel = mcWeightLabel_s.c_str();
  const int divisions = 1;
  static int tmp=0;
  Float_t range_low = config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_purityFitLow];
  Float_t range_high = config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_purityFitHigh];
  Float_t sieie_cut = config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_puritySieieThreshold];
  
  TH1D* hCand = new TH1D(Form("cand_%d",tmp),"",nSIGMABINS,0,maxSIGMA);
  TH1D* hBkg = (TH1D*)hCand->Clone(Form("bkg_%d",tmp));
  TH1D* hSig = (TH1D*)hCand->Clone(Form("sig_%d",tmp));

  TString sigshift = "+";
  sigshift += signalShift;
  TString bkgshift = "+";
  bkgshift += backgroundShift;
 
  TString varHere="";
  if(coll=="pp") varHere=purityVar_pp;
  else if(coll=="pbpb") varHere=purityVar;
  else cout << "There's no '" << coll << "' type of collision" << endl;

  dataTree->Project(hCand->GetName(), varHere, dataCandidateCut, "");
  if(bkgmcTree==0){
    dataTree->Project(hBkg->GetName(), varHere+bkgshift, sidebandCut, "");
  } else {
    bkgmcTree->Project(hBkg->GetName(), varHere+bkgshift, mcWeightLabel*sidebandCut, "");
  }
  mcTree->Project(hSig->GetName(), varHere+sigshift, mcWeightLabel*mcSignalCut, "");

  std::cout << "dataCount: " << hCand->GetEntries() << std::endl;
  std::cout << "bkgCount: " << hBkg->GetEntries() << std::endl;
  std::cout << "sigCount: " << hSig->GetEntries() << std::endl;
  
  TFile* fcorr;
  TF1* f1; 
  cout << "SideBand correction file :: " << fname_SBcorr << endl;
  if(fname_SBcorr!="") {
      fcorr = new TFile(fname_SBcorr);
      f1 = (TF1*) fcorr->Get("f1");
      f1->SetName("f1");
      cout << "formula : " << f1->GetExpFormula()<<", p0="<<f1->GetParameter(0)<<", p1="<<f1->GetParameter(1) << ", f(0) = " << f1->Eval(0)<< endl;

      for(int vv=0;vv<hBkg->GetNbinsX();++vv){
          double binVal = hBkg->GetBinContent(vv+1);
          double binErr = hBkg->GetBinError(vv+1);
          double binX = hBkg->GetBinLowEdge(vv+1)+(double)hBkg->GetBinWidth(vv+1)/2.;
          hBkg->SetBinContent(vv+1,binVal*abs(f1->Eval(binX)));
          hBkg->SetBinError(vv+1,binErr*abs(f1->Eval(binX)));
      }
  }

  /* fit using binned templates */
  Templates* templates = new Templates(hCand, hSig, hBkg, divisions);

  //Purity purity;
  Purity* purity = new Purity();
  purity->fit(templates, hCand, range_low, range_high, sieie_cut);

  std::cout << "nsig: " << purity->nsig << std::endl;
  std::cout << "nsigerr: " << purity->nsigerr << std::endl;
  std::cout << "purity: " << purity->purity << std::endl;
  std::cout << "chisq: " << purity->chisq << std::endl;
  std::cout << "ndf: " << purity->ndf << std::endl;
  std::cout << "shift: " << purity->shift << std::endl;
  std::cout << "shifterr: " << purity->shifterr << std::endl;
  std::cout << "ratio: " << purity->ratio << std::endl;
  std::cout << "ratioerr: " << purity->ratioerr << std::endl;

  //purity->write();

  //purity_values[i][j] = purity->purity;

  //PhotonPurity fitr = doFit(config, hSig, hBkg, hCand);

 // std::cout << ">>>>Purity: " << fitr.purity << std::endl;
 // std::cout << "nSig: " << fitr.nSig << std::endl;
 // std::cout << "chisq: " << fitr.chisq << std::endl;

 // delete hSig;
 // delete hBkg;
 // delete hCand;
  //delete fcorr;
  //delete f1;

  //fitr.sigMeanShift = signalShift;
    tmp++;
  return purity;
}

#endif
