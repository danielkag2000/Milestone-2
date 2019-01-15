#ifndef MILESTONE_2_STRINGSTREAMER_H
#define MILESTONE_2_STRINGSTREAMER_H

#include "cacheManager.h"

namespace cache {
    class StringStreamer : public Streamer<std::string> {
        virtual std::string serialize(const std::string* instance) {
            return *instance;
        }

        virtual std::string* deserialize(const std::string& str) {
            return new std::string(str);
        }

        virtual ~StringStreamer() = default;
    };
}

#endif