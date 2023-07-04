#pragma once
#include <cstdlib>
#include <memory>
#include <iostream>


template <typename T, typename Allocator = std::allocator<T>>
class List {
    struct Node {
        T value;
        Node* next;
        Node* prev;
        Node() = delete;
        Node(const T& Value, Node* Next, Node* Prev) : value(Value), next(Next), prev(Prev) {}
        Node(Node* Next, Node* Prev) : value(T()), next(Next), prev(Prev) {}
    };
    Node* first;
    Node* last;
    size_t sz;
    using NodeAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
    NodeAllocator alloc;
    using AllocTraits = std::allocator_traits<NodeAllocator>;

public:
    List() : alloc(NodeAllocator()) {
        sz = 0;
        first = AllocTraits::allocate(alloc, 1);
        last = AllocTraits::allocate(alloc, 1);
        first->next = last;
        last->prev = first;
    }
    explicit List(const Allocator& alloc1) : alloc(AllocTraits::select_on_container_copy_construction(alloc1)) {
        sz = 0;
        first = AllocTraits::allocate(alloc, 1);
        last = AllocTraits::allocate(alloc, 1);
        first->next = last;
        last->prev = first;
    }

    explicit List(size_t count, const T& value, const Allocator& alloc1 = Allocator()) : List(alloc1) {
        sz = count;
        Node* newnode;
        Node* prevnode = first;
        for (size_t i = 0; i < sz; ++i) {
            newnode = AllocTraits::allocate(alloc, 1);
            AllocTraits::construct(alloc, newnode, value, last, prevnode);
            prevnode->next = newnode;
            last->prev = newnode;
            prevnode = newnode;
        }
    }

    explicit List(size_t count, const Allocator& alloc1 = Allocator()) : List(alloc1) {
        sz = count;
        Node* newnode;
        Node* prevnode = first;
        for (size_t i = 0; i < sz; ++i) {
            newnode = AllocTraits::allocate(alloc, 1);
            AllocTraits::construct(alloc, newnode, last, prevnode);
            prevnode->next = newnode;
            last->prev = newnode;
            prevnode = newnode;
        }
    }

    NodeAllocator& get_allocator() {
        return alloc;
    }

    List(const List& another) : List(AllocTraits::select_on_container_copy_construction(another.alloc)) {
        sz = another.sz;
        Node* newnode;
        Node* prevnode = first;
        Node* an_first = another.first;
        for (size_t i = 0; i < sz; ++i) {
            an_first = an_first->next;
            newnode = AllocTraits::allocate(alloc, 1);
            AllocTraits::construct(alloc, newnode, an_first->value, last, prevnode);
            prevnode->next = newnode;
            last->prev = newnode;
            prevnode = newnode;
        }
    }

    List& operator= (const List& list1) {
        if (this != &list1) {
            Node* ptr = first;
            Node* prev;
            for (size_t i = 0; i < sz; ++i) {
                ptr = ptr->next;
                prev = ptr->prev;
                AllocTraits::destroy(alloc, prev);
                AllocTraits::deallocate(alloc, prev, 1);
            }
            if (AllocTraits::propagate_on_container_copy_assignment::value) {
                alloc = list1.alloc;
            }
            sz = list1.sz;
            first = AllocTraits::allocate(alloc, 1);
            last = AllocTraits::allocate(alloc, 1);
            first->next = last;
            last->prev = first;
            Node* newnode;
            Node* prevnode = first;
            Node* an_first = list1.first;
            for (size_t i = 0; i < sz; ++i) {
                an_first = an_first->next;
                newnode = AllocTraits::allocate(alloc, 1);
                AllocTraits::construct(alloc, newnode, an_first->value, last, prevnode);
                prevnode->next = newnode;
                last->prev = newnode;
                prevnode = newnode;
            }
        }
        return *this;
    }

    size_t size() const {
        return sz;
    }

    void push_back(T value) {
        Node* newnode = AllocTraits::allocate(alloc, 1);
        AllocTraits::construct(alloc, newnode, value, last, last->prev);
        last->prev->next = newnode;
        last->prev = newnode;
        ++sz;
    }

    void push_front(T value) {
        Node* newnode = AllocTraits::allocate(alloc, 1);
        AllocTraits::construct(alloc, newnode, value, first->next, first);
        first->next->prev = newnode;
        first->next = newnode;
        ++sz;
    }

