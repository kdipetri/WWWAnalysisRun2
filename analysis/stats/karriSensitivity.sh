# Nominal Signal regions 
#sh combinecards_in_dir.sh  /home/users/kdipetri/public_html/WWWAnalysisRun2/analysis/datacards_simple  www_nominal_datacard.txt 
#
## make a workspace from nominal www datacard
#text2workspace.py www_nominal_datacard.txt 
#
## compute significance
#combine -M ProfileLikelihood --significance www_nominal_datacard.root -t -1 --expectSignal=1 --rMin -50 --rMax 50
#
#
## two bins for ss mumu mjj in and mjj out
#sh combinecards_in_dir.sh  /home/users/kdipetri/public_html/WWWAnalysisRun2/analysis/datacards_ssmumu www_ssmumu_datacard.txt 
#
#text2workspace.py www_ssmumu_datacard.txt
#
#combine -M ProfileLikelihood --significance www_ssmumu_datacard.root -t -1 --expectSignal=1 --rMin -50 --rMax 50


# mjj SR
#cp /home/users/kdipetri/public_html/WWWAnalysisRun2/analysis/datacards_ssmjj/* .
#text2workspace.py www_ssmjj.txt

combine -n SignifExp -M Significance --significance www_ssmjj.root -t -1 --expectSignal=1
