#ifndef MINIREADER_MINIREADERSELECTIONCUTS_H
#define MINIREADER_MINIREADERSELECTIONCUTS_H

namespace M0Cuts {

  static constexpr const float JET_PT = 250000.;
  static constexpr const float MET_CUT = 250000.;
}

namespace M5Cuts {

  static constexpr const float JET_PT = 500000;
  static constexpr const float MET_CUT = 500000;
}

namespace M9Cuts {

  static constexpr const float JET_PT = 700000;
  static constexpr const float MET_CUT = 700000;
}

namespace ZnunuCuts {

  static constexpr const int N_JETS = 5; // WARNING this should be 5
  static constexpr const float DPHI_JETMET = .4;
  static constexpr const float MET_HARD = 250000.;
  static constexpr const float JET_PT_HARD = 150000.; // Changed from 400000 to study asymmetric cuts
}

namespace EventFilter {

  static constexpr const float DPHI_JETMET = .4;
  static constexpr const float N_JETS = 5; // WARNING!!!! should be 5
  static constexpr const int N_PVTX = 0;
  static constexpr const float MET_CUT = 250000;
  static constexpr const float JET_PT = 100000;
  static constexpr const float JET_ETA = 2.8;
}

namespace GoodJetCuts {

  static constexpr const float PT_CUT = 30000;
  static constexpr const float ETA_CUT = 2.8;
  static constexpr const float JVT_CUT = .64;
}

#endif // MINIREADER_MINIREADERSELECTIONCUTS_H
