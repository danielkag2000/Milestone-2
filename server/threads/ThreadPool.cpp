#include "ThreadPool.h"

namespace threads {

    void ThreadPool::add(pthread_t thread) {
        _lock.lock();
        _threads.insert(thread);
        _lock.unlock();
    }

    void ThreadPool::remove(pthread_t thread) {
        _lock.lock();
        _threads.erase(thread);
        _lock.unlock();
    }

    void ThreadPool::join() {
        while (true) {
            _lock.lock();

            if (_threads.empty()) {
                // finish once done
                _lock.unlock();
                break;
            }

            pthread_t thread = *_threads.begin();

            _lock.unlock();

            pthread_join(thread, nullptr);

            remove(thread);
        }
    }
}