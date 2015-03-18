#ifndef MINIREADER_MINIREADERMUONS_H
#define MINIREADER_MINIREADERMUONS_H

// ROOT include(s):
#include <TTree.h>

// STL include(s):
#include <vector>

class MiniReaderMuons {

  friend class MiniReaderAlg;

 private:

  int m_mu_mult;

  std::vector<double> *m_mu_pt;
  std::vector<double> *m_mu_eta;
  std::vector<double> *m_mu_phi;
  std::vector<double> *m_mu_e;
  std::vector<double> *m_mu_charge;
  std::vector<double> *m_mu_ptcone20;
  std::vector<double> *m_mu_ptcone30;
  std::vector<double> *m_mu_ptcone40;
  std::vector<double> *m_mu_d0;
  std::vector<double> *m_mu_z0;

  std::vector<int> *m_mu_isCombinedMuon;
  std::vector<int> *m_mu_isStandAloneMuon;
  std::vector<int> *m_mu_isSegmentTaggedMuon;
  std::vector<int> *m_mu_type;
  std::vector<int> *m_mu_quality;
  std::vector<int> *m_mu_isloose;
  std::vector<int> *m_mu_ismedium;
  std::vector<int> *m_mu_istight;
  std::vector<int> *m_mu_passOR;
  std::vector<int> *m_mu_isbase;
  std::vector<int> *m_mu_issignal;
  std::vector<int> *m_mu_passFilter;

 public:

  MiniReaderMuons();
  void ReadMuonBranches(TTree *);
};

#endif // MINIREADER_MINIREADERMUONS_H
