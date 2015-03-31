// Local include(s):
#include "MiniReader/MiniReaderAlg.h"
#include "MiniReader/MiniReaderSelectionCuts.h"

// SDL include(s):
#include <math.h>

double MiniReaderAlg::deltaPhi(double phi1, double phi2)
{
  double dphi = std::fabs(phi1 - phi2);

  return (dphi > M_PI) ? (2 * M_PI - dphi) : dphi;
}

bool MiniReaderAlg::isDeltaPhiJetMetLessThanN(float dphi)
{
  std::vector<double>::const_iterator it = std::find_if(m_jet.m_jet_phi->cbegin(),
							m_jet.m_jet_phi->cend(),
  [&](double phi) {
    return deltaPhi(phi, m_met.m_EtMissMuVetoPhi) < dphi;
  });

  return (it != m_jet.m_jet_phi->cend()) ? true : false;
}

bool MiniReaderAlg::elPassOR()
{
  std::vector<int>::const_iterator it = std::find_if(m_el.m_ele_passOR->cbegin(),
						     m_el.m_ele_passOR->cend(),
  [](double passOR) {
    return passOR;
  });

  return (it != m_el.m_ele_passOR->cend()) ? true : false;
}

bool MiniReaderAlg::muPassOR()
{
  std::vector<int>::const_iterator it = std::find_if(m_mu.m_mu_passOR->cbegin(),
						     m_mu.m_mu_passOR->cend(),
  [](double passOR) {
    return passOR;
  });

  return (it != m_mu.m_mu_passOR->cend()) ? true : false;
}

double MiniReaderAlg::deltaR(double eta1, double phi1, double eta2, double phi2)
{
  double dp = deltaPhi(phi1, phi2);
  double de = eta1 - eta2;

  return std::sqrt(dp * dp + de * de);
}

double MiniReaderAlg::toGeV(double in_var)
{
  return in_var * .001;
}




void MiniReaderAlg::doCutFlow()
{
  if (m_jet.m_jet_isbad)

    m_n_bad_jets++;

  if (m_jet.m_jet_isbad &&
      m_met.m_EtMissMuVeto > 250000)

    m_met_cut++;

  if (m_jet.m_jet_isbad &&
      m_met.m_EtMissMuVeto > 250000 &&
      m_jet.m_jet_pt->size() != 0 &&
      m_jet.m_jet_pt->at(0) > 250000)

    m_jet1_pt++;

  if (m_jet.m_jet_isbad &&
      m_met.m_EtMissMuVeto > 250000 &&
      m_jet.m_jet_pt->size() != 0 &&
      m_jet.m_jet_pt->at(0) > 250000 &&
      (m_el.m_ele_mult == 0 ||
      !elPassOR()))

    m_ele_mult_cut++;

  if (m_jet.m_jet_isbad &&
      m_met.m_EtMissMuVeto > 250000 &&
      m_jet.m_jet_pt->size() != 0 &&
      m_jet.m_jet_pt->at(0) > 250000 &&
      (m_el.m_ele_mult == 0 ||
      !elPassOR()) &&
      (m_mu.m_mu_mult == 0 ||
       !muPassOR()))

    m_mu_mult_cut++;

  if (m_jet.m_jet_isbad &&
      m_met.m_EtMissMuVeto > 250000 &&
      m_jet.m_jet_pt->size() != 0 &&
      m_jet.m_jet_pt->at(0) > 250000 &&
      (m_el.m_ele_mult == 0 ||
      !elPassOR()) &&
      (m_mu.m_mu_mult == 0 ||
       !muPassOR()) &&
      m_jet.m_jet_pt->size() < 4)


    m_n_jet_cut++;

  if (m_jet.m_jet_isbad &&
      m_met.m_EtMissMuVeto > 250000 &&
      m_jet.m_jet_pt->size() != 0 &&
      m_jet.m_jet_pt->at(0) > 250000 &&
      (m_el.m_ele_mult == 0 ||
      !elPassOR()) &&
      (m_mu.m_mu_mult == 0 ||
       !muPassOR()) &&
      (m_jet.m_jet_pt->size() < 4 ||
       m_jet.m_jet_pt->at(3) < 30000) &&
      !isDeltaPhiJetMetLessThanN(.4))

    m_dphi_jetmet_cut++;

  if (m_jet.m_jet_isbad &&
      m_met.m_EtMissMuVeto > 250000 &&
      m_jet.m_jet_pt->size() != 0 &&
      m_jet.m_jet_pt->at(0) > 250000 &&
      (m_el.m_ele_mult == 0 ||
      !elPassOR()) &&
      (m_mu.m_mu_mult == 0 ||
       !muPassOR()) &&
      m_jet.m_jet_mult < 4 &&
      !isDeltaPhiJetMetLessThanN(.4) &&
      m_met.m_EtMissMuVeto > 400000)

    m_met_hard_cut++;

  if (m_jet.m_jet_isbad &&
      m_met.m_EtMissMuVeto > 250000 &&
      m_jet.m_jet_pt->size() != 0 &&
      m_jet.m_jet_pt->at(0) > 250000 &&
      (m_el.m_ele_mult == 0 ||
      !elPassOR()) &&
      (m_mu.m_mu_mult == 0 ||
       !muPassOR()) &&
      m_jet.m_jet_mult < 4 &&
      !isDeltaPhiJetMetLessThanN(.4) &&
      m_met.m_EtMissMuVeto > 400000 &&
      m_jet.m_jet_pt->at(0) > 400000)

    m_jet1_pt_hard_cut++;
}
