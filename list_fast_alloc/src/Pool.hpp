#pragma once
#include <vector>

struct Pool {
    std::vector<int8_t*> pool;
    size_t index, current_capacity;
    Pool(size_t index, size_t current_capacity) : index(index), current_capacity(current_capacity) {}
    void next_block(size_t chunkSize) {
        pool.push_back(reinterpret_cast<int8_t*>(::operator new(2 * current_capacity * chunkSize)));
        ++index;
        current_capacity *= 2;
    }
    ~Pool() {
        for (auto block : pool) {
            ::operator delete(block);
        }
    }
};
