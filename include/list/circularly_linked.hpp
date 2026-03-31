#pragma once

#include <utility>     // provides std::swap
#include <stdexcept>

namespace dsac::list {

    /// circularly linked list
    template <typename T>
    class CircularlyLinkedList {
    private:
        class Node {
        public:
            T elem;
            Node* next;
            // ToDo
            Node(const T& element, Node* nxt = nullptr)
                : elem(element), next(nxt) {}
        };
    private:
        int sz{ 0 };
        Node* tail{ nullptr };
    public:
        // ToDo
        CircularlyLinkedList() = default;

        int size() const {
            return sz;
        }

        bool empty() const {
            return sz == 0;
        }

        T& front() {
            if (empty()) throw std::out_of_range("List is empty");
            return tail->next->elem;
        }

        const T& front() const {
            if (empty()) throw std::out_of_range("List is empty");
            return tail->next->elem;
        }

        T& back() {
            if (empty()) throw std::out_of_range("List is empty");
            return tail->elem;
        }

        const T& back() const {
            if (empty()) throw std::out_of_range("List is empty");
            return tail->elem;
        }

        void push_front(const T& elem) {
            Node* newest = new Node(elem);

            if (empty()) {
                newest->next = newest;
                tail = newest;
            }
            else {
                newest->next = tail->next;
                tail->next = newest;
            }
            ++sz;
        }

        void push_back(const T& elem) {
            push_front(elem);
            tail = tail->next;
        }

        void pop_front() {
            if (empty()) throw std::out_of_range("List is empty");

            Node* oldHead = tail->next;

            if (sz == 1) {
                delete oldHead;
                tail = nullptr;
                sz = 0;
                return;
            }

            tail->next = oldHead->next;
            delete oldHead;
            --sz;
        }

        void rotate() {
            if (!empty()) {
                tail = tail->next;
            }
        }

        void splitEven(CircularlyLinkedList& A, CircularlyLinkedList& B) {
            A.clear();
            B.clear();

            if (empty()) {
                return;
            }

            if (sz % 2 != 0) {
                throw std::logic_error("splitEven requires even-sized list");
            }

            Node* firstHead = tail->next;

            int half = sz / 2;
            Node* firstTail = firstHead;
            for (int i = 1; i < half; ++i) {
                firstTail = firstTail->next;
            }

            Node* secondHead = firstTail->next;

            Node* secondTail = tail;

            firstTail->next = firstHead;
            secondTail->next = secondHead;

            A.tail = firstTail;
            A.sz = half;

            B.tail = secondTail;
            B.sz = half;

            tail = nullptr;
            sz = 0;
        }

    private:
        void clone(const CircularlyLinkedList& other) {
            if (other.empty()) return;

            Node* walk = other.tail->next;
            for (int i = 0; i < other.sz; ++i) {
                push_back(walk->elem);
                walk = walk->next;
            }
        }

    public:
        friend void swap(CircularlyLinkedList& a, CircularlyLinkedList& b) {
            using std::swap;
            swap(a.sz, b.sz);
            swap(a.tail, b.tail);
        }

        void clear() {
            while (!empty()) {
                pop_front();
            }
        }

        CircularlyLinkedList(const CircularlyLinkedList& other) {
            clone(other);
        }

        CircularlyLinkedList& operator=(const CircularlyLinkedList& other) {
            if (this != &other) {
                CircularlyLinkedList temp(other);
                swap(*this, temp);
            }
            return *this;
        }

        CircularlyLinkedList(CircularlyLinkedList&& other) {
            sz = other.sz;
            tail = other.tail;

            other.sz = 0;
            other.tail = nullptr;
        }

        CircularlyLinkedList& operator=(CircularlyLinkedList&& other) {
            if (this != &other) {
                clear();
                sz = other.sz;
                tail = other.tail;

                other.sz = 0;
                other.tail = nullptr;
            }
            return *this;
        }

        ~CircularlyLinkedList() {
            clear();
        }

        void print() {
            if (empty()) return;
            Node* walk = tail->next;
            for (int i = 0; i < sz; ++i) {
                std::cout << walk->elem << " ";
                walk = walk->next;
            }
            std::cout << "\n";
        }
    };

}  // namespace dsac::list