// Created : 2019 July 31

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
const int colHere[]={2,4,8,kYellow+2,kCyan+1};
const int markerStyle[]={20,33,22,23,22,29};
double assym_gaus(double *x, double *par) {
   double mean = par[0];
   double sigmal = par[1];
   double sigmah = par[2];

   // beware, sometimes one of the two parameters is 0... that's bad
   if (sigmal<1e-3) sigmal = max(1e-3, sigmah);
   if (sigmah<1e-3) sigmah = max(1e-3, sigmal);

   if ((x[0] < mean))
      return TMath::Gaus(x[0],mean,sigmal,kTRUE);
   else
      return TMath::Gaus(x[0],mean,sigmah,kTRUE);
};

void toyStudy(TH2D* h2D_org, TH2D* h2D_toy);
void RM_percent(TH2D* h2D_org, TH2D* h2D_percent);

void toyStudy_responseMatrix(TString coll="pbpb", TString ver="190703_temp_v31_sys_MCsize", bool splitMC=false, bool isFineBinning=false, bool doWeight=true){
    cout << " :::::: toyStudy_responseMatrix :::::: " << endl;
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);
    gStyle->SetPaintTextFormat(".2f");
    SetyjPadStyle();
    
    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1;
    
    TString subver = ver(0,16);
    cout << subver << endl;
    TString cap = Form("%snominal_pbpb",subver.Data());
    if(coll=="pp") cap= Form("%snominal_pp",subver.Data());
    if(!doWeight) cap+=Form("_%s","noWeight");
    if(splitMC) cap+=Form("_%s","splitMC");
    
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/";
    TString inFname = Form("%soutput/correlation_genPt_recoPt_%s.root",dir.Data(),cap.Data());
    TFile* fin = new TFile(inFname);
    TH1D* h1D_pt[4][nCENTBINS]; // 0:gen reco-matched 2:reco gen-matched 3:reco not gen-matched 4: gen not reco-matched
    TH2D* h2D_gen_reco[nCENTBINS]; 
    TH2D* h2D_gen_reco_percent[nCENTBINS]; 
    TH2D* h2D_gen_reco_toy[nCENTBINS]; 
    TH2D* h2D_gen_reco_percent_toy[nCENTBINS]; 
    TString centSt[nCENTBINS]; 
    for(Int_t j=0;j<nCENTBINS;++j){
        centSt[j] = Form("cent%dto%d",(int)centBins_i[j]/2,(int)centBins_f[j]/2);
        cout << centSt[j] << endl;
        for(Int_t i=0;i<4;++i){ /// 0:gen reco-matched 1: gen not reco-matched 2:reco gen-matched 3:reco not gen-matched
            h1D_pt[i][j] = (TH1D*) fin->Get(Form("h1D_pt_%d_%s",i,centSt[j].Data()));
        }
        h2D_gen_reco[j] = (TH2D*) fin->Get(Form("h2D_corr_gen_reco_%s",centSt[j].Data())); 
        h2D_gen_reco[j]->SetName(Form("%s_original",h2D_gen_reco[j]->GetName())); 
        h2D_gen_reco_percent[j] = (TH2D*) fin->Get(Form("h2D_corr_gen_reco_%s",centSt[j].Data())); 
        //h2D_gen_reco_percent[j] = (TH2D*) fin->Get(Form("h2D_corr_gen_reco_percent_%s",centSt[j].Data())); 
        h2D_gen_reco_percent[j]->SetName(Form("%s_original",h2D_gen_reco_percent[j]->GetName())); 
        //h2D_gen_reco_percent[j]->SetName(Form("h2D_corr_gen_reco_original_percent_%s",centSt[j].Data())); 

        h2D_gen_reco_toy[j] = (TH2D*) h2D_gen_reco[j]->Clone(Form("h2D_corr_gen_reco_%s",centSt[j].Data())); 
        h2D_gen_reco_percent_toy[j] = (TH2D*) h2D_gen_reco_percent[j]->Clone(Form("h2D_corr_gen_reco_percent_%s",centSt[j].Data())); 
        toyStudy(h2D_gen_reco[j],h2D_gen_reco_toy[j]);
        RM_percent(h2D_gen_reco_toy[j],h2D_gen_reco_percent_toy[j]);
    }

    cap = Form("%s_pbpb",ver.Data());
    if(coll=="pp") cap= Form("%s_pp",ver.Data());
    if(!doWeight) cap+=Form("_%s","noWeight");
    if(splitMC) cap+=Form("_%s","splitMC");
    TString outFname = Form("%soutput/correlation_genPt_recoPt_%s.root",dir.Data(),cap.Data());
    TFile* fout = new TFile(outFname,"RECREATE");
    fout->cd();

    /////////////////////////////////////////////////////////////////////
    // DRAWING : h2D genPt vs. recoPt correlation with percent : Response matrix
    //gStyle->SetPaintTextFormat("4.2f");
    TCanvas* c3 =new TCanvas(Form("c%d",3),"", 400*nCENTBINS,400);
    c3->Divide(nCENTBINS,1);
    for(Int_t i=0;i<nCENTBINS;++i){
        c3->cd(i+1);
        gPad->SetLogy();
        gPad->SetLogx();
        h2D_gen_reco_percent_toy[i]->Draw("colz text");
        //h2D_gen_reco[i]->GetYaxis()->SetTitleOffset(0.5);
        //h2D_gen_reco[i]->Draw("colz text");
        drawText(Form("%s",coll.Data()),0.2,1.0-c3->GetTopMargin()-0.06);
    }
    c3->SaveAs(Form("%sfigures/correlation_genPt_recoPt_2D_percent_%s.pdf",dir.Data(),cap.Data()));

    TCanvas* c3_each[nCENTBINS];
    for(Int_t i=0;i<nCENTBINS;++i){
        if(coll!="pp"){
            drawText(Form("%d-%d %%",(int)centBins_i[i]/2,(int)centBins_f[i]/2),0.2,1.0-c3->GetTopMargin()-0.06-0.05);
            c3_each[i] = new TCanvas(Form("c3_each_cent%d",i),"", 400,400);
            gPad->SetLogy();
            gPad->SetLogx();
            h2D_gen_reco_percent_toy[i]->Draw("colz text");
            drawText(Form("%d-%d %%",(int)centBins_i[i]/2,(int)centBins_f[i]/2),0.2,1.0-c3->GetTopMargin()-0.06);
            c3_each[i]->SaveAs(Form("%sfigures/correlation_genPt_recoPt_2D_percent_%s_cent%d.pdf",dir.Data(),cap.Data(),i));
        }
    }

    for(Int_t i=0;i<nCENTBINS;++i){
        h1D_pt[0][i]->Write();
        h1D_pt[1][i]->Write();
        h1D_pt[2][i]->Write();
        h1D_pt[3][i]->Write();
        //h1D_pt_ratio[i]->Write();
        //h1D_pt_ratio_error[i]->Write();
        h2D_gen_reco[i]->Write();
        h2D_gen_reco_percent[i]->Write();
        h2D_gen_reco_toy[i]->Write();
        h2D_gen_reco_percent_toy[i]->Write();
    }
    fout->Close();

} 
void toyStudy(TH2D* h2D_org, TH2D* h2D_toy){
    for(int ii=0; ii<h2D_org->GetNbinsX();++ii){
        for(int jj=0; jj<h2D_org->GetNbinsY();++jj){
            double tempVal = h2D_org->GetBinContent(ii,jj);
            double tempErr = h2D_org->GetBinError(ii,jj);
            if(tempVal==0){
                cout << "Bin number x = "<< ii << ", y = " << jj << " : no entries " << endl;
                h2D_toy->SetBinContent(ii,jj,tempVal);
                h2D_toy->SetBinError(ii,jj,tempErr);
            } else{ 
                TF1 *tfAsyGauss = new TF1("tfAsy",assym_gaus,tempVal-tempErr*10,tempVal+tempErr*10,3);
                tfAsyGauss->SetParameters(tempVal,tempErr,tempErr);
                double toyVal = tfAsyGauss->GetRandom(); 
                cout << "Bin number x = "<< ii << ", y = " << jj << " : bin value = " << tempVal << ", bin error = " << tempErr << ", toy value = " << toyVal << endl; 
                toyVal = tfAsyGauss->GetRandom(); 
                cout << "Bin number x = "<< ii << ", y = " << jj << " : bin value = " << tempVal << ", bin error = " << tempErr << ", toy value = " << toyVal << endl; 
                toyVal = tfAsyGauss->GetRandom(); 
                cout << "Bin number x = "<< ii << ", y = " << jj << " : bin value = " << tempVal << ", bin error = " << tempErr << ", toy value = " << toyVal << endl; 
                toyVal = tfAsyGauss->GetRandom(); 
                cout << "Bin number x = "<< ii << ", y = " << jj << " : bin value = " << tempVal << ", bin error = " << tempErr << ", toy value = " << toyVal << endl; 
                toyVal = tfAsyGauss->GetRandom(); 
                h2D_toy->SetBinContent(ii,jj,TMath::Abs(toyVal));
                h2D_toy->SetBinError(ii,jj,tempErr);
                delete tfAsyGauss;
            }
        }
    }
}

void RM_percent(TH2D* h2D_org, TH2D* h2D_percent){
    for(int ypt=1; ypt<=h2D_org->GetNbinsY(); ++ypt){
        int totEvtInAbin = 0;
        for(int xpt=1; xpt<=h2D_org->GetNbinsX(); ++xpt)
            totEvtInAbin += h2D_org->GetBinContent(xpt,ypt);

        for(int xpt=1; xpt<=h2D_org->GetNbinsX(); ++xpt){
            int evtInAbin = h2D_org->GetBinContent(xpt,ypt);
            double percent = 0;
            percent = (double)evtInAbin/(double)totEvtInAbin;
            h2D_percent->SetBinContent(xpt,ypt,percent);
            h2D_percent->SetBinError(xpt,ypt,0);
            cout << "Bin number x = "<< xpt << ", y = " << ypt << " : event N = " << evtInAbin<< ", tot N = " << totEvtInAbin << ", percent = " << percent << endl; 
        }//x loop
    }//y loop
}
