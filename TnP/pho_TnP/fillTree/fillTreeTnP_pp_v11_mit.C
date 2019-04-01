#define MC // comment this line to run on data

#ifdef MC
// this is for GED photons, if you want hybrid, need to regenerate new class and include it
#include "ggTreeReaderPP.C"
#include "hltTreeReaderPP.C"
#include "globalTreeReaderPP.C"
#include "hiEvtTreeReaderPP.C"
#include "hltobjTreeReaderHiPho40PP.C"
#define ggTreeReaderPP ggTreeReaderPP
#define hltTreeReaderPP hltTreeReaderPP
#define globalTreeReaderPP globalTreeReaderPP
#define hiEvtTreeReaderPP hiEvtTreeReaderPP
#define hltobjTreeReaderPP hltobjTreeReaderHiPho40PP
#else
#include "ggTreeReaderPPData.C"
#include "hltTreeReaderPPData.C"
#include "globalTreeReaderPPData.C"
#include "hltobjTreeReaderHiPho40PPData.C"
#define ggTreeReaderPP ggTreeReaderPPData
#define hltTreeReaderPP   hltTreeReaderPPData
#define globalTreeReaderPP globalTreeReaderPPData
#define hltobjTreeReaderPP hltobjTreeReaderHiPho40PPData
#endif
#include "TH1F.h"
#include "TH1D.h"
#include "TF1.h"
#include "TLorentzVector.h"
#include "TRandom3.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <algorithm>


using namespace std;


float getDeltaR(float eta1,float phi1,float eta2,float phi2)
{
  float deltaPhi = TMath::Abs(phi1-phi2);
  float deltaEta = eta1-eta2;
  if(deltaPhi > TMath::Pi())
    deltaPhi = TMath::TwoPi() - deltaPhi;
  return TMath::Sqrt(deltaEta*deltaEta + deltaPhi*deltaPhi);
}

const double DRmax   = 0.3;
const double DRmax_HLT = 0.3;
const double acc_eta = 1.5;
const double acc_min_pt = 20;
const double acc_max_pt = 200;

class clHist {
   public:
      TH1F *hpt;
      TH1F *hmass;
      TH1F *hrap;
      TH1F *hint;

      clHist(const char* name) {
         hpt = new TH1F(Form("hpt_%s",name),"",200,0,200);
         hmass = new TH1F(Form("hmass_%s",name),"",40,60,120);
         hrap = new TH1F(Form("hrap_%s",name),"",30,-3,3);
         hint = new TH1F(Form("hint_%s",name),"",1,0,1);
      };

      void fill(double pt, double rap, double mass, double dphi, double weight=1.) {
         hpt->Fill(pt,weight);
         hrap->Fill(rap,weight);
         hmass->Fill(mass,weight);
         hint->Fill(0.5,weight);
      };
};


