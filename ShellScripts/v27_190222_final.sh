#!/bin/bash
#int yj_quickPhotonPurity_v2(const TString coll="pbpb", const TString ver="phoRaaCuts_purity_forPaper", bool doSplitPD=true, bool doPreScale=0, bool useSBcorr=0, bool noCentDepCorr=0, bool useMCSB=0){
#verFileCopy_a=('1800802_temp_v20')

verFileCopy_a=('190222_last_v27')
verName_a=('190222_last_v27_nominal')
preverName_a=('190220_temp_v26_nominal')
#
for ((i=0; i< ${#verName_a[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${preverName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${preverName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root
#    cp ./purity/output/purity_pbpb_${preverName_a[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_a[$i]}_splitPD.root
#    cp ./purity/output/purity_pp_${preverName_a[$i]}_splitPD.root ./purity/output/purity_pp_${verName_a[$i]}_splitPD.root
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v2.C++("pbpb","'${verName_a[$i]}'")' >& log/iso_efficiency_withSkimFile_v2_pbpb_${verName_a[$i]}.log
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v2.C++("pp","'${verName_a[$i]}'")' >& log/iso_efficiency_withSkimFile_v2_pp_${verName_a[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pbpb","'${verName_a[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v2_pbpb_${verName_a[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pp","'${verName_a[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v2_pp_${verName_a[$i]}.log
#    root -l -b -q 'performance/correlation_genPt_recoPt.C++("pbpb","'${verName_a[$i]}'")' >& log/correlation_pbpb_${verName_a[$i]}.log
#    root -l -b -q 'performance/correlation_genPt_recoPt.C++("pp","'${verName_a[$i]}'")' >& log/correlation_pp_${verName_a[$i]}.log
    root -l -b -q 'results/getRawDist_v5.C("'${verName_a[$i]}'",1,1)' >& log/getRawDist_v5_${verName_a[$i]}.log 
    root -l -b -q 'results/drawRaaXsec_v6.C++("'${verName_a[$i]}'",1)' >& log/drawRaaXsec_v6_${verName_a[$i]}.log
    source /data/ROOT-v5.34.21/bin/thisroot.sh
    python results/RooUnfold_photonRaa_v4.py ${verName_a[$i]} bin >& log/RooUnfold_photonRaa_v4_${verName_a[$i]}.log
    source /home/goyeonju/root/builddir/bin/thisroot.sh
    root -l -b -q 'results/drawUnfoldingFigures.C++("'${verName_a[$i]}'")' >& log/drawUnfoldingFigures_${verName_a[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v6_makeOutput.C++("'${verName_a[$i]}'",1)' >& log/drawRaaXsec_v6_makeOutput_${verName_a[$i]}.log
    
#     cp ./results/output/phoRaa_${preverName_a[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_a[$i]}_beforeUnfolding.root
#    root -l -b -q 'performance/compare_unfolding.C++("pbpb","'${verName_a[$i]}'")' >& log/compare_unfolding_pbpb_${verName_a[$i]}.log
#    root -l -b -q 'performance/compare_unfolding.C++("pp","'${verName_a[$i]}'")' >& log/compare_unfolding_pp_${verName_a[$i]}.log
done
#
verFileCopy_l=('190222_last_v27')
verName_l=('190222_last_v27_sys_unfolding_svd')
for ((i=0; i< ${#verName_l[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_l[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_l[$i]}.root
    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_l[$i]}.root
    cp ./purity/output/purity_pbpb_${verName_a[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_l[$i]}_splitPD.root
    cp ./purity/output/purity_pp_${verName_a[$i]}_splitPD.root ./purity/output/purity_pp_${verName_l[$i]}_splitPD.root
    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_l[$i]}_splitPD.root
    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_l[$i]}_pbpb.root 
    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_l[$i]}_pp.root 
    cp ./results/output/phoRaa_${preverName_a[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_l[$i]}_beforeUnfolding.root
    source /data/ROOT-v5.34.21/bin/thisroot.sh
    python results/RooUnfold_photonRaa_v4.py ${verName_l[$i]} svd >& log/RooUnfold_photonRaa_v4_${verName_l[$i]}.log
    source /home/goyeonju/root/builddir/bin/thisroot.sh
    root -l -b -q 'results/drawUnfoldingFigures.C++("'${verName_l[$i]}'")' >& log/drawUnfoldingFigures_${verName_l[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v6_makeOutput.C++("'${verName_l[$i]}'",1)' >& log/drawRaaXsec_v6_makeOutput_${verName_l[$i]}.log
done

for j in 1 2
do
    verFileCopy_m=('190222_last_v27')
    verName_m=('190222_last_v27_sys_unfolding_iterative'$j)
    for ((i=0; i< ${#verName_m[@]};i++))
    do
        cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_m[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
        cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_m[$i]}.root
        cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_m[$i]}.root
        cp ./purity/output/purity_pbpb_${verName_a[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_m[$i]}_splitPD.root
        cp ./purity/output/purity_pp_${verName_a[$i]}_splitPD.root ./purity/output/purity_pp_${verName_m[$i]}_splitPD.root
        cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_m[$i]}_splitPD.root
        cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_m[$i]}_pbpb.root 
        cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_m[$i]}_pp.root 
        cp ./results/output/phoRaa_${preverName_a[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_m[$i]}_beforeUnfolding.root
        source /data/ROOT-v5.34.21/bin/thisroot.sh
        python results/RooUnfold_photonRaa_v4.py ${verName_m[$i]} $j >& log/RooUnfold_photonRaa_v4_${verName_m[$i]}.log
        source /home/goyeonju/root/builddir/bin/thisroot.sh
        root -l -b -q 'results/drawUnfoldingFigures.C++("'${verName_m[$i]}'")' >& log/drawUnfoldingFigures_${verName_m[$i]}.log
        #root -l -b -q 'results/drawRaaXsec_v6_makeOutput.C++("'${verName_m[$i]}'",1)' >& log/drawRaaXsec_v6_makeOutput_${verName_m[$i]}.log
    done
done

#verFileCopy_p=('190222_last_v27')
#verName_p=('190222_last_v27_sys_unfolding_iterative4')
#for ((i=0; i< ${#verName_p[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_p[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_p[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_p[$i]}.root
#    cp ./purity/output/purity_pbpb_${verName_a[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_p[$i]}_splitPD.root
#    cp ./purity/output/purity_pp_${verName_a[$i]}_splitPD.root ./purity/output/purity_pp_${verName_p[$i]}_splitPD.root
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_p[$i]}_splitPD.root
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_p[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_p[$i]}_pp.root 
#    cp ./results/output/phoRaa_${preverName_a[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_p[$i]}_beforeUnfolding.root
#    source /data/ROOT-v5.34.21/bin/thisroot.sh
#    python results/RooUnfold_photonRaa_v4.py ${verName_p[$i]} 4 >& log/RooUnfold_photonRaa_v4_${verName_p[$i]}.log
#    source /home/goyeonju/root/builddir/bin/thisroot.sh
#    root -l -b -q 'results/drawUnfoldingFigures.C++("'${verName_p[$i]}'")' >& log/drawUnfoldingFigures_${verName_p[$i]}.log
#    #root -l -b -q 'results/drawRaaXsec_v6_makeOutput.C++("'${verName_p[$i]}'",1)' >& log/drawRaaXsec_v6_makeOutput_${verName_p[$i]}.log
#done
#
#verFileCopy_n=('190222_last_v27')
#verName_n=('190222_last_v27_sys_unfolding_iterative3')
#for ((i=0; i< ${#verName_n[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_n[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_n[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_n[$i]}.root
#    cp ./purity/output/purity_pbpb_${verName_a[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_n[$i]}_splitPD.root
#    cp ./purity/output/purity_pp_${verName_a[$i]}_splitPD.root ./purity/output/purity_pp_${verName_n[$i]}_splitPD.root
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_n[$i]}_splitPD.root
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_n[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_n[$i]}_pp.root 
#    cp ./results/output/phoRaa_${preverName_a[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_n[$i]}_beforeUnfolding.root
#    python results/RooUnfold_photonRaa_v4.py ${verName_n[$i]} 3 >& log/RooUnfold_photonRaa_v4_${verName_n[$i]}.log
#    root -l -b -q 'results/drawUnfoldingFigures.C++("'${verName_n[$i]}'")' >& log/drawUnfoldingFigures_${verName_n[$i]}.log
#    #root -l -b -q 'results/drawRaaXsec_v6_makeOutput.C++("'${verName_n[$i]}'",1)' >& log/drawRaaXsec_v6_makeOutput_${verName_n[$i]}.log
#done
#
#verFileCopy_o=('190222_last_v27')
#verName_o=('190222_last_v27_sys_unfolding_iterative2')
#for ((i=0; i< ${#verName_o[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_o[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_o[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_o[$i]}.root
#    cp ./purity/output/purity_pbpb_${verName_a[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_o[$i]}_splitPD.root
#    cp ./purity/output/purity_pp_${verName_a[$i]}_splitPD.root ./purity/output/purity_pp_${verName_o[$i]}_splitPD.root
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_o[$i]}_splitPD.root
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_o[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_o[$i]}_pp.root 
#    cp ./results/output/phoRaa_${preverName_a[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_o[$i]}_beforeUnfolding.root
#    python results/RooUnfold_photonRaa_v4.py ${verName_o[$i]} 2 >& log/RooUnfold_photonRaa_v4_${verName_o[$i]}.log
#    root -l -b -q 'results/drawUnfoldingFigures.C++("'${verName_o[$i]}'")' >& log/drawUnfoldingFigures_${verName_o[$i]}.log
#    #root -l -b -q 'results/drawRaaXsec_v6_makeOutput.C++("'${verName_o[$i]}'",1)' >& log/drawRaaXsec_v6_makeOutput_${verName_o[$i]}.log
#done
#
#verFileCopy_q=('190222_last_v27')
#verName_q=('190222_last_v27_sys_unfolding_iterative1')
#for ((i=0; i< ${#verName_q[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_o[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_q[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_q[$i]}.root
#    cp ./purity/output/purity_pbpb_${verName_a[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_q[$i]}_splitPD.root
#    cp ./purity/output/purity_pp_${verName_a[$i]}_splitPD.root ./purity/output/purity_pp_${verName_q[$i]}_splitPD.root
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_q[$i]}_splitPD.root
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_q[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_q[$i]}_pp.root 
#    cp ./results/output/phoRaa_${preverName_a[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_q[$i]}_beforeUnfolding.root
#    python results/RooUnfold_photonRaa_v4.py ${verName_q[$i]} 1 >& log/RooUnfold_photonRaa_v4_${verName_q[$i]}.log
#    root -l -b -q 'results/drawUnfoldingFigures.C++("'${verName_q[$i]}'")' >& log/drawUnfoldingFigures_${verName_q[$i]}.log
#    #root -l -b -q 'results/drawRaaXsec_v6_makeOutput.C++("'${verName_q[$i]}'",1)' >& log/drawRaaXsec_v6_makeOutput_${verName_q[$i]}.log
#done
#
#verFileCopy_r=('190222_last_v27')
#verName_r=('190222_last_v27_sys_unfolding_iterative6')
#for ((i=0; i< ${#verName_r[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_o[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_r[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_r[$i]}.root
#    cp ./purity/output/purity_pbpb_${verName_a[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_r[$i]}_splitPD.root
#    cp ./purity/output/purity_pp_${verName_a[$i]}_splitPD.root ./purity/output/purity_pp_${verName_r[$i]}_splitPD.root
#    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_r[$i]}_splitPD.root
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_r[$i]}_pbpb.root 
#    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_r[$i]}_pp.root 
#    cp ./results/output/phoRaa_${preverName_a[$i]}_beforeUnfolding.root ./results/output/phoRaa_${verName_r[$i]}_beforeUnfolding.root
#    python results/RooUnfold_photonRaa_v4.py ${verName_r[$i]} 6 >& log/RooUnfold_photonRaa_v4_${verName_r[$i]}.log
#    root -l -b -q 'results/drawUnfoldingFigures.C++("'${verName_r[$i]}'")' >& log/drawUnfoldingFigures_${verName_r[$i]}.log
#    #root -l -b -q 'results/drawRaaXsec_v6_makeOutput.C++("'${verName_r[$i]}'",1)' >& log/drawRaaXsec_v6_makeOutput_${verName_r[$i]}.log
#done

verFileCopy_c=('190222_last_v27_sys_purUp')
verName_c=('190222_last_v27_sys_purUp')
preverName_c=('180822_temp_v24_sys_purUp')
for ((i=0; i< ${#verName_c[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_c[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_c[$i]}.root
    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_c[$i]}.root
#    cp ./purity/output/purity_pbpb_${preverName_c[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_c[$i]}_splitPD.root
#    cp ./purity/output/purity_pp_${preverName_c[$i]}_splitPD.root ./purity/output/purity_pp_${verName_c[$i]}.root
    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pbpb","'${verName_c[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v2_pbpb_${verName_c[$i]}.log
    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pp","'${verName_c[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v2_pp_${verName_c[$i]}.log
    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_c[$i]}_pbpb.root 
    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_c[$i]}_pp.root 
    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_c[$i]}_splitPD.root
    root -l -b -q 'results/drawRaaXsec_v6.C++("'${verName_c[$i]}'",1)' >& log/drawRaaXsec_v6_${verName_c[$i]}.log
    python results/RooUnfold_photonRaa_v4.py ${verName_c[$i]} 6 >& log/RooUnfold_photonRaa_v4_${verName_c[$i]}.log
    root -l -b -q 'results/drawUnfoldingFigures.C++("'${verName_c[$i]}'")' >& log/drawUnfoldingFigures_${verName_c[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v6_makeOutput.C++("'${verName_c[$i]}'",1)' >& log/drawRaaXsec_v6_makeOutput_${verName_c[$i]}.log
done

verFileCopy_d=('190222_last_v27_sys_purDown')
verName_d=('190222_last_v27_sys_purDown')
preverName_d=('180822_temp_v24_sys_purDown')
for ((i=0; i< ${#verName_d[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_d[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_d[$i]}.root
    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_d[$i]}.root
#    cp ./purity/output/purity_pbpb_${preverName_d[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_d[$i]}_splitPD.root
#    cp ./purity/output/purity_pp_${preverName_d[$i]}_splitPD.root ./purity/output/purity_pp_${verName_d[$i]}.root
    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pbpb","'${verName_d[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v2_pbpb_${verName_d[$i]}.log
    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pp","'${verName_d[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v2_pp_${verName_d[$i]}.log
    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_d[$i]}_pbpb.root 
    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_d[$i]}_pp.root 
    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_d[$i]}_splitPD.root
    root -l -b -q 'results/drawRaaXsec_v6.C++("'${verName_d[$i]}'",1)' >& log/drawRaaXsec_v6_${verName_d[$i]}.log
    python results/RooUnfold_photonRaa_v4.py ${verName_d[$i]} 6 >& log/RooUnfold_photonRaa_v4_${verName_d[$i]}.log
    root -l -b -q 'results/drawUnfoldingFigures.C++("'${verName_d[$i]}'")' >& log/drawUnfoldingFigures_${verName_d[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v6_makeOutput.C++("'${verName_d[$i]}'",1)' >& log/drawRaaXsec_v6_makeOutput_${verName_d[$i]}.log
done

verFileCopy_f=('190222_last_v27_sys_IDup')
verName_f=('190222_last_v27_sys_IDup')
preverName_f=('180822_temp_v24_sys_IDup')
for ((i=0; i< ${#verName_f[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_f[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${preverName_f[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_f[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${preverName_f[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_f[$i]}.root
#    cp ./purity/output/purity_pbpb_${preverName_f[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_f[$i]}.root
#    cp ./purity/output/purity_pp_${preverName_f[$i]}_splitPD.root ./purity/output/purity_pp_${verName_f[$i]}.root
    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v2.C++("pbpb","'${verName_f[$i]}'")' >& log/efficiency_withSkimFile_v2_pbpb_${verName_f[$i]}.log
    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v2.C++("pp","'${verName_f[$i]}'")' >& log/efficiency_withSkimFile_v2_pp_${verName_f[$i]}.log
    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pbpb","'${verName_f[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pbpb_${verName_f[$i]}.log
    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pp","'${verName_f[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pp_${verName_f[$i]}.log
    root -l -b -q 'results/getRawDist_v5.C++("'${verName_f[$i]}'",1,0)' >& log/getRawDist_v5_${verName_f[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v6.C++("'${verName_f[$i]}'",0)' >& log/drawRaaXsec_v6_${verName_f[$i]}.log
    root -l -b -q 'performance/correlation_genPt_recoPt.C++("pbpb","'${verName_f[$i]}'")' >& log/correlation_pbpb_${verName_f[$i]}.log
    root -l -b -q 'performance/correlation_genPt_recoPt.C++("pp","'${verName_f[$i]}'")' >& log/correlation_pp_${verName_f[$i]}.log
    python results/RooUnfold_photonRaa_v4.py ${verName_f[$i]} 6 >& log/RooUnfold_photonRaa_v4_${verName_f[$i]}.log
    root -l -b -q 'results/drawUnfoldingFigures.C++("'${verName_f[$i]}'")' >& log/drawUnfoldingFigures_${verName_f[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v6_makeOutput.C++("'${verName_f[$i]}'",1)' >& log/drawRaaXsec_v6_makeOutput_${verName_f[$i]}.log
done

verFileCopy_fa=('190222_last_v27_sys_IDdown')
verName_fa=('190222_last_v27_sys_IDdown')
preverName_fa=('180822_temp_v24_sys_IDdown')
for ((i=0; i< ${#verName_fa[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_fa[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${preverName_fa[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_fa[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${preverName_fa[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_fa[$i]}.root
#    cp ./purity/output/purity_pbpb_${preverName_fa[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_fa[$i]}.root
#    cp ./purity/output/purity_pp_${preverName_fa[$i]}_splitPD.root ./purity/output/purity_pp_${verName_fa[$i]}.root
    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v2.C++("pbpb","'${verName_fa[$i]}'")' >& log/efficiency_withSkimFile_v2_pbpb_${verName_fa[$i]}.log
    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v2.C++("pp","'${verName_fa[$i]}'")' >& log/efficiency_withSkimFile_v2_pp_${verName_fa[$i]}.log
    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pbpb","'${verName_fa[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pbpb_${verName_fa[$i]}.log
    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pp","'${verName_fa[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pp_${verName_fa[$i]}.log
    root -l -b -q 'performance/correlation_genPt_recoPt.C++("pbpb","'${verName_fa[$i]}'")' >& log/correlation_pbpb_${verName_fa[$i]}.log
    root -l -b -q 'performance/correlation_genPt_recoPt.C++("pp","'${verName_fa[$i]}'")' >& log/correlation_pp_${verName_fa[$i]}.log
    root -l -b -q 'results/getRawDist_v5.C++("'${verName_fa[$i]}'",1,0)' >& log/getRawDist_v5_${verName_fa[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v6.C++("'${verName_fa[$i]}'",0)' >& log/drawRaaXsec_v6_${verName_fa[$i]}.log
    python results/RooUnfold_photonRaa_v4.py ${verName_fa[$i]} 6 >& log/RooUnfold_photonRaa_v4_${verName_fa[$i]}.log
    root -l -b -q 'results/drawUnfoldingFigures.C++("'${verName_fa[$i]}'")' >& log/drawUnfoldingFigures_${verName_fa[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v6_makeOutput.C++("'${verName_fa[$i]}'",1)' >& log/drawRaaXsec_v6_makeOutput_${verName_fa[$i]}.log
done

verFileCopy_b=('190222_last_v27_sys_phoEscale')
verName_b=('190222_last_v27_sys_phoEscale')
preverName_b=('180822_temp_v24_sys_phoEscale')
for ((i=0; i< ${#verName_b[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_b[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${preverName_b[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_b[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${preverName_b[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_b[$i]}.root
#    cp ./purity/output/purity_pbpb_${preverName_b[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_b[$i]}.root
#    cp ./purity/output/purity_pp_${preverName_b[$i]}_splitPD.root ./purity/output/purity_pp_${verName_b[$i]}.root
    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v2.C++("pbpb","'${verName_b[$i]}'")' >& log/efficiency_withSkimFile_v2_pbpb_${verName_b[$i]}.log
    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v2.C++("pp","'${verName_b[$i]}'")' >& log/efficiency_withSkimFile_v2_pp_${verName_b[$i]}.log
    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pbpb","'${verName_b[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v2_pbpb_${verName_b[$i]}.log
    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pp","'${verName_b[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v2_pp_${verName_b[$i]}.log
    root -l -b -q 'performance/correlation_genPt_recoPt.C++("pbpb","'${verName_b[$i]}'")' >& log/correlation_pbpb_${verName_b[$i]}.log
    root -l -b -q 'performance/correlation_genPt_recoPt.C++("pp","'${verName_b[$i]}'")' >& log/correlation_pp_${verName_b[$i]}.log
    root -l -b -q 'results/getRawDist_v5.C++("'${verName_b[$i]}'",1,1)' >& log/getRawDist_v5_${verName_b[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v6.C++("'${verName_b[$i]}'",1)' >& log/drawRaaXsec_v6_${verName_b[$i]}.log
    python results/RooUnfold_photonRaa_v4.py ${verName_b[$i]} 6 >& log/RooUnfold_photonRaa_v4_${verName_b[$i]}.log
    root -l -b -q 'results/drawUnfoldingFigures.C++("'${verName_b[$i]}'")' >& log/drawUnfoldingFigures_${verName_b[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v6_makeOutput.C++("'${verName_b[$i]}'",1)' >& log/drawRaaXsec_v6_makeOutput_${verName_b[$i]}.log
done

verFileCopy_j=('190222_last_v27_sys_phoEresol')
verName_j=('190222_last_v27_sys_phoEresol')
for ((i=0; i< ${#verName_j[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_j[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v2.C++("pbpb","'${verName_j[$i]}'")' >& log/efficiency_withSkimFile_v2_pbpb_${verName_j[$i]}.log
    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v2.C++("pp","'${verName_j[$i]}'")' >& log/efficiency_withSkimFile_v2_pp_${verName_j[$i]}.log
    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pbpb","'${verName_j[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v2_pbpb_${verName_j[$i]}.log
    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pp","'${verName_j[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v2_pp_${verName_j[$i]}.log
    root -l -b -q 'performance/correlation_genPt_recoPt.C++("pbpb","'${verName_j[$i]}'")' >& log/correlation_pbpb_${verName_j[$i]}.log
    root -l -b -q 'performance/correlation_genPt_recoPt.C++("pp","'${verName_j[$i]}'")' >& log/correlation_pp_${verName_j[$i]}.log
    root -l -b -q 'results/getRawDist_v5.C++("'${verName_j[$i]}'")' >& log/getRawDist_v5_${verName_j[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v6.C++("'${verName_j[$i]}'")' >& log/drawRaaXsec_v6_${verName_j[$i]}.log
    python results/RooUnfold_photonRaa_v4.py ${verName_j[$i]} 6 >& log/RooUnfold_photonRaa_v4_${verName_j[$i]}.log
    root -l -b -q 'results/drawUnfoldingFigures.C++("'${verName_j[$i]}'")' >& log/drawUnfoldingFigures_${verName_j[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v6_makeOutput.C++("'${verName_j[$i]}'",1)' >& log/drawRaaXsec_v6_makeOutput_${verName_j[$i]}.log
done

verFileCopy_e=('190222_last_v27_sys_eleCont')
verName_e=('190222_last_v27_sys_eleCont')
preverName_e=('180822_temp_v24_sys_eleCont')
for ((i=0; i< ${#verName_e[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_e[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${preverName_e[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_e[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${preverName_e[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_e[$i]}.root
#    cp ./purity/output/purity_pbpb_${preverName_e[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_e[$i]}.root
#    cp ./purity/output/purity_pp_${preverName_e[$i]}_splitPD.root ./purity/output/purity_pp_${verName_e[$i]}.root
    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v2.C++("pbpb","'${verName_e[$i]}'")' >& log/efficiency_withSkimFile_v2_pbpb_${verName_e[$i]}.log
    root -l -b -q 'efficiency/iso_efficiency_withSkimFile_v2.C++("pp","'${verName_e[$i]}'")' >& log/efficiency_withSkimFile_v2_pp_${verName_e[$i]}.log
    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pbpb","'${verName_e[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v2_pbpb_${verName_e[$i]}.log
    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pp","'${verName_e[$i]}'",1,1)' >& log/yj_quickPhotonPurity_v2_pp_${verName_e[$i]}.log
    root -l -b -q 'performance/correlation_genPt_recoPt.C++("pbpb","'${verName_e[$i]}'")' >& log/correlation_pbpb_${verName_e[$i]}.log
    root -l -b -q 'performance/correlation_genPt_recoPt.C++("pp","'${verName_e[$i]}'")' >& log/correlation_pp_${verName_e[$i]}.log
    root -l -b -q 'results/getRawDist_v5.C++("'${verName_e[$i]}'",1,1)' >& log/getRawDist_v5_${verName_e[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v6.C++("'${verName_e[$i]}'",1)' >& log/drawRaaXsec_v6_${verName_e[$i]}.log
    python results/RooUnfold_photonRaa_v4.py ${verName_e[$i]} 6 >& log/RooUnfold_photonRaa_v4_${verName_e[$i]}.log
    root -l -b -q 'results/drawUnfoldingFigures.C++("'${verName_e[$i]}'")' >& log/drawUnfoldingFigures_${verName_e[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v6_makeOutput.C++("'${verName_e[$i]}'",1)' >& log/drawRaaXsec_v6_makeOutput_${verName_e[$i]}.log
done

verFileCopy_h=('190222_last_v27_sys_TAAup')
verName_h=('190222_last_v27_sys_TAAup')
for ((i=0; i< ${#verName_h[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_h[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_h[$i]}.root
    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_h[$i]}.root
    cp ./purity/output/purity_pbpb_${verName_a[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_h[$i]}_splitPD.root
    cp ./purity/output/purity_pp_${verName_a[$i]}_splitPD.root ./purity/output/purity_pp_${verName_h[$i]}_splitPD.root
    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_h[$i]}_pbpb.root 
    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_h[$i]}_pp.root 
    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_h[$i]}_splitPD.root
    cp ./results/output/Unfold_${verName_a[$i]}.root ./results/output/Unfold_${verName_h[$i]}.root
    root -l -b -q 'results/drawRaaXsec_v6_makeOutput.C++("'${verName_h[$i]}'",1)' >& log/drawRaaXsec_v6_makeOutput_${verName_h[$i]}.log
done

verFileCopy_ha=('190222_last_v27_sys_TAAdown')
verName_ha=('190222_last_v27_sys_TAAdown')
for ((i=0; i< ${#verName_ha[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_ha[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_ha[$i]}.root
    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_ha[$i]}.root
    cp ./purity/output/purity_pbpb_${verName_a[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_ha[$i]}_splitPD.root
    cp ./purity/output/purity_pp_${verName_a[$i]}_splitPD.root ./purity/output/purity_pp_${verName_ha[$i]}_splitPD.root
    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pbpb.root ./performance/output/correlation_genPt_recoPt_${verName_ha[$i]}_pbpb.root 
    cp ./performance/output/correlation_genPt_recoPt_${verName_a[$i]}_pp.root ./performance/output/correlation_genPt_recoPt_${verName_ha[$i]}_pp.root 
    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_ha[$i]}_splitPD.root
    cp ./results/output/Unfold_${verName_a[$i]}.root ./results/output/Unfold_${verName_ha[$i]}.root
    root -l -b -q 'results/drawRaaXsec_v6_makeOutput.C++("'${verName_h[$i]}'",1)' >& log/drawRaaXsec_v6_makeOutput_${verName_ha[$i]}.log
done
#
#verFileCopy_t=('190222_last_v27_sys_TAA')
#verName_t=('190222_last_v27_sys_TAA')
#for ((i=0; i< ${#verName_t[@]};i++))
#do
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_h[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_t[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_h[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_t[$i]}.root
#    cp ./purity/output/purity_pbpb_${verName_h[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_t[$i]}_splitPD.root
#    cp ./purity/output/purity_pp_${verName_h[$i]}_splitPD.root ./purity/output/purity_pp_${verName_t[$i]}_splitPD.root
#    cp ./results/output/rawDist_${verName_h[$i]}_splitPD.root ./results/output/rawDist_${verName_t[$i]}_splitPD.root
#    cp ./results/output/phoRaa_${verName_h[$i]}.root ./results/output/phoRaa_${verName_t[$i]}.root
#done
##
##verFileCopy_k=('190222_last_v27_sys_phoEresol_sigDown')
##verName_k=('190222_last_v27_sys_phoEresol_sigDown')
##for ((i=0; i< ${#verName_k[@]};i++))
##do
##    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_k[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
##    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pbpb","'${verName_k[$i]}'")' >& log/efficiency_withSkimFile_pbpb_${verName_k[$i]}.log
##    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pp","'${verName_k[$i]}'")' >& log/efficiency_withSkimFile_pp_${verName_k[$i]}.log
##    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pbpb","'${verName_k[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pbpb_${verName_k[$i]}.log
##    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pp","'${verName_k[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pp_${verName_k[$i]}.log
##    root -l -b -q 'results/getRawDist_v5.C++("'${verName_k[$i]}'")' >& log/getRawDist_v5_${verName_k[$i]}.log
##    root -l -b -q 'results/drawRaaXsec_v6.C++("'${verName_k[$i]}'")' >& log/drawRaaXsec_v6_${verName_k[$i]}.log
##done
#
#cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
#root -l -b -q 'systematics/calc_systematic.C++("'${verFileCopy_a}'")' >& log/systematics_${verFileCopy_a}.log
#root -l -b -q 'systematics/calc_systematic_cent0to100.C++("'${verFileCopy_a}'")' >& log/systematics_cent0to100_${verFileCopy_a}.log
#root -l -b -q 'systematics/drawSystematicPlots.C++("'${verFileCopy_a}'")' >& log/drawSystematicsPlots_${verFileCopy_a}.log
#root -l -b -q 'plotting/photonRaaPlot_temp.C++("'${verFileCopy_a}'")' >& log/plotting_${verFileCopy_a}.log
#root -l -b -q 'plotting/photonRaaPlot_withJetphox.C++("'${verFileCopy_a}'")' >& log/plotting_${verFileCopy_a}.log
#root -l -b -q 'plotting/photonRaaPlot.C++("'${verFileCopy_a}'")' >& log/plotting_${verFileCopy_a}.log
