#ifndef MILESTONE_2_FILECACHEMANAGER_H
#define MILESTONE_2_FILECACHEMANAGER_H

#include "cacheManager.h"
#include <unordered_map>
#include <functional>
#include <list>
#include <mutex>
#include <bits/unordered_set.h>

namespace cache {

    template<typename T>
    /**
     * This object has the operator ==
     * @tparam T the type of the object
     */
    class Equals {
    protected:
        T* _obj;
    public:
        Equals(T* obj) : _obj(obj) { }

        bool operator==(const Equals<T>& h) const {
            return *_obj == *h._obj;
        }

        T* operator*() const {
            return _obj;
        }
    };

    template<typename T>
    /**
     * This object holds an object pointer inside of it which
     *  can be hashed and have the operator ==.
     * @tparam T the type of the object
     */
    class Hashable : public Equals<T> {
    private:
        size_t _hash;
        bool _hashed;
    public:
        Hashable(T *obj) : Equals<T>(obj), _hashed(false) {}

        size_t hash() {
            if (_hashed) {
                return _hash;
            }
            _hashed = true;

            T& obj = *this->_obj;
            std::hash<T> hasher;

            return (_hash = hasher(obj));
        }
    };
}

namespace std {
    template<typename T>
    struct hash<cache::Hashable<T>> {
        size_t operator()(const cache::Hashable<T>& hashable) {
            return hashable.hash();
        }
    };
}

namespace cache {

    PROBLEM_TEMPLATE
    struct PSPair {
        Hashable<P> prob;
        S* sol;
    };

    PROBLEM_TEMPLATE
    /**
     * PSList is a list of Problem-Solution pairs.
     * @tparam P the problem type
     * @tparam S the solution type
     */
    class PSList {
    private:
        std::mutex _lock;
        std::list<PSPair<P,S>> _data;

        /**
         * Get a solution for a problem without locking
         * @param problem the problem
         * @return a solution or nullptr if doesn't exist
         */
        S* getSolution(P *problem);
    public:
        PSList();

        /**
         * Get a solution for a problem if exists.
         * @param problem the problem to search for
         * @return a solution if exists. otherwise returns nullptr
         */
        S* get(P* problem);

        /**
         * Add a pair to the list.
         * @param problem the problem
         * @param solution the solution
         * @return true if added successfully, false otherwise.
         */
        bool add(P* problem, S* solution);

        /**
         * Frees all problem and solution memory.
         */
        void freeMemory();

        const std::list<PSPair<P,S>>& getData() { return _data; }
    };

    PROBLEM_TEMPLATE
    class SolutionFile : public CacheManager<P,S> {
    private:
        PSS<P,S>* _streamer;
        std::string _fname;

        PSList<P,S> _loaded;
        PSList<P,S> _unsaved;

        void load();

        void save();
    public:
        /**
         * Construct a solution file.
         * @param streamer a problem solution streamer
         * @param fname a filename
         */
        SolutionFile(PSS<P,S>* streamer, const std::string& fname);

        virtual bool solutionExists(P* p);

        virtual S* getSolution(P* p);

        virtual void saveSolution(P* p, S* sol);

        ~SolutionFile();
    };

    PROBLEM_TEMPLATE
    class FileCacheManager : public CacheManager<P, S> {
    private:
        PSS<P, S>* _streamer;
        std::string _dir;

        std::unordered_map<size_t, SolutionFile<P,S>*> _files;

        SolutionFile<P,S>* getFile(P* problem);
    public:
        FileCacheManager(PSS<P,S>* streamer,
                const std::string& directory = "./cache");

        virtual bool solutionExists(P* p);

        virtual S* getSolution(P* p);

        virtual void saveSolution(P* p, S* sol);

        virtual ~FileCacheManager();
    };
}

#include "fileCacheManager.tpp"

#endif
