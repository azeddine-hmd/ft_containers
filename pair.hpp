#pragma once

namespace ft {

    template<typename T1, typename T2>
    struct pair {
        typedef T1  first_type;
        typedef T2  second_type;

        T1  first;
        T2  second;

        pair(): first(), second() {

        }

        pair( first_type const& t1, second_type const& t2 ): first(t1), second(t2) {

        }

        template<typename U1, typename U2>
        pair( pair<U1, U2> const& copy ) {
            *this = copy;
        }

        ~pair() {
        }

        template<typename U1, typename U2>
        pair&   operator=( pair<U1, U2> const& rhs )
        {
            first = rhs.first;
            second = rhs.second;

            return *this;
        }

    };// class pair

    template<typename T1, typename T2>
    bool    operator==( ft::pair<T1,T2> const& lhs, ft::pair<T1,T2> const& rhs ) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template<typename T1, typename T2>
    bool    operator!=( ft::pair<T1,T2> const& lhs, ft::pair<T1,T2> const& rhs ) {
        return !(lhs == rhs);
    }

    template<typename T1, typename T2>
    bool    operator<( ft::pair<T1,T2> const& lhs, ft::pair<T1,T2> const& rhs ) {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template<typename T1, typename T2>
    bool    operator<=( ft::pair<T1,T2> const& lhs, ft::pair<T1,T2> const& rhs ) {
        return !(rhs < lhs);
    }

    template<typename T1, typename T2>
    bool    operator>( ft::pair<T1,T2> const& lhs, ft::pair<T1,T2> const& rhs ) {
        return rhs < lhs;
    }

    template<typename T1, typename T2>
    bool    operator>=( ft::pair<T1,T2> const& lhs, ft::pair<T1,T2> const& rhs ) {
        return !(lhs < rhs);
    }


template<typename T1,typename T2>
pair<T1, T2>    make_pair(T1 x, T2 y)
{
    return pair<T1, T2>(x,y);
}

}// namespace ft

template<typename T1, typename T2>
std::ostream&   operator<<( std::ostream& out, ft::pair<T1, T2> const& obj ) {
    out << " [ first: " << obj.first << " , second: " << obj.second << " ] " << std::endl;

    return out;
}