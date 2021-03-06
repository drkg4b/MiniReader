// EDM includes:
#include "xAODEventInfo/EventInfo.h"
#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include "SampleHandler/ToolsDiscovery.h"
#include "SampleHandler/Sample.h"

// This class header:
#include <MiniReader/MiniReaderAlg.h>

// Local inclede(s):
#include "MiniReader/MiniReaderJets.h"

MiniReaderAlg :: MiniReaderAlg() : m_submitDir("submitDir"), m_eventCounter(0),
				   m_current_sample_name("no_sample"),
				   m_lumi(2000), m_n_bad_jets(0), m_met_cut(0),
				   m_jet1_pt(0), m_ele_mult_cut(0),
				   m_mu_mult_cut(0), m_n_jet_cut(0),
				   m_dphi_jetmet_cut(0), m_met_hard_cut(0),
				   m_jet1_pt_hard_cut(0)
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().

  m_event_weight = 1.;

  // Reserve space for the histo for efficency:
  m_HistoContainer.reserve(200);
  m_ScatterPlotContainer.reserve(200);

  m_SensitivityTree = new TTree("SensTree", "SensTree");
}



EL::StatusCode MiniReaderAlg :: setupJob(EL::Job &job)
{
  // Here you put code that sets up the job on the submission object
  // so that it is ready to work with your algorithm, e.g. you can
  // request the D3PDReader service or add output files.  Any code you
  // put here could instead also go into the submission script.  The
  // sole advantage of putting it here is that it gets automatically
  // activated/deactivated when you add/remove the algorithm from your
  // job, which may or may not be of value to you.

  xAOD::Init("MiniReader").ignore(); // call before opening first file

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MiniReaderAlg :: histInitialize()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.

  // Initialize all the histograms:
  InitHisto();

  m_jet.InitJetHisto();

  for(const auto &histo_itr : m_jet.GetHistoMap())

    wk()->addOutput(histo_itr.second);

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MiniReaderAlg :: fileExecute()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MiniReaderAlg :: changeInput(bool firstFile)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.
  TTree *tree = wk()->tree();

  m_jet.ReadJetBranches(tree);
  m_el.ReadElectronBranches(tree);
  m_mu.ReadMuonBranches(tree);
  m_met.ReadMissingETBranches(tree);
  m_info.ReadEventInfoBranches(tree);
  m_cross.ReadCrossSectionBranches(tree);
  m_pvtx.ReadPrimaryVertexBranches(tree);
  m_truth.ReadTruthParticlesBranches(tree);

  // OLD WAY TO GET THE SUM OF WEIGHTS:
  // TFile *file = wk()->inputFile();

  // TH1F *h1 = (TH1F *)(file->Get("h_TrackNeventsWgt"));

  // int bin_all = h1->GetXaxis()->FindBin("All");

  // m_sample_weight = h1->GetBinContent(bin_all);

  // std::string file_name = file->GetName();

  // FIX FOR COMPRESSED SPECTRA MISSING NUMBERS:
  // if(file_name.find("371858") != std::string::npos) {

  //   m_process_xs13 = 6.8773;
  //   m_process_eff13 = .39627;
  // }

  // if(file_name.find("371865") != std::string::npos) {

  //   m_process_xs13 = 6.8773;
  //   m_process_eff13 = 0.39627;
  // }

  // if(file_name.find("5088310") != std::string::npos) {

  //   m_process_xs13 = 0.42481E+01;
  //   m_process_eff13 = .5585;
  // }

  // if(file_name.find("5088315") != std::string::npos) {

  //   m_process_xs13 = 0.19164E+01;
  //   m_process_eff13 = .4639;
  // }

  // if(file_name.find("5088318") != std::string::npos) {

  //   m_process_xs13 = 0.60441E+00;
  //   m_process_eff13 = .4877;
  // }

  // if(file_name.find("5088323") != std::string::npos) {

  //   m_process_xs13 = 0.19826E+01;
  //   m_process_eff13 = .5486;
  // }

  // if(file_name.find("5088327") != std::string::npos) {

  //   m_process_xs13 = 0.94110E+00;
  //   m_process_eff13 = .4331;
  // }

  // if(file_name.find("5088330") != std::string::npos) {

  //   m_process_xs13 = 0.31134E+00;
  //   m_process_eff13 = .4763;
  // }

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MiniReaderAlg :: initialize()
{
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.

  m_current_sample_name = wk()->metaData()->castString("sample_name");

  DefineTreeBranches();

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MiniReaderAlg :: execute()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  wk()->tree()->GetEntry(wk()->treeEntry());

  // if (!m_truth.m_pass_zpt) return EL::StatusCode::SUCCESS;

  m_jet.SkimJets();

  if (!passEventSelection()) return EL::StatusCode::SUCCESS;

  double event_weight = 1.;
  m_event_weight = 1.;

  if (wk()->metaData()->castString("sample_name") == "cutFlowSamples")

    doCutFlow();


  if(m_info.m_sum_of_weights != 0)

    event_weight = m_cross.m_process_xs13 *
                   m_cross.m_process_kfactor13 *
                   m_cross.m_process_eff13 *
                   m_info.m_mc_event_weight *
                   m_lumi /  m_info.m_sum_of_weights;

  // PR(m_current_sample_name);
  // PR(event_weight);
  // PR(m_info.m_sum_of_weights);
  // PR(m_cross.m_process_xs13);
  // PR(m_cross.m_process_kfactor13);
  // PR(m_cross.m_process_eff13);
  // PR(m_info.m_mc_event_weight);

  // WARNING FIX FOR AN ERROR IN THE CROSS SECTION IN THE INPUT TREE
  // if(m_current_sample_name == "D5")

  //   event_weight *= 1000;


  // FIX FOR THE KFACTOR NOT IN THE ROOT FILE:
  // if(m_current_sample_name == "Compressed_450_435" ||
  //    m_current_sample_name == "Compressed_450_425") {

  //   float process_kfactor13 = 1.7;

  //   event_weight = m_process_xs13 *
  //                  m_process_eff13 *
  //                  process_kfactor13 *
  //                  m_info.m_mc_event_weight *
  //                  m_lumi / m_info.m_sum_of_weughts;

    // event_weight = m_cross.m_process_xs13 *
    //                m_cross.m_process_eff13 *
    //                process_kfactor13 *
    //                m_info.m_global_event_weight *
    //                m_lumi / m_info.m_sum_of_weights;
  // }

  // WARNING Quick FIX TO BE CHANGED!!!!!!!!!!!!!!
  // if(m_current_sample_name == "ttbarJVTSamples")

  //   event_weight = 1.;

  // Making a tuple to pass to the fill functions:
  PassToJets MiniObjects = std::make_tuple(std::cref(m_pvtx),
					   std::cref(m_info));

  std::string region;
  std::string suffix;

  if (isZnunuBaseLine()) {

    region = "SR_";

    if (isM0()) {

      suffix = "_M0";

      // Fill Histos:
      FillMET(event_weight);
      FillEventInfo(event_weight);
      FillJets(event_weight);
      FillScatterPlots(event_weight);

      m_jet.FillJetHisto(region, suffix, event_weight, MiniObjects);

      // Fill sensitivity study tree:
      m_event_weight = event_weight;

      m_jet.FillJetTreeVariables();
      m_SensitivityTree->Fill();
    }
  }

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MiniReaderAlg :: postExecute()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MiniReaderAlg :: finalize()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events.

  PR(m_eventCounter);
  PR(m_n_bad_jets);
  PR(m_jet1_pt);
  PR(m_met_cut);
  PR(m_ele_mult_cut);
  PR(m_mu_mult_cut);
  PR(m_n_jet_cut);
  PR(m_dphi_jetmet_cut);
  PR(m_met_hard_cut);
  PR(m_jet1_pt_hard_cut);

  TProfile *prof = m_ScatterPlotContainer[0]->ProfileX();
  TProfile *prof1 = m_ScatterPlotContainer[1]->ProfileX();

  wk()->addOutput(prof);
  wk()->addOutput(prof1);

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MiniReaderAlg :: histFinalize()
{
  // This method is the mirror image of histInitialize(), meaning it
  // gets called after the last event has been processed on the worker
  // node and allows you to finish up any objects you created in
  // histInitialize() before they are written to disk.  This is
  // actually fairly rare, since this happens separately for each
  // worker node.  Most of the time you want to do your
  // post-processing on the submission node after all your histogram
  // outputs have been merged.  This is different from finalize() in
  // that it gets called on all worker nodes regardless of whether
  // they processed input events.

  PlotJetEfficency();

  return EL::StatusCode::SUCCESS;
}
