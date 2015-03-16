#include "MiniReader/MiniReaderJets.h"
#include <iostream>

MiniReaderJets::MiniReaderJets()
{
  m_jet_mult = 0;
  m_jet_pt = 0;
  m_jet_eta = 0;
  m_jet_phi = 0;
  m_jet_e = 0;
  m_jet_jvf = 0;
  m_jet_emf = 0;
  m_jet_chf = 0;
  m_jet_fmax = 0;
  m_jet_time = 0;
  m_jet_flavour_weight = 0;
  m_jet_constscale_eta = 0;
  m_jet_Cpt = 0;
  m_jet_Ceta = 0;
  m_jet_Cphi = 0;
  m_jet_Ce = 0;

  m_jet_passOR = 0;
  m_jet_isbase = 0;
  m_jet_isbad = 0;
  m_jet_passFilter = 0;

  b_jet_mult = 0;
  b_jet_pt = 0;
  b_jet_eta = 0;
  b_jet_phi = 0;
  b_jet_e = 0;
  b_jet_jvf = 0;
  b_jet_emf = 0;
  b_jet_chf = 0;
  b_jet_fmax = 0;
  b_jet_time = 0;
  b_jet_flavour_weight = 0;
  b_jet_constscale_eta = 0;
  b_jet_Cpt = 0;
  b_jet_Ceta = 0;
  b_jet_Cphi = 0;
  b_jet_Ce = 0;
  b_jet_passOR = 0;
  b_jet_isbase = 0;
  b_jet_isbad = 0;
  b_jet_passFilter = 0;
}

void MiniReaderJets::ReadBranches(TTree *tree)
{
  tree->SetBranchAddress("jet_mult", &m_jet_mult, &b_jet_mult);
  tree->SetBranchAddress("jet_pt", &m_jet_eta, &b_jet_pt);
  tree->SetBranchAddress("jet_eta", &m_jet_phi, &b_jet_eta);
  tree->SetBranchAddress("jet_phi", &m_jet_phi, &b_jet_phi);
  tree->SetBranchAddress("jet_e", &m_jet_e, &b_jet_e);
  tree->SetBranchAddress("jet_jvf", &m_jet_jvf, &b_jet_jvf);
  tree->SetBranchAddress("jet_emf", &m_jet_emf, &b_jet_emf);
  tree->SetBranchAddress("jet_chf", &m_jet_chf, &b_jet_chf);
  tree->SetBranchAddress("jet_fmax", &m_jet_fmax, &b_jet_fmax);
  tree->SetBranchAddress("jet_time", &m_jet_time, &b_jet_time);
  tree->SetBranchAddress("jet_flavour_weight", &m_jet_flavour_weight, &b_jet_flavour_weight);
  tree->SetBranchAddress("jet_constscale_eta", &m_jet_constscale_eta, &b_jet_constscale_eta);
  tree->SetBranchAddress("jet_Cpt", &m_jet_Cpt, &b_jet_Cpt);
  tree->SetBranchAddress("jet_Ceta", &m_jet_Ceta, &b_jet_Ceta);
  tree->SetBranchAddress("jet_Cphi", &m_jet_Cphi, &b_jet_Cphi);
  tree->SetBranchAddress("jet_Ce", &m_jet_Ce, &b_jet_Ce);
  tree->SetBranchAddress("jet_passOR", &m_jet_passOR, &b_jet_passOR);
  tree->SetBranchAddress("jet_isbase", &m_jet_isbase, &b_jet_isbase);
  tree->SetBranchAddress("jet_isbad", &m_jet_isbad, &b_jet_isbad);
  tree->SetBranchAddress("jet_passFilter", &m_jet_passFilter, &b_jet_passFilter);
}
