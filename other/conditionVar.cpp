#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void WorkerThread() {
    std::cout << "WorkerThread: Waiting..." << std::endl;
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready; });

    std::cout << "WorkerThread: Notified!" << std::endl;
}

int main() {
    std::thread workerThread(WorkerThread);

    // Simulate some work...
    std::this_thread::sleep_for(std::chrono::seconds(2));

    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
        std::cout << "Main: Notifying the worker thread." << std::endl;
    }
    cv.notify_one();

    workerThread.join();

    return 0;
}