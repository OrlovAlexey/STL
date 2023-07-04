#include <iostream>
#include <vector>
#include <list>
#include <time.h>
#include <assert.h>
#include "tests/list_test.cpp"
#include <type_traits>
#include <string>
#include <utility>
#include <iomanip>

#include "FastAllocator.hpp"
#include "List.hpp"

using namespace std;


int main() {
    List<int, FastAllocator<int>> list;
    return 0;
}
