#include <iostream>
#include <type_traits>
#include <cassert>

#include "correct_deque.h"
using namespace std;


void test1() {
    Deque<int> d(10, 3);

    d[3] = 5;

    d[7] = 8;

    d[9] = 10;

    std::string s = "33353338310";
    std::string ss;
    Deque<int> dd;

    {
        Deque<int> d2 = d;

        dd = d2;
    }

    d[1] = 2;

    d.at(2) = 1;

    try {
        d.at(10) = 0;
        assert(false);
    } catch (std::out_of_range&) {}

    const Deque<int>& ddd = dd;
    for (size_t i = 0; i < ddd.size(); ++i) {
        ss += std::to_string(ddd[i]);
    }

    assert(s == ss);
}

void test2() {
    Deque<int> d(1);

    d[0] = 0;

    for (int i = 0; i < 8; ++i) {
        d.push_back(i);
        d.push_front(i);
    }

    for (int i = 0; i < 12; ++i) {
        d.pop_front();
    }

    d.pop_back();
    assert(d.size() == 4);

    std::string ss;
//    d.print();
    for (size_t i = 0; i < d.size(); ++i) {
        ss += std::to_string(d[i]);
    }
//
    assert(ss == "3456");
}

void test3() {
    Deque<int> d;

    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 1000; ++j) {

            if (j % 3 == 2) {
                d.pop_back();
            } else {
                d.push_front(i*j);
            }

        }
    }

    assert(d.size() == 334'000);
//    cout << d.end() - d.begin();
    Deque<int>::iterator left = d.begin() + 100'000;
    Deque<int>::iterator right = d.end() - 233'990;
    while (d.begin() != left) d.pop_front();
    while (d.end() != right) d.pop_back();

    assert(d.size() == 10);

    assert(right - left == 10);

    std::string s;
    for (auto it = left; it != right; ++it) {
        ++*it;
    }
    for (auto it = right - 1; it >= left; --it) {
        s += std::to_string(*it);
    }

    assert(s == "51001518515355154401561015695158651595016120162051");
}

struct S {
    int x = 0;
    double y = 0.0;
};

void test4() {

    Deque<S> d(5, {1, 2.0});
    const Deque<S>& cd = d;

    static_assert(!std::is_assignable_v<decltype(*cd.begin()), S>);
    static_assert(std::is_assignable_v<decltype(*d.begin()), S>);
    static_assert(!std::is_assignable_v<decltype(*d.cbegin()), S>);

    static_assert(!std::is_assignable_v<decltype(*cd.end()), S>);
    static_assert(std::is_assignable_v<decltype(*d.end()), S>);
    static_assert(!std::is_assignable_v<decltype(*d.cend()), S>);

    assert(cd.size() == 5);

    auto it = d.begin() + 2;
    auto cit = cd.end() - 3;

    it->x = 5;
    assert(cit->x == 5);

    d.erase(d.begin() + 1);
    d.erase(d.begin() + 3);
    assert(d.size() == 3);

    auto dd = cd;

    dd.pop_back();
    dd.insert(dd.begin(), {3, 4.0});
    dd.insert(dd.begin() + 2, {4, 5.0});

    std::string s;
    for (const auto& x: dd) {
        s += std::to_string(x.x);
    }
    assert(s == "3145");

    std::string ss;
    for (const auto& x: d) {
        ss += std::to_string(x.x);
    }
    assert(ss == "151");
}

void test5() {
    Deque<int> d;

    d.push_back(1);
    d.push_front(2);

    auto left_ptr = &*d.begin();
    auto right_ptr = &*(d.end()-1);

    d.push_back(3);
    d.push_front(4);
    auto left = *d.begin();
    auto right = *(d.end()-1);

    for (int i = 0; i < 10'000; ++i) {
        d.push_back(i);
    }
    for (int i = 0; i < 20'000; ++i) {
        d.push_front(i);
    }

    std::string s;
    s += std::to_string(left);
    s += std::to_string(right);

    s += std::to_string(*left_ptr);
    s += std::to_string(*right_ptr);
    //for (auto it = left; it <= right; ++it) {
    //    s += std::to_string(*it);
    //}
    assert(s == "4321");
}

struct VerySpecialType {
    int x = 0;

    explicit VerySpecialType(int x): x(x) {}
};

struct NotDefaultConstructible {
    NotDefaultConstructible() = delete;
    NotDefaultConstructible(const NotDefaultConstructible&) = default;
    NotDefaultConstructible& operator=(const NotDefaultConstructible&) = default;

