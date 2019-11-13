## two bins for ss mumu mjj in and mjj out
sh combinecards_in_dir.sh  /home/users/kdipetri/public_html/WWWAnalysisRun2/analysis/datacards_ssmumu www_ssmumu_datacard.txt 

text2workspace.py www_ssmumu_datacard.txt

combine -M ProfileLikelihood --significance www_ssmumu_datacard.root -t -1 --expectSignal=1 --rMin -50 --rMax 50
