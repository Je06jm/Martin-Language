#ifndef MARTIN_CONFIG
#define MARTIN_CONFIG

#include <string>
#include "platform.hpp"

namespace Martin {

#ifdef windows
    static const std::string global_packages_path = "%LOCALAPPDATA%\\Martin\\Packages\\";
#else
    static const std::string global_packages_path = "/opt/Martin/Packages/";
#endif

}

#endif