    NotDefaultConstructible(VerySpecialType v): x(v.x) {}

public:
    int x = 0;
};

void test6() {
    Deque<NotDefaultConstructible> d;

    NotDefaultConstructible ndc = VerySpecialType(-1);

    for (int i = 0; i < 1500; ++i) {
        ++ndc.x;
        d.push_back(ndc);
    }

    assert(d.size() == 1500);

    for (int i = 0; i < 1300; ++i) {
        d.pop_front();
    }

    assert(d.size() == 200);

    assert(d[99].x == 1399);

    d[100] = VerySpecialType(0);
    assert(d[100].x == 0);
}


struct Explosive {
    int x = 0;
    Explosive(int x): x(x) {}
    Explosive(const Explosive&) {
        if (x) throw std::runtime_error("Boom!");
    }
};

void test7() {

    Deque<Explosive> d;
    d.push_back(Explosive(0));

    for (int i = 0; i < 30'000; ++i) {
        auto it = d.begin();
        auto x = it->x;
        size_t sz = d.size();
        try {
            if (i % 2)
                d.push_back(Explosive(1));
            else
                d.push_front(Explosive(1));
        } catch (...) {
            assert(it == d.begin());
            assert(d.begin()->x == x);
            assert(d.size() == sz);
        }

        d.push_back(Explosive(0));
    }
}


/*
struct S {
    int a;
    string s;
    S() = delete;
    S(int a, string s) : a(a), s(s) {}
};*/
int main() {
//    int n, m;
//    cin >> n;
//    Deque<int> d(27, 3);
//    Deque<string> d1;
//    Deque<S> d2;
//    S s1(1, "a"), s2(2, "b");
//    d2.push_back(s1);
//    d2.push_front(s2);
//    d2.pop_back();
//    d2.pop_back();
//    d2.pop_back();
//    for (int i = 0; i < n; ++i) {
//        d2.push_back(S(i, "i"));
//    }
//    for (int i = 0; i < n; ++i) {
//        d2.pop_back();
//    }
//    d1 = d;
//    d1.print();
//    d.push_back(1000);
//for (int i = 0; i < n; ++i)
//    d1.push_back("a");
//for (int i = 0; i < n; ++i)
//    d1.pop_back();
//    for (int i = 0; i < n; ++i)
//        cout << d1[i] << ' ';
//    cout << '\n';
//    S s1, s2;
//    d2.push_back(1);
//    d1 = d2;
//    d2.pop_back();
//    d2.push_back(2);
//    d2.push_back(3);
//    cout << d2.at(0);
//    Deque<int>::iterator it = d2.end();
//    it--;
//    it--;
//    cout << *it;
/*
    Deque<int> d;
    for (int i = 1; i <= n; ++i)
        d.push_back(i);
    d.print();
    Deque<int>::iterator it = d.begin();
    cout << *it << " " << it.index.first << " " << it.index.second << '\n';
//    it.plusplus(1);
    it = it + 16;
    cout << *it << " " << it.index.first << " " << it.index.second << '\n';
*/

//    Deque<int> d(1000);
//    Deque<int>::iterator it = d.begin() + 900;
//    d.insert(it, 100);
//    d.erase(--it);
//    d.print();
//    while (d.begin() != it) {
//        d.pop_front();
//    }
//    cout << *(it--);


/*
    Deque<int> d;
    for (int i = 0; i < 100; ++i) {
        d.push_back(i);
    }
    Deque<int>::iterator it = d.end() - 7;
    for (int i = 1; i < 93;++i) {
        cout << *(it - i) << " ";
        if (i % 10 == 0)
            cout << '\n';
    }
    */
//    cout << *(it - 40);
//    test1();
//    test2();
//    test3();
//    test1();
//    d2.print();
//    d1.print();
//    d.push_back(5);
//    cout << d[0] << '\n';
//    d.push_back(10);
//    cout << d[0] << " " << d[1] << '\n';
    test1();
    std::cout << "Test 1 passed.\n";

    test2();
    std::cout << "Test 2 passed.\n";

    test3();
    std::cout << "Test 3 passed.\n";

    test4();
    std::cout << "Test 4 passed.\n";

    test5();
    std::cout << "Test 5 passed.\n";

    test6();
    std::cout << "Test 6 passed.\n";

    test7();
    std::cout << "Tests passed, congratulations!\n";
    return 0;
}
