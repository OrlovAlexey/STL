#pragma once
#include <set>
#include <cmath>
#include <vector>

#include "List.hpp"

using std::pair;
using std::vector;

template <typename Key, typename Value, typename Hash = std::hash<Key>, typename Equal = std::equal_to<Key>, typename Alloc = std::allocator<std::pair<const Key, Value>>>
class UnorderedMap{
private:
    size_t sz;
    size_t bucket_n;
    using NodeType = pair<const Key, Value>;
    using hashedNodeType = pair<NodeType, size_t>;
    vector<List<hashedNodeType, Alloc>> hashTable;
    Hash hasher;
    Equal key_equal;
    constexpr static const float static_max_load_factor = 1.0;
    std::set<size_t> pointers;
public:

    UnorderedMap() : sz(), bucket_n(1), hashTable(1), hasher(), key_equal(), pointers() {}

    explicit UnorderedMap(size_t bucket_count, const Hash& hash = Hash(), const Equal& equal = Equal(), const Alloc& alloc = Alloc() ) : sz(), bucket_n(bucket_count), hasher(hash), key_equal(equal), pointers() {
        hashTable(bucket_count, alloc);
    }

    UnorderedMap(const UnorderedMap& other) {
        sz = other.sz;
        bucket_n = other.bucket_n;
        hasher = other.hasher;
        key_equal = other.key_equal;
        for (auto& chain : other.hashTable) {
            hashTable.push_back(chain);
        }
        pointers = other.pointers;
    }

    UnorderedMap(UnorderedMap&& other)  noexcept {
        sz = other.sz;
        other.sz = 0;
        bucket_n = other.bucket_n;
        other.bucket_n = 1;
        hasher = std::move(other.hasher);
        key_equal = std::move(other.key_equal);
        hashTable = std::move(other.hashTable);
        pointers = std::move(other.pointers);
    }

    UnorderedMap& operator= (const UnorderedMap& umap1) {
        if (this != &umap1) {
            sz = umap1.sz;
            bucket_n = umap1.bucket_n;
            hasher = umap1.hasher;
            key_equal = umap1.key_equal;
            hashTable = umap1.hashTable;
            pointers = umap1.pointers;
        }
        return *this;
    }

    UnorderedMap& operator= (UnorderedMap&& umap1)  noexcept {
        if (this != &umap1) {
            sz = umap1.sz; umap1.sz = 0;
            bucket_n = umap1.bucket_n; umap1.bucket_n = 1;
            hasher = std::move(umap1.hasher);
            key_equal = std::move(umap1.key_equal);
            hashTable = std::move(umap1.hashTable);
            pointers = std::move(umap1.pointers);
        }
        return *this;
    }

    Value& operator[] (const Key& key) {
        size_t hashValue = hasher(key) % bucket_n;
        auto& chain = hashTable[hashValue];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (key_equal(it->first.first, key)) {
                return it->first.second;
            }
        }
        auto pair_it = insert({key, Value()});
        return ((pair_it.first)->second);
    }

