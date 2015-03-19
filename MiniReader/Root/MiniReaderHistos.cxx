#include "MiniReader/MiniReaderAlg.h"
#include <math.h>

#define MINETA -5.
#define MAXETA 5.

#define SOME_ENUM(DO)  	      	\
  DO(InteractionPerCrossing)   	\
  DO(jetMultiplicity)  	       	\
  DO(jetEfficency)     	       	\

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
  DefineHisto(jetMultiplicity, 20, 0, 100);
  DefineHisto(jetEfficency, 20, 0, 40);
}

void MiniReaderAlg::FillJets()
{
  m_HistoContainer[jetMultiplicity]->Fill(m_jet.m_jet_mult);
}

void MiniReaderAlg::FillEventInfo()
{
  m_HistoContainer[InteractionPerCrossing]->Fill(m_runp.m_actualInteractionsPerCrossing);
}

void MiniReaderAlg::PlotJetEfficency()
{
  m_HistoContainer[jetEfficency]->Divide(m_HistoContainer[InteractionPerCrossing],
					 m_HistoContainer[InteractionPerCrossing]);
}
