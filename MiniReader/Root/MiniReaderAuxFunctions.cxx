// Local include(s):
#include "MiniReader/MiniReaderAlg.h"
#include "MiniReader/MiniReaderSelectionCuts.h"

// SDL include(s):
#include <math.h>

// Function to calculate delta phi between two particles:
double MiniReaderAlg::deltaPhi(double phi1, double phi2)
{
  double dphi = std::fabs(phi1 - phi2);

  return (dphi > M_PI) ? (2 * M_PI - dphi) : dphi;
}

// Function to check if the delta phi between the MET and any jet is less than
// some value:
bool MiniReaderAlg::isDeltaPhiJetMetLessThanN(float dphi)
{
  std::vector<double>::const_iterator it = std::find_if(m_jet.m_jet_phi->cbegin(),
							m_jet.m_jet_phi->cend(),
  [&](double phi) {
    return deltaPhi(phi, m_met.m_EtMissMuVetoPhi) < dphi;
  });

  return (it != m_jet.m_jet_phi->cend()) ? true : false;
}

// Function to check if the electrons passed the overlap removal:
bool MiniReaderAlg::elPassOR()
{
  std::vector<int>::const_iterator it = std::find_if(m_el.m_ele_passOR->cbegin(),
						     m_el.m_ele_passOR->cend(),
  [](double passOR) {
    return passOR;
  });

  return (it != m_el.m_ele_passOR->cend()) ? true : false;
}

// Function to check if the muons passed the overlap removal:
bool MiniReaderAlg::muPassOR()
{
  std::vector<int>::const_iterator it = std::find_if(m_mu.m_mu_passOR->cbegin(),
						     m_mu.m_mu_passOR->cend(),
  [](double passOR) {
    return passOR;
  });

  return (it != m_mu.m_mu_passOR->cend()) ? true : false;
}

// Function to calculate the delta R between two particles:
double MiniReaderAlg::deltaR(double eta1, double phi1, double eta2, double phi2)
{
  double dp = deltaPhi(phi1, phi2);
  double de = eta1 - eta2;

  return std::sqrt(dp * dp + de * de);
}

// Function to convert quantities to GeV from MeV:
double MiniReaderAlg::toGeV(double in_var)
{
  return in_var * .001;
}


// Function to perform the cut flow:
void MiniReaderAlg::doCutFlow()
{
  if (m_jet.m_jet_isnotbad)

    m_n_bad_jets++;

  if (/*m_jet.m_jet_isnotbad &&*/
      m_jet.m_jet_pt->size() != 0 &&
      m_jet.m_jet_pt->at(0) > 250000)

    m_jet1_pt++;

  if (/*m_jet.m_jet_isnotbad &&*/
      m_jet.m_jet_pt->size() != 0 &&
      m_jet.m_jet_pt->at(0) > 250000 &&
      m_met.m_EtMissMuVeto > 250000)

    m_met_cut++;

  if (/*m_jet.m_jet_isnotbad &&*/
      m_met.m_EtMissMuVeto > 250000 &&
      m_jet.m_jet_pt->size() != 0 &&
      m_jet.m_jet_pt->at(0) > 250000 &&
      (m_el.m_ele_mult == 0 ||
      !elPassOR()))

    m_ele_mult_cut++;

  if (m_jet.m_jet_isnotbad &&
      m_met.m_EtMissMuVeto > 250000 &&
      m_jet.m_jet_pt->size() != 0 &&
      m_jet.m_jet_pt->at(0) > 250000 &&
      (m_el.m_ele_mult == 0 ||
      !elPassOR()) &&
      (m_mu.m_mu_mult == 0 ||
       !muPassOR()))

    m_mu_mult_cut++;

  if (m_jet.m_jet_isnotbad &&
      m_met.m_EtMissMuVeto > 250000 &&
      m_jet.m_jet_pt->size() != 0 &&
      m_jet.m_jet_pt->at(0) > 250000 &&
      (m_el.m_ele_mult == 0 ||
      !elPassOR()) &&
      (m_mu.m_mu_mult == 0 ||
       !muPassOR()) &&
      m_jet.m_jet_pt->size() < 5)


    m_n_jet_cut++;

  if (m_jet.m_jet_isnotbad &&
      m_met.m_EtMissMuVeto > 250000 &&
      m_jet.m_jet_pt->size() != 0 &&
      m_jet.m_jet_pt->at(0) > 250000 &&
      (m_el.m_ele_mult == 0 ||
      !elPassOR()) &&
      (m_mu.m_mu_mult == 0 ||
       !muPassOR()) &&
      (m_jet.m_jet_pt->size() < 5 ||
       m_jet.m_jet_pt->at(3) < 30000) &&
      !isDeltaPhiJetMetLessThanN(.4))

    m_dphi_jetmet_cut++;

  if (m_jet.m_jet_isnotbad &&
      m_met.m_EtMissMuVeto > 250000 &&
      m_jet.m_jet_pt->size() != 0 &&
      m_jet.m_jet_pt->at(0) > 250000 &&
      (m_el.m_ele_mult == 0 ||
      !elPassOR()) &&
      (m_mu.m_mu_mult == 0 ||
       !muPassOR()) &&
      m_jet.m_jet_mult < 5 &&
      !isDeltaPhiJetMetLessThanN(.4) &&
      m_met.m_EtMissMuVeto > 400000)

    m_met_hard_cut++;

  if (m_jet.m_jet_isnotbad &&
      m_met.m_EtMissMuVeto > 250000 &&
      m_jet.m_jet_pt->size() != 0 &&
      m_jet.m_jet_pt->at(0) > 250000 &&
      (m_el.m_ele_mult == 0 ||
      !elPassOR()) &&
      (m_mu.m_mu_mult == 0 ||
       !muPassOR()) &&
      m_jet.m_jet_mult < 5 &&
      !isDeltaPhiJetMetLessThanN(.4) &&
      m_met.m_EtMissMuVeto > 400000 &&
      m_jet.m_jet_pt->at(0) > 400000)

    m_jet1_pt_hard_cut++;
}
