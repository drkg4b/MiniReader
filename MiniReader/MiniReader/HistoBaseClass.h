#ifndef MINIREADER_MINIREADERHISTOBASECLASS_H
#define MINIREADER_MINIREADERHISTOBASECLASS_H

// SDL include(s):
#include <vector>
#include <string>
#include <map>

// ROOT include(s):
#include <TH1.h>

class HistoBaseClass {

 protected:

  std::map<std::string, TH1 *> m_HistoContainerMap;

  std::vector<std::string> m_region;
  std::vector<std::string> m_suffix;

 public:

  HistoBaseClass();

  void DefineHisto(const std::string &, int, float, float);

  const std::map<std::string, TH1 *> GetHistoMap() const;
};

#endif // MINIREADER_MINIREADERHISTOBASECLASS_H
