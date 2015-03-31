// Local include(s):
#include "MiniReader/MiniReaderAlg.h"
#include "MiniReader/MiniReaderSelectionCuts.h"

bool MiniReaderAlg::passEventSelection()
{
  using namespace EventFilter;

  std::vector<double>::const_iterator it = std::find_if(m_jet.m_jet_phi->cbegin(),
							m_jet.m_jet_phi->cend(),
  [&](double phi) {
     return deltaPhi(phi, m_met.m_EtMissMuVetoPhi) < DPHI_JETMET &&
            m_jet.m_jet_isbad &&
            m_pvtx.m_pvtx_n > N_PVTX &&
            m_met.m_EtMissMuVeto > MET_CUT &&
            m_jet.m_jet_pt->size() != 0 &&
            m_jet.m_jet_pt->at(0) > JET_PT &&
            std::fabs(m_jet.m_jet_eta->at(0)) < JET_ETA &&
            m_jet.m_jet_mult > N_JETS;
  });

  return (it != m_jet.m_jet_phi->cend()) ? true : false;
}
