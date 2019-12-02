//
// Created by Sereg on 17.10.2019.
//

#ifndef LABEX_LINKEDLIST_H
#define LABEX_LINKEDLIST_H
#pragma once

#include "MyList.h"
#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>

template <typename E>
struct node {
    node<E> *next;
    E value;
    node(E v) : value(v), next(NULL) {
    }
};

template <typename E>
class MyLinkedList: public MyList<E> {
private:
    node<E> *head, *tail;

    void updateTail() {
        node<E> *r = head;
        if (r) while (r->next != NULL) r = r->next;
        tail = r;
    }

    node<E> *partition(node<E> *lo, node<E> *hi) {
        E pivot = hi->value;
        node<E> *prev = NULL;
        for (node<E> *t = lo; t != hi; t = t->next) {
            if (MyList<E>::cmp(t->value, pivot) < 0) {
                std::swap(lo->value, t->value);
                prev = lo;
                lo = lo->next;
            }
        }
        std::swap(lo->value, hi->value);
        return prev;
    }

    void quickSort(node<E> *lo, node<E> *hi) {
        if (!lo || !hi || lo == hi) return;
        node<E> *p = partition(lo, hi);
        quickSort(lo, p);
        if (p == NULL) {
            quickSort(lo->next, hi);
        } else if (p->next != hi) {
            quickSort(p->next->next, hi);
        }
    }

    void split(node<E> *src, node<E> **pFront, node<E> **pBack) {
        node<E> *fast = src->next;
        node<E> *slow = src;

        while (fast != NULL) {
            fast = fast->next;
            if (fast != NULL) {
                fast = fast->next;
                slow = slow->next;
            }
        }

        *pFront = src;
        *pBack = slow->next;
        slow->next = NULL;
    }

    node<E> *sortedMerge(node<E> *a, node<E> *b) {
        node<E> *ret = NULL;

        if (a == NULL) {
            return b;
        } else if (b == NULL) {
            return a;
        }

        if (MyList<E>::cmp(a->value, b->value) <= 0) {
            ret = a;
            ret->next = sortedMerge(a->next, b);
        } else {
            ret = b;
            ret->next = sortedMerge(a, b->next);
        }

        return ret;
    }

    void mergeSort(node<E> **pHead) {
        node<E> *h = *pHead;
        if (h == NULL || h->next == NULL) {
            return;
        }

        node<E> *a, *b;
        split(h, &a, &b);

        mergeSort(&a);
        mergeSort(&b);
        *pHead = sortedMerge(a, b);
    }

    void sortedInsert(node<E> **pHead, node<E> *t) {
        node<E> *h = *pHead;

        if (h == NULL || MyList<E>::cmp(h->value, t->value) >= 0) {
            t->next = h;
            *pHead = t;
            return;
        }

        node<E> *cur = h;
        while (cur->next != NULL && MyList<E>::cmp(cur->next->value, t->value) < 0) {
            cur = cur->next;
        }

        t->next = cur->next;
        cur->next = t;
    }

    void insertionSort(node<E> **pHead) {
        node<E> *sorted = NULL;

        node<E> *cur = *pHead;
        while (cur != NULL) {
            node<E> *t = cur->next;
            sortedInsert(&sorted, cur);
            cur = t;
        }

        *pHead = sorted;
    }

public:
    MyLinkedList() : MyList<E>() {
        head = tail = NULL;
    }

    void add(E element) {
        node<E> *n = new node<E>(element);
        if (head == NULL) {
            head = tail = n;
            return;
        }
        tail->next = n;
        tail = n;
    }

    void addFront(E element) {
        node<E> *n = new node<E>(element);
        if (head == NULL) {
            head = tail = n;
            return;
        }
        n->next = head;
        head = n;
    }

    virtual E get(int index) {
        int i = 0;
        for (node<E> *t = head; t != NULL; t = t->next) {
            if (i++ == index) {
                return t->value;
            }
        }

        throw std::out_of_range("index");
    }

    E remove(int index) {
        if (head == NULL) {
            throw std::out_of_range("index");
        }

        if (index == 0) {
            node<E> *t = head;
            head = head->next;
            E ret = t->value;
            delete t;
            if (head == NULL) {
                tail = NULL;
            }
            return ret;
        }

        node<E> *prev = head;
        int i = 1;
        for (node<E> *t = prev->next; t != NULL; t = t->next) {
            if (i++ == index) {
                prev->next = t->next;
                E ret = t->value;
                delete t;
                if (prev->next == NULL) {
                    tail = prev;
                }
                return ret;
            }
            prev = t;
        }

        throw std::out_of_range("index");
    }

    size_t getSize() {
        size_t ret = 0;
        for (node<E> *t = head; t != NULL; t = t->next) {
            ret++;
        }
        return ret;
    }

    int indexOf(E element) {
        int i = 0;
        for (node<E> *t = head; t != NULL; t = t->next) {
            if (t->value == element) {
                return i;
            }
            i++;
        }
        return -1;
    }

    std::string toString() {
        std::stringstream ret;
        ret << "[";
        for (node<E> *t = head; t != NULL; t = t->next) {
            ret << t->value;
            if (t->next != NULL) {
                ret << ", ";
            }
        }
        ret << "]";
        return ret.str();
    }

    void forEach(void (*b)(E)) {
        for (node<E> *t = head->next; t != NULL; t = t->next) {
            b(t->value);
        }
    }

    void insertionSort() {
        insertionSort(&head);
        updateTail();
    }

    void quickSort() {
        quickSort(head, tail);
    }

    void mergeSort() {
        mergeSort(&head);
        updateTail();
    }
};

#endif //LABEX_LINKEDLIST_H
