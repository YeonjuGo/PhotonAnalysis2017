#ifndef PhotonPurity_h
#define PhotonPurity_h

#include <TH1.h>
#include <TNtuple.h>
#include <TCut.h>
#include <TF1.h>
#include <string>
//#include "../phoRaaCuts/phoRaaCuts_temp.h"

#include "../ElectroWeak-Jet-Track-Analyses/Utilities/interface/CutConfigurationParser.h"

class PhotonPurity {
public:
  Double_t nev;
  Double_t nSig;
  Double_t nSigErr;
  Double_t purity;
  Double_t purityErr;
  Double_t chisq;
  Double_t sigMeanShift;
  Double_t sigMeanShiftErr;
  Double_t ratio;
  Double_t ratioErr;
  Double_t impurity;
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


PhotonPurity doFit(CutConfiguration config, TH1D* hSig=0, TH1D* hBkg=0, TH1D* hData1=0, double impurity = 0 )
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
  //f->SetParLimits(1,0,0.45);
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

  res.nev    = nev;
  res.nSig    = nev * ratio;
  res.nSigErr = nev * ratioError;
  res.chisq = (Double_t)f->GetChisquare();
  res.ndf = (Int_t)f->GetNDF();
  res.sigMeanShift = shift; 
  res.sigMeanShiftErr = shiftError; 
  res.ratioErr = ratioError; 
  res.ratio = ratio; 
  res.impurity = impurity; 

  TH1F *hSigPdf = (TH1F*)hSig->Clone(Form("%s_tmp",hSig->GetName()));
  hSigPdf->Scale(res.nSig/hSigPdf->Integral(1,nBins+1));

  TH1F *hBckPdf = (TH1F*)hBkg->Clone(Form("%s_tmp",hBkg->GetName()));
  hBckPdf->Scale((nev-res.nSig)/hBckPdf->Integral(1,nBins+1));

  Double_t ss1 = hSigPdf->Integral(1, hSigPdf->FindBin(purityBinVal),"width");
  Double_t bb1 = hBckPdf->Integral(1, hBckPdf->FindBin(purityBinVal),"width");
  res.purity = ss1/(ss1+bb1)+(bb1*impurity)/(ss1+bb1);
  res.purityErr = ss1/(ss1+bb1)*(TMath::Sqrt((res.nSigErr/res.nSig)*(res.nSigErr/res.nSig)+(res.ratioErr/res.ratio)*(res.ratioErr/res.ratio)));

  res.sigPdf = (TH1F*)hSigPdf->Clone(Form("%s_sig",hSig->GetName()));
  res.bckPdf = (TH1F*)hBckPdf->Clone(Form("%s_bck",hBkg->GetName()));
  res.data = (TH1D*)hData1->Clone(Form("%s_cand",hData1->GetName()));

  return res;
}

