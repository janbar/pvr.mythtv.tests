/*
 * File:   pvrtest.cpp
 * Author: janbar
 *
 * Created on 27 juin 2015
 */

#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <vector>

#include <client.h>
#include <pvrclient-mythtv.h>
#include <platform/util/timeutils.h>

#include "pvrtest.h"
#include "kodi/xbmc_addon_dll.h"
#include "kodi/xbmc_pvr_dll.h"
#include "sm_test.h"

using namespace ADDON;

PVRTEST_SETTINGS* pvr_settings = 0;
PVR_PROPERTIES*   pvr_props = 0;
PVRClient*        pvr_client = 0;

static char* getCmdOption(char **begin, char **end, const char* option)
{
  unsigned optionlen = strlen(option);
  for (char** itr = begin; itr < end; ++itr)
  {
    if (strncmp(option, *itr, optionlen) == 0)
    {
      char* tmp = *itr;
      while (*tmp && *tmp != '=') ++tmp;
      if (*tmp == '=')
        return ++tmp;
      if (++itr < end)
        return *itr;
      return tmp;
    }
  }
  return NULL;
}

static void printUsage()
{
  std::cout << "Option: (*) argument is required" << std::endl << std::endl;
  std::cout << "    (*) -h or --mythtvhost    <MythTV backend hostname or IP>" << std::endl;
  std::cout << "        -p or --protoport     <proto port [6544]>" << std::endl;
  std::cout << "        -w or --wsapiport     <WSAPI port [6543]>" << std::endl;
  std::cout << "        -s or --wsapipin      <WSAPI security pin [0000]>" << std::endl;
  std::cout << "        -l or --loglevel      <debug|warning|info|error|extradebug>" << std::endl;
}

int main(int argc, char** argv)
{
#ifdef __WINDOWS__
  //Initialize Winsock
  int ret = 0;
  WSADATA wsaData;
  if ((ret = WSAStartup(MAKEWORD(2, 2), &wsaData)))
    return ret;
#endif /* __WINDOWS__ */

  pvr_settings = new(PVRTEST_SETTINGS);
  pvr_settings->extradebug = 0;
  pvr_settings->host = "localhost";
  pvr_settings->port = 6543;
  pvr_settings->wsport = 6544;
  pvr_settings->wssecuritypin = "0000";
  pvr_settings->livetv = 1;
  pvr_settings->livetv_conflict_method = 1;
  pvr_settings->rec_template_provider = 1;
  pvr_settings->demuxing = 0;
  pvr_settings->tunedelay = 5;
  pvr_settings->group_recordings = 0;
  pvr_settings->enable_edl = 0;
  pvr_settings->block_shutdown = 1;
  pvr_settings->channel_icons = 1;
  pvr_settings->recording_icons = 1;
  pvr_settings->limit_tune_attempts = 1;

  char *buf;

  buf = getCmdOption(argv, argv + argc, "--help");
  if (buf)
  {
    printUsage();
    return EXIT_SUCCESS;
  }

  if ((buf = getCmdOption(argv, argv + argc, "--mythtvhost"))
          || (buf = getCmdOption(argv, argv + argc, "-h")))
    pvr_settings->host = buf;
  else
  {
    printUsage();
    return EXIT_FAILURE;
  }
  if ((buf = getCmdOption(argv, argv + argc, "--protoport"))
          || (buf = getCmdOption(argv, argv + argc, "-p")))
    pvr_settings->port = atoi(buf);
  if ((buf = getCmdOption(argv, argv + argc, "--wsapiport"))
          || (buf = getCmdOption(argv, argv + argc, "-w")))
    pvr_settings->wsport = atoi(buf);
  if ((buf = getCmdOption(argv, argv + argc, "--wsapipin"))
          || (buf = getCmdOption(argv, argv + argc, "-s")))
    pvr_settings->wssecuritypin = buf;

  ADDON::addon_log_t loglevel = ADDON::LOG_ERROR;
  if ((buf = getCmdOption(argv, argv + argc, "--loglevel"))
          || (buf = getCmdOption(argv, argv + argc, "-l")))
  {
    if (strncmp(buf, "debug", 5) == 0) loglevel = ADDON::LOG_DEBUG;
    else if (strncmp(buf, "warning", 7) == 0) loglevel = ADDON::LOG_NOTICE;
    else if (strncmp(buf, "info", 4) == 0) loglevel = ADDON::LOG_INFO;
    else if (strncmp(buf, "extradebug", 10) == 0)
    {
      loglevel = ADDON::LOG_DEBUG;
      pvr_settings->extradebug = 1;
    }
    else loglevel = ADDON::LOG_ERROR;
  }

  buf = NULL;

  pvr_props = new(PVR_PROPERTIES);
  pvr_props->strClientPath = "";
  pvr_props->strUserPath = "";

  pvr_client = new(PVRClient);
  get_addon(pvr_client);
  ADDON_STATUS status = ADDON_Create(pvr_client, pvr_props);
  assert(status == ADDON_STATUS_OK);
  XBMC->SetLogLevel(loglevel);

  // Get timer types
  {
    int size = 32;
    PVR_TIMER_TYPE* timerTypes = new PVR_TIMER_TYPE[size];
    pvr_client->GetTimerTypes(timerTypes, &size);
    for (int i = 0; i < size; ++i) { fprintf(stdout, ">>> Get timer type %2.2d:%s:%u\n", i, timerTypes[i].strDescription, timerTypes[i].iAttributes); }
    delete[] timerTypes;
  }

  PLATFORM::CTimeout timeout(5000);
  while (timeout.TimeLeft() > 0)
  {
    fprintf(stdout, "### WARNING ### Tests suite will be launched in %0.1f sec\n", (float)timeout.TimeLeft() / 1000.0);
    usleep(999999);
  }

  {
    pvrtest::TestSuite suite;
    suite.AddUnitTest(new sm_test());
    suite.RunAll();
  }

  ADDON_Destroy();
  delete pvr_client;
  delete pvr_props;
  delete pvr_settings;

#ifdef __WINDOWS__
  WSACleanup();
#endif /* __WINDOWS__ */
  return EXIT_SUCCESS;
}
