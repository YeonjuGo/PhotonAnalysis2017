#!/usr/bin/env python

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
ROOT.gSystem.Load("/home/goyeonju/unfolding/fromSVN/RooUnfold/libRooUnfold")
#ROOT.gSystem.Load("/home/goyeonju/unfolding/RooUnfold/libRooUnfold")
#ROOT.gSystem.Load("/cms/scratch/hyunyong/RooUnfold/libRooUnfold")

#type_ = sys.argv[2]
#print type_
u_binbybin = True 
u_svd = False
iter_ = 2 
#iter_ = int(sys.argv[2])
print "Bin-by-bin method"
#print "D'Agostini method"

#version = "180807_temp_v22"
version = sys.argv[1]

pytF = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/output/correlation_genPt_recoPt_"+version+"_pbpb.root"
pytF_pp = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/performance/output/correlation_genPt_recoPt_"+version+"_pp.root"
dataF = "/home/goyeonju/CMS/2017/PhotonAnalysis2017/results/output/rawDist_"+version+"_splitPD.root"
mc = ROOT.TFile(pytF)
mc_pp = ROOT.TFile(pytF_pp)
rd = ROOT.TFile(dataF)
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
h2d_list = []
RooUnfold_res = []

reco_list_pp = []
reco_nm_list_pp = []
rd_list_pp = []
gen_list_pp = []
h2d_list_pp = []
RooUnfold_res_pp = []

#fake_list = []
#miss_list = []

bin_list = ["cent0to100","cent0to10","cent10to30","cent30to50","cent50to100"]
#bin_list = [["non_eta_high_pt_sdr_pt3_", "jet3_pt_jet2_pt"], ["non_eta_high_pt_ldr_pt3_", "jet3_pt_jet2_pt"], ["non_eta_high_pt_dr_lpt3_", "del_r23"], ["non_eta_high_pt_dr_hpt3_", "del_r23"],["non_eta_high_pt_dr_mpt3_", "del_r23"]]
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
    
#for i,b in bin_list:
#pbpb
#for i,b in enumerate(bin_list):
#    tmp_2d = mc.Get("h2D_corr_gen_reco_"+b).Clone("h2D_corr_gen_reco_"+b)
#    h2d_list.append(deepcopy(tmp_2d))
#    tmp_mc = mc.Get("h1D_pt_1_"+b).Clone("h1D_pt_reco_"+b)
#    reco_list.append(deepcopy(tmp_mc))
#    tmp_gen = mc.Get("h1D_pt_0_"+b).Clone("h1D_pt_gen_"+b)
#    gen_list.append(deepcopy(tmp_gen))
#    tmp_rd = rd.Get("h1D_raw_cent"+str(i)).Clone("h1D_raw_cent"+str(i))
#    rd_list.append(deepcopy(tmp_rd))
#    RooUnfold_res.append(ROOT.RooUnfoldResponse(reco_list[-1], gen_list[-1], h2d_list[-1], "roounfold_res_"+b, "roounfold_res_"+b))
for i,b in enumerate(bin_list):
    tmp_2d = mc.Get("h2D_corr_gen_reco_"+b).Clone("h2D_corr_gen_reco_"+str(i))
    h2d_list.append(deepcopy(tmp_2d))
    tmp_mc_nm = mc.Get("h1D_pt_2_"+b).Clone("h1D_pt_reco_nm_"+str(i))
    reco_nm_list.append(deepcopy(tmp_mc_nm))
    tmp_mc = mc.Get("h1D_pt_1_"+b).Clone("h1D_pt_reco_"+str(i))
    reco_list.append(deepcopy(tmp_mc))
    tmp_gen = mc.Get("h1D_pt_0_"+b).Clone("h1D_pt_gen_"+str(i))
    gen_list.append(deepcopy(tmp_gen))
    tmp_rd = rd.Get("h1D_raw_cent"+str(i)).Clone("h1D_raw_cent"+str(i))
    rd_list.append(deepcopy(tmp_rd))
    RooUnfold_res.append(ROOT.RooUnfoldResponse(reco_list[-1], gen_list[-1], h2d_list[-1], "roounfold_res_"+str(i), "roounfold_res_"+str(i)))
    
