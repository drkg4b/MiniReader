#include "MiniReader/MiniReaderPrimaryVertex.h"

MiniReaderPrimaryVertex::MiniReaderPrimaryVertex()
{
  m_pvtx_n = 0;

  m_pvtx_ntracks = 0;
  m_pvtx_x = 0;
  m_pvtx_y = 0;
  m_pvtx_z = 0;
  m_pvtx_ndof = 0;
  m_pvtx_chi2 = 0;
}

void MiniReaderPrimaryVertex::ReadPrimaryVertexBranches(TTree *tree)
{
  tree->SetBranchAddress("pvtx_n", &m_pvtx_n);
  tree->SetBranchAddress("pvtx_ntracks", &m_pvtx_ntracks);
  tree->SetBranchAddress("pvtx_x", &m_pvtx_x);
  tree->SetBranchAddress("pvtx_y", &m_pvtx_y);
  tree->SetBranchAddress("pvtx_z", &m_pvtx_z);
  tree->SetBranchAddress("pvtx_ndof", &m_pvtx_ndof);
  tree->SetBranchAddress("pvtx_chi2", &m_pvtx_chi2);
}
