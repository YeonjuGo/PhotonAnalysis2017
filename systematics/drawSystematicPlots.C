// drawSystematicPlots.C 
// draw systematics plots
// Author: Yeonju Go 
// Written at 2017 Dec 13

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
//#include "../ElectroWeak-Jet-Track-Analyses/Systematics/interface/SysVar.h"

void drawSystematicPlots(TString ver="171017_temp_v9")
{
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0000);
    SetyjPadStyle();

    std::vector<std::string> sys_types {
        //"nominal",
        "sys_purUp",
        "sys_purDown",
        "sys_phoEscale",
        "sys_eleCont"
        //"sys_phoIso"                                              
    };
    int n_sys_types = sys_types.size();

    std::vector<std::string> sys_method {
        "diff", "ratio"
    };
    int n_sys_method = sys_method.size();
    
    std::vector<std::string> hist_types {
        "Raa", "dNdpt_corr2"
    };
    int n_hist_types = hist_types.size();
    
    std::vector<std::string> list;
    for(int i=0; i<n_sys_method; ++i){
        list.push_back(Form("%s_sys_purUp_sys_purDown_total",sys_method.at(i).c_str()));
        for(int k=0; k<n_sys_types; ++k){
            list.push_back(Form("%s_abs_%s",sys_method.at(i).c_str(),sys_types.at(k).c_str()));
        }
    }
    const int n_list = list.size();

    TFile* file = new TFile(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/systematics/output/systematics_%s.root",ver.Data()));

    TH1D* h[n_hist_types][n_list][nCentBinIF]; 
    TCanvas* c[n_hist_types][n_list]; 

    for(int i=0; i<n_hist_types; ++i){
        for(int j=0; j<n_list; ++j){
            c[i][j] = new TCanvas(Form("c_%d_%d",i,j),"",300*nCentBinIF,300);
            c[i][j]->Divide(nCentBinIF,1);
            for (int k=0; k<nCentBinIF; ++k) { //k=0 is 0-100%
                c[i][j]->cd(k+1);
                TString hist_name = Form("h1D_%s_cent%d_%s",hist_types.at(i).c_str(),k,list.at(j).c_str());
                h[i][j][k] = (TH1D*) file->Get(Form("%s",hist_name.Data()));
                if(h[i][j][k]->IsZombie()){
                    cout << "There's no <" << hist_name << "> histogram " << endl;
                    continue;
                }
                h[i][j][k]->GetYaxis()->SetTitle("| Sys. Variation - Nominal |");
                h[i][j][k]->GetYaxis()->SetRangeUser(0,0.3);
                h[i][j][k]->Draw();
                drawText(list.at(j).c_str(),0.2,1.0-(c[i][j]->GetTopMargin()+0.05));
                drawText(Form("Cent %d-%d %s",(int)centBins_i[k]/2,(int)centBins_f[k]/2,"%"),0.2,1.0-(c[i][j]->GetTopMargin()+0.12));
            }
            c[i][j]->SaveAs(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/systematics/figures/systematics_%s_%s_%s.pdf",hist_types.at(i).c_str(),list.at(j).c_str(),ver.Data()));
        }
    }

}
