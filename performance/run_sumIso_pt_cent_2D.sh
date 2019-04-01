#void sumIso_pt_cent_2D(TString ver = "180817_temp_v23", TString coll="pbpb", int sample = 0)
root -l -b -q 'sumIso_pt_cent_2D.C++("180817_temp_v23","pp",1)'
root -l -b -q 'sumIso_pt_cent_2D.C++("180817_temp_v23","pp",2)'
root -l -b -q 'sumIso_pt_cent_2D.C++("180817_temp_v23","pbpb",1)'
root -l -b -q 'sumIso_pt_cent_2D.C++("180817_temp_v23","pbpb",2)'
root -l -b -q 'sumIso_pt_cent_2D.C++("180817_temp_v23","pp",0)'
root -l -b -q 'sumIso_pt_cent_2D.C++("180817_temp_v23","pbpb",0)'
