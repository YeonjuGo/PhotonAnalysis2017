// drawSystematicPlots.C 
// draw systematics plots
// Author: Yeonju Go 
// Written at 2017 Dec 13

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
//#include "../ElectroWeak-Jet-Track-Analyses/Systematics/interface/SysVar.h"
const int colorStyle[]={kBlack,kPink-6,kGreen+3,kBlue-3,kOrange+4,kYellow+2,kMagenta,kCyan+2,kOrange+9,kGreen+2,kBlue+3,kRed,kYellow+3};
const int markerStyle[]={21,20,33,22,23,22,29};
void drawSystematicPlots(TString ver="180610_temp_v15")
{
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0000);
    //SetyjPadStyle();
    setTDRStyle();

    std::vector<std::string> sys_types {
        "sys_effUp",
        "sys_effDown",
        "sys_purUp",
        "sys_purDown",
        "sys_phoEresol_sigUp",                                              
        "sys_phoEresol_sigDown",                                              
       // "sys_phoEresol_rmsUp",                                              
       // "sys_phoEresol_rmsDown",                                              
        "sys_phoEscale",
        "sys_eleCont",
        //"sys_phoIso",                                              
        //"sys_mc",                                              
        "sys_TAA",                                              
    };
    int n_sys_types = sys_types.size();

    std::vector<std::string> sys_method {
        "diff", "ratio"
    };
    int n_sys_method = sys_method.size();
    
    std::vector<std::string> hist_types {
        "Raa", "dNdpt_corr2", "dNdpt_corr2_pp" 
    };
    int n_hist_types = hist_types.size();
   /* 
    std::vector<std::string> list;
    for(int i=0; i<n_sys_method; ++i){
        list.push_back(Form("%s_total",sys_method.at(i).c_str()));
        list.push_back(Form("%s_sys_purUp_sys_purDown_total",sys_method.at(i).c_str()));
        for(int k=0; k<n_sys_types; ++k){
            list.push_back(Form("%s_abs_%s",sys_method.at(i).c_str(),sys_types.at(k).c_str()));
        }
    }
    const int n_list = list.size();
   */ 
    
    std::vector<std::string> list;
    list.push_back("total");
    //list.push_back("sys_purUp_sys_purDown_total");
    for(int k=0; k<n_sys_types; ++k){
        list.push_back(Form("abs_%s",sys_types.at(k).c_str()));
    }
    const int n_list = list.size();

    TFile* file = new TFile(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/systematics/output/systematics_%s_cent0to100.root",ver.Data()));

    TH1D* h[n_hist_types][n_list][n_sys_method][nCentBinIF]; 
    TCanvas* c[n_hist_types][n_list][n_sys_method]; 


    //////////////////////////////////////////////////////
    // Draw systematics seperately depending on sources 
    cout << "Draw systematics seperately ... " << endl;
    for(int i=0; i<n_hist_types; ++i){//Raa, dNdpt
        Int_t nCENTBINS = nCentBinIF;
        if(hist_types[i] == "dNdpt_corr2_pp") nCENTBINS = 1; 
        for(int j=0; j<n_list; ++j){// systematic sources
            for (int l=0; l<n_sys_method; ++l) { //diff, ratio
                c[i][j][l] = new TCanvas(Form("c_%d_%d_%d",i,j,l),"",300*nCENTBINS,300);
                c[i][j][l]->Divide(nCENTBINS,1);
                for (int k=0; k<nCENTBINS; ++k) { //centrality (k=0 is 0-100%)
                    c[i][j][l]->cd(k+1);
                    TString hist_name = Form("h1D_%s_cent%d_%s_%s",hist_types.at(i).c_str(),k,sys_method.at(l).c_str(),list.at(j).c_str());
                    if(hist_types[i] == "dNdpt_corr2_pp") hist_name = Form("h1D_%s_%s_%s",hist_types.at(i).c_str(),sys_method.at(l).c_str(),list.at(j).c_str());
                    h[i][j][l][k] = (TH1D*) file->Get(Form("%s",hist_name.Data()));
                    if(h[i][j][l][k]->IsZombie()){
                        cout << "There's no <" << hist_name << "> histogram " << endl;
                        continue;
                    }

                    if(sys_method[l]=="diff") h[i][j][l][k]->GetYaxis()->SetTitle("|Variation-Nominal|");
                    else if(sys_method[l]=="ratio") h[i][j][l][k]->GetYaxis()->SetTitle("|(Variation-Nominal)/Nominal|");
                    if(sys_method[l]=="ratio") h[i][j][l][k]->GetYaxis()->SetRangeUser(0,0.3);
                    else {
                        if(hist_types[i] == "Raa") h[i][j][l][k]->GetYaxis()->SetRangeUser(0,0.3);
                    }
                    //if(sys_method[l]=="ratio") cout << "list name including ratio = " << list.at(j).c_str() << endl;

                    h[i][j][l][k]->Draw();
                    drawText(Form("%s_%s_%s",hist_types.at(i).c_str(),sys_method.at(l).c_str(),list.at(j).c_str()),0.2,1.0-(c[i][j][l]->GetTopMargin()+0.05));
                    if(hist_types[i] != "dNdpt_corr2_pp") drawText(Form("Cent %d-%d %s",(int)centBins_i[k]/2,(int)centBins_f[k]/2,"%"),0.2,1.0-(c[i][j][l]->GetTopMargin()+0.12));
                }
                c[i][j][l]->SaveAs(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/systematics/figures/systematics_%s_%s_%s_%s.pdf",hist_types.at(i).c_str(),sys_method.at(l).c_str(),list.at(j).c_str(),ver.Data()));
            }
        }
    }
     
    //////////////////////////////////////////////////////
    // Draw systematics all sources in one panel together (only ratio)
    cout << "Draw all sources' of systematics in one panel together ... " << endl;
    TCanvas* c_tot[n_hist_types]; 
    TLegend* l1 = new TLegend(0.6,0.6,0.9,0.9);
    TLegend* l1_pp = new TLegend(0.6,0.6,0.9,0.9);
    legStyle(l1);
    legStyle(l1_pp);
    for(int i=0; i<n_hist_types; ++i){
        Int_t nCENTBINS = nCentBinIF;
        if(hist_types[i] == "dNdpt_corr2_pp") nCENTBINS = 1; 
        c_tot[i] = new TCanvas(Form("c_tot_%d",i),"",300*nCENTBINS,300);
        c_tot[i]->Divide(nCENTBINS,1);
        for (int k=0; k<nCENTBINS; ++k) { //k=0 is 0-100%
            c_tot[i]->cd(k+1);
            for(int j=0; j<n_list; ++j){
                h[i][j][1][k]->GetYaxis()->SetTitle("|(Variation-Nominal)/Nominal|");
                h[i][j][1][k]->GetYaxis()->SetRangeUser(0,0.5);
                h[i][j][1][k]->SetLineColor(colorStyle[j]);
                if(j==0) h[i][j][1][k]->Draw("hist");
                else h[i][j][1][k]->Draw("hist same");
                
                //to obtaion legend
                if(i==0 && k==0){
                    string tempSt = "";
                    if(j==0) tempSt = "Tatal";
                    else tempSt = list[j].substr(list[j].find("sys")+4);
                    if(tempSt=="purUp_sys_purDown_total") tempSt = "purUp_purDown";
                    else if(tempSt=="effUp_sys_effDown_total") tempSt = "effUp_effDown";
                    else if(tempSt=="phoEresol_sigUp_sys_phoEresol_sigDown_total") tempSt = "Eresol_SIG_Up_Down";
                    else if(tempSt=="phoEresol_rmsUp_sys_phoEresol_rmsDown_total") tempSt = "Eresol_RMS_Up_Down";
                    cout << "NOW HIST = " << list.at(j).c_str()<< endl;
                    cout << "tempSt = " << tempSt << endl;
                    l1->AddEntry(h[i][j][1][k],Form("%s",tempSt.data()),"l"); 
                }
                if(hist_types[i]=="dNdpt_corr2_pp" && k==0){
                    string tempSt = "";
                    if(j==0) tempSt = "Tatal";
                    else tempSt = list[j].substr(list[j].find("sys")+4);
                    if(tempSt=="purUp_sys_purDown_total") tempSt = "purUp_purDown";
                    else if(tempSt=="effUp_sys_effDown_total") tempSt = "effUp_effDown";
                    else if(tempSt=="phoEresol_sigUp_sys_phoEresol_sigDown_total") tempSt = "Eresol_SIG_Up_Down";
                    else if(tempSt=="phoEresol_rmsUp_sys_phoEresol_rmsDown_total") tempSt = "Eresol_RMS_Up_Down";
                    if(tempSt=="TAA") tempSt = "lumi";
                    l1_pp->AddEntry(h[i][j][1][k],Form("%s",tempSt.data()),"l"); 
                }
            }
            if(hist_types[i]=="dNdpt_corr2_pp") l1_pp->Draw("same");
            else l1->Draw("same");
            drawText(Form("%s",hist_types.at(i).c_str()),0.2,1.0-(c_tot[i]->GetTopMargin()+0.05));
            if(hist_types[i] != "dNdpt_corr2_pp") drawText(Form("Cent %d-%d %s",(int)centBins_i[k]/2,(int)centBins_f[k]/2,"%"),0.2,1.0-(c_tot[i]->GetTopMargin()+0.12));
        }
        c_tot[i]->SaveAs(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/systematics/figures/systematics_summary_%s_ratio_%s.pdf",hist_types.at(i).c_str(),ver.Data()));
    }

}
