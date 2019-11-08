#!/bin/env python

from rooutil import datacard_writer as dw
from rooutil import pyrootutil as pr
import ROOT as r
import sys

histpath = sys.argv[1]

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

fname_photon  = "{}/photon.root".format(histpath)
#fname_qflip   = "{}/qflip.root".format(histpath)
fname_ddfakes = "{}/ddfakes.root".format(histpath)
fname_lostlep = "{}/lostlep.root".format(histpath)
fname_prompt  = "{}/prompt.root".format(histpath)
fname_signal  = "{}/signal.root".format(histpath)

print(fname_photon)

file_photon  = r.TFile.Open(fname_photon)
#file_qflip   = r.TFile.Open(fname_qflip)
file_ddfakes = r.TFile.Open(fname_ddfakes)
file_lostlep = r.TFile.Open(fname_lostlep)
file_prompt  = r.TFile.Open(fname_prompt)
file_signal  = r.TFile.Open(fname_signal)

hist_name = "SRSSmmKinSel__Mjj"
hist_photon  = file_photon.Get(hist_name) 
#hist_qflip   = file_qflip.Get(hist_name)  
hist_ddfakes = file_ddfakes.Get(hist_name)
hist_lostlep = file_lostlep.Get(hist_name)
hist_prompt  = file_prompt.Get(hist_name) 
hist_signal  = file_signal.Get(hist_name) 

hists = []
hists.append( hist_photon  ) 
#hists.append( hist_qflip   ) 
hists.append( hist_ddfakes ) 
hists.append( hist_lostlep ) 
hists.append( hist_prompt  ) 
hists.append( hist_signal  ) 

#for fname in fnames:
#
#    tmp_file = r.TFile.Open(fname)
#    tmp_hist = tmp_file.Get(hist_name)
#    hists.append(tmp_hist)

#print hists

bkg_hists = hists[:-1]
sig_hists = [hists[-1]]

bkg_hists[0].SetName("photon")
#bkg_hists[1].SetName("qflip")
bkg_hists[1].SetName("ddfakes")
bkg_hists[2].SetName("lostlep")
bkg_hists[3].SetName("prompt")
sig_hists[0].SetName("signal")

bkg_hists[0].SetTitle("photon")
#bkg_hists[1].SetTitle("qflip")
bkg_hists[1].SetTitle("ddfakes")
bkg_hists[2].SetTitle("lostlep")
bkg_hists[3].SetTitle("prompt")
sig_hists[0].SetTitle("signal")

totals_hist = sig_hists[0].Clone("totals_hist")
totals_hist.Add(bkg_hists[0])
totals_hist.Add(bkg_hists[1])
totals_hist.Add(bkg_hists[2])
totals_hist.Add(bkg_hists[3])
#totals_hist.Add(bkg_hists[4])


data_hist = totals_hist.Clone("data_obs")
data_hist.SetTitle("data_obs")
data_hist.Reset()

photon_total=0
#qflip_total=0
ddfakes_total=0
lostlep_total=0
prompt_total=0
signal_total=0
data_total=0
for bin in range(0,totals_hist.GetNbinsX()+2):
	content = totals_hist.GetBinContent(bin)
	rounded_content = int(totals_hist.GetBinContent(bin))
	err = (float(rounded_content))**0.5
	print(bin, content, rounded_content , err)
	data_hist.SetBinContent(bin,rounded_content)
	data_hist.SetBinError(bin,err)
	data_total += rounded_content
	photon_total  += hist_photon.GetBinContent(bin) 
	#qflip_total   += hist_qflip.GetBinContent(bin) 
	ddfakes_total += hist_ddfakes.GetBinContent(bin)
	lostlep_total += hist_lostlep.GetBinContent(bin)
	prompt_total  += hist_prompt.GetBinContent(bin)
	signal_total  += hist_signal.GetBinContent(bin)

print(data_hist.GetTitle()   , data_total   , data_hist.Integral(0,-1))
print(hist_photon.GetTitle() , photon_total , hist_photon.Integral(0,-1))
#print(hist_qflip.GetTitle()  , qflip_total  , hist_qflip.Integral(0,-1))
print(hist_ddfakes.GetTitle(), ddfakes_total, hist_ddfakes.Integral(0,-1))
print(hist_lostlep.GetTitle(), lostlep_total, hist_lostlep.Integral(0,-1))
print(hist_prompt.GetTitle() , prompt_total , hist_prompt.Integral(0,-1))
print(hist_signal.GetTitle() , signal_total , hist_signal.Integral(0,-1))

for hist in hists:
	print (hist.GetTitle(), hist.Integral(0,-1))


# Now create data card writer
# bkg2 does not need stat error as it is taken care of by CR stats
shapes_out="www_ssmjj_input_shapes.root"
d = dw.DataCardWriter(sig=sig_hists[0], bgs=bkg_hists, data=data_hist, systs=systs, shape_fit=True, shape_file=shapes_out, no_stat_procs=["ddfakes", "lostlep"])

i=1
d.set_bin(i) # just for giggles?
d.set_region_name("bin{}".format(i)) # just for giggles?
d.write("datacards_ssmjj/www_ssmjj.txt".format(i))

file_out="datacards_ssmjj/"+shapes_out
f=r.TFile.Open(file_out,"RECREATE")
f.cd()
bkg_hists[0].Write()
bkg_hists[1].Write()
bkg_hists[2].Write()
bkg_hists[3].Write()
#bkg_hists[4].Write()
sig_hists[0].Write()
data_hist.Write()
#f.close()

