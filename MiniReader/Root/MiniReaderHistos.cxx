#include "MiniReader/MiniReaderAlg.h"
#include <math.h>

#define MINETA -5.
#define MAXETA 5.

#define SOME_ENUM(DO)  	      	\
  DO(InteractionPerCrossing)   	\
  DO(jetMultiplicityNoCut)	\
  DO(n_pvtx_noCut)		\
  DO(n_pvtx_3jets)		\
  DO(n_pvtx_3jets_jetpt30)	\
  DO(n_pvtx_3jets_jetpt40)	\
  DO(n_pvtx_3jets_jetpt50)	\
  DO(n_pvtx_4jets)              \
  DO(n_pvtx_4jets_jetpt30)	\
  DO(n_pvtx_4jets_jetpt40)	\
  DO(n_pvtx_4jets_jetpt50)	\
  DO(n_pvtx_5jets)		\
  DO(n_pvtx_5jets_jetpt30)	\
  DO(n_pvtx_5jets_jetpt40)	\
  DO(n_pvtx_5jets_jetpt50)	\
  DO(jetEfficency_3jets)	\
  DO(jetEfficency_3jets_jetpt30)\
  DO(jetEfficency_3jets_jetpt40)\
  DO(jetEfficency_3jets_jetpt50)\
  DO(jetEfficency_4jets)	\
  DO(jetEfficency_4jets_jetpt30)\
  DO(jetEfficency_4jets_jetpt40)\
  DO(jetEfficency_4jets_jetpt50)\
  DO(jetEfficency_5jets)	\
  DO(jetEfficency_5jets_jetpt30)\
  DO(jetEfficency_5jets_jetpt40)\
  DO(jetEfficency_5jets_jetpt50)\


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

  m_HistoContainer.push_back(temp_pointer);
  wk()->addOutput(temp_pointer);
}

void MiniReaderAlg::InitHisto()
{
  // Jet Histos:
  DefineHisto(InteractionPerCrossing, 20, 0, 40);
  DefineHisto(jetMultiplicityNoCut, 20, 0, 100);

  DefineHisto(n_pvtx_noCut, 40, 0, 80);

  DefineHisto(n_pvtx_3jets, 40, 0, 80);
  DefineHisto(n_pvtx_3jets_jetpt30, 40, 0, 80);
  DefineHisto(n_pvtx_3jets_jetpt40, 40, 0, 80);
  DefineHisto(n_pvtx_3jets_jetpt50, 40, 0, 80);

  DefineHisto(n_pvtx_4jets, 40, 0, 80);
  DefineHisto(n_pvtx_4jets_jetpt30, 40, 0, 80);
  DefineHisto(n_pvtx_4jets_jetpt40, 40, 0, 80);
  DefineHisto(n_pvtx_4jets_jetpt50, 40, 0, 80);

  DefineHisto(n_pvtx_5jets, 40, 0, 80);
  DefineHisto(n_pvtx_5jets_jetpt30, 40, 0, 80);
  DefineHisto(n_pvtx_5jets_jetpt40, 40, 0, 80);
  DefineHisto(n_pvtx_5jets_jetpt50, 40, 0, 80);

  DefineHisto(jetEfficency_3jets, 40, 0, 80);
  DefineHisto(jetEfficency_3jets_jetpt30, 40, 0, 80);
  DefineHisto(jetEfficency_3jets_jetpt40, 40, 0, 80);
  DefineHisto(jetEfficency_3jets_jetpt50, 40, 0, 80);

  DefineHisto(jetEfficency_4jets, 40, 0, 80);
  DefineHisto(jetEfficency_4jets_jetpt30, 40, 0, 80);
  DefineHisto(jetEfficency_4jets_jetpt40, 40, 0, 80);
  DefineHisto(jetEfficency_4jets_jetpt50, 40, 0, 80);

  DefineHisto(jetEfficency_5jets, 40, 0, 80);
  DefineHisto(jetEfficency_5jets_jetpt30, 40, 0, 80);
  DefineHisto(jetEfficency_5jets_jetpt40, 40, 0, 80);
  DefineHisto(jetEfficency_5jets_jetpt50, 40, 0, 80);
}

