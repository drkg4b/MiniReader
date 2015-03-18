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
  tree->SetBranchAddress("EtMiss", &m_EtMiss);
  tree->SetBranchAddress("EtMissPhi", &m_EtMissPhi);
  tree->SetBranchAddress("WEtMiss", &m_WEtMiss);
  tree->SetBranchAddress("WEtMissPhi", &m_WEtMissPhi);
  tree->SetBranchAddress("ZEtMiss", &m_ZEtMiss);
  tree->SetBranchAddress("ZEtMissPhi", &m_ZEtMissPhi);
  tree->SetBranchAddress("EtMissMuVeto", &m_EtMissMuVeto);
  tree->SetBranchAddress("EtMissMuVetoPhi", &m_EtMissMuVetoPhi);
}
