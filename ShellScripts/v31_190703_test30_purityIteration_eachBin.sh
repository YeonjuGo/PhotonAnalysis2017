#!/bin/bash

verFileCopy_a=('190703_temp_v31')
verName_a=('190703_temp_v31_nominal')

#for ((i=0; i< ${#verName_a[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
####    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pbpb","'${verName_a[$i]}'")' >& log/iso_efficiency_withSkimFile_v3_pbpb_${verName_a[$i]}.log & sleep 20 
##    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_a[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_a[$i]}.log & sleep 20
###    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pbpb","'${verName_a[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pbpb_${verName_a[$i]}.log & sleep 20
####    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_a[$i]}'")' >& log/correlation_pbpb_${verName_a[$i]}.log & sleep 20
####    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_a[$i]}'",1)' >& log/correlation_pbpb_${verName_a[$i]}_splitMC.log & sleep 20 
####    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pp","'${verName_a[$i]}'")' >& log/iso_efficiency_withSkimFile_v3_pp_${verName_a[$i]}.log & sleep 20
##    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pp","'${verName_a[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pp_${verName_a[$i]}.log & sleep 20
###    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pp","'${verName_a[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pp_${verName_a[$i]}.log & sleep 20
####    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_a[$i]}'")' >& log/correlation_pp_${verName_a[$i]}.log & sleep 20 
####    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_a[$i]}'",1)' >& log/correlation_pp_${verName_a[$i]}_splitMC.log & sleep 20
####    root -l -b -q 'results/getRawDist_v8.C++("'${verName_a[$i]}'",1,1)' >& log/getRawDist_v8_${verName_a[$i]}.log & sleep 20 
##    wait $(jobs -p)
###    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_a[$i]}'",1,1)' >& log/fitPurity_pbpb_${verName_a[$i]}.log & sleep 20
###    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_a[$i]}'",1,1)' >& log/fitPurity_pp_${verName_a[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity_temp_v3.C++("pbpb","'${verName_a[$i]}'",1,1,2)' >& log/fitPurity_temp_v3_pbpb_${verName_a[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity_temp_v3.C++("pp","'${verName_a[$i]}'",1,1,2)' >& log/fitPurity_temp_v3_pp_${verName_a[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity_temp_v4.C++("pbpb","'${verName_a[$i]}'",1,1,2)' >& log/fitPurity_temp_v4_pbpb_${verName_a[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity_temp_v4.C++("pp","'${verName_a[$i]}'",1,1,2)' >& log/fitPurity_temp_v4_pp_${verName_a[$i]}.log & sleep 20
##    wait $(jobs -p)
##    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_a[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_a[$i]}.log
##    source /data/ROOT-v5.34.21/bin/thisroot.sh
##    python results/RooUnfold_photonRaa_v6.py ${verName_a[$i]} inv 0 noSplitMC >& log/RooUnfold_photonRaa_v6_${verName_a[$i]}.log
##    source /home/goyeonju/root/builddir/bin/thisroot.sh
###    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_a[$i]}'")' >& log/drawUnfoldingFigures_${verName_a[$i]}.log
######    root -l -b -q 'performance/divideTree.C++' >& log/divideTree_pbpb_20180815skim.log
###    source /data/ROOT-v5.34.21/bin/thisroot.sh
###    python results/RooUnfold_photonRaa_v6.py ${verName_a[$i]} inv 0 splitMC >& log/RooUnfold_photonRaa_v6_${verName_a[$i]}_splitMC.log
###    source /home/goyeonju/root/builddir/bin/thisroot.sh
###    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_a[$i]}'",1)' >& log/drawUnfoldingFigures_${verName_a[$i]}_splitMC.log
##    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_a[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_a[$i]}.log
##    
###     cp ./results/output/phoRaa_${preverName_a[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_a[$i]}_beforeUnfolding.root
###    root -l -b -q 'performance/compare_unfolding.C++("pbpb","'${verName_a[$i]}'")' >& log/compare_unfolding_pbpb_${verName_a[$i]}.log
###    root -l -b -q 'performance/compare_unfolding.C++("pp","'${verName_a[$i]}'")' >& log/compare_unfolding_pp_${verName_a[$i]}.log
#done
#cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_a}'")' >& log/plotting_v4_${verName_a}.log



######int yj_quickPhotonPurity_v7_iteration_eachBin(const TString coll="pp", const TString ver="phoRaaCuts_purity_forPaper", bool doSplitPD=true, bool doPreScale=0, double pt_i=20, double pt_f=25, int cent_i=0, int cent_f=10, int maxIter=10, double sideband_i=1, double sideband_f=3)


