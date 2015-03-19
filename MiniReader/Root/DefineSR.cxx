// Local include(s):
#include "MiniReader/MiniReaderAlg.h"
#include "MiniReader/MiniReaderSelectionCuts.h"

bool MiniReaderAlg::isM0()
{
  using namespace M0Cuts;

  return (m_el.m_ele_mult == 0 &&
	  m_mu.m_mu_mult == 0 &&
	  m_jet.m_jet_pt->at(0) > JET_PT &&
	  m_met.m_EtMissMuVeto > MET_CUT);
}

bool MiniReaderAlg::isM5()
{
  using namespace M5Cuts;

  return (m_el.m_ele_mult == 0 &&
	  m_mu.m_mu_mult == 0 &&
	  m_jet.m_jet_pt->at(0) > JET_PT &&
	  m_met.m_EtMissMuVeto > MET_CUT);
}

bool MiniReaderAlg::isM9()
{
  using namespace M9Cuts;

  return (m_el.m_ele_mult == 0 &&
	  m_mu.m_mu_mult == 0 &&
	  m_jet.m_jet_pt->at(0) > JET_PT &&
	  m_met.m_EtMissMuVeto > MET_CUT);
}
