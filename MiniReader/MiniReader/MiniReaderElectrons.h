#ifndef MINIREADER_MINIREADERELECTRONS_H
#define MINIREADER_MINIREADERELECTRONS_H

// ROOT include(s):
#include <TTree.h>

// STL include(s):
#include <vector>

class MiniReaderElectrons {

  friend class MiniReaderAlg;

 private:

  int m_ele_mult;

  std::vector<double> *m_ele_pt;
  std::vector<double> *m_ele_eta;
  std::vector<double> *m_ele_phi;
  std::vector<double> *m_ele_e;
  std::vector<double> *m_ele_cl_eta;
  std::vector<double> *m_ele_cl_phi;
  std::vector<double> *m_ele_charge;
  std::vector<double> *m_ele_d0;
  std::vector<double> *m_ele_z0;
  std::vector<double> *m_ele_topoetcone_corr30;
  std::vector<double> *m_ele_topoetcone_corr40;
  std::vector<double> *m_ele_ptcone20;
  std::vector<double> *m_ele_ptcone30;
  std::vector<double> *m_ele_ptcone40;

  std::vector<int> *m_ele_ismedium;
  std::vector<int> *m_ele_istight;
  std::vector<int> *m_ele_passOR;
  std::vector<int> *m_ele_isbase;
  std::vector<int> *m_ele_issignal;
  std::vector<int> *m_ele_passFilter;

 public:

  MiniReaderElectrons();
  void ReadElectronBranches(TTree *);
};

#endif // MINIREADER_MINIREADERELECTRONS_H
