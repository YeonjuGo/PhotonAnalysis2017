#!/bin/bash
#yj_quickPhotonPurity(const TString coll="pbpb", const TString ver="170523_temp_v1_NewPurityMethod", bool useSBcorr=1, bool noCe    ntDepCorr=1, bool useMCSB=0)
# OldPurityMethod : 0, 0, 0
# NewPurityMethod_noCentDepCorr : 1, 1, 0 
# NewPurityMethod_ptCentDepCorr : 1, 0, 0

verFileCopy_a=('171017_temp_v9')
verName_a=('171017_temp_v9_nominal')

for ((i=0; i< ${#verName_a[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    root -l -b -q 'efficiency/reco_efficiency_withForest.C++("pbpb","'${verName_a[$i]}'")' >& log/reco_efficiency_withForest_pbpb_${verName_a[$i]}.log
#    root -l -b -q 'efficiency/efficiency_withSkimFile.C++("pbpb","'${verName_a[$i]}'")' >& log/efficiency_withSkimFile_pbpb_${verName_a[$i]}.log
#    root -l -b -q 'efficiency/efficiency_withSkimFile.C++("pp","'${verName_a[$i]}'")' >& log/efficiency_withSkimFile_pp_${verName_a[$i]}.log
# root -l -b -q 'performance/compare_bkgShape_isoBkg_nonIsoBkg.C++("pbpb","'${verName_a[$i]}'")' >& log/compare_bkgShape_isoBkg_nonIsoBkg_pbpb_${verName_a[$i]}.log
# root -l -b -q 'performance/compare_bkgShape_isoBkg_nonIsoBkg.C++("pp","'${verName_a[$i]}'")' >& log/compare_bkgShape_isoBkg_nonIsoBkg_pp_${verName_a[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity_floatSig.C++("pbpb","'${verName_a[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_floatSig_pbpb_${verName_a[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity_floatSig.C++("pp","'${verName_a[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_floatSig_pp_${verName_a[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pbpb","'${verName_a[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pbpb_${verName_a[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pp","'${verName_a[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pp_${verName_a[$i]}.log
#    root -l -b -q 'results/getRawDist.C++("'${verName_a[$i]}'")' >& log/getRawDist_${verName_a[$i]}.log
#    root -l -b -q 'results/drawRaaXsec.C++("'${verName_a[$i]}'")' >& log/drawRaaXsec_${verName_a[$i]}.log
done
