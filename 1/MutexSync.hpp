#ifndef MUTEX_SYNC_HPP
#define MUTEX_SYNC_HPP

#include <mutex>
#include <thread>
#include <vector>
#include <random>
#include <iostream>
#include <random>

class MutexSync {
public:
    void run(int threadCount, int charCount);
private:
    std::mutex mtx;
    void threadTask(int charCount);
};

#endif