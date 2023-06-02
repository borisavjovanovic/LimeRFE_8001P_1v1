/**
@file VersionInfo.cpp
@author Lime Microsystems
@brief API for querying version and build information.
*/

#include "VersionInfo.h"
#include <sstream>

#define QUOTE_(x) #x
#define QUOTE(x) QUOTE_(x)

std::string lime::GetLibraryVersion(void)
{
    return "";
}

std::string lime::GetBuildTimestamp(void)
{
    return "";
}

std::string lime::GetAPIVersion(void)
{
    const std::string verStr(QUOTE(LIME_SUITE_API_VERSION));
    std::stringstream ss;
    ss << std::stoi(verStr.substr(2, 4)) << "."
       << std::stoi(verStr.substr(6, 2)) << "."
       << std::stoi(verStr.substr(8, 2));
    return ss.str();
}

std::string lime::GetABIVersion(void)
{
    return "";
}
