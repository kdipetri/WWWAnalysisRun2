#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "TChain.h"
#include "TCut.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/DataLoader.h"
#include "TMVA/TMVAGui.h"

#include "rooutil/rooutil.cc"

using namespace std;

int main(int argc, char** argv)
{
    // Output file
    TFile* outputFile = TFile::Open("BDT.root", "RECREATE");

    // Initialize TMVA
    TMVA::Tools::Instance();
    TMVA::Factory *factory = new TMVA::Factory("TMVA", outputFile, "V:DrawProgressBar=True:Transformations=I;D;P;G:AnalysisType=Classification");

    // sample parent directory
    TString dirpath = "/hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6";

    // Get signal sample TChain
    TString WWWSampleGlobber = dirpath + "/MAKER_WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/www_amcatnlo_*.root";
    TChain* WWWChain = RooUtil::FileUtil::createTChain("t", WWWSampleGlobber);

    // Get WZ sample TChain
    TString WZSampleGlobber = dirpath + "/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_*.root";
    TChain* WZChain = RooUtil::FileUtil::createTChain("t_lostlep", WZSampleGlobber);

    // Data Loader
    TMVA::DataLoader* dataloader = new TMVA::DataLoader("dataset");
    dataloader->AddSignalTree(WWWChain, 1.0);
    dataloader->AddBackgroundTree(WZChain, 1.0);
    dataloader->SetSignalWeightExpression("evt_scale1fb");
    dataloader->SetBackgroundWeightExpression("evt_scale1fb");

    // Add Variables
    dataloader->AddVariable("Pt3l");
    dataloader->AddVariable("DPhi3lMET");
    dataloader->AddVariable("nj", 'I');
    dataloader->AddVariable("nj30", 'I');

    // Prepare events
    TCut cut = "(nVlep == 3) * (nLlep == 3) * (nTlep == 3) * (lep_pt[0]>25.) * (pass_duplicate_ee_em_mm) * (nSFOS == 0)";
    //TCut cut = "1";
    //dataloader->PrepareTrainingAndTestTree(cut, cut, "nTest_Signal=100000:nTest_Background=100000:nTrain_Signal=100000:nTrain_Background=100000:SplitMode=random:!V");
    dataloader->PrepareTrainingAndTestTree(cut, cut, "SplitMode=random:!V");

    //TString option = "!H:V:NTrees=2000:BoostType=Grad:Shrinkage=1:!UseBaggedGrad:nCuts=20:MinNodeSize=3.%:MaxDepth=3:CreateMVAPdfs:SeparationType=SDivSqrtSPlusB:DoBoostMonitor";
    TString option = "!H:V:NTrees=2000:BoostType=Grad:Shrinkage=1:!UseBaggedGrad:nCuts=20:MinNodeSize=3.%:MaxDepth=3:CreateMVAPdfs:DoBoostMonitor";
    factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDT", option);
    factory->TrainAllMethods();
    factory->TestAllMethods();
    factory->EvaluateAllMethods();

    return 0;
}


//"/hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_1.root",
//"/hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_2.root",
//"/hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_3.root",
//"/hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_4.root",
//"/hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_5.root",
//"/hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_6.root",
//"/hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_7.root",
//"/hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_8.root",
//"/hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_9.root",
//"/hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_10.root",
//"/hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_11.root",

//    // Get WJets background sample TChains
//    std::vector<TString> WJetsSampleGlobbers = {
//        dirpath + "/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_HWW2016_skimmed_v2_v1.15.1/*.root",
//        dirpath + "/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_HWW2016_skimmed_v2_v1.15.1/*.root",
//        dirpath + "/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_HWW2016_skimmed_v2_v1.15.1/*.root",
//        dirpath + "/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_HWW2016_skimmed_v2_v1.15.1/*.root",
//        dirpath + "/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1_MINIAODSIM_HWW2016_skimmed_v2_v1.15.1/*.root",
//        dirpath + "/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1_MINIAODSIM_HWW2016_skimmed_v2_v1.15.1/*.root",
//        };
//    std::vector<TChain*> WJetsChains;
//    for (auto& sampleglobber : WJetsSampleGlobbers)
//        WJetsChains.push_back(RooUtil::FileUtil::createTChain("t", sampleglobber));

