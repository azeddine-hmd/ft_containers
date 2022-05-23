#include <iostream>
#include <vector>
#include "vector.hpp"
#include <map>
#include <unistd.h>
#include "map.hpp"
#include "pair.hpp"

#define NS std


#define T3 int
#define T4 std::string

typedef ft::pair<T3, T4>       PairType;
typedef ft::AvlNode<PairType>  AvlNode;
typedef ft::AvlTree<PairType>  AvlTree;

template<typename T1, typename T2>
AvlNode make_node(T1 key, T2 value) {
    return AvlNode(ft::make_pair(key, value));
}

int main() {

    {
//        AvlNode node1 = make_node(0, "node1");
//        AvlNode node2 = make_node(1, "node2");
//        AvlNode node3 = make_node(2, "node3");
//        AvlNode node4 = make_node(3, "node4");
//        AvlNode node5 = make_node(4, "node5");
//
//        node1.addLeftNode(&node2);
//        node2.addLeftNode(&node3);
//
//        node1.addRightNode(&node4);
//        node4.addRightNode(&node5);
//
//        std::cout << "node1: " << node1 << std::endl;
//        std::cout << "node2: " << node2 << std::endl;
//        std::cout << "node3: " << node3 << std::endl;
//        std::cout << "node4: " << node4 << std::endl;
//        std::cout << "node5: " << node5 << std::endl;
    }

    {
//        AvlNode node1 = make_node(0, "node1");
//        AvlNode node2 = make_node(1, "node2");
//        AvlNode node3 = make_node(2, "node3");
//        AvlNode node4 = make_node(3, "node4");
//        AvlNode node5 = make_node(4, "node5");
//
//        node1.addLeftNode(&node2);
//        node2.addRightNode(&node3);
//        node3.addLeftNode(&node4);
//
//        node1.addRightNode(&node5);
//
//        std::cout << "node1: " << node1 << std::endl;
//        std::cout << "node2: " << node2 << std::endl;
//        std::cout << "node3: " << node3 << std::endl;
//        std::cout << "node4: " << node4 << std::endl;
//        std::cout << "node5: " << node5 << std::endl;
    }

    {
//        AvlNode node1 = make_node(0, "node1");
//        AvlNode node2 = make_node(1, "node2");
//        AvlNode node3 = make_node(2, "node3");
//        AvlNode node4 = make_node(3, "node4");
//        AvlNode node5 = make_node(4, "node5");
//        AvlNode node6 = make_node(5, "node6");
//
//        node1.addLeftNode(&node2);
//        node1.addRightNode(&node3);
//        node3.addLeftNode(&node4);
//        node3.addRightNode(&node5);
//        node5.addRightNode(&node6);
//
//        std::cout << "node1: " << node1 << std::endl;
//        std::cout << "node2: " << node2 << std::endl;
//        std::cout << "node3: " << node3 << std::endl;
//        std::cout << "node4: " << node4 << std::endl;
//        std::cout << "node5: " << node5 << std::endl;
//        std::cout << "node6: " << node6 << std::endl;
    }

    {
//        AvlTree tree;
//        PairType pair0(0, "pair0");
//        PairType pair1(1, "pair1");
//        PairType pair2(2, "pair2");
//        PairType pair3(3, "pair3");
//        PairType pair4(4, "pair4");
//        PairType pair5(-1, "pair5");
//        PairType pair6(-300, "pair6");
//        PairType pair7(7, "pair7");
//        PairType pair10(10, "pair10");
//
//        //std::cout << ((pair1 < pair0) ? "true" : "false") << std::endl;
//
//        tree.insert(pair0);
//        tree.insert(pair1);
//        tree.insert(pair2);
//        tree.insert(pair3);
//        tree.insert(pair4);
//        tree.insert(pair5);
//        tree.insert(pair6);
//        tree.insert(pair10);
//        tree.insert(pair7);
//
//        tree.balanceFeedback(tree.getRoot());
//        std::cout << "reached" << std::endl;
    }

//    std::map<int, std::string> maper;
//    maper.insert(std::make_pair(1, "first"));
//
//    std::map<int, std::string>::iterator iter = maper.begin();
//    std::map<int, std::string>::iterator()

    return 0;
}
