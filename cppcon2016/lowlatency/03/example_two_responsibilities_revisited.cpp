#include <string>
#include <algorithm>
#include <memory>

using namespace std;

class TwoResponsibilities {
    unique_ptr<string> p, q;

    unique_ptr<string> duplicate_p() const {
        return unique_ptr<string>{!p ? nullptr : new string{*p}};
    }

    unique_ptr<string> duplicate_q() const {
        return unique_ptr<string>{!q ? nullptr : new string{*q}};
    }

    string p_value() const {
        return p ? *p : string{};
    }

    string q_value() const {
        return q ? *q : string{};
    }

public:
    bool empty() const noexcept {
        return !p && !q;
    }

    string value() const {
        return p_value() + " : " + q_value();
    }

    constexpr TwoResponsibilities() : p{}, q{} {
    }

    TwoResponsibilities(const string &s0, const string &s1) : p{new string{s0}} {
        q = unique_ptr<string>{new string{s1}};
    }

    TwoResponsibilities(const char *s0, const char *s1) : p{s0 ? new string{s0} : nullptr} {
        q = unique_ptr<string>{s1 ? new string{s1} : nullptr};
    }

    TwoResponsibilities(const TwoResponsibilities &other) : p{other.duplicate_p()} {
        q = other.duplicate_q();
    }

    TwoResponsibilities(TwoResponsibilities &&other) : p{std::move(other.p)}, q{std::move(other.q)} {
    }

    void swap(TwoResponsibilities &other) {
        using std::swap;
        swap(p, other.p);
        swap(q, other.q);
    }

    TwoResponsibilities &operator=(const TwoResponsibilities &other) {
        TwoResponsibilities{other}.swap(*this);
        return *this;
    }

    TwoResponsibilities &operator=(TwoResponsibilities &&other) {
        swap(other);
        return *this;
    }

    ~TwoResponsibilities() = default;
};

#include <iostream>

int main() {
    TwoResponsibilities obj{"I love", "my teacher"};
    cout << obj.value() << endl;
}