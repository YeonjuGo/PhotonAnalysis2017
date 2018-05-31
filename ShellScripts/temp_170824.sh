#!/bin/bash
verFileCopy=('170824_temp_v7')
verName=('170824_temp_v7_noCentDepCorr')

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
