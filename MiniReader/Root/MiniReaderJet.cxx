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
  tree->SetBranchAddress("jet_jvt", &m_jet_jvt);
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
  tree->SetBranchAddress("jet_isnotbad", &m_jet_isnotbad);
  tree->SetBranchAddress("jet_passFilter", &m_jet_passFilter);
}

////////////////////////////////////////////////////////////////////////////////
//// Select good jets
////////////////////////////////////////////////////////////////////////////////
void MiniReaderJets::SkimJets()
{
  using namespace GoodJetCuts;

  std::vector<double> jet_pt;
  std::vector<double> jet_eta;
  std::vector<double> jet_phi;
  std::vector<double> jet_jvf;
  std::vector<double> jet_jvt;
  std::vector<double> jet_flavour_weight;
  std::vector<double> jet_constscale_eta;

  for (int i = 0; i < m_jet_mult; ++i) {

    bool isPileup = m_jet_pt->at(i) < 50E3 &&
                    std::fabs(m_jet_eta->at(i) < 2.4) /*&&
                                                        std::fabs(m_jet_jvt->at(i)) > JVT_CUT*/;

    if (m_jet_passOR->at(i) && m_jet_passFilter->at(i) && m_jet_pt->at(i) >
        PT_CUT && !isPileup) {
      // if(m_jet_passOR->at(i) && m_jet_passFilter->at(i) && m_jet_pt->at(i) >
      //    PT_CUT && std::fabs(m_jet_eta->at(i)) < 2.4 /*&& m_jet_jvf->at(i) > .5*/) {

      jet_pt.push_back(m_jet_pt->at(i));
      jet_eta.push_back(m_jet_eta->at(i));
      jet_phi.push_back(m_jet_phi->at(i));
      jet_jvf.push_back(m_jet_jvf->at(i));
      jet_jvt.push_back(m_jet_jvt->at(i));
      jet_flavour_weight.push_back(m_jet_flavour_weight->at(i));
      jet_constscale_eta.push_back(m_jet_constscale_eta->at(i));
    }
  }

  m_jet_mult = jet_pt.size();
  *m_jet_pt = jet_pt;
  *m_jet_eta = jet_eta;
  *m_jet_phi = jet_phi;
  *m_jet_jvf = jet_jvf;
  *m_jet_jvt = jet_jvt;
  *m_jet_flavour_weight = jet_flavour_weight;
  *m_jet_constscale_eta = jet_constscale_eta;

  std::sort(m_jet_pt->begin(), m_jet_pt->end(), std::greater<double>());
}

////////////////////////////////////////////////////////////////////////////////
//// Fill variables for the TTree for TMVA analysis
////////////////////////////////////////////////////////////////////////////////
void MiniReaderJets::FillJetTreeVariables()
{
  m_jet1_pt = m_jet_pt->at(0);

  m_n_jet30 = 0;
  m_n_jet40 = 0;
  m_n_jet50 = 0;

  for (int i = 0; i < m_jet_mult; ++i) {

    if (m_jet_pt->at(i) > 30000)

      m_n_jet30++;

    if (m_jet_pt->at(i) > 40000)

      m_n_jet40++;

    if (m_jet_pt->at(i) > 50000)

      m_n_jet50++;
  }
}

