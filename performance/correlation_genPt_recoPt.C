// Created : 2017 April 18
// Modified : 2017 May18
// Author : Yeonju Go
// 

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
bool isConsBin = false;
const int colHere[]={2,4,8,kYellow+2,kCyan+1};
const int markerStyle[]={20,33,22,23,22,29};
void correlation_genPt_recoPt(TString coll="pp", TString ver="180718_temp_v19", bool isFineBinning=false, bool doWeight=true){
    cout << " :::::: correlation_genPt_recoPt.C :::::: " << endl;
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);
    gStyle->SetPaintTextFormat(".2f");
    SetyjPadStyle();
    
    //import skimed tree
    const char* fname;
    if(coll=="pp"){ 
        fname=Form("%s",ppMCfname.Data());
    } else if(coll=="pbpb"){
        fname=Form("%s",pbpbMCfname.Data());
    }
    TChain* t1 = new TChain("EventTree");
    TChain* t1_skim = new TChain("skim");
    TChain* t1_evt = new TChain("HiEvt");
    TChain* t1_hlt = new TChain("hltTree");
    t1->Add(fname);
    t1_skim->Add(fname);
    t1_evt->Add(fname);
    t1_hlt->Add(fname);
    t1->AddFriend(t1_skim);
    t1->AddFriend(t1_evt);
    t1->AddFriend(t1_hlt);

    //define constants and histograms
    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1;
    Int_t nFineBin = 10;
    TString cap = Form("%s_pbpb",ver.Data());
    if(coll=="pp") cap= Form("%s_pp",ver.Data());
    if(isFineBinning) cap+=Form("_nFinePtBins%d",nFineBin);
    //cap += "_noRecoEcorrection";
   
    TH1D* h1D_pt[2][nCENTBINS]; // 0:gen 1:reco
    TH1D* h1D_pt_ratio[nCENTBINS]; // 0:gen 1:reco
    TH2F* h2D_gen_reco[nCENTBINS]; 
   // TMatrix mymatrix(nbinsx+2,nbinsy+2,myhisto.GetArray(),"F") 
    TString centSt[nCENTBINS];
    for(Int_t j=0;j<nCENTBINS;++j){
        centSt[j] = Form("cent%dto%d",(int)centBins_i[j]/2,(int)centBins_f[j]/2);
        if(isFineBinning) h2D_gen_reco[j] = new TH2F(Form("h2D_corr_gen_reco_%s",centSt[j].Data()),";Gen p_{T}^{#gamma} (GeV);Reco p_{T}^{#gamma} (GeV)",nFineBin,ptBins[0],ptBins[nPtBin],nFineBin,ptBins[0],ptBins[nPtBin]);
        else h2D_gen_reco[j] = new TH2F(Form("h2D_corr_gen_reco_%s",centSt[j].Data()),";Gen p_{T}^{#gamma} (GeV);Reco p_{T}^{#gamma} (GeV)",nPtBin,ptBins,nPtBin,ptBins);
        for(Int_t i=0;i<2;++i){
            if(isFineBinning) h1D_pt[i][j] = new TH1D(Form("h1D_pt_%d_%s",i,centSt[j].Data()),";p_{T}^{#gamma} (GeV);",nFineBin, ptBins[0],ptBins[nPtBin]);
            else h1D_pt[i][j] = new TH1D(Form("h1D_pt_%d_%s",i,centSt[j].Data()),";p_{T}^{#gamma} (GeV);Entries",nPtBin, ptBins);
        }
        h1D_pt_ratio[j] = (TH1D*) h1D_pt[0][j]->Clone(Form("h1D_pt_ratio_%s",centSt[j].Data()));
    }

    //Fill histograms
    for(Int_t i=0;i<nCENTBINS;++i){
        TCut centCut = Form("(hiBin>=%d)&&(hiBin<%d)",centBins_i[i],centBins_f[i]);
        TCut commonCut = centCut && phoSignalCut_mc;
        if(coll=="pp"){
            centCut = "hiBin>=-999"; 
            commonCut = centCut && phoSignalCut_pp_mc;
        }
        //h1D fineBinning
        if(doWeight)    t1->Draw(Form("%s>>%s","pho_genEt",h1D_pt[0][i]->GetName()), Form("(%s)*((%s) && (%s))","weight",mcIsolation.GetTitle(),commonCut.GetTitle()));
        else            t1->Draw(Form("%s>>%s","pho_genEt",h1D_pt[0][i]->GetName()), mcIsolation && commonCut);
        h1D_pt[0][i]=(TH1D*)gDirectory->Get(h1D_pt[0][i]->GetName());
       // if(doWeight)    t1->Draw(Form("%s>>%s","phoEt",h1D_pt[1][i]->GetName()), Form("(%s)*((%s) && (%s))","weight",mcIsolation.GetTitle(),commonCut.GetTitle()));
       // else            t1->Draw(Form("%s>>%s","phoEt",h1D_pt[1][i]->GetName()), mcIsolation && commonCut);
        if(doWeight)    t1->Draw(Form("%s>>%s","phoEtCorrected",h1D_pt[1][i]->GetName()), Form("(%s)*((%s) && (%s))","weight",mcIsolation.GetTitle(),commonCut.GetTitle()));
        else            t1->Draw(Form("%s>>%s","phoEtCorrected",h1D_pt[1][i]->GetName()), mcIsolation && commonCut);
        h1D_pt[1][i]=(TH1D*)gDirectory->Get(h1D_pt[1][i]->GetName());
        
        //h2D fineBinning
        if(doWeight)    t1->Draw(Form("%s:%s>>%s","phoEtCorrected","pho_genEt",h2D_gen_reco[i]->GetName()), Form("(%s)*((%s) && (%s))","weight",mcIsolation.GetTitle(),commonCut.GetTitle()));
        else            t1->Draw(Form("%s:%s>>%s","phoEtCorrected","pho_genEt",h2D_gen_reco[i]->GetName()), mcIsolation && commonCut);
        h2D_gen_reco[i]=(TH2F*)gDirectory->Get(h2D_gen_reco[i]->GetName());
        h1D_pt_ratio[i]->Divide(h1D_pt[1][i],h1D_pt[0][i]);
    }

    /////////////////////////////////////////////////////////////////////
    // DRAWING : h2D genPt vs. recoPt correlation : Centrality Dependence  
    cout << " DRAWING STARTS " << endl;
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/";
   
    TCanvas* c1 =new TCanvas(Form("c%d",1),"", 400*nCENTBINS,400);
    c1->Divide(nCENTBINS,1);
    for(Int_t i=0;i<nCENTBINS;++i){
        c1->cd(i+1);
        h2D_gen_reco[i]->Draw("colz text");
        //h2D_gen_reco[i]->GetYaxis()->SetTitleOffset(0.5);
        //h2D_gen_reco[i]->Draw("colz text");
        drawText(Form("%d-%d %%",(int)centBins_i[i]/2,(int)centBins_f[i]/2),0.2,1.0-c1->GetTopMargin()+0.06);
    }
    c1->SaveAs(Form("%sfigures/correlation_genPt_recoPt_2D_%s.pdf",dir.Data(),cap.Data()));
     
    /////////////////////////////////////////////////////////////////////
    // DRAWING : h1D pT distribution : Centrality Dependence  
    TCanvas* c2 =new TCanvas(Form("c%d",2),"", 400*nCENTBINS,400*2);
