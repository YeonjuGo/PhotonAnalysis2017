// Created : 2017 April 18
// Modified : 2017 May18
// Author : Yeonju Go
// 

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
bool isConsBin = false;
const int colHere[]={2,4,8,kYellow+2,kCyan+1};
const int markerStyle[]={20,33,22,23,22,29};

#define _SET_BRANCH_VEC(tree, type, branch)     \
    std::vector<type>* branch = 0;              \
tree->SetBranchStatus(#branch, 1);          \
tree->SetBranchAddress(#branch, &branch);   \

#define _SET_BRANCH_VAR(tree, type, branch)     \
    type branch;                                \
tree->SetBranchStatus(#branch, 1);          \
tree->SetBranchAddress(#branch, &branch);   \

void correlation_genPt_recoPt_residualCorrection(TString coll="pp", TString ver="180802_temp_v20", bool doResCorr = false, bool isFineBinning=false, bool doWeight=true){
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

    t1->SetBranchStatus("*", 0);
    t1_evt->SetBranchStatus("*", 0);

     _SET_BRANCH_VEC(t1, float, mcEt);
     _SET_BRANCH_VEC(t1, float, mcEta);
     _SET_BRANCH_VEC(t1, float, mcPhi);
    _SET_BRANCH_VEC(t1, float, mcCalIsoDR04);
    _SET_BRANCH_VAR(t1, int, nPho);
    _SET_BRANCH_VEC(t1, float, phoEt);
    _SET_BRANCH_VEC(t1, float, phoEtCorrected);
    _SET_BRANCH_VEC(t1, float, phoEta);
    _SET_BRANCH_VEC(t1, float, phoPhi);
    _SET_BRANCH_VEC(t1, float, phoHoverE);
    _SET_BRANCH_VEC(t1, float, pho_ecalClusterIsoR4);
    _SET_BRANCH_VEC(t1, float, pho_hcalRechitIsoR4);
    _SET_BRANCH_VEC(t1, float, pho_trackIsoR4PtCut20);
    _SET_BRANCH_VEC(t1, float, phoSigmaIEtaIEta_2012);
    _SET_BRANCH_VEC(t1, float, pho_swissCrx);
    _SET_BRANCH_VEC(t1, float, pho_seedTime);
    _SET_BRANCH_VEC(t1, int, pho_genMatchedIndex);
    _SET_BRANCH_VEC(t1, float, pho_genEt);
    _SET_BRANCH_VEC(t1, float, pho_sumIsoCorrected);
    _SET_BRANCH_VAR(t1, float, weight);

    _SET_BRANCH_VAR(t1_evt, int, hiBin);

    //define constants and histograms
    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1;
    Int_t nFineBin = 10;
    TString cap = Form("%s_pbpb",ver.Data());
    if(coll=="pp") cap= Form("%s_pp",ver.Data());
    if(isFineBinning) cap+=Form("_nFinePtBins%d",nFineBin);
    if(!doWeight) cap+=Form("_%s","noWeight");
    if(doResCorr) cap+=Form("_%s","ResidualCorrection");
    //cap += "_noRecoEcorrection";

    TFile* energyCorrectionFile = 0;
    TF1* photonEnergyCorrections[nCENTBINS];
    if(coll=="pp"){
        energyCorrectionFile = TFile::Open("/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/output/photonEnergyResolution_pp_GED_DSCB.root");
        photonEnergyCorrections[0] = (TF1*)energyCorrectionFile->Get(Form("f_mean_fit_cent%i_eta0", 0));
    }

    TH1D* h1D_pt[2][nCENTBINS]; // 0:gen 1:reco
    TH1D* h1D_pt_ratio[nCENTBINS]; // 0:gen 1:reco
    TH1D* h1D_pt_ratio_error[nCENTBINS]; // 0:gen 1:reco
    TH2D* h2D_gen_reco[nCENTBINS]; 
    TH2D* h2D_gen_reco_percent[nCENTBINS]; 
    // TMatrix mymatrix(nbinsx+2,nbinsy+2,myhisto.GetArray(),"F") 
    TString centSt[nCENTBINS];
    for(Int_t j=0;j<nCENTBINS;++j){
        centSt[j] = Form("cent%dto%d",(int)centBins_i[j]/2,(int)centBins_f[j]/2);
        if(isFineBinning) h2D_gen_reco[j] = new TH2D(Form("h2D_corr_gen_reco_%s",centSt[j].Data()),";Gen p_{T}^{#gamma} (GeV);Reco p_{T}^{#gamma} (GeV)",nFineBin,ptBins[0],ptBins[nPtBin],nFineBin,ptBins[0],ptBins[nPtBin]);
        else h2D_gen_reco[j] = new TH2D(Form("h2D_corr_gen_reco_%s",centSt[j].Data()),";Gen p_{T}^{#gamma} (GeV);Reco p_{T}^{#gamma} (GeV)",nPtBin,ptBins,nPtBin,ptBins);
        h2D_gen_reco_percent[j] = (TH2D*) h2D_gen_reco[j]->Clone(Form("h2D_corr_gen_reco_percent_%s",centSt[j].Data()));

        for(Int_t i=0;i<2;++i){
            if(isFineBinning) h1D_pt[i][j] = new TH1D(Form("h1D_pt_%d_%s",i,centSt[j].Data()),";p_{T}^{#gamma} (GeV);",nFineBin, ptBins[0],ptBins[nPtBin]);
            else h1D_pt[i][j] = new TH1D(Form("h1D_pt_%d_%s",i,centSt[j].Data()),";p_{T}^{#gamma} (GeV);Entries",nPtBin, ptBins);
        }
        h1D_pt_ratio[j] = (TH1D*) h1D_pt[0][j]->Clone(Form("h1D_pt_ratio_%s",centSt[j].Data()));
        h1D_pt_ratio_error[j] = (TH1D*) h1D_pt[0][j]->Clone(Form("h1D_pt_ratio_error_%s",centSt[j].Data()));
    }

    uint64_t nentries = t1->GetEntries();
    for (uint64_t i=0; i<nentries; ++i) {
        if (i % 100000 == 0)
            printf("entry: %lu / %lu \n", i,nentries);

        t1->GetEntry(i);
        t1_evt->GetEntry(i);
        //cout << "nPho = " << nPho << endl;
        for (uint32_t j=0; j<nPho; ++j) {
            if (phoEt->at(j) < 10)
                continue;
            if (fabs(phoEta->at(j)) > 1.44)
                continue;
            if (pho_genMatchedIndex->at(j) < 0)
                continue;
            if(coll=="pbpb"){
            if (pho_swissCrx->at(j) > 0.9)
                continue;
            if (fabs(pho_seedTime->at(j)) > 3)
                continue;
            }
           // if (coll=="pbpb" && !(hoeCut && isoCut && sigmaCut))
           //     continue;
           // if (coll=="pp" && !(hoeCut_pp && isoCut_pp && sigmaCut_pp))
           //     continue;
             if (phoHoverE->at(j)>0.1)
                 continue;
             if (phoSigmaIEtaIEta_2012->at(j)>0.010)
                 continue;
             if ((pho_ecalClusterIsoR4->at(j)+pho_hcalRechitIsoR4->at(j)+pho_trackIsoR4PtCut20->at(j))>1)
                 continue;
            //cout << "entry = " << i << " passed photon " << endl;
            int icent = 0;
            if(coll=="pbpb"){
                for (; hiBin>=centBins_f[icent] && icent<nCENTBINS; ++icent);
            }
            //cout << "icent = " << icent << endl;

            int32_t mcindex = pho_genMatchedIndex->at(j);

            if (mcEt->at(mcindex) < 10)
                continue;
            if (mcCalIsoDR04->at(mcindex) > 5)
                continue;

            //cout << "sss" << endl;

            int ieta = 0;
            //for (; fabs(phoEta->at(j))>=etaBins[1][ieta] && ieta<nEtaBins; ++ieta);

            // according to the reco pt
            // int ipt = 0;
            // for (; fabs(phoEt->at(j))>=ptBins[ipt+1] && ipt<nPtBins; ++ipt){
            //     if(ipt>nPtBins) break;
            // }

            // according to the gen pt
            int ipt = 0;
            for (; fabs(mcEt->at(mcindex))>=ptBins[ipt+1] && ipt<nPtBin; ++ipt){
                if(ipt>nPtBin) break;
            }
            
            //cout << "ipt = "<< ipt << endl;
            double weight_ = weight;
            h1D_pt[0][icent]->Fill(pho_genEt->at(j), weight_);
            double corr = photonEnergyCorrections[icent]->Eval(phoEtCorrected->at(j));
            //cout << "reco pt = "<< phoEtCorrected->at(j)  << ", reco res corr et = "<< phoEtCorrected->at(j)*corr  << ", gen et = "<< pho_genEt->at(j) << ", weight = "<< weight_ << endl;
            if(doResCorr) h1D_pt[1][icent]->Fill(phoEtCorrected->at(j)*corr, weight_);
            else h1D_pt[1][icent]->Fill(phoEtCorrected->at(j), weight_);
            if(doResCorr) h2D_gen_reco[icent]->Fill(pho_genEt->at(j),phoEtCorrected->at(j)*corr,weight_);
            else h2D_gen_reco[icent]->Fill(pho_genEt->at(j),phoEtCorrected->at(j),weight_);
        }
    }
    for(Int_t i=0;i<nCENTBINS;++i){
        h1D_pt_ratio[i]->Divide(h1D_pt[1][i],h1D_pt[0][i]);
        h1D_pt_ratio_error[i] = getRatioErrorHist_completelyCorrelated(h1D_pt_ratio[i],h1D_pt[1][i],h1D_pt[0][i]);
    }

    cout << " DRAWING STARTS " << endl;
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/";
    /////////////////////////////////////////////////////////////////////
    // DRAWING : h1D pT distribution : Centrality Dependence  
    TCanvas* c2;
   if(coll=="pp") c2 =new TCanvas(Form("c%d",2),"", 400+100,400*2);
   else c2 =new TCanvas(Form("c%d",2),"", 400*nCENTBINS,400*2);
//    c2->Divide(nCENTBINS,2);
//    if(coll=="pp") 
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
       // h1D_pt[1][i]->Scale(100.);
       // h1D_pt[0][i]->Scale(100.);
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
        drawText(Form("%d-%d %%",(int)centBins_i[i]/2,(int)centBins_f[i]/2),0.2,1.0-c2->GetTopMargin()-0.06);
        c2->cd(i+1+nCENTBINS);
        h1D_pt_ratio[i]->SetTitle(";p_{T}^{#gamma} (GeV);Reco p_{T}/Gen p_{T}");
        h1D_pt_ratio[i]->GetYaxis()->SetRangeUser(0.8,1.2);
        SetHistTextSize(h1D_pt_ratio[i]);
        h1D_pt_ratio[i]->Draw("e");
        jumSun(ptBins[0],1,ptBins[nPtBin],1);
    } 
    c2->SaveAs(Form("%sfigures/correlation_genPt_recoPt_1D_%s.pdf",dir.Data(),cap.Data()));
    
    /////////////////////////////////////////////////////////////////////
    // DRAWING : h2D genPt vs. recoPt correlation : Centrality Dependence  
   
    TCanvas* c1 =new TCanvas(Form("c%d",1),"", 400*nCENTBINS,400);
    c1->Divide(nCENTBINS,1);
    for(Int_t i=0;i<nCENTBINS;++i){
        c1->cd(i+1);
        h2D_gen_reco[i]->Draw("colz text");
        //h2D_gen_reco[i]->GetYaxis()->SetTitleOffset(0.5);
        //h2D_gen_reco[i]->Draw("colz text");
        drawText(Form("%d-%d %%",(int)centBins_i[i]/2,(int)centBins_f[i]/2),0.2,1.0-c1->GetTopMargin()-0.06);
    }
    c1->SaveAs(Form("%sfigures/correlation_genPt_recoPt_2D_%s.pdf",dir.Data(),cap.Data()));
     
    /////////////////////////////////////////////////////////////////////
    // Do matrix
    for(Int_t i=0;i<nCENTBINS;++i){
        for(int xpt=1; xpt<=h2D_gen_reco[i]->GetNbinsX(); ++xpt){
            int totEvtInAbin = 0;
            for(int ypt=1; ypt<=h2D_gen_reco[i]->GetNbinsY(); ++ypt)
                totEvtInAbin += h2D_gen_reco[i]->GetBinContent(xpt,ypt);
            
            for(int ypt=1; ypt<=h2D_gen_reco[i]->GetNbinsY(); ++ypt){
                int evtInAbin = h2D_gen_reco[i]->GetBinContent(xpt,ypt); 
                double percent = 0;
                percent = (double)evtInAbin/(double)totEvtInAbin;
                h2D_gen_reco_percent[i]->SetBinContent(xpt,ypt,percent);
            }//y loop
        }//x loop
    }//centrality loop
    
    //gStyle->SetPaintTextFormat("4.2f");
    TCanvas* c3 =new TCanvas(Form("c%d",3),"", 400*nCENTBINS,400);
    c3->Divide(nCENTBINS,1);
    for(Int_t i=0;i<nCENTBINS;++i){
        c3->cd(i+1);
        h2D_gen_reco_percent[i]->Draw("colz text");
        //h2D_gen_reco[i]->GetYaxis()->SetTitleOffset(0.5);
        //h2D_gen_reco[i]->Draw("colz text");
        drawText(Form("%d-%d %%",(int)centBins_i[i]/2,(int)centBins_f[i]/2),0.2,1.0-c1->GetTopMargin()-0.06);
    }
    c1->SaveAs(Form("%sfigures/correlation_genPt_recoPt_2D_percent_%s.pdf",dir.Data(),cap.Data()));


    
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
        h1D_pt_ratio[i]->Write();
        h1D_pt_ratio_error[i]->Write();
        h2D_gen_reco[i]->Write();
        h2D_gen_reco_percent[i]->Write();
    }
    fout->Close();
}
