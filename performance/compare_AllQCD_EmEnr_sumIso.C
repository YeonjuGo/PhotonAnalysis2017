// Created : 2017 April 11
// Modified : 2018 Feb 15
// Author : Yeonju Go
// 
// To compare two datasets (ex. allqcdphoton and emenricheddijet) 

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"

int compareTwo(TTree* t1=0 ,TTree* t2=0,TString var="pt", int nBins=10, double xMin=0, double xMax=10, TCut cut1="",TCut cut2="", const char* cap="", TString ptTxt="", TString centTxt="", TString coll="pbpb");
void compare_AllQCD_EmEnr_sumIso(TString coll="PbPb"){

    const char* fname_1="0";
    const char* fname_2="0";
    if(coll=="pp"){ 
        fname_1=Form("%s",ppMCfname.Data());
        fname_2=Form("%s",ppMCEmEnrfname.Data());
    } else if(coll=="PbPb"){
        fname_1=Form("%s",pbpbMCfname.Data());
        fname_2=Form("%s",pbpbMCEmEnrfname.Data());
    }

    TFile* f1 = new TFile(fname_1);
    TTree* t1 = (TTree*) f1 -> Get("EventTree");
    TTree* t1_hi = (TTree*) f1 -> Get("skim");
    TTree* t1_evt = (TTree*) f1 -> Get("HiEvt");
    TTree* t1_hlt= (TTree*) f1 -> Get("hltTree");
    t1->AddFriend(t1_hi);
    t1->AddFriend(t1_evt);
    t1->AddFriend(t1_hlt);
    TFile* f2 = new TFile(fname_2);
    TTree* t2 = (TTree*) f2 -> Get("EventTree");
    TTree* t2_hi = (TTree*) f2 -> Get("skim");
    TTree* t2_evt = (TTree*) f2 -> Get("HiEvt");
    TTree* t2_hlt= (TTree*) f2 -> Get("hltTree");
    t2->AddFriend(t2_hi);
    t2->AddFriend(t2_evt);
    t2->AddFriend(t2_hlt);

    TString cap = "";
    //cap += coll;
    TCut cut1 = "(1==1)";
    TCut cut2 = "(1==1)";
    //TCut cut1 = mcIsolation;
    //TCut cut2 = mcBkgIsolation;


    int nBins = 50;
    TCut etaCut = Form("(abs(phoEta)>=%f)&&(abs(phoEta)<%f)", 0.0, 1.44);
    //TCut etaCut = Form("(abs(phoEta)>=%f)&&(abs(phoEta)<%f)", etaBins[0], etaBins[1]);
    TCut commonCut = "(1==1)";
    if(coll=="PbPb") commonCut = etaCut;
    else commonCut = etaCut;
    //if(coll=="pbpb") commonCut = ptCut && etaCut && hoeCut;
    //else commonCut = ptCut && etaCut && hoeCut_pp;
    //compareTwo(t1, t2, "pthat",nBins, 0, 300.0,cut1,cut2,cap);
    //compareTwo(t1, t2, "phoEt",nBins, 20, 300.0,cut1 && commonCut,cut2 && commonCut,cap);
    //compareTwo(t1, t2, "hiBin",nBins, 0, 200.0,cut1 && commonCut,cut2 && commonCut,cap);

    const int centBins_i_[] = {0,0,20,60,100,0,60};
    const int centBins_f_[] = {200,20,60,100,200,60,100};
    int nCentBinIF_ = sizeof(centBins_i)/sizeof(int);
    if(coll=="pp") nCentBinIF_=1;
    const double ptBins_i_[] = {20,50,80};
    const double ptBins_f_[] = {50,80,200};
    //const double ptBins_i_[] = {20,20,30,40,50,60,80,100,130,20,40,60,100};
    //const double ptBins_f_[] = {200,30,40,50,60,80,100,130,200,40,60,100,200};
    const int nPtBinIF_ = sizeof(ptBins_i_)/sizeof(double);
    for(Int_t ipt = 0; ipt < nPtBinIF_; ++ipt){
        TCut ptCut_ = Form("(phoEt>=%f)&&(phoEt<%f)", ptBins_i_[ipt], ptBins_f_[ipt]);
        for(Int_t jcent = 0; jcent < nCentBinIF_; ++jcent){
            TCut centCut_ = Form("(hiBin>=%d)&&(hiBin<%d)",centBins_i_[jcent],centBins_f_[jcent]);
            if(coll=="pp") centCut_ = "hiBin >-999";
            TCut totComCut = commonCut && ptCut_ && centCut_;
            TString ptTxt = Form("%d GeV < p_{T}^{#gamma} < %d GeV", (int)ptBins_i_[ipt], (int)ptBins_f_[ipt]); 
            TString centTxt = Form("Centrality %d - %d %s",centBins_i_[jcent]/2,centBins_f_[jcent]/2, "%"); 
            if(coll=="PbPb") cap = Form("%s_pt%dto%d_cent%dto%d",coll.Data(),(int)ptBins_i_[ipt],(int)ptBins_f_[ipt],centBins_i_[jcent]/2,centBins_f_[jcent]/2);
            else cap = Form("%s_pt%dto%d",coll.Data(),(int)ptBins_i_[ipt],(int)ptBins_f_[ipt]);
            compareTwo(t1, t2, "pho_sumIsoCorrected",100, -20, 80,mcIsolation && totComCut, mcBkgIsolation && totComCut,cap,ptTxt,centTxt, coll);
            compareTwo(t1, t2, "phoSigmaIEtaIEta_2012",100, 0.002, 0.02,mcIsolation && totComCut, mcBkgIsolation && totComCut,cap,ptTxt,centTxt, coll);
            //cap += "_noGenCut";
            //cout << totComCut.GetTitle() << endl;
/*            compareTwo(t1, t2, "phoEta",nBins, -1.44, 1.44,cut1 && totComCut,cut2 && totComCut,cap);
            compareTwo(t1, t2, "phoPhi",nBins, -TMath::Pi(), TMath::Pi(),cut1 && totComCut,cut2 && totComCut,cap);
            compareTwo(t1, t2, "phoSCE",nBins*2, 50, 500,cut1 && totComCut,cut2 && totComCut,cap);
            compareTwo(t1, t2, "phoSCEtaWidth",nBins, 0.005, 0.035,cut1 && totComCut,cut2 && totComCut,cap);
            compareTwo(t1, t2, "phoSCPhiWidth",nBins, 0.005, 0.2,cut1 && totComCut,cut2 && totComCut,cap);
            compareTwo(t1, t2, "phoSCBrem",nBins, 0.5, 15,cut1 && totComCut,cut2 && totComCut,cap);
            compareTwo(t1, t2, "phoR9",nBins, 0.1, 1.,cut1 && totComCut,cut2 && totComCut,cap);
            compareTwo(t1, t2, "phoHadTowerOverEm",nBins, 0, 2.,cut1 && totComCut,cut2 && totComCut,cap);
            compareTwo(t1, t2, "phoHoverE",nBins, 0, 2.,cut1 && totComCut,cut2 && totComCut,cap);
            compareTwo(t1, t2, "phoSigmaIEtaIEta",nBins, 0.002, 0.024,cut1 && totComCut,cut2 && totComCut,cap);
            compareTwo(t1, t2, "phoE3x3",nBins, 0, 600,cut1 && totComCut,cut2 && totComCut,cap);
            compareTwo(t1, t2, "phoE1x5",nBins, 0, 600,cut1 && totComCut,cut2 && totComCut,cap);
            compareTwo(t1, t2, "phoE2x5",nBins, 0, 600,cut1 && totComCut,cut2 && totComCut,cap);
            compareTwo(t1, t2, "phoE5x5",nBins, 0, 700,cut1 && totComCut,cut2 && totComCut,cap);
            compareTwo(t1, t2, "phoMaxEnergyXtal",nBins, 0, 300,cut1 && totComCut,cut2 && totComCut,cap);
            compareTwo(t1, t2, "phoSigmaEtaEta",nBins, 0, 0.02,cut1 && totComCut,cut2 && totComCut,cap);
            compareTwo(t1, t2, "phoR1x5",nBins, 0.2, 1,cut1 && totComCut,cut2 && totComCut,cap);
            compareTwo(t1, t2, "phoR2x5",nBins, 0.5, 1,cut1 && totComCut,cut2 && totComCut,cap);
            compareTwo(t1, t2, "phoSigmaIEtaIEta_2012",nBins, 0.005, 0.025,cut1 && totComCut,cut2 && totComCut,cap);
            compareTwo(t1, t2, "phoE3x3_2012",nBins, 0, 600,cut1 && totComCut,cut2 && totComCut,cap);
*/

        }
    }
} // main function

