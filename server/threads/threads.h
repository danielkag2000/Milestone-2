#ifndef MILESTONE_2_THREAD_POOL_H
#define MILESTONE_2_THREAD_POOL_H

#include <set>
#include <thread>
#include <mutex>

namespace threads {

    class Thread {
    private:
        std::mutex _joinLock;

        bool _alive;
        pthread_t _id;

        void lock() { _joinLock.lock(); }
        bool try_lock() { return _joinLock.try_lock(); }
        void unlock() { _joinLock.unlock(); };

        friend void* threadMain(void* args);
    public:
        /**
         * Create a thread for a function with arguments.
         * @param func the function
         * @param args the function arguments
         */
        Thread(void* (func)(void*), void* args);

        /**
         * Join this thread if it is alive.
         * @param returnValue a pointer to a variable
         *  which will hold the return value from the thread
         */
        void join(void** returnValue = NULL);
    };

    class ThreadPool {
    private:
        std::set<Thread*> _threads;
        std::mutex _lock;

    public:
        /**
         * Add a thread to the thread pool.
         * @param thread the thread to be added
         */
        void add(Thread* thread);

        /**
         * Wait for all threads currently running to finish execution.
         */
        void join();

        /**
         * Destroys all sub-thread instances.
         */
        ~ThreadPool();
    };
}


#endif
