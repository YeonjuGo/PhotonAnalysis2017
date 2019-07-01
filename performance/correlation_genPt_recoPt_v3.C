// Created : 2017 April 18
// Modified : 2019 June 24
// Author : Yeonju Go
// to have centrality dependenct matrix binning 
// ex) matrix in 30-50% has pt binning up to 200 GeV while some others have up to 300 GeV 

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
bool isConsBin = false;
const int colHere[]={2,4,8,kYellow+2,kCyan+1};
const int markerStyle[]={20,33,22,23,22,29};
void correlation_genPt_recoPt_v3(TString coll="pp", TString ver="190625_temp_v29_nominal", bool splitMC=false, bool isFineBinning=false, bool doWeight=true){
    cout << " :::::: correlation_genPt_recoPt.C :::::: " << endl;
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
    TChain* t1 = new TChain("EventTree");
    TChain* t1_skim = new TChain("skim");
    TChain* t1_evt = new TChain("HiEvt");
    TChain* t1_hlt = new TChain("hltTree");
    if(!splitMC){
        t1->Add(fname);
        t1_skim->Add(fname);
        t1_evt->Add(fname);
        t1_hlt->Add(fname);
    }
    t1->AddFriend(t1_skim);
    t1->AddFriend(t1_evt);
    t1->AddFriend(t1_hlt);
    int totEntry = t1->GetEntries();
    
    string str = fname; 
    str = str.substr(0, str.size()-5);
    cout << str << endl;
    str += "_splitMC_even_odd.root";
    cout << str << endl;
    const char* fname_splitMC = str.c_str();
    TChain* t1_even = new TChain("EventTree_even");
    TChain* t1_skim_even = new TChain("skim_even");
    TChain* t1_evt_even = new TChain("HiEvt_even");
    TChain* t1_hlt_even = new TChain("hltTree_even");
    TChain* t1_odd = new TChain("EventTree_odd");
    TChain* t1_skim_odd = new TChain("skim_odd");
    TChain* t1_evt_odd = new TChain("HiEvt_odd");
    TChain* t1_hlt_odd = new TChain("hltTree_odd");
    if(splitMC){
        t1_even->Add(fname_splitMC);
        t1_skim_even->Add(fname_splitMC);
        t1_evt_even->Add(fname_splitMC);
        t1_hlt_even->Add(fname_splitMC);
        t1_odd->Add(fname_splitMC);
        t1_skim_odd->Add(fname_splitMC);
        t1_evt_odd->Add(fname_splitMC);
        t1_hlt_odd->Add(fname_splitMC);
    }
    t1_even->AddFriend(t1_skim_even);
    t1_even->AddFriend(t1_hlt_even);
    t1_even->AddFriend(t1_evt_even);
    t1_odd->AddFriend(t1_skim_odd);
    t1_odd->AddFriend(t1_hlt_odd);
    t1_odd->AddFriend(t1_evt_odd);

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
    //cap += "_noRecoEcorrection";
   
    cout << "Define histograms" << endl;
    TH1D* h1D_pt[4][nCENTBINS]; // 0:gen reco-matched 2:reco gen-matched 3:reco not gen-matched 4: gen not reco-matched
    TH1D* h1D_pt_ratio[nCENTBINS]; // 0:gen 1:reco
    TH1D* h1D_pt_ratio_error[nCENTBINS]; // 0:gen 1:reco
    TH2D* h2D_gen_reco[nCENTBINS]; 
    TH2D* h2D_gen_reco_percent[nCENTBINS]; 
   // TMatrix mymatrix(nbinsx+2,nbinsy+2,myhisto.GetArray(),"F") 
    TString centSt[nCENTBINS];
    for(Int_t j=0;j<nCENTBINS;++j){
        centSt[j] = Form("cent%dto%d",(int)centBins_i[j]/2,(int)centBins_f[j]/2);

        // rebin ptbins for each centrality bins since we have less bins for peripheral region 
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[j];
        double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
            ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
        }
        
        if(isFineBinning) h2D_gen_reco[j] = new TH2D(Form("h2D_corr_gen_reco_%s",centSt[j].Data()),";Gen p_{T}^{#gamma} (GeV);Reco p_{T}^{#gamma} (GeV)",nFineBin,ptBins[0],ptBins[nPtBin],nFineBin,ptBins[0],ptBins[nPtBin]);
        else h2D_gen_reco[j] = new TH2D(Form("h2D_corr_gen_reco_%s",centSt[j].Data()),";Reco p_{T}^{#gamma} (GeV);Gen p_{T}^{#gamma} (GeV)",nPtBin_unfolding_centDep,ptBins_unfolding_centDep,nPtBin_unfolding_centDep,ptBins_unfolding_centDep);
        h2D_gen_reco_percent[j] = (TH2D*) h2D_gen_reco[j]->Clone(Form("h2D_corr_gen_reco_percent_%s",centSt[j].Data()));

        for(Int_t i=0;i<4;++i){ /// 0:gen reco-matched 1: gen not reco-matched 2:reco gen-matched 3:reco not gen-matched
            if(isFineBinning) h1D_pt[i][j] = new TH1D(Form("h1D_pt_%d_%s",i,centSt[j].Data()),";p_{T}^{#gamma} (GeV);",nFineBin, ptBins[0],ptBins[nPtBin]);
            else h1D_pt[i][j] = new TH1D(Form("h1D_pt_%d_%s",i,centSt[j].Data()),";p_{T}^{#gamma} (GeV);Entries",nPtBin_unfolding_centDep, ptBins_unfolding_centDep);
        }
        h1D_pt_ratio[j] = (TH1D*) h1D_pt[0][j]->Clone(Form("h1D_pt_ratio_%s",centSt[j].Data()));
    }

    cout << "Fill histograms" << endl;
    if(splitMC==0){
        //Fill histograms
        cout << "no split MC" << endl;
        for(Int_t i=0;i<nCENTBINS;++i){
            TCut centCut = Form("(hiBin>=%d)&&(hiBin<%d)",centBins_i[i],centBins_f[i]);
            TCut commonCut = centCut && phoSignalCut_mc;
            if(coll=="pp"){
                centCut = "hiBin>=-999"; 
                commonCut = centCut && phoSignalCut_pp_mc;
            }
            //gen (matched)
            if(doWeight)    t1->Draw(Form("%s>>%s","pho_genEt",h1D_pt[0][i]->GetName()), Form("(%s)*((%s) && (%s))","weight",mcIsolation.GetTitle(),commonCut.GetTitle())); //h1D fineBinning
            else            t1->Draw(Form("%s>>%s","pho_genEt",h1D_pt[0][i]->GetName()), mcIsolation && commonCut);
            h1D_pt[0][i]=(TH1D*)gDirectory->Get(h1D_pt[0][i]->GetName());
            // if(doWeight)    t1->Draw(Form("%s>>%s","phoEt",h1D_pt[1][i]->GetName()), Form("(%s)*((%s) && (%s))","weight",mcIsolation.GetTitle(),commonCut.GetTitle()));
            // else            t1->Draw(Form("%s>>%s","phoEt",h1D_pt[1][i]->GetName()), mcIsolation && commonCut);
            //reco (matched)
            if(doWeight)    t1->Draw(Form("%s>>%s","phoEtCorrected",h1D_pt[1][i]->GetName()), Form("(%s)*((%s) && (%s))","weight",mcIsolation.GetTitle(),commonCut.GetTitle()));
            else            t1->Draw(Form("%s>>%s","phoEtCorrected",h1D_pt[1][i]->GetName()), mcIsolation && commonCut);
            h1D_pt[1][i]=(TH1D*)gDirectory->Get(h1D_pt[1][i]->GetName());

            //reco (total, non-matched)
            if(doWeight)    t1->Draw(Form("%s>>%s","phoEtCorrected",h1D_pt[2][i]->GetName()), Form("(%s)*((%s))","weight",commonCut.GetTitle()));
            else            t1->Draw(Form("%s>>%s","phoEtCorrected",h1D_pt[2][i]->GetName()), commonCut);
            h1D_pt[2][i]=(TH1D*)gDirectory->Get(h1D_pt[2][i]->GetName());

            //gen (total, non-matched)
            if(doWeight)    t1->Draw(Form("%s>>%s","mcEt",h1D_pt[3][i]->GetName()), Form("(%s)*((%s)*(%s))","weight",mcIsolation_nm.GetTitle(),centCut.GetTitle()));
            else            t1->Draw(Form("%s>>%s","mcEt",h1D_pt[3][i]->GetName()), mcIsolation_nm && centCut);
            h1D_pt[3][i]=(TH1D*)gDirectory->Get(h1D_pt[3][i]->GetName());

            //h2D fineBinning
            if(doWeight)    t1->Draw(Form("%s:%s>>%s","pho_genEt","phoEtCorrected",h2D_gen_reco[i]->GetName()), Form("(%s)*((%s) && (%s))","weight",mcIsolation.GetTitle(),commonCut.GetTitle()));
            else            t1->Draw(Form("%s:%s>>%s","pho_genEt","phoEtCorrected",h2D_gen_reco[i]->GetName()), mcIsolation && commonCut);
            //if(doWeight)    t1->Draw(Form("%s:%s>>%s","phoEtCorrected","pho_genEt",h2D_gen_reco[i]->GetName()), Form("(%s)*((%s) && (%s))","weight",mcIsolation.GetTitle(),commonCut.GetTitle()));
            //else            t1->Draw(Form("%s:%s>>%s","phoEtCorrected","pho_genEt",h2D_gen_reco[i]->GetName()), mcIsolation && commonCut);
            h2D_gen_reco[i]=(TH2D*)gDirectory->Get(h2D_gen_reco[i]->GetName());

            h1D_pt_ratio[i]->Divide(h1D_pt[1][i],h1D_pt[0][i]);
            h1D_pt_ratio_error[i] = getRatioErrorHist_completelyCorrelated(h1D_pt_ratio[i],h1D_pt[1][i],h1D_pt[0][i]); 
        }
    } else{
        //Fill histograms
        cout << "split MC! half of MC stats are used for response matrix and the others for h1D histograms" << endl;
        cout << "split MC! this can be used for closure test, making statistical fluctuation" << endl;
        for(Int_t i=0;i<nCENTBINS;++i){
            TCut centCut = Form("(hiBin>=%d)&&(hiBin<%d)",centBins_i[i],centBins_f[i]);
            TCut commonCut = centCut && phoSignalCut_mc;
            if(coll=="pp"){
                centCut = "hiBin>=-999"; 
                commonCut = centCut && phoSignalCut_pp_mc;
            }
            TCut evenEntryCut = "Entry$%2==0";
            TCut oddEntryCut = "Entry$%2!=0";
            //gen (matched)
            cout << "centCut = " << centCut.GetTitle() << endl;
            cout << "Draw gen dist (matched), only even entries" << endl;
            if(doWeight)    t1_even->Draw(Form("%s>>%s","pho_genEt",h1D_pt[0][i]->GetName()), Form("(%s)*((%s) && (%s))","weight",mcIsolation.GetTitle(),commonCut.GetTitle())); //h1D fineBinning
            else            t1_even->Draw(Form("%s>>%s","pho_genEt",h1D_pt[0][i]->GetName()), mcIsolation && commonCut);
            h1D_pt[0][i]=(TH1D*)gDirectory->Get(h1D_pt[0][i]->GetName());
            //reco (matched)
            cout << "Draw reco dist (matched), only even entries" << endl;
            if(doWeight)    t1_even->Draw(Form("%s>>%s","phoEtCorrected",h1D_pt[1][i]->GetName()), Form("(%s)*((%s) && (%s))","weight",mcIsolation.GetTitle(),commonCut.GetTitle()));
            else            t1_even->Draw(Form("%s>>%s","phoEtCorrected",h1D_pt[1][i]->GetName()), mcIsolation && commonCut);
            h1D_pt[1][i]=(TH1D*)gDirectory->Get(h1D_pt[1][i]->GetName());

            //reco (total, non-matched)
            cout << "Draw total reco dist (matched)" << endl;
            if(doWeight)    t1->Draw(Form("%s>>%s","phoEtCorrected",h1D_pt[2][i]->GetName()), Form("(%s)*((%s))","weight",commonCut.GetTitle()));
            else            t1->Draw(Form("%s>>%s","phoEtCorrected",h1D_pt[2][i]->GetName()), commonCut);
            h1D_pt[2][i]=(TH1D*)gDirectory->Get(h1D_pt[2][i]->GetName());

            //gen (total, non-matched)
            cout << "Draw total gen dist (matched)" << endl;
            if(doWeight)    t1->Draw(Form("%s>>%s","mcEt",h1D_pt[3][i]->GetName()), Form("(%s)*((%s)*(%s))","weight",mcIsolation_nm.GetTitle(),centCut.GetTitle()));
            else            t1->Draw(Form("%s>>%s","mcEt",h1D_pt[3][i]->GetName()), mcIsolation_nm && centCut);
            h1D_pt[3][i]=(TH1D*)gDirectory->Get(h1D_pt[3][i]->GetName());

            //h2D fineBinning
            cout << "Draw response matrix (matched), only odd entries" << endl;
            if(doWeight)    t1_odd->Draw(Form("%s:%s>>%s","pho_genEt","phoEtCorrected",h2D_gen_reco[i]->GetName()), Form("(%s)*((%s) && (%s))","weight",mcIsolation.GetTitle(),commonCut.GetTitle()));
            else            t1_odd->Draw(Form("%s:%s>>%s","pho_genEt","phoEtCorrected",h2D_gen_reco[i]->GetName()), mcIsolation && commonCut);
            h2D_gen_reco[i]=(TH2D*)gDirectory->Get(h2D_gen_reco[i]->GetName());
            h1D_pt_ratio[i]->Divide(h1D_pt[1][i],h1D_pt[0][i]);
            //h1D_pt_ratio_error[i] = getRatioErrorHist_completelyCorrelated(h1D_pt_ratio[i],h1D_pt[1][i],h1D_pt[0][i]); 
        }
    }

    /////////////////////////////////////////////////////////////////////
    // Write output file  
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/";
    TString outFname = Form("%soutput/correlation_genPt_recoPt_%s.root",dir.Data(),cap.Data());
    //if(splitMC) outFname = Form("%soutput/correlation_genPt_recoPt_%s_splitMC.root",dir.Data(),cap.Data()); 
    cout << "Write in the output file : "<< outFname << endl;
    TFile* fout = new TFile(outFname,"RECREATE");
    fout->cd();
    //c1->Write();
    for(Int_t i=0;i<nCENTBINS;++i){
        h1D_pt[0][i]->Write();
        h1D_pt[1][i]->Write();
        h1D_pt[2][i]->Write();
        h1D_pt[3][i]->Write();
        h1D_pt_ratio[i]->Write();
        //h1D_pt_ratio_error[i]->Write();
        h2D_gen_reco[i]->Write();
        h2D_gen_reco_percent[i]->Write();
    }
    fout->Close();

    
    cout << " DRAWING STARTS " << endl;
    /////////////////////////////////////////////////////////////////////
    // DRAWING : h1D pT distribution : Centrality Dependence  
    TCanvas* c2;
   if(coll=="pp") c2 =new TCanvas(Form("c%d",2),"", 400+150,400*2);
   else c2 =new TCanvas(Form("c%d",2),"", 400*nCENTBINS,400*2);