    void pop_back() {
        Node* exnode = last->prev;
        exnode->prev->next = last;
        last->prev = exnode->prev;
        AllocTraits::destroy(alloc, exnode);
        AllocTraits::deallocate(alloc, exnode, 1);
        --sz;
    }

    void pop_front() {
        Node* exnode = first->next;
        exnode->next->prev = first;
        first->next = exnode->next;
        AllocTraits::destroy(alloc, exnode);
        AllocTraits::deallocate(alloc, exnode, 1);
        --sz;
    }

    template <bool IsConst = false>
    struct common_iterator : public std::iterator<std::bidirectional_iterator_tag, Node> {
        std::conditional_t<IsConst, const Node*, Node*> ptr;

        using value_type = std::conditional_t<IsConst, const T, T>;
        using pointer = std::conditional_t<IsConst, const T*, T*>;
        using reference = std::conditional_t<IsConst, const T&, T&>;

        common_iterator() : ptr(nullptr) {}
        common_iterator(std::conditional_t<IsConst, const Node*, Node*> Ptr) : ptr(Ptr) {}
        common_iterator(const common_iterator<false>& other) : ptr(other.ptr){}
        common_iterator& operator= (common_iterator it1) {
            ptr = it1.ptr;
            return *this;
        }
        common_iterator& operator++ () {
            ptr = ptr->next;
            return *this;
        }
        common_iterator operator++ (int) {
            common_iterator copy = *this;
            ++(*this);
            return copy;
        }
        common_iterator& operator-- () {
            ptr = ptr->prev;
            return *this;
        }
        common_iterator operator-- (int) {
            common_iterator copy = *this;
            --(*this);
            return copy;
        }
        bool operator== (const common_iterator<IsConst>& it1) const {
            return (ptr == it1.ptr);
        }
        bool operator!= (const common_iterator<IsConst>& it1) const {
            return !(*this == it1);
        }// (non-const == const) not works!!
        std::conditional_t<IsConst, const T&, T&> operator*() {
            return ptr->value;
        }
        std::conditional_t<IsConst, const T*, T*> operator->() {
            return &ptr->value;
        }
        friend common_iterator<false>;
    };

    using iterator = common_iterator<false>;
    using const_iterator = common_iterator<true>;

    iterator begin() {
        return iterator(first->next);
    }

    iterator end() {
        return iterator(last);
    }

    const_iterator begin() const {
        return const_iterator(const_cast<const Node*>(first->next));
    }

    const_iterator end() const {
        return const_iterator(const_cast<const Node*>(last));
    }

    const_iterator cbegin() const {
        return const_iterator(const_cast<const Node*>(first->next));
    }

    const_iterator cend() const {
        return const_iterator(const_cast<const Node*>(last));
    }

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    reverse_iterator rbegin() {
        return reverse_iterator(last);
    }
    reverse_iterator rend() {
        return reverse_iterator(first->next);
    }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(const_cast<const Node*>(last));
    }
    const_reverse_iterator rend() const {
        return const_reverse_iterator(const_cast<const Node*>(first->next));
    }
    const_reverse_iterator crbegin() {
        return const_reverse_iterator(const_cast<const Node*>(last));
    }
    const_reverse_iterator crend() {
        return const_reverse_iterator(const_cast<const Node*>(first->next));
    }

    void insert(const_iterator it, const T& value) {
        iterator find(const_cast<Node*>(it.ptr));
        Node* newnode = AllocTraits::allocate(alloc, 1);
        AllocTraits::construct(alloc, newnode, value, find.ptr, find.ptr->prev);
        find.ptr->prev->next = newnode;
        find.ptr->prev = newnode;
        ++sz;
    }

    void erase(const_iterator it) {
        iterator find(const_cast<Node*>(it.ptr));
        find.ptr->prev->next = find.ptr->next;
        find.ptr->next->prev = find.ptr->prev;
        AllocTraits::destroy(alloc, find.ptr);
        AllocTraits::deallocate(alloc, find.ptr, 1);
        --sz;
    }

    void print() {
        Node* p = first->next;
        for (size_t i = 0; i < sz; ++i) {
            std::cout << p->value;
            p = p->next;
        }
    }// print all elements in list

    ~List() {
        Node* ptr = first->next;
        Node* prev;
        for (size_t i = 0; i < sz; ++i) {
            ptr = ptr->next;
            prev = ptr->prev;
            AllocTraits::destroy(alloc, prev);
            AllocTraits::deallocate(alloc, prev, 1);
        }
    }
};
