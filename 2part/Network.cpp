//
// Created by Sereg on 26.11.2019.
//
#include "Network.h"

Network::Network(const string& cidr) : addr(Address(cidr.substr(0, cidr.find('/')))) {
    stringstream s;
    s << cidr.substr(cidr.find('/') + 1);
    s >> mask;
}

bool Network::test(const Address& bddr) {
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