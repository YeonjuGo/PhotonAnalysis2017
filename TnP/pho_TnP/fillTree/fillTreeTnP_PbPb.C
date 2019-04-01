//#define MC // comment this line to run on data

#ifdef MC
#include "ggTreeReaderPbPb.C"
#include "hltTreeReaderPbPb.C"
#include "globalTreeReaderPbPb.C"
#include "hiEvtTreeReaderPbPb.C"

#define ggTreeReaderPbPb ggTreeReaderPbPb
#define hltTreeReaderPbPb hltTreeReaderPbPb
#define globalTreeReaderPbPb globalTreeReaderPbPb
#define hiEvtTreeReaderPbPb hiEvtTreeReaderPbPb

#else
#include "ggTreeReaderPbPbData.C"
#include "hltTreeReaderPbPbData.C"
#include "globalTreeReaderPbPbData.C"
#include "hiEvtTreeReaderPbPbData.C"
#define ggTreeReaderPbPb ggTreeReaderPbPbData
#define hltTreeReaderPbPb   hltTreeReaderPbPbData
#define globalTreeReaderPbPb globalTreeReaderPbPbData
#define hiEvtTreeReaderPbPb hiEvtTreeReaderPbPbData
#endif
#include "TH1F.h"
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
const double acc_eta = 1.5;
const double acc_min_pt = 40;
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


