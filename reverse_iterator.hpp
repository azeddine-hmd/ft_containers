#pragma once

#include "iterator_traits.hpp"
#include "utils.hpp"

namespace ft {

    template<typename Iterator>
    struct reverse_iterator {
        typedef Iterator                                                    iterator_type;
        typedef typename iterator_traits<iterator_type>::iterator_category  iterator_category;
        typedef typename iterator_traits<iterator_type>::value_type         value_type;
        typedef typename iterator_traits<iterator_type>::difference_type    difference_type;
        typedef typename iterator_traits<iterator_type>::reference          reference;
        typedef typename iterator_traits<iterator_type>::pointer            pointer;

        iterator_type it;

        reverse_iterator() {

        }

        explicit reverse_iterator( iterator_type iter) {
            it = iter;
        }

        template<typename Iter>
        reverse_iterator( reverse_iterator<Iter> const& rev_iter ) {
            it = rev_iter.base();
        }

        ~reverse_iterator() {

        }

        iterator_type base() const {
            return iterator_type(it);
        }

        reverse_iterator& operator++() {
            it--;
            return *this;
        }

        reverse_iterator operator++( int ) {
            reverse_iterator tmp = *this;
            it--;
            return tmp;
        }

        reverse_iterator& operator--() {
            it++;
            return *this;
        }

        reverse_iterator operator--( int ) {
            reverse_iterator tmp = *this;
            it++;
            return tmp;
        }

        reference operator[](difference_type i) const {
            return base()[- i - 1];
        }

        reverse_iterator operator+=(difference_type i) {
            it -= i;
            return *this;
        }

        reverse_iterator operator-=(difference_type i) {
            it += i;
            return *this;
        }

        reverse_iterator operator+(difference_type i) const {
            return reverse_iterator(it - i);
        }

        reverse_iterator operator-(difference_type n) const {
            return reverse_iterator(it + n);
        }

        reference operator*() const {
            return *(--Iterator(it));
        }

        pointer operator->() const {
            return &(operator*());
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
    reverse_iterator<Iter> operator+(
        typename reverse_iterator<Iter>::difference_type n,
        reverse_iterator<Iter> const &rev_it
    ) {
        return reverse_iterator<Iter>(rev_it.base() - n);
    }

    template<typename Iter>
    typename reverse_iterator<Iter>::difference_type operator-(
        reverse_iterator<Iter> const &lhs, reverse_iterator<Iter> const &rhs
    ) {
        return -1 * (lhs.base() - rhs.base());
    }

} // namespace ft
