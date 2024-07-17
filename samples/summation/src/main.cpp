#include <chrono>
#include <iostream>

void single_thread( long long user_input )
{
    auto beg = std::chrono::high_resolution_clock::now();
    int  sum = 0;
    for ( int i = 0; i < user_input; i++ ) {
        sum += 1;
    }
    std::chrono::time_point< std::chrono::high_resolution_clock > end = std::chrono::high_resolution_clock::now();

    auto elapsed_time = std::chrono::duration_cast< std::chrono::nanoseconds >( end - beg );

    std::cout << "The loop ran " << sum << " times and added 1 each time for a total of " << sum << ".\n";
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
    // multi_thread( user_input );

    return 0;
}
