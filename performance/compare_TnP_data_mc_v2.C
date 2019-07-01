// comparison isolation variables between DATA and MC 
// Author : Yeonju Go

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
void compareTwo(TTree* t1=0 ,TTree* t2=0,TString var="pt", int nBins=10, double xMin=0, double xMax=10, TCut cut1="(1)", TCut cut2="(1)", const string cap = "", bool doWeight=true);
void compare_TnP_data_mc_v2(TString coll="PbPb", TString cap="_passID", TString ver="v21", bool doWeight=true){
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);
    SetyjPadStyle();

    //set file location
    const char* fname_data;
    const char* fname_mc;

    fname_data = Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/TnP/pho_TnP/fillTree/output_data_%s_%s%s.root",coll.Data(),ver.Data(),cap.Data());
    fname_mc = Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/TnP/pho_TnP/fillTree/output_mc_%s_%s%s.root",coll.Data(),ver.Data(),cap.Data());
    //fname_data = Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/TnP/pho_TnP/fillTree/output_data_%s_%s_noTrigCut.root",coll.Data(),ver.Data());
    //fname_mc = Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/TnP/pho_TnP/fillTree/output_mc_%s_%s%s_noTrigCut.root",coll.Data(),ver.Data(),cap.Data());

    TFile* f1 = new TFile(fname_data);
    TTree* t1 = (TTree*) f1->Get("phoTree/fitter_tree"); 
    TFile* f2 = new TFile(fname_mc);
    TTree* t2 = (TTree*) f2->Get("phoTree/fitter_tree"); 

    TCut cut1 = "(1==1)";
    TCut cut2 = "(1==1)";
    string cap_ =Form("%s_%s%s",coll.Data(),ver.Data(),cap.Data());
    //cap_ += "_noTrigCut";
    if(!doWeight) cap_ += "_noReweight";
    cout << "s" << endl;
    if(coll=="PbPb") compareTwo(t1,t2,"centBin",20,0,200,cut1,cut2,cap_);
    int nbins = 40;
    compareTwo(t1,t2,"probe_pt",nbins,15,130,cut1,cut2,cap_,doWeight);
    compareTwo(t1,t2,"probe_abseta",20,0,1.5,cut1,cut2,cap_,doWeight);
    compareTwo(t1,t2,"probe_eta",20,-1.5,1.5,cut1,cut2,cap_,doWeight);
    compareTwo(t1,t2,"probe_hoe",nbins/2,0,0.05,cut1,cut2,cap_,doWeight);
    compareTwo(t1,t2,"probe_sigmaIetaIeta",nbins,0,0.02,cut1,cut2,cap_,doWeight);
    compareTwo(t1,t2,"probe_hcalRechitIsoR4",nbins,-2,2,cut1,cut2,cap_,doWeight);
    compareTwo(t1,t2,"probe_ecalClusterIsoR4",nbins,-2,2,cut1,cut2,cap_,doWeight);
    compareTwo(t1,t2,"probe_hcalRechitIsoR4+probe_ecalClusterIsoR4",nbins,-2,2,cut1,cut2,cap_,doWeight);
    compareTwo(t1,t2,"probe_sumIso",nbins,-2,2,cut1,cut2,cap_,doWeight);
    compareTwo(t1,t2,"tag_pt",nbins,15,130,cut1,cut2,cap_,doWeight);
    compareTwo(t1,t2,"tag_eta",20,-1.5,1.5,cut1,cut2,cap_,doWeight);
    compareTwo(t1,t2,"tag_hoe",nbins/2,0,0.05,cut1,cut2,cap_,doWeight);
    compareTwo(t1,t2,"tag_sigmaIetaIeta",nbins,0,0.015,cut1,cut2,cap_,doWeight);
    //compareTwo(t1,t2,"tag_hcalRechitIsoR4",nbins,-2,2,cut1,cut2,cap_,doWeight);
    //compareTwo(t1,t2,"tag_ecalClusterIsoR4",nbins,-2,2,cut1,cut2,cap_,doWeight);
    //compareTwo(t1,t2,"tag_hcalRechitIsoR4+tag_ecalClusterIsoR4",nbins,-2,2,cut1,cut2,cap_,doWeight);
    //compareTwo(t1,t2,"tag_sumIso",nbins,-2,2,cut1,cut2,cap_,doWeight);

} // main function

