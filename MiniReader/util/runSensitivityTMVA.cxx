// The program header:
#include "MiniReader/SensitivityCuts.h"

// STL include(s):
#include <chrono>

int main(int argc, char **argv)
{
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  std::string signal_name = argv[1];
  std::string back_name = argv[2];
  std::string use_var = argv[3];

  std::string signal_sample;

  if (signal_name.find("D5") != std::string::npos)

    signal_sample = "D5_";

  if (signal_name.find("Compressed1") != std::string::npos)

    signal_sample = "Compressed1_";

  std::string init_object = signal_sample + use_var;

  // Create the objects:
  SensitivityCuts sens_obj(init_object);

  sens_obj.RegisterFactoryVariable("EtMissMuVeto");
  sens_obj.RegisterFactoryVariable("jet1_pt");
  sens_obj.RegisterFactoryVariable(use_var.c_str());

  sens_obj.SetEventWeights("event_weight");

  sens_obj.RunFactory(signal_name, back_name);

  // Get elapsed time:
  end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end - start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  std::cout << "finished computation at " << std::ctime(&end_time)
	    << "elapsed time: " << elapsed_seconds.count() << "s\n";

  return 0;
}
