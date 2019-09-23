// Created : 2017 April 18
// Modified : 2019 June 26
// Author : Yeonju Go
// (deprecated) iso_efficiency_withSkimFile_v2 : unfolding binning (15 GeV to 300 GeV)
// (deprecated) trigger efficiency will be calculated by MC here in this code
// 2019June25) different unfolding binning depending on centrality bin 
// 2019June25) apply trigger efficiency which is derived using DATA to here but not draw in canvas
// 2019June25) unfolding binning (20 GeV to 300 GeV) 

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_190703_temp_v31_efficiency_forPaper.h"
//#include "../phoRaaCuts/phoRaaCuts_temp.h"

bool isConsBin = false;
const int colHere[]={kYellow+2,kPink-5,kGreen+3,kBlue-3,kOrange+4,kYellow+2,kPink-5,kGreen+3,kBlue-3};
//const int colHere[]={kBlack,kPink-5,kGreen+3,kBlue-3,kOrange+4,kBlack,kPink-5,kGreen+3,kBlue-3};
//const int colHere[]={2,4,8,kYellow+2,kCyan+1,kOrange+7,kViolet-7};
const int markerStyle[]={24,33,24,34,29,20,28,22};
void draw_iso_efficiency_v2_forPaper(TString coll="pp", TString ver="190703_temp_v31_nominal", bool doWeight=true, bool doBkg=false, bool doSeparation=true){

    cout << " :::::: draw_iso_efficiency_v2.C :::::: " << endl;
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);
    SetyjPadStyle();
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/";

    TString fname;

    if(coll=="pp"){
        fname = Form("./output/pp_iso_efficiency_%s.root",ver.Data());
    } else if(coll=="pbpb"){
        fname = Form("./output/pbpb_iso_efficiency_%s.root",ver.Data());
    }
    TFile* f1 = new TFile(Form("%s",fname.Data()),"read");
    //TFile* f1 = new TFile(Form("%s",fname.Data()));
    //TFile* f1 = new TFile(fname,"read");

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
    TH1D* sig_eff[nCENTBINS][nEff];
    TH1D* sig_num[nCENTBINS][nEff];
    //TH1D* h_temp_trig[nCENTBINS][2]; //[Centrality][0:20-40GeV, 1: over 40GeV]

    //TH1D* h1D_eff[nCENTBINS][nEff];
    for(Int_t icent=0;icent<nCENTBINS;++icent){
        for(Int_t j=0;j<nEffloop;++j){
            sig_eff[icent][j] = (TH1D*) f1->Get(Form("sig_eff_cent%d_%s",icent,effSt[j].Data()));
            sig_num[icent][j] = (TH1D*) f1->Get(Form("sig_num_cent%d_%s",icent,effSt[j].Data()));
            cout << "get name = " << sig_eff[icent][j]->GetName() << endl; 
            cout << "get name = " << sig_num[icent][j]->GetName() << endl; 
        }
    }

    /////////////////////////////////////////////////////////////////////
    // DRAWING 
    cout << " SET HISTS " << endl;
    TLegend* l1 = new TLegend(0.65,0.2,0.9,0.55);
    //TLegend* l1 = new TLegend(0.5,0.2,0.85,0.45);
    legStyle(l1);

    //TH1D* sig_eff[nCENTBINS][nEff];
    //for(Int_t i=0;i<nCENTBINS;++i){
    //    // rebin ptbins for each centrality bins since we have less bins for peripheral region
    //    int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[i];
    //    double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
    //    for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
    //        ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
    //    } 

    //    //for(Int_t j=nEffloop-1;j>-1;--j){
    //    //    sig_eff[i][j] = new TH1D(Form("sig_eff_cent%d_%s",i,effSt[j].Data()),";p_{T}^{#gamma} (GeV);Efficiency",nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
    //    //    int temp_nPtBin_unfolding_centDep = nPtBin_unfolding_centDep;
    //    //    //if(isConsBin) temp_nPtBin_unfolding_centDep = nConstPtBin;
    //    //    //else temp_nPtBin_unfolding_centDep = nPtBin_unfolding_centDep;
    //    //    for(int k=0;k<temp_nPtBin_unfolding_centDep;++k){
    //    //        sig_eff[i][j]->SetBinContent(k+1,sig_eff[i][j]->GetBinContent(k+1));
    //    //        sig_eff[i][j]->SetBinError(k+1,sig_eff[i][j]->GetBinError(k+1));
    //    //    }
    //    //}
    //}

    /////////////////////////////////////////////////////////////////////
    // DRAWING : Centrality Dependence (Total Efficiency) 
    cout << " DRAWING STARTS " << endl;
    cout << " Total efficiency vs. pT " << endl;
    TCanvas* c1 =new TCanvas(Form("c%d",2),"", 400,400);
    gPad->SetLogx(); 
    TH1D* htemp_draw[nCENTBINS];
    for(Int_t i=0;i<nCENTBINS;++i){
        SetHistTextSize(sig_eff[i][1]);
        // if(i==0) {
        //     sig_eff[i][0]->SetMarkerStyle(33);
        //     sig_eff[i][0]->SetMarkerSize(1.4);
        // } else{
        //     sig_eff[i][0]->SetMarkerStyle(20);
        // }
        sig_eff[i][1]->SetMarkerColor(colHere[i]);
        sig_eff[i][1]->SetMarkerStyle(markerStyle[i+1]);
        sig_eff[i][1]->SetMarkerSize(1.2);
        sig_eff[i][1]->GetYaxis()->SetRangeUser(0,1.2);
        sig_eff[i][1]->GetXaxis()->SetRangeUser(25,200);
        sig_eff[i][1]->GetXaxis()->CenterTitle();
        sig_eff[i][1]->GetYaxis()->CenterTitle();
        htemp_draw[i] = (TH1D*) sig_eff[i][1]->Clone(Form("htemp_draw%d",i));
        htemp_draw[i]->SetTitle(";E_{T}^{#gamma} (GeV);Total Efficiency");
        if(i==0) sig_eff[i][1]->DrawCopy("p");
        else sig_eff[i][1]->DrawCopy("same p");
        if(coll=="pbpb") l1->AddEntry(htemp_draw[i], Form("%d-%d%s",centBins_i[i]/2,centBins_f[i]/2,"%"));
        //if(coll=="pbpb") l1->AddEntry(sig_eff[i][1], Form("%d%s-%d%s",centBins_i[i]/2,"%",centBins_f[i]/2,"%"));
    } 
    c1->SetLogx(); 
    jumSun(25,1,300,1);
    cout << "zzz" << endl;
    if(coll=="pbpb") l1->Draw("same");
    //drawText(Form("%s Total Isolation Efficiency",coll.Data()),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
    c1->SaveAs(Form("%sfigures/efficiency_forPaper_%s_totEff_centDep_%s.pdf",dir.Data(),coll.Data(),ver.Data()));

    /////////////////////////////////////////////////////////////////////
    // DRAWING : Centrality Dependence and Isolation Cut Dependence (each centrality bin separately)

    cout << "Each efficiency vs. pT in different centrality bins" << endl;
    TLegend* l2 = new TLegend(0.24,0.2,0.92,0.4);
    legStyle(l2);
    TCanvas* c2[nCENTBINS];
    for(Int_t i=0;i<nCENTBINS;++i){
        c2[i] = new TCanvas(Form("c_effDep_cent%d",i),"", 400,400);
        //c2[i]->SetLogx();

        for(Int_t j=1;j<nEffloop;++j){
            SetHistTextSize(sig_eff[i][j]);
            //sig_eff[i][j]->SetNdivisions(999); 
            sig_eff[i][j]->SetLineColor(colHere[j]);
            sig_eff[i][j]->SetMarkerColor(colHere[j]);
            sig_eff[i][j]->SetMarkerStyle(markerStyle[j]);
            if(j!=nEffloop-1) sig_eff[i][j]->SetMarkerSize(1.2);
            sig_eff[i][j]->GetYaxis()->SetRangeUser(0,1.2);
            sig_eff[i][j]->GetXaxis()->SetRangeUser(25,200);
            sig_eff[i][j]->GetXaxis()->CenterTitle();
            sig_eff[i][j]->GetYaxis()->CenterTitle();
            sig_eff[i][j]->SetTitle(";E_{T}^{#gamma} (GeV);Efficiency");
            if(j==1) sig_eff[i][j]->DrawCopy("p");
            else sig_eff[i][j]->DrawCopy("same p");
        } 
        for(Int_t j=nEff-1;j>0;--j){
            if(i==0) l2->AddEntry(sig_eff[i][j], Form("%s",effSt_legend[j].Data()));
        }
        l2->Draw("same");

        float xpos = 0.19;
        float ypos = 0.87;
        float dy = 0.05;
        float dx = 0.12;
        TLatex* latexCMS = new TLatex();
        latexCMS->SetTextFont(63);
        latexCMS->SetTextSize(21);
        //latexCMS->SetTextSize(32/2);
        latexCMS->DrawLatexNDC(xpos, ypos, "CMS");
        TLatex* latexPrelim = new TLatex();
        latexPrelim->SetTextFont(53);
        latexPrelim->SetTextSize(18);
        //latexPrelim->SetTextSize(28/2);
        latexPrelim->DrawLatexNDC(xpos+dx, ypos, "Preliminary");
        jumSun(25,1,200,1);

        float xpos2 = 0.9;
        if(coll=="pbpb") drawText(Form("%s","PYTHIA+HYDJET"),xpos2,ypos+0.01,1);
        if(coll=="pbpb") drawText(Form("%d-%d%s",centBins_i[i]/2,centBins_f[i]/2,"%"),xpos2,ypos-0.04,1);
        //if(coll=="pbpb") drawText(Form("%s","PYTHIA+HYDJET"),0.70,0.45,1);
        //if(coll=="pbpb") drawText(Form("%d-%d%s",centBins_i[i]/2,centBins_f[i]/2,"%"),0.70,0.40,1);
        else drawText(Form("%s","PYTHIA"),xpos2,ypos,1);
        //else drawText(Form("%s",coll.Data()),0.7,1.0-c1->GetBottomMargin()+0.4,0,kBlack,16);
        //else drawText(Form("%s",coll.Data()),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
        if(coll=="pbpb") c2[i]->SaveAs(Form("%sfigures/efficiency_forPaper_%s_effDep_%s_cent%dto%d.pdf",dir.Data(),coll.Data(),ver.Data(),centBins_i[i]/2,centBins_f[i]/2));
        else c2[i]->SaveAs(Form("%sfigures/efficiency_forPaper_%s_effDep_%s.pdf",dir.Data(),coll.Data(),ver.Data()));
    }

    /////////////////////////////////////////////////////////////////////
    // DRAWING : Centrality Dependence (Total Efficiency including trigger efficiency and tag and probe) 

    if(ptDepTnP && coll=="pbpb"){
        cout << "Applying TnP for PbPb in terms of pT" << endl;
        for(int j=0;j<nCentBinIF;++j){
            int nTnPbin = 0;
            int tempPtSec = pbpb_tnp_pt_sec[0];
            double tempTnP = pbpb_tnp_pt[0];
            int nbinsx = sig_eff[j][0]->GetNbinsX();
            for(int i=0; i<nbinsx;++i){
                double bincenter = sig_eff[j][0]->GetBinCenter(i+1);
                double bincontent = sig_eff[j][0]->GetBinContent(i+1);
                if(bincenter>=tempPtSec){
                    nTnPbin += 1;
                    tempPtSec = pbpb_tnp_pt_sec[nTnPbin];
                    tempTnP = pbpb_tnp_pt[nTnPbin];
                }
                sig_eff[j][0]->SetBinContent(i+1,bincontent*tempTnP);
                //cout << "pbpb ptBin " << ptBins_unfolding[i] << " - " << ptBins_unfolding[i+1] << " : " << tempTnP << endl;
            }
        }
    }
    if(ptDepTnP_pp && coll=="pp"){
        cout << "Applying TnP for pp in terms of pT" << endl;
        int nTnPbin = 0;
        int tempPtSec = pp_tnp_pt_sec[0];
        double tempTnP = pp_tnp_pt[0];
        int nbinsx = sig_eff[0][0]->GetNbinsX();
        for(int i=0; i<nbinsx;++i){
            double bincenter = sig_eff[0][0]->GetBinCenter(i+1);
            double bincontent = sig_eff[0][0]->GetBinContent(i+1);
            if(bincenter>=tempPtSec){
                nTnPbin += 1;
                tempPtSec = pp_tnp_pt_sec[nTnPbin];
                tempTnP = pp_tnp_pt[nTnPbin];
            }
            sig_eff[0][0]->SetBinContent(i+1,bincontent*tempTnP);
            //cout << "pp ptBin " << ptBins_unfolding[i] << " - " << ptBins_unfolding[i+1] << " : " << tempTnP << endl;
        }
    }
    cout << "Total efficiency including trigger vs. pT " << endl;
    TCanvas* c3 =new TCanvas(Form("c%d",3),"", 400,400);
    //c3->SetLogx();
    for(Int_t i=0;i<nCENTBINS;++i){
        SetHistTextSize(sig_eff[i][0]);
        sig_eff[i][0]->SetNdivisions(512);
        sig_eff[i][0]->SetMarkerColor(colHere[i]);
        sig_eff[i][0]->SetMarkerStyle(markerStyle[i+1]);
        sig_eff[i][0]->SetMarkerSize(1.1);
        sig_eff[i][0]->SetLineColor(colHere[i]);
        sig_eff[i][0]->GetYaxis()->SetRangeUser(0,1);
        if(i==0) sig_eff[i][0]->GetXaxis()->SetRangeUser(25,200);
        sig_eff[i][0]->SetTitle(";E_{T}^{#gamma} (GeV);Total Efficiency");
        //sig_eff[i][0]->SetTitle(";p_{T}^{#gamma} (GeV);Total Efficiency");
        sig_eff[i][0]->GetXaxis()->CenterTitle();
        sig_eff[i][0]->GetYaxis()->CenterTitle();
        if(i==0) sig_eff[i][0]->DrawCopy("p");
        else sig_eff[i][0]->DrawCopy("same p");
    } 
        float xpos = 0.19;
        float ypos = 0.87;
        float dx = 0.12;
        TLatex* latexCMS = new TLatex();
        latexCMS->SetTextFont(63);
        latexCMS->SetTextSize(21);
        //latexCMS->SetTextSize(32/2);
        latexCMS->DrawLatexNDC(xpos, ypos, "CMS");
        TLatex* latexPrelim = new TLatex();
        latexPrelim->SetTextFont(53);
        latexPrelim->SetTextSize(18);
        //latexPrelim->SetTextSize(28/2);
        latexPrelim->DrawLatexNDC(xpos+dx, ypos, "Preliminary");
        jumSun(25,1,200,1);

        float xpos2 = 0.9;
        if(coll=="pbpb") drawText(Form("%s","PYTHIA+HYDJET"),xpos2,ypos,1);
        //if(coll=="pbpb") drawText(Form("%d-%d%s",centBins_i[i]/2,centBins_f[i]/2,"%"),xpos2,ypos-0.03,1);
    if(coll=="pbpb") l1->Draw("same");
    else drawText(Form("%s",coll.Data()),0.7,0.45);
    //drawText(Form("%s Total Isolation Efficiency",coll.Data()),0.2,1.0-c1->GetBottomMargin()+0.06,0,kBlack,16);
    c3->SaveAs(Form("%sfigures/efficiency_forPaper_withTrigEff_withTnP_%s_tot_centDep_%s.pdf",dir.Data(),coll.Data(),ver.Data()));

}
