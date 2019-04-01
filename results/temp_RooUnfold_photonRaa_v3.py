#!/usr/bin/env python
# RooUnfold_photonRaa_v3.py ; use backFold function by Hyunyoung

import ROOT, sys, os
from copy import deepcopy
from array import array

def normHist(hist):
  intg = hist.Integral()
  hist.Scale(1.0/intg)
  for x in xrange(hist.GetNbinsX()):
    binW = hist.GetBinWidth(x+1)
    binC = hist.GetBinContent(x+1)
    binE = hist.GetBinError(x+1)
    hist.SetBinContent(x+1, binC/binW)
    hist.SetBinError(x+1, binE/binW)



def makeMat(hist):  
  tmpM = ROOT.TMatrixD(hist.GetNbinsX(),1)
  a = array('d', [hist.GetBinContent(x+1) for x in xrange(hist.GetNbinsX())])
  tmpM.SetMatrixArray(a)
  return tmpM

#response matrix to projection->gen and reco matched percent?
def RM2P(hist):
  nm = hist.GetNbinsX()
  nt = hist.GetNbinsY()
  tmpH = hist.Clone(hist.GetName()+"_Pij")
  tmpH.Reset()
  genHist = hist.ProjectionY()
  for y in xrange(nt):
    for x in xrange(nm):
      tmpH.SetBinContent(x+1,y+1, hist.GetBinContent(x+1,y+1)/genHist.GetBinContent(y+1))

  return tmpH

def backFold(uHist, Pij, miss, fake):
  #tmpH = uHist.Clone(miss.GetName()+"backFold")
  tmpH = uHist.Clone(miss.GetName().replace("miss", "backFold"))
  tmpH.Reset()
  nm = Pij.GetNbinsX()
  nt = Pij.GetNbinsY()
  for x in xrange(nm):
    tmpV = 0.0
    tmpE = 0.0
    for y in xrange(nt):
      Nm = uHist.GetBinContent(y+1)
      Em = uHist.GetBinError(y+1)
      P = Pij.GetBinContent(x+1,y+1)
      c = (miss.GetBinContent(y+1))/(fake.GetBinContent(x+1))
      tmpV += P*Nm*c
      tmpE += P*Em*c
      #tmpV += P*Nm
    tmpH.SetBinContent(x+1, tmpV)
    tmpH.SetBinError(x+1, tmpE)
  return tmpH



ROOT.gROOT.SetBatch()
#ROOT.gSystem.Load("/home/goyeonju/unfolding/fromSVN/RooUnfold/libRooUnfold")
ROOT.gSystem.Load("/home/goyeonju/unfolding/RooUnfold/libRooUnfold")
#ROOT.gSystem.Load("/cms/scratch/hyunyong/RooUnfold/libRooUnfold")

type_ = sys.argv[2]
print type_
u_binbybin = False
if type_ == "bin":
  u_binbybin = True
  u_svd = False
  print "binBybin method"
elif type_ == "svd":
  u_binbybin = False
  u_svd = True
  print "SVD method"
else:
  u_binbybin = False
  u_svd = False
  iter_ = int(sys.argv[2])
  print "D'Agostini method"

#u_binbybin = True 
#u_svd = False
#iter_ = 2 
##iter_ = int(sys.argv[2])
#print "Bin-by-bin method"
##print "D'Agostini method"

#version = "180807_temp_v22"
version = sys.argv[1]

pytF = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/output/correlation_genPt_recoPt_"+version+"_pbpb.root"
pytF_pp = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/output/correlation_genPt_recoPt_"+version+"_pp.root"
mc = ROOT.TFile(pytF)
mc_pp = ROOT.TFile(pytF_pp)
out_name = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/Unfold_"+version+".root"
#if u_binbybin:
#  out_name = "output/Unfold_bin_"+version+".root"
#elif u_svd:
#  out_name = "output/Unfold_svd_"+version+".root"
#else:
#  out_name = "output/Unfold_iter%d"%iter_+version+".root"



