#ifndef INC_2DGAMEENGINE_LINKEDLIST_H
#define INC_2DGAMEENGINE_LINKEDLIST_H

template<class T>
struct Node {
    T value;
    Node *next;

    explicit Node(T value) {
        this->value = value;
        this->next = nullptr;
    }
};

template<class T>
class LinkedList {
    Node<T> root;

    LinkedList(T value);
    ~LinkedList() = default;

    T get();
    T get(int idx);
};


#endif
