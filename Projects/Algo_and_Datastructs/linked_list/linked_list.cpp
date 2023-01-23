//
// Created by Therkelsen on 18-01-2023.
//

#include <string>
#include "linked_list.h"

int Node::repr() const {
    // read evaluate print
    return _data;
}

bool LinkedList::isEmpty() const {
    return _head == nullptr;
}

int LinkedList::size() {
    // returns the number of nodes in the list
    // takes linear time
    Node* curr = _head;
    int count(0);
    while(curr != nullptr) {
        count++;
        curr = curr->_next_node;
    }
    return count;
}

void LinkedList::add(int data) {
    // Adds new node containing data at head of list
    // takes O(1) time
    Node* N1 = new Node(data);
    N1->_next_node = _head;
    _head = N1;
}

Node* LinkedList::search(int key) const {
    // linear search for the first node containing data that matches the key
    // returns a pointer to the node if found, or a nullptr if not found
    // takes O(n) time
    Node* curr = _head;
    while(curr != nullptr) {
        if(curr->_data == key) {
            return curr;
        } else {
            curr = curr->_next_node;
        }
    }
    return nullptr;
}

void LinkedList::insert(int data, int position) {

}

std::string LinkedList::repr() const {
    // returns a string representation of the list
    // takes O(n) time
    std::string nodes = "\n";
    Node* curr = _head;
    while(curr != nullptr){
        if(curr == _head)
            nodes.append("[Head: " + std::to_string(curr->_data) + "] -> ");
        else if(curr->_next_node == nullptr)
            nodes.append("[Tail: " + std::to_string(curr->_data) + "]");
        else
            nodes.append("[" + std::to_string(curr->_data) + "] -> ");
        curr = curr->_next_node;
    }
    return nodes;
}