reco_list = []
reco_nm_list = [] #not gen-matched
rd_list = []
gen_list = []
gen_nm_list = []
h2d_list = []
RooUnfold_res = []

reco_list_pp = []
reco_nm_list_pp = []
rd_list_pp = []
gen_list_pp = []
gen_nm_list_pp = []
h2d_list_pp = []
RooUnfold_res_pp = []

#fake_list = []
#miss_list = []

bin_list = ["cent0to100","cent0to10","cent10to30","cent30to50","cent50to100"]
#KEY: TH1D  h1D_pt_0_cent50to100;1
#KEY: TH1D  h1D_pt_1_cent50to100;1
#KEY: TH1D  h1D_pt_ratio_cent50to100;1
#KEY: TH1D  h1D_pt_1_cent50to100_error;1
#KEY: TH2D  h2D_corr_gen_reco_cent50to100;1
#KEY: TH2D  h2D_corr_gen_reco_percent_cent50to100;1
# TFile*     correlation_genPt_recoPt_180807_temp_v22_pp.root
#  KEY: TCanvas  c1;1
#  KEY: TH1D h1D_pt_0_cent0to100;1 //gen
#  KEY: TH1D h1D_pt_1_cent0to100;1 //reco
#  KEY: TH1D h1D_pt_ratio_cent0to100;1
#  KEY: TH1D h1D_pt_1_cent0to100_error;1
#  KEY: TH2D h2D_corr_gen_reco_cent0to100;1
#  KEY: TH2D h2D_corr_gen_reco_percent_cent0to100;1

for i,b in enumerate(bin_list):
    tmp_2d = mc.Get("h2D_corr_gen_reco_"+b).Clone("h2D_corr_gen_reco_"+str(i)) # 2d correlation matrix
    h2d_list.append(deepcopy(tmp_2d))
    tmp_mc_nm = mc.Get("h1D_pt_2_"+b).Clone("h1D_pt_reco_nm_"+str(i)) # mc reco distribution (not gen matched)
    reco_nm_list.append(deepcopy(tmp_mc_nm))
    tmp_mc = mc.Get("h1D_pt_1_"+b).Clone("h1D_pt_reco_"+str(i)) # mc reco distribution (gen matched)
    reco_list.append(deepcopy(tmp_mc))
    tmp_gen = mc.Get("h1D_pt_0_"+b).Clone("h1D_pt_gen_"+str(i)) # mc gen distribution
    gen_list.append(deepcopy(tmp_gen))
    tmp_gen_nm = mc.Get("h1D_pt_3_"+b).Clone("h1D_pt_gen_nm_"+str(i)) # mc gen distribution (total, not matched)
    gen_nm_list.append(deepcopy(tmp_gen_nm))
    tmp_rd = mc.Get("h1D_pt_1_"+b).Clone("h1D_dNdpt_corr2_cent"+str(i)) # data distribution after efficiency & purity correction
    #tmp_rd = rd.Get("h1D_raw_cent"+str(i)).Clone("h1D_raw_cent"+str(i))
    rd_list.append(deepcopy(tmp_rd))
    #RooUnfold_res.append(ROOT.RooUnfoldResponse(reco_nm_list[i], gen_nm_list[i], h2d_list[i], "roounfold_res_"+str(i), "roounfold_res_"+str(i))) # create response matrix (mc reco, mc gen, mc correlation 2D, name, title)
    RooUnfold_res.append(ROOT.RooUnfoldResponse(reco_list[-1], gen_list[-1], h2d_list[-1], "roounfold_res_"+str(i), "roounfold_res_"+str(i))) # create response matrix (mc reco, mc gen, mc correlation 2D, name, title)
    
