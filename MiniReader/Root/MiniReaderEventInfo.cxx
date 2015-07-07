#include "MiniReader/MiniReaderEventInfo.h"

////////////////////////////////////////////////////////////////////////////////
//// Default constructor of the class
////////////////////////////////////////////////////////////////////////////////
MiniReaderEventInfo::MiniReaderEventInfo()
{
  m_EventNumber = 0;
  m_RunNumber = 0;
  m_mc_channel_number = 0;
  m_actualInteractionsPerCrossing = 0;
  m_averageInteractionsPerCrossing = 0;
  m_global_event_weight = 0;
  m_mc_event_weight = 0;
}

////////////////////////////////////////////////////////////////////////////////
//// Read the branches of the TTree
////////////////////////////////////////////////////////////////////////////////
void MiniReaderEventInfo::ReadEventInfoBranches(TTree *tree)
{
  tree->SetBranchAddress("EventNumber", &m_EventNumber);
  tree->SetBranchAddress("RunNumber", &m_RunNumber);
  tree->SetBranchAddress("MCChannelNumber", &m_mc_channel_number);
  tree->SetBranchAddress("actualInteractionsPerCrossing", &m_actualInteractionsPerCrossing);
  tree->SetBranchAddress("averageInteractionsPerCrossing", &m_averageInteractionsPerCrossing);
  tree->SetBranchAddress("global_event_weight", &m_global_event_weight);
  tree->SetBranchAddress("mc_event_weight", &m_mc_event_weight);
}

////////////////////////////////////////////////////////////////////////////////
//// Getter fot the average numbero of interaction per bunch crossing
////////////////////////////////////////////////////////////////////////////////
float MiniReaderEventInfo::GetAvgIntPerCross() const
{
  return m_averageInteractionsPerCrossing;
}
