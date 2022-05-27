#pragma once

#include "iterator_traits.hpp"

namespace ft {

    template<class InputIt>
    typename iterator_traits<InputIt>::difference_type distance(
        InputIt first,
        InputIt last
    ) {
        typename iterator_traits<InputIt>::difference_type result = 0;
        while (first != last) {
            ++first;
            ++result;
        }
        return result;
    }

    template<typename InputIt1, typename InputIt2>
    bool equal(
        InputIt1 first1,
        InputIt1 last1,
        InputIt2 first2
    ) {
        while (first1 != last1) {
            if (*first1++ != *first2++) {
                return false;
            }
            first1++;
        }
        return true;
    }

    template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
    bool equal(
        InputIt1 first1,
        InputIt1 last1,
        InputIt2 first2,
        BinaryPredicate pred
    ) {
        while (first1 != last1) {
            if (!pred(*first1, *first2)) {
                return false;
            }

            first1++;
            first2++;
        }
        return true;
    }

    template<typename InputIt1, typename InputIt2>
    bool lexicographical_compare(
        InputIt1 first1,
        InputIt1 last1,
        InputIt2 first2,
        InputIt2 last2
    ) {
        while (first1 != last1) {
            if (first2 == last2 || (*first1) > (*first2)) {
                return false;
            } else if ((*first1) < (*first2)) {
                return true;
            }
            first1++;
            first2++;
        }

        return first2 != last2;
    }

    template<typename InputIt1, typename InputIt2, typename Compare>
    bool lexicographical_compare(
        InputIt1 first1,
        InputIt1 last1,
        InputIt2 first2,
        InputIt2 last2,
        Compare comp
    ) {
        while (first1 != last1) {
            if ((!comp(*first1, *first2) && !comp(*first2, *first1))
                || (*first1) > (*first2)
                    ) {
                return false;
            } else if ((*first1) < (*first2)) {
                return true;
            }
            first1++;
            first2++;
        }

        return first2 != last2;
    }

} // namespace ft