#pp
tmp_2d_pp = mc_pp.Get("h2D_corr_gen_reco_cent0to100").Clone("h2D_corr_gen_reco_pp")
h2d_list_pp.append(deepcopy(tmp_2d_pp))
tmp_mc_nm_pp = mc_pp.Get("h1D_pt_2_cent0to100").Clone("h1D_pt_reco_nm_pp")
reco_nm_list_pp.append(deepcopy(tmp_mc_nm_pp))
tmp_mc_pp = mc_pp.Get("h1D_pt_1_cent0to100").Clone("h1D_pt_reco_pp")
reco_list_pp.append(deepcopy(tmp_mc_pp))
tmp_gen_pp = mc_pp.Get("h1D_pt_0_cent0to100").Clone("h1D_pt_gen_pp")
gen_list_pp.append(deepcopy(tmp_gen_pp))
tmp_gen_nm_pp = mc_pp.Get("h1D_pt_3_cent0to100").Clone("h1D_pt_gen_nm_pp")
gen_nm_list_pp.append(deepcopy(tmp_gen_nm_pp))
tmp_rd_pp = mc_pp.Get("h1D_pt_1_cent0to100").Clone("h1D_dNdpt_corr2_pp")
#tmp_rd_pp = rd.Get("h1D_raw_pp").Clone("h1D_raw_pp")
rd_list_pp.append(deepcopy(tmp_rd_pp))
#RooUnfold_res_pp.append(ROOT.RooUnfoldResponse(reco_nm_list_pp[i], gen_nm_list_pp[i], h2d_list_pp[i], "roounfold_res_pp", "roounfold_res_pp"))
RooUnfold_res_pp.append(ROOT.RooUnfoldResponse(reco_list_pp[-1], gen_list_pp[-1], h2d_list_pp[-1], "roounfold_res_pp", "roounfold_res_pp"))

# array covers centrality dependent unfolding 
RooUnfold_mc = [] # mc  
RooUnfold_mc_nm = []
RooUnfold_rd = []
RooUnfold_mc_pp = []
RooUnfold_mc_nm_pp = []
RooUnfold_rd_pp = []
#rRooUnfold_mc = []

# starting from here, unfolding! just use 'RooUnfold~' function.
svdK = 5
for i,res in enumerate(RooUnfold_res):
  if u_binbybin:
    RooUnfold_mc.append(ROOT.RooUnfoldBinByBin(res, reco_list[i]))
    RooUnfold_mc_nm.append(ROOT.RooUnfoldBinByBin(res, reco_nm_list[i]))
    RooUnfold_rd.append(ROOT.RooUnfoldBinByBin(res, rd_list[i]))
    #rRooUnfold_mc.append(ROOT.RooUnfoldBinByBin(res, rreco_list[i]))

  elif u_svd:
    RooUnfold_mc.append(ROOT.RooUnfoldSvd(res, reco_list[i], svdK))
    RooUnfold_mc_nm.append(ROOT.RooUnfoldSvd(res, reco_nm_list[i], svdK))
    RooUnfold_rd.append(ROOT.RooUnfoldSvd(res, rd_list[i], svdK))
    #rRooUnfold_mc.append(ROOT.RooUnfoldSvd(res, rreco_list[i], svdK))

  else:
    RooUnfold_mc.append(ROOT.RooUnfoldBayes(res, reco_list[i], iter_))
    RooUnfold_mc_nm.append(ROOT.RooUnfoldBayes(res, reco_nm_list[i], iter_))
    RooUnfold_rd.append(ROOT.RooUnfoldBayes(res, rd_list[i], iter_))
    #rRooUnfold_mc.append(ROOT.RooUnfoldBayes(res, rreco_list[i], iter_))

for i,respp in enumerate(RooUnfold_res_pp):
  if u_binbybin:
    RooUnfold_mc_pp.append(ROOT.RooUnfoldBinByBin(respp, reco_list_pp[i]))
    RooUnfold_mc_nm_pp.append(ROOT.RooUnfoldBinByBin(respp, reco_nm_list_pp[i]))
    RooUnfold_rd_pp.append(ROOT.RooUnfoldBinByBin(respp, rd_list_pp[i]))

  elif u_svd:
    RooUnfold_mc_pp.append(ROOT.RooUnfoldSvd(respp, reco_list_pp[i], svdK))
    RooUnfold_mc_nm_pp.append(ROOT.RooUnfoldSvd(respp, reco_nm_list_pp[i], svdK))
    RooUnfold_rd_pp.append(ROOT.RooUnfoldSvd(respp, rd_list_pp[i], svdK))

  else:
    RooUnfold_mc_pp.append(ROOT.RooUnfoldBayes(respp, reco_list_pp[i], iter_))
    RooUnfold_mc_nm_pp.append(ROOT.RooUnfoldBayes(respp, reco_nm_list_pp[i], iter_))
    RooUnfold_rd_pp.append(ROOT.RooUnfoldBayes(respp, rd_list_pp[i], iter_))

