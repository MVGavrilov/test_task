#include <SomeHash.h>

#include <iostream>

int main(int, char*[])
{
    auto sum = SomeHash::sum(1, 2);
    std::cout << sum << std::endl;
    return 0;
}