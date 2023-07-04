#include <iostream>
//#include <unordered_map>
//#include "unordered_map.h"
#include "unordered_map_test.cpp"

using namespace std;

struct S{
    int a;
    std::string s;
    vector<int> wow;
    S() = default;
};

int main() {
    /*
    UnorderedMap<int, int> mm;
    auto b = mm.begin();
    auto orig = mm.insert({1, 2});
    mm.insert({2, 2});
    auto fake = mm.insert({1, 3});
//    mm.print();

    for (int i = 0; i < 100; ++i) {
        mm.emplace(make_pair(i, i + 1));
    }
//    cout << mm.size();
    UnorderedMap<int, int> m(std::move(mm));

//    cout << (m.size());
//    cerr << m.at(9);
//    for (auto& it : mm)
//        cout << it.first << " " << it.second << '\n';
    UnorderedMap<int, int> m1;
    m1.insert(m.begin(), m.end());
    for (auto& it : m1)
        cout << it.first << " " << it.second << '\n';
//    for (auto it = m.begin(); it != m.end(); ++it) {
//
//        cout << it->first << " " << it->second << '\n';
//    }
//
//    UnorderedMap<int, int>::Iterator cnst = mm.begin();
//    cout << ((++cnst) == mm.end()) << '\n';
//    cout << (orig.first == fake.first) << '\n';
//    m[9];
//    cout << (m.find(9) == m.end()) << '\n';

//    unordered_map<int, int> m1;
//    auto one = m1.insert({1, 2});
//    m1.insert({2, 2});
//    auto two =  m1.insert({1, 3});
//    m1[9];
//    m1.at(9);
//    for (auto t : m1) {
//        cout << t.first << " " << t.second << '\n';
//    }
//    cout << (one.first == two.first) << '\n';

    UnorderedMap<string, S> ss;
    ss.insert({(const string)"w", S()});
*/
//    UnorderedMap<int, std::string> m;
//    m.reserve(10);
//    m.insert({4, "Summer has come and passed"});
//    auto beg = m.begin();

    UnorderedMap<string, int> m;
//    m.reserve(100);
    m.insert({"a", 1});
    auto it = m.begin();
    for (int i = 0; i < 1000; ++i) {
        m.insert({std::to_string(i), i * i + 1});
    }

    auto mm = std::move(m);
    m = std::move(mm);
//    m.print();

//    std::cout << std::distance(it, m.end());

//    for (auto it = m.begin(); it != m.end(); ++it) {
//        cout << it->first << " " << it->second << '\n';
//    }
//    cout << ((++++++++it) == m.end());
//
//    m.erase(it, m.end());

//    SimpleTest();
//    TestIterators();
//    TestConstIteratorDoesntAllowModification(0);
//    TestNoRedundantCopies();
    TestCustomHashAndCompare();
    TestCustomAlloc();
    return 0;
}
