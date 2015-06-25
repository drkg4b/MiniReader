#include "MiniReader/MiniReaderPrimaryVertex.h"

MiniReaderPrimaryVertex::MiniReaderPrimaryVertex()
{
  m_pvtx_n = 0;

  m_pvtx_ntracks = 0;
  m_pvtx_z = 0;
}

void MiniReaderPrimaryVertex::ReadPrimaryVertexBranches(TTree *tree)
{
  tree->SetBranchAddress("pvtx_n", &m_pvtx_n);
  tree->SetBranchAddress("pvtx_ntracks", &m_pvtx_ntracks);
  tree->SetBranchAddress("pvtx_z", &m_pvtx_z);
}
