#include "fileCacheManager.h"
#include <string>
#include <functional>
#include <fstream>
#include <algorithm>

namespace cache {

#define LOCK(var) std::lock_guard<std::mutex> lock(var);
    /*
     * solution file format:
     * for every (problem, solution):
     * {var} = value of variable var
     * ...<{problem length},{solution length}>{problem}{solution}...
     *
     * problem\solution length -- unsigned longs
     */

    PROBLEM_TEMPLATE
    /**
     * Read one solution from a given input stream.
     *  Will be parsed using the given parser.
     * @tparam P problem type
     * @tparam S solution type
     * @param in an input stream to read from
     * @param parser a parser to use for reading
     * @return a pair of solution and problem
     */
    PSPair<P,S> readSolution(std::istream& in, PSS<P, S>* parser) {
        char dummy;
        unsigned long problemLength, solutionLength;
        std::string str;

        in >> dummy; // get <
        in >> problemLength;
        in >> dummy; // get ,
        in >> solutionLength;
        in >> dummy; // get >

        // read problem
        str.resize(problemLength);
        in.read(&str[0], problemLength);
        P* prob = parser->getProblemStreamer()->deserialize(str);

        // read solution
        str.resize(solutionLength);
        in.read(&str[0], solutionLength);
        S* sol = parser->getSolutionStreamer()->deserialize(str);

        return { { prob }, sol };
    }

    PROBLEM_TEMPLATE
    void writeSolution(PSPair<P,S> pair,
            std::ostream& out, PSS<P,S>* serializer) {
        std::string problem(serializer->getProblemStreamer()->serialize(*pair.prob));
        std::string solution(serializer->getSolutionStreamer()->serialize(pair.sol));

        out << '<'
            << problem.length() << ',' << solution.length()
            << '>'
            << problem << solution;
    }

    PROBLEM_TEMPLATE
    void SolutionFile<P,S>::load() {
        std::ifstream in(_fname, std::ifstream::in);

        if (!in) {
            return;
        }

        while (in) {
            auto probSol = readSolution(in, _streamer);
            _loaded.add(*probSol.prob, probSol.sol);
        }

        in.close();
    }

    PROBLEM_TEMPLATE
    void SolutionFile<P,S>::save() {
        std::ofstream out(_fname, std::ofstream::out || std::ofstream::app);

        if (!out) {
            throw std::exception("Couldn't open file for output.");
        }

        for (PSPair<P,S>& unsaved : _unsaved.getData()) {
            writeSolution<P,S>(unsaved, out, _streamer);
        }

        out.close();
    }

    PROBLEM_TEMPLATE
    SolutionFile<P,S>::SolutionFile(PSS<P, S> *streamer,
            const std::string &fname) :
            _fname(fname), _streamer(streamer), _loaded() {
        load();
    }

    PROBLEM_TEMPLATE
    SolutionFile<P,S>::~SolutionFile() {
        _loaded.freeMemory();
    }

    PROBLEM_TEMPLATE
    bool SolutionFile<P,S>::solutionExists(P* p) {
        return _loaded.get(p) != nullptr;
    }

    PROBLEM_TEMPLATE
    S* SolutionFile<P,S>::getSolution(P * p) {
        return _loaded.get(p);
    }

    PROBLEM_TEMPLATE
    void SolutionFile<P,S>::saveSolution(P* p, S* s) {
        if (_loaded.add(p, s))
            _unsaved.add(p, s);
    }

    PROBLEM_TEMPLATE
    FileCacheManager<P,S>::
            FileCacheManager(PSS<P, S> *streamer, const std::string &directory)
            : _streamer(streamer), _dir(directory) {
    }

    PROBLEM_TEMPLATE
    SolutionFile<P, S>* FileCacheManager<P,S>::getFile(P* problem) {
        Hashable<P> hash(problem);

        SolutionFile<P,S>*& file = _files[hash.hash()];

        if (file == nullptr){
            file = new SolutionFile<P, S>(_streamer, to_string(hash.hash()));
        }

        return file;
    }

    PROBLEM_TEMPLATE
    S* FileCacheManager<P,S>::getSolution(P* p) {
        return getFile(p)->getSolution(p);
    }

    PROBLEM_TEMPLATE
    bool FileCacheManager<P,S>::solutionExists(P* p) {
        return getSolution(p) != nullptr;
    }

    PROBLEM_TEMPLATE
    void FileCacheManager<P,S>::saveSolution(P* p, S* sol) {
        getFile(p)->saveSolution(p, sol);
    }

    PROBLEM_TEMPLATE
    FileCacheManager<P,S>::~FileCacheManager() {
        for (auto& file : _files) {
            delete file.second;
        }
    }

    PROBLEM_TEMPLATE
    PSList<P,S>::PSList() : _lock(), _data(){}

    PROBLEM_TEMPLATE
    bool PSList<P,S>::add(P* problem, S *solution) {
        LOCK(_lock)

        // make sure there are no duplicates
        if (getSolution(problem) == nullptr) {
            PSPair<P,S> pair{ Hashable<P>(problem) , solution };
            _data.push_back(pair);
            return true;
        }
        else {
            return false;
        }
    }

    PROBLEM_TEMPLATE
    S* PSList<P,S>::getSolution(P *problem) {
        Equals<P> eq(problem);

        auto it = std::find_if(_data.begin(), _data.end(),
             [eq](const PSPair<P,S>& pair) {
                    return pair.prob == eq;
                });

        if (it == _data.end()) {
            return nullptr;
        }
        else {
            return (*it).sol;
        }
    }

    PROBLEM_TEMPLATE
    S* PSList<P,S>::get(P* problem) {
        LOCK(_lock)
        return getSolution(problem);
    }

    PROBLEM_TEMPLATE
    void PSList<P,S>::freeMemory() {
        LOCK(_lock)

        std::for_each(_data.begin(), _data.end(),
                [](const PSPair<P,S>& elem) {
           delete *elem.prob;
           delete elem.sol;
        });
    }
}