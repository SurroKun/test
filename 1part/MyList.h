//
// Created by Sereg on 17.10.2019.
//

#ifndef LABEX_MYLIST_H
#define LABEX_MYLIST_H
#pragma once

#include <string>
#include <cstdlib>

template <typename E>
class MyList {
protected:
    int (*cmp)(E, E);

public:
    MyList() {
        this->cmp = [](E a, E b) { return a < b ? -1 : (a > b ? 1 : 0); };
    }

    virtual void add(E element)     = 0;
    virtual E get(int index)        = 0;
    virtual E remove(int index)     = 0;
    virtual size_t getSize()        = 0;
    virtual int indexOf(E element)  = 0;
    virtual std::string toString()  = 0;

    virtual void insertionSort()    = 0;
    virtual void quickSort()        = 0;
    virtual void mergeSort()        = 0;

    virtual void forEach(void (*b)(E)) = 0;

    void fill(int n, E (*g)()) {
        for (int i = 0; i < n; i++) {
            this->add(g());
        }
    }

    void setComparator(int (*c)(E, E)) {
        this->cmp = c;
    }
};

#endif //LABEX_MYLIST_H
