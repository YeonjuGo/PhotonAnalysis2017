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
ROOT.gSystem.Load("/cms/scratch/hyunyong/RooUnfold/libRooUnfold")

type_ = sys.argv[2]
print type_
u_binbybin = True 
u_svd = False
iter_ = 2 
#iter_ = int(sys.argv[2])
print "Bin-by-bin method"
#print "D'Agostini method"

version = "180807_temp_v22"
#version = sys.argv[1]

pytF = "/cms/ldap_home/ygo/correlation_genPt_recoPt_"+version+"_pbpb.root"
dataF = "/cms/ldap_home/ygo/unfold/rawDist_180807_temp_v22_nominal_splitPD.root"
mc = ROOT.TFile(pytF)
rd = ROOT.TFile(dataF)
if u_binbybin:
  out_name = "Unfold_hist_PYTHIA8_bin.root"
elif u_svd:
  out_name = "Unfold_hist_PYTHIA8_svd.root"
else:
  out_name = "Unfold_hist_PYTHIA8_iter%d.root"%iter_


reco_list = []
rd_list = []
gen_list = []
h2d_list = []
RooUnfold_res = []

#fake_list = []
#miss_list = []
#
#jes_up_list = []
#jes_dn_list = []
#jer_list = []
#jer_up_list = []
#jer_dn_list = []
#pu_up_list = []
#pu_dn_list = []
#
#ct_reco_list = []
#ct_gen_list = []
#ct_h2d_list = []
#ct_RooUnfold_res = []
#ct_treco_list = []
#rreco_list = []

bin_list = ["cent0to10","cent10to30","cent30to50","cent50to100"]
#bin_list = [["non_eta_high_pt_sdr_pt3_", "jet3_pt_jet2_pt"], ["non_eta_high_pt_ldr_pt3_", "jet3_pt_jet2_pt"], ["non_eta_high_pt_dr_lpt3_", "del_r23"], ["non_eta_high_pt_dr_hpt3_", "del_r23"],["non_eta_high_pt_dr_mpt3_", "del_r23"]]
#KEY: TH1D  h1D_pt_0_cent50to100;1
#KEY: TH1D  h1D_pt_1_cent50to100;1
#KEY: TH1D  h1D_pt_ratio_cent50to100;1
#KEY: TH1D  h1D_pt_1_cent50to100_error;1
#KEY: TH2D  h2D_corr_gen_reco_cent50to100;1
#KEY: TH2D  h2D_corr_gen_reco_percent_cent50to100;1
    
#for i,b in bin_list:
for i,b in enumerate(bin_list):
    tmp_2d = mc.Get("h2D_corr_gen_reco_"+b).Clone("h2D_corr_gen_reco_"+b)
    h2d_list.append(deepcopy(tmp_2d))
    tmp_mc = mc.Get("h1D_pt_1_"+b).Clone("h1D_pt_1_"+b)
    reco_list.append(deepcopy(tmp_mc))
    tmp_gen = mc.Get("h1D_pt_0_"+b).Clone("h1D_pt_0_"+b)
    gen_list.append(deepcopy(tmp_gen))
    tmp_rd = rd.Get("h1D_raw_cent"+str(i)).Clone("h1D_raw_cent"+str(i))
    rd_list.append(deepcopy(tmp_rd))
    RooUnfold_res.append(ROOT.RooUnfoldResponse(reco_list[-1], gen_list[-1], h2d_list[-1], "roounfold_res_"+b, "roounfold_res_"+b))

RooUnfold_mc = []
RooUnfold_rd = []
#rRooUnfold_mc = []

#jes_up_uf = []
#jes_dn_uf = []
#jer_uf = []
#jer_up_uf = []
#jer_dn_uf = []
#pu_up_uf = []
#pu_dn_uf = []
#
svdK = 5
for i,res in enumerate(RooUnfold_res):
  if u_binbybin:
    RooUnfold_mc.append(ROOT.RooUnfoldBinByBin(res, reco_list[i]))
    RooUnfold_rd.append(ROOT.RooUnfoldBinByBin(res, rd_list[i]))
    #rRooUnfold_mc.append(ROOT.RooUnfoldBinByBin(res, rreco_list[i]))

  elif u_svd:
    RooUnfold_mc.append(ROOT.RooUnfoldSvd(res, reco_list[i], svdK))
    RooUnfold_rd.append(ROOT.RooUnfoldSvd(res, rd_list[i], svdK))
    #rRooUnfold_mc.append(ROOT.RooUnfoldSvd(res, rreco_list[i], svdK))

  else:
    RooUnfold_mc.append(ROOT.RooUnfoldBayes(res, reco_list[i], iter_))
    #RooUnfold_rd.append(ROOT.RooUnfoldBayes(res, rd_list[i], iter_))
    #rRooUnfold_mc.append(ROOT.RooUnfoldBayes(res, rreco_list[i], iter_))

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

Unfold_rd = []
for res in RooUnfold_rd:
  tmph = res.Hreco(e_opt)
  print "rd"
  Unfold_rd.append(tmph.Clone(tmph.GetName()+"_rd"))

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
  rd_list[x].Write()
  h2d_list[x].Write()
  RooUnfold_rd[x].Write()
  RooUnfold_res[x].Write()
  Unfold_mc[x].Write()
  Unfold_rd[x].Write()
 # Unfold_ct[x].Write()
 # rUnfold_mc[x].Write()
 # ct_treco_list[x].Write()
#for x in unfold_sys:
#  x.Write()

out_f.Write()
out_f.Close()
