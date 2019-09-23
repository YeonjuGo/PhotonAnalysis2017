// Created : 2017 April 11
// Modified : 2017 April 11
// Author : Yeonju Go
// 
// To compare two datasets (ex. allqcdphoton and emenricheddijet) 

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"

int compareThree(TTree* t1=0 ,TTree* t2=0,TTree* t3=0,TString var="pt", int nBins=10, double xMin=0, double xMax=10, TCut cut1="",TCut cut2="",TCut cut3="", const char* cap="", bool doWeight=true, bool doEmEnr=false);
void compare_Data_AllQCD_EmEnr(TString coll="pbpb", TString ver="190625_temp_v25", bool doWeight=true, bool doEmEnr=true){

    const char* fname_1="0";
    const char* fname_2="0";
    const char* fname_3="0";
    if(coll=="pp"){ 
        fname_1=Form("%s",ppMCfname.Data());
        fname_2=Form("%s",ppMCEmEnrfname.Data());
        fname_3=Form("%s",ppDatafname.Data());
    } else if(coll=="pbpb"){
        fname_1=Form("%s",pbpbMCfname.Data());
        fname_2=Form("%s",pbpbMCEmEnrfname.Data());
        fname_3=Form("%s",pbpbDatafname.Data());
    }

    TFile* f1 = new TFile(fname_1);//AllQCD
    TTree* t1 = (TTree*) f1 -> Get("EventTree");
    TTree* t1_hi = (TTree*) f1 -> Get("skim");
    TTree* t1_evt = (TTree*) f1 -> Get("HiEvt");
    TTree* t1_hlt= (TTree*) f1 -> Get("hltTree");
    t1->AddFriend(t1_hi);
    t1->AddFriend(t1_evt);
    t1->AddFriend(t1_hlt);

    TFile* f2 = new TFile(fname_2);//EmEnr
    TTree* t2 = (TTree*) f2 -> Get("EventTree");
    TTree* t2_hi = (TTree*) f2 -> Get("skim");
    TTree* t2_evt = (TTree*) f2 -> Get("HiEvt");
    TTree* t2_hlt= (TTree*) f2 -> Get("hltTree");
    t2->AddFriend(t2_hi);
    t2->AddFriend(t2_evt);
    t2->AddFriend(t2_hlt);

    TFile* f3 = new TFile(fname_3); //Data
    TTree* t3 = (TTree*) f3 -> Get("EventTree");
    TTree* t3_hi = (TTree*) f3 -> Get("skim");
    TTree* t3_evt = (TTree*) f3 -> Get("HiEvt");
    TTree* t3_hlt= (TTree*) f3 -> Get("hltTree");
    t3->AddFriend(t3_hi);
    t3->AddFriend(t3_evt);
    t3->AddFriend(t3_hlt);
    
    TString cap = Form("%s_%s_hoe_sig_iso_ele_trig20onMC",ver.Data(),coll.Data());
    if(doWeight) cap+="_weighted";
    else cap+= "_noWeight";
    int nBins = 20;
    //TCut etaCut = Form("(abs(phoEta)>=%f)&&(abs(phoEta)<%f)", etaBins[0], etaBins[1]);
    TCut commonCutMC = "(1==1)";
    TCut commonCutDATA = "(1==1)";

    if(coll=="pbpb") {
        commonCutDATA = ptCut && etaCut && trigCut_low && dataCut && hoeCut && sigmaCut && isoCut && electronCut; 
        commonCutMC = ptCut && etaCut && trigCut_mc_low && hoeCut && sigmaCut && isoCut && electronCut;
    } else {
        commonCutDATA = etaCut && trigCut_pp_low && dataCut_pp && hoeCut_pp && sigmaCut_pp && isoCut_pp && electronCut; 
        commonCutMC = etaCut && hoeCut_pp && trigCut_mc_pp_low && sigmaCut_pp && isoCut_pp && electronCut;
    }
    compareThree(t1, t2, t3, "phoEtCorrected",nBins, 20, 180.0,commonCutMC && mcIsolation,commonCutMC && mcBkgIsolation,commonCutDATA,cap,doWeight,doEmEnr);
    //if(coll=="pbpb") compareThree(t1, t2, t3, "hiBin",nBins, 0, 200.0,commonCutMC && mcIsolation,commonCutMC && mcIsolation,commonCutDATA,cap,doWeight,doEmEnr);
    compareThree(t1, t2, t3, "phoEta",nBins, -1.44, 1.44,commonCutMC && mcIsolation,commonCutMC && mcIsolation,commonCutDATA,cap,doWeight,doEmEnr);
    compareThree(t1, t2, t3, "phoPhi",nBins, -TMath::Pi(), TMath::Pi(),commonCutMC && mcIsolation,commonCutMC && mcIsolation,commonCutDATA,cap,doWeight,doEmEnr);

   // for(Int_t ipt = 0; ipt < nPtBinIF; ++ipt){
   //     TCut ptCut = Form("(phoEt>=%f)&&(phoEt<%f)", ptBins_i[ipt], ptBins_f[ipt]);
   //     for(Int_t jcent = 0; jcent < nCentBinIF; ++jcent){
   //         TCut centCut = Form("(hiBin>=%d)&&(hiBin<%d)",centBins_i[jcent],centBins_f[jcent]);
   //         TCut totComCutMC = commonCutMC && ptCut && centCut;
   //         TCut totComCutDATA = commonCutDATA && ptCut && centCut;

   //         cap = Form("hoecut_%s_pt%dto%d_cent%dto%d",coll.Data(),(int)ptBins_i[ipt],(int)ptBins_f[ipt],centBins_i[jcent]/2,centBins_f[jcent]/2);
   //         //cap = Form("%s_pt%dto%d_cent%dto%d",coll.Data(),(int)ptBins_i[ipt],(int)ptBins_f[ipt],centBins_i[jcent]/2,centBins_f[jcent]/2);
   //         //cout << totComCutMC.GetTitle() << endl;
   //         //compareThree(t1, t2, t3, "phoSCEtaWidth",nBins, 0.005, 0.035,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         //compareThree(t1, t2, t3, "phoSCPhiWidth",nBins, 0.005, 0.2,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "phoSCBrem",nBins, 0.5, 15,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "phoR9",nBins, 0.1, 1.,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "phoHoverE",nBins, 0, 1.0,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "phoE3x3",nBins, 0, 50,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "phoE1x5",nBins, 0, 150,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "phoE2x5",nBins, 0, 150,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         //compareThree(t1, t2, t3, "phoMaxEnergyXtal",nBins, 0, 300,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "phoSigmaIEtaIEta_2012",nBins, 0.005, 0.025,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         //compareThree(t1, t2, t3, "phoE3x3_2012",nBins, 0, 600,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         
   //         compareThree(t1, t2, t3, "pho_ecalClusterIsoR2",nBins, -5,45 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pho_ecalClusterIsoR3",nBins, -5,45 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pho_ecalClusterIsoR4",nBins, -5,45 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pho_ecalClusterIsoR5",nBins, -5,45 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pho_hcalRechitIsoR2",nBins, -5,45 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pho_hcalRechitIsoR3",nBins, -5,45 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pho_hcalRechitIsoR4",nBins, -5,45 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pho_hcalRechitIsoR5",nBins, -5,45 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pho_trackIsoR2PtCut20",nBins, -5,45 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pho_trackIsoR3PtCut20",nBins, -5,45 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pho_trackIsoR4PtCut20",nBins, -5,45 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pho_trackIsoR5PtCut20",nBins, -5,45 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pho_ecalClusterIsoR2+pho_hcalRechitIsoR2+pho_trackIsoR2PtCut20",nBins, -5,45 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pho_ecalClusterIsoR3+pho_hcalRechitIsoR3+pho_trackIsoR3PtCut20",nBins, -5,45 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20",nBins, -5,45 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pho_ecalClusterIsoR5+pho_hcalRechitIsoR5+pho_trackIsoR5PtCut20",nBins, -5,45 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pfcIso1",nBins, 0,50 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pfcIso2",nBins, 0,50 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pfcIso3",nBins, 0,50 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pfcIso4",nBins, 0,50 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pfcIso5",nBins, 0,50 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pfpIso1",nBins, 0,50 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pfpIso2",nBins, 0,50 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pfpIso3",nBins, 0,50 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pfpIso4",nBins, 0,50 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pfpIso5",nBins, 0,50 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pfnIso1",nBins, 0,50 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pfnIso2",nBins, 0,50 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pfnIso3",nBins, 0,50 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pfnIso4",nBins, 0,50 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pfnIso1+pfcIso1+pfpIso1",nBins, 0,50 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pfnIso2+pfcIso2+pfpIso2",nBins, 0,50 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pfnIso3+pfcIso3+pfpIso3",nBins, 0,50 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pfnIso4+pfcIso4+pfpIso4",nBins, 0,50 ,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "pfnIso5+pfcIso5+pfpIso5",nBins, 0,50 ,totComCutMC,totComCutMC,totComCutDATA,cap);
/* //           
   //         compareThree(t1, t2, t3, "phoSCE",nBins*2, 50, 500,cut1 && totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "phoHadTowerOverEm",nBins, 0, 2.,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "phoSigmaIEtaIEta",nBins, 0.002, 0.024,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "phoE5x5",nBins, 0, 700,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "phoSigmaEtaEta",nBins, 0, 0.02,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "phoR1x5",nBins, 0.2, 1,totComCutMC,totComCutMC,totComCutDATA,cap);
   //         compareThree(t1, t2, t3, "phoR2x5",nBins, 0.5, 1,totComCutMC,totComCutMC,totComCutDATA,cap);
*/
   //     }
   // }
} // main function

