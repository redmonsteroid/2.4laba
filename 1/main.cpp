#include <iostream>
#include <chrono>
#include "SyncPrimitives.hpp"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <quantityThreads> <quantityChar> <syncPrimitiveType>" << std::endl;
        return 1;
    }

    int quantityThreads = std::stoi(argv[1]);
    int quantityChar = std::stoi(argv[2]);
    int syncPrimitiveType = std::stoi(argv[3]);

    SyncPrimitives syncPrimitives;

    // Начало замера времени
    auto start = std::chrono::high_resolution_clock::now();

    // Запуск выбранного синхронизационного примитива
    syncPrimitives.CreateThreads(quantityThreads, quantityChar, syncPrimitiveType);

    // Конец замера времени
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Execution time: " << duration.count() << " seconds" << std::endl;

    return 0;
}
