#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void threadFunction1() {
    for (int i = 1; i <= 5; i++) { 
        cout << "Thread 1 is running: Step " << i << endl;
        this_thread::sleep_for(chrono::seconds(1)); 
    }
    cout << "Thread 1 has finished its work." << endl;
}

void threadFunction2() {
    for (int i = 1; i <= 10; i++) { 
        cout << "Thread 2 is running: Step " << i << endl;
        this_thread::sleep_for(chrono::seconds(1)); 
    }
    cout << "Thread 2 has finished its work." << endl;
}

int main() {
    thread t1(threadFunction1);
    thread t2(threadFunction2);

    t1.join();
    t2.join();

    cout << "Both threads have completed their tasks. Main thread exiting." << endl;
    return 0;
}
