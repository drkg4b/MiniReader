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
				   m_lumi(5000), m_sample_name("no_sample"),
				   m_sample_weight(0), m_n_bad_jets(0),
				   m_met_cut(0), m_jet1_pt(0),
				   m_ele_mult_cut(0), m_mu_mult_cut(0),
				   m_n_jet_cut(0), m_dphi_jetmet_cut(0),
				   m_met_hard_cut(0), m_jet1_pt_hard_cut(0)
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().

  // Reserve space for the histo for efficency:
  m_HistoContainer.reserve(200);
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

  m_sample_weight = 0;
  PR(m_sample_weight);

  TFile *file = wk()->inputFile();

  TH1F *h1 = (TH1F*)(file->Get("h_TrackNeventsWgt"));

  m_sample_weight = h1->GetBinContent(1);

  PR(m_sample_name);
  PR(m_sample_weight);

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

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode MiniReaderAlg :: execute()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  m_eventCounter++;

  wk()->tree()->GetEntry(wk()->treeEntry());

  if(!m_truth.m_pass_zpt) return EL::StatusCode::SUCCESS;

  m_jet.SkimJets();

  double event_weight = 1.;

  // doCutFlow();

  if(m_sample_weight != 0)

    event_weight = m_cross.m_process_xs13 *
                   m_cross.m_process_kfactor13 *
                   m_cross.m_process_eff13 *
                   m_lumi /  m_sample_weight;

  if(isZnunuBaseLine()) {

    if(isM0()) {

      // Fill Histos:
      FillMET(event_weight);
      FillEventInfo(event_weight);
      FillJets(event_weight);
    }
  }

  if (!passEventSelection()) return EL::StatusCode::SUCCESS;

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

  PR(m_n_bad_jets);
  PR(m_met_cut);
  PR(m_jet1_pt);
  PR(m_ele_mult_cut);
  PR(m_mu_mult_cut);
  PR(m_n_jet_cut);
  PR(m_dphi_jetmet_cut);
  PR(m_met_hard_cut);
  PR(m_jet1_pt_hard_cut);

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
