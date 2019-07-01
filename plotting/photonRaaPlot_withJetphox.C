// photonRaaPlot.C
// draw the final plots 
// Author: Yeonju Go
// Modified at 2018 June 10

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
//#include "../phoRaaCuts/temp_phoRaaCuts_temp.h"
//#include "../phoRaaCuts/styleUtil.h"
#include "../phoRaaCuts/tdrstyle.C"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TAttFill.h"

static const float ncoll_w_npart[4] = {43.58, 118.8, 239.9, 363.4};
void draw_sys_unc(TGraphErrors* gr, TH1* h1, TH1* h1_sys);
void draw_npart_sys_unc(TGraphErrors* gr, TH1* h1, TH1* h1_sys, int x_width);

const int markerStyle[]={20,33,34,29,20,29};
const int markerStyle_pp=21;//square
const int colorStyle_marker_pp=kOrange+7;
const int colorStyle_line_pp=kOrange+7;
const int colorStyle_sys_pp=kOrange+6;
const int colorStyle_marker[]={kBlack,kPink-6,kGreen+3,kBlue-3,kOrange+4};
const int colorStyle_sys[]={kYellow-7,kRed-10,kGreen-10,kBlue-10,kOrange-3};
const int colorStyle_line[]={kYellow-4,kPink-6,kGreen+3,kBlue-3,kOrange+4};
const double transparency[]={0.5,0.5,0.5,0.5,0.5,0.5};
const double scale[]={0,10.,100.,1000.,10000.,100000.};

TGraphAsymmErrors* scale_graph(TGraphAsymmErrors* gr, Float_t s);
TGraphAsymmErrors* devide_graph_by_hist(TGraphAsymmErrors* gr, TH1D* h1);
#define TH1_TO_TGRAPH(hist, graph,points)                                      \
    int npoints = hist->GetNbinsX();                                    \
graph = new TGraphAsymmErrors(points);                                 \
for (int p=0; p<points; ++p) {                                         \
    double Xmean = ptBins_mean_pbpb[p];                                 \
    double Ymean = hist->GetBinContent(p+1);                            \
    double Xerr_l= Xmean-ptBins_draw[p];                                \
    double Xerr_h= ptBins_draw[p+1]-Xmean;                              \
    double Yerr_l= hist->GetBinError(p+1);                              \
    double Yerr_h= hist->GetBinError(p+1);                              \
    graph->SetPoint(p, Xmean, Ymean);                                   \
    graph->SetPointError(p,Xerr_l,Xerr_h,Yerr_l,Yerr_h);                \
}

