#include <iostream>
#include <gtest/gtest.h>
#include "String.hpp"

using namespace std;


TEST(StringTest, Constructors) {
    String s;
    String ss{'a', 'b', 'c'};
    String sss("testes");
}

TEST(StringTest, Plus) {
    String s;
    String ss{'a', 'b', 'c'};
    String sss("testes");
    String ssss = s + sss;
    ASSERT_EQ(ssss, "testes");
    ssss = ss;
    ssss += 'a';
    ASSERT_EQ(ssss, "abca");
}

TEST(StringTest, Equality) {
    String s;
    String ss{'a', 'b', 'c'};
    String sss("testes");
    s = sss;
    bool equality = s.operator==(sss);
    bool inequality = s.operator==(ss);
    ASSERT_TRUE(equality);
    ASSERT_FALSE(inequality);
    inequality = s.operator!=(sss);
    equality = s.operator!=(ss);
    ASSERT_TRUE(equality);
    ASSERT_FALSE(inequality);
}

TEST(StringTest, Find) {
    String s("My String is very beautiful.");
    size_t index = s.find("es");
    ASSERT_EQ(index, (size_t)-1);
    index = s.find("is");
    ASSERT_EQ(index, 10);
    index = s.rfind("e");
    ASSERT_EQ(index, 19);
    ASSERT_EQ(String("ing"), s.substr(6, 3));
}

TEST(StringTest, BigString) {
    String big_s;
    for (size_t i = 0; i < 100000000; ++i) {
        big_s.push_back('a');
    }
    for (size_t i = 0; i < 100000000; ++i) {
        big_s.pop_back();
    }
    ASSERT_EQ(big_s, "");
}

TEST(StringTest, TimeMeasure) {
    String ss;
    int k = 0;
    while (k < 100) {
        clock_t start = clock();
        ss[1] = 'a';
        for (size_t i = 0; i < 100000000; ++i) {
            ss.push_back('a');
        }
        ss += 'a';
        for (size_t i = 0; i < 100000000; ++i) {
            ss.pop_back();
        }
        cout << ss << '\n';
        clock_t end = clock();
        double seconds = (double) (end - start) / CLOCKS_PER_SEC;
        printf("The time: %f seconds\n", seconds);
        k++;
    }
    cout << ss.front() << " " << ss.back() << '\n';
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}