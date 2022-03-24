#pragma once

#include <string>

namespace ft {

//    template<
//            typename Category,
//            typename T,
//            typename Reference = T,
//            typename Pointer = T*,
//            typename Distance = ptrdiff_t
//    >
//    struct iterator {
//        typedef T         value_type;
//        typedef Reference reference;
//        typedef Pointer   pointer;
//        typedef Distance  difference_type;
//        typedef Category  iterator_category;
//    };

    template<typename T>
    struct iterator {
        typedef typename T::difference_type     difference_type;
        typedef typename T::value_type          value_type;
        typedef typename T::pointer             pointer;
        typedef typename T::reference           reference;
        typedef typename T::iterator_category   iterator_category;
    };

    template<typename T>
    struct iterator<T*> {
        typedef std::ptrdiff_t            difference_type;
        typedef T                         value_type;
        typedef T*                        pointer;
        typedef T&                        reference;
        typedef std::forward_iterator_tag iterator_category;
    };

    template<typename T>
    struct iterator<const T*> {
        typedef std::ptrdiff_t                  difference_type;
        typedef T                               value_type;
        typedef const T*                        pointer;
        typedef const T&                        reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

    /* [ iterator manipulators ] */

    template<class InputIt>
    typename ft::iterator<InputIt>::difference_type distance(InputIt first, InputIt last)
    {
        typename ft::iterator<InputIt>::difference_type result = 0;
        while (first != last)
        {
            ++first;
            ++result;
        }
        return result;
    }

    template <typename InputIt1, typename InputIt2>
    bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
    {
        while (first1 != last1) {
            if (*first1++ != *first2++) {
                return false;
            }
            first1++;
        }
        return true;
    }

    template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
    bool equal (InputIt1 first1, InputIt1 last1,
                InputIt2 first2, BinaryPredicate pred)
    {
        while (first1 != last1) {
            if (!pred()) {

            }

            first1++;
            first2++;
        }
            if (!pred(*first1++, *first2++))
                return false;
        return true;
    }

} // namespace ft
