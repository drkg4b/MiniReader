// EDM include(s):
#include "xAODRootAccess/Init.h"
#include "SampleHandler/SampleHandler.h"
#include "SampleHandler/DiskListLocal.h"
#include "SampleHandler/ToolsDiscovery.h"
#include "EventLoop/DirectDriver.h"
#include "EventLoop/Job.h"
#include <TSystem.h>

// The class header:
#include "MiniReader/MiniReaderAlg.h"

// STL include(s):
#include <chrono>

int main(int argc, char *argv[])
{
   std::chrono::time_point<std::chrono::system_clock> start, end;
   start = std::chrono::system_clock::now();

   // Take the submit directory from the input if provided:
   std::string submitDir = "submitDir";
   if (argc > 1) submitDir = argv[ 1 ];

   // Set up the job for xAOD access:
   xAOD::Init().ignore();

   // Construct the samples to run on:
   SH::SampleHandler sh;

   const char *inputFilePath = gSystem->ExpandPathName("/home/drkg4b/work/input_samples/"); // using $ALRB_TutorialData previously defined
   SH::DiskListLocal list(inputFilePath);
   SH::scanDir(sh, list, "*");  // specifying one particular file for testing

   // Set the name of the input TTree. It's always "CollectionTree"
   // for xAOD files.
   sh.setMetaString("nc_tree", "CollectionTree");

   // Print what we found:
   sh.print();

   // Create an EventLoop job:
   EL::Job job;
   job.sampleHandler(sh);
   // Add our analysis to the job:
     MiniReaderAlg *alg = new MiniReaderAlg();

   job.algsAdd(alg);

   // Set max number of events:
   job.options()->setDouble(EL::Job::optMaxEvents, 1000);

   // Use TTreeCache with 100 Mb:
   job.options()->setDouble(EL::Job::optCacheSize, 100 * 1024 * 1024);

   // Read desired numbr of events:
   job.options()->setDouble(EL::Job::optCacheLearnEntries, 30);

   // Set log level:


   // Run the job using the local/direct driver:
   EL::DirectDriver driver;
   driver.submit(job, submitDir);

   end = std::chrono::system_clock::now();

   std::chrono::duration<double> elapsed_seconds = end - start;
   std::time_t end_time = std::chrono::system_clock::to_time_t(end);

   std::cout << "finished computation at " << std::ctime(&end_time)
             << "elapsed time: " << elapsed_seconds.count() << "s\n";

   return 0;
}
