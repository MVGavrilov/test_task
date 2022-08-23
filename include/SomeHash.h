#pragma once

#include <unordered_map>
#include <memory>
#include <mutex>
#include <iostream>

namespace SomeHash {
    template<typename T>
    class SomeHashTest;

    template<typename T>
    class SomeHash {
    public:

        friend class SomeHashTest<T>;

        SomeHash() {
            m_map = std::make_unique<std::unordered_map<T, unsigned int>>();
        }

        explicit SomeHash(const T &value) {
            m_map = std::make_unique<std::unordered_map<T, unsigned int>>();
            add(value);
        }

        SomeHash(const SomeHash &other) {
            m_map = std::make_unique<std::unordered_map<T, unsigned int>>(*other.m_map);
        }

        SomeHash(SomeHash &&other)  noexcept {
            m_map = std::move(other.m_map);
        }

        void add(const T &value) {
            const std::lock_guard<std::mutex> lock(m_mutex);
            if (m_map->find(value) == m_map->end()) {
                m_map->insert({value, 1});
            } else {
                if (m_map->at(value) < std::numeric_limits<unsigned int>::max()) {
                    (*m_map)[value]++;
                } else {
                    throw std::runtime_error("Too many elements in the hash");
                }
            }
        }

        unsigned int find(const T &value) const {
            const std::lock_guard<std::mutex> lock(m_mutex);
            if (m_map->find(value) == m_map->end()) {
                return 0;
            } else {
                return (*m_map)[value];
            }
        }

        void remove(const T &value) {
            const std::lock_guard<std::mutex> lock(m_mutex);
            if (m_map->find(value) != m_map->end()) {
                if ((*m_map)[value] == 1) {
                    m_map->erase(value);
                } else {
                    --(*m_map)[value];
                }
            } else {
                throw std::runtime_error("Element not found in the hash");
            }
        };

        friend std::ostream &operator<<(std::ostream &os, const SomeHash &hash) {
            const std::lock_guard<std::mutex> lock(hash.m_mutex);
            auto start_address = reinterpret_cast<size_t>(hash.m_map.get());
            for (const auto &[key, value]: *hash.m_map) {
                os << key << ": " << reinterpret_cast<size_t>(&value) - start_address << std::endl;
            }
            return os;
        }

        void display() const {
            std::cout << *this;
        }

    private:
        std::unique_ptr<std::unordered_map<T, unsigned int>> m_map;
        mutable std::mutex m_mutex;
    };

    // I’m not sure that the class for testing needs to be designed like this (rather sure that it isn’t),
    // but I didn’t come up with a normal way right away
    template<typename T>
    class SomeHashTest {
    public:
        SomeHashTest() = delete;
        explicit SomeHashTest(SomeHash<T> * hash): m_some_hash(hash) {}
        void set_value(const T &key, const unsigned int &value) {
            (*m_some_hash->m_map)[key] = value;
        }
    private:
        SomeHash<int> * m_some_hash;
    };
}