void compareTwo(TTree* t1, TTree* t2, TString var, int nBins, double xMin, double xMax, TCut cut1, TCut cut2, const string cap, bool doWeight)  {
    SetHistTitleStyle();
    SetyjPadStyle();
    gStyle->SetOptStat(0); 
    static int j = 0;
    cout << "here1" << endl;
    TCanvas* c =new TCanvas(Form("c_%s_%d",var.Data(),j),"", 400,600);
    ratioPanelCanvas(c);
    c->cd(1);
    //TCanvas* c=  new TCanvas(Form("c_%s_%d",var.Data(),j),"", 400,800);
	//c->Divide(1,2);
	//c->cd(1);
	//if(var=="probe_hoe" || var=="tag_hoe") gPad->SetLogy();
    TString xTitle = var;
    if(var=="pho_ecalClusterIsoR4+pho_hcalRechitIsoR4+pho_trackIsoR4PtCut20") xTitle = "sumIso";
	TH1D* h1 = new TH1D(Form("h1_%s_%d",var.Data(),j), Form(";%s;",xTitle.Data()), nBins,xMin,xMax);
	TH1D* h2 = (TH1D*)h1->Clone(Form("h2_%s_%d",var.Data(),j));
    cout << "here2" << endl;
	h1->Sumw2();
	h2->Sumw2();
    if(doWeight){
        t1->Draw(Form("%s>>%s",var.Data(),h1->GetName()), Form("(%s)*(%s)",cut1.GetTitle(),"final_weight"));
        t2->Draw(Form("%s>>%s",var.Data(),h2->GetName()), Form("(%s)*(%s)",cut2.GetTitle(),"final_weight"));	
    } else{
        t1->Draw(Form("%s>>%s",var.Data(),h1->GetName()), cut1);
        t2->Draw(Form("%s>>%s",var.Data(),h2->GetName()), cut2);	
    }
	h1->Scale( 1. / h1->Integral());
	h2->Scale( 1. / h2->Integral());
	//h1->Scale( 1. / t1->GetEntries(cut1));
	//h2->Scale( 1. / t2->GetEntries(cut2));
    SetHistColor(h1,2);
    SetHistColor(h2,1);
    h1->SetMarkerStyle(20);
	h1->SetMarkerSize(0.8);
    h1->SetNdivisions(505);
    h2->SetNdivisions(505);
    SetHistTextSize(h1);
    cout << "here3" << endl;
    SetHistTextSize(h2);
    TLegend* l1 = new TLegend(0.6,0.7,0.9,0.9);
    legStyle(l1);
    l1->AddEntry(h1, "DATA", "p");
    l1->AddEntry(h2, "MC", "l");
    cout << "here3.1" << endl;

    double range = cleverRange(h1,h2,1.5,1.e-4);
	h1->DrawCopy("L e");
	h2->DrawCopy("hist e same");
    l1->Draw("e same");
    
    c->cd(2);
	h1->Divide(h2);
    cout << "here3.2" << endl;
	h1->SetYTitle("DATA / MC");
	h1->GetYaxis()->SetRangeUser(0.0,2.0);
    SetHistColor(h1,2);
    h1->SetMarkerStyle(20);
	h1->SetMarkerSize(0.8);
    SetHistTextSize(h1);
	h1->DrawCopy("");
    cout << "here3.3" << endl;
	//h2->DrawCopy("le1");
	jumSun(xMin,1,xMax,1);
    drawText(cap.data(),0.2,0.2+0.7);
    cout << "here4" << endl;
    //drawText("pcollisionEventSelection",0.2,0.2);
	c-> SaveAs(Form("figures/compare_TnP_data_mc_%s_%s.pdf",xTitle.Data(),cap.data()));
    j++;
}
