#include "MiniReader/MiniReaderAlg.h"
#include <math.h>

static constexpr const float MINETA = -5.;
static constexpr const float MAXETA = 5.;

#define SOME_ENUM(DO)			\
  DO(EtMissMuVeto)                      \
  DO(InteractionPerCrossing)		\
  DO(InteractionPerCrossing_eta24)	\
  DO(jetMultiplicityNoCut)              \
  DO(n_pvtx_noCut)                      \
  DO(n_pvtx_eta24)                      \
  DO(jvf)				\
  DO(jvf_highPileUp)			\
  DO(jvf_lowPileUp)			\
  DO(n_pvtx_3jets_jetpt30)              \
  DO(n_pvtx_3jets_jetpt40)              \
  DO(n_pvtx_3jets_jetpt50)              \
  DO(n_pvtx_3jets_jetpt70)              \
  DO(n_pvtx_3jets_jetpt30_jvf_acc)      \
  DO(n_pvtx_3jets_jetpt40_jvf_acc)      \
  DO(n_pvtx_3jets_jetpt50_jvf_acc)      \
  DO(n_pvtx_3jets_jetpt70_jvf_acc)      \
  DO(mu_3jets_jetpt30)			\
  DO(mu_3jets_jetpt40)			\
  DO(mu_3jets_jetpt50)			\
  DO(mu_3jets_jetpt70)			\
  DO(mu_3jets_jetpt30_jvf_acc)		\
  DO(mu_3jets_jetpt40_jvf_acc)		\
  DO(mu_3jets_jetpt50_jvf_acc)		\
  DO(mu_3jets_jetpt70_jvf_acc)		\
  DO(n_pvtx_4jets_jetpt30)              \
  DO(n_pvtx_4jets_jetpt40)              \
  DO(n_pvtx_4jets_jetpt50)              \
  DO(n_pvtx_4jets_jetpt70)              \
  DO(n_pvtx_4jets_jetpt30_jvf_acc)      \
  DO(n_pvtx_4jets_jetpt40_jvf_acc)      \
  DO(n_pvtx_4jets_jetpt50_jvf_acc)      \
  DO(n_pvtx_4jets_jetpt70_jvf_acc)      \
  DO(mu_4jets_jetpt30)			\
  DO(mu_4jets_jetpt40)			\
  DO(mu_4jets_jetpt50)			\
  DO(mu_4jets_jetpt70)			\
  DO(mu_4jets_jetpt30_jvf_acc)		\
  DO(mu_4jets_jetpt40_jvf_acc)		\
  DO(mu_4jets_jetpt50_jvf_acc)		\
  DO(mu_4jets_jetpt70_jvf_acc)		\
  DO(n_pvtx_5jets_jetpt30)              \
  DO(n_pvtx_5jets_jetpt40)              \
  DO(n_pvtx_5jets_jetpt50)              \
  DO(n_pvtx_5jets_jetpt70)              \
  DO(n_pvtx_5jets_jetpt30_jvf_acc)      \
  DO(n_pvtx_5jets_jetpt40_jvf_acc)      \
  DO(n_pvtx_5jets_jetpt50_jvf_acc)      \
  DO(n_pvtx_5jets_jetpt70_jvf_acc)      \
  DO(mu_5jets_jetpt30)			\
  DO(mu_5jets_jetpt40)			\
  DO(mu_5jets_jetpt50)			\
  DO(mu_5jets_jetpt70)			\
  DO(mu_5jets_jetpt30_jvf_acc)		\
  DO(mu_5jets_jetpt40_jvf_acc)		\
  DO(mu_5jets_jetpt50_jvf_acc)		\
  DO(mu_5jets_jetpt70_jvf_acc)		\
  DO(jetEfficency_3jets_jetpt30)        \
  DO(jetEfficency_3jets_jetpt40)        \
  DO(jetEfficency_3jets_jetpt50)        \
  DO(jetEfficency_3jets_jetpt70)        \
  DO(jetEfficency_3jets_jetpt30_mu)     \
  DO(jetEfficency_3jets_jetpt40_mu)     \
  DO(jetEfficency_3jets_jetpt50_mu)     \
  DO(jetEfficency_3jets_jetpt70_mu)     \
  DO(jetEfficency_3jets_jetpt30_jvf_acc)\
  DO(jetEfficency_3jets_jetpt40_jvf_acc)\
  DO(jetEfficency_3jets_jetpt50_jvf_acc)\
  DO(jetEfficency_3jets_jetpt70_jvf_acc)\
  DO(jetEfficency_3jets_jetpt30_jvf_acc_mu)\
  DO(jetEfficency_3jets_jetpt40_jvf_acc_mu)\
  DO(jetEfficency_3jets_jetpt50_jvf_acc_mu)\
  DO(jetEfficency_3jets_jetpt70_jvf_acc_mu)\
  DO(jetEfficency_4jets_jetpt30)        \
  DO(jetEfficency_4jets_jetpt40)        \
  DO(jetEfficency_4jets_jetpt50)        \
  DO(jetEfficency_4jets_jetpt70)        \
  DO(jetEfficency_4jets_jetpt30_mu)     \
  DO(jetEfficency_4jets_jetpt40_mu)     \
  DO(jetEfficency_4jets_jetpt50_mu)     \
  DO(jetEfficency_4jets_jetpt70_mu)     \
  DO(jetEfficency_4jets_jetpt30_jvf_acc)\
  DO(jetEfficency_4jets_jetpt40_jvf_acc)\
  DO(jetEfficency_4jets_jetpt50_jvf_acc)\
  DO(jetEfficency_4jets_jetpt70_jvf_acc)\
  DO(jetEfficency_4jets_jetpt30_jvf_acc_mu)\
  DO(jetEfficency_4jets_jetpt40_jvf_acc_mu)\
  DO(jetEfficency_4jets_jetpt50_jvf_acc_mu)\
  DO(jetEfficency_4jets_jetpt70_jvf_acc_mu)\
  DO(jetEfficency_5jets_jetpt30)        \
  DO(jetEfficency_5jets_jetpt40)        \
  DO(jetEfficency_5jets_jetpt50)        \
  DO(jetEfficency_5jets_jetpt70)        \
  DO(jetEfficency_5jets_jetpt30_mu)     \
  DO(jetEfficency_5jets_jetpt40_mu)     \
  DO(jetEfficency_5jets_jetpt50_mu)     \
  DO(jetEfficency_5jets_jetpt70_mu)     \
  DO(jetEfficency_5jets_jetpt30_jvf_acc)\
  DO(jetEfficency_5jets_jetpt40_jvf_acc)\
  DO(jetEfficency_5jets_jetpt50_jvf_acc)\
  DO(jetEfficency_5jets_jetpt70_jvf_acc)\
  DO(jetEfficency_5jets_jetpt30_jvf_acc_mu)\
  DO(jetEfficency_5jets_jetpt40_jvf_acc_mu)\
  DO(jetEfficency_5jets_jetpt50_jvf_acc_mu)\
  DO(jetEfficency_5jets_jetpt70_jvf_acc_mu)\


