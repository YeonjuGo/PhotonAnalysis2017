// calc_systematic.C 
// calculate systematics  
// Author: Yeonju Go 
// Written at 2017 Oct 25

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
#include "../ElectroWeak-Jet-Track-Analyses/Systematics/interface/SysVar.h"

void calc_systematic(TString ver="180610_temp_v15")
{
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0000);
    SetyjPadStyle();

#define _EFF_UP   1
#define _EFF_DOWN 2
#define _PURITY_UP   3
#define _PURITY_DOWN 4
#define _RESOL_SIG_UP  5
#define _RESOL_SIG_DOWN  6
//#define _RESOL_RMS_UP  7
//#define _RESOL_RMS_DOWN  8

    std::vector<std::string> sys_types {
        "nominal",
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

    std::vector<std::string> input_list;

    for(int i=0; i<n_sys_types; ++i){
        input_list.push_back(Form("/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/phoRaa_%s_%s.root",ver.Data(),sys_types.at(i).c_str()));
        cout << "input file : " << input_list.at(i) << endl;
    }
    const int n_input_files = input_list.size();

    if (n_input_files != n_sys_types) {
        printf("%i input files for %i systematic variations\n", n_input_files, n_sys_types);
        //printf("please add dummy files to input file list: %s\n", inputList.Data());
        //return 1;
    } 

    TFile* input_files[n_input_files];
    std::vector<bool> valid_input(n_input_files, false);
    for (int i=0; i<n_input_files; ++i) {
        input_files[i] = new TFile(input_list.at(i).c_str(), "read");
        valid_input[i] = (input_files[i] && input_files[i]->IsOpen());
    }

    if (!valid_input[0]) {
        printf("file with nominal histograms broken!\n");
    }

    std::vector<std::string> hist_types {
        "Raa", "dNdpt_corr2", "dNdpt_corr2_pp"
    };
    int n_hist_types = hist_types.size();
    
    // std::vector<std::string> data_types {"PbPb_Data", "PbPb_MC", "pp_Data", "pp_MC"};
    // int n_data_types = data_types.size();

    //////////////////////////////////////////////////
    // Calculate Systematics and write it in output file
    //////////////////////////////////////////////////
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/systematics";
    const TString outputFile = Form("%s/output/systematics_%s.root",dir.Data(),ver.Data());
    TFile* output = new TFile(outputFile, "recreate");


    typedef std::vector<SysVar*>    vvector;
    typedef std::vector<vvector>    vvvector;
    typedef std::vector<vvvector>   vvvvector;
    //typedef std::vector<vvvvector>  vvvvvector;
    //typedef std::vector<vvvvvector> vvvvvvector;

    vvvvector systematics(n_hist_types, vvvector(nCentBinIF, vvector()));

    for (int i=0; i<n_hist_types; ++i) {
        for (int k=0; k<nCentBinIF; ++k) { //k=0 is allCentBin
            std::string hist_name;
            if (hist_types[i] == "Raa" || hist_types[i] == "dNdpt_corr2")
                hist_name = Form("%s_cent%d", hist_types[i].c_str(), k);
            else if(hist_types[i] == "dNdpt_corr2_pp") hist_name =  Form("%s", hist_types[i].c_str()); 
            else 
                printf("invalid histogram type: %s\n", hist_types[i].c_str());

            if((hist_types[i] == "dNdpt_corr2_pp") && k>0) continue;

            // for (int l=0; l<n_data_types; ++l) {
            //     if (hist_types[i] == "Raa")
            //         if (l) break;

            printf("nominal: %s\n", hist_name.c_str());
            TH1D* h1D_nominal = (TH1D*)input_files[0]->Get(Form("h1D_%s", hist_name.c_str()));

            printf("calculating systematics...\n");

            for (int m=1; m<n_sys_types; ++m) {
                if (!valid_input[m])
                    continue;
                
                if(hist_types[i] == "dNdpt_corr2_pp" && sys_types[m]=="sys_TAA") continue; 
                if(hist_types[i] == "Raa" && sys_types[m]=="sys_TAA") continue; 
                TH1D* h1D_varied = (TH1D*)input_files[m]->Get(Form("h1D_%s", hist_name.c_str()));

                SysVar* sys_hists = new SysVar(hist_name, sys_types[m]);
                sys_hists->init(h1D_nominal, h1D_varied);

                sys_hists->calc_sys();

               // if (sys_types[m] == "sys_eleCont")
               //     sys_hists->scale_sys(0.25);
                
                systematics[i][k].push_back(sys_hists);
            }
        }
    }

    //pp lumi systematic 2.3%
    std::string hist_name = "dNdpt_corr2_pp"; 
    SysVar* sys_pplumi= new SysVar(hist_name,"sys_TAA");
    TH1D* h1D_nominal = (TH1D*)input_files[0]->Get(Form("h1D_dNdpt_corr2_pp%s",""));
    TH1D* h1D_varied = (TH1D*) h1D_nominal->Clone(Form("h1D_dNdpt_corr2_pp%s","_varied"));
    //TH1D* h1D_varied = (TH1D*)input_files[0]->Get(Form("h1D_dNdpt_corr2_pp%s",""));
    h1D_varied->Scale(1./1.023);
    sys_pplumi->init(h1D_nominal, h1D_varied);
    sys_pplumi->calc_sys();
    systematics[2][0].push_back(sys_pplumi);

    std::vector<TotalSysVar*> total_sys;

    printf("calculating total systematics...\n");
    for (std::size_t i=0; i<systematics.size(); ++i) {
        printf("for %s\n", hist_types[i].c_str());
        for (std::size_t k=0; k<systematics[i].size(); ++k) {
            if (!systematics[i][k].size())
                continue;

            std::size_t m = 0;
            TotalSysVar* total_sys_hists = new TotalSysVar();
            //eff total
            if (valid_input[_EFF_UP] && valid_input[_EFF_DOWN]) {
                TotalSysVar* eff_sys_hists = new TotalSysVar(systematics[i][k][m], systematics[i][k][m+1]);
                total_sys_hists->add_SysVar(eff_sys_hists);
                ++m; ++m;
            } else if (valid_input[_EFF_UP] ^ valid_input[_EFF_DOWN]) {
                total_sys_hists->add_SysVar(systematics[i][k][m]);
                ++m;
            }
            //purity total
            if (valid_input[_PURITY_UP] && valid_input[_PURITY_DOWN]) {
                TotalSysVar* purity_sys_hists = new TotalSysVar(systematics[i][k][m], systematics[i][k][m+1]);
                total_sys_hists->add_SysVar(purity_sys_hists);
                ++m; ++m;
            } else if (valid_input[_PURITY_UP] ^ valid_input[_PURITY_DOWN]) {
                total_sys_hists->add_SysVar(systematics[i][k][m]);
                ++m;
            }
            //resolution sig total(when there's two source)
            if (valid_input[_RESOL_SIG_UP] && valid_input[_RESOL_SIG_DOWN]) {
                TotalSysVar* resol_sig_sys_hists = new TotalSysVar(systematics[i][k][m], systematics[i][k][m+1]);
                total_sys_hists->add_SysVar(resol_sig_sys_hists);
                ++m; ++m;
            } else if (valid_input[_RESOL_SIG_UP] ^ valid_input[_RESOL_SIG_DOWN]) {
                total_sys_hists->add_SysVar(systematics[i][k][m]);
                ++m;
            }
            //resolution rms total(when there's two source)
           // if (valid_input[_RESOL_RMS_UP] && valid_input[_RESOL_RMS_DOWN]) {
           //     TotalSysVar* resol_rms_sys_hists = new TotalSysVar(systematics[i][k][m], systematics[i][k][m+1]);
           //     total_sys_hists->add_SysVar(resol_rms_sys_hists);
           //     ++m; ++m;
           // } else if (valid_input[_RESOL_RMS_UP] ^ valid_input[_RESOL_RMS_DOWN]) {
           //     total_sys_hists->add_SysVar(systematics[i][k][m]);
           //     ++m;
           // }

            for (; m<systematics[i][k].size(); ++m)
                total_sys_hists->add_SysVar(systematics[i][k][m]);

            if (total_sys_hists->non_zero()) {
                total_sys.push_back(total_sys_hists);
                //total_sys_hists->print_latex(sys_types);
            }
        }
    }

    printf("writing objects...\n");
    output->Write("", TObject::kOverwrite);
    output->Close();
}
