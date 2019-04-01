#ifndef phoRaaCuts_180817_temp_v23_H 
#define phoRaaCuts_180817_temp_v23_H 
// 1. pp photon selection(ID cuts) is from EGamma POG.
// 2. pbpb MC is CYMBAL total(v1+ext) and v14 of EmEnrichedDijet
// 3. centrality bin (0,10,30,50,100)
// 4. pp is GED 
// 5. (pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20) instead of sumIsoCorrected.  
// 6. sumIso < 1 GeV 
// 7. pt bin (20,30,40,50,60,80,100,130,200) with lower pt PDs
// 8. electron rejection has been seperated from noise cut 
// 9. photon energy correction with DSCB 
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
TString ppDatafname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-08-15-nominal/pp_Data_photonRaaSkim_HighPtLowerPhotons.root";
TString ppDatafname_high = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-08-15-nominal/pp_Data_photonRaaSkim_HighPtPhoton30AndZ.root";
TString ppMCfname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-08-15-nominal/pp_MC_photonRaaSkim.root";
TString ppMCEmEnrfname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-08-15-nominal/pp_EmEnrMC_photonRaaSkim.root";
TString pbpbDatafname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-08-15-nominal/PbPb_Data_photonRaaSkim_HIHardProbes_HIHardProbesPhotons.root";
TString pbpbDatafname_high = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-08-15-nominal/PbPb_Data_photonRaaSkim_HIPhoton40AndZ.root";
TString pbpbMCfname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-08-15-nominal/PbPb_MC_photonRaaSkim_Cymbal.root";
TString pbpbMCEmEnrfname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-08-15-nominal/PbPb_EmEnrMC_photonRaaSkim.root";
TString pbpbData_config = "/home/goyeonju/CMS/2016/PhotonAnalysis2016/ElectroWeak-Jet-Track-Analyses/CutConfigurations/photonRaa.conf";
TString pbpbMC_config = "/home/goyeonju/CMS/2016/PhotonAnalysis2016/ElectroWeak-Jet-Track-Analyses/CutConfigurations/photonRaa_mc.conf";
TString ppData_config = "/home/goyeonju/CMS/2016/PhotonAnalysis2016/ElectroWeak-Jet-Track-Analyses/CutConfigurations/photonRaa_pp.conf";
TString ppMC_config = "/home/goyeonju/CMS/2016/PhotonAnalysis2016/ElectroWeak-Jet-Track-Analyses/CutConfigurations/photonRaa_pp_mc.conf";
TString pbpb_forest_inputList = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/inputfilelist/pbpblist_v14_HydjetCymbal.txt"; 
TString pp_forest_inputList = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/inputfilelist/pplist.txt"; 
TString pbpb_recoEfficiency= "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/output/pbpb_reco_efficiency_Cymbal_withExt_0731.root";
TString pp_recoEfficiency = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/output/pp_reco_efficiency_withExt_0731.root";
TString pp_trigEfficiency = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/output/pp_trigger_efficiency_photon_skim_low_doIDcut1_doPreScale1_doAnalysisBin1.root";

/////////////// BINNING ///////////////////
const double ptBins[] = {20,30,40,50,60,80,100,130,200};
const double ptBins_draw[] = {20,30,40,50,60,80,100,130,200};
const double ptBins_draw_final[] = {10,20,30,40,50,60,80,100,130,200};
const double ptBins_mean_pbpb[] = {24.9978,34.0831,44.1832,54.2284,67.949,87.9602,111.623,152.674};
const double ptBins_mean_pp[] = {23.7754,33.8593,44.1152,54.4049,68.1255,88.3309,111.783,153.876};
//const double ptBins_mean_pbpb[] = {44.1827,54.2862,67.7425,88.1946,111.643};
//const double ptBins_mean_pp[] = {44.5213,54.188,67.5644,88.1521,111.85};
const int nPtBin = sizeof(ptBins)/sizeof(double) -1;
const double ptBins_i[] = {20,20,30,40,50,60,80,100,130};
const double ptBins_f[] = {200,30,40,50,60,80,100,130,200};
const int nPtBinIF = sizeof(ptBins_i)/sizeof(double);
const int centBins[] = {0,20,60,100,200};
const int nCentBin = sizeof(centBins)/sizeof(int) -1;
const int centBins_i[] = {0,0,20,60,100};
const int centBins_f[] = {200,20,60,100,200};
const int rejectPtBins[] = {0,0,0,1,2};
const int nCentBinIF = sizeof(centBins_i)/sizeof(int);
const double TA[nCentBinIF] = {5.607*1000,23.22*1000,11.51*1000,3.819*1000,0.4395*1000}; 
//const double TA[nCentBinIF] = {5.762*1000,23.651*1000,11.814*1000,4.026*1000,0.4885*1000}; //TAA up
////const double TA[nCentBinIF] = {5.416*1000,22.531*1000,11.122*1000,3.611*1000,0.4075*1000}; //TAA down
const double TA_err[nCentBinIF] = {0.089,0.017,0.024,0.054,0.112}; //err {8.9 1.7, 2.4, 5.4, 11.2} % 
const double TA_err_up[nCentBinIF] = {0.034,0.03,0.034,0.054,0.112}; //err {3.4, 3.0, 3.4, 5.4, 11.2} % 
const double TA_err_down[nCentBinIF] = {0.028,0.019,0.026,0.054,0.073}; //err {2.8, 1.9, 2.6, 5.4, 7.3} % 
const double TA_up[nCentBinIF] = {5.762*1000,23.651*1000,11.814*1000,4.026*1000,0.4885*1000}; //TAA up 
const double TA_down[nCentBinIF] = {5.416*1000,22.531*1000,11.122*1000,3.611*1000,0.4075*1000}; //TAA down
//const double TA[nCentBinIF] = {6.108*1000,23.612*1000,11.784*1000,1.571*1000}; //err {8.9 1.7, 2.4, 12} % 
//double lumi_pp = 28.0302*1e12; //2.3 % err 

