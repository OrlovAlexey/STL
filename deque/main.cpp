#include <iostream>
#include <type_traits>
#include <cassert>

#include "Deque.hpp"
using namespace std;


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


    Deque<int> deque;
    return 0;
}