////////////////////////////////////////////////////////////////////////////////
//// Initialize the histograms for the jet class
////////////////////////////////////////////////////////////////////////////////
void MiniReaderJets::InitJetHisto()
{
  DefineHisto("jet1_pt", 100, 0, 1100E3);
  DefineHisto("n_jets", 10, 0, 10);

  DefineHisto("n_pvtx_noCut", 8, 0, 40);

  std::vector<std::string> plot_pref = {"n_pvtx_", "mu_"};
  std::vector<std::string> njets = {"3jets_", "4jets_", "5jets_"};
  std::vector<std::string> jetpt = {"jetpt30", "jetpt40", "jetpt50", "jetpt70"};
  std::vector<std::string> jvt_val = {"", "_jvt14", "_jvt64", "_jvt92"};

  for (size_t i = 0; i < plot_pref.size(); ++i) {
    for (size_t j = 0; j < njets.size(); ++j) {
      for (size_t k = 0; k < jetpt.size(); ++k) {
        for (size_t n = 0; n < jvt_val.size(); ++n) {

          std::string histo_name = plot_pref[i] + njets[j] + jetpt[k] +
                                   jvt_val[n];

          DefineHisto(histo_name, 8, 0, 40);
        }
      }
    }
  }

  // DefineHisto("n_pvtx_3jets_jetpt30", 8, 0, 40);
  // DefineHisto("n_pvtx_3jets_jetpt40", 8, 0, 40);
  // DefineHisto("n_pvtx_3jets_jetpt50", 8, 0, 40);
  // DefineHisto("n_pvtx_3jets_jetpt70", 8, 0, 40);

  // DefineHisto("mu_3jets_jetpt30", 8, 0, 40);
  // DefineHisto("mu_3jets_jetpt40", 8, 0, 40);
  // DefineHisto("mu_3jets_jetpt50", 8, 0, 40);
  // DefineHisto("mu_3jets_jetpt70", 8, 0, 40);

  // DefineHisto("n_pvtx_4jets_jetpt30", 8, 0, 40);
  // DefineHisto("n_pvtx_4jets_jetpt40", 8, 0, 40);
  // DefineHisto("n_pvtx_4jets_jetpt50", 8, 0, 40);
  // DefineHisto("n_pvtx_4jets_jetpt70", 8, 0, 40);

  // DefineHisto("mu_4jets_jetpt30", 8, 0, 40);
  // DefineHisto("mu_4jets_jetpt40", 8, 0, 40);
  // DefineHisto("mu_4jets_jetpt50", 8, 0, 40);
  // DefineHisto("mu_4jets_jetpt70", 8, 0, 40);

  // DefineHisto("n_pvtx_5jets_jetpt30", 8, 0, 40);
  // DefineHisto("n_pvtx_5jets_jetpt40", 8, 0, 40);
  // DefineHisto("n_pvtx_5jets_jetpt50", 8, 0, 40);
  // DefineHisto("n_pvtx_5jets_jetpt70", 8, 0, 40);

  // DefineHisto("mu_5jets_jetpt30", 8, 0, 40);
  // DefineHisto("mu_5jets_jetpt40", 8, 0, 40);
  // DefineHisto("mu_5jets_jetpt50", 8, 0, 40);
  // DefineHisto("mu_5jets_jetpt70", 8, 0, 40);

  // // Histo for JVT studies:
  // DefineHisto("n_pvtx_3jets_jetpt30_jvt14", 8, 0, 40);
  // DefineHisto("n_pvtx_3jets_jetpt40_jvt14", 8, 0, 40);
  // DefineHisto("n_pvtx_3jets_jetpt50_jvt14", 8, 0, 40);
  // DefineHisto("n_pvtx_3jets_jetpt70_jvt14", 8, 0, 40);

  // DefineHisto("n_pvtx_3jets_jetpt30_jvt64", 8, 0, 40);
  // DefineHisto("n_pvtx_3jets_jetpt40_jvt64", 8, 0, 40);
  // DefineHisto("n_pvtx_3jets_jetpt50_jvt64", 8, 0, 40);
  // DefineHisto("n_pvtx_3jets_jetpt70_jvt64", 8, 0, 40);

  // DefineHisto("n_pvtx_3jets_jetpt30_jvt92", 8, 0, 40);
  // DefineHisto("n_pvtx_3jets_jetpt40_jvt92", 8, 0, 40);
  // DefineHisto("n_pvtx_3jets_jetpt50_jvt92", 8, 0, 40);
  // DefineHisto("n_pvtx_3jets_jetpt70_jvt92", 8, 0, 40);

  // DefineHisto("mu_3jets_jetpt30_jvt14", 8, 0, 40);
  // DefineHisto("mu_3jets_jetpt40_jvt14", 8, 0, 40);
  // DefineHisto("mu_3jets_jetpt50_jvt14", 8, 0, 40);
  // DefineHisto("mu_3jets_jetpt70_jvt14", 8, 0, 40);

  // DefineHisto("mu_3jets_jetpt30_jvt64", 8, 0, 40);
  // DefineHisto("mu_3jets_jetpt40_jvt64", 8, 0, 40);
  // DefineHisto("mu_3jets_jetpt50_jvt64", 8, 0, 40);
  // DefineHisto("mu_3jets_jetpt70_jvt64", 8, 0, 40);

  // DefineHisto("mu_3jets_jetpt30_jvt92", 8, 0, 40);
  // DefineHisto("mu_3jets_jetpt40_jvt92", 8, 0, 40);
  // DefineHisto("mu_3jets_jetpt50_jvt92", 8, 0, 40);
  // DefineHisto("mu_3jets_jetpt70_jvt92", 8, 0, 40);

  // DefineHisto("n_pvtx_4jets_jetpt30_jvt14", 8, 0, 40);
  // DefineHisto("n_pvtx_4jets_jetpt40_jvt14", 8, 0, 40);
  // DefineHisto("n_pvtx_4jets_jetpt50_jvt14", 8, 0, 40);
  // DefineHisto("n_pvtx_4jets_jetpt70_jvt14", 8, 0, 40);

  // DefineHisto("n_pvtx_4jets_jetpt30_jvt64", 8, 0, 40);
  // DefineHisto("n_pvtx_4jets_jetpt40_jvt64", 8, 0, 40);
  // DefineHisto("n_pvtx_4jets_jetpt50_jvt64", 8, 0, 40);
  // DefineHisto("n_pvtx_4jets_jetpt70_jvt64", 8, 0, 40);

  // DefineHisto("n_pvtx_4jets_jetpt30_jvt92", 8, 0, 40);
  // DefineHisto("n_pvtx_4jets_jetpt40_jvt92", 8, 0, 40);
  // DefineHisto("n_pvtx_4jets_jetpt50_jvt92", 8, 0, 40);
  // DefineHisto("n_pvtx_4jets_jetpt70_jvt92", 8, 0, 40);

  // DefineHisto("mu_4jets_jetpt30_jvt14", 8, 0, 40);
  // DefineHisto("mu_4jets_jetpt40_jvt14", 8, 0, 40);
  // DefineHisto("mu_4jets_jetpt50_jvt14", 8, 0, 40);
  // DefineHisto("mu_4jets_jetpt70_jvt14", 8, 0, 40);

  // DefineHisto("mu_4jets_jetpt30_jvt64", 8, 0, 40);
  // DefineHisto("mu_4jets_jetpt40_jvt64", 8, 0, 40);
  // DefineHisto("mu_4jets_jetpt50_jvt64", 8, 0, 40);
  // DefineHisto("mu_4jets_jetpt70_jvt64", 8, 0, 40);

  // DefineHisto("mu_4jets_jetpt30_jvt92", 8, 0, 40);
  // DefineHisto("mu_4jets_jetpt40_jvt92", 8, 0, 40);
  // DefineHisto("mu_4jets_jetpt50_jvt92", 8, 0, 40);
  // DefineHisto("mu_4jets_jetpt70_jvt92", 8, 0, 40);

  // DefineHisto("n_pvtx_5jets_jetpt30_jvt14", 8, 0, 40);
  // DefineHisto("n_pvtx_5jets_jetpt40_jvt14", 8, 0, 40);
  // DefineHisto("n_pvtx_5jets_jetpt50_jvt14", 8, 0, 40);
  // DefineHisto("n_pvtx_5jets_jetpt70_jvt14", 8, 0, 40);

  // DefineHisto("n_pvtx_5jets_jetpt30_jvt64", 8, 0, 40);
  // DefineHisto("n_pvtx_5jets_jetpt40_jvt64", 8, 0, 40);
  // DefineHisto("n_pvtx_5jets_jetpt50_jvt64", 8, 0, 40);
  // DefineHisto("n_pvtx_5jets_jetpt70_jvt64", 8, 0, 40);

  // DefineHisto("n_pvtx_5jets_jetpt30_jvt92", 8, 0, 40);
  // DefineHisto("n_pvtx_5jets_jetpt40_jvt92", 8, 0, 40);
  // DefineHisto("n_pvtx_5jets_jetpt50_jvt92", 8, 0, 40);
  // DefineHisto("n_pvtx_5jets_jetpt70_jvt92", 8, 0, 40);

  // DefineHisto("mu_5jets_jetpt30_jvt14", 8, 0, 40);
  // DefineHisto("mu_5jets_jetpt40_jvt14", 8, 0, 40);
  // DefineHisto("mu_5jets_jetpt50_jvt14", 8, 0, 40);
  // DefineHisto("mu_5jets_jetpt70_jvt14", 8, 0, 40);

  // DefineHisto("mu_5jets_jetpt30_jvt64", 8, 0, 40);
  // DefineHisto("mu_5jets_jetpt40_jvt64", 8, 0, 40);
  // DefineHisto("mu_5jets_jetpt50_jvt64", 8, 0, 40);
  // DefineHisto("mu_5jets_jetpt70_jvt64", 8, 0, 40);

  // DefineHisto("mu_5jets_jetpt30_jvt92", 8, 0, 40);
  // DefineHisto("mu_5jets_jetpt40_jvt92", 8, 0, 40);
  // DefineHisto("mu_5jets_jetpt50_jvt92", 8, 0, 40);
  // DefineHisto("mu_5jets_jetpt70_jvt92", 8, 0, 40);
}

