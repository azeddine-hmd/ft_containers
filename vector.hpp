#pragma once

#include <algorithm>
#include "iterator.hpp"

namespace ft {

    template<typename T, typename Allocator = std::allocator<T> >
    class vector {

    public:

        typedef std::size_t size_type;
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef std::ptrdiff_t difference_type;

        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

    private:

        allocator_type m_alloc;
        value_type *m_valptr;
        size_type m_size;
        size_type m_capacity;

        void clean() {
            clear();
            m_alloc.deallocate(m_valptr, m_capacity);
        }

    public:

        vector(allocator_type const &alloc = allocator_type()) {
            m_alloc = alloc;
            m_size = 0;
            m_capacity = 0;
            m_valptr = NULL;
        }

        vector(size_type n,
               value_type const &val = value_type(),
               allocator_type const &alloc = allocator_type()
        ) {
            m_alloc = alloc;
            m_size = n;
            m_capacity = n;
            m_valptr = m_alloc.allocate(n);
            for (size_type i = 0; i < m_size; i++) {
                m_alloc.construct(&m_valptr[i], val);
            }
        }

        vector(vector<T, Allocator> const &copy) {
            *this = copy;
        }

        vector<T, Allocator> &operator=(vector<T, Allocator> const &rhs) {
            if (this != &rhs) {
                clean();
                m_size = rhs.m_size;
                m_capacity = rhs.m_capacity;
                m_valptr = m_alloc.allocate(m_capacity);
                for (size_type i = 0; i < m_size; i++) {
                    m_alloc.construct(&m_valptr[i], rhs.m_valptr[i]);
                }
            }

            return *this;
        }

        ~vector() {
            clean();
        }

        void push_back(const_reference val) {
            if (m_capacity == 0) {
                reserve(1);
            } else if (m_size + 1 > m_capacity) {
                reserve(m_capacity * 2);
            }
            m_valptr[m_size++] = val;
        }

        void pop_back(void) {
            if (m_size) {
                m_alloc.destroy(&m_valptr[m_size--]);
            }
        }

        void resize(size_type n, value_type val = value_type()) {
            if (n < m_size) {
                for (size_type i = n; i < m_size; i++)
                    m_alloc.destroy(&m_valptr[i]);
                m_size = n;
            } else if (n > m_capacity) {
                (n > m_capacity * 2) ? reserve(n) : reserve(m_capacity * 2);
                while (m_size < n) {
                    m_alloc.construct(&m_valptr[m_size++], val);
                }
            } else if (n > m_size) {
                while (m_size < n) {
                    m_alloc.construct(&m_valptr[m_size++]);
                }
            }
        }


        void reserve(size_type n) {
            if (n > max_size()) {
                throw std::length_error("ft::vector: new capacity exceeds ram max length");
            } else if (n > m_capacity) {
                pointer newValptr;
                newValptr = m_alloc.allocate(n);
                for (size_type i = 0; i < m_size; i++) {
                    m_alloc.construct(&newValptr[i], &m_valptr[i]);
                    m_alloc.destroy(&m_valptr[i]);
                }
                m_alloc.deallocate(m_valptr);
                m_capacity = n;
                m_valptr = newValptr;
            }
        }

        void assign(size_type n, const_reference val) {
            if (n > m_capacity)
                reserve(n);
            for (size_type i = 0; i < m_size; i++)
                m_alloc.destroy(&m_valptr[i]);
            for (size_type i = 0; i < n; i++)
                m_alloc.construct(&m_valptr[i], val);
            m_size = n;
        }

        void swap (reference x){
            pointer   tmpValptr = m_valptr;
            size_type tmpSize = m_size;
            size_type tmpCapacity = m_capacity;

            m_valptr = x.m_valptr;
            m_size = x.m_size;
            m_capacity = x.m_capacity;

            x.m_valptr = tmpValptr;
            x.m_size = tmpSize;
            x.m_capacity = tmpCapacity;
        }

        void clear() {
            for (size_type i = 0; i < m_size; i++) {
                m_alloc.destroy(&m_valptr[i]);
            }
            m_size = 0;
        }


        size_type max_size() const {
            return m_alloc.max_size();
        };

        size_type size() const {
            return m_size;
        }

        size_type capacity() const {
            return m_capacity;
        }

        bool empty(void) const {
            return m_size == 0;
        }

        allocator_type get_allocator() const {
            return m_alloc;
        }

        reference operator[](size_type n) {
            return m_valptr[n];
        }

        const_reference operator[](size_type n) const {
            return m_valptr[n];
        }

        reference back() {
            return m_valptr[m_size - 1];
        }

        const_reference back() const {
            return m_valptr[m_size - 1];
        }

        reference at(size_type n) {
            if (n >= m_size) throw std::out_of_range("ft::vector: element's out of bounds");
            return m_valptr[n];
        }

        const_reference at(size_type n) const {
            if (n >= m_size) throw std::out_of_range("ft::vector: element's out of bounds");
            return m_valptr[n];
        }

        reference front() {
            return m_valptr[0];
        }

        const_reference front() const {
            return m_valptr[0];
        }

    }; // class vector
} // namespace ft
