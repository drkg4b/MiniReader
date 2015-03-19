// Local include(s):
#include "MiniReader/MiniReaderAlg.h"

// SDL include(s):
#include <math.h>

double MiniReaderAlg::deltaPhi(double phi1, double phi2)
{
  double dphi = std::fabs(phi1 - phi2);

  return (dphi > M_PI) ? (2 * M_PI - dphi) : dphi;
}


double MiniReaderAlg::deltaR(double eta1, double phi1, double eta2, double phi2)
{
  double dp = deltaPhi(phi1, phi2);
  double de = eta1 - eta2;

  return std::sqrt(dp * dp + de * de);
}
