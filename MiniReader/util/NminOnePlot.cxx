// ROOT include(s):
#include <TFile.h>
#include <TTree.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <THStack.h>
#include <TLegend.h>
#include <TF1.h>
#include <TH1.h>

// STL include(s):
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <string>
#include <chrono>
#include <array>
#include <tuple>
#include <map>

// Atlas Style:
#include "MiniReader/AtlasStyle.h"

#define PR(x) std::cout << #x << " = " << x << std::endl

////////////////////////////////////////////////////////////////////////////////
//// Forward declarations
////////////////////////////////////////////////////////////////////////////////
std::tuple<std::vector<double>, std::vector<double> >
GetSigAndBkgEvents(std::tuple<TTree *, TTree *>,
                   const std::vector<std::vector<std::string> > &, const std::string &);

std::vector<double> SistParam(const std::vector<double> &);

std::vector<double> CalculateSensitivity(const std::vector<double> &, const
std::vector<double> &, const std::vector<double> &);

void PrintMaxValue(const std::vector<double> &, const std::vector<double> &);

void PlotFOM(std::vector<double> &, std::vector<double> &);

std::vector<std::vector<std::string> > ReadVarValuesFromFile(const std::string &);

void plotEtMissStack(std::tuple<TTree *, TTree *> , const std::vector<std::vector<std::string> > &);

////////////////////////////////////////////////////////////////////////////////
//// Main Function
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  std::string sig_tree_name = argv[1];
  std::string bkg_tree_name = argv[2];
  std::string in_file = argv[3];

  TFile sig_file(sig_tree_name.c_str());
  TFile bkg_file(bkg_tree_name.c_str());

  TTree *sig_tree = static_cast<TTree *>(sig_file.Get("SensTree"));
  TTree *bkg_tree = static_cast<TTree *>(bkg_file.Get("SensTree"));

  long sig_entries = sig_tree->GetEntries();
  long bkg_entries = bkg_tree->GetEntries();

  PR(sig_entries);
  PR(bkg_entries);

  std::tuple<TTree *, TTree *> tree_tuple(sig_tree, bkg_tree);

  std::vector<std::vector<std::string> > cut_values;

  cut_values = ReadVarValuesFromFile(in_file);

  std::vector<double> sigE;
  std::vector<double> bkgE;

  // std::tie(sigE, bkgE) = GetSigAndBkgEvents(tree_tuple, cut_values, "et_miss");

  // std::vector<double> et_miss;
  // std::vector<double> sensitivity;

  // for(size_t i = 1; i < cut_values[1].size(); ++i)

  //   et_miss.push_back(std::stod(cut_values[1][i]));

  // sensitivity = CalculateSensitivity(sigE, bkgE, et_miss);

  // for(size_t i = 0; i < et_miss.size(); ++i) {

  //   std::cout << et_miss[i] << "\t" << sigE[i] << "\t" << bkgE[i] << std::endl;
  // }

  // PlotFOM(et_miss, sensitivity);

  // PrintMaxValue(et_miss, sensitivity);

  plotEtMissStack(tree_tuple, cut_values);

  // Get elapsed time:
  end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end - start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  std::cout << "finished computation at " << std::ctime(&end_time)
            << "elapsed time: " << elapsed_seconds.count() << "s\n";

  return 0;
}

