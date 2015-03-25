#ifndef MINIREADER_MINIREADERSELECTIONCUTS_H
#define MINIREADER_MINIREADERSELECTIONCUTS_H

namespace M0Cuts {

  static constexpr const float JET_PT = 250000;
  static constexpr const float MET_CUT = 250000;
}

namespace M5Cuts {

  static constexpr const float JET_PT = 500000;
  static constexpr const float MET_CUT = 500000;
}

namespace M9Cuts {

  static constexpr const float JET_PT = 700000;
  static constexpr const float MET_CUT = 700000;
}

namespace EventFilter {

  static constexpr const float DPHI_JETMET = .4;
  static constexpr const float N_JETS = -1; // WARNING!!!! to be changed
  static constexpr const float N_PVTX = 0;
  static constexpr const float MET_CUT = 250000;
  static constexpr const float JET_PT = 250000;
  static constexpr const float JET_ETA = 2.8;
}

#endif // MINIREADER_MINIREADERSELECTIONCUTS_H
