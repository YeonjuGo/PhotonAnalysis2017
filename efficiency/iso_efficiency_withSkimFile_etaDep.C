// Created : 2017 April 18
// Modified : 2017 May18
// Author : Yeonju Go
// 

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
bool isConsBin = true;//
const int colHere[]={2,4,8,kYellow+2,kCyan+1};
const int markerStyle[]={20,33,22,23,22,29};
void iso_efficiency_withSkimFile_etaDep(TString coll="pbpb", TString ver="v18", bool doWeight=true, bool doBkg=false, bool doSeparation=true){
    
    cout << " :::::: iso_efficiency_withSkimFile.C :::::: " << endl;
    if(doSeparation) cout << " :::::: Isolation Separation will be processed :::::: " << endl;
    else cout << " :::::: Only total efficiency will be calculated :::::: " << endl;
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);
    SetyjPadStyle();

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

    //define constants and histograms
    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1;
    Int_t nEff = 5;//1(tot):noiseCut && hoeCut && sigmaCut && isoCut && eleRej, 1(iso):noiseCut && hoeCut && sigmaCut && isoCut, 2(sigma):noiseCut && hoeCut && sigmaCut, 3(hoe):noiseCut && hoeCut, 4(noise):noise//
    Int_t nEffloop = nEff;
    if(doSeparation==0) nEffloop = 1;
    TString effSt[] = {"tot","iso","sigma","hoe","noise"};
    TString effSt_legend[] = {"total(noise & H/E & #sigma_{i#etai#eta} & sumIso & eleRej)","noise & H/E & #sigma_{i#etai#eta} & sumIso","noise & H/E & #sigma_{i#etai#eta}","noise & H/E","noise"};
    TH1D* bkg_den[nCENTBINS];
    TH1D* bkg_num[nCENTBINS][nEff];
    TH1D* bkg_eff[nCENTBINS][nEff];
    TH1D* sig_den[nCENTBINS];
    TH1D* sig_num[nCENTBINS][nEff];
    TH1D* sig_eff[nCENTBINS][nEff];

    //const int nConstEtaBin = 100;
    const int nConstEtaBin = 10;
    const double xMax = -1.44;
    const double xMin = 1.44;
    const double EtaBins[] = {-1.44,-1.00,-0.50,0.00,0.50,1.00,1.44}; 
    const int nEtaBin = sizeof(EtaBins)/sizeof(double) -1;

    for(Int_t i=0;i<nCENTBINS;++i){
        if(isConsBin) {
            bkg_den[i] = new TH1D(Form("bkg_den_cent%d",i),";#eta^{#gamma};dN/d#eta",nConstEtaBin, xMin, xMax);
            sig_den[i] = new TH1D(Form("sig_den_cent%d",i),";#eta^{#gamma};dN/d#eta",nConstEtaBin, xMin, xMax);
        } else{
            bkg_den[i] = new TH1D(Form("bkg_den_cent%d",i),";#eta^{#gamma} (GeV);dN/d#eta",nEtaBin,EtaBins);
            sig_den[i] = new TH1D(Form("sig_den_cent%d",i),";#eta^{#gamma} (GeV);dN/d#eta",nEtaBin,EtaBins);
        } 
        for(Int_t j=0;j<nEffloop;++j){
            if(isConsBin) {
                bkg_num[i][j] = new TH1D(Form("bkg_num_cent%d_%s",i,effSt[j].Data()),";#eta^{#gamma} (GeV);dN/d#eta",nConstEtaBin, xMin, xMax);
                bkg_eff[i][j] = new TH1D(Form("bkg_eff_cent%d_%s",i,effSt[j].Data()),";#eta^{#gamma} (GeV);Efficiency",nConstEtaBin, xMin, xMax);
                sig_num[i][j] = new TH1D(Form("sig_num_cent%d_%s",i,effSt[j].Data()),";#eta^{#gamma} (GeV);dN/d#eta",nConstEtaBin, xMin, xMax);
                sig_eff[i][j] = new TH1D(Form("sig_eff_cent%d_%s",i,effSt[j].Data()),";#eta^{#gamma} (GeV);Efficiency",nConstEtaBin, xMin, xMax);
            } else{ 
                bkg_num[i][j] = new TH1D(Form("bkg_num_cent%d_%s",i,effSt[j].Data()),";#eta^{#gamma} (GeV);dN/d#eta",nEtaBin,EtaBins);
                bkg_eff[i][j] = new TH1D(Form("bkg_eff_cent%d_%s",i,effSt[j].Data()),";#eta^{#gamma} (GeV);Efficiency",nEtaBin,EtaBins);
                sig_num[i][j] = new TH1D(Form("sig_num_cent%d_%s",i,effSt[j].Data()),";#eta^{#gamma} (GeV);dN/d#eta",nEtaBin,EtaBins);
                sig_eff[i][j] = new TH1D(Form("sig_eff_cent%d_%s",i,effSt[j].Data()),";#eta^{#gamma} (GeV);Efficiency",nEtaBin,EtaBins);
            }
        }}

    // define cut seperately, step-by-step 
    TCut centCut[nCENTBINS];
    TCut commonCut[nCENTBINS];
    TCut numCut[nEff];
    numCut[0] = noiseCut && hoeCut && sigmaCut && isoCut && electronCut;
    numCut[1] = noiseCut && hoeCut && sigmaCut && isoCut;
    numCut[2] = noiseCut && hoeCut && sigmaCut;
    numCut[3] = noiseCut && hoeCut;
    numCut[4] = noiseCut;
    for(Int_t i=0;i<nCENTBINS;++i){
        centCut[i] = Form("(hiBin>=%d)&&(hiBin<%d)",centBins_i[i],centBins_f[i]);
        //commonCut[i] = trigCut_mc && etaCut && centCut[i];
        commonCut[i] = trigCut_mc && evtSelFilterCut && etaCut && centCut[i];
    } 
    if(coll=="pp") {
        //commonCut[0] = trigCut_mc_pp && etaCut; 
        commonCut[0] = trigCut_mc_pp && evtSelFilterCut_pp && etaCut; 
        numCut[0] = noiseCut && hoeCut_pp && sigmaCut_pp && isoCut_pp && electronCut; 
        numCut[1] = noiseCut && hoeCut_pp && sigmaCut_pp && isoCut_pp; 
        numCut[2] = noiseCut && hoeCut_pp && sigmaCut_pp; 
        numCut[3] = noiseCut && hoeCut_pp; 
        numCut[4] = noiseCut; 
    }

    //Fill histograms
    for(Int_t i=0;i<nCENTBINS;++i){
        if(doWeight)    t1->Draw(Form("%s>>%s",phoEtVar.Data(),sig_den[i]->GetName()), Form("(%s)*((%s) && (%s))","weight",mcIsolation.GetTitle(),commonCut[i].GetTitle()));
        else            t1->Draw(Form("%s>>%s",phoEtVar.Data(),sig_den[i]->GetName()), mcIsolation && commonCut[i]);
        sig_den[i]=(TH1D*)gDirectory->Get(sig_den[i]->GetName());
        if(doBkg){ 
            if(doWeight)    t1->Draw(Form("%s>>%s",phoEtVar.Data(),bkg_den[i]->GetName()), Form("(%s)*((%s) && (%s))","weight",mcBkgIsolation.GetTitle(),commonCut[i].GetTitle()));
            else            t1->Draw(Form("%s>>%s",phoEtVar.Data(),bkg_den[i]->GetName()),mcBkgIsolation && commonCut[i]);
            bkg_den[i]=(TH1D*)gDirectory->Get(bkg_den[i]->GetName());
        }
        for(Int_t j=0;j<nEffloop;++j){
            if(doWeight)    t1->Draw(Form("%s>>%s",phoEtVar.Data(),sig_num[i][j]->GetName()),Form("(%s)*((%s) && (%s) && (%s))","weight",mcIsolation.GetTitle(), commonCut[i].GetTitle(), numCut[j].GetTitle())); 
            else            t1->Draw(Form("%s>>%s",phoEtVar.Data(),sig_num[i][j]->GetName()), mcIsolation && commonCut[i] && numCut[j]); 
            sig_num[i][j]=(TH1D*)gDirectory->Get(sig_num[i][j]->GetName());
            if(doBkg){
                if(doWeight)    t1->Draw(Form("%s>>%s",phoEtVar.Data(),sig_num[i][j]->GetName()),Form("(%s)*((%s) && (%s) && (%s))","weight",mcBkgIsolation.GetTitle(), commonCut[i].GetTitle(), numCut[j].GetTitle())); 
                else            t1->Draw(Form("%s>>%s",phoEtVar.Data(),bkg_num[i][j]->GetName()),mcBkgIsolation && commonCut[i] && numCut[j]); 
                bkg_num[i][j]=(TH1D*)gDirectory->Get(bkg_num[i][j]->GetName());
            }
        }
    }

    for(Int_t i=0;i<nCENTBINS;++i){
        for(Int_t j=0;j<nEffloop;++j){
            sig_eff[i][j]->Divide(sig_num[i][j],sig_den[i],1.,1.,"B");
            if(doBkg) bkg_eff[i][j]->Divide(bkg_num[i][j],bkg_den[i],1.,1.,"B");
        }}
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/";

    /////////////////////////////////////////////////////////////////////
    // DRAWING 
    cout << " DRAWING STARTS " << endl;
    TLegend* l1 = new TLegend(0.5,0.2,0.8,0.4);
    legStyle(l1);

   // TH1D* bkg_eff_draw[nCENTBINS][nEff];
   // TH1D* sig_eff_draw[nCENTBINS][nEff];
   // for(Int_t i=0;i<nCENTBINS;++i){
   //     for(Int_t j=0;j<nEffloop;++j){
   //         bkg_eff_draw[i][j] = new TH1D(Form("bkg_eff_draw_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);Efficiency",nEtaBin,EtaBins_draw);
   //         sig_eff_draw[i][j] = new TH1D(Form("sig_eff_draw_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);Efficiency",nEtaBin,EtaBins_draw);
   //         //bkg_eff_draw[i][j] = new TH1D(Form("bkg_eff_draw_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);Efficiency",nEtaBin,EtaBins_draw);
   //         //sig_eff_draw[i][j] = new TH1D(Form("sig_eff_draw_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);Efficiency",nEtaBin,EtaBins_draw);
   //         int temp_nEtaBin = -1;
   //         if(isConsBin) temp_nEtaBin = nConstEtaBin;
   //         else temp_nEtaBin = nEtaBin;
   //         for(int k=0;k<temp_nEtaBin;++k){
   //             if(doBkg) {
   //                 bkg_eff_draw[i][j]->SetBinContent(k+1,bkg_eff[i][j]->GetBinContent(k+1));
   //                 bkg_eff_draw[i][j]->SetBinError(k+1,bkg_eff[i][j]->GetBinError(k+1));
   //             }
   //             sig_eff_draw[i][j]->SetBinContent(k+1,sig_eff[i][j]->GetBinContent(k+1));
   //             sig_eff_draw[i][j]->SetBinError(k+1,sig_eff[i][j]->GetBinError(k+1));
   //         }
   //     }}

    /////////////////////////////////////////////////////////////////////
    // DRAWING : Centrality Dependence (Total Efficiency) 
    TCanvas* c1 =new TCanvas(Form("c%d",2),"", 400,400);
    //c1->SetLogx(); 
    for(Int_t i=0;i<nCENTBINS;++i){
        SetHistTextSize(sig_eff[i][0]);
       // if(i==0) {
       //     sig_eff_draw[i][0]->SetMarkerStyle(33);
       //     sig_eff_draw[i][0]->SetMarkerSize(1.4);
       // } else{
       //     sig_eff_draw[i][0]->SetMarkerStyle(20);
       // }
        sig_eff[i][0]->SetMarkerColor(colHere[i]);
        sig_eff[i][0]->SetMarkerStyle(markerStyle[i]);
        sig_eff[i][0]->GetYaxis()->SetRangeUser(0,1);
        sig_eff[i][0]->GetXaxis()->CenterTitle();
        sig_eff[i][0]->GetYaxis()->CenterTitle();
        if(i==0) sig_eff[i][0]->DrawCopy("p");
        else sig_eff[i][0]->DrawCopy("same p");
        if(coll=="pbpb") l1->AddEntry(sig_eff[i][0], Form("%d%s-%d%s",centBins_i[i]/2,"%",centBins_f[i]/2,"%"));
    } 
    if(coll=="pbpb") l1->Draw("same");
    drawText(Form("%s Total Isolation Efficiency",coll.Data()),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
    c1->SaveAs(Form("%sfigures/efficiency_iso_etaDep_%s_tot_centDep_%s.pdf",dir.Data(),coll.Data(),ver.Data()));

    /////////////////////////////////////////////////////////////////////
    // DRAWING : Centrality Dependence and Isolation Cut Dependence (Seperately)

    TLegend* l2 = new TLegend(0.15,0.2,0.9,0.4);
    legStyle(l2);
    TCanvas* c2[nCENTBINS];
    for(Int_t i=0;i<nCENTBINS;++i){
        c2[i] = new TCanvas(Form("c_isoDep_cent%d",i),"", 400,400);

        for(Int_t j=0;j<nEffloop;++j){
            SetHistTextSize(sig_eff[i][j]);
            //SetHistTextSize(sig_eff_draw[i][j]);
           // if(j==0) {
           //     sig_eff_draw[i][j]->SetMarkerStyle(33);
           // } else{
           //     sig_eff_draw[i][j]->SetMarkerStyle(20);
           // }
            sig_eff[i][j]->SetMarkerColor(colHere[j]);
            sig_eff[i][j]->SetMarkerStyle(markerStyle[j]);
            sig_eff[i][j]->GetYaxis()->SetRangeUser(0,1);
            sig_eff[i][j]->GetXaxis()->CenterTitle();
            sig_eff[i][j]->GetYaxis()->CenterTitle();
            if(j==0) sig_eff[i][j]->DrawCopy("p");
            else sig_eff[i][j]->DrawCopy("same p");
        } 
        for(Int_t j=nEff-1;j>-1;--j){
            if(i==0) l2->AddEntry(sig_eff[i][j], Form("%s",effSt_legend[j].Data()));
        }
        l2->Draw("same");
        if(coll=="pbpb") drawText(Form("%s %d%s-%d%s",coll.Data(),centBins_i[i]/2,"%",centBins_f[i]/2,"%"),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
        else drawText(Form("%s",coll.Data()),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
        if(coll=="pbpb") c2[i]->SaveAs(Form("%sfigures/efficiency_iso_etaDep_%s_isoDep_%s_cent%d%s-%d%s.pdf",dir.Data(),coll.Data(),ver.Data(),centBins_i[i]/2,"%",centBins_f[i]/2,"%"));
        else c2[i]->SaveAs(Form("%sfigures/efficiency_iso_etaDep_%s_isoDep_%s.pdf",dir.Data(),coll.Data(),ver.Data()));
    }
    //*/
    /////////////////////////////////////////////////////////////////////
    // Write output file  
    cout << "Output File : " << endl;
    TString outFname = Form("%soutput/%s_iso_efficiency_etaDep_%s.root",dir.Data(),coll.Data(),ver.Data());
    TFile* fout = new TFile(outFname,"RECREATE");
    fout->cd();
    c1->Write();
    cout << " aaaaaaaaag" << endl;
    for(Int_t i=0;i<nCENTBINS;++i){
        sig_den[i]->Write();
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
