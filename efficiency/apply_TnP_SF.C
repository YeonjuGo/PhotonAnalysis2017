// Created : 2017 April 18
// Modified : 2017 May18
// Author : Yeonju Go
// 

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
bool isConstBin = false;
const int colHere[]={2,4,8,kYellow+2,kCyan+1};
const int markerStyle[]={20,33,22,23,34,29};
void apply_TnP_SF(TString coll="pbpb", TString ver="180619_temp_v17_nominal", bool doWeight=true, bool doBkg=false, bool doSeparation=true){
    
    cout << " :::::: iso_efficiency_withSkimFile.C :::::: " << endl;
    if(doSeparation) cout << " :::::: Isolation Separation will be processed :::::: " << endl;
    else cout << " :::::: Only total efficiency will be calculated :::::: " << endl;
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);
    SetyjPadStyle();

    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/";
    const char* fin;
    if(coll=="pp"){
        fin= Form("%soutput/pp_iso_efficiency_%s_nominal.root",dir.Data(),ver.Data());
    } else if(coll=="pbpb"){
        fin= Form("%soutput/pbpb_iso_efficiency_%s_nominal.root",dir.Data(),ver.Data());
    }
    TFile* f1 = new TFile(fin,"read");

    const char* fname;
    if(coll=="pp"){
        fname = Form("%soutput/pp_iso_efficiency_%s_sys_eff.root",dir.Data(),ver.Data());
    } else if(coll=="pbpb"){
        fname = Form("%soutput/pbpb_iso_efficiency_%s_sys_eff.root",dir.Data(),ver.Data());
    }
    TFile* fout  = new TFile(fname,"recreate");

    ///////////////////////////////////////////////////////////
    
    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1;
    Int_t nConstPtBin = 50;
    
    Int_t nEff = 5;//1(tot):noiseCut && hoeCut && sigmaCut && isoCut && eleRej, 1(iso):noiseCut && hoeCut && sigmaCut && isoCut, 2(sigma):noiseCut && hoeCut && sigmaCut, 3(hoe):noiseCut && hoeCut, 4(noise):noise//
    Int_t nEffloop = nEff;
    if(doSeparation==0) nEffloop = 1;
    TString effSt[] = {"tot","iso","sigma","hoe","noise"};
    TString effSt_legend[] = {"total(noise & H/E & #sigma_{i#etai#eta} & sumIso & eleRej)","noise & H/E & #sigma_{i#etai#eta} & sumIso","noise & H/E & #sigma_{i#etai#eta}","noise & H/E","noise"};

    TH1D* h1D_eff[nCENTBINS];
    TH1D* h1D_eff_original[nCENTBINS];
    for(Int_t icent=0;icent<nCENTBINS;++icent){
        h1D_eff[icent] = (TH1D*) f1->Get(Form("sig_eff_cent%d_tot",icent));
        h1D_eff_original[icent] = (TH1D*) h1D_eff[icent]->Clone(Form("sig_eff_cent%d_tot_original",icent));
    }


    if(coll=="pp"){
        h1D_eff[0]->Scale(1.05);
    } else{
        for(Int_t icent=0;icent<nCENTBINS;++icent){
            if(icent==0 || icent==1){
                h1D_eff[icent]->Scale(0.764887);
            } else{
                h1D_eff[icent]->Scale(0.965852);
            } 
        }
    }
    
    for(Int_t icent=0;icent<nCENTBINS;++icent){
        h1D_eff[icent]->Write();
        h1D_eff_original[icent]->Write();
    }
}
