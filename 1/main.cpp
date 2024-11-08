#include <iostream>
#include "ThreadManager.hpp"
#include <cstdlib>

using namespace std;

int main (int argc, char *argv[]) {
    if (argc!=4){
        cout << "Usage: ./1task <number of threads> <number of iterations> <number of elements in array>" << endl;
        return 1;
    }

    int threadCount = atoi(argv[1]);
    int charCount = atoi(argv[2]);
    int syncType = atoi(argv[3]);

    if (threadCount<=0 || charCount<=0){
        cout << "Numbers of threads and char must be positive" << endl;
    }

    double executionTime = ThreadManager::measureExecutionTime(threadCount, charCount, syncType);
    cout << "Execution time: " << executionTime << endl;
    return 0;
}