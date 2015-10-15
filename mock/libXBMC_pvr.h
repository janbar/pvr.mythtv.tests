#pragma once
/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "xbmc_pvr_types.h"
#include "libXBMC_addon.h"

#define DVD_TIME_BASE 1000000
#define DVD_NOPTS_VALUE    (-1LL<<52) // should be possible to represent in both double and __int64

class CHelper_libXBMC_pvr
{
public:
  CHelper_libXBMC_pvr(void)
  {
  }

  ~CHelper_libXBMC_pvr(void)
  {
  }

  /*!
   * @brief Resolve all callback methods
   * @param handle Pointer to the add-on
   * @return True when all methods were resolved, false otherwise.
   */
    bool RegisterMe(void *Handle);

  /*!
   * @brief Transfer an EPG tag from the add-on to XBMC
   * @param handle The handle parameter that XBMC used when requesting the EPG data
   * @param entry The entry to transfer to XBMC
   */
  void TransferEpgEntry(const ADDON_HANDLE handle, const EPG_TAG* entry);

  /*!
   * @brief Transfer a channel entry from the add-on to XBMC
   * @param handle The handle parameter that XBMC used when requesting the channel list
   * @param entry The entry to transfer to XBMC
   */
  void TransferChannelEntry(const ADDON_HANDLE handle, const PVR_CHANNEL* entry);

  /*!
   * @brief Transfer a timer entry from the add-on to XBMC
   * @param handle The handle parameter that XBMC used when requesting the timers list
   * @param entry The entry to transfer to XBMC
   */
  void TransferTimerEntry(const ADDON_HANDLE handle, const PVR_TIMER* entry);

  /*!
   * @brief Transfer a recording entry from the add-on to XBMC
   * @param handle The handle parameter that XBMC used when requesting the recordings list
   * @param entry The entry to transfer to XBMC
   */
  void TransferRecordingEntry(const ADDON_HANDLE handle, const PVR_RECORDING* entry);

  /*!
   * @brief Transfer a channel group from the add-on to XBMC. The group will be created if it doesn't exist.
   * @param handle The handle parameter that XBMC used when requesting the channel groups list
   * @param entry The entry to transfer to XBMC
   */
  void TransferChannelGroup(const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP* entry);

  /*!
   * @brief Transfer a channel group member entry from the add-on to XBMC. The channel will be added to the group if the group can be found.
   * @param handle The handle parameter that XBMC used when requesting the channel group members list
   * @param entry The entry to transfer to XBMC
   */
  void TransferChannelGroupMember(const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP_MEMBER* entry);

  /*!
   * @brief Add or replace a menu hook for the context menu for this add-on
   * @param hook The hook to add
   */
  void AddMenuHook(PVR_MENUHOOK* hook);

  /*!
   * @brief Display a notification in XBMC that a recording started or stopped on the server
   * @param strRecordingName The name of the recording to display
   * @param strFileName The filename of the recording
   * @param bOn True when recording started, false when it stopped
   */
  void Recording(const char* strRecordingName, const char* strFileName, bool bOn);

  /*!
   * @brief Request XBMC to update it's list of timers
   */
  void TriggerTimerUpdate(void);

  /*!
   * @brief Request XBMC to update it's list of recordings
   */
  void TriggerRecordingUpdate(void);

  /*!
   * @brief Request XBMC to update it's list of channels
   */
  void TriggerChannelUpdate(void);

  /*!
   * @brief Schedule an EPG update for the given channel channel
   * @param iChannelUid The unique id of the channel for this add-on
   */
  void TriggerEpgUpdate(unsigned int iChannelUid);

  /*!
   * @brief Request XBMC to update it's list of channel groups
   */
  void TriggerChannelGroupsUpdate(void);

#ifdef USE_DEMUX
  /*!
   * @brief Free a packet that was allocated with AllocateDemuxPacket
   * @param pPacket The packet to free
   */
  void FreeDemuxPacket(DemuxPacket* pPacket)
  {
    if (pPacket)
    {
      if (pPacket->pData)
        delete[] pPacket->pData;
      delete pPacket;
    }
  }

  /*!
   * @brief Allocate a demux packet. Free with FreeDemuxPacket
   * @param iDataSize The size of the data that will go into the packet
   * @return The allocated packet
   */
  DemuxPacket* AllocateDemuxPacket(int iDataSize)
  {
    unsigned char* data = new unsigned char[iDataSize];
    if (data)
    {
      DemuxPacket* pkt = new DemuxPacket();
      pkt->pData = data;
      return pkt;
    }
    return NULL;
  }
#endif
};
