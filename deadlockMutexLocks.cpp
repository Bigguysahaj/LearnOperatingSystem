#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutexA;
std::mutex mutexB;

void threadA()
{
    std::cout << "Thread A trying to acquire mutex A" << std::endl;
    mutexA.lock();
    std::cout << "Thread A acquired mutex A" << std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Adding a delay to simulate some work
    
    std::cout << "Thread A trying to acquire mutex B" << std::endl;
    mutexB.lock(); // Deadlock happens here
    std::cout << "Thread A acquired mutex B" << std::endl;
    
    mutexB.unlock();
    mutexA.unlock();
}

void threadB()
{
    std::cout << "Thread B trying to acquire mutex B" << std::endl;
    mutexB.lock();
    std::cout << "Thread B acquired mutex B" << std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Adding a delay to simulate some work
    
    std::cout << "Thread B trying to acquire mutex A" << std::endl;
    mutexA.lock(); // Deadlock happens here
    std::cout << "Thread B acquired mutex A" << std::endl;
    
    mutexA.unlock();
    mutexB.unlock();
}

int main()
{
    std::thread t1(threadA);
    std::thread t2(threadB);
    
    t1.join();
    t2.join();
    
    return 0;
}
