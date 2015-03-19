// Local include(s):
#include "MiniReader/MiniReaderAlg.h"
#include "MiniReader/MiniReaderSelectionCuts.h"

// SDL include(s):
#include <algorithm>

bool MiniReaderAlg::passEventSelection()
{
  using namespace EventFilter;

  std::vector<double>::const_iterator it = std::find_if(m_jet.m_jet_phi->cbegin(),
							m_jet.m_jet_phi->cend(),
  [&](double phi) {
     return deltaPhi(phi, m_met.m_EtMissMuVetoPhi) < DPHI_JETMET &&
            m_jet.m_jet_mult > N_JETS;
  });

  return (it != m_jet.m_jet_phi->cend()) ? true : false;
}
