#ifndef phoRaaCuts_190625_temp_v29_H 
#define phoRaaCuts_190625_temp_v29_H 
// 1. pp photon selection(ID cuts) is from EGamma POG.
// 2. pbpb MC is CYMBAL total(v1+ext) and v14 of EmEnrichedDijet
// 3. centrality bin (0,10,30,50,100)
// 4. pp is GED 
// 5. (pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20) instead of sumIsoCorrected.  
// 6. sumIso < 1 GeV 
// 7. pt bin (20,30,40,50,60,80,100,130,200) with lower pt PDs
// 8. electron rejection has been seperated from noise cut 
// 9. photon energy correction with DSCB 
// 10. unfolding bin 
// 11. new skim with the new photon cut at 10 GeV (it was 15 GeV beforehand) 2019.02.26
// 12. no 30 trigger for 30-40 GeV bin 
// 29. have different pT binning for each centrality bin 
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
TString ppDatafname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2019-07-02-meanEcorr/pp_Data_photonRaaSkim_HighPtLowerPhotons_190702_meanEcorr.root";
TString ppDatafname_high = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2019-07-02-meanEcorr/pp_Data_photonRaaSkim_HighPtPhoton30AndZ_190702_meanEcorr.root";
TString ppMCfname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2019-07-02-meanEcorr/pp_MC_photonRaaSkim_190702_meanEcorr.root";
TString ppMCEmEnrfname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2019-07-02-meanEcorr/pp_EmEnrMC_photonRaaSkim_190702_meanEcorr.root";
TString pbpbDatafname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2019-07-02-meanEcorr/PbPb_Data_photonRaaSkim_HIHardProbes_HIHardProbesPhotons_190702_meanEcorr.root";
TString pbpbDatafname_high = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2019-07-02-meanEcorr/PbPb_Data_photonRaaSkim_HIPhoton40AndZ_190702_meanEcorr.root";
TString pbpbMCfname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2019-07-02-meanEcorr/PbPb_MC_photonRaaSkim_Cymbal_190702_meanEcorr.root";
TString pbpbMCEmEnrfname = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2019-07-02-meanEcorr/PbPb_EmEnrMC_photonRaaSkim_190702_meanEcorr.root";
TString pbpbData_config = "/home/goyeonju/CMS/2016/PhotonAnalysis2016/ElectroWeak-Jet-Track-Analyses/CutConfigurations/photonRaa.conf";
TString pbpbMC_config = "/home/goyeonju/CMS/2016/PhotonAnalysis2016/ElectroWeak-Jet-Track-Analyses/CutConfigurations/photonRaa_mc.conf";
TString ppData_config = "/home/goyeonju/CMS/2016/PhotonAnalysis2016/ElectroWeak-Jet-Track-Analyses/CutConfigurations/photonRaa_pp.conf";
TString ppMC_config = "/home/goyeonju/CMS/2016/PhotonAnalysis2016/ElectroWeak-Jet-Track-Analyses/CutConfigurations/photonRaa_pp_mc.conf";
TString pbpb_forest_inputList = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/inputfilelist/pbpblist_v14_HydjetCymbal.txt"; 
TString pp_forest_inputList = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/inputfilelist/pplist.txt"; 
TString pbpb_recoEfficiency= "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/output/pbpb_reco_efficiency_Cymbal_withExt_190626_pt20to300.root";
TString pp_recoEfficiency = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/output/pp_reco_efficiency_withExt_190626_pt20to300.root";
TString pp_trigEfficiency = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/output/pp_trigger_efficiency_photon_skim_low_doIDcut1_doPreScale1_doAnalysisBin1.root";
TString pbpb_tnp = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/tnp_output/correction_functions_pbpb_ptDep_passID_VoigtErfExp2_inputFile_v26_runningCode_v10_2ptBins_mass60to120_recoIDPho_ptDep15_40_200_cent0_100.txt";
TString pp_tnp = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/tnp_output/correction_functions_pp_ptDep_passID_VoigtErfExp_inputFile_v35_runningCode_v5_test_mass70to110_recoIDPho_pt15_30_40_200.txt";

//////////////// TnP ///////////////////
const bool centDepTnP = false;
const bool ptDepTnP = true;
const bool ptDepTnP_pp = true;
const double pp_tnp_pt_sec[] = {30,40,300};
const int n_pp_tnp_pt_sec  = sizeof(pp_tnp_pt_sec)/sizeof(double);
const double pp_tnp_pt[] = {0.998072,0.992498,0.991067};
//const double pp_tnp_pt[] = {0.981024,0.992931,0.998623}; //sys_TnP
//nominal TnP file for pp : correction_functions_pp_ptDep_passID_VoigtErfExp_inputFile_v35_runningCode_v5_test_mass70to110_recoIDPho_pt15_30_40_200.txt
//sys TnP file for pp :correction_functions_pp_ptDep_passID_BWResCBErfExp7_inputFile_v35_runningCode_v5_test_mass70to110_recoIDPho_pt15_30_40_200.txt 

