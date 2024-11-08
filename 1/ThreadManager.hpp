#ifndef THREAD_MANAGER_HPP
#define THREAD_MANAGER_HPP

#include "MutexSync.hpp"
#include <chrono>

class ThreadManager {
public:
    static void runThreads(int threadCount, int charCount, int syncType);
    static double measureExecutionTime(int threadCount, int charCount, int syncType);
};

#endif