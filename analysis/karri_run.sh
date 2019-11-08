
sh process.sh -s -i Loose2016_v5.3.2 -t karri_test_binning -r phchang 
sh process.sh -s -i Loose2017_v5.3.2 -t karri_test_binning -r phchang 
sh process.sh -s -i Loose2018_v5.3.2 -t karri_test_binning -r phchang 

# run like wvz
# sh runall.sh -b mtsum -t WVZ -v v0.1.12.7 -s -1 -2

# Different n-tuples live here 
# /nfs-7/userdata/phchang/WWW_babies/
# using 
# Loose2016_v5.3.2

# options 
# -h    Help                   (Display this message)"
# -i    Input baby version     (e.g. -i WWW2017_v5.0.0)"
# -t    Job tag                (e.g. -t test1)"
# -u    Enable user study"
# -x    Skip cutflow histograms"
# -k    Do skim"
# -s    Do systematics"
# -r    Username for input     (e.g. -r mliu or -r phchang)"


# combinings years

sh combineyearshisto.sh -t karri_test_binning -b Loose -v v5.3.2 

# Options with arguments:"
#   -t    tag used when running the looper (e.g. test_2019_10_12_0610)"
#   -b    baby type                        (e.g. Loose or WWW or VVV or etc.)"
#   -v    baby version                     (e.g. v5.3.0  <- always start with 'v')"