////////////////////////////////////////////////////////////////////////////////
//// Calculate signal and background events:
////
//// This function calculates the number of events in the signal and background
//// trees for each value of the variable being scanned.
////////////////////////////////////////////////////////////////////////////////
std::tuple<std::vector<double>, std::vector<double> > GetSigAndBkgEvents(std::tuple<TTree *, TTree *> tree_tuple,
    const std::vector<std::vector<std::string> > &cut_values, const std::string &scan_var)
{
  std::vector<double> sigE;
  std::vector<double> bkgE;

  std::vector<std::string> et_miss_max = cut_values[0];
  std::vector<std::string> et_miss_min = cut_values[1];
  std::vector<std::string> et_miss_best = cut_values[2];

  std::vector<std::string> jet1_pt_max = cut_values[3];
  std::vector<std::string> jet1_pt_min = cut_values[4];
  std::vector<std::string> jet1_pt_best = cut_values[5];

  std::vector<std::string> n_jet_max = cut_values[6];
  std::vector<std::string> n_jet_min = cut_values[7];
  std::vector<std::string> n_jet_best = cut_values[8];

  sigE.reserve(et_miss_max.size());
  sigE.reserve(et_miss_max.size());

  for (size_t i = 1; i < et_miss_min.size(); ++i) {

    TH1F *h0 = new TH1F("h0", "h0", 100, 0, 20000000);
    TH1F *h1 = new TH1F("h1", "h1", 100, 0, 20000000);

    TTree *sig_tree = std::get<0>(tree_tuple);
    TTree *bkg_tree = std::get<1>(tree_tuple);

    std::string condition;

    if (i != 0 && scan_var == "et_miss")

      condition = "event_weight * (" + et_miss_min[0] + et_miss_min[i]
	+ " && " + jet1_pt_min[0] + jet1_pt_best[0] + " && " + n_jet_min[0] +
	n_jet_best[0] + ")";

    if (i != 0 && scan_var == "jet1_pt")

      condition = "event_weight * (" + et_miss_min[0] + et_miss_best[0]
	+ " && " + jet1_pt_min[0] + jet1_pt_min[i] + " && " + n_jet_min[0] +
	n_jet_best[0] + ")";

    if (i != 0 && scan_var == "n_jet")

      condition = "event_weight * (" + et_miss_min[0] + et_miss_best[0]
	+ " && " + jet1_pt_min[0] + jet1_pt_best[0] + " && " + n_jet_min[0] +
	n_jet_min[i] + ")";

    std::cout << "Calculating number of events for condition: " << condition <<
              std::endl;

      sig_tree->Project("h0", "jet1_pt", condition.c_str());
      bkg_tree->Project("h1", "jet1_pt", condition.c_str());

      sigE.push_back(h0->Integral());
      bkgE.push_back(h1->Integral());

      std::cout << "Signal events = " << h0->Integral() << "\tBackground events = "
		<< h1->Integral() << std::endl;

    delete h0;
    delete h1;
  }

  return std::tuple<std::vector<double>, std::vector<double> > {sigE, bkgE};
}

////////////////////////////////////////////////////////////////////////////////
//// Parametrization of the systematic error:
////
//// This function parametrize the systematic error.
////////////////////////////////////////////////////////////////////////////////
std::vector<double> SistParam(const std::vector<double> &et_miss)
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

  TF1 *fit_func = static_cast<TF1 *>(gr.FindObject("pol2"));

  std::vector<double> bkg_sist;

  bkg_sist.reserve(et_miss.size());

  for (size_t i = 0; i < et_miss.size(); ++i)

    bkg_sist.push_back(fit_func->Eval(et_miss[i]));

  return bkg_sist;
}

