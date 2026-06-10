#include "LinkedList.h"

template<class T>
LinkedList<T>::LinkedList(T value) {
    this->root = new Node<T>(value);
}

template<class T>
T LinkedList<T>::get() {
    return this->root;
}

template<class T>
T LinkedList<T>::get(int idx) {
    int i = 0;
    Node<T> *curr = this->root;
    while (i != idx && curr != nullptr) {
        curr = curr->next;
        i++;
    }
    return i == idx ? curr : nullptr;
}
