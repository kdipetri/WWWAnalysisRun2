#!/bin/env python

from rooutil import datacard_writer as dw
from rooutil import pyrootutil as pr
import ROOT as r
import sys


# Systematics
# Supported types of input are
#    1. [TH1, TH1] # up and down variation
#    2. TH1
#    3. [float, float] # up and down variation
#    4. float
#    5. str         # direct input
#    6. [str, ... ] # direct input per bin
#    7. None
# All of the yields on these are expected to be the YIELDS AFTER SYST IS APPLIED. (i.e. NOT FRACTIONS)
# You can mix and match
systs = []

# removing qflip , has no events for mumu channel 
#20% symmetric error on prompt
systs.append( ("promptSyst"  , "lnN" , [] , {"signal":0 , "prompt":"1.15" , "photon":0     , "ddfakes":0     , "lostlep":0}) )
systs.append( ("ddfakesSyst" , "lnN" , [] , {"signal":0 , "prompt":0     , "photon":0      , "ddfakes":"1.5" , "lostlep":0}) )
systs.append( ("lostlepSyst" , "lnN" , [] , {"signal":0 , "prompt":0     , "photon":0      , "ddfakes":0     , "lostlep":1.2}) )
#systs.append( ("qflipSyst"   , "lnN" , [] , {"signal":0 , "prompt":0     , "photon":0      , "ddfakes":0     , "lostlep":0}) )
systs.append( ("photonSyst"  , "lnN" , [] , {"signal":0 , "prompt":0     , "photon":"1.15" , "ddfakes":0     , "lostlep":0}) )
## 20% symmetric error on prompt
#systs.append( ("promptSyst"  , "lnN" , [] , {"signal":0 , "prompt":"1.15" , "photon":0     , "qflip":0     , "ddfakes":0     , "lostlep":0}) )
#systs.append( ("ddfakesSyst" , "lnN" , [] , {"signal":0 , "prompt":0     , "photon":0     , "qflip":0     , "ddfakes":"1.5" , "lostlep":0}) )
#systs.append( ("lostlepSyst" , "lnN" , [] , {"signal":0 , "prompt":0     , "photon":0     , "qflip":0     , "ddfakes":0     , "lostlep":1.2}) )
#systs.append( ("qflipSyst"   , "lnN" , [] , {"signal":0 , "prompt":0     , "photon":0     , "qflip":"1.15" , "ddfakes":0     , "lostlep":0}) )
#systs.append( ("photonSyst"  , "lnN" , [] , {"signal":0 , "prompt":0     , "photon":"1.15" , "qflip":0     , "ddfakes":0     , "lostlep":0}) )


histpath = sys.argv[1]

# process info
processes = []
processes.append("data")
processes.append("photon")
#processes.append("qflip")
processes.append("ddfakes")
processes.append("lostlep")
processes.append("prompt")
processes.append("signal")

# signal region
region = "SRSSmmKinSel"
label = "mm"

# different xmax
hist_suffixes = []
hist_suffixes.append("__Mjj")#xmax = 300	
hist_suffixes.append("__MjjZoom")#xmax = 150
hist_suffixes.append("__MjjLZoom")#xmax = 500
hist_suffixes.append("__MjjL")#xmax = 750

# nominal number of bins is 180
rebins = []
rebins.append(0)#180 bins
rebins.append(2)#90 bins
rebins.append(3)#60 bins
rebins.append(4)#45 bins
rebins.append(5)#36 bins
rebins.append(6)#30 bins

for hist_suffix in hist_suffixes:
	#print(hist_suffix)
	for rebin in rebins:  

	    hists = []
	    for process in processes: 
    	        hists.append(
                	pr.get_yield_histogram(
                        list_of_file_names = [  "{}/{}.root".format(histpath,process) ],
                        regions = [region], 
                        labels = [label], 
                        hsuffix = hist_suffix, 
			histName = process,
			doShape=True
                    )
                )
	    for hist in hists:
		#print(hist.GetName(), hist.Integral(0,-1))
		if rebin > 0 : hist.Rebin(rebin)
	
	    # separate into components
	    data_hist = hists[0]
	    bkg_hists = hists[1:-1]
	    sig_hists = [hists[-1]]

	    # Silly formating
	    data_hist.SetName("data_obs")
	    data_hist.SetTitle("data_obs")


	    # Now create data card writer
	    # bkg2 does not need stat error as it is taken care of by CR stats
	    outdir = "datacards_ssmjj"
	    shapes_out="{}/www_ssmjj_input_shapes_{}_rebin{}.root".format(outdir,hist_suffix,str(rebin))
	    d = dw.DataCardWriter(sig=sig_hists[0], bgs=bkg_hists, data=data_hist, systs=systs, shape_fit=True, shape_file=shapes_out, no_stat_procs=["ddfakes", "lostlep"])
	    
	    i=1
	    d.set_bin(i) # just for giggles?
	    d.set_region_name("bin{}".format(i)) # just for giggles?
	    d.write("{}/www_ssmjj_{}_rebin{}.txt".format(outdir, hist_suffix,str(rebin)))
	    
	    f=r.TFile.Open(shapes_out,"RECREATE")
	    f.cd()
	    bkg_hists[0].Write()
	    bkg_hists[1].Write()
	    bkg_hists[2].Write()
	    bkg_hists[3].Write()
	    #bkg_hists[4].Write()
	    sig_hists[0].Write()
	    data_hist.Write()
	    #f.close()

