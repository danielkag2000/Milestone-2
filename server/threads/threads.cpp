#include "threads.h"
#include <iostream>
#include <unistd.h>
#include "../../exceptions.h"

namespace threads {

    using namespace std;

    struct ThreadData {
        void* (*funcptr)(void*);
        void* funcargs;
        Thread* t; // a pointer to the current thread(for setting alive and not alive)
    };

#define SET_ALIVE_SAFE(thread, alive)\
    if (thread->try_lock()) {\
        thread->_alive = alive;\
        thread->unlock();\
    }\
    else { \
        /* someone tries to join */ \
        thread->_alive = alive;\
        sleep(1);\
    }



    /**
     * The main method for each thread.
     * Turns on 'isAlive' when beginning and turns in off when finishing
     */
    void* threadMain(void* args) {
        ThreadData* inData = (ThreadData*) args;
        ThreadData data(*inData);
        delete inData;

        SET_ALIVE_SAFE(data.t, true);

        // run thread
        try {
            data.funcptr(data.funcargs);
        }
        catch (const exception& e) {
            cerr << e.what() << endl;
        }
        catch (...) {
            cerr << "error in thread." << endl;
        }

        SET_ALIVE_SAFE(data.t, false);

        return nullptr;
    }

    Thread::Thread(void* (func)(void*), void* args) : _alive(false) {
        ThreadData* data = new ThreadData;
        data->t = this;
        data->funcptr = func;
        data->funcargs = args;

        if (pthread_create(&_id, NULL, threadMain, data) < 0) {
            using namespace exceptions;
            throw system_generic_error(errno, "failed opening thread");
        }
    }

    void Thread::join() {
        lock();
        if (_alive) {
            pthread_join(_id, NULL);
        }
        unlock();
    }

    void ThreadPool::add(Thread* thread) {
        _threads.insert(thread);
    }

    void ThreadPool::join() {
        for (Thread* t : _threads) {
            t->join();
        }
    }

    ThreadPool::~ThreadPool() {
        for (Thread* t : _threads) {
            delete t;
        }
    }

}