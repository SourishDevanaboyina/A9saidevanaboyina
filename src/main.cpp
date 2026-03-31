// src/main.cpp
#include <iostream>

#include "list/singly_linked.hpp"
#include "list/circularly_linked.hpp"
#include "list/doubly_linked.hpp"

int main() {
    // Create Two Singly Linked Lists
    dsac::list::SinglyLinkedList<int> SL, SM;

    // Add elements
    SL.push_back(1); SL.push_back(2);
    SL.push_back(3); SL.push_back(4);

    SM.push_back(5); SM.push_back(6);
    SM.push_back(7); SM.push_back(8);

    // Use range-based for to display
    // works using begin and end
    std::cout << "SL: ";
    for (int x : SL) 
        std::cout << x << ' ';
    std::cout << "\nSM: ";
    for (int x : SM) 
        std::cout << x << ' ';

    //attach the contents of list M to end of the current list and clears list M
    // No nodes are copied or allocated; only pointer links are adjusted.
    SL.concatenate(SM);

    // Use range-based for to display after concatenate
    // works using begin and end
    std::cout << "\nSL: ";
    for (int x : SL) 
        std::cout << x << ' ';
    std::cout << "\nSM: ";
    for (int x : SM) 
        std::cout << x << ' ';

    // Reverses the linked list in place
    SL.reverse();
    std::cout << "\nSL: ";
    for (int x : SL) 
    std::cout << x << ' ';

    std::cout << "\n";

    // Create Doubly Linked List
    dsac::list::DoublyLinkedList<int> DL;
    dsac::list::DoublyLinkedList<int> DM;

    // Add elements to the lists
    DL.push_back(1);
    DL.push_back(2);
    DL.push_back(3);

    DM.push_back(4);
    DM.push_back(5);
    DM.push_back(6);

    // Use range-based for to display
    // works using begin and end
    std::cout << "\nDL: ";
    for (int x : DL) 
        std::cout << x << " ";

    std::cout << "\nDM: ";
    for (int x : DM) 
        std::cout << x << " ";

    // Concatenates all nodes from list M to the end of the current list
    // After the operation, M becomes an empty list
    // No nodes are copied or allocated; only pointer links are adjusted.
    // Does nothing if M is empty or if this and M are the same list.
    DL.concatenate(DM);

    std::cout << "\nDL: ";
    for (int x : DL) 
        std::cout << x << " ";

    std::cout << "\nDM: ";
    for (int x : DM) 
        std::cout << x << " ";


    std::cout << "\n";

    // Create three Circularly Linked List
    dsac::list::CircularlyLinkedList<int> L, A, B;
    // Add elements to the list
    for (int i{1}; i<=6; i++) 
        L.push_back(i);

    // Splits the current even-sized circular list into two equal-sized circular lists A and B
    // After splitting, A and B become the two halves (preserving original order), and the original list becomes empty. 
    //If the size is odd, throw std::logic_error
    L.splitEven(A, B);

    // use front as we have no begin/end
    std::cout << "A: ";
    for (int i{0}; i < A.size(); i++) {
        std::cout << A.front() << " ";
        A.rotate();
    }
    std::cout << "\n";

    std::cout << "B: ";
    for (int i{0}; i < B.size(); i++) {
        std::cout << B.front() << " ";
        B.rotate();
    }
    std::cout << "\n";

    return 0;
}

/*
SL: 1 2 3 4 
SM: 5 6 7 8 
SL: 1 2 3 4 5 6 7 8 
SM: 
SL: 8 7 6 5 4 3 2 1 

DL: 1 2 3 
DM: 4 5 6 
DL: 1 2 3 4 5 6 
DM: 
A: 1 2 3 
B: 4 5 6
*/