PhotonPurity getPurity(const TString coll, CutConfiguration config, TTree *dataTree, TTree *mcTree,
		       TCut dataCandidateCut, TCut sidebandCut,
		       TCut mcSignalCut, TCut dataWeightLabel, double inputNev = 0.0,  double inputRatio = 0.0, int niter=0, TCut mcSignalSBCut = "",
               TString outputName ="", TString fname_SBcorr="", TTree *bkgmcTree=0)
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
  TH1D* hBkg = (TH1D*)hCand->Clone("bkg");
  TH1D* hSig = (TH1D*)hCand->Clone("sig");
  TH1D* hBkg_temp = (TH1D*)hCand->Clone("bkg_temp");
  TH1D* hSig_sb = (TH1D*)hCand->Clone("sig_sb");

  TString sigshift = "+";
  sigshift += signalShift;
  TString bkgshift = "+";
  bkgshift += backgroundShift;
 
  TString varHere="phoSigmaIEtaIEta_2012";
  //if(coll=="pp") varHere=purityVar_pp;
  //else if(coll=="pbpb") varHere=purityVar;
  //else cout << "There's no '" << coll << "' type of collision" << endl;



  //if(doPreScale){
  dataTree->Project(hCand->GetName(), varHere, dataCandidateCut, "");
  //dataTree->Project(hCand->GetName(), varHere, dataWeightLabel*dataCandidateCut, "");
  //} else{
  //    dataTree->Project(hCand->GetName(), varHere, dataCandidateCut, "");
  //}

  if(bkgmcTree==0){
      dataTree->Project(hBkg_temp->GetName(), varHere+bkgshift, sidebandCut, "");
  } else {
      bkgmcTree->Project(hBkg_temp->GetName(), varHere+bkgshift, mcWeightLabel*sidebandCut, "");
  }
  mcTree->Project(hSig->GetName(), varHere+sigshift, mcWeightLabel*mcSignalCut, "");

  double sig_count = hSig->GetEntries();
  std::cout << "dataCount: " << hCand->GetEntries() << std::endl;
  std::cout << "bkgCount: " << hBkg_temp->GetEntries() << std::endl;
  std::cout << "sigCount: " << sig_count << std::endl;

  double purityBinVal = 0.010;
  double impurity = 0.0;
  if(inputNev!=0 && niter!=0){
      Int_t nBins = hCand->GetNbinsX();
      double Nsig = inputNev * inputRatio;
      hSig->Scale(Nsig/hSig->Integral(1,nBins+1));
      //hBkg_temp->Scale((inputNev-Nsig)/hBkg_temp->Integral(1,nBins+1));
      
      mcTree->Project(hSig_sb->GetName(), varHere+sigshift, mcWeightLabel*mcSignalSBCut, "");
      TH1D* hSig_sb_beforeScale = (TH1D*) hSig_sb->Clone("hSig_sb_beforeScale");
      double sig_sb_count = hSig_sb->GetEntries();
      std::cout << "sigInSBCount: " << sig_sb_count << std::endl;

      hSig_sb->Scale(Nsig*(sig_sb_count/sig_count)/hSig_sb->Integral(1,nBins+1));
      hBkg = (TH1D*) hBkg_temp->Clone("bkg");
      hBkg->Add(hSig_sb,-1); 
  
      Double_t ss1 = hSig_sb->Integral(1, hSig_sb->FindBin(purityBinVal),"width");
      Double_t bb1 = hBkg_temp->Integral(1, hBkg_temp->FindBin(purityBinVal),"width");
      impurity = ss1/bb1;
      //double impurityErr = ss1/(bb1)*(TMath::Sqrt((res.nSigErr/res.nSig)*(res.nSigErr/res.nSig)+(res.ratioErr/res.ratio)*(res.ratioErr/res.ratio)));
      
      std::cout << "Normalized Background DATA counts: " << hBkg_temp->Integral() << std::endl;
      std::cout << "Normalized Signal MC in Sideband counts: " << hSig_sb->Integral() << std::endl;
      std::cout << " ::::: " << niter << " th iteration ::::: "  << std::endl;
      std::cout << "Input nEvt  : " << inputNev<< std::endl;
      std::cout << "Input Ratio : " << inputRatio<< std::endl;
      std::cout << "Impurity : " << impurity<< std::endl;

      TCanvas* ctt = new TCanvas("ctt", "",300,300);
      hBkg_temp->SetLineColor(1); 
      hBkg->SetLineColor(8); 
      hSig->SetLineColor(2); 
      hSig_sb->SetLineColor(2); 
      //hSig_sb_beforeScale->SetLineColor(kYellow+1); 
      //hSig->Draw("hist");
      hBkg_temp->Draw("hist");
      hBkg->Draw("hist same");
      hSig_sb->Draw("hist same");
      //hSig_sb_beforeScale->Draw("hist same");

      
      TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/purity/";
      ctt->SaveAs(Form("%sfigures/%s_SigSubInSB.pdf",dir.Data(),outputName.Data()));

      delete ctt;
      delete hSig_sb_beforeScale;
  } else{
      hBkg = (TH1D*) hBkg_temp->Clone("bkg");
  }
  
  PhotonPurity fitr = doFit(config, hSig, hBkg_temp, hCand, impurity);

  std::cout << ">>>>Purity: " << fitr.purity << std::endl;
  std::cout << ">>>>PurityError: " << fitr.purityErr << std::endl;
  std::cout << "nev: " << fitr.nev<< std::endl;
  std::cout << "nSig: " << fitr.nSig << std::endl;
  std::cout << "nSigErr: " << fitr.nSigErr << std::endl;
  std::cout << "chisq: " << fitr.chisq << std::endl;
  //std::cout << "shift: " << fitr.sigMeanShift << std::endl;
  //std::cout << "shiftErr: " << fitr.sigMeanShiftErr << std::endl;
  std::cout << "ratio: " << fitr.ratio<< std::endl;
  std::cout << "ratioErr: " << fitr.ratioErr<< std::endl;
  std::cout << "Impurity in bkg sideband (Signal contamination): " << fitr.impurity<< std::endl;

  delete hSig;
  delete hSig_sb;
  delete hBkg;
  delete hBkg_temp;
  delete hCand;
  //delete fcorr;
  //delete f1;

  //fitr.sigMeanShift = signalShift;

  return fitr;
}

#endif