#pp
tmp_2d_pp = mc_pp.Get("h2D_corr_gen_reco_cent0to100").Clone("h2D_corr_gen_reco_pp")
h2d_list_pp.append(deepcopy(tmp_2d_pp))
tmp_mc_nm_pp = mc_pp.Get("h1D_pt_2_cent0to100").Clone("h1D_pt_reco_nm_pp")
reco_nm_list_pp.append(deepcopy(tmp_mc_nm_pp))
tmp_mc_pp = mc_pp.Get("h1D_pt_1_cent0to100").Clone("h1D_pt_reco_pp")
reco_list_pp.append(deepcopy(tmp_mc_pp))
tmp_gen_pp = mc_pp.Get("h1D_pt_0_cent0to100").Clone("h1D_pt_gen_pp")
gen_list_pp.append(deepcopy(tmp_gen_pp))
tmp_rd_pp = rd.Get("h1D_raw_pp").Clone("h1D_raw_pp")
rd_list_pp.append(deepcopy(tmp_rd_pp))
RooUnfold_res_pp.append(ROOT.RooUnfoldResponse(reco_list_pp[-1], gen_list_pp[-1], h2d_list_pp[-1], "roounfold_res_pp", "roounfold_res_pp"))

RooUnfold_mc = []
RooUnfold_mc_nm = []
RooUnfold_rd = []
RooUnfold_mc_pp = []
RooUnfold_mc_nm_pp = []
RooUnfold_rd_pp = []
#rRooUnfold_mc = []

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

for i,res in enumerate(RooUnfold_res_pp):
  if u_binbybin:
    RooUnfold_mc_pp.append(ROOT.RooUnfoldBinByBin(res, reco_list_pp[i]))
    RooUnfold_mc_nm_pp.append(ROOT.RooUnfoldBinByBin(res, reco_nm_list_pp[i]))
    RooUnfold_rd_pp.append(ROOT.RooUnfoldBinByBin(res, rd_list_pp[i]))

  elif u_svd:
    RooUnfold_mc_pp.append(ROOT.RooUnfoldSvd(res, reco_list_pp[i], svdK))
    RooUnfold_mc_nm_pp.append(ROOT.RooUnfoldSvd(res, reco_nm_list_pp[i], svdK))
    RooUnfold_rd_pp.append(ROOT.RooUnfoldSvd(res, rd_list_pp[i], svdK))

  else:
    RooUnfold_mc_pp.append(ROOT.RooUnfoldBayes(res, reco_list_pp[i], iter_))
    RooUnfold_mc_nm_pp.append(ROOT.RooUnfoldBayes(res, reco_nm_list_pp[i], iter_))
    RooUnfold_rd_pp.append(ROOT.RooUnfoldBayes(res, rd_list_pp[i], iter_))

#if u_binbybin:
#  RooUnfold_mc_pp.append(ROOT.RooUnfoldBinByBin(RooUnfold_res_pp, reco_list_pp[1]))
#  RooUnfold_rd_pp.append(ROOT.RooUnfoldBinByBin(RooUnfold_res_pp, rd_list_pp[1]))
#
#elif u_svd:
#  RooUnfold_mc_pp.append(ROOT.RooUnfoldSvd(RooUnfold_res_pp, reco_list_pp[1], svdK))
#  RooUnfold_rd_pp.append(ROOT.RooUnfoldSvd(RooUnfold_res_pp, rd_list_pp[1], svdK))
#
#else:
#  RooUnfold_mc_pp.append(ROOT.RooUnfoldBayes(RooUnfold_res_pp, reco_list_pp[1], iter_))
#  RooUnfold_rd_pp.append(ROOT.RooUnfoldBayes(RooUnfold_res_pp, rd_list_pp[1], iter_))
#hist_reco= (TH1D*) unfold.Hreco();
#   
#RooUnfold_ct = []
#for i,res in enumerate(ct_RooUnfold_res):
#  if u_binbybin:
#    RooUnfold_ct.append(ROOT.RooUnfoldBinByBin(res, ct_treco_list[i]))
#  else:
#    RooUnfold_ct.append(ROOT.RooUnfoldBayes(res, ct_treco_list[i], 7))
#

