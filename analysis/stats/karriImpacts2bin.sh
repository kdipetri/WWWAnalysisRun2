
#sh combinecards_in_dir.sh  /home/users/kdipetri/public_html/WWWAnalysisRun2/analysis/datacards_ssmumu www_ssmumu_datacard.txt 

datacard=www_ssmumu_3bin_datacard
#datacard=www_ssmumu_datacard
text2workspace.py ${datacard}.txt -m 125


CMSSW_8_1_0/src/CombineHarvester/CombineTools/scripts/combineTool.py -M Impacts -d ${datacard}.root -m 125 -t -1  --doInitialFit --robustFit 1 --expectSignal=1
CMSSW_8_1_0/src/CombineHarvester/CombineTools/scripts/combineTool.py -M Impacts -d ${datacard}.root -m 125 -t -1 --robustFit 1 --doFits --parallel 15 --expectSignal=1
CMSSW_8_1_0/src/CombineHarvester/CombineTools/scripts/combineTool.py -M Impacts -d ${datacard}.root -m 125 -t -1 -o impacts_${datacard}.json 
CMSSW_8_1_0/src/CombineHarvester/CombineTools/scripts/plotImpacts.py -i impacts_${datacard}.json -o impacts_${datacard}

