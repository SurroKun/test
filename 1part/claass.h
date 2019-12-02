//
// Created by Sereg on 17.10.2019.
//

#ifndef LABEX_CLAASS_H
#define LABEX_CLAASS_H

#include <iostream>
#include <vector>
#include <sstream>
#include <bitset>

using namespace std;

class Address {
private:
    vector<bool> arr;

public:
    Address(const string& str) {
        char d;
        int n;

        if (str.find('.') != string::npos) {
            d = '.';
            n =  8;
        } else {
            d = ':';
            n = 16;
        }

        for (size_t i = 0, j = str.find(d); true; i = j + 1) {
            j = str.find(d, i);

            string s;
            if (j != string::npos) {
                s = str.substr(i, j - i);
            } else {
                s = str.substr(i);
            }

            stringstream t;
            if (d == ':') t << hex;
            t << s;

            unsigned short c;
            t >> c;

            bitset<16> b(c);
            for (int k = n - 1; k >= 0; k--) {
                arr.push_back(b[k]);
            }

            if (j == string::npos) break;
        }
    }

    vector<bool> bits() const {
        return arr;
    }

    string toString() {
        stringstream ret;
        int n;

        if (arr.size() == 32) {
            n =  8;
        } else {
            n = 16;
            ret << hex;
        }

        for (int i = 0; i < (arr.size() / n); i++) {
            bitset<16> b;
            for (int j = n - 1; j >= 0; j--) {
                b[j] = arr[i * n + (n - j - 1)];
            }
            ret << b.to_ulong();
            if (i < (arr.size() / n) - 1) {
                ret << (arr.size() == 32 ? '.' : ':');
            }
        }

        return ret.str();
    }
};

class Network {
private:
    Address addr;
    int mask;

public:
    Network(const string& cidr) : addr(Address(cidr.substr(0, cidr.find('/')))) {
        stringstream s;
        s << cidr.substr(cidr.find('/') + 1);
        s >> mask;
    }

    bool test(const Address& bddr) {
        vector<bool> a = addr.bits();
        vector<bool> b = bddr.bits();

        if (a.size() != b.size()) return false;

        for (int i = 0; i < mask; i++) {
            if (a[i] != b[i]) {
                return false;
            }
        }

        return true;
    }
};

int main() {
    cout << "hello world" << endl;

    cout << "192.168.5.1   in 192.168.5.85/24 = ";
    cout << Network("192.168.5.85/24").test(Address("192.168.5.1"  ));
    cout << endl;
    cout << "192.168.5.254 in 192.168.5.85/24 = ";
    cout << Network("192.168.5.85/24").test(Address("192.168.5.254"));
    cout << endl;
    cout << "192.168.4.254 in 192.168.5.85/24 = ";
    cout << Network("192.168.5.85/24").test(Address("192.168.4.254"));
    cout << endl;
    cout << "191.168.5.254 in 192.168.5.85/24 = ";
    cout << Network("192.168.5.85/24").test(Address("191.168.5.254"));
    cout << endl;

    cout << endl;

    cout << "2001:0db8:abcd:0012:0000:0000:0000:0000 in 2001:db8:abcd:12:0:0:0:0/64 = ";
    cout << Network("2001:db8:abcd:12:0:0:0:0/64").test(Address("2001:0db8:abcd:0012:0000:0000:0000:0000"));
    cout << endl;
    cout << "2001:0db8:abcd:0012:ffff:ffff:ffff:ffff in 2001:db8:abcd:12:0:0:0:0/64 = ";
    cout << Network("2001:db8:abcd:12:0:0:0:0/64").test(Address("2001:0db8:abcd:0012:ffff:ffff:ffff:ffff"));
    cout << endl;
    cout << "2001:0db8:abcd:0011:ffff:ffff:ffff:ffff in 2001:db8:abcd:12:0:0:0:0/64 = ";
    cout << Network("2001:db8:abcd:12:0:0:0:0/64").test(Address("2001:0db8:abcd:0011:ffff:ffff:ffff:ffff"));
    cout << endl;
    cout << "2001:0db8:abcd:0013:0000:0000:0000:0000 in 2001:db8:abcd:12:0:0:0:0/64 = ";
    cout << Network("2001:db8:abcd:12:0:0:0:0/64").test(Address("2001:0db8:abcd:0013:0000:0000:0000:0000"));
    cout << endl;

    return 0;
}


#endif //LABEX_CLAASS_H
