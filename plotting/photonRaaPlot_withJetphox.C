// photonRaaPlot.C
// draw the final plots 
// Author: Yeonju Go
// Modified at 2018 June 10

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/temp_phoRaaCuts_temp.h"
//#include "../phoRaaCuts/styleUtil.h"
#include "../phoRaaCuts/tdrstyle.C"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TAttFill.h"

static const float ncoll_w_npart[4] = {43.58, 118.8, 239.9, 363.4};
void draw_sys_unc(TGraphErrors* gr, TH1* h1, TH1* h1_sys);
void draw_npart_sys_unc(TGraphErrors* gr, TH1* h1, TH1* h1_sys, int x_width);

const int markerStyle[]={20,33,22,23,22,29};
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
#define TH1_TO_TGRAPH(hist, graph)                                          \
    int npoints = hist->GetNbinsX();                                        \
graph = new TGraphAsymmErrors(npoints);                                 \
for (int p=0; p<npoints; ++p) {                                         \
    double Xmean = ptBins_mean_pbpb[p];                                 \
    double Ymean = hist->GetBinContent(p+1);                            \
    double Xerr_l= Xmean-ptBins_draw[p];                                \
    double Xerr_h= ptBins_draw[p+1]-Xmean;                              \
    double Yerr_l= hist->GetBinError(p+1);                              \
    double Yerr_h= hist->GetBinError(p+1);                              \
    graph->SetPoint(p, Xmean, Ymean);                                   \
    graph->SetPointError(p,Xerr_l,Xerr_h,Yerr_l,Yerr_h);                \
}