/////////////// CUTS ///////////////////
//Systematics
const TString phoEtVar = "phoEtCorrected";
//const TString phoEtVar = "phoEtCorrected_sys"; //E scale
//const TString phoEtVar = "phoEtCorrected_resSys_sig"; //res up
//const TString phoEtVar = "phoEtCorrected_resSys_sig2"; //res down
//Trigger and EvtSelection Cuts
const TCut trigCut_low = "HLT_HISinglePhoton20_Eta1p5_v1 || HLT_HISinglePhoton20_Eta1p5_v2";
const TCut trigCut_high = "HLT_HISinglePhoton40_Eta1p5_v1";
//const TCut trigCut_high = "HLT_HISinglePhoton40_Eta1p5_v1";
const TCut trigCut_pp_low = "HLT_HISinglePhoton20_Eta1p5_v1";
const TCut trigCut_pp_high = "HLT_HISinglePhoton40_Eta1p5_v1";
//const TCut trigCut_pp_high = "HLT_HISinglePhoton40_Eta1p5_v1 || HLT_HISinglePhoton30_Eta1p5_v1";
const TCut trigCut_mc = "(1==1)";
//const TCut trigCut_mc = "HLT_HISinglePhoton15_Eta1p5_v2";
const TCut trigCut_mc_pp = "(1==1)";
//const TCut trigCut_mc_pp = "HLT_HISinglePhoton15_Eta1p5ForPPRef_v1";
//const TCut evtSelFilterCut = "(1==1)"; // already applied on the skim file
const TCut evtSelFilterCut = "pcollisionEventSelection && HBHENoiseFilterResultRun2Loose"; // already applied on the skim file
const TCut evtSelFilterCut_pp = "pBeamScrapingFilter && pPAprimaryVertexFilter && HBHENoiseFilterResultRun2Loose";// pVertexFilterCutEandG is for pPb pileup
//Noise Cuts
const TCut spikeRejection = "(phoSigmaIEtaIEta_2012>=0.002) && (pho_swissCrx<=0.9) && (abs(pho_seedTime)<=3)";
const TCut hotspotCut = "pho_is2015Noise==0";
const TCut electronCut = "pho_isEle==0";
//const TCut electronCut = "pho_isEle>=0"; //electron sys
const TCut noiseCut = spikeRejection && hotspotCut;
//Kinematic Cuts
const TCut ptCut = "phoEtCorrected>20";
const TCut etaCut = "abs(phoEta)<1.44";
//Isolation Cuts for PbPb
const TCut hoeCut = "phoHoverE<0.1";
//const TCut hoeCut = "phoHoverE<0.05"; //ID down
const TCut isoCut = "pho_sumIsoCorrected<1.0";
//const TCut isoCut = "pho_sumIsoCorrected<3.0"; //ID up
//const TCut isoCut = "(pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20)<1.0";
const TCut sigmaCut = "phoSigmaIEtaIEta_2012<0.010";
//const TCut nonIsoSBCut = "pho_sumIsoCorrected > 10.0 && pho_sumIsoCorrected < 20.0";
//const TCut nonIsoSBCut = "pho_sumIsoCorrected > 5.0 && pho_sumIsoCorrected < 10.0"; //purDown
const TCut nonIsoSBCut = "pho_sumIsoCorrected > 20.0 && pho_sumIsoCorrected < 30.0"; //purUp
//const TCut nonIsoSBCut = "(pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20) > 10.0 && (pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20) < 20.0";
//const TCut nonIsoSBCut = "(pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20) > 5.0 && (pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20) < 10.0"; //purDown
//const TCut nonIsoSBCut = "(pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20) > 20.0 && (pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20) < 30.0"; //purUp
//Isolation Cuts for pp
const TCut isoCut_pp = isoCut;
const TCut hoeCut_pp = hoeCut;
const TCut sigmaCut_pp = sigmaCut;
//Cuts for GED photons in pp collisions 
//https://twiki.cern.ch/twiki/bin/viewauth/CMS/CutBasedPhotonIdentificationRun2Archive#SPRING15_selections_25_ns
//medium
//const TCut isoCut_pp = "((pfcIso4<=1.37) && (pfnIso4<=1.06+0.014*phoEt+0.000019*phoEt*phoEt) && pfpIso4<=(0.28+0.0053*phoEt))";
//const TCut hoeCut_pp = "phoHoverE<0.05";
//const TCut sigmaCut_pp = "phoSigmaIEtaIEta<0.0102";
//tight ID down
//const TCut isoCut_pp = "((pfcIso4<=0.76) && (pfnIso4<=0.97+0.014*phoEt+0.000019*phoEt*phoEt) && pfpIso4<=(0.08+0.0053*phoEt))";
//const TCut hoeCut_pp = "phoHoverE<0.05";
//const TCut sigmaCut_pp = "phoSigmaIEtaIEta<0.0100";
////loose ID up 
//const TCut isoCut_pp = "((pfcIso4<=3.32) && (pfnIso4<=1.92+0.014*phoEt+0.000019*phoEt*phoEt) && pfpIso4<=(0.81+0.0053*phoEt))";
//const TCut hoeCut_pp = "phoHoverE<0.05";
//const TCut sigmaCut_pp = "phoSigmaIEtaIEta<0.0102";
const TCut nonIsoSBCut_pp = nonIsoSBCut;

