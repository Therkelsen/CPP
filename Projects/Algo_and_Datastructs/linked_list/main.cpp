#include <iostream>
#include "linked_list.h"


int main() {
    std::cout << std::boolalpha;
    Node N1(10);
    std::cout << "Size of N1: " << N1.repr() << std::endl;
    Node N2(20);
    N1._next_node = &N2;
    std::cout << "Size of N2: " << N2.repr() << std::endl;

    LinkedList L1;
    std::cout << "Is L1 empty?: " << L1.isEmpty() << std::endl;
    std::cout << "Nodes in L1: " << L1.size() << std::endl;
    L1.add(10);
    L1.add(25);
    L1.add(13);
    std::cout << "Is L1 empty?: " << L1.isEmpty() << std::endl;
    std::cout << "Nodes in L1: " << L1.size() << std::endl;
    std::cout << "L1 repr: " << L1.repr() << std::endl;

    Node N3(L1.search(10));
    std::cout << "Size of N3: " << N3.repr() << std::endl;
    Node N4(L1.search(9999));
    std::cout << "Size of N4: " << N4.repr() << std::endl;
}
