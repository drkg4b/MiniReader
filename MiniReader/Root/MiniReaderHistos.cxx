#include "MiniReader/MiniReaderAlg.h"
#include <math.h>

static constexpr const float MINETA = -5.;
static constexpr const float MAXETA = 5.;

#define SOME_ENUM(DO)		\
  DO(EtMissMuVeto)		\
  DO(InteractionPerCrossing)    \
  DO(jetMultiplicityNoCut)	\
  DO(n_pvtx_noCut)		\
  DO(n_pvtx_3jets_jetpt30)	\
  DO(n_pvtx_3jets_jetpt40)	\
  DO(n_pvtx_3jets_jetpt50)	\
  DO(n_pvtx_3jets_jetpt70)	\
  DO(n_pvtx_4jets_jetpt30)	\
  DO(n_pvtx_4jets_jetpt40)	\
  DO(n_pvtx_4jets_jetpt50)	\
  DO(n_pvtx_4jets_jetpt70)	\
  DO(n_pvtx_5jets_jetpt30)	\
  DO(n_pvtx_5jets_jetpt40)	\
  DO(n_pvtx_5jets_jetpt50)	\
  DO(n_pvtx_5jets_jetpt70)	\
  DO(jetEfficency_3jets_jetpt30)\
  DO(jetEfficency_3jets_jetpt40)\
  DO(jetEfficency_3jets_jetpt50)\
  DO(jetEfficency_3jets_jetpt70)\
  DO(jetEfficency_4jets_jetpt30)\
  DO(jetEfficency_4jets_jetpt40)\
  DO(jetEfficency_4jets_jetpt50)\
  DO(jetEfficency_4jets_jetpt70)\
  DO(jetEfficency_5jets_jetpt30)\
  DO(jetEfficency_5jets_jetpt40)\
  DO(jetEfficency_5jets_jetpt50)\
  DO(jetEfficency_5jets_jetpt70)\


#define MAKE_ENUM(VAR) VAR,
enum HistoNames {
  SOME_ENUM(MAKE_ENUM)
};

#define MAKE_STRINGS(VAR) #VAR,
const char *const HistoNamesString[] = {
  SOME_ENUM(MAKE_STRINGS)
};


void MiniReaderAlg::DefineHisto(int name, int nbin, float x_low, float x_max)
{
  TH1F *temp_pointer = new TH1F(HistoNamesString[name],
                                HistoNamesString[name], nbin, x_low, x_max);

  TH1::SetDefaultSumw2(true);

  m_HistoContainer.push_back(temp_pointer);
  wk()->addOutput(temp_pointer);
}

void MiniReaderAlg::InitHisto()
{
  // MET Histos:
  DefineHisto(EtMissMuVeto, 100, 0, 1100);

  // Jet Histos:
  DefineHisto(InteractionPerCrossing, 60, 0, 40);
  DefineHisto(jetMultiplicityNoCut, 20, 0, 100);

  DefineHisto(n_pvtx_noCut, 40, 0, 80);

  DefineHisto(n_pvtx_3jets_jetpt30, 40, 0, 80);
  DefineHisto(n_pvtx_3jets_jetpt40, 40, 0, 80);
  DefineHisto(n_pvtx_3jets_jetpt50, 40, 0, 80);
  DefineHisto(n_pvtx_3jets_jetpt70, 40, 0, 80);

  DefineHisto(n_pvtx_4jets_jetpt30, 40, 0, 80);
  DefineHisto(n_pvtx_4jets_jetpt40, 40, 0, 80);
  DefineHisto(n_pvtx_4jets_jetpt50, 40, 0, 80);
  DefineHisto(n_pvtx_4jets_jetpt70, 40, 0, 80);

  DefineHisto(n_pvtx_5jets_jetpt30, 40, 0, 80);
  DefineHisto(n_pvtx_5jets_jetpt40, 40, 0, 80);
  DefineHisto(n_pvtx_5jets_jetpt50, 40, 0, 80);
  DefineHisto(n_pvtx_5jets_jetpt70, 40, 0, 80);

  DefineHisto(jetEfficency_3jets_jetpt30, 40, 0, 80);
  DefineHisto(jetEfficency_3jets_jetpt40, 40, 0, 80);
  DefineHisto(jetEfficency_3jets_jetpt50, 40, 0, 80);
  DefineHisto(jetEfficency_3jets_jetpt70, 40, 0, 80);

  DefineHisto(jetEfficency_4jets_jetpt30, 40, 0, 80);
  DefineHisto(jetEfficency_4jets_jetpt40, 40, 0, 80);
  DefineHisto(jetEfficency_4jets_jetpt50, 40, 0, 80);
  DefineHisto(jetEfficency_4jets_jetpt70, 40, 0, 80);

  DefineHisto(jetEfficency_5jets_jetpt30, 40, 0, 80);
  DefineHisto(jetEfficency_5jets_jetpt40, 40, 0, 80);
  DefineHisto(jetEfficency_5jets_jetpt50, 40, 0, 80);
  DefineHisto(jetEfficency_5jets_jetpt70, 40, 0, 80);
}

void MiniReaderAlg::FillMET(double weight)
{
  m_HistoContainer[EtMissMuVeto]->Fill(toGeV(m_met.m_EtMissMuVeto), weight);
}