e_opt = 2
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
#unfold_sys = []
#for res in jes_up_uf:
#  tmph = res.Hreco(e_opt)
#  unfold_sys.append(tmph.Clone(tmph.GetName()+"_jes_u"))
#for res in jes_dn_uf:
#  tmph = res.Hreco(e_opt)
#  unfold_sys.append(tmph.Clone(tmph.GetName()+"_jes_d"))
#for res in jer_uf:
#  tmph = res.Hreco(e_opt)
#  unfold_sys.append(tmph.Clone(tmph.GetName()+"_jer"))
#for res in jer_up_uf:
#  tmph = res.Hreco(e_opt)
#  unfold_sys.append(tmph.Clone(tmph.GetName()+"_jer_u"))
#for res in jer_dn_uf:
#  tmph = res.Hreco(e_opt)
#  unfold_sys.append(tmph.Clone(tmph.GetName()+"_jer_d"))
#for res in pu_up_uf:
#  tmph = res.Hreco(e_opt)
#  unfold_sys.append(tmph.Clone(tmph.GetName()+"_pu_u"))
#for res in pu_dn_uf:
#  tmph = res.Hreco(e_opt)
#  unfold_sys.append(tmph.Clone(tmph.GetName()+"_pu_d"))
#
#print "backFold"


#for i, res in enumerate(RooUnfold_mc):
#  RM = h2d_list[i]
#  Pij = RM2P(RM)
# 
#  bdet = RM.ProjectionX()
#  bgen = RM.ProjectionY()
#  fake = bdet.Clone(RM.GetName().replace("resM2", "fake"))
#  fake.Divide(reco_list[i])
#
#  miss = bgen.Clone(RM.GetName().replace("resM2", "miss"))
#  miss.Divide(gen_list[i])
#
#  mcbHist = backFold(Unfold_mc[i], Pij, miss, fake)
#  unfold_sys.append(deepcopy(mcbHist.Clone(mcbHist.GetName().replace("backFold", "backFold_mc"))))
#
#  genbHist = backFold(gen_list[i], Pij, miss, fake)
#  unfold_sys.append(deepcopy(genbHist.Clone(genbHist.GetName().replace("backFold", "Fold_gen"))))
#
#  rdbHist = backFold(Unfold_rd[i], Pij, miss, fake)
#  unfold_sys.append(deepcopy(rdbHist.Clone(rdbHist.GetName().replace("backFold", "backFold_rd"))))
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
  reco_list[x].Write()
  reco_nm_list[x].Write()
  rd_list[x].Write()
  h2d_list[x].Write()
  RooUnfold_rd[x].Write()
  RooUnfold_res[x].Write()
  Unfold_mc[x].Write()
  Unfold_mc_nm[x].Write()
  Unfold_rd[x].Write()
 # Unfold_ct[x].Write()
 # rUnfold_mc[x].Write()
 # ct_treco_list[x].Write()
#for x in unfold_sys:
#  x.Write()
for x in xrange(len(RooUnfold_res_pp)):
    gen_list_pp[x].Write()
    reco_list_pp[x].Write()
    reco_nm_list_pp[x].Write()
    rd_list_pp[x].Write()
    h2d_list_pp[x].Write()
    RooUnfold_rd_pp[x].Write()
    RooUnfold_res_pp[x].Write()
    Unfold_mc_pp[x].Write()
    Unfold_mc_nm_pp[x].Write()
    Unfold_rd_pp[x].Write()

out_f.Write()
out_f.Close()
