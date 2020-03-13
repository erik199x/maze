
#include <chrono>
#include <iostream>
#include <random>

int main()
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> uid(1, 6);

    int r = uid(generator);

    std::cout << r << std::endl;
}