void MiniReaderAlg::FillJets(double weight)
{
  m_HistoContainer[jetMultiplicityNoCut]->Fill(m_jet.m_jet_mult, weight);
  m_HistoContainer[n_pvtx_noCut]->Fill(m_pvtx.m_pvtx_n, weight);

  // Event survives if at most 3 jets or if there are more than 3 jets but the
  // pt of the third is less than some threshold (Mind the vector counting start
  // from 0):
  if (m_jet.m_jet_mult < 4 || (m_jet.m_jet_mult > 2 && m_jet.m_jet_pt->at(2) < 30000))

    m_HistoContainer[n_pvtx_3jets_jetpt30]->Fill(m_pvtx.m_pvtx_n, weight);

  if (m_jet.m_jet_mult < 4 || (m_jet.m_jet_mult > 2 && m_jet.m_jet_pt->at(2) < 40000))

    m_HistoContainer[n_pvtx_3jets_jetpt40]->Fill(m_pvtx.m_pvtx_n, weight);

  if (m_jet.m_jet_mult < 4 || (m_jet.m_jet_mult > 2 && m_jet.m_jet_pt->at(2) < 50000))

    m_HistoContainer[n_pvtx_3jets_jetpt50]->Fill(m_pvtx.m_pvtx_n, weight);

  if (m_jet.m_jet_mult < 4 || (m_jet.m_jet_mult > 2 && m_jet.m_jet_pt->at(2) < 70000))

    m_HistoContainer[n_pvtx_3jets_jetpt70]->Fill(m_pvtx.m_pvtx_n, weight);

  // Event survives if at most 4 jets or if there are more than 4 jets but the
  // pt of the fourth is less than some threshold (Mind the vector counting start
  // from 0):
  if (m_jet.m_jet_mult < 5 || (m_jet.m_jet_mult > 3 && m_jet.m_jet_pt->at(3) < 30000))

    m_HistoContainer[n_pvtx_4jets_jetpt30]->Fill(m_pvtx.m_pvtx_n, weight);

  if (m_jet.m_jet_mult < 5 || (m_jet.m_jet_mult > 3 && m_jet.m_jet_pt->at(3) < 40000))

    m_HistoContainer[n_pvtx_4jets_jetpt40]->Fill(m_pvtx.m_pvtx_n, weight);

  if (m_jet.m_jet_mult < 5 || (m_jet.m_jet_mult > 3 && m_jet.m_jet_pt->at(3) < 50000))

    m_HistoContainer[n_pvtx_4jets_jetpt50]->Fill(m_pvtx.m_pvtx_n, weight);

  if (m_jet.m_jet_mult < 5 || (m_jet.m_jet_mult > 3 && m_jet.m_jet_pt->at(3) < 70000))

    m_HistoContainer[n_pvtx_4jets_jetpt70]->Fill(m_pvtx.m_pvtx_n, weight);

  // Event survives if at most 4 jets or if there are more than 4 jets but the
  // pt of the fourth is less than some threshold (Mind the vector counting start
  // from 0):
  if (m_jet.m_jet_mult < 6 || (m_jet.m_jet_mult > 4 && m_jet.m_jet_pt->at(4) < 30000))

    m_HistoContainer[n_pvtx_5jets_jetpt30]->Fill(m_pvtx.m_pvtx_n, weight);

  if (m_jet.m_jet_mult < 6 || (m_jet.m_jet_mult > 4 && m_jet.m_jet_pt->at(4) < 40000))

    m_HistoContainer[n_pvtx_5jets_jetpt40]->Fill(m_pvtx.m_pvtx_n, weight);

  if (m_jet.m_jet_mult < 6 || (m_jet.m_jet_mult > 4 && m_jet.m_jet_pt->at(4) < 50000))

    m_HistoContainer[n_pvtx_5jets_jetpt50]->Fill(m_pvtx.m_pvtx_n, weight);

  if (m_jet.m_jet_mult < 6 || (m_jet.m_jet_mult > 4 && m_jet.m_jet_pt->at(4) < 70000))

    m_HistoContainer[n_pvtx_5jets_jetpt70]->Fill(m_pvtx.m_pvtx_n, weight);
}

void MiniReaderAlg::FillEventInfo(double weight)
{
  m_HistoContainer[InteractionPerCrossing]->Fill(m_info.m_actualInteractionsPerCrossing,
      weight);
}

void MiniReaderAlg::PlotJetEfficency()
{
  m_HistoContainer[jetEfficency_3jets_jetpt30]->Divide(m_HistoContainer[n_pvtx_3jets_jetpt30],
						       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_3jets_jetpt40]->Divide(m_HistoContainer[n_pvtx_3jets_jetpt40],
						       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_3jets_jetpt50]->Divide(m_HistoContainer[n_pvtx_3jets_jetpt50],
						       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_3jets_jetpt70]->Divide(m_HistoContainer[n_pvtx_3jets_jetpt70],
						       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_4jets_jetpt30]->Divide(m_HistoContainer[n_pvtx_4jets_jetpt30],
						       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_4jets_jetpt40]->Divide(m_HistoContainer[n_pvtx_4jets_jetpt40],
						       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_4jets_jetpt50]->Divide(m_HistoContainer[n_pvtx_4jets_jetpt50],
						       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_4jets_jetpt70]->Divide(m_HistoContainer[n_pvtx_4jets_jetpt70],
						       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_5jets_jetpt30]->Divide(m_HistoContainer[n_pvtx_5jets_jetpt30],
						       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_5jets_jetpt40]->Divide(m_HistoContainer[n_pvtx_5jets_jetpt40],
						       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_5jets_jetpt50]->Divide(m_HistoContainer[n_pvtx_5jets_jetpt50],
						       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_5jets_jetpt70]->Divide(m_HistoContainer[n_pvtx_5jets_jetpt70],
						       m_HistoContainer[n_pvtx_noCut]);
}
