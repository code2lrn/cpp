#include <string>
#include <algorithm>
#include <memory>

using namespace std;

class OneResponsibility {
    unique_ptr<string> p;

    unique_ptr<string> duplicate() const {
        return unique_ptr<string>{empty() ? nullptr : new string{*p}};
    }

public:
    bool empty() const noexcept {
        return !static_cast<bool>(p);
    }

    string value() const {
        return empty() ? string{} : *p;
    }

    constexpr OneResponsibility() : p{} {
    }

    OneResponsibility(const string &s) : p{new string{s}} {
    }

    OneResponsibility(const char *s) : p{s ? new string{s} : nullptr} {
    }

    OneResponsibility(const OneResponsibility &other) : p{other.duplicate()} {
    }

    OneResponsibility(OneResponsibility &&other) : p{std::move(other.p)} {
    }

    void swap(OneResponsibility &other) {
        using std::swap;
        swap(p, other.p);
    }

    OneResponsibility &operator=(const OneResponsibility &other) {
        OneResponsibility{other}.swap(*this);
        return *this;
    }

    OneResponsibility &operator=(OneResponsibility &&other) {
        swap(other);
        return *this;
    }

    ~OneResponsibility() = default;
};

#include <iostream>

int main() {
    OneResponsibility obj{"I love my teacher"};
    cout << obj.value() << endl;
}