void fillTreeTnP_PbPb() {
   TChain *tchHLT = new TChain("hltanalysis/HltTree");
   TChain *tchEvt = new TChain("ggHiNtuplizer/EventTree");
   TChain *tchGlob = new TChain("skimanalysis/HltTree");
   TChain *tchHiEvt = new TChain("hiEvtAnalyzer/HiTree");
#ifdef MC
   tchEvt->Add("root://xrootd.cmsaf.mit.edu//store/user/tatar/official/Pythia8_Z30eeJet_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-FOREST/0.root");
   tchHLT->Add("root://xrootd.cmsaf.mit.edu//store/user/tatar/official/Pythia8_Z30eeJet_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-FOREST/0.root");
   tchGlob->Add("root://xrootd.cmsaf.mit.edu//store/user/tatar/official/Pythia8_Z30eeJet_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-FOREST/0.root");
   tchHiEvt->Add("root://xrootd.cmsaf.mit.edu//store/user/tatar/official/Pythia8_Z30eeJet_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-FOREST/0.root");
#else
   ifstream myReadFile;
   myReadFile.open("HIPhoton40AndZ.txt");
   string path = "root://xrootd.cmsaf.mit.edu//store/user/rbi/HIPhoton40AndZ/azsigmon-HIRun2015E-PromptReco-AOD-DielectronSkim-ElePt8-v3_forest_csjet_v1_3/160315_214446/0000/";
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

   // set branch status
   hltR.fChain->SetBranchStatus("*",0);
   evtR.fChain->SetBranchStatus("*",0);
   globR.fChain->SetBranchStatus("*",0);

   //PbPb island photons
   evtR.fChain->SetBranchStatus("nPho",1);
   evtR.fChain->SetBranchStatus("phoEt",1);
   evtR.fChain->SetBranchStatus("phoSCEta",1);
   evtR.fChain->SetBranchStatus("phoSCPhi",1);
   evtR.fChain->SetBranchStatus("phoHoverE",1);
   evtR.fChain->SetBranchStatus("phoSigmaIEtaIEta_2012",1);
#ifdef MC
   evtR.fChain->SetBranchStatus("pho_genMatchedIndex",1);
#endif
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
#else
   hltR.fChain->SetBranchStatus("HLT_HISinglePhoton40_Eta1p5_v1",1);
#endif
   hltR.fChain->SetBranchStatus("Event",1);

   // global filters
   globR.fChain->SetBranchStatus("pcollisionEventSelection",1);
   globR.fChain->SetBranchStatus("HBHENoiseFilterResultRun2Loose",1);

   hiEvtR.fChain->SetBranchStatus("hiBin",1);
   hiEvtR.fChain->SetBranchStatus("vz",1);

   if (evtR.fChain == 0) return;
   if (hltR.fChain == 0) return;
   if (globR.fChain == 0) return;
   if (hiEvtR.fChain == 0) return;

   Long64_t nentries = evtR.fChain->GetEntriesFast();
   Long64_t nentries2 = hltR.fChain->GetEntriesFast();
   Long64_t nentries3 = globR.fChain->GetEntriesFast();

   if (nentries != nentries2 || nentries != nentries3 || nentries3 != nentries2) return;

#ifdef MC
   TFile *fout = new TFile("output_mc_PbPb_massRange.root","RECREATE");
#else
   TFile *fout = new TFile("output_data_PbPb_massRange.root","RECREATE");
#endif

   // tree for tnp
   TDirectory *tdir = fout->mkdir("phoTree");
   tdir->cd();
   TTree *tr = new TTree("fitter_tree","");

   // probe photon
   float probe_pt, probe_eta, probe_phi, probe_abseta;
   //tag photon   
   float tag_pt, tag_eta, tag_phi;
   //diphoton
   float diPhoMass;
   //flags
   int passID;
   int passISO;
   int passL1;
   int passHLT;
   //weights for mc, for data = 1
   float vz_weight, cent_weight, final_weight;
   int centBin;

   // book variables
   tr->Branch("probe_pt",&probe_pt,"probe_pt/F");
   tr->Branch("tag_pt",&tag_pt,"tag_pt/F");
   tr->Branch("probe_eta",&probe_eta,"probe_eta/F");
   tr->Branch("probe_abseta",&probe_abseta,"probe_abseta/F");
   tr->Branch("tag_eta",&tag_eta,"tag_eta/F");
   tr->Branch("probe_phi",&probe_phi,"probe_phi/F");
   tr->Branch("tag_phi",&tag_phi,"tag_phi/F");
   tr->Branch("diPhoMass",&diPhoMass,"diPhoMass/F");
   tr->Branch("passID",&passID,"passID/I");
   tr->Branch("passISO",&passISO,"passISO/I");
   tr->Branch("passL1",&passL1,"passL1/I");
   tr->Branch("passHLT",&passHLT,"passHLT/I");
   tr->Branch("cent_weight",&cent_weight,"cent_weight/F");
   tr->Branch("vz_weight",&vz_weight,"vz_weight/F");
   tr->Branch("final_weight",&final_weight,"final_weight/F");
   tr->Branch("centBin",&centBin,"centBin/I");
#ifdef MC
   TFile fileW("pbpb_ZtoEE_MC_weights.root");
   TH1F *hCentW = (TH1F*)fileW.Get("hcent");
   TH1F *hVzW = (TH1F*)fileW.Get("hvz");
#endif


   double nentryTnp = 0;
   double treeFilled = 0;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      if (jentry%100000==0) cout << "--> " << jentry << "/" << nentries << endl;
      cout << "--> " << jentry << "/" << nentries << endl;
      Long64_t ientry_evt = evtR.LoadTree(jentry);
      if (ientry_evt < 0) break;
      Long64_t ientry_hlt = hltR.LoadTree(jentry);
      if (ientry_hlt < 0) break;
      Long64_t ientry_glob = globR.LoadTree(jentry);
      if (ientry_glob < 0) break;
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
#ifdef MC
      nb = hiEvtR.fChain->GetEntry(jentry);  nbytes += nb;
#endif

      //noise filters
      bool noiseFiltOk = (globR.pcollisionEventSelection && globR.HBHENoiseFilterResultRun2Loose);
      if(!noiseFiltOk) continue;

      //need at least 2 reco electrons and 2 photons
      bool gte_two_pho = evtR.nPho>=2;
      bool gte_two_ele = evtR.nEle>=2;
      if(!gte_two_pho || !gte_two_ele) continue;

#ifdef MC
      bool hltOk = hltR.HLT_HISinglePhoton40_Eta1p5_v2;
#else
      bool hltOk = hltR.HLT_HISinglePhoton40_Eta1p5_v1;
#endif
      if(!hltOk) continue;

      float cent_w = 1.;
      float vz_w = 1.;

#ifdef MC
      int i = hCentW->GetXaxis()->FindBin(hiEvtR.hiBin);
      cent_w = hCentW->GetBinContent(i);
      int j = hVzW->GetXaxis()->FindBin(hiEvtR.vz);
      vz_w = hVzW->GetBinContent(j);
#endif
      vz_weight = vz_w;
      cent_weight = cent_w;
      final_weight = vz_weight*cent_weight;

      centBin = hiEvtR.hiBin;

      //match all electrons to photons 
      vector<int> v_phoIndMatch;
      vector<float> v_phoEt;
      vector<float> v_phoSCEta;
      vector<float> v_phoSCPhi;
      vector<float> v_phoHoverE;
      vector<float> v_phoSigmaIEtaIEta;
      vector<float> v_ecalClusterIsoR4;
      vector<float> v_hcalRechitIsoR4;

      for(int iEle = 0; iEle < evtR.nEle; iEle++){
	double dR_pho_ele = 999.;
	bool phoFound = false;
	int iPhoMatch =  0;
	bool phoMatch = false;

	bool eleInAcc = (abs(evtR.eleSCEta->at(iEle)) < acc_eta && evtR.elePt->at(iEle) > acc_min_pt && evtR.elePt->at(iEle) < acc_max_pt);
	if(!eleInAcc) continue;

	for(Int_t iPho = 0; iPho < evtR.nPho; iPho++){

	  bool phoInAcc = (abs(evtR.phoSCEta->at(iPho)) < acc_eta && evtR.phoEt->at(iPho) > acc_min_pt && evtR.phoEt->at(iPho) < acc_max_pt);
	  if(!phoInAcc) continue;

	  double dRtmp = getDeltaR(evtR.eleSCEta->at(iEle),evtR.eleSCPhi->at(iEle),evtR.phoSCEta->at(iPho),evtR.phoSCPhi->at(iPho));
	  
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
	  v_phoSCEta.push_back(evtR.phoSCEta->at(iPhoMatch));
	  v_phoSCPhi.push_back(evtR.phoSCPhi->at(iPhoMatch));
	  v_phoHoverE.push_back(evtR.phoHoverE->at(iPhoMatch));
	  v_phoSigmaIEtaIEta.push_back(evtR.phoSigmaIEtaIEta_2012->at(iPhoMatch));
	  v_ecalClusterIsoR4.push_back(evtR.pho_ecalClusterIsoR4->at(iPhoMatch));
	  v_hcalRechitIsoR4.push_back(evtR.pho_hcalRechitIsoR4->at(iPhoMatch));
	}
	if(!phoMatch) continue;
      }

      if(v_phoIndMatch.size() < 2) continue;

      bool tagFound = false;
      bool asProbe = false;
      int tagInd = -999.;
      vector<int> probeInd;
      vector<int> probeInd_passID;
      vector<int> probeInd_passISO;
      vector<int> probeInd_passL1;
      vector<int> probeInd_passHLT;

      for(int iPhoM = 0; iPhoM < v_phoIndMatch.size(); iPhoM++){
	asProbe = false;

	//pass ISO
	bool ISO = (v_ecalClusterIsoR4.at(iPhoM) + v_hcalRechitIsoR4.at(iPhoM)) < 1;
	//pass ID 
	bool ID = (v_phoHoverE.at(iPhoM)<0.1 && v_phoSigmaIEtaIEta.at(iPhoM)<0.01);
	//match to L1 
	bool L1 = false;
	TLorentzVector phoTLorVect;
	phoTLorVect.SetPtEtaPhiM(v_phoEt.at(iPhoM),v_phoSCEta.at(iPhoM),v_phoSCPhi.at(iPhoM),0);
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

	//match to HLT : add this part for MC when forest is ready, and switch start from false. For now HLT eff = 1.
	bool HLT = true;
	/*
#ifdef MC
	matchHLT = false;
#else
	matchHLT = false;
#endif
	*/
	//if passes everything -> tag
	if(ISO && ID && L1 && HLT && !tagFound){
	  tagFound = true;
	  tagInd = iPhoM;
	}
	//if passes everything (dont forget to add HLT here too), but already got a tag, OR doesn't pass something -> probe
	if((ISO && ID && L1 && HLT && tagFound && tagInd != iPhoM) || (!ISO || !ID || !L1 || !HLT)){
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

	  if(L1 && HLT){
	    probeInd_passHLT.push_back(1);
	  }
	  else{
	    probeInd_passHLT.push_back(0);
	  }

	  if(L1 && HLT && ID){
	    probeInd_passID.push_back(1);
	  }
	  else{
	    probeInd_passID.push_back(0);
	  }

	  if(L1 && HLT && ID && ISO){
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
        tag_pt = v_phoEt.at(tagInd);
        tag_eta = v_phoSCEta.at(tagInd);
        tag_phi = v_phoSCPhi.at(tagInd);

	//cout << "tag = " << tag_pt << " , " << tag_eta << " , " << tag_phi << endl;

        probe_pt = v_phoEt.at(probeInd.at(itp));
        probe_eta = v_phoSCEta.at(probeInd.at(itp));
        probe_abseta = abs(probe_eta);
        probe_phi = v_phoSCPhi.at(probeInd.at(itp));

	//cout << "probe = " << probe_pt << " , " << probe_eta << " , " << probe_phi << endl;


	diPhoMass = TMath::Sqrt(2*tag_pt*probe_pt*(TMath::CosH(tag_eta-probe_eta)-TMath::Cos(tag_phi-probe_phi)));
	bool massRange = (diPhoMass > 60 && diPhoMass < 120);
	if(!massRange) continue;

	passID = probeInd_passID.at(itp);
	passISO = probeInd_passISO.at(itp);
	passL1 = probeInd_passL1.at(itp);
	passHLT = probeInd_passHLT.at(itp);
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

