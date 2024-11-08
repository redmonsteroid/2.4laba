#include "SyncPrimitives.hpp"
#include <cstdlib>
#include <ctime>

// Race Condition
void SyncPrimitives::GRCRaceCondition(int thread_id, std::string& buffer, int& quantityChar) {
    std::string local_chars;
    for (int i = 0; i < quantityChar; ++i) {
        char random_char = static_cast<char>(rand() % (126 - 32 + 1) + 32);
        local_chars += random_char;
    }
    buffer += local_chars;
    std::cout << "Thread " << thread_id << " generated: " << local_chars << std::endl;
}

// Mutex
void SyncPrimitives::GRCMutex(int thread_id, std::string& buffer, int& quantityChar) {
    std::lock_guard<std::mutex> lock(GRCmutex);
    std::string local_chars;
    for (int i = 0; i < quantityChar; ++i) {
        char random_char = static_cast<char>(rand() % (126 - 32 + 1) + 32);
        local_chars += random_char;
    }
    buffer += local_chars;
    std::cout << "Thread " << thread_id << " generated: " << local_chars << std::endl;
}

// Semaphore
std::binary_semaphore smphSignalCreateThreadsToGRCSemaphore(1);
std::binary_semaphore smphSignalGRCSemaphoreToCreateThreads(1);

void SyncPrimitives::GRCSemaphore(int thread_id, std::string& buffer, int& quantityChar) {
    smphSignalCreateThreadsToGRCSemaphore.acquire();
    
    std::string local_chars;
    for (int i = 0; i < quantityChar; ++i) {
        char random_char = static_cast<char>(rand() % (126 - 32 + 1) + 32);
        local_chars += random_char;
    }
    
    buffer += local_chars;
    std::cout << "Thread " << thread_id << " generated: " << local_chars << std::endl;

    smphSignalGRCSemaphoreToCreateThreads.release();  // Освобождаем семафор после выполнения
}

// SemaphoreSlim
void SyncPrimitives::GRCSemaphoreSlim(int thread_id, std::string& buffer, int& quantityChar) {
    static std::counting_semaphore<1> smphSlim(1);
    smphSlim.acquire();
    std::string local_chars;
    for (int i = 0; i < quantityChar; ++i) {
        char random_char = static_cast<char>(rand() % (126 - 32 + 1) + 32);
        local_chars += random_char;
    }
    buffer += local_chars;
    std::cout << "Thread " << thread_id << " generated: " << local_chars << std::endl;
    smphSlim.release();
}

// Barrier
void SyncPrimitives::GRCBarrier(int thread_id, std::string& buffer, int& quantityChar) {
    barrierGRCBarrier.arrive_and_wait();
    std::string local_chars;
    for (int i = 0; i < quantityChar; ++i) {
        char random_char = static_cast<char>(rand() % (126 - 32 + 1) + 32);
        local_chars += random_char;
    }
    buffer += local_chars;
    std::cout << "Thread " << thread_id << " generated: " << local_chars << std::endl;
}

// SpinLock
void SyncPrimitives::GRCSpinLock(int thread_id, std::string& buffer, int& quantityChar) {
    while (spinlock.test_and_set(std::memory_order_acquire));
    std::string local_chars;
    for (int i = 0; i < quantityChar; ++i) {
        char random_char = static_cast<char>(rand() % (126 - 32 + 1) + 32);
        local_chars += random_char;
    }
    buffer += local_chars;
    std::cout << "Thread " << thread_id << " generated: " << local_chars << std::endl;
    spinlock.clear(std::memory_order_release);
}

// Create Threads
void SyncPrimitives::CreateThreads(const int& quantityThreads, int& quantityChar, int syncType) {
    std::string buffer;
    srand(static_cast<unsigned int>(time(0))); 
    std::vector<std::thread> threads;

    for (int i = 0; i < quantityThreads; ++i) {
        switch(syncType) {
            case 0: threads.emplace_back(&SyncPrimitives::GRCRaceCondition, this, i, std::ref(buffer), std::ref(quantityChar)); break;

            case 1: threads.emplace_back(&SyncPrimitives::GRCMutex, this, i, std::ref(buffer), std::ref(quantityChar)); break;

            case 2: smphSignalCreateThreadsToGRCSemaphore.release();  // Разрешаем начальный доступ к семафору
                threads.emplace_back(&SyncPrimitives::GRCSemaphore, this, i, std::ref(buffer), std::ref(quantityChar)); 
                smphSignalGRCSemaphoreToCreateThreads.acquire();  // Ожидаем выполнения потока
                break;

            case 3: threads.emplace_back(&SyncPrimitives::GRCSemaphoreSlim, this, i, std::ref(buffer), std::ref(quantityChar)); break;

            case 4: threads.emplace_back(&SyncPrimitives::GRCBarrier, this, i, std::ref(buffer), std::ref(quantityChar)); break;

            case 5: threads.emplace_back(&SyncPrimitives::GRCSpinLock, this, i, std::ref(buffer), std::ref(quantityChar)); break;
            
            default: break;
        }
    }

    for (auto& thread : threads) {
        thread.join();
    }
    std::cout << "Buffer: " << buffer << std::endl;
}
