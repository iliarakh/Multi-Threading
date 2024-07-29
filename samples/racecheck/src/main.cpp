#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>

int val = 0;
std::mutex mtx;

void print_if_odd()
{
    while (true) {
        mtx.lock();
        if (val % 2 == 1) {  // if val is odd
            std::cout << "VAL IS ODD: ";
            std::cout << "VAL = " << val << "\n";
            val++;
        }
        mtx.unlock();
    }
}

void print_if_even()
{
    while (true) {
        mtx.lock();
        if (val % 2 == 0) {
            std::cout << "VAL IS EVEN: ";
            std::cout << "VAL = " << val << "\n";
            val++;
        }
        mtx.unlock();
    }
}

int main()
{
    std::thread evenThread(print_if_even);
    std::thread oddThread(print_if_odd);

    evenThread.join();
    oddThread.join();
}
