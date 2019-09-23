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

####int yj_quickPhotonPurity_v3(const TString coll="pp", const TString ver="phoRaaCuts_purity_forPaper", 
####                            bool doSplitPD=1, bool doPreScale=0, bool useSBcorr=1, bool centDepCorr=0, int ptDepCorrThr=0, int Nfunc=0, bool useMCSB=0, bool use30trig=0){
#verFileCopy_side13=('190703_temp_v31_sidebandSigEffat85')
#verName_side13=('190703_temp_v31_pur_sidebandSigEffat85')
#preverName_side13=('190220_temp_v26_nominal')
#for ((i=0; i< ${#verName_side13[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_side13[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_side13[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_side13[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pbpb","'${verName_side13[$i]}'",1,0,0,0,50,1)' >& log/yj_quickPhotonPurity_v4_noPreScale_pbpb_${verName_side13[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pp","'${verName_side13[$i]}'",1,0,0,0,50,1)' >& log/yj_quickPhotonPurity_v4_noPreScale_pp_${verName_side13[$i]}.log
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_side13[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_side13[$i]}_pp.root 
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_side13[$i]}_splitPD.root
#    wait $(jobs -p)
#    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_side13[$i]}'",2,1)' >& log/fitPurity_pbpb_${verName_side13[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_side13[$i]}'",2,1)' >& log/fitPurity_pp_${verName_side13[$i]}.log & sleep 20
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_side13[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_side13[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_side13[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_side13[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_side13[$i]}'")' >& log/drawUnfoldingFigures_${verName_side13[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_side13[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_side13[$i]}.log
#done
#cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side13}'")' >& log/plotting_v4_${verName_side13}.log

verFileCopy_side19=('190703_temp_v31_sidebandSigEffat85')
verName_side19=('190703_temp_v31_pur_sidebandSigEffat85_SBcorr_noCentDep_ptDep_Nfunc0')
preverName_side19=('190220_temp_v26_nominal')
for ((i=0; i< ${#verName_side19[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_side19[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_side19[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_side19[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pbpb","'${verName_side19[$i]}'",1,0,1,0,50,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pbpb_${verName_side19[$i]}.log & sleep 20
#    cp ./purity/output/purity_pp_190703_temp_v31_pur_sidebandSigEffat85_SBcorr_centDep_noPtDep_Nfunc0_splitPD_noPreScale.root ./purity/output/purity_pp_${verName_side19[$i]}_splitPD_noPreScale.root
##    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pp","'${verName_side19[$i]}'",1,0,1,0,50,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pp_${verName_side19[$i]}.log
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_side19[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_side19[$i]}_pp.root 
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_side19[$i]}_splitPD.root
#    wait $(jobs -p)
    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_side19[$i]}'",2,1)' >& log/fitPurity_pbpb_${verName_side19[$i]}.log & sleep 20
    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_side19[$i]}'",2,1)' >& log/fitPurity_pp_${verName_side19[$i]}.log & sleep 20
    wait $(jobs -p)
    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_side19[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_side19[$i]}.log
    source /data/ROOT-v5.34.21/bin/thisroot.sh
    python results/RooUnfold_photonRaa_v6.py ${verName_side19[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_side19[$i]}.log
    source /home/goyeonju/root/builddir/bin/thisroot.sh
    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_side19[$i]}'")' >& log/drawUnfoldingFigures_${verName_side19[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_side19[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_side19[$i]}.log
done
cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side19}'")' >& log/plotting_v4_${verName_side19}.log
#
verFileCopy_side20=('190703_temp_v31_sidebandSigEffat85_v2')
verName_side20=('190703_temp_v31_pur_sidebandSigEffat85_v2_SBcorr_noCentDep_ptDep_Nfunc0')
preverName_side20=('190220_temp_v26_nominal')
for ((i=0; i< ${#verName_side20[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_side20[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_side20[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_side20[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pbpb","'${verName_side20[$i]}'",1,0,1,0,50,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pbpb_${verName_side20[$i]}.log & sleep 20
#    cp ./purity/output/purity_pp_190703_temp_v31_pur_sidebandSigEffat85_v2_SBcorr_centDep_noPtDep_Nfunc0_splitPD_noPreScale.root ./purity/output/purity_pp_${verName_side20[$i]}_splitPD_noPreScale.root
#    #root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pp","'${verName_side20[$i]}'",1,0,1,0,50,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pp_${verName_side20[$i]}.log
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_side20[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_side20[$i]}_pp.root 
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_side20[$i]}_splitPD.root
#    wait $(jobs -p)
    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_side20[$i]}'",2,1)' >& log/fitPurity_pbpb_${verName_side20[$i]}.log & sleep 20
    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_side20[$i]}'",2,1)' >& log/fitPurity_pp_${verName_side20[$i]}.log & sleep 20
    wait $(jobs -p)
    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_side20[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_side20[$i]}.log
    source /data/ROOT-v5.34.21/bin/thisroot.sh
    python results/RooUnfold_photonRaa_v6.py ${verName_side20[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_side20[$i]}.log
    source /home/goyeonju/root/builddir/bin/thisroot.sh
    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_side20[$i]}'")' >& log/drawUnfoldingFigures_${verName_side20[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_side20[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_side20[$i]}.log
done
cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side20}'")' >& log/plotting_v4_${verName_side20}.log

#verFileCopy_side18=('190703_temp_v31_sidebandSigEffat85')
#verName_side18=('190703_temp_v31_pur_sidebandSigEffat85_SBcorr_centDep_noPtDep_Nfunc0')
#preverName_side18=('190220_temp_v26_nominal')
#for ((i=0; i< ${#verName_side18[@]};i++))
#do
##    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_side18[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
##    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_side18[$i]}.root
##    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_side18[$i]}.root
##    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pbpb","'${verName_side18[$i]}'",1,0,1,1,0,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pbpb_${verName_side18[$i]}.log & sleep 20
##    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pp","'${verName_side18[$i]}'",1,0,1,0,50,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pp_${verName_side18[$i]}.log
##    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_side18[$i]}_pbpb.root 
##    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_side18[$i]}_pp.root 
##    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_side18[$i]}_splitPD.root
##    wait $(jobs -p)
##    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_side18[$i]}'",2,1)' >& log/fitPurity_pbpb_${verName_side18[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_side18[$i]}'",2,1)' >& log/fitPurity_pp_${verName_side18[$i]}.log & sleep 20
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_side18[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_side18[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_side18[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_side18[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_side18[$i]}'")' >& log/drawUnfoldingFigures_${verName_side18[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_side18[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_side18[$i]}.log
#done
#cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side18}'")' >& log/plotting_v4_${verName_side18}.log
#
#verFileCopy_side16=('190703_temp_v31_sidebandSigEffat85')
#verName_side16=('190703_temp_v31_pur_sidebandSigEffat85_SBcorr_centDep_noPtDep_Nfunc1')
#preverName_side16=('190220_temp_v26_nominal')
#for ((i=0; i< ${#verName_side16[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_side16[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_side16[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_side16[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pbpb","'${verName_side16[$i]}'",1,0,1,1,0,1)' >& log/yj_quickPhotonPurity_v4_noPreScale_pbpb_${verName_side16[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pp","'${verName_side16[$i]}'",1,0,1,0,50,1)' >& log/yj_quickPhotonPurity_v4_noPreScale_pp_${verName_side16[$i]}.log
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_side16[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_side16[$i]}_pp.root 
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_side16[$i]}_splitPD.root
#    wait $(jobs -p)
#    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_side16[$i]}'",2,1)' >& log/fitPurity_pbpb_${verName_side16[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_side16[$i]}'",2,1)' >& log/fitPurity_pp_${verName_side16[$i]}.log & sleep 20
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_side16[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_side16[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_side16[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_side16[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_side16[$i]}'")' >& log/drawUnfoldingFigures_${verName_side16[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_side16[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_side16[$i]}.log
#done
#cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side16}'")' >& log/plotting_v4_${verName_side16}.log
#
#verFileCopy_side15=('190703_temp_v31_sidebandSigEffat85_v2')
#verName_side15=('190703_temp_v31_pur_sidebandSigEffat85_v2_SBcorr_centDep_noPtDep_Nfunc1')
#preverName_side15=('190220_temp_v26_nominal')
#for ((i=0; i< ${#verName_side15[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_side15[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_side15[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_side15[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pbpb","'${verName_side15[$i]}'",1,0,1,1,0,1)' >& log/yj_quickPhotonPurity_v4_noPreScale_pbpb_${verName_side15[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pp","'${verName_side15[$i]}'",1,0,1,0,50,1)' >& log/yj_quickPhotonPurity_v4_noPreScale_pp_${verName_side15[$i]}.log
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_side15[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_side15[$i]}_pp.root 
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_side15[$i]}_splitPD.root
#    wait $(jobs -p)
#    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_side15[$i]}'",2,1)' >& log/fitPurity_pbpb_${verName_side15[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_side15[$i]}'",2,1)' >& log/fitPurity_pp_${verName_side15[$i]}.log & sleep 20
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_side15[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_side15[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_side15[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_side15[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_side15[$i]}'")' >& log/drawUnfoldingFigures_${verName_side15[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_side15[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_side15[$i]}.log
#done
#cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side15}'")' >& log/plotting_v4_${verName_side15}.log
#
#
#verFileCopy_side17=('190703_temp_v31_sidebandSigEffat85_v2')
#verName_side17=('190703_temp_v31_pur_sidebandSigEffat85_v2_SBcorr_centDep_noPtDep_Nfunc0')
#preverName_side17=('190220_temp_v26_nominal')
#for ((i=0; i< ${#verName_side17[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_side17[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_side17[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_side17[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pbpb","'${verName_side17[$i]}'",1,0,1,1,0,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pbpb_${verName_side17[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pp","'${verName_side17[$i]}'",1,0,1,0,50,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pp_${verName_side17[$i]}.log
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_side17[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_side17[$i]}_pp.root 
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_side17[$i]}_splitPD.root
#    wait $(jobs -p)
#    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_side17[$i]}'",2,1)' >& log/fitPurity_pbpb_${verName_side17[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_side17[$i]}'",2,1)' >& log/fitPurity_pp_${verName_side17[$i]}.log & sleep 20
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_side17[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_side17[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_side17[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_side17[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_side17[$i]}'")' >& log/drawUnfoldingFigures_${verName_side17[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_side17[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_side17[$i]}.log
#done
#cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side17}'")' >& log/plotting_v4_${verName_side17}.log
#
#
#verFileCopy_side14=('190703_temp_v31_sidebandSigEffat85_v2')
#verName_side14=('190703_temp_v31_pur_sidebandSigEffat85_v2')
#preverName_side14=('190220_temp_v26_nominal')
#for ((i=0; i< ${#verName_side14[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_side14[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_side14[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_side14[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pbpb","'${verName_side14[$i]}'",1,0,0,0,50,1)' >& log/yj_quickPhotonPurity_v4_noPreScale_pbpb_${verName_side14[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pp","'${verName_side14[$i]}'",1,0,0,0,50,1)' >& log/yj_quickPhotonPurity_v4_noPreScale_pp_${verName_side14[$i]}.log
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_side14[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_side14[$i]}_pp.root 
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_side14[$i]}_splitPD.root
#    wait $(jobs -p)
#    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_side14[$i]}'",2,1)' >& log/fitPurity_pbpb_${verName_side14[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_side14[$i]}'",2,1)' >& log/fitPurity_pp_${verName_side14[$i]}.log & sleep 20
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_side14[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_side14[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_side14[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_side14[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_side14[$i]}'")' >& log/drawUnfoldingFigures_${verName_side14[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_side14[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_side14[$i]}.log
#done
#cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side14}'")' >& log/plotting_v4_${verName_side14}.log


#verFileCopy_side6=('190703_temp_v31_sideband40to50')
#verName_side6=('190703_temp_v31_pur_SBcorr_noCentDep_ptDep50_sideband40to50_Nfunc1')
#preverName_side6=('190220_temp_v26_nominal')
#
#for ((i=0; i< ${#verName_side6[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_side6[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_side6[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_side6[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_side6[$i]}'",1,0,1,0,50,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_side6[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_side6[$i]}'",1,0,1,0,50,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_side6[$i]}.log
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_side6[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_side6[$i]}_pp.root 
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_side6[$i]}_splitPD.root
#    wait $(jobs -p)
#    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_side6[$i]}'",2,1)' >& log/fitPurity_pbpb_${verName_side6[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_side6[$i]}'",2,1)' >& log/fitPurity_pp_${verName_side6[$i]}.log & sleep 20
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_side6[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_side6[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_side6[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_side6[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_side6[$i]}'")' >& log/drawUnfoldingFigures_${verName_side6[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_side6[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_side6[$i]}.log
#done
#cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side6}'")' >& log/plotting_v4_${verName_side6}.log
#
#verFileCopy_side7=('190703_temp_v31_sideband30to40')
#verName_side7=('190703_temp_v31_pur_SBcorr_noCentDep_ptDep50_sideband30to40_Nfunc1')
#preverName_side7=('190220_temp_v26_nominal')
#
#for ((i=0; i< ${#verName_side7[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_side7[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_side7[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_side7[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_side7[$i]}'",1,0,1,0,50,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_side7[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_side7[$i]}'",1,0,1,0,50,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_side7[$i]}.log
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_side7[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_side7[$i]}_pp.root 
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_side7[$i]}_splitPD.root
#    wait $(jobs -p)
#    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_side7[$i]}'",2,1)' >& log/fitPurity_pbpb_${verName_side7[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_side7[$i]}'",2,1)' >& log/fitPurity_pp_${verName_side7[$i]}.log & sleep 20
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_side7[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_side7[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_side7[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_side7[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_side7[$i]}'")' >& log/drawUnfoldingFigures_${verName_side7[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_side7[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_side7[$i]}.log
#done
#cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side7}'")' >& log/plotting_v4_${verName_side7}.log
#
#verFileCopy_side8=('190703_temp_v31_sideband20to30')
#verName_side8=('190703_temp_v31_pur_SBcorr_noCentDep_ptDep50_sideband20to30_Nfunc1')
#preverName_side8=('190220_temp_v26_nominal')
#
#for ((i=0; i< ${#verName_side8[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_side8[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_side8[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_side8[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_side8[$i]}'",1,0,1,0,50,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_side8[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_side8[$i]}'",1,0,1,0,50,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_side8[$i]}.log
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_side8[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_side8[$i]}_pp.root 
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_side8[$i]}_splitPD.root
#    wait $(jobs -p)
#    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_side8[$i]}'",2,1)' >& log/fitPurity_pbpb_${verName_side8[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_side8[$i]}'",2,1)' >& log/fitPurity_pp_${verName_side8[$i]}.log & sleep 20
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_side8[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_side8[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_side8[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_side8[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_side8[$i]}'")' >& log/drawUnfoldingFigures_${verName_side8[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_side8[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_side8[$i]}.log
#done
#cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side8}'")' >& log/plotting_v4_${verName_side8}.log
#
#verFileCopy_side9=('190703_temp_v31')
#verName_side9=('190703_temp_v31_pur_SBcorr_noCentDep_ptDep50_sideband10to20_Nfunc1')
#preverName_side9=('190220_temp_v26_nominal')
#
#for ((i=0; i< ${#verName_side9[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_side9[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_side9[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_side9[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_side9[$i]}'",1,0,1,0,50,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_side9[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_side9[$i]}'",1,0,1,0,50,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_side9[$i]}.log
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_side9[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_side9[$i]}_pp.root 
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_side9[$i]}_splitPD.root
#    wait $(jobs -p)
#    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_side9[$i]}'",2,1)' >& log/fitPurity_pbpb_${verName_side9[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_side9[$i]}'",2,1)' >& log/fitPurity_pp_${verName_side9[$i]}.log & sleep 20
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_side9[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_side9[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_side9[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_side9[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_side9[$i]}'")' >& log/drawUnfoldingFigures_${verName_side9[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_side9[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_side9[$i]}.log
#done
#cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side9}'")' >& log/plotting_v4_${verName_side9}.log
#
#verFileCopy_side10=('190703_temp_v31')
#verName_side10=('190703_temp_v31_pur_SBcorr_noCentDep_ptDep40_sideband10to20_Nfunc1')
#preverName_side10=('190220_temp_v26_nominal')
#
#for ((i=0; i< ${#verName_side10[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_side10[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_side10[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_side10[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_side10[$i]}'",1,0,1,0,40,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_side10[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_side10[$i]}'",1,0,1,0,40,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_side10[$i]}.log
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_side10[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_side10[$i]}_pp.root 
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_side10[$i]}_splitPD.root
#    wait $(jobs -p)
#    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_side10[$i]}'",2,1)' >& log/fitPurity_pbpb_${verName_side10[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_side10[$i]}'",2,1)' >& log/fitPurity_pp_${verName_side10[$i]}.log & sleep 20
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_side10[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_side10[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_side10[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_side10[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_side10[$i]}'")' >& log/drawUnfoldingFigures_${verName_side10[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_side10[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_side10[$i]}.log
#done
#cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side10}'")' >& log/plotting_v4_${verName_side10}.log
#
#verFileCopy_side5=('190703_temp_v31_sideband40to50')
#verName_side5=('190703_temp_v31_pur_SBcorr_noCentDep_ptDep50_sideband40to50_Nfunc0')
#preverName_side5=('190220_temp_v26_nominal')
#
#for ((i=0; i< ${#verName_side5[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_side5[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_side5[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_side5[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_side5[$i]}'",1,0,1,0,50,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_side5[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_side5[$i]}'",1,0,1,0,50,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_side5[$i]}.log
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_side5[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_side5[$i]}_pp.root 
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_side5[$i]}_splitPD.root
#    wait $(jobs -p)
#    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_side5[$i]}'",2,1)' >& log/fitPurity_pbpb_${verName_side5[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_side5[$i]}'",2,1)' >& log/fitPurity_pp_${verName_side5[$i]}.log & sleep 20
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_side5[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_side5[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_side5[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_side5[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_side5[$i]}'")' >& log/drawUnfoldingFigures_${verName_side5[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_side5[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_side5[$i]}.log
#done
#cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side5}'")' >& log/plotting_v4_${verName_side5}.log
#
#verFileCopy_side4=('190703_temp_v31_sideband30to40')
#verName_side4=('190703_temp_v31_pur_SBcorr_noCentDep_ptDep50_sideband30to40_Nfunc0')
#preverName_side4=('190220_temp_v26_nominal')
#
#for ((i=0; i< ${#verName_side4[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_side4[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_side4[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_side4[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_side4[$i]}'",1,0,1,0,50,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_side4[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_side4[$i]}'",1,0,1,0,50,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_side4[$i]}.log
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_side4[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_side4[$i]}_pp.root 
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_side4[$i]}_splitPD.root
#    wait $(jobs -p)
#    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_side4[$i]}'",2,1)' >& log/fitPurity_pbpb_${verName_side4[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_side4[$i]}'",2,1)' >& log/fitPurity_pp_${verName_side4[$i]}.log & sleep 20
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_side4[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_side4[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_side4[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_side4[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_side4[$i]}'")' >& log/drawUnfoldingFigures_${verName_side4[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_side4[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_side4[$i]}.log
#done
#cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side4}'")' >& log/plotting_v4_${verName_side4}.log
#
#verFileCopy_side3=('190703_temp_v31_sideband20to30')
#verName_side3=('190703_temp_v31_pur_SBcorr_noCentDep_ptDep50_sideband20to30_Nfunc0')
#preverName_side3=('190220_temp_v26_nominal')
#
#for ((i=0; i< ${#verName_side3[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_side3[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_side3[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_side3[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_side3[$i]}'",1,0,1,0,50,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_side3[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_side3[$i]}'",1,0,1,0,50,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_side3[$i]}.log
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_side3[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_side3[$i]}_pp.root 
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_side3[$i]}_splitPD.root
#    wait $(jobs -p)
#    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_side3[$i]}'",2,1)' >& log/fitPurity_pbpb_${verName_side3[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_side3[$i]}'",2,1)' >& log/fitPurity_pp_${verName_side3[$i]}.log & sleep 20
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_side3[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_side3[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_side3[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_side3[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_side3[$i]}'")' >& log/drawUnfoldingFigures_${verName_side3[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_side3[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_side3[$i]}.log
#done
#cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side3}'")' >& log/plotting_v4_${verName_side3}.log
#
#verFileCopy_side2=('190703_temp_v31')
#verName_side2=('190703_temp_v31_pur_SBcorr_noCentDep_ptDep50_sideband10to20_Nfunc0')
#preverName_side2=('190220_temp_v26_nominal')
#
#for ((i=0; i< ${#verName_side2[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_side2[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_side2[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_side2[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_side2[$i]}'",1,0,1,0,50,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_side2[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_side2[$i]}'",1,0,1,0,50,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_side2[$i]}.log
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_side2[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_side2[$i]}_pp.root 
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_side2[$i]}_splitPD.root
#    wait $(jobs -p)
#    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_side2[$i]}'",2,1)' >& log/fitPurity_pbpb_${verName_side2[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_side2[$i]}'",2,1)' >& log/fitPurity_pp_${verName_side2[$i]}.log & sleep 20
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_side2[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_side2[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_side2[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_side2[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_side2[$i]}'")' >& log/drawUnfoldingFigures_${verName_side2[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_side2[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_side2[$i]}.log
#done
#cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side2}'")' >& log/plotting_v4_${verName_side2}.log
#
#verFileCopy_side1=('190703_temp_v31')
#verName_side1=('190703_temp_v31_pur_SBcorr_noCentDep_ptDep40_sideband10to20_Nfunc0')
#preverName_side1=('190220_temp_v26_nominal')
#
#for ((i=0; i< ${#verName_side1[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_side1[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_side1[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_side1[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_side1[$i]}'",1,0,1,0,40,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_side1[$i]}.log & sleep 20
#    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_side1[$i]}'",1,0,1,0,40,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_side1[$i]}.log
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_side1[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_side1[$i]}_pp.root 
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_side1[$i]}_splitPD.root
#    wait $(jobs -p)
#    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_side1[$i]}'",2,1)' >& log/fitPurity_pbpb_${verName_side1[$i]}.log & sleep 20
#    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_side1[$i]}'",2,1)' >& log/fitPurity_pp_${verName_side1[$i]}.log & sleep 20
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_side1[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_side1[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_side1[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_side1[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_side1[$i]}'")' >& log/drawUnfoldingFigures_${verName_side1[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_side1[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_side1[$i]}.log
#done
#cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side1}'")' >& log/plotting_v4_${verName_side1}.log



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
###    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_ab[$i]}.root
###    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_ab[$i]}.root
###    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_ab[$i]}'",1,0,1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_SBcorr_noCentDepCorr_pbpb_${verName_ab[$i]}.log & sleep 20
###    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_ab[$i]}'",1,0,1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_SBcorr_noCentDepCorr_pp_${verName_ab[$i]}.log
###    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_ab[$i]}_pbpb.root 
###    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_ab[$i]}_pp.root 
###    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_ab[$i]}_splitPD.root
###    wait $(jobs -p)
##    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_ab[$i]}'",2,1)' >& log/fitPurity_pbpb_${verName_ab[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_ab[$i]}'",2,1)' >& log/fitPurity_pp_${verName_ab[$i]}.log & sleep 20
##    wait $(jobs -p)
##    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_ab[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_ab[$i]}.log
##    source /data/ROOT-v5.34.21/bin/thisroot.sh
##    python results/RooUnfold_photonRaa_v6.py ${verName_ab[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_ab[$i]}.log
##    source /home/goyeonju/root/builddir/bin/thisroot.sh
##    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_ab[$i]}'")' >& log/drawUnfoldingFigures_${verName_ab[$i]}.log
##    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_ab[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_ab[$i]}.log
#done
###
#
##verFileCopy_un=('190703_temp_v31')
##verName_un=('190703_temp_v31_sys_unfolding_MCsize')
##for ((i=0; i< ${#verName_un[@]};i++))
##do
##    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_un[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
##    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_un[$i]}_splitPD.root
##    root -l -b -q 'toyStudy_responseMatrix.C++("pp","'${verName_un[$i]}'")' >& log/correlation_toyStudy_responseMatrix_pp_${verName_un[$i]}.log
##    root -l -b -q 'toyStudy_responseMatrix.C++("pbpb","'${verName_un[$i]}'")' >& log/correlation_toyStudy_responseMatrix_pbpb_${verName_un[$i]}.log
##    cp ./results/output/phoRaa_${verName_a[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_un[$i]}_beforeUnfolding.root
##    source /data/ROOT-v5.34.21/bin/thisroot.sh
##    python results/RooUnfold_photonRaa_v6.py ${verName_un[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_un[$i]}.log
##    source /home/goyeonju/root/builddir/bin/thisroot.sh
##    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_un[$i]}'",1)' >& log/drawUnfoldingFigures_${verName_un[$i]}_splitMC.log
##    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_un[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_un[$i]}.log
##done
#
#
#########for j in 1 2 3 4 5 6 7 8 9 10
########for j in 100 1 2 3 4 5 6 7 8 9 10
##for j in {1..10} 
##do
##    verFileCopy_l=('190703_temp_v31')
##    verName_l=('190703_temp_v31_sys_unfolding_svd'$j)
##    for ((i=0; i< ${#verName_l[@]};i++))
##    do
##        cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_l[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
##        cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_l[$i]}_splitPD.root
##        cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_l[$i]}_pbpb.root 
##        cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_l[$i]}_pp.root 
##        cp ./results/output/phoRaa_${verName_a[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_l[$i]}_beforeUnfolding.root
##        source /data/ROOT-v5.34.21/bin/thisroot.sh
##        python results/RooUnfold_photonRaa_v6.py ${verName_l[$i]} svd $j noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_l[$i]}.log
##        source /home/goyeonju/root/builddir/bin/thisroot.sh
##        root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_l[$i]}'")' >& log/drawUnfoldingFigures_${verName_l[$i]}.log
##        cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb_splitMC.root ./performance/output/correlation_genPt_recoPt_${verName_l[$i]}_pbpb_splitMC.root 
##        cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp_splitMC.root ./performance/output/correlation_genPt_recoPt_${verName_l[$i]}_pp_splitMC.root 
##        source /data/ROOT-v5.34.21/bin/thisroot.sh
##        python results/RooUnfold_photonRaa_v6.py ${verName_l[$i]} svd $j splitMC >& log/RooUnfold_photonRaa_v6_${verName_l[$i]}_splitMC.log
##        source /home/goyeonju/root/builddir/bin/thisroot.sh
##        root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_l[$i]}'",1)' >& log/drawUnfoldingFigures_${verName_l[$i]}_splitMC.log
##        root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_l[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_l[$i]}.log
##    done
##done
##
###for j in 1 2 3 4 5 6 7 8 9 10
###for j in {100..105}
##for j in {1..30}
##do
##    verFileCopy_m=('190703_temp_v31')
##    verName_m=('190703_temp_v31_sys_unfolding_iterative'$j)
##    for ((i=0; i< ${#verName_m[@]};i++))
##    do
##        cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_m[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
##        cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_m[$i]}_splitPD.root
##        cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_m[$i]}_pbpb.root 
##        cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_m[$i]}_pp.root 
##        cp ./results/output/phoRaa_${verName_a[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_m[$i]}_beforeUnfolding.root
##        source /data/ROOT-v5.34.21/bin/thisroot.sh
##        python results/RooUnfold_photonRaa_v6.py ${verName_m[$i]} $j 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_m[$i]}.log
##        source /home/goyeonju/root/builddir/bin/thisroot.sh
##        root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_m[$i]}'")' >& log/drawUnfoldingFigures_${verName_m[$i]}.log
##        cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb_splitMC.root ./performance/output/correlation_genPt_recoPt_${verName_m[$i]}_pbpb_splitMC.root 
##        cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp_splitMC.root ./performance/output/correlation_genPt_recoPt_${verName_m[$i]}_pp_splitMC.root 
##        source /data/ROOT-v5.34.21/bin/thisroot.sh
##        python results/RooUnfold_photonRaa_v6.py ${verName_m[$i]} $j 0 splitMC >& log/RooUnfold_photonRaa_v6_${verName_m[$i]}_splitMC.log
##        source /home/goyeonju/root/builddir/bin/thisroot.sh
##        root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_m[$i]}'",1)' >& log/drawUnfoldingFigures_${verName_m[$i]}.log
##        root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_m[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_m[$i]}.log
##    done
##done
###
###
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
#verFileCopy_dmore4=('190703_temp_v31_sys_purDown_more4')
#verName_dmore4=('190703_temp_v31_sys_purDown_more4')
#preverName_dmore4=('180822_temp_v24_sys_purDown_more4')
#for ((i=0; i< ${#verName_dmore4[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_dmore4[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
##    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_dmore4[$i]}.root
##    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_dmore4[$i]}.root
##    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pbpb","'${verName_dmore4[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pbpb_${verName_dmore4[$i]}.log & sleep 20
##    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pp","'${verName_dmore4[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pp_${verName_dmore4[$i]}.log & sleep 20
##    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_dmore4[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_dmore4[$i]}.log & sleep 20
##    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_dmore4[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_dmore4[$i]}.log & sleep 20
#    wait $(jobs -p)
##    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_dmore4[$i]}_pbpb.root 
##    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_dmore4[$i]}_pp.root 
##    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_dmore4[$i]}_splitPD.root
##    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_dmore4[$i]}'",1,1)' >& log/fitPurity_pbpb_${verName_dmore4[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_dmore4[$i]}'",1,1)' >& log/fitPurity_pp_${verName_dmore4[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity_temp_v4.C++("pbpb","'${verName_dmore4[$i]}'",1,1,2)' >& log/fitPurity_temp_v4_pbpb_${verName_dmore4[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity_temp_v4.C++("pp","'${verName_dmore4[$i]}'",1,1,2)' >& log/fitPurity_temp_v4_pp_${verName_dmore4[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity_temp_v3.C++("pbpb","'${verName_dmore4[$i]}'",1,1,2)' >& log/fitPurity_temp_v3_pbpb_${verName_dmore4[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity_temp_v3.C++("pp","'${verName_dmore4[$i]}'",1,1,2)' >& log/fitPurity_temp_v3_pp_${verName_dmore4[$i]}.log & sleep 20
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v8_beforeUnfolding_withTnP.C++("'${verName_dmore4[$i]}'",1)' >& log/drawRaaXsec_v8_beforeUnfolding_withTnP_${verName_dmore4[$i]}.log
##root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_dmore4[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_dmore4[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_dmore4[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_dmore4[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
##    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_dmore4[$i]}'")' >& log/drawUnfoldingFigures_${verName_dmore4[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_dmore4[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_dmore4[$i]}.log
#done
##
##
#verFileCopy_dmore3=('190703_temp_v31_sys_purDown_more3')
#verName_dmore3=('190703_temp_v31_sys_purDown_more3')
#preverName_dmore3=('180822_temp_v24_sys_purDown_more3')
#for ((i=0; i< ${#verName_dmore3[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_dmore3[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
####    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_dmore3[$i]}.root
####    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_dmore3[$i]}.root
###    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pbpb","'${verName_dmore3[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pbpb_${verName_dmore3[$i]}.log & sleep 20
###    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pp","'${verName_dmore3[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pp_${verName_dmore3[$i]}.log & sleep 20
##    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_dmore3[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_dmore3[$i]}.log & sleep 20
##    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_dmore3[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_dmore3[$i]}.log & sleep 20
##    wait $(jobs -p)
####    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_dmore3[$i]}_pbpb.root 
####    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_dmore3[$i]}_pp.root 
####    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_dmore3[$i]}_splitPD.root
####    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_dmore3[$i]}'",1,1)' >& log/fitPurity_pbpb_${verName_dmore3[$i]}.log & sleep 20
####    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_dmore3[$i]}'",1,1)' >& log/fitPurity_pp_${verName_dmore3[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity_temp_v3.C++("pbpb","'${verName_dmore3[$i]}'",1,1,2)' >& log/fitPurity_temp_v4_pbpb_${verName_dmore3[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity_temp_v3.C++("pp","'${verName_dmore3[$i]}'",1,1,2)' >& log/fitPurity_temp_v4_pp_${verName_dmore3[$i]}.log & sleep 20
###    root -l -b -q 'purity/fitPurity_temp_v4.C++("pbpb","'${verName_dmore3[$i]}'",1,1,2)' >& log/fitPurity_temp_v3_pbpb_${verName_dmore3[$i]}.log & sleep 20
###    root -l -b -q 'purity/fitPurity_temp_v4.C++("pp","'${verName_dmore3[$i]}'",1,1,2)' >& log/fitPurity_temp_v3_pp_${verName_dmore3[$i]}.log & sleep 20
##    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v8_beforeUnfolding_withTnP.C++("'${verName_dmore3[$i]}'",1)' >& log/drawRaaXsec_v8_beforeUnfolding_withTnP_${verName_dmore3[$i]}.log
##root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_dmore3[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_dmore3[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_dmore3[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_dmore3[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_dmore3[$i]}'")' >& log/drawUnfoldingFigures_${verName_dmore3[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_dmore3[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_dmore3[$i]}.log
#done
##
##
##verFileCopy_dmore2=('190703_temp_v31_sys_purDown_more2')
##verName_dmore2=('190703_temp_v31_sys_purDown_more2')
##preverName_dmore2=('180822_temp_v24_sys_purDown_more2')
##for ((i=0; i< ${#verName_dmore2[@]};i++))
##do
##    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_dmore2[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
####    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_dmore2[$i]}.root
####    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_dmore2[$i]}.root
####    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_dmore2[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_dmore2[$i]}.log & sleep 20
####    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_dmore2[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_dmore2[$i]}.log
####    wait $(jobs -p)
####    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_dmore2[$i]}_pbpb.root 
####    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_dmore2[$i]}_pp.root 
####    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_dmore2[$i]}_splitPD.root
##    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_dmore2[$i]}'",1,1,2)' >& log/fitPurity_pbpb_${verName_dmore2[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_dmore2[$i]}'",1,1,2)' >& log/fitPurity_pp_${verName_dmore2[$i]}.log & sleep 20
##    wait $(jobs -p)
##    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_dmore2[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_dmore2[$i]}.log
##    source /data/ROOT-v5.34.21/bin/thisroot.sh
##    python results/RooUnfold_photonRaa_v6.py ${verName_dmore2[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_dmore2[$i]}.log
##    source /home/goyeonju/root/builddir/bin/thisroot.sh
##    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_dmore2[$i]}'")' >& log/drawUnfoldingFigures_${verName_dmore2[$i]}.log
##    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_dmore2[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_dmore2[$i]}.log
##done
###
##
##verFileCopy_dmore=('190703_temp_v31_sys_purDown_more')
##verName_dmore=('190703_temp_v31_sys_purDown_more')
##preverName_dmore=('180822_temp_v24_sys_purDown_more')
##for ((i=0; i< ${#verName_dmore[@]};i++))
##do
##    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_dmore[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
####    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_dmore[$i]}.root
####    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_dmore[$i]}.root
####    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_dmore[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_dmore[$i]}.log & sleep 20
####    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_dmore[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_dmore[$i]}.log
####    wait $(jobs -p)
####    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_dmore[$i]}_pbpb.root 
####    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_dmore[$i]}_pp.root 
####    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_dmore[$i]}_splitPD.root
##    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_dmore[$i]}'",1,1,2)' >& log/fitPurity_pbpb_${verName_dmore[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_dmore[$i]}'",1,1,2)' >& log/fitPurity_pp_${verName_dmore[$i]}.log & sleep 20
##    wait $(jobs -p)
##    root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_dmore[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_dmore[$i]}.log
##    source /data/ROOT-v5.34.21/bin/thisroot.sh
##    python results/RooUnfold_photonRaa_v6.py ${verName_dmore[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_dmore[$i]}.log
##    source /home/goyeonju/root/builddir/bin/thisroot.sh
##    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_dmore[$i]}'")' >& log/drawUnfoldingFigures_${verName_dmore[$i]}.log
##    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_dmore[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_dmore[$i]}.log
##done
##
#verFileCopy_d=('190703_temp_v31_sys_purDown')
#verName_d=('190703_temp_v31_sys_purDown')
#preverName_d=('180822_temp_v24_sys_purDown')
#for ((i=0; i< ${#verName_d[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_d[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#####    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_d[$i]}.root
#####    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_d[$i]}.root
###    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pbpb","'${verName_d[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pbpb_${verName_d[$i]}.log & sleep 20
###    root -l -b -q 'purity/yj_quickPhotonPurity_v4.C++("pp","'${verName_d[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v4_noPreScale_pp_${verName_d[$i]}.log & sleep 20
##    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pbpb","'${verName_d[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pbpb_${verName_d[$i]}.log & sleep 20
##    root -l -b -q 'purity/yj_quickPhotonPurity_v3.C++("pp","'${verName_d[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v3_noPreScale_pp_${verName_d[$i]}.log & sleep 20
##    wait $(jobs -p)
#####    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_d[$i]}_pbpb.root 
#####    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_d[$i]}_pp.root 
#####    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_d[$i]}_splitPD.root
#####    root -l -b -q 'purity/fitPurity.C++("pbpb","'${verName_d[$i]}'",1,1)' >& log/fitPurity_pbpb_${verName_d[$i]}.log & sleep 20
#####    root -l -b -q 'purity/fitPurity.C++("pp","'${verName_d[$i]}'",1,1)' >& log/fitPurity_pp_${verName_d[$i]}.log & sleep 20
###    root -l -b -q 'purity/fitPurity_temp_v4.C++("pbpb","'${verName_d[$i]}'",1,1,2)' >& log/fitPurity_temp_v4_pbpb_${verName_d[$i]}.log & sleep 20
###    root -l -b -q 'purity/fitPurity_temp_v4.C++("pp","'${verName_d[$i]}'",1,1,2)' >& log/fitPurity_temp_v4_pp_${verName_d[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity_temp_v3.C++("pbpb","'${verName_d[$i]}'",1,1,2)' >& log/fitPurity_temp_v3_pbpb_${verName_d[$i]}.log & sleep 20
##    root -l -b -q 'purity/fitPurity_temp_v3.C++("pp","'${verName_d[$i]}'",1,1,2)' >& log/fitPurity_temp_v3_pp_${verName_d[$i]}.log & sleep 20
#    wait $(jobs -p)
#    root -l -b -q 'results/drawRaaXsec_v8_beforeUnfolding_withTnP.C++("'${verName_d[$i]}'",1)' >& log/drawRaaXsec_v8_beforeUnfolding_withTnP_${verName_d[$i]}.log
##root -l -b -q 'results/drawRaaXsec_v7_beforeUnfolding_withTnP_temp.C++("'${verName_d[$i]}'",1)' >& log/drawRaaXsec_v7_beforeUnfolding_withTnP_temp_${verName_d[$i]}.log
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v6.py ${verName_d[$i]} inv 0 noSplitMC  >& log/RooUnfold_photonRaa_v6_${verName_d[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures_v3.C++("'${verName_d[$i]}'")' >& log/drawUnfoldingFigures_${verName_d[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v7_afterUnfolding.C++("'${verName_d[$i]}'",1)' >& log/drawRaaXsec_v7_afterUnfolding_${verName_d[$i]}.log
#done
#####
#cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side1}'")' >& log/plotting_v4_${verName_side1}.log
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side2}'")' >& log/plotting_v4_${verName_side2}.log
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side3}'")' >& log/plotting_v4_${verName_side3}.log
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side4}'")' >& log/plotting_v4_${verName_side4}.log
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side5}'")' >& log/plotting_v4_${verName_side5}.log
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side6}'")' >& log/plotting_v4_${verName_side6}.log
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side7}'")' >& log/plotting_v4_${verName_side7}.log
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side8}'")' >& log/plotting_v4_${verName_side8}.log
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side9}'")' >& log/plotting_v4_${verName_side9}.log
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verName_side10}'")' >& log/plotting_v4_${verName_side10}.log

#root -l -b -q 'systematics/calc_systematic.C++("'${verFileCopy_a}'")' >& log/systematics_${verFileCopy_a}.log
#root -l -b -q 'systematics/drawSystematicPlots.C++("'${verFileCopy_a}'")' >& log/drawSystematicsPlots_${verFileCopy_a}.log
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4.C++("'${verFileCopy_a}'")' >& log/plotting_v4_${verFileCopy_a}.log
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verFileCopy_a}'")' >& log/plotting_v4_${verFileCopy_a}.log
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verFileCopy_d}'")' >& log/plotting_v4_${verFileCopy_d}.log
##root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verFileCopy_dmore}'")' >& log/plotting_v4_${verFileCopy_dmore}.log
##root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verFileCopy_dmore2}'")' >& log/plotting_v4_${verFileCopy_dmore2}.log
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verFileCopy_dmore3}'")' >& log/plotting_v4_${verFileCopy_dmore3}.log
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verFileCopy_dmore4}'")' >& log/plotting_v4_${verFileCopy_dmore4}.log
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verFileCopy_dmore5}'")' >& log/plotting_v4_${verFileCopy_dmore5}.log
#root -l -b -q 'plotting/photonRaaPlot_withJetphox_v4_temp.C++("'${verFileCopy_ab}'")' >& log/plotting_v4_${verFileCopy_ab}.log
