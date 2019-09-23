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
void compare_Data_MC_bkgPhotons(TString coll="pbpb", TString ver="190703_temp_v31", bool isBkg=true, double sigCut = 1, double sideband_i = 40, double sideband_f = 50, int Nfunc = 1){

    const char* fname_1 ="";
    const char* fname_2 ="";
    if(coll=="pp"){ 
        fname_1=ppDatafname_high;
        fname_2=ppMCEmEnrfname;
    } else if(coll=="pbpb"){
        fname_1=pbpbDatafname_high;
        fname_2=pbpbMCEmEnrfname;
    }
    if(!isBkg){
        if(coll=="pp"){ 
            fname_1=ppDatafname_high;
            fname_2=ppMCfname;
        } else if(coll=="pbpb"){
            fname_1=pbpbDatafname_high;
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
    TFile* f2 = new TFile(fname_2);
    TTree* t2 = (TTree*) f2 -> Get("EventTree");
    TTree* t2_hi = (TTree*) f2 -> Get("skim");
    TTree* t2_evt = (TTree*) f2 -> Get("HiEvt");
    TTree* t2_hlt = (TTree*) f2 -> Get("hltTree");
    t2->AddFriend(t2_hi);
    t2->AddFriend(t2_evt);
    t2->AddFriend(t2_hlt);

    //const int centBins_i_[] = {0};
    //const int centBins_f_[] = {20};
    //const int centBins_i_[] = {0};
    //const int centBins_f_[] = {200};
    const int centBins_i_[] = {0,0,20,60,100};
    const int centBins_f_[] = {200,20,60,100,200};
    int nCentBinIF_ = sizeof(centBins_i_)/sizeof(int);
    if(coll=="pp") nCentBinIF_=1;
    //const double ptBins_i_[] = {20};
    //const double ptBins_f_[] = {200};
    const double ptBins_i_[] = {20,20,40,20,50};
    const double ptBins_f_[] = {200,40,200,50,200};
    //const double ptBins_i_[] = {20,25,30,40,50,60,80,100,130};
    //const double ptBins_f_[] = {25,30,40,50,60,80,100,130,200};
    int nPtBinIF_ = sizeof(ptBins_i_)/sizeof(double);

    const double sumIsoBins_i[] = {-999,1.0,1.0,5.0,10.0,20.0};
    const double sumIsoBins_f[] = {1.0,5.0,7.0,10.0,20.0,30.0};
    int nSumIso = sizeof(sumIsoBins_i)/sizeof(double);

    Int_t nCENTBINS = nCentBinIF_;
    if(coll=="pp") nCENTBINS=1;
    for(Int_t i = 0; i < nPtBinIF_; ++i) 
    {
        TCut ptCut_ = Form("(phoEtCorrected >= %f) && (phoEtCorrected < %f)", ptBins_i_[i], ptBins_f_[i]);
        for(Int_t k = 0; k < nCENTBINS; ++k){ 
            TCut centCut = Form("(hiBin >= %d) && (hiBin < %d)", centBins_i_[k], centBins_f_[k]);    
            if(coll=="pp") centCut = "hiBin<10000";
            TCut commonCut;

            TCut nonHoeCut = "phoHoverE>0.1";
            TCut nonSigmaCut = "phoSigmaIEtaIEta_2012>0.011";
            TCut nonSumIsoCut = "pho_sumIsoCorrected>50.0";
            commonCut = nonHoeCut && ptCut_ && etaCut && centCut;
            //commonCut = hoeCut && ptCut_ && etaCut && centCut;
            //for(Int_t j = 0; j < nSumIso; ++j){
               // TCut sumIsoCut = Form("pho_sumIsoCorrected > %f && pho_sumIsoCorrected < %f", sumIsoBins_i[j],sumIsoBins_f[j]);

                TCut totCut_data = commonCut && trigCut_high && evtSelFilterCut && noiseCut; 
                if(coll=="pp") totCut_data = commonCut && trigCut_high && evtSelFilterCut_pp && noiseCut; 
                TCut totCut_mc = commonCut && mcBkgIsolation;  
                if(!isBkg) totCut_mc = commonCut && mcIsolation;  

                TString cap = Form("%s_%s_pt%dto%d_cent%dto%d",ver.Data(),coll.Data(),(int)ptBins_i_[i],(int)ptBins_f_[i],(int)centBins_i_[k]/2,(int)centBins_f_[k]/2);
                if(coll=="pp") cap = Form("%s_%s_pt%dto%d",ver.Data(),coll.Data(),(int)ptBins_i_[i],(int)ptBins_f_[i]);
                TString cap2_sumIso = "dataSB_to_EmEnr_sumIso50"; 
                TString cap2_sigma = "dataSB_to_EmEnr_sigma0p011"; 
                //if(isBkg) cap2 = Form("data_to_bkg_sumIso%dto%d",(int)sumIsoBins_i[j],(int)sumIsoBins_f[j]);
                //else cap2 = Form("data_to_sig_sumIso%dto%d",(int)sumIsoBins_i[j],(int)sumIsoBins_f[j]);
                cout << "start" << endl;
                compareTwo(t1, t2, purityVar,50, 0., 0.030, totCut_data && nonSumIsoCut, totCut_mc && nonSumIsoCut,cap,cap2_sumIso,isBkg,Nfunc); 
                compareTwo(t1, t2, "pho_sumIsoCorrected",150, -50, 100, totCut_data && nonSigmaCut, totCut_mc && nonSigmaCut,cap,cap2_sigma,isBkg,Nfunc); 
            //}

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
    t1->Draw(Form("%s>>%s",var.Data(),h1->GetName()), Form("%s",cut1.GetTitle()));
    //t1->Draw(Form("%s>>%s",var.Data(),h1->GetName()), Form("(weight)*(%s)",cut1.GetTitle()));
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
        l1->AddEntry(h1,"BKG DATA","pl");
        l1->AddEntry(h1,"Background MC","l");
    } else{
        l1->AddEntry(h1,"BKG DATA","pl");
        l1->AddEntry(h1,"Signal MC","l");
    }
    l1->Draw();

    c->cd(2);
    h1->Divide(h2);
    h1->SetYTitle("BKG DATA / EmEnrichedDijet MC");
    //h1->SetYTitle("Isolated / NonIsolated");
    double ratioRange = getCleverRange(h1);
    h1->SetAxisRange(0,3,"Y");
    h1->DrawCopy("le1");

    //fitting 
    //TF1* f1;
    //if(Nfunc == 0){ // pol1
    //    f1 = new TF1("f1", "pol1",0.007,0.02);
    //    f1->SetParameters(1.73284,-91.6665);
    //} else if(Nfunc == 1){ //DSCB
    //    f1 = new TF1("f1", fnc_DSCB, 0.001, 0.025, 7);
    //    //f1 -> SetParameters(1.5,0.006,0.001,0.79,3.63,0.59,1.67);
    //    f1 -> SetParLimits(0,1.0,3.0);
    //    f1 -> SetParLimits(1,0.005,0.012);
    //    f1 -> SetParameters(2.34652e+00,8.92997e-03,6.39936e-04,1.26405e-01,6.17292e-01,3.31750e-01,9.01061e+00);
    //}
    //
    //h1->Fit(f1,"Q R");
    //h1->Fit(f1,"R");
    //jumSun(xMin,1,xMax,1);
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
    //if(Nfunc==0) drawText(Form("f(x)=%.2fx+%.2f",f1->GetParameter(1),f1->GetParameter(0)),0.3,0.9);
    c->SaveAs(Form("%sfigures/compareBKG_%s_%s_%s_function%d.pdf",dir.Data(),var.Data(),cap.Data(),cap2.Data(),Nfunc));
    TFile* fout = new TFile(Form("%soutput/compare_dataSB_to_EmEnr_%s_%s_function%d.root",dir.Data(),cap.Data(),cap2.Data(),Nfunc),"RECREATE");
    //f1->Write();
    c->Write();
    h1->Write();
    h2->Write();
    fout->Close();
    delete fout;
    //delete f1;
    delete c;
    delete h1;
    delete h2;

    i++;
}
