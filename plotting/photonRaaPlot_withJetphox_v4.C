// photonRaaPlot_withJetphox_v4.C
// draw the final plots 
// Author: Yeonju Go
// Modified at 2019 Aug. 08
// v3 : to have jetphox PDF systematic uncertainty in the ratio plot
// v4 : merge jetphox ratio plot on the bottom of the cross section plot.  
// v4 : pp and pbpb cross section plot seperately. 

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
#include "../phoRaaCuts/tdrstyle.C"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TAttFill.h"

static const float ncoll_w_npart[4] = {43.58, 118.8, 239.9, 363.4};
void draw_sys_unc(TGraphErrors* gr, TH1* h1, TH1* h1_sys);
void draw_npart_sys_unc(TGraphErrors* gr, TH1* h1, TH1* h1_sys, int x_width);

const int markerStyle[]={21,33,34,29,20,29};
const int markerStyle_pp=21;//square
const int colorStyle_marker_pp=kOrange+7;
const int colorStyle_line_pp=kOrange+7;
const int colorStyle_sys_pp=kOrange+6;
const int colorStyle_marker[]={kBlack,kPink-6,kGreen+3,kBlue-3,kOrange+4};
const int colorStyle_sys[]={kYellow-7,kRed-10,kGreen-10,kBlue-10,kOrange-3};
const int colorStyle_line[]={kYellow-4,kPink-6,kGreen+3,kBlue-3,kOrange+4};
const double transparency[]={0.5,0.5,0.5,0.5,0.5,0.5};
const double scale[]={1.,10.,100.,1000.,10000.,100000.};

TGraphAsymmErrors* scale_graph(TGraphAsymmErrors* gr, Float_t s);
TGraphAsymmErrors* divide_graph_by_hist(TGraphAsymmErrors* gr, TH1D* h1);
void hist_to_graph(TGraphAsymmErrors* gr, TH1D* h1, TH1D* h2, TH1D* h3, bool doSelfScale);
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

