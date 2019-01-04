#ifndef MILESTONE_2_CACHEMANAGER_H
#define MILESTONE_2_CACHEMANAGER_H

#define PROBLEM_TEMPLATE template<class Problem, class Solution>

namespace algorithm {

    PROBLEM_TEMPLATE
    class CacheManager {
        virtual bool solutionExists(Problem* p) = 0;

        virtual Solution* getSolution(Problem* p) = 0;

        virtual void saveSolution(Problem* p, Solution* sol) = 0;

        virtual ~CacheManager() = default;
    };
}

#endif
