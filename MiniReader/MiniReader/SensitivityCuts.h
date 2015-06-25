// TMVA include(s):
#include <TMVA/Factory.h>
#include <TMVA/Tools.h>
#include <TMVA/Config.h>

// ROOT include(s):
#include <TFile.h>
#include <TTree.h>
#include <TCut.h>

// STL include(s):
#include <string>
#include <memory>
#include <iostream>

// EDM include(s):
#include "CxxUtils/make_unique.h"

#define PR(x) std::cout << #x << " = " << x << std::endl

class SensitivityCuts {

private:

  std::unique_ptr<TMVA::Factory> m_factory;
  // std::shared_ptr<TMVA::Factory> m_factory;
  // TMVA::Factory *m_factory;
  TFile *m_out_file;

public:

  SensitivityCuts(std::string);
  ~SensitivityCuts();
  void RegisterFactoryVariable(std::string);
  void SetEventWeights(std::string);
  void RunFactory(std::string, std::vector<std::string>);
};
