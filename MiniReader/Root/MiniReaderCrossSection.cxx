#include "MiniReader/MiniReaderCrossSection.h"

MiniReaderCrossSection::MiniReaderCrossSection()
{
  m_process_xs8 = 0;
  m_process_kfactor8 = 0;
  m_process_eff8 = 0;
  m_process_xsrelunc8 = 0;
  m_process_name8 = 0;
  m_process_xs13 = 0;
  m_process_kfactor13 = 0;
  m_process_eff13 = 0;
  m_process_xsrelunc13 = 0;
  m_process_name13 = 0;
}

void MiniReaderCrossSection::ReadCrossSectionBranches(TTree *tree)
{
  tree->SetBranchAddress("process_xs8", &m_process_xs8);
  tree->SetBranchAddress("process_kfactor8", &m_process_kfactor8);
  tree->SetBranchAddress("process_eff8", &m_process_eff8);
  tree->SetBranchAddress("process_xsrelunc8", &m_process_xsrelunc8);
  tree->SetBranchAddress("process_name8", &m_process_name8);
  tree->SetBranchAddress("process_xs13", &m_process_xs13);
  tree->SetBranchAddress("process_kfactor13", &m_process_kfactor13);
  tree->SetBranchAddress("process_eff13", &m_process_eff13);
  tree->SetBranchAddress("process_xsrelunc13", &m_process_xsrelunc13);
  tree->SetBranchAddress("process_name13", &m_process_name13);
}