#define SCATTER_ENUM(DO)  \
  DO(n_jet_per_n_pvtx)    \
  DO(n_jet_per_n_pvtx_jvf_acc)  \

#define CONCAT(a, b) a ## b

#define STRING(a) STRINGIZE(a)
#define STRINGIZE(a) #a

#define MAKE_ENUM(VAR) VAR,
#define MAKE_STRINGS(VAR) #VAR,

enum HistoNames {
  SOME_ENUM(MAKE_ENUM)
};

enum ScatterNames {
  SCATTER_ENUM(MAKE_ENUM)
};

const char *const HistoNamesString[] = {
  SOME_ENUM(MAKE_STRINGS)
};

const char *const ScatterNameString[] = {
  SCATTER_ENUM(MAKE_STRINGS)
};

void MiniReaderAlg::DefineHisto(int name, int nbin, float x_low, float x_max)
{
  TH1F *temp_pointer = new TH1F(HistoNamesString[name], HistoNamesString[name],
                                nbin, x_low, x_max);

  TH1::SetDefaultSumw2(true);

  m_HistoContainer.push_back(temp_pointer);
  wk()->addOutput(temp_pointer);
}

void MiniReaderAlg::DefineScatterPlot(int name, int nbinx, double x_low, double
                                      x_max, int nbiny, double y_low, double
                                      y_max)
{
  TH2F *temp_pointer = new TH2F(ScatterNameString[name], ScatterNameString[name],
                                nbinx, x_low, x_max, nbiny, y_low, y_max);

  m_ScatterPlotContainer.push_back(temp_pointer);
  wk()->addOutput(temp_pointer);
}

