set (CMAKE_CXX_STANDARD 11)
cmake_minimum_required(VERSION 3.1.3)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE TYPE INTERNAL FORCE)
project (LimeRFE_8001P)

#include modules for finding CyAPI
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

add_subdirectory(LimeRFE_8001P)
option(BUILD_SHARED_LIBS "Build the shared library" ON)
