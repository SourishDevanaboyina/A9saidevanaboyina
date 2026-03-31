#pragma once

#include <utility>     // provides std::swap
#include <stdexcept>
#include <iostream>

namespace dsac::list {
    //akin to std::list
    template <typename T>
    class DoublyLinkedList {
    private:
        class Node {
        public:
            T elem;
            Node* prev{ nullptr };
            Node* next{ nullptr };

            // ToDo
            Node()
                : elem(), prev(nullptr), next(nullptr) {}

            Node(const T& element, Node* prv, Node* nxt)
                : elem(element), prev(prv), next(nxt) {}
        };

        int sz{ 0 };
        Node* header; // sentinel node
        Node* trailer;// sentinel node

        void create_sentinels() {
            header = new Node();
            trailer = new Node();
            header->next = trailer;
            trailer->prev = header;
        }

    public:
        // ToDo
        DoublyLinkedList() {
            create_sentinels();
        }

        int size() const {
            return sz;
        }

        bool empty() const {
            return sz == 0;
        }

        T& front() {
            if (empty()) throw std::out_of_range("List is empty");
            return header->next->elem;
        }

        const T& front() const {
            if (empty()) throw std::out_of_range("List is empty");
            return header->next->elem;
        }

        T& back() {
            if (empty()) throw std::out_of_range("List is empty");
            return trailer->prev->elem;
        }

        const T& back() const {
            if (empty()) throw std::out_of_range("List is empty");
            return trailer->prev->elem;
        }

    private:
        Node* insert_before(T elem, Node* successor) {
            Node* predecessor = successor->prev;
            Node* newest = new Node(elem, predecessor, successor);
            predecessor->next = newest;
            successor->prev = newest;
            ++sz;
            return newest;
        }

        void erase(Node* node) {
            Node* predecessor = node->prev;
            Node* successor = node->next;
            predecessor->next = successor;
            successor->prev = predecessor;
            delete node;
            --sz;
        }

    public:
        void push_front(const T& elem) {
            insert_before(elem, header->next);
        }

        void push_back(const T& elem) {
            insert_before(elem, trailer);
        }

        void pop_front() {
            if (empty()) throw std::out_of_range("List is empty");
            erase(header->next);
        }

        void pop_back() {
            if (empty()) throw std::out_of_range("List is empty");
            erase(trailer->prev);
        }

        void concatenate(DoublyLinkedList& M) {
            if (this == &M) return;

            if (M.empty()) return;

            if (empty()) {
                header->next = M.header->next;
                trailer->prev = M.trailer->prev;

                M.header->next->prev = header;
                M.trailer->prev->next = trailer;

                sz = M.sz;
            }
            else {
                Node* thisLast = trailer->prev;
                Node* mFirst = M.header->next;
                Node* mLast = M.trailer->prev;

                thisLast->next = mFirst;
                mFirst->prev = thisLast;

                mLast->next = trailer;
                trailer->prev = mLast;

                sz += M.sz;
            }

            M.header->next = M.trailer;
            M.trailer->prev = M.header;
            M.sz = 0;
        }

    public:
        class iterator {
            friend class DoublyLinkedList;
        private:
            Node* node_ptr;
        public:
            iterator(Node* ptr = nullptr)
                : node_ptr(ptr) {}

            T& operator*() const {
                return node_ptr->elem;
            }

            T* operator->() const {
                return &(node_ptr->elem);
            }

            iterator& operator++() {
                node_ptr = node_ptr->next;
                return *this;
            }

            iterator operator++(int) {
                iterator temp(*this);
                ++(*this);
                return temp;
            }

            iterator& operator--() {
                node_ptr = node_ptr->prev;
                return *this;
            }

            iterator operator--(int) {
                iterator temp(*this);
                --(*this);
                return temp;
            }

            bool operator==(const iterator& other) const {
                return node_ptr == other.node_ptr;
            }

            bool operator!=(const iterator& other) const {
                return node_ptr != other.node_ptr;
            }
        };

        class const_iterator {
        private:
            const Node* node_ptr;
        public:
            const_iterator(const Node* ptr = nullptr)
                : node_ptr(ptr) {}

            const T& operator*() const {
                return node_ptr->elem;
            }

            const T* operator->() const {
                return &(node_ptr->elem);
            }

            const_iterator& operator++() {
                node_ptr = node_ptr->next;
                return *this;
            }

            const_iterator operator++(int) {
                const_iterator temp(*this);
                ++(*this);
                return temp;
            }

            const_iterator& operator--() {
                node_ptr = node_ptr->prev;
                return *this;
            }

            const_iterator operator--(int) {
                const_iterator temp(*this);
                --(*this);
                return temp;
            }

            bool operator==(const const_iterator& other) const {
                return node_ptr == other.node_ptr;
            }

            bool operator!=(const const_iterator& other) const {
                return node_ptr != other.node_ptr;
            }
        };

    public:
        iterator begin() {
            return iterator(header->next);
        }

        const_iterator begin() const {
            return const_iterator(header->next);
        }

        iterator end() {
            return iterator(trailer);
        }

        const_iterator end() const {
            return const_iterator(trailer);
        }

        iterator insert(iterator it, const T& elem) {
            return iterator(insert_before(elem, it.node_ptr));
        }

        iterator erase(iterator it) {
            if (it.node_ptr == header || it.node_ptr == trailer) {
                throw std::out_of_range("Invalid erase");
            }
            iterator result(it.node_ptr->next);
            erase(it.node_ptr);
            return result;
        }

    private:
        void clone(const DoublyLinkedList& other) {
            for (Node* walk = other.header->next; walk != other.trailer; walk = walk->next) {
                push_back(walk->elem);
            }
        }

    public:
        friend void swap(DoublyLinkedList& a, DoublyLinkedList& b) {
            using std::swap;
            swap(a.sz, b.sz);
            swap(a.header, b.header);
            swap(a.trailer, b.trailer);
        }

        void clear() {
            while (!empty()) {
                pop_front();
            }
        }

        DoublyLinkedList(const DoublyLinkedList& other) {
            create_sentinels();
            clone(other);
        }

        DoublyLinkedList& operator=(const DoublyLinkedList& other) {
            if (this != &other) {
                DoublyLinkedList temp(other);
                swap(*this, temp);
            }
            return *this;
        }

        DoublyLinkedList(DoublyLinkedList&& other) {
            header = other.header;
            trailer = other.trailer;
            sz = other.sz;

            other.create_sentinels();
            other.sz = 0;
        }

        DoublyLinkedList& operator=(DoublyLinkedList&& other) {
            if (this != &other) {
                clear();
                delete header;
                delete trailer;

                header = other.header;
                trailer = other.trailer;
                sz = other.sz;

                other.create_sentinels();
                other.sz = 0;
            }
            return *this;
        }

        ~DoublyLinkedList() {
            clear();
            delete header;
            delete trailer;
        }

        void print() const {
            for (Node* walk = header->next; walk != trailer; walk = walk->next) {
                std::cout << walk->elem << " ";
            }
            std::cout << "\n";
        }
    };
}  // namespace dsac::list