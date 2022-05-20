#pragma once

#include "pair.hpp"
#include <iostream>

namespace ft {

    template<typename T,
            typename Alloc = std::allocator<T>
            >
    class AvlNode {

    public:

        typedef T   value_type;
        AvlNode*    m_parent;
        AvlNode*    m_right;
        AvlNode*    m_left;

    private:

        Alloc       m_alloc;
        T*          m_val;
        int         m_height;

    private:

        AvlNode()  {

        }

    public:

        AvlNode( const T& val ) {
            m_val = m_alloc.allocate(1);
            m_alloc.construct(m_val, val);
            m_parent = m_right = m_left = NULL;
            m_height = 0;
        }

        AvlNode&    operator=( AvlNode const& rhs ) {
            if (this != *rhs) {
                m_right = rhs.m_right;
                m_left = rhs.m_left;
                m_parent = rhs.m_parent;
                m_height = rhs.m_height;
                m_alloc.destroy(m_val);
                m_alloc.deaalocate(m_val, 1);
                m_val = rhs.m_val;
            }

            return *this;
        }

        int getHeight() const {
            return m_height;
        }

        T const&    getValue() const {
            if (!m_val) throw std::runtime_error("value is null");
            return *m_val;
        }

        int getBalanceFactor() const {
            if (!m_left && !m_right) {
                return 0;
            } else if (!m_left) {
                return -(m_right->m_height + 1);
            } else if (!m_right) {
                return m_left->m_height + 1;
            } else {
                return (m_left->m_height + 1) - (m_right->m_height + 1);
            }
        }

        void addLeftNode( AvlNode* node ) {
            if (m_left)
                throw std::runtime_error("left node already exist");
            else if (node->m_parent)
                throw std::runtime_error("parent node already exist");

            m_left = node;
            node->m_parent = this;
            updateHeight();
        }

        void addRightNode( AvlNode* node ) {
            if (m_right)
                throw std::runtime_error("right node already exist");
            m_right = node;
            if (node->m_parent)
                throw std::runtime_error("added node already have parent");
            node->m_parent = this;
            updateHeight();
        }

        bool haveLeftNode() const {
            return m_left;
        }

        bool haveRightNode() const {
            return m_right;
        }

        AvlNode *getRightNode() const {
            return m_right;
        }

        AvlNode *getLeftNode() const {
            return m_left;
        }

        bool    isBalanced() const {
            int blcFactor = getBalanceFactor();
            return (blcFactor == -1 || blcFactor == 0 || blcFactor == 1);
        }

        void updateHeight() {
            if (!m_left && !m_right) {
                m_height = 0;
            } else if (!m_left) {
                m_height = m_right->m_height + 1;
            } else if (!m_right) {
                m_height = m_left->m_height + 1;
            } else {
                m_height = std::max(m_left->m_height, m_right->m_height) + 1;
            }

            if (m_parent) m_parent->updateHeight();
        }

        void destroy() {
            if (!m_val)
                return;
            m_alloc.destroy(m_val);
            m_alloc.deallocate(m_val, 1);
            m_left->destroy();
            m_left = NULL;
            m_right->destroy();
            m_right = NULL;
            m_parent = NULL;
            m_height = 0;
        }

        AvlNode* previous() {
            AvlNode * parent;
            if (!m_left) {
                parent = m_parent;
            }
            //TODO: so what next?
        }

    }; // class AvlNode

    template<
            typename T,
            typename Compare = std::less<T>,
            typename Alloc = std::allocator<T>
    >
    class AvlTree {

    public:
        typedef T                                               value_type;
        typedef AvlNode<T, Alloc>                               Node;
        typedef typename Alloc::template rebind<Node>::other    node_allocator;

    private:
        node_allocator      m_nodeAlloc;
        Compare             cmp;
        Node*               m_root;
        bool                m_isFound;

    private:
        Node*   makeNode( T const& val ) {
            Node * node = m_nodeAlloc.allocate(1);
            m_nodeAlloc.construct(node, val);
            return node;
        }