////////////////////////////////////////////////////////////////////////////////
//// Fill jet class histograms
////////////////////////////////////////////////////////////////////////////////
void MiniReaderJets::FillJetHisto(const std::string &reg, const std::string &suf,
                                  const double weight, const PassToJets &obj_tuple)
{
  int n_pvtx = std::get<0>(obj_tuple).GetPvtxN();
  float avgIntPerCross = std::get<1>(obj_tuple).GetAvgIntPerCross();

  m_HistoContainerMap[reg + "jet1_pt" + suf]->Fill(m_jet1_pt, weight);
  m_HistoContainerMap[reg + "n_jets" + suf]->Fill(m_jet_mult, weight);
  m_HistoContainerMap[reg + "n_pvtx_noCut" + suf]->Fill(n_pvtx, weight);

  // Event survives if at most 3 jets or if there are more than 3 jets but the
  // pt of the fourth is less than some threshold (Mind the vector counting start
  // from 0):
  std::vector<std::string> plot_pref = {"n_pvtx_", "mu_"};
  std::vector<int> jetpt = {30, 40, 50, 70};
  std::vector<std::string> jvt_val = {"", "_jvt14", "_jvt64", "_jvt92"};
  std::vector<double> jvt_tresh = {999, .14, .64, .92}; // the first value is dummy

  avgIntPerCross = std::round(avgIntPerCross) + .5;

  for (size_t i = 0; i < plot_pref.size(); ++i) {
    for (int j = 3; j < 6; ++j) {
      for (size_t k = 0; k < jetpt.size(); ++k) {
        for (size_t n = 0; n < jvt_val.size(); ++n) {

          std::string histo_name = reg + plot_pref[i] + std::to_string(j) +
                                   "jets_jetpt" + std::to_string(jetpt[k]) + jvt_val[n] + suf;


          if(n == 0) {
            if (i == 0)

              fillNjetPt(histo_name, j, jetpt[k] * 1E3, weight, n_pvtx);

            else

              fillNjetPt(histo_name, j, jetpt[k] * 1E3, weight, avgIntPerCross);
          }

          else {

            if (i == 0)

              fillNjetPtJVT(histo_name, j, jetpt[k] * 1E3, jvt_tresh[n], weight, n_pvtx);

            else

              fillNjetPtJVT(histo_name, j, jetpt[k] * 1E3, jvt_tresh[n], weight, avgIntPerCross);

          }
        }
      }
    }
  }

  // fillNjetPt(reg + "n_pvtx_3jets_jetpt30" + suf, 3, 30000, weight, n_pvtx);
  // fillNjetPt(reg + "n_pvtx_3jets_jetpt40" + suf, 3, 40000, weight, n_pvtx);
  // fillNjetPt(reg + "n_pvtx_3jets_jetpt50" + suf, 3, 50000, weight, n_pvtx);
  // fillNjetPt(reg + "n_pvtx_3jets_jetpt70" + suf, 3, 70000, weight, n_pvtx);

  // avgIntPerCross = std::round(avgIntPerCross) + .5;

  // fillNjetPt(reg + "mu_3jets_jetpt30" + suf, 3, 30000, weight, avgIntPerCross);
  // fillNjetPt(reg + "mu_3jets_jetpt40" + suf, 3, 40000, weight, avgIntPerCross);
  // fillNjetPt(reg + "mu_3jets_jetpt50" + suf, 3, 50000, weight, avgIntPerCross);
  // fillNjetPt(reg + "mu_3jets_jetpt70" + suf, 3, 70000, weight, avgIntPerCross);

  // // Event survives if at most 4 jets or if there are more than 4 jets but the
  // // pt of the fifth is less than some threshold (Mind the vector counting start
  // // from 0):
  // fillNjetPt(reg + "n_pvtx_4jets_jetpt30" + suf, 4, 30000, weight, n_pvtx);
  // fillNjetPt(reg + "n_pvtx_4jets_jetpt40" + suf, 4, 40000, weight, n_pvtx);
  // fillNjetPt(reg + "n_pvtx_4jets_jetpt50" + suf, 4, 50000, weight, n_pvtx);
  // fillNjetPt(reg + "n_pvtx_4jets_jetpt70" + suf, 4, 70000, weight, n_pvtx);

  // fillNjetPt(reg + "mu_4jets_jetpt30" + suf, 4, 30000, weight, avgIntPerCross);
  // fillNjetPt(reg + "mu_4jets_jetpt40" + suf, 4, 40000, weight, avgIntPerCross);
  // fillNjetPt(reg + "mu_4jets_jetpt50" + suf, 4, 50000, weight, avgIntPerCross);
  // fillNjetPt(reg + "mu_4jets_jetpt70" + suf, 4, 70000, weight, avgIntPerCross);

  // // Event survives if at most 4 jets or if there are more than 5 jets but the
  // // pt of the sixth is less than some threshold (Mind the vector counting start
  // // from 0):
  // fillNjetPt(reg + "n_pvtx_5jets_jetpt30" + suf, 5, 30000, weight, n_pvtx);
  // fillNjetPt(reg + "n_pvtx_5jets_jetpt40" + suf, 5, 40000, weight, n_pvtx);
  // fillNjetPt(reg + "n_pvtx_5jets_jetpt50" + suf, 5, 50000, weight, n_pvtx);
  // fillNjetPt(reg + "n_pvtx_5jets_jetpt70" + suf, 5, 70000, weight, n_pvtx);

  // fillNjetPt(reg + "mu_5jets_jetpt30" + suf, 5, 30000, weight, avgIntPerCross);
  // fillNjetPt(reg + "mu_5jets_jetpt40" + suf, 5, 40000, weight, avgIntPerCross);
  // fillNjetPt(reg + "mu_5jets_jetpt50" + suf, 5, 50000, weight, avgIntPerCross);
  // fillNjetPt(reg + "mu_5jets_jetpt70" + suf, 5, 70000, weight, avgIntPerCross);

  // // Filling the JVT plot for different thresholds:
  // // For 3 jets:
  // fillNjetPtJVT(reg + "n_pvtx_3jets_jetpt30_jvt14" + suf, 3, 30000, .14, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_3jets_jetpt40_jvt14" + suf, 3, 40000, .14, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_3jets_jetpt50_jvt14" + suf, 3, 50000, .14, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_3jets_jetpt70_jvt14" + suf, 3, 70000, .14, weight, n_pvtx);

  // fillNjetPtJVT(reg + "n_pvtx_3jets_jetpt30_jvt64" + suf, 3, 30000, .64, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_3jets_jetpt40_jvt64" + suf, 3, 40000, .64, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_3jets_jetpt50_jvt64" + suf, 3, 50000, .64, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_3jets_jetpt70_jvt64" + suf, 3, 70000, .64, weight, n_pvtx);

  // fillNjetPtJVT(reg + "n_pvtx_3jets_jetpt30_jvt92" + suf, 3, 30000, .92, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_3jets_jetpt40_jvt92" + suf, 3, 40000, .92, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_3jets_jetpt50_jvt92" + suf, 3, 50000, .92, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_3jets_jetpt70_jvt92" + suf, 3, 70000, .92, weight, n_pvtx);

  // fillNjetPtJVT(reg + "mu_3jets_jetpt30_jvt14" + suf, 3, 30000, .14, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_3jets_jetpt40_jvt14" + suf, 3, 40000, .14, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_3jets_jetpt50_jvt14" + suf, 3, 50000, .14, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_3jets_jetpt70_jvt14" + suf, 3, 70000, .14, weight, avgIntPerCross);

  // fillNjetPtJVT(reg + "mu_3jets_jetpt30_jvt64" + suf, 3, 30000, .64, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_3jets_jetpt40_jvt64" + suf, 3, 40000, .64, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_3jets_jetpt50_jvt64" + suf, 3, 50000, .64, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_3jets_jetpt70_jvt64" + suf, 3, 70000, .64, weight, avgIntPerCross);

  // fillNjetPtJVT(reg + "mu_3jets_jetpt30_jvt92" + suf, 3, 30000, .92, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_3jets_jetpt40_jvt92" + suf, 3, 40000, .92, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_3jets_jetpt50_jvt92" + suf, 3, 50000, .92, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_3jets_jetpt70_jvt92" + suf, 3, 70000, .92, weight, avgIntPerCross);

  // // For 4 jets:
  // fillNjetPtJVT(reg + "n_pvtx_4jets_jetpt30_jvt14" + suf, 4, 30000, .14, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_4jets_jetpt40_jvt14" + suf, 4, 40000, .14, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_4jets_jetpt50_jvt14" + suf, 4, 50000, .14, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_4jets_jetpt70_jvt14" + suf, 4, 70000, .14, weight, n_pvtx);

  // fillNjetPtJVT(reg + "n_pvtx_4jets_jetpt30_jvt64" + suf, 4, 30000, .64, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_4jets_jetpt40_jvt64" + suf, 4, 40000, .64, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_4jets_jetpt50_jvt64" + suf, 4, 50000, .64, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_4jets_jetpt70_jvt64" + suf, 4, 70000, .64, weight, n_pvtx);

  // fillNjetPtJVT(reg + "n_pvtx_4jets_jetpt30_jvt92" + suf, 4, 30000, .92, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_4jets_jetpt40_jvt92" + suf, 4, 40000, .92, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_4jets_jetpt50_jvt92" + suf, 4, 50000, .92, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_4jets_jetpt70_jvt92" + suf, 4, 70000, .92, weight, n_pvtx);

  // fillNjetPtJVT(reg + "mu_4jets_jetpt30_jvt14" + suf, 4, 30000, .14, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_4jets_jetpt40_jvt14" + suf, 4, 40000, .14, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_4jets_jetpt50_jvt14" + suf, 4, 50000, .14, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_4jets_jetpt70_jvt14" + suf, 4, 70000, .14, weight, avgIntPerCross);

  // fillNjetPtJVT(reg + "mu_4jets_jetpt30_jvt64" + suf, 4, 30000, .64, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_4jets_jetpt40_jvt64" + suf, 4, 40000, .64, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_4jets_jetpt50_jvt64" + suf, 4, 50000, .64, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_4jets_jetpt70_jvt64" + suf, 4, 70000, .64, weight, avgIntPerCross);

  // fillNjetPtJVT(reg + "mu_4jets_jetpt30_jvt92" + suf, 4, 30000, .92, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_4jets_jetpt40_jvt92" + suf, 4, 40000, .92, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_4jets_jetpt50_jvt92" + suf, 4, 50000, .92, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_4jets_jetpt70_jvt92" + suf, 4, 70000, .92, weight, avgIntPerCross);

  // // For 5 jets:
  // fillNjetPtJVT(reg + "n_pvtx_5jets_jetpt30_jvt14" + suf, 5, 30000, .14, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_5jets_jetpt40_jvt14" + suf, 5, 40000, .14, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_5jets_jetpt50_jvt14" + suf, 5, 50000, .14, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_5jets_jetpt70_jvt14" + suf, 5, 70000, .14, weight, n_pvtx);

  // fillNjetPtJVT(reg + "n_pvtx_5jets_jetpt30_jvt64" + suf, 5, 30000, .64, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_5jets_jetpt40_jvt64" + suf, 5, 40000, .64, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_5jets_jetpt50_jvt64" + suf, 5, 50000, .64, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_5jets_jetpt70_jvt64" + suf, 5, 70000, .64, weight, n_pvtx);

  // fillNjetPtJVT(reg + "n_pvtx_5jets_jetpt30_jvt92" + suf, 5, 30000, .92, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_5jets_jetpt40_jvt92" + suf, 5, 40000, .92, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_5jets_jetpt50_jvt92" + suf, 5, 50000, .92, weight, n_pvtx);
  // fillNjetPtJVT(reg + "n_pvtx_5jets_jetpt70_jvt92" + suf, 5, 70000, .92, weight, n_pvtx);

  // fillNjetPtJVT(reg + "mu_5jets_jetpt30_jvt14" + suf, 5, 30000, .14, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_5jets_jetpt40_jvt14" + suf, 5, 40000, .14, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_5jets_jetpt50_jvt14" + suf, 5, 50000, .14, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_5jets_jetpt70_jvt14" + suf, 5, 70000, .14, weight, avgIntPerCross);

  // fillNjetPtJVT(reg + "mu_5jets_jetpt30_jvt64" + suf, 5, 30000, .64, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_5jets_jetpt40_jvt64" + suf, 5, 40000, .64, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_5jets_jetpt50_jvt64" + suf, 5, 50000, .64, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_5jets_jetpt70_jvt64" + suf, 5, 70000, .64, weight, avgIntPerCross);

  // fillNjetPtJVT(reg + "mu_5jets_jetpt30_jvt92" + suf, 5, 30000, .92, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_5jets_jetpt40_jvt92" + suf, 5, 40000, .92, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_5jets_jetpt50_jvt92" + suf, 5, 50000, .92, weight, avgIntPerCross);
  // fillNjetPtJVT(reg + "mu_5jets_jetpt70_jvt92" + suf, 5, 70000, .92, weight, avgIntPerCross);
}
