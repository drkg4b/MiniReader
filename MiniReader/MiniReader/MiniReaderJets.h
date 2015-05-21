#ifndef MINIREADER_MINIREADERJETS_H
#define MINIREADER_MINIREADERJETS_H

// ROOT include(s):
#include <TTree.h>

// STL include(s):
#include <vector>
#include <algorithm>

class MiniReaderJets {

  friend class MiniReaderAlg;

 private:

  int m_jet_mult;

  std::vector<double> *m_jet_pt;
  std::vector<double> *m_jet_eta;
  std::vector<double> *m_jet_phi;
  std::vector<double> *m_jet_e;
  std::vector<double> *m_jet_jvf;
  std::vector<double> *m_jet_jvt;
  std::vector<double> *m_jet_emf;
  std::vector<double> *m_jet_chf;
  std::vector<double> *m_jet_fmax;
  std::vector<double> *m_jet_time;
  std::vector<double> *m_jet_flavour_weight;
  std::vector<double> *m_jet_constscale_eta;
  std::vector<double> *m_jet_Cpt;
  std::vector<double> *m_jet_Ceta;
  std::vector<double> *m_jet_Cphi;
  std::vector<double> *m_jet_Ce;

  // Needed to fill the tree for TMVA:
  double m_jet1_pt;
  int m_n_jet30;
  int m_n_jet40;
  int m_n_jet50;

  std::vector<int> *m_jet_passOR;
  std::vector<int> *m_jet_isbase;
  std::vector<int> *m_jet_isnotbad;
  std::vector<int> *m_jet_passFilter;

 public:

  MiniReaderJets();
  void ReadJetBranches(TTree *);
  void FillJetTreeVariables();
  void SkimJets();
};

#endif // MINIREADER_MINIREADERJETS_H
