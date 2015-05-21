#include "MiniReader/SensitivityPlot.h"

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
SensitivityPlot::SensitivityPlot(const std::string &sig_sample, const
                                 std::string &bkg_sample) :
  m_sigE(0), m_bkgE(0)
{
  m_reader = CxxUtils::make_unique<TMVA::Reader>("!Color:!Silent");

  m_sig_file = new TFile(sig_sample.c_str());
  m_bkg_file = new TFile(bkg_sample.c_str());

  if (m_sig_file->IsOpen())

    std::cout << "Opened signal file: " << m_sig_file->GetName() << std::endl;

  if (m_bkg_file->IsOpen())

    std::cout << "Opened Background file: " << m_bkg_file->GetName() << std::endl;

  m_sig_tree = static_cast<TTree *>(m_sig_file->Get("SensTree"));
  m_bkg_tree = static_cast<TTree *>(m_bkg_file->Get("SensTree"));

  EtMiss_cutsMin.reserve(100);

  m_tree_var.reserve(10);

  m_effS_vec.reserve(100);
  m_effB_vec.reserve(100);

  m_sig_events.reserve(100);
  m_bkg_events.reserve(100);

  m_sensitivity.reserve(100);
}

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
void SensitivityPlot::RegisterToReader(const std::string &tree_name)
{
  float var1 = 0;

  m_tree_var.push_back(var1);

  m_reader->AddVariable(tree_name.c_str(), &var1);
}

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
void SensitivityPlot::RegisterMVA(const std::string &dir, const std::string &prefix,
                                  const std::string &method)
{
  std::string weightfile = dir + prefix + "_CutsGA.weights.xml";

  m_reader->BookMVA(method.c_str(), weightfile.c_str());
}

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
void SensitivityPlot::SetSigBkgEvent()
{
  TH1F *h0 = new TH1F("h0", "h0", 100, 0, 20000000);
  TH1F *h1 = new TH1F("h1", "h1", 100, 0, 20000000);

  m_sig_tree->Project("h0", "jet1_pt", "event_weight");
  m_bkg_tree->Project("h1", "jet1_pt", "event_weight");

  m_sigE = h0->Integral();
  m_bkgE = h1->Integral();
  // m_sigE = m_sig_tree->GetEntries("jet1_pt*event_weight");
  // m_bkgE = m_bkg_tree->GetEntries("jet1_pt*event_weight");
}

