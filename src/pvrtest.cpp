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

#include "sm_test.h"

using namespace ADDON;

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

  g_bExtraDebug = false;
  g_szMythHostname = "localhost";
  g_iProtoPort = 6543;
  g_iWSApiPort = 6544;
  g_szWSSecurityPin = "0000";

  char *buf;

  buf = getCmdOption(argv, argv + argc, "--help");
  if (buf)
  {
    printUsage();
    return EXIT_SUCCESS;
  }

  if ((buf = getCmdOption(argv, argv + argc, "--mythtvhost"))
          || (buf = getCmdOption(argv, argv + argc, "-h")))
    g_szMythHostname = buf;
  else
  {
    printUsage();
    return EXIT_FAILURE;
  }
  if ((buf = getCmdOption(argv, argv + argc, "--protoport"))
          || (buf = getCmdOption(argv, argv + argc, "-p")))
    g_iProtoPort = atoi(buf);
  if ((buf = getCmdOption(argv, argv + argc, "--wsapiport"))
          || (buf = getCmdOption(argv, argv + argc, "-w")))
    g_iWSApiPort = atoi(buf);
  if ((buf = getCmdOption(argv, argv + argc, "--wsapipin"))
          || (buf = getCmdOption(argv, argv + argc, "-s")))
    g_szWSSecurityPin = buf;

  ADDON::addon_log_t loglevel = ADDON::LOG_ERROR;
  if ((buf = getCmdOption(argv, argv + argc, "--loglevel"))
          || (buf = getCmdOption(argv, argv + argc, "-l")))
  {
    if (strncmp(buf, "debug", 5) == 0) loglevel = ADDON::LOG_DEBUG;
    else if (strncmp(buf, "warning", 7) == 0) loglevel = ADDON::LOG_NOTICE;
    else if (strncmp(buf, "info", 4) == 0) loglevel = ADDON::LOG_INFO;
    else if (strncmp(buf, "extradebug", 10) == 0) { loglevel = ADDON::LOG_DEBUG; g_bExtraDebug = true; }
    else loglevel = ADDON::LOG_ERROR;
  }

  buf = NULL;

  // Initialize global variables used by PVRClientMythTV
  // normally, those would be loaded in client.cpp.
  static PVRClientMythTV              *m_myth;
  static CHelper_libXBMC_addon        *m_xbmc_addon;
  static CHelper_libXBMC_pvr          *m_xbmc_pvr;
  static CHelper_libXBMC_codec        *m_xbmc_codec;
  //static CHelper_libKODI_guilib       *m_kodi_guilib;

  m_xbmc_addon = new CHelper_libXBMC_addon();
  XBMC = m_xbmc_addon;

  m_xbmc_pvr = new CHelper_libXBMC_pvr();
  PVR = m_xbmc_pvr;

  m_xbmc_codec = new CHelper_libXBMC_codec();
  CODEC = m_xbmc_codec;

  XBMC->SetLogLevel(loglevel);

  // Establish MythTV connection
  m_myth = new PVRClientMythTV();
  bool connected = m_myth->Connect();
  assert(connected);

  // Get timer types
  {
    int size = 32;
    PVR_TIMER_TYPE* timerTypes = new PVR_TIMER_TYPE[size];
    m_myth->GetTimerTypes(timerTypes, &size);
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

  delete m_myth;
  delete m_xbmc_codec;
  delete m_xbmc_pvr;
  delete m_xbmc_addon;
#ifdef __WINDOWS__
  WSACleanup();
#endif /* __WINDOWS__ */
  return EXIT_SUCCESS;
}
