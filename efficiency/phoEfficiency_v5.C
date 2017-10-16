/*
* To get photon reconstruction & various isolation efficiency.
* Apply denominator and numerator cuts as a string in argument. 
* Using Event, mc, photon For 3 kinds of loops, Fill the *gen* photons one by one. 
* 
* v4 update : add TGraphAsymmErrors objects with BayesianDivision 
* Created at 2016 Apr 07
* Modified at 2016 Aug 13
* Creator : Yeonju Go
*/ 

#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "TLatex.h"
#include "TCut.h"
#include "TEfficiency.h"
#include "TChain.h"
#include "stdio.h"
#include <vector>
#include <map>
#include <string>
#include "../yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
#include "../ElectroWeak-Jet-Track-Analyses/TreeHeaders/ggHiNtuplizerTree.h"
#include "../ElectroWeak-Jet-Track-Analyses/Utilities/interface/CutConfigurationParser.h"
#include "../ElectroWeak-Jet-Track-Analyses/Utilities/interface/InputConfigurationParser.h"
//using namespace std;
const float delta2 = 0.15*0.15;
const float delta = 0.15;

void stringToMap(string cutst, map<string,int> & cutmap, int mapVal){
    std::string s = cutst;
    std::string delimiter = "_";
    //std::string delimiter = ",";

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        cutmap[token] = mapVal;
        //std::cout << token << std::endl;
        s.erase(0, pos + delimiter.length());
    }
    //std::cout << s << std::endl;
    cutmap[s] = mapVal;
}

TH1D* changeToPrettyBin(TH1D* h){
    TH1D* hnew = new TH1D(Form("%s_prettyBin",h->GetName()),Form("%s",h->GetTitle()),nPtBin,ptBins_draw);
    for(int i=0;i<h->GetNbinsX();++i){
        hnew->SetBinContent(i+1,h->GetBinContent(i+1));
        float err = h->GetBinError(i+1);
        if(err!=0) hnew->SetBinError(i+1,err);
        else hnew->SetBinError(i+1,0.0001);
    }
    return hnew;
}

