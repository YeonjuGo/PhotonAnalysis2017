// 2016 Mar . comparing two datasets (ex. allqcdphoton and emenricheddijet) 
// Created : 31 May 2017
// Modified : 01 June 2017
// Author : Yeonju Go

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
double fnc_DSCB(double* xx, double* params)
{
    double x   = xx[0];
    // gaussian core
    double N     = params[0];
    double mean  = params[1];
    double sigma = params[2];
    // transition parameters
    double a1  = params[3];
    double n1  = params[4];
    double a2  = params[5];
    double n2  = params[6];

    double u   = (x-mean)/sigma;
    double A1  = TMath::Power(n1/TMath::Abs(a1),n1)*TMath::Exp(-a1*a1/2);
    double A2  = TMath::Power(n2/TMath::Abs(a2),n2)*TMath::Exp(-a2*a2/2);
    double B1  = n1/TMath::Abs(a1) - TMath::Abs(a1);
    double B2  = n2/TMath::Abs(a2) - TMath::Abs(a2);

    double res = N;
    if      (u < -a1) res *= A1*TMath::Power(B1-u,-n1);
    else if (u < a2)  res *= TMath::Exp(-u*u/2);
    else              res *= A2*TMath::Power(B2+u,-n2);
    return res;
}

void compareTwo(TTree* t1=0 ,TTree* t2=0,TString var="pt", int nBins=10, double xMin=0, double xMax=10, TCut cut1="",TCut cut2="", TString cap="", TString cap2="", bool isBkg=true, int Nfunc=0);
void compare_sigmaIEtaIEta_iso_nonIso(TString coll="pbpb", TString ver="190703_temp_v31", bool isBkg=true, bool isConstantSB = false, double sigCut = 1, double sideband_i = 40, double sideband_f = 50, int Nfunc = 0, int interval = 5){

    const char* fname_1 ="";
    const char* fname_2 ="";
    if(coll=="pp"){ 
        fname_1=ppMCEmEnrfname;
        fname_2=ppMCEmEnrfname;
    } else if(coll=="pbpb"){
        fname_1=pbpbMCEmEnrfname;
        fname_2=pbpbMCEmEnrfname;
    }
    if(!isBkg){
        if(coll=="pp"){ 
            fname_1=ppMCfname;
            fname_2=ppMCfname;
        } else if(coll=="pbpb"){
            fname_1=pbpbMCfname;
            fname_2=pbpbMCfname;
        }
    }
    TFile* f1 = new TFile(fname_1);
    TTree* t1 = (TTree*) f1 -> Get("EventTree");
    TTree* t1_hi = (TTree*) f1 -> Get("skim");
    TTree* t1_hlt = (TTree*) f1 -> Get("hltTree");
    TTree* t1_evt = (TTree*) f1 -> Get("HiEvt");
    t1->AddFriend(t1_hi);
    t1->AddFriend(t1_evt);
    t1->AddFriend(t1_hlt);
    //TFile* f2 = new TFile(fname_2);
    //TTree* t2 = (TTree*) f2 -> Get("EventTree");
    //TTree* t2_hi = (TTree*) f2 -> Get("skim");
    //TTree* t2_evt = (TTree*) f2 -> Get("HiEvt");
    //TTree* t2_hlt = (TTree*) f2 -> Get("hltTree");
    //t2->AddFriend(t2_hi);
    //t2->AddFriend(t2_evt);
    //t2->AddFriend(t2_hlt);

    //const int centBins_i_[] = {0};
    //const int centBins_f_[] = {20};
    const int centBins_i_[] = {0};
    const int centBins_f_[] = {200};
    //const int centBins_i_[] = {0,20,60,100};
    //const int centBins_f_[] = {20,60,100,200};
    int nCentBinIF_ = sizeof(centBins_i_)/sizeof(int);
    const double temp_sumIso_pbpb_i[] = {7.0,6.0,4.0,1.0};
    if(coll=="pp") nCentBinIF_=1;
    //const double ptBins_i_[] = {20};
    //const double ptBins_f_[] = {200};
    const double ptBins_i_[] = {20};
    const double ptBins_f_[] = {50};
    //const double ptBins_i_[] = {20,50};
    //const double ptBins_f_[] = {50,200};
    //const double ptBins_i_[] = {20,20,25,30,40,50,60,80,100,130};
    //const double ptBins_f_[] = {200,25,30,40,50,60,80,100,130,200};
    int nPtBinIF_ = sizeof(ptBins_i_)/sizeof(double);
    
    //const double tempSumIso_i[] = {10};
    //const double tempSumIso_f[] = {100};
    const double tempSumIso_i[] = {2,2.5,3,4,5,6,8,10,13,20};
    const double tempSumIso_f[] = {7,7.5,8,9,10,11,13,15,18,25};
    //const double tempSumIso_i[] = {2,2.5,3,4,5,6,8,10,13,20,     2,2.5,3,4,5,6,8,10,13,20};
    //lconst double tempSumIso_f[] = {7,7.5,8,9,10,11,13,15,18,25, 12,12.5,13,14,15,16,18,20,23,30};
   
    //const double tempSumIso_i[] = {2,3,4,6,8,10,14,18,24,  2,3,4,6,8,10,14,18,24};
    //const double tempSumIso_f[] = {7,8,9,11,13,15,19,23,29,12,13,14,16,18,20,24,28,34};
    int nTempSumIso = sizeof(tempSumIso_i)/sizeof(double);
    if(isConstantSB==true) nTempSumIso = 1;

    Int_t nCENTBINS = nCentBinIF_;
    if(coll=="pp") nCENTBINS=1;
    for(Int_t i = 0; i < nPtBinIF_; ++i) 
    {
        TCut ptCut_ = Form("(phoEtCorrected >= %f) && (phoEtCorrected < %f)", ptBins_i_[i], ptBins_f_[i]);
        for(Int_t k = 0; k < nCENTBINS; ++k){ 
            TCut centCut = Form("(hiBin >= %d) && (hiBin < %d)", centBins_i_[k], centBins_f_[k]);    
            if(coll=="pp") centCut = "hiBin<10000";
            TCut IsoBkgCut;
            TCut nonIsoBkgCut;
            TCut commonCut;


            for(Int_t ss = 0; ss < nTempSumIso; ++ss){ 
                if(coll=="pp") {
                    //int tempSumIso_pp_i = 0.2*ptBins_i_[i]-2;
                    //int tempSumIso_pp_f = 0.2*ptBins_f_[i]-2+interval;
                    //if(ptBins_i_<50) ptCut_ = Form("(phoEtCorrected >= %f) && (phoEtCorrected < %f)", 20.0, 50.0);
                    //else ptCut_ = Form("(phoEtCorrected >= %f) && (phoEtCorrected < %f)", 50.0, 200.0);

                    if(isBkg) commonCut = mcBkgIsolation && hoeCut_pp && ptCut_ && etaCut;
                    else commonCut = mcIsolation && hoeCut_pp && ptCut_ && etaCut;
                    //commonCut = mcBkgIsolation && trigCut_mc_pp && evtSelFilterCut_pp && hoeCut_pp && ptCut_ && etaCut;
                    //IsoBkgCut = commonCut && isoCut_pp;
                    //nonIsoBkgCut = commonCut && nonIsoSBCut_pp;
                    IsoBkgCut = commonCut && Form("pho_sumIsoCorrected < %f", sigCut);
                    nonIsoBkgCut = commonCut && Form("pho_sumIsoCorrected > %f && pho_sumIsoCorrected < %f", (double)tempSumIso_i[ss],(double)tempSumIso_f[ss]);
                    //nonIsoBkgCut = commonCut && Form("pho_sumIsoCorrected > %f && pho_sumIsoCorrected < %f", (double)tempSumIso_pp_i,(double)tempSumIso_pp_f);
                    if(isConstantSB) nonIsoBkgCut = commonCut && Form("pho_sumIsoCorrected > %f && pho_sumIsoCorrected < %f", sideband_i,sideband_f);
                } else{//PbPb
                    if(isBkg) commonCut = mcBkgIsolation && hoeCut && ptCut_ && etaCut && centCut;
                    else commonCut = mcIsolation && hoeCut && ptCut_ && etaCut && centCut;
                    IsoBkgCut = commonCut && Form("pho_sumIsoCorrected < %f", sigCut);
                    nonIsoBkgCut = commonCut && Form("pho_sumIsoCorrected > %f && pho_sumIsoCorrected < %f", (double)tempSumIso_i[ss],(double)tempSumIso_f[ss]);
                    //nonIsoBkgCut = commonCut && Form("pho_sumIsoCorrected > %f && pho_sumIsoCorrected < %f",temp_sumIso_pbpb_i[k] ,temp_sumIso_pbpb_i[k]+interval);
                    if(isConstantSB) nonIsoBkgCut = commonCut && Form("pho_sumIsoCorrected > %f && pho_sumIsoCorrected < %f",sideband_i ,sideband_f);
                }

                // if(coll=="pp") {
                //     if(isBkg) commonCut = mcBkgIsolation && ptCut_ && etaCut;
                //     else commonCut = mcIsolation && ptCut_ && etaCut;
                //     IsoBkgCut = commonCut && isoCut_pp;
                //     nonIsoBkgCut = commonCut &&  isoCut_pp && hoeCut_pp;
                // } else{//PbPb
                //     if(isBkg) commonCut = mcBkgIsolation && ptCut_ && etaCut && centCut;
                //     else commonCut = mcIsolation && ptCut_ && etaCut && centCut;
                //     IsoBkgCut = commonCut && isoCut;
                //     nonIsoBkgCut = commonCut && isoCut && hoeCut;
                // }

                TString cap = Form("%s_%s_pt%dto%d_cent%dto%d",ver.Data(),coll.Data(),(int)ptBins_i_[i],(int)ptBins_f_[i],(int)centBins_i_[k]/2,(int)centBins_f_[k]/2);
                if(coll=="pp") cap = Form("%s_%s_pt%dto%d",ver.Data(),coll.Data(),(int)ptBins_i_[i],(int)ptBins_f_[i]);
                TString cap2 = ""; 
                if(isBkg){ 
                    //cap2 = Form("bkgPhotons_sigSumIso1_sidebandSumIso%dto%d",(int)sideband_i,(int)sideband_f);
                    if(coll=="pp") cap2 = Form("bkgPhotons_sigSumIso1_sidebandSumIso%.1fto%.1f",(float)tempSumIso_i[ss],(float)tempSumIso_f[ss]);
                    if(coll=="pbpb") cap2 = Form("bkgPhotons_sigSumIso1_sidebandSumIso%.1fto%.1f",(float)tempSumIso_i[ss],(float)tempSumIso_f[ss]);
                    if(isConstantSB) cap2 = Form("bkgPhotons_sigSumIso1_sidebandSumIso%.1fto%.1f",(float)sideband_i,(float)sideband_f);
                   // if(coll=="pp") cap2 = Form("bkgPhotons_sigSumIso1_sidebandSumIso%dto%d",(int)tempSumIso_i[ss],(int)tempSumIso_f[ss]);
                   // if(coll=="pbpb") cap2 = Form("bkgPhotons_sigSumIso1_sidebandSumIso%dto%d",(int)tempSumIso_i[ss],(int)tempSumIso_f[ss]);
                   // 
                    //if(coll=="pp") cap2 = Form("bkgPhotons_sigSumIso1_sidebandSumIso%dto%d",(int)(0.2*ptBins_i_[i]-2),(int)(0.2*ptBins_i_[i]-2+interval));
                    //if(coll=="pbpb") cap2 = Form("bkgPhotons_sigSumIso1_sidebandSumIso%dto%d",(int)temp_sumIso_pbpb_i[k],(int)(temp_sumIso_pbpb_i[k]+interval));
                } else{ 
                    cap2 = Form("sigPhotons_sigSumIso1_sidebandSumIso%dto%d",(int)sideband_i,(int)sideband_f);
                }
                cap2+= "_fitRange0p008to0p015";
                //const char* cap2 = "mcTotWeighted_fitChi2_shift-0.0003";
                cout << "start" << endl;
                if(coll=="pp") compareTwo(t1, t1, purityVar_pp,50, 0., 0.030, IsoBkgCut, nonIsoBkgCut,cap,cap2,isBkg,Nfunc);
                else compareTwo(t1, t1, purityVar,50, 0., 0.030, IsoBkgCut, nonIsoBkgCut ,cap,cap2,isBkg,Nfunc); 
            }
        }
    }
} // main function

