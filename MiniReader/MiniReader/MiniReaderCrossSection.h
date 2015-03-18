#ifndef MINIREADER_MINIREADERCROSSSECTION_H
#define MINIREADER_MINIREADERCROSSSECTION_H

// ROOT include(s):
#include <TTree.h>

// STL include(s):
#include <vector>
#include <string>

class MiniReaderCrossSection {

  friend class MiniReaderAlg;

 private:

  float m_process_xs8;
  float m_process_kfactor8;
  float m_process_eff8;
  float m_process_xsrelunc8;
  std::string *m_process_name8;
  float m_process_xs13;
  float m_process_kfactor13;
  float m_process_eff13;
  float m_process_xsrelunc13;
  std::string *m_process_name13;

 public:

  MiniReaderCrossSection();
  void ReadCrossSectionBranches(TTree *);
};

#endif // MINIREADER_MINIREADERCROSSSECTION_H
