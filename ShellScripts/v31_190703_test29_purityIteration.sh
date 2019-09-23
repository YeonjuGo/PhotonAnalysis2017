#!/bin/bash
#int yj_quickPhotonPurity_v7_iteration_separateCent(const TString coll="pbpb", const TString ver="phoRaaCuts_purity_forPaper", bool doSplitPD=true, bool doPreScale=0, bool useSBcorr=0, bool noCentDepCorr=0, bool useMCSB=0){
#verFileCopy_a=('1800802_temp_v20')

verFileCopy_a=('190703_temp_v31')
verName_a=('190703_temp_v31_nominal')
preverName_a=('190220_temp_v26_nominal')

for ((i=0; i< ${#verName_a[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
###    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pbpb","'${verName_a[$i]}'")' >& log/iso_efficiency_withSkimFile_v3_pbpb_${verName_a[$i]}.log & sleep 20 
#    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_a[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_a[$i]}.log & sleep 20
##    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pbpb","'${verName_a[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pbpb_${verName_a[$i]}.log & sleep 20
###    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_a[$i]}'")' >& log/correlation_pbpb_${verName_a[$i]}.log & sleep 20
###    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_a[$i]}'",1)' >& log/correlation_pbpb_${verName_a[$i]}_splitMC.log & sleep 20 
###    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pp","'${verName_a[$i]}'")' >& log/iso_efficiency_withSkimFile_v3_pp_${verName_a[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pp","'${verName_a[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pp_${verName_a[$i]}.log & sleep 20
##    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pp","'${verName_a[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pp_${verName_a[$i]}.log & sleep 20
###    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_a[$i]}'")' >& log/correlation_pp_${verName_a[$i]}.log & sleep 20 
###    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_a[$i]}'",1)' >& log/correlation_pp_${verName_a[$i]}_splitMC.log & sleep 20
###    root -l -b -q 'results/getRawDist_v8.C++("'${verName_a[$i]}'",1,1)' >& log/getRawDist_v8_${verName_a[$i]}.log & sleep 20 
#    wait $(jobs -p)
##    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_a[$i]}'",1,1)' >& log/fitPurity_pbpb_${verName_a[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_a[$i]}'",1,1)' >& log/fitPurity_pp_${verName_a[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity_temp_v3.C++("pbpb","'${verName_a[$i]}'",1,1,2)' >& log/fitPurity_temp_v3_pbpb_${verName_a[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity_temp_v3.C++("pp","'${verName_a[$i]}'",1,1,2)' >& log/fitPurity_temp_v3_pp_${verName_a[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity_temp_v4.C++("pbpb","'${verName_a[$i]}'",1,1,2)' >& log/fitPurity_temp_v4_pbpb_${verName_a[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity_temp_v4.C++("pp","'${verName_a[$i]}'",1,1,2)' >& log/fitPurity_temp_v4_pp_${verName_a[$i]}.log & sleep 20
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_a[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_a[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_a[$i]} inv 0 noSplitMC >& log/RooUnfold_photonRaa_v6_${verName_a[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
##    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_a[$i]}'")' >& log/drawUnfoldingFigures_${verName_a[$i]}.log
#####    root -l -b -q 'performance/divideTree.C++' >& log/divideTree_pbpb_20180815skim.log
##    source /data/ROOT-v5.34.21/bin/thisroot.sh
##    python results/RooUnfold_photonRaa_v6.py ${verName_a[$i]} inv 0 splitMC >& log/RooUnfold_photonRaa_v6_${verName_a[$i]}_splitMC.log
##    source /home/goyeonju/root/builddir/bin/thisroot.sh
##    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_a[$i]}'",1)' >& log/drawUnfoldingFigures_${verName_a[$i]}_splitMC.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_a[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_a[$i]}.log
#    
##     cp ./results/output/phoRaa_${preverName_a[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_a[$i]}_beforeUnfolding.root
##    root -l -b -q 'performance/compare_unfolding.C++("pbpb","'${verName_a[$i]}'")' >& log/compare_unfolding_pbpb_${verName_a[$i]}.log
##    root -l -b -q 'performance/compare_unfolding.C++("pp","'${verName_a[$i]}'")' >& log/compare_unfolding_pp_${verName_a[$i]}.log
done
#cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_a}'")' >& log/plotting_v4_${verName_a}.log



######int yj_quickPhotonPurity_v7_iteration_separateCent(const TString coll="pp", const TString ver="phoRaaCuts_purity_forPaper", bool doSplitPD=true, bool doPreScale=0, int centHere = 1, double sideband_i = 10, double sideband_f = 20, bool useSBcorr=0, bool centDepCorr=0, int ptDepCorrThr=0, int Nfunc=0, bool useMCSB=0, bool use30trig=0){

verFileCopy_test1=('190703_temp_v31')
verName_test1=('190703_temp_v31_pur_maxiter3_sideband5to10')

verFileCopy_test2=('190703_temp_v31')
verName_test2=('190703_temp_v31_pur_maxiter3_sideband1to5')

for ((i=0; i< ${#verName_test1[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_test1[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_test1[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_test1[$i]}.root
##   cp ./purity/output/purity_pbpb_190703_temp_v31_pur_sidebandSigEffat85_SBcorr_centDep_noPtDep_Nfunc0_splitPD_noPreScale.root ./purity/output/purity_pbpb_${verName_test1[$i]}_splitPD_noPreScale.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test1[$i]}'",1,0,1,5,10)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test1[$i]}_cent1.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test1[$i]}'",1,0,2,5,10)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test1[$i]}_cent2.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test1[$i]}'",1,0,3,5,10)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test1[$i]}_cent3.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test1[$i]}'",1,0,4,5,10)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test1[$i]}_cent4.log & sleep 20
##    cp ./purity/output/purity_pp_190703_temp_v31_pur_SBptDep10GeVinterval_ppPtDepCorr_pbpbPtDepCorr_Nfunc0_splitPD_noPreScale.root ./purity/output/purity_pp_${verName_test1[$i]}_splitPD_noPreScale.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pp","'${verName_test1[$i]}'",1,0,0,5,10)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pp_${verName_test1[$i]}.log
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_test1[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_test1[$i]}_pp.root 
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_test1[$i]}_splitPD.root
#    wait $(jobs -p)
    root -l -b -q 'purity/fitPurity_separateCent.C++("pbpb","'${verName_test1[$i]}'",2,0)' >& log/fitPurity_separateCent_pbpb_${verName_test1[$i]}_iter0.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pp","'${verName_test1[$i]}'",2,0)' >& log/fitPurity_separateCent_pp_${verName_test1[$i]}_iter0.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pbpb","'${verName_test1[$i]}'",2,1)' >& log/fitPurity_separateCent_pbpb_${verName_test1[$i]}_iter1.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pp","'${verName_test1[$i]}'",2,1)' >& log/fitPurity_separateCent_pp_${verName_test1[$i]}_iter1.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pbpb","'${verName_test1[$i]}'",2,2)' >& log/fitPurity_separateCent_pbpb_${verName_test1[$i]}_iter2.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pp","'${verName_test1[$i]}'",2,2)' >& log/fitPurity_separateCent_pp_${verName_test1[$i]}_iter2.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pbpb","'${verName_test1[$i]}'",2,3)' >& log/fitPurity_separateCent_pbpb_${verName_test1[$i]}_iter3.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pp","'${verName_test1[$i]}'",2,3)' >& log/fitPurity_separateCent_pp_${verName_test1[$i]}_iter3.log & sleep 20
    wait $(jobs -p)
    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_test1[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_test1[$i]}.log
    source /data/ROOT-v5.34.21/bin/thisroot.sh
    python results/RooUnfold_photonRaa_v6.py ${verName_test1[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_test1[$i]}.log
    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_test1[$i]}'")' >& log/drawUnfoldingFigures_${verName_test1[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_test1[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_test1[$i]}.log
done
cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_test1}'")' >& log/plotting_v4_${verName_test1}.log



verFileCopy_test3=('190703_temp_v31')
verName_test3=('190703_temp_v31_pur_maxiter3_sideband10to20')
################################################################################################
# verFileCopy_test2=('190703_temp_v31')
# verName_test2=('190703_temp_v31_pur_maxiter3_sideband1to5')

for ((i=0; i< ${#verName_test2[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_test2[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_test2[$i]}.root
    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_test2[$i]}.root
#   cp ./purity/output/purity_pbpb_190703_temp_v31_pur_sidebandSigEffat85_SBcorr_centDep_noPtDep_Nfunc0_splitPD_noPreScale.root ./purity/output/purity_pbpb_${verName_test2[$i]}_splitPD_noPreScale.root
    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test2[$i]}'",1,0,1,1,5)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test2[$i]}_cent1.log & sleep 20
    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test2[$i]}'",1,0,2,1,5)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test2[$i]}_cent2.log & sleep 20
    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test2[$i]}'",1,0,3,1,5)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test2[$i]}_cent3.log & sleep 20
    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test2[$i]}'",1,0,4,1,5)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test2[$i]}_cent4.log & sleep 20
#    cp ./purity/output/purity_pp_190703_temp_v31_pur_SBptDep10GeVinterval_ppPtDepCorr_pbpbPtDepCorr_Nfunc0_splitPD_noPreScale.root ./purity/output/purity_pp_${verName_test2[$i]}_splitPD_noPreScale.root
    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pp","'${verName_test2[$i]}'",1,0,0,1,5)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pp_${verName_test2[$i]}.log & sleep 20
    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test3[$i]}'",1,0,1,10,20)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test3[$i]}_cent1.log & sleep 20
    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test3[$i]}'",1,0,2,10,20)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test3[$i]}_cent2.log & sleep 20
    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test3[$i]}'",1,0,3,10,20)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test3[$i]}_cent3.log & sleep 20
    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test3[$i]}'",1,0,4,10,20)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test3[$i]}_cent4.log & sleep 20
#    cp ./purity/output/purity_pp_190703_temp_v31_pur_SBptDep10GeVinterval_ppPtDepCorr_pbpbPtDepCorr_Nfunc0_splitPD_noPreScale.root ./purity/output/purity_pp_${verName_test3[$i]}_splitPD_noPreScale.root
    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pp","'${verName_test3[$i]}'",1,0,0,10,20)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pp_${verName_test3[$i]}.log
    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_test2[$i]}_pbpb.root 
    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_test2[$i]}_pp.root 
    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_test2[$i]}_splitPD.root
    wait $(jobs -p)
    root -l -b -q 'purity/fitPurity_separateCent.C++("pbpb","'${verName_test2[$i]}'",2,0)' >& log/fitPurity_separateCent_pbpb_${verName_test2[$i]}_iter0.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pp","'${verName_test2[$i]}'",2,0)' >& log/fitPurity_separateCent_pp_${verName_test2[$i]}_iter0.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pbpb","'${verName_test2[$i]}'",2,1)' >& log/fitPurity_separateCent_pbpb_${verName_test2[$i]}_iter1.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pp","'${verName_test2[$i]}'",2,1)' >& log/fitPurity_separateCent_pp_${verName_test2[$i]}_iter1.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pbpb","'${verName_test2[$i]}'",2,2)' >& log/fitPurity_separateCent_pbpb_${verName_test2[$i]}_iter2.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pp","'${verName_test2[$i]}'",2,2)' >& log/fitPurity_separateCent_pp_${verName_test2[$i]}_iter2.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pbpb","'${verName_test2[$i]}'",2,3)' >& log/fitPurity_separateCent_pbpb_${verName_test2[$i]}_iter3.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pp","'${verName_test2[$i]}'",2,3)' >& log/fitPurity_separateCent_pp_${verName_test2[$i]}_iter3.log & sleep 20
