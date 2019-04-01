//#define MC // comment this line to run on data

#ifdef MC
#include "ggTreeReaderPbPb.C"
#include "hltTreeReaderPbPb.C"
#include "globalTreeReaderPbPb.C"
#include "hiEvtTreeReaderPbPb.C"
#include "hltobjTreeReaderHiPho40PbPb.C"
#define ggTreeReaderPbPb ggTreeReaderPbPb
#define hltTreeReaderPbPb hltTreeReaderPbPb
#define globalTreeReaderPbPb globalTreeReaderPbPb
#define hiEvtTreeReaderPbPb hiEvtTreeReaderPbPb
#define hltobjTreeReaderPbPb hltobjTreeReaderHiPho40PbPb

#else
#include "ggTreeReaderPbPbData.C"
#include "hltTreeReaderPbPbData.C"
#include "globalTreeReaderPbPbData.C"
#include "hiEvtTreeReaderPbPbData.C"
#include "hltobjTreeReaderHiPho40PbPbData.C"
#define ggTreeReaderPbPb ggTreeReaderPbPbData
#define hltTreeReaderPbPb   hltTreeReaderPbPbData
#define globalTreeReaderPbPb globalTreeReaderPbPbData
#define hiEvtTreeReaderPbPb hiEvtTreeReaderPbPbData
#define hltobjTreeReaderPbPb hltobjTreeReaderHiPho40PbPbData
#endif
#include "TH1F.h"
#include "TH1D.h"
#include "TF1.h"
#include "TRandom3.h"
#include "TLorentzVector.h"
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


