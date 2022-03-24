#pragma once

#include <string>

namespace ft {

    template<
            typename Category,
            typename T,
            typename Distance = ptrdiff_t,
            typename Pointer = T*,
            typename Reference = T&
    >
    struct iterator {
        typedef T                               value_type;
        typedef Distance                        difference_type;
        typedef Pointer                         pointer;
        typedef Reference                       reference;
        typedef Category                        iterator_category;
    };

    template<typename T>
    struct iterator_traits {
        typedef typename T::difference_type     difference_type;
        typedef typename T::value_type          value_type;
        typedef typename T::pointer             pointer;
        typedef typename T::reference           reference;
        typedef typename T::iterator_category   iterator_category;
    };

    template<typename T>
    struct iterator_traits<T*> {
        typedef std::ptrdiff_t                  difference_type;
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef std::forward_iterator_tag       iterator_category;
    };

    template<typename T>
    struct iterator_traits<const T *> {
        typedef std::ptrdiff_t                  difference_type;
        typedef T                               value_type;
        typedef const T*                        pointer;
        typedef const T&                        reference;
        typedef std::random_access_iterator_tag iterator_category;
    };


} // namespace ft
