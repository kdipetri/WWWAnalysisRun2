##!/bin/env python

# This script submits the jobs to condor
# It takes a while and it is not ideal to run over them on a local machine

################
#
# There is only one setting to be aware of which is the job tag
#
################
# The following defines the tag for this round of submission (change it every time you submit)
job_tag = "test_2019_09_04_1854"

#_____________________________________________________________________________________________
# Create the samples mapping between the sample name -> the location of input sample hadoop directory and arguments map for each sample
samples_map = {}
arguments_map = {}
sample_list = []

tag = "v5.2.0"

# 2016
input_fr_ntup_tag = "FR2016_{}".format(tag)
base_dir_path = "/hadoop/cms/store/user/phchang/metis/wwwbaby/{}/merged".format(input_fr_ntup_tag)
# samples_map[input_fr_ntup_tag+"_ss"] = base_dir_path
# arguments_map[input_fr_ntup_tag+"_ss"] = "0"
# sample_list.append(input_fr_ntup_tag+"_ss")
samples_map[input_fr_ntup_tag+"_3l"] = base_dir_path
arguments_map[input_fr_ntup_tag+"_3l"] = "1"
sample_list.append(input_fr_ntup_tag+"_3l")

# 2017
input_fr_ntup_tag = "FR2017_{}".format(tag)
base_dir_path = "/hadoop/cms/store/user/phchang/metis/wwwbaby/{}/merged".format(input_fr_ntup_tag)
# samples_map[input_fr_ntup_tag+"_ss"] = base_dir_path
# arguments_map[input_fr_ntup_tag+"_ss"] = "0"
# sample_list.append(input_fr_ntup_tag+"_ss")
samples_map[input_fr_ntup_tag+"_3l"] = base_dir_path
arguments_map[input_fr_ntup_tag+"_3l"] = "1"
sample_list.append(input_fr_ntup_tag+"_3l")

# 2018
input_fr_ntup_tag = "FR2018_{}".format(tag)
base_dir_path = "/hadoop/cms/store/user/phchang/metis/wwwbaby/{}/merged".format(input_fr_ntup_tag)
# samples_map[input_fr_ntup_tag+"_ss"] = base_dir_path
# arguments_map[input_fr_ntup_tag+"_ss"] = "0"
# sample_list.append(input_fr_ntup_tag+"_ss")
samples_map[input_fr_ntup_tag+"_3l"] = base_dir_path
arguments_map[input_fr_ntup_tag+"_3l"] = "1"
sample_list.append(input_fr_ntup_tag+"_3l")

# Now submit the job!
import pyrootutil as ru
ru.submit_metis(
        job_tag=job_tag,                                            # The tag for this round of submission
        sample_list=sample_list,                                    # The list of samples to submitted (in this case, the sample list is "sample_name"_ss or _3l.)
        samples_map=samples_map,                                    # The dictionary of where the input locations are for a given sample
        arguments_map=arguments_map,                                # The dictionary of whether to run same-sign or three-lepton
        tar_files=["doAnalysis", "setup.sh", "histmap", "rooutil"], # Files/directories to transfer to working nodes
        exec_script="metis.sh",                                     # Executable to run for each condor job
        hadoop_dirname="franalysis")                                # Where the output of the condor jobs will be (i.e. /hadoop/cms/store/user/${USER}/metis/"hadoop_dirname")

import os

#eof