const double pbpb_tnp_pt_sec[] = {40,300};
const int n_pbpb_tnp_pt_sec  = sizeof(pbpb_tnp_pt_sec)/sizeof(double);
const double pbpb_tnp_pt[] = {0.95237,0.988644}; //nominal
//const double pbpb_tnp_pt[] = {0.947274,0.989143}; //sys_TnP
//nominal TnP file for pbpb : correction_functions_pbpb_ptDep_passID_VoigtErfExp2_inputFile_v26_runningCode_v10_2ptBins_mass60to120_recoIDPho_ptDep15_40_200_cent0_100.txt
//sys TnP file for pp : correction_functions_pbpb_ptDep_passID_VoigtErfExp2_inputFile_v27_runningCode_v10_2ptBins_mass60to120_recoIDPho_ptDep15_40_200_cent0_100.txt 

const double pbpb_tnp_cent_sec[] = {20,200};
const int n_pbpb_tnp_cent_sec  = sizeof(pbpb_tnp_cent_sec)/sizeof(double);
const double pbpb_tnp_cent[] = {0.767002,0.963798};

/////////////// BINNING ///////////////////
const double ptBins[] = {25,30,40,50,60,80,100,130,200};
const double ptBins_draw[] = {25,30,40,50,60,80,100,130,200};
const double ptBins_draw_final[] = {15,25,30,40,50,60,80,100,130,200};
const double ptBins_unfolding[] = {20,25,30};
//const double ptBins_unfolding[] = {20,25,30,40,50,60,80,100,130,200,300};
const double ptBins_mean_pbpb[] = {27.7444,34.0872,44.1777,54.243,67.977,88.0138,111.867,152.202};
const double ptBins_mean_pp[] = {27.1233,33.7975,44.1448,54.3516,68.0108,88.7239,111.387,151.673};
const double ptBins_mean_unfolding_pbpb[] = {22.19,27.7444,34.0872,44.1777,54.243,67.977,88.0138,111.867,152.202,227.849};
const double ptBins_mean_unfolding_pp[] = {22.035,27.1233,33.7975,44.1448,54.3516,68.0108,88.7239,111.387,151.673,236.152};
const int nPtBin = sizeof(ptBins)/sizeof(double) -1;
const int nPtBin_unfolding = sizeof(ptBins_unfolding)/sizeof(double) -1;
const double ptBins_i[] = {25,25,30,40,50,60,80,100,130};
const double ptBins_f[] = {200,30,40,50,60,80,100,130,200};
const int nPtBinIF = sizeof(ptBins_i)/sizeof(double);
const int centBins[] = {0,20,60,100,200};
const int nCentBin = sizeof(centBins)/sizeof(int) -1;
const int centBins_i[] = {0,0};
const int centBins_f[] = {200,20};
//const int centBins_i[] = {0,0,20,60,100};
//const int centBins_f[] = {200,20,60,100,200};
const int rejectPtBins[] = {0,0,0,1,2};
const int nCentBinIF = sizeof(centBins_i)/sizeof(int);
//const double TA[nCentBinIF] = {5.607*1000,23.22*1000,11.51*1000,3.819*1000,0.4395*1000}; 
////const double TA[nCentBinIF] = {5.762*1000,23.651*1000,11.814*1000,4.026*1000,0.4885*1000}; //TAA up
//////const double TA[nCentBinIF] = {5.416*1000,22.531*1000,11.122*1000,3.611*1000,0.4075*1000}; //TAA down
//const double TA_err[nCentBinIF] = {0.089,0.017,0.024,0.054,0.112}; //err {8.9 1.7, 2.4, 5.4, 11.2} % 
//const double TA_err_up[nCentBinIF] = {0.034,0.03,0.034,0.054,0.112}; //err {3.4, 3.0, 3.4, 5.4, 11.2} % 
//const double TA_err_down[nCentBinIF] = {0.028,0.019,0.026,0.054,0.073}; //err {2.8, 1.9, 2.6, 5.4, 7.3} % 
//const double TA_up[nCentBinIF] = {5.762*1000,23.651*1000,11.814*1000,4.026*1000,0.4885*1000}; //TAA up 
//const double TA_down[nCentBinIF] = {5.416*1000,22.531*1000,11.122*1000,3.611*1000,0.4075*1000}; //TAA down
////const double TA[nCentBinIF] = {6.108*1000,23.612*1000,11.784*1000,1.571*1000}; //err {8.9 1.7, 2.4, 12} % 
////double lumi_pp = 28.0302*1e12; //2.3 % err 

