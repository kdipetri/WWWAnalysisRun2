#ifndef scalefactors_wvz_h
#define scalefactors_wvz_h

#include "wwwtree.h"
#include "rooutil/rooutil.h"
#include "InputConfig.h"

class ScaleFactorWVZ {

public:

    // Scale factors
    RooUtil::HistMap* histmap_2016_elec_reco_highpt_sf;
    RooUtil::HistMap* histmap_2016_elec_reco_lowpt_sf;
    RooUtil::HistMap* histmap_2016_elec_medium_sf;
    RooUtil::HistMap* histmap_2016_elec_veto_sf;
    RooUtil::HistMap* histmap_2017_elec_reco_highpt_sf;
    RooUtil::HistMap* histmap_2017_elec_reco_lowpt_sf;
    RooUtil::HistMap* histmap_2017_elec_medium_sf;
    RooUtil::HistMap* histmap_2017_elec_veto_sf;
    RooUtil::HistMap* histmap_2018_elec_reco_sf;
    RooUtil::HistMap* histmap_2018_elec_medium_sf;
    RooUtil::HistMap* histmap_2018_elec_veto_sf;
    RooUtil::HistMap* histmap_2016_muon_BCDEF_id_sf;
    RooUtil::HistMap* histmap_2016_muon_BCDEF_id_lowpt_sf;
    RooUtil::HistMap* histmap_2016_muon_BCDEF_tightiso_sf;
    RooUtil::HistMap* histmap_2016_muon_BCDEF_looseiso_sf;
    RooUtil::HistMap* histmap_2016_muon_GH_id_sf;
    RooUtil::HistMap* histmap_2016_muon_GH_id_lowpt_sf;
    RooUtil::HistMap* histmap_2016_muon_GH_tightiso_sf;
    RooUtil::HistMap* histmap_2016_muon_GH_looseiso_sf;
    RooUtil::HistMap* histmap_2017_muon_id_sf;
    RooUtil::HistMap* histmap_2017_muon_id_lowpt_sf;
    RooUtil::HistMap* histmap_2017_muon_tightiso_sf;
    RooUtil::HistMap* histmap_2017_muon_looseiso_sf;
    RooUtil::HistMap* histmap_2018_muon_id_sf;
    RooUtil::HistMap* histmap_2018_muon_id_lowpt_sf;
    RooUtil::HistMap* histmap_2018_muon_tightiso_sf;
    RooUtil::HistMap* histmap_2018_muon_looseiso_sf;
    RooUtil::HistMap* histmap_2016_fake_rate_el;
    RooUtil::HistMap* histmap_2016_fake_rate_mu;
    RooUtil::HistMap* histmap_2017_fake_rate_el;
    RooUtil::HistMap* histmap_2017_fake_rate_mu;
    RooUtil::HistMap* histmap_2018_fake_rate_el;
    RooUtil::HistMap* histmap_2018_fake_rate_mu;

