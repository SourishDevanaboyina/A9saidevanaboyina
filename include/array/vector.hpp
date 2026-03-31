#pragma once
#include <algorithm>     // provides max
#include <stdexcept>     // provides out_of_range exception

namespace dsac::array {

    template <typename T>
class Vector {
    private:
        int cap{0};
        int sz{0};
        T* data{nullptr};
    public:
        Vector();
        int capacity();
        int size();
        bool empty() const;
        
        const T& operator[](int i) const;
        T& operator[](int i);
        
        const T& at(int i) const;
        T& at(int i);

        const T& front() const;
        T& front();

        const T& back() const;
        T& back();

        void push_back(const T& elem);

        void pop_back();

        void insert(int i, const T& elem);
        void erase(int i);

        void reserve(int minimum);

        Vector(const Vector& other);

        Vector& operator=(const Vector& other);

        Vector(Vector&& other);
        Vector& operator=(Vector&& other);

        ~Vector();
    
    private:
        void clone(const Vector& other);

        void transfer(Vector& other);

    public:
        class iterator {
            friend class Vector;
            private:
                Vector* vec;
                int ind;        // index within the vector
            
            public:
                iterator(Vector* v = nullptr, int i = -1);
                T& operator*() const;
                T* operator->() const;
                iterator& operator++();
                iterator operator++(int);
                iterator& operator--();
                iterator operator--(int);
                bool operator==(iterator rhs) const;
                bool operator!=(iterator rhs) const;
        };

        class const_iterator {
            private:
                const Vector* vec;
                int ind;                   // index within the vector
            
            public:
                const_iterator(const Vector* v = nullptr, int i = -1);
                const T& operator*() const;
                const T* operator->() const;
                const_iterator& operator++();
                const_iterator operator++(int);
                const_iterator& operator--();
                const_iterator operator--(int);
                bool operator==(const_iterator rhs) const;
                bool operator!=(const_iterator rhs) const;
        };

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;

        iterator insert(iterator it, const T& elem);

        iterator erase(iterator it);


        void shrink();
        
        void shrink_to_fit();
    
}; // Vector class

}  // namespace dsac::array