void photonRaaPlot_withJetphox(TString ver="190303_temp_v28", bool doJETPHOX = true) {
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    
    TString cap = Form("%s_withJetphox_ppNLO",ver.Data());
    // input files 
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/";
    const std::string input_file = Form("%sresults/output/phoRaa_afterUnfolding_%s_nominal.root",dir.Data(),ver.Data());
    const std::string sys_file = Form("%ssystematics/output/systematics_%s.root",dir.Data(),ver.Data());
    //const std::string sys_file = Form("%ssystematics/output/systematics_%s_cent0to100.root",dir.Data(),ver.Data());
    TFile* input = new TFile(input_file.c_str(), "read");
    TFile* sys = new TFile(sys_file.c_str(), "read");

    cout << "input files done" << endl;
    // define histogram types  
    std::vector<std::string> hist_types {
        "Raa", "dNdpt_corr2", "dNdpt_corr2_pp"
    };
    int n_hist_types = hist_types.size(); 

    ///////////////////////////////////////////////////////////////////////////////////////
    // Global Uncertainty
    double sys_ppLumi = 0.023; 
    double sys_global[nCentBinIF];
    for (int k=0; k<nCentBinIF; ++k) //k=0 is 0-100 % 
        sys_global[k] = TMath::Sqrt(TA_err[k]*TA_err[k]+sys_ppLumi*sys_ppLumi);
    //double sys_global = TMath::Sqrt(sys_MB*sys_MB+sys_ppLumi*sys_ppLumi); 

    // define histograms, graphs, ..., etc 
    TObject* generic[n_hist_types][nCentBinIF];
    TH1D* h1D_nominal[n_hist_types][nCentBinIF];
    TH1D* systematics[n_hist_types][nCentBinIF];            
    TH1D* h1D_nominal_withUnderOverFlowBins[n_hist_types][nCentBinIF];
    TH1D* systematics_withUnderOverFlowBins[n_hist_types][nCentBinIF];            
    TH1D* htemp[n_hist_types]; // for cosmetics, will draw axis and its titles
    TGraphAsymmErrors* gr_sys[n_hist_types][nCentBinIF];
    TGraphAsymmErrors* gr_nominal[n_hist_types][nCentBinIF];
    TGraphAsymmErrors* gr_sys_scaled[nCentBinIF]; // for dNdpt
    TGraphAsymmErrors* gr_sys_jp_data_ratio[nCentBinIF]; // for the ratio of dNdpt and JETPHOX
    TGraphAsymmErrors* gr_nominal_scaled[nCentBinIF]; // for dNdpt

    ///////////////////////////////////////////////////////////////////////////////////////
    // Define graphs and histgorams  
    cout << "define graphs and histograms..." << endl;
    TCanvas* c_temp = new TCanvas(Form("c_%s","temp"),"",600,600);
    for (int i=0; i<n_hist_types; ++i) {
        c_temp->cd();
        for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100 % 
            if(hist_types[i] == "dNdpt_corr2_pp" && k>0) continue; 

            std::string hist_name;
            if(hist_types[i] == "dNdpt_corr2_pp"){
                hist_name = Form("h1D_%s", hist_types[i].c_str());
                if(k>0) continue;
            } else{
                hist_name = Form("h1D_%s_cent%d", hist_types[i].c_str(), k);
            }
            cout << "histname : " << hist_name  << endl;

            // nominal value part
            generic[i][k] = input->Get(hist_name.data());
            h1D_nominal_withUnderOverFlowBins[i][k] = (TH1D*)generic[i][k];
            systematics_withUnderOverFlowBins[i][k] = (TH1D*)sys->Get((hist_name + "_diff_total").c_str());
            h1D_nominal[i][k] = removeHistFirstAndLastBins(h1D_nominal_withUnderOverFlowBins[i][k]); 
            systematics[i][k] = removeHistFirstAndLastBins(systematics_withUnderOverFlowBins[i][k]); 
            
            //systematics[i][k] = (TH1D*)sys->Get((hist_name + "_diff_sys_purUp_sys_purDown_total").c_str()); //this is only purity up and down

            // histogram cosmetics 
            if(k==0){    
                if(hist_types[i] == "Raa") htemp[i] = new TH1D(Form("htemp_%d",i),"",nPtBin+1,ptBins_draw_final); 
                else htemp[i] = new TH1D(Form("htemp_%d",i),"",nPtBin,ptBins_draw); 
                if(hist_types[i] == "Raa") htemp[i]->GetYaxis()->SetRangeUser(0.0,2.0);
            }
            h1D_nominal[i][k]->SetMarkerColor(colorStyle_marker[k]);
            h1D_nominal[i][k]->SetLineColor(colorStyle_marker[k]);
            h1D_nominal[i][k]->SetMarkerStyle(markerStyle[k]);
            h1D_nominal[i][k]->SetFillStyle(3001);
            h1D_nominal[i][k]->SetFillColor(colorStyle_sys[k]);
            if(markerStyle[i]==33) h1D_nominal[i][k]->SetMarkerSize(1.6);
            else h1D_nominal[i][k]->SetMarkerSize(1);
            if(hist_types[i] == "dNdpt_corr2_pp"){
                h1D_nominal[i][k]->SetMarkerColor(colorStyle_marker_pp);
                h1D_nominal[i][k]->SetLineColor(colorStyle_line_pp);
                h1D_nominal[i][k]->SetFillColor(colorStyle_sys_pp);
                h1D_nominal[i][k]->SetMarkerStyle(21);
            } 

            // histogram to graph for nominal value 
            
            TH1_TO_TGRAPH(h1D_nominal[i][k], gr_nominal[i][k],nPtBin-rejectPtBins[k]);
                gr_nominal[i][k]->SetMarkerColor(colorStyle_marker[k]);
            gr_nominal[i][k]->SetLineColor(colorStyle_marker[k]);
            gr_nominal[i][k]->SetMarkerStyle(markerStyle[k]);
            if(hist_types[i] != "Raa") gr_nominal[i][k]->SetMarkerSize(1.8);
            if(hist_types[i] == "dNdpt_corr2_pp"){
                gr_nominal[i][k]->SetMarkerColor(colorStyle_marker_pp);
                gr_nominal[i][k]->SetLineColor(colorStyle_line_pp);
                gr_nominal[i][k]->SetMarkerStyle(markerStyle_pp);
            } 

            //systematic part
            //gr_sys[i][k] = new TGraphAsymmErrors(gr_nominal[i][k]);
            gr_sys[i][k] = new TGraphAsymmErrors(nPtBin-rejectPtBins[k]);
            //gr_sys[i][k] = new TGraphAsymmErrors(h1D_nominal[i][k]);
            gr_sys[i][k]->SetName(Form("gr_sys_%d_%d",i,k));
            gr_sys[i][k]->SetFillStyle(3001);
            gr_sys[i][k]->SetFillColor(colorStyle_sys[k]);
            cout <<  h1D_nominal[i][k]->GetNbinsX()<< endl;
            //cout << h1D_nominal[i][k]->GetNbinsX() << endl;
            
            //for (int ipt=1; ipt<=h1D_nominal[i][k]->GetNbinsX(); ++ipt) {
            //ipt starting from 2 when using Unfolding underflow bin!!
            //ipt starting from 1 when not using Unfolding underflow bin!!
            for (int ipt=1; ipt<=nPtBin-rejectPtBins[k]; ++ipt) {
            //for (int ipt=2; ipt<=nPtBin-rejectPtBins[k]; ++ipt) {
                //cout << 
                //if (h1D_nominal[i][k]->GetBinError(i) == 0) continue;
                double x = h1D_nominal[i][k]->GetBinCenter(ipt);
                int sys_bin = systematics[i][k]->FindBin(x);
                double bin_width = h1D_nominal[i][k]->GetBinLowEdge(ipt+1) - h1D_nominal[i][k]->GetBinLowEdge(ipt);
                double val = h1D_nominal[i][k]->GetBinContent(ipt);
                double error = TMath::Abs(systematics[i][k]->GetBinContent(sys_bin));
                cout << "histname : " << hist_name << ", ipt " << ipt << ", Systematic Error = " << error << endl;
                Double_t pxtmp, pytmp;
               // //When using unfolding underflow bin
               // gr_sys[i][k]->SetPointError(ipt-2, (bin_width/2), (bin_width/2), error, error); 
               // gr_sys[i][k]->SetPoint(ipt-2, x, val); 
                //When not using unfolding underflow bin
                gr_sys[i][k]->SetPointError(ipt-1, (bin_width/2), (bin_width/2), error, error); 
                gr_sys[i][k]->SetPoint(ipt-1, x, val); 
                cout << "ipt = "<< ipt << ": " << gr_sys[i][k]->GetErrorYhigh(ipt-1) << endl;
            } 

            //systematic cosmetics 
            gr_sys[i][k]->SetFillStyle(1001);
            gr_sys[i][k]->SetFillColorAlpha(colorStyle_sys[k],0.2);
            //gr_sys[i][k]->SetFillColorAlpha(colorStyle_sys[k],0.5-0.05*k);
            if(hist_types[i] == "dNdpt_corr2_pp")   gr_sys[i][k]->SetFillColorAlpha(colorStyle_sys[k],0.2);
            if(hist_types[i] == "Raa") gr_sys[i][k]->GetYaxis()->SetRangeUser(0.5,1.5);

        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////
    // DRAW : Centrality seperately 
    cout << "Draw centrality separately..." << endl;

    setTDRStyle();   
    TCanvas* c_sep[n_hist_types][nCentBinIF];

    TLegend* leg_glo = new TLegend(0.53,0.67,0.94,0.77);
    float dx = 2.5;
    TBox *globalUncBox_pplumi = new TBox(ptBins_draw_final[0],1-sys_ppLumi,ptBins_draw_final[0]+dx,1+sys_ppLumi);
    globalUncBox_pplumi -> SetFillColorAlpha(28,0.5);
    globalUncBox_pplumi -> SetLineColor(kOrange+3);
    globalUncBox_pplumi -> SetLineWidth(2);
    TBox *globalUncBox_TAA[nCentBinIF];
    for (int i=0; i<n_hist_types; ++i) {
        for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100 %
            if(hist_types[i] == "dNdpt_corr2_pp" && k>0) continue;
            if(i==0){
                globalUncBox_TAA[k] = new TBox(ptBins_draw_final[0]+dx,1-TA_err_down[k],ptBins_draw_final[0]+5,1+TA_err_up[k]); // asymetrical TAA uncertainty
                globalUncBox_TAA[k] -> SetFillColorAlpha(kGray+2,0.5);
                globalUncBox_TAA[k] -> SetLineColor(kBlack);
                globalUncBox_TAA[k] -> SetLineWidth(2);
            }
            c_sep[i][k] = new TCanvas(Form("c_%s_%d",hist_types[i].c_str(),k),"",600,600);
            c_sep[i][k]->cd();
            c_sep[i][k]->SetRightMargin(0.05);
            c_sep[i][k]->SetTopMargin(0.07);

            //////////////////////////////
            // cosmetics 
            htemp[i]->GetXaxis()->CenterTitle();
            htemp[i]->GetYaxis()->CenterTitle();
            htemp[i]->GetYaxis()->SetTitleOffset(1.8);
            htemp[i]->GetXaxis()->SetTitleOffset(1.5);
            htemp[i]->GetXaxis()->SetTitleFont(42);
            htemp[i]->GetYaxis()->SetTitleFont(42);
            htemp[i]->GetXaxis()->SetTitleColor(1);
            htemp[i]->GetYaxis()->SetTitleColor(1);
            htemp[i]->GetXaxis()->SetLabelSize(0.04);
            if(hist_types[i] == "Raa"){
                htemp[i]->GetYaxis()->SetTitleOffset(1.4);
                htemp[i]->GetXaxis()->SetTitleOffset(1.2);
            }
            if(hist_types[i] == "Raa") htemp[i]->SetTitle(";Photon E_{T} (GeV/c);R_{AA}");
            else if(hist_types[i] == "dNdpt_corr2") htemp[i]->SetTitle(";Photon E_{T} (GeV/c);#frac{1}{N_{evt}} #frac{1}{<T_{AA}>} #frac{d^{2}N^{PbPb}}{dp_{T}d#eta} (#frac{pb}{GeV/c})");
            else if(hist_types[i] == "dNdpt_corr2_pp") htemp[i]->SetTitle(";Photon E_{T} (GeV);#frac{d^{2}#sigma^{pp}}{dp_{T}d#eta} (#frac{pb}{GeV/c})");

            if(hist_types[i] != "Raa") htemp[i]->GetYaxis()->SetRangeUser(0.01,1.e+5);
            if(hist_types[i] == "dNdpt_corr2" || hist_types[i] == "dNdpt_corr2_pp")
                gPad->SetLogy();

            ////////////////////////////
            // draw graphs 
            gr_sys[i][k]->SetFillColorAlpha(colorStyle_sys[k],0.5);
            htemp[i]->DrawCopy("p");
            gr_sys[i][k]->Draw("2");
            gr_nominal[i][k]->Draw("P");

            ////////////////////////////////
            // Draw CMS latex and lumi etc. 
            TString lumiSt= " 27.4 pb^{-1} pp + 404 #mub^{-1} PbPb (5.02 TeV)";
            drawLumi(c_sep[i][k],lumiSt,0.2); 
            drawCMS(c_sep[i][k],"Preliminary",0.5); 

            float xpos_r = 1-c_sep[i][k]->GetRightMargin();
            float xpos_l = c_sep[i][k]->GetLeftMargin();
            float ypos_t = 1-c_sep[i][k]->GetTopMargin();
            float dy = 0.05; 
            float extraDY = 1.5; 
            drawText(Form("%d-%d %s",(int)centBins_i[k]/2,(int)centBins_f[k]/2,"%"),xpos_r-dy,ypos_t-dy*extraDY,1,kBlack,0.04); 
            drawText("|#eta^{#gamma}| < 1.44",xpos_r-dy,ypos_t-dy*extraDY-dy,1,kBlack,0.04); 
            if(hist_types[i] == "Raa")  jumSun(ptBins_draw_final[0],1,ptBins[nPtBin],1);

            ///////////////////////////////////////
            // Draw global uncertainty box for Raa 
            if(i==0){// for RAA
                //globalUncBox = new TBox(xpos_l+sys_global_x*3,1-sys_global,xmax-sys_global_x*2,1+sys_global);
                globalUncBox_TAA[k] -> Draw("l same");
                globalUncBox_pplumi -> Draw("l same");
                if(k==0){
                    leg_glo->AddEntry(globalUncBox_TAA[k],"T_{AA} uncertainty","f");
                    leg_glo->AddEntry(globalUncBox_pplumi,"Luminosity uncertainty","f");
                }
                leg_glo->Draw("same");
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////
    // DRAW : All centrality in one panel 
    cout << "Draw All centrality bin together in a panel..." << endl;
    TCanvas* c[n_hist_types];
    TLegend* leg_raa = new TLegend(0.65,0.7,0.90,0.9);
    legStyle(leg_raa);
    for (int i=0; i<n_hist_types; ++i) {
        c[i] = new TCanvas(Form("c_%s",hist_types[i].c_str()),"",600,600);
        c[i]->SetRightMargin(0.05);
        c[i]->SetTopMargin(0.07);
        if(hist_types[i] == "dNdpt_corr2_pp") c[i-1]->cd();
        else c[i]->cd();

        for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100 % 
            if(hist_types[i] == "dNdpt_corr2_pp" && k>0) continue;

            ////////////////////////////
            // Dummy hist draw 
            if(hist_types[i] == "Raa") htemp[i]->SetTitle(";Photon E_{T} (GeV);R_{AA}");
            else htemp[i]->SetTitle(";Photon E_{T} (GeV/c);#frac{d^{2}#sigma^{pp}}{dp_{T}d#eta} or #frac{1}{N_{evt}}#frac{1}{<T_{AA}>}#frac{d^{2}N^{PbPb}}{dp_{T}d#eta} (#frac{pb}{GeV/c})");
            if(hist_types[i] != "Raa") htemp[i]->GetYaxis()->SetRangeUser(0.01,1e+10);
            if(k==0 && hist_types[i] != "dNdpt_corr2_pp") htemp[i]->DrawCopy();

            ////////////////////////////
            // Scale dNdpt 
            if(hist_types[i] == "dNdpt_corr2"){
                float scale = 0.;
                if(k==0) continue; 
                else if(k==1) scale = 10.; 
                else if(k==2) scale = 100.; 
                else if(k==3) scale = 1000.; 
                else if(k==4) scale = 10000.; 
                gr_sys_scaled[k] = scale_graph(gr_sys[i][k],scale);
                gr_nominal_scaled[k] = scale_graph(gr_nominal[i][k],scale);
                gr_sys_scaled[k]->Draw("2");
                gr_nominal_scaled[k]->Draw("p");
            } else{
                gr_sys[i][k]->Draw("2");
                gr_nominal[i][k]->Draw("P");
            }

            ////////////////////////////
            // legend and line etc. 
            if(i==0) 
                leg_raa->AddEntry(h1D_nominal[i][k],Form("%d-%d %s",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%"),"plf");
            if(hist_types[i] == "Raa") jumSun(ptBins_draw_final[0],1,ptBins[nPtBin],1);
            if(hist_types[i] == "dNdpt_corr2") gPad->SetLogy();
        }

        ////////////////////////////////
        // Draw CMS latex and lumi etc. 
        TString lumiSt= " 27.4 pb^{-1} pp + 404 #mub^{-1} PbPb (5.02 TeV)";
        drawLumi(c[i],lumiSt,0.2); 
        drawCMS(c[i],"Preliminary",0.5); 
        if(i==0) leg_raa->Draw("same");
    } 


    /////////////////////////////////////////////////////////////////////////////////////////////
    // Draw Jetphox pp NLO
    // direct contribution
    // /home/samba.old/jaebeom/ForYeonju/ggd_2test_aa_CT14lo.root
    // /home/samba.old/jaebeom/ForYeonju/ggo_2test_aa_CT14lo.root
    
    cout << "DRAWING JETPHOX..." << endl; 
    TFile* fdir_pp = TFile::Open("/home/samba.old/jaebeom/ForYeonju/ggd_2test_pp_CT14nlo_true.root","read");
    TFile* fonef_pp = TFile::Open("/home/samba.old/jaebeom/ForYeonju/ggo_2test_pp_CT14nlo_true.root","read");
    TFile* fdir_pbpb = TFile::Open("/home/samba.old/jaebeom/ForYeonju/ggd_2test_aa_CT14nlo_false_601.root","read");
    TFile* fonef_pbpb = TFile::Open("/home/samba.old/jaebeom/ForYeonju/ggo_2test_aa_CT14nlo_false_601.root","read");
    //TFile* fdir_pp = TFile::Open("/home/goyeonju/CMS/2016/JETPHOX/jetphox_1.3.1_3_pp/pawres/ggd_2test_pp_0609.root","read");
    //TFile* fonef_pp = TFile::Open("/home/goyeonju/CMS/2016/JETPHOX/jetphox_1.3.1_3_pp/pawres/ggo_2test_pp_0609.root","read");
    //TFile* fdir_pbpb = TFile::Open("/home/goyeonju/CMS/2016/JETPHOX/jetphox_1.3.1_3_pbpb/pawres/ggd_PbPb5TeV_NLO_EPS09_cteq66.root","read");
    //TFile* fonef_pbpb = TFile::Open("/home/goyeonju/CMS/2016/JETPHOX/jetphox_1.3.1_3_pbpb/pawres/ggo_PbPb5TeV_NLO_EPS09_cteq66.root","read");
    
    cout << "Getting JETPHOX histograms..." << endl; 
    TH1D* h1D_jp[3][2][2];//[0:dir, 1:onef, 2:inclusive] [0:Leading Order, 1:Next-to-Leading Order] [0:pbpb, 1:pp]
    TH1D* TF1[3][2][2];//[0:dir, 1:onef, 2:inclusive] [0:Leading Order, 1:Next-to-Leading Order] [0:pbpb, 1:pp]
    // direct contribution
    h1D_jp[0][0][0] = (TH1D*) fdir_pbpb->Get("hp40");
    h1D_jp[0][0][0]->SetName("jp_dir_lo_pbpb");
    h1D_jp[0][1][0] = (TH1D*) fdir_pbpb->Get("hp41");
    h1D_jp[0][1][0]->SetName("jp_dir_nlo_pbpb");
    h1D_jp[0][0][1] = (TH1D*) fdir_pp->Get("hp40");
    h1D_jp[0][0][1]->SetName("jp_dir_lo_pp");
    h1D_jp[0][1][1] = (TH1D*) fdir_pp->Get("hp41");
    h1D_jp[0][1][1]->SetName("jp_dir_nlo_pp");

    // one fragmentation contribution
    //h1D_jp[1][0][0] = (TH1D*) fonef_pp->Get("hp40");
    h1D_jp[1][0][0] = (TH1D*) fonef_pbpb->Get("hp40");
    h1D_jp[1][0][0]->SetName("jp_onef_lo_pbpb");
    //h1D_jp[1][1][0] = (TH1D*) fonef_pp->Get("hp41");
    h1D_jp[1][1][0] = (TH1D*) fonef_pbpb->Get("hp41");
    h1D_jp[1][1][0]->SetName("jp_onef_nlo_pbpb");
    h1D_jp[1][0][1] = (TH1D*) fonef_pp->Get("hp40");
    h1D_jp[1][0][1]->SetName("jp_onef_lo_pp");
    h1D_jp[1][1][1] = (TH1D*) fonef_pp->Get("hp41");
    h1D_jp[1][1][1]->SetName("jp_onef_nlo_pp");
    
    // direct + one fragmentation
    h1D_jp[2][0][0] = (TH1D*) h1D_jp[1][0][0]->Clone("jp_inclusive_lo_pbpb");
    h1D_jp[2][0][0]->Add(h1D_jp[0][0][0]);
    h1D_jp[2][1][0] = (TH1D*) h1D_jp[1][1][0]->Clone("jp_inclusive_nlo_pbpb");
    h1D_jp[2][1][0]->Add(h1D_jp[0][1][0]);
    h1D_jp[2][0][1] = (TH1D*) h1D_jp[1][0][1]->Clone("jp_inclusive_lo_pp");
    h1D_jp[2][0][1]->Add(h1D_jp[0][0][1]);
    h1D_jp[2][1][1] = (TH1D*) h1D_jp[1][1][1]->Clone("jp_inclusive_nlo_pp");
    h1D_jp[2][1][1]->Add(h1D_jp[0][1][1]);
    

    cout << "Set cosmetics..." << endl; 
    //cosmetics
    for(int icont=0;icont<3;++icont){
    for(int ior=0;ior<2;++ior){
    for(int icoll=0;icoll<2;++icoll){
        h1D_jp[icont][ior][icoll]->Scale(1./2.88);
        if(icoll==0) h1D_jp[icont][ior][0]->SetLineColor(2);
        else h1D_jp[icont][ior][1]->SetLineColor(1);
        h1D_jp[icont][ior][icoll]->SetLineWidth(2);
    }}}
    
    cout << "Draw in cross section panel..." << endl; 
    //final for dndpt
    TH1D* hjp_draw_dndpt[2][nCentBinIF]; //[0:pbpb, 1:pp] [centraltiy] only for inclusive, next-to-leading order 
    for(int icoll=0;icoll<2;++icoll){
        for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100 % 
            hjp_draw_dndpt[icoll][k] = (TH1D*) h1D_jp[2][1][icoll]->Clone(Form("hjp_draw%d_%d",k,icoll));
            if(k==1) hjp_draw_dndpt[icoll][k]->Scale(10);
            else if(k==2) hjp_draw_dndpt[icoll][k]->Scale(100);
            else if(k==3) hjp_draw_dndpt[icoll][k]->Scale(1000);
            else if(k==4) hjp_draw_dndpt[icoll][k]->Scale(10000);
            else if(k==5) hjp_draw_dndpt[icoll][k]->Scale(100000);
            else if(k==6) hjp_draw_dndpt[icoll][k]->Scale(1000000);
        }
    }

    //draw in cross section panel
    //if(doJETPHOX){
        c[1]->cd();
        for(int icoll=1;icoll<2;++icoll){ // icoll = 0 is pbpb, 1 is pp
            for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100 % 
                    hjp_draw_dndpt[icoll][k]->Draw("hist same"); // option C is for a smooth curve
               // gr_sys[i][k] = scale_graph(gr_sys[i][k],1./hjp_draw_dndpt[icoll][k]);
               // gr_nominal_scaled[k] = scale_graph(gr_nominal[i][k],scale);
               // gr_sys_scaled[k]->Draw("2");
            }
        }

        cout << "Draw in Raa panel..." << endl; 
        //final for raa
        TH1D* hjp_draw_raa = (TH1D*) h1D_jp[2][1][0]->Clone("jp_inclusive_nlo_raa"); //only for inclusive, next-to-leading order 
        hjp_draw_raa->Divide(h1D_jp[2][1][1]);

        //draw in raa panel
        c[0]->cd();
        //hjp_draw_raa->Draw("C same");
        for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100 % 
            c_sep[0][k]->cd();
            //  hjp_draw_raa->Draw("C same");
        }

       // ///////////////////////////////////////////////////////
       // // JETPHOX hist to graph
       // TGraphAsymmErrors* g_jp_dndpt[2][nCentBinIF];
       // TGraphAsymmErrors* g_jp_raa;
       // for(int icoll=0;icoll<2;++icoll){
       //     for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100 % 
       //         TH1_TO_TGRAPH(hjp_draw_dndpt[icoll][k], g_jp_dndpt[icoll][k]);
       //         g_jp_dndpt[icoll][k]->Draw("C same"); // option C is for a smooth curve
       //     }
       // }
       // TH1_TO_TGRAPH(hjp_draw_raa, g_jp_raa);
       // //draw in raa panel
       // c[0]->cd();
       // g_jp_raa->Draw("C same"); // option C is for a smooth curve
       // //hjp_draw_raa->Draw("C same");
       // for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100 % 
       //     c_sep[0][k]->cd();
       //     g_jp_raa->Draw("C same"); // option C is for a smooth curve
       //     //  hjp_draw_raa->Draw("C same");
       // }
       
       // ///////////////////////////////////////////////////////
       // // pp to JETPHOX ratio 
        cout << "data to JETPHOX ratio..." << endl; 
       TCanvas* c_ratio_data_jp = new TCanvas("c_ratio_data_jp","",600,600); 
       TH1D* ratio_data_jp[nCentBinIF];//0:pp, 1:0-10%, 2:10-30%, 3:30-100%
        for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100 % 
            if(k==0) ratio_data_jp[k] = (TH1D*) h1D_nominal[2][k]->Clone(Form("ratio_data_jp_%d",k)); 
            else ratio_data_jp[k] = (TH1D*) h1D_nominal[1][k]->Clone(Form("ratio_data_jp_%d",k)); 

            ratio_data_jp[k]->Divide(hjp_draw_dndpt[1][0]);
            ratio_data_jp[k]->GetYaxis()->SetRangeUser(0,2.5);
            ratio_data_jp[k]->SetTitle(";photon E_{T} GeV;DATA / JETPHOX (pp CTEQ66 NLO) ");
            if(k==0) ratio_data_jp[k]->Draw();
            else ratio_data_jp[k]->Draw("same");
        }
        jumSun(ptBins[0],1,ptBins[nPtBin],1);
    //}// if JETPHOX ? 


    ////////////////////////////////////////////////////////////////////////////////////////
    // Draw cross section legend 
    
    // DRAW extra text e.g. eta on cross section & spectra  
    c[1]->cd();
    TLegend* leg_dndpt = new TLegend(0.55,0.64,0.90,0.90);
    //TLegend* leg_dndpt = new TLegend(0.55,0.59,0.90,0.90);
    //TLegend* leg_dndpt = new TLegend(0.55,0.69,0.90,0.90);
    legStyle(leg_dndpt);
    for (int k=nCentBinIF-1; k>0; --k) { //k=0 is 0-100 % 
        if(k==1) leg_dndpt->AddEntry(h1D_nominal[1][k],Form("%d-%d %s      x 10",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%"),"plf");
        else if(k==2) leg_dndpt->AddEntry(h1D_nominal[1][k],Form("%d-%d %s    x 10^{%d}",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%",k),"plf");
        else if(k==3) leg_dndpt->AddEntry(h1D_nominal[1][k],Form("%d-%d %s    x 10^{%d}",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%",k),"plf");
        else if(k==4) leg_dndpt->AddEntry(h1D_nominal[1][k],Form("%d-%d %s  x 10^{%d}",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%",k),"plf");
        else leg_dndpt->AddEntry(h1D_nominal[1][k],Form("%d-%d %s \t x 10^{%d}",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%",k),"plf");
    }
    leg_dndpt->AddEntry(h1D_nominal[2][0],Form("pp%s",""),"plf");
    if(doJETPHOX) leg_dndpt->AddEntry(hjp_draw_dndpt[1][0],"JETPHOX (pp NLO)","l");
    //leg_dndpt->AddEntry(hjp_draw_dndpt[0][0],"JETPHOX (pbpb EPS09 NLO)","l");
    leg_dndpt->Draw("same");
       

    double legBottom = leg_dndpt->GetX1();
    //double legTop = leg_dndpt->GetX2();
    //cout << "legBottom = " << legBottom << ", GetX1() = "<< legTop << endl;
    float xpos_r = 1-c[1]->GetRightMargin();
    float xpos_l = c[1]->GetLeftMargin();
    float dy = 0.05; 
    float extraDY = 1.5; 
    //drawText(Form("%d-%d %s",(int)centBins_i[k]/2,(int)centBins_f[k]/2,"%"),xpos_r-dy,legBottom-dy*extraDY,1,kBlack,0.04); 
    //drawText("|#eta^{#gamma}| < 1.44",xpos_r-dy,legBottom+2*dy,1,kBlack,0.04); 
    drawText("|#eta^{#gamma}| < 1.44",xpos_l+0.19,0.75,1,kBlack,0.04); 

    c_ratio_data_jp->cd();
    leg_dndpt->Draw("same");
    c_ratio_data_jp->SaveAs(Form("%splotting/figures/finalPlot_ratio_data_to_JEXPHOX_%s_total.pdf",dir.Data(),cap.Data()));
    
    
    // DRAW extra text e.g. eta on RAA  
    c[0]->cd(); // RAA plot
    drawText("|#eta^{#gamma}| < 1.44",xpos_r-dy,legBottom+2*dy,1,kBlack,0.04); 
    //globalUncBox -> Draw("l same");

    /////////////////////////////////////////////////////////////////////////////////////////////
    // Store pdf files 
    cout << "Save figures..." << endl;
    for (int i=0; i<n_hist_types; ++i) {
        if(hist_types[i] != "dNdpt_corr2_pp") 
            c[i]->SaveAs(Form("%splotting/figures/finalPlot_%s_%s_total.pdf",dir.Data(),hist_types[i].c_str(),cap.Data()));
        for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100 % 
            if(hist_types[i] == "dNdpt_corr2_pp" && k>0) continue;
            c_sep[i][k]->SaveAs(Form("%splotting/figures/finalPlot_%s_%s_cent%d_%d.pdf",dir.Data(),hist_types[i].c_str(),cap.Data(),(int)centBins_i[k]/2,(int)centBins_f[k]/2));
        }
    }


}

TGraphAsymmErrors* scale_graph(TGraphAsymmErrors* gr=0, Float_t s=0){
    int np = gr->GetN();                                        
    TGraphAsymmErrors* new_gr = (TGraphAsymmErrors*) gr->Clone(Form("%s_scaled",gr->GetName()));
    //TGraphAsymmErrors* new_gr = new TGraphAsymmErrors(np);
    new_gr->SetName(Form("%s_scaled",gr->GetName()));
    for (int p=0; p<np; ++p) {                                         
        double Xmean = 0;                            
        double Ymean = 0;                            
        gr->GetPoint(p,Xmean,Ymean); 
        new_gr->SetPoint(p,Xmean,Ymean*s); 
        double Xerr_l= gr->GetErrorXlow(p); 
        double Xerr_h= gr->GetErrorXhigh(p);
        double Yerr_l= gr->GetErrorYlow(p);
        double Yerr_h= gr->GetErrorYhigh(p);
        new_gr->SetPointError(p,Xerr_l,Xerr_h,Yerr_l*s,Yerr_h*s);                
    }
    return new_gr;
}

TGraphAsymmErrors* devide_graph_by_hist(TGraphAsymmErrors* gr=0, TH1D* h1=0){
    int np = gr->GetN();                                        
    TGraphAsymmErrors* new_gr = (TGraphAsymmErrors*) gr->Clone(Form("%s_scaled",gr->GetName()));
    //TGraphAsymmErrors* new_gr = new TGraphAsymmErrors(np);
    new_gr->SetName(Form("%s_scaled",gr->GetName()));
    for (int p=0; p<np; ++p) {                                         
        double Xmean = 0;                            
        double Ymean = 0;               
        double scaleF = h1->GetBinContent(p);        
        gr->GetPoint(p,Xmean,Ymean); 
        new_gr->SetPoint(p,Xmean,Ymean*scaleF); 
        double Xerr_l= gr->GetErrorXlow(p); 
        double Xerr_h= gr->GetErrorXhigh(p);
        double Yerr_l= gr->GetErrorYlow(p);
        double Yerr_h= gr->GetErrorYhigh(p);
        new_gr->SetPointError(p,Xerr_l,Xerr_h,Yerr_l*scaleF,Yerr_h*scaleF);                
    }
    return new_gr;
}
