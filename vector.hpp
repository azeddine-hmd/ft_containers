#pragma once

#include <algorithm>
#include <iterator>
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"
#include "is_integral.hpp"
#include "enable_if.hpp"

namespace ft {

    template<typename Iter>
    class VectorIter {
    public:
        typedef Iter                                                        iterator_type;
        typedef typename iterator_traits<iterator_type>::iterator_category  iterator_category;
        typedef typename iterator_traits<iterator_type>::value_type         value_type;
        typedef typename iterator_traits<iterator_type>::difference_type    difference_type;
        typedef typename iterator_traits<iterator_type>::pointer            pointer;
        typedef value_type const *                                          const_pointer;
        typedef typename iterator_traits<iterator_type>::reference          reference;
        typedef value_type const &                                          const_reference;
    private:
        Iter m_pIter;
    public:
        VectorIter(): m_pIter(NULL) {}

        VectorIter(pointer pIter): m_pIter(pIter) {

        }

        VectorIter(VectorIter const &copy) {
            *this = copy;
        }

        ~VectorIter() {}

        VectorIter &operator=(VectorIter const &other) {
            m_pIter = other.m_pIter;
            return *this;
        }

        reference operator*() {
            return *m_pIter;
        }

        const_reference operator*() const {
            return *m_pIter;
        }
        pointer operator->() {
            return m_pIter;
        }
        const_pointer operator->() const {
            return m_pIter;
        }
        reference operator[](int val) {
            return m_pIter[val];
        }

        const_reference operator[](int val) const {
            return m_pIter[val];
        }

        VectorIter &operator++() {
            m_pIter++;
            return *this;
        }

        VectorIter operator++(int) {
            VectorIter tmp = *this;
            m_pIter++;
            return tmp;
        }

        VectorIter &operator--() {
            m_pIter--;
            return *this;
        }

        VectorIter operator--(int) {
            VectorIter tmp = *this;
            m_pIter--;
            return tmp;
        }

        VectorIter &operator+=(int value) {
            m_pIter += value;
            return *this;
        }

        VectorIter operator+(int value) const {
            VectorIter tmp = *this;
            return tmp += value;
        }

        VectorIter &operator-=(int value) {
            m_pIter -= value;
            return *this;
        }

        VectorIter operator-(int value) const {
            VectorIter tmp = *this;
            return tmp -= value;
        }

        difference_type operator-(VectorIter const &other) const {
            return m_pIter - other.m_pIter;
        }

        bool operator==(VectorIter const &other) const {
            return m_pIter == other.m_pIter;
        }

        bool operator!=(VectorIter const &other) const {
            return m_pIter != other.m_pIter;
        }

        bool operator<(VectorIter const &other) const {
            return m_pIter < other.m_pIter;
        }

        bool operator<=(VectorIter const &other) const {
            return m_pIter <= other.m_pIter;
        }

        bool operator>(VectorIter const &other) const {
            return m_pIter > other.m_pIter;
        }

        bool operator>=(VectorIter const &other) const {
            return m_pIter >= other.m_pIter;
        }

    }; // class VectorIter

    template<
          typename T,
          typename Allocator = std::allocator<T>
    >
    class vector {

    public:
        typedef T                                                       value_type;
        typedef std::size_t                                             size_type;
        typedef std::ptrdiff_t                                          difference_type;

        typedef Allocator                                               allocator_type;
        typedef typename allocator_type::reference                      reference;
        typedef typename allocator_type::const_reference                const_reference;
        typedef typename allocator_type::pointer                        pointer;
        typedef typename allocator_type::const_pointer                  const_pointer;

        typedef typename ft::VectorIter<pointer>                        iterator;
        typedef typename ft::VectorIter<const_pointer>                  const_iterator;
        typedef typename ft::reverse_iterator<iterator>                 reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator>           const_reverse_iterator;

    private:
        allocator_type  m_alloc;
        pointer         m_valptr;
        size_type       m_size;
        size_type       m_capacity;


    public:

        explicit vector( allocator_type const &alloc = allocator_type() ) {
            m_alloc = alloc;
            m_size = 0;
            m_capacity = 0;
            m_valptr = NULL;
        }

