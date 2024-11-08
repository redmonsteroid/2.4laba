#ifndef SYNC_PRIMITIVES_HPP
#define SYNC_PRIMITIVES_HPP

#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <semaphore>
#include <barrier>
#include <atomic>

class SyncPrimitives {
public:
    void GRCRaceCondition(int thread_id, std::string& buffer, int& quantityChar);
    void GRCMutex(int thread_id, std::string& buffer, int& quantityChar);
    void GRCSemaphore(int thread_id, std::string& buffer, int& quantityChar);
    void GRCSemaphoreSlim(int thread_id, std::string& buffer, int& quantityChar);
    void GRCBarrier(int thread_id, std::string& buffer, int& quantityChar);
    void GRCSpinLock(int thread_id, std::string& buffer, int& quantityChar);
    void GRCSpinWait(int thread_id, std::string& buffer, int& quantityChar);
    void CreateThreads(const int& quantityThreads, int& quantityChar, int syncType);
private:
    std::mutex GRCmutex;
    std::binary_semaphore smphSignalCreateThreadsToGRCSemaphore{0}, smphSignalGRCSemaphoreToCreateThreads{0};
    std::barrier<> barrierGRCBarrier{1};
    std::atomic_flag spinlock = ATOMIC_FLAG_INIT;
};

#endif // SYNC_PRIMITIVES_HPP
