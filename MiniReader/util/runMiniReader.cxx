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
#include <fstream>

// ROOT Include(s):
#include "TChain.h"

void ReadChainFromTextFile(TChain &, std::string);

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
   std::string base_dir = "/home/g/gbertoli/pfs/data/minitrees/v105/";

   TChain chain_znunu("MiniTree_NoSys");

   ReadChainFromTextFile(chain_znunu, base_dir + "znunu/znunu_file_list.txt");

   TChain chain_zmumu("MiniTree_NoSys");

   ReadChainFromTextFile(chain_zmumu, base_dir + "zmumu/zmumu_file_list.txt");

   TChain chain_zee("MiniTree_NoSys");

   ReadChainFromTextFile(chain_zee, base_dir + "zee/zee_file_list.txt");

   TChain chain_ztautau("MiniTree_NoSys");

   ReadChainFromTextFile(chain_ztautau, base_dir + "ztautau/ztautau_file_list.txt");

   TChain chain_wmunu("MiniTree_NoSys");

   ReadChainFromTextFile(chain_wmunu, base_dir + "wmunu/wmunu_file_list.txt");

   TChain chain_wenu("MiniTree_NoSys");

   ReadChainFromTextFile(chain_wenu, base_dir + "wenu/wenu_file_list.txt");

   TChain chain_wtaunu("MiniTree_NoSys");

   ReadChainFromTextFile(chain_wtaunu, base_dir + "wtaunu/wtaunu_file_list.txt");

   TChain chain_top("MiniTree_NoSys");

   ReadChainFromTextFile(chain_top, base_dir + "top/top_file_list.txt");

   TChain chain_stop("MiniTree_NoSys");

   ReadChainFromTextFile(chain_stop, base_dir + "stop/stop_file_list.txt");

   TChain chain_qcd("MiniTree_NoSys");

   ReadChainFromTextFile(chain_qcd, base_dir + "qcd/qcd_file_list.txt");

   TChain chain_diboson("MiniTree_NoSys");

   ReadChainFromTextFile(chain_diboson, base_dir + "diboson/diboson_file_list.txt");

   // Signal samples:
   TChain chain_d5("MiniTree_NoSys");

   chain_d5.Add((base_dir + "add_303499/"
		 "user.cclement.ntupsthlm_v105a.mc15_13TeV.303499.Pythia8EvtGen_A14NNPDF23LO_ADDGraviton_d5MD3200_Jet100_hist"
		 "/*hist-output.root").c_str());

   TChain chain_comp_400_375("MiniTree_NoSys");

   chain_comp_400_375.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371864.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_400_375_MET100_hist"
			   "/*hist-output.root").c_str());

   TChain chain_comp_400_385("MiniTree_NoSys");

   chain_comp_400_385.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371857.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_400_385_MET100_hist"
			   "/*hist-output.root").c_str());

   TChain chain_comp_400_395("MiniTree_NoSys");

   chain_comp_400_395.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371850.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_400_395_MET100_hist"
			   "/*hist-output.root").c_str());

   TChain chain_comp_450_425("MiniTree_NoSys");

   chain_comp_450_425.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371865.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_450_425_MET100_hist"
			   "/*hist-output.root").c_str());

   TChain chain_comp_450_435("MiniTree_NoSys");

   chain_comp_450_435.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371858.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_450_435_MET100_hist"
			   "/*hist-output.root").c_str());

   TChain chain_comp_450_445("MiniTree_NoSys");

   chain_comp_450_445.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371851.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_450_445_MET100_hist"
			   "/*hist-output.root").c_str());

   TChain chain_comp_500_475("MiniTree_NoSys");

   chain_comp_500_475.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371866.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_500_475_MET100_hist"
			   "/*hist-output.root").c_str());

   TChain chain_comp_500_485("MiniTree_NoSys");

   chain_comp_500_485.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371859.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_500_485_MET100_hist"
			   "/*hist-output.root").c_str());

   TChain chain_comp_500_495("MiniTree_NoSys");

   chain_comp_500_495.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371852.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_500_495_MET100_hist"
			   "/*hist-output.root").c_str());

   TChain chain_comp_550_525("MiniTree_NoSys");

   chain_comp_550_525.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371867.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_550_525_MET100_hist"
			   "/*hist-output.root").c_str());

   TChain chain_comp_550_535("MiniTree_NoSys");

   chain_comp_550_535.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371860.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_550_535_MET100_hist"
			   "/*hist-output.root").c_str());

   TChain chain_comp_550_545("MiniTree_NoSys");

   chain_comp_550_545.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371853.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_550_545_MET100_hist"
			   "/*hist-output.root").c_str());

   TChain chain_comp_600_575("MiniTree_NoSys");

   chain_comp_600_575.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371868.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_600_575_MET100_hist"
			   "/*hist-output.root").c_str());

   TChain chain_comp_600_585("MiniTree_NoSys");

   chain_comp_600_585.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371861.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_600_585_MET100_hist"
			   "/*hist-output.root").c_str());

   TChain chain_comp_600_595("MiniTree_NoSys");

   chain_comp_600_595.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371854.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_600_595_MET100_hist"
			   "/*hist-output.root").c_str());

   TChain chain_comp_650_625("MiniTree_NoSys");

   chain_comp_650_625.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371869.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_650_625_MET100_hist"
			   "/*hist-output.root").c_str());

   TChain chain_comp_650_635("MiniTree_NoSys");

   chain_comp_650_635.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371862.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_650_635_MET100_hist"
			   "/*hist-output.root").c_str());

   TChain chain_comp_650_645("MiniTree_NoSys");

   chain_comp_650_645.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371855.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_650_645_MET100_hist"
			   "/*hist-output.root").c_str());

   TChain chain_comp_700_675("MiniTree_NoSys");

   chain_comp_700_675.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371870.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_700_675_MET100_hist"
			   "/*hist-output.root").c_str());

   TChain chain_comp_700_685("MiniTree_NoSys");

   chain_comp_700_685.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371863.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_700_685_MET100_hist"
			   "/*hist-output.root").c_str());

   TChain chain_comp_700_695("MiniTree_NoSys");

   chain_comp_700_695.Add((base_dir + "compressed/"
			   "user.cclement.ntupsthlm_v105a.mc15_13TeV.371856.MadGraphPythia8EvtGen_A14NNPDF23LO_SS_direct_700_695_MET100_hist"
			   "/*hist-output.root").c_str());

   // CutFlow samples:
   // TChain chain_cutflow("MiniTree_NoSys");

   // chain_cutflow.Add("/home/drkg4b/work/input_samples/cutFlow_p1872/*.root");


   // Construct the samples to run on:
   SH::SampleHandler sh;

   sh.add(SH::makeFromTChain("ZnunuSamples", chain_znunu));
   // sh.add(SH::makeFromTChain("ZmumuSamples", chain_zmumu));
   // sh.add(SH::makeFromTChain("ZeeSamples", chain_zee));
   // sh.add(SH::makeFromTChain("ZtautauSamples", chain_ztautau));
   // sh.add(SH::makeFromTChain("WmunuSamples", chain_wmunu));
   // sh.add(SH::makeFromTChain("WenuSamples", chain_wenu));
   // sh.add(SH::makeFromTChain("WtaunuSamples", chain_wtaunu));
   // sh.add(SH::makeFromTChain("TopSamples", chain_top));
   // sh.add(SH::makeFromTChain("StopSamples", chain_stop));
   // sh.add(SH::makeFromTChain("QcdSamples", chain_qcd));
   // sh.add(SH::makeFromTChain("DibosonSamples", chain_diboson));

   sh.add(SH::makeFromTChain("D5", chain_d5));

   // sh.add(SH::makeFromTChain("Compressed_400_375", chain_comp_400_375));
   // sh.add(SH::makeFromTChain("Compressed_400_385", chain_comp_400_385));
   // sh.add(SH::makeFromTChain("Compressed_400_395", chain_comp_400_395));
   sh.add(SH::makeFromTChain("Compressed_450_425", chain_comp_450_425));
   sh.add(SH::makeFromTChain("Compressed_450_435", chain_comp_450_435));
   sh.add(SH::makeFromTChain("Compressed_450_445", chain_comp_450_445));
   // sh.add(SH::makeFromTChain("Compressed_500_475", chain_comp_500_475));
   // sh.add(SH::makeFromTChain("Compressed_500_485", chain_comp_500_485));
   // sh.add(SH::makeFromTChain("Compressed_500_495", chain_comp_500_495));
   // sh.add(SH::makeFromTChain("Compressed_550_525", chain_comp_550_525));
   // sh.add(SH::makeFromTChain("Compressed_550_535", chain_comp_550_535));
   // sh.add(SH::makeFromTChain("Compressed_550_545", chain_comp_550_545));
   // sh.add(SH::makeFromTChain("Compressed_600_575", chain_comp_600_575));
   // sh.add(SH::makeFromTChain("Compressed_600_585", chain_comp_600_585));
   // sh.add(SH::makeFromTChain("Compressed_600_595", chain_comp_600_595));
   // sh.add(SH::makeFromTChain("Compressed_650_625", chain_comp_650_625));
   // sh.add(SH::makeFromTChain("Compressed_650_635", chain_comp_650_635));
   // sh.add(SH::makeFromTChain("Compressed_650_645", chain_comp_650_645));
   // sh.add(SH::makeFromTChain("Compressed_700_675", chain_comp_700_675));
   // sh.add(SH::makeFromTChain("Compressed_700_685", chain_comp_700_685));
   // sh.add(SH::makeFromTChain("Compressed_700_695", chain_comp_700_695));

   // sh.add(SH::makeFromTChain("cutFlowSamples", chain_cutflow));

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

void ReadChainFromTextFile(TChain &ch, std::string file_name)
{
  std::ifstream in_file(file_name);

  if (!in_file.is_open())

    std::cout<<"Sorry, inputfilenamestream could not be opened!" << std::endl;

  else{

    std::string rootfile;

    while (getline(in_file, rootfile))

      ch.Add(rootfile.c_str());
  }
}