////////////////////////////////////////////////////////////////////////////////
//// Print the maximum value:
////
//// This function will print the maximum value of the FOM.
////////////////////////////////////////////////////////////////////////////////
void PrintMaxValue(const std::vector<double> &variable, const std::vector<double> &sensitivity)
{
  std::vector<double>::const_iterator max_itr =
    std::max_element(std::begin(sensitivity), std::end(sensitivity));

  std::vector<double>::const_iterator sens_itr = std::begin(sensitivity);

  int position = std::distance(sens_itr, max_itr);

  std::cout << "The max values is given by:\n" <<
            variable[position] << "\t" << sensitivity[position] << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
//// Calculate the sensitivity:
////
//// This function will calculate the FOM.
////////////////////////////////////////////////////////////////////////////////
std::vector<double> CalculateSensitivity(const std::vector<double> &sig_events,
const std::vector<double> &bkg_events, const std::vector<double> &et_miss)
{
  std::vector<double> bkg_sist;
  std::vector<double> sensitivity;

  bkg_sist = SistParam(et_miss);

  for (size_t i = 0; i < et_miss.size(); ++i) {

    double sens = sig_events[i] /
                          std::sqrt(bkg_events[i] +
                                    std::pow(bkg_sist[i] * bkg_events[i], 2));

    if(sens != sens)

      sensitivity.push_back(0.);

    else

      sensitivity.push_back(sens);
  }

  for(size_t i = 0; i < sensitivity.size(); ++i)

    std::cout << sig_events[i] << "\t" << bkg_events[i] << "\t" << bkg_sist[i]
	      << "\t" << sensitivity[i] << "\t"
	      << std::pow(bkg_sist[i] * bkg_events[i], 2) << "\t"
	      << std::sqrt(bkg_events[i] + std::pow(bkg_sist[i] * bkg_events[i], 2))
	      << std::endl;

  return sensitivity;
}

////////////////////////////////////////////////////////////////////////////////
//// Plot FOM:
////
//// This function will plot the calculated FOM.
////////////////////////////////////////////////////////////////////////////////
void PlotFOM(std::vector<double> &scanned_var, std::vector<double>
             &sensitivity)
{
  AtlasStyle();

  TCanvas c1;

  int n = scanned_var.size();

  std::reverse(std::begin(sensitivity), std::end(sensitivity));
  std::reverse(std::begin(scanned_var), std::end(scanned_var));

  for(size_t i = 0; i < sensitivity.size(); ++i)

    std::cout << sensitivity[i] << "\t\t" << scanned_var[i] << std::endl;

  TGraph gr(n, &scanned_var[0], &sensitivity[0]);

  gr.SetTitle("");
  gr.GetXaxis()->SetTitle("#slash{E}_{T}");
  gr.GetYaxis()->SetTitle("F.O.M.");

  gr.GetXaxis()->SetRangeUser(0, 1200E3);

  gr.Draw("AP");

  c1.Print("graph.pdf");
}

////////////////////////////////////////////////////////////////////////////////
//// Function to read the cut values:
////
//// This function will read the cut values from the log file produced and store
//// them in vectors to be used to get the number of events.
////////////////////////////////////////////////////////////////////////////////
std::vector<std::vector<std::string> > ReadVarValuesFromFile(const std::string &file_name)
{
  std::fstream in_file(file_name, std::ios::in);

  std::vector<std::string> et_miss_min;
  std::vector<std::string> et_miss_max;
  std::vector<std::string> et_miss_best;

  std::vector<std::string> jet1_pt_min;
  std::vector<std::string> jet1_pt_max;
  std::vector<std::string> jet1_pt_best;

  std::vector<std::string> n_jet_min;
  std::vector<std::string> n_jet_max;
  std::vector<std::string> n_jet_best;

  std::string line;

  et_miss_min.reserve(1000);
  et_miss_max.reserve(1000);
  et_miss_best.reserve(1000);

  jet1_pt_min.reserve(1000);
  jet1_pt_max.reserve(1000);
  jet1_pt_best.reserve(1000);

  n_jet_min.reserve(1000);
  n_jet_max.reserve(1000);
  n_jet_best.reserve(1000);

  while (std::getline(in_file, line)) {

    std::string col1, col2, col3, col4, col5, col6, col7;

    std::stringstream ss(line);

    ss >> col1 >> col2 >> col3 >> col4 >> col5 >> col6 >> col7;

    et_miss_min.push_back(col2);
    et_miss_max.push_back(col3);

    jet1_pt_min.push_back(col4);
    jet1_pt_max.push_back(col5);

    n_jet_min.push_back(col6);
    n_jet_max.push_back(col7);

    if (col1.find("!") == 0) {

      et_miss_best.push_back(col2);
      jet1_pt_best.push_back(col4);
      n_jet_best.push_back(col6);
    }
  }

  std::vector<std::vector<std::string> > cut_values;

  cut_values.reserve(9);

  cut_values.push_back(et_miss_max);
  cut_values.push_back(et_miss_min);
  cut_values.push_back(et_miss_best);

  cut_values.push_back(jet1_pt_max);
  cut_values.push_back(jet1_pt_min);
  cut_values.push_back(jet1_pt_best);

  cut_values.push_back(n_jet_max);
  cut_values.push_back(n_jet_min);
  cut_values.push_back(n_jet_best);

  return cut_values;
}

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
void plotEtMissStack(std::tuple<TTree *, TTree *> tree_tuple, const std::vector<std::vector<std::string> > &cut_values)
{
  std::vector<std::string> jet1_pt_min = cut_values[4];
  std::vector<std::string> jet1_pt_best = cut_values[5];

  std::vector<std::string> n_jet_min = cut_values[7];
  std::vector<std::string> n_jet_best = cut_values[8];

  TH1F *h0 = new TH1F("h0", "h0", 100, 0, 2E6);
  TH1F *h1 = new TH1F("h1", "h1", 100, 0, 2E6);

  TTree *sig_tree = std::get<0>(tree_tuple);
  TTree *bkg_tree = std::get<1>(tree_tuple);

  std::string condition = "event_weight * (" + jet1_pt_min[0] + jet1_pt_best[0] +
    " && " + n_jet_min[0] + n_jet_best[0] + ")";

  // The goff option suppress generating the graphics
  sig_tree->Project("h0", "EtMissMuVeto", condition.c_str(), "goff");
  bkg_tree->Project("h1", "EtMissMuVeto", condition.c_str(), "goff");

  SetAtlasStyle();

  THStack *hs = new THStack("hs", "");

  h0->SetFillColor(kMagenta);
  h1->SetFillColor(kBlue);

  // hs->Add(h0);
  // hs->Add(h1);

  TCanvas c1;

  c1.SetLogy();

  hs->SetMaximum(1.5 * h1->GetMaximum());

  TLegend leg;

  leg.AddEntry(h0, "Compressed Spectra");
  leg.AddEntry(h1, "All Backgrounds");

  h0->GetXaxis()->SetTitle("#slash{E}_{T} [MeV]");
  h0->GetYaxis()->SetTitle("Entries");

  h1->Draw("hist");
  h0->Draw("same");
  leg.Draw("same");

  // h0->Rebin(4);
  // h1->Rebin(4);

  // hs->Draw("hist");

  // h0->Draw("same");

  c1.Print("EtMissStack.pdf");
}
