#include <iostream>
#include "fastallocator.h"
#include <vector>
#include <list>
#include <time.h>
#include <assert.h>
#include "tests/list_test.cpp"
#include <type_traits>
#include <string>
#include <utility>
#include <iomanip>

using namespace std;
/*
struct S {
    static int ctor_calls;
    static int dtor_calls;
    int a, b;
    S() {
        ++ctor_calls;

        a = 5;
        b = 10;
    }
    S(const S& s1) : a(s1.a), b(s1.b) {
        ++ctor_calls;

    }
    ~S() {
        dtor_calls++;
    }
};
int S::ctor_calls = 0;
int S::dtor_calls = 0;

struct D {
    char a, b, c;
    D() {
        a = 'a';
        b = 'b';
        c = 'c';
    }
};
 */

int main() {
/*
    FixedAllocator<8> alloc;
    int* a = reinterpret_cast<int*>(alloc.allocate(1));
    for (int i = 0; i < 8; ++i) {
        cin >> a[i];
    }

    for (int i = 0; i < 8; ++i) {
        cout << a[i];
    }
    alloc.deallocate(reinterpret_cast<int8_t *>(a));
*/
/*
    vector<int, FastAllocator<int>> v(4);
    for (int i = 0; i < 4; ++i) {
        cin >> v[i];
    }

    for (int i = 0; i < 4; ++i) {
        cout << v[i];
    }
    v.pop_back();
*/
/*
    std::list<int> original;
    std::list<int, FastAllocator<int>> fast;


    clock_t start1 = clock();
    for (int i = 0; i < 100000; ++i) {
        original.push_back(i);
    }
    for (int i = 0; i < 100000; ++i) {
        original.pop_back();
    }
    clock_t end1 = clock();
    double seconds1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
    cout << "original: "  << seconds1 << '\n';


    clock_t start2 = clock();
    for (int i = 0; i < 10; ++i) {
        fast.push_back(i);
    }
    for (int i = 0; i < 100000; ++i) {
        fast.pop_back();
    }
    clock_t end2 = clock();
    double seconds2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
    cout << "fast: "  << seconds2 << '\n';
*/

    vector<int, FastAllocator<int>> v;
    list<int, FastAllocator<int>> orig1(10);
    list<int, FastAllocator<int>> orig2(1);
    orig2 = orig1;
    orig2.push_back(7);
    orig2.push_front(4);
    deque<int, FastAllocator<int>> d;
//    for (auto i : orig2) {
//        cout << i;
//    }
    for ( list<int, FastAllocator<int>>::iterator it = orig2.begin(); it != orig2.end(); ++it ) {
        int x = *it;
        cout << x;
    }

/*
    List<int, FastAllocator<int>> lst1(10);
    lst1.push_back(2);
    lst1.push_front(3);
    List<int, FastAllocator<int>> lst2;
    lst2 = lst1;
    lst2.pop_back();
    lst2.pop_front();
    lst2.insert(++lst2.begin(), 8);
    lst2.erase(++lst2.begin());
    lst1.print();
    lst2.print();
    */

/*
    List<int, FastAllocator<int>> lst;
    for (int i = 0; i < 10; ++i) {
        lst.push_back(i);
    }
    List<int, FastAllocator<int>>::iterator normal = lst.begin();
    List<int, FastAllocator<int>>::const_iterator constant = lst.begin();
    if (constant == normal) {
        cout << "good" << '\n';
    }
//    normal = constant;
    constant = normal;

    auto itera = lst.end();
    lst.insert(itera, 1);
    --itera;
    lst.erase(itera);

    auto it = lst.begin();
    while (it != lst.end()) {
        cout << *it;
        ++it;
    }
    */
/*
    List<int, FastAllocator<int>> lst(10, 1);
    for (int i = 0; i < 100000; ++i) {
        lst.push_back(i);
    }
    for (int i = 0; i < 100000; ++i) {
        lst.pop_back();
    }
    assert(lst.size() == 10);
    auto it = lst.rbegin();
    while (it != lst.rend()) {
        cout << *it;
        ++it;
    }
    */
/*
    {
        List<S, FastAllocator<S>> lst(5);
    }
    cout << S::ctor_calls << '\n';
    cout << S::dtor_calls << '\n';
*/
/*
    List<int, FastAllocator<int>> lst(10);
    for (int i = 0; i < 10000; ++i) {
        lst.push_back(i);
    }
//    for (int i = 0; i < 1000000; ++i) {
//        lst.pop_back();
//    }
    auto it = lst.end(); it--;
    auto end = lst.begin(); end++; end++; end++; end++;
    while (end != it) {
        lst.erase(it);
        it--;
    }
    for (auto i : lst) {
        cout << i << " ";
    }
    */

/*
    FastAllocator<D> fast1;
    FastAllocator<D> fast2;
    fast2 = fast1;

    List<int, FastAllocator<int>> lst1;
    List<int, FastAllocator<int>> lst2;
    lst2 = lst1;
*/

//    List<int, FastAllocator<int>> fast;
//
//    test_list<List<int, FastAllocator<int>>>(std::move(fast));
//    std::deque<char, FastAllocator<char>> deq;
//
//    test_std_deque(std::move(deq));
//    BasicListTest<>();

//    BasicListTest<FastAllocator<int>>();

//    TestAccountant<>(); //TROUBLES



//    TestAccountant<FastAllocator<Accountant>>();

//    TestNotDefaultConstructible<>();
//    TestNotDefaultConstructible<FastAllocator<NotDefaultConstructible>>();

//    TestNotDefaultConstructible<FastAllocator<deque<int>>>();

//    deque<char, FastAllocator<char>> deq1;
//    for (int i = 0; i < 10000; ++i) {
//        deq1.push_back('a');
//        deq1.push_front('a');
//    }
//    for (int i = 0; i < 10000; ++i) {
//        deq1.pop_back();
//        deq1.pop_front();
//    }
//    deque<char, FastAllocator<char>> deq2 = std::move(deq1);


//    test_std_deque(std::deque<char, FastAllocator<char>>());
//    TestWhimsicalAllocator();

//    TestWhimsicalAllocator();

//    TestPerformance<std::list>();

    BasicListTest<FastAllocator<int>>();

//    lst.print();
//    for (auto i : lst2) {
//        cout << i;
//    }
//    List<int, FastAllocator<int>>::reverse_iterator it = lst2.rbegin();
//    while(it != lst2.rend()) {
//        cout << *it;
//        it++;
//    }
    return 0;
}