#RooUnfold_ct = []
#for i,res in enumerate(ct_RooUnfold_res):
#  if u_binbybin:
#    RooUnfold_ct.append(ROOT.RooUnfoldBinByBin(res, ct_treco_list[i]))
#  else:
#    RooUnfold_ct.append(ROOT.RooUnfoldBayes(res, ct_treco_list[i], 7))
#

#RooUnfold_res is type of RooUnfoldResponse. Hreco function gets TH1D hist from the RooUnfold_res
e_opt = 2 # yj; Error option
print "Set Unfold"
Unfold_mc = []
for res in RooUnfold_mc:
  tmph = res.Hreco(e_opt)
  print "mc"
  Unfold_mc.append(tmph.Clone(tmph.GetName()+"_mc"))

Unfold_mc_nm = []
for res in RooUnfold_mc_nm:
  tmph = res.Hreco(e_opt)
  print "mc_nm"
  Unfold_mc_nm.append(tmph.Clone(tmph.GetName()+"_mc_nm"))

Unfold_rd = []
for res in RooUnfold_rd:
  tmph = res.Hreco(e_opt)
  print "rd"
  Unfold_rd.append(tmph.Clone(tmph.GetName()+"_rd"))

Unfold_mc_pp = []
for res in RooUnfold_mc_pp:
  tmph = res.Hreco(e_opt)
  print "mc_pp"
  Unfold_mc_pp.append(tmph.Clone(tmph.GetName()+"_mc_pp"))

Unfold_mc_nm_pp = []
for res in RooUnfold_mc_nm_pp:
  tmph = res.Hreco(e_opt)
  print "mc_nm_pp"
  Unfold_mc_nm_pp.append(tmph.Clone(tmph.GetName()+"_mc_nm_pp"))

Unfold_rd_pp = []
for res in RooUnfold_rd_pp:
  tmph = res.Hreco(e_opt)
  print "rd_pp"
  Unfold_rd_pp.append(tmph.Clone(tmph.GetName()+"_rd_pp"))

#Unfold_ct = []
#for res in RooUnfold_ct:
#  tmph = res.Hreco(e_opt)
#  print "ct"
#  Unfold_ct.append(tmph.Clone(tmph.GetName()+"_ct"))
#
#rUnfold_mc = []
#for res in rRooUnfold_mc:
#  tmph = res.Hreco(e_opt)
#  print "rmc"
#  rUnfold_mc.append(tmph.Clone(tmph.GetName()+"_rmc"))
#
backfold_mc = []
backfold_mc_nm = []
fold_gen = []
fold_gen_nm = []
backfold_rd = []

backfold_mc_pp = []
backfold_mc_nm_pp = []
fold_gen_pp = []
fold_gen_nm_pp = []
backfold_rd_pp = []

