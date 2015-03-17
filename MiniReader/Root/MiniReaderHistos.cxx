#include "MiniReader/MiniReaderAlg.h"
#include <math.h>

#define MINETA -5.
#define MAXETA 5.

#define SOME_ENUM(DO)       \
  DO(jetMultiplicity)	    \

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
  DefineHisto(jetMultiplicity, 20, 0, 20);
}

void MiniReaderAlg::FillJets()
{
  // m_HistoContainer[jetMultiplicity]->Fill(m_jet.m_jet_mult);
}
