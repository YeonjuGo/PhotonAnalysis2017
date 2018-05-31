// photonRaaPlot.C
// draw the final plots 
// Author: Yeonju Go
// Written at 2017 Nov 26

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TAttFill.h"

static const float ncoll_w_npart[4] = {43.58, 118.8, 239.9, 363.4};
void draw_sys_unc(TGraphErrors* gr, TH1* h1, TH1* h1_sys);
void draw_npart_sys_unc(TGraphErrors* gr, TH1* h1, TH1* h1_sys, int x_width);

const int markerStyle[]={20,33,21,23,22,34};
//const int markerStyle[]={20,27,25,34,22,23};
//kFullCircle,kOpenDiamond, kOpenSquare 
//const int colorStyle_marker[]={kBlack,kRed-10,kGreen-10,kBlue-10,kOrange-3};
//const int colorStyle_marker[]={kBlack,kPink,kGreen,kBlue,kOrange};
//const int colorStyle_sys[]={kYellow,kRed,kGreen,kBlue,kOrange};
//const int colorStyle_line[]={kYellow,kPink,kGreen,kBlue,kOrange};
const int colorStyle_marker[]={kBlack,kPink-6,kGreen+3,kBlue-3,kOrange+4};
const int colorStyle_sys[]={kYellow-7,kRed-10,kGreen-10,kBlue-10,kOrange-3};
const int colorStyle_line[]={kYellow-4,kPink-6,kGreen+3,kBlue-3,kOrange+4};
const double transparency[]={0.5,0.5,0.5,0.5,0.5,0.5};

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

