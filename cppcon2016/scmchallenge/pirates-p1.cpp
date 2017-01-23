//
// Created by Ranga on 9/18/16.
//

/*

C++ Pirates have roamed the seas for a long time. They have hidden treasures in many a secret cove. The following code is one such cove. In this code, C++ Pirates think they have found a way to control access to the key to the next level, by requiring users to first obtain an instance of secret_cove::hidden_password which is hidden, private, within secret_cove. The expected way to obtain a hidden_password instance is through the secret_cove::accept() member function, which will call back a K object and pass it a secret_cove::hidden_password instance.

The C++ Pirates see this as a way to force users to use such objects as a legal_key, which can use a hidden_password but cannot really keep it in a meaningful manner. Your task is to be a C++ Pirate trying to access secret_cove::key_to_next_level() without first passing through secret_cove::accept(). Secret C++ Pirate Coves are very much "old school" and work in C++03.

Your trick has to be named skeleton_key, as the skeleton_key is the key to open all coffers. Once you have found the skeleton_key, the next challenge will be revealed.

*/

#include <string>
#include <iostream>

using namespace std;

class secret_cove {
    class hidden_password {

    };

public:
    template<typename K>
    string accept(K k) {
        return k(*this, hidden_password());
    }

    string key_to_next_level(hidden_password) const {
        return "sesame!";
    }
};

struct legal_key {
    template<typename PWD>
    string operator()(const secret_cove &s, PWD pwd) {
        return s.key_to_next_level(pwd);
    }
};

// ===============================================
class my_secret_cove : public secret_cove {
public:
    string key_to_next_level( string param ) {
        return param;
    }
};

string skeleton_key() {
    return "sesame!";
}

#define secret_cove my_secret_cove
// ===============================================

int main() {
    secret_cove hideout;
    cout << hideout.accept(legal_key()) << endl;
    cout << hideout.key_to_next_level(skeleton_key()) << endl;
    return 0;
}