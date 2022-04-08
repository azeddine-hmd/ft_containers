#pragma once

#include "iterator_traits.hpp"
#include "utils.hpp"

namespace ft {

    template<typename Iter>
    class reverse_iterator {
    public:
        typedef Iter iterator_type;
        typedef ft::reverse_iterator<iterator_type> self_type;
        typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
        typedef typename iterator_traits<iterator_type>::value_type value_type;
        typedef typename iterator_traits<iterator_type>::difference_type difference_type;
        typedef typename iterator_traits<iterator_type &>::reference reference;
        typedef typename iterator_traits<iterator_type *>::pointer pointer;
    private:
        iterator_type m_rIter;
    public:
        reverse_iterator() : m_rIter() {}

        reverse_iterator(iterator_type it) : m_rIter(it) {}

        template<typename IterCopy>
        reverse_iterator(reverse_iterator<IterCopy> const &rIter) {
            m_rIter = rIter.base();
        }

        ~reverse_iterator() {}

        iterator_type base() const {
            return m_rIter;
        }

        self_type &operator++() {
            m_rIter--;
            return *this;
        }

        self_type operator++(int) {
            self_type tmp = *this;
            m_rIter--;
            return tmp;
        }

        self_type &operator--() {
            m_rIter++;
            return *this;
        }

        self_type operator--(int) {
            self_type tmp = *this;
            m_rIter++;
            return tmp;
        }

        reference operator[](difference_type i) const {
            return m_rIter[-i];
        }

        self_type operator+=(difference_type i) {
            m_rIter -= i;
            return *this;
        }

        self_type operator-=(difference_type i) {
            m_rIter += i;
            return *this;
        }

        reverse_iterator operator+(difference_type i) const {
            return self_type(m_rIter - i);
        }

        reverse_iterator operator-(difference_type n) const {
            return m_rIter + n;
        }

        reference operator*() const {
            return *( --Iterator(m_rIter) );
        }

        pointer operator->() const {
            return &m_rIter;
        }
    }; // class reverse_iterator

    template<typename Iter1, typename Iter2>
    bool operator==(reverse_iterator<Iter1> const &lhs, reverse_iterator<Iter2> const &rhs) {
        return (lhs.base()) == rhs.base();
    }

    template<typename Iter1, typename Iter2>
    bool operator!=(reverse_iterator<Iter1> const &lhs, reverse_iterator<Iter2> const &rhs) {
        return (lhs.it) != (rhs.it);
    }

    template<typename Iter1, typename Iter2>
    bool operator>=(reverse_iterator<Iter1> const &lhs, reverse_iterator<Iter2> const &rhs) {
        return lhs.base() <= rhs.base();
    }

    template<typename Iter1, typename Iter2>
    bool operator>(reverse_iterator<Iter1> const &lhs, reverse_iterator<Iter2> const &rhs) {
        return lhs.base() < rhs.base();
    }

    template<typename Iter1, typename Iter2>
    bool operator<=(reverse_iterator<Iter1> const &lhs, reverse_iterator<Iter2> const &rhs) {
        return lhs.base() >= rhs.base();
    }

    template<typename Iter1, typename Iter2>
    bool operator<(reverse_iterator<Iter1> const &lhs, const reverse_iterator<Iter2> &rhs) {
        return lhs.base() > rhs.base();
    }

    template<typename Iter>
    reverse_iterator<Iter>
    operator+(typename reverse_iterator<Iter>::difference_type n, reverse_iterator<Iter> const &rIter) {
        return reverse_iterator<Iter>(rIter.base() - n);
    }

    template<typename Iter>
    typename reverse_iterator<Iter>::difference_type
    operator-(reverse_iterator<Iter> const &lhs, reverse_iterator<Iter> const &rhs) {
        return lhs.base() - rhs.base();
    }

} // namespace ft