void fillTreeTnP_PbPb_v9_mit() {
   TChain *tchHLT = new TChain("hltanalysis/HltTree");
   TChain *tchEvt = new TChain("ggHiNtuplizer/EventTree");
   TChain *tchGlob = new TChain("skimanalysis/HltTree");
   TChain *tchHiEvt = new TChain("hiEvtAnalyzer/HiTree");
   TChain *tchHtlObj = new TChain("hltobject/HLT_HISinglePhoton40_Eta1p5_v");
   TChain *tchHtlObj_low = new TChain("hltobject/HLT_HISinglePhoton20_Eta1p5_v");
#ifdef MC
   //Ze30eeJet ext1
   //tchEvt->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-v1-FOREST/job0.root");
   //tchHLT->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-v1-FOREST/job0.root");
   //tchGlob->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-v1-FOREST/job0.root");
   //tchHiEvt->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-v1-FOREST/job0.root");
   //tchHtlObj->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-v1-FOREST/job0.root");
   //tchHtlObj_low->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-v1-FOREST/job0.root");
   ////Ze30eeJet
   //tchEvt->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1-FOREST/job0.root");
   //tchHLT->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1-FOREST/job0.root");
   //tchGlob->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1-FOREST/job0.root");
   //tchHiEvt->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1-FOREST/job0.root");
   //tchHtlObj->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1-FOREST/job0.root");
   //tchHtlObj_low->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Z30eeJet_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1-FOREST/job0.root");
   //Ze10e10 ext1
   tchEvt->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-v1-FOREST/job0.root");
   tchHLT->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-v1-FOREST/job0.root");
   tchGlob->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-v1-FOREST/job0.root");
   tchHiEvt->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-v1-FOREST/job0.root");
   tchHtlObj->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-v1-FOREST/job0.root");
   tchHtlObj_low->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-v1-FOREST/job0.root");
   //Ze10e10 
   tchEvt->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1-FOREST/job0.root");
   tchHLT->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1-FOREST/job0.root");
   tchGlob->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1-FOREST/job0.root");
   tchHiEvt->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1-FOREST/job0.root");
   tchHtlObj->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1-FOREST/job0.root");
   tchHtlObj_low->Add("/mnt/hadoop/cms/store/user/katatar/official/Pythia8_Ze10e10_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1-FOREST/job0.root");
#else
   ifstream myReadFile;
   myReadFile.open("HIPhoton40AndZ.txt");
   string path = "/mnt/hadoop/cms/store/user/rbi/HIPhoton40AndZ/azsigmon-HIRun2015E-PromptReco-AOD-DielectronSkim-ElePt8-v3_forest_csjet_v1_3/160315_214446/0000/";
   char output[800];

   if (myReadFile.is_open()) {
     while (!myReadFile.eof()) {
       myReadFile >> output;
       if (myReadFile.eof()) break;

       stringstream ss;
       string s_output = "";
       string finalPath = "";
       ss << output;
       ss >> s_output;

       finalPath += path;
       finalPath += s_output;
       cout << "path = " << finalPath << endl;
       tchHLT->Add(finalPath.c_str());
       tchEvt->Add(finalPath.c_str());
       tchGlob->Add(finalPath.c_str());
       tchHiEvt->Add(finalPath.c_str());
       tchHtlObj->Add(finalPath.c_str());
       tchHtlObj_low->Add(finalPath.c_str());
     }
   }
   cout << "all added" << endl;
   myReadFile.close();
   cout << "file is closed" << endl;
#endif
   cout << tchHLT->GetEntriesFast() << " " << tchEvt->GetEntriesFast() << " " << tchGlob->GetEntriesFast()  << endl;
   cout << tchHLT->GetEntries() << " " << tchEvt->GetEntries() << " " << tchGlob->GetEntries()  << endl;
   cout << tchHLT->GetEntriesFast() << " " << tchEvt->GetEntriesFast() << " " << tchGlob->GetEntriesFast()  << endl;

   hltTreeReaderPbPb hltR(tchHLT);
   ggTreeReaderPbPb evtR(tchEvt);
   globalTreeReaderPbPb globR(tchGlob);
   hiEvtTreeReaderPbPb hiEvtR(tchHiEvt);
   hltobjTreeReaderPbPb hltObjR(tchHtlObj);
   hltobjTreeReaderPbPb hltObjR_low(tchHtlObj_low);

   // set branch status
   hltR.fChain->SetBranchStatus("*",0);
   evtR.fChain->SetBranchStatus("*",0);
   globR.fChain->SetBranchStatus("*",0);
   hiEvtR.fChain->SetBranchStatus("*",0);
   hltObjR.fChain->SetBranchStatus("*",0);
   hltObjR_low.fChain->SetBranchStatus("*",0);

   //PbPb island photons
   evtR.fChain->SetBranchStatus("nPho",1);
   evtR.fChain->SetBranchStatus("phoEt",1);
   evtR.fChain->SetBranchStatus("phoEta",1);
   evtR.fChain->SetBranchStatus("phoPhi",1);
   //evtR.fChain->SetBranchStatus("phoSCEta",1);
   //evtR.fChain->SetBranchStatus("phoSCPhi",1);
   evtR.fChain->SetBranchStatus("phoHoverE",1);
   evtR.fChain->SetBranchStatus("phoSigmaIEtaIEta_2012",1);

   evtR.fChain->SetBranchStatus("pho_ecalClusterIsoR4",1);
   evtR.fChain->SetBranchStatus("pho_hcalRechitIsoR4",1);
   evtR.fChain->SetBranchStatus("pho_trackIsoR4PtCut20",1);

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

   // l1
   hltR.fChain->SetBranchStatus("NL1IsolEm",1);
   hltR.fChain->SetBranchStatus("L1IsolEm*",1);
   hltR.fChain->SetBranchStatus("NL1NIsolEm",1);
   hltR.fChain->SetBranchStatus("L1NIsolEm*",1);
#ifdef MC
   hltR.fChain->SetBranchStatus("HLT_HISinglePhoton40_Eta1p5_v2",1);
   hltR.fChain->SetBranchStatus("HLT_HISinglePhoton20_Eta1p5_v2",1);
#else
   hltR.fChain->SetBranchStatus("HLT_HISinglePhoton40_Eta1p5_v1",1);
   hltR.fChain->SetBranchStatus("HLT_HISinglePhoton20_Eta1p5_v1",1);
#endif
   hltR.fChain->SetBranchStatus("Event",1);

   // global filters
   globR.fChain->SetBranchStatus("pcollisionEventSelection",1);
   globR.fChain->SetBranchStatus("HBHENoiseFilterResultRun2Loose",1);

   hiEvtR.fChain->SetBranchStatus("hiBin",1);
   hiEvtR.fChain->SetBranchStatus("vz",1);

   hltObjR.fChain->SetBranchStatus("TriggerObjID",1);
   hltObjR.fChain->SetBranchStatus("pt",1);
   hltObjR.fChain->SetBranchStatus("eta",1);
   hltObjR.fChain->SetBranchStatus("phi",1);
   hltObjR.fChain->SetBranchStatus("mass",1);
   hltObjR_low.fChain->SetBranchStatus("TriggerObjID",1);
   hltObjR_low.fChain->SetBranchStatus("pt",1);
   hltObjR_low.fChain->SetBranchStatus("eta",1);
   hltObjR_low.fChain->SetBranchStatus("phi",1);
   hltObjR_low.fChain->SetBranchStatus("mass",1);

   if (evtR.fChain == 0) return;
   if (hltR.fChain == 0) return;
   if (globR.fChain == 0) return;
   if (hiEvtR.fChain == 0) return;
   if (hltObjR.fChain == 0) return;
   if (hltObjR_low.fChain == 0) return;

   Long64_t nentries = evtR.fChain->GetEntriesFast();
   Long64_t nentries2 = hltR.fChain->GetEntriesFast();
   Long64_t nentries3 = globR.fChain->GetEntriesFast();

   if (nentries != nentries2 || nentries != nentries3 || nentries3 != nentries2) return;

#ifdef MC
   TFile *fout = new TFile("output_mc_PbPb_v9.root","RECREATE");
#else
   TFile *fout = new TFile("output_data_PbPb_v9.root","RECREATE");
#endif

   // tree for tnp
   TDirectory *tdir = fout->mkdir("phoTree");
   tdir->cd();
   TTree *tr = new TTree("fitter_tree","");

   // probe photon
   float probe_pt, probe_eta, probe_phi, probe_abseta;
   float probe_hoe, probe_sigmaIetaIeta, probe_ecalClusterIsoR4, probe_hcalRechitIsoR4, probe_sumIso;
   //tag photon   
   float tag_pt, tag_eta, tag_phi;
   float tag_hoe, tag_sigmaIetaIeta, tag_ecalClusterIsoR4, tag_hcalRechitIsoR4, tag_sumIso;
   //diphoton
   float diPhoMass;
   //flags
   int passID;
   int passISO;
   int passL1;
   int passHLT;
   int passHLT_low;
   //weights for mc, for data = 1
   float vz_weight, cent_weight, cent_weight_res, final_weight;
   int centBin;

   // book variables
   tr->Branch("probe_pt",&probe_pt,"probe_pt/F");
   tr->Branch("tag_pt",&tag_pt,"tag_pt/F");
   tr->Branch("probe_eta",&probe_eta,"probe_eta/F");
   tr->Branch("probe_abseta",&probe_abseta,"probe_abseta/F");
   tr->Branch("tag_eta",&tag_eta,"tag_eta/F");
   tr->Branch("probe_phi",&probe_phi,"probe_phi/F");
   tr->Branch("tag_phi",&tag_phi,"tag_phi/F");
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
   tr->Branch("cent_weight",&cent_weight,"cent_weight/F");
   tr->Branch("vz_weight",&vz_weight,"vz_weight/F");
   tr->Branch("final_weight",&final_weight,"final_weight/F");
   tr->Branch("centBin",&centBin,"centBin/I");
#ifdef MC
   tr->Branch("cent_weight_res",&cent_weight_res,"cent_weight_res/F");
   TFile fileW("pbpb_Ze10e10_MC_weights.root");
   TH1F *hCentW = (TH1F*)fileW.Get("hcent_tmp");
   TH1F *hVzW = (TH1F*)fileW.Get("hvz");
   
   TFile fileW_res("resWeight_MC_weights.root");
   TH1F *hCentW_res = (TH1F*)fileW_res.Get("hcent");
#endif

   //files for energy corection and smearing
   TFile fcorr("photonEnergyCorrections_pbpb_COMB_AllQCD_0726.root");
   const int nCentBins = 7; 
   int centBins[2][nCentBins] = {{0, 10, 20, 40, 60, 100, 140},{10, 20, 40, 60, 100, 140, 200}};
   TF1* photonEnergyCorrections[nCentBins] = {0};
   for (int i=0; i<nCentBins; ++i){
	   photonEnergyCorrections[i] = (TF1*)fcorr.Get(Form("f_mean_gaus_cent%i_eta%i", i, 0));
   }
#ifdef MC
   TFile fsmear("eleMatchedPhotonZPeak_pbpb_AllQCD_0726_reweighted_nCentBins4.root");
   TF1* f_z_width_data = (TF1*)fsmear.Get("f_width");
   TF1* f_z_width_mc= (TF1*)fsmear.Get("f_width_mc");
#endif
   TRandom3 *r3=new TRandom3();

   double nentryTnp = 0;
   double treeFilled = 0;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      if (jentry%100000==0) cout << "--> " << jentry << "/" << nentries << endl;
      //cout << "--> " << jentry << "/" << nentries << endl;
      Long64_t ientry_evt = evtR.LoadTree(jentry);
      if (ientry_evt < 0) break;
      //cout << "after evtR" << endl;
      Long64_t ientry_hlt = hltR.LoadTree(jentry);
      if (ientry_hlt < 0) break;
      //cout << "after hlt" << endl;
      Long64_t ientry_glob = globR.LoadTree(jentry);
      if (ientry_glob < 0) break;
      //cout << "after global" << endl;
      Long64_t ientry_hievt = hiEvtR.LoadTree(jentry);
      if (ientry_hievt < 0) break;
      //cout << "after hiEvt" << endl;
      Long64_t ientry_hltobj = hltObjR.LoadTree(jentry);
      if (ientry_hltobj < 0) break;
      Long64_t ientry_hltobj_low = hltObjR_low.LoadTree(jentry);
      if (ientry_hltobj_low < 0) break;
      //cout << "after hltobg" << endl;

      // basic cuts
      evtR.b_nEle->GetEntry(ientry_evt);
      evtR.b_nPho->GetEntry(ientry_evt);

      //don't remove this! 
      nb = evtR.fChain->GetEntry(jentry);   nbytes += nb;
      nb = hltR.fChain->GetEntry(jentry);   nbytes += nb;
      nb = globR.fChain->GetEntry(jentry);   nbytes += nb;
      nb = hiEvtR.fChain->GetEntry(jentry);  nbytes += nb;
      nb = hltObjR.fChain->GetEntry(jentry);  nbytes += nb;
      nb = hltObjR_low.fChain->GetEntry(jentry);  nbytes += nb;

      //noise filters
      bool noiseFiltOk = (globR.pcollisionEventSelection && globR.HBHENoiseFilterResultRun2Loose);
      if(!noiseFiltOk) continue;

      //need at least 2 reco electrons and 2 photons
      bool gte_two_pho = evtR.nPho>=2;
      bool gte_two_ele = evtR.nEle>=2;
      if(!gte_two_pho || !gte_two_ele) continue;

#ifdef MC
      bool hltOk = hltR.HLT_HISinglePhoton40_Eta1p5_v2;
      bool hltOk_low = hltR.HLT_HISinglePhoton20_Eta1p5_v2;
#else
      bool hltOk = hltR.HLT_HISinglePhoton40_Eta1p5_v1;
      bool hltOk_low = hltR.HLT_HISinglePhoton20_Eta1p5_v1;
#endif
      if(!hltOk && !hltOk_low) continue;

      float cent_w = 1.;
      float cent_w_res = 1.;
      float vz_w = 1.;

#ifdef MC
      //int i = hCentW->GetXaxis()->FindBin(hiEvtR.hiBin);
      //cent_w = hCentW->GetBinContent(i);
      int j = hVzW->GetXaxis()->FindBin(hiEvtR.vz);
      vz_w = hVzW->GetBinContent(j);
      if(hiEvtR.hiBin<160){
	      int ii = hCentW->GetXaxis()->FindBin(hiEvtR.hiBin);
	      cent_w= hCentW->GetBinContent(ii);
      } else{
	      int ii = hCentW->GetXaxis()->FindBin(160);
	      cent_w= hCentW->GetBinContent(ii);
      }
      if(hiEvtR.hiBin<160){
              int ii = hCentW_res->GetXaxis()->FindBin(hiEvtR.hiBin);
              cent_w_res = hCentW_res->GetBinContent(ii);
      } else{
              int ii = hCentW_res->GetXaxis()->FindBin(160);
              cent_w_res = hCentW_res->GetBinContent(ii);
      }
      vz_weight = vz_w;
      cent_weight = cent_w;
      final_weight = vz_weight*cent_weight;
      cent_weight_res = cent_w_res;
      final_weight = vz_weight*cent_weight*cent_w_res;
#else
      vz_weight = vz_w;
      cent_weight = cent_w;
      final_weight = vz_weight*cent_weight;
#endif

      centBin = hiEvtR.hiBin;

      //match all electrons to photons 
      vector<int> v_phoIndMatch;
      vector<float> v_phoEt;
      vector<float> v_phoEta;
      vector<float> v_phoPhi;
      //vector<float> v_phoSCEta;
      //vector<float> v_phoSCPhi;
      vector<float> v_phoHoverE;
      vector<float> v_phoSigmaIEtaIEta;
      vector<float> v_ecalClusterIsoR4;
      vector<float> v_hcalRechitIsoR4;

      //hiBin for energy correction
      int icent = 0;
      for (; hiEvtR.hiBin>=centBins[1][icent] && icent<nCentBins; ++icent);
      for(int iEle = 0; iEle < evtR.nEle; iEle++){
	double dR_pho_ele = 999.;
	bool phoFound = false;
	int iPhoMatch =  0;
	bool phoMatch = false;

	bool eleInAcc = (abs(evtR.eleEta->at(iEle)) < acc_eta && evtR.elePt->at(iEle) > acc_min_pt && evtR.elePt->at(iEle) < acc_max_pt);
	//bool eleInAcc = (abs(evtR.eleSCEta->at(iEle)) < acc_eta && evtR.elePt->at(iEle) > acc_min_pt && evtR.elePt->at(iEle) < acc_max_pt);
	if(!eleInAcc) continue;

	for(Int_t iPho = 0; iPho < evtR.nPho; iPho++){

	  bool phoInAcc = (abs(evtR.phoEta->at(iPho)) < acc_eta && evtR.phoEt->at(iPho) > acc_min_pt && evtR.phoEt->at(iPho) < acc_max_pt);
	  //bool phoInAcc = (abs(evtR.phoSCEta->at(iPho)) < acc_eta && evtR.phoEt->at(iPho) > acc_min_pt && evtR.phoEt->at(iPho) < acc_max_pt);
	  if(!phoInAcc) continue;

	  double dRtmp = getDeltaR(evtR.eleEta->at(iEle),evtR.elePhi->at(iEle),evtR.phoEta->at(iPho),evtR.phoPhi->at(iPho));
	  //double dRtmp = getDeltaR(evtR.eleSCEta->at(iEle),evtR.eleSCPhi->at(iEle),evtR.phoSCEta->at(iPho),evtR.phoSCPhi->at(iPho));
	  
	  if( dRtmp < dR_pho_ele ){
	    dR_pho_ele = dRtmp;
	    phoFound = true;
	    iPhoMatch = iPho;
	  }
	}
	if(phoFound && dR_pho_ele<0.1) {
	  phoMatch = true;
	  v_phoIndMatch.push_back(iPhoMatch);
	  v_phoEt.push_back(evtR.phoEt->at(iPhoMatch));
	  v_phoEta.push_back(evtR.phoEta->at(iPhoMatch));
	  v_phoPhi.push_back(evtR.phoPhi->at(iPhoMatch));
      //do not use SC(super cluster) eta, phi
	  //v_phoSCEta.push_back(evtR.phoSCEta->at(iPhoMatch));
	  //v_phoSCPhi.push_back(evtR.phoSCPhi->at(iPhoMatch));
	  v_phoHoverE.push_back(evtR.phoHoverE->at(iPhoMatch));
	  v_phoSigmaIEtaIEta.push_back(evtR.phoSigmaIEtaIEta_2012->at(iPhoMatch));
	  v_ecalClusterIsoR4.push_back(evtR.pho_ecalClusterIsoR4->at(iPhoMatch));
	  v_hcalRechitIsoR4.push_back(evtR.pho_hcalRechitIsoR4->at(iPhoMatch));
	}
	if(!phoMatch) continue;
      }

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
        double phoEt_corrected = v_phoEt.at(iPhoM) / photonEnergyCorrections[icent]->Eval(v_phoEt.at(iPhoM));
#ifdef MC
	//pt smearing for mc photons
	double dataSigma = f_z_width_data->Eval(hiEvtR.hiBin);
	double mcSigma = f_z_width_mc->Eval(hiEvtR.hiBin);
	double smearSigma = TMath::Sqrt(dataSigma*dataSigma-mcSigma*mcSigma);
	phoEt_corrected = phoEt_corrected * r3->Gaus(1, smearSigma);
#endif

	//pass ISO
	bool ISO = (v_ecalClusterIsoR4.at(iPhoM) + v_hcalRechitIsoR4.at(iPhoM)) < 1;
	//pass ID 
	bool ID = (v_phoHoverE.at(iPhoM)<0.1 && v_phoSigmaIEtaIEta.at(iPhoM)<0.01);
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

	//match to HLT : add this part for MC when forest is ready;
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
	//match to HLT : add this part for MC when forest is ready;
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

	//if passes everything -> tag
	//if(ISO && ID && L1 && HLT && !tagFound){
	if(ISO && ID && (HLT || HLT_low) && !tagFound){//removed L1 condition
	  tagFound = true;
	  tagInd = iPhoM;
	}
	//if passes everything, but already got a tag, OR doesn't pass something -> probe
	//if((ISO && ID && L1 && HLT && tagFound && tagInd != iPhoM) || (!ISO || !ID || !L1 || !HLT)){
	if((ISO && ID && (HLT || HLT_low) && tagFound && tagInd != iPhoM) || (!ISO || !ID || !(HLT || HLT_low))){
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

	  //if(L1 && HLT){
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

	  //if(L1 && HLT && ID){
	  //if( (HLT || HLT_low) && ID){
	  if(ID){
	    probeInd_passID.push_back(1);
	  }
	  else{
	    probeInd_passID.push_back(0);
	  }

	  //if(L1 && HLT && ID && ISO){
	  //if( (HLT || HLT_low) && ID && ISO){
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
        double phoEt_corrected_tag = v_phoEt.at(tagInd) / photonEnergyCorrections[icent]->Eval(v_phoEt.at(tagInd));
        double phoEt_corrected_probe = v_phoEt.at(probeInd.at(itp)) / photonEnergyCorrections[icent]->Eval(v_phoEt.at(probeInd.at(itp)));
#ifdef MC
	//pt smearing for mc photons
	double dataSigma = f_z_width_data->Eval(hiEvtR.hiBin);
	double mcSigma = f_z_width_mc->Eval(hiEvtR.hiBin);
	double smearSigma = TMath::Sqrt(dataSigma*dataSigma-mcSigma*mcSigma);
	phoEt_corrected_tag = phoEt_corrected_tag * r3->Gaus(1, smearSigma);
	phoEt_corrected_probe = phoEt_corrected_probe * r3->Gaus(1, smearSigma);
#endif
        //tag_pt = v_phoEt.at(tagInd);
        tag_pt = phoEt_corrected_tag; 
        tag_eta = v_phoEta.at(tagInd);
        tag_phi = v_phoPhi.at(tagInd);
        //tag_eta = v_phoSCEta.at(tagInd);
        //tag_phi = v_phoSCPhi.at(tagInd);
        tag_hoe = v_phoHoverE.at(tagInd);
        tag_sigmaIetaIeta = v_phoSigmaIEtaIEta.at(tagInd);
        tag_ecalClusterIsoR4 = v_ecalClusterIsoR4.at(tagInd);
        tag_hcalRechitIsoR4 = v_hcalRechitIsoR4.at(tagInd);
        tag_sumIso = v_ecalClusterIsoR4.at(tagInd) + v_hcalRechitIsoR4.at(tagInd);

	//cout << "tag = " << tag_pt << " , " << tag_eta << " , " << tag_phi << endl;

        probe_pt = phoEt_corrected_probe; 
        //probe_pt = v_phoEt.at(probeInd.at(itp));
        probe_eta = v_phoEta.at(probeInd.at(itp));
        //probe_eta = v_phoSCEta.at(probeInd.at(itp));
        probe_abseta = abs(probe_eta);
        probe_phi = v_phoPhi.at(probeInd.at(itp));
        //probe_phi = v_phoSCPhi.at(probeInd.at(itp));
        probe_hoe = v_phoHoverE.at(itp);
        probe_sigmaIetaIeta = v_phoSigmaIEtaIEta.at(itp);
        probe_ecalClusterIsoR4 = v_ecalClusterIsoR4.at(itp);
        probe_hcalRechitIsoR4 = v_hcalRechitIsoR4.at(itp);
        probe_sumIso = v_ecalClusterIsoR4.at(itp) + v_hcalRechitIsoR4.at(itp);

	//cout << "probe = " << probe_pt << " , " << probe_eta << " , " << probe_phi << endl;


	diPhoMass = TMath::Sqrt(2*tag_pt*probe_pt*(TMath::CosH(tag_eta-probe_eta)-TMath::Cos(tag_phi-probe_phi)));
	bool massRange = (diPhoMass > 60 && diPhoMass < 120);
	if(!massRange) continue;

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

      //cout << "nentryTnp = " << nentryTnp << endl;
      //cout << "treeFilled = " << treeFilled << endl;
   
   } // event loop

   cout << "nentryTnp = " << nentryTnp << endl;
   cout << "treeFilled = " << treeFilled << endl;
   //write the output
   fout->Write();
   fout->Close();

}

