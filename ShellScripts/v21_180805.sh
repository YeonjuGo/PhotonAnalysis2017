#!/bin/bash
#int yj_quickPhotonPurity_v2(const TString coll="pbpb", const TString ver="phoRaaCuts_purity_forPaper", bool doSplitPD=true, bool doPreScale=0, bool useSBcorr=0, bool noCentDepCorr=0, bool useMCSB=0){
#verFileCopy_a=('1800802_temp_v20')

verFileCopy_a=('180805_temp_v21')
verName_a=('180805_temp_v21_nominal')
preverName_a=('180802_temp_v20_nominal')

#for ((i=0; i< ${#verName_a[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    cp ./efficiency/output/pbpb_iso_efficiency_${preverName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root
#    cp ./purity/output/purity_pbpb_${preverName_a[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_a[$i]}_splitPD.root
##   root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pbpb","'${verName_a[$i]}'")' >& log/iso_efficiency_withSkimFile_pbpb_${verName_a[$i]}.log
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pp","'${verName_a[$i]}'")' >& log/iso_efficiency_withSkimFile_pp_${verName_a[$i]}.log
##   root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pbpb","'${verName_a[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v2_pbpb_doPreScale_${verName_a[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pp","'${verName_a[$i]}'",1,0)' >& log/yj_quickPhotonPurity_v2_pp_doPreScale_${verName_a[$i]}.log
#    root -l -b -q 'results/getRawDist_v3.C++("'${verName_a[$i]}'")' >& log/getRawDist_v3_${verName_a[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v3.C++("'${verName_a[$i]}'")' >& log/drawRaaXsec_v3_${verName_a[$i]}.log
#done

