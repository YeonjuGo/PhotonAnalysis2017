#ifndef phoRaaCuts_170524_temp_v2_H
#define phoRaaCuts_170524_temp_v2_H
//isoCut = sumIso<1GeV from v1
//
//
//
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

//////////////// FILES ///////////////////
TString ppDatafname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2017-03-29-nominal/pp_Data_photonRaaSkim.root";
TString ppMCfname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2017-03-29-nominal/pp_MC_photonRaaSkim.root";
TString ppMCEmEnrfname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2017-03-29-nominal/pp_EmEnrMC_photonRaaSkim.root";
TString pbpbDatafname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2017-03-29-nominal/PbPb_Data_photonRaaSkim.root";
TString pbpbMCfname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2017-03-29-nominal/PbPb_MC_photonRaaSkim.root";
TString pbpbMCEmEnrfname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2017-03-29-nominal/PbPb_EmEnrMC_photonRaaSkim.root";

TString pbpbData_config = "/home/goyeonju/CMS/2016/PhotonAnalysis2016/ElectroWeak-Jet-Track-Analyses/CutConfigurations/photonRaa.conf";
TString pbpbMC_config = "/home/goyeonju/CMS/2016/PhotonAnalysis2016/ElectroWeak-Jet-Track-Analyses/CutConfigurations/photonRaa_mc.conf";
TString ppData_config = "/home/goyeonju/CMS/2016/PhotonAnalysis2016/ElectroWeak-Jet-Track-Analyses/CutConfigurations/photonRaa_pp.conf";
TString ppMC_config = "/home/goyeonju/CMS/2016/PhotonAnalysis2016/ElectroWeak-Jet-Track-Analyses/CutConfigurations/photonRaa_pp_mc.conf";

/////////////// BINNING ///////////////////
const double ptBins[] = {40,50,60,80,999};
const double ptBins_draw[] = {40,50,60,80,120};
const int nPtBin = sizeof(ptBins)/sizeof(double) -1;
const double ptBins_i[] = {40,40,50,60,80};
const double ptBins_f[] = {999,50,60,80,999};
const int nPtBinIF = sizeof(ptBins_i)/sizeof(double);
const int centBins[] = {0,60,200};
const int nCentBin = sizeof(centBins)/sizeof(int) -1;
const int centBins_i[] = {0,0,60};
const int centBins_f[] = {200,60,200};
const int nCentBinIF = sizeof(centBins_i)/sizeof(int);
const double TA[nCentBinIF] = {5.607*1000,15.41*1000,1.405*1000};

/////////////// CUTS ///////////////////
//Trigger and EvtSelection Cuts
const TCut trigCut = "HLT_HISinglePhoton40_Eta1p5_v1";
const TCut trigCut_mc = "HLT_HISinglePhoton40_Eta1p5_v2";
const TCut trigCut_mc_pp = "HLT_HISinglePhoton40_Eta1p5ForPPRef_v1";
const TCut evtSelFilterCut = "pcollisionEventSelection";
const TCut evtSelFilterCut_pp = "pBeamScrapingFilter && pPAprimaryVertexFilter";// pVertexFilterCutEandG is for pPb pileup
//Noise Cuts
const TCut spikeRejection = "(phoSigmaIEtaIEta_2012>=0.002) && (pho_swissCrx<=0.9) && (abs(pho_seedTime)<=3)";
const TCut hotspotCut = "pho_is2015Noise==0";
const TCut electronCut = "pho_isEle==0";
const TCut noiseCut = spikeRejection && hotspotCut && electronCut;
//Kinematic Cuts
const TCut etaCut = "abs(phoEta)<1.44";
//Isolation Cuts for PbPb
const TCut hoeCut = "phoHoverE<0.1";
const TCut isoCut = "pho_sumIsoCorrected<1.0";
const TCut sigmaCut = "phoSigmaIEtaIEta_2012<0.010";
const TCut nonIsoSBCut = "pho_sumIsoCorrected > 10.0 && pho_sumIsoCorrected < 20.0";
//Isolation Cuts for pp
const TCut isoCut_pp = isoCut;
const TCut hoeCut_pp = "phoHoverE<0.05";
//const TCut isoCut_pp = "((pfcIso4<=1.37) && (pfnIso4<=1.06+0.014*phoEt+0.000019*phoEt*phoEt) && pfpIso4<=(0.28+0.0053*phoEt))";
//const TCut hoeCut_pp = "phoHoverE<0.05";
const TCut sigmaCut_pp = "phoSigmaIEtaIEta<0.0102";
const TCut nonIsoSBCut_pp = nonIsoSBCut;

const TCut dataCut = trigCut && evtSelFilterCut && spikeRejection && hotspotCut && electronCut;
const TCut dataCut_pp = trigCut && evtSelFilterCut_pp && spikeRejection && hotspotCut && electronCut;
const TCut mcCut = trigCut_mc && evtSelFilterCut && noiseCut;
const TCut mcCut_pp = trigCut_mc_pp && evtSelFilterCut_pp && noiseCut;
const TCut phoSignalCut = dataCut && hoeCut && isoCut && sigmaCut;
const TCut phoSignalCut_pp = dataCut_pp && hoeCut_pp && isoCut_pp && sigmaCut_pp;

/////////////// FOR PURITY ///////////////////
const TString purityVar= "phoSigmaIEtaIEta_2012";
const TString purityVar_pp= "phoSigmaIEtaIEta_2012";
const TCut sampleIsolation = dataCut && hoeCut && isoCut;
const TCut sampleIsolation_pp = dataCut_pp && hoeCut_pp && isoCut_pp;
const TCut sidebandIsolation = dataCut && hoeCut && nonIsoSBCut;
const TCut sidebandIsolation_pp = dataCut_pp && hoeCut_pp && nonIsoSBCut_pp;
//Only Gen Info
const TCut mcIsolation = "(pho_genMatchedIndex!= -1) && abs(pho_genPID)==22 && pho_genCalIsoDR04<5 && (abs(pho_genMomPID)<=22 || pho_genMomPID==-999)";
const TCut mcBkgIsolation = "(pho_genMatchedIndex!= -1) && abs(pho_genPID)==22 && !(pho_genCalIsoDR04<5 && (abs(pho_genMomPID)<=22 || pho_genMomPID==-999))";
const TCut mcSignalCut_woKine = mcIsolation && mcCut;
const TCut mcSignalCut_woKine_pp = mcIsolation && mcCut_pp;

#endif

