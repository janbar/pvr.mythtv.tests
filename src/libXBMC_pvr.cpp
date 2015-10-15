#include <kodi/libXBMC_pvr.h>
#include "pvrtest.h"

bool CHelper_libXBMC_pvr::RegisterMe(void* Handle)
{
  return Handle != NULL;
}

void CHelper_libXBMC_pvr::TransferEpgEntry(const ADDON_HANDLE handle, const EPG_TAG* entry)
{
  std::cout << "EPG_TAG.iUniqueBroadcastId = " << entry->iUniqueBroadcastId << std::endl;
  std::cout << "EPG_TAG.strTitle = " << entry->strTitle << std::endl;
  std::cout << "EPG_TAG.iChannelNumber = " << entry->iChannelNumber << std::endl;
  std::cout << "EPG_TAG.startTime = " << entry->startTime << std::endl;
  std::cout << "EPG_TAG.endTime = " << entry->endTime << std::endl;
  std::cout << "EPG_TAG.iGenreType = " << entry->iGenreType << std::endl;
  std::cout << "EPG_TAG.iGenreSubType = " << entry->iGenreSubType << std::endl;
  std::cout << std::endl;
}

void CHelper_libXBMC_pvr::TransferChannelEntry(const ADDON_HANDLE handle, const PVR_CHANNEL* entry)
{
}

void CHelper_libXBMC_pvr::TransferTimerEntry(const ADDON_HANDLE handle, const PVR_TIMER* entry)
{
}

void CHelper_libXBMC_pvr::TransferRecordingEntry(const ADDON_HANDLE handle, const PVR_RECORDING* entry)
{
}

void CHelper_libXBMC_pvr::TransferChannelGroup(const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP* entry)
{
}

void CHelper_libXBMC_pvr::TransferChannelGroupMember(const ADDON_HANDLE handle, const PVR_CHANNEL_GROUP_MEMBER* entry)
{
}

void CHelper_libXBMC_pvr::AddMenuHook(PVR_MENUHOOK* hook)
{
}

void CHelper_libXBMC_pvr::Recording(const char* strRecordingName, const char* strFileName, bool bOn)
{
}

void CHelper_libXBMC_pvr::TriggerTimerUpdate()
{
  std::cout << ">>> " << __FUNCTION__ << std::endl;
}

void CHelper_libXBMC_pvr::TriggerRecordingUpdate()
{
  std::cout << ">>> " << __FUNCTION__ << std::endl;
  pvr_client->GetRecordings(NULL, false);
  pvr_client->GetRecordings(NULL, true);
}

void CHelper_libXBMC_pvr::TriggerChannelUpdate()
{
  std::cout << ">>> " << __FUNCTION__ << std::endl;
}

void CHelper_libXBMC_pvr::TriggerEpgUpdate(unsigned int iChannelUid)
{
  std::cout << ">>> " << __FUNCTION__ << std::endl;
}

void CHelper_libXBMC_pvr::TriggerChannelGroupsUpdate()
{
  std::cout << ">>> " << __FUNCTION__ << std::endl;
}