void MiniReaderAlg::InitHisto()
{
  // MET Histos:
  DefineHisto(EtMissMuVeto, 100, 0, 1100);

  // Jet Histos:
  DefineHisto(InteractionPerCrossing, 8, 0, 40);
  DefineHisto(InteractionPerCrossing_eta24, 8, 0, 40);
  DefineHisto(jetMultiplicityNoCut,40, 0, 100);

  DefineHisto(n_pvtx_noCut, 8, 0, 40);
  DefineHisto(n_pvtx_eta24, 8, 0, 40);

  DefineHisto(jvf, 50, -2, 2);
  DefineHisto(jvf_highPileUp, 50, -2, 2);
  DefineHisto(jvf_lowPileUp, 50, -2, 2);

  DefineHisto(n_pvtx_3jets_jetpt30, 8, 0, 40);
  DefineHisto(n_pvtx_3jets_jetpt40, 8, 0, 40);
  DefineHisto(n_pvtx_3jets_jetpt50, 8, 0, 40);
  DefineHisto(n_pvtx_3jets_jetpt70, 8, 0, 40);

  DefineHisto(n_pvtx_3jets_jetpt30_jvf_acc, 8, 0, 40);
  DefineHisto(n_pvtx_3jets_jetpt40_jvf_acc, 8, 0, 40);
  DefineHisto(n_pvtx_3jets_jetpt50_jvf_acc, 8, 0, 40);
  DefineHisto(n_pvtx_3jets_jetpt70_jvf_acc, 8, 0, 40);

  DefineHisto(mu_3jets_jetpt30, 8, 0, 40);
  DefineHisto(mu_3jets_jetpt40, 8, 0, 40);
  DefineHisto(mu_3jets_jetpt50, 8, 0, 40);
  DefineHisto(mu_3jets_jetpt70, 8, 0, 40);

  DefineHisto(mu_3jets_jetpt30_jvf_acc, 8, 0, 40);
  DefineHisto(mu_3jets_jetpt40_jvf_acc, 8, 0, 40);
  DefineHisto(mu_3jets_jetpt50_jvf_acc, 8, 0, 40);
  DefineHisto(mu_3jets_jetpt70_jvf_acc, 8, 0, 40);

  DefineHisto(n_pvtx_4jets_jetpt30, 8, 0, 40);
  DefineHisto(n_pvtx_4jets_jetpt40, 8, 0, 40);
  DefineHisto(n_pvtx_4jets_jetpt50, 8, 0, 40);
  DefineHisto(n_pvtx_4jets_jetpt70, 8, 0, 40);

  DefineHisto(n_pvtx_4jets_jetpt30_jvf_acc, 8, 0, 40);
  DefineHisto(n_pvtx_4jets_jetpt40_jvf_acc, 8, 0, 40);
  DefineHisto(n_pvtx_4jets_jetpt50_jvf_acc, 8, 0, 40);
  DefineHisto(n_pvtx_4jets_jetpt70_jvf_acc, 8, 0, 40);

  DefineHisto(mu_4jets_jetpt30, 8, 0, 40);
  DefineHisto(mu_4jets_jetpt40, 8, 0, 40);
  DefineHisto(mu_4jets_jetpt50, 8, 0, 40);
  DefineHisto(mu_4jets_jetpt70, 8, 0, 40);

  DefineHisto(mu_4jets_jetpt30_jvf_acc, 8, 0, 40);
  DefineHisto(mu_4jets_jetpt40_jvf_acc, 8, 0, 40);
  DefineHisto(mu_4jets_jetpt50_jvf_acc, 8, 0, 40);
  DefineHisto(mu_4jets_jetpt70_jvf_acc, 8, 0, 40);

  DefineHisto(n_pvtx_5jets_jetpt30, 8, 0, 40);
  DefineHisto(n_pvtx_5jets_jetpt40, 8, 0, 40);
  DefineHisto(n_pvtx_5jets_jetpt50, 8, 0, 40);
  DefineHisto(n_pvtx_5jets_jetpt70, 8, 0, 40);

  DefineHisto(n_pvtx_5jets_jetpt30_jvf_acc, 8, 0, 40);
  DefineHisto(n_pvtx_5jets_jetpt40_jvf_acc, 8, 0, 40);
  DefineHisto(n_pvtx_5jets_jetpt50_jvf_acc, 8, 0, 40);
  DefineHisto(n_pvtx_5jets_jetpt70_jvf_acc, 8, 0, 40);

  DefineHisto(mu_5jets_jetpt30, 8, 0, 40);
  DefineHisto(mu_5jets_jetpt40, 8, 0, 40);
  DefineHisto(mu_5jets_jetpt50, 8, 0, 40);
  DefineHisto(mu_5jets_jetpt70, 8, 0, 40);

  DefineHisto(mu_5jets_jetpt30_jvf_acc, 8, 0, 40);
  DefineHisto(mu_5jets_jetpt40_jvf_acc, 8, 0, 40);
  DefineHisto(mu_5jets_jetpt50_jvf_acc, 8, 0, 40);
  DefineHisto(mu_5jets_jetpt70_jvf_acc, 8, 0, 40);

  DefineHisto(jetEfficency_3jets_jetpt30, 8, 0, 40);
  DefineHisto(jetEfficency_3jets_jetpt40, 8, 0, 40);
  DefineHisto(jetEfficency_3jets_jetpt50, 8, 0, 40);
  DefineHisto(jetEfficency_3jets_jetpt70, 8, 0, 40);

  DefineHisto(jetEfficency_3jets_jetpt30_mu, 8, 0, 40);
  DefineHisto(jetEfficency_3jets_jetpt40_mu, 8, 0, 40);
  DefineHisto(jetEfficency_3jets_jetpt50_mu, 8, 0, 40);
  DefineHisto(jetEfficency_3jets_jetpt70_mu, 8, 0, 40);

  DefineHisto(jetEfficency_3jets_jetpt30_jvf_acc, 8, 0, 40);
  DefineHisto(jetEfficency_3jets_jetpt40_jvf_acc, 8, 0, 40);
  DefineHisto(jetEfficency_3jets_jetpt50_jvf_acc, 8, 0, 40);
  DefineHisto(jetEfficency_3jets_jetpt70_jvf_acc, 8, 0, 40);

  DefineHisto(jetEfficency_3jets_jetpt30_jvf_acc_mu, 8, 0, 40);
  DefineHisto(jetEfficency_3jets_jetpt40_jvf_acc_mu, 8, 0, 40);
  DefineHisto(jetEfficency_3jets_jetpt50_jvf_acc_mu, 8, 0, 40);
  DefineHisto(jetEfficency_3jets_jetpt70_jvf_acc_mu, 8, 0, 40);

  DefineHisto(jetEfficency_4jets_jetpt30, 8, 0, 40);
  DefineHisto(jetEfficency_4jets_jetpt40, 8, 0, 40);
  DefineHisto(jetEfficency_4jets_jetpt50, 8, 0, 40);
  DefineHisto(jetEfficency_4jets_jetpt70, 8, 0, 40);

  DefineHisto(jetEfficency_4jets_jetpt30_mu, 8, 0, 40);
  DefineHisto(jetEfficency_4jets_jetpt40_mu, 8, 0, 40);
  DefineHisto(jetEfficency_4jets_jetpt50_mu, 8, 0, 40);
  DefineHisto(jetEfficency_4jets_jetpt70_mu, 8, 0, 40);

  DefineHisto(jetEfficency_4jets_jetpt30_jvf_acc, 8, 0, 40);
  DefineHisto(jetEfficency_4jets_jetpt40_jvf_acc, 8, 0, 40);
  DefineHisto(jetEfficency_4jets_jetpt50_jvf_acc, 8, 0, 40);
  DefineHisto(jetEfficency_4jets_jetpt70_jvf_acc, 8, 0, 40);

  DefineHisto(jetEfficency_4jets_jetpt30_jvf_acc_mu, 8, 0, 40);
  DefineHisto(jetEfficency_4jets_jetpt40_jvf_acc_mu, 8, 0, 40);
  DefineHisto(jetEfficency_4jets_jetpt50_jvf_acc_mu, 8, 0, 40);
  DefineHisto(jetEfficency_4jets_jetpt70_jvf_acc_mu, 8, 0, 40);

  DefineHisto(jetEfficency_5jets_jetpt30, 8, 0, 40);
  DefineHisto(jetEfficency_5jets_jetpt40, 8, 0, 40);
  DefineHisto(jetEfficency_5jets_jetpt50, 8, 0, 40);
  DefineHisto(jetEfficency_5jets_jetpt70, 8, 0, 40);

  DefineHisto(jetEfficency_5jets_jetpt30_mu, 8, 0, 40);
  DefineHisto(jetEfficency_5jets_jetpt40_mu, 8, 0, 40);
  DefineHisto(jetEfficency_5jets_jetpt50_mu, 8, 0, 40);
  DefineHisto(jetEfficency_5jets_jetpt70_mu, 8, 0, 40);

  DefineHisto(jetEfficency_5jets_jetpt30_jvf_acc, 8, 0, 40);
  DefineHisto(jetEfficency_5jets_jetpt40_jvf_acc, 8, 0, 40);
  DefineHisto(jetEfficency_5jets_jetpt50_jvf_acc, 8, 0, 40);
  DefineHisto(jetEfficency_5jets_jetpt70_jvf_acc, 8, 0, 40);

  DefineHisto(jetEfficency_5jets_jetpt30_jvf_acc_mu, 8, 0, 40);
  DefineHisto(jetEfficency_5jets_jetpt40_jvf_acc_mu, 8, 0, 40);
  DefineHisto(jetEfficency_5jets_jetpt50_jvf_acc_mu, 8, 0, 40);
  DefineHisto(jetEfficency_5jets_jetpt70_jvf_acc_mu, 8, 0, 40);

  DefineScatterPlot(n_jet_per_n_pvtx, 40, 0, 40, 10, 0, 10);
  DefineScatterPlot(n_jet_per_n_pvtx_jvf_acc, 40, 0, 40, 10, 0, 10);
}

