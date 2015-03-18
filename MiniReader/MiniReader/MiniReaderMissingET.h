#ifndef MINIREADER_MINIREADERMISSINGET_H
#define MINIREADER_MINIREADERMISSINGET_H

// ROOT include(s):
#include <TTree.h>

// STL include(s):
#include <vector>

class MiniReaderMissingET {

  friend class MiniReaderAlg;

 private:

  double m_EtMiss;
  double m_EtMissPhi;
  double m_WEtMiss;
  double m_WEtMissPhi;
  double m_ZEtMiss;
  double m_ZEtMissPhi;
  double m_EtMissMuVeto;
  double m_EtMissMuVetoPhi;

 public:

  MiniReaderMissingET();
  void ReadMissingETBranches(TTree *);
};

#endif // MINIREADER_MINIREADERMISSINGET_H
