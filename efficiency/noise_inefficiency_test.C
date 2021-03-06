// Created : 2017 April 18
// Modified : 2017 May18
// Author : Yeonju Go
// 

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
bool isConsBin = false;
bool doPthatWeight = true;
bool doEmEnrSample = true;
const int colHere[]={2,4,8,kYellow+2,kCyan+1};
void noise_inefficiency_test(TString coll="pp", TString ver="180501_temp_v13_eleRejNew_iso", bool doSeparation=true){
    cout << " :::::: noise_inefficiency_test.C :::::: " << endl;
    if(doSeparation) cout << " :::::: Isolation Separation will be processed :::::: " << endl;
    else cout << " :::::: Only total efficiency will be calculated :::::: " << endl;
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);
    SetyjPadStyle();

    const char* fname[2];
    if(coll=="pp"){ 
        fname[0]=Form("%s",ppMCfname.Data());
        fname[1]=Form("%s",ppMCEmEnrfname.Data());
    } else if(coll=="pbpb"){
        fname[0]=Form("%s",pbpbMCfname.Data());
        fname[1]=Form("%s",pbpbMCEmEnrfname.Data());
    }
    //////////////// NEW ELECTRON REJECTION /////////////////
    if(coll=="pp"){ 
        fname[0]="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-04-06-nominal/pp_MC_photonRaaSkim_eleRejNew.root";
        fname[1]="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-04-06-nominal/pp_EmEnrMC_photonRaaSkim_eleRejNew.root";
    } else if(coll=="pbpb"){
        fname[0]="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-04-06-nominal/PbPb_MC_photonRaaSkim_v14_eleRejNew.root";
        fname[1]="/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2018-04-06-nominal/PbPb_EmEnrMC_photonRaaSkim_v14_eleRejNew.root";
    }
    
    TChain* t1 = new TChain("EventTree");
    TChain* t1_skim = new TChain("skim");
    TChain* t1_evt = new TChain("HiEvt");
    TChain* t1_hlt = new TChain("hltTree");
    int nSAMPLE = 2;
    if(doEmEnrSample) nSAMPLE = 2;
    else nSAMPLE = 1;
    for(Int_t j=0;j<nSAMPLE;++j){
        t1->Add(fname[j]);
        t1_skim->Add(fname[j]);
        t1_evt->Add(fname[j]);
        t1_hlt->Add(fname[j]);
    }
    t1->AddFriend(t1_skim);
    t1->AddFriend(t1_evt);
    t1->AddFriend(t1_hlt);

    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1;

    Int_t nEff = 3;//0(electron):spikeRejection && hotspotCut && electronCut (= noiseCut), 1(hotspot):spikeRejection && hotspotCut, 2(spike):spikeRejection
    Int_t nEffloop = nEff;
    if(doSeparation==0) nEffloop = 1;
    TString effSt[] = {"eleRej","sig_sumIso","sig"};
    TString effSt_legend[] = {"noise & H/E & #sigma_{I#etaI#eta} & sumIso & electron rej.","noise & H/E & #sigma_{I#etaI#eta} & sumIso","noise & H/E & #sigma_{I#etaI#eta}"};
   // TString effSt[] = {"tot","hotspot","spike"};
   // TString effSt_legend[] = {"total noise(spike & hotspot & electron)","spike & hotspot","spike"};
    TH1D* bkg_den[nCENTBINS];
    TH1D* bkg_num[nCENTBINS][nEff];
    TH1D* bkg_eff[nCENTBINS][nEff];
    TH1D* sig_den[nCENTBINS];
    TH1D* sig_num[nCENTBINS][nEff];
    TH1D* sig_eff[nCENTBINS][nEff];

    const int nConstPtBin = 100;
    const int xMax = 140;
    const int xMin = 40;
    for(Int_t i=0;i<nCENTBINS;++i){
        if(isConsBin) {
            bkg_den[i] = new TH1D(Form("bkg_den_cent%d",i),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nConstPtBin, xMin, xMax);
            sig_den[i] = new TH1D(Form("sig_den_cent%d",i),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nConstPtBin, xMin, xMax);
        } else{
            bkg_den[i] = new TH1D(Form("bkg_den_cent%d",i),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nPtBin,ptBins);
            sig_den[i] = new TH1D(Form("sig_den_cent%d",i),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nPtBin,ptBins);
        } 
        for(Int_t j=0;j<nEffloop;++j){
            if(isConsBin) {
                bkg_num[i][j] = new TH1D(Form("bkg_num_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nConstPtBin, xMin, xMax);
                bkg_eff[i][j] = new TH1D(Form("bkg_eff_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);Efficiency",nConstPtBin, xMin, xMax);
                sig_num[i][j] = new TH1D(Form("sig_num_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nConstPtBin, xMin, xMax);
                sig_eff[i][j] = new TH1D(Form("sig_eff_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);Efficiency",nConstPtBin, xMin, xMax);
            } else{ 
                bkg_num[i][j] = new TH1D(Form("bkg_num_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nPtBin,ptBins);
                bkg_eff[i][j] = new TH1D(Form("bkg_eff_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);Efficiency",nPtBin,ptBins);
                sig_num[i][j] = new TH1D(Form("sig_num_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);dN/dp_{T}",nPtBin,ptBins);
                sig_eff[i][j] = new TH1D(Form("sig_eff_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);Efficiency",nPtBin,ptBins);
            }
        }}

    TCut centCut[nCENTBINS];
    TCut commonCut[nCENTBINS];
    TCut numCut[nEff];
    //numCut[0] = electronCut; // only electronCut
    numCut[0] = spikeRejection && hotspotCut && hoeCut && sigmaCut && isoCut && electronCut; // it's the same with noiseCut
    numCut[1] = spikeRejection && hotspotCut && hoeCut && sigmaCut && isoCut;
    numCut[2] = spikeRejection && hotspotCut && hoeCut && sigmaCut;
   // numCut[0] = spikeRejection && hotspotCut && electronCut; // it's the same with noiseCut
   // numCut[1] = spikeRejection && hotspotCut;
   // numCut[2] = spikeRejection;

    for(Int_t i=0;i<nCENTBINS;++i){
        centCut[i] = Form("(hiBin>=%d)&&(hiBin<%d)",centBins_i[i],centBins_f[i]);
        commonCut[i] = trigCut_mc && etaCut && centCut[i];
        //commonCut[i] = trigCut_mc && evtSelFilterCut && etaCut && centCut[i];
    } 

    if(coll=="pp") {
        commonCut[0] = trigCut_mc_pp && etaCut; 
        numCut[0] = spikeRejection && hotspotCut && hoeCut && sigmaCut && isoCut && electronCut;
        numCut[1] = spikeRejection && hotspotCut && hoeCut && sigmaCut && isoCut;
        numCut[2] = spikeRejection && hotspotCut && hoeCut && sigmaCut;  
       // numCut[0] = spikeRejection && hotspotCut && electronCut; // it's the same with noiseCut
       // numCut[1] = spikeRejection && hotspotCut;
       // numCut[2] = spikeRejection;
    }
    for(Int_t i=0;i<nCENTBINS;++i){
        //fill signal photons denominator 
        if(doPthatWeight) t1->Draw(Form("%s>>%s",phoEtVar.Data(),sig_den[i]->GetName()),Form("(%s)*((%s) && (%s))","weight",mcIsolation.GetTitle(),commonCut[i].GetTitle()));
        else t1->Draw(Form("%s>>%s",phoEtVar.Data(),sig_den[i]->GetName()), mcIsolation && commonCut[i]);
        sig_den[i]=(TH1D*)gDirectory->Get(sig_den[i]->GetName());
        
        //fill background photons denominator 
        if(doPthatWeight) t1->Draw(Form("%s>>%s",phoEtVar.Data(),bkg_den[i]->GetName()),Form("(%s)*((%s) && (%s))","weight",mcBkgIsolation.GetTitle(),commonCut[i].GetTitle()));
        else t1->Draw(Form("%s>>%s",phoEtVar.Data(),bkg_den[i]->GetName()),mcBkgIsolation && commonCut[i]);
        bkg_den[i]=(TH1D*)gDirectory->Get(bkg_den[i]->GetName());

        for(Int_t j=0;j<nEffloop;++j){
            //fill signal photons numerator 
            if(doPthatWeight) t1->Draw(Form("%s>>%s",phoEtVar.Data(),sig_num[i][j]->GetName()),Form("(%s)*((%s) && (%s) && (%s))","weight",mcIsolation.GetTitle(), commonCut[i].GetTitle(), numCut[j].GetTitle())); 
            else t1->Draw(Form("%s>>%s",phoEtVar.Data(),sig_num[i][j]->GetName()), mcIsolation && commonCut[i] && numCut[j]); 
            sig_num[i][j]=(TH1D*)gDirectory->Get(sig_num[i][j]->GetName());
            
            //fill background photons numerator 
            if(doPthatWeight) t1->Draw(Form("%s>>%s",phoEtVar.Data(),bkg_num[i][j]->GetName()),Form("(%s)*((%s) && (%s) && (%s))","weight",mcBkgIsolation.GetTitle(), commonCut[i].GetTitle(), numCut[j].GetTitle())); 
            else t1->Draw(Form("%s>>%s",phoEtVar.Data(),bkg_num[i][j]->GetName()),mcBkgIsolation && commonCut[i] && numCut[j]); 
            bkg_num[i][j]=(TH1D*)gDirectory->Get(bkg_num[i][j]->GetName());
        }
    }

    for(Int_t i=0;i<nCENTBINS;++i){
        for(Int_t j=0;j<nEffloop;++j){
            sig_eff[i][j]->Divide(sig_num[i][j],sig_den[i],1.,1.,"B");
            bkg_eff[i][j]->Divide(bkg_num[i][j],bkg_den[i],1.,1.,"B");
        }}
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/";

    /////////////////////////////////////////////////////////////////////
    // DRAWING 
    cout << " DRAWING STARTS " << endl;
    TLegend* l1 = new TLegend(0.5,0.2,0.8,0.4);
    legStyle(l1);

    TH1D* bkg_eff_draw[nCENTBINS][nEff];
    TH1D* sig_eff_draw[nCENTBINS][nEff];
    for(Int_t i=0;i<nCENTBINS;++i){
        for(Int_t j=0;j<nEffloop;++j){
            bkg_eff_draw[i][j] = new TH1D(Form("bkg_eff_draw_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);Efficiency",nPtBin,ptBins_draw);
            sig_eff_draw[i][j] = new TH1D(Form("sig_eff_draw_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);Efficiency",nPtBin,ptBins_draw);
            int temp_nPtBin = -1;
            if(isConsBin) temp_nPtBin = nConstPtBin;
            else temp_nPtBin = nPtBin;
            for(int k=0;k<temp_nPtBin;++k){
                bkg_eff_draw[i][j]->SetBinContent(k+1,bkg_eff[i][j]->GetBinContent(k+1));
                bkg_eff_draw[i][j]->SetBinError(k+1,bkg_eff[i][j]->GetBinError(k+1));
                sig_eff_draw[i][j]->SetBinContent(k+1,sig_eff[i][j]->GetBinContent(k+1));
                sig_eff_draw[i][j]->SetBinError(k+1,sig_eff[i][j]->GetBinError(k+1));
            }
        }}

    /////////////////////////////////////////////////////////////////////
    // DRAWING : Centrality Dependence (Total Efficiency) 
    TCanvas* c1 =new TCanvas(Form("c%d",2),"", 400,400);
    //c1->SetLogx(); 
    for(Int_t i=0;i<nCENTBINS;++i){
        SetHistTextSize(sig_eff_draw[i][0]);
        if(i==0) {
            sig_eff_draw[i][0]->SetMarkerStyle(33);
            sig_eff_draw[i][0]->SetMarkerSize(1.4);
            bkg_eff_draw[i][0]->SetMarkerStyle(33);
        } else{
            sig_eff_draw[i][0]->SetMarkerStyle(20);
            bkg_eff_draw[i][0]->SetMarkerStyle(20);
        }
        sig_eff_draw[i][0]->SetMarkerColor(colHere[i]);
        bkg_eff_draw[i][0]->SetMarkerColor(colHere[i]);
        sig_eff_draw[i][0]->GetYaxis()->SetRangeUser(0.0,1);
        //sig_eff_draw[i][0]->GetYaxis()->SetRangeUser(0.8,1);
        sig_eff_draw[i][0]->GetXaxis()->CenterTitle();
        sig_eff_draw[i][0]->GetYaxis()->CenterTitle();
        if(i==0) sig_eff_draw[i][0]->Draw("p");
        else sig_eff_draw[i][0]->Draw("same p");
        //bkg_eff[i]->Draw("same p");
        if(coll=="pbpb") l1->AddEntry(sig_eff_draw[i][0], Form("%d%s-%d%s",centBins_i[i]/2,"%",centBins_f[i]/2,"%"));
    } 
    if(coll=="pbpb") l1->Draw("same");
    drawText(Form("%s Total Isolation Efficiency",coll.Data()),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
    if(doPthatWeight) ver += "_pthatWeighted";
    if(!doEmEnrSample) ver += "_noEmEnrSample"; 
    c1->SaveAs(Form("%sfigures/%s_tot_noise_inefficiency_centDep_%s.pdf",dir.Data(),coll.Data(),ver.Data())); 

    /////////////////////////////////////////////////////////////////////
    // DRAWING : Centrality Dependence and Isolation Cut Dependence (Seperately)
    cout << "sss" << endl; 
    TLegend* l2 = new TLegend(0.13,0.2,0.9,0.4);
    legStyle(l2);
    TCanvas* c2[nCENTBINS];
    cout << "sss" << endl; 
    for(Int_t i=0;i<nCENTBINS;++i){
        c2[i] = new TCanvas(Form("c_isoDep_cent%d",i),"", 400,400);
        cout << "ggggggggg" << endl; 

        for(Int_t j=0;j<nEffloop;++j){
            SetHistTextSize(sig_eff_draw[i][j]);
            if(j==0) {
                sig_eff_draw[i][j]->SetMarkerStyle(33);
                bkg_eff_draw[i][j]->SetMarkerStyle(33);
            } else{
                sig_eff_draw[i][j]->SetMarkerStyle(20);
                bkg_eff_draw[i][j]->SetMarkerStyle(20);
            }
            sig_eff_draw[i][j]->SetMarkerColor(colHere[j]);
            bkg_eff_draw[i][j]->SetMarkerColor(colHere[j]);
            sig_eff_draw[i][j]->GetYaxis()->SetRangeUser(0.0,1);
            //sig_eff_draw[i][j]->GetYaxis()->SetRangeUser(0.8,1);
            sig_eff_draw[i][j]->GetXaxis()->CenterTitle();
            sig_eff_draw[i][j]->GetYaxis()->CenterTitle();
            if(j==0) sig_eff_draw[i][j]->Draw("p");
            else sig_eff_draw[i][j]->Draw("same p");
        } 
        cout << "zzzzzzzzzzggggggggg" << endl; 
        for(Int_t j=nEffloop-1;j>-1;--j){
            if(i==0) l2->AddEntry(sig_eff_draw[i][j], Form("%s",effSt_legend[j].Data()));
        }
        cout << "aaaaaaaaazzzzzzzzzzggggggggg" << endl; 
        l2->Draw("same");
        if(coll=="pbpb") drawText(Form("%s %d%s-%d%s",coll.Data(),centBins_i[i]/2,"%",centBins_f[i]/2,"%"),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
        else drawText(Form("%s",coll.Data()),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
        if(coll=="pbpb") c2[i]->SaveAs(Form("%sfigures/%s_noise_inefficiency_isoDep_%s_cent%d%s-%d%s.pdf",dir.Data(),coll.Data(),ver.Data(),centBins_i[i]/2,"%",centBins_f[i]/2,"%"));
        else c2[i]->SaveAs(Form("%sfigures/%s_noise_inefficiency_isoDep_%s.pdf",dir.Data(),coll.Data(),ver.Data()));
    }
    //*/
    /////////////////////////////////////////////////////////////////////
    // Write output file  
    cout << "Output File : " << endl;
    TString outFname = Form("%soutput/%s_noise_inefficiency_%s.root",dir.Data(),coll.Data(),ver.Data());
    TFile* fout = new TFile(outFname,"RECREATE");
    fout->cd();
    c1->Write();
    cout << " aaaaaaaaag" << endl;
    for(Int_t i=0;i<nCENTBINS;++i){
        sig_den[i]->Write();
        bkg_den[i]->Write();
        c2[i]->Write();
        for(Int_t j=0;j<nEffloop;++j){
            sig_num[i][j]->Write();
            bkg_num[i][j]->Write();
            sig_eff[i][j]->Write();
            bkg_eff[i][j]->Write();
        }}
}
