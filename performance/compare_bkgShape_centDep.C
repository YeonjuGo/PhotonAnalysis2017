// 2016 Mar 3. comparing two datasets (ex. allqcdphoton and emenricheddijet) 
// Modified : 30 May 2017
// Author : Yeonju Go

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_170523_temp_v1.h"

void compareTwo(TTree* t1=0 ,TTree* t2=0,TString var="pt", int nBins=10, double xMin=0, double xMax=10, TCut cut1="",TCut cut2="", const char* cap="");
void compare_bkgShape_centDep(TString coll="pbpb"){

    const char* fname_1 ="";
    const char* fname_2 ="";
    if(coll=="pp"){ 
        fname_1=ppDatafname;
        fname_2=ppMCEmEnrfname;
    } else if(coll=="pbpb"){
        fname_1=pbpbDatafname;
        fname_2=pbpbMCEmEnrfname;
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

    float sumIsoBins[] = {1.,5.,10.,15.,20.,25.,30.,40.,60.,100.};
    int nBinsSumIso = sizeof(sumIsoBins)/sizeof(sumIsoBins[0])-1;
    //cout << "nBinsSumIso = " << nBinsSumIso << endl;
    //float sigmaBins[] = {0.00,0.01,0.015,0.020,0.030};
    //int nBinsSigma = sizeof(sigmaBins)/sizeof(sigmaBins[0])-1;

    for(Int_t i = 0; i < nPtBinIF; ++i) 
    {
        TCut ptCut = Form("(phoEtCorrected >= %f) && (phoEtCorrected < %f)", ptBins_i[i], ptBins_f[i]);
        cout << "nBinsSumIso = " << nBinsSumIso << endl;
        for(Int_t k = 0; k < nCentBinIF; ++k){ 
            TCut centCut = Form("(hiBin >= %d) && (hiBin < %d)", centBins_i[k], centBins_f[k]);    
            for(Int_t jj=0;jj<nBinsSumIso;++jj){
                TCut dataTotCut;
                TCut mcTotCut_;
                TCut VariedSumIsoCut = Form("(pho_sumIsoCorrected>%f) && (pho_sumIsoCorrected<=%f)",sumIsoBins[jj],sumIsoBins[jj+1]);
                //TCut sumIsoCut = Form("((pho_ecalClusterIsoR4 + pho_hcalRechitIsoR4 + pho_trackIsoR4PtCut20)>%f) && ((pho_ecalClusterIsoR4 + pho_hcalRechitIsoR4 + pho_trackIsoR4PtCut20)<=%f)",sumIsoBins[jj],sumIsoBins[jj+1]);
                if(coll=="pp") dataTotCut = trigCut && evtSelFilterCut_pp && hoeCut_ppGED && VariedSumIsoCut && ptCut && etaCut && hotspotCut && spikeRejection;
                else dataTotCut = trigCut && evtSelFilterCut && hoeCut && VariedSumIsoCut && ptCut && etaCut && centCut && hotspotCut && spikeRejection;
               // if(coll=="pp") mcTotCut_ = mcBkgIsolation && hoeCut_ppGED && ptCut && etaCut;
               // else mcTotCut_ = mcBkgIsolation && hoeCut && ptCut && etaCut;
                if(coll=="pp") mcTotCut_ = mcBkgIsolation && hoeCut_ppGED && ptCut && etaCut && VariedSumIsoCut;
                else mcTotCut_ = mcBkgIsolation && hoeCut && ptCut && etaCut && VariedSumIsoCut;
                const char* cap = Form("%s_pt%dto%d_cent%dto%d_sumIso%dto%d_mcTotWeighted_WITHSumIsoCutOnMC",coll.Data(),(int)ptBins_i[i],(int)ptBins_f[i],(int)centBins_i[k]/2,(int)centBins_f[k]/2,(int)sumIsoBins[jj],(int)sumIsoBins[jj+1]);
                //const char* cap = Form("%s_pt%dto%d_cent%dto%d_sumIso%dto%d_mcTotWeighted_noSumIsoCutOnMC",coll.Data(),(int)ptBins_i[i],(int)ptBins_f[i],(int)centBins_i[k]/2,(int)centBins_f[k]/2,(int)sumIsoBins[jj],(int)sumIsoBins[jj+1]);
                compareTwo(t1, t2, "phoSigmaIEtaIEta_2012",50, 0., 0.030, dataTotCut, mcTotCut_,cap);
                //compareTwo(t1, t2, "pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20",100, -100, 300, dataTotCut, mcTotCut_,cap);
                /*
                   TCut sigmaCut = Form("((phoSigmaIEtaIEta_2012)>%.3f) && ((phoSigmaIEtaIEta_2012)<=%.3f)",sigmaBins[jj],sigmaBins[jj+1]);
                //        if(coll=="pp") dataTotCut = evtSelFilterCut_pp && hoeCut_ppGED && sigmaCut && ptCut && etaCut && hotspotCut && spikeRejection;
                //        else if(coll=="pbpb") dataTotCut = evtSelFilterCut && hoeCut && sigmaCut && ptCut && etaCut && hotspotCut && spikeRejection;
                //TCut mcTotCut_ = mcBkgIsolation && dataTotCut; 
                //cout << dataTotCut.GetTitle() << endl;
                //cout << mcTotCut_.GetTitle() << endl;

                //const char* cap = Form("%s_sigma%.3fto%.3f_pt%dto%d",coll.Data(),sigmaBins[j],sigmaBins[j+1],(int)ptBins[i],(int)ptBins[i+1]);
                //const char* cap = Form("%s_sumIso%dto%d_pt%dto%d",coll.Data(),sumIsoBins[j],sumIsoBins[j+1],(int)ptBins[i],999);
                //compareTwo(t1, t2, "pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20",100, -100, 300, dataTotCut, mcTotCut_,cap);
                */
            }
        }
    }  
} // main function

void compareTwo(TTree* t1, TTree* t2, TString var, int nBins, double xMin, double xMax, TCut cut1, TCut cut2, const char* cap)  {
    SetHistTitleStyle();
    SetyjPadStyle();
    gStyle->SetOptStat(0);
    TH1::SetDefaultSumw2();
    static int i = 1;
    TCanvas* c =new TCanvas(Form("c_%s_%d",var.Data(),i),"", 400,800);
    c->Divide(1,2);
    c->cd(1);
    gPad->SetLogy();
    double ptbin[] = {60,70,80,90,100,110,120,130,140,150,170,200,250};
    int nptbin = sizeof(ptbin)/sizeof(double) -1;
    TH1D* h1;
    if(var=="phoEt") h1 = new TH1D(Form("h1_%s_%d",var.Data(),i), Form(";%s;",var.Data()),nptbin, ptbin);
    else h1 = new TH1D(Form("h1_%s_%d",var.Data(),i), Form(";%s;",var.Data()), nBins,xMin,xMax);
    TH1D* h2 = (TH1D*)h1->Clone(Form("h2_%s_%d",var.Data(),i));

    h1->Sumw2();
    h2->Sumw2();
    t1->Draw(Form("%s>>%s",var.Data(),h1->GetName()), cut1);
    t2->Draw(Form("%s>>%s",var.Data(),h2->GetName()), cut2);
    //t2->Draw(Form("%s>>%s",var.Data(),h2->GetName()), Form("(pthatWeight*vtxWeight*centWeight)*(%s)",cut2.GetTitle()));	
    h1->Scale( 1. / h1->Integral(),"width");
    h2->Scale( 1. / h2->Integral(),"width");
    h1->SetMarkerStyle(20);
    h1->SetMarkerSize(0.8);
    h1->SetMarkerColor(2);
    double range;
    if(var=="phoEt") range = cleverRange(h1,h2,1.5,1.e-4);
    else if(var=="phoHoverE") range = cleverRange(h1,h2,1.5,1.e-4);
    else  range = cleverRange(h1,h2,1.5,1.e-7);
    range = cleverRangeOnlyMax(h1,h2,1.5,1.e-2);
    h1->DrawCopy("L hist e");
    h2->DrawCopy("hist e same");
    TLegend* l1 = new TLegend(0.7,0.7,0.95,0.9);
    legStyle(l1);
    l1->AddEntry(h1,"DATA","pl");
    l1->AddEntry(h1,"EmEnrDijet","l");
    l1->Draw();

    c->cd(2);
    h1->Divide(h2);
    h1->SetYTitle("DATA / Em-Enriched Dijet");
    double ratioRange = getCleverRange(h1);
    //if(ratioRange > 5) h1->SetAxisRange(0,5,"Y");
    //else h1->SetAxisRange(0,2,"Y");
    h1->SetAxisRange(0,2,"Y");
    //h1->SetAxisRange(0,3,"Y");
    h1->DrawCopy("le1");

    //fitting 

    TF1* f1 = new TF1("f1", "pol1",0.005,0.02);
    h1->Fit(f1,"Q R");
    jumSun(xMin,1,xMax,1);
    drawText(cap,0.2,0.2);
    c-> SaveAs(Form("figures/compare_%s_%s.pdf",var.Data(),cap));
    i++;
}
