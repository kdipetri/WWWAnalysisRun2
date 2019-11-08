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

#
# mjj SR
#

# Copy datacards to stat dir
cp /home/users/kdipetri/public_html/WWWAnalysisRun2/analysis/datacards_ssmjj/* datacards_ssmjj/.

# setup for output
rm output.txt
touch output.txt

# loop through options 
#for hist in MjjLZoom ; do
#	for rebin in 2 ; do
for hist in Mjj MjjLZoom ; do
	for rebin in 2 3 4 5 6; do
	
	   # save the configuraiton 
	   echo "${hist} rebin${rebin}" >> output.txt  
	
	   # make root workspace
	   text2workspace.py datacards_ssmjj/www_ssmjj___${hist}_rebin${rebin}.txt	

	   # compute expected 
	   combine -n SignifExp -M Significance --significance datacards_ssmjj/www_ssmjj___${hist}_rebin${rebin}.root -t -1 --expectSignal=1 | grep "Significance:" >> output.txt 
	
	   # compute observed
	   combine -n SignifExp -M Significance --significance datacards_ssmjj/www_ssmjj___${hist}_rebin${rebin}.root | grep "Significance:" >> output.txt 
	done
done
