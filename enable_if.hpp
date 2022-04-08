#pragma once

template<bool B, class D = void>
struct enable_if {
};

template<class D>
struct enable_if<true, D> {
    typedef D type;
};
