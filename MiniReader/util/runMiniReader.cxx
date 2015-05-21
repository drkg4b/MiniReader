// EDM include(s):
#include "xAODRootAccess/Init.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/DiskListLocal.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "SampleHandler/ScanDir.h"
#include "EventLoop/DirectDriver.h"
#include "EventLoop/ProofDriver.h"
#include "EventLoop/Job.h"
#include <TSystem.h>

// The class header:
#include "MiniReader/MiniReaderAlg.h"

// STL include(s):
#include <chrono>

// ROOT Include(s):
#include "TChain.h"

int main(int argc, char *argv[])
{
   std::chrono::time_point<std::chrono::system_clock> start, end;
   start = std::chrono::system_clock::now();

   // Take the submit directory from the input if provided:
   std::string submitDir = "submitDir";

   if (argc > 1) submitDir = argv[1];

   // Recomended way to access samples:
   // SH::ScanDir().maxDepth(0)
   //   .filePattern("hist-*.root")
   //   .sampleRename("*","ZnunuSamples")
   //   .scan(sh, "/home/drkg4b/work/input_samples/BP-v1/BP-01/");

   TChain chain("MiniTree");

   chain.Add("/home/drkg4b/work/input_samples/BP-v1/BP-01/hist-*.root");

   TChain chain1("MiniTree");

   chain1.Add("/home/drkg4b/work/input_samples/signals/user.cclement.t02.mc14_13TeV.191040.MadGraphPythia_AUET2BMSTW2008LO_D5_400_1000_MET100_hist-output.root.19926114/*.root");

   TChain chain2("MiniTree");

   chain2.Add("/home/drkg4b/work/input_samples/signals/compressed/model1/*.root");

   TChain chain3("MiniTree");

   chain3.Add("/home/drkg4b/work/input_samples/signals/compressed/model2/*.root");

   TChain chain4("MiniTree");

   chain4.Add("/home/drkg4b/work/input_samples/background/ttbar/*.root");

   TChain chain5("MiniTree");

   chain5.Add("/home/drkg4b/work/input_samples/background/ttbar_jvt/*.root");

   // TChain chain1("MiniTree");

   // chain1.Add("/home/drkg4b/work/input_samples/cutFlow-00/hist-*ZnunuMassive*.root");

   // Construct the samples to run on:
   SH::SampleHandler sh;

   sh.add(SH::makeFromTChain("ZnunuSamples", chain));
   sh.add(SH::makeFromTChain("D5", chain1));
   sh.add(SH::makeFromTChain("Compressed1", chain2));
   sh.add(SH::makeFromTChain("Compressed2", chain3));
   // sh.add(SH::makeFromTChain("ttbarSamples", chain4));
   // sh.add(SH::makeFromTChain("ttbarJVTSamples", chain5));
   // sh.add(SH::makeFromTChain("cutFlowSamples", chain2));

   // print what we found:
   sh.print();

   // Create an EventLoop job:
   EL::Job job;
   job.sampleHandler(sh);

   // Add our analysis to the job:
   MiniReaderAlg *alg = new MiniReaderAlg();

   alg->m_submitDir = submitDir;

   job.algsAdd(alg);

   // Set max number of events:
   // job.options()->setDouble(EL::Job::optMaxEvents, 1000);

   // Use TTreeCache with 100 Mb:
   job.options()->setDouble(EL::Job::optCacheSize, 100 * 1024 * 1024);

   // Read desired numbr of events:
   job.options()->setDouble(EL::Job::optCacheLearnEntries, 30);

   // Set log level:
   // alg->msg().setLevel( MSG::DEBUG );

   // Run the job using the local/direct driver:
   EL::DirectDriver driver;
   // EL::ProofDriver driver;
   driver.submit(job, submitDir);

   end = std::chrono::system_clock::now();

   std::chrono::duration<double> elapsed_seconds = end - start;
   std::time_t end_time = std::chrono::system_clock::to_time_t(end);

   std::cout << "finished computation at " << std::ctime(&end_time)
             << "elapsed time: " << elapsed_seconds.count() << "s\n";

   return 0;
}
