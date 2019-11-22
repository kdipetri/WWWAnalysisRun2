## single bin for full ss mu mu
#sh combinecards_in_dir.sh  /home/users/kdipetri/public_html/WWWAnalysisRun2/analysis/datacards_ssmumu_inclusive www_ssmumu_inclusive_datacard.txt 

#text2workspace.py www_ssmumu_inclusive_datacard.txt

#combine -M ProfileLikelihood --significance www_ssmumu_inclusive_datacard.root -t -1 --expectSignal=1 --rMin -50 --rMax 50


## two bins for ss mumu mjj in and mjj out
#sh combinecards_in_dir.sh  /home/users/kdipetri/public_html/WWWAnalysisRun2/analysis/datacards_ssmumu www_ssmumu_datacard.txt 

text2workspace.py www_ssmumu_datacard.txt

combine -M ProfileLikelihood --significance www_ssmumu_datacard.root -n ExpPre -t -1 --expectSignal=1 --rMin -50 --rMax 50

## one bin fit for ss mumu mjj in 
#sh combinecards_in_dir.sh  /home/users/kdipetri/public_html/WWWAnalysisRun2/analysis/datacards_ssmumumjjin www_ssmumu_mjjin_datacard.txt 

text2workspace.py www_ssmumu_mjjin_datacard.txt

combine -M ProfileLikelihood --significance www_ssmumu_mjjin_datacard.root -n ExpPre -t -1 --expectSignal=1 --rMin -50 --rMax 50

# one bit fit for ss mumu mjj out
#sh combinecards_in_dir.sh  /home/users/kdipetri/public_html/WWWAnalysisRun2/analysis/datacards_ssmumumjjout www_ssmumu_mjjout_datacard.txt

text2workspace.py www_ssmumu_mjjout_datacard.txt

combine -M ProfileLikelihood --significance www_ssmumu_mjjout_datacard.root -n ExpPre -t -1 --expectSignal=1 --rMin -50 --rMax 50

## three bins for ss mumu mjj low in high 
#sh combinecards_in_dir.sh  /home/users/kdipetri/public_html/WWWAnalysisRun2/analysis/datacards_ssmumu_3bin www_ssmumu_3bin_datacard.txt 

text2workspace.py www_ssmumu_3bin_datacard.txt

combine -M ProfileLikelihood --significance www_ssmumu_3bin_datacard.root -n ExpPre -t -1 --expectSignal=1 --rMin -50 --rMax 50
