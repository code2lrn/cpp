#include <string>
#include <algorithm>
using namespace std;
class TwoResponsibilities {
    string *p, *q;
    string* duplicate_p() const {
        return !p ? nullptr : new string {*p};
    }
    string* duplicate_q() const {
        return !q ? nullptr : new string {*q};
    }
    string p_value() const {
        return p? *p : string{};
    }
    string q_value() const {
        return q? *q : string{};
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
    TwoResponsibilities(const string &s0, const string &s1) : p { new string { s0 } } {
        try {
            q = new string { s1 };
        } catch (...) {
            delete p;
            throw;
        }
    }
    TwoResponsibilities(const char *s0, const char *s1) : p { s0? new string { s0 } : nullptr } {
        try {
            q = s1? new string { s1 } : nullptr;
        } catch (...) {
            delete p;
            throw;
        }
    }
    TwoResponsibilities(const TwoResponsibilities &other) : p{ other.duplicate_p() } {
        try {
            q = other.duplicate_q();
        } catch (...) {
            delete p;
            throw;
        }
    }
    TwoResponsibilities(TwoResponsibilities &&other) : p{ other.p }, q{ other.q } {
        other.p = nullptr;
        other.q = nullptr;
    }
    void swap(TwoResponsibilities &other) {
        using std::swap;
        swap(p, other.p);
        swap(q, other.q);
    }
    TwoResponsibilities& operator=(const TwoResponsibilities &other) {
        TwoResponsibilities{ other }.swap(*this);
        return *this;
    }
    TwoResponsibilities& operator=(TwoResponsibilities &&other) {
        swap(other);
        return *this;
    }
    ~TwoResponsibilities() {
        delete q;
        delete p;
    }
};
#include <iostream>
int main() {
    TwoResponsibilities obj{ "I love", "my teacher" };
    cout << obj.value() << endl;
}