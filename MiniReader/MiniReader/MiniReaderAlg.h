#ifndef MiniReader_MiniReaderAlg_H
#define MiniReader_MiniReaderAlg_H

// Infrastructure include(s):
#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"
#include <EventLoop/Algorithm.h>
#include <EventLoop/Worker.h>

// ROOT include(s):
#include "TTree.h"
#include "TH1F.h"
#include "TBranch.h"

// Local inclede(s):
#include "MiniReader/MiniReaderJets.h"
#include "MiniReader/MiniReaderElectrons.h"

#define PR(x) std::cout << #x << " = " << x << std::endl

class MiniReaderAlg : public EL::Algorithm
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
public:
  // float cutValue;



  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
public:
  // Tree *myTree; //!
  // TH1 *myHist; //!

  MiniReaderJets m_jet; //!
  MiniReaderElectrons m_el; //!

  int m_eventCounter; //!

  std::vector<TH1F*> m_HistoContainer; //!

  void DefineHisto(int, int, float, float); //!
  void InitHisto(); //!

  void FillJets(); //!


  // this is a standard constructor
  MiniReaderAlg();

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

  // this is needed to distribute the algorithm to the workers
  ClassDef(MiniReaderAlg, 1);
};

#endif
