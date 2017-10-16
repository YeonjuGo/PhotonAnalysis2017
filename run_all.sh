#!/bin/bash
verFileCopy=('170601_temp_v3' '170608_temp_v4' '170608_temp_v5')
verName=('170601_temp_v3_OldPurityMethod' '170608_temp_v4_OldPurityMethod' '170608_temp_v5_OldPurityMethod')
#ver=('170523_temp_v1' '170524_temp_v2' '170601_temp_v3' '170608_temp_v4')
#ver=('170523_temp_v1_NewPurityMethod' '170524_temp_v2_NewPurityMethod')
#yj_quickPhotonPurity(const TString coll="pbpb", const TString ver="170523_temp_v1_NewPurityMethod", bool useSBcorr=1, bool noCentDepCorr=1, bool useMCSB=0) // 2017.08.24
for ((i=0; i< ${#verName[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    root -l -b -q 'efficiency/efficiency_withSkimFile.C++("pbpb","'${verName[$i]}'")' >& log/efficiency_withSkimFile_pbpb_${verName[$i]}.log
    root -l -b -q 'efficiency/efficiency_withSkimFile.C++("pp","'${verName[$i]}'")' >& log/efficiency_withSkimFile_pp_${verName[$i]}.log
    root -l -b -q 'performance/compare_bkgShape_isoBkg_nonIsoBkg.C++("pbpb","'${verName[$i]}'")' >& log/compare_bkgShape_isoBkg_nonIsoBkg_pbpb_${verName[$i]}.log
    root -l -b -q 'performance/compare_bkgShape_isoBkg_nonIsoBkg.C++("pp","'${verName[$i]}'")' >& log/compare_bkgShape_isoBkg_nonIsoBkg_pp_${verName[$i]}.log
    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pbpb","'${verName[$i]}'",1,1,0)' >& log/yj_quickPhotonPurity_pbpb_${verName[$i]}.log
    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pp","'${verName[$i]}'",1,1,0)' >& log/yj_quickPhotonPurity_pp_${verName[$i]}.log
    root -l -b -q 'results/getRawDist.C++("'${verName[$i]}'")' >& log/getRawDist_${verName[$i]}.log
    root -l -b -q 'results/drawRaaXsec.C++("'${verName[$i]}'")' >& log/drawRaaXsec_${verName[$i]}.log
done
