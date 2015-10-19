#ifndef MINIREADER_MINIREADERRUNPARAM_H
#define MINIREADER_MINIREADERRUNPARAM_H

// ROOT include(s):
#include <TTree.h>

// STL include(s):
#include <vector>

class MiniReaderEventInfo {

  friend class MiniReaderAlg;

 private:

  unsigned long long int m_EventNumber;
  unsigned int m_RunNumber;
  uint32_t m_mc_channel_number;
  float m_actualInteractionsPerCrossing;
  float m_averageInteractionsPerCrossing;
  float m_global_event_weight;
  float m_mc_event_weight;
  float m_sum_of_weights;

 public:

  MiniReaderEventInfo();
  void ReadEventInfoBranches(TTree *);
  float GetAvgIntPerCross() const;
};

#endif // MINIREADER_MINIREADERRUNPARAM_H
