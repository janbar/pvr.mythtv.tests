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
#include "xbmc_codec_types.h"
#include "libXBMC_addon.h"

#ifdef _WIN32
#define CODEC_HELPER_DLL "\\library.xbmc.codec\\libXBMC_codec" ADDON_HELPER_EXT
#else
#define CODEC_HELPER_DLL_NAME "libXBMC_codec-" ADDON_HELPER_ARCH ADDON_HELPER_EXT
#define CODEC_HELPER_DLL "/library.xbmc.codec/" CODEC_HELPER_DLL_NAME
#endif

class CHelper_libXBMC_codec
{
public:
  CHelper_libXBMC_codec(void)
  {
  }

  ~CHelper_libXBMC_codec(void)
  {
  }

  /*!
   * @brief Resolve all callback methods
   * @param handle Pointer to the add-on
   * @return True when all methods were resolved, false otherwise.
   */
  bool RegisterMe(void* handle)
  {
    return handle != NULL;
  }

  /*!
   * @brief Get the codec id used by XBMC
   * @param strCodecName The name of the codec
   * @return The codec_id, or a codec_id with 0 values when not supported
   */
  xbmc_codec_t GetCodecByName(const char* strCodecName)
  {
    (void)strCodecName;
    xbmc_codec_t codec;
    codec.codec_type = XBMC_CODEC_TYPE_UNKNOWN;
    codec.codec_id = 0;
    return codec;
  }
};

