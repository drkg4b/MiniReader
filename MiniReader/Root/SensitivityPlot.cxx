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

  m_bin_error.reserve(100);
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

    for (size_t i = 0; i < m_effS_vec.size(); ++i) {

      mcuts->GetCuts(m_effS_vec[i], cutsMin, cutsMax);

      PR(cutsMin[0]);

      if (cutsMin[0] != 0)

        EtMiss_cutsMin.push_back(cutsMin[0]);

      std::cout << "--- ------------------------------------------------------\n";
      std::cout << "--- Retrieve cut values for signal efficiency of " << m_effS_vec[i] <<
                " from Reader\n";

      for (uint j = 0; j < cutsMin.size(); ++j) {

        std::cout << "... Cut: "
                  << cutsMin[j]
                  << " < \""
                  << mcuts->GetInputVar(j)
                  << "\" <= "
                  << cutsMax[j] << std::endl;
      }

      std::cout << "--- ------------------------------------------------------\n";
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
void SensitivityPlot::WriteCutsToFile(double max_pos, const std::string
				      &sig_name, const std::string &use_var)
{
  TMVA::MethodCuts *mcuts = m_reader->FindCutsMVA("CutsGA");

  std::string file_name = sig_name + use_var + "_cuts.log";

  std::ofstream out_file(file_name, std::ios::out);

  if(out_file.is_open())
    PR(file_name);

  if (mcuts) {

    std::vector<double> cutsMin;
    std::vector<double> cutsMax;

    for (size_t i = 0; i < m_effS_vec.size(); ++i) {

      mcuts->GetCuts(m_effS_vec[i], cutsMin, cutsMax);

      // cannot comapre float need to use this hack:
      if(std::fabs(m_effS_vec[i] - max_pos) < .0001)

	out_file << "!";

      if(i != 0)

	out_file << m_effS_vec[i];

      for (uint j = 0; j < cutsMin.size(); ++j) {

	if(i == 0 && j == 0)

	  out_file << "eff" << std::setw(15) <<
	    mcuts->GetInputVar(0) << ">" << std::setw(15) <<
	    mcuts->GetInputVar(0) << "<=" << std::setw(15) <<
	    mcuts->GetInputVar(1) << ">" << std::setw(15) <<
	    mcuts->GetInputVar(1) << "<=" << std::setw(15) <<
	    mcuts->GetInputVar(2) << ">" << std::setw(15) <<
	    mcuts->GetInputVar(2) << "<=" << std::setw(15) <<  "\n" << i;

	out_file << std::setw(15) << cutsMin[j] << std::setw(15) <<
	  cutsMax[j];
      }

      out_file << "\n";
    }
  }

  out_file.close();
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
  int n = 7;

  std::array<double, 7> x, y;

  x[0] = 250000;
  x[1] = 300000;
  x[2] = 350000;
  x[3] = 400000;
  x[4] = 450000;
  x[5] = 600000;
  x[6] = 700000;

  y[0] = .0264;
  y[1] = .0282;
  y[2] = .0328;
  y[3] = .0344;
  y[4] = .0375;
  y[5] = .0576;
  y[6] = .0822;

  TCanvas c1;

  TGraph gr(n, &x[0], &y[0]);

  gr.Fit("pol2", "q");

  // gr.SetTitle("");
  // gr.GetXaxis()->SetTitle("#slash{E}_{T}");
  // gr.GetYaxis()->SetTitle("#sigma");

  // gr.Draw("AP");

  // c1.Print("graph.pdf");

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
void SensitivityPlot::GetEfficiencyPerBin(std::string sig_var)
{
  std::string open_file = "TMVASensitivityCuts_" + sig_var +  ".root";

  TFile *file = new TFile(open_file.c_str());

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
  for (size_t i = 0; i < m_sig_events.size(); ++i) {

    double bkg_err = GetSistFromParam(EtMiss_cutsMin[i]);

    std::cout << "EtMiss_cutsMin = " << EtMiss_cutsMin[i] << "\tbkg_err = " <<
      bkg_err << "\tm_sig_events[i] = " << m_sig_events[i] << "\tm_bkg_events[i] = "
	      << m_bkg_events[i] << std::endl;

    m_sensitivity.push_back(m_sig_events[i] /
                            std::sqrt(m_bkg_events[i] +
                                      std::pow(bkg_err * m_bkg_events[i], 2)));
  }
}

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
void SensitivityPlot::CalculateBinError()
{
  std::vector<double> first_term;
  std::vector<double> second_term;
  std::vector<double> bkg_err;
  std::vector<double> sig_err;

  m_sig_tree->Draw("event_weight");

  TH1F *htemp = (TH1F *)gPad->GetPrimitive("htemp");

  double sig_weight_mean = htemp->GetMean();
  long sig_entries = htemp->GetEntries();

  m_bkg_tree->Draw("event_weight");

  htemp = (TH1F *)gPad->GetPrimitive("htemp");

  double bkg_weight_mean = htemp->GetMean();
  long bkg_entries = htemp->GetEntries();

  for (size_t i = 0; i < m_sig_events.size(); ++i) {

    double bkg_rel_err = GetSistFromParam(EtMiss_cutsMin[i]);

    bkg_err.push_back(bkg_weight_mean * std::sqrt(bkg_entries * m_effB_vec[i] *
                      (1 - m_effB_vec[i])));

    sig_err.push_back(sig_weight_mean * std::sqrt(sig_entries * m_effS_vec[i] *
                      (1 - m_effS_vec[i])));

    first_term .push_back(std::pow(bkg_err[i] / std::sqrt(m_bkg_events[i] +
                                   std::pow(bkg_rel_err *
                                            m_bkg_events[i], 2)), 2));

    second_term .push_back(std::pow(sig_err[i] * m_sig_events[i] *
                                    (1 + std::pow(bkg_rel_err, 2) * m_bkg_events[i])
                                    / (2 * std::pow(m_bkg_events[i] +
                                        std::pow(bkg_rel_err *
                                            m_bkg_events[i], 2), 1.5)), 2));

    m_bin_error.push_back(std::sqrt(first_term[i] + second_term[i]));
  }
}

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
void SensitivityPlot::DoSensitivityPlot(const std::string &out_dir, const std::string
					&sig_name, const std::string &use_var)
{
  SetAtlasStyle();

  std::string out_name = out_dir + sig_name + use_var;

  TCanvas c1;

  TH1F *h0 = new TH1F("h0", "h0", 100, 0, 1);

  for (size_t i = 0; i < m_sensitivity.size(); ++i)

    // check for nan entries:
    if (m_sensitivity[i] != m_sensitivity[i])

      h0->SetBinContent(i, 0.);

    else {

      h0->SetBinContent(i, m_sensitivity[i]);
      h0->SetBinError(i, m_bin_error[i]);
    }

  h0->GetXaxis()->SetTitle("#varepsilon_{s}");
  h0->GetYaxis()->SetTitle("F.O.M.");

  h0->Draw("E");

  c1.Print((out_name + ".pdf").c_str());

  // SistParam();

  int bin_max = h0->GetMaximumBin();
  double max_eff = h0->GetXaxis()->GetBinCenter(bin_max);

  PrintCutsAtMaximum(max_eff);
  WriteCutsToFile(max_eff, sig_name, use_var);
  PR(m_sigE);
  PR(m_bkgE);
}
