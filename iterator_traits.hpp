#pragma once

#include <string>

namespace ft {

   struct random_access_iterator_tag {};

    template<typename Iter>
    struct iterator_traits {
        typedef typename std::ptrdiff_t            difference_type;
        typedef typename Iter::value_type          value_type;
        typedef typename Iter::pointer             pointer;
        typedef typename Iter::reference           reference;
        typedef typename Iter::iterator_category   iterator_category;
    };

    template<typename T>
    struct iterator_traits<T *> {
        typedef std::ptrdiff_t                  difference_type;
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef random_access_iterator_tag      iterator_category;
    };

    template<typename T>
    struct iterator_traits<T const*> {
        typedef std::ptrdiff_t                  difference_type;
        typedef T                               value_type;
        typedef const T*                        pointer;
        typedef const T&                        reference;
        typedef random_access_iterator_tag      iterator_category;
    };


} // namespace ft