//    for (auto& WJetsChain : WJetsChains) dataloader->AddBackgroundTree(WJetsChain, 1.0);

///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_DYJetsToLL_M-10to50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2_MINIAODSIM_WWW2017_v4.0.6/merged/dy_m10_madpgrah_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1_MINIAODSIM_WWW2017_v4.0.6/merged/dy_m50_amcatnlo_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_DoubleEG_Run2017B-31Mar2018-v1_MINIAOD_WWW2017_v4.0.6/merged/data_Run2017B_ee_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_DoubleEG_Run2017C-31Mar2018-v1_MINIAOD_WWW2017_v4.0.6/merged/data_Run2017C_ee_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_DoubleEG_Run2017D-31Mar2018-v1_MINIAOD_WWW2017_v4.0.6/merged/data_Run2017D_ee_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_DoubleEG_Run2017E-31Mar2018-v1_MINIAOD_WWW2017_v4.0.6/merged/data_Run2017E_ee_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_DoubleEG_Run2017F-31Mar2018-v1_MINIAOD_WWW2017_v4.0.6/merged/data_Run2017F_ee_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_DoubleMuon_Run2017B-31Mar2018-v1_MINIAOD_WWW2017_v4.0.6/merged/data_Run2017B_mm_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_DoubleMuon_Run2017C-31Mar2018-v1_MINIAOD_WWW2017_v4.0.6/merged/data_Run2017C_mm_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_DoubleMuon_Run2017D-31Mar2018-v1_MINIAOD_WWW2017_v4.0.6/merged/data_Run2017D_mm_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_DoubleMuon_Run2017E-31Mar2018-v1_MINIAOD_WWW2017_v4.0.6/merged/data_Run2017E_mm_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_DoubleMuon_Run2017F-31Mar2018-v1_MINIAOD_WWW2017_v4.0.6/merged/data_Run2017F_mm_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ggh_hzz4l_powheg_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_GluGluHToZZTo4L_M125_13TeV_powheg2_JHUGenV7011_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ggh_hzz4l_powheg_2.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_MuonEG_Run2017B-31Mar2018-v1_MINIAOD_WWW2017_v4.0.6/merged/data_Run2017B_em_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_MuonEG_Run2017C-31Mar2018-v1_MINIAOD_WWW2017_v4.0.6/merged/data_Run2017C_em_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_MuonEG_Run2017D-31Mar2018-v1_MINIAOD_WWW2017_v4.0.6/merged/data_Run2017D_em_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_MuonEG_Run2017E-31Mar2018-v1_MINIAOD_WWW2017_v4.0.6/merged/data_Run2017E_em_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_MuonEG_Run2017F-31Mar2018-v1_MINIAOD_WWW2017_v4.0.6/merged/data_Run2017F_em_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/singletop_schanlep_amcatnlo_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/singletop_antitop_powheg_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/singletop_top_powheg_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/tw_antitopnofullhad_powheg_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/tw_topnofullhad_powheg_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_TTGamma_SingleLeptFromT_TuneCP5_PSweights_13TeV_madgraph_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ttg_1ltop_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_TTGamma_SingleLeptFromTbar_TuneCP5_PSweights_13TeV_madgraph_pythia8_RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ttg_1ltbr_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ttbar_2l_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_TTJets_SingleLeptFromT_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ttbar_1ltop_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_TTJets_SingleLeptFromTbar_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ttbar_1ltbr_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ttw_lv_amcatnlo_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ttw_lv_amcatnlo_2.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ttw_lv_amcatnlo_3.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ttw_lv_amcatnlo_4.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_TTWJetsToLNu_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ttw_lv_amcatnlo_5.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_TTWJetsToQQ_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ttw_qq_amcatnlo_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ttz_llvvm10_amcatnlo_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ttz_llvvm10_amcatnlo_2.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ttz_llvvm10_amcatnlo_3.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ttz_llvvm10_amcatnlo_4.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ttz_llvvm10_amcatnlo_5.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ttz_llvvm10_amcatnlo_6.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_TTZToLLNuNu_M-10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ttz_llvvm10_amcatnlo_7.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ttz_llm1to10_amcatnlo_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_TTZToQQ_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ttz_qq_amcatnlo_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_VHToNonbb_M125_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_WWW2017_v4.0.6/merged/vh_nonbb_amcatnlo_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_WWW2017_v4.0.6/merged/wjets_ht100_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wjets_ht1200_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wjets_ht200_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3_MINIAODSIM_WWW2017_v4.0.6/merged/wjets_ht2500_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wjets_ht400_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wjets_ht600_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wjets_ht800_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14_ext1-v2_MINIAODSIM_WWW2017_v4.0.6/merged/wjets_incl_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WWW_4F_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/www_amcatnlo_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WWZ_4F_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wwz_amcatnlo_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WW_DoubleScattering_13TeV-pythia8_TuneCP5_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ww_dblsct_pythia_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WW_TuneCP5_13TeV-pythia8_RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_MINIAODSIM_WWW2017_v4.0.6/merged/ww_pythia_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZG_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wzg_amcatnlo_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_WWW2017_v4.0.6/merged/wz_1l2q_amcatnlo_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8_v2_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_1l3v_amcatnlo_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_2l2q_amcatnlo_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_0Jets_MLL-4to50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_0jmll4_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_0Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v3_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_0jmll50_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_13TeV-powheg-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_powheg_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_1Jets_MLL-4to50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_1jmll4_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_1Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_1jmll50_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_1Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_1jmll50_madgraph_2.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_2Jets_MLL-4to50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_2jmll4_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_2Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_2jmll50_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_2Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_2jmll50_madgraph_2.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_2Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_2jmll50_madgraph_3.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_3Jets_MLL-4to50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_3jmll4_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_3Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_3jmll50_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_3Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_3jmll50_madgraph_2.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_3Jets_MLL-50_TuneCP5_13TeV-madgraphMLM-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_3jmll50_madgraph_3.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_10.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_11.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_2.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_3.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_4.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_5.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_6.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_7.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_8.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_3lv_amcatnlo_9.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZZ_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wzz_amcatnlo_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WZ_TuneCP5_13TeV-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/wz_incl_amcatnlo_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_WpWpJJ_EWK-QCD_TuneCP5_13TeV-madgraph-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/vbsww_madgraph_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_ZZTo4L_13TeV_powheg_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/zz_4l_powheg_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_ZZTo4L_13TeV_powheg_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/zz_4l_powheg_2.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_ZZTo4L_13TeV_powheg_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/zz_4l_powheg_3.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_ZZTo4L_13TeV_powheg_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/zz_4l_powheg_4.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_ZZTo4L_13TeV_powheg_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/zz_4l_powheg_5.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_ZZTo4L_13TeV_powheg_pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/zz_4l_powheg_6.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_ZZZ_TuneCP5_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/zzz_amcatnlo_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/tzq_ll_amcatnlo_1.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/tzq_ll_amcatnlo_10.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/tzq_ll_amcatnlo_11.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/tzq_ll_amcatnlo_12.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/tzq_ll_amcatnlo_13.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/tzq_ll_amcatnlo_2.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/tzq_ll_amcatnlo_3.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/tzq_ll_amcatnlo_4.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/tzq_ll_amcatnlo_5.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/tzq_ll_amcatnlo_6.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/tzq_ll_amcatnlo_7.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/tzq_ll_amcatnlo_8.root
///hadoop/cms/store/user/phchang/metis/wwwbaby/WWW2017_v4.0.6/MAKER_tZq_ll_4f_ckm_NLO_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1_MINIAODSIM_WWW2017_v4.0.6/merged/tzq_ll_amcatnlo_9.root
