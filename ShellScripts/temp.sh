#!/bin/bash
#yj_quickPhotonPurity(const TString coll="pbpb", const TString ver="170523_temp_v1_NewPurityMethod", bool useSBcorr=1, bool noCe    ntDepCorr=1, bool useMCSB=0)
# OldPurityMethod : 0, 0, 0
# NewPurityMethod_noCentDepCorr : 1, 1, 0 
# NewPurityMethod_ptCentDepCorr : 1, 0, 0

verFileCopy_a=('171017_temp_v9')
verName_a=('171017_temp_v9')
#root -l -b -q './systematics/calc_systematic.C++("'${verName_a[$i]}'")' >& log/systematics_${verName_a[$i]}.log
root -l -b -q './plotting/photonRaaPlot.C++("'${verName_a[$i]}'")' >& log/plotting_${verName_a[$i]}.log
