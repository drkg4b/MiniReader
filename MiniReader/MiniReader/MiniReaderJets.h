#ifndef MINIREADER_MINIREADERJETS_H
#define MINIREADER_MINIREADERJETS_H

// ROOT include(s):
#include <TBranch.h>
#include <TTree.h>

// STL include(s):
#include <vector>

class MiniReaderJets {

  friend class MiniReaderAlg;

 private:

  int *m_jet_mult;

  std::vector<double> *m_jet_pt;
  std::vector<double> *m_jet_eta;
  std::vector<double> *m_jet_phi;
  std::vector<double> *m_jet_e;
  std::vector<double> *m_jet_jvf;
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

  std::vector<int> *m_jet_passOR;
  std::vector<int> *m_jet_isbase;
  std::vector<int> *m_jet_isbad;
  std::vector<int> *m_jet_passFilter;

 public:

  MiniReaderJets();
  void ReadJetBranches(TTree *);
};

#endif // MINIREADER_MINIREADERJETS_H