//Cut variation = fragDirPhoCut, fragPhoCut, dirPhoCut, decayPhoCut, hotspotCut, spikeCut, hoeCut(pp/pbpb), sigEtaEtaCut(pp/pbpb), sumIsoCut(pp/pbpb)
void phoEfficiency_v5(const TString inputFile, string den_st="", string num_st="hotspotCut_spikeCut_hoeCut_sigEtaEtaCut_sumIsoCut", const TString coll="pbpb", int cent_i=0, int cent_f=200, const char* ver="v5",int ppIsoIndex=1)
{
    gStyle->SetStatStyle(0);
    SetHistTitleStyle();
    TH1::SetDefaultSumw2();
    double pur_num_pp[] = {91.0,89.0,88.0,84.0};
    gStyle->SetLabelSize(0.03,"Y");
    gStyle->SetTitleYSize(0.05);
    gStyle->SetTitleXSize(0.05);
    TChain *treePho;
    if(coll=="pbpb") treePho = new TChain("ggHiNtuplizer/EventTree");
    else if(coll=="pp") treePho = new TChain("ggHiNtuplizerGED/EventTree");
    TChain *treeEvt = new TChain("hiEvtAnalyzer/HiTree");

    std::vector<std::string> inputFiles = InputConfigurationParser::ParseFiles(inputFile.Data());
    std::cout<<"input ROOT files : num = "<<inputFiles.size()<< std::endl;
    for(std::vector<std::string>::iterator it = inputFiles.begin() ; it != inputFiles.end(); ++it) {
        treePho->Add((*it).c_str());
        treeEvt->Add((*it).c_str());
        cout <<"input ROOT file : " << (*it).c_str() << endl;
    }

    ggHiNtuplizer pho;
    pho.setupTreeForReading(treePho);
    ULong64_t event=0;
    unsigned run=0;
    unsigned lumi=0;
    int hiBin=0;
    treeEvt->SetBranchAddress("evt",&event);
    treeEvt->SetBranchAddress("run",&run);
    treeEvt->SetBranchAddress("lumi",&lumi);
    treeEvt->SetBranchAddress("hiBin",&hiBin);

    // if map=0,no cut on den&num// map=1, cut on both den and num// map=2, cut on only num but not on den//
    map<string,int> cut_map; 
    stringToMap(den_st,cut_map,1);
    stringToMap(num_st,cut_map,2);
    cout << "############ MAP KEYS ############## " << endl;
    //cout << "0 for non of them, 1 for both of them, 2 for only numberator" << endl;
    for(map<string,int>::iterator it = cut_map.begin() ; it != cut_map.end() ; ++it)
    {
        cout << it->first <<" "  << it->second << endl;
    }
    cout << "#################################### " << endl;

    ///////////////////////////////////////////
    // DEFINE histograms
    
    TH2D* h2D_Num = new TH2D("h2D_Num", ";|#eta|;p_{T} (GeV)", nEtaBin, etaBins, nPtBin, ptBins);
    TH2D* h2D_Den = (TH2D*) h2D_Num->Clone("h2D_Den");
    TH2D* h2D_Eff = (TH2D*) h2D_Num->Clone("h2D_Eff");
    TH2D* h2D_Num_recons = new TH2D("h2D_Num_recons", ";|#eta|;p_{T} (GeV)", nEtaBin, etaBins, nPtBin, ptBins);
    TH2D* h2D_Den_recons = (TH2D*) h2D_Num->Clone("h2D_Den_recons");
    TH2D* h2D_Eff_recons = (TH2D*) h2D_Num->Clone("h2D_Eff_recons");
    TH2D* h2D_Eff_total;
    if(den_st=="") h2D_Eff_total = (TH2D*) h2D_Num->Clone("h2D_Eff_total");
    
    //h1D plots in barrel region 
    TH1D* h1D_Num = new TH1D("h1D_Num", ";p_{T}^{#gamma} (GeV);", nPtBin, ptBins);
    TH1D* h1D_Den = (TH1D*) h1D_Num->Clone("h1D_Den"); 
    TH1D* h1D_Num_recons = new TH1D("h1D_Num_recons", ";p_{T}^{#gamma} (GeV);", nPtBin, ptBins);
    TH1D* h1D_Den_recons = (TH1D*) h1D_Num->Clone("h1D_Den_recons"); 

    
    ///////////////////////////////////////////
    // Event Loop 
    int totalNumEntries = 0; 
    int totalDenEntries = 0; 
    Long64_t nentries = treePho->GetEntries();
    for(int ientries = 0; ientries < nentries; ++ientries)
    {
        if (ientries % 10000 == 0)  {
            std::cout << "current entry = " <<ientries<<" out of "<<nentries<<" : "<<std::setprecision(2)<<(double)ientries/nentries*100<<" %"<<std::endl;
        }
        treePho->GetEntry(ientries);
        treeEvt->GetEntry(ientries);

        if(coll=="pbpb" && !(hiBin>=cent_i && hiBin<cent_f)) continue;
        for (int igen = 0; igen < pho.nMC; ++igen){
            if (pho.mcStatus->at(igen) != 1 || (pho.mcPID->at(igen)) != 22 ) continue;
            if (pho.mcPt->at(igen)<30) continue;
            if (pho.mcCalIsoDR04->at(igen)>5) continue;

            //////////////// FLAGS FOR DENOMERATOR and NUMERATOR ////////////
            bool denFlag = 1;
            bool numFlag = 1;
 
            //cout << "passed gen continues " << endl;
            if (cut_map.find("dirPhoCut") != cut_map.end()) {
                bool isPass = (abs(pho.mcMomPID->at(igen)) == 22 || pho.mcMomPID->at(igen) == -999);
                //cout << "momID = " << pho.mcMomPID->at(igen) <<", dirPhoCut isPass = " << isPass << endl; 
                if( (cut_map.at("dirPhoCut") ==1) && (!isPass) ) continue; 
                else if((cut_map.at("dirPhoCut") ==2) && (!isPass) ) numFlag=0; 
            }

            if (cut_map.find("fragPhoCut") != cut_map.end()) {
                bool isPass = (abs(pho.mcMomPID->at(igen)) < 22);
                //cout << "momID = " << pho.mcMomPID->at(igen) <<", fragPhoCut isPass = " << isPass << endl; 
                if( (cut_map.at("fragPhoCut") ==1) && (!isPass) ) continue; 
                else if((cut_map.at("fragPhoCut") ==2) && (!isPass) ) numFlag=0; 
            }

            if (cut_map.find("fragDirPhoCut") != cut_map.end()) {
                bool isPass = (abs(pho.mcMomPID->at(igen)) <= 22 || pho.mcMomPID->at(igen) == -999);
                //cout << "momID = " << pho.mcMomPID->at(igen) <<", fragDirPhoCut isPass = " << isPass << endl; 
                if( (cut_map.at("fragDirPhoCut") ==1) && (!isPass) ) continue; 
                else if((cut_map.at("fragDirPhoCut") ==2) && (!isPass) ) numFlag=0; 
            }

            if (cut_map.find("decayPhoCut") != cut_map.end()) {
                bool isPass = ( (abs(pho.mcMomPID->at(igen)) > 22) && (pho.mcMomPID->at(igen) !=-999) );
                //cout << "momID = " << pho.mcMomPID->at(igen) <<", decayPhoCut isPass = " << isPass << endl; 
                if( (cut_map.at("decayPhoCut") ==1) && (!isPass) ) continue; 
                else if((cut_map.at("decayPhoCut") ==2) && (!isPass) ) numFlag=0; 
            }

            ///// MATCHING PART /////
            Float_t currentDiffPt(1000);
            Float_t currentRecoPt(-1);
            int matchedIndex = -1;
            for(int ipho = 0; ipho < pho.nPho; ++ipho){
                //cout << "pho.phoEt = " << pho.phoEt->at(ipho) << endl;
                float tempDR = getDR(pho.phoEta->at(ipho), pho.phoPhi->at(ipho), pho.mcEta->at(igen), pho.mcPhi->at(igen));
                float tempDiffPt = abs( pho.mcPt->at(igen) - pho.phoEt->at(ipho) );
                if( (tempDR < delta) && (tempDiffPt < currentDiffPt) ) {
                    currentDiffPt = tempDiffPt;
                    currentRecoPt = pho.phoEt->at(ipho);
                    matchedIndex = ipho;
                }
            }
            bool isBarrel = abs(pho.mcEta->at(igen)) < 1.4442; 
             
            ///////////////// RECONSTRUCTION EFFICIENCY ///////////////
            h2D_Den_recons->Fill( abs(pho.mcEta->at(igen)), pho.mcEt->at(igen) );
            if(isBarrel) h1D_Den_recons->Fill( pho.mcEt->at(igen) );
            if(matchedIndex==-1) continue;
            h2D_Num_recons->Fill( abs(pho.mcEta->at(igen)), pho.mcEt->at(igen) );
            if(isBarrel) h1D_Num_recons->Fill( pho.mcEt->at(igen) );
            ///////////////////////////////////////////////////////////            
#if 1 
            totalDenEntries++; 
            if(TMath::Abs(pho.phoEta->at(matchedIndex))>3) continue; 
            if(pho.phoEt->at(matchedIndex)<25) continue; 

            ///////////////// START CONDITONS //////////////    
            if (cut_map.find("spikeCut") != cut_map.end()) {
                bool isFail = ( (pho.phoEta->at(matchedIndex)<1.44) &&
                        (pho.phoSigmaIEtaIEta->at(matchedIndex) < 0.002 ||
                         pho.pho_swissCrx->at(matchedIndex)     > 0.9   ||
                         TMath::Abs(pho.pho_seedTime->at(matchedIndex)) > 3) );
                //cout << "is spike(fail) ? = " << isFail << endl; 
                if( (cut_map.at("spikeCut") ==1) && (isFail) ) continue; 
                else if((cut_map.at("spikeCut") ==2) && (isFail) ) numFlag=0; 
            }
   
            if (cut_map.find("hotspotCut") != cut_map.end()) {
                bool isFail = 
                   ( (pho.phoE3x3->at(matchedIndex)/pho.phoE5x5->at(matchedIndex) > 2./3.-0.03 && pho.phoE3x3->at(matchedIndex)/pho.phoE5x5->at(matchedIndex) < 2./3.+0.03) &&
                    (pho.phoE1x5->at(matchedIndex)/pho.phoE5x5->at(matchedIndex) > 1./3.-0.03 && pho.phoE1x5->at(matchedIndex)/pho.phoE5x5->at(matchedIndex) < 1./3.+0.03) &&
                    (pho.phoE2x5->at(matchedIndex)/pho.phoE5x5->at(matchedIndex) > 2./3.-0.03 && pho.phoE2x5->at(matchedIndex)/pho.phoE5x5->at(matchedIndex) < 2./3.+0.03) ); 
                if( (cut_map.at("hotspotCut") ==1) && (isFail) ) continue; 
                else if((cut_map.at("hotspotCut") ==2) && (isFail) ) numFlag=0; 
            }

            if (cut_map.find("hoeCut") != cut_map.end()) {
                if(coll=="pbpb"){
                    bool isPass = (pho.phoHoverE->at(matchedIndex)<0.1);
                    if( (cut_map.at("hoeCut") ==1) && (!isPass) ) continue; 
                    else if((cut_map.at("hoeCut") ==2) && (!isPass) ) numFlag=0; 
                } else if(coll=="pp"){
                    bool isPass = (pho.phoHoverE->at(matchedIndex)<0.05);
                    if( (cut_map.at("hoeCut") ==1) && (!isPass) ) continue; 
                    else if((cut_map.at("hoeCut") ==2) && (!isPass) ) numFlag=0; 
                }
            }

            if (cut_map.find("sigEtaEtaCut") != cut_map.end()) {
                if(coll=="pbpb"){
                    bool isPass = (pho.phoSigmaIEtaIEta_2012->at(matchedIndex)<0.0101);
                    if( (cut_map.at("sigEtaEtaCut") ==1) && (!isPass) ) continue; 
                    else if((cut_map.at("sigEtaEtaCut") ==2) && (!isPass) ) numFlag=0; 
                } else if(coll=="pp"){
                    float cut_sig_EB=0.0;
                    float cut_sig_EE=0.0;
                    if(ppIsoIndex==0) {cut_sig_EB=0.0102; cut_sig_EE=0.0274;} 
                    else if(ppIsoIndex==1 || ppIsoIndex==3) {cut_sig_EB=0.0102; cut_sig_EE=0.0268;} 
                    else if(ppIsoIndex==2) {cut_sig_EB=0.0100; cut_sig_EE=0.0268;} 
                    bool isPass =( 
                        (abs(pho.phoEta->at(matchedIndex))<=1.44 && pho.phoSigmaIEtaIEta->at(matchedIndex)<cut_sig_EB) ||
                        (abs(pho.phoEta->at(matchedIndex))>1.44 && pho.phoSigmaIEtaIEta->at(matchedIndex)<cut_sig_EE)
                    );
                    if( (cut_map.at("sigEtaEtaCut") ==1) && (!isPass) ) continue; 
                    else if((cut_map.at("sigEtaEtaCut") ==2) && (!isPass) ) numFlag=0; 
                }
            }

            if (cut_map.find("sumIsoCut") != cut_map.end()) {
                if(coll=="pbpb"){
                    float sumIso = pho.pho_ecalClusterIsoR4->at(matchedIndex) + pho.pho_hcalRechitIsoR4->at(matchedIndex) + pho.pho_trackIsoR4PtCut20->at(matchedIndex);
                    bool isPass = (sumIso<(16.7202-0.154349*hiBin+0.00040613*hiBin*hiBin));
                    //bool isPass = (sumIso<1.0);// in v2, sumIso cut is 1.0, in v3, 5.0
                    if( (cut_map.at("sumIsoCut") ==1) && (!isPass) ) continue; 
                    else if((cut_map.at("sumIsoCut") ==2) && (!isPass) ) numFlag=0; 
                } else if(coll=="pp"){
                    float cut_phoHOverE_EB=0;// Barrel
                    float cut_phoSigmaIEtaIEta_EB=0;
                    float cut_pfcIso4_EB=0;
                    float cut_pfnIso4_c0_EB=0;
                    float cut_pfnIso4_c1_EB=0;
                    float cut_pfnIso4_c2_EB=0;
                    float cut_pfpIso4_c0_EB=0;
                    float cut_pfpIso4_c1_EB=0;
                    float cut_phoHOverE_EE=0;//Endcap
                    float cut_phoSigmaIEtaIEta_EE=0;
                    float cut_pfcIso4_EE=0;
                    float cut_pfnIso4_c0_EE=0;
                    float cut_pfnIso4_c1_EE=0;
                    float cut_pfnIso4_c2_EE=0;
                    float cut_pfpIso4_c0_EE=0;
                    float cut_pfpIso4_c1_EE=0;

                    if(ppIsoIndex==0){
                        // default photon isolation for PP is "Loose".
                        cut_phoHOverE_EB = 0.05;            // Barrel
                        cut_phoSigmaIEtaIEta_EB = 0.0102;
                        cut_pfcIso4_EB = 3.32;
                        cut_pfnIso4_c0_EB = 1.92;
                        cut_pfnIso4_c1_EB = 0.014;
                        cut_pfnIso4_c2_EB = 0.000019;
                        cut_pfpIso4_c0_EB = 0.81;
                        cut_pfpIso4_c1_EB = 0.0053;
                        cut_phoHOverE_EE = 0.05;            // Endcap
                        cut_phoSigmaIEtaIEta_EE = 0.0274;
                        cut_pfcIso4_EE = 1.97;
                        cut_pfnIso4_c0_EE = 11.86;
                        cut_pfnIso4_c1_EE = 0.0139;
                        cut_pfnIso4_c2_EE = 0.000025;
                        cut_pfpIso4_c0_EE = 0.83;
                        cut_pfpIso4_c1_EE = 0.0034;
                    } else if(ppIsoIndex==1) {
                        // photon isolation for PP is "Medium".
                        cut_phoHOverE_EB = 0.05;            // Barrel
                        cut_phoSigmaIEtaIEta_EB = 0.0102;
                        cut_pfcIso4_EB = 1.37;
                        cut_pfnIso4_c0_EB = 1.06;
                        cut_pfnIso4_c1_EB = 0.014;
                        cut_pfnIso4_c2_EB = 0.000019;
                        cut_pfpIso4_c0_EB = 0.28;
                        cut_pfpIso4_c1_EB = 0.0053;
                        cut_phoHOverE_EE = 0.05;            // Endcap
                        cut_phoSigmaIEtaIEta_EE = 0.0268;
                        cut_pfcIso4_EE = 1.10;
                        cut_pfnIso4_c0_EE = 2.69;
                        cut_pfnIso4_c1_EE = 0.0139;
                        cut_pfnIso4_c2_EE = 0.000025;
                        cut_pfpIso4_c0_EE = 0.39;
                        cut_pfpIso4_c1_EE = 0.0034;
                    } else if(ppIsoIndex==2){
                        // photon isolation for PP is "Tight".
                        cut_phoHOverE_EB = 0.05;            // Barrel
                        cut_phoSigmaIEtaIEta_EB = 0.0100;
                        cut_pfcIso4_EB = 0.76;
                        cut_pfnIso4_c0_EB = 0.97;
                        cut_pfnIso4_c1_EB = 0.014;
                        cut_pfnIso4_c2_EB = 0.000019;
                        cut_pfpIso4_c0_EB = 0.08;
                        cut_pfpIso4_c1_EB = 0.0053;
                        cut_phoHOverE_EE = 0.05;            // Endcap
                        cut_phoSigmaIEtaIEta_EE = 0.0268;
                        cut_pfcIso4_EE = 0.56;
                        cut_pfnIso4_c0_EE = 2.09;
                        cut_pfnIso4_c1_EE = 0.0139;
                        cut_pfnIso4_c2_EE = 0.000025;
                        cut_pfpIso4_c0_EE = 0.16;
                        cut_pfpIso4_c1_EE = 0.0034;
                    }

                    bool barrelIso = ((pho.pfcIso4->at(matchedIndex)<=cut_pfcIso4_EB) && (pho.pfnIso4->at(matchedIndex)<=cut_pfnIso4_c0_EB+0.014*pho.phoEt->at(matchedIndex)+0.000019*pho.phoEt->at(matchedIndex)*pho.phoEt->at(matchedIndex)) && pho.pfpIso4->at(matchedIndex)<=(cut_pfpIso4_c0_EB+0.0053*pho.phoEt->at(matchedIndex)));                    
                    bool endcapIso = ((pho.pfcIso4->at(matchedIndex)<=cut_pfcIso4_EE) && (pho.pfnIso4->at(matchedIndex)<=cut_pfnIso4_c0_EE+0.0139*pho.phoEt->at(matchedIndex)+0.000025*pho.phoEt->at(matchedIndex)*pho.phoEt->at(matchedIndex)) && pho.pfpIso4->at(matchedIndex)<=(cut_pfpIso4_c0_EE+0.0034*pho.phoEt->at(matchedIndex)));  
                    bool isPass = ( ( (abs(pho.phoEta->at(matchedIndex))<=1.44) && barrelIso ) || 
                            ( (abs(pho.phoEta->at(matchedIndex))>1.44) && endcapIso ) );
                    if(ppIsoIndex==3) {
                        float sumIso = pho.pho_ecalClusterIsoR4->at(matchedIndex) + pho.pho_hcalRechitIsoR4->at(matchedIndex) + pho.pho_trackIsoR4PtCut20->at(matchedIndex);
                        isPass = (sumIso<1.0);// in v2, sumIso cut is 1.0, in v3, 5.0
                    }
                    if( (cut_map.at("sumIsoCut") ==1) && (!isPass) ) continue; 
                    else if((cut_map.at("sumIsoCut") ==2) && (!isPass) ) numFlag=0; 
                }//for pp in sumIso condition
            }//sumIso condition 
            ///////////////// END OF CONDITON //////////////    
            //cout << "denFlag = " << denFlag << ", numFlag = " << numFlag << endl;
            
            h2D_Den->Fill( abs(pho.mcEta->at(igen)), pho.mcEt->at(igen) );
            if(isBarrel) { h1D_Den->Fill( pho.mcEt->at(igen) ); totalDenEntries++; } 
            if(numFlag) {
                h2D_Num->Fill( abs(pho.mcEta->at(igen)), pho.mcEt->at(igen) );
                if(isBarrel) { h1D_Num->Fill( pho.mcEt->at(igen) ); totalNumEntries++; } 
            }
#endif
        }//gen loop
    }//event loop

    
    //////////////////////////////////////////////////
    ///////////////// GET EFFICIENCY /////////////////    

    int numEntries = h2D_Num->Integral(0,h2D_Num->GetNbinsX(),0,1);
    int denEntries = h2D_Den->Integral(0,h2D_Num->GetNbinsX(),0,1);
    std::cout << "Numerator Entries = " << numEntries << std::endl; 
    std::cout << "Denominator Entries = " << denEntries << std::endl; 
    std::cout << "Efficiency  = " << (float)numEntries/(float)denEntries << std::endl; 
    
    std::cout << "=========Numbers from the loop==========" << std::endl; 
    std::cout << "Numerator Entries = " << totalNumEntries<< std::endl; 
    std::cout << "Denominator Entries = " <<totalDenEntries << std::endl; 
    std::cout << "Efficiency  = " << (float)totalNumEntries/(float)totalDenEntries<< std::endl; 
    h2D_Eff->Divide(h2D_Num,h2D_Den,1.,1.,"B");
    h2D_Eff_recons->Divide(h2D_Num_recons,h2D_Den_recons,1.,1.,"B");

    TH1D* h1D_pt_recons= (TH1D*) h2D_Eff_recons->ProjectionY("h1D_Eff_pt_recons",0,1);
    TH1D* h1D_pt = (TH1D*) h2D_Eff->ProjectionY("h1D_Eff_pt",0,1);
 
    TH1D* h1D_pt_recons_pretty = changeToPrettyBin(h1D_pt_recons);
    TH1D* h1D_pt_pretty = changeToPrettyBin(h1D_pt);
    h1D_pt_recons_pretty->SetTitle(";p_{T} (GeV);Reconstruction Efficiency");
    h1D_pt_recons_pretty->SetMarkerStyle(20);
    h1D_pt_recons_pretty->SetAxisRange(0.50,1.0001,"Y");
    h1D_pt_pretty->SetTitle(";p_{T} (GeV);RecoCut Efficiency");
    h1D_pt_pretty->SetMarkerStyle(20);
    h1D_pt_pretty->SetAxisRange(0.50,1.0001,"Y");

    TH1D* h1D_pt_total;
    TH1D* h1D_pt_total_pretty;
    if(den_st=="") { 
        h2D_Eff_total->Divide(h2D_Num,h2D_Den_recons,1.,1.,"B");
        h1D_pt_total = (TH1D*) h2D_Eff_total->ProjectionY("h1D_Eff_pt_total",0,1);
        h1D_pt_total_pretty = changeToPrettyBin(h1D_pt_total);

        h1D_pt_total_pretty->SetTitle(";p_{T} (GeV);Total Efficiency");
        h1D_pt_total_pretty->SetMarkerStyle(20);
        h1D_pt_total_pretty->SetAxisRange(0.50,1.0001,"Y");
    } 
    
    //////////////////////////////////////////////////
    // BayesDivide with TGraphAsymmErrors
    TGraphAsymmErrors* a_Eff = new TGraphAsymmErrors();
    a_Eff->SetName(Form("a_Eff"));
    a_Eff->SetTitle(h1D_Num->GetTitle());
    a_Eff->GetYaxis()->SetTitle("Isolation Efficiency");
    a_Eff->BayesDivide(h1D_Num, h1D_Den);
    a_Eff->SetMarkerStyle(kFullCircle);
    a_Eff->Draw("p e");

    TGraphAsymmErrors* a_Eff_recons = new TGraphAsymmErrors();
    a_Eff_recons->SetName(Form("a_Eff_recons"));
    a_Eff_recons->SetTitle(h1D_Num->GetTitle());
    a_Eff_recons->GetYaxis()->SetTitle("Reconstruction Efficiency");
    a_Eff_recons->BayesDivide(h1D_Num, h1D_Den);
    a_Eff_recons->SetMarkerStyle(kFullCircle);
    a_Eff_recons->Draw("p e");


    const char* cap="";
    if(coll=="pbpb") cap = Form("%s_cent%d_%d",coll.Data(),(int)cent_i/2,(int)cent_f/2);
    else if(coll=="pp" && ppIsoIndex==0) cap = Form("pp_LooseCut");
    else if(coll=="pp" && ppIsoIndex==1) cap = Form("pp_MediumCut");
    else if(coll=="pp" && ppIsoIndex==2) cap = Form("pp_TightCut");
    else if(coll=="pp" && ppIsoIndex==3) cap = Form("pp_PbPbStyleIso");
    saveHistogramsToPicture(h1D_pt_recons_pretty, "pdf",Form("efficiency_Den_%s_Num_%s_%s",den_st.data(),num_st.data(),cap),cap);
    saveHistogramsToPicture(h1D_pt_pretty, "pdf",Form("efficiency_Den_%s_Num_%s_%s",den_st.data(),num_st.data(),cap),cap);
    saveHistogramsToPicture(h2D_Eff, "pdf",Form("efficiency_pt_eta_Den_%s_Num_%s_%s",den_st.data(),num_st.data(),cap),cap,"figures",0);
    saveHistogramsToPicture(h2D_Eff_recons, "pdf",Form("reconstruction_efficiency_pt_eta_Den_%s_Num_%s_%s",den_st.data(),num_st.data(),cap),cap,"figures",0);

    if(den_st=="") saveHistogramsToPicture(h2D_Eff_total, "pdf",Form("total_efficiency_pt_eta_Den_%s_Num_%s_%s",den_st.data(),num_st.data(),cap),cap,"figures",0);
    if(den_st=="") saveHistogramsToPicture(h1D_pt_total_pretty, "pdf",Form("efficiency_Den_%s_Num_%s_%s",den_st.data(),num_st.data(),cap),cap);

    TString outputFile = Form("hist_efficiency_%s_%s_Den_%s_Num_%s.root",cap,ver,den_st.data(),num_st.data());
    cout << "output ROOT file : " << outputFile << endl;

    TFile* outf = new TFile(Form("output/%s",outputFile.Data()), "RECREATE");
    outf->cd();
    h2D_Num->Write();
    h2D_Den->Write();
    h2D_Eff->Write();
    h2D_Num_recons->Write();
    h2D_Den_recons->Write();
    h2D_Eff_recons->Write();
    h1D_pt_recons->Write();
    h1D_pt->Write();
    h1D_Num->Write();
    h1D_Den->Write();
    a_Eff->Write();
    a_Eff_recons->Write();
    if(den_st==""){
        h2D_Eff_total->Write();
        h1D_pt_total->Write();
    }
    outf->Close();
}

