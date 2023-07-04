#include "String.hpp"

String::String() {
    str[0] = '\0';
}

String::String(const char *s) {
    for (; s[sz] != '\0'; ++sz) {} // strlen(s)
    capacity = 2 * sz;
    this->str = new char[capacity];
    std::copy(s, s + sz, str);
}

String::String(size_t sz, char c) {
    this->sz = sz;
    capacity = 2 * sz;
    str = new char[capacity];
    memset(str, c, sz);
}

String::String(std::initializer_list<char> lst) {
    sz = lst.size();
    capacity = 2 * sz;
    str = new char[capacity];
    std::copy(lst.begin(), lst.end(), str);
}

String::String(const String &s) {
    sz = s.sz;
    capacity = 2 * sz;
    str = new char[capacity];
    std::copy(s.str, s.str + s.sz, str);
}

String::String(String &&s) {
    this->sz = s.sz;
    capacity = 2 * sz;
    this->str = s.str;
    s.str = nullptr;
}

String &String::operator=(String s) {
    swap(s);
    return *this;
}

String &String::operator+=(const char &c) {
    push_back(c);
    return *this;
}

String &String::operator+=(const String &s) {
    if (s.sz + sz > capacity) {
        capacity = 2 * (sz + s.sz);
        char *copy = str;
        str = new char[capacity];
        std::copy(copy, copy + sz, str);
        std::copy(s.str, s.str + s.sz, str + sz);
        delete[] copy;
    } else {
        std::copy(s.str, s.str + s.sz, str + sz);
    }
    sz = sz + s.sz;
    return *this;
}

bool String::operator==(const String &s) const {
    if (s.sz != this->sz) return false;
    for (size_t i = 0; i < s.sz; ++i) {
        if (this->str[i] != s.str[i]) {
            return false;
        }
    }
    return true;
}

bool String::operator!=(const String &s) const {
    return !(operator==(s));
}

char &String::operator[](size_t index) {
    return str[index];
}

const char &String::operator[](size_t index) const {
    return str[index];
}

size_t String::find(const String &subs) const {
    for (size_t i = 0; i < sz; ++i) {
        if (str[i] == subs[0]) {
            bool mark = true;
            size_t k = i + 1;
            for (size_t j = 1; j < subs.sz; ++j, ++k) {
                if (str[k] != subs[j]) {
                    mark = false;
                    break;
                }
            }
            if (mark) {
                return i;
            }
        }
    }
    return -1;
}

size_t String::rfind(const String &subs) const {
    for (size_t i = sz; i > 0; --i) {
        if (str[i - 1] == subs[0]) {
            bool mark = true;
            int k = (int) i;
            for (int j = 1; j < (int) subs.sz; ++j, ++k) {
                if (str[k] != subs[j]) {
                    mark = false;
                    break;
                }
            }
            if (mark) {
                return i - 1;
            }
        }
    }
    return -1;
}

String String::substr(const size_t &start, const size_t &count) const {
    String newStr(count);
    std::copy(str + start, str + start + count, newStr.str);
    return newStr;
}

size_t String::length() const {
    return sz;
}

void String::push_back(const char &c) {
    if (2 * sz >= capacity) {
        capacity *= 2;
        char *copy = str;
        str = new char[capacity];
        std::copy(copy, copy + sz, str);
        delete[] copy;
    }
    if (str == nullptr) str = new char[capacity];
    str[sz] = c;
    sz++;
} // adds symbol to the end

void String::pop_back() {
    if (4 * sz <= capacity) {
        capacity /= 2;
        char *copy = str;
        str = new char[capacity];
        std::copy(copy, copy + sz, str);
        delete[] copy;
    }
    sz--;
    str[sz] = '\0';
} // removes symbol from the end

bool String::empty() const {
    return (sz == 0);
} // checks if string is empty

void String::clear() {
    sz = 0;
} // clears the string

char String::front() const {
    return *str;
} // returns first symbol in string

char &String::front() {
    return *str;
}

char String::back() const {
    return str[sz - 1];
} // returns last symbol in string

char &String::back() {
    return str[sz - 1];
}

String::~String() {
    delete[] str;
}

void String::swap(String &s) {
    std::swap(capacity, s.capacity);
    std::swap(sz, s.sz);
    std::swap(str, s.str);
}

String operator+(const String &a, const String &b) {
    String copy = a;
    copy += b;
    return copy;
}

std::ostream &operator<<(std::ostream &out, const String &s) {
    for (size_t i = 0; i < s.length(); ++i) {
        out << s[i];
    }
    return out;
}

std::istream &operator>>(std::istream &in, String &s) {
    char c;
    s.clear();
    in.get(c);
    while (c != '\n' && c != ' ' && c != '\0' && c != '\t' && c != '\r') {
        s.push_back(c);
        if (!in.get(c))
            return in;
    }
    return in;
}
