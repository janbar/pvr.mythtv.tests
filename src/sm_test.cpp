/*
 * File:   sm_test.cpp
 * Author: janbar
 *
 * Created on 27 juin 2015
 */

#include "sm_test.h"
#include <cppmyth/MythScheduleHelperNoHelper.h>
#include <tools.h>

using namespace ADDON;

static void print_report(const MythTimerEntry& inEntry, const MythTimerEntry& outEntry, const MythRecordingRule& rule);

bool sm_test::sm_test_1(const char* tag, TimerTypeId type, MythScheduleManager* ms, const MythTimerEntry& entry,
        bool (*test)(const MythTimerEntry&, const MythTimerEntry&))
{
  MythTimerEntry inEntry = entry;
  inEntry.timerType = type;
  MythRecordingRule rule = ms->NewFromTimer(inEntry, false);
  MythTimerEntry outEntry;

  if (rule.Type() == Myth::RT_UNKNOWN || !ms->FillTimerEntryWithRule(outEntry, rule))
  {
    Out(pvrtest::TEST_INCOMPLETE, "%s (%d)", tag, type);
    return true;
  }

  bool ret = (*test)(inEntry, outEntry);

  Out((ret ? pvrtest::TEST_SUCCEEDED : pvrtest::TEST_FAILED), "%s (%d)", tag, type);
  if (!ret)
    print_report(inEntry, outEntry, rule);
  return ret;
}

