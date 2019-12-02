//
// Created by Sereg on 17.10.2019.
//

#ifndef LABEX_MYSTDVECTORLIST_H
#define LABEX_MYSTDVECTORLIST_H
#pragma once

#include "MyList.h"
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

template <typename E>
class MyStdVectorList: public MyList<E> {
private:
    std::vector<E> arr;

    int partition(int lo, int hi) {
        E pivot = arr[hi];
        for (int j = lo; j < hi; j++) {
            if (MyList<E>::cmp(arr[j], pivot) < 0) {
                std::swap(arr[lo++], arr[j]);
            }
        }
        std::swap(arr[lo], arr[hi]);
        return lo;
    }

    void quickSort(int lo, int hi) {
        if (lo >= hi) return;
        int p = partition(lo, hi);
        quickSort(lo, p - 1);
        quickSort(p + 1, hi);
    }

    void merge(int lt, int m, int rt) {
        int n1 = m - lt + 1;
        int n2 = rt - m;

        E *L = new E[n1];
        E *R = new E[n2];

        for (int i = 0; i < n1; i++) {
            L[i] = arr[lt + i];
        }

        for (int j = 0; j < n2; j++) {
            R[j] = arr[m + j + 1];
        }

        int i = 0, j = 0;
        int k;

        for (k = lt; i < n1 && j < n2; k++) {
            if (MyList<E>::cmp(L[i], R[j]) <= 0) {
                arr[k] = L[i++];
            } else {
                arr[k] = R[j++];
            }
        }

        while (i < n1) {
            arr[k++] = L[i++];
        }

        while (j < n2) {
            arr[k++] = R[j++];
        }
    }

    void mergeSort(int lt, int rt) {
        if (lt >= rt) return;
        int m = lt + (rt - lt) / 2;
        mergeSort(lt, m);
        mergeSort(m + 1, rt);
        merge(lt, m, rt);
    }

public:
    MyStdVectorList() : MyList<E>() {
    }

    void add(E element) {
        arr.push_back(element);
    }

    E get(int index) {
        return arr[index];
    }

    E remove(int index) {
        E ret = arr[index];
        arr.erase(arr.begin() + index);
        return ret;
    }

    size_t getSize() {
        return arr.size();
    }

    int indexOf(E element) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == element) {
                return i;
            }
        }
        return -1;
    }

    std::string toString() {
        std::stringstream ret;
        ret << "[";
        for (int i = 0; i < arr.size(); i++) {
            ret << arr[i];
            if (i != arr.size() - 1) {
                ret << ", ";
            }
        }
        ret << "]";
        return ret.str();
    }

    void forEach(void (*b)(E)) {
        for (int i = 0; i < arr.size(); i++) {
            b(arr[i]);
        }
    }

    void insertionSort() {
        for (int i = 1; i < arr.size(); i++) {
            E key = arr[i];
            int j;
            for (j = i - 1; j >= 0 && MyList<E>::cmp(arr[j], key) > 0; j--) {
                arr[j + 1] = arr[j];
            }
            arr[j + 1] = key;
        }
    }

    void quickSort() {
        quickSort(0, arr.size() - 1);
    }

    void mergeSort() {
        mergeSort(0, arr.size() - 1);
    }
};

#endif //LABEX_MYSTDVECTORLIST_H
