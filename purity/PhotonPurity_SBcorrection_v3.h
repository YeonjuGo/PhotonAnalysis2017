#ifndef PhotonPurity_h
#define PhotonPurity_h

#include <TH1.h>
#include <TNtuple.h>
#include <TCut.h>
#include <TF1.h>
#include <string>
#include "../phoRaaCuts/phoRaaCuts_temp.h"

#include "../ElectroWeak-Jet-Track-Analyses/Utilities/interface/CutConfigurationParser.h"

class PhotonPurity {
public:
  Double_t nSig;
  Double_t nSigErr;
  Double_t purity;
  Double_t purityErr;
  Double_t chisq;
  Double_t sigMeanShift;
  Double_t sigMeanShiftErr;
  Double_t ratio;
  Double_t ratioErr;
  Int_t ndf;

  TH1F *sigPdf;
  TH1F *bckPdf;
  TH1D *data;
};

class histFunction2
{
public:
  histFunction2(TH1D *h, TH1D *h2);
  ~histFunction2(){
    delete histBck;
    delete histSig;
  };

  Double_t evaluate(Double_t *x, Double_t *par);
  TH1D *histSig;
  TH1D *histBck;
  Double_t lowEdge;
  Double_t highEdge;
  Double_t nbin;
};

histFunction2::histFunction2(TH1D *h,TH1D *h2)
{
  histSig=(TH1D*)h->Clone();
  histBck=(TH1D*)h2->Clone();

  nbin=h->GetNbinsX();
  lowEdge=h->GetBinLowEdge(1);
  highEdge=h->GetBinLowEdge(nbin+1);

  histSig->SetName("hSig");
  histSig->Scale(1./histSig->Integral(1,histSig->GetNbinsX()+1));
  histBck->SetName("hBck");
  histBck->Scale(1./histBck->Integral(1,histBck->GetNbinsX()+1));
}

Double_t histFunction2::evaluate(Double_t *x, Double_t *par) {

  Double_t xx = x[0];
  Int_t binNum=histBck->FindBin(xx);
  Int_t shiftedSigBinNum = histSig->FindBin(xx + par[2]);
  return par[0]*(histSig->GetBinContent(shiftedSigBinNum)*par[1]+histBck->GetBinContent(binNum)*(1-par[1]));
}


PhotonPurity doFit(CutConfiguration config, TH1D* hSig=0, TH1D* hBkg=0, TH1D* hData1=0)
{
  Float_t varLow = config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_purityFitLow];
  Float_t varHigh = config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_purityFitHigh];
  Float_t purityBinVal = config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_puritySieieThreshold];

  TH1D* hDatatmp = (TH1D*)hData1->Clone(Form("%s_datatmp",hData1->GetName()));
  Int_t nBins = hDatatmp->GetNbinsX();
  histFunction2 *myFits = new histFunction2(hSig,hBkg);
  TF1 *f = new TF1("f",myFits,&histFunction2::evaluate,varLow,varHigh,3);
  f->SetParameters( hDatatmp->Integral(1,nBins+1), 0.7, 0.0);
  f->SetParLimits(1,0,1);
  //f->SetParLimits(2,-0.0001,+0.0001);
  f->FixParameter(2,0.0);
  hDatatmp->Fit("f","WL M 0 Q","",varLow,varHigh);
  hDatatmp->Fit("f","WL M 0 Q","",varLow,varHigh);
  hDatatmp->Fit("f","WL M 0 Q","",varLow,varHigh);

  PhotonPurity res;
  res.nSig =0;
  Double_t nev = f->GetParameter(0);
  Double_t ratio = f->GetParameter(1);
  Double_t shift = f->GetParameter(2);
  Double_t nevError = f->GetParError(0);
  Double_t ratioError = f->GetParError(1);
  Double_t shiftError = f->GetParError(2);
  Double_t purityError = f->GetParError(2);

  std::cout << "nev: " << nev << " nevError: " << nevError << std::endl;
  std::cout << "ratio: " << ratio << " ratioError: " << ratioError << std::endl;
  std::cout << "shift: " << shift << " shiftError: " << shiftError << std::endl;

  res.nSig    = nev * ratio;
  res.nSigErr = nev * ratioError;
  res.chisq = (Double_t)f->GetChisquare();
  res.ndf = (Int_t)f->GetNDF();
  res.sigMeanShift = shift; 
  res.sigMeanShiftErr = shiftError; 
  res.ratioErr = ratioError; 
  res.ratio = ratio; 

  TH1F *hSigPdf = (TH1F*)hSig->Clone(Form("%s_tmp",hSig->GetName()));
  hSigPdf->Scale(res.nSig/hSigPdf->Integral(1,nBins+1));

  TH1F *hBckPdf = (TH1F*)hBkg->Clone(Form("%s_tmp",hBkg->GetName()));
  hBckPdf->Scale((nev-res.nSig)/hBckPdf->Integral(1,nBins+1));

  Double_t ss1 = hSigPdf->Integral(1, hSigPdf->FindBin(purityBinVal),"width");
  Double_t bb1 = hBckPdf->Integral(1, hBckPdf->FindBin(purityBinVal),"width");
  res.purity = ss1/(ss1+bb1);
  res.purityErr = ss1/(ss1+bb1)*(TMath::Sqrt((res.nSigErr/res.nSig)*(res.nSigErr/res.nSig)+(res.ratioErr/res.ratio)*(res.ratioErr/res.ratio)));

  res.sigPdf = (TH1F*)hSigPdf->Clone(Form("%s_sig",hSig->GetName()));
  res.bckPdf = (TH1F*)hBckPdf->Clone(Form("%s_bck",hBkg->GetName()));
  res.data = (TH1D*)hData1->Clone(Form("%s_cand",hData1->GetName()));

  return res;
}

