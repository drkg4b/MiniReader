#ifndef MiniReader_MiniReaderAlg_H
#define MiniReader_MiniReaderAlg_H

// Infrastructure include(s):
#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"
#include <EventLoop/Algorithm.h>
#include <EventLoop/Worker.h>

// ROOT include(s):
#include <TTree.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TBranch.h>
#include <TChain.h>
#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TCanvas.h>
#include <TProfile.h>

// Local inclede(s):
#include "MiniReader/MiniReaderElectrons.h"
#include "MiniReader/MiniReaderMuons.h"
#include "MiniReader/MiniReaderJets.h"
#include "MiniReader/MiniReaderMissingET.h"
#include "MiniReader/MiniReaderEventInfo.h"
#include "MiniReader/MiniReaderCrossSection.h"
#include "MiniReader/MiniReaderPrimaryVertex.h"
#include "MiniReader/MiniReaderTruthParticles.h"

// STL include(s):
#include <algorithm>
#include <string>

#define PR(x) std::cout << #x << " = " << x << std::endl

class MiniReaderAlg : public EL::Algorithm {
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
 public:
  // float cutValue;



  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
 public:
  // Tree *myTree; //!
  // TH1 *myHist; //!

  // Submission dir:
  std:: string m_submitDir;

  // To read the branches:
  MiniReaderElectrons m_el; //!
  MiniReaderMuons m_mu; //!
  MiniReaderJets m_jet; //!
  MiniReaderMissingET m_met; //!
  MiniReaderEventInfo m_info; //!
  MiniReaderCrossSection m_cross; //!
  MiniReaderPrimaryVertex m_pvtx; //!
  MiniReaderTruthParticles m_truth; //!

  int m_eventCounter; //!

  std::string m_current_sample_name; //!

  // Luminosity:
  double m_lumi;

  // The histogram container:
  std::vector<TH1F *> m_HistoContainer; //!
  std::vector<TH2F *> m_ScatterPlotContainer; //!

  // To fill the histograms:
  void DefineHisto(int, int, float, float); //!
  void DefineScatterPlot(int, int, double, double, int, double, double); //!
  void InitHisto(); //!

  void FillMET(double); //!
  template <typename T>
    void fillNjetPt(int, int, int, double, T); //!
  template <typename T>
    void fillNjetPtJVF(std::vector<float>, int, int, int, double, T); //!
  void DivideHisto(int, int, int); //!
  void FillJets(double); //!
  void FillEventInfo(double); //!
  void FillScatterPlots(double weight); //!

  // Auxiliary functions:
  double deltaPhi(double, double); //!
  double deltaR(double, double, double, double); //!
  bool isDeltaPhiJetMetLessThanN(float); //!
  bool elPassOR(); //!
  bool muPassOR(); //!
  double toGeV(double); //!
  void doCutFlow(); //!

  // SR definitions:
  bool isZnunuBaseLine(); //!
  bool isM0(); //!
  bool isM5(); //!
  bool isM9(); //!

  // Event definition:
  bool passEventSelection(); //!

  // Plot functions:
  void PlotJetEfficency(); //!

  // FIX FOR THE COMPRESSED SPECTRA:
  float m_process_xs13; //!
  float m_process_eff13; //!

  float m_event_weight; //!

  // Sensitivity study TMVA tree:
  TTree *m_SensitivityTree;
  void DefineTreeBranches();

  // Cut Flow variables:
  int m_n_bad_jets; //!
  int m_met_cut; //!
  int m_jet1_pt; //!
  int m_ele_mult_cut; //!
  int m_mu_mult_cut; //!
  int m_n_jet_cut; //!
  int m_dphi_jetmet_cut; //!
  int m_met_hard_cut; //!
  int m_jet1_pt_hard_cut; //!

  // this is a standard constructor
  MiniReaderAlg();

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob(EL::Job &job);
  virtual EL::StatusCode fileExecute();
  virtual EL::StatusCode histInitialize();
  virtual EL::StatusCode changeInput(bool firstFile);
  virtual EL::StatusCode initialize();
  virtual EL::StatusCode execute();
  virtual EL::StatusCode postExecute();
  virtual EL::StatusCode finalize();
  virtual EL::StatusCode histFinalize();

  // this is needed to distribute the algorithm to the workers
  ClassDef(MiniReaderAlg, 1);
};

#endif