//    Value& operator[] (Key&& key) {
//
//    }

    Value& at(const Key& key) {
        size_t hashValue = hasher(key) % bucket_n;
        auto& chain = hashTable[hashValue];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (key_equal(it->first.first, key)) {
                return it->first.second;
            }
        }
        throw std::out_of_range("No such key in map.");
    }

    const Value& at(const Key& key) const {
        size_t hashValue = hasher(key) % bucket_n;
        auto& chain = hashTable[hashValue];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (key_equal(it->first->first, key)) {
                return it->first->second;
            }
        }
        throw std::out_of_range("No such key in map.");
    }

    size_t size() const {
        return sz;
    }

    template <bool IsConst = false>
    struct CommonIterator : public std::iterator<std::forward_iterator_tag, hashedNodeType> {
        using ListIter = typename List<hashedNodeType, Alloc>::iterator;
        using ConstListIter = typename List<hashedNodeType, Alloc>::const_iterator;
        std::conditional_t<IsConst, ConstListIter, ListIter> inner_iter;
        using SetIter = typename std::set<size_t>::iterator;
        using ConstSetIter = typename std::set<size_t>::const_iterator;
        std::conditional_t<IsConst, ConstSetIter, SetIter> outer_iter;
        std::conditional_t<IsConst, const UnorderedMap*, UnorderedMap*> owner;

        using value_type = std::conditional_t<IsConst, const NodeType, NodeType>;
        using pointer = std::conditional_t<IsConst, const NodeType*, NodeType*>;
        using reference = std::conditional_t<IsConst, const NodeType&, NodeType&>;

        CommonIterator() : inner_iter(), outer_iter(), owner(nullptr) {}

        CommonIterator(std::conditional_t<IsConst, ConstListIter, ListIter> iter, std::conditional_t<IsConst, ConstSetIter, SetIter> index, std::conditional_t<IsConst, const UnorderedMap*, UnorderedMap*> owner) : inner_iter(iter), outer_iter(index), owner(owner) {}

        CommonIterator(const CommonIterator<false> &other) : inner_iter(other.inner_iter), outer_iter(other.outer_iter), owner(other.owner) {}

        CommonIterator& operator= (CommonIterator it1) {
            inner_iter = it1.inner_iter;
            outer_iter = it1.outer_iter;
            owner = it1.owner;
            return *this;
        }

        CommonIterator& operator++ () {
            inner_iter++;
            if (inner_iter == owner->hashTable[*outer_iter].end()) {
                ++outer_iter;
                if (outer_iter == owner->pointers.end()) {
                    return *this;
                }
                inner_iter = owner->hashTable[*outer_iter].begin();
            }
            return *this;
        }

        CommonIterator operator++ (int) {
            CommonIterator copy = *this;
            ++(*this);
            return copy;
        }

        bool operator== (const CommonIterator<IsConst>& it1) const {
            return (outer_iter == it1.outer_iter && inner_iter == it1.inner_iter && owner == it1.owner);
        }

        bool operator!= (const CommonIterator<IsConst>& it1) const {
            return !(*this == it1);
        }

        reference operator* () {
            return inner_iter->first;
        }

        pointer operator-> () {
            return &(inner_iter->first);
        }

        friend CommonIterator<false>;
    };
    using Iterator = CommonIterator<false>;
    using ConstIterator = CommonIterator<true>;

    Iterator begin() {
        if (hashTable.begin() == hashTable.end())
            return end();
        return Iterator(hashTable[*pointers.begin()].begin(), pointers.begin(), this);
    }

    Iterator end() {
        if (hashTable.begin() == hashTable.end())
            return Iterator(nullptr, pointers.end(), this);
        return Iterator(hashTable[*(--pointers.end())].end(), pointers.end(), this);
    }

    ConstIterator begin() const {
        return ConstIterator(hashTable[*pointers.begin()].begin(), pointers.begin(), this);
    }

    ConstIterator end() const {
        return ConstIterator(hashTable[*(--pointers.end())].end(), pointers.end(), this);
    }

    ConstIterator cbegin() const {
        return ConstIterator(hashTable[*pointers.begin()].begin(), pointers.begin(), this);
    }

    ConstIterator cend() const {
        return ConstIterator(hashTable[*(--pointers.end())].end(), pointers.end(), this);
    }

    pair<Iterator, bool> insert(const NodeType& pair_value) {
        auto& key = pair_value.first;
        auto& value = pair_value.second;
        if (load_factor() >= max_load_factor()) {
            rehash(2 * bucket_n);
        }

        size_t hashValue = hasher(key);
        auto& chain = hashTable[hashValue % bucket_n];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (key_equal(it->first.first, key)) {
                return {Iterator(it, pointers.find(hashValue % bucket_n), this), false};
            }
        }
        chain.push_back(std::make_pair(std::make_pair(key, value), hashValue));
        ++sz;
        auto temp_it = pointers.insert(hashValue % bucket_n);
        return {Iterator(--chain.end(), temp_it.first, this), true};
    }

    template <typename NodeTypeT>
    auto insert(NodeTypeT&& pair_value) -> pair<Iterator, bool> {
        if (load_factor() >= max_load_factor()) {
            rehash(2 * bucket_n);
        }

        size_t hashValue = hasher(std::forward<const Key>(pair_value.first));
        auto& chain = hashTable[hashValue % bucket_n];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (key_equal(std::forward<const Key>(it->first.first), std::forward<const Key>(pair_value.first))) {
                return {Iterator(it, pointers.find(hashValue % bucket_n), this), false};
            }
        }
        chain.push_back(std::forward<NodeTypeT>(pair_value), hashValue);
        ++sz;
        auto temp_it = pointers.insert(hashValue % bucket_n);
        return {Iterator(--chain.end(), temp_it.first, this), true};
    }

    auto insert(NodeType&& x) {
        return insert<>(x);
    }

    template <class InputIt>
    void insert(InputIt first, InputIt last) {
        for (InputIt iter = first; iter != last; ++iter) {
            auto temp = *iter;
            insert(temp);
        }
    }

    template <class... Args>
    pair<Iterator, bool> emplace(Args&&... args) {
        if (load_factor() >= max_load_factor()) {
            rehash(2 * bucket_n);
        }

        typename List<hashedNodeType, Alloc>::iterator list_it = hashTable[0].makeNode(std::forward<Args>(args)...);
        size_t hashValue = hasher(list_it->first.first);
        list_it->second = hashValue;

        auto &chain = hashTable[hashValue % bucket_n];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (key_equal(it->first.first, list_it->first.first)) {
                hashTable[0].deleteNode(list_it);
                return {Iterator(it, pointers.find(hashValue % bucket_n), this), false};
            }
        }
        chain.insert_back(list_it);
        ++sz;
        auto temp_it = pointers.insert(hashValue % bucket_n);
        return {Iterator(--chain.end(), temp_it.first, this), true};
    }

    Iterator erase(Iterator iter) {
        auto copy = iter;
        ++copy;
        size_t hashValue = hasher(iter->first);
        --sz;
        hashTable[hashValue % bucket_n].erase(iter.inner_iter);
        if (hashTable[hashValue % bucket_n].empty()) {
            pointers.erase(hashValue % bucket_n);
        }
        return copy;
    }

    Iterator erase(ConstIterator iter) {
        auto copy = iter;
        copy++;
        size_t hashValue = hasher(iter->first);
        --sz;
        hashTable[hashValue % bucket_n].erase(iter.inner_iter);
        if (hashTable[hashValue % bucket_n].empty()) {
            pointers.erase(hashValue % bucket_n);
        }
        return copy;
    }

    template <class InputIt>
    Iterator erase(InputIt first, InputIt last) {
        Iterator iter;
        for (iter = first; iter != last;) {
            iter = erase(iter);
        }
        return iter;
    }

    Iterator find(const Key& key) {
        size_t hashValue = hasher(key);
        auto& chain = hashTable[hashValue % bucket_n];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (key_equal(it->first.first, key)) {
                return Iterator(it, pointers.find(hashValue % bucket_n), this);
            }
        }
        return end();
    }

    ConstIterator find(const Key& key) const {
        size_t hashValue = hasher(key);
        auto& chain = hashTable[hashValue % bucket_n];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (key_equal(it->first.first, key)) {
                return Iterator(it, pointers.find(hashValue % bucket_n), this);
            }
        }
        return end();
    }

    void rehash(size_t count) {
        size_t old_bucket_n = bucket_n;
        bucket_n = count;
        vector<List<hashedNodeType, Alloc>> new_hashTable(bucket_n);
        std::set<size_t> new_pointers;
        size_t hashValue;
        for (size_t i = 0; i < old_bucket_n; ++i) {
            auto it = hashTable[i].begin();
            auto it_copy = it;
            for (; it != hashTable[i].end(); it = it_copy) {
                it_copy = it;
                it_copy++;
                hashValue = it->second;
                new_hashTable[hashValue % bucket_n].insert_back(it);
                new_pointers.insert(hashValue % bucket_n);
            }
            hashTable[i].make_empty();
        }
        hashTable = std::move(new_hashTable);
        pointers = std::move(new_pointers);
    }

    void reserve(size_t count) {
        if (count <= bucket_n)
            return;
        rehash(std::ceil(static_cast<float>(count) / max_load_factor()));
    }

    float load_factor() const {
        return (static_cast<float>(sz) / static_cast<float>(bucket_n));
    }

    float max_load_factor() const {
        return static_max_load_factor;
    }

    size_t max_size() const {
        return bucket_n;
    }

    ~UnorderedMap() = default;

    void print() {
        for (auto& chain : hashTable) {
            for (auto& element : chain) {
                std::cout << element.first.first << " " << element.first.second << '\n';
            }
        }
    }
};