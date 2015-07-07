#ifndef MINIREADER_MINIREADERPRIMARYVERTEX_H
#define MINIREADER_MINIREADERPRIMARYVERTEX_H

// ROOT include(s):
#include <TTree.h>

// STL include(s):
#include <vector>

class MiniReaderPrimaryVertex {

  friend class MiniReaderAlg;

 private:

  int m_pvtx_n;

  std::vector<int>    *m_pvtx_ntracks;
  std::vector<double> *m_pvtx_z;

 public:

  MiniReaderPrimaryVertex();
  void ReadPrimaryVertexBranches(TTree *);
  int GetPvtxN() const;
};

#endif // MINIREADER_MINIREADERPRIMARYVERTEX_H
