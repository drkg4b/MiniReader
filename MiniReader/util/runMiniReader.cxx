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

   // Background samples:
   TChain chain_znunu("MiniTree");

   chain_znunu.Add("/home/drkg4b/work/input_samples/background/Znunu/*hist-output.root");

   TChain chain_zmumu("MiniTree");

   chain_zmumu.Add("/home/drkg4b/work/input_samples/background/Zmumu/*hist-output.root");

   TChain chain_zee("MiniTree");

   chain_zee.Add("/home/drkg4b/work/input_samples/background/Zee/*hist-output.root");

   TChain chain_ztautau("MiniTree");

   chain_ztautau.Add("/home/drkg4b/work/input_samples/background/Ztautau/*hist-output.root");

   TChain chain_wmunu("MiniTree");

   chain_wmunu.Add("/home/drkg4b/work/input_samples/background/Wmunu/*hist-output.root");

   TChain chain_wenu("MiniTree");

   chain_wenu.Add("/home/drkg4b/work/input_samples/background/Wenu/*hist-output.root");

   TChain chain_wtaunu("MiniTree");

   chain_wtaunu.Add("/home/drkg4b/work/input_samples/background/Wtaunu/*hist-output.root");

   TChain chain_ttbar("MiniTree");

   chain_ttbar.Add("/home/drkg4b/work/input_samples/background/ttbar/*hist-output.root");

   // Signal samples:
   TChain chain_d5("MiniTree");

   chain_d5.Add("/home/drkg4b/work/input_samples/signals/user.cclement.t02.mc14_13TeV.191040.MadGraphPythia_AUET2BMSTW2008LO_D5_400_1000_MET100_hist-output.root.19926114/*.root");

   TChain chain_comp1("MiniTree");

   chain_comp1.Add("/home/drkg4b/work/input_samples/signals/compressed/model1/*.root");

   TChain chain_comp2("MiniTree");

   chain_comp2.Add("/home/drkg4b/work/input_samples/signals/compressed/model2/*.root");

   // CutFlow samples:
   TChain chain_cutflow("MiniTree");

   chain_cutflow.Add("/home/drkg4b/work/input_samples/cutFlow_p1872/*.root");


   // Construct the samples to run on:
   SH::SampleHandler sh;

   // sh.add(SH::makeFromTChain("ZnunuSamples", chain_znunu));
   // sh.add(SH::makeFromTChain("ZmumuSamples", chain_zmumu));
   // sh.add(SH::makeFromTChain("ZeeSamples", chain_zee));
   // sh.add(SH::makeFromTChain("ZtautauSamples", chain_ztautau));
   // sh.add(SH::makeFromTChain("WmunuSamples", chain_wmunu));
   // sh.add(SH::makeFromTChain("WenuSamples", chain_wenu));
   // sh.add(SH::makeFromTChain("WtaunuSamples", chain_wtaunu));
   // sh.add(SH::makeFromTChain("ttbarSamples", chain_ttbar));
   // sh.add(SH::makeFromTChain("D5", chain_d5));
   // sh.add(SH::makeFromTChain("Compressed1", chain_comp1));
   // sh.add(SH::makeFromTChain("Compressed2", chain_comp2));
   // sh.add(SH::makeFromTChain("ttbarJVTSamples", chain5));
   sh.add(SH::makeFromTChain("cutFlowSamples", chain_cutflow));

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

   // Remove submission dir, NOT recommended:
   job.options()->setDouble (EL::Job::optRemoveSubmitDir, 1);

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