void MiniReaderAlg::FillMET(double weight)
{
  m_HistoContainer[EtMissMuVeto]->Fill(toGeV(m_met.m_EtMissMuVeto), weight);
}

void MiniReaderAlg::FillScatterPlots(double weight)
{
  m_ScatterPlotContainer[n_jet_per_n_pvtx]->Fill(m_pvtx.m_pvtx_n,
      m_jet.m_jet_mult, weight);

  int n_jet_jvf_acc = 0;

  for (int i = 0; i < m_jet.m_jet_mult; ++i) {

    if (std::fabs(m_jet.m_jet_jvf->at(i)) > .5)

      ++n_jet_jvf_acc;
  }

  m_ScatterPlotContainer[n_jet_per_n_pvtx_jvf_acc]->Fill(m_pvtx.m_pvtx_n,
      n_jet_jvf_acc, weight);
}


template <typename T>
void MiniReaderAlg::fillNjetPt(int name, int n_jet, int pt_tresh, double weight,
			       T fill_var)
{
  if (m_jet.m_jet_mult <= n_jet || (m_jet.m_jet_mult > n_jet && m_jet.m_jet_pt->at(n_jet) < pt_tresh))

    m_HistoContainer[name]->Fill(fill_var, weight);
}

template <typename T>
void MiniReaderAlg::fillNjetPtJVF(std::vector<float> jet_pt, int name, int n_jet, int
		   pt_tresh, double weight, T fill_var)
{
  if (jet_pt.size() <= n_jet || (jet_pt.size() > n_jet && jet_pt.at(n_jet) < pt_tresh))

    m_HistoContainer[name]->Fill(fill_var, weight);
}

