#include "MutexSync.hpp"

using namespace std;

void MutexSync::threadTask(int charCount){
    lock_guard<mutex> lock(mtx);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(32, 126);
    for (int i = 0; i < charCount; i++){
        char randomChar = static_cast<char>(dist(gen));
        cout << randomChar;
    }   
}

void MutexSync::run(int threadCount, int charCount) {
    vector<thread> threads;
    for (int i = 0; i < threadCount; ++i) {
        threads.emplace_back(&MutexSync::threadTask, this, charCount);
    }
    for (auto& t : threads) {
        t.join();
    }
}