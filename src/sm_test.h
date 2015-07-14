/*
 * File:   sm_test.h
 * Author: janbar
 *
 * Created on 27 juin 2015
 */

#ifndef SM_TEST_H
#define	SM_TEST_H

#include "testsuite.h"
#include <client.h>
#include <cppmyth/MythScheduleManager.h>

class sm_test : public pvrtest::UnitTest
{
public:
  virtual ~sm_test() {}
  virtual void RunTest();

private:

  bool sm_test_1(const char* tag, TimerTypeId type, MythScheduleManager* ms, const MythTimerEntry& entry,
        bool (*test)(const MythTimerEntry&, const MythTimerEntry&));

  static bool check1(const MythTimerEntry& inEntry, const MythTimerEntry& outEntry)
  {
    return inEntry.timerType == outEntry.timerType
            && inEntry.epgCheck == outEntry.epgCheck
            && (inEntry.chanid == outEntry.chanid || (inEntry.epgCheck && inEntry.epgInfo.ChannelID() == outEntry.chanid))
            && (inEntry.callsign == outEntry.callsign || (inEntry.epgCheck && inEntry.epgInfo.Callsign() == outEntry.callsign))
            && inEntry.epgSearch == outEntry.epgSearch
            && inEntry.category == outEntry.category
            && inEntry.title == outEntry.title
            && inEntry.priority == outEntry.priority
            && inEntry.expiration == outEntry.expiration
            && inEntry.dupMethod == outEntry.dupMethod
            && inEntry.startOffset == outEntry.startOffset
            && inEntry.endOffset == outEntry.endOffset
            && (inEntry.startTime == outEntry.startTime || (inEntry.epgCheck && inEntry.epgInfo.StartTime() == outEntry.startTime))
            && (inEntry.endTime == outEntry.endTime || (inEntry.epgCheck && inEntry.epgInfo.EndTime() == outEntry.endTime))
            ;
  }

  static bool check2(const MythTimerEntry& inEntry, const MythTimerEntry& outEntry)
  {
    return inEntry.timerType == outEntry.timerType
            && inEntry.epgCheck == outEntry.epgCheck
            && (inEntry.chanid == outEntry.chanid || (inEntry.epgCheck && inEntry.epgInfo.ChannelID() == outEntry.chanid))
            && (inEntry.callsign == outEntry.callsign || (inEntry.epgCheck && inEntry.epgInfo.Callsign() == outEntry.callsign))
            //&& inEntry.epgSearch == outEntry.epgSearch
            && inEntry.category == outEntry.category
            && inEntry.title == outEntry.title
            && inEntry.priority == outEntry.priority
            && inEntry.expiration == outEntry.expiration
            && inEntry.dupMethod == outEntry.dupMethod
            && inEntry.startOffset == outEntry.startOffset
            && inEntry.endOffset == outEntry.endOffset
            && (inEntry.startTime == outEntry.startTime || (inEntry.epgCheck && inEntry.epgInfo.StartTime() == outEntry.startTime))
            && (inEntry.endTime == outEntry.endTime || (inEntry.epgCheck && inEntry.epgInfo.EndTime() == outEntry.endTime))
            ;
  }

  static bool check3(const MythTimerEntry& inEntry, const MythTimerEntry& outEntry)
  {
    return inEntry.timerType == outEntry.timerType
            && inEntry.epgCheck == outEntry.epgCheck
            //&& (inEntry.chanid == outEntry.chanid || (inEntry.epgCheck && inEntry.epgInfo.ChannelID() == outEntry.chanid))
            //&& (inEntry.callsign == outEntry.callsign || (inEntry.epgCheck && inEntry.epgInfo.Callsign() == outEntry.callsign))
            //&& inEntry.epgSearch == outEntry.epgSearch
            && inEntry.category == outEntry.category
            && inEntry.title == outEntry.title
            && inEntry.priority == outEntry.priority
            && inEntry.expiration == outEntry.expiration
            && inEntry.dupMethod == outEntry.dupMethod
            && inEntry.startOffset == outEntry.startOffset
            && inEntry.endOffset == outEntry.endOffset
            && (inEntry.startTime == outEntry.startTime || (inEntry.epgCheck && inEntry.epgInfo.StartTime() == outEntry.startTime))
            && (inEntry.endTime == outEntry.endTime || (inEntry.epgCheck && inEntry.epgInfo.EndTime() == outEntry.endTime))
            ;
  }

  static bool check4(const MythTimerEntry& inEntry, const MythTimerEntry& outEntry)
  {
    return inEntry.timerType == outEntry.timerType
            //&& inEntry.epgCheck == outEntry.epgCheck
            && (inEntry.chanid == outEntry.chanid || (inEntry.epgCheck && inEntry.epgInfo.ChannelID() == outEntry.chanid))
            && (inEntry.callsign == outEntry.callsign || (inEntry.epgCheck && inEntry.epgInfo.Callsign() == outEntry.callsign))
            && inEntry.epgSearch == outEntry.epgSearch
            && inEntry.category == outEntry.category
            && inEntry.title == outEntry.title
            && inEntry.priority == outEntry.priority
            && inEntry.expiration == outEntry.expiration
            && inEntry.dupMethod == outEntry.dupMethod
            && inEntry.startOffset == outEntry.startOffset
            && inEntry.endOffset == outEntry.endOffset
            && (inEntry.startTime == outEntry.startTime || (inEntry.epgCheck && inEntry.epgInfo.StartTime() == outEntry.startTime))
            && (inEntry.endTime == outEntry.endTime || (inEntry.epgCheck && inEntry.epgInfo.EndTime() == outEntry.endTime))
            ;
  }
};

#endif	/* SM_TEST_H */