//    c2->Divide(nCENTBINS,2);
    makeMultiPanelCanvas(c2,nCENTBINS,2);
    TLegend* l1 = new TLegend(0.6,0.7,0.9,0.9);
    legStyle(l1);
    for(Int_t i=0;i<nCENTBINS;++i){
        c2->cd(i+1);
        SetHistTextSize(h1D_pt[1][i]);
        SetHistTextSize(h1D_pt[0][i]);
        h1D_pt[1][i]->GetXaxis()->CenterTitle();
        h1D_pt[1][i]->Scale(1.,"width");
        h1D_pt[0][i]->Scale(1.,"width");
        h1D_pt[0][i]->SetLineColor(4);
        h1D_pt[0][i]->SetLineColor(2);
        h1D_pt[1][i]->Draw("hist e");
        h1D_pt[0][i]->Draw("hist same e");
        gPad->SetLogy();
        if(i==0){
            l1->AddEntry(h1D_pt[0][i], "GEN", "l");
            l1->AddEntry(h1D_pt[1][i], "RECO", "l");
        }
        l1->Draw("same");
        drawText(Form("%d-%d %%",(int)centBins_i[i]/2,(int)centBins_f[i]/2),0.2,1.0-c1->GetTopMargin()-0.06);
        c2->cd(i+1+nCENTBINS);
        h1D_pt_ratio[i]->SetTitle(";p_{T}^{#gamma} (GeV);Reco p_{T}/Gen p_{T}");
        h1D_pt_ratio[i]->GetYaxis()->SetRangeUser(0.8,1.2);
        SetHistTextSize(h1D_pt_ratio[i]);
        h1D_pt_ratio[i]->Draw();
        jumSun(ptBins[0],1,ptBins[nPtBin],1);
    } 
    c2->SaveAs(Form("%sfigures/correlation_genPt_recoPt_1D_%s.pdf",dir.Data(),cap.Data()));
    
    /////////////////////////////////////////////////////////////////////
    // Write output file  
    TString outFname = Form("%soutput/correlation_genPt_recoPt_%s.root",dir.Data(),cap.Data());
    cout << "Write in the output file : "<< outFname << endl;
    TFile* fout = new TFile(outFname,"RECREATE");
    fout->cd();
    c1->Write();
    for(Int_t i=0;i<nCENTBINS;++i){
        h1D_pt[0][i]->Write();
        h1D_pt[1][i]->Write();
        h2D_gen_reco[i]->Write();
    }
    fout->Close();
}
