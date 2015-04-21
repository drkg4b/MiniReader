#include "MiniReader/MiniReaderAlg.h"

void MiniReaderAlg::DefineTreeBranches()
{
  wk()->addOutput(m_SensitivityTree);

  // MET:
  m_SensitivityTree->Branch("EtMissMuVeto", &m_met.m_EtMissMuVeto);

  // Jet:
  m_SensitivityTree->Branch("jet_mult", &m_jet.m_jet_mult);
  m_SensitivityTree->Branch("jet_pt", &m_jet.m_jet_pt);

  m_SensitivityTree->Print();
}