        Node* insertNode( Node* current, Node* newNode ) {
            if (!current)
                return newNode;
            if (!cmp(newNode->getValue(), current->getValue())) {
                current->m_right = insertNode(current->m_right, newNode);
                current->m_right->m_parent = current;
            } else if (cmp(newNode->getValue(), current->getValue())) {
                current->m_left = insertNode(current->m_left, newNode);
                current->m_left->m_parent = current;
            }

            return balanceNode(m_root, newNode->getValue());
        }

        Node* rotateLeft( Node* x ) {
            Node* y = x->m_right;
            Node* yLeftST = y->m_left;

            if (!y)
                throw std::runtime_error("right tree does not exist");

            if (y->m_left)
                y->m_left->m_parent = x;
            y->m_left = x;
            x->m_right = yLeftST;

            y->m_parent = x->m_parent;
            x->m_parent = y;

            x->updateHeight();
            y->updateHeight();

            return y;
        }

        Node* rotateRight( Node* y ) {
            Node* x = y->m_left;
            Node* xRightST = x->m_right;

            if (!x)
                throw std::runtime_error("left tree does not exist");

            if (x->m_right)
                x->m_right->m_parent = y;
            x->m_right = y;
            y->m_left = xRightST;

            x->m_parent = y->m_parent;
            y->m_parent = x;

            y->updateHeight();
            x->updateHeight();

            return x;
        }

        Node* balanceNode( Node* current, const typename Node::value_type val ) {
            int balanceFactor = current->getBalanceFactor();
            if (balanceFactor > 1) {
                if (cmp(val, current->getLeftNode()->getValue())) {
                    return rotateRight(current);
                } else {
                    rotateLeft(current->getLeftNode());
                    return rotateRight(current);
                }
            } else if (balanceFactor < -1) {
                if (!cmp(val, current->getRightNode()->getValue())) {
                    return rotateLeft(current);
                } else {
                    rotateRight(current->getRightNode());
                    return rotateLeft(current);
                }
            }
            return current;
        }

    public:
        AvlTree(): m_root(NULL) {

        }

        AvlTree( T const& val ) {
            m_root = makeNode(val);
        }

        AvlTree& operator=( AvlTree const& rhs ) {
            m_root = rhs.m_root;
            return *this;
        }

        void insert( T const& val ) {
            if (m_root) {
                insertNode(m_root, makeNode(val));
            } else {
                m_root = makeNode(val);
            }
        }

        Node* find( Node* current, const value_type& val ) const {
            if (!current || current->getValue().first == val.first) {
                return current;
            }
            if (!cmp(val, m_root->getValue())) {
                return find(current->m_right, val);
            } else {
                return find(current->m_left, val);
            }
        }

        Node* search( value_type const& val ) const {
            return find(m_root, val);
        }

        Node* findMin() const {
            if (!m_root)
                return NULL;
            Node * min = m_root;
            while (min->m_left)
                min = min->m_left;
            return min;
        }

        Node* findMax() const {
            if (!m_root)
                return NULL;
            Node * max = m_root;
            while (max->m_right)
                max = max->m_right;
            return max;
        }

        void balanceFeedback( Node* current ) {
            if (current->haveLeftNode())
                balanceFeedback(current->getLeftNode());
            else if (current->haveRightNode())
                balanceFeedback(current->getRightNode());
            //if (!current->isBalanced()) {
            std::cout << current->getBalanceFactor() << std::endl;
            //}
        }

        Node* getRoot() const {
            return m_root;
        }
    };// class AvlTree

}// namespace ft


template<typename T1, typename T2>
std::ostream&   operator<<( std::ostream& out, ft::AvlNode<T1, T2> const& obj ) {
    out << "[ height: " << obj.getHeight() << " , balance factor: " << obj.getBalanceFactor() << " , value: " << obj.getValue() << " ]" << std::endl;

    return out;
}