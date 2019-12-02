#include <iostream>
#include <cstdlib>
#include <ctime>

#include "MyList.h"
#include "LinkedList.h"
#include "MyArrayList.h"
#include "MyStdVectorList.h"


using namespace std;

int main() {
    cout << "hello world" << endl;

    srand(time(NULL));

    MyList<int> *myList;
    myList = new MyLinkedList<int>();

    myList->fill(15, [] { return 10 + rand() % 90; });
    cout << myList->toString() << endl;

    myList->insertionSort();

    cout << "sorted:" << endl;
    cout << myList->toString() << endl;

    cout << endl;

    MyList<string> *myStringList;
    myStringList = new MyArrayList<string>();

    myStringList->add("abcd");
    myStringList->add("qwerty");
    myStringList->add("xyz");
    myStringList->add("rtyuiodfghjk");
    myStringList->add("tgbyh");

    myStringList->setComparator([](string a, string b) {
        return (int) (a.length() - b.length());
    });

    cout << myStringList->toString() << endl;

    myStringList->quickSort();

    cout << "sorted:" << endl;
    cout << myStringList->toString() << endl;

    cout << endl;

    MyList<double> *myDoubleList;
    myDoubleList = new MyArrayList<double>();

    myDoubleList->fill(10, [] { return (2 + rand() % 10) * 5.1; });

    cout << myDoubleList->toString() << endl;

    myDoubleList->mergeSort();

    cout << "sorted:" << endl;
    cout << myDoubleList->toString() << endl;

    return 0;
}