void MiniReaderAlg::FillJets(double weight)
{
  m_HistoContainer[jetMultiplicityNoCut]->Fill(m_jet.m_jet_mult, weight);
  m_HistoContainer[n_pvtx_noCut]->Fill(m_pvtx.m_pvtx_n, weight);

  for (size_t i = 0; i < m_jet.m_jet_jvf->size(); ++i) {

    m_HistoContainer[jvf]->Fill(m_jet.m_jet_jvf->at(i), weight);

    if (m_jet.m_jet_mult < 4 || (m_jet.m_jet_mult > 3 && m_jet.m_jet_pt->at(3) <
                                 30000)) {

      if (m_pvtx.m_pvtx_n > 15)

        m_HistoContainer[jvf_highPileUp]->Fill(m_jet.m_jet_jvf->at(i), weight);

      if (m_pvtx.m_pvtx_n < 15)

        m_HistoContainer[jvf_lowPileUp]->Fill(m_jet.m_jet_jvf->at(i), weight);
    }
  }

  // Event survives if at most 3 jets or if there are more than 3 jets but the
  // pt of the fourth is less than some threshold (Mind the vector counting start
  // from 0):
  fillNjetPt(n_pvtx_3jets_jetpt30, 3, 30000, weight, m_pvtx.m_pvtx_n);
  fillNjetPt(n_pvtx_3jets_jetpt40, 3, 40000, weight, m_pvtx.m_pvtx_n);
  fillNjetPt(n_pvtx_3jets_jetpt50, 3, 50000, weight, m_pvtx.m_pvtx_n);
  fillNjetPt(n_pvtx_3jets_jetpt70, 3, 70000, weight, m_pvtx.m_pvtx_n);

  fillNjetPt(mu_3jets_jetpt30, 3, 30000, weight, std::round(m_info.m_averageInteractionsPerCrossing) + .5);
  fillNjetPt(mu_3jets_jetpt40, 3, 40000, weight, std::round(m_info.m_averageInteractionsPerCrossing) + .5);
  fillNjetPt(mu_3jets_jetpt50, 3, 50000, weight, std::round(m_info.m_averageInteractionsPerCrossing) + .5);
  fillNjetPt(mu_3jets_jetpt70, 3, 70000, weight, std::round(m_info.m_averageInteractionsPerCrossing) + .5);

  // Event survives if at most 4 jets or if there are more than 4 jets but the
  // pt of the fifth is less than some threshold (Mind the vector counting start
  // from 0):
  fillNjetPt(n_pvtx_4jets_jetpt30, 4, 30000, weight, m_pvtx.m_pvtx_n);
  fillNjetPt(n_pvtx_4jets_jetpt40, 4, 40000, weight, m_pvtx.m_pvtx_n);
  fillNjetPt(n_pvtx_4jets_jetpt50, 4, 50000, weight, m_pvtx.m_pvtx_n);
  fillNjetPt(n_pvtx_4jets_jetpt70, 4, 70000, weight, m_pvtx.m_pvtx_n);

  fillNjetPt(mu_4jets_jetpt30, 4, 30000, weight, std::round(m_info.m_averageInteractionsPerCrossing) + .5);
  fillNjetPt(mu_4jets_jetpt40, 4, 40000, weight, std::round(m_info.m_averageInteractionsPerCrossing) + .5);
  fillNjetPt(mu_4jets_jetpt50, 4, 50000, weight, std::round(m_info.m_averageInteractionsPerCrossing) + .5);
  fillNjetPt(mu_4jets_jetpt70, 4, 70000, weight, std::round(m_info.m_averageInteractionsPerCrossing) + .5);

  // // Event survives if at most 4 jets or if there are more than 5 jets but the
  // // pt of the sixth is less than some threshold (Mind the vector counting start
  // // from 0):
  fillNjetPt(n_pvtx_5jets_jetpt30, 5, 30000, weight, m_pvtx.m_pvtx_n);
  fillNjetPt(n_pvtx_5jets_jetpt40, 5, 40000, weight, m_pvtx.m_pvtx_n);
  fillNjetPt(n_pvtx_5jets_jetpt50, 5, 50000, weight, m_pvtx.m_pvtx_n);
  fillNjetPt(n_pvtx_5jets_jetpt70, 5, 70000, weight, m_pvtx.m_pvtx_n);

  fillNjetPt(mu_5jets_jetpt30, 5, 30000, weight, std::round(m_info.m_averageInteractionsPerCrossing) + .5);
  fillNjetPt(mu_5jets_jetpt40, 5, 40000, weight, std::round(m_info.m_averageInteractionsPerCrossing) + .5);
  fillNjetPt(mu_5jets_jetpt50, 5, 50000, weight, std::round(m_info.m_averageInteractionsPerCrossing) + .5);
  fillNjetPt(mu_5jets_jetpt70, 5, 70000, weight, std::round(m_info.m_averageInteractionsPerCrossing) + .5);

  // Additional condition on JVF and eta:
  std::vector<float> jvf_acc_jet_pt;
  int n_pvtx_eta24_count = -999;
  float n_intPerCrossing_eta24 = -999;

  for (int i = 0; i < m_jet.m_jet_mult; ++i) {

    if (std::fabs(m_jet.m_jet_eta->at(i)) < 2.4 && std::fabs(m_jet.m_jet_jvf->at(i)) > .5)
    // if (std::fabs(m_jet.m_jet_eta->at(i)) < 2.4 && m_jet.m_jet_jvt->at(i) > .2)

      jvf_acc_jet_pt.push_back(m_jet.m_jet_pt->at(i));

    if (std::fabs(m_jet.m_jet_eta->at(i))) {

      n_pvtx_eta24_count = m_pvtx.m_pvtx_n;
      n_intPerCrossing_eta24 = m_info.m_averageInteractionsPerCrossing;
    }
  }

  m_HistoContainer[n_pvtx_eta24]->Fill(n_pvtx_eta24_count, weight);
  m_HistoContainer[InteractionPerCrossing_eta24]->Fill(std::round(n_intPerCrossing_eta24)
						       + .5, weight);


  // For the three jets:
  fillNjetPtJVF(jvf_acc_jet_pt, n_pvtx_3jets_jetpt30_jvf_acc, 3, 30000, weight, m_pvtx.m_pvtx_n);
  fillNjetPtJVF(jvf_acc_jet_pt, n_pvtx_3jets_jetpt40_jvf_acc, 3, 40000, weight, m_pvtx.m_pvtx_n);
  fillNjetPtJVF(jvf_acc_jet_pt, n_pvtx_3jets_jetpt50_jvf_acc, 3, 50000, weight, m_pvtx.m_pvtx_n);
  fillNjetPtJVF(jvf_acc_jet_pt, n_pvtx_3jets_jetpt70_jvf_acc, 3, 70000, weight, m_pvtx.m_pvtx_n);

  fillNjetPtJVF(jvf_acc_jet_pt, mu_3jets_jetpt30_jvf_acc, 3, 30000, weight, std::round(n_intPerCrossing_eta24) + .5);
  fillNjetPtJVF(jvf_acc_jet_pt, mu_3jets_jetpt40_jvf_acc, 3, 40000, weight, std::round(n_intPerCrossing_eta24) + .5);
  fillNjetPtJVF(jvf_acc_jet_pt, mu_3jets_jetpt50_jvf_acc, 3, 50000, weight, std::round(n_intPerCrossing_eta24) + .5);
  fillNjetPtJVF(jvf_acc_jet_pt, mu_3jets_jetpt70_jvf_acc, 3, 70000, weight, std::round(n_intPerCrossing_eta24) + .5);

  // For the four jets:
  fillNjetPtJVF(jvf_acc_jet_pt, n_pvtx_4jets_jetpt30_jvf_acc, 4, 30000, weight, m_pvtx.m_pvtx_n);
  fillNjetPtJVF(jvf_acc_jet_pt, n_pvtx_4jets_jetpt40_jvf_acc, 4, 40000, weight, m_pvtx.m_pvtx_n);
  fillNjetPtJVF(jvf_acc_jet_pt, n_pvtx_4jets_jetpt50_jvf_acc, 4, 50000, weight, m_pvtx.m_pvtx_n);
  fillNjetPtJVF(jvf_acc_jet_pt, n_pvtx_4jets_jetpt70_jvf_acc, 4, 70000, weight, m_pvtx.m_pvtx_n);

  fillNjetPtJVF(jvf_acc_jet_pt, mu_4jets_jetpt30_jvf_acc, 4, 30000, weight, std::round(n_intPerCrossing_eta24) + .5);
  fillNjetPtJVF(jvf_acc_jet_pt, mu_4jets_jetpt40_jvf_acc, 4, 40000, weight, std::round(n_intPerCrossing_eta24) + .5);
  fillNjetPtJVF(jvf_acc_jet_pt, mu_4jets_jetpt50_jvf_acc, 4, 50000, weight, std::round(n_intPerCrossing_eta24) + .5);
  fillNjetPtJVF(jvf_acc_jet_pt, mu_4jets_jetpt70_jvf_acc, 4, 70000, weight, std::round(n_intPerCrossing_eta24) + .5);

  // // For the five jets:
  fillNjetPtJVF(jvf_acc_jet_pt, n_pvtx_5jets_jetpt30_jvf_acc, 5, 30000, weight, m_pvtx.m_pvtx_n);
  fillNjetPtJVF(jvf_acc_jet_pt, n_pvtx_5jets_jetpt40_jvf_acc, 5, 40000, weight, m_pvtx.m_pvtx_n);
  fillNjetPtJVF(jvf_acc_jet_pt, n_pvtx_5jets_jetpt50_jvf_acc, 5, 50000, weight, m_pvtx.m_pvtx_n);
  fillNjetPtJVF(jvf_acc_jet_pt, n_pvtx_5jets_jetpt70_jvf_acc, 5, 70000, weight, m_pvtx.m_pvtx_n);

  fillNjetPtJVF(jvf_acc_jet_pt, mu_5jets_jetpt30_jvf_acc, 5, 30000, weight, std::round(n_intPerCrossing_eta24) + .5);
  fillNjetPtJVF(jvf_acc_jet_pt, mu_5jets_jetpt40_jvf_acc, 5, 40000, weight, std::round(n_intPerCrossing_eta24) + .5);
  fillNjetPtJVF(jvf_acc_jet_pt, mu_5jets_jetpt50_jvf_acc, 5, 50000, weight, std::round(n_intPerCrossing_eta24) + .5);
  fillNjetPtJVF(jvf_acc_jet_pt, mu_5jets_jetpt70_jvf_acc, 5, 70000, weight, std::round(n_intPerCrossing_eta24) + .5);
}

