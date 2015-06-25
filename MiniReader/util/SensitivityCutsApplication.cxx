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
  std::string use_var = argv[3];
  std::string out_dir = argv[4];

  std::string sig_name;

  if (sig_sample.find("D5") != std::string::npos)

    sig_name = "D5_";

  if (sig_sample.find("Compressed1") != std::string::npos)

    sig_name = "Compressed1_";

  // Create the object:
  SensitivityPlot sens(sig_sample, bkg_sample);

  // Add variables to the TMVA reader:
  sens.RegisterToReader("EtMissMuVeto");
  sens.RegisterToReader("jet1_pt");
  sens.RegisterToReader(use_var.c_str());

  std::string weight_dir = "weight" + sig_name + use_var + "/";

  // Book the MVA method:
  sens.RegisterMVA(weight_dir.c_str(), "TMVAClassification", "CutsGA");

  sens.SetSigBkgEvent();
  sens.GetEfficiencyPerBin(sig_name + use_var);
  sens.PrintCuts();
  sens.SetTotalSigEvents();
  sens.SetTotalBkgEvents();
  sens.CalculateBinError();
  sens.CalculateSensitivity();
  sens.DoSensitivityPlot(out_dir, sig_name, use_var);

  // Get elapsed time:
  end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end - start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  std::cout << "finished computation at " << std::ctime(&end_time)
	    << "elapsed time: " << elapsed_seconds.count() << "s\n";

  return 0;
}
