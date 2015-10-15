#include <kodi/libXBMC_addon.h>

#include <cstring>

#include "pvrtest.h"

bool ADDON::CHelper_libXBMC_addon::GetSetting(const char* settingName, void* settingValue)
{
  if (strcmp(settingName, "host") == 0)
    strcpy(static_cast<char*>(settingValue), pvr_settings->host);
  else if (strcmp(settingName, "port") == 0)
    *static_cast<int*>(settingValue) = pvr_settings->port;
  else if (strcmp(settingName, "wsport") == 0)
    *static_cast<int*>(settingValue) = pvr_settings->wsport;
  else if (strcmp(settingName, "wssecuritypin") == 0)
    strcpy(static_cast<char*>(settingValue), pvr_settings->wssecuritypin);
  else if (strcmp(settingName, "extradebug") == 0)
    *static_cast<bool*>(settingValue) = pvr_settings->extradebug ? true : false;
  else if (strcmp(settingName, "livetv") == 0)
    *static_cast<bool*>(settingValue) = pvr_settings->livetv ? true : false;
  else if (strcmp(settingName, "livetv_conflict_method") == 0)
    *static_cast<int*>(settingValue) = pvr_settings->livetv_conflict_method;
  else if (strcmp(settingName, "rec_template_provider") == 0)
    *static_cast<int*>(settingValue) = pvr_settings->rec_template_provider;
  else if (strcmp(settingName, "demuxing") == 0)
    *static_cast<bool*>(settingValue) = pvr_settings->demuxing ? true : false;
  else if (strcmp(settingName, "tunedelay") == 0)
    *static_cast<int*>(settingValue) = pvr_settings->tunedelay;
  else if (strcmp(settingName, "group_recordings") == 0)
    *static_cast<int*>(settingValue) = pvr_settings->group_recordings;
  else if (strcmp(settingName, "enable_edl") == 0)
    *static_cast<int*>(settingValue) = pvr_settings->enable_edl;
  else if (strcmp(settingName, "block_shutdown") == 0)
    *static_cast<bool*>(settingValue) = pvr_settings->block_shutdown ? true : false;
  else if (strcmp(settingName, "channel_icons") == 0)
    *static_cast<bool*>(settingValue) = pvr_settings->channel_icons ? true : false;
  else if (strcmp(settingName, "recording_icons") == 0)
    *static_cast<bool*>(settingValue) = pvr_settings->recording_icons ? true : false;
  else if (strcmp(settingName, "limit_tune_attempts") == 0)
    *static_cast<bool*>(settingValue) = pvr_settings->limit_tune_attempts ? true : false;
  else
    return false;
  return true;
}
