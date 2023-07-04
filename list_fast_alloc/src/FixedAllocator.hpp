#pragma once
#include "Pool.hpp"

template <size_t chunkSize>
class FixedAllocator {
    std::shared_ptr<Pool> pool;
    size_t used;
    static const size_t starting_size = 100;
public:
    FixedAllocator() {
        pool = std::make_shared<Pool>(0, starting_size * chunkSize);
        pool->pull.push_back(reinterpret_cast<int8_t*>(::operator new(starting_size * chunkSize)));
        used = 0;
    }
    FixedAllocator& operator= (const FixedAllocator& fixed1) {
        if (this != &fixed1) {
            pool = fixed1.pool;
            used = fixed1.used;
        }
        return *this;
    }
    int8_t* allocate(size_t n) {
        size_t temp = used;
        used += n * chunkSize;
        if (used > pool->current_capacity) {
            pool->next_block(chunkSize);
            used = n * chunkSize;
            temp = 0;
        }
        return (pool->pull[pool->index] + temp);
    }
    void deallocate(int8_t*) {}
    ~FixedAllocator() = default;
};
