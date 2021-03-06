#!/bin/bash
#int yj_quickPhotonPurity_v3(const TString coll="pbpb", const TString ver="phoRaaCuts_purity_forPaper", bool doSplitPD=true, bool doPreScale=0, bool useSBcorr=0, bool noCentDepCorr=0, bool useMCSB=0){
#verFileCopy_a=('1800802_temp_v20')

verFileCopy_a=('190703_temp_v31')
verName_a=('190703_temp_v31_nominal')
preverName_a=('190220_temp_v26_nominal')

for ((i=0; i< ${#verName_a[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
##    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pbpb","'${verName_a[$i]}'")' >& log/iso_efficiency_withSkimFile_v3_pbpb_${verName_a[$i]}.log & sleep 20 
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_a[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_a[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pbpb","'${verName_a[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pbpb_${verName_a[$i]}.log & sleep 20
##    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_a[$i]}'")' >& log/correlation_pbpb_${verName_a[$i]}.log & sleep 20
##    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_a[$i]}'",1)' >& log/correlation_pbpb_${verName_a[$i]}_splitMC.log & sleep 20 
##    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pp","'${verName_a[$i]}'")' >& log/iso_efficiency_withSkimFile_v3_pp_${verName_a[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_a[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_a[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pp","'${verName_a[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pp_${verName_a[$i]}.log & sleep 20
##    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_a[$i]}'")' >& log/correlation_pp_${verName_a[$i]}.log & sleep 20 
##    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_a[$i]}'",1)' >& log/correlation_pp_${verName_a[$i]}_splitMC.log & sleep 20
##    root -l -b -q 'results/getRawDist_v8.C++("'${verName_a[$i]}'",1,1)' >& log/getRawDist_v8_${verName_a[$i]}.log & sleep 20 
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


verFileCopy_test1=('190703_temp_v31_sigSumIso5_sideband5to15')
verName_test1=('190703_temp_v31_sigSumIso5_sideband5to15')
preverName_test1=('190220_temp_v26_nominal')

verFileCopy_test2=('190703_temp_v31_sigSumIso5_sideband10to20')
verName_test2=('190703_temp_v31_sigSumIso5_sideband10to20')
preverName_test2=('190220_temp_v26_nominal')

for ((i=0; i< ${#verName_test1[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_test1[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pbpb","'${verName_test1[$i]}'")' >& log/iso_efficiency_withSkimFile_v3_pbpb_${verName_test1[$i]}.log & sleep 5 
    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_test1[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_test1[$i]}.log & sleep 20
    root -l -b -q 'purity/yj_quickPhotonPurity_v3_sideband10to20.C++("pbpb","'${verName_test2[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_test2[$i]}.log & sleep 20
    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_test1[$i]}'")' >& log/correlation_pbpb_${verName_test1[$i]}.log & sleep 20
    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_test1[$i]}'",1)' >& log/correlation_pbpb_${verName_test1[$i]}_splitMC.log & sleep 20 
    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pp","'${verName_test1[$i]}'")' >& log/iso_efficiency_withSkimFile_v3_pp_${verName_test1[$i]}.log & sleep 20
    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_test1[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_test1[$i]}.log & sleep 20
    root -l -b -q 'purity/yj_quickPhotonPurity_v3_sideband10to20.C++("pp","'${verName_test2[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_test2[$i]}.log & sleep 20
    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_test1[$i]}'")' >& log/correlation_pp_${verName_test1[$i]}.log & sleep 20 
    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_test1[$i]}'",1)' >& log/correlation_pp_${verName_test1[$i]}_splitMC.log & sleep 20
    root -l -b -q 'results/getRawDist_v8.C++("'${verName_test1[$i]}'",1,1)' >& log/getRawDist_v8_${verName_test1[$i]}.log & sleep 20 
    wait $(jobs -p)
    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_test1[$i]}'",0,1)' >& log/fitPurity_pbpb_${verName_test1[$i]}.log & sleep 20
    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_test1[$i]}'",0,1)' >& log/fitPurity_pp_${verName_test1[$i]}.log & sleep 20
    wait $(jobs -p)
    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_test1[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_test1[$i]}.log
    source /data/ROOT-v5.34.21/bin/thisroot.sh
    python results/RooUnfold_photonRaa_v6.py ${verName_test1[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_test1[$i]}.log
    source /home/goyeonju/root/builddir/bin/thisroot.sh
    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_test1[$i]}'")' >& log/drawUnfoldingFigures_${verName_test1[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_test1[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_test1[$i]}.log
done
cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_test1}'")' >& log/plotting_v4_${verName_test1}.log


for ((i=0; i< ${#verName_test2[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_test2[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    cp ./efficiency/output/pbpb_iso_efficiency_${verName_test1[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_test2[$i]}.root
    cp ./efficiency/output/pp_iso_efficiency_${verName_test1[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_test2[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_test2[$i]}'",1,0,1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_SBcorr_centDepCorr_pbpb_${verName_test2[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_test2[$i]}'",1,0,1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_SBcorr_centDepCorr_pp_${verName_test2[$i]}.log
    cp ./performance/output/correlation_genPt_recoPt_${verName_test1[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_test2[$i]}_pbpb.root 
    cp ./performance/output/correlation_genPt_recoPt_${verName_test1[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_test2[$i]}_pp.root 
    cp ./results/output/rawDist_${verName_test1[$i]}_splitPD.root ./results/output/rawDist_${verName_test2[$i]}_splitPD.root
    wait $(jobs -p)
    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_test2[$i]}'",1,1)' >& log/fitPurity_pbpb_${verName_test2[$i]}.log & sleep 20
    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_test2[$i]}'",1,1)' >& log/fitPurity_pp_${verName_test2[$i]}.log & sleep 20
    wait $(jobs -p)
    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_test2[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_test2[$i]}.log
    source /data/ROOT-v5.34.21/bin/thisroot.sh
    python results/RooUnfold_photonRaa_v6.py ${verName_test2[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_test2[$i]}.log
    source /home/goyeonju/root/builddir/bin/thisroot.sh
    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_test2[$i]}'")' >& log/drawUnfoldingFigures_${verName_test2[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_test2[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_test2[$i]}.log
done
cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_test2}'")' >& log/plotting_v4_${verName_test2}.log




verFileCopy_test3=('190703_temp_v31_sigSumIso3_sideband3to13')
verName_test3=('190703_temp_v31_sigSumIso3_sideband3to13')
preverName_test3=('190220_temp_v26_nominal')

verFileCopy_test4=('190703_temp_v31_sigSumIso3_sideband10to20')
verName_test4=('190703_temp_v31_sigSumIso3_sideband10to20')
preverName_test4=('190220_temp_v26_nominal')

for ((i=0; i< ${#verName_test3[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_test3[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pbpb","'${verName_test3[$i]}'")' >& log/iso_efficiency_withSkimFile_v3_pbpb_${verName_test3[$i]}.log & sleep 5 
    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_test3[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_test3[$i]}.log & sleep 20
    root -l -b -q 'purity/yj_quickPhotonPurity_v3_sideband10to20.C++("pbpb","'${verName_test4[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_test4[$i]}.log & sleep 20
    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_test3[$i]}'")' >& log/correlation_pbpb_${verName_test3[$i]}.log & sleep 20
    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_test3[$i]}'",1)' >& log/correlation_pbpb_${verName_test3[$i]}_splitMC.log & sleep 20 
    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pp","'${verName_test3[$i]}'")' >& log/iso_efficiency_withSkimFile_v3_pp_${verName_test3[$i]}.log & sleep 20
    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_test3[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_test3[$i]}.log & sleep 20
    root -l -b -q 'purity/yj_quickPhotonPurity_v3_sideband10to20.C++("pp","'${verName_test4[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_test4[$i]}.log & sleep 20
    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_test3[$i]}'")' >& log/correlation_pp_${verName_test3[$i]}.log & sleep 20 
    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_test3[$i]}'",1)' >& log/correlation_pp_${verName_test3[$i]}_splitMC.log & sleep 20
    root -l -b -q 'results/getRawDist_v8.C++("'${verName_test3[$i]}'",1,1)' >& log/getRawDist_v8_${verName_test3[$i]}.log & sleep 20 
    wait $(jobs -p)
    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_test3[$i]}'",0,1)' >& log/fitPurity_pbpb_${verName_test3[$i]}.log & sleep 20
    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_test3[$i]}'",0,1)' >& log/fitPurity_pp_${verName_test3[$i]}.log & sleep 20
    wait $(jobs -p)
    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_test3[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_test3[$i]}.log
    source /data/ROOT-v5.34.21/bin/thisroot.sh
    python results/RooUnfold_photonRaa_v6.py ${verName_test3[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_test3[$i]}.log
    source /home/goyeonju/root/builddir/bin/thisroot.sh
    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_test3[$i]}'")' >& log/drawUnfoldingFigures_${verName_test3[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_test3[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_test3[$i]}.log
done
cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_test3}'")' >& log/plotting_v4_${verName_test3}.log


for ((i=0; i< ${#verName_test4[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_test4[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    cp ./efficiency/output/pbpb_iso_efficiency_${verName_test3[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_test4[$i]}.root
    cp ./efficiency/output/pp_iso_efficiency_${verName_test3[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_test4[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_test4[$i]}'",1,0,1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_SBcorr_centDepCorr_pbpb_${verName_test4[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_test4[$i]}'",1,0,1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_SBcorr_centDepCorr_pp_${verName_test4[$i]}.log
    cp ./performance/output/correlation_genPt_recoPt_${verName_test3[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_test4[$i]}_pbpb.root 
    cp ./performance/output/correlation_genPt_recoPt_${verName_test3[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_test4[$i]}_pp.root 
    cp ./results/output/rawDist_${verName_test3[$i]}_splitPD.root ./results/output/rawDist_${verName_test4[$i]}_splitPD.root
    wait $(jobs -p)
    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_test4[$i]}'",1,1)' >& log/fitPurity_pbpb_${verName_test4[$i]}.log & sleep 20
    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_test4[$i]}'",1,1)' >& log/fitPurity_pp_${verName_test4[$i]}.log & sleep 20
    wait $(jobs -p)
    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_test4[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_test4[$i]}.log
    source /data/ROOT-v5.34.21/bin/thisroot.sh
    python results/RooUnfold_photonRaa_v6.py ${verName_test4[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_test4[$i]}.log
    source /home/goyeonju/root/builddir/bin/thisroot.sh
    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_test4[$i]}'")' >& log/drawUnfoldingFigures_${verName_test4[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_test4[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_test4[$i]}.log
done
cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_test4}'")' >& log/plotting_v4_${verName_test4}.log



verFileCopy_test5=('190703_temp_v31_sigSumIso10_sideband10to20')
verName_test5=('190703_temp_v31_sigSumIso10_sideband10to20')
preverName_test5=('190220_temp_v26_nominal')

verFileCopy_test6=('190703_temp_v31_sigSumIso10_sideband20to30')
verName_test6=('190703_temp_v31_sigSumIso10_sideband20to30')
preverName_test6=('190220_temp_v26_nominal')

for ((i=0; i< ${#verName_test5[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_test5[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pbpb","'${verName_test5[$i]}'")' >& log/iso_efficiency_withSkimFile_v3_pbpb_${verName_test5[$i]}.log & sleep 5 
    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_test5[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_test5[$i]}.log & sleep 20
    root -l -b -q 'purity/yj_quickPhotonPurity_v3_sideband20to30.C++("pbpb","'${verName_test6[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_test6[$i]}.log & sleep 20
    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_test5[$i]}'")' >& log/correlation_pbpb_${verName_test5[$i]}.log & sleep 20
    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_test5[$i]}'",1)' >& log/correlation_pbpb_${verName_test5[$i]}_splitMC.log & sleep 20 
    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pp","'${verName_test5[$i]}'")' >& log/iso_efficiency_withSkimFile_v3_pp_${verName_test5[$i]}.log & sleep 20
    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_test5[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_test5[$i]}.log & sleep 20
    root -l -b -q 'purity/yj_quickPhotonPurity_v3_sideband20to30.C++("pp","'${verName_test6[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_test6[$i]}.log & sleep 20
    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_test5[$i]}'")' >& log/correlation_pp_${verName_test5[$i]}.log & sleep 20 
    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_test5[$i]}'",1)' >& log/correlation_pp_${verName_test5[$i]}_splitMC.log & sleep 20
    root -l -b -q 'results/getRawDist_v8.C++("'${verName_test5[$i]}'",1,1)' >& log/getRawDist_v8_${verName_test5[$i]}.log & sleep 20 
    wait $(jobs -p)
    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_test5[$i]}'",0,1)' >& log/fitPurity_pbpb_${verName_test5[$i]}.log & sleep 20
    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_test5[$i]}'",0,1)' >& log/fitPurity_pp_${verName_test5[$i]}.log & sleep 20
    wait $(jobs -p)
    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_test5[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_test5[$i]}.log
    source /data/ROOT-v5.34.21/bin/thisroot.sh
    python results/RooUnfold_photonRaa_v6.py ${verName_test5[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_test5[$i]}.log
    source /home/goyeonju/root/builddir/bin/thisroot.sh
    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_test5[$i]}'")' >& log/drawUnfoldingFigures_${verName_test5[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_test5[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_test5[$i]}.log
done
cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_test5}'")' >& log/plotting_v4_${verName_test5}.log


for ((i=0; i< ${#verName_test6[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_test6[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    cp ./efficiency/output/pbpb_iso_efficiency_${verName_test5[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_test6[$i]}.root
    cp ./efficiency/output/pp_iso_efficiency_${verName_test5[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_test6[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_test6[$i]}'",1,0,1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_SBcorr_centDepCorr_pbpb_${verName_test6[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_test6[$i]}'",1,0,1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_SBcorr_centDepCorr_pp_${verName_test6[$i]}.log
    cp ./performance/output/correlation_genPt_recoPt_${verName_test5[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_test6[$i]}_pbpb.root 
    cp ./performance/output/correlation_genPt_recoPt_${verName_test5[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_test6[$i]}_pp.root 
    cp ./results/output/rawDist_${verName_test5[$i]}_splitPD.root ./results/output/rawDist_${verName_test6[$i]}_splitPD.root
    wait $(jobs -p)
    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_test6[$i]}'",1,1)' >& log/fitPurity_pbpb_${verName_test6[$i]}.log & sleep 20
    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_test6[$i]}'",1,1)' >& log/fitPurity_pp_${verName_test6[$i]}.log & sleep 20
    wait $(jobs -p)
    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_test6[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_test6[$i]}.log
    source /data/ROOT-v5.34.21/bin/thisroot.sh
    python results/RooUnfold_photonRaa_v6.py ${verName_test6[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_test6[$i]}.log
    source /home/goyeonju/root/builddir/bin/thisroot.sh
    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_test6[$i]}'")' >& log/drawUnfoldingFigures_${verName_test6[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_test6[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_test6[$i]}.log
done
cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_test6}'")' >& log/plotting_v4_${verName_test6}.log




















#verFileCopy_abc=('190703_temp_v31_pur_SBcorr_centDep')
#verName_abc=('190703_temp_v31_pur_SBcorr_centDep')
#preverName_abc=('190220_temp_v26_nominal')
#
#for ((i=0; i< ${#verName_abc[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
###    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_abc[$i]}.root
##    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_abc[$i]}.root
##    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_abc[$i]}'",1,0,1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_SBcorr_centDepCorr_pbpb_${verName_abc[$i]}.log & sleep 20
##    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_abc[$i]}'",1,0,1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_SBcorr_centDepCorr_pp_${verName_abc[$i]}.log
##    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_abc[$i]}_pbpb.root 
##    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_abc[$i]}_pp.root 
##    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_abc[$i]}_splitPD.root
##    wait $(jobs -p)
##    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_abc[$i]}'",1,1)' >& log/fitPurity_pbpb_${verName_abc[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_abc[$i]}'",1,1)' >& log/fitPurity_pp_${verName_abc[$i]}.log & sleep 20
##    wait $(jobs -p)
##    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_abc[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_abc[$i]}.log
##    source /data/ROOT-v5.34.21/bin/thisroot.sh
##    python results/RooUnfold_photonRaa_v6.py ${verName_abc[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_abc[$i]}.log
##    source /home/goyeonju/root/builddir/bin/thisroot.sh
##    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_abc[$i]}'")' >& log/drawUnfoldingFigures_${verName_abc[$i]}.log
##    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_abc[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_abc[$i]}.log
#done
#verFileCopy_ab=('190703_temp_v31_pur_SBcorr_noCentDep')
#verName_ab=('190703_temp_v31_pur_SBcorr_noCentDep')
#preverName_ab=('190220_temp_v26_nominal')
#
#for ((i=0; i< ${#verName_ab[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
##    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_ab[$i]}.root
##    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_ab[$i]}.root
##    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_ab[$i]}'",1,0,1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_SBcorr_noCentDepCorr_pbpb_${verName_ab[$i]}.log & sleep 20
##    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_ab[$i]}'",1,0,1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_SBcorr_noCentDepCorr_pp_${verName_ab[$i]}.log
##    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_ab[$i]}_pbpb.root 
##    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_ab[$i]}_pp.root 
##    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_ab[$i]}_splitPD.root
##    wait $(jobs -p)
#    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_ab[$i]}'",0,1)' >& log/fitPurity_pbpb_${verName_ab[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_ab[$i]}'",2,1)' >& log/fitPurity_pp_${verName_ab[$i]}.log & sleep 20
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_ab[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_ab[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_ab[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_ab[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_ab[$i]}'")' >& log/drawUnfoldingFigures_${verName_ab[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_ab[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_ab[$i]}.log
#done
###
##
###verFileCopy_un=('190703_temp_v31')
###verName_un=('190703_temp_v31_sys_unfolding_MCsize')
###for ((i=0; i< ${#verName_un[@]};i++))
###do
###    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_un[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
###    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_un[$i]}_splitPD.root
###    root -l -b -q 'toyStudy_responseMatrix.C++("pp","'${verName_un[$i]}'")' >& log/correlation_toyStudy_responseMatrix_pp_${verName_un[$i]}.log
###    root -l -b -q 'toyStudy_responseMatrix.C++("pbpb","'${verName_un[$i]}'")' >& log/correlation_toyStudy_responseMatrix_pbpb_${verName_un[$i]}.log
###    cp ./results/output/phoRaa_${verName_a[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_un[$i]}_beforeUnfolding.root
###    source /data/ROOT-v5.34.21/bin/thisroot.sh
###    python results/RooUnfold_photonRaa_v6.py ${verName_un[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_un[$i]}.log
###    source /home/goyeonju/root/builddir/bin/thisroot.sh
###    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_un[$i]}'",1)' >& log/drawUnfoldingFigures_${verName_un[$i]}_splitMC.log
###    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_un[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_un[$i]}.log
###done
##
##
##########for j in 1 2 3 4 5 6 7 8 9 10
#########for j in 100 1 2 3 4 5 6 7 8 9 10
###for j in {1..10} 
###do
###    verFileCopy_l=('190703_temp_v31')
###    verName_l=('190703_temp_v31_sys_unfolding_svd'$j)
###    for ((i=0; i< ${#verName_l[@]};i++))
###    do
###        cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_l[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
###        cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_l[$i]}_splitPD.root
###        cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_l[$i]}_pbpb.root 
###        cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_l[$i]}_pp.root 
###        cp ./results/output/phoRaa_${verName_a[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_l[$i]}_beforeUnfolding.root
###        source /data/ROOT-v5.34.21/bin/thisroot.sh
###        python results/RooUnfold_photonRaa_v6.py ${verName_l[$i]} svd $j noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_l[$i]}.log
###        source /home/goyeonju/root/builddir/bin/thisroot.sh
###        root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_l[$i]}'")' >& log/drawUnfoldingFigures_${verName_l[$i]}.log
###        cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb_splitMC.root ./performance/output/correlation_genPt_recoPt_${verName_l[$i]}_pbpb_splitMC.root 
###        cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp_splitMC.root ./performance/output/correlation_genPt_recoPt_${verName_l[$i]}_pp_splitMC.root 
###        source /data/ROOT-v5.34.21/bin/thisroot.sh
###        python results/RooUnfold_photonRaa_v6.py ${verName_l[$i]} svd $j splitMC >& log/RooUnfold_photonRaa_v6_${verName_l[$i]}_splitMC.log
###        source /home/goyeonju/root/builddir/bin/thisroot.sh
###        root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_l[$i]}'",1)' >& log/drawUnfoldingFigures_${verName_l[$i]}_splitMC.log
###        root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_l[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_l[$i]}.log
###    done
###done
###
####for j in 1 2 3 4 5 6 7 8 9 10
####for j in {100..105}
###for j in {1..30}
###do
###    verFileCopy_m=('190703_temp_v31')
###    verName_m=('190703_temp_v31_sys_unfolding_iterative'$j)
###    for ((i=0; i< ${#verName_m[@]};i++))
###    do
###        cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_m[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
###        cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_m[$i]}_splitPD.root
###        cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_m[$i]}_pbpb.root 
###        cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_m[$i]}_pp.root 
###        cp ./results/output/phoRaa_${verName_a[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_m[$i]}_beforeUnfolding.root
###        source /data/ROOT-v5.34.21/bin/thisroot.sh
###        python results/RooUnfold_photonRaa_v6.py ${verName_m[$i]} $j 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_m[$i]}.log
###        source /home/goyeonju/root/builddir/bin/thisroot.sh
###        root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_m[$i]}'")' >& log/drawUnfoldingFigures_${verName_m[$i]}.log
###        cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb_splitMC.root ./performance/output/correlation_genPt_recoPt_${verName_m[$i]}_pbpb_splitMC.root 
###        cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp_splitMC.root ./performance/output/correlation_genPt_recoPt_${verName_m[$i]}_pp_splitMC.root 
###        source /data/ROOT-v5.34.21/bin/thisroot.sh
###        python results/RooUnfold_photonRaa_v6.py ${verName_m[$i]} $j 0 splitMC >& log/RooUnfold_photonRaa_v6_${verName_m[$i]}_splitMC.log
###        source /home/goyeonju/root/builddir/bin/thisroot.sh
###        root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_m[$i]}'",1)' >& log/drawUnfoldingFigures_${verName_m[$i]}.log
###        root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_m[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_m[$i]}.log
###    done
###done
####
####
#verFileCopy_c=('190703_temp_v31_sys_purUp')
#verName_c=('190703_temp_v31_sys_purUp')
#preverName_c=('180822_temp_v24_sys_purUp')
##for ((i=0; i< ${#verName_c[@]};i++))
##do
##    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_c[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
####    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_c[$i]}.root
####    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_c[$i]}.root
####    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_c[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_c[$i]}.log & sleep 20
####    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_c[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_c[$i]}.log
####    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_c[$i]}_pbpb.root 
####    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_c[$i]}_pp.root 
####    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_c[$i]}_splitPD.root
####    wait $(jobs -p)
####    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_c[$i]}'",1,1)' >& log/fitPurity_pbpb_${verName_c[$i]}.log & sleep 20
####    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_c[$i]}'",1,1)' >& log/fitPurity_pp_${verName_c[$i]}.log & sleep 20
####    wait $(jobs -p)
####    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_c[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_c[$i]}.log
####    source /data/ROOT-v5.34.21/bin/thisroot.sh
####    python results/RooUnfold_photonRaa_v6.py ${verName_c[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_c[$i]}.log
####    source /home/goyeonju/root/builddir/bin/thisroot.sh
####    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_c[$i]}'")' >& log/drawUnfoldingFigures_${verName_c[$i]}.log
###    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_c[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_c[$i]}.log
##done
##
#verFileCopy_dmore5=('190703_temp_v31_sys_purDown_more5')
#verName_dmore5=('190703_temp_v31_sys_purDown_more5')
#preverName_dmore5=('180822_temp_v24_sys_purDown_more5')
#for ((i=0; i< ${#verName_dmore5[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_dmore5[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
###    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_dmore5[$i]}.root
###    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_dmore5[$i]}.root
###    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pbpb","'${verName_dmore5[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pbpb_${verName_dmore5[$i]}.log & sleep 20
###    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pp","'${verName_dmore5[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pp_${verName_dmore5[$i]}.log & sleep 20
##    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_dmore5[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_dmore5[$i]}.log & sleep 20
##    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_dmore5[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_dmore5[$i]}.log & sleep 20
##    wait $(jobs -p)
###    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_dmore5[$i]}_pbpb.root 
###    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_dmore5[$i]}_pp.root 
###    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_dmore5[$i]}_splitPD.root
###    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_dmore5[$i]}'",1,1)' >& log/fitPurity_pbpb_${verName_dmore5[$i]}.log & sleep 20
###    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_dmore5[$i]}'",1,1)' >& log/fitPurity_pp_${verName_dmore5[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity_temp_v4.C++("pbpb","'${verName_dmore5[$i]}'",1,1,2)' >& log/fitPurity_temp_v4_pbpb_${verName_dmore5[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity_temp_v4.C++("pp","'${verName_dmore5[$i]}'",1,1,2)' >& log/fitPurity_temp_v4_pp_${verName_dmore5[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity_temp_v3.C++("pbpb","'${verName_dmore5[$i]}'",1,1,2)' >& log/fitPurity_temp_v3_pbpb_${verName_dmore5[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity_temp_v3.C++("pp","'${verName_dmore5[$i]}'",1,1,2)' >& log/fitPurity_temp_v3_pp_${verName_dmore5[$i]}.log & sleep 20
##    wait $(jobs -p)
##    root -l -b -q 'results/drawRaaXsec_v8_beforeUnfolding_withTnP.C++("'${verName_dmore5[$i]}'",1)' >& log/drawRaaXsec_v8_beforeUnfolding_withTnP_${verName_dmore5[$i]}.log
##    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_dmore5[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_dmore5[$i]}.log
##    source /data/ROOT-v5.34.21/bin/thisroot.sh
##    python results/RooUnfold_photonRaa_v6.py ${verName_dmore5[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_dmore5[$i]}.log
##    source /home/goyeonju/root/builddir/bin/thisroot.sh
###    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_dmore5[$i]}'")' >& log/drawUnfoldingFigures_${verName_dmore5[$i]}.log
##    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_dmore5[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_dmore5[$i]}.log
#done
##verFileCopy_dmore4=('190703_temp_v31_sys_purDown_more4')
##verName_dmore4=('190703_temp_v31_sys_purDown_more4')
##preverName_dmore4=('180822_temp_v24_sys_purDown_more4')
##for ((i=0; i< ${#verName_dmore4[@]};i++))
##do
##    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_dmore4[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
###    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_dmore4[$i]}.root
###    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_dmore4[$i]}.root
###    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pbpb","'${verName_dmore4[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pbpb_${verName_dmore4[$i]}.log & sleep 20
###    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pp","'${verName_dmore4[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pp_${verName_dmore4[$i]}.log & sleep 20
###    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_dmore4[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_dmore4[$i]}.log & sleep 20
###    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_dmore4[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_dmore4[$i]}.log & sleep 20
##    wait $(jobs -p)
###    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_dmore4[$i]}_pbpb.root 
###    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_dmore4[$i]}_pp.root 
###    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_dmore4[$i]}_splitPD.root
###    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_dmore4[$i]}'",1,1)' >& log/fitPurity_pbpb_${verName_dmore4[$i]}.log & sleep 20
###    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_dmore4[$i]}'",1,1)' >& log/fitPurity_pp_${verName_dmore4[$i]}.log & sleep 20
###    root -l -b -q 'purity/fitPurity_temp_v4.C++("pbpb","'${verName_dmore4[$i]}'",1,1,2)' >& log/fitPurity_temp_v4_pbpb_${verName_dmore4[$i]}.log & sleep 20
###    root -l -b -q 'purity/fitPurity_temp_v4.C++("pp","'${verName_dmore4[$i]}'",1,1,2)' >& log/fitPurity_temp_v4_pp_${verName_dmore4[$i]}.log & sleep 20
###    root -l -b -q 'purity/fitPurity_temp_v3.C++("pbpb","'${verName_dmore4[$i]}'",1,1,2)' >& log/fitPurity_temp_v3_pbpb_${verName_dmore4[$i]}.log & sleep 20
###    root -l -b -q 'purity/fitPurity_temp_v3.C++("pp","'${verName_dmore4[$i]}'",1,1,2)' >& log/fitPurity_temp_v3_pp_${verName_dmore4[$i]}.log & sleep 20
##    wait $(jobs -p)
##    root -l -b -q 'results/drawRaaXsec_v8_beforeUnfolding_withTnP.C++("'${verName_dmore4[$i]}'",1)' >& log/drawRaaXsec_v8_beforeUnfolding_withTnP_${verName_dmore4[$i]}.log
###root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_dmore4[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_dmore4[$i]}.log
##    source /data/ROOT-v5.34.21/bin/thisroot.sh
##    python results/RooUnfold_photonRaa_v6.py ${verName_dmore4[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_dmore4[$i]}.log
##    source /home/goyeonju/root/builddir/bin/thisroot.sh
###    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_dmore4[$i]}'")' >& log/drawUnfoldingFigures_${verName_dmore4[$i]}.log
##    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_dmore4[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_dmore4[$i]}.log
##done
###
###
##verFileCopy_dmore3=('190703_temp_v31_sys_purDown_more3')
##verName_dmore3=('190703_temp_v31_sys_purDown_more3')
##preverName_dmore3=('180822_temp_v24_sys_purDown_more3')
##for ((i=0; i< ${#verName_dmore3[@]};i++))
##do
##    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_dmore3[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#####    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_dmore3[$i]}.root
#####    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_dmore3[$i]}.root
####    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pbpb","'${verName_dmore3[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pbpb_${verName_dmore3[$i]}.log & sleep 20
####    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pp","'${verName_dmore3[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pp_${verName_dmore3[$i]}.log & sleep 20
###    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_dmore3[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_dmore3[$i]}.log & sleep 20
###    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_dmore3[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_dmore3[$i]}.log & sleep 20
###    wait $(jobs -p)
#####    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_dmore3[$i]}_pbpb.root 
#####    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_dmore3[$i]}_pp.root 
#####    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_dmore3[$i]}_splitPD.root
#####    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_dmore3[$i]}'",1,1)' >& log/fitPurity_pbpb_${verName_dmore3[$i]}.log & sleep 20
#####    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_dmore3[$i]}'",1,1)' >& log/fitPurity_pp_${verName_dmore3[$i]}.log & sleep 20
###    root -l -b -q 'purity/fitPurity_temp_v3.C++("pbpb","'${verName_dmore3[$i]}'",1,1,2)' >& log/fitPurity_temp_v4_pbpb_${verName_dmore3[$i]}.log & sleep 20
###    root -l -b -q 'purity/fitPurity_temp_v3.C++("pp","'${verName_dmore3[$i]}'",1,1,2)' >& log/fitPurity_temp_v4_pp_${verName_dmore3[$i]}.log & sleep 20
####    root -l -b -q 'purity/fitPurity_temp_v4.C++("pbpb","'${verName_dmore3[$i]}'",1,1,2)' >& log/fitPurity_temp_v3_pbpb_${verName_dmore3[$i]}.log & sleep 20
####    root -l -b -q 'purity/fitPurity_temp_v4.C++("pp","'${verName_dmore3[$i]}'",1,1,2)' >& log/fitPurity_temp_v3_pp_${verName_dmore3[$i]}.log & sleep 20
###    wait $(jobs -p)
##    root -l -b -q 'results/drawRaaXsec_v8_beforeUnfolding_withTnP.C++("'${verName_dmore3[$i]}'",1)' >& log/drawRaaXsec_v8_beforeUnfolding_withTnP_${verName_dmore3[$i]}.log
###root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_dmore3[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_dmore3[$i]}.log
##    source /data/ROOT-v5.34.21/bin/thisroot.sh
##    python results/RooUnfold_photonRaa_v6.py ${verName_dmore3[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_dmore3[$i]}.log
##    source /home/goyeonju/root/builddir/bin/thisroot.sh
##    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_dmore3[$i]}'")' >& log/drawUnfoldingFigures_${verName_dmore3[$i]}.log
##    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_dmore3[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_dmore3[$i]}.log
##done
###
###
###verFileCopy_dmore2=('190703_temp_v31_sys_purDown_more2')
###verName_dmore2=('190703_temp_v31_sys_purDown_more2')
###preverName_dmore2=('180822_temp_v24_sys_purDown_more2')
###for ((i=0; i< ${#verName_dmore2[@]};i++))
###do
###    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_dmore2[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#####    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_dmore2[$i]}.root
#####    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_dmore2[$i]}.root
#####    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_dmore2[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_dmore2[$i]}.log & sleep 20
#####    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_dmore2[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_dmore2[$i]}.log
#####    wait $(jobs -p)
#####    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_dmore2[$i]}_pbpb.root 
#####    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_dmore2[$i]}_pp.root 
#####    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_dmore2[$i]}_splitPD.root
###    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_dmore2[$i]}'",1,1,2)' >& log/fitPurity_pbpb_${verName_dmore2[$i]}.log & sleep 20
###    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_dmore2[$i]}'",1,1,2)' >& log/fitPurity_pp_${verName_dmore2[$i]}.log & sleep 20
###    wait $(jobs -p)
###    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_dmore2[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_dmore2[$i]}.log
###    source /data/ROOT-v5.34.21/bin/thisroot.sh
###    python results/RooUnfold_photonRaa_v6.py ${verName_dmore2[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_dmore2[$i]}.log
###    source /home/goyeonju/root/builddir/bin/thisroot.sh
###    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_dmore2[$i]}'")' >& log/drawUnfoldingFigures_${verName_dmore2[$i]}.log
###    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_dmore2[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_dmore2[$i]}.log
###done
####
###
###verFileCopy_dmore=('190703_temp_v31_sys_purDown_more')
###verName_dmore=('190703_temp_v31_sys_purDown_more')
###preverName_dmore=('180822_temp_v24_sys_purDown_more')
###for ((i=0; i< ${#verName_dmore[@]};i++))
###do
###    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_dmore[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#####    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_dmore[$i]}.root
#####    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_dmore[$i]}.root
#####    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_dmore[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_dmore[$i]}.log & sleep 20
#####    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_dmore[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_dmore[$i]}.log
#####    wait $(jobs -p)
#####    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_dmore[$i]}_pbpb.root 
#####    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_dmore[$i]}_pp.root 
#####    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_dmore[$i]}_splitPD.root
###    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_dmore[$i]}'",1,1,2)' >& log/fitPurity_pbpb_${verName_dmore[$i]}.log & sleep 20
###    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_dmore[$i]}'",1,1,2)' >& log/fitPurity_pp_${verName_dmore[$i]}.log & sleep 20
###    wait $(jobs -p)
###    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_dmore[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_dmore[$i]}.log
###    source /data/ROOT-v5.34.21/bin/thisroot.sh
###    python results/RooUnfold_photonRaa_v6.py ${verName_dmore[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_dmore[$i]}.log
###    source /home/goyeonju/root/builddir/bin/thisroot.sh
###    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_dmore[$i]}'")' >& log/drawUnfoldingFigures_${verName_dmore[$i]}.log
###    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_dmore[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_dmore[$i]}.log
###done
###
##verFileCopy_d=('190703_temp_v31_sys_purDown')
##verName_d=('190703_temp_v31_sys_purDown')
##preverName_d=('180822_temp_v24_sys_purDown')
##for ((i=0; i< ${#verName_d[@]};i++))
##do
##    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_d[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
######    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_d[$i]}.root
######    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_d[$i]}.root
####    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pbpb","'${verName_d[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pbpb_${verName_d[$i]}.log & sleep 20
####    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pp","'${verName_d[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pp_${verName_d[$i]}.log & sleep 20
###    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_d[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_d[$i]}.log & sleep 20
###    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_d[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_d[$i]}.log & sleep 20
###    wait $(jobs -p)
######    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_d[$i]}_pbpb.root 
######    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_d[$i]}_pp.root 
######    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_d[$i]}_splitPD.root
######    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_d[$i]}'",1,1)' >& log/fitPurity_pbpb_${verName_d[$i]}.log & sleep 20
######    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_d[$i]}'",1,1)' >& log/fitPurity_pp_${verName_d[$i]}.log & sleep 20
####    root -l -b -q 'purity/fitPurity_temp_v4.C++("pbpb","'${verName_d[$i]}'",1,1,2)' >& log/fitPurity_temp_v4_pbpb_${verName_d[$i]}.log & sleep 20
####    root -l -b -q 'purity/fitPurity_temp_v4.C++("pp","'${verName_d[$i]}'",1,1,2)' >& log/fitPurity_temp_v4_pp_${verName_d[$i]}.log & sleep 20
###    root -l -b -q 'purity/fitPurity_temp_v3.C++("pbpb","'${verName_d[$i]}'",1,1,2)' >& log/fitPurity_temp_v3_pbpb_${verName_d[$i]}.log & sleep 20
###    root -l -b -q 'purity/fitPurity_temp_v3.C++("pp","'${verName_d[$i]}'",1,1,2)' >& log/fitPurity_temp_v3_pp_${verName_d[$i]}.log & sleep 20
##    wait $(jobs -p)
##    root -l -b -q 'results/drawRaaXsec_v8_beforeUnfolding_withTnP.C++("'${verName_d[$i]}'",1)' >& log/drawRaaXsec_v8_beforeUnfolding_withTnP_${verName_d[$i]}.log
###root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_d[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_d[$i]}.log
##    source /data/ROOT-v5.34.21/bin/thisroot.sh
##    python results/RooUnfold_photonRaa_v6.py ${verName_d[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_d[$i]}.log
##    source /home/goyeonju/root/builddir/bin/thisroot.sh
##    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_d[$i]}'")' >& log/drawUnfoldingFigures_${verName_d[$i]}.log
##    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_d[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_d[$i]}.log
##done
######
####verFileCopy_tnp=('190703_temp_v31_TnP')
####verName_tnp=('190703_temp_v31_TnP')
####for ((i=0; i< ${#verName_tnp[@]};i++))
####    do
####        cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_tnp[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
####        cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_tnp[$i]}.root
####        cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_tnp[$i]}.root
####        cp ./purity/output/purity_pbpb_${verName_a[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_tnp[$i]}_splitPD.root
####        cp ./purity/output/purity_pp_${verName_a[$i]}_splitPD.root ./purity/output/purity_pp_${verName_tnp[$i]}_splitPD.root
####        cp ./purity/output/purity_withFunc_pbpb_${verName_a[$i]}_splitPD.root ./purity/output/purity_withFunc_pbpb_${verName_tnp[$i]}_splitPD.root
####        cp ./purity/output/purity_withFunc_pp_${verName_a[$i]}_splitPD.root ./purity/output/purity_withFunc_pp_${verName_tnp[$i]}_splitPD.root
####        cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_tnp[$i]}_pbpb.root
####        cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_tnp[$i]}_pp.root
####        cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_tnp[$i]}_splitPD.root
####        wait $(jobs -p)
#####        root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_withTnP.C++("'${verName_tnp[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_withTnP_${verName_tnp[$i]}.log
####        source /data/ROOT-v5.34.21/bin/thisroot.sh
####        python results/RooUnfold_photonRaa_v6.py ${verName_tnp[$i]} inv 0 noSplitMC >& log/RooUnfold_photonRaa_v6_${verName_tnp[$i]}_splitMC.log
####        source /home/goyeonju/root/builddir/bin/thisroot.sh
####        root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_tnp[$i]}'")' >& log/drawUnfoldingFigures_${verName_tnp[$i]}.log
####        root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_tnp[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_tnp[$i]}.log
####done
######
#####verFileCopy_f=('190703_temp_v31_sys_IDup')
#####verName_f=('190703_temp_v31_sys_IDup')
#####preverName_f=('180822_temp_v24_sys_IDup')
#####for ((i=0; i< ${#verName_f[@]};i++))
#####do
#####    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_f[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#######    cp ./efficiency/output/pbpb_iso_efficiency_${preverName_f[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_f[$i]}.root
#######    cp ./efficiency/output/pp_iso_efficiency_${preverName_f[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_f[$i]}.root
#######    cp ./purity/output/purity_pbpb_${preverName_f[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_f[$i]}.root
#######    cp ./purity/output/purity_pp_${preverName_f[$i]}_splitPD.root ./purity/output/purity_pp_${verName_f[$i]}.root
#######    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pbpb","'${verName_f[$i]}'")' >& log/efficiency_withSkimFile_v2_pbpb_${verName_f[$i]}.log & sleep 20
#######    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pp","'${verName_f[$i]}'")' >& log/efficiency_withSkimFile_v2_pp_${verName_f[$i]}.log & sleep 20
#######    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_f[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_f[$i]}.log & sleep 20
#######    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_f[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_f[$i]}.log & sleep 20
######    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_f[$i]}'",1,1)' >& log/fitPurity_pbpb_${verName_f[$i]}.log & sleep 20
######    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_f[$i]}'",1,1)' >& log/fitPurity_pp_${verName_f[$i]}.log & sleep 20
#######    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_f[$i]}'")' >& log/correlation_pbpb_${verName_f[$i]}.log & sleep 20
#######    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_f[$i]}'")' >& log/correlation_pp_${verName_f[$i]}.log & sleep 20
######    root -l -b -q 'results/getRawDist_v8.C++("'${verName_f[$i]}'",1,1)' >& log/getRawDist_v8_${verName_f[$i]}.log & sleep 20
######    wait $(jobs -p)
######    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_f[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_f[$i]}.log
######    source /data/ROOT-v5.34.21/bin/thisroot.sh
######    python results/RooUnfold_photonRaa_v6.py ${verName_f[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_f[$i]}.log
######    source /home/goyeonju/root/builddir/bin/thisroot.sh
######    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_f[$i]}'")' >& log/drawUnfoldingFigures_${verName_f[$i]}.log
######    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_f[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_f[$i]}.log
#####done
#####
#####verFileCopy_fa=('190703_temp_v31_sys_IDdown')
#####verName_fa=('190703_temp_v31_sys_IDdown')
#####preverName_fa=('180822_temp_v24_sys_IDdown')
#####for ((i=0; i< ${#verName_fa[@]};i++))
#####do
#####    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_fa[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#######    cp ./efficiency/output/pbpb_iso_efficiency_${preverName_fa[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_fa[$i]}.root
#######    cp ./efficiency/output/pp_iso_efficiency_${preverName_fa[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_fa[$i]}.root
#######    cp ./purity/output/purity_pbpb_${preverName_fa[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_fa[$i]}.root
#######    cp ./purity/output/purity_pp_${preverName_fa[$i]}_splitPD.root ./purity/output/purity_pp_${verName_fa[$i]}.root
#######    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pbpb","'${verName_fa[$i]}'")' >& log/efficiency_withSkimFile_v2_pbpb_${verName_fa[$i]}.log & sleep 20
#######    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pp","'${verName_fa[$i]}'")' >& log/efficiency_withSkimFile_v2_pp_${verName_fa[$i]}.log & sleep 20
#######    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_fa[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_fa[$i]}.log & sleep 20
#######    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_fa[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_fa[$i]}.log & sleep 20
######    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_fa[$i]}'",1,1)' >& log/fitPurity_pbpb_${verName_fa[$i]}.log & sleep 20
######    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_fa[$i]}'",1,1)' >& log/fitPurity_pp_${verName_fa[$i]}.log & sleep 20
#######    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_fa[$i]}'")' >& log/correlation_pbpb_${verName_fa[$i]}.log & sleep 20
#######    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_fa[$i]}'")' >& log/correlation_pp_${verName_fa[$i]}.log & sleep 20
######    root -l -b -q 'results/getRawDist_v8.C++("'${verName_fa[$i]}'",1,1)' >& log/getRawDist_v8_${verName_fa[$i]}.log & sleep 20
######    wait $(jobs -p)
######    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_fa[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_fa[$i]}.log
######    source /data/ROOT-v5.34.21/bin/thisroot.sh
######    python results/RooUnfold_photonRaa_v6.py ${verName_fa[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_fa[$i]}.log
######    source /home/goyeonju/root/builddir/bin/thisroot.sh
######    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_fa[$i]}'")' >& log/drawUnfoldingFigures_${verName_fa[$i]}.log
######    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_fa[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_fa[$i]}.log
#####done
#####
####verFileCopy_b=('190703_temp_v31_sys_phoEscale')
####verName_b=('190703_temp_v31_sys_phoEscale')
####preverName_b=('180822_temp_v24_sys_phoEscale')
####for ((i=0; i< ${#verName_b[@]};i++))
####do
####    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_b[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
####    #cp ./efficiency/output/pbpb_iso_efficiency_${preverName_b[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_b[$i]}.root
####    #cp ./efficiency/output/pp_iso_efficiency_${preverName_b[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_b[$i]}.root
####    #cp ./purity/output/purity_pbpb_${preverName_b[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_b[$i]}.root
####    #cp ./purity/output/purity_pp_${preverName_b[$i]}_splitPD.root ./purity/output/purity_pp_${verName_b[$i]}.root
#####    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pbpb","'${verName_b[$i]}'")' >& log/efficiency_withSkimFile_v2_pbpb_${verName_b[$i]}.log & sleep 20
#####    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_b[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_b[$i]}.log & sleep 20
#####    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_b[$i]}'")' >& log/correlation_pbpb_${verName_b[$i]}.log & sleep 20
#####    #root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_b[$i]}'",1)' >& log/correlation_pbpb_${verName_b[$i]}.log & sleep 20
#####    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pp","'${verName_b[$i]}'")' >& log/efficiency_withSkimFile_v2_pp_${verName_b[$i]}.log & sleep 20
#####    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_b[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_b[$i]}.log & sleep 20
#####    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_b[$i]}'")' >& log/correlation_pp_${verName_b[$i]}.log & sleep 20
#####    #root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_b[$i]}'",1)' >& log/correlation_pp_${verName_b[$i]}.log & sleep 20
#####    root -l -b -q 'results/getRawDist_v8.C++("'${verName_b[$i]}'",1,1)' >& log/getRawDist_v8_${verName_b[$i]}.log & sleep 20
#####    wait $(jobs -p)
#####    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_b[$i]}'",1,1)' >& log/fitPurity_pbpb_${verName_b[$i]}.log & sleep 20
#####    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_b[$i]}'",1,1)' >& log/fitPurity_pp_${verName_b[$i]}.log & sleep 20
#####    wait $(jobs -p)
#####    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_b[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_b[$i]}.log
####    source /data/ROOT-v5.34.21/bin/thisroot.sh
####    python results/RooUnfold_photonRaa_v6.py ${verName_b[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_b[$i]}.log
####    source /home/goyeonju/root/builddir/bin/thisroot.sh
####    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_b[$i]}'")' >& log/drawUnfoldingFigures_${verName_b[$i]}.log
####    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_b[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_b[$i]}.log
####done
#####
####verFileCopy_j=('190703_temp_v31_sys_phoEresol')
####verName_j=('190703_temp_v31_sys_phoEresol')
####for ((i=0; i< ${#verName_j[@]};i++))
####do
####    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_j[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#####    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pbpb","'${verName_j[$i]}'")' >& log/efficiency_withSkimFile_v2_pbpb_${verName_j[$i]}.log & sleep 20
#####    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_j[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_j[$i]}.log & sleep 20
#####    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_j[$i]}'")' >& log/correlation_pbpb_${verName_j[$i]}.log & sleep 20
#####    #root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_j[$i]}'",1)' >& log/correlation_pbpb_${verName_j[$i]}.log & sleep 20
#####    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pp","'${verName_j[$i]}'")' >& log/efficiency_withSkimFile_v2_pp_${verName_j[$i]}.log & sleep 20
#####    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_j[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_j[$i]}.log & sleep 20
#####    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_j[$i]}'")' >& log/correlation_pp_${verName_j[$i]}.log & sleep 20
######    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_j[$i]}'",1)' >& log/correlation_pp_${verName_j[$i]}.log & sleep 20
#####    root -l -b -q 'results/getRawDist_v8.C++("'${verName_j[$i]}'")' >& log/getRawDist_v8_${verName_j[$i]}.log & sleep 20
#####    wait $(jobs -p)
#####    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_j[$i]}'",1,1)' >& log/fitPurity_pbpb_${verName_j[$i]}.log & sleep 20
#####    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_j[$i]}'",1,1)' >& log/fitPurity_pp_${verName_j[$i]}.log & sleep 20
#####    wait $(jobs -p)
#####    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_j[$i]}'")' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_j[$i]}.log
####    source /data/ROOT-v5.34.21/bin/thisroot.sh
####    python results/RooUnfold_photonRaa_v6.py ${verName_j[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_j[$i]}.log
####    source /home/goyeonju/root/builddir/bin/thisroot.sh
####    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_j[$i]}'")' >& log/drawUnfoldingFigures_${verName_j[$i]}.log
####    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_j[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_j[$i]}.log
####done
#####
####verFileCopy_e=('190703_temp_v31_sys_eleCont')
####verName_e=('190703_temp_v31_sys_eleCont')
####preverName_e=('180822_temp_v24_sys_eleCont')
####for ((i=0; i< ${#verName_e[@]};i++))
####do
####    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_e[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#####    #cp ./efficiency/output/pbpb_iso_efficiency_${preverName_e[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_e[$i]}.root
#####    #cp ./efficiency/output/pp_iso_efficiency_${preverName_e[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_e[$i]}.root
#####    #cp ./purity/output/purity_pbpb_${preverName_e[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_e[$i]}.root
#####    #cp ./purity/output/purity_pp_${preverName_e[$i]}_splitPD.root ./purity/output/purity_pp_${verName_e[$i]}.root
#####    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pbpb","'${verName_e[$i]}'")' >& log/efficiency_withSkimFile_v2_pbpb_${verName_e[$i]}.log & sleep 20
#####    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_e[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_e[$i]}.log & sleep 20
#####    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_e[$i]}'")' >& log/correlation_pbpb_${verName_e[$i]}.log & sleep 20
#####    #root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_e[$i]}'",1)' >& log/correlation_pbpb_${verName_e[$i]}.log & sleep 20
#####    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pp","'${verName_e[$i]}'")' >& log/efficiency_withSkimFile_v2_pp_${verName_e[$i]}.log & sleep 20
#####    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_e[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_e[$i]}.log & sleep 20
#####    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_e[$i]}'")' >& log/correlation_pp_${verName_e[$i]}.log & sleep 20
#####    #root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_e[$i]}'",1)' >& log/correlation_pp_${verName_e[$i]}.log & sleep 20
#####    root -l -b -q 'results/getRawDist_v8.C++("'${verName_e[$i]}'",1,1)' >& log/getRawDist_v8_${verName_e[$i]}.log & sleep 20
#####    wait $(jobs -p)
#####    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_e[$i]}'",1,1)' >& log/fitPurity_pbpb_${verName_e[$i]}.log & sleep 20
#####    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_e[$i]}'",1,1)' >& log/fitPurity_pp_${verName_e[$i]}.log & sleep 20
#####    wait $(jobs -p)
#####    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_e[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_e[$i]}.log
#####    ### special step only for electron efficiency systematic 
#####    cp ./results/output/phoRaa_${verName_e[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_e[$i]}_beforeEffCorrection_beforeUnfolding.root
#####    root -l -b -q 'results/drawRaaXsec_eleCont_subtraced.C++("'${verName_e[$i]}'")' >& log/drawRaaXsec_eleCont_subtraced_${verName_e[$i]}.log
#####    ###
####    source /data/ROOT-v5.34.21/bin/thisroot.sh
####    python results/RooUnfold_photonRaa_v6.py ${verName_e[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_e[$i]}.log
####    source /home/goyeonju/root/builddir/bin/thisroot.sh
####    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_e[$i]}'")' >& log/drawUnfoldingFigures_${verName_e[$i]}.log
####    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_e[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_e[$i]}.log
####done
#####
####verFileCopy_h=('190703_temp_v31_sys_TAAup')
####verName_h=('190703_temp_v31_sys_TAAup')
####for ((i=0; i< ${#verName_h[@]};i++))
####do
####    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_h[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
####    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_h[$i]}.root
####    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_h[$i]}.root
####    cp ./purity/output/purity_pbpb_${verName_a[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_h[$i]}_splitPD.root
####    cp ./purity/output/purity_pp_${verName_a[$i]}_splitPD.root ./purity/output/purity_pp_${verName_h[$i]}_splitPD.root
####    cp ./purity/output/purity_withFunc_pbpb_${verName_a[$i]}_splitPD.root ./purity/output/purity_withFunc_pbpb_${verName_h[$i]}_splitPD.root
####    cp ./purity/output/purity_withFunc_pp_${verName_a[$i]}_splitPD.root ./purity/output/purity_withFunc_pp_${verName_h[$i]}_splitPD.root
####    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_h[$i]}_pbpb.root 
####    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_h[$i]}_pp.root 
####    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_h[$i]}_splitPD.root
####    cp ./results/output/Unfold_${verName_a[$i]}.root ./results/output/Unfold_${verName_h[$i]}.root
####    cp ./results/output/phoRaa_${verName_a[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_h[$i]}_beforeUnfolding.root
####    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_h[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_h[$i]}.log
####done
####
####verFileCopy_ha=('190703_temp_v31_sys_TAAdown')
####verName_ha=('190703_temp_v31_sys_TAAdown')
####for ((i=0; i< ${#verName_ha[@]};i++))
####do
####    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_ha[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
####    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_ha[$i]}.root
####    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_ha[$i]}.root
####    cp ./purity/output/purity_pbpb_${verName_a[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_ha[$i]}_splitPD.root
####    cp ./purity/output/purity_pp_${verName_a[$i]}_splitPD.root ./purity/output/purity_pp_${verName_ha[$i]}_splitPD.root
####    cp ./purity/output/purity_withFunc_pbpb_${verName_a[$i]}_splitPD.root ./purity/output/purity_withFunc_pbpb_${verName_ha[$i]}_splitPD.root
####    cp ./purity/output/purity_withFunc_pp_${verName_a[$i]}_splitPD.root ./purity/output/purity_withFunc_pp_${verName_ha[$i]}_splitPD.root
####    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_ha[$i]}_pbpb.root 
####    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_ha[$i]}_pp.root 
####    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_ha[$i]}_splitPD.root
####    cp ./results/output/Unfold_${verName_a[$i]}.root ./results/output/Unfold_${verName_ha[$i]}.root
####    cp ./results/output/phoRaa_${verName_a[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_ha[$i]}_beforeUnfolding.root
####    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_h[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_ha[$i]}.log
####done
#####
#####verFileCopy_an=('190703_temp_v31')
#####verName_an=('190703_temp_v31_noUnfolding')
#####preverName_an=('190220_temp_v26_noUnfolding')
######
#####for ((i=0; i< ${#verName_a[@]};i++))
#####do
#####    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
######    cp ./efficiency/output/pbpb_iso_efficiency_${preverName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root
######    cp ./efficiency/output/pp_iso_efficiency_${preverName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root
######    cp ./purity/output/purity_pbpb_${preverName_a[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_a[$i]}_splitPD.root
######    cp ./purity/output/purity_pp_${preverName_a[$i]}_splitPD.root ./purity/output/purity_pp_${verName_a[$i]}_splitPD.root
######    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pbpb","'${verName_a[$i]}'")' >& log/iso_efficiency_withSkimFile_v3_pbpb_${verName_a[$i]}.log & sleep 20 
######    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_a[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_a[$i]}.log & sleep 20
######    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_a[$i]}'")' >& log/correlation_pbpb_${verName_a[$i]}.log & sleep 20
######    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pp","'${verName_a[$i]}'")' >& log/iso_efficiency_withSkimFile_v3_pp_${verName_a[$i]}.log & sleep 20
######    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_a[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_a[$i]}.log & sleep 20
######    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_a[$i]}'")' >& log/correlation_pp_${verName_a[$i]}.log & sleep 20 
######    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_a[$i]}'",1)' >& log/correlation_pbpb_${verName_a[$i]}_splitMC.log & sleep 20 
######    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_a[$i]}'",1)' >& log/correlation_pp_${verName_a[$i]}_splitMC.log & sleep 20
######    root -l -b -q 'results/getRawDist_v8.C++("'${verName_a[$i]}'",1,1)' >& log/getRawDist_v8_${verName_a[$i]}.log & sleep 20 
######    wait $(jobs -p)
######    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_a[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_a[$i]}.log
#####    source /data/ROOT-v5.34.21/bin/thisroot.sh
#####    python results/RooUnfold_photonRaa_v6.py ${verName_a[$i]} bin 0 noSplitMC >& log/RooUnfold_photonRaa_v6_${verName_a[$i]}.log
#####    source /home/goyeonju/root/builddir/bin/thisroot.sh
#####    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_a[$i]}'")' >& log/drawUnfoldingFigures_${verName_a[$i]}.log
######    root -l -b -q 'performance/divideTree.C++' >& log/divideTree_pbpb_20180815skim.log
#####    source /data/ROOT-v5.34.21/bin/thisroot.sh
#####    python results/RooUnfold_photonRaa_v6.py ${verName_a[$i]} bin 0 splitMC >& log/RooUnfold_photonRaa_v6_${verName_a[$i]}_splitMC.log
#####    source /home/goyeonju/root/builddir/bin/thisroot.sh
#####    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_a[$i]}'",1)' >& log/drawUnfoldingFigures_${verName_a[$i]}_splitMC.log
#####    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_a[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_a[$i]}.log
######    
######     cp ./results/output/phoRaa_${preverName_a[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_a[$i]}_beforeUnfolding.root
######    root -l -b -q 'performance/compare_unfolding.C++("pbpb","'${verName_a[$i]}'")' >& log/compare_unfolding_pbpb_${verName_a[$i]}.log
######    root -l -b -q 'performance/compare_unfolding.C++("pp","'${verName_a[$i]}'")' >& log/compare_unfolding_pp_${verName_a[$i]}.log
#####done
##
##verFileCopy_a=('190703_temp_v31')
##verName_a=('190703_temp_v31_nominal')
##preverName_a=('190220_temp_v26_nominal')
##
##for ((i=0; i< ${#verName_a[@]};i++))
##do
##    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
####    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pbpb","'${verName_a[$i]}'")' >& log/iso_efficiency_withSkimFile_v3_pbpb_${verName_a[$i]}.log & sleep 20 
###    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_a[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_a[$i]}.log & sleep 20
####    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pbpb","'${verName_a[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pbpb_${verName_a[$i]}.log & sleep 20
####    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_a[$i]}'")' >& log/correlation_pbpb_${verName_a[$i]}.log & sleep 20
####    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pbpb","'${verName_a[$i]}'",1)' >& log/correlation_pbpb_${verName_a[$i]}_splitMC.log & sleep 20 
####    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v3.C++("pp","'${verName_a[$i]}'")' >& log/iso_efficiency_withSkimFile_v3_pp_${verName_a[$i]}.log & sleep 20
###    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_a[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_a[$i]}.log & sleep 20
####    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pp","'${verName_a[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pp_${verName_a[$i]}.log & sleep 20
####    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_a[$i]}'")' >& log/correlation_pp_${verName_a[$i]}.log & sleep 20 
####    root -l -b -q 'performance/correlation_genPt_recoPt_v3.C++("pp","'${verName_a[$i]}'",1)' >& log/correlation_pp_${verName_a[$i]}_splitMC.log & sleep 20
####    root -l -b -q 'results/getRawDist_v8.C++("'${verName_a[$i]}'",1,1)' >& log/getRawDist_v8_${verName_a[$i]}.log & sleep 20 
###    wait $(jobs -p)
####    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_a[$i]}'",1,1)' >& log/fitPurity_pbpb_${verName_a[$i]}.log & sleep 20
####    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_a[$i]}'",1,1)' >& log/fitPurity_pp_${verName_a[$i]}.log & sleep 20
###    root -l -b -q 'purity/fitPurity_temp_v3.C++("pbpb","'${verName_a[$i]}'",1,1,2)' >& log/fitPurity_temp_v3_pbpb_${verName_a[$i]}.log & sleep 20
###    root -l -b -q 'purity/fitPurity_temp_v3.C++("pp","'${verName_a[$i]}'",1,1,2)' >& log/fitPurity_temp_v3_pp_${verName_a[$i]}.log & sleep 20
####    root -l -b -q 'purity/fitPurity_temp_v4.C++("pbpb","'${verName_a[$i]}'",1,1,2)' >& log/fitPurity_temp_v4_pbpb_${verName_a[$i]}.log & sleep 20
####    root -l -b -q 'purity/fitPurity_temp_v4.C++("pp","'${verName_a[$i]}'",1,1,2)' >& log/fitPurity_temp_v4_pp_${verName_a[$i]}.log & sleep 20
###    wait $(jobs -p)
###    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_a[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_a[$i]}.log
###    source /data/ROOT-v5.34.21/bin/thisroot.sh
###    python results/RooUnfold_photonRaa_v6.py ${verName_a[$i]} inv 0 noSplitMC >& log/RooUnfold_photonRaa_v6_${verName_a[$i]}.log
###    source /home/goyeonju/root/builddir/bin/thisroot.sh
####    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_a[$i]}'")' >& log/drawUnfoldingFigures_${verName_a[$i]}.log
#######    root -l -b -q 'performance/divideTree.C++' >& log/divideTree_pbpb_20180815skim.log
####    source /data/ROOT-v5.34.21/bin/thisroot.sh
####    python results/RooUnfold_photonRaa_v6.py ${verName_a[$i]} inv 0 splitMC >& log/RooUnfold_photonRaa_v6_${verName_a[$i]}_splitMC.log
####    source /home/goyeonju/root/builddir/bin/thisroot.sh
####    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_a[$i]}'",1)' >& log/drawUnfoldingFigures_${verName_a[$i]}_splitMC.log
###    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_a[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_a[$i]}.log
###    
####     cp ./results/output/phoRaa_${preverName_a[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_a[$i]}_beforeUnfolding.root
####    root -l -b -q 'performance/compare_unfolding.C++("pbpb","'${verName_a[$i]}'")' >& log/compare_unfolding_pbpb_${verName_a[$i]}.log
####    root -l -b -q 'performance/compare_unfolding.C++("pp","'${verName_a[$i]}'")' >& log/compare_unfolding_pp_${verName_a[$i]}.log
##done
###
##cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
##root -l -b -q 'systematics/calc_systematic.C++("'${verFileCopy_a}'")' >& log/systematics_${verFileCopy_a}.log
##root -l -b -q 'systematics/drawSystematicPlots.C++("'${verFileCopy_a}'")' >& log/drawSystematicsPlots_${verFileCopy_a}.log
##root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4.C++("'${verFileCopy_a}'")' >& log/plotting_v4_${verFileCopy_a}.log
##root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verFileCopy_a}'")' >& log/plotting_v4_${verFileCopy_a}.log
##root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verFileCopy_d}'")' >& log/plotting_v4_${verFileCopy_d}.log
###root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verFileCopy_dmore}'")' >& log/plotting_v4_${verFileCopy_dmore}.log
###root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verFileCopy_dmore2}'")' >& log/plotting_v4_${verFileCopy_dmore2}.log
##root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verFileCopy_dmore3}'")' >& log/plotting_v4_${verFileCopy_dmore3}.log
##root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verFileCopy_dmore4}'")' >& log/plotting_v4_${verFileCopy_dmore4}.log
##root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verFileCopy_dmore5}'")' >& log/plotting_v4_${verFileCopy_dmore5}.log
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verFileCopy_ab}'")' >& log/plotting_v4_${verFileCopy_ab}.log
