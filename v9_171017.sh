#!/bin/bash
#yj_quickPhotonPurity(const TString coll="pbpb", const TString ver="170523_temp_v1_NewPurityMethod", bool useSBcorr=1, bool noCe    ntDepCorr=1, bool useMCSB=0)
# OldPurityMethod : 0, 0, 0
# NewPurityMethod_noCentDepCorr : 1, 1, 0 
# NewPurityMethod_ptCentDepCorr : 1, 0, 0
verFileCopy_a=('171017_temp_v9')
verName_a=('171017_temp_v9_OldPurityMethod')

for ((i=0; i< ${#verName_a[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
# root -l -b -q 'efficiency/efficiency_withSkimFile.C++("pbpb","'${verName_a[$i]}'")' >& log/efficiency_withSkimFile_pbpb_${verName_a[$i]}.log
# root -l -b -q 'efficiency/efficiency_withSkimFile.C++("pp","'${verName_a[$i]}'")' >& log/efficiency_withSkimFile_pp_${verName_a[$i]}.log
# root -l -b -q 'performance/compare_bkgShape_isoBkg_nonIsoBkg.C++("pbpb","'${verName_a[$i]}'")' >& log/compare_bkgShape_isoBkg_nonIsoBkg_pbpb_${verName_a[$i]}.log
# root -l -b -q 'performance/compare_bkgShape_isoBkg_nonIsoBkg.C++("pp","'${verName_a[$i]}'")' >& log/compare_bkgShape_isoBkg_nonIsoBkg_pp_${verName_a[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pbpb","'${verName_a[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pbpb_${verName_a[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pp","'${verName_a[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pp_${verName_a[$i]}.log
#    root -l -b -q 'results/getRawDist.C++("'${verName_a[$i]}'")' >& log/getRawDist_${verName_a[$i]}.log
    root -l -b -q 'results/drawRaaXsec.C++("'${verName_a[$i]}'")' >& log/drawRaaXsec_${verName_a[$i]}.log
done

verFileCopy_b=('171017_temp_v9')
verName_b=('171017_temp_v9_NewPurityMethod_noCentDepCorr')

for ((i=0; i< ${#verName_b[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_b[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    root -l -b -q 'efficiency/efficiency_withSkimFile.C++("pbpb","'${verName_b[$i]}'")' >& log/efficiency_withSkimFile_pbpb_${verName_b[$i]}.log
#    root -l -b -q 'efficiency/efficiency_withSkimFile.C++("pp","'${verName_b[$i]}'")' >& log/efficiency_withSkimFile_pp_${verName_b[$i]}.log
#    root -l -b -q 'performance/compare_bkgShape_isoBkg_nonIsoBkg.C++("pbpb","'${verName_b[$i]}'")' >& log/compare_bkgShape_isoBkg_nonIsoBkg_pbpb_${verName_b[$i]}.log
#    root -l -b -q 'performance/compare_bkgShape_isoBkg_nonIsoBkg.C++("pp","'${verName_b[$i]}'")' >& log/compare_bkgShape_isoBkg_nonIsoBkg_pp_${verName_b[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pbpb","'${verName_b[$i]}'",1,1,0)' >& log/yj_quickPhotonPurity_pbpb_${verName_b[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pp","'${verName_b[$i]}'",1,1,0)' >& log/yj_quickPhotonPurity_pp_${verName_b[$i]}.log
#    root -l -b -q 'results/getRawDist.C++("'${verName_b[$i]}'")' >& log/getRawDist_${verName_b[$i]}.log
    root -l -b -q 'results/drawRaaXsec.C++("'${verName_b[$i]}'")' >& log/drawRaaXsec_${verName_b[$i]}.log
done

verFileCopy_c=('171017_temp_v9')
verName_c=('171017_temp_v9_NewPurityMethod_ptCentDepCorr')

for ((i=0; i< ${#verName_c[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_c[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    root -l -b -q 'efficiency/efficiency_withSkimFile.C++("pbpb","'${verName_c[$i]}'")' >& log/efficiency_withSkimFile_pbpb_${verName_c[$i]}.log
#    root -l -b -q 'efficiency/efficiency_withSkimFile.C++("pp","'${verName_c[$i]}'")' >& log/efficiency_withSkimFile_pp_${verName_c[$i]}.log
#    root -l -b -q 'performance/compare_bkgShape_isoBkg_nonIsoBkg.C++("pbpb","'${verName_c[$i]}'")' >& log/compare_bkgShape_isoBkg_nonIsoBkg_pbpb_${verName_c[$i]}.log
#    root -l -b -q 'performance/compare_bkgShape_isoBkg_nonIsoBkg.C++("pp","'${verName_c[$i]}'")' >& log/compare_bkgShape_isoBkg_nonIsoBkg_pp_${verName_c[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pbpb","'${verName_c[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_pbpb_${verName_c[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pp","'${verName_c[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_pp_${verName_c[$i]}.log
#    root -l -b -q 'results/getRawDist.C++("'${verName_c[$i]}'")' >& log/getRawDist_${verName_c[$i]}.log
    root -l -b -q 'results/drawRaaXsec.C++("'${verName_c[$i]}'")' >& log/drawRaaXsec_${verName_c[$i]}.log
done
