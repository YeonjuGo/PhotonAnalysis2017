// drawUnfoldingFigures.C 
// Author: Yeonju Go 
// Written at 2019 Feb 12
// Modified : 2019 Feb 12

#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TCut.h"
#include "TProfile.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TString.h"
#include "TMatrixD.h"
#include "TLatex.h"
#include "TSystem.h"
#include "stdio.h"
//#include "/home/goyeonju/unfolding/RooUnfold/src/RooUnfoldBayes.h"
//#include "/home/goyeonju/unfolding/RooUnfold/src/RooUnfoldResponse.h"
#include <iostream>
#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"

const TString LABEL = "PbPb #sqrt{s}_{_{NN}}=5.02 TeV";
const int colHere[]={1,2,4,kGreen+1,kYellow+1};
const int markerHere[]={22,28,24,28,28,28};
const int markerHere_closed[]={20,33,33,33,33};

//void drawUnfoldingFigures(TString ver="190303_temp_v28_sys_unfolding_iterative30", bool doSplitMC = true)
void drawUnfoldingFigures(TString ver="190303_temp_v28_sys_unfolding_svd10", bool doSplitMC = true)
{
    gSystem->Load("/home/goyeonju/unfolding/RooUnfold/libRooUnfold");
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0000);

    TString infname = Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/Unfold_%s.root",ver.Data());
    if(doSplitMC) infname = Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/Unfold_%s_splitMC.root",ver.Data());
    TString cap ="";
    if(doSplitMC) cap = "_splitMC";
    TFile* f_in = new TFile(Form("%s",infname.Data()));

    TH1D* h1D_pbpb[4][3][nCentBinIF]; // [0:data, 1:reco mc_genMatched 2:reco mc all, 3:gen mc][0:measured, 1:unfolded, 2:backfolded] // for gen, [2][0]: gen, [3][1]:nothing, [3][2]:folded gen
    TH1D* h1D_pp[4][3]; // 
    TH1D* ratio[4][3][nCentBinIF]; // unfolded/measured, backfolded/measured
    TH1D* ratio_pp[4][3]; // unfolded/measured, backfolded/measured

    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/";
    /////////////////////////////////////////////////////////
    // Get histograms
    cout << "Get Histograms after unfolding..." <<endl;
    for(int i=0;i<4;++i){
        for(int k=0;k<3;++k){
            //pbpb
            for(int j=0;j<nCentBinIF;++j)
            {
                TString histname = ""; 
                if(k==0){ //prior distribution
                    if(i==0) histname = Form("h1D_dNdpt_corr2_cent%d",j);      
                    else if(i==1) histname = Form("h1D_pt_reco_%d",j);      
                    else if(i==2) histname = Form("h1D_pt_reco_nm_%d",j);      
                    else if(i==3) histname = Form("h1D_pt_gen_%d",j);      
                    else histname = "";
                } else if(k==1){ //unfolded distribution
                    if(i==0) histname = Form("roounfold_res_%d_rd",j);      
                    else if(i==1) histname = Form("roounfold_res_%d_mc",j);      
                    else if(i==2) histname = Form("roounfold_res_%d_mc_nm",j);      
                    else if(i==3) histname = Form("h1D_pt_gen_%d",j);      
                    else histname = "";
                } else{ //backfolded distribution or folded distribution for gen
                    if(i==0) histname = Form("h1D_backFold_rd_%d",j);      
                    else if(i==1) histname = Form("h1D_backFold_mc_%d",j);      
                    else if(i==2) histname = Form("h1D_backFold_mc_nm_%d",j);      
                    else if(i==3) histname = Form("h1D_Fold_gen_%d",j);      
                    else histname = "";
                }

                if(histname==""){ cout << "ERROR :: THE HIST DOES NOT EXIST" << endl;
                }else{ 
                    h1D_pbpb[i][k][j] = (TH1D*) f_in->Get(histname.Data());
                    h1D_pbpb[i][k][j]->SetName(Form("h1D_pbpb_%d_%d_%d",i,k,j)); 
                    h1D_pbpb[i][k][j]->Scale(1.,"width");

                    //if(i==0){
                    //    h1D_pbpb[i][k][j]->Scale(1./TA[j]/nMB[j]);
                    //    h1D_pbpb[i][k][j]->Scale(1e12);
                    //    h1D_pbpb[i][k][j]->Scale(1./2.88);
                    //}else{
                    //    //h1D_pbpb[i][k][j]->Scale(1./h1D_pbpb[i][k][j]->Integral());
                    //}

                    h1D_pbpb[i][k][j]->SetMarkerStyle(markerHere[k]);
                    h1D_pbpb[i][k][j]->SetMarkerColor(colHere[k]);
                    h1D_pbpb[i][k][j]->SetLineColor(colHere[k]);
                    ratio[i][k][j] = (TH1D*) h1D_pbpb[i][k][j]->Clone(Form("ratio_pbpb_%d_%d_%d",i,k,j));
                    //ratio[i][k][j] = new TH1D(Form("ratio_pbpb_%d_%d_%d",i,k,j), "", nPtBin,ptBins_draw); 
                    if(k!=0) ratio[i][k][j]->Divide(h1D_pbpb[i][k][j],h1D_pbpb[i][0][j],1.,1.);

                }
            }
            //pp
            TString histname = ""; 
            if(k==0){ //prior distribution
                if(i==0) histname = "h1D_dNdpt_corr2_pp";      
                else if(i==1) histname = "h1D_pt_reco_pp";      
                else if(i==2) histname = "h1D_pt_reco_nm_pp";      
                else if(i==3) histname = "h1D_pt_gen_pp";      
                else histname = "";
            } else if(k==1){ //unfolded distribution
                if(i==0) histname = "roounfold_res_pp_rd_pp";      
                else if(i==1) histname = "roounfold_res_pp_mc_pp";      
                else if(i==2) histname = "roounfold_res_pp_mc_nm_pp";      
                else if(i==3) histname = "h1D_pt_gen_pp";      
                else histname = "";
            } else{ //backfolded distribution or folded distribution for gen
                if(i==0) histname = "h1D_backFold_rd_pp";      
                else if(i==1) histname = "h1D_backFold_mc_pp";      
                else if(i==2) histname = "h1D_backFold_mc_nm_pp";      
                else if(i==3) histname = "h1D_Fold_gen_pp";      
                else histname = "";
            }
            if(histname==""){ cout << "ERROR :: THE HIST DOES NOT EXIST" << endl;
            } else{ h1D_pp[i][k] = (TH1D*) f_in->Get(histname.Data());
                h1D_pp[i][k]->SetName(Form("h1D_pp_%d_%d",i,k)); 
                h1D_pp[i][k]->Scale(1.,"width");
                //if(i==0){
                //    h1D_pp[i][k]->Scale(1./lumi_pp);
                //    h1D_pp[i][k]->Scale(1e12);
                //    h1D_pp[i][k]->Scale(1./2.88);
                //}else{
                //    //h1D_pp[i][k]->Scale(1./h1D_pp[i][k]->Integral());
                //}
                h1D_pp[i][k]->SetMarkerStyle(markerHere[k]);
                h1D_pp[i][k]->SetMarkerColor(colHere[k]);
                h1D_pp[i][k]->SetLineColor(colHere[k]);
                //ratio_pp[i][k] = new TH1D(Form("ratio_pp_%d_%d",i,k), "", nPtBin,ptBins_draw); 
                ratio_pp[i][k] = (TH1D*) h1D_pp[i][k]->Clone(Form("ratio_pp_%d_%d",i,k));
                if(k!=0) ratio_pp[i][k]->Divide(h1D_pp[i][k],h1D_pp[i][0],1.,1.);
                //ratio_pp[i][k]->Divide(ratio_pp[i][0]);
            }
        }//k loop
    }//i loop

    /////////////////////////////////////////////////////////
    // Draw plots : PbPb 

    //TH1D* h1D_pbpb[4][3][nCentBinIF]; // [0:data, 1:reco mc_genMatched 2:reco mc all, 3:gen mc][0:measured, 1:unfolded, 2:backfolded] // for gen, [2][0]: gen, [3][1]:nothing, [3][2]:folded gen

    cout << "DRAW..." <<endl;
    TH1D* htemp_data = new TH1D("htemp_data",";E_{T}^{#gamma} (GeV);;", nPtBin_unfolding,ptBins_unfolding);
    htemp_data->GetYaxis()->SetRangeUser(1e-2,1e4);
    htemp_data->GetYaxis()->CenterTitle();
    TH1D* htemp = new TH1D("htemp",";E_{T}^{#gamma} (GeV);Entries;", nPtBin_unfolding,ptBins_unfolding);
    htemp->GetYaxis()->SetRangeUser(1e-2,1e4);
    htemp->GetYaxis()->CenterTitle();
    TH1D* htemp_ratio = new TH1D("htemp_ratio",";E_{T}^{#gamma} (GeV);Ratio;", nPtBin_unfolding,ptBins_unfolding);
    htemp_ratio->GetYaxis()->SetRangeUser(0.8,1.2);
    htemp_ratio->GetYaxis()->CenterTitle();
    TCanvas* ctot[nCentBinIF];

    TH1D* ratio_extra[5][nCentBinIF];
    for(int i=0;i<5;++i){
    for(int j=0;j<nCentBinIF;++j){
        ratio_extra[i][j] = new TH1D(Form("ratio_extra_%d_%d",i,j),"",nPtBin_unfolding, ptBins_unfolding);
    }}

    //pbpb
    TLegend* l1 = new TLegend(0.4742479,0.6763028,0.9351224,0.8916344);
    legStyle(l1);
    l1->AddEntry(h1D_pbpb[0][0][0],"Measured DATA", "l");
    l1->AddEntry(h1D_pbpb[0][1][0],"Unfolded DATA", "pl");
    l1->AddEntry(h1D_pbpb[0][2][0],"Backfolded DATA", "pl");
    
    TLegend* l2 = new TLegend(0.4742479,0.6763028,0.9351224,0.8916344);
    legStyle(l2);
    l2->AddEntry(h1D_pbpb[1][0][0],"Reco MC", "l");
    l2->AddEntry(h1D_pbpb[1][1][0],"Unfolded Reco MC", "pl");
    l2->AddEntry(h1D_pbpb[1][2][0],"Backfolded Reco MC", "pl");
    l2->AddEntry(h1D_pbpb[3][0][0],"Gen MC", "pl");

    TLegend* l3 = new TLegend(0.4742479,0.6763028,0.9351224,0.8916344);
    //TLegend* l3 = new TLegend(0.6,0.65,0.8,0.89);
    legStyle(l3);
    l3->AddEntry(h1D_pbpb[3][0][0],"Gen MC", "l");
    l3->AddEntry(h1D_pbpb[3][2][0],"Folded Gen MC", "pl");
    l3->AddEntry(h1D_pbpb[1][0][0],"Reco MC", "pl");
    
    TLegend* l4 = new TLegend(0.3508152,0.727444,0.9235783,0.8916344);
    //TLegend* l4 = new TLegend(0.4,0.75,0.9,0.89);
    legStyle(l4);
    l4->AddEntry(ratio[0][1][0],"Unfolded DATA / Measured DATA", "pl");
    l4->AddEntry(ratio[0][2][0],"Backfolded DATA / Measured DATA", "pl");
    
    TLegend* l5 = new TLegend(0.3508152,0.727444,0.9235783,0.8916344);
    legStyle(l5);
    l5->AddEntry(ratio[1][1][0],"Unfolded Reco MC / Reco MC", "pl");
    l5->AddEntry(ratio[1][2][0],"Backfolded Reco MC / Reco MC", "pl");
    l5->AddEntry(ratio_extra[0][0],"Unfolded Reco MC / Gen MC", "pl");

    TLegend* l6 = new TLegend(0.3508152,0.727444,0.9235783,0.8916344);
    legStyle(l6);
    l6->AddEntry(ratio[3][2][0],"Folded Gen MC / Gen MC", "pl");
    l6->AddEntry(ratio_extra[1][0],"Folded Gen MC / Reco MC", "pl");
    for(int j=0;j<nCentBinIF;++j){
        ctot[j] = new TCanvas(Form("ctot%d",j),"",400*3,400*2);
        ctot[j]->Divide(3,2);

        /////////////////////////////////////////////
        // SPECTRA 
        ctot[j]->cd(1); // DATA
        gPad->SetLogy();
        htemp_data->DrawCopy();
        for(int k=0;k<3;++k){
            //cout << k << "   " << h1D_pbpb[0][k][j]->GetBinContent(2) << endl;
            if(k==0) h1D_pbpb[0][k][j]->DrawCopy("same hist");
            else h1D_pbpb[0][k][j]->DrawCopy("same");
        }
        l1->Draw("same");
        drawText("DATA",0.2,0.2+0.05);
        drawText(Form("%d%s-%d%s",centBins_i[j]/2,"%",centBins_f[j]/2,"%"),0.2,0.2);
        drawText(Form("%s",ver.Data()),0.2,0.2-0.05);

        ctot[j]->cd(2); // MC
        gPad->SetLogy();
        htemp->DrawCopy();
        for(int k=0;k<3;++k){
            if(k==0) h1D_pbpb[1][k][j]->DrawCopy("same hist");
            else h1D_pbpb[1][k][j]->DrawCopy("same");
        }
        l2->Draw("same");
        h1D_pbpb[3][0][j]->Draw("same"); //gen dist
        drawText("MC RECO",0.2,0.2+0.05);

        ctot[j]->cd(3); // MC gen
        gPad->SetLogy();
        htemp->DrawCopy();
        h1D_pbpb[3][0][j]->DrawCopy("same hist");
        h1D_pbpb[3][2][j]->DrawCopy("same");
        h1D_pbpb[1][0][j]->DrawCopy("same"); //reco
        l3->Draw("same");
        drawText("GEN",0.2,0.2+0.05);

        /////////////////////////////////////////////
        // RATIO 
        ctot[j]->cd(4); // DATA
        htemp_ratio->Draw();

        for(int k=1;k<3;++k){
            ratio[0][k][j]->Draw("same");
        }
        jumSun(ptBins_unfolding[0],1,ptBins_unfolding[nPtBin_unfolding],1);
        l4->Draw("same");

        ctot[j]->cd(5); // MC
        htemp_ratio->Draw();
        for(int k=1;k<3;++k){
            ratio[1][k][j]->Draw("same");
        }
        ratio_extra[0][j]->Divide(h1D_pbpb[1][1][j],h1D_pbpb[3][0][j]);// reco_unfolded/gen
        ratio_extra[0][j]->SetMarkerStyle(markerHere[0]);
        //ratio_extra[0][j]->SetMarkerColor(kYellow);
        ratio_extra[0][j]->DrawCopy("same");
        jumSun(ptBins_unfolding[0],1,ptBins_unfolding[nPtBin_unfolding],1);
        l5->Draw("same");

        ctot[j]->cd(6); // MC
        htemp_ratio->Draw();
        ratio[3][2][j]->Draw("same");// folded_gen/gen
        ratio_extra[1][j]->Divide(h1D_pbpb[3][2][j],h1D_pbpb[1][0][j]);// folded_gen/reco
        ratio_extra[1][j]->SetMarkerStyle(markerHere[0]);
        ratio_extra[1][j]->DrawCopy("same");
        jumSun(ptBins_unfolding[0],1,ptBins_unfolding[nPtBin_unfolding],1);
        l6->Draw("same");
    
        ctot[j]->SaveAs(Form("%sfigures/unfoldingFigures_%s_cent%dto%d%s.pdf",dir.Data(),ver.Data(),centBins_i[j]/2,centBins_f[j]/2,cap.Data()));

    }

    /////////////////////////////////////////////////////////
    // Draw plots : pp
    //
    htemp->GetYaxis()->SetRangeUser(1e-1,1e4);
    htemp_ratio->GetYaxis()->SetRangeUser(0.8,1.2);

    cout << "DRAW pp..." <<endl;
    TCanvas* ctot_pp= new TCanvas("ctot_pp","",400*3,400*2);
    ctot_pp->Divide(3,2);

    /////////////////////////////////////////////
    // SPECTRA 
    ctot_pp->cd(1); // DATA
    gPad->SetLogy();
    htemp_data->Draw();
    for(int k=0;k<3;++k){
        if(k==0) h1D_pp[0][k]->DrawCopy("same hist");
        else h1D_pp[0][k]->DrawCopy("same");
    }
    l1->Draw("same");
    drawText("DATA pp",0.2,0.2+0.05);

    ctot_pp->cd(2); // MC
    gPad->SetLogy();
    htemp->Draw();
    for(int k=0;k<3;++k){
        if(k==0) h1D_pp[1][k]->DrawCopy("same hist");
        else h1D_pp[1][k]->DrawCopy("same");
    }
    h1D_pp[3][0]->Draw("same"); //gen dist
    drawText("MC RECO",0.2,0.2+0.05);
    l2->Draw("same");

    ctot_pp->cd(3); // MC gen
    gPad->SetLogy();
    htemp->Draw();
    h1D_pp[3][0]->DrawCopy("same hist");
    h1D_pp[3][2]->DrawCopy("same");
    h1D_pp[1][0]->DrawCopy("same"); //reco
    drawText("GEN",0.2,0.2+0.05);
    l3->Draw("same");

    /////////////////////////////////////////////
    // RATIO 
    ctot_pp->cd(4); // DATA
    htemp_ratio->Draw();

    for(int k=1;k<3;++k){
        ratio_pp[0][k]->Draw("same p");
    }
    jumSun(ptBins_unfolding[0],1,ptBins_unfolding[nPtBin_unfolding],1);
    l4->Draw("same");

    ctot_pp->cd(5); // MC
    htemp_ratio->Draw();
    for(int k=1;k<3;++k){
        ratio_pp[1][k]->Draw("same p");
    }
    ratio_extra[2][0]->Divide(h1D_pp[1][1],h1D_pp[3][0]);// reco_unfolded/gen
    ratio_extra[2][0]->SetMarkerStyle(markerHere[0]);
    ratio_extra[2][0]->DrawCopy("same p");
    jumSun(ptBins_unfolding[0],1,ptBins_unfolding[nPtBin_unfolding],1);
    l5->Draw("same");

    ctot_pp->cd(6); // MC
    htemp_ratio->Draw();
    ratio_pp[3][2]->Draw("same p");// folded_gen/gen
    ratio_extra[3][0]->Divide(h1D_pp[3][2],h1D_pp[1][0]);// folded_gen/reco
    ratio_extra[3][0]->SetMarkerStyle(markerHere[0]); 
    ratio_extra[3][0]->DrawCopy("same p");
    jumSun(ptBins_unfolding[0],1,ptBins_unfolding[nPtBin_unfolding],1);
    l6->Draw("same");

    ctot_pp->SaveAs(Form("%sfigures/unfoldingFigures_%s_pp%s.pdf",dir.Data(),ver.Data(),cap.Data()));

}