void sm_test::RunTest()
{
  MythScheduleManager* ms = new MythScheduleManager(g_szMythHostname, g_iProtoPort, g_iWSApiPort, g_szWSSecurityPin);
  g_iRecTemplateType = 0;

  time_t now = time(NULL);

  Myth::ProgramPtr programPtr(new Myth::Program);
  time_t st = now;
  timeadd(&st, -86400);
  programPtr->startTime = st;
  timeadd(&st, 3600);
  programPtr->endTime = st;
  programPtr->category = "News magazine";
  programPtr->catType = "News";
  programPtr->title = "My news";
  programPtr->channel.callSign = "CHANNEL 101";
  programPtr->channel.chanId = 101;
  programPtr->description = "The regular news: weather report, magazine, sports";
  programPtr->subTitle = "20h news";
  programPtr->programId = "P0000001";
  programPtr->seriesId = "S0000001";

  MythEPGInfo epgInfo(programPtr);

  MythTimerEntry in_epg, in_sch, in_sch_ch, in_ch_ts;

  in_epg.epgInfo = epgInfo;
  in_epg.epgCheck = true;
  in_epg.chanid = 101;
  in_epg.callsign = "CHANNEL 101";
  in_epg.epgSearch = "news";
  in_epg.title = "My news";
  in_epg.category = "News magazine";
  in_epg.priority = -10;
  in_epg.expiration = EXPIRATION_ALLOW_EXPIRE_ID;
  in_epg.dupMethod = Myth::DM_CheckSubtitle;
  in_epg.startOffset = 11;
  in_epg.endOffset = 18;

  in_sch.chanid = 0;
  in_sch.callsign = "";
  in_sch.epgSearch = "news";
  in_sch.title = "My news";
  in_sch.category = "";
  in_sch.priority = -10;
  in_sch.expiration = EXPIRATION_ALLOW_EXPIRE_ID;
  in_sch.dupMethod = Myth::DM_CheckSubtitle;
  in_sch.startOffset = 11;
  in_sch.endOffset = 18;

  in_sch_ch.chanid = 101;
  in_sch_ch.callsign = "CHANNEL 101";
  in_sch_ch.epgSearch = "news";
  in_sch_ch.title = "My news";
  in_sch_ch.category = "";
  in_sch_ch.priority = -10;
  in_sch_ch.expiration = EXPIRATION_ALLOW_EXPIRE_ID;
  in_sch_ch.dupMethod = Myth::DM_CheckSubtitle;
  in_sch_ch.startOffset = 11;
  in_sch_ch.endOffset = 18;

  in_ch_ts.chanid = 101;
  in_ch_ts.callsign = "CHANNEL 101";
  in_ch_ts.epgSearch = "";
  in_ch_ts.title = "My news";
  in_ch_ts.category = "";
  in_ch_ts.priority = -10;
  in_ch_ts.expiration = EXPIRATION_ALLOW_EXPIRE_ID;
  in_ch_ts.dupMethod = Myth::DM_CheckSubtitle;
  in_ch_ts.startOffset = 11;
  in_ch_ts.endOffset = 18;
  in_ch_ts.startTime = programPtr->startTime;
  in_ch_ts.endTime = programPtr->endTime;

  sm_test_1("Record this - epg-based", TIMER_TYPE_THIS_SHOWING, ms, in_epg, &check1);
  sm_test_1("Record one (any channel) - epg-based", TIMER_TYPE_RECORD_ONE, ms, in_epg, &check3); //no search, no chan
  sm_test_1("Record all (this channel) - epg-based", TIMER_TYPE_RECORD_ALL, ms, in_epg, &check2); //no search
  sm_test_1("Record series (this channel) - epg-based", TIMER_TYPE_RECORD_SERIES, ms, in_epg, &check2); //no search
  sm_test_1("Search keyword (this channel) - epg-based", TIMER_TYPE_SEARCH_KEYWORD, ms, in_epg, &check4);
  sm_test_1("Search people (this channel) - epg-based", TIMER_TYPE_SEARCH_PEOPLE, ms, in_epg, &check4);
  in_epg.dupMethod = Myth::DM_CheckNone;
  sm_test_1("Record daily (this channel) - epg-based", TIMER_TYPE_RECORD_DAILY, ms, in_epg, &check2); //no search
  sm_test_1("Record weekly (this channel) - epg-based", TIMER_TYPE_RECORD_WEEKLY, ms, in_epg, &check2); //no search

  sm_test_1("Record this - search any channel", TIMER_TYPE_THIS_SHOWING, ms, in_sch, &check1);
  sm_test_1("Record one - search any channel", TIMER_TYPE_RECORD_ONE, ms, in_sch, &check1);
  sm_test_1("Record all - search any channel", TIMER_TYPE_RECORD_ALL, ms, in_sch, &check1);
  sm_test_1("Search keyword - search any channel", TIMER_TYPE_SEARCH_KEYWORD, ms, in_sch, &check1);
  sm_test_1("Search people - search any channel", TIMER_TYPE_SEARCH_PEOPLE, ms, in_sch, &check1);
  in_sch.dupMethod = Myth::DM_CheckNone;
  sm_test_1("Record daily - search any channel", TIMER_TYPE_RECORD_DAILY, ms, in_sch, &check1);
  sm_test_1("Record weekly - search any channel", TIMER_TYPE_RECORD_WEEKLY, ms, in_sch, &check1);

  sm_test_1("Record this - search this channel", TIMER_TYPE_THIS_SHOWING, ms, in_sch_ch, &check1);
  sm_test_1("Record one - search this channel", TIMER_TYPE_RECORD_ONE, ms, in_sch_ch, &check1);
  sm_test_1("Record all - search this channel", TIMER_TYPE_RECORD_ALL, ms, in_sch_ch, &check1);
  sm_test_1("Search keyword - search this channel", TIMER_TYPE_SEARCH_KEYWORD, ms, in_sch_ch, &check1);
  sm_test_1("Search people - search this channel", TIMER_TYPE_SEARCH_PEOPLE, ms, in_sch_ch, &check1);
  in_sch_ch.dupMethod = Myth::DM_CheckNone;
  sm_test_1("Record daily - search this channel", TIMER_TYPE_RECORD_DAILY, ms, in_sch_ch, &check1);
  sm_test_1("Record weekly - search this channel", TIMER_TYPE_RECORD_WEEKLY, ms, in_sch_ch, &check1);

  sm_test_1("Record this - manual", TIMER_TYPE_THIS_SHOWING, ms, in_ch_ts, &check1);
  in_ch_ts.dupMethod = Myth::DM_CheckNone;
  sm_test_1("Record daily - manual", TIMER_TYPE_RECORD_DAILY, ms, in_ch_ts, &check2); //no search
  sm_test_1("Record weekly - manual", TIMER_TYPE_RECORD_WEEKLY, ms, in_ch_ts, &check2); //no search

  delete ms;
}

