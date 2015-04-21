// TMVA include(s):
#include <TMVA/Factory.h>
#include <TMVA/Tools.h>

// ROOT include(s):
#include <TFile.h>
#include <TTree.h>
#include <TCut.h>

// STL include(s):
#include <string>

int main(int argc, char *argv[])
{
  std::string out_name("TMVASensitivityCuts.root");

  TFile *out_file = new TFile(out_name.c_str(), "RECREATE");

  // Create the factory object:
  TMVA::Factory *factory = new TMVA::Factory("TMVAClassification", out_file,
  "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification");


  factory->AddVariable("EtMissMuVeto");
  factory->AddVariable("jet_mult");
  factory->AddVariable("jet_pt");

  std::string signal_name = argv[1];
  std::string back_name = argv[2];

  TFile in_signal(signal_name.c_str());
  TFile in_back(back_name.c_str());

  TTree *signal = (TTree*)in_signal.Get("SensTree");
  TTree *back = (TTree*)in_back.Get("SensTree");

  factory->AddSignalTree(signal);
  factory->AddBackgroundTree(back);

   // Set individual event weights (the variables must exist in the original TTree)
   //    for signal    : factory->SetSignalWeightExpression    ("weight1*weight2");
   //    for background: factory->SetBackgroundWeightExpression("weight1*weight2");

   // Apply additional cuts on the signal and background samples (can be different)
   TCut mycuts = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
   TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";

   factory->PrepareTrainingAndTestTree(mycuts, mycutb,
   "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V");

   // Cut optimisation
   factory->BookMethod(TMVA::Types::kCuts, "Cuts",
   "!H:!V:FitMethod=GA:EffSel:SampleSize=200000:VarProp=FSmart" );

   // Train MVAs using the set of training events
   factory->TrainAllMethods();

   // ---- Evaluate all MVAs using the set of test events
   factory->TestAllMethods();

   // ----- Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();

   out_file->Close();

  delete factory;

  return 0;
}
