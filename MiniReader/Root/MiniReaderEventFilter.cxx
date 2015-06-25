// Local include(s):
#include "MiniReader/MiniReaderAlg.h"
#include "MiniReader/MiniReaderSelectionCuts.h"

bool MiniReaderAlg::passEventSelection()
{
  using namespace EventFilter;

  return m_jet.m_jet_mult != 0 &&
    //m_jet.m_jet_isnotbad &&
         m_pvtx.m_pvtx_n > N_PVTX &&
         m_jet.m_jet_pt->at(0) > JET_PT &&
         m_met.m_EtMissMuVeto > MET_CUT &&
         m_jet.m_jet_mult < N_JETS &&
	 !isDeltaPhiJetMetLessThanN(DPHI_JETMET) &&
         std::fabs(m_jet.m_jet_eta->at(0)) < JET_ETA;
}