void photonRaaPlot_withJetphox_v4(TString ver="190703_temp_v31", bool doJETPHOX = true) {
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    
    TString cap = Form("%s_withJetphox_NLO",ver.Data());
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
                //if(k>0) continue;
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

            // histogram cosmetics, this is used for legend 
            if(k==0){    
                if(hist_types[i] == "Raa") htemp[i] = new TH1D(Form("htemp_%d",i),"",nPtBin+1,ptBins_draw_final); 
                else htemp[i] = new TH1D(Form("htemp_%d",i),"",nPtBin,ptBins_draw); 
                if(hist_types[i] == "Raa") htemp[i]->GetYaxis()->SetRangeUser(0.0,2.0);
                else if(hist_types[i] ==  "dNdpt_corr2_pp") htemp[i]->GetYaxis()->SetRangeUser(0.01,1.e+5);
            }
            h1D_nominal[i][k]->SetMarkerColor(colorStyle_marker[k]);
            h1D_nominal[i][k]->SetLineColor(colorStyle_marker[k]);
            h1D_nominal[i][k]->SetMarkerStyle(markerStyle[k]);
            h1D_nominal[i][k]->SetFillStyle(3001);
            h1D_nominal[i][k]->SetFillColor(colorStyle_sys[k]);
            if(markerStyle[k]==33) h1D_nominal[i][k]->SetMarkerSize(1.8);
            else if(markerStyle[k]==21) h1D_nominal[i][k]->SetMarkerSize(1.2);
            else h1D_nominal[i][k]->SetMarkerSize(1.4);
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
            if(hist_types[i] != "Raa" && markerStyle[k]==21) gr_nominal[i][k]->SetMarkerSize(1.2);
            if(hist_types[i] != "Raa" && markerStyle[k]==20) gr_nominal[i][k]->SetMarkerSize(1.6);
            
            if(hist_types[i] == "dNdpt_corr2_pp"){
                gr_nominal[i][k]->SetMarkerColor(colorStyle_marker_pp);
                gr_nominal[i][k]->SetLineColor(colorStyle_line_pp);
                gr_nominal[i][k]->SetMarkerStyle(markerStyle_pp);
            } 

            //systematic part
            gr_sys[i][k] = new TGraphAsymmErrors(nPtBin-rejectPtBins[k]);
            gr_sys[i][k]->SetName(Form("gr_sys_%d_%d",i,k));
            gr_sys[i][k]->SetFillStyle(3001);
            gr_sys[i][k]->SetFillColor(colorStyle_sys[k]);
            gr_sys[i][k]->SetLineColor(colorStyle_sys[k]);
            cout <<  h1D_nominal[i][k]->GetNbinsX()<< endl;
            
            //ipt starting from 2 when using Unfolding underflow bin!!
            //ipt starting from 1 when not using Unfolding underflow bin!!
            for (int ipt=1; ipt<=nPtBin-rejectPtBins[k]; ++ipt) {
                double x = h1D_nominal[i][k]->GetBinCenter(ipt);
                int sys_bin = systematics[i][k]->FindBin(x);
                double bin_width = h1D_nominal[i][k]->GetBinLowEdge(ipt+1) - h1D_nominal[i][k]->GetBinLowEdge(ipt);
                double val = h1D_nominal[i][k]->GetBinContent(ipt);
                double error = TMath::Abs(systematics[i][k]->GetBinContent(sys_bin));
                cout << "histname : " << hist_name << ", ipt " << ipt << ", val = " << val << ", Systematic Error = " << error << endl;
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
            gr_sys[i][k]->SetFillColorAlpha(colorStyle_sys[k],0.9);
            if(hist_types[i] == "dNdpt_corr2_pp")   gr_sys[i][k]->SetFillColorAlpha(colorStyle_sys[k],0.9);
            if(hist_types[i] == "Raa") gr_sys[i][k]->GetYaxis()->SetRangeUser(0.5,1.5);
            else if(hist_types[i] ==  "dNdpt_corr2_pp") gr_sys[i][k]->GetYaxis()->SetRangeUser(0.01,1.e+5);

        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////
    // DRAW : Centrality seperately 
    cout << "Draw centrality separately..." << endl;

    setTDRStyle();   
    TCanvas* c_sep[n_hist_types][nCentBinIF];

    TLegend* leg_glo = new TLegend(0.53,0.67,0.94,0.77);
    float dx = 5;
    //float dx = 2.5;
    TBox *globalUncBox_pplumi = new TBox(ptBins_draw_final[0],1-sys_ppLumi,ptBins_draw_final[0]+dx,1+sys_ppLumi);
    globalUncBox_pplumi -> SetFillColorAlpha(28,0.5);
    globalUncBox_pplumi -> SetLineColor(kOrange+3);
    globalUncBox_pplumi -> SetLineWidth(2);
    TBox *globalUncBox_TAA[nCentBinIF];
    for (int i=0; i<n_hist_types; ++i) {
        for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100 %
            if(hist_types[i] == "dNdpt_corr2_pp" && k>0) continue;
            if(i==0){
                globalUncBox_TAA[k] = new TBox(ptBins_draw_final[0]+dx,1-TA_err_down[k],ptBins_draw_final[0]+dx*2,1+TA_err_up[k]); // asymetrical TAA uncertainty
                globalUncBox_TAA[k] -> SetFillColorAlpha(kGray+2,0.5);
                globalUncBox_TAA[k] -> SetLineColor(kBlack);
                globalUncBox_TAA[k] -> SetLineWidth(2);
            }
            if(i==0 && k==0) c_sep[i][k] = new TCanvas(Form("c_%s_%d",hist_types[i].c_str(),k),"",600,600);
            else c_sep[i][k] = new TCanvas(Form("c_%s_%d",hist_types[i].c_str(),k),"",600,400);
            c_sep[i][k]->cd();
            c_sep[i][k]->SetRightMargin(0.05);
            c_sep[i][k]->SetTopMargin(0.07);

            //////////////////////////////
            // cosmetics 
            htemp[i]->GetXaxis()->CenterTitle();
            htemp[i]->GetYaxis()->CenterTitle();
            htemp[i]->GetYaxis()->SetTitleSize(0.050);
            htemp[i]->GetYaxis()->SetTitleOffset(1.2);
            htemp[i]->GetXaxis()->SetTitleSize(0.055);
            htemp[i]->GetXaxis()->SetTitleOffset(1.5);
            htemp[i]->GetXaxis()->SetTitleFont(42);
            htemp[i]->GetYaxis()->SetTitleFont(42);
            htemp[i]->GetXaxis()->SetTitleColor(1);
            htemp[i]->GetYaxis()->SetTitleColor(1);
            htemp[i]->GetXaxis()->SetLabelSize(0.041);
            htemp[i]->GetYaxis()->SetLabelSize(0.045);
            //htemp[i]->GetXaxis()->SetLabelSize(0.046);
            //htemp[i]->GetYaxis()->SetLabelSize(0.05);
            if(hist_types[i] == "Raa"){
                htemp[i]->GetYaxis()->SetTitleOffset(1.4);
                htemp[i]->GetXaxis()->SetTitleOffset(1.2);
                htemp[i]->GetYaxis()->SetTitleSize(0.055);
                htemp[i]->GetYaxis()->SetTitleOffset(1.0);
                htemp[i]->GetXaxis()->SetTitleSize(0.045);
                htemp[i]->GetXaxis()->SetTitleOffset(1.2);
            }
            if(hist_types[i] == "Raa") htemp[i]->SetTitle(";E_{T}^{#gamma} (GeV);R_{AA}");
            else if(hist_types[i] == "dNdpt_corr2") htemp[i]->SetTitle(";E_{T}^{#gamma} (GeV);#frac{1}{N_{evt}} #frac{1}{<T_{AA}>} #frac{d^{2}N^{PbPb}}{dE_{T}d#eta} (#frac{pb}{GeV})");
            else if(hist_types[i] == "dNdpt_corr2_pp") htemp[i]->SetTitle(";E_{T}^{#gamma} (GeV);#frac{d^{2}#sigma^{pp}}{dE_{T}d#eta} (#frac{pb}{GeV})");

            if(hist_types[i] != "Raa") htemp[i]->GetYaxis()->SetRangeUser(0.01,1.e+5);
            if(hist_types[i] == "dNdpt_corr2" || hist_types[i] == "dNdpt_corr2_pp")
                gPad->SetLogy();

            ////////////////////////////
            // draw graphs 
            gr_sys[i][k]->SetFillColorAlpha(colorStyle_sys[k],0.7);
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
        c[i] = new TCanvas(Form("c_%s",hist_types[i].c_str()),"",600,700);
        if(hist_types[i] == "Raa"){
            c[i]->cd();
        } else{
            ratioPanelCanvas(c[i]);
            c[i]->cd(1);
        }
        //c[i]->SetRightMargin(0.05);
        //c[i]->SetTopMargin(0.07);
        //if(hist_types[i] == "dNdpt_corr2_pp") c[i-1]->cd();
        //else c[i]->cd();

        for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100 % 
            if(hist_types[i] == "dNdpt_corr2_pp" && k>0) continue;

            ////////////////////////////
            // Dummy hist draw 
            if(hist_types[i] == "Raa") htemp[i]->SetTitle(";E_{T}^{#gamma} (GeV);R_{AA}");
            else if(hist_types[i] == "dNdpt_corr2_pp") htemp[i]->SetTitle(";E_{T}^{#gamma} (GeV);#frac{d^{2}#sigma^{pp}}{dE_{T}d#eta} (#frac{pb}{GeV})");
            else htemp[i]->SetTitle(";E_{T}^{#gamma} (GeV);#frac{1}{N_{evt}}#frac{1}{<T_{AA}>}#frac{d^{2}N^{PbPb}}{dE_{T}d#eta} (#frac{pb}{GeV})");
            //if(hist_types[i] == "dNdpt_corr2") htemp[i]->GetYaxis()->SetRangeUser(0.01,1e+10);
            //else if(hist_types[i] ==  "dNdpt_corr2_pp") htemp[i]->GetYaxis()->SetRangeUser(0.01,1.e+5);
            if(hist_types[i] == "dNdpt_corr2") htemp[i]->GetYaxis()->SetRangeUser(0.05,5e+8);
            else if(hist_types[i] ==  "dNdpt_corr2_pp") htemp[i]->GetYaxis()->SetRangeUser(0.05,1.e+4);
            if(k==0) htemp[i]->DrawCopy();
            //if(k==0 && hist_types[i] != "dNdpt_corr2_pp") htemp[i]->DrawCopy();

            ////////////////////////////
            // Scale dNdpt 
            if(hist_types[i] == "dNdpt_corr2"){
                float scale = 1.;
                if(k==0) scale = 1.; //continue; 
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
            if(hist_types[i] == "dNdpt_corr2" || hist_types[i] == "dNdpt_corr2_pp" ) gPad->SetLogy();
        }

        ////////////////////////////////
        // Draw CMS latex and lumi etc. 
        TString lumiSt= " 27.4 pb^{-1} pp / 404 #mub^{-1} PbPb (5.02 TeV)";
        if(hist_types[i] == "dNdpt_corr2_pp") lumiSt= " 27.4 pb^{-1} pp (5.02 TeV)";
        else if(hist_types[i] == "dNdpt_corr2") lumiSt= " 404 #mub^{-1} PbPb (5.02 TeV)";
        drawLumi(c[i],lumiSt,0.01, 0.650); 
        drawCMS(c[i],"Preliminary",0.9); 
        if(i==0) leg_raa->Draw("same");
    } 


    /////////////////////////////////////////////////////////////////////////////////////////////
    // Draw Jetphox pp NLO
    // /home/samba.old/jaebeom/ForYeonju/
    
    cout << "Import JETPHOX files..." << endl; 
    TString fname[2][3][3];//[0:dir, 1:onef, 2:inclusive] [0:pbpb, 1:pp, 2:nCTEQ] [0:scale 1.0(nominal) 1:scale 0.5 2:scale 2]
    TFile* fjp[2][3][3];//[0:dir, 1:onef, 2:inclusive] [0:pbpb, 1:pp, 2:nCTEQ] [0:scale 1.0(nominal) 1:scale 0.5 2:scale 2]
    //nominal scale 1.0
    fname[0][0][0] = "/home/samba.old/jaebeom/ForYeonju/Nominal1B/ggdPbPb_EPPS16nlo_CT14nlo_Pb208_nominal_scale_190716.root";
    fname[1][0][0] = "/home/samba.old/jaebeom/ForYeonju/Nominal1B/ggoPbPb_EPPS16nlo_CT14nlo_Pb208_nominal_scale_190716.root";
    //fname[0][1][0] = "/home/samba.old/jaebeom/ForYeonju/ggdpp_CT10nlo_10M_180910.root";
    //fname[1][1][0] = "/home/samba.old/jaebeom/ForYeonju/ggopp_CT10nlo_10M_180910.root";
    //fname[0][1][0] = "/home/samba.old/jaebeom/ForYeonju/ggdpp_CT10nlo_1M_180910.root";
    //fname[1][1][0] = "/home/samba.old/jaebeom/ForYeonju/ggopp_CT10nlo_1M_180910.root";
    fname[0][1][0] = "/home/samba.old/jaebeom/ForYeonju/Nominal1B/ggdpp_CT14nlo_nominal_scale1_190719.root"; 
    fname[1][1][0] = "/home/samba.old/jaebeom/ForYeonju/Nominal1B/ggopp_CT14nlo_nominal_scale1_190719.root"; 
    fname[0][2][0] = "/home/samba.old/jaebeom/ForYeonju/Nominal1B/ggdPbPb_nCTEQ15_208_82_nominal_scale1_190717.root";
    fname[1][2][0] = "/home/samba.old/jaebeom/ForYeonju/Nominal1B/ggoPbPb_nCTEQ15_208_82_nominal_scale1_190717.root";
    //scale 0.5
    fname[0][0][1] = "/home/samba.old/jaebeom/ForYeonju/Nominal1B/ggdPbPb_EPPS16nlo_CT14nlo_Pb208_1B.root";
    fname[1][0][1] = "/home/samba.old/jaebeom/ForYeonju/Nominal1B/ggoPbPb_EPPS16nlo_CT14nlo_Pb208_1B.root";
    fname[0][1][1] = "/home/samba.old/jaebeom/ForYeonju/Nominal1B/ggdpp_CT14nlo_1B_cd.root";
    fname[1][1][1] = "/home/samba.old/jaebeom/ForYeonju/Nominal1B/ggopp_CT14nlo_1B_cd.root";
    fname[0][2][1] = "/home/samba.old/jaebeom/ForYeonju/Nominal1B/ggdPbPb_nCTEQ15_208_82_1B.root";
    fname[1][2][1] = "/home/samba.old/jaebeom/ForYeonju/Nominal1B/ggoPbPb_nCTEQ15_208_82_1B.root";
    //scale 2.0
    fname[0][0][2] = "/home/samba.old/jaebeom/ForYeonju/Nominal1B/ggdPbPb_EPPS16nlo_CT14nlo_Pb208_nominal_scale2_190717.root";
    fname[1][0][2] = "/home/samba.old/jaebeom/ForYeonju/Nominal1B/ggoPbPb_EPPS16nlo_CT14nlo_Pb208_nominal_scale2_190717.root";
    fname[0][1][2] = "/home/samba.old/jaebeom/ForYeonju/Nominal1B/ggdpp_CT14nlo_nominal_scale2_190717.root";
    fname[1][1][2] = "/home/samba.old/jaebeom/ForYeonju/Nominal1B/ggopp_CT14nlo_nominal_scale2_190717.root";
    fname[0][2][2] = "/home/samba.old/jaebeom/ForYeonju/Nominal1B/ggdPbPb_nCTEQ15_208_82_nominal_scale2_190717.root";
    fname[1][2][2] = "/home/samba.old/jaebeom/ForYeonju/Nominal1B/ggoPbPb_nCTEQ15_208_82_nominal_scale2_190717.root";
    TFile* fsys_pp = TFile::Open("/home/samba.old/jaebeom/ForYeonju/Sys_pp_CT14nlo_relUnc.root","read");
    TFile* fsys_pbpb = TFile::Open("/home/samba.old/jaebeom/ForYeonju/Sys_PbPb_EPPS16nlo_CT14nlo_Pb208_relUnc.root","read");
    //TFile* fsys_pp = TFile::Open("/home/samba.old/jaebeom/ForYeonju/Sys_pp_CT14nlo.root","read");
    //TFile* fsys_pbpb = TFile::Open("/home/samba.old/jaebeom/ForYeonju/Sys_PbPb_EPPS16nlo_CT14nlo_Pb208_merged.root","read");
    
    for(int itype=0; itype<2; ++itype){//dir, onef
        for(int icoll=0; icoll<3; ++icoll){//EPPS16, CT14, (nCTEQ)
            for(int isys=0; isys<3; ++isys){//scale 1.0, 0.5, 2.0
                fjp[itype][icoll][isys] = TFile::Open(Form("%s",fname[itype][icoll][isys].Data()),"read");    
            }
        }
    }

    
    cout << "Getting JETPHOX histograms from each file..." << endl; 
    TH1D* h1D_jp[3][2][3][3];//[0:dir, 1:onef, 2:inclusive] [0:Leading Order, 1:Next-to-Leading Order] [0:pbpb, 1:pp, 2:nCTEQ] [0:scale 1.0(nominal) 1:scale 0.5 2:scale 2]
    
    for(int itype=0; itype<2; ++itype){//dir, onef
    for(int iord=0; iord<2; ++iord){//LO, NLO
    for(int icoll=0; icoll<3; ++icoll){//EPPS16, CT14, (nCTEQ)
    for(int isys=0; isys<3; ++isys){//scale 1.0, 0.5, 2.0
        cout << "itype = " << itype<<  ", iorder  = " << iord <<  ", icoll = " << icoll<<  ", isys = " << isys << endl;
        const char* histname = "hp40";
        if(iord==1) histname = "hp41"; 
        //const char* histname = iord == 0 ? "hp40" : "hp41";
        const char* n_type = itype == 0 ? "dir" : "onef";
        const char* n_coll = "EPPS16";
        if(icoll==1) n_coll = "CT14";
        //const char* n_coll = icoll == 0 ? "EPPS16" : "CT14";
        const char* n_tot = Form("%s_%s_scale%d", n_type, n_coll, isys);
        cout << "tot name = " << n_tot << endl;
        h1D_jp[itype][iord][icoll][isys] = (TH1D*) fjp[itype][icoll][isys]->Get(histname);
        h1D_jp[itype][iord][icoll][isys]->SetName(Form("jp_nlo_%s",n_tot));
        
        if(itype==1){
            n_type = "inclusive"; 
            n_tot = Form("%s_%s_scale%d", n_type, n_coll, isys);
            h1D_jp[2][iord][icoll][isys] = (TH1D*) h1D_jp[1][iord][icoll][isys]->Clone(Form("jp_nlo_%s",n_tot));
            h1D_jp[2][iord][icoll][isys]->Add(h1D_jp[0][iord][icoll][isys]);
        }
        
    }}}}
    
    // systematic histograms 
    TH1D* h1D_sys_jetphox[n_hist_types];
    h1D_sys_jetphox[2] = (TH1D*) fsys_pp->Get("h_nlo_nom_relErr");
    h1D_sys_jetphox[2] -> SetName("h_nlo_nom_pp");
    h1D_sys_jetphox[1] = (TH1D*) fsys_pbpb->Get("h_nlo_nom_relErr");
    h1D_sys_jetphox[1] -> SetName("h_nlo_nom_pbpb");

    //cosmetics
    cout << "Set JETPHOX hist cosmetics..." << endl; 
    for(int icont=0;icont<3;++icont){
    for(int ior=0;ior<2;++ior){
    for(int icoll=0;icoll<3;++icoll){
    for(int isys=0; isys<3; ++isys){//scale 1.0, 0.5, 2.0
        h1D_jp[icont][ior][icoll][isys]->Scale(1./2.88);
        if(icoll==0){ 
            h1D_jp[icont][ior][0][isys]->SetLineColor(2);
            h1D_jp[icont][ior][0][isys]->SetLineStyle(6);
        } else{ 
            h1D_jp[icont][ior][icoll][isys]->SetLineColor(1);
            h1D_jp[icont][ior][icoll][isys]->SetLineStyle(2);
        }
        h1D_jp[icont][ior][icoll][isys]->SetLineWidth(2);
    }}}}

    cout << "Draw JETPHOX in cross section panel..." << endl; 
    //final for dndpt for jetphox //scale up each centrality bin 
    TH1D* hjp_draw_dndpt[3][nCentBinIF]; //[0:pbpb, 1:pp, 2:pbpb_nCTEQ] [centraltiy] only for inclusive, next-to-leading order 
    for(int icoll=0;icoll<3;++icoll){
        for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100 % 
            hjp_draw_dndpt[icoll][k] = (TH1D*) h1D_jp[2][1][icoll][0]->Clone(Form("hjp_draw%d_%d",k,icoll));//onef+dir
            //hjp_draw_dndpt[icoll][k] = (TH1D*) h1D_jp[1][1][icoll]->Clone(Form("hjp_draw%d_%d",k,icoll));//only onef
            //hjp_draw_dndpt[icoll][k] = (TH1D*) h1D_jp[0][1][icoll]->Clone(Form("hjp_draw%d_%d",k,icoll));//only dir
            if(k==1) hjp_draw_dndpt[icoll][k]->Scale(10);
            else if(k==2) hjp_draw_dndpt[icoll][k]->Scale(100);
            else if(k==3) hjp_draw_dndpt[icoll][k]->Scale(1000);
            else if(k==4) hjp_draw_dndpt[icoll][k]->Scale(10000);
            else if(k==5) hjp_draw_dndpt[icoll][k]->Scale(100000);
            else if(k==6) hjp_draw_dndpt[icoll][k]->Scale(1000000);
            if(icoll==0) removeHistLastBins(hjp_draw_dndpt[icoll][k],rejectPtBins[k]);
        }
    }
    //draw JETPHOX lines in the cross section panel
    c[1]->cd(1);//cross section in pbpb
    for(int in=0; in<1; ++in){ //[0: EPPS16, 2:nCTEQ15]
        if(in==1) continue;
        hjp_draw_dndpt[in][0]->SetLineStyle(1);
        hjp_draw_dndpt[in][0]->Draw("C same"); // option C is for a smooth curve

        cout << "JETPHOX PbPb cross section values " << endl;
        for(int ipt=0;ipt<nPtBin;++ipt){
            double val = hjp_draw_dndpt[in][0]->GetBinContent(ipt+1);
            cout << "pt " << ptBins_draw[ipt] << " - " << ptBins_draw[ipt+1] << " : " << val << endl;
        }
    }
    c[2]->cd(1);//cross section in pp 
    hjp_draw_dndpt[1][0]->SetLineStyle(1);
    hjp_draw_dndpt[1][0]->SetLineColor(2);
    hjp_draw_dndpt[1][0]->Draw("C same"); // option C is for a smooth curve

    cout << "JETPHOX pp cross section values " << endl;
    for(int ipt=0;ipt<nPtBin;++ipt){
        double val = hjp_draw_dndpt[1][0]->GetBinContent(ipt+1);
        cout << "pt " << ptBins_draw[ipt] << " - " << ptBins_draw[ipt+1] << " : " << val << endl;
    }


    cout << "Draw JETPHOX in Raa panel..." << endl; 
    TH1D* hjp_draw_raa[2][3]; // [0: EPPS16, 1:nCTEQ15][scale 1.0, 0.5, 2.0]
    for(int isys=0; isys<3; ++isys){//scale 1.0, 0.5, 2.0
        hjp_draw_raa[0][isys] = (TH1D*) h1D_jp[2][1][0][isys]->Clone(Form("jp_inclusive_nlo_raa_scale%d",isys)); //only for inclusive, next-to-leading order 
        hjp_draw_raa[1][isys] = (TH1D*) h1D_jp[2][1][2][isys]->Clone(Form("jp_inclusive_nlo_raa_nCTEQ_scale%d",isys)); //only for inclusive, next-to-leading order 
        hjp_draw_raa[0][isys]->Divide(h1D_jp[2][1][1][isys]);
        hjp_draw_raa[1][isys]->Divide(h1D_jp[2][1][1][isys]);
    }

    //draw JETPHOX lines in the raa panel
    c[0]->cd(1);
    for(int in=0; in<1; ++in){ //[0: EPPS16, 1:nCTEQ15]
        c_sep[0][0]->cd();
        hjp_draw_raa[in][0]->SetLineStyle(1);
        hjp_draw_raa[in][0]->Draw("hist pe same");
        for(int ipt=0; ipt<hjp_draw_raa[in][0]->GetNbinsX();++ipt)
            cout << "ipt = " << ipt << ", bin error = " << hjp_draw_raa[in][0]->GetBinError(ipt+1)<< endl;;
    }
    
    ////////////////////////////////////////////////////////////
    // JETPHOX RAA scale error 
    cout << "JETPHOX RAA scale systematic..." << endl; 
    TGraphAsymmErrors* gr_raa_sys_scale[2];
    for(int in=0; in<1; ++in){ //[0: EPPS16, 1:nCTEQ15]
        gr_raa_sys_scale[in] = new TGraphAsymmErrors(nPtBin);
        gr_raa_sys_scale[in]->SetName(Form("gr_raa_sys_scale%d",in));
        for(int ipt=1; ipt<=hjp_draw_raa[in][0]->GetNbinsX();++ipt){
            double dy_up = abs(hjp_draw_raa[in][0]->GetBinContent(ipt)-hjp_draw_raa[in][1]->GetBinContent(ipt));
            double dy_down = abs(hjp_draw_raa[in][0]->GetBinContent(ipt)-hjp_draw_raa[in][2]->GetBinContent(ipt));
            double dy = 0;
            if(dy_up>=dy_down) dy = dy_up; 
            else dy = dy_down; 
            cout << "dy_up = " << dy_up << ", dy_down = " << dy_down << ", dy = " << dy << endl;

            double x = hjp_draw_raa[in][0]->GetBinCenter(ipt);
            double val = hjp_draw_raa[in][0]->GetBinContent(ipt);
            double bin_width = hjp_draw_raa[in][0]->GetBinLowEdge(ipt+1) - hjp_draw_raa[in][0]->GetBinLowEdge(ipt);
            gr_raa_sys_scale[in]->SetPointError(ipt-1, (bin_width/2), (bin_width/2), dy, dy); 
            gr_raa_sys_scale[in]->SetPoint(ipt-1, x, val); 
        }
        gr_raa_sys_scale[in]->SetFillStyle(3004);
        //gr_raa_sys_scale[in]->SetFillStyle(3013);
        gr_raa_sys_scale[in]->SetFillColor(kPink);
        gr_raa_sys_scale[in]->SetLineColor(kPink);
        gr_raa_sys_scale[in]->Draw("2");
    }
    
    ////////////////////////////////////////////////////////////
    // JETPHOX RAA PDF error 
    cout << "JETPHOX RAA pdf systematic..." << endl; 
    TGraphAsymmErrors* gr_raa_sys_pdf[2];// [0: EPPS16, 1:nCTEQ15]
    for(int in=0; in<1; ++in){ //[0: EPPS16, 1:nCTEQ15]
        gr_raa_sys_pdf[in] = new TGraphAsymmErrors(nPtBin);
        gr_raa_sys_pdf[in]->SetName(Form("gr_raa_sys_pdf%d",in));
        for(int ipt=1; ipt<=hjp_draw_raa[in][0]->GetNbinsX();++ipt){
            double pbpb_up = h1D_sys_jetphox[1]->GetBinContent(ipt)+h1D_sys_jetphox[1]->GetBinError(ipt);
            double pbpb_down = h1D_sys_jetphox[1]->GetBinContent(ipt)-h1D_sys_jetphox[1]->GetBinError(ipt);
            double pbpb_nom = h1D_sys_jetphox[1]->GetBinContent(ipt);
            double pp = h1D_sys_jetphox[2]->GetBinContent(ipt);
            double ratio_up = pbpb_up/pp;
            double ratio_down = pbpb_down/pp;
            double ratio_nom = pbpb_nom/pp;

            double dy_up = abs(ratio_up-ratio_nom);
            double dy_down = abs(ratio_down-ratio_nom);
            double dy = 0;
            if(dy_up>=dy_down) dy = dy_up; 
            else dy = dy_down; 

            double x = hjp_draw_raa[in][0]->GetBinCenter(ipt);
            double val = hjp_draw_raa[in][0]->GetBinContent(ipt);
            double bin_width = hjp_draw_raa[in][0]->GetBinLowEdge(ipt+1) - hjp_draw_raa[in][0]->GetBinLowEdge(ipt);
            gr_raa_sys_pdf[in]->SetPointError(ipt-1, (bin_width/2), (bin_width/2), dy, dy); 
            gr_raa_sys_pdf[in]->SetPoint(ipt-1, x, val); 
        }
        gr_raa_sys_pdf[in]->SetFillStyle(3005);
        gr_raa_sys_pdf[in]->SetFillColor(kAzure-1);
        gr_raa_sys_pdf[in]->SetLineColor(kAzure-1);
        gr_raa_sys_pdf[in]->Draw("2");
    }

    ////////////////////////////////////////////////////////////
    // DATA/JETPHOX ratio at the bottom of cross section panel  
    cout << "Data to JETPHOX ratio..." << endl; 

    TH1D* ratio_data_jp[n_hist_types][nCentBinIF];//[0:raa 1:pbpb Xsec 2:pp Xsec][0:0-100%, 1:0-10%, 2:10-30%, 3:30-100%]
    TGraphAsymmErrors* gr_ratio[n_hist_types][nCentBinIF];
    TGraphAsymmErrors* gr_sys_ratio[n_hist_types][nCentBinIF];

    float xpos_r = 1-c_sep[1][0]->GetRightMargin();
    float xpos_l = c_sep[1][0]->GetLeftMargin();
    float ypos_t = 1-c_sep[1][0]->GetTopMargin();
    float dy = 0.05; 
    float extraDY = 1.5; 
    for (int i=0; i<n_hist_types; ++i) {
        for (int k=0; k<1; ++k) { //k=0 is 0-100 %
        //for (int k=0; k<nCentBinIF; ++k) {} //k=0 is 0-100 %
            if(i==0) continue; //raa
            if(hist_types[i] == "dNdpt_corr2_pp" && k>0) continue;
            c[i]->cd(2);
            if(k==0){
                htemp[i]->GetYaxis()->SetRangeUser(0.5,2.5);
                //htemp[i]->GetYaxis()->SetRangeUser(0,2.5);
                htemp[i]->SetTitle(";E_{T}^{#gamma} (GeV);DATA / JETPHOX");
                //if(i==1) htemp[i]->SetTitle(";E_{T}^{#gamma} (GeV);DATA / JETPHOX (EPPS16+CT14 nlo) ");
                //else htemp[i]->SetTitle(";E_{T}^{#gamma} (GeV);DATA / JETPHOX (CT14 nlo) ");
                htemp[i]->GetXaxis()->CenterTitle();
                htemp[i]->GetYaxis()->CenterTitle();
                htemp[i]->GetXaxis()->SetTitleFont(42);
                htemp[i]->GetYaxis()->SetTitleFont(42);
                cout << "font : " << htemp[i]->GetXaxis()->GetTitleSize() << endl;
                htemp[i]->GetXaxis()->SetTitleSize(0.075);
                htemp[i]->GetYaxis()->SetTitleSize(0.075);
                htemp[i]->GetXaxis()->SetTitleOffset(1.5);
                htemp[i]->GetYaxis()->SetTitleOffset(0.7);
                htemp[i]->GetXaxis()->SetTitleColor(1);
                htemp[i]->GetYaxis()->SetTitleColor(1);
                htemp[i]->GetXaxis()->SetLabelSize(0.06);
                htemp[i]->GetYaxis()->SetLabelSize(0.06);
                //htemp[i]->GetXaxis()->SetLabelSize(0.07);
                //htemp[i]->GetYaxis()->SetLabelSize(0.07);
                htemp[i]->SetNdivisions(505,"Y");
                htemp[i]->DrawCopy("p");
                jumSun(ptBins[0],1,ptBins[nPtBin],1);
                //drawText(Form("%d-%d %s",(int)centBins_i[k]/2,(int)centBins_f[k]/2,"%"),xpos_r-dy,ypos_t-dy*extraDY,1,kBlack,0.04); 
                //drawText("|#eta^{#gamma}| < 1.44",xpos_r-dy,ypos_t-dy*extraDY-dy,1,kBlack,0.04); 
                //TString lumiSt= " 27.4 pb^{-1} pp + 404 #mub^{-1} PbPb (5.02 TeV)";
                //drawLumi(c_ratio_data_jp,lumiSt,0.2); 
                //drawCMS(c_ratio_data_jp,"Preliminary",0.5); 
            }

            ratio_data_jp[i][k] = (TH1D*) h1D_nominal[i][k]->Clone(Form("ratio_data_jp_%d",k)); 
            //hjp_draw_dndpt[2][nCentBinIF]; //[0:pbpb, 1:pp] [centraltiy] only for inclusive, next-to-leading order
            ratio_data_jp[i][k]->Divide(hjp_draw_dndpt[i-1][0]); //hjp_draw_dndpt[0][0] pbpb dndpt, hjp_draw_dndpt[1][0] pp dndpt
            ratio_data_jp[i][k]->GetYaxis()->SetRangeUser(0.0,2.0);

            //////////////////////////////////////////////////////////////////////////////////////////
            //// Graph for ratio systematic uncertainty from DATA  
            //// Histogram to graph for ratios 
            TH1_TO_TGRAPH(ratio_data_jp[i][k], gr_ratio[i][k],nPtBin-rejectPtBins[k]);
            gr_ratio[i][k]->SetMarkerColor(colorStyle_marker[k]);
            gr_ratio[i][k]->SetLineColor(colorStyle_marker[k]);
            gr_ratio[i][k]->SetMarkerStyle(markerStyle[k]);
            gr_ratio[i][k] = divide_graph_by_hist(gr_nominal[i][k],hjp_draw_dndpt[i-1][0]);
            gr_sys_ratio[i][k] = divide_graph_by_hist(gr_sys[i][k],hjp_draw_dndpt[i-1][0]);
            gr_sys_ratio[i][k]->SetFillStyle(1001);
            gr_sys_ratio[i][k]->SetFillColorAlpha(colorStyle_sys[k],0.7);
            gr_sys_ratio[i][k]->Draw("2");
            gr_ratio[i][k]->Draw("Pe");

        }
    }

    cout << "JETPHOX scale error" << endl;
    ////////////////////////////////////////////////////////////////////////////////////////
    // Calculate JETPHOX scale error (systematic uncertainty)  
    // 
    //TH1D* h1D_ratio_jetphox_sys_scale[2][2]; //[0:EPPS16, 1:CT14][0: jetphox(scale0.5)/jetphox(scale1.0), 1: jetphox(scale2.0)/jetphox(scale1.0)]
    TGraphAsymmErrors* gr_jetphox_sys_scale[2];//[0:EPPS16, 1:CT14]
    for(int icoll=0;icoll<2;++icoll){//EPPS16, CT14, nCTEQ15
        //for(int isys=0; isys<2; ++isys){//scale 1.0, 0.5, 2.0
        //    h1D_ratio_jetphox_sys_scale[icoll][isys] = (TH1D*) h1D_jp[2][1][icoll][isys+1]->Clone(Form("h1D_ratio_jetphox_sys_icoll%d_scale%d",icoll,isys));
        //    h1D_ratio_jetphox_sys_scale[icoll][isys]->Divide(h1D_jp[2][1][icoll][0]);
        //    //h1D_ratio_jetphox_sys_scale[icoll][isys]->SetLineColor(kBlue+2);
        //    h1D_ratio_jetphox_sys_scale[icoll][isys]->SetLineColor(2);
        //    h1D_ratio_jetphox_sys_scale[icoll][isys]->SetLineWidth(2);
        //    h1D_ratio_jetphox_sys_scale[icoll][isys]->SetLineStyle(8);
        //    h1D_ratio_jetphox_sys_scale[icoll][isys]->SetFillColor(kPink);
        //    h1D_ratio_jetphox_sys_scale[icoll][isys]->SetFillStyle(3004);

        //    // if(icoll==1){//pp
        //    //     //c_ratio_data_jp_pp->cd();
        //    //     c[2]->cd(2);
        //    //     h1D_ratio_jetphox_sys_scale[icoll][isys]->Draw("same l");
        //    // } else{ 
        //    //     for (int k=0; k<1; ++k) { //k=0 is 0-100 % 
        //    //         c[1]->cd(2);
        //    //         if(k==0) h1D_ratio_jetphox_sys_scale[icoll][isys]->Draw("same");
        //    //     }
        //    // }
        //}
        gr_jetphox_sys_scale[icoll] = new TGraphAsymmErrors(nPtBin-rejectPtBins[0]);
        hist_to_graph(gr_jetphox_sys_scale[icoll], h1D_jp[2][1][icoll][0], h1D_jp[2][1][icoll][1], h1D_jp[2][1][icoll][2],1);
        //hist_to_graph(gr_jetphox_sys_scale[icoll], h1D_jp[2][1][icoll][0], h1D_ratio_jetphox_sys_scale[icoll][0], h1D_ratio_jetphox_sys_scale[icoll][1]);
        gr_jetphox_sys_scale[icoll]->SetLineColor(kPink);
        gr_jetphox_sys_scale[icoll]->SetFillColor(kPink);
        gr_jetphox_sys_scale[icoll]->SetFillStyle(3004);
        if(icoll==1){//pp
            c[2]->cd(2);
            gr_jetphox_sys_scale[icoll]->Draw("2");
        } else{ 
            c[1]->cd(2);
            gr_jetphox_sys_scale[icoll]->Draw("2");
        }

    }

    cout << "JETPHOX PDF error" << endl;
    ////////////////////////////////////////////////////////////////////////////////////////
    // Calculate JETPHOX PDF error (systematic uncertainty)  
    TGraphAsymmErrors* gr_jetphox_sys_pdf[n_hist_types][nCentBinIF];
    //pbpb
    for (int i=0; i<n_hist_types; ++i) {
        for (int k=0; k<1; ++k) { //k=0 is 0-100 %
            //for (int k=0; k<nCentBinIF; ++k) {} //k=0 is 0-100 %
            if(i==0) continue; //raa
            if(hist_types[i] == "dNdpt_corr2_pp" && k>0) continue;
            c[i]->cd(2);

            gr_jetphox_sys_pdf[i][k] = new TGraphAsymmErrors(nPtBin-rejectPtBins[k]);
            gr_jetphox_sys_pdf[i][k]->SetName(Form("gr_jetphox_sys_pdf_%d_%d",i,k));
            gr_jetphox_sys_pdf[i][k]->SetFillStyle(3005);
            gr_jetphox_sys_pdf[i][k]->SetFillColor(kAzure-1); 
            gr_jetphox_sys_pdf[i][k]->SetLineColor(kAzure-1); 
            //gr_jetphox_sys_pdf[i][k]->SetFillStyle(3013);
            //gr_jetphox_sys_pdf[i][k]->SetFillColor(12); 

            for (int ipt=1; ipt<=nPtBin-rejectPtBins[k]; ++ipt) {
                double x = h1D_sys_jetphox[i]->GetBinCenter(ipt);
                double val = h1D_sys_jetphox[i]->GetBinContent(ipt);
                double error = h1D_sys_jetphox[i]->GetBinError(ipt)/val;
                double bin_width = h1D_sys_jetphox[i]->GetBinLowEdge(ipt+1) - h1D_sys_jetphox[i]->GetBinLowEdge(ipt);
                gr_jetphox_sys_pdf[i][k]->SetPointError(ipt-1, (bin_width/2), (bin_width/2), error, error);
                gr_jetphox_sys_pdf[i][k]->SetPoint(ipt-1, x, 1);
            }
            if(k==0) gr_jetphox_sys_pdf[i][k]->Draw("2");
        }
    }

    cout << "JETPHOX legend" << endl;
    ////////////////////////////////////////////////////////////////////////////////////////
    // Draw jetphox legend in each ratio plots
    TLegend* leg_jp[n_hist_types];
    for (int i=0; i<n_hist_types; ++i) {
        if(i==0) continue;
        leg_jp[i] = new TLegend(0.42,0.65,0.90,0.90);

        leg_jp[i]->SetName(Form("legend_jetphox_%d",i));
        legStyle(leg_jp[i]);
        leg_jp[i]->AddEntry(gr_ratio[i][0],"Data / JETPHOX","pl");
        leg_jp[i]->AddEntry(gr_sys_ratio[i][0],"Systematic Uncertainty","f");
       // if(i==0) leg_jp[i]->AddEntry(hjp_draw_raa[0],"JETPHOX PbPb(EPPS16+CT14)/pp(CT14)","l");
        leg_jp[i]->AddEntry(gr_jetphox_sys_pdf[i][0],"JETPHOX PDF Uncertainty","f");
        leg_jp[i]->AddEntry(gr_jetphox_sys_scale[i-1],"JETPHOX Scale Uncertainty (#font[42]{E_{T}^{#gamma}/2 < #mu < 2E_{T}^{#gamma}})","f");
        //leg_jp[i]->AddEntry(h1D_ratio_jetphox_sys_scale[i-1][0],"JETPHOX Scale Uncertainty (#font[12]{E_{T}^{#gamma}/2 < #mu < 2E_{T}^{#gamma}})","l");
       //leg_jp->AddEntry((TObject*)0,"#it{E_{T}^{#gamma}< #mu < 2E_{T}^{#gamma}}","");
        c[i]->cd(2);
        leg_jp[i]->Draw("same");
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    // Draw jetphox legend in raa plots
    int i=0;
    leg_jp[i] = new TLegend(0.42,0.20,0.90,0.45);
    leg_jp[i]->SetName(Form("legend_jetphox_%d",i));
    legStyle(leg_jp[i]);
    leg_jp[i]->AddEntry(h1D_nominal[i][0],"Data","pl");
    leg_jp[i]->AddEntry(gr_sys[i][0],"Systematic Uncertainty","f");
    leg_jp[i]->AddEntry(hjp_draw_raa[0][0],"JETPHOX PbPb(EPPS16+CT14)/pp(CT14)","l");
    leg_jp[i]->AddEntry(gr_raa_sys_scale[0],"JETPHOX PDF Uncertainty","f");
    leg_jp[i]->AddEntry(gr_raa_sys_pdf[0],"JETPHOX Scale Uncertainty (#font[42]{E_{T}^{#gamma}/2 < #mu < 2E_{T}^{#gamma}})","f");
    c_sep[0][0]->cd();
    leg_jp[i]->Draw("same");

    // //leg_jp->AddEntry((TObject*)0,"#it{E_{T}^{#gamma}< #mu < 2E_{T}^{#gamma}}","");

    cout << "cross section legend" << endl;
    ////////////////////////////////////////////////////////////////////////////////////////
    // Draw cross section legend 
    // DRAW extra text e.g. eta on cross section & spectra  
    // cross section for PbPb
    c[1]->cd(1);
    TLegend* leg_dndpt = new TLegend(0.56,0.46,0.92,0.85);
    legStyle(leg_dndpt);
    for (int k=nCentBinIF-1; k>=0; --k) { //k=0 is 0-100 % 
        if(k==0) leg_dndpt->AddEntry(h1D_nominal[1][k],Form("%d-%d %s      ",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%"),"plf");
        else if(k==1) leg_dndpt->AddEntry(h1D_nominal[1][k],Form("%d-%d %s      x 10",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%"),"plf");
        else if(k==2) leg_dndpt->AddEntry(h1D_nominal[1][k],Form("%d-%d %s    x 10^{%d}",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%",k),"plf");
        else if(k==3) leg_dndpt->AddEntry(h1D_nominal[1][k],Form("%d-%d %s    x 10^{%d}",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%",k),"plf");
        else if(k==4) leg_dndpt->AddEntry(h1D_nominal[1][k],Form("%d-%d %s  x 10^{%d}",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%",k),"plf");
        else leg_dndpt->AddEntry(h1D_nominal[1][k],Form("%d-%d %s \t x 10^{%d}",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%",k),"plf");
    }
    //leg_dndpt->AddEntry(h1D_nominal[2][0],Form("pp%s",""),"plf");
    leg_dndpt->AddEntry(hjp_draw_dndpt[0][0],"JETPHOX (EPPS16+CT14)","l");
    leg_dndpt->AddEntry((TObject*)0,"#font[42]{NLO pQCD / BFG II FF}","");
    leg_dndpt->AddEntry((TObject*)0,"#font[42]{#mu_{F} = #mu_{f} = #mu_{R} = E_{T}^{#gamma}}","");
    //leg_dndpt->AddEntry((TObject*)0,"#font[12]{#mu_{F} = #mu_{f} = #mu_{R} = E_{T}^{#gamma}}","");
    leg_dndpt->Draw("same");
    double legBottom_pbpb = leg_dndpt->GetY1();
    xpos_r = 1-c[1]->GetRightMargin();
    xpos_l = c[1]->GetLeftMargin();
    drawText("|#eta^{#gamma}| < 1.44",xpos_r-0.05,legBottom_pbpb-1*dy,1,kBlack,0.04); 

    // cross section for pp 
    c[2]->cd(1);
    TLegend* leg_dndpt_pp = new TLegend(0.56,0.63,0.92,0.85);
    legStyle(leg_dndpt_pp);
    leg_dndpt_pp->AddEntry(h1D_nominal[2][0],Form("pp%s",""),"plf");
    leg_dndpt_pp->AddEntry(hjp_draw_dndpt[1][0],"JETPHOX (CT14 PDF)","l");
    leg_dndpt_pp->AddEntry((TObject*)0,"#font[42]{NLO pQCD / BFG II FF}","");
    leg_dndpt_pp->AddEntry((TObject*)0,"#font[42]{#mu_{F} = #mu_{f} = #mu_{R} = E_{T}^{#gamma}}","");
    //leg_dndpt_pp->AddEntry((TObject*)0,"#font[132]{NLO pQCD / BFG II FF}","");
    //leg_dndpt_pp->AddEntry((TObject*)0,"#font[12]{#mu_{F} = #mu_{f} = #mu_{R} = E_{T}^{#gamma}}","");
    leg_dndpt_pp->Draw("same");
    double legBottom_pp = leg_dndpt_pp->GetY1();
    drawText("|#eta^{#gamma}| < 1.44",xpos_r-0.05,legBottom_pp-1*dy,1,kBlack,0.04); 
    
    // DRAW extra text e.g. eta on RAA  
    //c[0]->cd(); // RAA plot
    //double legBottom_raa = leg_dndpt->GetX1();
    //drawText("|#eta^{#gamma}| < 1.44",xpos_r-dy,,1,kBlack,0.04); 
    //drawText("|#eta^{#gamma}| < 1.44",xpos_r-dy,legBottom+2*dy,1,kBlack,0.04); 
    //globalUncBox -> Draw("l same");

    ////Legend for DATA/JETPHOX ratio
    ////c_ratio_data_jp->cd();
    //TLegend* leg_ratio = new TLegend(0.55,0.64,0.90,0.90);
    //legStyle(leg_ratio);
    //for (int k=nCentBinIF-1; k>0; --k) { //k=0 is 0-100 % 
    //    if(k==1)     leg_ratio->AddEntry(h1D_nominal[1][k],Form("%d-%d %s      / EPPS16+CT14 nlo",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%"),"plf");
    //    else if(k==2) leg_ratio->AddEntry(h1D_nominal[1][k],Form("%d-%d %s    / EPPS16+CT14 nlo",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%"),"plf");
    //    else if(k==3) leg_ratio->AddEntry(h1D_nominal[1][k],Form("%d-%d %s    / EPPS16+CT14 nlo",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%"),"plf");
    //    else if(k==4) leg_ratio->AddEntry(h1D_nominal[1][k],Form("%d-%d %s  / EPPS16+CT14 nlo",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%"),"plf");
    //    else leg_ratio->AddEntry(h1D_nominal[1][k],Form("%d-%d %s \t / EPPS16+CT14 nlo",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%"),"plf");
    //}
    //leg_ratio->AddEntry(h1D_nominal[2][0],Form("pp        / CT14 nlo%s",""),"plf");
    ////if(doJETPHOX) leg_ratio->AddEntry(hjp_draw_dndpt[0][0],"JETPHOX (CT14 NLO)","l");
    ////if(doJETPHOX) leg_ratio->AddEntry(hjp_draw_dndpt[1][0],"JETPHOX (EPPS16+CT14 NLO)","l");
    //leg_ratio->Draw("same");
    
    //c_ratio_data_jp->SaveAs(Form("%splotting/figures/finalPlot_ratio_data_to_JEXPHOX_%s_total.pdf",dir.Data(),cap.Data()));
    //c_ratio_data_jp_pp->SaveAs(Form("%splotting/figures/finalPlot_ratio_data_to_JEXPHOX_%s_pp.pdf",dir.Data(),cap.Data()));
    //for (int k=0; k<nCentBinIF; ++k)
    //    c_ratio_data_jp_pbpb[k]->SaveAs(Form("%splotting/figures/finalPlot_ratio_data_to_JEXPHOX_%s_cent%d_%d.pdf",dir.Data(),cap.Data(),(int)centBins_i[k]/2,(int)centBins_f[k]/2));
    //
/*
*/
    /////////////////////////////////////////////////////////////////////////////////////////////
    // Store pdf files 
    cout << "Save figures..." << endl;
    //c_temp2->SaveAs(Form("%splotting/figures/finalPlot_temp_%s_total.pdf",dir.Data(),cap.Data()));
    for (int i=0; i<n_hist_types; ++i) {
        //if(hist_types[i] != "dNdpt_corr2_pp") 
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

TGraphAsymmErrors* divide_graph_by_hist(TGraphAsymmErrors* gr=0, TH1D* h1=0){
    int np = gr->GetN();                                        
    TGraphAsymmErrors* new_gr = (TGraphAsymmErrors*) gr->Clone(Form("%s_dividedBy_%s",gr->GetName(),h1->GetName()));
    //TGraphAsymmErrors* new_gr = new TGraphAsymmErrors(np);
    new_gr->SetName(Form("%s_dividedBy_%s",gr->GetName(),h1->GetName()));
    for (int p=0; p<np; ++p) {                                         
        double Xmean = 0;                            
        double Ymean = 0;               
        double scaleF = h1->GetBinContent(p+1);        
        gr->GetPoint(p,Xmean,Ymean); 
        new_gr->SetPoint(p,Xmean,Ymean/scaleF); 
        double Xerr_l= gr->GetErrorXlow(p); 
        double Xerr_h= gr->GetErrorXhigh(p);
        double Yerr_l= gr->GetErrorYlow(p);
        double Yerr_h= gr->GetErrorYhigh(p);
        new_gr->SetPointError(p,Xerr_l,Xerr_h,Yerr_l/scaleF,Yerr_h/scaleF);                
    }
    return new_gr;
}

void hist_to_graph(TGraphAsymmErrors* gr=0, TH1D* h1=0, TH1D* h2=0, TH1D* h3=0, bool doSelfScale=1){
    int np = gr->GetN();                                        
    for (int p=0; p<np; ++p) {                                         
        double Xmean = h1->GetBinCenter(p+1);
        double bin_width = h1->GetBinLowEdge(p+2) - h1->GetBinLowEdge(p+1);
        double nominal = h1->GetBinContent(p+1);        
        double sysDown = h2->GetBinContent(p+1);        
        double sysUp = h3->GetBinContent(p+1);        
        double dy = abs(nominal-sysDown);
        if(dy<abs(sysUp-nominal)) dy = abs(sysUp-nominal);
        cout << " nominal = " << nominal << ", sysDown = " << sysDown << ", sysUp = " << sysUp << endl;

        if(doSelfScale){
            gr->SetPoint(p,Xmean,nominal/nominal); 
            gr->SetPointError(p,(bin_width)/2.,(bin_width)/2.,dy/nominal,dy/nominal);                
        } else{
            gr->SetPoint(p,Xmean,nominal); 
            gr->SetPointError(p,(bin_width)/2.,(bin_width)/2.,dy,dy);                
        }
        //if(doSelfScale){
        //    gr->SetPoint(p,Xmean,nominal/nominal); 
        //    gr->SetPointError(p,(bin_width)/2.,(bin_width)/2.,(nominal-sysDown)/nominal,(sysUp-nominal)/nominal);                
        //} else{
        //    gr->SetPoint(p,Xmean,nominal); 
        //    gr->SetPointError(p,(bin_width)/2.,(bin_width)/2.,nominal-sysDown,sysUp-nominal);                
        //}
    }
}
