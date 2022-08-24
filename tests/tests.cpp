#include "SomeHash.hpp"

#include <gtest/gtest.h>
#include <regex>

TEST(some_hash_test, constructor_test) {
    SomeHash::SomeHash<int> hash1;
    EXPECT_EQ(0, hash1.find(1));

    SomeHash::SomeHash<int> hash2(1);
    EXPECT_EQ(1, hash2.find(1));

    SomeHash::SomeHash<int> hash3(hash2);
    EXPECT_EQ(1, hash3.find(1));
    hash2.add(2);
    EXPECT_EQ(0, hash3.find(2));
    EXPECT_EQ(1, hash2.find(2));
    hash3.add(4);
    EXPECT_EQ(1, hash3.find(4));
    EXPECT_EQ(0, hash2.find(4));

    hash3.add(3);
    SomeHash::SomeHash<int> hash4(std::move(hash3));
    EXPECT_EQ(1, hash4.find(1));
    EXPECT_EQ(0, hash4.find(2));
    EXPECT_EQ(1, hash4.find(3));
    EXPECT_EQ(1, hash4.find(4));
}

TEST(some_hash_test, simple_add_test) {
    SomeHash::SomeHash<int> hash;
    hash.add(1);
    EXPECT_EQ(1, hash.find(1));

    hash.add(1);
    EXPECT_EQ(2, hash.find(1));

    hash.add(2);
    EXPECT_EQ(1, hash.find(2));
}

TEST(some_hash_test, add_alot_test) {
    SomeHash::SomeHash<int> hash;

    for (int i = 0; i < 100; ++i) {
        hash.add(1);
        EXPECT_EQ(i+1, hash.find(1));
    }

    SomeHash::SomeHashTest<int> tmp(&hash);
    tmp.set_value(1, std::numeric_limits<unsigned int>::max());

    EXPECT_ANY_THROW(hash.add(1));
}

TEST(some_hash_test, remove_test) {
    SomeHash::SomeHash<int> hash;
    hash.add(1);
    hash.add(2);
    hash.remove(1);
    EXPECT_EQ(0, hash.find(1));
    EXPECT_EQ(1, hash.find(2));
    EXPECT_ANY_THROW(hash.remove(1));
}

TEST(some_hash_test, display_test) {
    SomeHash::SomeHash<int> hash;
    hash.add(1);
    hash.add(2);
    hash.add(3);
    hash.display();
}

TEST(some_hash_test, ostream_test) {
    SomeHash::SomeHash<int> hash;
    hash.add(1);
    hash.add(2);
    std::stringstream ss;
    ss << hash;
    std::string l1, l2;
    std::getline(ss, l1);
    std::getline(ss, l2);
    std::regex r1("1: [0-9]+");
    std::regex r2("2: [0-9]+");
    EXPECT_TRUE(std::regex_match(l1, r1) && std::regex_match(l2, r2) ||
                std::regex_match(l1, r2) && std::regex_match(l2, r1));
}

class A {
public:
    int a;
    bool operator==(const A &other) const {
        return a == other.a;
    }
};
namespace std {
    template<>
    struct hash<A> {
        size_t operator()(const A &a) const {
            return hash<int>()(a.a);
        }
    };
}

TEST(some_hash_test, custom_type_test) {
    SomeHash::SomeHash<A> hash;
    A a1;
    a1.a = 1;
    A a2;
    a2.a = 1;
    A a3;
    a3.a = 2;
    hash.add(a1);
    hash.add(a2);
    hash.add(a3);
    EXPECT_EQ(2, hash.find(a1));
    EXPECT_EQ(2, hash.find(a2));
    EXPECT_EQ(1, hash.find(a3));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
