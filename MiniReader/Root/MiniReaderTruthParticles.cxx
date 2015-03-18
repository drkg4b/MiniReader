#include "MiniReader/MiniReaderTruthParticles.h"

MiniReaderTruthParticles::MiniReaderTruthParticles()
{
  m_true_zpt = 0;
  m_true_zm = 0;
  m_true_wpt = 0;
  m_pass_zpt = 0;
  m_pass_wpt = 0;
  m_pdf_pdgid1 = 0;
  m_pdf_pdgid2 = 0;
  m_pdf_x1 = 0;
  m_pdf_x2 = 0;
  m_pdf_pdfid1 = 0;
  m_pdf_pdfid2 = 0;
  m_pdf_scale = 0;
}

void MiniReaderTruthParticles::ReadTruthParticlesBranches(TTree *tree)
{
  tree->SetBranchAddress("true_zpt", &m_true_zpt);
  tree->SetBranchAddress("true_zm", &m_true_zm);
  tree->SetBranchAddress("true_wpt", &m_true_wpt);
  tree->SetBranchAddress("pass_zpt", &m_pass_zpt);
  tree->SetBranchAddress("pass_wpt", &m_pass_wpt);
  tree->SetBranchAddress("pdf_pdgid1", &m_pdf_pdgid1);
  tree->SetBranchAddress("pdf_pdgid2", &m_pdf_pdgid2);
  tree->SetBranchAddress("pdf_x1", &m_pdf_x1);
  tree->SetBranchAddress("pdf_x2", &m_pdf_x2);
  tree->SetBranchAddress("pdf_pdfid1", &m_pdf_pdfid1);
  tree->SetBranchAddress("pdf_pdfid2", &m_pdf_pdfid2);
  tree->SetBranchAddress("pdf_scale", &m_pdf_scale);
}