verFileCopy_f=('180805_temp_v21_sys_IDup')
verName_f=('180805_temp_v21_sys_IDup')
preverName_f=('180802_temp_v20_sys_IDup')
for ((i=0; i< ${#verName_f[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_f[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    cp ./efficiency/output/pbpb_iso_efficiency_${preverName_f[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_f[$i]}.root
    cp ./purity/output/purity_pbpb_${preverName_f[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_f[$i]}_splitPD.root
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pbpb","'${verName_f[$i]}'")' >& log/efficiency_withSkimFile_pbpb_${verName_f[$i]}.log
    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pp","'${verName_f[$i]}'")' >& log/efficiency_withSkimFile_pp_${verName_f[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pbpb","'${verName_f[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pbpb_${verName_f[$i]}.log
    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pp","'${verName_f[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pp_${verName_f[$i]}.log
    root -l -b -q 'results/getRawDist_v3.C++("'${verName_f[$i]}'")' >& log/getRawDist_v3_${verName_f[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v3.C++("'${verName_f[$i]}'")' >& log/drawRaaXsec_v3_${verName_f[$i]}.log
done
#
verFileCopy_fa=('180805_temp_v21_sys_IDdown')
verName_fa=('180805_temp_v21_sys_IDdown')
preverName_fa=('180802_temp_v20_sys_IDdown')
for ((i=0; i< ${#verName_fa[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_fa[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    cp ./efficiency/output/pbpb_iso_efficiency_${preverName_fa[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_fa[$i]}.root
    cp ./purity/output/purity_pbpb_${preverName_fa[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_fa[$i]}_splitPD.root
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pbpb","'${verName_fa[$i]}'")' >& log/efficiency_withSkimFile_pbpb_${verName_fa[$i]}.log
    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pp","'${verName_fa[$i]}'")' >& log/efficiency_withSkimFile_pp_${verName_fa[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pbpb","'${verName_fa[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pbpb_${verName_fa[$i]}.log
    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pp","'${verName_fa[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pp_${verName_fa[$i]}.log
    root -l -b -q 'results/getRawDist_v3.C++("'${verName_fa[$i]}'")' >& log/getRawDist_v3_${verName_fa[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v3.C++("'${verName_fa[$i]}'")' >& log/drawRaaXsec_v3_${verName_fa[$i]}.log
done
#
verFileCopy_c=('180805_temp_v21_sys_purUp')
verName_c=('180805_temp_v21_sys_purUp')
preverName_c=('180802_temp_v20_sys_purUp')
for ((i=0; i< ${#verName_c[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_c[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_c[$i]}.root
    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_c[$i]}.root
    cp ./purity/output/purity_pbpb_${preverName_c[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_c[$i]}_splitPD.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pbpb","'${verName_c[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pbpb_${verName_c[$i]}.log
    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pp","'${verName_c[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pp_${verName_c[$i]}.log
    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_c[$i]}_splitPD.root
    root -l -b -q 'results/drawRaaXsec_v3.C++("'${verName_c[$i]}'")' >& log/drawRaaXsec_v3_${verName_c[$i]}.log
done

verFileCopy_d=('180805_temp_v21_sys_purDown')
verName_d=('180805_temp_v21_sys_purDown')
preverName_d=('180802_temp_v20_sys_purDown')
for ((i=0; i< ${#verName_d[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_d[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_d[$i]}.root
    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_d[$i]}.root
    cp ./purity/output/purity_pbpb_${preverName_d[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_d[$i]}_splitPD.root
#    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pbpb","'${verName_d[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pbpb_${verName_d[$i]}.log
    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pp","'${verName_d[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pp_${verName_d[$i]}.log
    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_d[$i]}_splitPD.root
    root -l -b -q 'results/drawRaaXsec_v3.C++("'${verName_d[$i]}'")' >& log/drawRaaXsec_v3_${verName_d[$i]}.log
done

verFileCopy_b=('180805_temp_v21_sys_phoEscale')
verName_b=('180805_temp_v21_sys_phoEscale')
preverName_b=('180802_temp_v20_sys_phoEscale')

for ((i=0; i< ${#verName_b[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_b[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    cp ./efficiency/output/pbpb_iso_efficiency_${preverName_b[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_b[$i]}.root
    cp ./purity/output/purity_pbpb_${preverName_b[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_b[$i]}_splitPD.root
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pbpb","'${verName_b[$i]}'")' >& log/efficiency_withSkimFile_pbpb_${verName_b[$i]}.log
   root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pp","'${verName_b[$i]}'")' >& log/efficiency_withSkimFile_pp_${verName_b[$i]}.log
#   root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pbpb","'${verName_b[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pbpb_${verName_b[$i]}.log
   root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pp","'${verName_b[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pp_${verName_b[$i]}.log
   root -l -b -q 'results/getRawDist_v3.C++("'${verName_b[$i]}'")' >& log/getRawDist_v3_${verName_b[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v3.C++("'${verName_b[$i]}'")' >& log/drawRaaXsec_v3_${verName_b[$i]}.log
done
#
verFileCopy_e=('180805_temp_v21_sys_eleCont')
verName_e=('180805_temp_v21_sys_eleCont')
preverName_e=('180802_temp_v20_sys_eleCont')
for ((i=0; i< ${#verName_e[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_e[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    cp ./efficiency/output/pbpb_iso_efficiency_${preverName_e[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_e[$i]}.root
    cp ./purity/output/purity_pbpb_${preverName_e[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_e[$i]}_splitPD.root
#   root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pbpb","'${verName_e[$i]}'")' >& log/efficiency_withSkimFile_pbpb_${verName_e[$i]}.log
   root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pp","'${verName_e[$i]}'")' >& log/efficiency_withSkimFile_pp_${verName_e[$i]}.log
#   root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pbpb","'${verName_e[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pbpb_${verName_e[$i]}.log
   root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pp","'${verName_e[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pp_${verName_e[$i]}.log
   root -l -b -q 'results/getRawDist_v3.C++("'${verName_e[$i]}'")' >& log/getRawDist_v3_${verName_e[$i]}.log
    root -l -b -q 'results/drawRaaXsec_v3.C++("'${verName_e[$i]}'")' >& log/drawRaaXsec_v3_${verName_e[$i]}.log
done
#
verFileCopy_h=('180805_temp_v21_sys_TAAup')
verName_h=('180805_temp_v21_sys_TAAup')
for ((i=0; i< ${#verName_h[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_h[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_h[$i]}.root
    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_h[$i]}.root
    cp ./purity/output/purity_pbpb_${verName_a[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_h[$i]}_splitPD.root
    cp ./purity/output/purity_pp_${verName_a[$i]}_splitPD.root ./purity/output/purity_pp_${verName_h[$i]}_splitPD.root
    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_h[$i]}_splitPD.root
    root -l -b -q 'results/drawRaaXsec_v3.C++("'${verName_h[$i]}'")' >& log/drawRaaXsec_v3_${verName_h[$i]}.log
done

verFileCopy_ha=('180805_temp_v21_sys_TAAdown')
verName_ha=('180805_temp_v21_sys_TAAdown')
for ((i=0; i< ${#verName_ha[@]};i++))
do
    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_ha[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
    cp ./efficiency/output/pbpb_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_ha[$i]}.root
    cp ./efficiency/output/pp_iso_efficiency_${verName_a[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_ha[$i]}.root
    cp ./purity/output/purity_pbpb_${verName_a[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_ha[$i]}_splitPD.root
    cp ./purity/output/purity_pp_${verName_a[$i]}_splitPD.root ./purity/output/purity_pp_${verName_ha[$i]}_splitPD.root
    cp ./results/output/rawDist_${verName_a[$i]}_splitPD.root ./results/output/rawDist_${verName_ha[$i]}_splitPD.root
    root -l -b -q 'results/drawRaaXsec_v3.C++("'${verName_ha[$i]}'")' >& log/drawRaaXsec_v3_${verName_ha[$i]}.log
done

verFileCopy_t=('180805_temp_v21_sys_TAA')
verName_t=('180805_temp_v21_sys_TAA')
for ((i=0; i< ${#verName_t[@]};i++))
do
    cp ./efficiency/output/pbpb_iso_efficiency_${verName_h[$i]}.root ./efficiency/output/pbpb_iso_efficiency_${verName_t[$i]}.root
    cp ./efficiency/output/pp_iso_efficiency_${verName_h[$i]}.root ./efficiency/output/pp_iso_efficiency_${verName_t[$i]}.root
    cp ./purity/output/purity_pbpb_${verName_h[$i]}_splitPD.root ./purity/output/purity_pbpb_${verName_t[$i]}_splitPD.root
    cp ./purity/output/purity_pp_${verName_h[$i]}_splitPD.root ./purity/output/purity_pp_${verName_t[$i]}_splitPD.root
    cp ./results/output/rawDist_${verName_h[$i]}_splitPD.root ./results/output/rawDist_${verName_t[$i]}_splitPD.root
    cp ./results/output/phoRaa_${verName_h[$i]}.root ./results/output/phoRaa_${verName_t[$i]}.root
done


#verFileCopy_j=('180805_temp_v21_sys_phoEresol_sigUp')
#verName_j=('180805_temp_v21_sys_phoEresol_sigUp')
#for ((i=0; i< ${#verName_j[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_j[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pbpb","'${verName_j[$i]}'")' >& log/efficiency_withSkimFile_pbpb_${verName_j[$i]}.log
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pp","'${verName_j[$i]}'")' >& log/efficiency_withSkimFile_pp_${verName_j[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pbpb","'${verName_j[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pbpb_${verName_j[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pp","'${verName_j[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pp_${verName_j[$i]}.log
#    root -l -b -q 'results/getRawDist_v3.C++("'${verName_j[$i]}'")' >& log/getRawDist_v3_${verName_j[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v3.C++("'${verName_j[$i]}'")' >& log/drawRaaXsec_v3_${verName_j[$i]}.log
#done
#
#verFileCopy_k=('180805_temp_v21_sys_phoEresol_sigDown')
#verName_k=('180805_temp_v21_sys_phoEresol_sigDown')
#for ((i=0; i< ${#verName_k[@]};i++))
#do
#    cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_k[$i]}.h ./phoRaaCuts/phoRaaCuts_temp.h
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pbpb","'${verName_k[$i]}'")' >& log/efficiency_withSkimFile_pbpb_${verName_k[$i]}.log
#    root -l -b -q 'efficiency/iso_efficiency_withSkimFile.C++("pp","'${verName_k[$i]}'")' >& log/efficiency_withSkimFile_pp_${verName_k[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pbpb","'${verName_k[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pbpb_${verName_k[$i]}.log
#    root -l -b -q 'purity/yj_quickPhotonPurity_v2.C++("pp","'${verName_k[$i]}'",1,0,0)' >& log/yj_quickPhotonPurity_v2_pp_${verName_k[$i]}.log
#    root -l -b -q 'results/getRawDist_v3.C++("'${verName_k[$i]}'")' >& log/getRawDist_v3_${verName_k[$i]}.log
#    root -l -b -q 'results/drawRaaXsec_v3.C++("'${verName_k[$i]}'")' >& log/drawRaaXsec_v3_${verName_k[$i]}.log
#done

cp ./phoRaaCuts/phoRaaCuts_${verFileCopy_a}.h ./phoRaaCuts/phoRaaCuts_temp.h
root -l -b -q 'systematics/calc_systematic.C++("'${verFileCopy_a}'")' >& log/systematics_${verFileCopy_a}.log
root -l -b -q 'systematics/calc_systematic_cent0to100.C++("'${verFileCopy_a}'")' >& log/systematics_cent0to100_${verFileCopy_a}.log
root -l -b -q 'systematics/drawSystematicPlots.C++("'${verFileCopy_a}'")' >& log/drawSystematicsPlots_${verFileCopy_a}.log
root -l -b -q 'plotting/photonRaaPlot_withJetphox.C++("'${verFileCopy_a}'")' >& log/plotting_${verFileCopy_a}.log
#root -l -b -q 'plotting/photonRaaPlot.C++("'${verFileCopy_a}'")' >& log/plotting_${verFileCopy_a}.log
