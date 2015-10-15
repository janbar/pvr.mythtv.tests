project(pvr.test)

cmake_minimum_required(VERSION 2.6)

set(APP_VERSION_MAJOR "16" CACHE string "Application version major")
set(APP_VERSION_MINOR "0" CACHE string "Application verison minor")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

enable_language(CXX)
enable_language(C)

include_directories(${CMAKE_BINARY_DIR}/include
                    ${PROJECT_SOURCE_DIR}/pvr.mythtv/lib/cppmyth/src
                    ${PROJECT_SOURCE_DIR}/pvr.mythtv/src
                    ${PROJECT_SOURCE_DIR}/src)

add_definitions(-DUSE_DEMUX -D__STDC_FORMAT_MACROS)

if(NOT WIN32)
  add_definitions("-fPIC -Wall")
else()
  add_definitions(-DTARGET_WINDOWS -D_WINSOCKAPI_
    -D_USE_32BIT_TIME_T -D_CRT_SECURE_NO_WARNINGS
    -D_SCL_SECURE_NO_WARNINGS -D__STDC_CONSTANT_MACROS)
  set(CMAKE_CXX_FLAGS_RELEASE "/MT /W3 /Od /RTC1 /EHsc")
  set(CMAKE_CXX_FLAGS_DEBUG "/MTd /W3 /Od /RTC1 /EHsc")
  set(CMAKE_C_FLAGS_RELEASE "/MT /W3")
  set(CMAKE_C_FLAGS_DEBUG "/MTd /W3")
endif()

add_subdirectory(pvr.mythtv)
add_subdirectory(mock)

set(pvrtest_SOURCES
    src/libXBMC_pvr.cpp
    src/libXBMC_addon.cpp
    src/pvrtest.cpp
    src/sm_test.cpp)

if(NOT WIN32 AND (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX))
  if(HAS_BUILTIN_SYNC_ADD_AND_FETCH)
    add_definitions("-DHAS_BUILTIN_SYNC_ADD_AND_FETCH")
  endif()
  if(HAS_BUILTIN_SYNC_SUB_AND_FETCH)
    add_definitions("-DHAS_BUILTIN_SYNC_SUB_AND_FETCH")
  endif()
endif()

set(DEPLIBS pvr.mythtv)
if(NOT WIN32)
  list(APPEND DEPLIBS dl)
endif()

add_executable (pvrtest ${pvrtest_SOURCES})
target_link_libraries (pvrtest ${DEPLIBS})
