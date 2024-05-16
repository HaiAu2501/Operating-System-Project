// C++ Program to illustrate the use of counting_semaphore
#include <iostream>
#include <semaphore>
#include <thread>
using namespace std;

// Initialize semaphore with a count of 3
counting_semaphore<10> semaphore(2);

void worker(int id)
{
    // aquiring
    semaphore.acquire();

    // doing some work
    cout << "Thread " << id << " acquired the semaphore."
         << endl;

    // releasing
    semaphore.release();
    cout << "Thread " << id << " released the semaphore."
         << endl;
}

// driver code
int main()
{
    thread t1(worker, 1);
    thread t2(worker, 2);
    thread t3(worker, 3);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
