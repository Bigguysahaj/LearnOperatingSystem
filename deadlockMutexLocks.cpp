#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex mutexA;
mutex mutexB;

void threadA()
{
    cout << "Thread A trying to acquire mutex A" << endl;
    mutexA.lock();
    cout << "Thread A acquired mutex A" << endl;
    
    this_thread::sleep_for(std::chrono::seconds(1)); // Adding a delay to simulate some work
    
    cout << "Thread A trying to acquire mutex B" << endl;
    mutexB.lock(); // Deadlock happens here
    cout << "Thread A acquired mutex B" << endl;
    
    mutexB.unlock();
    mutexA.unlock();
}

void threadB()
{
    cout << "Thread B trying to acquire mutex B" << endl;
    mutexB.lock();
    cout << "Thread B acquired mutex B" << endl;
    
    this_thread::sleep_for(std::chrono::seconds(1)); // Adding a delay to simulate some work
    
    cout << "Thread B trying to acquire mutex A" << endl;
    mutexA.lock(); // Deadlock happens here
    cout << "Thread B acquired mutex A" << endl;
    
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
