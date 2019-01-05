#ifndef MILESTONE_2_SOLVER_H
#define MILESTONE_2_SOLVER_H

namespace algorithm {
    template <class Problem, class Solution>
    class Solver {
    public:
        virtual Solution solve(Problem) = 0;

        virtual ~Solver() {};
    };
}

#endif