void compareTwo(TTree* t1, TTree* t2, TString var, int nBins, double xMin, double xMax, TCut cut1, TCut cut2, TString cap, TString cap2, bool isBkg, int Nfunc)  {
    SetHistTitleStyle();
    SetyjPadStyle();
    gStyle->SetOptStat(0);
    TH1::SetDefaultSumw2();
    static int i = 1;
    TCanvas* c =new TCanvas(Form("c_%s_%d",var.Data(),i),"", 400,800);
    c->Divide(1,2);
    c->cd(1);
    gPad->SetLogy();
    TH1D* h1 = new TH1D(Form("h1_%s_%d",var.Data(),i), Form(";%s;",var.Data()),nBins,xMin,xMax);
    TH1D* h2 = (TH1D*)h1->Clone(Form("h2_%s_%d",var.Data(),i));

    h1->Sumw2();
    h2->Sumw2();
    //t1->Draw(Form("%s>>%s",var.Data(),h1->GetName()), cut1);
    //t2->Draw(Form("(%s)>>%s",var.Data(),h2->GetName()), cut2);
    //t2->Draw(Form("(%s-0.0005)>>%s",var.Data(),h2->GetName()), cut2);
    t1->Draw(Form("%s>>%s",var.Data(),h1->GetName()), Form("(weight)*(%s)",cut1.GetTitle()));
    //t2->Draw(Form("(%s)>>%s",var.Data(),h2->GetName()), Form("(weight)*(%s)",cut2.GetTitle()));
    t2->Draw(Form("(%s)>>%s",var.Data(),h2->GetName()), Form("(weight)*(%s)",cut2.GetTitle()));
    //t2->Draw(Form("(%s-0.0003)>>%s",var.Data(),h2->GetName()), Form("(weight)*(%s)",cut2.GetTitle()));
    //h1->Scale( 1. / h1->Integral());
    //h2->Scale( 1. / h2->Integral());
    h1->Scale( 1. / h1->Integral(),"width");
    h2->Scale( 1. / h2->Integral(),"width");
    h1->SetMarkerStyle(20);
    h1->SetMarkerSize(0.8);
    h1->SetMarkerColor(2);
    double range = cleverRangeOnlyMax(h1,h2,1.5,1.e-2);
    h1->DrawCopy("L hist e");
    h2->DrawCopy("hist e same");
    TLegend* l1 = new TLegend(0.47,0.84,0.92,0.94);
    legStyle(l1);
    if(isBkg){
        l1->AddEntry(h1,"Bkg MC Isolated","pl");
        l1->AddEntry(h1,"Bkg MC Non-isolated","l");
    } else{
        l1->AddEntry(h1,"Signal MC Isolated","pl");
        l1->AddEntry(h1,"Signal MC Non-isolated","l");
    }
    l1->Draw();

    c->cd(2);
    h1->Divide(h2);
    h1->SetYTitle("Isolated / NonIsolated");
    double ratioRange = getCleverRange(h1);
    h1->SetAxisRange(0,3,"Y");
    h1->DrawCopy("le1");

    //fitting 
    TF1* f1;
    if(Nfunc == 0){ // pol1
        f1 = new TF1("f1", "pol1",0.008,0.015);
        f1->SetParameters(1.73284,-91.6665);
    } else if(Nfunc == 1){ //DSCB
        f1 = new TF1("f1", fnc_DSCB, 0.001, 0.025, 7);
        //f1 -> SetParameters(1.5,0.006,0.001,0.79,3.63,0.59,1.67);
        f1 -> SetParLimits(0,1.0,3.0);
        f1 -> SetParLimits(1,0.005,0.012);
        f1 -> SetParameters(2.34652e+00,8.92997e-03,6.39936e-04,1.26405e-01,6.17292e-01,3.31750e-01,9.01061e+00);
    }
    
    h1->Fit(f1,"Q R");
    h1->Fit(f1,"R");
    jumSun(xMin,1,xMax,1);
    //TF1* f2gaus = new TF1("f2gaus","gaus(0)+gaus(3)",0.005,0.025);
    //f2gaus->SetParameter(1,0.005);
    //f2gaus->SetParameter(2,0.002);
    //f2gaus->SetParameter(4,0.01);
    //f2gaus->SetParameter(5,0.006);
    //h1->Fit(f2gaus,"R");

   // TF1 *fratio = new TF1("fratio","[0]*TMath::Erf((x-[1])/[2])",0.005,0.025,3);//0) plateau, 1) x-intrecept, 2) x broad
   // fratio->SetParNames("eff0","x0","m");
   // fratio->SetParameters(0.5,0.015,0.5);
   // //fratio->SetParLimits(0,0,1);
   // //fratio->SetParLimits(1,0.,10.);
   // //fratio->SetParLimits(2,0,10.);
   // h1->Fit(fratio,"WRME");
   // h1->Fit(fratio,"WRME");
   // fratio->Draw("same");

    //chi2 = gratio->Chisquare(fratio);
    //dof = gratio->GetN() - fratio->GetNpar();
    //pval = TMath::Prob(chi2,dof);
    //tchi.SetTextColor(kBlack);
    //tchi.SetTextSize(0.035*0.7/0.3);
    //tchi.DrawLatex(0.6,0.8,Form("#chi^{2}/dof = %.1f/%d (p-value: %.2f)",chi2,dof,pval));

    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/";

    drawText(cap,0.2,0.2);
    drawText(cap2,0.2,0.26);
    if(Nfunc==0) drawText(Form("f(x)=%.2fx+%.2f",f1->GetParameter(1),f1->GetParameter(0)),0.3,0.9);
    c->SaveAs(Form("%sfigures/compareBKG_%s_%s_%s_function%d.pdf",dir.Data(),var.Data(),cap.Data(),cap2.Data(),Nfunc));
    TFile* fout = new TFile(Form("%soutput/SigmaIEtaIEta_Iso_nonIso_%s_%s_function%d.root",dir.Data(),cap.Data(),cap2.Data(),Nfunc),"RECREATE");
    f1->Write();
    c->Write();
    h1->Write();
    h2->Write();
    fout->Close();
    delete fout;
    delete f1;
    delete c;
    delete h1;
    delete h2;

    i++;
}