print "backFold for PbPb"
for i, res in enumerate(RooUnfold_mc):
  RM = h2d_list[i] #response matrix
  Pij = RM2P(RM)
 
  bdet = RM.ProjectionX()
  bgen = RM.ProjectionY()
  #fake = bdet.Clone(RM.GetName()+"fake")
  fake = bdet.Clone(RM.GetName().replace("h2D_corr_gen_reco", "fake"))
  fake.Divide(reco_list[i])

  #miss = bgen.Clone(RM.GetName()+"miss")
  miss = bgen.Clone(RM.GetName().replace("h2D_corr_gen_reco", "miss"))
  miss.Divide(gen_list[i])

  mcbHist = backFold(Unfold_mc[i], Pij, miss, fake)
  #backfold_mc.append(mcbHist.Clone(mcbHist.GetName()+"_backFold_mc_"+str(i)))
  backfold_mc.append(deepcopy(mcbHist.Clone(mcbHist.GetName().replace("backFold","h1D_backFold_mc")))) 
  #backfold_mc.append(deepcopy(mcbHist.Clone(mcbHist.GetName().replace("backFold","h1D_backFold_mc_"+str(i))))) 
  print ("centrality bin =",i) 
  print reco_list[i].GetBinContent(2)
  print Unfold_mc[i].GetBinContent(2)
  print mcbHist.GetBinContent(2)
  #backfold_mc.append(tmph.Clone(tmph.GetName()+"_mc"))
  #unfold_sys.append(deepcopy(mcbHist.Clone(mcbHist.GetName().replace("backFold", "backFold_mc")))) 
    #backFold : reco mc -> (unfolding) -> gen-like mc -> (backfolding) -> reco-like mc
  mcbHist_nm = backFold(Unfold_mc_nm[i], Pij, miss, fake)
  backfold_mc_nm.append(deepcopy(mcbHist_nm.Clone(mcbHist_nm.GetName().replace("backFold","h1D_backFold_mc_nm")))) 
  #backfold_mc_nm.append(deepcopy(mcbHist_nm.Clone(mcbHist_nm.GetName().replace("backFold","h1D_backFold_mc_nm_"+str(i))))) 

  genbHist = backFold(gen_list[i], Pij, miss, fake)
  fold_gen.append(deepcopy(genbHist.Clone(genbHist.GetName().replace("backFold", "h1D_Fold_gen")))) 
  
  genbHist_nm = backFold(gen_nm_list[i], Pij, miss, fake)
  fold_gen_nm.append(deepcopy(genbHist_nm.Clone(genbHist_nm.GetName().replace("backFold", "h1D_Fold_gen_nm")))) 
  #fold_gen.append(deepcopy(genbHist.Clone(genbHist.GetName().replace("backFold", "h1D_Fold_gen_"+str(i))))) 
  #unfold_sys.append(deepcopy(genbHist.Clone(genbHist.GetName().replace("backFold", "Fold_gen")))) 
    #fold_gen : gen mc -> (backfolding) -> reco-like mc

  rdbHist = backFold(Unfold_rd[i], Pij, miss, fake)
  backfold_rd.append(deepcopy(rdbHist.Clone(rdbHist.GetName().replace("backFold", "h1D_backFold_rd")))) 
  #backfold_rd.append(deepcopy(rdbHist.Clone(rdbHist.GetName().replace("backFold", "h1D_backFold_rd_"+str(i))))) 
  #unfold_sys.append(deepcopy(rdbHist.Clone(rdbHist.GetName().replace("backFold", "backFold_rd")))) 
    #backFold : real reco data -> (unfolding) -> gen-like data -> (backfolding) -> reco-like data

print "<< test backfolding >>"
for i, res in enumerate(backfold_mc):
    print backfold_mc[i].GetBinContent(2)
  
