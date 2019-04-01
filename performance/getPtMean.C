#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"

void getPtMean(TString coll="pbpb", TString ver="temp"){
    gStyle -> SetOptStat(0);

    TFile *f1 = 0; 
    if(coll=="pbpb") f1 = TFile::Open(pbpbDatafname);
    else if(coll=="pp") f1 = TFile::Open(ppDatafname);

    TTree *t = (TTree*)f1->Get("EventTree");
    TTree *t_hi = (TTree*)f1->Get("HiEvt");
    TTree *t_hlt = (TTree*)f1->Get("hltTree");
    TTree *t_skim = (TTree*)f1->Get("skim");
    t->AddFriend(t_hi);
    t->AddFriend(t_hlt);
    t->AddFriend(t_skim);
    TH1D* h[nPtBin];
    double meanPt[nPtBin];
    double errorPt[nPtBin];
    for (int ipt=0; ipt<nPtBin; ++ipt) {
        h[ipt] = new TH1D(Form("h%d",ipt),Form("%d",ipt),nPtBin,ptBins);
        TCut ptCut = Form("%s >= %f && %s < %f",phoEtVar.Data(), ptBins[ipt], phoEtVar.Data(), ptBins[ipt+1]);
        if(coll=="pbpb") t->Draw(Form("%s>>%s",phoEtVar.Data(),h[ipt]->GetName()), phoSignalCut && etaCut && ptCut);
        else if(coll=="pp") t->Draw(Form("%s>>%s",phoEtVar.Data(),h[ipt]->GetName()), phoSignalCut_pp && etaCut && ptCut);
        meanPt[ipt] = h[ipt] -> GetMean();
        errorPt[ipt] = h[ipt] -> GetMeanError();
        cout <<coll<<": "<<ptBins[ipt] << " <= pt < "<<ptBins[ipt+1]<< "; mean = " << meanPt[ipt] << ", mean error = " <<  errorPt[ipt] << endl;
    }
}
