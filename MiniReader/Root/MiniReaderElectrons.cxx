#include "MiniReader/MiniReaderElectrons.h"

MiniReaderElectrons::MiniReaderElectrons()
{
  m_ele_mult = 0;

  m_ele_pt = 0;
  m_ele_eta = 0;
  m_ele_phi = 0;
  m_ele_e = 0;
  m_ele_cl_eta = 0;
  m_ele_cl_phi = 0;
  m_ele_charge = 0;
  m_ele_d0 = 0;
  m_ele_z0 = 0;
  m_ele_ptcone20 = 0;
  m_ele_ptcone30 = 0;

  m_ele_ismedium = 0;
  m_ele_istight = 0;
  m_ele_passOR = 0;
  m_ele_isbase = 0;
  m_ele_issignal = 0;
  m_ele_passFilter = 0;
}

void MiniReaderElectrons::ReadElectronBranches(TTree *tree)
{
  tree->SetBranchAddress("ele_mult", &m_ele_mult);
  tree->SetBranchAddress("ele_pt", &m_ele_pt);
  tree->SetBranchAddress("ele_eta", &m_ele_eta);
  tree->SetBranchAddress("ele_phi", &m_ele_phi);
  tree->SetBranchAddress("ele_e", &m_ele_e);
  tree->SetBranchAddress("ele_cl_eta", &m_ele_cl_eta);
  tree->SetBranchAddress("ele_cl_phi", &m_ele_cl_phi);
  tree->SetBranchAddress("ele_charge", &m_ele_charge);
  tree->SetBranchAddress("ele_d0", &m_ele_d0);
  tree->SetBranchAddress("ele_z0", &m_ele_z0);
  tree->SetBranchAddress("ele_ptcone20", &m_ele_ptcone20);
  tree->SetBranchAddress("ele_ptcone30", &m_ele_ptcone30);
  tree->SetBranchAddress("ele_ismedium", &m_ele_ismedium);
  tree->SetBranchAddress("ele_istight", &m_ele_istight);
  tree->SetBranchAddress("ele_passOR", &m_ele_passOR);
  tree->SetBranchAddress("ele_isbase", &m_ele_isbase);
  tree->SetBranchAddress("ele_issignal", &m_ele_issignal);
  tree->SetBranchAddress("ele_passFilter", &m_ele_passFilter);
}
