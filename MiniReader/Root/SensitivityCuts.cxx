#include "MiniReader/SensitivityCuts.h"

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
SensitivityCuts::SensitivityCuts(std::string out_suffix)
{
  std::string out_name = "TMVASensitivityCuts_" + out_suffix + ".root";

  m_out_file = new TFile(out_name.c_str(), "RECREATE");

  // Create the factory object:
  // m_factory = std::make_shared<TMVA::Factory>("TMVAClassification", m_out_file,
  // 						   "!V:!Silent:Color:DrawProgressBar:"
  // 						   "Transformations=I;N;D;P;U;G,D:"
  // 						   "AnalysisType=Classification");
  m_factory = CxxUtils::make_unique<TMVA::Factory>("TMVAClassification", m_out_file,
  						   "!V:!Silent:Color:DrawProgressBar:"
  						   "Transformations=I;N;D;P;U;G,D:"
  						   "AnalysisType=Classification");

  // m_factory = new TMVA::Factory("TMVAClassification", m_out_file,
  // 				"!V:!Silent:Color:DrawProgressBar:"
  // 				"Transformations=I;N;D;P;U;G,D:"
  // 				"AnalysisType=Classification");

  std::string weight_dir = "weight" + out_suffix;

  (TMVA::gConfig().GetIONames()).fWeightFileDir = weight_dir.c_str();
}

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
void SensitivityCuts::RegisterFactoryVariable(std::string var)
{
  m_factory->AddVariable(var.c_str());
}

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
void SensitivityCuts::SetEventWeights(std::string var)
{
  // Set individual event weights (the variables must exist in the original TTree)
  m_factory->SetSignalWeightExpression(var.c_str());
  m_factory->SetBackgroundWeightExpression(var.c_str());
}

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
void SensitivityCuts::RunFactory(std::string signal_name, std::string back_name)
{
  // Get signal tree:
  TFile sig_file(signal_name.c_str());

  TTree *sig_tree = static_cast<TTree *>(sig_file.Get("SensTree"));

  m_factory->AddSignalTree(sig_tree);

  // Get background tree:
  TFile bkg_file(back_name.c_str());

  TTree *bkg_tree = static_cast<TTree *>(bkg_file.Get("SensTree"));

  m_factory->AddBackgroundTree(bkg_tree);

  // Apply additional cuts on the signal and background samples (can be different)
  TCut mycuts = ""; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
  TCut mycutb = ""; // for example: TCut mycutb = "abs(var1)<0.5";

  m_factory->PrepareTrainingAndTestTree(mycuts, mycutb, "nTrain_Signal=0:"
				      "nTrain_Background=0:SplitMode=Random:"
				      "NormMode=NumEvents:!V");

  // Cut optimisation
  m_factory->BookMethod(TMVA::Types::kCuts, "CutsGA",
                      "H:!V:FitMethod=GA:"
		      //"CutRangeMin[0]=250000:CutRangeMax[0]=900000:"
		      //"CutRangeMin[2]=0:CutRangeMax[2]=8:"
		      "VarProp=FSmart:EffSel:Steps=30:Cycles=3:PopSize=400:SC_steps=10:"
		      "SC_rate=5:SC_factor=0.95");

  // Train MVAs using the set of training events
  m_factory->TrainAllMethods();

  // ---- Evaluate all MVAs using the set of test events
  m_factory->TestAllMethods();

  // ----- Evaluate and compare performance of all configured MVAs
  m_factory->EvaluateAllMethods();
}

////////////////////////////////////////////////////////////////////////////////
////
////////////////////////////////////////////////////////////////////////////////
SensitivityCuts::~SensitivityCuts()
{
  // delete m_factory;
  m_out_file->Close();
}
