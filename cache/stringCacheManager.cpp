#include "stringCacheManager.h"
#include "stringStreamer.h"

using namespace std;

namespace cache {

    StringCacheManager::StringCacheManager(const string &dir){
        _streamer = new StringStreamer;
        _streamerCollection = new DefaultPSS<string, string>(_streamer, _streamer);
        _cm = new FileCacheManager<string, string>(_streamerCollection, dir);
    }

    bool StringCacheManager::solutionExists(std::string *p) {
        return _cm->solutionExists(p);
    }

    std::string* StringCacheManager::getSolution(std::string *p) {
        return _cm->getSolution(p);
    }

    void StringCacheManager::saveSolution(std::string *p, std::string *sol) {
        _cm->saveSolution(p, sol);
    }

    StringCacheManager::~StringCacheManager() {
        delete _cm;
        delete _streamerCollection;
        delete _streamer;
    }
}