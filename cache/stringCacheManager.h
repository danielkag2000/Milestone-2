#ifndef MILESTONE_2_STRINGCACHEMANAGER_H
#define MILESTONE_2_STRINGCACHEMANAGER_H

#include "fileCacheManager.h"

namespace cache {

    class StringCacheManager : public CacheManager<std::string, std::string> {
    private:
        CacheManager<std::string, std::string>* _cm;
        Streamer<std::string>* _streamer;
        PSS<std::string, std::string>* _streamerCollection;
    public:
        StringCacheManager(const std::string& dir = "./cache/");

        virtual bool solutionExists(std::string* p);

        virtual std::string* getSolution(std::string* p);

        virtual void saveSolution(std::string* p, std::string* sol);

        virtual ~StringCacheManager();
    };
}


#endif