void MiniReaderAlg::FillEventInfo(double weight)
{
  m_HistoContainer[InteractionPerCrossing]->Fill(std::round(m_info.m_averageInteractionsPerCrossing)
						 + .5, weight);
}

void MiniReaderAlg::DivideHisto(int name, int num, int den)
{
  m_HistoContainer[name]->Divide(m_HistoContainer[num], m_HistoContainer[den]);
}


void MiniReaderAlg::PlotJetEfficency()
{
  DivideHisto(jetEfficency_3jets_jetpt30, n_pvtx_3jets_jetpt30, n_pvtx_noCut);
  DivideHisto(jetEfficency_3jets_jetpt40, n_pvtx_3jets_jetpt40, n_pvtx_noCut);
  DivideHisto(jetEfficency_3jets_jetpt50, n_pvtx_3jets_jetpt50, n_pvtx_noCut);
  DivideHisto(jetEfficency_3jets_jetpt70, n_pvtx_3jets_jetpt70, n_pvtx_noCut);

  DivideHisto(jetEfficency_3jets_jetpt30_jvf_acc, n_pvtx_3jets_jetpt30_jvf_acc, n_pvtx_eta24);
  DivideHisto(jetEfficency_3jets_jetpt40_jvf_acc, n_pvtx_3jets_jetpt40_jvf_acc, n_pvtx_eta24);
  DivideHisto(jetEfficency_3jets_jetpt50_jvf_acc, n_pvtx_3jets_jetpt50_jvf_acc, n_pvtx_eta24);
  DivideHisto(jetEfficency_3jets_jetpt70_jvf_acc, n_pvtx_3jets_jetpt70_jvf_acc, n_pvtx_eta24);

  DivideHisto(jetEfficency_3jets_jetpt30_mu, mu_3jets_jetpt30, InteractionPerCrossing);
  DivideHisto(jetEfficency_3jets_jetpt40_mu, mu_3jets_jetpt40, InteractionPerCrossing);
  DivideHisto(jetEfficency_3jets_jetpt50_mu, mu_3jets_jetpt50, InteractionPerCrossing);
  DivideHisto(jetEfficency_3jets_jetpt70_mu, mu_3jets_jetpt70, InteractionPerCrossing);

  DivideHisto(jetEfficency_3jets_jetpt30_jvf_acc_mu, mu_3jets_jetpt30_jvf_acc, InteractionPerCrossing_eta24);
  DivideHisto(jetEfficency_3jets_jetpt40_jvf_acc_mu, mu_3jets_jetpt40_jvf_acc, InteractionPerCrossing_eta24);
  DivideHisto(jetEfficency_3jets_jetpt50_jvf_acc_mu, mu_3jets_jetpt50_jvf_acc, InteractionPerCrossing_eta24);
  DivideHisto(jetEfficency_3jets_jetpt70_jvf_acc_mu, mu_3jets_jetpt70_jvf_acc, InteractionPerCrossing_eta24);

  DivideHisto(jetEfficency_4jets_jetpt30, n_pvtx_4jets_jetpt30, n_pvtx_noCut);
  DivideHisto(jetEfficency_4jets_jetpt40, n_pvtx_4jets_jetpt40, n_pvtx_noCut);
  DivideHisto(jetEfficency_4jets_jetpt50, n_pvtx_4jets_jetpt50, n_pvtx_noCut);
  DivideHisto(jetEfficency_4jets_jetpt70, n_pvtx_4jets_jetpt70, n_pvtx_noCut);

  DivideHisto(jetEfficency_4jets_jetpt30_jvf_acc, n_pvtx_4jets_jetpt30_jvf_acc, n_pvtx_eta24);
  DivideHisto(jetEfficency_4jets_jetpt40_jvf_acc, n_pvtx_4jets_jetpt40_jvf_acc, n_pvtx_eta24);
  DivideHisto(jetEfficency_4jets_jetpt50_jvf_acc, n_pvtx_4jets_jetpt50_jvf_acc, n_pvtx_eta24);
  DivideHisto(jetEfficency_4jets_jetpt70_jvf_acc, n_pvtx_4jets_jetpt70_jvf_acc, n_pvtx_eta24);

  DivideHisto(jetEfficency_4jets_jetpt30_mu, mu_4jets_jetpt30, InteractionPerCrossing);
  DivideHisto(jetEfficency_4jets_jetpt40_mu, mu_4jets_jetpt40, InteractionPerCrossing);
  DivideHisto(jetEfficency_4jets_jetpt50_mu, mu_4jets_jetpt50, InteractionPerCrossing);
  DivideHisto(jetEfficency_4jets_jetpt70_mu, mu_4jets_jetpt70, InteractionPerCrossing);

  DivideHisto(jetEfficency_4jets_jetpt30_jvf_acc_mu, mu_4jets_jetpt30_jvf_acc, InteractionPerCrossing_eta24);
  DivideHisto(jetEfficency_4jets_jetpt40_jvf_acc_mu, mu_4jets_jetpt40_jvf_acc, InteractionPerCrossing_eta24);
  DivideHisto(jetEfficency_4jets_jetpt50_jvf_acc_mu, mu_4jets_jetpt50_jvf_acc, InteractionPerCrossing_eta24);
  DivideHisto(jetEfficency_4jets_jetpt70_jvf_acc_mu, mu_4jets_jetpt70_jvf_acc, InteractionPerCrossing_eta24);

  DivideHisto(jetEfficency_5jets_jetpt30, n_pvtx_5jets_jetpt30, n_pvtx_noCut);
  DivideHisto(jetEfficency_5jets_jetpt40, n_pvtx_5jets_jetpt40, n_pvtx_noCut);
  DivideHisto(jetEfficency_5jets_jetpt50, n_pvtx_5jets_jetpt50, n_pvtx_noCut);
  DivideHisto(jetEfficency_5jets_jetpt70, n_pvtx_5jets_jetpt70, n_pvtx_noCut);

  DivideHisto(jetEfficency_5jets_jetpt30_jvf_acc, n_pvtx_5jets_jetpt30_jvf_acc, n_pvtx_eta24);
  DivideHisto(jetEfficency_5jets_jetpt40_jvf_acc, n_pvtx_5jets_jetpt40_jvf_acc, n_pvtx_eta24);
  DivideHisto(jetEfficency_5jets_jetpt50_jvf_acc, n_pvtx_5jets_jetpt50_jvf_acc, n_pvtx_eta24);
  DivideHisto(jetEfficency_5jets_jetpt70_jvf_acc, n_pvtx_5jets_jetpt70_jvf_acc, n_pvtx_eta24);

  DivideHisto(jetEfficency_5jets_jetpt30_mu, mu_5jets_jetpt30, InteractionPerCrossing);
  DivideHisto(jetEfficency_5jets_jetpt40_mu, mu_5jets_jetpt40, InteractionPerCrossing);
  DivideHisto(jetEfficency_5jets_jetpt50_mu, mu_5jets_jetpt50, InteractionPerCrossing);
  DivideHisto(jetEfficency_5jets_jetpt70_mu, mu_5jets_jetpt70, InteractionPerCrossing);

  DivideHisto(jetEfficency_5jets_jetpt30_jvf_acc_mu, mu_5jets_jetpt30_jvf_acc, InteractionPerCrossing_eta24);
  DivideHisto(jetEfficency_5jets_jetpt40_jvf_acc_mu, mu_5jets_jetpt40_jvf_acc, InteractionPerCrossing_eta24);
  DivideHisto(jetEfficency_5jets_jetpt50_jvf_acc_mu, mu_5jets_jetpt50_jvf_acc, InteractionPerCrossing_eta24);
  DivideHisto(jetEfficency_5jets_jetpt70_jvf_acc_mu, mu_5jets_jetpt70_jvf_acc, InteractionPerCrossing_eta24);
}