static void print_report(const MythTimerEntry& inEntry, const MythTimerEntry& outEntry, const MythRecordingRule& rule)
{
  std::cout << "========================== Report ==========================" << std::endl;
  std::cout << "rule.Type = " << rule.Type() << std::endl;
  std::cout << "rule.Filter = " << rule.Filter() << std::endl;
  std::cout << "rule.SearchType = " << rule.SearchType() << std::endl;
  std::cout << "rule.Inactive = " << rule.Inactive() << std::endl;
  std::cout << "rule.ChannelID = " << rule.ChannelID() << std::endl;
  std::cout << "rule.Callsign = " << rule.Callsign() << std::endl;
  std::cout << "rule.StartTime = " << rule.StartTime() << std::endl;
  std::cout << "rule.EndTime = " << rule.EndTime() << std::endl;
  std::cout << "rule.Title = " << rule.Title() << std::endl;
  std::cout << "rule.Category = " << rule.Category() << std::endl;
  std::cout << "rule.Description = " << rule.Description() << std::endl;
  std::cout << std::endl;

  std::cout << "inEntry.timerType = " << inEntry.timerType << std::endl;
  std::cout << "inEntry.epgCheck = " << inEntry.epgCheck << std::endl;
  std::cout << "inEntry.chanid = " << inEntry.chanid << std::endl;
  std::cout << "inEntry.callsign = " << inEntry.callsign << std::endl;
  std::cout << "inEntry.startTime = " << inEntry.startTime << std::endl;
  std::cout << "inEntry.endTime = " << inEntry.endTime << std::endl;
  std::cout << "inEntry.epgSearch = " << inEntry.epgSearch << std::endl;
  std::cout << "inEntry.category = " << inEntry.category << std::endl;
  std::cout << "inEntry.title = " << inEntry.title << std::endl;
  std::cout << "inEntry.priority = " << inEntry.priority << std::endl;
  std::cout << "inEntry.expiration = " << inEntry.expiration << std::endl;
  std::cout << "inEntry.dupMethod = " << inEntry.dupMethod << std::endl;
  std::cout << "inEntry.startOffset = " << inEntry.startOffset << std::endl;
  std::cout << "inEntry.endOffset = " << inEntry.endOffset << std::endl;
  std::cout << std::endl;

  std::cout << "outEntry.timerType = " << outEntry.timerType << std::endl;
  std::cout << "outEntry.epgCheck = " << outEntry.epgCheck << std::endl;
  std::cout << "outEntry.chanid = " << outEntry.chanid << std::endl;
  std::cout << "outEntry.callsign = " << outEntry.callsign << std::endl;
  std::cout << "outEntry.startTime = " << outEntry.startTime << std::endl;
  std::cout << "outEntry.endTime = " << outEntry.endTime << std::endl;
  std::cout << "outEntry.epgSearch = " << outEntry.epgSearch << std::endl;
  std::cout << "outEntry.category = " << outEntry.category << std::endl;
  std::cout << "outEntry.title = " << outEntry.title << std::endl;
  std::cout << "outEntry.priority = " << outEntry.priority << std::endl;
  std::cout << "outEntry.expiration = " << outEntry.expiration << std::endl;
  std::cout << "outEntry.dupMethod = " << outEntry.dupMethod << std::endl;
  std::cout << "outEntry.startOffset = " << outEntry.startOffset << std::endl;
  std::cout << "outEntry.endOffset = " << outEntry.endOffset << std::endl;
  std::cout << "============================================================" << std::endl;
  std::cout << std::endl;
}
