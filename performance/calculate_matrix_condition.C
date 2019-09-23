// Created : 2017 April 18
// Modified 1: 2019 June 24
// Author : Yeonju Go
// to have centrality dependenct matrix binning 
// ex) matrix in 30-50% has pt binning up to 200 GeV while some others have up to 300 GeV 

#include "../phoRaaCuts/yjUtility.h"
#include "TMatrixD.h"
#include "TDecompSVD.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
bool isConsBin = false;
const int colHere[]={2,4,8,kYellow+2,kCyan+1};
const int markerStyle[]={20,33,22,23,22,29};
void calculate_matrix_condition(TString coll="pbpb", TString ver="190703_temp_v31_nominal", bool splitMC=false, bool isFineBinning=false, bool doWeight=true){
    cout << " :::::: calculate_matrix_condition.C :::::: " << endl;
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);
    gStyle->SetPaintTextFormat(".2f");
    SetyjPadStyle();
    
    //import skimed tree
    cout << "Import skimmed MC trees" << endl;
    const char* fname = "";
    if(coll=="pp"){ 
        fname=Form("%s",ppMCfname.Data());
    } else if(coll=="pbpb"){
        fname=Form("%s",pbpbMCfname.Data());
    }

    cout << "Define constants" << endl;
    //define constants and histograms
    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1;
    Int_t nFineBin = 10;
    TString cap = Form("%s_pbpb",ver.Data());
    if(coll=="pp") cap= Form("%s_pp",ver.Data());
    if(isFineBinning) cap+=Form("_nFinePtBins%d",nFineBin);
    if(!doWeight) cap+=Form("_%s","noWeight");
    if(splitMC) cap+=Form("_%s","splitMC");

    /////////////////////////////////////////////////////////////////////
    // Input file  
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/";
    TString inFname = Form("%soutput/correlation_genPt_recoPt_%s.root",dir.Data(),cap.Data());
    cout << "Input file : "<< inFname << endl;
    TFile* fin = new TFile(inFname);

    TH2D* h2D_gen_reco[nCENTBINS]; 
    TH2D* h2D_gen_reco_percent[nCENTBINS]; 

    TString centSt[nCENTBINS];
    for(Int_t j=0;j<nCENTBINS;++j){
        centSt[j] = Form("cent%dto%d",(int)centBins_i[j]/2,(int)centBins_f[j]/2);

        // rebin ptbins for each centrality bins since we have less bins for peripheral region 
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];
        double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
            ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
        }

        h2D_gen_reco[j] = (TH2D*) fin->Get(Form("h2D_corr_gen_reco_%s",centSt[j].Data()));
        h2D_gen_reco_percent[j] = (TH2D*) fin->Get(Form("h2D_corr_gen_reco_percent_%s",centSt[j].Data()));
    }
    TMatrixD* matD[nCENTBINS];
    /////////////////////////////////////////////////////////////////////
    // Calculate Matrix for h2D genPt vs. recoPt correlation with percent : Response matrix 
    TCanvas* c3 =new TCanvas(Form("c%d",3),"", 400*nCENTBINS,400*2);
    c3->Divide(nCENTBINS,2);
    for(Int_t i=0;i<nCENTBINS;++i){
        cout << "centrality " << i << endl;
        int ny = h2D_gen_reco[i]->GetNbinsY();
        int nx = h2D_gen_reco[i]->GetNbinsX();
        matD[i] = new TMatrixD(ny,nx);

        TMatrixD testmat(nx,ny);
        for(int ypt=1; ypt<=ny; ++ypt){
            for(int xpt=1; xpt<=h2D_gen_reco[i]->GetNbinsX(); ++xpt){
                double evtInAbin = h2D_gen_reco[i]->GetBinContent(xpt,ypt); 
                testmat(ypt-1,xpt-1) = evtInAbin;
                //matD[i](ypt-1,xpt-1) = evtInAbin;
            }//x loop
        }//y loop
        c3->cd(i+1);
        testmat.Draw("colz text");
        //TMatrixD mymatrix(nx+2,ny+2,h2D_gen_reco[i]->GetArray(),"F");
        //mymatrix.Draw("colz text");
        drawText("TMatrixD",0.2,0.2);
        TDecompSVD dsvd(testmat);
        cout << dsvd.Condition() << endl;
        c3->cd(nCENTBINS+i+1);
        gPad->SetLogy();
        gPad->SetLogx();
        h2D_gen_reco[i]->Draw("colz text");
        drawText("TH2D",0.2,0.2);
    }//centrality loop
    cout << "ss " << endl;
}