/////////////// CUTS ///////////////////
//Systematics
const TString phoEtVar = "phoEtCorrected";
//const TString phoEtVar = "phoEtCorrected_sys"; //phoEscale
//const TString phoEtVar = "phoEtCorrected_resSys_sig"; //phoEresol
//Trigger and EvtSelection Cuts
const TCut trigCut_low = "HLT_HISinglePhoton20_Eta1p5_v1 || HLT_HISinglePhoton20_Eta1p5_v2";
const TCut trigCut_high = "HLT_HISinglePhoton40_Eta1p5_v1";
const TCut trigCut_30to40= trigCut_low; 
const TCut trigCut_pp_low = "HLT_HISinglePhoton20_Eta1p5_v1";
const TCut trigCut_pp_high = "HLT_HISinglePhoton40_Eta1p5_v1";
const TCut trigCut_pp_30to40= trigCut_low; 
const TCut trigCut_mc = "(HLT_HISinglePhoton20_Eta1p5_v2==1 && phoEtCorrected>=20 && phoEtCorrected<40) || (HLT_HISinglePhoton40_Eta1p5_v2==1 && phoEtCorrected>=40) ";
const TCut trigCut_mc_pp = "(HLT_HISinglePhoton20_Eta1p5ForPPRef_v1==1 && phoEtCorrected>=20 && phoEtCorrected<40) || (HLT_HISinglePhoton40_Eta1p5ForPPRef_v1==1 && phoEtCorrected>=40)";
//const TCut evtSelFilterCut = "(1==1)"; // already applied on the skim file
const TCut evtSelFilterCut = "pcollisionEventSelection && HBHENoiseFilterResultRun2Loose"; // already applied on the skim file
const TCut evtSelFilterCut_pp = "pBeamScrapingFilter && pPAprimaryVertexFilter && HBHENoiseFilterResultRun2Loose";// pVertexFilterCutEandG is for pPb pileup
//Noise Cuts
const TCut spikeRejection = "(phoSigmaIEtaIEta_2012>=0.002) && (pho_swissCrx<=0.9) && (abs(pho_seedTime)<=3)";
const TCut hotspotCut = "pho_is2015Noise==0";
const TCut electronCut = "pho_isEle==0";
//const TCut electronCut = "pho_isEle>=0"; // eleCont
const TCut noiseCut = spikeRejection && hotspotCut;
//Kinematic Cuts
const TCut ptCut = Form("%s>20",phoEtVar.Data());
//const TCut ptCut = "phoEtCorrected>20";
const TCut etaCut = "abs(phoEta)<1.44";
//Isolation Cuts for PbPb
const TCut hoeCut = "phoHoverE<0.1";
const TCut isoCut = "pho_sumIsoCorrected<0.5";
//const TCut isoCut = "pho_sumIsoCorrected<1.0";
//const TCut isoCut = "pho_sumIsoCorrected<2.0"; //IDup
//const TCut isoCut = "pho_sumIsoCorrected<0.5"; //IDdown
//const TCut isoCut = "(pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20)<1.0";
const TCut sigmaCut = "phoSigmaIEtaIEta_2012<0.010";
//const TCut nonIsoSBCut = "pho_sumIsoCorrected > 10.0 && pho_sumIsoCorrected < 20.0";
const TCut nonIsoSBCut = "pho_sumIsoCorrected > 0.5 && pho_sumIsoCorrected < 1.0"; //purDown
//const TCut nonIsoSBCut = "pho_sumIsoCorrected > 5.0 && pho_sumIsoCorrected < 10.0"; //purDown
//const TCut nonIsoSBCut = "pho_sumIsoCorrected > 20.0 && pho_sumIsoCorrected < 30.0"; //purUp
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

const TCut dataCut = evtSelFilterCut && noiseCut;
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
const TCut mcIsolation_nm = "abs(mcPID)==22 && mcCalIsoDR04<5 && (abs(mcMomPID)<=22 || mcMomPID==-999)";
const TCut mcBkgIsolation = "(pho_genMatchedIndex!= -1) && abs(pho_genPID)==22 && !(pho_genCalIsoDR04<5 && (abs(pho_genMomPID)<=22 || pho_genMomPID==-999))";
const TCut mcSignalCut_woKine = mcIsolation && mcCut && hoeCut && isoCut;
const TCut mcSignalCut_woKine_pp = mcIsolation && mcCut_pp && hoeCut_pp && isoCut_pp;

#endif

