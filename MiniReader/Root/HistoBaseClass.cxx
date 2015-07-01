#include "MiniReader/HistoBaseClass.h"

////////////////////////////////////////////////////////////////////////////////
//// Default constructor of the class
////////////////////////////////////////////////////////////////////////////////
HistoBaseClass::HistoBaseClass()
{
  m_region = {"SR_"};
  m_suffix = {"_M0"};
}

////////////////////////////////////////////////////////////////////////////////
//// Define histograms.
////
//// Will define the histograms and store them in maps.
////////////////////////////////////////////////////////////////////////////////
void HistoBaseClass::DefineHisto(const std::string &name, int nbin, float x_low,
				 float x_max)
{
  for(size_t i = 0; i < m_region.size(); ++i) {
    for(size_t j = 0; j < m_suffix.size(); ++j) {

      std::string histo_name = m_region[i] + name + m_suffix[j];

      TH1F *temp_pointer = new TH1F(histo_name.c_str(), histo_name.c_str(),
				    nbin, x_low, x_max);

      TH1::SetDefaultSumw2(true);

      m_HistoContainerMap[histo_name] = temp_pointer;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
//// Return the histogram vector container
////////////////////////////////////////////////////////////////////////////////
const std::map<std::string, TH1 *> HistoBaseClass::GetHistoMap() const
{
  return m_HistoContainerMap;
}
