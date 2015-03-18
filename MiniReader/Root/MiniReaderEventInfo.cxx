#include "MiniReader/MiniReaderEventInfo.h"

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

void MiniReaderEventInfo::ReadEventInfoBranches(TTree *tree)
{
  tree->SetBranchAddress("EventNumber", &m_EventNumber);
  tree->SetBranchAddress("RunNumber", &m_RunNumber);
  tree->SetBranchAddress("mchannel_number", &m_mc_channel_number);
  tree->SetBranchAddress("actualInteractionsPerCrossing", &m_actualInteractionsPerCrossing);
  tree->SetBranchAddress("averageInteractionsPerCrossing", &m_averageInteractionsPerCrossing);
  tree->SetBranchAddress("global_event_weight", &m_global_event_weight);
  tree->SetBranchAddress("mc_event_weight", &m_mc_event_weight);
}