    //______________________________________________________________________________________________
    void loadScaleFactors()
    {
        histmap_2016_elec_reco_highpt_sf    = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/EGM2D_BtoH_GT20GeV_RecoSF_Legacy2016.root:EGamma_SF2D"); // x=eta, y=pt
        histmap_2016_elec_reco_lowpt_sf     = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/EGM2D_BtoH_low_RecoSF_Legacy2016.root:EGamma_SF2D"); // x=eta, y=pt
        histmap_2016_elec_medium_sf         = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/2016LegacyReReco_ElectronMedium_Fall17V2.root:EGamma_SF2D"); // x=eta, y=pt
        histmap_2016_elec_veto_sf           = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/2016_ElectronWPVeto_Fall17V2.root:EGamma_SF2D"); // x=eta, y=pt
        histmap_2017_elec_reco_highpt_sf    = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/egammaEffi.txt_EGM2D_runBCDEF_passingRECO.root:EGamma_SF2D"); // x=eta, y=pt
        histmap_2017_elec_reco_lowpt_sf     = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/egammaEffi.txt_EGM2D_runBCDEF_passingRECO_lowEt.root:EGamma_SF2D"); // x=eta, y=pt
        histmap_2017_elec_medium_sf         = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/2017_ElectronMedium.root:EGamma_SF2D"); // x=eta, y=pt
        histmap_2017_elec_veto_sf           = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/2017_ElectronWPVeto_Fall17V2.root:EGamma_SF2D"); // x=eta, y=pt
        histmap_2018_elec_reco_sf           = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/egammaEffi.txt_EGM2D_updatedAll.root:EGamma_SF2D"); // x=eta, y=pt
        histmap_2018_elec_medium_sf         = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/2018_ElectronMedium.root:EGamma_SF2D"); // x=eta, y=pt
        histmap_2018_elec_veto_sf           = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/2018_ElectronWPVeto_Fall17V2.root:EGamma_SF2D"); // x=eta, y=pt
        histmap_2016_muon_BCDEF_id_sf       = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/EfficiencyStudies_2016_rootfiles_RunBCDEF_SF_ID.root:NUM_MediumID_DEN_genTracks_eta_pt"); // x=eta, y=pt
        histmap_2016_muon_BCDEF_id_lowpt_sf = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/EfficiencyStudies_2016_rootfiles_lowpt_RunBCDEF_SF_ID.root:NUM_MediumID_DEN_genTracks_pt_abseta"); // x=pt, y=abseta
        histmap_2016_muon_BCDEF_tightiso_sf = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/EfficiencyStudies_2016_rootfiles_RunBCDEF_SF_ISO.root:NUM_TightRelIso_DEN_MediumID_eta_pt"); // x=eta, y=pt
        histmap_2016_muon_BCDEF_looseiso_sf = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/EfficiencyStudies_2016_rootfiles_RunBCDEF_SF_ISO.root:NUM_LooseRelIso_DEN_MediumID_eta_pt"); // x=eta, y=pt
        histmap_2016_muon_GH_id_sf          = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/EfficiencyStudies_2016_rootfiles_RunGH_SF_ID.root:NUM_MediumID_DEN_genTracks_eta_pt"); // x=eta, y=pt 45% of 2016 data
        histmap_2016_muon_GH_id_lowpt_sf    = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/EfficiencyStudies_2016_rootfiles_lowpt_RunGH_SF_ID.root:NUM_MediumID_DEN_genTracks_pt_abseta"); // x=pt, y=abseta 45% of 2016 data
        histmap_2016_muon_GH_tightiso_sf    = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/EfficiencyStudies_2016_rootfiles_RunGH_SF_ISO.root:NUM_TightRelIso_DEN_MediumID_eta_pt"); // x=eta, y=pt 45% of 2016 data
        histmap_2016_muon_GH_looseiso_sf    = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/EfficiencyStudies_2016_rootfiles_RunGH_SF_ISO.root:NUM_LooseRelIso_DEN_MediumID_eta_pt"); // x=eta, y=pt 45% of 2016 data
        histmap_2017_muon_id_sf             = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/EfficiencyStudies_2017_rootfiles_RunBCDEF_SF_ID.root:NUM_MediumID_DEN_genTracks_pt_abseta"); // x=pt, y=abseta
        histmap_2017_muon_id_lowpt_sf       = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/EfficiencyStudies_2017_rootfiles_lowpt_RunBCDEF_SF_ID_JPsi.root:NUM_MediumID_DEN_genTracks_pt_abseta"); // x=pt, y=abseta
        histmap_2017_muon_tightiso_sf       = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/EfficiencyStudies_2017_rootfiles_RunBCDEF_SF_ISO.root:NUM_TightRelIso_DEN_MediumID_pt_abseta"); // x=pt, y=abseta
        histmap_2017_muon_looseiso_sf       = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/EfficiencyStudies_2017_rootfiles_RunBCDEF_SF_ISO.root:NUM_LooseRelIso_DEN_MediumID_pt_abseta"); // x=pt, y=abseta
        histmap_2018_muon_id_sf             = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/EfficiencyStudies_2018_rootfiles_RunABCD_SF_ID.root:NUM_MediumID_DEN_TrackerMuons_pt_abseta"); // x=pt, y=abseta
        histmap_2018_muon_id_lowpt_sf       = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/EfficiencyStudies_2018_rootfiles_lowpt_RunABCD_SF_ID.root:NUM_MediumID_DEN_genTracks_pt_abseta"); // x=pt, y=abseta
        histmap_2018_muon_tightiso_sf       = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/EfficiencyStudies_2018_rootfiles_RunABCD_SF_ISO.root:NUM_TightRelIso_DEN_MediumID_pt_abseta"); // x=pt, y=abseta
        histmap_2018_muon_looseiso_sf       = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/EfficiencyStudies_2018_rootfiles_RunABCD_SF_ISO.root:NUM_LooseRelIso_DEN_MediumID_pt_abseta"); // x=pt, y=abseta
        histmap_2016_fake_rate_el           = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/fake_rate_el_2016.root:fake_rate_el_data");
        histmap_2016_fake_rate_mu           = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/fake_rate_mu_2016.root:fake_rate_mu_data");
        histmap_2017_fake_rate_el           = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/fake_rate_el_2017.root:fake_rate_el_data");
        histmap_2017_fake_rate_mu           = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/fake_rate_mu_2017.root:fake_rate_mu_data");
        histmap_2018_fake_rate_el           = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/fake_rate_el_2018.root:fake_rate_el_data");
        histmap_2018_fake_rate_mu           = new RooUtil::HistMap("/nfs-7/userdata/phchang/analysis_data/scalefactors/wvz/v1/fake_rate_mu_2018.root:fake_rate_mu_data");

    }

