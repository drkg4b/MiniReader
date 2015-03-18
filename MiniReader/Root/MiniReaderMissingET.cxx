#include "MiniReader/MiniReaderMissingET.h"

MiniReaderMissingET::MiniReaderMissingET()
{
  m_EtMiss = 0;
  m_EtMissPhi = 0;
  m_WEtMiss = 0;
  m_WEtMissPhi = 0;
  m_ZEtMiss = 0;
  m_ZEtMissPhi = 0;
  m_EtMissMuVeto = 0;
  m_EtMissMuVetoPhi = 0;
}

void MiniReaderMissingET::ReadMissingETBranches(TTree *tree)
{
  tree->SetBranchAddress("m_EtMiss", &m_EtMiss);
  tree->SetBranchAddress("m_EtMissPhi", &m_EtMissPhi);
  tree->SetBranchAddress("m_WEtMiss", &m_WEtMiss);
  tree->SetBranchAddress("m_WEtMissPhi", &m_WEtMissPhi);
  tree->SetBranchAddress("m_ZEtMiss", &m_ZEtMiss);
  tree->SetBranchAddress("m_ZEtMissPhi", &m_ZEtMissPhi);
  tree->SetBranchAddress("m_EtMissMuVeto", &m_EtMissMuVeto);
  tree->SetBranchAddress("m_EtMissMuVetoPhi", &m_EtMissMuVetoPhi);
}
