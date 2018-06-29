// To get (( Reconstruction Efficiency = recoMatched generated photons / generated isolated photons ))
// Inherited from  
// Date : 2018 Feb 08
// Creator : Yeonju Go 

#include "../phoRaaCuts/yjUtility.h"
#include "../phoRaaCuts/phoRaaCuts_temp.h"
#include "../ElectroWeak-Jet-Track-Analyses/TreeHeaders/ggHiNtuplizerTree.h"
const float delta2 = 0.15*0.15;
const float delta = 0.15;

void reco_efficiency_withForest(TString coll="pbpb", TString ver="Cymbal_noFlt30_in4cent")
{
    cout << " :::::: reco_efficiency_withForest.C :::::: " << endl;
    TH1::SetDefaultSumw2();
    gStyle->SetOptStat(0);
    //SetyjPadStyle();

    ///////////////////////////////////////////////////////////////////////////
    // TCAHIN, GET FILE 
    TChain* t;
    if(coll=="pp") t = new TChain("ggHiNtuplizer/EventTree");
    else if(coll=="pbpb") t = new TChain("ggHiNtuplizer/EventTree");
    else cout << "[ERROR] It's weird, what is the collision? " << coll << endl;

    TChain* t_evt = new TChain("hiEvtAnalyzer/HiTree");
    //TChain * t_skim = new TChain("skimanalysis/HltTree");
    //TChain * t_hlt = new TChain("hltanalysisReco/HltTree");
    
    int nFiles(0);
    char line[1024];
    //TString inFileName = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/inputfilelist/pbpblist_HydjetDrum_v1_and_ext1.txt"; 
    TString inFileName = Form("%s",pbpb_forest_inputList.Data());
    if(coll=="pp") inFileName = Form("%s",pp_forest_inputList.Data());
    ifstream in(inFileName.Data());
    while (in.getline(line,1024,'\n'))
    {
        //cout << line << endl;
        const char* fname = Form("%s",line);
        //const char* fname = Form("%s/%s/%s",dir,runN[ir].data(),line);
        t->Add(fname);
        t_evt->Add(fname);
        nFiles++;
        cout << "Added " << fname << endl;
    } 
    t->AddFriend(t_evt);
    ///////////////////////////////////////////////////////////////////////////
    // SetBranchAddress
    Int_t           nMC=0;
    std::vector<int>     *mcPID=0;
    std::vector<int>     *mcStatus=0;
    std::vector<float>   *mcPt=0;
    std::vector<float>   *mcEta=0;
    std::vector<float>   *mcPhi=0;
    std::vector<float>   *mcE=0;
    std::vector<float>   *mcEt=0;
    std::vector<float>   *mcMass=0;
    std::vector<int>     *mcMomPID=0;
    std::vector<float>   *mcCalIsoDR03=0;
    std::vector<float>   *mcCalIsoDR04=0;
    std::vector<float>   *mcTrkIsoDR03=0;
    std::vector<float>   *mcTrkIsoDR04=0;
    Int_t           nPho=0;
    std::vector<float>   *phoE=0;
    std::vector<float>   *phoEt=0;
    std::vector<float>   *phoEtCorrected=0;
    std::vector<float>   *phoEtCorrected_sys=0;
    std::vector<float>   *phoEta=0;
    std::vector<float>   *phoPhi=0;
    std::vector<float>   *phoR9=0;
    std::vector<float>   *phoHoverE=0;
    std::vector<float>   *phoSigmaIEtaIEta=0;
    Int_t           pho_isEle=0;
    Int_t           pho_is2015Noise=0;
    std::vector<float>   *phoSigmaIEtaIEta_2012=0;
    std::vector<float>   *pho_sumIsoCorrected=0;
    std::vector<float>   *pho_swissCrx=0;
    std::vector<float>   *pho_seedTime=0;
    if (t->GetBranch("nMC")) t->SetBranchAddress("nMC", &nMC);
    if (t->GetBranch("mcPID")) t->SetBranchAddress("mcPID", &mcPID);
    if (t->GetBranch("mcStatus")) t->SetBranchAddress("mcStatus", &mcStatus);
    if (t->GetBranch("mcPt")) t->SetBranchAddress("mcPt", &mcPt);
    if (t->GetBranch("mcEta")) t->SetBranchAddress("mcEta", &mcEta);
    if (t->GetBranch("mcPhi")) t->SetBranchAddress("mcPhi", &mcPhi);
    if (t->GetBranch("mcE")) t->SetBranchAddress("mcE", &mcE);
    if (t->GetBranch("mcEt")) t->SetBranchAddress("mcEt", &mcEt);
    if (t->GetBranch("mcMass")) t->SetBranchAddress("mcMass", &mcMass);
    if (t->GetBranch("mcMomPID")) t->SetBranchAddress("mcMomPID", &mcMomPID);
    if (t->GetBranch("mcCalIsoDR03")) t->SetBranchAddress("mcCalIsoDR03", &mcCalIsoDR03);
    if (t->GetBranch("mcCalIsoDR04")) t->SetBranchAddress("mcCalIsoDR04", &mcCalIsoDR04);
    if (t->GetBranch("mcTrkIsoDR03")) t->SetBranchAddress("mcTrkIsoDR03", &mcTrkIsoDR03);
    if (t->GetBranch("mcTrkIsoDR04")) t->SetBranchAddress("mcTrkIsoDR04", &mcTrkIsoDR04);
    if (t->GetBranch("nPho")) t->SetBranchAddress("nPho", &nPho);
    if (t->GetBranch("phoE")) t->SetBranchAddress("phoE", &phoE);
    if (t->GetBranch("phoEt")) t->SetBranchAddress("phoEt", &phoEt);
    if (t->GetBranch("phoEtCorrected")) t->SetBranchAddress("phoEtCorrected", &phoEtCorrected);
    if (t->GetBranch("phoEtCorrected_sys")) t->SetBranchAddress("phoEtCorrected_sys", &phoEtCorrected_sys);
    if (t->GetBranch("phoEta")) t->SetBranchAddress("phoEta", &phoEta);
    if (t->GetBranch("phoPhi")) t->SetBranchAddress("phoPhi", &phoPhi);
    if (t->GetBranch("phoR9")) t->SetBranchAddress("phoR9", &phoR9);
    if (t->GetBranch("phoHoverE")) t->SetBranchAddress("phoHoverE", &phoHoverE);
    if (t->GetBranch("phoSigmaIEtaIEta")) t->SetBranchAddress("phoSigmaIEtaIEta", &phoSigmaIEtaIEta);
    if (t->GetBranch("pho_isEle")) t->SetBranchAddress("pho_isEle", &pho_isEle);
    if (t->GetBranch("pho_is2015Noise")) t->SetBranchAddress("pho_is2015Noise", &pho_is2015Noise);
    if (t->GetBranch("phoSigmaIEtaIEta_2012")) t->SetBranchAddress("phoSigmaIEtaIEta_2012", &phoSigmaIEtaIEta_2012);
    if (t->GetBranch("pho_swissCrx")) t->SetBranchAddress("pho_swissCrx", &pho_swissCrx);
    if (t->GetBranch("pho_seedTime")) t->SetBranchAddress("pho_seedTime", &pho_seedTime);
    int hiBin;
    t->SetBranchAddress("hiBin",&hiBin);

    ///////////////////////////////////////////////////////////////////////////
    // HISTOGRAM DEFINE
    Int_t nCENTBINS = nCentBinIF;
    if(coll=="pp") nCENTBINS=1; 
    TH1D* h1D_Num[nCENTBINS];//reconstructed photons among generated photons (reco pt & reco eta)
    TH1D* h1D_Den[nCENTBINS];//generated photons (gen pt & gen eta)
    TH1D* h1D_Eff[nCENTBINS];//reconstructed photons in generated photons / generated photons
    for(Int_t i=0;i<nCENTBINS;++i){
        h1D_Num[i] = new TH1D(Form("reco_num_cent%d",i), ";p_{T}^{#gamma} (GeV);dN/dp_{T}", nPtBin, ptBins);
        h1D_Den[i] = (TH1D*) h1D_Num[i]->Clone(Form("reco_den_cent%d",i));
        h1D_Eff[i] = new TH1D(Form("reco_eff_cent%d",i), ";p_{T}^{#gamma} (GeV);Efficiency", nPtBin, ptBins);
        //inTree->Draw("phoEt:abs(phoEta)>>h2D_Num","pho_genMatchedIndex!=-1","colz");
        //inTree->Draw("mcEt[pho_genMatchedIndex]:abs(mcEta[pho_genMatchedIndex])>>h2D_Den","pho_genMatchedIndex!=-1","colz");
        //inTree->Draw("mcE:abs(mcEta)>>h2D_Den","(mcPID==22||mcPID==-22)&&(mcStatus==1)","colz");
    } 

    ///////////////////////////////////////////////////////////////////////////
    // EVENT LOOP 
    int nhotspot = 0;
    Long64_t nentries = t->GetEntries();
    for(int ientries = 0; ientries < nentries; ++ientries){
        t->GetEntry(ientries);
        if (ientries % 20000 == 0)
            printf("current entry = %d out of %lld : %.3f %%\n", ientries, nentries, (double)ientries / nentries * 100);
        for (int igen = 0; igen < nMC; ++igen){
            if (mcStatus->at(igen) != 1 || abs(mcPID->at(igen)) != 22 ) continue;
            if (mcPt->at(igen)<10) continue;
            if (mcCalIsoDR04->at(igen)>5) continue;
            if (abs(mcEta->at(igen))>1.4442) continue;
            bool isPass = (abs(mcMomPID->at(igen)) <= 22 || mcMomPID->at(igen) == -999);
            if (!isPass) continue; //MomID condition; selecting only prompt photons (direct photons & photons fragmented from quarks)

            Int_t currentCent(-1);
            if(coll=="pp") currentCent = 0;
            else if(coll=="pbpb"){
                for(Int_t i=1;i<nCENTBINS;++i){ 
                    if(hiBin>=centBins_i[i] && hiBin<centBins_f[i])
                        currentCent = i;
                }
            }
            
            if(coll=="pbpb") h1D_Den[currentCent]->Fill(mcEt->at(igen));
            h1D_Den[0]->Fill(mcEt->at(igen));

            Float_t currentDiffPt(1000);
            Float_t currentRecoPt(-1);
            int matchedIndex = -1;
            for(int ipho = 0; ipho < nPho; ++ipho){
                float tempDR = getDR(phoEta->at(ipho), phoPhi->at(ipho), mcEta->at(igen), mcPhi->at(igen));
                float tempDiffPt = abs( mcPt->at(igen) - phoEt->at(ipho) );
                if( (tempDR < delta) && (tempDiffPt < currentDiffPt) ) {
                    currentDiffPt = tempDiffPt;
                    currentRecoPt = phoEt->at(ipho);
                    matchedIndex = ipho;
                }
            }//photon loop
            /*
               for(int ipho = 0; ipho < pho.nPho; ipho++){
               if(pho.pho_genMatchedIndex->at(ipho)!=-1) 
               cout << "genMatchedIndexPt="<<pho.mcPt->at(pho.pho_genMatchedIndex->at(ipho))<<", genPt="<<pho.mcPt->at(igen)<<", recoPt="<<pho.phoEt->at(ipho)<<endl;
               }
               */
            if(matchedIndex!=-1) {
                // cout << "genMatchedIndexPt="<<pho.mcPt->at(pho.pho_genMatchedIndex->at(matchedIndex))<<", genPt="<<pho.mcPt->at(igen)<<", recoPt="<<pho.phoEt->at(matchedIndex)<<endl;
                if(coll=="pbpb") h1D_Num[currentCent]->Fill(mcEt->at(igen));
                h1D_Num[0]->Fill(mcEt->at(igen));
            }
        }//gen loop
    }
    for(Int_t i=0;i<nCENTBINS;++i) 
        h1D_Eff[i]->Divide(h1D_Num[i],h1D_Den[i],1,1,"B");

   // TH1D* h1D_Num_pt = (TH1D*) h2D_Num->ProjectionY("h1D_Num_pt",0,1); 
   // TH1D* h1D_Den_pt = (TH1D*) h2D_Den->ProjectionY("h1D_Den_pt",0,1);
   // TH1D* h1D_Eff_pt = (TH1D*) h1D_Den_pt->Clone("h1D_Eff_pt");
   // h1D_Eff_pt->Reset();
   // h1D_Eff_pt->Divide(h1D_Num_pt,h1D_Den_pt,1,1,"B"); 
   // TEfficiency* hEff = new TEfficiency(h1D_Num_pt,h1D_Den_pt);
   // saveHistogramsToPicture(h1D_Eff_pt, "pdf",Form("reco_%s",cap));
   // saveHistogramsToPicture(h2D_Eff, "pdf",Form("reco_%s",cap));
    TString dir = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/efficiency/";
    TFile* fout = new TFile(Form("%soutput/%s_reco_efficiency_%s.root",dir.Data(),coll.Data(),ver.Data()),"RECREATE");   
    fout->cd();
    for(Int_t i=0;i<nCENTBINS;++i){ 
        h1D_Num[i]->Write();
        h1D_Den[i]->Write();
        h1D_Eff[i]->Write();
    }
    fout->Close();
}