#ptBins=(20 25 30)
ptBins=(20 30 40 50 60 80 130)
length=${#ptBins[@]}
centBins=(0 10 30 50 100)

current=0
echo "$current"


#
#verFileCopy_test1=('190703_temp_v31_pur_no2012SigmaVar')
#verName_test1=('190703_temp_v31_pur_v2_maxiter5_sideband1to3_no2012SigmaVar_noBkgNorm')
#maxiter=5
#side_i=1
#side_f=3
#for ((i=0; i< ${#verName_test1[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_test1[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
##    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pbpb","'${verName_test1[$i]}'")' >& log/iso_efficiency_withSkimFile_v3_pbpb_${verName_test1[$i]}.log & sleep 20 
##    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_test1[$i]}'")' >& log/correlation_pbpb_${verName_test1[$i]}.log & sleep 20
##    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_test1[$i]}'",1)' >& log/correlation_pbpb_${verName_test1[$i]}_splitMC.log & sleep 20 
##    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pp","'${verName_test1[$i]}'")' >& log/iso_efficiency_withSkimFile_v3_pp_${verName_test1[$i]}.log & sleep 20
##    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_test1[$i]}'")' >& log/correlation_pp_${verName_test1[$i]}.log & sleep 20 
##    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_test1[$i]}'",1)' >& log/correlation_pp_${verName_test1[$i]}_splitMC.log & sleep 20
##    root -l -b -q 'results/getRawDist_v8.C++("'${verName_test1[$i]}'",1,1)' >& log/getRawDist_v8_${verName_test1[$i]}.log & sleep 20 
##    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_test1[$i]}.root
##    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_test1[$i]}.root
###   cp ./purity/output/purity_pbpb_190703_temp_v31_pur_sidebandSigEffat85_SBcorr_centDep_noPtDep_Nfunc0_splitPD_noPreScale.root ./purity/output/purity_pbpb_${verName_test1[$i]}_splitPD_noPreScale.root
#
##    current=0
##
##    for ((p=0; p< ${#ptBins[@]};p++))
##    do
##        current=$((current+1))
##        if [[ "$current" -eq "$length" ]]
##        then
##            true
##        else
##            root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pp","'${verName_test1[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}',0,0,'$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pp_${verName_test1[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}.log & sleep 20
##            for ((j=0; j< ${#centBins[@]};j++))
##            do
##                if [[ "${centBins[$((j))]}" -eq "100" ]]
##                then
##                    true
##                else
##                    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pbpb","'${verName_test1[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}','${centBins[$((j))]}','${centBins[$((j+1))]}','$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pbpb_${verName_test1[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}_cent${centBins[$((j))]}to${centBins[$((j+1))]}.log & sleep 20
##                fi
##            done
##        fi
##    done
#
##root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test1[$i]}'",1,0,1,5,10)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test1[$i]}_cent1.log & sleep 20
##    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test1[$i]}'",1,0,1,5,10)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test1[$i]}_cent1.log & sleep 20
##    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test1[$i]}'",1,0,2,5,10)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test1[$i]}_cent2.log & sleep 20
##    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test1[$i]}'",1,0,3,5,10)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test1[$i]}_cent3.log & sleep 20
##    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pbpb","'${verName_test1[$i]}'",1,0,4,5,10)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pbpb_${verName_test1[$i]}_cent4.log & sleep 20
###    cp ./purity/output/purity_pp_190703_temp_v31_pur_SBptDep10GeVinterval_ppPtDepCorr_pbpbPtDepCorr_Nfunc0_splitPD_noPreScale.root ./purity/output/purity_pp_${verName_test1[$i]}_splitPD_noPreScale.root
##    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_separateCent.C++("pp","'${verName_test1[$i]}'",1,0,0,5,10)' >& log/yj_quickPhotonPurity_v7_iteration_separateCent_noPreScale_pp_${verName_test1[$i]}.log
##    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_test1[$i]}_pbpb.root 
##    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_test1[$i]}_pp.root 
##    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_test1[$i]}_splitPD.root
##    wait $(jobs -p)
##    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test1[$i]}'",0,0)' >& log/fitPurity_eachBin_pbpb_${verName_test1[$i]}_iter0.log & sleep 20
#    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test1[$i]}'",0,4)' >& log/fitPurity_eachBin_pbpb_${verName_test1[$i]}_iter4.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin.C++("pp","'${verName_test1[$i]}'",0,0)' >& log/fitPurity_eachBin_pp_${verName_test1[$i]}_iter0.log & sleep 20
#    root -l -b -q 'purity/fitPurity_eachBin.C("pp","'${verName_test1[$i]}'",0,4)' >& log/fitPurity_eachBin_pp_${verName_test1[$i]}_iter4.log & sleep 10
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_test1[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_test1[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_test1[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_test1[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
##    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_test1[$i]}'")' >& log/drawUnfoldingFigures_${verName_test1[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_test1[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_test1[$i]}.log
#done
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_test1}'")' >& log/plotting_v4_${verName_test1}.log
##
#
#
#
#verFileCopy_test2=('190703_temp_v31_pur_no2012SigmaVar')
#verName_test2=('190703_temp_v31_pur_v2_maxiter5_sideband1to5_no2012SigmaVar_noBkgNorm')
#maxiter=5
#side_i=1
#side_f=5
#for ((i=0; i< ${#verName_test2[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_test2[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
##    cp ./efficiency/output/pbpb_iso_efficiency_${verName_test1[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_test2[$i]}.root
##    cp ./efficiency/output/pp_iso_efficiency_${verName_test1[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_test2[$i]}.root
###   cp ./purity/output/purity_pbpb_190703_temp_v31_pur_sidebandSigEffat85_SBcorr_centDep_noPtDep_Nfunc0_splitPD_noPreScale.root ./purity/output/purity_pbpb_${verName_test2[$i]}_splitPD_noPreScale.root
##
##    current=0
##    for ((p=0; p< ${#ptBins[@]};p++))
##    do
##        current=$((current+1))
##        if [[ "$current" -eq "$length" ]]
##        then
##            true
##        else
##            root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pp","'${verName_test2[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}',0,0,'$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pp_${verName_test2[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}.log & sleep 10
##            for ((j=0; j< ${#centBins[@]};j++))
##            do
##                if [[ "${centBins[$((j))]}" -eq "100" ]]
##                then
##                    true
##                else
##                    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pbpb","'${verName_test2[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}','${centBins[$((j))]}','${centBins[$((j+1))]}','$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pbpb_${verName_test2[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}_cent${centBins[$((j))]}to${centBins[$((j+1))]}.log & sleep 10
##                fi
##            done
##        fi
##    done
##
##    cp ./performance/output/correlation_genPt_recoPt_${verName_test1[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_test2[$i]}_pbpb.root 
##    cp ./performance/output/correlation_genPt_recoPt_${verName_test1[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_test2[$i]}_pp.root 
##    cp ./results/output/rawDist_${verName_test1[$i]}_splitPD.root ./results/output/rawDist_${verName_test2[$i]}_splitPD.root
##    wait $(jobs -p)
##    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test2[$i]}'",0,0)' >& log/fitPurity_eachBin_pbpb_${verName_test2[$i]}_iter0.log & sleep 10
#    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test2[$i]}'",0,1)' >& log/fitPurity_eachBin_pbpb_${verName_test2[$i]}_iter1.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test2[$i]}'",0,4)' >& log/fitPurity_eachBin_pbpb_${verName_test2[$i]}_iter4.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin.C++("pp","'${verName_test2[$i]}'",0,0)' >& log/fitPurity_eachBin_pp_${verName_test2[$i]}_iter0.log & sleep 10
#    root -l -b -q 'purity/fitPurity_eachBin.C("pp","'${verName_test2[$i]}'",0,1)' >& log/fitPurity_eachBin_pp_${verName_test2[$i]}_iter1.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin.C("pp","'${verName_test2[$i]}'",0,4)' >& log/fitPurity_eachBin_pp_${verName_test2[$i]}_iter4.log & sleep 10
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_test2[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_test2[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_test2[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_test2[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_test2[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_test2[$i]}.log
#done
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_test2}'")' >& log/plotting_v4_${verName_test2}.log
#
##verFileCopy_test8=('190703_temp_v31_pur_no2012SigmaVar')
##verName_test8=('190703_temp_v31_pur_v2_maxiter5_sideband1to7_no2012SigmaVar_noBkgNorm')
##maxiter=5
##side_i=1
##side_f=7
##for ((i=0; i< ${#verName_test8[@]};i++))
##do
##    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_test8[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
##    cp ./efficiency/output/pbpb_iso_efficiency_${verName_test1[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_test8[$i]}.root
##    cp ./efficiency/output/pp_iso_efficiency_${verName_test1[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_test8[$i]}.root
###   cp ./purity/output/purity_pbpb_190703_temp_v31_pur_sidebandSigEffat85_SBcorr_centDep_noPtDep_Nfunc0_splitPD_noPreScale.root ./purity/output/purity_pbpb_${verName_test8[$i]}_splitPD_noPreScale.root
##
##    current=0
##    for ((p=0; p< ${#ptBins[@]};p++))
##    do
##        current=$((current+1))
##        if [[ "$current" -eq "$length" ]]
##        then
##            true
##        else
##            root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pp","'${verName_test8[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}',0,0,'$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pp_${verName_test8[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}.log & sleep 10
##            for ((j=0; j< ${#centBins[@]};j++))
##            do
##                if [[ "${centBins[$((j))]}" -eq "100" ]]
##                then
##                    true
##                else
##                    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pbpb","'${verName_test8[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}','${centBins[$((j))]}','${centBins[$((j+1))]}','$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pbpb_${verName_test8[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}_cent${centBins[$((j))]}to${centBins[$((j+1))]}.log & sleep 10
##                fi
##            done
##        fi
##    done
##
##    cp ./performance/output/correlation_genPt_recoPt_${verName_test1[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_test8[$i]}_pbpb.root 
##    cp ./performance/output/correlation_genPt_recoPt_${verName_test1[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_test8[$i]}_pp.root 
##    cp ./results/output/rawDist_${verName_test1[$i]}_splitPD.root ./results/output/rawDist_${verName_test8[$i]}_splitPD.root
##    wait $(jobs -p)
###    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test8[$i]}'",0,0)' >& log/fitPurity_eachBin_pbpb_${verName_test8[$i]}_iter0.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test8[$i]}'",0,4)' >& log/fitPurity_eachBin_pbpb_${verName_test8[$i]}_iter4.log & sleep 10
###    root -l -b -q 'purity/fitPurity_eachBin.C++("pp","'${verName_test8[$i]}'",0,0)' >& log/fitPurity_eachBin_pp_${verName_test8[$i]}_iter0.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin.C("pp","'${verName_test8[$i]}'",0,4)' >& log/fitPurity_eachBin_pp_${verName_test8[$i]}_iter4.log & sleep 10
##    wait $(jobs -p)
##    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_test8[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_test8[$i]}.log
##    source /data/ROOT-v5.34.21/bin/thisroot.sh
##    python results/RooUnfold_photonRaa_v6.py ${verName_test8[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_test8[$i]}.log
##    source /home/goyeonju/root/builddir/bin/thisroot.sh
##    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_test8[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_test8[$i]}.log
##done
##root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_test8}'")' >& log/plotting_v4_${verName_test8}.log
##
##
##verFileCopy_test8=('190703_temp_v31_pur_no2012SigmaVar')
##verName_test8=('190703_temp_v31_pur_v2_maxiter5_sideband5to10_no2012SigmaVar_noBkgNorm')
##maxiter=5
##side_i=5
##side_f=10
##for ((i=0; i< ${#verName_test8[@]};i++))
##do
##    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_test8[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
##    cp ./efficiency/output/pbpb_iso_efficiency_${verName_test1[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_test8[$i]}.root
##    cp ./efficiency/output/pp_iso_efficiency_${verName_test1[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_test8[$i]}.root
###   cp ./purity/output/purity_pbpb_190703_temp_v31_pur_sidebandSigEffat85_SBcorr_centDep_noPtDep_Nfunc0_splitPD_noPreScale.root ./purity/output/purity_pbpb_${verName_test8[$i]}_splitPD_noPreScale.root
##
##    current=0
##    for ((p=0; p< ${#ptBins[@]};p++))
##    do
##        current=$((current+1))
##        if [[ "$current" -eq "$length" ]]
##        then
##            true
##        else
##            root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pp","'${verName_test8[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}',0,0,'$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pp_${verName_test8[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}.log & sleep 10
##            for ((j=0; j< ${#centBins[@]};j++))
##            do
##                if [[ "${centBins[$((j))]}" -eq "100" ]]
##                then
##                    true
##                else
##                    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pbpb","'${verName_test8[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}','${centBins[$((j))]}','${centBins[$((j+1))]}','$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pbpb_${verName_test8[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}_cent${centBins[$((j))]}to${centBins[$((j+1))]}.log & sleep 10
##                fi
##            done
##        fi
##    done
##
##    cp ./performance/output/correlation_genPt_recoPt_${verName_test1[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_test8[$i]}_pbpb.root 
##    cp ./performance/output/correlation_genPt_recoPt_${verName_test1[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_test8[$i]}_pp.root 
##    cp ./results/output/rawDist_${verName_test1[$i]}_splitPD.root ./results/output/rawDist_${verName_test8[$i]}_splitPD.root
##    wait $(jobs -p)
###    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test8[$i]}'",0,0)' >& log/fitPurity_eachBin_pbpb_${verName_test8[$i]}_iter0.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test8[$i]}'",0,4)' >& log/fitPurity_eachBin_pbpb_${verName_test8[$i]}_iter4.log & sleep 10
###    root -l -b -q 'purity/fitPurity_eachBin.C++("pp","'${verName_test8[$i]}'",0,0)' >& log/fitPurity_eachBin_pp_${verName_test8[$i]}_iter0.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin.C("pp","'${verName_test8[$i]}'",0,4)' >& log/fitPurity_eachBin_pp_${verName_test8[$i]}_iter4.log & sleep 10
##    wait $(jobs -p)
##    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_test8[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_test8[$i]}.log
##    source /data/ROOT-v5.34.21/bin/thisroot.sh
##    python results/RooUnfold_photonRaa_v6.py ${verName_test8[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_test8[$i]}.log
##    source /home/goyeonju/root/builddir/bin/thisroot.sh
##    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_test8[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_test8[$i]}.log
##done
##root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_test8}'")' >& log/plotting_v4_${verName_test8}.log


verFileCopy_test10=('190703_temp_v31')
verName_test10=('190703_temp_v31_pur_v2_maxiter5_sideband1to3_coarsePurBins')
maxiter=5
side_i=1
side_f=3
ptBins=(20 30 40 50 60 80 130)
length=${#ptBins[@]}
centBins=(0 30 100)
#centBins=(0 10 30 50 100)
#for ((i=0; i< ${#verName_test10[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_test10[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
##    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_test10[$i]}.root
##    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_test10[$i]}.root
##
##    current=0
##    for ((p=0; p< ${#ptBins[@]};p++))
##    do
##        current=$((current+1))
##        if [[ "$current" -eq "$length" ]]
##        then
##            true
##        else
##            root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pp","'${verName_test10[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}',0,0,'$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pp_${verName_test10[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}.log & sleep 10
##            for ((j=0; j< ${#centBins[@]};j++))
##            do
##                if [[ "${centBins[$((j))]}" -eq "100" ]]
##                then
##                    true
##                else
##                    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pbpb","'${verName_test10[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}','${centBins[$((j))]}','${centBins[$((j+1))]}','$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pbpb_${verName_test10[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}_cent${centBins[$((j))]}to${centBins[$((j+1))]}.log & sleep 10
##                fi
##            done
##        fi
##    done
##    wait $(jobs -p)
##
###     root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pbpb","'${verName_test10[$i]}'",1,0,20,25,0,10,'$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pbpb_${verName_test10[$i]}_pt30to40_cent0to10.log & sleep 10
###     root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pbpb","'${verName_test10[$i]}'",1,0,50,60,10,30,'$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pbpb_${verName_test10[$i]}_pt50to60_cent10to30.log & sleep 10
##    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_test10[$i]}_pbpb.root 
##    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_test10[$i]}_pp.root 
##    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_test10[$i]}_splitPD.root
#    wait $(jobs -p)
##    root -l -b -q 'purity/fitPurity_eachBin_temp_centComb.C("pbpb","'${verName_test10[$i]}'",0,0)' >& log/fitPurity_eachBin_centComb_pbpb_${verName_test10[$i]}_iter0.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin_temp_centComb.C("pbpb","'${verName_test10[$i]}'",0,1)' >& log/fitPurity_eachBin_pbpb_${verName_test10[$i]}_iter1.log & sleep 10
#    root -l -b -q 'purity/fitPurity_eachBin_temp_centComb.C("pbpb","'${verName_test10[$i]}'",0,4)' >& log/fitPurity_eachBin_centComb_pbpb_${verName_test10[$i]}_iter4.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin_temp_centComb.C++("pp","'${verName_test10[$i]}'",0,0)' >& log/fitPurity_eachBin_centComb_pp_${verName_test10[$i]}_iter0.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin_temp_centComb.C++("pp","'${verName_test10[$i]}'",0,1)' >& log/fitPurity_eachBin_pp_${verName_test10[$i]}_iter1.log & sleep 10
#    root -l -b -q 'purity/fitPurity_eachBin_temp_centComb.C("pp","'${verName_test10[$i]}'",0,4)' >& log/fitPurity_eachBin_centComb_pp_${verName_test10[$i]}_iter4.log & sleep 10
#
##    root -l -b -q 'purity/fitPurity_eachBin_temp.C("pbpb","'${verName_test10[$i]}'",0,1)' >& log/fitPurity_eachBin_pbpb_${verName_test10[$i]}_iter1.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin_temp.C("pbpb","'${verName_test10[$i]}'",0,4)' >& log/fitPurity_eachBin_pbpb_${verName_test10[$i]}_iter4.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin_temp.C++("pp","'${verName_test10[$i]}'",0,1)' >& log/fitPurity_eachBin_pp_${verName_test10[$i]}_iter1.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin_temp.C("pp","'${verName_test10[$i]}'",0,4)' >& log/fitPurity_eachBin_pp_${verName_test10[$i]}_iter4.log & sleep 10
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_test10[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_test10[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_test10[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_test10[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_test10[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_test10[$i]}.log
#done
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_test10}'")' >& log/plotting_v4_${verName_test10}.log

#verFileCopy_test10=('190703_temp_v31')
#verName_test10=('190703_temp_v31_pur_v2_maxiter5_sideband1to5_sigShiftFloat')
#maxiter=5
#side_i=1
#side_f=5
#for ((i=0; i< ${#verName_test10[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_test10[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#   cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_test10[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_test10[$i]}.root
#
#    current=0
#    for ((p=0; p< ${#ptBins[@]};p++))
#    do
#        current=$((current+1))
#        if [[ "$current" -eq "$length" ]]
#        then
#            true
#        else
#            root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pp","'${verName_test10[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}',0,0,'$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pp_${verName_test10[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}.log & sleep 10
#            for ((j=0; j< ${#centBins[@]};j++))
#            do
#                if [[ "${centBins[$((j))]}" -eq "100" ]]
#                then
#                    true
#                else
#                    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pbpb","'${verName_test10[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}','${centBins[$((j))]}','${centBins[$((j+1))]}','$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pbpb_${verName_test10[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}_cent${centBins[$((j))]}to${centBins[$((j+1))]}.log & sleep 10
#                fi
#            done
#        fi
#    done
#    wait $(jobs -p)
#
##     root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pbpb","'${verName_test10[$i]}'",1,0,20,25,0,10,'$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pbpb_${verName_test10[$i]}_pt30to40_cent0to10.log & sleep 10
##     root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pbpb","'${verName_test10[$i]}'",1,0,50,60,10,30,'$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pbpb_${verName_test10[$i]}_pt50to60_cent10to30.log & sleep 10
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_test10[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_test10[$i]}_pp.root 
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_test10[$i]}_splitPD.root
#    wait $(jobs -p)
##    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test10[$i]}'",0,0)' >& log/fitPurity_eachBin_pbpb_${verName_test10[$i]}_iter0.log & sleep 10
#    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test10[$i]}'",0,1)' >& log/fitPurity_eachBin_pbpb_${verName_test10[$i]}_iter1.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test10[$i]}'",0,4)' >& log/fitPurity_eachBin_pbpb_${verName_test10[$i]}_iter4.log & sleep 10
#    root -l -b -q 'purity/fitPurity_eachBin.C++("pp","'${verName_test10[$i]}'",0,1)' >& log/fitPurity_eachBin_pp_${verName_test10[$i]}_iter1.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin.C++("pp","'${verName_test10[$i]}'",0,0)' >& log/fitPurity_eachBin_pp_${verName_test10[$i]}_iter0.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin.C("pp","'${verName_test10[$i]}'",0,4)' >& log/fitPurity_eachBin_pp_${verName_test10[$i]}_iter4.log & sleep 10
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_test10[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_test10[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_test10[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_test10[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_test10[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_test10[$i]}.log
#done
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_test10}'")' >& log/plotting_v4_${verName_test10}.log
#

verFileCopy_test12=('190703_temp_v31')
verName_test12=('190703_temp_v31_pur_v2_impurityCorr_sideband1to5')

#ptBins=(20 30)
ptBins=(20 30 40 50 60 80 130)
length=${#ptBins[@]}
#centBins=(0 30)
centBins=(0 10 30 50 100)

maxiter=5
side_i=1
side_f=5
for ((i=0; i< ${#verName_test12[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_test12[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#   cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_test12[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_test12[$i]}.root
###
#    current=0
#    for ((p=0; p< ${#ptBins[@]};p++))
#    do
#        current=$((current+1))
#        if [[ "$current" -eq "$length" ]]
#        then
#            true
#        else
#            root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2_impurity.C("pp","'${verName_test12[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}',0,0,'$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pp_${verName_test12[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}.log & sleep 10
#            for ((j=0; j< ${#centBins[@]};j++))
#            do
#                if [[ "${centBins[$((j))]}" -eq "100" ]]
#                then
#                    true
#                else
#                    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2_impurity.C("pbpb","'${verName_test12[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}','${centBins[$((j))]}','${centBins[$((j+1))]}','$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pbpb_${verName_test12[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}_cent${centBins[$((j))]}to${centBins[$((j+1))]}.log & sleep 10
#                fi
#            done
#        fi
#    done
#
##    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2_temp.C("pbpb","'${verName_test12[$i]}'",1,0,60,80,0,30,'$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pbpb_${verName_test12[$i]}_pt60to80_cent0to30.log & sleep 10
##     root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2_temp.C("pbpb","'${verName_test12[$i]}'",1,0,50,60,30,50,'$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pbpb_${verName_test12[$i]}_pt50to60_cent30to50.log & sleep 10
    wait $(jobs -p)
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_test12[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_test12[$i]}_pp.root 
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_test12[$i]}_splitPD.root
    wait $(jobs -p)
#    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test12[$i]}'",0,0)' >& log/fitPurity_eachBin_pbpb_${verName_test12[$i]}_iter0.log & sleep 10
    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test12[$i]}'",0,1)' >& log/fitPurity_eachBin_pbpb_${verName_test12[$i]}_iter1.log & sleep 10
#    root -l -b -q 'purity/fitPurity_eachBin_temp_centComb.C("pbpb","'${verName_test12[$i]}'",0,1)' >& log/fitPurity_eachBin_pbpb_${verName_test12[$i]}_iter4.log & sleep 10
    root -l -b -q 'purity/fitPurity_eachBin.C++("pp","'${verName_test12[$i]}'",0,1)' >& log/fitPurity_eachBin_pp_${verName_test12[$i]}_iter1.log & sleep 10
#    root -l -b -q 'purity/fitPurity_eachBin.C++("pp","'${verName_test12[$i]}'",0,0)' >& log/fitPurity_eachBin_pp_${verName_test12[$i]}_iter0.log & sleep 10
#    root -l -b -q 'purity/fitPurity_eachBin_temp_centComb.C("pp","'${verName_test12[$i]}'",0,1)' >& log/fitPurity_eachBin_pp_${verName_test12[$i]}_iter4.log & sleep 10
    wait $(jobs -p)
    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_test12[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_test12[$i]}.log
    source /data/ROOT-v5.34.21/bin/thisroot.sh
    python results/RooUnfold_photonRaa_v6.py ${verName_test12[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_test12[$i]}.log
    source /home/goyeonju/root/builddir/bin/thisroot.sh
    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_test12[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_test12[$i]}.log
done
root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_test12}'")' >& log/plotting_v4_${verName_test12}.log
#
#
#verFileCopy_test3=('190703_temp_v31')
#verName_test3=('190703_temp_v31_pur_v2_maxiter5_sideband1to5')
#
##ptBins=(20 30)
#ptBins=(20 30 40 50 60 80 130)
#length=${#ptBins[@]}
#centBins=(0 30)
##centBins=(0 10 30 50 100)
#
#maxiter=5
#side_i=1
#side_f=5
#for ((i=0; i< ${#verName_test3[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_test3[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
##   cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_test3[$i]}.root
##    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_test3[$i]}.root
###
##    current=0
##    for ((p=0; p< ${#ptBins[@]};p++))
##    do
##        current=$((current+1))
##        if [[ "$current" -eq "$length" ]]
##        then
##            true
##        else
##            root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pp","'${verName_test3[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}',0,0,'$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pp_${verName_test3[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}.log & sleep 10
##            for ((j=0; j< ${#centBins[@]};j++))
##            do
##                if [[ "${centBins[$((j))]}" -eq "100" ]]
##                then
##                    true
##                else
##                    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pbpb","'${verName_test3[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}','${centBins[$((j))]}','${centBins[$((j+1))]}','$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pbpb_${verName_test3[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}_cent${centBins[$((j))]}to${centBins[$((j+1))]}.log & sleep 10
##                fi
##            done
##        fi
##    done
##
#     root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2_temp.C("pbpb","'${verName_test3[$i]}'",1,0,60,80,0,30,'$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pbpb_${verName_test3[$i]}_pt60to80_cent0to30.log & sleep 10
##     root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2_temp.C("pbpb","'${verName_test3[$i]}'",1,0,50,60,30,50,'$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pbpb_${verName_test3[$i]}_pt50to60_cent30to50.log & sleep 10
##    wait $(jobs -p)
##    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_test3[$i]}_pbpb.root 
##    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_test3[$i]}_pp.root 
##    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_test3[$i]}_splitPD.root
#    wait $(jobs -p)
##    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test3[$i]}'",0,0)' >& log/fitPurity_eachBin_pbpb_${verName_test3[$i]}_iter0.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test3[$i]}'",0,1)' >& log/fitPurity_eachBin_pbpb_${verName_test3[$i]}_iter1.log & sleep 10
#    root -l -b -q 'purity/fitPurity_eachBin_temp_centComb.C("pbpb","'${verName_test3[$i]}'",0,1)' >& log/fitPurity_eachBin_pbpb_${verName_test3[$i]}_iter4.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin.C++("pp","'${verName_test3[$i]}'",0,1)' >& log/fitPurity_eachBin_pp_${verName_test3[$i]}_iter1.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin.C++("pp","'${verName_test3[$i]}'",0,0)' >& log/fitPurity_eachBin_pp_${verName_test3[$i]}_iter0.log & sleep 10
#    root -l -b -q 'purity/fitPurity_eachBin_temp_centComb.C("pp","'${verName_test3[$i]}'",0,1)' >& log/fitPurity_eachBin_pp_${verName_test3[$i]}_iter4.log & sleep 10
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_test3[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_test3[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_test3[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_test3[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_test3[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_test3[$i]}.log
#done
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_test3}'")' >& log/plotting_v4_${verName_test3}.log
##
##
#
##verFileCopy_test4=('190703_temp_v31')
##verName_test4=('190703_temp_v31_pur_v2_maxiter5_sideband1to3')
##
##maxiter=5
##side_i=1
##side_f=3
##for ((i=0; i< ${#verName_test4[@]};i++))
##do
##    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_test4[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
###    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_test4[$i]}.root
###    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_test4[$i]}.root
###
###    current=0
###    for ((p=0; p< ${#ptBins[@]};p++))
###    do
###        current=$((current+1))
###        if [[ "$current" -eq "$length" ]]
###        then
###            true
###        else
###            root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pp","'${verName_test4[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}',0,0,'$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pp_${verName_test4[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}.log & sleep 10
###            for ((j=0; j< ${#centBins[@]};j++))
###            do
###                if [[ "${centBins[$((j))]}" -eq "100" ]]
###                then
###                    true
###                else
###                    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pbpb","'${verName_test4[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}','${centBins[$((j))]}','${centBins[$((j+1))]}','$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pbpb_${verName_test4[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}_cent${centBins[$((j))]}to${centBins[$((j+1))]}.log & sleep 10
###                fi
###            done
###        fi
###    done
###    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_test4[$i]}_pbpb.root 
###    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_test4[$i]}_pp.root 
###    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_test4[$i]}_splitPD.root
###    wait $(jobs -p)
###    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test4[$i]}'",0,0)' >& log/fitPurity_eachBin_pbpb_${verName_test4[$i]}_iter0.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test4[$i]}'",0,4)' >& log/fitPurity_eachBin_pbpb_${verName_test4[$i]}_iter4.log & sleep 10
###    root -l -b -q 'purity/fitPurity_eachBin.C++("pp","'${verName_test4[$i]}'",0,0)' >& log/fitPurity_eachBin_pp_${verName_test4[$i]}_iter0.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin.C("pp","'${verName_test4[$i]}'",0,4)' >& log/fitPurity_eachBin_pp_${verName_test4[$i]}_iter4.log & sleep 10
##    wait $(jobs -p)
##    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_test4[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_test4[$i]}.log
##    source /data/ROOT-v5.34.21/bin/thisroot.sh
##    python results/RooUnfold_photonRaa_v6.py ${verName_test4[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_test4[$i]}.log
##    source /home/goyeonju/root/builddir/bin/thisroot.sh
##    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_test4[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_test4[$i]}.log
##done
##root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_test4}'")' >& log/plotting_v4_${verName_test4}.log
##
##
##
##
##verFileCopy_test5=('190703_temp_v31')
##verName_test5=('190703_temp_v31_pur_v2_maxiter5_sideband1to7')
##
##maxiter=5
##side_i=1
##side_f=7
##for ((i=0; i< ${#verName_test5[@]};i++))
##do
##    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_test5[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
##    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_test5[$i]}.root
##    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_test5[$i]}.root
##
##    current=0
##    for ((p=0; p< ${#ptBins[@]};p++))
##    do
##        current=$((current+1))
##        if [[ "$current" -eq "$length" ]]
##        then
##            true
##        else
##            root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pp","'${verName_test5[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}',0,0,'$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pp_${verName_test5[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}.log & sleep 10
##            for ((j=0; j< ${#centBins[@]};j++))
##            do
##                if [[ "${centBins[$((j))]}" -eq "100" ]]
##                then
##                    true
##                else
##                    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pbpb","'${verName_test5[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}','${centBins[$((j))]}','${centBins[$((j+1))]}','$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pbpb_${verName_test5[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}_cent${centBins[$((j))]}to${centBins[$((j+1))]}.log & sleep 10
##                fi
##            done
##        fi
##    done
##
##    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_test5[$i]}_pbpb.root 
##    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_test5[$i]}_pp.root 
##    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_test5[$i]}_splitPD.root
##    wait $(jobs -p)
###    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test5[$i]}'",0,0)' >& log/fitPurity_eachBin_pbpb_${verName_test5[$i]}_iter0.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test5[$i]}'",0,4)' >& log/fitPurity_eachBin_pbpb_${verName_test5[$i]}_iter4.log & sleep 10
###    root -l -b -q 'purity/fitPurity_eachBin.C++("pp","'${verName_test5[$i]}'",0,0)' >& log/fitPurity_eachBin_pp_${verName_test5[$i]}_iter0.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin.C("pp","'${verName_test5[$i]}'",0,4)' >& log/fitPurity_eachBin_pp_${verName_test5[$i]}_iter4.log & sleep 10
##    wait $(jobs -p)
##    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_test5[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_test5[$i]}.log
##    source /data/ROOT-v5.34.21/bin/thisroot.sh
##    python results/RooUnfold_photonRaa_v6.py ${verName_test5[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_test5[$i]}.log
##    source /home/goyeonju/root/builddir/bin/thisroot.sh
##    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_test5[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_test5[$i]}.log
##done
##root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_test5}'")' >& log/plotting_v4_${verName_test5}.log
##
##
##verFileCopy_test6=('190703_temp_v31')
##verName_test6=('190703_temp_v31_pur_v2_maxiter5_sideband3to7')
##
##maxiter=5
##side_i=3
##side_f=7
##for ((i=0; i< ${#verName_test6[@]};i++))
##do
##    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_test6[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
##    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_test6[$i]}.root
##    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_test6[$i]}.root
##
##    current=0
##    for ((p=0; p< ${#ptBins[@]};p++))
##    do
##        current=$((current+1))
##        if [[ "$current" -eq "$length" ]]
##        then
##            true
##        else
##            root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pp","'${verName_test6[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}',0,0,'$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pp_${verName_test6[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}.log & sleep 10
##            for ((j=0; j< ${#centBins[@]};j++))
##            do
##                if [[ "${centBins[$((j))]}" -eq "100" ]]
##                then
##                    true
##                else
##                    root -l -b -q 'purity/yj_quickPhotonPurity_v7_iteration_eachBin_v2.C("pbpb","'${verName_test6[$i]}'",1,0,'${ptBins[$((p))]}','${ptBins[$((p+1))]}','${centBins[$((j))]}','${centBins[$((j+1))]}','$maxiter','$side_i','$side_f')' >& log/yj_quickPhotonPurity_v7_iteration_eachBin_pbpb_${verName_test6[$i]}_pt${ptBins[$((p))]}to${ptBins[$((p+1))]}_cent${centBins[$((j))]}to${centBins[$((j+1))]}.log & sleep 10
##                fi
##            done
##        fi
##    done
##
##    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_test6[$i]}_pbpb.root 
##    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_test6[$i]}_pp.root 
##    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_test6[$i]}_splitPD.root
##    wait $(jobs -p)
###    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test6[$i]}'",0,0)' >& log/fitPurity_eachBin_pbpb_${verName_test6[$i]}_iter0.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin.C("pbpb","'${verName_test6[$i]}'",0,4)' >& log/fitPurity_eachBin_pbpb_${verName_test6[$i]}_iter4.log & sleep 10
###    root -l -b -q 'purity/fitPurity_eachBin.C++("pp","'${verName_test6[$i]}'",0,0)' >& log/fitPurity_eachBin_pp_${verName_test6[$i]}_iter0.log & sleep 10
##    root -l -b -q 'purity/fitPurity_eachBin.C("pp","'${verName_test6[$i]}'",0,4)' >& log/fitPurity_eachBin_pp_${verName_test6[$i]}_iter4.log & sleep 10
##    wait $(jobs -p)
##    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_test6[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_test6[$i]}.log
##    source /data/ROOT-v5.34.21/bin/thisroot.sh
##    python results/RooUnfold_photonRaa_v6.py ${verName_test6[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_test6[$i]}.log
##    source /home/goyeonju/root/builddir/bin/thisroot.sh
##    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_test6[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_test6[$i]}.log
##done
##root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_test6}'")' >& log/plotting_v4_${verName_test6}.log
##
