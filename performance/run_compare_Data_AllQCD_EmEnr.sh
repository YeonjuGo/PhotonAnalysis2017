###compare_Data_AllQCD_EmEnr(TString coll="pbpb", TString ver="190625_temp_v25", bool doWeight=true, bool doEmEnr=true){
root -l -b -q 'compare_Data_AllQCD_EmEnr.C++("pp","190703_temp_v31",1,0)'
root -l -b -q 'compare_Data_AllQCD_EmEnr.C++("pbpb","190703_temp_v31",1,0)'
#root -l -b -q 'compare_Data_AllQCD_EmEnr.C++("pp","190625_temp_v25",1,1)'
#root -l -b -q 'compare_Data_AllQCD_EmEnr.C++("pp","190625_temp_v25",1,0)'
#root -l -b -q 'compare_Data_AllQCD_EmEnr.C++("pbpb","190625_temp_v25",1,1)'
#root -l -b -q 'compare_Data_AllQCD_EmEnr.C++("pbpb","190625_temp_v25",1,0)'
