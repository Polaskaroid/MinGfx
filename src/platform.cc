
#include "platform.h"

#include "mingfx_config.h"

#include <vector>
#include <sstream>

#ifdef WIN32
    #include <windows.h>
#else
    #include <sys/stat.h>
#endif


namespace MinGfx {
    
bool Platform::fileExists(const std::string &filename) {
#ifdef WIN32
    DWORD attr = ::GetFileAttributesW(filename.c_str());
    return (attr != 0xFFFFFFFF);
#else
    struct stat buf;
    return (stat(filename.c_str(), &buf) == 0);
#endif
}
    

std::string Platform::findFile(const std::string &basename, const std::vector<std::string> &searchpath) {
    for (int i=0; i<searchpath.size(); i++) {
        std::string fname = searchpath[i] + "/" + basename;
        if (Platform::fileExists(fname)) {
            return fname;
        }
    }
    return basename;
}

std::string Platform::findFile(const std::string &basename, const std::string &searchpath) {
    std::vector<std::string> paths;
    std::stringstream ss(searchpath);
    std::string path;
    while (ss >> path) {
        paths.push_back(path);
        if (ss.peek() == ';')
            ss.ignore();
    }
    return findFile(basename, paths);
}


std::string Platform::findMinGfxDataFile(const std::string &basename) {
    std::vector<std::string> searchpath;
    searchpath.push_back(".");
    searchpath.push_back("data");
    searchpath.push_back(MINGFX_DATA_DIR_INSTALL);
    searchpath.push_back(MINGFX_DATA_DIR_BUILD);
    return findFile(basename, searchpath);
}

std::string Platform::findMinGfxShaderFile(const std::string &basename) {
    std::vector<std::string> searchpath;
    searchpath.push_back(".");
    searchpath.push_back("shaders");
    searchpath.push_back(MINGFX_SHADERS_DIR_INSTALL);
    searchpath.push_back(MINGFX_SHADERS_DIR_BUILD);
    return findFile(basename, searchpath);
}


} // end namespace