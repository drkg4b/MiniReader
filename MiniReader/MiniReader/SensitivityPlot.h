#ifndef MINIREADER_SENSITIVITYPLOT_H
#define MINIREADER_SENSITIVITYPLOT_H

// TMVA include(s):
#include "TMVA/Reader.h"
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/MethodCuts.h"

// STL include(s):
#include <functional>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <math.h>
#include <array>
#include <map>

// ROOT include(s):
#include <TCanvas.h>
#include <TFile.h>
#include <TGraphErrors.h>
#include <TTree.h>
#include <TH1F.h>
#include <TF1.h>

// EDM include(s):
#include "CxxUtils/make_unique.h"

#define PR(x) std::cout << #x << " = " << x << std::endl

class SensitivityPlot {

 private:

  std::unique_ptr<TMVA::Reader> m_reader;

  TFile *m_sig_file;
  TFile *m_bkg_file;

  TTree *m_sig_tree;
  TTree *m_bkg_tree;

  unsigned long m_sigE;
  unsigned long m_bkgE;

  std::vector<double> EtMiss_cutsMin;

  std::vector<float> m_tree_var;

  std::vector<double> m_effS_vec;
  std::vector<double> m_effB_vec;

  std::vector<double> m_sig_events;
  std::vector<double> m_bkg_events;

  std::vector<double> m_sensitivity;

  void SetSigBkgEvent();
  void SetTotalSigEvents();
  void SetTotalBkgEvents();
  void GetEfficiencyPerBin();
  TGraph SistParam();
  double GetSistFromParam(double);
  void PrintCutsAtMaximum(double);

 public:

  SensitivityPlot(const std::string &, const std::string &);
  void RegisterToReader(const std::string &);
  void RegisterMVA(const std::string &, const std::string &, const std::string &);

  template <typename T>
    void PrepareTree(const std::string &var_name, T &var)
    {
      m_sig_tree->SetBranchAddress(var_name.c_str(), &var);
    }

  void CalcMethodEffForEff(float);
  void PrintCuts();
  void CalculateSensitivity();
  void DoSensitivityPlot();
};

#endif // MINIREADER_SENSITIVITYPLOT_H
