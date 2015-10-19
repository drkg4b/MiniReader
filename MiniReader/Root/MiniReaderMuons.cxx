#include "MiniReader/MiniReaderMuons.h"

MiniReaderMuons::MiniReaderMuons()
{
  m_mu_mult = 0;

  m_mu_pt = 0;
  m_mu_eta = 0;
  m_mu_phi = 0;
  m_mu_e = 0;
  m_mu_charge = 0;
  m_mu_ptcone20 = 0;
  m_mu_ptcone30 = 0;
  m_mu_d0 = 0;
  m_mu_z0 = 0;

  m_mu_isCombinedMuon = 0;
  m_mu_isStandAloneMuon = 0;
  m_mu_isSegmentTaggedMuon = 0;
  m_mu_type = 0;
  m_mu_quality = 0;
  m_mu_isloose = 0;
  m_mu_ismedium = 0;
  m_mu_istight = 0;
  m_mu_passOR = 0;
  m_mu_isbase = 0;
  m_mu_issignal = 0;
  m_mu_passFilter = 0;
}

void MiniReaderMuons::ReadMuonBranches(TTree *tree)
{
  tree->SetBranchAddress("mu_mult", &m_mu_mult);
  tree->SetBranchAddress("mu_pt", &m_mu_pt);
  tree->SetBranchAddress("mu_eta", &m_mu_eta);
  tree->SetBranchAddress("mu_phi", &m_mu_phi);
  tree->SetBranchAddress("mu_e", &m_mu_e);
  tree->SetBranchAddress("mu_charge", &m_mu_charge);
  tree->SetBranchAddress("mu_ptcone20", &m_mu_ptcone20);
  tree->SetBranchAddress("mu_ptcone30", &m_mu_ptcone30);
  tree->SetBranchAddress("mu_d0", &m_mu_d0);
  tree->SetBranchAddress("mu_z0", &m_mu_z0);
  tree->SetBranchAddress("mu_isCombinedMuon", &m_mu_isCombinedMuon);
  tree->SetBranchAddress("mu_isStandAloneMuon", &m_mu_isStandAloneMuon);
  tree->SetBranchAddress("mu_isSegmentTaggedMuon", &m_mu_isSegmentTaggedMuon);
  tree->SetBranchAddress("mu_type", &m_mu_type);
  tree->SetBranchAddress("mu_quality", &m_mu_quality);
  tree->SetBranchAddress("mu_isloose", &m_mu_isloose);
  tree->SetBranchAddress("mu_ismedium", &m_mu_ismedium);
  tree->SetBranchAddress("mu_istight", &m_mu_istight);
  tree->SetBranchAddress("mu_passOR", &m_mu_passOR);
  tree->SetBranchAddress("mu_isbase", &m_mu_isbase);
  tree->SetBranchAddress("mu_issignal", &m_mu_issignal);
  tree->SetBranchAddress("mu_passFilter", &m_mu_passFilter);
}
