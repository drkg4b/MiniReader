// The class header:
#include "MiniReader/SensitivityPlot.h"

// STL include(s):
#include <chrono>

int main(int argc, char *argv[])
{
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  // Get the signal sample:
  std::string sig_sample = argv[1];
  std::string bkg_sample = argv[2];

  // Create the object:
  SensitivityPlot sens(sig_sample, bkg_sample);

  // Add variables to the TMVA reader:
  sens.RegisterToReader("EtMissMuVeto");
  sens.RegisterToReader("jet1_pt");
  sens.RegisterToReader("n_jet30");

  // Book the MVA method:
  sens.RegisterMVA("weights/", "TMVAClassification", "CutsGA");

  double EtMissMuVeto = 0;

  sens.PrepareTree("EtMissMuVeto", EtMissMuVeto);

  sens.PrintCuts();

  float bkg_sist = .02;

  sens.DoSensitivityPlot();

  // Get elapsed time:
  end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end - start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  std::cout << "finished computation at " << std::ctime(&end_time)
	    << "elapsed time: " << elapsed_seconds.count() << "s\n";

  return 0;
}
