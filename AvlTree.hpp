#pragma once

#include "pair.hpp"
#include <iostream>

namespace ft {

    template<
            typename T,
            typename Alloc = std::allocator<T>
    >
    struct AvlNode {

    typedef T   value_type;

    public:
        T*          m_val;
        AvlNode*    m_parent;
        AvlNode*    m_right;
        AvlNode*    m_left;
        Alloc       m_alloc;
        int         m_height;

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

//        bool    isBalanced() const {
//            int blcFactor = getBalanceFactor();
//            return (blcFactor == -1 || blcFactor == 0 || blcFactor == 1);
//        }

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

        //TODO: move it to tree; plus what the heck is this ??
//        void destroy() {
//            if (!m_val)
//                return;
//            m_alloc.destroy(m_val);
//            m_alloc.deallocate(m_val, 1);
//            m_left->destroy();
//            m_left = NULL;
//            m_right->destroy();
//            m_right = NULL;
//            m_parent = NULL;
//            m_height = 0;
//        }

        AvlNode* next() {
            AvlNode * curr = this;

            if (!curr) {
                return;
            }

            if (!m_right) {
                AvlNode * parent = m_parent;
                while (parent && parent->m_right && curr->m_val->first == parent->m_right->m_val->first) {
                    curr = parent;
                    parent = parent->m_parent;
                }
                curr = parent;
            } else {
                curr = m_right;
                while (curr->haveLeftNode())
                    curr = curr->m_left;
            }

            return curr;
        }

        AvlNode* previous() {
            AvlNode * curr = this;

            if (!m_left) {
                AvlNode * parent = m_parent;
                while (parent && parent->m_left && curr->m_val->first == parent->m_left->m_val->first) {
                    curr = parent;
                    parent = parent->m_parent;
                }
                curr = parent;
            } else {
                curr = m_left;
                while (curr->m_right)
                    curr = curr->m_right;
            }

            return curr;
        }

        AvlNode* getRoot() {
            AvlNode * root = this;
            while (root && root->haveParentNode())
                root = root->haveParentNode();
            return root;
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
        Compare             key_compare;
        Node*               m_root;

    private:
        Node*   makeNode( T const& val ) {
            Node * node = m_nodeAlloc.allocate(1);
            m_nodeAlloc.construct(node, val);
            return node;
        }

        Node* insertNode( Node* current, Node* newNode ) {
            if (!current)
                return newNode;
            if (!cm(newNode->m_val->first, current->m_val->first)) {
                current->m_right = insertNode(current->m_right, newNode);
                current->m_right->m_parent = current;
            } else if (key_compare(newNode->m_val->first, current->m_val->first)) {
                current->m_left = insertNode(current->m_left, newNode);
                current->m_left->m_parent = current;
            }

            return balanceTree(current, newNode->m_val);
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

        Node* balanceTree( Node* current, typename Node::value_type const val ) {
            int balanceFactor = current->getBalanceFactor();

            if (balanceFactor > 1) {
                if (key_compare(val.first, current->getLeftNode()->m_val->first)) {
                    return rotateRight(current);
                } else {
                    rotateLeft(current->getLeftNode());
                    return rotateRight(current);
                }
            } else if (balanceFactor < -1) {
                if (!key_compare(val.first, current->getRightNode()->getValue().first)) {
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

        AvlTree(AvlTree* root): m_root(root) {

        }

        ~AvlTree() {

        }

        AvlTree& operator=( AvlTree const& rhs ) {
            m_root = rhs.m_root;
            return *this;
        }

        void insert( T const& val ) {
            if (m_root) {
                m_root = insertNode(m_root, makeNode(val));
            } else {
                m_root = makeNode(val);
            }
        }

        Node* find( Node* current, const value_type& val ) const {
            if (!current || current->getValue().first == val.first) {
                return current;
            }
            if (!key_compare(val.first, current->getValue().first)) {
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

        //TODO: only for debugging
        void balanceFeedback( Node* current ) {
            if (current->haveLeftNode())
                balanceFeedback(current->getLeftNode());
            else if (current->haveRightNode())
                balanceFeedback(current->getRightNode());
            //if (!current->isBalanced()) {
            std::cout << current->getBalanceFactor() << std::endl;
            //}
        }

        Node* del( Node* node, value_type const& val,  bool& is_found ) {
            if (!node)
                return NULL;

            if (val.first == node->getValue().first) {
                is_found = true;
                // node have only one child right or left
                if (!node->haveRightNode() || !node->haveLeftNode()) {
                    Node * tmp = node->m_right ? node->m_right : node->m_left;

                    // node have no child
                    if (!tmp) {
                        tmp = node;
                        node = NULL;
                    } else {
                        // node have one child
                        Node * nodeParent = node->m_parent;
                        *node = *tmp;
                        node->m_parent = nodeParent;
                    }
                    m_nodeAlloc.destroy(tmp->m_val);
                    m_nodeAlloc.deallocate(tmp->m_val, 1);
                    m_nodeAlloc.deallocate(tmp, 1);
                } else {
                    // node has two children
                    Node * min = findMin(node->m_right);
                    value_type* tmp = node->value;
                    node->m_val = min->m_val;
                    min->m_val = tmp;
                    m_nodeAlloc.construct(min->m_val, *(node->m_val));
                    node->m_right = del(node->m_right, *(node->m_val), is_found);
                }
            }  else if (!key_compare(val.first, node->m_val->first)) {
                node->right = del(node->right, val, is_found);
            } else {
                node->left = del(node->left, val, is_found);
            }

            if (node == NULL)
                return NULL;

            return balanceTree(node, val);
        }

        bool erase( value_type const& val ) {
            bool is_found = false;
            m_root = del(m_root, val, is_found);
            return is_found;
        }

        Alloc getAllocator() const {
            return m_nodeAlloc;
        }

    };// class AvlTree

}// namespace ft


//TODO: only for debugging
template<typename T1, typename T2>
std::ostream&   operator<<( std::ostream& out, ft::AvlNode<T1, T2> const& obj ) {
    out << "[ height: " << obj.getHeight() << " , balance factor: " << obj.getBalanceFactor() << " , value: " << obj.m_val << " ]" << std::endl;

    return out;
}