// Created : 2017 April 18
// Modified : 2019 June 26
// Author : Yeonju Go
// (deprecated) iso_efficiency_withSkimFile_v2 : unfolding binning (15 GeV to 300 GeV)
// (deprecated) trigger efficiency will be calculated by MC here in this code
// 2019June25) different unfolding binning depending on centrality bin 
// 2019June25) apply trigger efficiency which is derived using DATA to here but not draw in canvas
// 2019June25) unfolding binning (20 GeV to 300 GeV) 

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"

bool isConsBin = false;
const int colHere[]={kBlack,kPink-5,kGreen+3,kBlue-3,kOrange+4,kBlack};
//const int colHere[]={2,4,8,kYellow+2,kCyan+1,kOrange+7,kViolet-7};
const int markerStyle[]={24,33,26,34,29,22,24,33};
void iso_efficiency_withSkimFile_v3(TString coll="pbpb", TString ver="190703_temp_v31_nominal", bool doWeight=true, bool doBkg=false, bool doSeparation=true){
    
    cout << " :::::: iso_efficiency_withSkimFile.C :::::: " << endl;
    if(doSeparation) cout << " :::::: Isolation Separation will be processed :::::: " << endl;
    else cout << " :::::: Only total efficiency will be calculated :::::: " << endl;
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);
    SetyjPadStyle();
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/";

    //import skimed tree
    const char* fname[2];
    if(coll=="pp"){ 
        fname[0]=Form("%s",ppMCfname.Data());
        fname[1]=Form("%s",ppMCEmEnrfname.Data());
    } else if(coll=="pbpb"){
        fname[0]=Form("%s",pbpbMCfname.Data());
        fname[1]=Form("%s",pbpbMCEmEnrfname.Data());
    }
    TChain* t1 = new TChain("EventTree");
    TChain* t1_skim = new TChain("skim");
    TChain* t1_evt = new TChain("HiEvt");
    TChain* t1_hlt = new TChain("hltTree");
    for(Int_t j=0;j<2;++j){
        t1->Add(fname[j]);
        t1_skim->Add(fname[j]);
        t1_evt->Add(fname[j]);
        t1_hlt->Add(fname[j]);
    }
    t1->AddFriend(t1_skim);
    t1->AddFriend(t1_evt);
    t1->AddFriend(t1_hlt);


    //////////////////////////////////////////
    // Import trigger efficiency plots
    //TFile* file_eff[2];
    //TF1* f_eff[2];
    //file_eff[0] = Open::TFile(Form("%s/triggerEfficiency/trigger_efficiency_fit_SinglePhoton20_%s.root",dir.Data(),coll.Data()));
    //f_eff[0] = (TF1*) file_eff[0]->Get(Form("efficiency_func_HLT_HISinglePhoton20_%s",coll.Data()));
    //file_eff[1] = Open::TFile(Form("%s/triggerEfficiency/trigger_efficiency_fit_SinglePhoton40_%s.root",dir.Data(),coll.Data()));
    //f_eff[1] = (TF1*) file_eff[0]->Get(Form("efficiency_func_HLT_HISinglePhoton40_%s",coll.Data()));

    //define constants and histograms
    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1;
    Int_t nEff = 6;//0(tot,trigEff):noiseCut && hoeCut && sigmaCut && isoCut && eleRej && trigEff, 0(electron rejection):noiseCut && hoeCut && sigmaCut && isoCut && eleRej, 1(iso):noiseCut && hoeCut && sigmaCut && isoCut, 2(sigma):noiseCut && hoeCut && sigmaCut, 3(hoe):noiseCut && hoeCut, 4(noise):noise//
    Int_t nEffloop = nEff;
    if(doSeparation==0) nEffloop = 1;
    TString effSt[] = {"tot","eleRej","iso","sigma","hoe","noise"};
    TString effSt_legend[] = {"total(noise & H/E & #sigma_{i#etai#eta} & sumIso & eleRej & trig)","noise & H/E & #sigma_{i#etai#eta} & sumIso & eleRej","noise & H/E & #sigma_{i#etai#eta} & sumIso","noise & H/E & #sigma_{i#etai#eta}","noise & H/E","noise"};
    //TString effSt[] = {"tot","trig","iso","sigma","hoe","noise"};
    //TString effSt_legend[] = {"total(noise & H/E & #sigma_{i#etai#eta} & sumIso & eleRej & trig)","noise & H/E & #sigma_{i#etai#eta} & sumIso & eleRej","noise & H/E & #sigma_{i#etai#eta} & sumIso","noise & H/E & #sigma_{i#etai#eta}","noise & H/E","noise"};
    TH1D* bkg_den[nCENTBINS];
    TH1D* bkg_num[nCENTBINS][nEff];
    TH1D* bkg_eff[nCENTBINS][nEff];
    TH1D* sig_den[nCENTBINS];
    TH1D* sig_num[nCENTBINS][nEff];
    TH1D* sig_eff[nCENTBINS][nEff];
    TH1D* h_temp_trig[nCENTBINS][2]; //[Centrality][0:20-40GeV, 1: over 40GeV]

    const int nConstPtBin = 100;
    const int xMax = 140;
    const int xMin = 40;
    for(Int_t i=0;i<nCENTBINS;++i){
        // rebin ptbins for each centrality bins since we have less bins for peripheral region
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[i];
        double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
            ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
        } 

        if(isConsBin) {
            if(doBkg) bkg_den[i] = new TH1D(Form("bkg_den_cent%d",i),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nConstPtBin, xMin, xMax);
            sig_den[i] = new TH1D(Form("sig_den_cent%d",i),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nConstPtBin, xMin, xMax);
            h_temp_trig[i][0] = new TH1D(Form("sig_num_cent%d_trig20_pt20to40",i),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nConstPtBin, xMin, xMax);
            h_temp_trig[i][1] = new TH1D(Form("sig_num_cent%d_trig40_pt40to300",i),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nConstPtBin, xMin, xMax);
            
        } else{
            if(doBkg) bkg_den[i] = new TH1D(Form("bkg_den_cent%d",i),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
            sig_den[i] = new TH1D(Form("sig_den_cent%d",i),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
            h_temp_trig[i][0] = new TH1D(Form("sig_num_cent%d_trig20_pt20to40",i),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
            h_temp_trig[i][1] = new TH1D(Form("sig_num_cent%d_trig40_pt40to300",i),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
        } 

        for(Int_t j=0;j<nEffloop;++j){
            if(isConsBin) {
                if(doBkg) bkg_num[i][j] = new TH1D(Form("bkg_num_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nConstPtBin, xMin, xMax);
                if(doBkg) bkg_eff[i][j] = new TH1D(Form("bkg_eff_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);Efficiency",nConstPtBin, xMin, xMax);
                sig_num[i][j] = new TH1D(Form("sig_num_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nConstPtBin, xMin, xMax);
                sig_eff[i][j] = new TH1D(Form("sig_eff_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);Efficiency",nConstPtBin, xMin, xMax);
            } else{ 
                if(doBkg) bkg_num[i][j] = new TH1D(Form("bkg_num_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
                if(doBkg) bkg_eff[i][j] = new TH1D(Form("bkg_eff_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);Efficiency",nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
                sig_num[i][j] = new TH1D(Form("sig_num_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
                sig_eff[i][j] = new TH1D(Form("sig_eff_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);Efficiency",nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
            }
        }}

    // define cut seperately, step-by-step 
    TCut centCut[nCENTBINS];
    TCut commonCut[nCENTBINS];
    TCut numCut[nEff];
    numCut[0] = noiseCut && hoeCut && sigmaCut && isoCut && electronCut;
    numCut[1] = noiseCut && hoeCut && sigmaCut && isoCut && electronCut;
    numCut[2] = noiseCut && hoeCut && sigmaCut && isoCut;
    numCut[3] = noiseCut && hoeCut && sigmaCut;
    numCut[4] = noiseCut && hoeCut;
    numCut[5] = noiseCut;
    for(Int_t i=0;i<nCENTBINS;++i){
        centCut[i] = Form("(hiBin>=%d)&&(hiBin<%d)",centBins_i[i],centBins_f[i]);
        commonCut[i] =etaCut && centCut[i];
    } 
    if(coll=="pp") {
        commonCut[0] = etaCut; 
        numCut[0] = noiseCut && hoeCut_pp && sigmaCut_pp && isoCut_pp && electronCut; 
        numCut[1] = noiseCut && hoeCut_pp && sigmaCut_pp && isoCut_pp && electronCut; 
        numCut[2] = noiseCut && hoeCut_pp && sigmaCut_pp && isoCut_pp; 
        numCut[3] = noiseCut && hoeCut_pp && sigmaCut_pp; 
        numCut[4] = noiseCut && hoeCut_pp; 
        numCut[5] = noiseCut; 
    }

    //Fill histograms
    for(Int_t i=0;i<nCENTBINS;++i){
        //DENOMINATOR
        if(doWeight)    t1->Draw(Form("%s>>%s",phoEtVar.Data(),sig_den[i]->GetName()), Form("(%s)*((%s) && (%s))","weight",mcIsolation.GetTitle(),commonCut[i].GetTitle()));
        else            t1->Draw(Form("%s>>%s",phoEtVar.Data(),sig_den[i]->GetName()), mcIsolation && commonCut[i]);
        sig_den[i]=(TH1D*)gDirectory->Get(sig_den[i]->GetName());
        if(doBkg){ 
            if(doWeight)    t1->Draw(Form("%s>>%s",phoEtVar.Data(),bkg_den[i]->GetName()), Form("(%s)*((%s) && (%s))","weight",mcBkgIsolation.GetTitle(),commonCut[i].GetTitle()));
            else            t1->Draw(Form("%s>>%s",phoEtVar.Data(),bkg_den[i]->GetName()),mcBkgIsolation && commonCut[i]);
            bkg_den[i]=(TH1D*)gDirectory->Get(bkg_den[i]->GetName());
        }

        //NUMERATOR except trigger efficiency 
        for(Int_t j=1;j<nEffloop;++j){
            if(doWeight)    t1->Draw(Form("%s>>%s",phoEtVar.Data(),sig_num[i][j]->GetName()),Form("(%s)*((%s) && (%s) && (%s))","weight",mcIsolation.GetTitle(), commonCut[i].GetTitle(), numCut[j].GetTitle())); 
            else            t1->Draw(Form("%s>>%s",phoEtVar.Data(),sig_num[i][j]->GetName()), mcIsolation && commonCut[i] && numCut[j]); 
            sig_num[i][j]=(TH1D*)gDirectory->Get(sig_num[i][j]->GetName());
            if(doBkg){
                if(doWeight)    t1->Draw(Form("%s>>%s",phoEtVar.Data(),sig_num[i][j]->GetName()),Form("(%s)*((%s) && (%s) && (%s))","weight",mcBkgIsolation.GetTitle(), commonCut[i].GetTitle(), numCut[j].GetTitle())); 
                else            t1->Draw(Form("%s>>%s",phoEtVar.Data(),bkg_num[i][j]->GetName()),mcBkgIsolation && commonCut[i] && numCut[j]); 
                bkg_num[i][j]=(TH1D*)gDirectory->Get(bkg_num[i][j]->GetName());
            }
        }
        //NUMERATOR for trigger efficiency 
        int j = 0;

        //HLT20 trigger with all other signal cuts for total efficiency for 20-40 GeV
        TCut trig20_ptCut = Form("(%s>=20 && %s<40)",phoEtVar.Data(),phoEtVar.Data());
        if(coll=="pp"){//pp
            if(doWeight)    t1->Draw(Form("%s>>%s",phoEtVar.Data(),h_temp_trig[i][0]->GetName()),Form("(%s * (0.5*(1+TMath::Erf((%s-2.00457e+01)/(%s*8.10508e-02)))))*((%s) && (%s) && (%s) && (%s))","weight",phoEtVar.Data(),phoEtVar.Data(),mcIsolation.GetTitle(), commonCut[i].GetTitle(), numCut[j].GetTitle(), trig20_ptCut.GetTitle())); 
            else            t1->Draw(Form("%s>>%s",phoEtVar.Data(),h_temp_trig[i][0]->GetName()),Form("(0.5*(1+TMath::Erf((%s-2.00457e+01)/(%s*8.10508e-02))))*((%s) && (%s) && (%s) && (%s))",phoEtVar.Data(),phoEtVar.Data(),mcIsolation.GetTitle(), commonCut[i].GetTitle(), numCut[j].GetTitle(), trig20_ptCut.GetTitle())); 
        } else{ //pbpb //No correction for PbPb HLT20! fully efficient
            if(doWeight)    t1->Draw(Form("%s>>%s",phoEtVar.Data(),h_temp_trig[i][0]->GetName()),Form("(%s)*((%s) && (%s) && (%s) && (%s))","weight",mcIsolation.GetTitle(), commonCut[i].GetTitle(), numCut[j].GetTitle(), trig20_ptCut.GetTitle())); 
            else            t1->Draw(Form("%s>>%s",phoEtVar.Data(),h_temp_trig[i][0]->GetName()),Form("(%f)*((%s) && (%s) && (%s) && (%s))",1.0,mcIsolation.GetTitle(), commonCut[i].GetTitle(), numCut[j].GetTitle(), trig20_ptCut.GetTitle())); 
        }
        h_temp_trig[i][0]=(TH1D*)gDirectory->Get(h_temp_trig[i][0]->GetName());

        //HLT40 trigger with all other signal cuts for total efficiency for 40-300 GeV
        TCut trig40_ptCut = Form("(%s>=40)",phoEtVar.Data());
        if(coll=="pp"){//pp
            if(doWeight)    t1->Draw(Form("%s>>%s",phoEtVar.Data(),h_temp_trig[i][1]->GetName()),Form("(%s * (0.5*(1+TMath::Erf((%s-3.96603e+01)/(%s*5.73495e-02)))))*((%s) && (%s) && (%s) && (%s))","weight",phoEtVar.Data(),phoEtVar.Data(),mcIsolation.GetTitle(), commonCut[i].GetTitle(), numCut[j].GetTitle(), trig40_ptCut.GetTitle())); 
            else            t1->Draw(Form("%s>>%s",phoEtVar.Data(),h_temp_trig[i][1]->GetName()),Form("(0.5*(1+TMath::Erf((%s-3.96603e+01)/(%s*5.73495e-02))))*((%s) && (%s) && (%s) && (%s))",phoEtVar.Data(),phoEtVar.Data(),mcIsolation.GetTitle(), commonCut[i].GetTitle(), numCut[j].GetTitle(), trig40_ptCut.GetTitle())); 
        } else{ //pbpb //No correction for PbPb HLT20! fully efficient
            if(doWeight)    t1->Draw(Form("%s>>%s",phoEtVar.Data(),h_temp_trig[i][1]->GetName()),Form("(%s * (0.5*(1+TMath::Erf((%s-3.81566e+01)/(%s*4.64286e-02)))))*((%s) && (%s) && (%s) && (%s))","weight",phoEtVar.Data(),phoEtVar.Data(),mcIsolation.GetTitle(), commonCut[i].GetTitle(), numCut[j].GetTitle(), trig40_ptCut.GetTitle())); 
            else            t1->Draw(Form("%s>>%s",phoEtVar.Data(),h_temp_trig[i][1]->GetName()),Form("(0.5*(1+TMath::Erf((%s-3.81566e+01)/(%s*4.64286e-02))))*((%s) && (%s) && (%s) && (%s))",phoEtVar.Data(),phoEtVar.Data(),mcIsolation.GetTitle(), commonCut[i].GetTitle(), numCut[j].GetTitle(), trig40_ptCut.GetTitle())); 
        }
        h_temp_trig[i][1]=(TH1D*)gDirectory->Get(h_temp_trig[i][1]->GetName());
        //Total efficiency including trigger
        sig_num[i][j]->Add(h_temp_trig[i][0],h_temp_trig[i][1]);

        if(doBkg){
            if(doWeight)    t1->Draw(Form("%s>>%s",phoEtVar.Data(),sig_num[i][j]->GetName()),Form("(%s)*((%s) && (%s) && (%s))","weight",mcBkgIsolation.GetTitle(), commonCut[i].GetTitle(), numCut[j].GetTitle())); 
            else            t1->Draw(Form("%s>>%s",phoEtVar.Data(),bkg_num[i][j]->GetName()),mcBkgIsolation && commonCut[i] && numCut[j]); 
            bkg_num[i][j]=(TH1D*)gDirectory->Get(bkg_num[i][j]->GetName());
        }
    }
    // Efficiency Function : 0.5*(1+TMath::Erf((x-[0])/(x*[1])))
    //    Parameters for pp HLT20 : 
    // NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE
    //  1  p0           2.00457e+01   5.09031e-03   1.24198e-04   1.48211e-03
    //  2  p1           8.10508e-02   4.35111e-04   1.06163e-05   6.16771e-03
    //    Parameters for pp HLT40 : 
    // NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE
    //  1  p0           3.96603e+01   3.44755e-02   1.87199e-04   6.35772e-08
    //  2  p1           5.73495e-02   1.40888e-03   7.65009e-06  -5.69217e-04
    //    Parameters for PbPb HLT40 : 
    //  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE
    //   1  p0           3.81566e+01   1.46324e-02   1.48500e-04   1.19237e-05
    //   2  p1           4.64286e-02   5.93852e-04   6.02683e-06  -1.46557e-03
    // Example)) nt->Draw(Form("%f*%s>>h_temp1",s,var.data()),Form("(0.94038/(1+TMath::Exp(-0.10831*(%s-11.30114)))+3.06281/(%s-11.30114))*(    %s && %s<%f)",var.data(),var.data(),cut.GetTitle(),var.data(),rangeDiv));
    for(Int_t i=0;i<nCENTBINS;++i){
        for(Int_t j=0;j<nEffloop;++j){
            sig_eff[i][j]->Divide(sig_num[i][j],sig_den[i],1.,1.,"B");
            if(doBkg) bkg_eff[i][j]->Divide(bkg_num[i][j],bkg_den[i],1.,1.,"B");
        }
    }

    /////////////////////////////////////////////////////////////////////
    // DRAWING 
    cout << " DRAWING STARTS " << endl;
    TLegend* l1 = new TLegend(0.5,0.2,0.8,0.4);
    legStyle(l1);

    TH1D* bkg_eff_draw[nCENTBINS][nEff];
    TH1D* sig_eff_draw[nCENTBINS][nEff];
    for(Int_t i=0;i<nCENTBINS;++i){
        // rebin ptbins for each centrality bins since we have less bins for peripheral region
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[i];
        double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
            ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
        } 

        for(Int_t j=nEffloop-1;j>-1;--j){
            bkg_eff_draw[i][j] = new TH1D(Form("bkg_eff_draw_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);Efficiency",nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
            sig_eff_draw[i][j] = new TH1D(Form("sig_eff_draw_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);Efficiency",nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
            int temp_nPtBin_unfolding_centDep = -1;
            if(isConsBin) temp_nPtBin_unfolding_centDep = nConstPtBin;
            else temp_nPtBin_unfolding_centDep = nPtBin_unfolding_centDep;
            for(int k=0;k<temp_nPtBin_unfolding_centDep;++k){
                if(doBkg) {
                    bkg_eff_draw[i][j]->SetBinContent(k+1,bkg_eff[i][j]->GetBinContent(k+1));
                    bkg_eff_draw[i][j]->SetBinError(k+1,bkg_eff[i][j]->GetBinError(k+1));
                }
                sig_eff_draw[i][j]->SetBinContent(k+1,sig_eff[i][j]->GetBinContent(k+1));
                sig_eff_draw[i][j]->SetBinError(k+1,sig_eff[i][j]->GetBinError(k+1));
            }
        }}

    /////////////////////////////////////////////////////////////////////
    // DRAWING : Centrality Dependence (Total Efficiency) 
    TCanvas* c1 =new TCanvas(Form("c%d",2),"", 400,400);
    TH1D* htemp_draw[nCENTBINS];
    for(Int_t i=0;i<nCENTBINS;++i){
        SetHistTextSize(sig_eff_draw[i][1]);
       // if(i==0) {
       //     sig_eff_draw[i][0]->SetMarkerStyle(33);
       //     sig_eff_draw[i][0]->SetMarkerSize(1.4);
       // } else{
       //     sig_eff_draw[i][0]->SetMarkerStyle(20);
       // }
        sig_eff_draw[i][1]->SetMarkerColor(colHere[i]);
        sig_eff_draw[i][1]->SetMarkerStyle(markerStyle[i]);
        sig_eff_draw[i][1]->GetYaxis()->SetRangeUser(0,1);
        sig_eff_draw[i][1]->GetXaxis()->CenterTitle();
        sig_eff_draw[i][1]->GetYaxis()->CenterTitle();
        htemp_draw[i] = (TH1D*) sig_eff[i][1]->Clone(Form("htemp_draw%d",i));
        if(i==0) sig_eff_draw[i][1]->DrawCopy("p");
        else sig_eff_draw[i][1]->DrawCopy("same p");
        if(coll=="pbpb") l1->AddEntry(htemp_draw[i], Form("%d%s-%d%s",centBins_i[i]/2,"%",centBins_f[i]/2,"%"));
        //if(coll=="pbpb") l1->AddEntry(sig_eff_draw[i][1], Form("%d%s-%d%s",centBins_i[i]/2,"%",centBins_f[i]/2,"%"));
    } 
    if(coll=="pbpb") l1->Draw("same");
    drawText(Form("%s Total Isolation Efficiency",coll.Data()),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
    c1->SetLogx(); 
    c1->SaveAs(Form("%sfigures/efficiency_%s_totEff_centDep_%s.pdf",dir.Data(),coll.Data(),ver.Data()));

    /////////////////////////////////////////////////////////////////////
    // DRAWING : Centrality Dependence and Isolation Cut Dependence (each centrality bin separately)

    TLegend* l2 = new TLegend(0.25,0.2,0.9,0.4);
    legStyle(l2);
    TCanvas* c2[nCENTBINS];
    for(Int_t i=0;i<nCENTBINS;++i){
        c2[i] = new TCanvas(Form("c_effDep_cent%d",i),"", 400,400);
        c2[i]->SetLogx();

        for(Int_t j=1;j<nEffloop;++j){
            SetHistTextSize(sig_eff_draw[i][j]);
            sig_eff_draw[i][j]->SetLineColor(colHere[j]);
            sig_eff_draw[i][j]->SetMarkerColor(colHere[j]);
            sig_eff_draw[i][j]->SetMarkerStyle(markerStyle[j]);
            sig_eff_draw[i][j]->GetYaxis()->SetRangeUser(0,1);
            sig_eff_draw[i][j]->GetXaxis()->CenterTitle();
            sig_eff_draw[i][j]->GetYaxis()->CenterTitle();
            if(j==1) sig_eff_draw[i][j]->DrawCopy("p");
            else sig_eff_draw[i][j]->DrawCopy("same p");
        } 
        for(Int_t j=nEff-1;j>0;--j){
            if(i==0) l2->AddEntry(sig_eff_draw[i][j], Form("%s",effSt_legend[j].Data()));
        }
        l2->Draw("same");
        if(coll=="pbpb") drawText(Form("%s %d%s-%d%s",coll.Data(),centBins_i[i]/2,"%",centBins_f[i]/2,"%"),0.6,0.45);
        else drawText(Form("%s",coll.Data()),0.6,0.45);
        if(coll=="pbpb") c2[i]->SaveAs(Form("%sfigures/efficiency_%s_effDep_%s_cent%d%s-%d%s.pdf",dir.Data(),coll.Data(),ver.Data(),centBins_i[i]/2,"%",centBins_f[i]/2,"%"));
        else c2[i]->SaveAs(Form("%sfigures/efficiency_%s_effDep_%s.pdf",dir.Data(),coll.Data(),ver.Data()));
    }

    /////////////////////////////////////////////////////////////////////
    // DRAWING : Centrality Dependence (Total Efficiency including trigger efficiency) 
    TCanvas* c3 =new TCanvas(Form("c%d",3),"", 400,400);
    c3->SetLogx();
    for(Int_t i=0;i<nCENTBINS;++i){
        SetHistTextSize(sig_eff_draw[i][0]);
        sig_eff_draw[i][0]->SetMarkerColor(colHere[i]);
        sig_eff_draw[i][0]->SetMarkerStyle(markerStyle[i]);
        sig_eff_draw[i][0]->GetYaxis()->SetRangeUser(0,1);
        sig_eff_draw[i][0]->SetTitle(";p_{T}^{#gamma} (GeV);Total Efficiency");
        sig_eff_draw[i][0]->GetXaxis()->CenterTitle();
        sig_eff_draw[i][0]->GetYaxis()->CenterTitle();
        if(i==0) sig_eff_draw[i][0]->DrawCopy("p");
        else sig_eff_draw[i][0]->DrawCopy("same p");
    } 
    if(coll=="pbpb") l1->Draw("same");
    //drawText(Form("%s Total Isolation Efficiency",coll.Data()),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
    c3->SaveAs(Form("%sfigures/efficiency_withTrigEff_%s_tot_centDep_%s.pdf",dir.Data(),coll.Data(),ver.Data()));
    //*/

    /////////////////////////////////////////////////////////////////////
    // Write output file  
    TString outFname = Form("%soutput/%s_iso_efficiency_%s.root",dir.Data(),coll.Data(),ver.Data());
    cout << "Output File : " << outFname << endl;
    TFile* fout = new TFile(outFname,"RECREATE");
    fout->cd();
    c1->Write();
    c3->Write();
    for(Int_t i=0;i<nCENTBINS;++i){
        sig_den[i]->Write();
        h_temp_trig[i][0]->Write();
        h_temp_trig[i][1]->Write();
        if(doBkg) bkg_den[i]->Write();
        c2[i]->Write();
        for(Int_t j=0;j<nEffloop;++j){
            sig_num[i][j]->Write();
            sig_eff[i][j]->Write();
            if(doBkg){
                bkg_num[i][j]->Write();
                bkg_eff[i][j]->Write();
            }
        }
    }
}
