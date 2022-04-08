#pragma once

#include <string>

namespace ft {

//    template<
//            typename Category,
//            typename Iter,
//            typename Distance = ptrdiff_t,
//            typename Pointer = Iter*,
//            typename Reference = Iter&
//    >
//    struct iterator {
//        typedef Iter                               value_type;
//        typedef Distance                        difference_type;
//        typedef Pointer                         pointer;
//        typedef Reference                       reference;
//        typedef Category                        iterator_category;
//    };

    template<typename Iter>
    struct iterator_traits {
        typedef typename std::ptrdiff_t            difference_type;
        typedef typename Iter::value_type          value_type;
        typedef typename Iter::pointer             pointer;
        typedef typename Iter::reference           reference;
        typedef typename Iter::iterator_category   iterator_category;
    };

    template<typename T>
    struct iterator_traits<T*> {
        typedef std::ptrdiff_t                  difference_type;
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef std::random_access_iterator_tag iterator_category;
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
