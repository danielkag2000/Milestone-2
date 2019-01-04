#ifndef MILESTONE_2_FILECACHEMANAGER_H
#define MILESTONE_2_FILECACHEMANAGER_H

#include "cacheManager.h"

namespace algorithm {

    PROBLEM_TEMPLATE
    class FileCacheManager : public CacheManager<Problem, Solution> {
        virtual bool solutionExists(Problem* p);

        virtual Solution* getSolution(Problem* p);

        virtual void saveSolution(Problem* p, Solution* sol);

        virtual ~FileCacheManager() = default;
    };
}

#endif //MILESTONE_2_FILECACHEMANAGER_H