#root -l -b -q 'purity/fitPurity_separateCent.C++("pbpb","'${verName_test2[$i]}'",2,1)' >& log/fitPurity_separateCent_pbpb_${verName_test2[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity_separateCent.C++("pp","'${verName_test2[$i]}'",2,1)' >& log/fitPurity_separateCent_pp_${verName_test2[$i]}.log & sleep 20
    wait $(jobs -p)
    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_test2[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_test2[$i]}.log
    source /data/ROOT-v5.34.21/bin/thisroot.sh
    python results/RooUnfold_photonRaa_v6.py ${verName_test2[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_test2[$i]}.log
    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_test2[$i]}'")' >& log/drawUnfoldingFigures_${verName_test2[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_test2[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_test2[$i]}.log
done
cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_test2}'")' >& log/plotting_v4_${verName_test2}.log



################################################################################################

for ((i=0; i< ${#verName_test3[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_test3[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_test3[$i]}.root
    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_test3[$i]}.root
#   cp ./purity/output/purity_pbpb_190703_temp_v31_pur_sidebandSigEffat85_SBcorr_centDep_noPtDep_Nfunc0_splitPD_noPreScale.root ./purity/output/purity_pbpb_${verName_test3[$i]}_splitPD_noPreScale.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test3[$i]}'",1,0,1,10,20)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test3[$i]}_cent1.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test3[$i]}'",1,0,2,10,20)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test3[$i]}_cent2.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test3[$i]}'",1,0,3,10,20)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test3[$i]}_cent3.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test3[$i]}'",1,0,4,10,20)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test3[$i]}_cent4.log & sleep 20
##    cp ./purity/output/purity_pp_190703_temp_v31_pur_SBptDep10GeVinterval_ppPtDepCorr_pbpbPtDepCorr_Nfunc0_splitPD_noPreScale.root ./purity/output/purity_pp_${verName_test3[$i]}_splitPD_noPreScale.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pp","'${verName_test3[$i]}'",1,0,0,10,20)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pp_${verName_test3[$i]}.log
    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_test3[$i]}_pbpb.root 
    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_test3[$i]}_pp.root 
    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_test3[$i]}_splitPD.root
    wait $(jobs -p)
    root -l -b -q 'purity/fitPurity_separateCent.C++("pbpb","'${verName_test3[$i]}'",2,0)' >& log/fitPurity_separateCent_pbpb_${verName_test3[$i]}_iter0.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pp","'${verName_test3[$i]}'",2,0)' >& log/fitPurity_separateCent_pp_${verName_test3[$i]}_iter0.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pbpb","'${verName_test3[$i]}'",2,1)' >& log/fitPurity_separateCent_pbpb_${verName_test3[$i]}_iter1.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pp","'${verName_test3[$i]}'",2,1)' >& log/fitPurity_separateCent_pp_${verName_test3[$i]}_iter1.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pbpb","'${verName_test3[$i]}'",2,2)' >& log/fitPurity_separateCent_pbpb_${verName_test3[$i]}_iter2.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pp","'${verName_test3[$i]}'",2,2)' >& log/fitPurity_separateCent_pp_${verName_test3[$i]}_iter2.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pbpb","'${verName_test3[$i]}'",2,3)' >& log/fitPurity_separateCent_pbpb_${verName_test3[$i]}_iter3.log & sleep 20
    root -l -b -q 'purity/fitPurity_separateCent.C++("pp","'${verName_test3[$i]}'",2,3)' >& log/fitPurity_separateCent_pp_${verName_test3[$i]}_iter3.log & sleep 20
#root -l -b -q 'purity/fitPurity_separateCent.C++("pbpb","'${verName_test3[$i]}'",2,1)' >& log/fitPurity_separateCent_pbpb_${verName_test3[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity_separateCent.C++("pp","'${verName_test3[$i]}'",2,1)' >& log/fitPurity_separateCent_pp_${verName_test3[$i]}.log & sleep 20
    wait $(jobs -p)
    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_test3[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_test3[$i]}.log
    source /data/ROOT-v5.34.21/bin/thisroot.sh
    python results/RooUnfold_photonRaa_v6.py ${verName_test3[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_test3[$i]}.log
    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_test3[$i]}'")' >& log/drawUnfoldingFigures_${verName_test3[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_test3[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_test3[$i]}.log
done
cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_test3}'")' >& log/plotting_v4_${verName_test3}.log
