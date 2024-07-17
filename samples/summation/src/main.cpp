#include <chrono>
#include <iostream>
#include <thread>

void double_sum( long long count, int * sum )
{
    *sum = 0;
    for ( int i = 0; i < count; i++ ) {
        *sum += 2;
    }
}

void multi_thread( long long user_input )
{
    int sum1;
    int sum2;
    int sum3;
    int sum4;

    int * ptrsum1 = &sum1;
    int * ptrsum2 = &sum2;
    int * ptrsum3 = &sum3;
    int * ptrsum4 = &sum4;

    long long count     = user_input / 4;
    auto      rem       = user_input % 4;
    long long count_rem = count + rem;

    auto beg = std::chrono::high_resolution_clock::now();

    std::thread t1( double_sum, count, ptrsum1 );      //
    std::thread t2( double_sum, count, ptrsum2 );      //
    std::thread t3( double_sum, count, ptrsum3 );      //
    std::thread t4( double_sum, count_rem, ptrsum4 );  //

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::chrono::time_point< std::chrono::high_resolution_clock > end = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast< std::chrono::nanoseconds >( end - beg );

    std::cout << "The loop ran " << sum1 + sum2 + sum3 + sum4 << " times and added 2 each time for a total of "
              << sum1 + sum2 + sum3 + sum4 << ".\n";
    std::cout << "The loop ran for " << elapsed_time.count() << " nanoseconds" << ".\n";
}

void single_thread( long long user_input )
{
    int  total = 0;
    auto beg   = std::chrono::high_resolution_clock::now();
    double_sum( user_input, &total );
    std::chrono::time_point< std::chrono::high_resolution_clock > end = std::chrono::high_resolution_clock::now();

    auto elapsed_time = std::chrono::duration_cast< std::chrono::nanoseconds >( end - beg );

    std::cout << "The loop ran " << total << " times and added 2 each time for a total of " << total << ".\n";
    std::cout << "The loop ran for " << elapsed_time.count() << " nanoseconds" << ".\n";
}

int main()
{
    long long user_input;
    std::cout << "Enter a number: ";
    std::cin >> user_input;

    std::cout << "Running single thread algorithm...\n";
    single_thread( user_input );

    std::cout << "Running multi thread algorithm...\n";
    multi_thread( user_input );

    return 0;
}
