### compare_bkgShape_isoBkg_nonIsoBkg(TString coll="pp", TString ver="180817_temp_v23", bool isBkg=true){

root -l -b -q 'compare_sigmaIEtaIEta_iso_nonIso.C++("pp","190625_temp_v29",1)'
root -l -b -q 'compare_sigmaIEtaIEta_iso_nonIso.C++("pp","190625_temp_v29",0)'
root -l -b -q 'compare_sigmaIEtaIEta_iso_nonIso.C++("pbpb","190625_temp_v29",1)'
root -l -b -q 'compare_sigmaIEtaIEta_iso_nonIso.C++("pbpb","190625_temp_v29",0)'
