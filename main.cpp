#include <iostream>
#include <vector>
#include "vector.hpp"
#include "pair.hpp"

#define NS std

int main() {
    NS::vector<int> v;

    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(6);
    v.push_back(7);
    v.push_back(8);
    v.push_back(9);
    v.push_back(10);

    v.insert(v.begin() + 4, 5);
    v.insert(v.end(), 99);

    for (NS::vector<int>::iterator iter = v.begin(); iter != v.end(); iter++) {
        std::cout << *iter << std::endl;
    }

    NS::pair<int, std::string> a(1, "first element");

    return 0;
}