print "backFold for pp"
for i,respp in enumerate(RooUnfold_res_pp):
    RM_pp = h2d_list_pp[i] #response matrix
    Pij_pp = RM2P(RM_pp)
    
    bdet_pp = RM_pp.ProjectionX()
    bgen_pp = RM_pp.ProjectionY()
    fake_pp = bdet.Clone(RM_pp.GetName().replace("h2D_corr_gen_reco", "fake"))
    fake_pp.Divide(reco_list_pp[i])
    
    miss_pp = bgen.Clone(RM_pp.GetName().replace("h2D_corr_gen_reco", "miss"))
    miss_pp.Divide(gen_list_pp[i])
    
    mcbHist_pp = backFold(Unfold_mc_pp[i], Pij_pp, miss_pp, fake_pp)
    backfold_mc_pp.append(deepcopy(mcbHist_pp.Clone(mcbHist_pp.GetName().replace("backFold","h1D_backFold_mc")))) 
    #backFold : reco mc -> (unfolding) -> gen-like mc -> (backfolding) -> reco-like mc
    
    mcbHist_nm_pp = backFold(Unfold_mc_nm_pp[i], Pij_pp, miss_pp, fake_pp)
    backfold_mc_nm_pp.append(deepcopy(mcbHist_nm_pp.Clone(mcbHist_nm_pp.GetName().replace("backFold","h1D_backFold_mc_nm")))) 
    
    genbHist_pp = backFold(gen_list_pp[i], Pij_pp, miss_pp, fake_pp)
    fold_gen_pp.append(deepcopy(genbHist_pp.Clone(genbHist_pp.GetName().replace("backFold", "h1D_Fold_gen")))) 
    #fold_gen : gen mc -> (backfolding) -> reco-like mc
    genbHist_nm_pp = backFold(gen_nm_list_pp[i], Pij_pp, miss_pp, fake_pp)
    fold_gen_nm_pp.append(deepcopy(genbHist_nm_pp.Clone(genbHist_nm_pp.GetName().replace("backFold", "h1D_Fold_gen_nm")))) 
    
    rdbHist_pp = backFold(Unfold_rd_pp[i], Pij_pp, miss_pp, fake_pp)
    backfold_rd_pp.append(deepcopy(rdbHist_pp.Clone(rdbHist_pp.GetName().replace("backFold", "h1D_backFold_rd")))) 
    #backFold : real reco data -> (unfolding) -> gen-like data -> (backfolding) -> reco-like data
#
#
#  CTRM = ct_h2d_list[i]
#  CTPij = RM2P(CTRM)
#  ctdet = CTRM.ProjectionX()
#  ctgen = CTRM.ProjectionY()
#  ctfake = ctdet.Clone(CTRM.GetName().replace("ct_resM", "fake"))
#  ctfake.Divide(ct_reco_list[i])
#  ctmiss = ctgen.Clone(CTRM.GetName().replace("ct_resM", "miss"))
#  ctmiss.Divide(ct_gen_list[i])
#  ctbHist = backFold(Unfold_ct[i], CTPij, ctmiss, ctfake)
#  unfold_sys.append(deepcopy(ctbHist.Clone(ctbHist.GetName().replace("backFold", "backFold_ct"))))
#

out_f = ROOT.TFile(out_name,"RECREATE")
out_f.cd()
for x in xrange(len(RooUnfold_res)):
  gen_list[x].Write()
  gen_nm_list[x].Write()
  reco_list[x].Write()
  reco_nm_list[x].Write()
  rd_list[x].Write()
  h2d_list[x].Write()
  RooUnfold_rd[x].Write()
  RooUnfold_res[x].Write()
  Unfold_mc[x].Write()
  Unfold_mc_nm[x].Write()
  Unfold_rd[x].Write()
  backfold_mc[x].Write()
  backfold_mc_nm[x].Write()
  fold_gen[x].Write()
  fold_gen_nm[x].Write()
  backfold_rd[x].Write()
 # Unfold_ct[x].Write()
 # rUnfold_mc[x].Write()
 # ct_treco_list[x].Write()
#for x in unfold_sys:
#    x.Write()
for x in xrange(len(RooUnfold_res_pp)):
    gen_list_pp[x].Write()
    gen_nm_list_pp[x].Write()
    reco_list_pp[x].Write()
    reco_nm_list_pp[x].Write()
    rd_list_pp[x].Write()
    h2d_list_pp[x].Write()
    RooUnfold_rd_pp[x].Write()
    RooUnfold_res_pp[x].Write()
    Unfold_mc_pp[x].Write()
    Unfold_mc_nm_pp[x].Write()
    Unfold_rd_pp[x].Write()
    backfold_mc_pp[x].Write()
    backfold_mc_nm_pp[x].Write()
    fold_gen_pp[x].Write()
    fold_gen_nm_pp[x].Write()
    backfold_rd_pp[x].Write()

out_f.Write()
out_f.Close()
