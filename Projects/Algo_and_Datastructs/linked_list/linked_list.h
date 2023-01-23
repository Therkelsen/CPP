//
// Created by Therkelsen on 18-01-2023.
//

#ifndef LINKED_LIST_LINKED_LIST_H
#define LINKED_LIST_LINKED_LIST_H


class Node {
public:
    // data in node
    int _data = 0;
    // next node in list
    Node* _next_node = nullptr;
    // constructor
    explicit Node(int data) {
        _data = data;
    }
    explicit Node(Node* N) {
        if(N != nullptr) {
            _data = N->_data;
            _next_node = N->_next_node;
        }
    }
    // read evaluate print
    int repr() const;
};

class LinkedList {
    // singly linked list
public:
    // head pointer
    Node *_head;

    // constructor
    LinkedList() {
        _head = nullptr;
    };

    bool isEmpty() const;

    int size();

    void add(int data);

    std::string repr() const;

    Node *search(int key) const;
};


#endif //LINKED_LIST_LINKED_LIST_H
