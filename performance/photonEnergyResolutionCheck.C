#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TVirtualFitter.h"

#include "TString.h"

#include <vector>

//#include "../Utilities/interface/InputConfigurationParser.h"
#include "../ElectroWeak-Jet-Track-Analyses/Utilities/mathUtil.h"
#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"

#define _SET_BRANCH_VEC(tree, type, branch)     \
    std::vector<type>* branch = 0;              \
tree->SetBranchStatus(#branch, 1);          \
tree->SetBranchAddress(#branch, &branch);   \

#define _SET_BRANCH_VAR(tree, type, branch)     \
    type branch;                                \
tree->SetBranchStatus(#branch, 1);          \
tree->SetBranchAddress(#branch, &branch);   \

float dR(float eta1, float eta2, float phi1, float phi2);
double myFunc(double *x, double *par){
    return par[0]+ par[1]/sqrt(x[0]) + par[2]/x[0];
}
TH1F* getPullHist(TH1F *h1, TF1 *f);
void photonEnergyResolutionCheck(bool isPP = false, TString ver="180807_temp_v22", TString fnc_name="DSCB", bool doIsoCut=false){
    gStyle->SetOptFit(0);
    gStyle->SetOptStat(0);

    ////////////////////////////////////////////
    //import skimed tree
    const char* fname;
    if(isPP){
        fname=Form("%s",ppMCfname.Data());
    } else{
        fname=Form("%s",pbpbMCfname.Data());
    }
    TChain* t1 = new TChain("EventTree");
    TChain* t1_evt = new TChain("HiEvt");
    // TChain* t1_skim = new TChain("skim");
    // TChain* t1_hlt = new TChain("hltTree");
    t1->Add(fname);
    t1_evt->Add(fname);
    // t1_skim->Add(fname);
    // t1_hlt->Add(fname);
    t1->AddFriend(t1_evt);
    // t1->AddFriend(t1_skim);
    // t1->AddFriend(t1_hlt);

    // caption
    TString collSt = "pbpb";
    if(isPP) collSt = "pp";
    TString GEDcap = "";
    if(isPP) GEDcap = "GED";
    TString cap = Form("%s_%s_%s",collSt.Data(),ver.Data(),fnc_name.Data());
    if(isPP) cap = Form("%s_%s_GED_%s",collSt.Data(),ver.Data(),fnc_name.Data());
    if (doIsoCut) cap += "_isoCut";
    TString outfname = Form("output/photonEnergyResolution_%s.root",cap.Data());

    t1->SetBranchStatus("*", 0);
    t1_evt->SetBranchStatus("*", 0);

    _SET_BRANCH_VEC(t1, float, mcEt);
    _SET_BRANCH_VEC(t1, float, mcEta);
    _SET_BRANCH_VEC(t1, float, mcPhi);
    _SET_BRANCH_VEC(t1, float, mcCalIsoDR04);
    _SET_BRANCH_VEC(t1, float, phoEt);
    _SET_BRANCH_VEC(t1, float, phoEtCorrected);
    _SET_BRANCH_VEC(t1, float, phoEta);
    _SET_BRANCH_VEC(t1, float, phoPhi);
    _SET_BRANCH_VEC(t1, float, phoHoverE);
    _SET_BRANCH_VEC(t1, float, pho_ecalClusterIsoR4);
    _SET_BRANCH_VEC(t1, float, pho_hcalRechitIsoR4);
    _SET_BRANCH_VEC(t1, float, pho_trackIsoR4PtCut20);
    _SET_BRANCH_VEC(t1, float, phoSigmaIEtaIEta_2012);
    _SET_BRANCH_VEC(t1, float, pho_swissCrx);
    _SET_BRANCH_VEC(t1, float, pho_seedTime);
    _SET_BRANCH_VEC(t1, int, pho_genMatchedIndex);
    _SET_BRANCH_VAR(t1, int, hiBin);

    // _SET_BRANCH_VEC(t_photon, float, elePt);
    // _SET_BRANCH_VEC(t_photon, float, eleEta);
    // _SET_BRANCH_VEC(t_photon, float, elePhi);
    // _SET_BRANCH_VEC(t_photon, float, eleEoverP);
    // _SET_BRANCH_VEC(t_photon, float, eleSigmaIEtaIEta_2012);
    // _SET_BRANCH_VEC(t_photon, float, eledEtaAtVtx);
    // _SET_BRANCH_VEC(t_photon, float, eledPhiAtVtx);
    // _SET_BRANCH_VEC(t_photon, float, eleHoverE);
    // _SET_BRANCH_VEC(t_photon, float, eleEoverPInv);
    // _SET_BRANCH_VEC(t_photon, float, eleD0);
    // _SET_BRANCH_VEC(t_photon, float, eleDz);
    // _SET_BRANCH_VEC(t_photon, float, eleMissHits);


    // kinematic ranges
    //int centBins_[2][7] = {{0,10,20,40,60,100,140},{10,20,40,60,100,140,200}};
    //int nCentBins = 7;
    int centBins_[2][5] = {{0,20,60,100,140},{20,60,100,140,200}};
    int nCentBins = 5;
    if(isPP){ nCentBins = 1;}
    //int centBins[2][5] = {{0,20,60,100,140},{20,60,100,140,200}};
    //int nCentBins = 5;
    float etaBins[2][1] = {{0},{1.44}};
    int nEtaBins = 1; 

    gStyle->SetOptStat(0);

    cout << "sss"<< endl;
    //double ptBins_normal[] = {30,35,40,50,60,70,80,90,100,110,120,140};
    double ptBins_normal[] = {15,16,17,18,19,20,21,22,24,26,28,30,35,40,50,60,70,80,90,100,110,120,140};
    //double ptBins_normal[] = {20,22,24,26,28,30,35,40,50,60,70,80,90,100,110,120,140};
    const int nPtBins_normal = sizeof(ptBins_normal)/sizeof(double) -1;
    double ptBins_isoCut[] = {20,25,30,35,40,50,60,70,80,90,100,110,120,140};
    const int nPtBins_isoCut = sizeof(ptBins_isoCut)/sizeof(double) -1;
    int nPtBins = nPtBins_normal;
    if(doIsoCut) nPtBins = nPtBins_isoCut;
    double ptBins[nPtBins];
    double ptBins_fit[nPtBins-2];
    for(int i=0; i<nPtBins+1; ++i){
        if(doIsoCut) ptBins[i] = ptBins_isoCut[i];
        else ptBins[i] = ptBins_normal[i];
        cout << "ipt = " << i << " : ptBin = " << ptBins[i] << endl;
        if(i>=2){
            if(doIsoCut) ptBins_fit[i-2] = ptBins_isoCut[i];
            else ptBins_fit[i-2] = ptBins_normal[i];
        }
    } 
    int nPtBins_fit = nPtBins-2;
    if(doIsoCut) nPtBins_fit = nPtBins-2;
    for(int i=0; i<nPtBins_fit+1; ++i)
        cout << "ipt = " << i << " : ptBin_fit = " << ptBins_fit[i] << endl;

    //double ptBins[] = {10,20,30,40,50,60,70,80,90,100,120,150,200};
    //double ptBins[] = {10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
    //const int nPtBins = sizeof(ptBins)/sizeof(double) -1;
    const int nPtBins_2d = 50; 
    int nbins = 100; //for ratio
    if(collSt=="pp") nbins = 500;
    else nbins = 100; 
    TH2F* h_pt[nCentBins][nEtaBins];
    TH2F* h_ptratio[nCentBins][nEtaBins];
    TProfile* h_ptprof[nCentBins][nEtaBins];

    TH1F* h_ratio[nCentBins][nEtaBins][nPtBins];
    TH1F* h_ratio_pull[nCentBins][nEtaBins][nPtBins];    
    TH1F* h_mean_fit[nCentBins][nEtaBins];
    TH1F* h_sig_fit[nCentBins][nEtaBins];
    TH1F* h_sig_fit_band[nCentBins][nEtaBins];
    TH1F* h_mean[nCentBins][nEtaBins];
    TH1F* h_rms[nCentBins][nEtaBins];

    for (int i=0; i<nCentBins; ++i) {
        for (int j=0; j<nEtaBins; ++j) {
            TString centSt = Form("%i-%i%%", centBins_[0][i]/2, centBins_[1][i]/2); 
            if(isPP) centSt = "pp";
            h_pt[i][j] = new TH2F(Form("h_pt_%i_%i", i, j), Form("%s, %.2f<|#eta|<%.2f;reco p_{T}^{#gamma};gen p_{T}^{#gamma}", centSt.Data(), etaBins[0][j], etaBins[1][j]), nPtBins_2d, 0, 200, nPtBins_2d, 0, 200);
            h_ptratio[i][j] = new TH2F(Form("h_ptratio_%i_%i", i, j), Form("%s, %.2f<|#eta|<%.2f;reco p_{T}^{#gamma};#frac{reco p_{T}^{#gamma}}{gen p_{T}^{#gamma}}", centSt.Data(), etaBins[0][j], etaBins[1][j]), nPtBins_2d, 0, 200, 50, 0, 2);

            h_mean_fit[i][j] = new TH1F(Form("h_mean_fit_%i_%i", i, j), Form("%s, %.2f<|#eta|<%.2f;gen p_{T}^{#gamma};<#frac{reco p_{T}^{#gamma}}{gen p_{T}^{#gamma}}>", centSt.Data(), etaBins[0][j], etaBins[1][j]), nPtBins_fit, ptBins_fit);
            h_sig_fit[i][j] = new TH1F(Form("h_sigma_fit_%i_%i", i, j), Form("%s, %.2f<|#eta|<%.2f;gen p_{T}^{#gamma};#sigma(#frac{reco p_{T}^{#gamma}}{gen p_{T}^{#gamma}})", centSt.Data(), etaBins[0][j], etaBins[1][j]), nPtBins_fit, ptBins_fit);
            h_sig_fit_band[i][j] = (TH1F*)  h_sig_fit[i][j]->Clone(Form("h_sig_fit_band_%i_%i", i, j));

            h_mean[i][j] = (TH1F*)  h_mean_fit[i][j]->Clone(Form("h_mean_%i_%i", i, j));
            h_rms[i][j] = (TH1F*)  h_sig_fit[i][j]->Clone(Form("h_rms_%i_%i", i, j));
            for (int k=0; k<nPtBins; ++k) {
                if(i<6)
                h_ratio[i][j][k] = new TH1F(Form("h_ratio_cent%i_eta%i_pt%i", i, j, k), ";#frac{reco p_{T}^{#gamma}}{gen p_{T}^{#gamma}};", nbins,0.0,2.0);
                else 
                h_ratio[i][j][k] = new TH1F(Form("h_ratio_cent%i_eta%i_pt%i", i, j, k), ";#frac{reco p_{T}^{#gamma}}{gen p_{T}^{#gamma}};", nbins,0.0,2.0);
            }
        }
    }

    uint64_t nentries = t1->GetEntries();
    for (uint64_t i=0; i<nentries; ++i) {
        if (i % 100000 == 0)
            printf("entry: %lu / %lu \n", i,nentries);

        t1->GetEntry(i);
        t1_evt->GetEntry(i);

        for (uint32_t j=0; j<phoEt->size(); ++j) {
            if (phoEt->at(j) < 10)
                continue;
            if (fabs(phoEta->at(j)) > 1.44)
                continue;
            if (pho_genMatchedIndex->at(j) < 0)
                continue;
            if (pho_swissCrx->at(j) > 0.9)
                continue;
            if (fabs(pho_seedTime->at(j)) > 3)
                continue;
            if (doIsoCut && phoHoverE->at(j)>0.1) 
                continue;
            if (doIsoCut && phoSigmaIEtaIEta_2012->at(j)>0.011) 
                continue;
            if (doIsoCut && (pho_ecalClusterIsoR4->at(j)+pho_hcalRechitIsoR4->at(j)+pho_trackIsoR4PtCut20->at(j))>1) 
                continue;

            // if(!isPhotonSample){ //Electron matching is only for ZtoEE sample
            //     int matchedEleIndex = -1;
            //     float matchedEoverP = 100;
            //     for (uint32_t k=0; k<elePt->size(); ++k) {
            //         if (elePt->at(k) < 10)
            //             continue;
            //         if (eleSigmaIEtaIEta_2012->at(k) > 0.01107)
            //             continue;
            //         if (eleEoverPInv->at(k) > 0.28051)
            //             continue;
            //         if (fabs(eledEtaAtVtx->at(k)) > 0.01576)
            //             continue;
            //         if (fabs(eledPhiAtVtx->at(k)) > 0.15724)
            //             continue;
            //         if (eleHoverE->at(k) > 0.08849)
            //             continue;
            //         if (fabs(eleD0->at(k)) > 0.05216)
            //             continue;
            //         if (fabs(eleDz->at(k)) > 0.12997)
            //             continue;
            //         if (eleMissHits->at(k) > 1)
            //             continue;
            //         if (dR(phoEta->at(j), eleEta->at(k), phoPhi->at(j), elePhi->at(k)) > 0.04242)
            //             continue;
            //         if (eleEoverP->at(k) > matchedEoverP)
            //             continue;
            //         matchedEleIndex = k;
            //     }
            //     if (matchedEleIndex == -1)
            //         continue;
            // }

            int icent = 0;
            if(!isPP){
                for (; hiBin>=centBins_[1][icent] && icent<nCentBins; ++icent);
            }
            //cout << "hiBin = " << hiBin << ", icent = " << icent << endl;
            int32_t mcindex = pho_genMatchedIndex->at(j);

            if (mcEt->at(mcindex) < 10)
                continue;
            if (mcCalIsoDR04->at(mcindex) > 5)
                continue;


            int ieta = 0;
            //for (; fabs(phoEta->at(j))>=etaBins[1][ieta] && ieta<nEtaBins; ++ieta);

            // according to the reco pt
            // int ipt = 0;
            // for (; fabs(phoEt->at(j))>=ptBins[ipt+1] && ipt<nPtBins; ++ipt){
            //     if(ipt>nPtBins) break;    
            // }

            // according to the gen pt
            int ipt = 0;
            for (; fabs(mcEt->at(mcindex))>=ptBins[ipt+1] && ipt<nPtBins; ++ipt){
                if(ipt>nPtBins) break;
            }

            h_pt[icent][ieta]->Fill(phoEtCorrected->at(j), mcEt->at(mcindex));
            h_ptratio[icent][ieta]->Fill(mcEt->at(mcindex), phoEtCorrected->at(j)/mcEt->at(mcindex));
            //h_ptratio[icent][ieta]->Fill(phoEtCorrected->at(j), phoEtCorrected->at(j)/mcEt->at(mcindex));
            if(ipt<nPtBins) h_ratio[icent][ieta][ipt]->Fill(phoEtCorrected->at(j)/mcEt->at(mcindex));
        }
    }


    ///////////////////////////////////////
    // Gaus or DSCB fitting for reco/gen pt ratio  
    TCanvas* c[nCentBins][nEtaBins];
    TCanvas* ctemp = new TCanvas("ctemp","",300,300);
    TF1* ff[nCentBins][nEtaBins][nPtBins];
    for (int i=0; i<nCentBins; ++i) {
        for (int j=0; j<nEtaBins; ++j) {
            c[i][j] = new TCanvas(Form("can_cent%d_eta%d",i,j),"",250*4,250*3);
            c[i][j]->Divide(5,4);
            for (int k=0; k<nPtBins; ++k) {
                ctemp->cd();
                h_ratio[i][j][k]->Scale(1./h_ratio[i][j][k]->Integral());
                h_ratio[i][j][k]->SetMarkerStyle(20);
                h_ratio[i][j][k]->SetMarkerSize(0.6);
                // gaussian or Double-sided crystal ball fitting 
                if(fnc_name=="gaus"){ 
                    ff[i][j][k] = cleverGaus(h_ratio[i][j][k], Form("f_%s",h_ratio[i][j][k]->GetName()));
                } else if(fnc_name=="DSCB"){
                    Int_t peakBin  = h_ratio[i][j][k]->GetMaximumBin();
                    Double_t peakContent  = h_ratio[i][j][k]->GetBinContent(peakBin);
                    Double_t peak =  h_ratio[i][j][k]->GetBinCenter(peakBin);
                    Double_t sigma = h_ratio[i][j][k]->GetRMS(); 
                    if(collSt =="pbpb"){
                        if((i==0 || i==1) && k<12)
                        ff[i][j][k] = new TF1(Form("f1_%d_%d_%d",i,j,k), fnc_DSCB, peak-4.5*sigma, peak+4.5*sigma, 7);
                        else if((i==0 || i==1) && k>=12)
                        ff[i][j][k] = new TF1(Form("f1_%d_%d_%d",i,j,k), fnc_DSCB, peak-3.5*sigma, peak+3.5*sigma, 7);
                        else 
                        ff[i][j][k] = new TF1(Form("f1_%d_%d_%d",i,j,k), fnc_DSCB, peak-2.5*sigma, peak+2.5*sigma, 7);
                        if(nCentBins==7){
                            if(i==0 && j==0 && (k==3 || k==6)){
                                ff[i][j][k]->SetParameters(peakContent,1.00995e+00,8.96961e-02,1.86464e+00,1.33083e+02,6.96234e-01,3.44766e+01);
                            } else if(i==1 && j==0 && (k==3 || k==4)){
                                ff[i][j][k]->SetParameters(peakContent,9.52954e-01,4.27061e-02,9.00252e-01,1.37031e+02,3.33283e-01,1.10311e+02);
                            } else if(i==2 && j==0 && (k==2 || k==3 || k==4 || k==5)){
                                ff[i][j][k]->SetParameters(peakContent,9.80694e-01,3.92717e-02,1.32194e+00,1.75705e+00,5.40295e-01,1.19989e+02);
                            } else if(i==3 && j==0 && (k==6 || k==7)){
                                ff[i][j][k]->SetParameters(peakContent,9.94747e-01,2.99991e-02,1.21006e+00,1.39507e+00,5.05288e-01,1.14040e+02);
                            } else if(i==4 && j==0 && (k==3 || k==6 || k==7)){
                                ff[i][j][k]->SetParameters(peakContent,9.92694e-01,2.83387e-02,1.04563e+00,1.78215e+00,9.12513e-01,5.30552e+00);
                            } else if(i==5 && j==0 && (k==2 || k==5 || k==6 || k==7 || k==8 || k==9)){
                                ff[i][j][k]->SetParameters(peakContent,1.02296e+00,2.00926e-02,7.01717e-01,2.51708e+00,1.35686e+00,3.86881e+00);
                            } else if(i==6 && j==0){
                                ff[i][j][k]->SetParameters(peakContent,1.02296e+00,2.00926e-02,7.01717e-01,2.51708e+00,1.35686e+00,3.86881e+00);
                            } else {
                                ff[i][j][k]->SetParameters(peakContent,peak,sigma,0.79,3.63,0.59,1.67);
                            }

                            if(i==0) 
                                ff[i][j][k]->SetParLimits(2,0.015,0.09);
                            else if(i==1) 
                                ff[i][j][k]->SetParLimits(2,0.015,0.06);
                            else if(i==2) 
                                ff[i][j][k]->SetParLimits(2,0.015,0.04);
                            else if(i==3 || i==4)  
                                ff[i][j][k]->SetParLimits(2,0.01,0.03);
                            else  
                                ff[i][j][k]->SetParLimits(2,0.005,0.025);

                            if(i==0){
                                ff[i][j][k]->SetParLimits(3,1.8,2.0);
                                ff[i][j][k]->SetParLimits(4,1.3,5.0);
                            } else if(i==1){
                                ff[i][j][k]->SetParLimits(3,1.8,2.0);
                                ff[i][j][k]->SetParLimits(4,1.3,2.0);
                            } else if(i==2){
                                ff[i][j][k]->SetParLimits(3,1.10,2.0);
                                ff[i][j][k]->SetParLimits(4,1.30,2.0);
                            } else{
                                ff[i][j][k]->SetParLimits(3,1.10,2.0);
                                ff[i][j][k]->SetParLimits(4,1.30,2.0);
                            }
                        } else if(nCentBins==5){
                            if(i==0 && j==0 && (k==3 || k==6)){
                                ff[i][j][k]->SetParameters(peakContent,1.00995e+00,8.96961e-02,1.86464e+00,1.33083e+02,6.96234e-01,3.44766e+01);
                            //} else if(i==1 && j==0 && (k==3 || k==4)){
                            //    ff[i][j][k]->SetParameters(peakContent,9.52954e-01,4.27061e-02,9.00252e-01,1.37031e+02,3.33283e-01,1.10311e+02);
                            //} else if(i==1 && j==0 && (k==2 || k==3 || k==4 || k==5)){
                            //    ff[i][j][k]->SetParameters(peakContent,9.80694e-01,3.92717e-02,1.32194e+00,1.75705e+00,5.40295e-01,1.19989e+02);
                            } else if(i==1 && j==0 && (k==6 || k==7)){
                                ff[i][j][k]->SetParameters(peakContent,9.89671e-01,3.55789e-02,1.10045e+00,2.48962e+00,5.75673e-01,1.14708e+02);
                                //ff[i][j][k]->SetParameters(peakContent,9.94747e-01,2.99991e-02,1.21006e+00,1.39507e+00,5.05288e-01,1.14040e+02);
                            } else if(i==2 && j==0 && (k==3 || k==6 || k==7)){
                                ff[i][j][k]->SetParameters(peakContent,9.92694e-01,2.83387e-02,1.04563e+00,1.78215e+00,9.12513e-01,5.30552e+00);
                            } else if(i==3 && j==0 && (k==2 || k==5 || k==6 || k==7 || k==8 || k==9)){
                                ff[i][j][k]->SetParameters(peakContent,1.02296e+00,2.00926e-02,7.01717e-01,2.51708e+00,1.35686e+00,3.86881e+00);
                            } else if(i==4 && j==0){
                                ff[i][j][k]->SetParameters(peakContent,1.02296e+00,2.00926e-02,7.01717e-01,2.51708e+00,1.35686e+00,3.86881e+00);
                            } else {
                                ff[i][j][k]->SetParameters(peakContent,peak,sigma,0.79,3.63,0.59,1.67);
                            }

                            if(i==0) 
                                ff[i][j][k]->SetParLimits(2,0.015,0.09);
                            else if(i==1) 
                                ff[i][j][k]->SetParLimits(2,0.015,0.04);
                            else  
                                ff[i][j][k]->SetParLimits(2,0.005,0.025);

                            if(i==0){
                                ff[i][j][k]->SetParLimits(3,1.1,2.1);
                                ff[i][j][k]->SetParLimits(4,1.3,5.0);
                            } else if(i==1){
                                ff[i][j][k]->SetParLimits(3,1.1,2.1);
                                ff[i][j][k]->SetParLimits(4,1.5,3.0);
                            } else{
                                ff[i][j][k]->SetParLimits(3,1.1,2.1);
                                ff[i][j][k]->SetParLimits(4,1.3,2.1);
                            }

                        }
                    } else{ // pp
                        ff[i][j][k] = new TF1(Form("f1_%d_%d_%d",i,j,k), fnc_DSCB, peak-2.5*sigma, peak+2.5*sigma, 7);
                        ff[i][j][k]->SetParameters(peakContent,peak,sigma,8.70778e-01,2.89393e+00,1.80957e+00,2.90252e+00);
                        ff[i][j][k]->SetParLimits(2,0.005,0.02);
                        //ff[i][j][k]->SetParLimits(2,0.007,0.016);
                        ff[i][j][k]->SetParLimits(3,0.9,1.3);
                        ff[i][j][k]->SetParLimits(4,2.0,3.4);
                        ff[i][j][k]->SetParLimits(5,1.5,2.2);
                        ff[i][j][k]->SetParLimits(6,2.5,3.5);
                        //ff[i][j][k]->FixParameter(5,2.00245e+00);
                        //ff[i][j][k]->FixParameter(6,2.89410e+00);
                    }
                    ff[i][j][k]->SetParLimits(0,peakContent*0.9,peakContent*1.1);
                    h_ratio[i][j][k]->Fit(ff[i][j][k],"LL M O Q R");
                    h_ratio[i][j][k]->Fit(ff[i][j][k],"LL M O Q R");
                    if(i==0 || i==1){
                    h_ratio[i][j][k]->Fit(ff[i][j][k],"LL M O Q R");
                    h_ratio[i][j][k]->Fit(ff[i][j][k],"LL M O Q R");
                    h_ratio[i][j][k]->Fit(ff[i][j][k],"LL M O Q R");
                    h_ratio[i][j][k]->Fit(ff[i][j][k],"LL M O Q R");
                    h_ratio[i][j][k]->Fit(ff[i][j][k],"LL M O Q R");
                    }
                    cout << ">>>>>>>> cent : " << i << ", ptbins : " << ptBins[k] << " - " << ptBins[k+1] << endl; 
                    h_ratio[i][j][k]->Fit(ff[i][j][k],"LL M O R");
                } else if(fnc_name=="COMB"){
                    Int_t peakBin  = h_ratio[i][j][k]->GetMaximumBin();
                    Double_t peakContent  = h_ratio[i][j][k]->GetBinContent(peakBin);
                    Double_t peak =  h_ratio[i][j][k]->GetBinCenter(peakBin);
                    Double_t sigma = h_ratio[i][j][k]->GetRMS(); 
                    if(collSt =="pbpb"){
                        if(centBins_[0][i]==100 || centBins_[0][i]==140){
                            ff[i][j][k] = cleverGaus(h_ratio[i][j][k], Form("f_%s",h_ratio[i][j][k]->GetName()));
                        } else{
                            ff[i][j][k] = new TF1(Form("f1_%d_%d_%d",i,j,k), fnc_DSCB, peak-2.5*sigma, peak+2.5*sigma, 7);
                            ff[i][j][k]->SetParameters(peakContent,peak,sigma,0.79,3.63,0.59,1.67);
                        }
                    } else{ // pp
                        ff[i][j][k] = cleverGaus(h_ratio[i][j][k], Form("f_%s",h_ratio[i][j][k]->GetName()));
                    }
                }

                if(k>=2){
                    //gPad->SetLogy();
                    double mean = ff[i][j][k]->GetParameter(1);
                    double mean_err = ff[i][j][k]->GetParError(1);
                    double resol = abs(ff[i][j][k]->GetParameter(2));
                    double resol_err = abs(ff[i][j][k]->GetParError(2));
                    h_mean_fit[i][j]->SetBinContent(k+1-2, mean);
                    h_mean_fit[i][j]->SetBinError(k+1-2, mean_err);
                    h_sig_fit[i][j]->SetBinContent(k+1-2, resol);
                    h_sig_fit[i][j]->SetBinError(k+1-2, resol_err);

                    // mean calculation
                    // mean = h_ratio[i][j][k]->GetMean();
                    // mean_err = h_ratio[i][j][k]->GetMeanError();
                    // resol = h_ratio[i][j][k]->GetRMS();
                    // resol_err = h_ratio[i][j][k]->GetRMSError();
                    // h_mean[i][j]->SetBinContent(k+1, mean);
                    // h_mean[i][j]->SetBinError(k+1, mean_err);
                    // h_rms[i][j]->SetBinContent(k+1, resol);
                    // h_rms[i][j]->SetBinError(k+1, resol_err);

                    c[i][j]->cd(k+1-2);
                    h_ratio[i][j][k]->GetXaxis()->SetRangeUser(0.7,1.3);
                    h_ratio[i][j][k]->Draw("p");
                    TString centSt = Form("%i-%i%%", centBins_[0][i]/2, centBins_[1][i]/2); 
                    if(isPP) centSt = "pp";
                    float xpos = 0.21;
                    float dy = 0.09;
                    drawText(Form("%s, %.2f<|#eta|<%.2f", centSt.Data(), etaBins[0][j], etaBins[1][j]),xpos,0.84);
                    drawText(Form("%d<p_{T}^{gen #gamma}<%d GeV", (int)ptBins[k],(int)ptBins[k+1]),xpos,0.84-dy);
                    drawText(Form("%s fitting", fnc_name.Data()),xpos,0.84-2*dy);
                }
                ctemp->cd();
            }
            c[i][j]->SaveAs(Form("figures/photonEnergy_recoPt_over_genPt_fitting_ptDep_%s_cent%d_eta%d.pdf",cap.Data(),i,j));
        }
    }

    ////////////////////////////////////////////////////////
    // pull distribution
    TCanvas* c_pull[nCentBins][nEtaBins];
    for (int i=0; i<nCentBins; ++i) {
        for (int j=0; j<nEtaBins; ++j) {
            c_pull[i][j] = new TCanvas(Form("can_pull_cent%d_eta%d",i,j),"",250*4,250*3);
            c_pull[i][j]->Divide(5,4);
            for (int k=2; k<nPtBins; ++k) {
                h_ratio_pull[i][j][k] = getPullHist(h_ratio[i][j][k], ff[i][j][k]);
                h_ratio_pull[i][j][k]->SetTitle(";#frac{reco p_{T}^{#gamma}}{gen p_{T}^{#gamma}};Pull");
                h_ratio_pull[i][j][k]->SetMarkerStyle(20);
                h_ratio_pull[i][j][k]->SetMarkerSize(0.6);
                h_ratio_pull[i][j][k]->GetYaxis()->SetRangeUser(-5,5);
                h_ratio_pull[i][j][k]->GetXaxis()->SetRangeUser(0.7,1.3);
                c_pull[i][j]->cd(k+1-2);
                h_ratio_pull[i][j][k]->Draw("p");
                jumSun(0.7,0,1.3,0);
                TString centSt = Form("%i-%i%%", centBins_[0][i]/2, centBins_[1][i]/2);
                if(isPP) centSt = "pp";
                float xpos = 0.21;
                float dy = 0.09;
                drawText(Form("%s, %.2f<|#eta|<%.2f", centSt.Data(), etaBins[0][j], etaBins[1][j]),xpos,0.84);
                drawText(Form("%d<p_{T}^{gen #gamma}<%d GeV", (int)ptBins[k],(int)ptBins[k+1]),xpos,0.84-dy);
                drawText(Form("%s fitting", fnc_name.Data()),xpos,0.84-2*dy);
            }
            c_pull[i][j]->SaveAs(Form("figures/photonEnergy_recoPt_over_genPt_fitting_PullDist_ptDep_%s_cent%d_eta%d.pdf",cap.Data(),i,j));
        }
    }

    ////////////////////////////////////////////////////////
    // mean of reco/gen pt for each pt bin  
    TF1 *f_mean[nCentBins][nEtaBins];
    TF1 *f_mean_fit[nCentBins][nEtaBins];
    for (int i=0; i<nCentBins; ++i) {
        for (int j=0; j<nEtaBins; ++j) {
            f_mean_fit[i][j] = new TF1(Form("f_mean_fit_cent%d_eta%d",i,j), myFunc, 0, 300, 3);
            f_mean_fit[i][j] -> SetParameters(0.03, 0.8, 0.01);
            f_mean_fit[i][j] -> SetParNames("C", "S", "N");
            h_mean_fit[i][j] -> Fit(f_mean_fit[i][j], "RLL Q");
            h_mean_fit[i][j] -> Fit(f_mean_fit[i][j], "RLL Q");
            h_mean_fit[i][j] -> Fit(f_mean_fit[i][j], "RLL Q");

            f_mean[i][j] = new TF1(Form("f_mean_cent%d_eta%d",i,j), myFunc, 0, 300, 3);
            f_mean[i][j] -> SetParameters(0.03, 0.8, 0.01);
            f_mean[i][j] -> SetParNames("C", "S", "N");
            h_mean[i][j] -> Fit(f_mean[i][j], "RLL Q");
            h_mean[i][j] -> Fit(f_mean[i][j], "RLL Q");

            if(fnc_name=="COMB" && collSt =="pbpb"){
                if(centBins_[0][i]==0 || centBins_[0][i]==10 || centBins_[0][i]==20 || centBins_[0][i]==40){
                    f_mean_fit[i][j] -> SetParameter(0,f_mean[i][j]->GetParameter(0));
                    f_mean_fit[i][j] -> SetParameter(1,f_mean[i][j]->GetParameter(1));
                    f_mean_fit[i][j] -> SetParameter(2,f_mean[i][j]->GetParameter(2));
                }
            } 
        }
    }


    ////////////////////////////////////////////////////////
    // resolution of reco/gen pt for each pt bin  
    TF1 *f_rms[nCentBins][nEtaBins];
    TF1 *f_sig_fit[nCentBins][nEtaBins];
    // TF1 *f_sig_fit_high[nCentBins][nEtaBins];
    // TF1 *f_sig_fit_low[nCentBins][nEtaBins];
    for (int i=0; i<nCentBins; ++i) {
        for (int j=0; j<nEtaBins; ++j) {
            f_sig_fit[i][j] = new TF1(Form("f_sig_fit_cent%d_eta%d",i,j), myFunc, 0, 300, 3);
            f_sig_fit[i][j] -> SetParameters(0.03, 0.8, 0.01);
            f_sig_fit[i][j] -> SetParNames("C", "S", "N");
            h_sig_fit[i][j] -> Fit(f_sig_fit[i][j], "RLL Q");
            h_sig_fit[i][j] -> Fit(f_sig_fit[i][j], "RLL Q");
            h_sig_fit[i][j] -> Fit(f_sig_fit[i][j], "RLL");

            (TVirtualFitter::GetFitter())->GetConfidenceIntervals(h_sig_fit_band[i][j]);
            //Now the histogram has the fitted function values as the
            //bin contents and the confidence intervals as bin errors
            h_sig_fit_band[i][j]->SetStats(kFALSE);
            h_sig_fit_band[i][j]->SetFillColor(2);
            h_sig_fit_band[i][j]->SetFillStyle(3002);

            // f_sig_fit_high[i][j] = new TF1(Form("f_sig_fit_high_cent%d_eta%d",i,j), myFunc, 0, 300, 3);
            // f_sig_fit_high[i][j] -> SetParameter(0,f_sig_fit[i][j]->GetParameter(0)+f_sig_fit[i][j]->GetParError(0));
            // f_sig_fit_high[i][j] -> SetParameter(1,f_sig_fit[i][j]->GetParameter(1)+f_sig_fit[i][j]->GetParError(1));
            // f_sig_fit_high[i][j] -> SetParameter(2,f_sig_fit[i][j]->GetParameter(2)+f_sig_fit[i][j]->GetParError(2));
            // f_sig_fit_low[i][j] = new TF1(Form("f_sig_fit_low_cent%d_eta%d",i,j), myFunc, 0, 300, 3);
            // f_sig_fit_low[i][j] -> SetParameter(0,f_sig_fit[i][j]->GetParameter(0)-f_sig_fit[i][j]->GetParError(0));
            // f_sig_fit_low[i][j] -> SetParameter(1,f_sig_fit[i][j]->GetParameter(1)-f_sig_fit[i][j]->GetParError(1));
            // f_sig_fit_low[i][j] -> SetParameter(2,f_sig_fit[i][j]->GetParameter(2)-f_sig_fit[i][j]->GetParError(2));

            f_rms[i][j] = new TF1(Form("f_rms_cent%d_eta%d",i,j), myFunc, 0, 300, 3);
            f_rms[i][j] -> SetParameters(0.03, 0.8, 0.01);
            f_rms[i][j] -> SetParNames("C", "S", "N");
            h_rms[i][j] -> Fit(f_rms[i][j], "RLL Q");
            h_rms[i][j] -> Fit(f_rms[i][j], "RLL Q");
        }
    }

    //////////////////////////////////////////////////
    //Draw
    int j=0; // plot only barrel photons

    int nRow = 1;
    int nCol = 1;
    if(nCentBins<=2){ nCol = nCentBins; }
    else if(nCentBins>2 && nCentBins<=4){ nCol=2; nRow=2;} 
    else if(nCentBins>4 && nCentBins<=6){ nCol=3; nRow=2;} 
    else if(nCentBins>6 && nCentBins<=9){ nCol=4; nRow=2;} 
    else { nCol=4; nRow=3; }

    // 2D plot : Gen/Reco pT vs. Reco pT 
    TCanvas* c_2d = new TCanvas("c_ratio_vs_recopt", "", 500*nCol, 500 *nRow);
    c_2d->Divide(nCol,nRow);
    c_2d->SetRightMargin(0.10);
    for (int i=0; i<nCentBins; ++i) {
        c_2d->cd(i+1);
        h_ptratio[i][j]->Draw("colz");
    }
    c_2d->SaveAs(Form("figures/photonEnergyCorrection_2D_ratio_vs_genPt_%s.pdf",cap.Data())); 
    // 2D plot : Gen vs. Reco pT 
    TCanvas* c_mat = new TCanvas("c_genpt_vs_recopt", "", 500*nCol, 500 *nRow);
    c_mat->Divide(nCol,nRow);
    c_mat->SetRightMargin(0.10);
    for (int i=0; i<nCentBins; ++i) {
        c_mat->cd(i+1);
        h_pt[i][j]->Draw("colz");
    }
    c_mat->SaveAs(Form("figures/photonEnergyCorrection_2D_genPt_vs_recoPt_%s.pdf",cap.Data())); 

    // mean(gen/reco pT) vs. Reco pT
    TCanvas* c_mean = new TCanvas("c_mean", "", 500*nCol, 500*nRow);
    c_mean->Divide(nCol,nRow);
    c_mean->SetRightMargin(0.10);
    for (int i=0; i<nCentBins; ++i){
        c_mean->cd(i+1);
        h_mean_fit[i][j]->SetMarkerColor(2);
        h_mean_fit[i][j]->SetMarkerStyle(25);
        h_mean_fit[i][j]->GetYaxis()->SetRangeUser(0.8,1.1);
        h_mean_fit[i][j]->Draw("p");
        // h_mean[i][j]->SetMarkerColor(8);
        // h_mean[i][j]->SetMarkerStyle(24);
        // h_mean[i][j]->Draw("p same");

        // f_mean[i][j]->SetLineColor(8);
        // f_mean[i][j]->DrawCopy("same");
        f_mean_fit[i][j]->SetLineColor(2);
        f_mean_fit[i][j]->DrawCopy("same");
        jumSun(ptBins[0],1,ptBins[nPtBins],1);
        float c = f_mean_fit[i][j]->GetParameter(0);
        float n = f_mean_fit[i][j]->GetParameter(1);
        float s = f_mean_fit[i][j]->GetParameter(2);
        drawText(Form("%.2f + #frac{%.2f}{#sqrt{p_{T}}} + #frac{%.2f}{p_{T}}",c,n,s),0.4,0.3);
        drawText(Form("%s","After energy correction"),0.4,0.4);
    }
    TLegend* l1 = new TLegend(0.5,0.7,0.9,0.9); 
    legStyle(l1);
    l1->AddEntry(h_mean[0][0],"Mean","p");
    l1->AddEntry(f_mean[0][0],"Fit","l");
    //l1->AddEntry(h_mean_fit[0][0],Form("Mean(%s)",fnc_name.Data()),"p");
    //l1->AddEntry(f_mean_fit[0][0],Form("Fit Mean(%s)",fnc_name.Data()),"l");
    l1->Draw("same");

    TString st_cnsFun = "C + #frac{N}{#sqrt{p_{T}}} + #frac{S}{p_{T}}";
    c_mean->SaveAs(Form("figures/photonEnergyCorrection_1D_mean_vs_genPt_%s.pdf",cap.Data())); 

    // resolution(gen/reco pT) vs. Reco pT
    TCanvas* c_res = new TCanvas("c_res", "", 500*nCol, 500*nRow);
    c_res->Divide(nCol,nRow);
    c_res->SetRightMargin(0.10);
    for (int i=0; i<nCentBins; ++i) {
        c_res->cd(i+1);
        h_sig_fit[i][j]->SetMarkerColor(2);
        h_sig_fit[i][j]->SetMarkerStyle(25);
        h_sig_fit[i][j]->GetYaxis()->SetRangeUser(0.0,0.1);
        if(isPP) 
            h_sig_fit[i][j]->GetYaxis()->SetRangeUser(0.0,0.05);
        f_sig_fit[i][j]->SetLineColor(2);
        h_sig_fit[i][j]->Draw("p");
        // h_rms[i][j]->SetMarkerColor(8);
        // h_rms[i][j]->SetMarkerStyle(24);
        // h_rms[i][j]->Draw("p same");

        // f_rms[i][j]->SetLineColor(8);
        // f_rms[i][j]->DrawCopy("same");
        //f_sig_fit[i][j]->DrawCopy("same");

        // f_sig_fit_high[i][j]->SetLineColor(4);
        // f_sig_fit_high[i][j]->DrawCopy("same");
        // f_sig_fit_low[i][j]->SetLineColor(3);
        // f_sig_fit_low[i][j]->DrawCopy("same");

        //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(h_sig_fit_band[i][j]);
        //Now the histogram has the fitted function values as the
        //bin contents and the confidence intervals as bin errors
        //h_sig_fit_band[i][j]->SetStats(kFALSE);
        //h_sig_fit_band[i][j]->SetFillColor(2);
        h_sig_fit_band[i][j]->Draw("e3 same");

        float c = f_sig_fit[i][j]->GetParameter(0);
        float n = f_sig_fit[i][j]->GetParameter(1);
        float s = f_sig_fit[i][j]->GetParameter(2);
        drawText(Form("%.2f + #frac{%.2f}{#sqrt{p_{T}}} + #frac{%.2f}{p_{T}}",c,n,s),0.4,0.55);
    }
    TLegend* l2 = new TLegend(0.5,0.7,0.9,0.9); 
    legStyle(l2);
    // l2->AddEntry(h_rms[0][0],"RMS","p");
    // l2->AddEntry(f_rms[0][0],"Fit RMS","l");
    l2->AddEntry(h_sig_fit[0][0],Form("#sigma%s",""),"p");
    l2->AddEntry(f_sig_fit[0][0],Form("Fit #sigma%s",""),"l");
    l2->AddEntry(h_sig_fit_band[0][0],Form("95%% Confidence Level%s",""),"f");
    //l2->AddEntry(h_sig_fit[0][0],Form("#sigma(%s)",fnc_name.Data()),"p");
    //l2->AddEntry(f_sig_fit[0][0],Form("Fit #sigma(%s)",fnc_name.Data()),"l");
    //l2->AddEntry(h_sig_fit_band[0][0],Form("95%% Confidence Level%s",""),"lf");
    l2->Draw("same");
    c_res->SaveAs(Form("figures/photonEnergyCorrection_1D_resolution_vs_genPt_%s.pdf",cap.Data())); 

    for (int i=0; i<nCentBins; ++i) {
        for (int j=0; j<nEtaBins; ++j) {
            for (int l=0; l<7; ++l) {
                double mean=0;
                for (int k=0; k<nPtBins; ++k) {
                    double par = ff[i][j][k]->GetParameter(l);
                    cout << ">>>>>>>> cent : " << i  << ", parameter " << l << ", ptbins : " << ptBins[k] << " - " << ptBins[k+1] << " : " << par << endl; 
                    mean+=par;
                }
                cout << ">>>>>>>> cent : " << i  << ", parameter " << l << ", mean : " << mean/nPtBins << endl; 
            }
        }
    }



    /////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////
    // Save 
    TFile* energyCorrectionFile = TFile::Open(Form("%s",outfname.Data()), "recreate");
    c_2d->Write("", TObject::kOverwrite);
    c_mat->Write("", TObject::kOverwrite);
    c_mean->Write("", TObject::kOverwrite);
    c_res->Write("", TObject::kOverwrite);
    for (int i=0; i<nCentBins; ++i) {
        for (int j=0; j<nEtaBins; ++j) {
            h_pt[i][j]->Write(Form("h_matrix_cent%i_eta%i", i, j), TObject::kOverwrite);
            h_ptratio[i][j]->Write(Form("h_ptratio_cent%i_eta%i", i, j), TObject::kOverwrite);

            f_rms[i][j]->Write();
            f_sig_fit[i][j]->Write();
            h_sig_fit_band[i][j]->Write();
            f_mean[i][j]->Write();
            f_mean_fit[i][j]->Write();
            h_mean_fit[i][j]->Write(Form("photonEnergyCorr_mean_fit_cent%i_eta%i", i, j), TObject::kOverwrite);
            h_sig_fit[i][j]->Write(Form("photonEnergyCorr_sigma_fit_cent%i_eta%i", i, j), TObject::kOverwrite);
            h_mean[i][j]->Write(Form("photonEnergyCorr_mean_cent%i_eta%i", i, j), TObject::kOverwrite);
            h_rms[i][j]->Write(Form("photonEnergyCorr_rms_cent%i_eta%i", i, j), TObject::kOverwrite);
            c[i][j]->Write(Form("ratio_cent%i_eta%i", i, j), TObject::kOverwrite);

            for (int k=0; k<nPtBins; ++k) {
                h_ratio[i][j][k]->Write();
                if(k>=2)h_ratio_pull[i][j][k]->Write();
            }
        }
    }
    energyCorrectionFile->Close();
}


#define _PI 3.1415926535897932384
float dR(float eta1, float eta2, float phi1, float phi2) {
    float deta = eta1 - eta2;
    float dphi = fabs(phi1 - phi2);
    dphi = (dphi > _PI) ? 2 * _PI - dphi : dphi;
    return sqrt(deta * deta + dphi * dphi);
}

TH1F* getPullHist(TH1F *h1, TF1 *f){
    Int_t nBins = h1->GetNbinsX();
    Double_t xMin = h1->GetBinLowEdge(1);
    Double_t xMax = h1->GetBinLowEdge(nBins)+h1->GetBinWidth(nBins);
    TH1F* hp = new TH1F(Form("%s_pull",h1->GetName()), ";#frac{reco p_{T}^{#gamma}}{gen p_{T}^{#gamma}};Pull", nBins,xMin,xMax);
    for(Int_t ix=1; ix<=nBins; ++ix){
        float data = h1->GetBinContent(ix);
        float data_err = h1->GetBinError(ix);
        float data_pos = h1->GetBinLowEdge(ix)+(h1->GetBinWidth(ix))/2.;
        float fit = f->Eval(data_pos);
        float pull = (data-fit)/data_err;
        if(data==0) pull = 0;
        hp->SetBinContent(ix+1,pull);
        hp->SetBinError(ix+1,0);
        // cout << "pull hist bin " << ix << " value = " << hp->GetBinContent(ix+1) << endl;
    }
    return hp;
}