void photonRaaPlot(TString ver="171017_temp_v9") {
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/";
    const std::string input_file = Form("%sresults/output/phoRaa_%s_nominal.root",dir.Data(),ver.Data());
    const std::string sys_file = Form("%ssystematics/output/systematics_%s.root",dir.Data(),ver.Data());
    TFile* input = new TFile(input_file.c_str(), "read");
    TFile* sys = new TFile(sys_file.c_str(), "read");
    std::vector<std::string> hist_types {
        "Raa", "dNdpt_corr2"
    };
    int n_hist_types = hist_types.size(); 
    TCanvas* c[n_hist_types];
    TObject* generic[n_hist_types][nCentBinIF];
    TH1D* h1D_nominal[n_hist_types][nCentBinIF];
    TH1D* htemp[n_hist_types];
    TGraphAsymmErrors* gr_sys[n_hist_types][nCentBinIF];
    TGraphAsymmErrors* gr_nominal[n_hist_types][nCentBinIF];
    auto mg  = new TMultiGraph();

    TCanvas* ctemp[n_hist_types];
    TCanvas* c_sep[n_hist_types][nCentBinIF];
    TH1D* systematics[n_hist_types][nCentBinIF];            

    TH1D* h1D_dNdpt_pp = (TH1D*) input ->Get("h1D_dNdpt_corr2_pp"); 
    TGraphAsymmErrors* gr_dNdpt_pp_nominal; 
    TGraphAsymmErrors* gr_dNdpt_pp_sys;

    for (int i=0; i<n_hist_types; ++i) {
        c[i] = new TCanvas(Form("c_%s",hist_types[i].c_str()),"",600,680);
        c[i]->cd();
        for (int k=0; k<nCentBinIF; ++k) { //k=0 is allCentBin
            std::string hist_name;
            hist_name = Form("h1D_%s_cent%d", hist_types[i].c_str(), k);
            generic[i][k] = input->Get(hist_name.data());
            h1D_nominal[i][k] = (TH1D*)generic[i][k];
            //systematics[i][k] = (TH1D*)sys->Get((hist_name + "_diff_total").c_str());
            systematics[i][k] = (TH1D*)sys->Get((hist_name + "_diff_sys_purUp_sys_purDown_total").c_str());
            // COSMETICS
            if(k==0){    
                htemp[i] = (TH1D*) h1D_nominal[i][0]->Clone(Form("htemp_%d",i));
                htemp[i]->SetMarkerColor(0);
                htemp[i]->SetLineColor(0);
                htemp[i]->Draw("e p");
            }

            h1D_nominal[i][k]->SetMarkerColor(colorStyle_marker[k]);
            h1D_nominal[i][k]->SetLineColor(colorStyle_marker[k]);
            h1D_nominal[i][k]->SetMarkerStyle(markerStyle[k]);
            if(markerStyle[i]==33)
                h1D_nominal[i][k]->SetMarkerSize(1.6);
            
            TH1_TO_TGRAPH(h1D_nominal[i][k], gr_nominal[i][k])
            gr_nominal[i][k]->SetMarkerColor(colorStyle_marker[k]);
            gr_nominal[i][k]->SetLineColor(colorStyle_marker[k]);
            gr_nominal[i][k]->SetMarkerStyle(markerStyle[k]);

            gr_sys[i][k] = new TGraphAsymmErrors(h1D_nominal[i][k]);
            gr_sys[i][k]->SetName(Form("gr_sys_%d_%d",i,k));
           
            for (int ipt=1; ipt<=h1D_nominal[i][k]->GetNbinsX(); ++ipt) {
                //if (h1D_nominal[i][k]->GetBinError(i) == 0) continue;
                double x = h1D_nominal[i][k]->GetBinCenter(ipt);
                int sys_bin = systematics[i][k]->FindBin(x);
                double bin_width = h1D_nominal[i][k]->GetBinLowEdge(ipt+1) - h1D_nominal[i][k]->GetBinLowEdge(ipt);
                double val = h1D_nominal[i][k]->GetBinContent(ipt);
                double error = TMath::Abs(systematics[i][k]->GetBinContent(sys_bin));
                Double_t pxtmp, pytmp;
                gr_sys[i][k]->SetPointError(ipt-1, (bin_width/2), (bin_width/2), error, error); 
                cout << "ipt = "<< ipt << ": " << gr_sys[i][k]->GetErrorYhigh(ipt-1) << endl;
            } 
            //gr_sys[i][k]->SetFillStyle(4050);
            gr_sys[i][k]->SetFillStyle(1001);
            gr_sys[i][k]->SetFillColorAlpha(colorStyle_sys[k],0.5-0.05*k);
            if(hist_types[i] == "Raa")
                gr_sys[i][k]->GetYaxis()->SetRangeUser(0.5,1.5);
            
           // if(k==0) gr_sys[i][k]->Draw("A2");
           // else gr_sys[i][k]->Draw("2");
            gr_sys[i][k]->DrawClone("2");
            
            if(hist_types[i] == "Raa")
                jumSun(40,1,120,1);
            if(hist_types[i] == "dNdpt_corr2")
                gPad->SetLogy();
        }
    }
   
    ////////////////////////////////////////
    // DRAW : All centrality in one panel 
    TLegend* leg = new TLegend(0.55,0.7,0.85,0.9);
    legStyle(leg);
    for (int i=0; i<n_hist_types; ++i) {
        for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100 % 
            c[i]->cd();
            if(k==0) htemp[i]->Draw();
           // mg->Add(gr_nominal[i][k],"P");
           // mg->Add(gr_sys[i][k],"2");
           // mg->Draw("pmc plc");
            gr_sys[i][k]->Draw("2");
            gr_nominal[i][k]->Draw("P");
            //h1D_nominal[i][k]->Draw("same e p");
            if(i==0){
                leg->AddEntry(h1D_nominal[i][k],Form("Cent %d-%d %s",(int)(centBins_i[k]/2),(int)(centBins_f[k]/2),"%"),"pl");
            }
            if(hist_types[i] == "Raa"){
                jumSun(40,1,120,1);
            }
        }
        leg->Draw("same");
    } 
   
    ////////////////////////////////////////
    // DRAW : Centrality seperately 
    for (int i=0; i<n_hist_types; ++i) {
        for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100 %
            c_sep[i][k] = new TCanvas(Form("c_%s_%d",hist_types[i].c_str(),k),"",600,680);
            c_sep[i][k]->cd();
            if(hist_types[i] == "dNdpt_corr2"){
                gPad->SetLogy();
            }
            htemp[i]->Draw("p");
            gr_sys[i][k]->SetFillColorAlpha(colorStyle_sys[k],0.2);
            gr_sys[i][k]->Draw("2");
            gr_nominal[i][k]->Draw("P");
            //gr_nominal[i][k]->Draw("same e p");
            drawText(Form("%d-%d %s",(int)centBins_i[k]/2,(int)centBins_f[k]/2,"%"),0.2,0.2); 
            if(hist_types[i] == "Raa"){
                jumSun(40,1,120,1);
            }
        }
    }
    
    for (int i=0; i<n_hist_types; ++i) {
        c[i]->SaveAs(Form("%splotting/figures/finalPlot_%s_%s.pdf",dir.Data(),hist_types[i].c_str(),ver.Data()));
        for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100 % 
            c_sep[i][k]->SaveAs(Form("%splotting/figures/finalPlot_%s_%s_cent%d_%d.pdf",dir.Data(),hist_types[i].c_str(),ver.Data(),(int)centBins_i[k]/2,(int)centBins_f[k]/2));
        }
    }