    //______________________________________________________________________________________________
    float IndividualLeptonScaleFactor(int lep_idx, bool isNominal, int vare=0, int varm=0)
    {
        if (vare != 0 and vare != 1 and vare != -1)
            RooUtil::error(TString::Format("Unrecognized variation value vare = %d", vare).Data(), "IndividualLeptonScaleFactor");
        if (varm != 0 and varm != 1 and varm != -1)
            RooUtil::error(TString::Format("Unrecognized variation value varm = %d", varm).Data(), "IndividualLeptonScaleFactor");
        if (www.isData())
            return 1.;
        // Based on lep_Veto indices
        float scalefactor = 1;
        if (lep_idx < 0)
            return 1;
        int absid = abs(www.lep_pdgId().at(lep_idx));
        float pt = absid == 11 ? std::min((double) www.lep_pt().at(lep_idx), 499.9) : std::min((double) www.lep_pt().at(lep_idx), 119.9);
        float eta = www.lep_eta().at(lep_idx);
        float abseta = fabs(eta);
        int year = input.year;
        if (absid == 11)
        {
            if (year == 2016)
            {
                if (pt > 20)
                {
                    if (vare == 0)
                        scalefactor *= histmap_2016_elec_reco_highpt_sf    ->eval(eta, pt); // x=eta, y=pt
                    if (vare == 1)
                        scalefactor *= histmap_2016_elec_reco_highpt_sf    ->eval_up(eta, pt); // x=eta, y=pt
                    if (vare ==-1)
                        scalefactor *= histmap_2016_elec_reco_highpt_sf    ->eval_down(eta, pt); // x=eta, y=pt
                }
                else
                {
                    if (vare == 0)
                        scalefactor *= histmap_2016_elec_reco_lowpt_sf     ->eval(eta, pt); // x=eta, y=pt
                    if (vare == 1)
                        scalefactor *= histmap_2016_elec_reco_lowpt_sf     ->eval_up(eta, pt); // x=eta, y=pt
                    if (vare ==-1)
                        scalefactor *= histmap_2016_elec_reco_lowpt_sf     ->eval_down(eta, pt); // x=eta, y=pt
                }
                if (isNominal)
                {
                    if (vare == 0)
                        scalefactor *= histmap_2016_elec_medium_sf         ->eval(eta, pt); // x=eta, y=pt
                    if (vare == 1)
                        scalefactor *= histmap_2016_elec_medium_sf         ->eval_up(eta, pt); // x=eta, y=pt
                    if (vare ==-1)
                        scalefactor *= histmap_2016_elec_medium_sf         ->eval_down(eta, pt); // x=eta, y=pt
                }
                else
                {
                    if (vare == 0)
                        scalefactor *= histmap_2016_elec_veto_sf           ->eval(eta, pt); // x=eta, y=pt
                    if (vare == 1)
                        scalefactor *= histmap_2016_elec_veto_sf           ->eval_up(eta, pt); // x=eta, y=pt
                    if (vare ==-1)
                        scalefactor *= histmap_2016_elec_veto_sf           ->eval_down(eta, pt); // x=eta, y=pt
                }
            }
            else if (year == 2017)
            {
                if (pt > 20)
                {
                    if (vare == 0)
                        scalefactor *= histmap_2017_elec_reco_highpt_sf    ->eval(eta, pt); // x=eta, y=pt
                    if (vare == 1)
                        scalefactor *= histmap_2017_elec_reco_highpt_sf    ->eval_up(eta, pt); // x=eta, y=pt
                    if (vare ==-1)
                        scalefactor *= histmap_2017_elec_reco_highpt_sf    ->eval_down(eta, pt); // x=eta, y=pt
                }
                else
                {
                    if (vare == 0)
                        scalefactor *= histmap_2017_elec_reco_lowpt_sf     ->eval(eta, pt); // x=eta, y=pt
                    if (vare == 1)
                        scalefactor *= histmap_2017_elec_reco_lowpt_sf     ->eval_up(eta, pt); // x=eta, y=pt
                    if (vare ==-1)
                        scalefactor *= histmap_2017_elec_reco_lowpt_sf     ->eval_down(eta, pt); // x=eta, y=pt
                }
                if (isNominal)
                {
                    if (vare == 0)
                        scalefactor *= histmap_2017_elec_medium_sf         ->eval(eta, pt); // x=eta, y=pt
                    if (vare == 1)
                        scalefactor *= histmap_2017_elec_medium_sf         ->eval_up(eta, pt); // x=eta, y=pt
                    if (vare ==-1)
                        scalefactor *= histmap_2017_elec_medium_sf         ->eval_down(eta, pt); // x=eta, y=pt
                }
                else
                {
                    if (vare == 0)
                        scalefactor *= histmap_2017_elec_veto_sf           ->eval(eta, pt); // x=eta, y=pt
                    if (vare == 1)
                        scalefactor *= histmap_2017_elec_veto_sf           ->eval_up(eta, pt); // x=eta, y=pt
                    if (vare ==-1)
                        scalefactor *= histmap_2017_elec_veto_sf           ->eval_down(eta, pt); // x=eta, y=pt
                }
            }
            else if (year == 2018)
            {
                if (vare == 0)
                    scalefactor *= histmap_2018_elec_reco_sf           ->eval(eta, pt); // x=eta, y=pt
                if (vare == 1)
                    scalefactor *= histmap_2018_elec_reco_sf           ->eval_up(eta, pt); // x=eta, y=pt
                if (vare ==-1)
                    scalefactor *= histmap_2018_elec_reco_sf           ->eval_down(eta, pt); // x=eta, y=pt
                if (isNominal)
                {
                    if (vare == 0)
                        scalefactor *= histmap_2018_elec_medium_sf         ->eval(eta, pt); // x=eta, y=pt
                    if (vare == 1)
                        scalefactor *= histmap_2018_elec_medium_sf         ->eval_up(eta, pt); // x=eta, y=pt
                    if (vare ==-1)
                        scalefactor *= histmap_2018_elec_medium_sf         ->eval_down(eta, pt); // x=eta, y=pt
                }
                else
                {
                    if (vare == 0)
                        scalefactor *= histmap_2018_elec_veto_sf           ->eval(eta, pt); // x=eta, y=pt
                    if (vare == 1)
                        scalefactor *= histmap_2018_elec_veto_sf           ->eval_up(eta, pt); // x=eta, y=pt
                    if (vare ==-1)
                        scalefactor *= histmap_2018_elec_veto_sf           ->eval_down(eta, pt); // x=eta, y=pt
                }
            }
        }
        else if (absid == 13)
        {
            if (year == 2016)
            {
                if (pt > 20)
                {
                    if (varm == 0)
                        scalefactor *= 0.550 * histmap_2016_muon_BCDEF_id_sf       ->eval(eta, pt)  // x=eta, y=pt
                            +0.450 * histmap_2016_muon_GH_id_sf          ->eval(eta, pt); // x=eta, y=pt 0.450 of 2016 data
                    if (varm == 1)
                        scalefactor *= 0.550 * histmap_2016_muon_BCDEF_id_sf       ->eval_up(eta, pt)  // x=eta, y=pt
                            +0.450 * histmap_2016_muon_GH_id_sf          ->eval_up(eta, pt); // x=eta, y=pt 0.450 of 2016 data
                    if (varm ==-1)
                        scalefactor *= 0.550 * histmap_2016_muon_BCDEF_id_sf       ->eval_down(eta, pt)  // x=eta, y=pt
                            +0.450 * histmap_2016_muon_GH_id_sf          ->eval_down(eta, pt); // x=eta, y=pt 0.450 of 2016 data
                }
                else
                {
                    if (varm == 0)
                        scalefactor *= 0.550 * histmap_2016_muon_BCDEF_id_lowpt_sf ->eval(pt, abseta)  // x=pt, y=abseta
                            +0.450 * histmap_2016_muon_GH_id_lowpt_sf    ->eval(pt, abseta); // x=pt, y=abseta 0.450 of 2016 data
                    if (varm == 1)
                        scalefactor *= 0.550 * histmap_2016_muon_BCDEF_id_lowpt_sf ->eval_up(pt, abseta)  // x=pt, y=abseta
                            +0.450 * histmap_2016_muon_GH_id_lowpt_sf    ->eval_up(pt, abseta); // x=pt, y=abseta 0.450 of 2016 data
                    if (varm ==-1)
                        scalefactor *= 0.550 * histmap_2016_muon_BCDEF_id_lowpt_sf ->eval_down(pt, abseta)  // x=pt, y=abseta
                            +0.450 * histmap_2016_muon_GH_id_lowpt_sf    ->eval_down(pt, abseta); // x=pt, y=abseta 0.450 of 2016 data
                }
                if (isNominal)
                {
                    if (varm == 0)
                        scalefactor *= 0.550 * histmap_2016_muon_BCDEF_tightiso_sf ->eval(eta, std::max((double) pt, 20.1))  // x=eta, y=pt
                            +0.450 * histmap_2016_muon_GH_tightiso_sf    ->eval(eta, std::max((double) pt, 20.1)); // x=eta, y=pt 0.450 of 2016 data
                    if (varm == 1)
                        scalefactor *= 0.550 * histmap_2016_muon_BCDEF_tightiso_sf ->eval_up(eta, std::max((double) pt, 20.1))  // x=eta, y=pt
                            +0.450 * histmap_2016_muon_GH_tightiso_sf    ->eval_up(eta, std::max((double) pt, 20.1)); // x=eta, y=pt 0.450 of 2016 data
                    if (varm ==-1)
                        scalefactor *= 0.550 * histmap_2016_muon_BCDEF_tightiso_sf ->eval_down(eta, std::max((double) pt, 20.1))  // x=eta, y=pt
                            +0.450 * histmap_2016_muon_GH_tightiso_sf    ->eval_down(eta, std::max((double) pt, 20.1)); // x=eta, y=pt 0.450 of 2016 data
                }
                else
                {
                    if (varm == 0)
                        scalefactor *= 0.550 * histmap_2016_muon_BCDEF_looseiso_sf ->eval(eta, std::max((double) pt, 20.1))  // x=eta, y=pt
                            +0.450           * histmap_2016_muon_GH_looseiso_sf    ->eval(eta, std::max((double) pt, 20.1)); // x=eta, y=pt 0.450 of 2016 data
                    if (varm == 1)
                        scalefactor *= 0.550 * histmap_2016_muon_BCDEF_looseiso_sf ->eval_up(eta, std::max((double) pt, 20.1))  // x=eta, y=pt
                            +0.450           * histmap_2016_muon_GH_looseiso_sf    ->eval_up(eta, std::max((double) pt, 20.1)); // x=eta, y=pt 0.450 of 2016 data
                    if (varm ==-1)
                        scalefactor *= 0.550 * histmap_2016_muon_BCDEF_looseiso_sf ->eval_down(eta, std::max((double) pt, 20.1))  // x=eta, y=pt
                            +0.450           * histmap_2016_muon_GH_looseiso_sf    ->eval_down(eta, std::max((double) pt, 20.1)); // x=eta, y=pt 0.450 of 2016 data
                }
            }
            else if (year == 2017)
            {
                if (pt > 20)
                {
                    if (varm == 0)
                        scalefactor *= histmap_2017_muon_id_sf             ->eval(pt, abseta); // x=pt, y=abseta
                    if (varm == 1)
                        scalefactor *= histmap_2017_muon_id_sf             ->eval_up(pt, abseta); // x=pt, y=abseta
                    if (varm ==-1)
                        scalefactor *= histmap_2017_muon_id_sf             ->eval_down(pt, abseta); // x=pt, y=abseta
                }
                else
                {
                    if (varm == 0)
                        scalefactor *= histmap_2017_muon_id_lowpt_sf       ->eval(pt, abseta); // x=pt, y=abseta
                    if (varm == 1)
                        scalefactor *= histmap_2017_muon_id_lowpt_sf       ->eval_up(pt, abseta); // x=pt, y=abseta
                    if (varm ==-1)
                        scalefactor *= histmap_2017_muon_id_lowpt_sf       ->eval_down(pt, abseta); // x=pt, y=abseta
                }
                if (isNominal)
                {
                    if (varm == 0)
                        scalefactor *= histmap_2017_muon_tightiso_sf       ->eval(std::max((double) pt, 20.1), abseta); // x=pt, y=abseta
                    if (varm == 1)
                        scalefactor *= histmap_2017_muon_tightiso_sf       ->eval_up(std::max((double) pt, 20.1), abseta); // x=pt, y=abseta
                    if (varm ==-1)
                        scalefactor *= histmap_2017_muon_tightiso_sf       ->eval_down(std::max((double) pt, 20.1), abseta); // x=pt, y=abseta
                }
                else
                {
                    if (varm == 0)
                        scalefactor *= histmap_2017_muon_looseiso_sf       ->eval(std::max((double) pt, 20.1), abseta); // x=pt, y=abseta
                    if (varm == 1)
                        scalefactor *= histmap_2017_muon_looseiso_sf       ->eval_up(std::max((double) pt, 20.1), abseta); // x=pt, y=abseta
                    if (varm ==-1)
                        scalefactor *= histmap_2017_muon_looseiso_sf       ->eval_down(std::max((double) pt, 20.1), abseta); // x=pt, y=abseta
                }
            }
            else if (year == 2018)
            {
                if (pt > 20)
                {
                    if (varm == 0)
                        scalefactor *= histmap_2018_muon_id_sf             ->eval(pt, abseta); // x=pt, y=abseta
                    if (varm == 1)
                        scalefactor *= histmap_2018_muon_id_sf             ->eval_up(pt, abseta); // x=pt, y=abseta
                    if (varm ==-1)
                        scalefactor *= histmap_2018_muon_id_sf             ->eval_down(pt, abseta); // x=pt, y=abseta
                }
                else
                {
                    if (varm == 0)
                        scalefactor *= histmap_2018_muon_id_lowpt_sf       ->eval(pt, abseta); // x=pt, y=abseta
                    if (varm == 1)
                        scalefactor *= histmap_2018_muon_id_lowpt_sf       ->eval_up(pt, abseta); // x=pt, y=abseta
                    if (varm ==-1)
                        scalefactor *= histmap_2018_muon_id_lowpt_sf       ->eval_down(pt, abseta); // x=pt, y=abseta
                }
                if (isNominal)
                {
                    if (varm == 0)
                        scalefactor *= histmap_2018_muon_tightiso_sf       ->eval(std::max((double) pt, 15.1), abseta); // x=pt, y=abseta
                    if (varm == 1)
                        scalefactor *= histmap_2018_muon_tightiso_sf       ->eval_up(std::max((double) pt, 15.1), abseta); // x=pt, y=abseta
                    if (varm ==-1)
                        scalefactor *= histmap_2018_muon_tightiso_sf       ->eval_down(std::max((double) pt, 15.1), abseta); // x=pt, y=abseta
                }
                else
                {
                    if (varm == 0)
                        scalefactor *= histmap_2018_muon_looseiso_sf       ->eval(std::max((double) pt, 15.1), abseta); // x=pt, y=abseta
                    if (varm == 1)
                        scalefactor *= histmap_2018_muon_looseiso_sf       ->eval_up(std::max((double) pt, 15.1), abseta); // x=pt, y=abseta
                    if (varm ==-1)
                        scalefactor *= histmap_2018_muon_looseiso_sf       ->eval_down(std::max((double) pt, 15.1), abseta); // x=pt, y=abseta
                }
            }
        }
        return scalefactor;
    }

    //______________________________________________________________________________________________
    float LeptonScaleFactor()
    {
        if (input.is_data)
            return 1.;
        // Based on lep_Veto indices
        float scalefactor = 1;
        for (int ilep = 0; ilep < www.lep_pt().size(); ++ilep)
            scalefactor *= IndividualLeptonScaleFactor(ilep, false);
        return scalefactor;
    }

};

#ifndef __CINT__
extern ScaleFactorWVZ scalefactorwvz;
#endif

#endif
// eof