void MiniReaderAlg::FillJets()
{
  m_HistoContainer[jetMultiplicityNoCut]->Fill(m_jet.m_jet_mult);
  m_HistoContainer[n_pvtx_noCut]->Fill(m_pvtx.m_pvtx_n);

  if(m_jet.m_jet_mult == 3) {

    m_HistoContainer[n_pvtx_3jets]->Fill(m_pvtx.m_pvtx_n);

    if(m_jet.m_jet_pt->at(0) >= 30000 && m_jet.m_jet_pt->at(0) < 40000)

      m_HistoContainer[n_pvtx_3jets_jetpt30]->Fill(m_pvtx.m_pvtx_n);

    if(m_jet.m_jet_pt->at(0) >= 40000 && m_jet.m_jet_pt->at(0) < 50000)

      m_HistoContainer[n_pvtx_3jets_jetpt40]->Fill(m_pvtx.m_pvtx_n);

    if(m_jet.m_jet_pt->at(0) >= 50000)

      m_HistoContainer[n_pvtx_3jets_jetpt50]->Fill(m_pvtx.m_pvtx_n);
  }


  if(m_jet.m_jet_mult == 4) {

    m_HistoContainer[n_pvtx_4jets]->Fill(m_pvtx.m_pvtx_n);

    if(m_jet.m_jet_pt->at(0) >= 30000 && m_jet.m_jet_pt->at(0) < 40000)

      m_HistoContainer[n_pvtx_4jets_jetpt30]->Fill(m_pvtx.m_pvtx_n);

    if(m_jet.m_jet_pt->at(0) >= 40000 && m_jet.m_jet_pt->at(0) < 50000)

      m_HistoContainer[n_pvtx_4jets_jetpt40]->Fill(m_pvtx.m_pvtx_n);

    if(m_jet.m_jet_pt->at(0) >= 50000)

      m_HistoContainer[n_pvtx_4jets_jetpt50]->Fill(m_pvtx.m_pvtx_n);
}

  if(m_jet.m_jet_mult == 5) {

    m_HistoContainer[n_pvtx_5jets]->Fill(m_pvtx.m_pvtx_n);

    if(m_jet.m_jet_pt->at(0) >= 30000 && m_jet.m_jet_pt->at(0) < 40000)

      m_HistoContainer[n_pvtx_5jets_jetpt30]->Fill(m_pvtx.m_pvtx_n);

    if(m_jet.m_jet_pt->at(0) >= 40000 && m_jet.m_jet_pt->at(0) < 50000)

      m_HistoContainer[n_pvtx_5jets_jetpt40]->Fill(m_pvtx.m_pvtx_n);

    if(m_jet.m_jet_pt->at(0) >= 50000)

      m_HistoContainer[n_pvtx_5jets_jetpt50]->Fill(m_pvtx.m_pvtx_n);
  }
}

void MiniReaderAlg::FillEventInfo()
{
  m_HistoContainer[InteractionPerCrossing]->Fill(m_info.m_actualInteractionsPerCrossing);
}

void MiniReaderAlg::PlotJetEfficency()
{
  m_HistoContainer[jetEfficency_3jets]->Divide(m_HistoContainer[n_pvtx_3jets],
					       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_3jets_jetpt30]->Divide(m_HistoContainer[n_pvtx_3jets_jetpt30],
						       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_3jets_jetpt40]->Divide(m_HistoContainer[n_pvtx_3jets_jetpt40],
						       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_3jets_jetpt50]->Divide(m_HistoContainer[n_pvtx_3jets_jetpt50],
						       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_4jets]->Divide(m_HistoContainer[n_pvtx_4jets],
					       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_4jets_jetpt30]->Divide(m_HistoContainer[n_pvtx_4jets_jetpt30],
						       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_4jets_jetpt40]->Divide(m_HistoContainer[n_pvtx_4jets_jetpt40],
						       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_4jets_jetpt50]->Divide(m_HistoContainer[n_pvtx_4jets_jetpt50],
						       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_5jets]->Divide(m_HistoContainer[n_pvtx_5jets],
					       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_5jets_jetpt30]->Divide(m_HistoContainer[n_pvtx_5jets_jetpt30],
						       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_5jets_jetpt40]->Divide(m_HistoContainer[n_pvtx_5jets_jetpt40],
						       m_HistoContainer[n_pvtx_noCut]);

  m_HistoContainer[jetEfficency_5jets_jetpt50]->Divide(m_HistoContainer[n_pvtx_5jets_jetpt50],
						       m_HistoContainer[n_pvtx_noCut]);

}
