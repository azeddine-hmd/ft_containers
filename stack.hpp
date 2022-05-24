#pragma once

#include "vector.hpp"

namespace ft {

    template<
            typename T,
            typename Container = vector<T>
    >
    class stack {
    public:
        typedef T               value_type;
        typedef Container       container_type;
        typedef size_t          size_type;

    protected:
        container_type c;

    public:
        explicit stack( container_type const& ctnr = container_type() ) {
            this->c = ctnr;
        }

        bool empty() const {
            return c.empty();
        }

        size_t size() const {
            return c.size();
        }

        value_type& top() {
            return c.pop_back();
        }

        value_type const& top() const {
            return c.pop_back();
        }

        void pop() {
            c.pop_back();
        }

        void push(T element) {
            c.push_back(element);
        }

        bool operator==( stack const& rhs ) {
            return this->c == rhs.c;
        }

        bool operator>=( stack const& rhs ) {
            return this->c >= rhs.c;
        }

        bool operator<=( stack const& rhs ) {
            return this->c <= rhs.c;
        }

        bool operator<( stack const& rhs ) {
            return this->c < rhs.c;
        }

        bool operator>( stack const& rhs ) {
            return this->c > rhs.c;
        }

        bool operator!=( stack const& rhs ) {
            return this->c != rhs.c;
        }
    };

}
