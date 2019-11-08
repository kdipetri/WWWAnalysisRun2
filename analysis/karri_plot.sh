#python plot.py -i "hists/combineyearsLoose_v5.3.2/karri_test_wsys/"  -u -m #yields  
#python plot.py -i "hists/combineyearsLoose_v5.3.2/karri_test_wsys/"  -m  SRSSeeKinSel__Mjj 
#python plot.py -i "hists/combineyearsLoose_v5.3.2/karri_test_wsys/"  -m  SRSSemKinSel__Mjj
python plot.py -d -i "hists/combineyearsLoose_v5.3.2/karri_test_binning/"  -m  SRSSmmKinSel__Mjj
python plot.py -d -i "hists/combineyearsLoose_v5.3.2/karri_test_binning/"  -m  SRSSmmKinSel__MjjL
python plot.py -d -i "hists/combineyearsLoose_v5.3.2/karri_test_binning/"  -m  SRSSmmKinSel__MjjZoom
python plot.py -d -i "hists/combineyearsLoose_v5.3.2/karri_test_binning/"  -m  SRSSmmKinSel__MjjLZoom


# options
#'-i' , '--input_dir'              , dest='input_dir'       , help='input dir path (where hists are) NOTE: pattern MUST be hists/${BABY_VERSION}/${TAG}/', required=True      ) 
#'-o' , '--output_dir'             , dest='output_dir'      , help='output dir path'                        , default='plots'                                                 ) 
#'-n' , '--nbins'                  , dest='nbins'           , help='number of bins for the histograms'      , default=30                                                      ) 
#'-xt', '--xaxis_title'            , dest='xaxis_title'     , help='X-axis title'                           , default=None                                                    ) 
#'-y' , '--yaxis_range'            , dest='yaxis_range'     , help='Y-axis range set by user'               , default=None                                                    ) 
#'-l' , '--yaxis_log'              , dest='yaxis_log'       , help='Y-axis set to log'                      , default=False                              , action='store_true') 
#'-s' , '--sig_scale'              , dest='sig_scale'       , help='Signal scale'                           , default=1                                                       ) 
#'-u' , '--rm_udflow'              , dest='rm_udflow'       , help='Remove underflow'                       , default=False                              , action='store_true') 
#'-S' , '--do_scan'                , dest='do_scan'         , help='Do cut scan'                            , default=False                              , action='store_true') 
#'-d' , '--draw_data'              , dest='draw_data'       , help='Draw data'                              , default=False                              , action='store_true') 
#'-1' , '--stack_signal'           , dest='stack_signal'    , help='stack signal'                           , default=False                              , action='store_true') 
#'-v' , '--split_signal'           , dest='split_signal'    , help='Split signal'                           , default=False                              , action='store_true') 
#'-7' , '--split_vbsttw'           , dest='split_vbsttw'    , help='Split VBS and ttW background'           , default=False                              , action='store_true') 
#'-m' , '--use_mc_fake'            , dest='use_mc_fake'     , help='use_mc_fake'                            , default=False                              , action='store_true') 
#'-P' , '--use_private_sig_sample' , dest='use_private'     , help='Use private signal sample'              , default=False                              , action='store_true') 
#'-a' , '--sum_hists'              , dest='sum_hists'       , help='Sum all hists that passes filter'       , default=False                              , action='store_true') 
#'-O' , '--output_name'            , dest='output_name'     , help='output file name when using sum_hists'  , default=None                                                    ) 
#'-t' , '--syst'                   , dest='syst'            , help='Specific syst variation'                , default=""                                                      ) 
#'-8' , '--do_grep'                , dest='do_grep'         , help='Use filter as pattern matching'         , default=False                              , action='store_true') 
#'-p' , '--order_by_purity'        , dest='order_by_purity' , help='Rearrange 9 bin SR plot by S/B purity'  , default=False                              , action='store_true') 
#'-uw', '--usewhatSR'              , dest='usewhatSR'       , help='what selecton for the nine bins'        , default=False, action='store_true') 
#'-w' , '--whatSR'                 , dest='whatSR'          , help='what selecton for the nine bins'        , default=["SRSSeeMjjInFull", "SRSSemMjjInFull", "SRSSmmMjjInFull", "SRSSeeMjjOutFull", "SRSSemMjjOutFull", "SRSSemMjjOutFull", "SRSS1JeeFull", "SRSS1JemFull", "SRSS1JmmFull", "SR0SFOSFull", "SR1SFOSFull", "SR2SFOSFull",], nargs='+') 
#'hist_filters', metavar='<histogram_names>=(e.g. SRSSmmPre__lep_pt1,SRSSmmNj2__lep_pt1)', type=str, nargs='*', help='patterns to use to filter histograms to dump')
