#ifndef MINIREADER_MINIREADERJETS_H
#define MINIREADER_MINIREADERJETS_H

// Local Incluede(s):
#include "MiniReader/HistoBaseClass.h"
#include "MiniReader/MiniReaderPrimaryVertex.h"
#include "MiniReader/MiniReaderEventInfo.h"

// ROOT include(s):
#include <TTree.h>

// STL include(s):
#include <vector>
#include <tuple>
#include <iostream>
#include <algorithm>

#define PR(x) std::cout << #x << " = " << x << std::endl

using PassToJets = std::tuple < const MiniReaderPrimaryVertex &, const
                   MiniReaderEventInfo & >;

class MiniReaderJets : public HistoBaseClass {

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
  void InitJetHisto();
  void FillJetHisto(const std::string &, const std::string &, const double,
                    const PassToJets &);

private:

  template <typename T>
  void fillNjetPt(const std::string &, int, int, double, T);

  template <typename T>
    void fillNjetPtJVT(const std::string &, int, int, double, double, T);
};

template <typename T>
void MiniReaderJets::fillNjetPt(const std::string &name, int n_jet, int
                                pt_tresh, double weight, T fill_var)
{
  if (m_jet_mult <= n_jet || (m_jet_mult > n_jet && m_jet_pt->at(n_jet) < pt_tresh))

    m_HistoContainerMap[name]->Fill(fill_var, weight);
}

template <typename T>
void MiniReaderJets::fillNjetPtJVT(const std::string &name, int n_jet, int
                                   pt_tresh, double jvt_tresh, double weight,
				   T fill_var)
{
  // Count the number of jets with JVT above threshold:
  int n_jet_jvt = 0;

  for(int i = 0; i < m_jet_mult; ++i) {

    if(std::fabs(m_jet_jvt->at(i)) > jvt_tresh)

      n_jet_jvt++;
  }

  // Now check if these jets pass the other requirements:
  if (n_jet_jvt <= n_jet || (n_jet_jvt > n_jet && m_jet_pt->at(n_jet) < pt_tresh))

    m_HistoContainerMap[name]->Fill(fill_var, weight);
}

#endif // MINIREADER_MINIREADERJETS_H
