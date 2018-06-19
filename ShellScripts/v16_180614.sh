#!/bin/bash
#yj_quickPhotonPurity(const TString coll="pbpb", const TString ver="170523_temp_v1_NewPurityMethod", bool useSBcorr=1, bool noCe    ntDepCorr=1, bool useMCSB=0)
# OldPurityMethod : 0, 0, 0
# NewPurityMethod_noCentDepCorr : 1, 1, 0 
# NewPurityMethod_ptCentDepCorr : 1, 0, 0

verFileCopy_a=('180614_temp_v16')
verName_a=('180614_temp_v16_nominal')
#
#for ((i=0; i< ${#verName_a[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pbpb","'${verName_a[$i]}'")' >& log/iso_efficiency_withSkimFile_pbpb_${verName_a[$i]}.log
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pp","'${verName_a[$i]}'")' >& log/iso_efficiency_withSkimFile_pp_${verName_a[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pbpb","'${verName_a[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pbpb_${verName_a[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pp","'${verName_a[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pp_${verName_a[$i]}.log
#    root -l -b -q 'results/getRawDist.C++("'${verName_a[$i]}'")' >& log/getRawDist_${verName_a[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v2.C++("'${verName_a[$i]}'")' >& log/drawRaaXsec_v2_${verName_a[$i]}.log
#done
#
#verFileCopy_f=('180614_temp_v16_sys_effUp')
#verName_f=('180614_temp_v16_sys_effUp')
#for ((i=0; i< ${#verName_f[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_f[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pbpb","'${verName_f[$i]}'")' >& log/efficiency_withSkimFile_pbpb_${verName_f[$i]}.log
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pp","'${verName_f[$i]}'")' >& log/efficiency_withSkimFile_pp_${verName_f[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pbpb","'${verName_f[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pbpb_${verName_f[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pp","'${verName_f[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pp_${verName_f[$i]}.log
#    root -l -b -q 'results/getRawDist.C++("'${verName_f[$i]}'")' >& log/getRawDist_${verName_f[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v2.C++("'${verName_f[$i]}'")' >& log/drawRaaXsec_v2_${verName_f[$i]}.log
#done
#
#verFileCopy_fa=('180614_temp_v16_sys_effDown')
#verName_fa=('180614_temp_v16_sys_effDown')
#for ((i=0; i< ${#verName_fa[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_fa[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pbpb","'${verName_fa[$i]}'")' >& log/efficiency_withSkimFile_pbpb_${verName_fa[$i]}.log
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pp","'${verName_fa[$i]}'")' >& log/efficiency_withSkimFile_pp_${verName_fa[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pbpb","'${verName_fa[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pbpb_${verName_fa[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pp","'${verName_fa[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pp_${verName_fa[$i]}.log
#    root -l -b -q 'results/getRawDist.C++("'${verName_fa[$i]}'")' >& log/getRawDist_${verName_fa[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v2.C++("'${verName_fa[$i]}'")' >& log/drawRaaXsec_v2_${verName_fa[$i]}.log
#done
#
#verFileCopy_c=('180614_temp_v16_sys_purUp')
#verName_c=('180614_temp_v16_sys_purUp')
#for ((i=0; i< ${#verName_c[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_c[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_c[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_c[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pbpb","'${verName_c[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pbpb_${verName_c[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pp","'${verName_c[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pp_${verName_c[$i]}.log
#    cp ./results/output/rawDist_${verName_a[$i]}.root ./results/output/rawDist_${verName_c[$i]}.root
#    root -l -b -q 'results/drawRaaXsec_v2.C++("'${verName_c[$i]}'")' >& log/drawRaaXsec_v2_${verName_c[$i]}.log
#done
#
#verFileCopy_d=('180614_temp_v16_sys_purDown')
#verName_d=('180614_temp_v16_sys_purDown')
#for ((i=0; i< ${#verName_d[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_d[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_d[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_d[$i]}.root
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pbpb","'${verName_d[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pbpb_${verName_d[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pp","'${verName_d[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pp_${verName_d[$i]}.log
#    cp ./results/output/rawDist_${verName_a[$i]}.root ./results/output/rawDist_${verName_d[$i]}.root
#    root -l -b -q 'results/drawRaaXsec_v2.C++("'${verName_d[$i]}'")' >& log/drawRaaXsec_v2_${verName_d[$i]}.log
#done
#
verFileCopy_b=('180614_temp_v16_sys_phoEscale')
verName_b=('180614_temp_v16_sys_phoEscale')

for ((i=0; i< ${#verName_b[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_b[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pbpb","'${verName_b[$i]}'")' >& log/efficiency_withSkimFile_pbpb_${verName_b[$i]}.log
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pp","'${verName_b[$i]}'")' >& log/efficiency_withSkimFile_pp_${verName_b[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pbpb","'${verName_b[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pbpb_${verName_b[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pp","'${verName_b[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pp_${verName_b[$i]}.log
#    root -l -b -q 'results/getRawDist.C++("'${verName_b[$i]}'")' >& log/getRawDist_${verName_b[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v2.C++("'${verName_b[$i]}'")' >& log/drawRaaXsec_v2_${verName_b[$i]}.log
done
#
verFileCopy_e=('180614_temp_v16_sys_eleCont')
verName_e=('180614_temp_v16_sys_eleCont')
for ((i=0; i< ${#verName_e[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_e[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pbpb","'${verName_e[$i]}'")' >& log/efficiency_withSkimFile_pbpb_${verName_e[$i]}.log
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pp","'${verName_e[$i]}'")' >& log/efficiency_withSkimFile_pp_${verName_e[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pbpb","'${verName_e[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pbpb_${verName_e[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pp","'${verName_e[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pp_${verName_e[$i]}.log
#    root -l -b -q 'results/getRawDist.C++("'${verName_e[$i]}'")' >& log/getRawDist_${verName_e[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v2.C++("'${verName_e[$i]}'")' >& log/drawRaaXsec_v2_${verName_e[$i]}.log
done
#
verFileCopy_h=('180614_temp_v16_sys_TAA')
verName_h=('180614_temp_v16_sys_TAA')
for ((i=0; i< ${#verName_h[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_h[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_h[$i]}.root
#    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_h[$i]}.root
#    cp ./purity/output/purity_pbpb_${verName_a[$i]}.root ./purity/output/purity_pbpb_${verName_h[$i]}.root
#    cp ./purity/output/purity_pp_${verName_a[$i]}.root ./purity/output/purity_pp_${verName_h[$i]}.root
#    cp ./results/output/rawDist_${verName_a[$i]}.root ./results/output/rawDist_${verName_h[$i]}.root
    root -l -b -q 'results/drawRaaXsec_v2.C++("'${verName_h[$i]}'")' >& log/drawRaaXsec_v2_${verName_h[$i]}.log
done
#
#verFileCopy_j=('180614_temp_v16_sys_phoEresol_sigUp')
#verName_j=('180614_temp_v16_sys_phoEresol_sigUp')
#for ((i=0; i< ${#verName_j[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_j[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pbpb","'${verName_j[$i]}'")' >& log/efficiency_withSkimFile_pbpb_${verName_j[$i]}.log
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pp","'${verName_j[$i]}'")' >& log/efficiency_withSkimFile_pp_${verName_j[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pbpb","'${verName_j[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pbpb_${verName_j[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pp","'${verName_j[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pp_${verName_j[$i]}.log
#    root -l -b -q 'results/getRawDist.C++("'${verName_j[$i]}'")' >& log/getRawDist_${verName_j[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v2.C++("'${verName_j[$i]}'")' >& log/drawRaaXsec_v2_${verName_j[$i]}.log
#done
#
#verFileCopy_k=('180614_temp_v16_sys_phoEresol_sigDown')
#verName_k=('180614_temp_v16_sys_phoEresol_sigDown')
#for ((i=0; i< ${#verName_k[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_k[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pbpb","'${verName_k[$i]}'")' >& log/efficiency_withSkimFile_pbpb_${verName_k[$i]}.log
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pp","'${verName_k[$i]}'")' >& log/efficiency_withSkimFile_pp_${verName_k[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pbpb","'${verName_k[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pbpb_${verName_k[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pp","'${verName_k[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pp_${verName_k[$i]}.log
#    root -l -b -q 'results/getRawDist.C++("'${verName_k[$i]}'")' >& log/getRawDist_${verName_k[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v2.C++("'${verName_k[$i]}'")' >& log/drawRaaXsec_v2_${verName_k[$i]}.log
#done
#
#verFileCopy_l=('180614_temp_v16_sys_phoEresol_rmsUp')
#verName_l=('180614_temp_v16_sys_phoEresol_rmsUp')
#for ((i=0; i< ${#verName_l[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_l[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pbpb","'${verName_l[$i]}'")' >& log/efficiency_withSkimFile_pbpb_${verName_l[$i]}.log
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pp","'${verName_l[$i]}'")' >& log/efficiency_withSkimFile_pp_${verName_l[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pbpb","'${verName_l[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pbpb_${verName_l[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pp","'${verName_l[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pp_${verName_l[$i]}.log
#    root -l -b -q 'results/getRawDist.C++("'${verName_l[$i]}'")' >& log/getRawDist_${verName_l[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v2.C++("'${verName_l[$i]}'")' >& log/drawRaaXsec_v2_${verName_l[$i]}.log
#done
#
#verFileCopy_m=('180614_temp_v16_sys_phoEresol_rmsDown')
#verName_m=('180614_temp_v16_sys_phoEresol_rmsDown')
#for ((i=0; i< ${#verName_m[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_m[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pbpb","'${verName_m[$i]}'")' >& log/efficiency_withSkimFile_pbpb_${verName_m[$i]}.log
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pp","'${verName_m[$i]}'")' >& log/efficiency_withSkimFile_pp_${verName_m[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pbpb","'${verName_m[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pbpb_${verName_m[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity.C++("pp","'${verName_m[$i]}'",0,0,0)' >& log/yj_quickPhotonPurity_pp_${verName_m[$i]}.log
#    root -l -b -q 'results/getRawDist.C++("'${verName_m[$i]}'")' >& log/getRawDist_${verName_m[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v2.C++("'${verName_m[$i]}'")' >& log/drawRaaXsec_v2_${verName_m[$i]}.log
#done
#
cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
root -l -b -q 'systematics/calc_systematic.C++("'${verFileCopy_a}'")' >& log/systematics_${verFileCopy_a}.log
root -l -b -q 'systematics/calc_systematic_cent0to100.C++("'${verFileCopy_a}'")' >& log/systematics_cent0to100_${verFileCopy_a}.log
root -l -b -q 'systematics/drawSystematicPlots.C++("'${verFileCopy_a}'")' >& log/drawSystematicsPlots_${verFileCopy_a}.log
root -l -b -q 'plotting/photonRaaPlot.C++("'${verFileCopy_a}'")' >& log/plotting_${verFileCopy_a}.log