int compareThree(TTree* t1, TTree* t2, TTree* t3, TString var, int nBins, double xMin, double xMax, TCut cut1, TCut cut2, TCut cut3, const char* cap, bool doWeight, bool doEmEnr)  {
    gStyle->SetOptStat(0);
    TH1::SetDefaultSumw2();
    int i = 1;
    //static int i = 1;
    TCanvas* c =new TCanvas(Form("c_%s_%s",var.Data(),cap),"", 400,600);
    ratioPanelCanvas(c);
    c->cd(1);

    TLegend* l1 = new TLegend(0.6,0.77,0.92,0.92);
    l1->SetName(Form("l1_%s_%s",var.Data(),cap));
    legStyle(l1);
    //if(var!="phoEta" && var!="phoPhi") 

    TH1D* h1;
    h1 = new TH1D(Form("h1_%s_%s",var.Data(),cap), Form(";%s;",var.Data()), nBins,xMin,xMax);
    TH1D* h2 = (TH1D*)h1->Clone(Form("h2_%s_%s",var.Data(),cap));
    TH1D* h3 = (TH1D*)h1->Clone(Form("h3_%s_%s",var.Data(),cap));

    h1->Sumw2();
    h2->Sumw2();
    h3->Sumw2();
    if(doWeight) t1->Draw(Form("%s>>%s",var.Data(),h1->GetName()), Form("(weight)*(%s)",cut1.GetTitle()));
    else t1->Draw(Form("%s>>%s",var.Data(),h1->GetName()), Form("(%s)",cut1.GetTitle()));
    h1=(TH1D*)gDirectory->Get(h1->GetName());
    if(doEmEnr){ 
        if(doWeight) t2->Draw(Form("%s>>%s",var.Data(),h2->GetName()), Form("(weight)*(%s)",cut2.GetTitle()));	
        else t2->Draw(Form("%s>>%s",var.Data(),h2->GetName()), Form("(%s)",cut2.GetTitle()));	
        h2=(TH1D*)gDirectory->Get(h2->GetName());
    }
    t3->Draw(Form("%s>>%s",var.Data(),h3->GetName()), Form("(%s)",cut3.GetTitle()));	
    h3=(TH1D*)gDirectory->Get(h3->GetName());
    h1->Scale( 1. / h1->Integral(),"width");
    if(doEmEnr) h2->Scale( 1. / h2->Integral(),"width");
    h3->Scale( 1. / h3->Integral(),"width");
    //cout << cut1.GetTitle() << endl;	
    //////////////////////////////////
    // Cosmetics
    h3->SetMarkerStyle(20);
    h3->SetMarkerSize(0.6);
    h3->SetMarkerColor(1);
    //h3->SetMarkerColor(1);
    h3->SetLineColor(1);
    h3->SetTitleSize(13);
//    h1->SetFillColor(30);
//    h1->SetFillStyle(3001);
//    h1->SetLineColor(8);
    h1->SetFillColor(46);
    h1->SetFillStyle(3354);
    //h1->SetFillStyle(3001);
    h1->SetLineColor(2);
    h2->SetFillColor(38);
    h2->SetFillStyle(3345);
    //h2->SetFillStyle(3001);
    h2->SetLineColor(9);

    double YminVal;
   if(doEmEnr) YminVal = cleverRange(h1,h2,h3,1.2);
   else YminVal = cleverRange(h1,h3,1.2);
    h3->SetTitle(";;Arbitrary normalization");
    SetHistTextSize(h3);
    if((var!="phoEta" && var!="phoPhi") && YminVal!=0) c->GetPad(1)->SetLogy();

    l1->AddEntry(h3,"DATA","pl");
    //l1->AddEntry(h3,"PbPb DATA","pl");
    l1->AddEntry(h1,"Signal MC","F");
    if(doEmEnr) l1->AddEntry(h2,"Background MC","F");	
    h3->DrawCopy("p e");
   if(doEmEnr)  h2->DrawCopy("hist e same");
    h1->DrawCopy("hist e same");
    l1->Draw();
    //drawText("PbPb 5 TeV",0.91,0.76,1);
    float xpos = 0.91;
    float ypos = 0.72;
    float dy = 0.05;
    drawText("|#eta|<1.44",xpos,ypos,1);
    drawText("p_{T}^{#gamma}>20 GeV",xpos,ypos-dy,1);
    drawText("H/E<0.1",xpos,ypos-dy*2,1);
    drawText("#sigma_{i#etai#eta}<0.01",xpos,ypos-dy*3,1);
    drawText("sumIso<1 GeV",xpos,ypos-dy*4,1);

    c->cd(2);
    h1->Divide(h3);
    if(doEmEnr) h2->Divide(h3);
    TString varName = "corrected p_{T}^{#gamma}";
    if(var=="phoEtCorrected") varName = "corrected p_{T}^{#gamma}";
    else if(var=="phoEta") varName = "#eta^{#gamma}";
    else if(var=="phoPhi") varName = "#phi^{#gamma}";
    h1->SetTitle(Form(";%s;MC/DATA",varName.Data()));
    //double ratioRange = getCleverRange(h1);
    h1->SetAxisRange(0,2,"Y");
    SetHistTextSize(h1);
    SetHistTextSize(h2);
    h1->DrawCopy("le1");
    if(doEmEnr) h2->DrawCopy("le1 same");
    jumSun(xMin,1,xMax,1);
    //drawText(cap,0.2,c->GetPad(2)->GetBottomMargin()+0.04);

    //fitting 
    //TF1* f1 = new TF1("f1", "pol1",0.005,0.02);
    //h1->Fit(f1,"Q R");
    //c->GetPad(1)->SetLogy();
    if(doEmEnr) c->SaveAs(Form("figures/compareDATA_MCs/compare_Data_AllQCD_EmEnr_%s_%s.pdf",var.Data(),cap));
    else c->SaveAs(Form("figures/compareDATA_MCs/compare_Data_AllQCD_%s_%s.pdf",var.Data(),cap));
    i++;
    delete c;
    delete h1;
    delete h2;
    delete h3;
    delete l1;
    return 1;
}
