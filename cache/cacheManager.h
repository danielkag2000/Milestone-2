#ifndef MILESTONE_2_CACHEMANAGER_H
#define MILESTONE_2_CACHEMANAGER_H

#define PROBLEM_TEMPLATE template<class P, class S>

#include <string>

namespace cache {

    PROBLEM_TEMPLATE
    class CacheManager {
    public:
        virtual bool solutionExists(P* p) = 0;

        virtual S* getSolution(P* p) = 0;

        virtual void saveSolution(P* p, S* sol) = 0;

        virtual ~CacheManager() = default;
    };

    template<typename T>
    class Streamer {
    public:
        /**
         * Serialize a given object instance
         * @param instance the instance
         * @return a serialized string of the object
         */
        virtual std::string serialize(const T* instance) = 0;

        /**
         * Deserialize an object from the given string.
         *  Creates an object on the heap!
         * @param str the string
         * @return the deserialized object
         */
        virtual T* deserialize(const std::string& str) = 0;

        /**
         * Destructor.
         */
        virtual ~Streamer() = default;
    };

    PROBLEM_TEMPLATE
    /**
     * An abstract factory which creates problem streamers
     *  with their corresponding solution streamers.
     * @tparam P the problem type
     * @tparam S the solution type
     */
    class ProblemSolutionStreamer {
    public:
        /**
         * Get the streamer for the problems.
         * @return the problem streamer
         */
        virtual Streamer<P>* getProblemStreamer() = 0;

        /**
         * Get a streamer for the solutions.
         * @return the streamer
         */
        virtual Streamer<S>* getSolutionStreamer() = 0;

        /**
         * Destructor.
         */
        virtual ~ProblemSolutionStreamer() = default;
    };

    PROBLEM_TEMPLATE
    class DefaultPSS : public ProblemSolutionStreamer<P,S> {
    private:
        Streamer<P>* _problemStreamer;
        Streamer<S>* _solutionStreamer;

    public:
        DefaultPSS(Streamer<P>* pstreamer, Streamer<S>* sstreamer) :
            _problemStreamer(pstreamer),
            _solutionStreamer(sstreamer) {
        }

        virtual Streamer<P>* getProblemStreamer() {
            return _problemStreamer;
        }

        virtual Streamer<S>* getSolutionStreamer() {
            return _solutionStreamer;
        }

        virtual ~DefaultPSS() = default;
    };

    // alias
    PROBLEM_TEMPLATE
    using PSS = ProblemSolutionStreamer<P,S>;
}

#endif
