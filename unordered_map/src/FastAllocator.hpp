#pragma once
#include "FixedAllocator.hpp"

template <typename T>
class FastAllocator {
public:
    FixedAllocator<4> fixed_alloc4;
    FixedAllocator<8> fixed_alloc8;
    typedef size_t     size_type;
    typedef ptrdiff_t  difference_type;
    typedef T*         pointer;
    typedef const T*   const_pointer;
    typedef T&         reference;
    typedef const T&   const_reference;
    typedef T          value_type;
    template<typename U>
    struct rebind {
        using other = FastAllocator<U>;
    };

    FastAllocator() noexcept {}

    FastAllocator(const FastAllocator& fastAllocator1) noexcept {
        fixed_alloc4 = fastAllocator1.fixed_alloc4;
        fixed_alloc8 = fastAllocator1.fixed_alloc8;
    }

    template <class U>
    FastAllocator (const FastAllocator<U>& fastAllocator1) noexcept {
        fixed_alloc4 = fastAllocator1.fixed_alloc4;
        fixed_alloc8 = fastAllocator1.fixed_alloc8;
    }

    FastAllocator& operator= (const FastAllocator<value_type>& fastAllocator1) {
        if (this != &fastAllocator1) {
            fixed_alloc4 = fastAllocator1.fixed_alloc4;
            fixed_alloc8 = fastAllocator1.fixed_alloc8;
        }
        return *this;
    }
    struct propagate_on_container_move_assignment : std::true_type {};

    pointer allocate(size_type n) {
        pointer ptr;
        size_t sz = n * sizeof(value_type);
        if (sz % 8 == 0) {
            ptr = reinterpret_cast<pointer>(fixed_alloc8.allocate(sz / 8));
        }
        else if (sz % 4 == 0) {
            ptr = reinterpret_cast<pointer>(fixed_alloc4.allocate(sz / 4));
        }
        else {
            ptr = reinterpret_cast<pointer>(::operator new(sz));
        }
        return ptr;
    }

    void deallocate(pointer ptr, size_type n) {
        if (!ptr) {
            return;
        }
        size_t sz = n * sizeof(value_type);
        if (sz % 8 == 0) {
            fixed_alloc8.deallocate(reinterpret_cast<int8_t*>(ptr));
        }
        else if (sz % 4 == 0) {
            fixed_alloc4.deallocate(reinterpret_cast<int8_t*>(ptr));
        }
        else {
            ::operator delete(ptr);
        }
    }

    template <typename... Args>
    void construct(pointer ptr, const Args&... args) {
        new(ptr) T(args...);
    }
    void destroy(pointer ptr) {
        ptr->~value_type();
    }
    ~FastAllocator() = default;
};

template <>
class FastAllocator<char*>{
public:
    typedef size_t         size_type;
    typedef ptrdiff_t      difference_type;
    typedef char**         pointer;
    typedef const char**   const_pointer;
    typedef char*&         reference;
    typedef const char*&   const_reference;
    typedef char*          value_type;

    template<typename U>
    struct rebind {
        using other = FastAllocator<U>;
    };

    FastAllocator() noexcept {}

    FastAllocator (const FastAllocator&) noexcept {}

    template <typename U>
    FastAllocator (const FastAllocator<U>&) noexcept {}

    FastAllocator& operator= (const FastAllocator<value_type>&) {
        return *this;
    }
    struct propagate_on_container_move_assignment : std::true_type {};

    pointer allocate(size_type n) {
        return reinterpret_cast<pointer>(::operator new(n * sizeof(value_type)));
    }

    void deallocate(pointer ptr, size_type n) {
        if (!ptr) {
            return;
        }
        ::operator delete(ptr, n * sizeof(value_type));
    }

    template <typename... Args>
    void construct(pointer ptr, const Args&... args) {
        new(ptr) value_type(args...);
    }
    void destroy(pointer ptr) {
        ptr->~value_type();
    }
    ~FastAllocator() = default;
};

template <class T, class U>
bool operator== (const FastAllocator<T>&, const FastAllocator<U>&) {
    return true;
}

template <class T, class U>
bool operator!= (const FastAllocator<T>&, const FastAllocator<U>&) {
    return false;
}
