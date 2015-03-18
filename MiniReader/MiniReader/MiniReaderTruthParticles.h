#ifndef MINIREADER_MINIREADERTRUTHPARTICLES_H
#define MINIREADER_MINIREADERTRUTHPARTICLES_H

// ROOT include(s):
#include <TTree.h>

// STL include(s):
#include <vector>

class MiniReaderTruthParticles {

  friend class MiniReaderAlg;

 private:

  double m_true_zpt;
  double m_true_zm;
  double m_true_wpt;
  bool m_pass_zpt;
  bool m_pass_wpt;
  int m_pdf_pdgid1;
  int m_pdf_pdgid2;
  float m_pdf_x1;
  float m_pdf_x2;
  int m_pdf_pdfid1;
  int m_pdf_pdfid2;
  float m_pdf_scale;

 public:

  MiniReaderTruthParticles();
  void ReadTruthParticlesBranches(TTree *);
};

#endif // MINIREADER_MINIREADERTRUTHPARTICLES_H