int compareTwo(TTree* t1, TTree* t2, TString var, int nBins, double xMin, double xMax, TCut cut1, TCut cut2, const char* cap, TString ptTxt, TString centTxt, TString coll)  {
    gStyle->SetOptStat(0);
    TH1::SetDefaultSumw2();
    SetyjPadStyle();
    int i = 1;
    //static int i = 1;
    TCanvas* c =new TCanvas(Form("c_%s_%s",var.Data(),cap),"", 500,400);
    //TCanvas* c =new TCanvas(Form("c_%s_%s",var.Data(),cap),"", 400,600);
    //ratioPanelCanvas(c);
    //c->cd(1);
    cout << "Made canvas" << endl;
    TLegend* l1 = new TLegend(0.52,0.68,0.80,0.90);
    l1->SetName(Form("l1_%s_%s",var.Data(),cap));
    legStyle(l1);

    TString varName = var;
    if(var=="pho_ecalClusterIsoR5+pho_hcalRechitIsoR5+pho_trackIsoR5PtCut20") varName = "sumIso";
    if(var=="pho_sumIsoCorrected") varName = "sumIso";
    TH1D* h1;
    h1 = new TH1D(Form("h1_%s_%s",var.Data(),cap), Form(";%s;",varName.Data()), nBins,xMin,xMax);
    TH1D* h2 = (TH1D*)h1->Clone(Form("h2_%s_%s",var.Data(),cap));

    h1->Sumw2();
    h2->Sumw2();
    t1->Draw(Form("%s>>%s",var.Data(),h1->GetName()), Form("(weight)*(%s)",cut1.GetTitle()));
    h1=(TH1D*)gDirectory->Get(h1->GetName());
    t2->Draw(Form("%s>>%s",var.Data(),h2->GetName()), Form("(weight)*(%s)",cut2.GetTitle()));	
    h2=(TH1D*)gDirectory->Get(h2->GetName());
    cout << "filled hist" << endl;
    h1->Scale( 1. / h1->Integral(),"width");
    h2->Scale( 1. / h2->Integral(),"width");
    cout << "scale" << endl;
    //cout << cut1.GetTitle() << endl;	
    //////////////////////////////////
    // Cosmetics
    //h1->GetYaxis()->SetRangeUser(0,0.05);
    SetHistTextSize(h1);
    SetHistTextSize(h2);
    h1->SetTitle(";sumIso;Arbitrary normalization");
    h2->SetTitle(";sumIso;Arbitrary normalization");
    h1->SetMarkerStyle(20);
    h1->SetMarkerSize(0.6);
    h1->SetMarkerColor(2);
    h1->SetLineColor(1);
    h1->SetTitleSize(13);
    h2->SetFillColor(38);
    h2->SetFillStyle(3001);
    h2->SetLineColor(9);
    double YminVal;
    cout << "done" << endl;
    YminVal = cleverRange(h1,h2,1.2);
    cout << "cleverRange" << endl;
    //h2->SetTitle(";;Arbitrary normalization");
    //SetHistTextSize(h2);
    //if(YminVal!=0) c->GetPad(1)->SetLogy();

    l1->AddEntry(h1,"Signal MC","pl");
    l1->AddEntry(h2,"Background MC","F");	
    //l1->AddEntry(h1,"AllQCDPhotons","pl");
    //l1->AddEntry(h2,"EmEnrichedDijet","F");	
    h2->DrawCopy("hist e");
    h1->DrawCopy("hist e same");
    l1->Draw();
    //drawText("PbPb 5 TeV",0.91,0.76,1);
    float xpos = 0.85;
    float ypos = 0.60;
    float dy = 0.05;
    float ddy = 0.02;
    drawText("|#eta|<1.44",xpos,ypos,1);
    drawText(Form("%s 5.02 TeV",coll.Data()),xpos,ypos-dy,1);
    drawText(Form("%s",ptTxt.Data()),xpos,ypos-dy*2-ddy,1);
    if(coll=="PbPb") drawText(Form("%s",centTxt.Data()),xpos,ypos-dy*3-ddy,1);
    //drawText("p_{T}^{#gamma}>20 GeV",0.91,0.76-0.05,1);
    jumSun(1,0,1,1);
    //jumSun(1,0,1,1);

   // c->cd(2);
   // h1->Divide(h2);
   // h1->SetTitle(Form(";%s;Signal/Background",var.Data()));
   // //double ratioRange = getCleverRange(h1);
   // h1->SetAxisRange(0,2,"Y");
   // SetHistTextSize(h1);
   // h1->DrawCopy("le1");
   // //jumSun(xMin,1,xMax,1);
   // drawText(cap,0.2,c->GetPad(2)->GetBottomMargin()+0.04);

    //fitting 
    //TF1* f1 = new TF1("f1", "pol1",0.005,0.02);
    //h1->Fit(f1,"Q R");
    //c->GetPad(1)->SetLogy();
    c->SaveAs(Form("figures/compare_signal_bkg_%s_%s.pdf",varName.Data(),cap));
    i++;
    delete c;
    delete h1;
    delete h2;
    delete l1;
    return 1;
}
