#include <SomeHash.h>

#include <iostream>

int main()
{
    SomeHash::SomeHash<int> hash;

    hash.add(1);
    hash.display();
    hash.add(2);
    hash.display();
    hash.remove(2);
    hash.display();

    std::cout << "Minimum value for int: " << std::numeric_limits<unsigned int>::min() << std::endl;
    std::cout << "Maximum value for int: " << std::numeric_limits<unsigned int>::max() << std::endl;

    auto hash2(std::move(hash));
    hash2.display();

}