#include <SomeHash.hpp>

#include <iostream>

int main()
{
    SomeHash::SomeHash<int> hash;

    hash.add(1);
    hash.display();
    std::cout << std::endl;

    hash.add(2);
    hash.display();
    std::cout << std::endl;

    hash.remove(2);
    hash.display();
    std::cout << std::endl;

    auto hash2(std::move(hash));
    hash2.display();
    std::cout << "hash2.find(1) = " << hash2.find(1) << std::endl;
    std::cout << "hash2.find(2) = " << hash2.find(2) << std::endl;
    std::cout << "----------------------" << std::endl;
    std::cout << hash2;

}