#ifndef phoRaaCuts_v1_H
#define phoRaaCuts_v1_H

#include <TCut.h>

#define PI 3.141592653589

enum sampleType { kHIDATA, kHIMC, kHIMCEmEnr, kPPDATA, kPPMC, kPPMCEmEnr};
TString getSampleName ( sampleType colli) {
    if (colli == kHIDATA) return "pbpbDATA";
    if (colli == kHIMC) return "pbpbMC";
    if (colli == kHIMCEmEnr) return "pbpbMCEmEnr";
    if (colli == kPPDATA) return "ppDATA";
    if (colli == kPPMC) return "ppMC";
    if (colli == kPPMCEmEnr) return "ppMCEmEnr";
    return "NULL";
}
TString getSampleName ( int colli) {
    if (colli == kHIDATA) return "pbpbDATA";
    if (colli == kHIMC) return "pbpbMC";
    if (colli == kHIMCEmEnr) return "pbpbMCEmEnr";
    if (colli == kPPDATA) return "ppDATA";
    if (colli == kPPMC) return "ppMC";
    if (colli == kPPMCEmEnr) return "ppMCEmEnr";
    return "NULL";
}

TString ppDatafname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2017-03-29-nominal/pp_Data_photonRaaSkim.root";
TString ppMCfname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2017-03-29-nominal/pp_MC_photonRaaSkim.root";
TString ppMCEmEnrfname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2017-03-29-nominal/pp_EmEnrMC_photonRaaSkim.root";
TString pbpbDatafname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2017-03-29-nominal/PbPb_Data_photonRaaSkim.root";
TString pbpbMCfname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2017-03-29-nominal/PbPb_MC_photonRaaSkim.root";
TString pbpbMCEmEnrfname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2017-03-29-nominal/PbPb_EmEnrMC_photonRaaSkim.root";


//const double ptBins[] = {20,30,40,50,60,70,80,90,100,120,140,180,220};
const double ptBins[] = {40,50,60,80,999};
const double ptBins_draw[] = {40,50,60,80,120};
const int nPtBin = sizeof(ptBins)/sizeof(double) -1;
const double ptBins_i[] = {40,40,50,60,80};
const double ptBins_f[] = {999,50,60,80,999};
const int nPtBinIF = sizeof(ptBins_i)/sizeof(double);
//const double etaBins[] = {0.0,1.44,2.0,2.5};
const double etaBins[] = {0.0,1.44};
const int nEtaBin = sizeof(etaBins)/sizeof(double) -1;
const int centBins[] = {0,60,200};
const int nCentBin = sizeof(centBins)/sizeof(int) -1;
const int centBins_i[] = {0,0,60};
const int centBins_f[] = {200,60,200};
const int nCentBinIF = sizeof(centBins_i)/sizeof(int);

const TCut trigCut = "HLT_HISinglePhoton40_Eta1p5_v1";
const TCut trigCut_mc_pbpb = "HLT_HISinglePhoton40_Eta1p5_v2";
const TCut trigCut_mc_pp = "HLT_HISinglePhoton40_Eta1p5ForPPRef_v1";
const TCut evtSelFilterCut = "pcollisionEventSelection";
const TCut evtSelFilterCut_pp = "pBeamScrapingFilter && pPAprimaryVertexFilter";// pVertexFilterCutEandG is for pPb pileup
const TCut spikeRejection = "(phoSigmaIEtaIEta_2012>=0.002) && (pho_swissCrx<=0.9) && (abs(pho_seedTime)<=3)";

const TCut hoeCut = "phoHoverE<0.1";
const TCut sumIsoCut = "(pho_ecalClusterIsoR4 + pho_hcalRechitIsoR4 + pho_trackIsoR4PtCut20) < 1.0";
const TCut sigmaCut = "(phoSigmaIEtaIEta_2012)<0.010";
const TCut hotspotCut = "pho_is2015Noise==0";
//const TCut hotspotCut = "!((phoE3x3/phoE5x5 > 2/3-0.03 && phoE3x3/phoE5x5 < 2/3+0.03) && (phoE1x5/phoE5x5 > 1/3-0.03 && phoE1x5/phoE5x5 < 1/3+0.03) && (phoE2x5/phoE5x5 > 2/3-0.03 && phoE2x5/phoE5x5 < 2/3+0.03))";

const TCut dataCut = trigCut && evtSelFilterCut && spikeRejection && hotspotCut;
const TCut dataCut_pp = trigCut && evtSelFilterCut_pp && spikeRejection && hotspotCut;

const TCut phoSignalCut = hoeCut && sumIsoCut && sigmaCut && hotspotCut;


const TCut isoCut_ppGED = "((pfcIso4<=1.37) && (pfnIso4<=1.06+0.014*phoEt+0.000019*phoEt*phoEt) && pfpIso4<=(0.28+0.0053*phoEt))";
const TCut hoeCut_ppGED = "phoHoverE<0.05";
const TCut sigmaCut_ppGED = "phoSigmaIEtaIEta<0.0102";

const TCut phoSignalCut_ppGED = isoCut_ppGED && hoeCut_ppGED && sigmaCut_ppGED;


const TCut sidebandIsolation = "((pho_ecalClusterIsoR4 + pho_hcalRechitIsoR4 + pho_trackIsoR4PtCut20)>10) && ((pho_ecalClusterIsoR4 + pho_hcalRechitIsoR4 + pho_trackIsoR4PtCut20)<20) && phoHoverE<0.1";
const TCut mcIsolation = "(pho_genMatchedIndex!= -1) && mcCalIsoDR04[pho_genMatchedIndex]<5 && abs(mcPID[pho_genMatchedIndex])==22 && (abs(mcMomPID[pho_genMatchedIndex])<=22 || mcMomPID[pho_genMatchedIndex]==-999)";
const TCut mcBkgIsolation = "(pho_genMatchedIndex!= -1) && !(mcCalIsoDR04[pho_genMatchedIndex]<5 && abs(mcPID[pho_genMatchedIndex])==22 && (abs(mcMomPID[pho_genMatchedIndex])<=22 || mcMomPID[pho_genMatchedIndex]==-999))"; 

TString pbpbEff_fname_cent1 = "/home/goyeonju/CMS/2016/PhotonAnalysis2016/160107_phoRaaEfficiency/output/hist_efficiency_total_pbpb_cent0-60_v1_nohotspot.root";
TString pbpbEff_fname_cent2 = "/home/goyeonju/CMS/2016/PhotonAnalysis2016/160107_phoRaaEfficiency/output/hist_efficiency_total_pbpb_cent60-200_v1_nohotspot.root";
TString ppEff_fname = "/home/goyeonju/CMS/2016/PhotonAnalysis2016/160107_phoRaaEfficiency/output/hist_efficiency_total_pp_v1_nohotspot.root";


#endif