void photonRaaPlot_withJetphox(TString ver="180610_temp_v15") {
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);

    TString cap = "withJetphox_ppNLO";
    // input files 
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/";
    const std::string input_file = Form("%sresults/output/phoRaa_%s_nominal.root",dir.Data(),ver.Data());
    const std::string sys_file = Form("%ssystematics/output/systematics_%s_cent0to100.root",dir.Data(),ver.Data());
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
    double sys_global = sys_ppLumi; 
    //double sys_global = TMath::Sqrt(sys_MB*sys_MB+sys_ppLumi*sys_ppLumi); 

    // define histograms, graphs, ..., etc 
    TObject* generic[n_hist_types][nCentBinIF];
    TH1D* h1D_nominal[n_hist_types][nCentBinIF];
    TH1D* systematics[n_hist_types][nCentBinIF];            
    TH1D* htemp[n_hist_types]; // for cosmetics, will draw axis and its titles
    TGraphAsymmErrors* gr_sys[n_hist_types][nCentBinIF];
    TGraphAsymmErrors* gr_nominal[n_hist_types][nCentBinIF];
    TGraphAsymmErrors* gr_sys_scaled[nCentBinIF]; // for dNdpt
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
            h1D_nominal[i][k] = (TH1D*)generic[i][k];
            systematics[i][k] = (TH1D*)sys->Get((hist_name + "_diff_total").c_str());
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
            TH1_TO_TGRAPH(h1D_nominal[i][k], gr_nominal[i][k])
                gr_nominal[i][k]->SetMarkerColor(colorStyle_marker[k]);
            gr_nominal[i][k]->SetLineColor(colorStyle_marker[k]);
            gr_nominal[i][k]->SetMarkerStyle(markerStyle[k]);
            if(hist_types[i] == "dNdpt_corr2_pp"){
                gr_nominal[i][k]->SetMarkerColor(colorStyle_marker_pp);
                gr_nominal[i][k]->SetLineColor(colorStyle_line_pp);
                gr_nominal[i][k]->SetMarkerStyle(markerStyle_pp);
            } 

            //systematic part
            gr_sys[i][k] = new TGraphAsymmErrors(h1D_nominal[i][k]);
            gr_sys[i][k]->SetName(Form("gr_sys_%d_%d",i,k));
            cout << h1D_nominal[i][k]->GetNbinsX() << endl;
            for (int ipt=1; ipt<=h1D_nominal[i][k]->GetNbinsX(); ++ipt) {
                //if (h1D_nominal[i][k]->GetBinError(i) == 0) continue;
                double x = h1D_nominal[i][k]->GetBinCenter(ipt);
                int sys_bin = systematics[i][k]->FindBin(x);
                double bin_width = h1D_nominal[i][k]->GetBinLowEdge(ipt+1) - h1D_nominal[i][k]->GetBinLowEdge(ipt);
                double val = h1D_nominal[i][k]->GetBinContent(ipt);
                double error = TMath::Abs(systematics[i][k]->GetBinContent(sys_bin));
                cout << "histname : " << hist_name << ", ipt " << ipt << ", Systematic Error = " << error << endl;
                Double_t pxtmp, pytmp;
                gr_sys[i][k]->SetPointError(ipt-1, (bin_width/2), (bin_width/2), error, error); 
                //gr_sys[i][k]->SetPoint(ipt-1, (bin_width/2), (bin_width/2), error, error); 
                //cout << "ipt = "<< ipt << ": " << gr_sys[i][k]->GetErrorYhigh(ipt-1) << endl;
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

    TBox *globalUncBox = new TBox(ptBins_draw_final[0],1-sys_global,ptBins_draw_final[0]+5,1+sys_global);
    globalUncBox -> SetFillColorAlpha(kGray+2,0.5);
    globalUncBox -> SetLineColor(kBlack);
    globalUncBox -> SetLineWidth(2);
    for (int i=0; i<n_hist_types; ++i) {
        for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100 %
            if(hist_types[i] == "dNdpt_corr2_pp" && k>0) continue;
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

            if(hist_types[i] != "Raa") htemp[i]->GetYaxis()->SetRangeUser(1,1.e+3);
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
            if(i==0){
                //globalUncBox = new TBox(xpos_l+sys_global_x*3,1-sys_global,xmax-sys_global_x*2,1+sys_global);
                globalUncBox -> Draw("l same");
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
            if(hist_types[i] != "Raa") htemp[i]->GetYaxis()->SetRangeUser(0.1,1e+8);
            if(k==0 && hist_types[i] != "dNdpt_corr2_pp") htemp[i]->DrawCopy();

            ////////////////////////////
            // Scale dNdpt 
            if(hist_types[i] == "dNdpt_corr2"){
                float scale = 0.;
                if(k==0) continue; 
                else if(k==1) scale = 10.; 
                else if(k==2) scale = 100.; 
                else if(k==3) scale = 1000.; 
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
    ////////////////////////////////
    // Draw cross section legend 
    c[1]->cd();
    TLegend* leg_dndpt = new TLegend(0.55,0.69,0.90,0.90);
    legStyle(leg_dndpt);
    //    leg_dndpt->AddEntry(h1D_nominal[1][3],"30-100\% x 10^{3}","plf");
    //    leg_dndpt->AddEntry(h1D_nominal[1][2],"10-30\% x 10^{2}","plf");
    //    leg_dndpt->AddEntry(h1D_nominal[1][1],"0-10\% x 10","plf");
    for (int k=nCentBinIF-1; k>0; --k) { //k=0 is 0-100 % 
        if(k==1) leg_dndpt->AddEntry(h1D_nominal[1][k],Form("%d-%d %s      x 10",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%"),"plf");
        else if(k==2) leg_dndpt->AddEntry(h1D_nominal[1][k],Form("%d-%d %s    x 10^{%d}",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%",k),"plf");
        else if(k==3) leg_dndpt->AddEntry(h1D_nominal[1][k],Form("%d-%d %s  x 10^{%d}",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%",k),"plf");
        else leg_dndpt->AddEntry(h1D_nominal[1][k],Form("%d-%d %s \t x 10^{%d}",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%",k),"plf");
    }
    leg_dndpt->AddEntry(h1D_nominal[2][0],Form("pp%s",""),"plf");
    leg_dndpt->Draw("same");

    double legBottom = leg_dndpt->GetX1();
    //double legTop = leg_dndpt->GetX2();
    //cout << "legBottom = " << legBottom << ", GetX1() = "<< legTop << endl;
    float xpos_r = 1-c[1]->GetRightMargin();
    float dy = 0.05; 
    float extraDY = 1.5; 
    //drawText(Form("%d-%d %s",(int)centBins_i[k]/2,(int)centBins_f[k]/2,"%"),xpos_r-dy,legBottom-dy*extraDY,1,kBlack,0.04); 
    drawText("|#eta^{#gamma}| < 1.44",xpos_r-dy,legBottom+2*dy,1,kBlack,0.04); 

    c[0]->cd(); // RAA plot
    drawText("|#eta^{#gamma}| < 1.44",xpos_r-dy,legBottom+2*dy,1,kBlack,0.04); 
    //globalUncBox -> Draw("l same");


    /////////////////////////////////////////////////////////////////////////////////////////////
    // Draw Jetphox pp NLO
    // direct contribution
    TFile* fdir = TFile::Open("/home/goyeonju/CMS/2016/JETPHOX/jetphox_1.3.1_3_pp/pawres/ggd_2test_pp_0609.root","read");
    TH1D* h1D_jp_dir[2];//0:Leading Order, 1:Next-to-Leading Order
    h1D_jp_dir[0] = (TH1D*) fdir->Get("hp40"); 
    h1D_jp_dir[1] = (TH1D*) fdir->Get("hp41"); 
   
    // one fragmentation contribution
    TFile* fonef = TFile::Open("/home/goyeonju/CMS/2016/JETPHOX/jetphox_1.3.1_3_pp/pawres/ggo_2test_pp_0609.root","read");
    TH1D* h1D_jp_onef[2];//0:Leading Order, 1:Next-to-Leading Order
    h1D_jp_onef[0] = (TH1D*) fonef->Get("hp40"); 
    h1D_jp_onef[1] = (TH1D*) fonef->Get("hp41"); 
   
    TH1D* h1D_jp_inclusive[2];//0:Leading Order, 1:Next-to-Leading Order
    h1D_jp_inclusive[0] = (TH1D*) h1D_jp_dir[0]->Clone("jp_dir_onef_lo");
    h1D_jp_inclusive[0]->Add(h1D_jp_onef[0]);
    
    h1D_jp_inclusive[1] = (TH1D*) h1D_jp_dir[1]->Clone("jp_dir_onef_nlo");
    h1D_jp_inclusive[1]->Add(h1D_jp_onef[1]);

    for(int i=0;i<2;++i){
        h1D_jp_dir[i]->Scale(1./2.88); 
        h1D_jp_onef[i]->Scale(1./2.88); 
        h1D_jp_inclusive[i]->Scale(1./2.88); 
        h1D_jp_dir[i]->SetLineColor(2);
        h1D_jp_onef[i]->SetLineColor(4);
        h1D_jp_inclusive[i]->SetLineColor(8);
    }
    //Cross section
    c[1]->cd();
    h1D_jp_dir[1]->Draw("hist same");
    h1D_jp_onef[1]->Draw("hist same");
    h1D_jp_inclusive[1]->Draw("hist same");


    /////////////////////////////////////////////////////////////////////////////////////////////
    // Store pdf files 
    cout << "Save figures..." << endl;
    for (int i=0; i<n_hist_types; ++i) {
        if(hist_types[i] != "dNdpt_corr2_pp") 
            c[i]->SaveAs(Form("%splotting/figures/finalPlot_%s_%s_total_%s.pdf",dir.Data(),hist_types[i].c_str(),ver.Data(),cap.Data()));
        for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100 % 
            if(hist_types[i] == "dNdpt_corr2_pp" && k>0) continue;
            c_sep[i][k]->SaveAs(Form("%splotting/figures/finalPlot_%s_%s_%s_cent%d_%d.pdf",dir.Data(),hist_types[i].c_str(),ver.Data(),cap.Data(),(int)centBins_i[k]/2,(int)centBins_f[k]/2));
        }
    }


    //    gRFB_sys[iy]->GetXaxis()->SetLimits(0.,32.0);
    //    gRFB_sys[iy]->SetMinimum(0.0);
    //    gRFB_sys[iy]->SetFillColorAlpha(kRed-10,0.5);
    //    gRFB_sys[iy]->SetLineColor(kPink-6);
    //    gRFB_sys[0]->SetFillColorAlpha(kGreen-10,0.5);
    //    gRFB_sys[1]->SetFillColorAlpha(kRed-10,0.5);
    //    gRFB_sys[2]->SetFillColorAlpha(kBlue-10,0.5);
    //    gRFB_sys[0]->SetLineColor(kGreen+3);
    //    gRFB_sys[1]->SetLineColor(kPink-6);
    //    gRFB_sys[2]->SetLineColor(kBlue-3);

    //// global uncertainty from lumi
    //    TBox * globbox_pp = new TBox(0.0, 1-pp_lumi_relerr, 1.5, 1+pp_lumi_relerr);
    //    globbox_pp->SetFillColorAlpha(kGray+2,0.5);
    //    globbox_pp->SetLineColor(kBlack);
    //    TBox * globbox_pa = new TBox(1.5, 1-pPb_lumi_relerr, 3.0, 1+pPb_lumi_relerr);
    //    globbox_pa->SetFillColorAlpha(kWhite,0.5);
    //    globbox_pa->SetLineColor(kBlack);
    //    TBox * globbox_all = new TBox(0.0, 1-glb_err, 1.5, 1+glb_err);
    //    globbox_all->SetFillColorAlpha(kGray+2,0.5);
    //    globbox_all->SetLineColor(kBlack);

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