const TCut dataCut =evtSelFilterCut && noiseCut;
const TCut dataCut_pp = evtSelFilterCut_pp && noiseCut;
const TCut mcCut = noiseCut;
const TCut mcCut_pp = noiseCut;
//const TCut mcCut = trigCut_mc && evtSelFilterCut && noiseCut;
//const TCut mcCut_pp = trigCut_mc_pp && evtSelFilterCut_pp && noiseCut;
const TCut phoSignalCut = dataCut && hoeCut && isoCut && sigmaCut && electronCut;
const TCut phoSignalCut_pp = dataCut_pp && hoeCut_pp && isoCut_pp && sigmaCut_pp && electronCut;
const TCut phoSignalCut_mc = mcCut && hoeCut && isoCut && sigmaCut && electronCut;
const TCut phoSignalCut_pp_mc = mcCut_pp && hoeCut_pp && isoCut_pp && sigmaCut_pp && electronCut;
const TCut phoSignalCut_woTrig = noiseCut && hoeCut && isoCut && sigmaCut && electronCut;
const TCut phoSignalCut_woTrig_pp = evtSelFilterCut_pp && noiseCut && hoeCut_pp && isoCut_pp && sigmaCut_pp && electronCut;

/////////////// FOR PURITY ///////////////////
const TString purityVar= "phoSigmaIEtaIEta_2012";
const TString purityVar_pp= "phoSigmaIEtaIEta_2012";
const TCut sampleIsolation = evtSelFilterCut && noiseCut && hoeCut && isoCut;
const TCut sampleIsolation_pp = evtSelFilterCut_pp && noiseCut && hoeCut_pp && isoCut_pp;
const TCut sidebandIsolation = dataCut && hoeCut && nonIsoSBCut && electronCut;
const TCut sidebandIsolation_pp = dataCut_pp && hoeCut_pp && nonIsoSBCut_pp && electronCut;
const TCut sampleIsolation_woTrig = noiseCut && hoeCut && isoCut && electronCut;
const TCut sampleIsolation_woTrig_pp = noiseCut && hoeCut_pp && isoCut_pp && electronCut;
const TCut sidebandIsolation_woTrig = noiseCut && hoeCut && nonIsoSBCut && electronCut;
const TCut sidebandIsolation_woTrig_pp = noiseCut && hoeCut_pp && nonIsoSBCut_pp && electronCut;
//Only Gen Info
const TCut mcIsolation = "(pho_genMatchedIndex!= -1) && abs(pho_genPID)==22 && pho_genCalIsoDR04<5 && (abs(pho_genMomPID)<=22 || pho_genMomPID==-999)";
const TCut mcBkgIsolation = "(pho_genMatchedIndex!= -1) && abs(pho_genPID)==22 && !(pho_genCalIsoDR04<5 && (abs(pho_genMomPID)<=22 || pho_genMomPID==-999))";
const TCut mcSignalCut_woKine = mcIsolation && mcCut && hoeCut && isoCut;
const TCut mcSignalCut_woKine_pp = mcIsolation && mcCut_pp && hoeCut_pp && isoCut_pp;

#endif

