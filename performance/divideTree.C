#include <iostream>
#include <TFile.h>
#include <TChain.h>
static const long MAXTREESIZE = 10000000000;

void divideTree(TString coll="pp")
{
    using namespace std;

    TString skimVer = "2019-07-02-meanEcorr";
    //TString skimVer = "2019-06-30-nominal";
    //TString skimVer = "2019-02-25-nominal";
    TString fname = Form("/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/%s/PbPb_MC_photonRaaSkim_Cymbal_190702_meanEcorr.root",skimVer.Data());
    TString fname_out = Form("/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/%s/PbPb_MC_photonRaaSkim_Cymbal_190702_meanEcorr_splitMC_even_odd.root",skimVer.Data());
    if(coll=="pp"){
        fname = Form("/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/%s/pp_MC_photonRaaSkim_190702_meanEcorr.root",skimVer.Data());
        fname_out = Form("/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/%s/pp_MC_photonRaaSkim_190702_meanEcorr_splitMC_even_odd.root",skimVer.Data());
    }
    //TString fname = Form("/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/%s/PbPb_MC_photonRaaSkim_Cymbal.root",skimVer.Data());
    //TString fname_out = Form("/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/%s/PbPb_MC_photonRaaSkim_Cymbal_splitMC_even_odd.root",skimVer.Data());
    //if(coll=="pp"){
    //    fname = Form("/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/%s/pp_MC_photonRaaSkim.root",skimVer.Data());
    //    fname_out = Form("/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/%s/pp_MC_photonRaaSkim_splitMC_even_odd.root",skimVer.Data());
    //}
    //TString fname_even = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2019-02-25-nominal/PbPb_MC_photonRaaSkim_Cymbal_even.root";
    //TString fname_odd = "/home/goyeonju/CMS/Files/photon2016/GAMMAJETFILES/2019-02-25-nominal/PbPb_MC_photonRaaSkim_Cymbal_odd.root";

    TChain *mytree_hlt = new TChain("hltTree");
    mytree_hlt->Add(fname.Data());
    TChain *mytree_pho = new TChain("EventTree");
    mytree_pho->Add(fname.Data());
    TChain *mytree_evt = new TChain("HiEvt");
    mytree_evt->Add(fname.Data());
    TChain *mytree_skim = new TChain("skim");
    mytree_skim->Add(fname.Data());

    TFile* output = new TFile(Form("%s",fname_out.Data()),"recreate");

    TTree* hlt_even = (TTree*)mytree_hlt->CloneTree(0);
    TTree* hlt_odd = (TTree*)mytree_hlt->CloneTree(0);
    hlt_even->SetName(Form("%s_even",mytree_hlt->GetName()));
    hlt_odd->SetName(Form("%s_odd",mytree_hlt->GetName()));
    TTree* pho_even = (TTree*)mytree_pho->CloneTree(0);
    TTree* pho_odd = (TTree*)mytree_pho->CloneTree(0);
    pho_even->SetName(Form("%s_even",mytree_pho->GetName()));
    pho_odd->SetName(Form("%s_odd",mytree_pho->GetName()));
    TTree* evt_even = (TTree*)mytree_evt->CloneTree(0);
    TTree* evt_odd = (TTree*)mytree_evt->CloneTree(0);
    evt_even->SetName(Form("%s_even",mytree_evt->GetName()));
    evt_odd->SetName(Form("%s_odd",mytree_evt->GetName()));
    TTree* skim_even = (TTree*)mytree_skim->CloneTree(0);
    TTree* skim_odd = (TTree*)mytree_skim->CloneTree(0);
    skim_even->SetName(Form("%s_even",mytree_skim->GetName()));
    skim_odd->SetName(Form("%s_odd",mytree_skim->GetName()));

    int nevt = mytree_pho->GetEntries();

    for(int iev=0; iev<nevt ; ++iev){
        if(iev%5000==0) cout << ">>>>> EVENT " << iev << " / " << nevt <<  " ("<<(int)(100.*iev/nevt) << "%)" << endl;
        mytree_hlt->GetEntry(iev);
        mytree_pho->GetEntry(iev);
        mytree_evt->GetEntry(iev);
        mytree_skim->GetEntry(iev);
        if(iev%2==0){
            hlt_even->Fill();
            pho_even->Fill();
            evt_even->Fill();
            skim_even->Fill();
        } else{
            hlt_odd->Fill();
            pho_odd->Fill();
            evt_odd->Fill();
            skim_odd->Fill();
        }
    }
    cout << "Loop ENDED" << endl;
    cout << "totalentries            = " << nevt << endl;
    cout << "outputTreeHLT_even->GetEntries()   = " << hlt_even->GetEntries() << std::endl;
    cout << "outputTreePho_even->GetEntries()   = " << pho_even->GetEntries() << std::endl;
    cout << "outputTreeSkim_even->GetEntries()  = " << skim_even->GetEntries() << std::endl;
    cout << "outputTreeHiEvt_even->GetEntries() = " << evt_even->GetEntries() << std::endl;
    cout << "outputTreeHLT_odd->GetEntries()   = " << hlt_odd->GetEntries() << std::endl;
    cout << "outputTreePho_odd->GetEntries()   = " << pho_odd->GetEntries() << std::endl;
    cout << "outputTreeSkim_odd->GetEntries()  = " << skim_odd->GetEntries() << std::endl;
    cout << "outputTreeHiEvt_odd->GetEntries() = " << evt_odd->GetEntries() << std::endl;
    hlt_even->Write();
    pho_even->Write();
    evt_even->Write();
    skim_even->Write();
    hlt_odd->Write();
    pho_odd->Write();
    evt_odd->Write();
    skim_odd->Write();
    output->Close();


}