        explicit vector(
                size_type n,
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

        template<typename InputIt>
        vector (
                InputIt first,
                InputIt last,
                allocator_type const &alloc = allocator_type(),
                typename enable_if< !is_integral<InputIt>::value, InputIt>::type* = NULL
        ) {
            m_capacity = 0;
            m_alloc = alloc;
            reserve(ft::distance(first, last));
            initIterRange(first, last);
        }

        vector( vector const &copy ) {
            *this = copy;
        }

        vector &operator=( vector const &rhs ) {
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

        void push_back( const_reference val ) {
            if (m_capacity == 0) {
                reserve(1);
            } else if (m_size + 1 > m_capacity) {
                reserve(m_capacity * 2);
            }
            m_valptr[m_size++] = val;
        }

        void pop_back() {
            if (m_size && m_capacity) {
                m_alloc.destroy(&m_valptr[--m_size]);
            }
        }

        void resize( size_type n, value_type val = value_type() ) {
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


        void reserve( size_type n ) {
            if (n > max_size()) {
                throw std::length_error("ft::vector: new capacity exceeds ram max length");
            } else if (n > m_capacity) {
                pointer newValptr;
                newValptr = m_alloc.allocate(n);
                for (size_type i = 0; i < m_size; i++) {
                    m_alloc.construct(&newValptr[i], m_valptr[i]);
                    m_alloc.destroy(&m_valptr[i]);
                }
                m_alloc.deallocate(m_valptr, m_capacity);
                m_capacity = n;
                m_valptr = newValptr;
            }
        }

        void assign( size_type n, const_reference val ) {
            if (n > m_capacity)
                reserve(n);
            for (size_type i = 0; i < m_size; i++)
                m_alloc.destroy(&m_valptr[i]);
            for (size_type i = 0; i < n; i++)
                m_alloc.construct(&m_valptr[i], val);
            m_size = n;
        }

        template <class InputIt>
        void assign (
                InputIt first,
                InputIt last,
                typename enable_if< !is_integral<InputIt>::value, InputIt >::type* = NULL
        ) {
            clear();
            reserve(ft::distance(first, last));
            initIterRange(first, last);
        }

        iterator insert( iterator position, const value_type& val ) {
            difference_type pos = position - begin();
            size_type element_to_move = end() - position;
            ft::vector<T> tmp;

            tmp.assign(position, end());

            if (m_size + 1 > m_capacity) {
                reserve(m_capacity * 2);
            }
            resize(m_size - element_to_move);
            push_back(val);
            for (size_type i = 0; i < element_to_move; i++) {
                push_back(tmp[i]);
            }
            return begin() + pos;
        }

        void swap( reference x ){
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

        bool empty() const {
            return m_size == 0;
        }

        allocator_type get_allocator() const {
            return m_alloc;
        }

        reference operator[](size_type n) {
            return m_valptr[n];
        }

        const_reference operator[]( size_type n ) const {
            return m_valptr[n];
        }

        reference back() {
            return m_valptr[m_size - 1];
        }

        const_reference back() const {
            return m_valptr[m_size - 1];
        }

        reference at( size_type n ) {
            if (n >= m_size) throw std::out_of_range("ft::vector: element's out of bounds");
            return m_valptr[n];
        }

        const_reference at( size_type n ) const {
            if (n >= m_size) throw std::out_of_range("ft::vector: element's out of bounds");
            return m_valptr[n];
        }

        reference front() {
            return m_valptr[0];
        }

        const_reference front() const {
            return m_valptr[0];
        }

        iterator	begin() {
            return iterator(&m_valptr[0]);
        }

        const_iterator begin() const {
            return const_iterator(&m_valptr[0]);
        }

        iterator	end() {
            return iterator(&m_valptr[m_size]);
        }

        const_iterator end() const {
            return const_iterator(&m_valptr[m_size]);
        }

        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }

        reverse_iterator rend() {
            return  reverse_iterator(this->begin());
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }

    private:
        void clean() {
            clear();
            m_alloc.deallocate(m_valptr, m_capacity);
        }

        template<typename InputIt>
        void initIterRange( InputIt first, InputIt last ) {
            while (first != last) {
                push_back(*first++);
            }
        }

    }; // class vector


} // namespace ft
