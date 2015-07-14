#pragma once

#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>

#ifdef _WIN32                   // windows
#ifndef snprintf
#define snprintf _snprintf
#endif
#ifndef strnicmp
#define strnicmp _strnicmp
#endif
#ifndef _SSIZE_T_DEFINED
typedef intptr_t      ssize_t;
#define _SSIZE_T_DEFINED
#endif // !_SSIZE_T_DEFINED
#include "dlfcn-win32.h"
#define ADDON_DLL               "\\library.xbmc.addon\\libXBMC_addon" ADDON_HELPER_EXT
#define ADDON_HELPER_EXT        ".dll"
#else
#if defined(__APPLE__)          // osx
#if defined(__POWERPC__)
#define ADDON_HELPER_ARCH       "powerpc-osx"
#elif defined(__arm__)
#define ADDON_HELPER_ARCH       "arm-osx"
#elif defined(__x86_64__)
#define ADDON_HELPER_ARCH       "x86-osx"
#else
#define ADDON_HELPER_ARCH       "x86-osx"
#endif
#else                           // linux
#if defined(__x86_64__)
#define ADDON_HELPER_ARCH       "x86_64-linux"
#elif defined(_POWERPC)
#define ADDON_HELPER_ARCH       "powerpc-linux"
#elif defined(_POWERPC64)
#define ADDON_HELPER_ARCH       "powerpc64-linux"
#elif defined(__ARMEL__)
#define ADDON_HELPER_ARCH       "arm"
#elif defined(__mips__)
#define ADDON_HELPER_ARCH       "mips"
#else
#define ADDON_HELPER_ARCH       "i486-linux"
#endif
#endif
#include <dlfcn.h>              // linux+osx
#define ADDON_HELPER_EXT        ".so"
#define ADDON_DLL_NAME "libXBMC_addon-" ADDON_HELPER_ARCH ADDON_HELPER_EXT
#define ADDON_DLL "/library.xbmc.addon/" ADDON_DLL_NAME
#endif
#if defined(ANDROID)
#include <sys/stat.h>
#endif

#ifdef LOG_DEBUG
#undef LOG_DEBUG
#endif
#ifdef LOG_INFO
#undef LOG_INFO
#endif
#ifdef LOG_NOTICE
#undef LOG_NOTICE
#endif
#ifdef LOG_ERROR
#undef LOG_ERROR
#endif

#include <cstdio>
#include <cctype>
#include <iostream>

using namespace ::std;

namespace ADDON
{
  typedef enum addon_log
  {
    LOG_DEBUG,
    LOG_INFO,
    LOG_NOTICE,
    LOG_ERROR
  } addon_log_t;

  typedef enum queue_msg
  {
    QUEUE_INFO,
    QUEUE_WARNING,
    QUEUE_ERROR
  } queue_msg_t;

  class CHelper_libXBMC_addon
  {
  public:
    CHelper_libXBMC_addon() : m_logLevel(LOG_ERROR)
    {
    }
    ~CHelper_libXBMC_addon() {}

    bool RegisterMe(void *Handle)
    {
      return Handle != NULL;
    }

    void SetLogLevel(addon_log_t loglevel)
    {
      m_logLevel = loglevel;
    }

    void Log(const addon_log_t loglevel, const char *format, ... )
    {
      if (loglevel < m_logLevel)
        return;
      char buffer[16384];
      va_list args;
      va_start (args, format);
      vsprintf (buffer, format, args);
      va_end (args);
      log(loglevel, buffer);
    }

    bool GetSetting(const char* settingName, void *settingValue) { return false; }

    void QueueNotification(const queue_msg_t type, const char *format, ... )
    {
      char buffer[16384];
      va_list args;
      va_start (args, format);
      vsprintf (buffer, format, args);
      va_end (args);
      notify(type, buffer);
    }

    bool WakeOnLan(const char* mac) { return true; }
    char* UnknownToUTF8(const char* str) { static char buf[255]; strncpy(buf, str, sizeof(buf)); return buf; }
    char* GetLocalizedString(int dwCode) { static char buf[255]; snprintf(buf, sizeof(buf), "string#%d", dwCode); return buf; }
    char* GetDVDMenuLanguage() { static char buf[3] = { 'e', 'n', '\0' }; return buf; }
    void FreeString(char* str) {}
    void* OpenFile(const char* strFileName, unsigned int flags) { return NULL; }
    void* OpenFileForWrite(const char* strFileName, bool bOverWrite) { return NULL; }
    unsigned int ReadFile(void* file, void* lpBuf, int64_t uiBufSize) { return 0; }
    bool ReadFileString(void* file, char *szLine, int iLineLength) { return false; }
    int WriteFile(void* file, const void* lpBuf, int64_t uiBufSize) { return 0; }
    void FlushFile(void* file) {}
    int64_t SeekFile(void* file, int64_t iFilePosition, int iWhence) { return 0; }
    int TruncateFile(void* file, int64_t iSize) { return 0; }
    int64_t GetFilePosition(void* file) { return 0; }
    int64_t GetFileLength(void* file) { return 0; }
    void CloseFile(void* file) {}
    void GetFileChunkSize(void* file) {}
    bool FileExists(const char *strFileName, bool bUseCache) { return false; }
    int StatFile(const char *strFileName, struct __stat64* buffer) { return 0; }
    bool DeleteFile(const char *strFileName) { return false; }
    bool CanOpenDirectory(const char* strUrl) { return false; }
    bool CreateDirectory(const char *strPath) { return false; }
    bool DirectoryExists(const char *strPath) { return false; }
    bool RemoveDirectory(const char *strPath) { return false; }

  private:

    addon_log_t m_logLevel;

    static void log(const ADDON::addon_log_t loglevel, char *buffer)
    {
      char* last = buffer;
      switch (loglevel)
      {
        case LOG_DEBUG:
          fprintf(stdout, "LOGD: "); break;
        case LOG_INFO:
          fprintf(stdout, "LOGI: "); break;
        case LOG_NOTICE:
          fprintf(stdout, "LOGN: "); break;
        case LOG_ERROR:
          fprintf(stdout, "LOGE: "); break;
      }
      while (*buffer)
      {
        fputc(*buffer, stdout);
        last = buffer++;
      }
      if (std::iscntrl(*last) == 0)
        fprintf(stdout, "\n");
    }

    static void notify(const ADDON::queue_msg_t type, char *buffer)
    {
      switch (type)
      {
        case QUEUE_INFO:
          fprintf(stdout, "QUEI: "); break;
        case QUEUE_WARNING:
          fprintf(stdout, "QUEW: "); break;
        case QUEUE_ERROR:
          fprintf(stdout, "QUEE: "); break;
      }
      fprintf(stdout, "%s", buffer);
    }
  };
}

