#ifndef MILESTONE_2_THREAD_POOL_H
#define MILESTONE_2_THREAD_POOL_H

#include <set>
#include <thread>
#include <mutex>

namespace threads {

    class ThreadPool {
    private:
        std::set<pthread_t> _threads;
        std::mutex _lock;

    public:
        /**
         * Add a thread to the thread pool.
         * @param thread
         */
        void add(pthread_t thread);

        /**
         * Remove a thread from the thread pool.
         * @param thread
         */
        void remove(pthread_t thread);

        /**
         * Wait for all threads currently running to finish execution.
         */
        void join();
    };
}


#endif
