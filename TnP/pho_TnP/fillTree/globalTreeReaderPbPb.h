//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jul 31 17:17:45 2018 by ROOT version 5.34/36
// from TTree HltTree/
// found on file: root://xrootd.cmsaf.mit.edu//store/user/tatar/official/Pythia8_Z30eeJet_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-FOREST/0.root
//////////////////////////////////////////////////////////

#ifndef globalTreeReaderPbPb_h
#define globalTreeReaderPbPb_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class globalTreeReaderPbPb {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           ana_step;
   Int_t           pcollisionEventSelection;
   Int_t           pHBHENoiseFilterResultProducer;
   Int_t           HBHENoiseFilterResult;
   Int_t           HBHENoiseFilterResultRun1;
   Int_t           HBHENoiseFilterResultRun2Loose;
   Int_t           HBHENoiseFilterResultRun2Tight;
   Int_t           HBHEIsoNoiseFilterResult;
   Int_t           pprimaryVertexFilter;
   Int_t           phfCoincFilter1;
   Int_t           phfCoincFilter2;
   Int_t           phfCoincFilter3;
   Int_t           phfCoincFilter4;
   Int_t           phfCoincFilter5;
   Int_t           pclusterCompatibilityFilter;

   // List of branches
   TBranch        *b_ana_step;   //!
   TBranch        *b_pcollisionEventSelection;   //!
   TBranch        *b_pHBHENoiseFilterResultProducer;   //!
   TBranch        *b_HBHENoiseFilterResult;   //!
   TBranch        *b_HBHENoiseFilterResultRun1;   //!
   TBranch        *b_HBHENoiseFilterResultRun2Loose;   //!
   TBranch        *b_HBHENoiseFilterResultRun2Tight;   //!
   TBranch        *b_HBHEIsoNoiseFilterResult;   //!
   TBranch        *b_pprimaryVertexFilter;   //!
   TBranch        *b_phfCoincFilter1;   //!
   TBranch        *b_phfCoincFilter2;   //!
   TBranch        *b_phfCoincFilter3;   //!
   TBranch        *b_phfCoincFilter4;   //!
   TBranch        *b_phfCoincFilter5;   //!
   TBranch        *b_pclusterCompatibilityFilter;   //!

   globalTreeReaderPbPb(TTree *tree=0);
   virtual ~globalTreeReaderPbPb();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef globalTreeReaderPbPb_cxx
globalTreeReaderPbPb::globalTreeReaderPbPb(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("root://xrootd.cmsaf.mit.edu//store/user/tatar/official/Pythia8_Z30eeJet_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-FOREST/0.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("root://xrootd.cmsaf.mit.edu//store/user/tatar/official/Pythia8_Z30eeJet_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-FOREST/0.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("root://xrootd.cmsaf.mit.edu//store/user/tatar/official/Pythia8_Z30eeJet_Hydjet_MB/HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13_ext1-FOREST/0.root:/skimanalysis");
      dir->GetObject("HltTree",tree);

   }
   Init(tree);
}

globalTreeReaderPbPb::~globalTreeReaderPbPb()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t globalTreeReaderPbPb::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t globalTreeReaderPbPb::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void globalTreeReaderPbPb::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("ana_step", &ana_step, &b_ana_step);
   fChain->SetBranchAddress("pcollisionEventSelection", &pcollisionEventSelection, &b_pcollisionEventSelection);
   fChain->SetBranchAddress("pHBHENoiseFilterResultProducer", &pHBHENoiseFilterResultProducer, &b_pHBHENoiseFilterResultProducer);
   fChain->SetBranchAddress("HBHENoiseFilterResult", &HBHENoiseFilterResult, &b_HBHENoiseFilterResult);
   fChain->SetBranchAddress("HBHENoiseFilterResultRun1", &HBHENoiseFilterResultRun1, &b_HBHENoiseFilterResultRun1);
   fChain->SetBranchAddress("HBHENoiseFilterResultRun2Loose", &HBHENoiseFilterResultRun2Loose, &b_HBHENoiseFilterResultRun2Loose);
   fChain->SetBranchAddress("HBHENoiseFilterResultRun2Tight", &HBHENoiseFilterResultRun2Tight, &b_HBHENoiseFilterResultRun2Tight);
   fChain->SetBranchAddress("HBHEIsoNoiseFilterResult", &HBHEIsoNoiseFilterResult, &b_HBHEIsoNoiseFilterResult);
   fChain->SetBranchAddress("pprimaryVertexFilter", &pprimaryVertexFilter, &b_pprimaryVertexFilter);
   fChain->SetBranchAddress("phfCoincFilter1", &phfCoincFilter1, &b_phfCoincFilter1);
   fChain->SetBranchAddress("phfCoincFilter2", &phfCoincFilter2, &b_phfCoincFilter2);
   fChain->SetBranchAddress("phfCoincFilter3", &phfCoincFilter3, &b_phfCoincFilter3);
   fChain->SetBranchAddress("phfCoincFilter4", &phfCoincFilter4, &b_phfCoincFilter4);
   fChain->SetBranchAddress("phfCoincFilter5", &phfCoincFilter5, &b_phfCoincFilter5);
   fChain->SetBranchAddress("pclusterCompatibilityFilter", &pclusterCompatibilityFilter, &b_pclusterCompatibilityFilter);
   Notify();
}

Bool_t globalTreeReaderPbPb::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void globalTreeReaderPbPb::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t globalTreeReaderPbPb::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef globalTreeReaderPbPb_cxx
