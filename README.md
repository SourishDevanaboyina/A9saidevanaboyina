# A9: Linked Lists

In this assignment, you will complete the implementation of three linked-list data structures:

* singly_linked.hpp
* circularly_linked.hpp
* doubly_linked.hpp

Starter code and implementation guidance are provided inside each header file.

A sample main.cpp is included to demonstrate expected behavior and sample output. You are responsible for testing beyond the provided example, including edge cases and special cases, before submitting.

## Requirements

* Implement all required functions discussed in the three header files above.
* In addition, you must implement the following functions:
* SinglyLinkedList
  * concatenate for SinglyLinkedList
  * reverse for SinglyLinkedList
* CircularlyLinkedList
  * splitEven for CircularlyLinkedList
* DoublyLinkedList
  * concatenate for DoublyLinkedList

## Important constraint

* These functions must be implemented by manipulating pointer links directly.
  * Do not use copy operations.
  * Do not use move operations.
  * Do not create replacement nodes to simulate the result.
* Your implementation should reorganize the existing nodes through pointer updates.

## Testing Expectations

* The provided main.cpp is only an example.
* Before submission, you should test your implementation with a variety of cases, including:
  * empty lists
  * single-node lists
  * lists with two nodes
  * longer lists
  * cases where special operations change the head, tail, or both
  * cases where the result is empty or split into uneven parts, when applicable

## Submission Files

* Submit only these files:
  * Linked List Header Files
    * singly_linked.hpp
    * circularly_linked.hpp
    * doubly_linked.hpp
  * Tests
    * test_linked_list.cpp
      * at least two cases for Singly Linked List, Circular Linked List, Doubly Linked List
* Notes
  * You do not need to submit main.cpp
  * Do not submit build or executable files/folders. Penalty: -2 points
  * Failure to follow the assignment instructions may result in no credit, even if your code passes the autograder test cases.

## Helper Code for Special Function

* Clone this repo and implement the functions

```cpp
//SinglyLinkedList
void concatenate(SinglyLinkedList& M) {
    // self-concatenation: do nothing

    // nothing to add if M is empty

    // current list is empty: adopt M in complete

    // general splice: tail -> M.head, then adopt M.tail

    // reset M to empty state
}

//SinglyLinkedList
// Reverse the singly linked list in-place, using O(1) extra space.
// After this, head and tail are swapped, and all links are reversed.
void reverse() {
    // nothing to do for empty or single-node list
	// Traverse the list and reverse links one by one
}

//CircularlyLinkedList
// Split *this into two circular lists A and B, each with half the nodes.
// Precondition: sz is even. After the call, *this becomes empty and
// A and B each point to one of the two halves.
void splitEven(CircularlyLinkedList& A, CircularlyLinkedList& B) {
    // If the list is empty, both result lists should also be empty

    // splitEven is only valid for even-sized lists else throw exception

    // head is the first node in the circular list

    // Find the last node of the first half

    // The node after firstTail is the head of the second half

    // The original tail becomes the tail of the second half

    // Rewire pointers to form two separate circular lists
    
    // Clear destination lists first
    
    // Assign the two halves

    // Original list becomes empty
}

// DoublyLinkedList
void concatenate(DoublyLinkedList& M) {
    // self-concat not allowed
    
    // nothing to add if M empty
	
    // Case 1: current list (*this) is empty
    
    // Case 2: both lists are non-empty

    // Reset M to empty using its OWN sentinels
}
```



## Rubrics

| Test Case                                                    |      |
| ------------------------------------------------------------ | ---- |
| Autograder Instructor Test Cases                             | 6    |
| Autograder Student Test Cases                                | 2    |
| Manual Grading for test cases (at least two cases for Singly Linked List, Circular Linked List, Doubly Linked List) | 2    |
| Manual Grading to check only pointers rearranged in concatenation, reverse, splitEven. Nodes not moved or copied. (concatenate, reverse, splitEven) | 5    |
| Negative Points for build folder submitted                   | -2   |
