project(mock)

cmake_minimum_required (VERSION 2.6 FATAL_ERROR)
cmake_policy (VERSION 2.6)

#
# Install mocked headers
configure_file(libXBMC_addon.h ${CMAKE_BINARY_DIR}/include/kodi/libXBMC_addon.h COPYONLY)
configure_file(libXBMC_codec.h ${CMAKE_BINARY_DIR}/include/kodi/libXBMC_codec.h COPYONLY)
configure_file(libXBMC_pvr.h ${CMAKE_BINARY_DIR}/include/kodi/libXBMC_pvr.h COPYONLY)
configure_file(libKODI_guilib.h ${CMAKE_BINARY_DIR}/include/kodi/libKODI_guilib.h COPYONLY)