void fillTreeTnP_pp_v11_mit() {
   TChain *tchHLT = new TChain("hltanalysis/HltTree");
   TChain *tchEvt = new TChain("ggHiNtuplizerGED/EventTree");
   TChain *tchGlob = new TChain("skimanalysis/HltTree");
   string hltObjStr = "";
   string hltObjStr_low = "";
#ifdef MC
   hltObjStr = "hltobject/HLT_HISinglePhoton40_Eta1p5ForPPRef_v1";
   hltObjStr_low = "hltobject/HLT_HISinglePhoton20_Eta1p5ForPPRef_v1";
#else
   hltObjStr = "hltobject/HLT_HISinglePhoton40_Eta1p5_v";
   hltObjStr_low = "hltobject/HLT_HISinglePhoton20_Eta1p5_v";
//HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v1
//HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v1
#endif
   TChain *tchHLTObj = new TChain(hltObjStr.c_str());
   TChain *tchHLTObj_low = new TChain(hltObjStr_low.c_str());
#ifdef MC
   TChain *tchHiEvt = new TChain("hiEvtAnalyzer/HiTree");
   ///////Ze30eeJet ext1 
   //tchEvt->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3_ext1-v1-FOREST/merged.root");
   //tchHLT->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3_ext1-v1-FOREST/merged.root");
   //tchGlob->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3_ext1-v1-FOREST/merged.root");
   //tchHiEvt->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3_ext1-v1-FOREST/merged.root");
   //tchHLTObj->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3_ext1-v1-FOREST/merged.root");
   //tchHLTObj_low->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3_ext1-v1-FOREST/merged.root");
   /////////Ze30eeJet 
   //tchEvt->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1-FOREST/merged.root");
   //tchHLT->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1-FOREST/merged.root");
   //tchGlob->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1-FOREST/merged.root");
   //tchHiEvt->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1-FOREST/merged.root");
   //tchHLTObj->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1-FOREST/merged.root");
   //tchHLTObj_low->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1-FOREST/merged.root");
   //////Ze10e10 ext1
   tchEvt->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3_ext1-v1-FOREST/merged.root");
   tchHLT->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3_ext1-v1-FOREST/merged.root");
   tchGlob->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3_ext1-v1-FOREST/merged.root");
   tchHiEvt->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3_ext1-v1-FOREST/merged.root");
   tchHLTObj->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3_ext1-v1-FOREST/merged.root");
   tchHLTObj_low->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3_ext1-v1-FOREST/merged.root");
   //Ze10e10 
   tchEvt->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1-FOREST/merged.root");
   tchHLT->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1-FOREST/merged.root");
   tchGlob->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1-FOREST/merged.root");
   tchHiEvt->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1-FOREST/merged.root");
   tchHLTObj->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1-FOREST/merged.root");
   tchHLTObj_low->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10/HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1-FOREST/merged.root");
#else
   tchHLT->Add("/mnt/hadoop/cms/store/user/tatar/HighPtPhoton30AndZ/HIRun2015E-PromptReco-AOD-dielectron-skim-FOREST/0.root");
   tchEvt->Add("/mnt/hadoop/cms/store/user/tatar/HighPtPhoton30AndZ/HIRun2015E-PromptReco-AOD-dielectron-skim-FOREST/0.root");
   tchGlob->Add("/mnt/hadoop/cms/store/user/tatar/HighPtPhoton30AndZ/HIRun2015E-PromptReco-AOD-dielectron-skim-FOREST/0.root");
   tchHLTObj->Add("/mnt/hadoop/cms/store/user/tatar/HighPtPhoton30AndZ/HIRun2015E-PromptReco-AOD-dielectron-skim-FOREST/0.root");
   tchHLTObj_low->Add("/mnt/hadoop/cms/store/user/tatar/HighPtPhoton30AndZ/HIRun2015E-PromptReco-AOD-dielectron-skim-FOREST/0.root");
#endif
   cout << tchHLT->GetEntriesFast() << " " << tchEvt->GetEntriesFast() << " " << tchGlob->GetEntriesFast()  << endl;
   cout << tchHLT->GetEntries() << " " << tchEvt->GetEntries() << " " << tchGlob->GetEntries() << endl;
#ifdef MC
   cout << tchHLT->GetEntries() << " " << tchEvt->GetEntries() << " " << tchGlob->GetEntries() << endl;
#else
   cout << tchHLT->GetEntries() << " " << tchEvt->GetEntries() << " " << tchGlob->GetEntries() << " " << tchHLTObj->GetEntries()  << endl;
#endif
   cout << tchHLT->GetEntriesFast() << " " << tchEvt->GetEntriesFast() << " " << tchGlob->GetEntriesFast()  << endl;

   hltTreeReaderPP hltR(tchHLT);
   ggTreeReaderPP evtR(tchEvt);
   globalTreeReaderPP globR(tchGlob);
   hltobjTreeReaderPP hltObjR(tchHLTObj);
   hltobjTreeReaderPP hltObjR_low(tchHLTObj_low);
#ifdef MC
   hiEvtTreeReaderPP hiEvtR(tchHiEvt);
#endif

   // set branch status
   hltR.fChain->SetBranchStatus("*",0);
   evtR.fChain->SetBranchStatus("*",0);
   globR.fChain->SetBranchStatus("*",0);
   hltObjR.fChain->SetBranchStatus("*",0);
   hltObjR_low.fChain->SetBranchStatus("*",0);
#ifdef MC
   hiEvtR.fChain->SetBranchStatus("*",0);
#endif

   //pp GED photons
   evtR.fChain->SetBranchStatus("nPho",1);
   evtR.fChain->SetBranchStatus("phoEt",1);
   evtR.fChain->SetBranchStatus("phoEta",1);
   evtR.fChain->SetBranchStatus("phoPhi",1);
   evtR.fChain->SetBranchStatus("phoSCEta",1);
   evtR.fChain->SetBranchStatus("phoSCPhi",1);
   evtR.fChain->SetBranchStatus("phoHoverE",1);
   evtR.fChain->SetBranchStatus("phoSigmaIEtaIEta_2012",1);

   evtR.fChain->SetBranchStatus("pho_ecalClusterIsoR4",1);
   evtR.fChain->SetBranchStatus("pho_hcalRechitIsoR4",1);
   evtR.fChain->SetBranchStatus("pho_trackIsoR4PtCut20",1);
  // evtR.fChain->SetBranchStatus("pfcIso4",1);
  // evtR.fChain->SetBranchStatus("pfnIso4",1);
  // evtR.fChain->SetBranchStatus("pfpIso4",1);

   //PbPb electrons
   evtR.fChain->SetBranchStatus("nEle",1);
   evtR.fChain->SetBranchStatus("eleHoverE",1);
   evtR.fChain->SetBranchStatus("eleMissHits",1);
   evtR.fChain->SetBranchStatus("eleCharge",1);
   evtR.fChain->SetBranchStatus("elePt",1);
   evtR.fChain->SetBranchStatus("eleEta",1);
   evtR.fChain->SetBranchStatus("elePhi",1);
   evtR.fChain->SetBranchStatus("eleSCEta",1);
   evtR.fChain->SetBranchStatus("eleSCPhi",1);

   // hlt
   hltR.fChain->SetBranchStatus("NL1IsolEm",1);
   hltR.fChain->SetBranchStatus("L1IsolEm*",1);
   hltR.fChain->SetBranchStatus("NL1NIsolEm",1);
   hltR.fChain->SetBranchStatus("L1NIsolEm*",1);
#ifdef MC
   hltR.fChain->SetBranchStatus("HLT_HISinglePhoton40_Eta1p5ForPPRef_v1",1);
   hltR.fChain->SetBranchStatus("HLT_HISinglePhoton20_Eta1p5ForPPRef_v1",1);
   hltR.fChain->SetBranchStatus("HLT_HIDoublePhoton15_Eta1p5_Mass50_1000ForPPRef_v1",1);
#else
   hltR.fChain->SetBranchStatus("HLT_HISinglePhoton40_Eta1p5_v1",1);
   hltR.fChain->SetBranchStatus("HLT_HISinglePhoton20_Eta1p5_v1",1);
   hltR.fChain->SetBranchStatus("HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v1",1);
#endif
   hltR.fChain->SetBranchStatus("Bx",1);
   hltR.fChain->SetBranchStatus("Event",1);

   // global filters
   globR.fChain->SetBranchStatus("pBeamScrapingFilter",1);
   globR.fChain->SetBranchStatus("pPAprimaryVertexFilter",1);
#ifdef MC
   hiEvtR.fChain->SetBranchStatus("vz",1);
#endif

   //set hlt objects
   hltObjR.fChain->SetBranchStatus("TriggerObjID",1);
   hltObjR.fChain->SetBranchStatus("pt",1);
   hltObjR.fChain->SetBranchStatus("eta",1);
   hltObjR.fChain->SetBranchStatus("phi",1);
   hltObjR.fChain->SetBranchStatus("mass",1);
   //set hlt objects
   hltObjR_low.fChain->SetBranchStatus("TriggerObjID",1);
   hltObjR_low.fChain->SetBranchStatus("pt",1);
   hltObjR_low.fChain->SetBranchStatus("eta",1);
   hltObjR_low.fChain->SetBranchStatus("phi",1);
   hltObjR_low.fChain->SetBranchStatus("mass",1);


   if (evtR.fChain == 0) return;
   if (hltR.fChain == 0) return;
   if (globR.fChain == 0) return;
   if (hltObjR.fChain == 0) return;
   if (hltObjR_low.fChain == 0) return;
#ifdef MC
   if (hiEvtR.fChain == 0) return;
#endif

   Long64_t nentries = evtR.fChain->GetEntriesFast();
   Long64_t nentries2 = hltR.fChain->GetEntriesFast();
   Long64_t nentries3 = globR.fChain->GetEntriesFast();

   if (nentries != nentries2 || nentries != nentries3 || nentries3 != nentries2) return;

#ifdef MC
   TFile *fout = new TFile("output_mc_pp_v11.root","RECREATE");
#else
   TFile *fout = new TFile("output_data_pp_v11.root","RECREATE");
#endif

   // tree for tnp
   TDirectory *tdir = fout->mkdir("phoTree");
   tdir->cd();
   TTree *tr = new TTree("fitter_tree","");

   // probe photon
   float probe_pt, probe_eta, probe_phi, probe_abseta;
   float probe_hoe, probe_sigmaIetaIeta, probe_ecalClusterIsoR4, probe_hcalRechitIsoR4, probe_sumIso;
   float probe_SCeta, probe_SCphi;
   //tag photon   
   float tag_pt, tag_eta, tag_phi;
   float tag_hoe, tag_sigmaIetaIeta, tag_ecalClusterIsoR4, tag_hcalRechitIsoR4, tag_sumIso;
   float tag_SCeta, tag_SCphi;
   //diphoton
   float diPhoMass;
   //flags
   int passID;
   int passISO;
   int passL1;
   int passHLT;
   int passHLT_low;
   //weights for mc, for data = 1
   float vz_weight, final_weight;

   // book variables
   tr->Branch("probe_pt",&probe_pt,"probe_pt/F");
   tr->Branch("tag_pt",&tag_pt,"tag_pt/F");
   tr->Branch("probe_eta",&probe_eta,"probe_eta/F");
   tr->Branch("probe_SCeta",&probe_SCeta,"probe_SCeta/F");
   tr->Branch("probe_abseta",&probe_abseta,"probe_abseta/F");
   tr->Branch("tag_eta",&tag_eta,"tag_eta/F");
   tr->Branch("tag_SCeta",&tag_SCeta,"tag_SCeta/F");
   tr->Branch("probe_phi",&probe_phi,"probe_phi/F");
   tr->Branch("tag_phi",&tag_phi,"tag_phi/F");
   tr->Branch("probe_SCphi",&probe_SCphi,"probe_SCphi/F");
   tr->Branch("tag_SCphi",&tag_SCphi,"tag_SCphi/F");
   tr->Branch("probe_hoe",&probe_hoe,"probe_hoe/F");
   tr->Branch("tag_hoe",&tag_hoe,"tag_hoe/F");
   tr->Branch("probe_sigmaIetaIeta",&probe_sigmaIetaIeta,"probe_sigmaIetaIeta/F");
   tr->Branch("tag_sigmaIetaIeta",&tag_sigmaIetaIeta,"tag_sigmaIetaIeta/F");
   tr->Branch("probe_ecalClusterIsoR4",&probe_ecalClusterIsoR4,"probe_ecalClusterIsoR4/F");
   tr->Branch("tag_ecalClusterIsoR4",&tag_ecalClusterIsoR4,"tag_ecalClusterIsoR4/F");
   tr->Branch("probe_hcalRechitIsoR4",&probe_hcalRechitIsoR4,"probe_hcalRechitIsoR4/F");
   tr->Branch("tag_hcalRechitIsoR4",&tag_hcalRechitIsoR4,"tag_hcalRechitIsoR4/F");
   tr->Branch("probe_sumIso",&probe_sumIso,"probe_sumIso/F");
   tr->Branch("tag_sumIso",&tag_sumIso,"tag_sumIso/F");
   tr->Branch("diPhoMass",&diPhoMass,"diPhoMass/F");
   tr->Branch("passID",&passID,"passID/I");
   tr->Branch("passISO",&passISO,"passISO/I");
   tr->Branch("passL1",&passL1,"passL1/I");
   tr->Branch("passHLT",&passHLT,"passHLT/I");
   tr->Branch("passHLT_low",&passHLT_low,"passHLT_low/I");
   tr->Branch("vz_weight",&vz_weight,"vz_weight/F");
   tr->Branch("final_weight",&final_weight,"final_weight/F");

#ifdef MC
   TFile fileW("pp_Ze10e10_MC_weights.root");
   TH1F *hVzW = (TH1F*)fileW.Get("hvz");
#endif

   //files for energy corection and smearing 
   TFile fcorr("photonEnergyCorrections_pp_GED_COMB_AllQCD_0729.root");
   TF1* photonEnergyCorrections_pp = (TF1*)fcorr.Get(Form("f_mean_gaus_cent0_eta%i", 0));
#ifdef MC
   TFile fsmear("eleMatchedPhotonZPeak_pp_GED_COMB_AllQCD_0729_reweighted.root"); 
   TH1D* h_z_width_data_pp= (TH1D*)fsmear.Get("h_z_mass_width");
   TH1D* h_z_width_mc_pp= (TH1D*)fsmear.Get("h_z_mass_width_mc");
#endif

    TRandom3 *r3=new TRandom3();
   double nentryTnp = 0;
   double treeFilled = 0;
   int tagPrescl = 0;
   
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      if (jentry%100000==0) cout << "--> " << jentry << "/" << nentries << endl;
      //cout << "--> " << jentry << "/" << nentries << endl;
      Long64_t ientry_evt = evtR.LoadTree(jentry);
//		cout << "ientry_evt = " << ientry_evt << endl;
      if (ientry_evt < 0) break;
      Long64_t ientry_hlt = hltR.LoadTree(jentry);
//		cout << "ientry_hlt = " << ientry_hlt << endl;
      if (ientry_hlt < 0) break;
      Long64_t ientry_glob = globR.LoadTree(jentry);
//		cout << "ientry_glob = " << ientry_glob << endl;
      if (ientry_glob < 0) break;
      Long64_t ientry_hltobj = hltObjR.LoadTree(jentry);
//		cout << "ientry_hltobj = " << ientry_hltobj << endl;
      if (ientry_hltobj < 0) break;
      Long64_t ientry_hltobj_low = hltObjR_low.LoadTree(jentry);
//		cout << "ientry_hltobj_low = " << ientry_hltobj_low << endl;
      if (ientry_hltobj_low < 0) break;

#ifdef MC
      Long64_t ientry_hievt = hiEvtR.LoadTree(jentry);
      if (ientry_hievt < 0) break;
#endif

      // basic cuts
      evtR.b_nEle->GetEntry(ientry_evt);
      evtR.b_nPho->GetEntry(ientry_evt);

      //don't remove this! 
      nb = evtR.fChain->GetEntry(jentry);   nbytes += nb;
      nb = hltR.fChain->GetEntry(jentry);   nbytes += nb;
      nb = globR.fChain->GetEntry(jentry);   nbytes += nb;
      nb = hltObjR.fChain->GetEntry(jentry);  nbytes += nb;
      nb = hltObjR_low.fChain->GetEntry(jentry);  nbytes += nb;
#ifdef MC
      nb = hiEvtR.fChain->GetEntry(jentry);  nbytes += nb;
#endif

      //noise filters
      bool noiseFiltOk = (globR.pBeamScrapingFilter && globR.pPAprimaryVertexFilter);
      if(!noiseFiltOk) continue;

      //need at least 2 reco electrons and 2 photons
      bool gte_two_pho = evtR.nPho>=2;
      bool gte_two_ele = evtR.nEle>=2;
      if(!gte_two_pho || !gte_two_ele) continue;

      //cout << "here1" << endl;

#ifdef MC
      bool hltOk = hltR.HLT_HISinglePhoton40_Eta1p5ForPPRef_v1;
      bool hltOk_low = hltR.HLT_HISinglePhoton20_Eta1p5ForPPRef_v1;
      bool hltOk_ele = hltR.HLT_HIDoublePhoton15_Eta1p5_Mass50_1000ForPPRef_v1;
#else
      bool hltOk = hltR.HLT_HISinglePhoton40_Eta1p5_v1;
      bool hltOk_low = hltR.HLT_HISinglePhoton20_Eta1p5_v1;
      bool hltOk_ele = hltR.HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v1;
#endif
      if(!(hltOk || hltOk_low)) continue;
      if(!hltOk_ele) continue;

       //cout << "here2" << endl;

      float vz_w = 1.;
#ifdef MC
      int j = hVzW->GetXaxis()->FindBin(hiEvtR.vz);
      vz_w = hVzW->GetBinContent(j);
#endif
      vz_weight = vz_w;
      final_weight = vz_weight;

      vector<int> v_phoIndMatch;
      vector<float> v_phoEt;
      vector<float> v_phoSCEta;
      vector<float> v_phoSCPhi;
      vector<float> v_phoEta;
      vector<float> v_phoPhi;
      vector<float> v_phoHoverE;
      vector<float> v_phoSigmaIEtaIEta;
      vector<float> v_ecalClusterIsoR4;
      vector<float> v_hcalRechitIsoR4;
      //vector<float> v_pfcIso4;
      //vector<float> v_pfnIso4;
      //vector<float> v_pfpIso4;

      //cout << "here3" << endl;

      for(int iEle = 0; iEle < evtR.nEle; iEle++){
	//cout << "iEle = " << iEle << endl;
	double dR_pho_ele = 999.;
	bool phoFound = false;
	int iPhoMatch =  0;
	//int nPhoMatch = 0;
	bool phoMatch = false;

	bool eleInAcc = (abs(evtR.eleSCEta->at(iEle)) < acc_eta && evtR.elePt->at(iEle) > acc_min_pt && evtR.elePt->at(iEle) < acc_max_pt);
	if(!eleInAcc) continue;

	//cout << "ele in acceptance" << endl;

	for(Int_t iPho = 0; iPho < evtR.nPho; iPho++){

	  bool phoInAcc = (abs(evtR.phoSCEta->at(iPho)) < acc_eta && evtR.phoEt->at(iPho) > acc_min_pt && evtR.phoEt->at(iPho) < acc_max_pt);
	  if(!phoInAcc) continue;

	  //cout << "iPho = " << iPho << " , in acc" << endl;

	  double dRtmp = getDeltaR(evtR.eleSCEta->at(iEle),evtR.eleSCPhi->at(iEle),evtR.phoSCEta->at(iPho),evtR.phoSCPhi->at(iPho));
	  
	  if( dRtmp < dR_pho_ele ){
	    dR_pho_ele = dRtmp;
	    phoFound = true;
	    iPhoMatch = iPho;
	    //cout << "iPhoMatch = " << iPhoMatch << endl;
	  }
	}

	if(phoFound && dR_pho_ele<0.1) {
	  phoMatch = true;
	  //cout << "match found" << endl;
	  v_phoIndMatch.push_back(iPhoMatch);
	  //cout << "match found1" << endl;
	  v_phoEt.push_back(evtR.phoEt->at(iPhoMatch));
	  //cout << "match found2" << endl;
	  v_phoSCEta.push_back(evtR.phoSCEta->at(iPhoMatch));
	  //cout << "match found3" << endl;
	  v_phoSCPhi.push_back(evtR.phoSCPhi->at(iPhoMatch));
	  v_phoEta.push_back(evtR.phoEta->at(iPhoMatch));
	  v_phoPhi.push_back(evtR.phoPhi->at(iPhoMatch));
	  //cout << "match found4" << endl;
	  v_phoHoverE.push_back(evtR.phoHoverE->at(iPhoMatch));
	  //cout << "match found5" << endl;
      v_phoSigmaIEtaIEta.push_back(evtR.phoSigmaIEtaIEta_2012->at(iPhoMatch));
      v_ecalClusterIsoR4.push_back(evtR.pho_ecalClusterIsoR4->at(iPhoMatch));
      v_hcalRechitIsoR4.push_back(evtR.pho_hcalRechitIsoR4->at(iPhoMatch));
	  //cout << "match found6" << endl;
	 // v_pfcIso4.push_back(evtR.pfcIso4->at(iPhoMatch));
	 // //cout << "match found7" << endl;
	 // v_pfnIso4.push_back(evtR.pfnIso4->at(iPhoMatch));
	 // //cout << "match found8" << endl;
	 // v_pfpIso4.push_back(evtR.pfpIso4->at(iPhoMatch));
	}
	if(!phoMatch) continue;
      }
      //cout << "here5" << endl;

      // requirement : at least 2 electron-matched photons per event
      if(v_phoIndMatch.size() < 2) continue;

      bool tagFound = false;
      bool asProbe = false;
      int tagInd = -999.;
      vector<int> probeInd;
      vector<int> probeInd_passID;
      vector<int> probeInd_passISO;
      vector<int> probeInd_passL1;
      vector<int> probeInd_passHLT;
      vector<int> probeInd_passHLT_low;

      for(int iPhoM = 0; iPhoM < v_phoIndMatch.size(); iPhoM++){

	asProbe = false;
	// pt energy correction and smearing
	double phoEt_corrected = v_phoEt.at(iPhoM) / photonEnergyCorrections_pp->Eval(v_phoEt.at(iPhoM));
#ifdef MC
	double dataSigma = h_z_width_data_pp->GetBinContent(1);
	double mcSigma = h_z_width_mc_pp->GetBinContent(1);
	double smearSigma = TMath::Sqrt(dataSigma*dataSigma-mcSigma*mcSigma);
	phoEt_corrected = phoEt_corrected * r3->Gaus(1, smearSigma);
#endif

	//pass ISO
    	bool ISO = (v_ecalClusterIsoR4.at(iPhoM) + v_hcalRechitIsoR4.at(iPhoM)) < 1;
	//bool ISO = ((v_pfcIso4.at(iPhoM)<=1.37) && (v_pfnIso4.at(iPhoM)<=1.06+0.014*v_phoEt.at(iPhoM)+0.000019*v_phoEt.at(iPhoM)*v_phoEt.at(iPhoM)) && v_pfpIso4.at(iPhoM)<=(0.28+0.0053*v_phoEt.at(iPhoM)));
	//pass ID
	bool ID = (v_phoHoverE.at(iPhoM)<0.05 && v_phoSigmaIEtaIEta.at(iPhoM)<0.01);
	//match to L1 
	bool L1 = false;
	TLorentzVector phoTLorVect;
	phoTLorVect.SetPtEtaPhiM(phoEt_corrected,v_phoEta.at(iPhoM),v_phoPhi.at(iPhoM),0);
	//phoTLorVect.SetPtEtaPhiM(phoEt_corrected,v_phoSCEta.at(iPhoM),v_phoSCPhi.at(iPhoM),0);
	//phoTLorVect.SetPtEtaPhiM(v_phoEt.at(iPhoM),v_phoSCEta.at(iPhoM),v_phoSCPhi.at(iPhoM),0);
	double minDR0 = 999.;
	//L1-offline matching 
	for (int i=0; i<hltR.NL1IsolEm; i++) {
	  if (hltR.L1IsolEmEt[i]<21) continue;
	  TLorentzVector tlv; tlv.SetPtEtaPhiM(hltR.L1IsolEmEt[i],hltR.L1IsolEmEta[i],hltR.L1IsolEmPhi[i],0);
	  double dr0 = tlv.DeltaR(phoTLorVect);
	  if (dr0<minDR0) {
	    minDR0 = dr0;
	  }
	}
	if(minDR0<DRmax) L1 = true;

	//match to HLT : add for MC when forest is ready
	bool HLT = false;	
	int hltObjSize = hltObjR.TriggerObjID->size();
	double minDR1 = 999.;
        for (int j=0; j<hltObjSize; j++) {
          if (hltObjR.TriggerObjID->at(j)<0) continue;
          TLorentzVector thltv; thltv.SetPtEtaPhiM(hltObjR.pt->at(j),hltObjR.eta->at(j),hltObjR.phi->at(j),0);
          double dr1 = thltv.DeltaR(phoTLorVect);
          if (dr1<minDR1) {
            minDR1 = dr1;
          }
        }
        if(minDR1<DRmax_HLT) HLT = true;
	//match to HLT : add for MC when forest is ready
	bool HLT_low = false;	
	int hltObjSize_low = hltObjR_low.TriggerObjID->size();
	double minDR1_low = 999.;
        for (int j=0; j<hltObjSize_low; j++) {
          if (hltObjR_low.TriggerObjID->at(j)<0) continue;
          TLorentzVector thltv; thltv.SetPtEtaPhiM(hltObjR_low.pt->at(j),hltObjR_low.eta->at(j),hltObjR_low.phi->at(j),0);
          double dr1 = thltv.DeltaR(phoTLorVect);
          if (dr1<minDR1_low) {
            minDR1_low = dr1;
          }
        }
        if(minDR1_low<DRmax_HLT) HLT_low = true;
	
	//if passes everything 
	//if(ISO && ID && L1 && HLT && !tagFound){
	if(ISO && ID && (HLT || HLT_low) && !tagFound){
//	if(ISO && ID && !tagFound){
	  tagFound = true;
	  tagInd = iPhoM;
	}
	//if passes everything, but already got a tag, OR doesn't pass something -> probe
	//if((ISO && ID && L1 && HLT && tagFound && tagInd != iPhoM) || (!ISO || !ID || !L1 || !HLT)){
	if((ISO && ID && (HLT || HLT_low) && tagFound && tagInd != iPhoM) || (!ISO || !ID || !L1 || !(HLT||HLT_low))){
	//if((ISO && ID && tagFound && tagInd != iPhoM) || (!ISO || !ID)){
	  asProbe = true;
	}
	if(asProbe){
	  probeInd.push_back(iPhoM);

	  // keep the order L1, HLT, ID and ISO : ISO should be the last one as it depends on centrality and this is a cut which cuts most of stats
	  if(L1){
	    probeInd_passL1.push_back(1);
	  }
	  else{
	    probeInd_passL1.push_back(0);
	  }

	  if(HLT){
	    probeInd_passHLT.push_back(1);
	  }
	  else{
	    probeInd_passHLT.push_back(0);
	  }
	  
      if(HLT_low){
	    probeInd_passHLT_low.push_back(1);
	  }
	  else{
	    probeInd_passHLT_low.push_back(0);
	  }


	  if(ID){
	    probeInd_passID.push_back(1);
	  }
	  else{
	    probeInd_passID.push_back(0);
	  }

	  if(ID && ISO){
	    probeInd_passISO.push_back(1);
	  }
	  else{
	    probeInd_passISO.push_back(0);
	  }

	}

      }
   
      if(!tagFound) continue;

      nentryTnp++;
      //cout << "tagInd = " << tagInd << endl;
      //cout << "tag is found and number of probes = " << probeInd.size() << endl;

      for(int itp = 0; itp < probeInd.size(); itp++){
	// pt energy correction and smearing
	double phoEt_corrected_tag = v_phoEt.at(tagInd) / photonEnergyCorrections_pp->Eval(v_phoEt.at(tagInd));
	double phoEt_corrected_probe= v_phoEt.at(probeInd.at(itp)) / photonEnergyCorrections_pp->Eval(v_phoEt.at(probeInd.at(itp)));
#ifdef MC
	double dataSigma = h_z_width_data_pp->GetBinContent(1);
	double mcSigma = h_z_width_mc_pp->GetBinContent(1);
	double smearSigma = TMath::Sqrt(dataSigma*dataSigma-mcSigma*mcSigma);
	phoEt_corrected_tag = phoEt_corrected_tag * r3->Gaus(1, smearSigma);
	phoEt_corrected_probe = phoEt_corrected_probe * r3->Gaus(1, smearSigma);
#endif

        //tag_pt = v_phoEt.at(tagInd);
        tag_pt = phoEt_corrected_tag; 
        tag_SCeta = v_phoSCEta.at(tagInd);
        tag_SCphi = v_phoSCPhi.at(tagInd);
        tag_eta = v_phoEta.at(tagInd);
        tag_phi = v_phoPhi.at(tagInd);
        tag_hoe = v_phoHoverE.at(tagInd);
        tag_sigmaIetaIeta = v_phoSigmaIEtaIEta.at(tagInd);
        tag_ecalClusterIsoR4 = v_ecalClusterIsoR4.at(tagInd);
        tag_hcalRechitIsoR4 = v_hcalRechitIsoR4.at(tagInd);
        tag_sumIso = v_ecalClusterIsoR4.at(tagInd) + v_hcalRechitIsoR4.at(tagInd);

	//cout << "tag = " << tag_pt << " , " << tag_eta << " , " << tag_phi << endl;

        //probe_pt = v_phoEt.at(probeInd.at(itp));
        probe_pt = phoEt_corrected_probe; 
        probe_eta = v_phoEta.at(probeInd.at(itp));
        probe_SCeta = v_phoSCEta.at(probeInd.at(itp));
        probe_abseta = abs(probe_eta);
        probe_SCphi = v_phoSCPhi.at(probeInd.at(itp));
        probe_phi = v_phoPhi.at(probeInd.at(itp));
        probe_hoe = v_phoHoverE.at(probeInd.at(itp));
        probe_sigmaIetaIeta = v_phoSigmaIEtaIEta.at(probeInd.at(itp));
        probe_ecalClusterIsoR4 = v_ecalClusterIsoR4.at(probeInd.at(itp));
        probe_hcalRechitIsoR4 = v_hcalRechitIsoR4.at(probeInd.at(itp));
        probe_sumIso = v_ecalClusterIsoR4.at(probeInd.at(itp)) + v_hcalRechitIsoR4.at(probeInd.at(itp));

	//cout << "probe = " << probe_pt << " , " << probe_eta << " , " << probe_phi << endl;

	//don't apply any cut
	diPhoMass = TMath::Sqrt(2*tag_pt*probe_pt*(TMath::CosH(tag_eta-probe_eta)-TMath::Cos(tag_phi-probe_phi)));

	// apply the cut
	bool massRange = (diPhoMass > 60 && diPhoMass < 120);
	if(!massRange) continue;

#ifdef MC
    if(tag_pt>15 && tag_pt<40) tagPrescl++;
    if((tag_pt>15 && tag_pt<40) && tagPrescl%20!=0) continue;
#endif

	passID = probeInd_passID.at(itp);
	passISO = probeInd_passISO.at(itp);
	passL1 = probeInd_passL1.at(itp);
	passHLT = probeInd_passHLT.at(itp);
	passHLT_low = probeInd_passHLT_low.at(itp);
	//cout << "diphoton mass = " << diPhoMass << endl;
	//cout << "pass ID = " << passID << " ISO = " << passISO << " L1 = " << passL1 << " HLT = " << passHLT << endl;

	treeFilled++;
	//fill the tree here ! 
	tr->Fill();
      }
   
   } // event loop

   cout << "nentryTnp = " << nentryTnp << endl;
   cout << "treeFilled = " << treeFilled << endl;
   //write the output
   fout->Write();
   fout->Close();

}

