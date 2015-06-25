// Local include(s):
#include "MiniReader/MiniReaderJets.h"
#include "MiniReader/MiniReaderSelectionCuts.h"

MiniReaderJets::MiniReaderJets()
{
  m_jet_mult = 0;
  m_jet_pt = 0;
  m_jet_eta = 0;
  m_jet_phi = 0;
  m_jet_e = 0;
  m_jet_jvf = 0;
  m_jet_jvt = 0;
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
  m_jet_isnotbad = 0;
  m_jet_passFilter = 0;
}

void MiniReaderJets::ReadJetBranches(TTree *tree)
{
  tree->SetBranchAddress("jet_mult", &m_jet_mult);
  tree->SetBranchAddress("jet_pt", &m_jet_pt);
  tree->SetBranchAddress("jet_eta", &m_jet_eta);
  tree->SetBranchAddress("jet_phi", &m_jet_phi);
  tree->SetBranchAddress("jet_e", &m_jet_e);
  tree->SetBranchAddress("jet_jvf", &m_jet_jvf);
  // tree->SetBranchAddress("jet_jvt", &m_jet_jvt);
  tree->SetBranchAddress("jet_emf", &m_jet_emf);
  tree->SetBranchAddress("jet_chf", &m_jet_chf);
  tree->SetBranchAddress("jet_fmax", &m_jet_fmax);
  tree->SetBranchAddress("jet_time", &m_jet_time);
  tree->SetBranchAddress("jet_flavour_weight", &m_jet_flavour_weight);
  tree->SetBranchAddress("jet_constscale_eta", &m_jet_constscale_eta);
  tree->SetBranchAddress("jet_Cpt", &m_jet_Cpt);
  tree->SetBranchAddress("jet_Ceta", &m_jet_Ceta);
  tree->SetBranchAddress("jet_Cphi", &m_jet_Cphi);
  tree->SetBranchAddress("jet_Ce", &m_jet_Ce);
  tree->SetBranchAddress("jet_passOR", &m_jet_passOR);
  tree->SetBranchAddress("jet_isbase", &m_jet_isbase);

  try {

    tree->SetBranchAddress("jet_isnotbad", &m_jet_isnotbad);
    throw 20;

  } catch (int e)
    {
      tree->SetBranchAddress("jet_isbad", &m_jet_isnotbad);
    }

  tree->SetBranchAddress("jet_passFilter", &m_jet_passFilter);
}

void MiniReaderJets::SkimJets()
{
  using namespace GoodJetCuts;

  std::vector<double> jet_pt;
  std::vector<double> jet_eta;
  std::vector<double> jet_phi;
  std::vector<double> jet_jvf;
  // std::vector<double> jet_jvt;
  std::vector<double> jet_flavour_weight;
  std::vector<double> jet_constscale_eta;

  for(int i = 0; i < m_jet_mult; ++i) {

    if(m_jet_passOR->at(i) && m_jet_passFilter->at(i) && m_jet_pt->at(i) > PT_CUT) {
    // if(m_jet_passOR->at(i) && m_jet_passFilter->at(i) && m_jet_pt->at(i) >
    //    PT_CUT && std::fabs(m_jet_eta->at(i)) < 2.4 /*&& m_jet_jvf->at(i) > .5*/) {

      jet_pt.push_back(m_jet_pt->at(i));
      jet_eta.push_back(m_jet_eta->at(i));
      jet_phi.push_back(m_jet_phi->at(i));
      jet_jvf.push_back(m_jet_jvf->at(i));
      // jet_jvt.push_back(m_jet_jvt->at(i));
      jet_flavour_weight.push_back(m_jet_flavour_weight->at(i));
      jet_constscale_eta.push_back(m_jet_constscale_eta->at(i));
    }
  }

  m_jet_mult = jet_pt.size();
  *m_jet_pt = jet_pt;
  *m_jet_eta = jet_eta;
  *m_jet_phi = jet_phi;
  *m_jet_jvf = jet_jvf;
  // *m_jet_jvt = jet_jvt;
  *m_jet_flavour_weight = jet_flavour_weight;
  *m_jet_constscale_eta = jet_constscale_eta;

  std::sort(m_jet_pt->begin(), m_jet_pt->end(), std::greater<double>());
}

void MiniReaderJets::FillJetTreeVariables()
{
  m_jet1_pt = m_jet_pt->at(0);

  m_n_jet30 = 0;
  m_n_jet40 = 0;
  m_n_jet50 = 0;

  for(int i = 0; i < m_jet_mult; ++i) {

    if(m_jet_pt->at(i) > 30000)

      m_n_jet30++;

    if(m_jet_pt->at(i) > 40000)

      m_n_jet40++;

    if(m_jet_pt->at(i) > 50000)

      m_n_jet50++;
  }
}
