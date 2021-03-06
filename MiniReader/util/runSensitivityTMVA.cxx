// The program header:
#include "MiniReader/SensitivityCuts.h"

// STL include(s):
#include <chrono>
#include <unistd.h>

int main(int argc, char **argv)
{
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  std::vector<std::string> back_names;

  std::string signal_name = argv[1];
  // std::string back_name = argv[2];

  back_names.push_back(argv[2]);
  back_names.push_back(argv[3]);
  back_names.push_back(argv[4]);
  back_names.push_back(argv[5]);
  back_names.push_back(argv[6]);
  back_names.push_back(argv[7]);
  back_names.push_back(argv[8]);
  back_names.push_back(argv[9]);

  std::string use_var = argv[10];

  std::string signal_sample;

  if (signal_name.find("D5") != std::string::npos)

    signal_sample = "D5_";

  if (signal_name.find("Compressed_450_435") != std::string::npos)

    signal_sample = "Compressed_450_435_";

  if (signal_name.find("Compressed_450_425") != std::string::npos)

    signal_sample = "Compressed_450_425_";

  std::string init_object = signal_sample + use_var;

  // Create the objects:
  SensitivityCuts sens_obj(init_object);

  sens_obj.RegisterFactoryVariable("EtMissMuVeto");
  sens_obj.RegisterFactoryVariable("jet1_pt");
  sens_obj.RegisterFactoryVariable(use_var.c_str());

  sens_obj.SetEventWeights("event_weight");

  sens_obj.RunFactory(signal_name, back_names);

  // Get elapsed time:
  end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end - start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  std::cout << "finished computation at " << std::ctime(&end_time)
	    << "elapsed time: " << elapsed_seconds.count() << "s\n";

  return 0;
}
