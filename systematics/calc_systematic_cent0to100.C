// calc_systematic.C 
// calculate systematics  
// Author: Yeonju Go 
// Written at 2017 Oct 25

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
#include "../ElectroWeak-Jet-Track-Analyses/Systematics/interface/SysVar.h"

void calc_systematic_cent0to100(TString ver="180619_temp_v17")
{
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0000);
    SetyjPadStyle();

    std::cout << "caculate 0-100 \% bin" << endl;

    std::vector<std::string> sys_types {
        //"nominal",
        "sys_effUp",
        "sys_effDown",
        "sys_purUp",
        "sys_purDown",
        "sys_phoEresol_sigUp",                                              
        "sys_phoEresol_sigDown",                                              
//        "sys_phoEresol_rmsUp",                                              
//        "sys_phoEresol_rmsDown",                                              
        "sys_phoEscale",
        "sys_eleCont",
        //"sys_phoIso",                                            
        //"sys_mc",                                              
        "sys_TAA"                                              
    };
    int n_sys_types = sys_types.size();

    std::vector<std::string> hist_types {
        "Raa", "dNdpt_corr2", "dNdpt_corr2_pp"
    };
    int n_hist_types = hist_types.size();
    
    std::vector<std::string> sys_method {
        "diff", "ratio"
    };
    int n_sys_method = sys_method.size();

    std::vector<std::string> list;
    for(int i=0; i<n_sys_method; ++i){
        for(int k=0; k<n_sys_types; ++k){
            list.push_back(Form("%s_abs_%s",sys_method.at(i).c_str(),sys_types.at(k).c_str()));
        }
        list.push_back(Form("%s_sys_effUp_sys_effDown_total",sys_method.at(i).c_str()));
        list.push_back(Form("%s_sys_purUp_sys_purDown_total",sys_method.at(i).c_str()));
        list.push_back(Form("%s_sys_phoEresol_sigUp_sys_phoEresol_sigDown_total",sys_method.at(i).c_str()));
       // list.push_back(Form("%s_sys_phoEresol_rmsUp_sys_phoEresol_rmsDown_total",sys_method.at(i).c_str()));
        list.push_back(Form("%s_total",sys_method.at(i).c_str()));
    }
    const int n_list = list.size();
    
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/systematics";
    const TString inputFile = Form("%s/output/systematics_%s.root",dir.Data(),ver.Data());
    TFile* input = new TFile(inputFile, "read");
    const TString outputFile = Form("%s/output/systematics_%s_cent0to100.root",dir.Data(),ver.Data());
    TFile* output = new TFile(outputFile, "recreate");

    std::cout << "Getting systematic histograms from : " << inputFile << endl;
    TH1D* h[n_hist_types][n_list][nCentBinIF];
    TH1D* htemp[n_hist_types][n_list][nCentBinIF];
    TH1D* h_noCal[n_hist_types][n_list]; // back up for 0-100% from efficiency and purity, not from each centrality bins
    //Get histograms from the output file 
    for(int i=0; i<n_hist_types; ++i){
        cout << "a" << endl;
        for(int j=0; j<n_list; ++j){
            //if(hist_types[i] == "dNdpt_corr2_pp") continue; 
            for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100%
        cout << "bba" << endl;
                if(hist_types[i] == "dNdpt_corr2_pp" && k>0) continue;
                if(hist_types[i] == "Raa" && (list[j] == "diff_abs_sys_TAA" || list[j] == "ratio_abs_sys_TAA") ){
                   cout << list[j] << endl;  continue;}
                TString hist_name = ""; 
                if(hist_types[i] == "dNdpt_corr2_pp") hist_name = Form("h1D_%s_%s",hist_types.at(i).c_str(),list.at(j).c_str());
                else hist_name = Form("h1D_%s_cent%d_%s",hist_types.at(i).c_str(),k,list.at(j).c_str());
        cout << "hist name = " << hist_name<< endl;
                h[i][j][k] = (TH1D*) input->Get(Form("%s",hist_name.Data()));
        cout << "kkkzzzzzbba" << endl;
                if(h[i][j][k]->IsZombie()){
                    cout << "There's no <" << hist_name << "> histogram " << endl;
                    continue;
                }
            } 
        }
    }

    /////////////////////////////////////////////////////////
    // Calculate 0-100 % bin
    std::cout << "Calculate 0-100 \% bin" << endl;
    TFile* f_raw = new TFile(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/rawDist_%s_nominal.root",ver.Data()));
    TH1D* h1D_raw[nCentBinIF]; 
    double weight[nCentBinIF];
    double entries[nCentBinIF];
    for(int j=0;j<nCentBinIF;j++){
        h1D_raw[j] = (TH1D*) f_raw->Get(Form("h1D_raw_cent%d",j));
        entries[j] = h1D_raw[j]->Integral();
        if(j!=0) weight[j] = entries[j]/entries[0];
        cout << "weight for cent : " << centBins_i[j] << "\% to " << centBins_f[j] << "\% = " <<entries[j]<<"/"<<entries[0]<<" = " <<  weight[j] << endl;
    }
    
    for(int i=0; i<n_hist_types; ++i){
        for(int j=0; j<n_list; ++j){
            if(hist_types[i] == "dNdpt_corr2_pp") continue; 
            for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100%
                TString hist_name = Form("h1D_%s_cent%d_%s",hist_types.at(i).c_str(),k,list.at(j).c_str());
                if(hist_types[i] == "Raa" && (list[j] == "diff_abs_sys_TAA" || list[j] == "ratio_abs_sys_TAA") ){
                   cout << list[j] << endl;  continue;}

                if(k==0){
                    h_noCal[i][j] = (TH1D*) h[i][j][k]->Clone(Form("%s_noCal",h[i][j][k]->GetName()));
                } else{
                    double centWeight = (centBins_f[k]-centBins_i[k])/2./100.;
                    htemp[i][j][k] = (TH1D*) h[i][j][k]->Clone(Form("%s_temp",h[i][j][k]->GetName()));
                    htemp[i][j][k]->Scale(weight[k]);
                    //htemp[i][j][k]->Scale(centWeight);
                    if(k==1) h[i][j][0] = (TH1D*) htemp[i][j][k]->Clone(Form("%s",h[i][j][0]->GetName()));
                    else h[i][j][0]->Add(htemp[i][j][k]);
                }

            }// centrality loop
        }// systematic loop
    }// hist type loop
    std::cout << "DONE calculating" << endl;

    output->cd();
    for(int i=0; i<n_hist_types; ++i){
    std::cout << "a" << endl;
        for(int j=0; j<n_list; ++j){
    std::cout << "b" << endl;
    std::cout << "" << endl;
            if(hist_types[i] != "dNdpt_corr2_pp" && (hist_types[i] != "Raa" && (list[j] == "diff_abs_sys_TAA" || list[j] == "ratio_abs_sys_TAA"))) h_noCal[i][j]->Write();
    std::cout << "c" << endl;
            for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100%
                if(hist_types[i] == "dNdpt_corr2_pp" && k>0) continue;
                if(hist_types[i] == "Raa" && (list[j] == "diff_abs_sys_TAA" || list[j] == "ratio_abs_sys_TAA") ){
                cout << list[j] << endl;  continue;}
                TString hist_name = ""; 
                if(hist_types[i] == "dNdpt_corr2_pp") hist_name = Form("h1D_%s_%s",hist_types.at(i).c_str(),list.at(j).c_str());
                else hist_name = Form("h1D_%s_cent%d_%s",hist_types.at(i).c_str(),k,list.at(j).c_str());
                cout << hist_name << endl;
    std::cout << "d" << endl;
                h[i][j][k]->Write();
    std::cout << "e" << endl;
            }
        }
    }

}
