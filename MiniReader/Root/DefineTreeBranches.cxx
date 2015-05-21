#include "MiniReader/MiniReaderAlg.h"

void MiniReaderAlg::DefineTreeBranches()
{
  wk()->addOutput(m_SensitivityTree);

  // MET:
  m_SensitivityTree->Branch("EtMissMuVeto", &m_met.m_EtMissMuVeto);

  // Jet:
  m_SensitivityTree->Branch("jet1_pt", &m_jet.m_jet1_pt);
  m_SensitivityTree->Branch("n_jet30", &m_jet.m_n_jet30);
  m_SensitivityTree->Branch("n_jet40", &m_jet.m_n_jet40);
  m_SensitivityTree->Branch("n_jet50", &m_jet.m_n_jet50);

  // Event info:
  m_SensitivityTree->Branch("event_weight", &m_event_weight);

  m_SensitivityTree->Print();
}