void SensitivityPlot::CalcMethodEffForEff(float effS)
{

}

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
void SensitivityPlot::PrintCuts()
{
  // test: retrieve cuts for particular signal efficiency
  // CINT ignores dynamic_casts so we have to use a cuts-secific Reader function
  // to acces the pointer:
  TMVA::MethodCuts *mcuts = m_reader->FindCutsMVA("CutsGA") ;

  if (mcuts) {

    std::vector<double> cutsMin;
    std::vector<double> cutsMax;

    for (float i = 0.01; i < 1.; i += 0.01) {

      mcuts->GetCuts(i, cutsMin, cutsMax);

      if(cutsMin[0] != 0)

	EtMiss_cutsMin.push_back(cutsMin[0]);

      std::cout << "--- ------------------------------------------------------\n";
      std::cout << "--- Retrieve cut values for signal efficiency of " << i <<
                " from Reader\n";

      for (uint i = 0; i < cutsMin.size(); ++i) {

        std::cout << "... Cut: "
                  << cutsMin[i]
                  << " < \""
                  << mcuts->GetInputVar(i)
                  << "\" <= "
                  << cutsMax[i] << std::endl;
      }

      std::cout << "--- ------------------------------------------------------\n";
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
void SensitivityPlot::PrintCutsAtMaximum(double max_pos)
{
  TMVA::MethodCuts *mcuts = m_reader->FindCutsMVA("CutsGA") ;

  if (mcuts) {

    std::vector<double> cutsMin;
    std::vector<double> cutsMax;

    mcuts->GetCuts(max_pos, cutsMin, cutsMax);

    std::cout << "--- ------------------------------------------------------\n";
    std::cout << "--- Retrieve cut values for max signal efficiency of " <<
      max_pos << " from Reader\n";

    for (uint i = 0; i < cutsMin.size(); ++i) {

      std::cout << "... Cut: "
		<< cutsMin[i]
		<< " < \""
		<< mcuts->GetInputVar(i)
		<< "\" <= "
		<< cutsMax[i] << std::endl;
    }

    std::cout << "--- ------------------------------------------------------\n";
  }
}

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
TGraph SensitivityPlot::SistParam()
{
  int n = 3;

  std::array<double, 3> x, y;

  std::vector<double> cuts_copy = EtMiss_cutsMin;

  std::sort(std::begin(cuts_copy), std::end(cuts_copy), std::greater<double>());

  int mid_point = EtMiss_cutsMin.size() / 2;

  PR(cuts_copy.size());
  PR(cuts_copy.back());

  PR(cuts_copy[0]);
  PR(cuts_copy[mid_point]);
  PR(cuts_copy[cuts_copy.size()]);

  x[0] = cuts_copy[0];
  x[1] = cuts_copy[mid_point];
  x[2] = cuts_copy[cuts_copy.size()];

  y[2] = .025;
  y[1] = .035;
  y[0] = .075;

  TCanvas c1;

  TGraph gr(n, &x[0], &y[0]);

  gr.Fit("pol2");

  gr.Draw("AP");

  c1.Print("graph.pdf");

  return gr;
}

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
double SensitivityPlot::GetSistFromParam(double EtMissValue)
{
  TGraph gr = SistParam();

  TF1 *fit_func = static_cast<TF1 *>(gr.FindObject("pol2"));

  return fit_func->Eval(EtMissValue);
}

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
void SensitivityPlot::GetEfficiencyPerBin()
{
  TFile *file = new TFile("TMVASensitivityCuts.root");

  if (file->IsOpen())

    std::cout << "Opened file: " << file->GetName() << std::endl;

  // This is hard coded for now:
  std::string path = "Method_Cuts/CutsGA/";

  std::string effS_histo = path + "MVA_CutsGA_effS";
  std::string effB_histo = path + "MVA_CutsGA_effB";

  TH1F *h0 = static_cast<TH1F *>(file->Get(effS_histo.c_str()));
  TH1F *h1 = static_cast<TH1F *>(file->Get(effB_histo.c_str()));

  for (int i = 0; i < h0->GetNbinsX(); ++i)

    m_effS_vec.push_back(h0->GetBinContent(i));

  for (int i = 0; i < h0->GetNbinsX(); ++i)

    m_effB_vec.push_back(h1->GetBinContent(i));
}

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
void SensitivityPlot::SetTotalSigEvents()
{
  // std::transform(std::begin(m_effS_vec), std::end(m_effS_vec), std::begin(m_sig_events),
  //     std::bind1st(std::multiplies<double>(), m_sigE));

  for (size_t i = 0; i < m_effS_vec.size(); ++i)

    m_sig_events.push_back(m_effS_vec[i] * m_sigE);
}

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
void SensitivityPlot::SetTotalBkgEvents()
{
  // std::transform(std::begin(m_effB_vec), std::end(m_effB_vec), std::begin(m_bkg_events),
  //     std::bind1st(std::multiplies<double>(), m_bkgE));

  for (size_t i = 0; i < m_effB_vec.size(); ++i)

    m_bkg_events.push_back(m_effB_vec[i] * m_bkgE);
}

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
void SensitivityPlot::CalculateSensitivity()
{
  PR(GetSistFromParam(EtMiss_cutsMin[0]));

  for (size_t i = 0; i < m_sig_events.size(); ++i) {

    double bkg_err = GetSistFromParam(EtMiss_cutsMin[i]);

    m_sensitivity.push_back(m_sig_events[i] /
                            std::sqrt(m_bkg_events[i] +
                                      std::pow(bkg_err * m_bkg_events[i], 2)));
  }
}

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
void SensitivityPlot::DoSensitivityPlot()
{
  SetSigBkgEvent();
  GetEfficiencyPerBin();
  SetTotalSigEvents();
  SetTotalBkgEvents();

  CalculateSensitivity();

  TCanvas c1;

  TH1F *h0 = new TH1F("h0", "h0", 100, 0, 1);

  for (size_t i = 0; i < m_sensitivity.size(); ++i)

    // check for nan entries:
    if (m_sensitivity[i] != m_sensitivity[i])

      h0->SetBinContent(i, 0.);

    else

      h0->SetBinContent(i, m_sensitivity[i]);

  h0->Draw();

  c1.Print("sensitivity.pdf");

  SistParam();

  int bin_max = h0->GetMaximumBin();
  double max_eff = h0->GetXaxis()->GetBinCenter(bin_max);

  PrintCutsAtMaximum(max_eff);
  PR(m_sigE);
  PR(m_bkgE);
}