PhotonPurity getPurity(const TString coll, CutConfiguration config, TTree *dataTree, TTree *dataTree_high, TTree *mcTree,
		       TCut dataCandidateCut, TCut sidebandCut,
		       TCut mcSignalCut, TCut dataWeightLabel, TString fname_SBcorr="", TTree *bkgmcTree=0)
{
  Float_t signalShift = config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_puritySignalShift];
  Float_t backgroundShift = config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_purityBackgroundShift];
  const Int_t nSIGMABINS = config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].i[CUTS::PHO::k_puritySieieBins];
  const Float_t maxSIGMA = config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].f[CUTS::PHO::k_puritySieieHistMax];
  const std::string mcWeightLabel_s = config.proc[CUTS::kHISTOGRAM].obj[CUTS::kPHOTON].s[CUTS::PHO::k_monteCarloWeightLabel];
  TCut mcWeightLabel = mcWeightLabel_s.c_str();
    cout << "Weight is applied : " << mcWeightLabel << endl;
  //TCut dataWeightLabel = "phoPreScale";
  //if(coll=="pbpb") 
    cout << "DATA Weight is applied : " << dataWeightLabel << endl;
  TH1D* hCand = new TH1D("cand","",nSIGMABINS,0,maxSIGMA);
  TH1D* hCand_high = (TH1D*)hCand->Clone("cand_high");
  TH1D* hBkg = (TH1D*)hCand->Clone("bkg");
  TH1D* hBkg_high = (TH1D*)hCand->Clone("bkg_high");
  TH1D* hSig = (TH1D*)hCand->Clone("sig");

  TString sigshift = "+";
  sigshift += signalShift;
  TString bkgshift = "+";
  bkgshift += backgroundShift;
 
  TString varHere="phoSigmaIEtaIEta_2012";
  //if(coll=="pp") varHere=purityVar_pp;
  //else if(coll=="pbpb") varHere=purityVar;
  //else cout << "There's no '" << coll << "' type of collision" << endl;

    TCut dataCutHigh = dataCandidateCut && trigCut_high;
    TCut dataCutLow = dataCandidateCut && trigCut_low;
    if(coll=="pp") dataCutHigh = dataCandidateCut && trigCut_pp_high;
    if(coll=="pp") dataCutLow = dataCandidateCut && trigCut_pp_low;
    TCut sideCutHigh = sidebandCut && trigCut_high;
    TCut sideCutLow = sidebandCut && trigCut_low;
    if(coll=="pp") sideCutHigh = sidebandCut && trigCut_pp_high;
    if(coll=="pp") sideCutLow = sidebandCut && trigCut_pp_low;
    


  //if(doPreScale){
      dataTree->Project(hCand->GetName(), varHere, dataCutLow, "");
      //dataTree->Project(hCand->GetName(), varHere, dataWeightLabel*dataCutLow, "");
      dataTree_high->Project(hCand_high->GetName(), varHere, dataCutHigh, "");
      //dataTree->Project(hCand->GetName(), varHere, dataWeightLabel*dataCandidateCut, "");
      //dataTree_high->Project(hCand_high->GetName(), varHere, dataCandidateCut, "");
      hCand->Add(hCand_high);
  //} else{
  //    dataTree->Project(hCand->GetName(), varHere, dataCandidateCut, "");
  //}

  if(bkgmcTree==0){
    dataTree->Project(hBkg->GetName(), varHere+bkgshift, sideCutLow, "");
    //dataTree->Project(hBkg->GetName(), varHere+bkgshift, dataWeightLabel*sideCutLow, "");
    dataTree_high->Project(hBkg_high->GetName(), varHere+bkgshift, sideCutHigh, "");
    //dataTree->Project(hBkg->GetName(), varHere+bkgshift, dataWeightLabel*sidebandCut, "");
    //dataTree_high->Project(hBkg_high->GetName(), varHere+bkgshift, sidebandCut, "");
    hBkg->Add(hBkg_high);
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
  
  PhotonPurity fitr = doFit(config, hSig, hBkg, hCand);

  std::cout << ">>>>Purity: " << fitr.purity << std::endl;
  std::cout << ">>>>PurityError: " << fitr.purityErr << std::endl;
  std::cout << "nSig: " << fitr.nSig << std::endl;
  std::cout << "nSigErr: " << fitr.nSigErr << std::endl;
  std::cout << "chisq: " << fitr.chisq << std::endl;
  std::cout << "shift: " << fitr.sigMeanShift << std::endl;
  std::cout << "shiftErr: " << fitr.sigMeanShiftErr << std::endl;
  std::cout << "ratio: " << fitr.ratio<< std::endl;
  std::cout << "ratioErr: " << fitr.ratioErr<< std::endl;

  delete hSig;
  delete hBkg;
  delete hCand;
  delete hBkg_high;
  delete hCand_high;
  //delete fcorr;
  //delete f1;

  //fitr.sigMeanShift = signalShift;

  return fitr;
}

#endif
