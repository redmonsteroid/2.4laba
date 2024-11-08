#include "ThreadManager.hpp"
#include <iostream>

void ThreadManager::runThreads(int threadCount, int charCount, int syncType) {
    if (syncType == 1) {
        MutexSync mutexSync;
        mutexSync.run(threadCount, charCount);
    }
    else {
        std::cerr << "Ошибка: неизвестный тип синхронизации.\n";
    }
}

double ThreadManager::measureExecutionTime(int threadCount, int charCount, int syncType) {
    auto start = std::chrono::high_resolution_clock::now();
    runThreads(threadCount, charCount, syncType);
    auto end = std::chrono::high_resolution_clock::now();
    
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}