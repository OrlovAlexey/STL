#include <iostream>
#include <cstring>

using namespace std;


class String {
private:
    size_t sz = 0;
    size_t capacity = 1;
    char* str = new char[1];
public:
    String();
    String(const char *s);
    String(size_t sz, char c = '\0');
    String(std::initializer_list<char> lst); // example: String s{'a', 'b', 'c'};
    String(const String &s);
    String(String &&s);
    String &operator=(String s);

    String &operator+=(const char &c);
    String &operator+=(const String &s);
    bool operator==(const String &s) const;
    bool operator!=(const String &s) const;

    size_t find(const String &subs) const; // search the first occurrence of the subs
    size_t rfind(const String &subs) const; // search the last occurrence of the subs
    String substr(const size_t &start, const size_t &count) const; // returns substring starting from start and length count

    void push_back(const char &c); // adds symbol to the end
    void pop_back(); // removes symbol from the end

    bool empty() const; // checks if string is empty
    void clear(); // clears the string
    size_t length() const;

    char &operator[](size_t index); // access to i-th symbol by reference
    const char &operator[](size_t index) const; // const access to i-th symbol
    char front() const; // returns first symbol in string
    char &front();
    char back() const; // returns last symbol in string
    char &back();

    ~String();

private:
    void swap(String &s); // for the assignment operator
};


String operator+ (const String& a, const String& b);

std::ostream& operator<< (std::ostream& out, const String& s);

std::istream& operator>>(std::istream& in, String& s);
