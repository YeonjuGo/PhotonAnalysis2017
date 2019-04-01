import FWCore.ParameterSet.Config as cms

import sys
args =sys.argv[1:]
if len(args) < 3: 
   type = "PbPb"
   dataOrMC = "MC"
   #dataOrMC = "Data"
else: 
      type = args[1]
      dataOrMC = args[2]
print "Will run type ", type, " on ", dataOrMC

process = cms.Process("TagProbe")
process.load('FWCore.MessageService.MessageLogger_cfi')
process.source = cms.Source("EmptySource")
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )    
#choose your pdf here
PDFName = "BWResCBExp"

pass_str = "passID"

EFFICIENCYSET =cms.PSet(
        recoIDPho_1bin = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(pass_str,"true"),
            UnbinnedVariables = cms.vstring("diPhoMass","final_weight"),
            BinnedVariables = cms.PSet(
                probe_pt = cms.vdouble(40, 130),
                probe_abseta = cms.vdouble(0., 1.5),
            ),
         BinToPDFmap = cms.vstring(PDFName)
        ),
        recoIDPho_pt = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(pass_str,"true"),
            UnbinnedVariables = cms.vstring("diPhoMass","final_weight"),
            BinnedVariables = cms.PSet(
                probe_pt = cms.vdouble(40, 50, 130),
                probe_abseta = cms.vdouble(0.0, 1.5),
            ),
         BinToPDFmap = cms.vstring(PDFName)
        ),
        recoIDPho_abseta = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(pass_str,"true"),
            UnbinnedVariables = cms.vstring("diPhoMass","final_weight"),
            BinnedVariables = cms.PSet(
                probe_pt = cms.vdouble(40, 130),
                probe_abseta = cms.vdouble(0.0, 1.0, 1.5),
            ),
         BinToPDFmap = cms.vstring(PDFName)
        ),
        recoIDPho_cent = cms.PSet(
            EfficiencyCategoryAndState = cms.vstring(pass_str,"true"),
            UnbinnedVariables = cms.vstring("diPhoMass","final_weight"),
            BinnedVariables = cms.PSet(
                probe_pt = cms.vdouble(40, 130),
                probe_abseta = cms.vdouble(0.0, 1.5),
                centBin = cms.vdouble(0, 20, 60, 200),
            ),
         BinToPDFmap = cms.vstring(PDFName)
        )
)


process.tagProbeFitTreeAnalyzer = cms.EDAnalyzer("TagProbeFitTreeAnalyzer",
    # IO parameters:
    InputFileNames = cms.vstring("file:/afs/cern.ch/work/i/ikucher/TnP_EG/photonRaa/output_PbPb%s_allStats_v2.root" % dataOrMC),
    InputDirectoryName = cms.string("phoTree"),
    InputTreeName = cms.string("fitter_tree"),
    OutputFileName = cms.string("tnp_Ana_%s_%s_%s_recoIDPho_test.root" % ( dataOrMC, type, PDFName )),
    #numbrer of CPUs to use for fitting
    NumCPU = cms.uint32(4),
    # specifies whether to save the RooWorkspace containing the data for each bin and
    # the pdf object with the initial and final state snapshots
    binnedFit = cms.bool(False),
    #binsForFit = cms.uint32(30),
    binsForMassPlots = cms.uint32(30),
    SaveWorkspace = cms.bool(False),
    WeightVariable = cms.string("final_weight"),    

    # defines all the real variables of the probes available in the input tree and intended for use in the efficiencies
    Variables = cms.PSet(
                         diPhoMass           = cms.vstring("dipho Mass", "60.0", "120.0", "GeV/c^{2}"), 
                         probe_pt            = cms.vstring("Probe p_{T}", "40.0", "130.0", "GeV/c"),
                         probe_eta           = cms.vstring("Probe #eta", "-1.5", "1.5", ""),
                         probe_abseta        = cms.vstring("Probe |#eta|", "0.0", "1.5", ""),
                         centBin             = cms.vstring("centr", "0", "200", ""),
                         final_weight        = cms.vstring("weight", "-1.", "20.", "")
    ),
    # defines all the discrete variables of the probes available in the input tree and intended for use in the efficiency calculations
    Categories = cms.PSet(
                        passID = cms.vstring("passID", "dummy[true=1,false=0]"),
    ),

    # defines all the PDFs that will be available for the efficiency calculations; uses RooFit's "factory" syntax;
    # each pdf needs to define "signal", "backgroundPass", "backgroundFail" pdfs, "efficiency[0.9,0,1]" and "signalFractionInPassing[0.9]" are used for initial values  
    PDFs = cms.PSet(
      VoigtExp = cms.vstring(
         "Voigtian::signal(diPhoMass, mean[91,85,95], width[3,1,10], sigma[3,1,10])",
         "Exponential::backgroundPass(diPhoMass, lp[0,-5,5])",
         "Exponential::backgroundFail(diPhoMass, lf[0,-5,5])",
         "efficiency[0.9,0,1]",
         "signalFractionInPassing[0.9]"
         ),
      BWResCBExp = cms.vstring(
         "BreitWigner::bw(diPhoMass, m0[91.2,81.2,101.2], width[2.495,1,10])",
         "RooCBShape::res(diPhoMass, peak[0], sigma[1.7,0.01,10], alpha[1.8,0,3], n[0.8,0,10])",
         "FCONV::signal(diPhoMass, bw, res)",
         "Exponential::backgroundPass(diPhoMass, lp[0,-5,5])",
         "Exponential::backgroundFail(diPhoMass, lf[0,-5,5])",
         "efficiency[0.9,0.5,1]",
         "signalFractionInPassing[0.9]",
         ),
      BWResCBCheb = cms.vstring(
         "BreitWigner::bw(diPhoMass, m0[91.2,81.2,101.2], width[2.495,1,10])",
         "RooCBShape::res(diPhoMass, peak[0], sigma[1.7,0.01,10], alpha[1.8,0,3], n[0.8,0,10])",
         "FCONV::signal(diPhoMass, bw, res)",
         "Chebychev::backgroundPass(diPhoMass, {c1p[0,-10,10], c2p[0,-10,10], c3p[0,-10,10]})",
         "Chebychev::backgroundFail(diPhoMass, {c1f[0,-10,10], c2f[0,-10,10], c3f[0,-10,10]})",
         "efficiency[0.9,0.5,1]",
         "signalFractionInPassing[0.9]",
         ),
      
     ),
    # defines a set of efficiency calculations, what PDF to use for fitting and how to bin the data;
    # there will be a separate output directory for each calculation that includes a simultaneous fit, side band subtraction and counting. 
    Efficiencies = EFFICIENCYSET 
)

process.fitness = cms.Path(
    process.tagProbeFitTreeAnalyzer
)
