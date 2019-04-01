// comparison isolation variables between DATA and MC 
// Author : Yeonju Go

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
void sumIso_pt_cent_2D(TString ver = "180817_temp_v23", TString coll="pbpb", int sample = 0){
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);
    SetyjPadStyle();

    TString cap = ver+"_"+coll+"_etaCut";
    //set file location
    const char* fname;
    if(coll=="pp"){
        if(sample==0){
            cap+="_DATA";
            fname = ppDatafname;
        } else if(sample==1){
            cap+="_AllQCDPhotons";
            fname = ppMCfname;
        } else if(sample==2){
            cap+="_EmEnrichedDijet";
            fname = ppMCEmEnrfname;
        } else{
            cout << "[ERROR] There is no this kind of sample type" << endl;
            return;
        }
    } else if(coll=="pbpb"){
        if(sample==0){
            cap+="_DATA";
            fname = pbpbDatafname;
        } else if(sample==1){
            cap+="_AllQCDPhotons";
            fname = pbpbMCfname;
        } else if(sample==2){
            cap+="_EmEnrichedDijet";
            fname = pbpbMCEmEnrfname;
        } else{
            cout << "[ERROR] There is no this kind of sample type" << endl;
            return;
        }
    } else{
        cout << "[ERROR] There is no this kind of sample type" << endl;
        return;
    }

    TFile* f1 = new TFile(fname);
    TChain* t1 = new TChain("EventTree");
    TChain* t1_evt = new TChain("HiEvt");
    //TChain* t1_skim = new TChain("skim");
    //TChain* t1_hlt = new TChain("hltTree");
    t1->Add(fname);
    t1_evt->Add(fname);
    //t1_skim->Add(fname);
    //t1_hlt->Add(fname);
    t1->AddFriend(t1_evt);
    //t1->AddFriend(t1_skim);
    //t1->AddFriend(t1_hlt);
    TCanvas* c1 = new TCanvas("c1","",400,400);

    TCut centCut_ = "hiBin>=0 && hiBin<=200";
    if(coll=="pp") centCut_ = "hiBin>-100";
    TH2D* h2D = new TH2D("h2D_sumIso_pt",";p_{T}^{#gamma};sumIso",200,20,200,200,-200,400);
    TH1D* h1D_pt = new TH1D("h1D_pt",";p_{T}^{#gamma};",200,20,200);
    TH1D* proj_pt = new TH1D("proj_pt",";p_{T}^{#gamma};",200,20,200);
    t1->Draw("pho_sumIso:phoEtCorrected>>h2D_sumIso_pt",Form("(weight)*(%s && %s && %s && %s && %s)",noiseCut.GetTitle(), hoeCut.GetTitle(),sigmaCut.GetTitle(),etaCut.GetTitle(), centCut_.GetTitle()));
    t1->Draw("phoEtCorrected>>h1D_pt",Form("(weight)*(%s && %s && %s && %s && %s)",noiseCut.GetTitle(), hoeCut.GetTitle(),sigmaCut.GetTitle(),etaCut.GetTitle(), centCut_.GetTitle()));
    //t1->Draw("pho_sumIso:phoEtCorrected>>h2D_sumIso_pt",Form("(weight)*(%s && %s && %s && %s)",noiseCut.GetTitle(), && hoeCut && sigmaCut && etaCut && centCut_);
    //t1->Draw("phoEtCorrected>>h1D_pt",noiseCut && hoeCut && sigmaCut && etaCut && centCut_);
    proj_pt = h2D->ProfileX(); 
    proj_pt->SetTitle(";p_{T}^{#gamma};<sumIso>");
    proj_pt->SetMarkerStyle(20);
    proj_pt->SetMarkerColor(1);

    h2D->Draw("colz");
    proj_pt->Draw("same pe");
    c1->SaveAs(Form("figures/sumIso_ID_h2D_sumIso_pt_%s.pdf",cap.Data()));
    h1D_pt->Draw("");
    c1->SaveAs(Form("figures/sumIso_ID_h1D_pt_%s.pdf",cap.Data()));
    proj_pt->Draw("");

    if(sample==0){
        proj_pt->Fit("pol1");
        TF1* f_pt = (TF1*)proj_pt->GetFunction("pol1");
        f_pt->Draw("same");
        drawText(Form("%.3f+%.3fx",f_pt->GetParameter(0),f_pt->GetParameter(1)),0.2,0.8);
    }
    c1->SaveAs(Form("figures/sumIso_ID_proj_pt_%s.pdf",cap.Data()));

    if(coll=="pbpb"){

        TH2D* h2D_cent = new TH2D("h2D_sumIso_cent",";Centrality;sumIso",200,0,200,200,-200,400);
        TH1D* h1D_cent = new TH1D("h1D_cent",";Centrality;",200,0,200);
        TH1D* proj_cent = new TH1D("proj_cent",";Centrality;",200,0,200);
        t1->Draw("pho_sumIso:hiBin>>h2D_sumIso_cent",Form("(weight)*(%s && %s && %s)",noiseCut.GetTitle(), hoeCut.GetTitle(), sigmaCut.GetTitle()));
        t1->Draw("hiBin>>h1D_cent",Form("(weight)*(%s && %s && %s)",noiseCut.GetTitle(), hoeCut.GetTitle(), sigmaCut.GetTitle()));
        //t1->Draw("pho_sumIso:hiBin>>h2D_sumIso_cent",noiseCut && hoeCut && sigmaCut);
        //t1->Draw("hiBin>>h1D_cent",noiseCut && hoeCut && sigmaCut);
        proj_cent = h2D_cent->ProfileX(); 
        proj_cent->SetTitle(";Centrality;<sumIso>");
        proj_cent->SetMarkerStyle(20);
        proj_cent->SetMarkerColor(1);

        TCanvas* c1 = new TCanvas("c1","",400,400);
        h2D_cent->Draw("colz");
        proj_cent->Draw("same pe");
        c1->SaveAs(Form("figures/sumIso_ID_h2D_sumIso_cent_%s.pdf",cap.Data()));
        h1D_cent->Draw("");
        c1->SaveAs(Form("figures/sumIso_ID_h1D_cent_%s.pdf",cap.Data()));
        proj_cent->Draw("");
        if(sample==0){
            proj_cent->Fit("pol2");
            TF1* f_cent = (TF1*)proj_cent->GetFunction("pol2");
            f_cent->Draw("same");
            drawText(Form("%.3f+%.3fx+%.3fx^{2}",f_cent->GetParameter(0),f_cent->GetParameter(1),f_cent->GetParameter(2)),0.2,0.8);
        }
        c1->SaveAs(Form("figures/sumIso_ID_proj_cent_%s.pdf",cap.Data()));
}

} // main function
