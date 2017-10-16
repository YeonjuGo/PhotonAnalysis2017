// Author: Yeonju Go
// Modifired : 2017 May 23 
// Created : 2017 May 23 

#include "TStyle.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCut.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLegendEntry.h"
#include "TString.h"
#include "TLatex.h"
#include "stdio.h"
#include <iostream>

#include "../phoRaaCuts/phoRaaCuts_temp.h"

void calculate_N_MB() {
  gStyle->SetOptStat(0);
  TH1::SetDefaultSumw2();
  
  int run[] =
  {262620, 262640, 262656, 262694, 262695, 262703,
      262726, 262735, 262768, 262784, 262811, 262816,
      262818, 262834, 262837, 262893, 262921, 262988,
      263005, 263022, 263035, 263261, 263286, 263322,
      263333, 263349, 263362, 263379, 263400, 263410,
      263502, 263584, 263604, 263614};
  const int Nrun = sizeof(run)/sizeof(int);

  const char* dir = "/home/goyeonju/CMS/Files/centrality/pbpb2015/"; //KOREA UNIV.
  const char* dataset = "HIMinimumBias2"; 
  int nEvents[Nrun];
  for(int i=0; i<Nrun; ++i){
      TFile* f1;
      f1 = TFile::Open(Form("%sEventTree_PbPb_data_%s_run%d_15Feb.root",dir,dataset,run[i]));
      if(f1->IsZombie()) { cout << run[i] << " doesn't exist!! " << endl; continue;}
      //cout << "Open file : " << f1->GetName() << endl;
      TTree* t1_hlt = (TTree*) f1 -> Get("hltanalysis/HltTree");
      TCut trigCut = "";
      if(run[i]<263155) trigCut = "HLT_HIL1MinimumBiasHF1AND_v1==1";
      else trigCut = "HLT_HIL1MinimumBiasHF2AND_part1_v1==1";
      nEvents[i] = t1_hlt->GetEntries(trigCut);
      cout << run[i]<< " # of events :\t"  <<nEvents[i] << endl;
   }
   
  int tot_nEvents = 0;  
  for(int i=0; i<Nrun; ++i){
    tot_nEvents += nEvents[i];
  }
  cout << " Total # of MB events : \t" << tot_nEvents << endl;
}

  
  
