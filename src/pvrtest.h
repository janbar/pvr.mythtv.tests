/* 
 * File:   pvrtest.h
 * Author: jlb
 *
 * Created on 13 octobre 2015, 17:21
 */

#ifndef PVRTEST_H
#define	PVRTEST_H

#include <kodi/xbmc_pvr_types.h>

struct PVRTEST_SETTINGS
{
  const char*             host;
  int                     port;
  int                     wsport;
  const char*             wssecuritypin;
  int                     extradebug;
  int                     livetv;
  int                     livetv_conflict_method;
  int                     rec_template_provider;
  int                     demuxing;
  int                     tunedelay;
  int                     group_recordings;
  int                     enable_edl;
  int                     block_shutdown;
  int                     channel_icons;
  int                     recording_icons;
  int                     limit_tune_attempts;
};

extern PVRTEST_SETTINGS*  pvr_settings;

extern PVR_PROPERTIES*    pvr_props;

extern PVRClient*         pvr_client;

#endif	/* PVRTEST_H */

