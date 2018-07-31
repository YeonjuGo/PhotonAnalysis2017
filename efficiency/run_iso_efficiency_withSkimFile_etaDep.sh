#void iso_efficiency_withSkimFile_etaDep(TString coll="pbpb", TString ver="v18", bool doWeight=true, bool doBkg=false, bool doSeparation=true){
root -l -b -q 'iso_efficiency_withSkimFile_etaDep.C++("pbpb","180718_temp_v19", 1)'
root -l -b -q 'iso_efficiency_withSkimFile_etaDep.C++("pp","180718_temp_v19", 1)'