//    c2->Divide(nCENTBINS,2);
//    if(coll=="pp") 
        makeMultiPanelCanvas(c2,nCENTBINS,2);
    TLegend* l1 = new TLegend(0.6,0.7,0.9,0.9);
    legStyle(l1);
    for(Int_t i=0;i<nCENTBINS;++i){
        // rebin ptbins for each centrality bins since we have less bins for peripheral region 
        int nPtBin_unfolding_centDep = nPtBin_unfolding-rejectPtBins[i];
        double ptBins_unfolding_centDep[nPtBin_unfolding_centDep];
        for(int iiu=0; iiu<=nPtBin_unfolding_centDep;++iiu){
            ptBins_unfolding_centDep[iiu] = ptBins_unfolding[iiu];
        }

        c2->cd(i+1);
        SetHistTextSize(h1D_pt[1][i]);
        SetHistTextSize(h1D_pt[0][i]);
        h1D_pt[1][i]->GetXaxis()->CenterTitle();
        /////////////////////////////////////////////// 2019.01.28 update (comment out width option)
        h1D_pt[2][i]->Scale(1.,"width");
        h1D_pt[1][i]->Scale(1.,"width");
        h1D_pt[0][i]->Scale(1.,"width");
        ////////////////////////////////////////////////
       // h1D_pt[1][i]->Scale(100.);
       // h1D_pt[0][i]->Scale(100.);
        h1D_pt[0][i]->SetLineColor(4);
        h1D_pt[0][i]->SetLineColor(2);
        h1D_pt[1][i]->Draw("hist e");
        h1D_pt[0][i]->Draw("hist same e");
        gPad->SetLogy();
        gPad->SetLogx();
        if(i==0){
            l1->AddEntry(h1D_pt[0][i], "GEN", "l");
            l1->AddEntry(h1D_pt[1][i], "RECO", "l");
        }
        l1->Draw("same");
        if(coll=="pp") drawText(Form("pp%s",""),0.4,1.0-c2->GetTopMargin()-0.06);
        else  drawText(Form("%d-%d %%",(int)centBins_i[i]/2,(int)centBins_f[i]/2),0.2,1.0-c2->GetTopMargin()-0.06);
        c2->cd(i+1+nCENTBINS);
        gPad->SetLogx();
        h1D_pt_ratio[i]->SetTitle(";p_{T}^{#gamma} (GeV);Reco p_{T}/Gen p_{T}");
        h1D_pt_ratio[i]->GetYaxis()->SetRangeUser(0.8,1.2);
        SetHistTextSize(h1D_pt_ratio[i]);
        h1D_pt_ratio[i]->Draw("e");
        jumSun(ptBins[0],1,ptBins_unfolding_centDep[nPtBin_unfolding_centDep],1);
    } 
    c2->SaveAs(Form("%sfigures/correlation_genPt_recoPt_1D_%s.pdf",dir.Data(),cap.Data()));
    
    /////////////////////////////////////////////////////////////////////
    // DRAWING : h2D genPt vs. recoPt correlation : Centrality Dependence  
   
    TCanvas* c1 =new TCanvas(Form("c%d",1),"", 400*nCENTBINS,400);
    c1->Divide(nCENTBINS,1);
    for(Int_t i=0;i<nCENTBINS;++i){
        c1->cd(i+1);
        gPad->SetLogx();
        gPad->SetLogy();
        h2D_gen_reco[i]->Draw("colz text");
        //h2D_gen_reco[i]->GetYaxis()->SetTitleOffset(0.5);
        drawText(Form("%d-%d %%",(int)centBins_i[i]/2,(int)centBins_f[i]/2),0.2,1.0-c1->GetTopMargin()-0.06);
    }
    c1->SaveAs(Form("%sfigures/correlation_genPt_recoPt_2D_%s.pdf",dir.Data(),cap.Data()));

    /////////////////////////////////////////////////////////////////////
    // Do matrix
    for(Int_t i=0;i<nCENTBINS;++i){
        for(int ypt=1; ypt<=h2D_gen_reco[i]->GetNbinsY(); ++ypt){
            int totEvtInAbin = 0;
            for(int xpt=1; xpt<=h2D_gen_reco[i]->GetNbinsX(); ++xpt)
                totEvtInAbin += h2D_gen_reco[i]->GetBinContent(xpt,ypt);

            for(int xpt=1; xpt<=h2D_gen_reco[i]->GetNbinsX(); ++xpt){
                int evtInAbin = h2D_gen_reco[i]->GetBinContent(xpt,ypt); 
                double percent = 0;
                percent = (double)evtInAbin/(double)totEvtInAbin;
                h2D_gen_reco_percent[i]->SetBinContent(xpt,ypt,percent);
            }//x loop
        }//y loop
    }//centrality loop
    
    //gStyle->SetPaintTextFormat("4.2f");
    TCanvas* c3 =new TCanvas(Form("c%d",3),"", 400*nCENTBINS,400);
    c3->Divide(nCENTBINS,1);
    for(Int_t i=0;i<nCENTBINS;++i){
        c3->cd(i+1);
        gPad->SetLogy();
        gPad->SetLogx();
        h2D_gen_reco_percent[i]->Draw("colz text");
        //h2D_gen_reco[i]->GetYaxis()->SetTitleOffset(0.5);
        //h2D_gen_reco[i]->Draw("colz text");
        drawText(Form("%d-%d %%",(int)centBins_i[i]/2,(int)centBins_f[i]/2),0.2,1.0-c1->GetTopMargin()-0.06);
    }
    c3->SaveAs(Form("%sfigures/correlation_genPt_recoPt_2D_percent_%s.pdf",dir.Data(),cap.Data()));


    
}