//    gRFB_sys[iy]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
//    gRFB_sys[iy]->GetXaxis()->CenterTitle();
//    gRFB_sys[iy]->GetYaxis()->SetTitle("R_{FB}");
//    gRFB_sys[iy]->GetYaxis()->CenterTitle();
//    gRFB_sys[iy]->GetXaxis()->SetLimits(0.,32.0);
//    gRFB_sys[iy]->SetMinimum(0.0);
//    gRFB_sys[iy]->SetFillColorAlpha(kRed-10,0.5);
//    gRFB_sys[iy]->SetLineColor(kPink-6);
//
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

void draw_sys_unc(TGraphErrors* gr, TH1* h1, TH1* h1_sys) {
    for (int i=1; i<=h1->GetNbinsX(); ++i) {
        if (h1->GetBinError(i) == 0) continue;

        double x = h1->GetBinCenter(i);
        int sys_bin = h1_sys->FindBin(x);
        double bin_width = h1->GetBinLowEdge(i+1) - h1->GetBinLowEdge(i);

        double val = h1->GetBinContent(i);
        double error = 0.2; 
        //double error = TMath::Abs(h1_sys->GetBinContent(sys_bin));
        cout << "error : " << error << endl; 
        Double_t pxtmp, pytmp;
        gr->GetPoint(i, pxtmp, pytmp);
        gr->SetPointError(i, 10, error); 
        //gr->SetPointError(i, (bin_width/2), error); 
      //  gr->SetPointError(i, (bin_width/2), TMath::Abs(val-error)); 

       // gr->SetPoint(0, x - (bin_width/2), std::max(val - error, h1->GetMinimum()));
       // gr->SetPoint(1, x + (bin_width/2), std::max(val - error, h1->GetMinimum()));
       // gr->SetPoint(2, x + (bin_width/2), std::min(val + error, h1->GetMaximum()));
       // gr->SetPoint(3, x - (bin_width/2), std::min(val + error, h1->GetMaximum()));

        //gr->DrawClone("same f");
    }
}

void draw_npart_sys_unc(TGraphErrors* gr, TH1* h1, TH1* h1_sys, int x_width) {
    for (int i=1; i<=h1->GetNbinsX(); ++i) {
        if (h1->GetBinError(i) == 0) continue;

        double x = ncoll_w_npart[i-1];
        double val = h1->GetBinContent(i);
        double error = TMath::Abs(h1_sys->GetBinContent(i));

        if (val < 0)
            continue;

        gr->SetPoint(0, x - (x_width/2), std::max(val - error, h1->GetMinimum()));
        gr->SetPoint(1, x + (x_width/2), std::max(val - error, h1->GetMinimum()));
        gr->SetPoint(2, x + (x_width/2), std::min(val + error, h1->GetMaximum()));
        gr->SetPoint(3, x - (x_width/2), std::min(val + error, h1->GetMaximum()));

        gr->DrawClone("f");
    }
}
