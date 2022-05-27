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
        value_type* m_val;
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

        AvlNode( AvlNode const& other ) {
            *this = other;
        }

        AvlNode&    operator=( AvlNode const& rhs ) {
            if (this != &rhs) {
                m_right = rhs.m_right;
                m_left = rhs.m_left;
                m_parent = rhs.m_parent;
                m_height = rhs.m_height;
                if (m_val) {
                    m_alloc.destroy(m_val);
                    m_alloc.deallocate(m_val, 1);
                    m_val = NULL;
                }
                m_val = m_alloc.allocate(1);
                m_alloc.construct(m_val, *(rhs.m_val));
            }

            return *this;
        }

        int getHeight(AvlNode* node) const {
            if (node == NULL) return 0;
            return node->m_height;
        }

        int getBalanceFactor() const {
            return (getHeight(m_left) - getHeight(m_right));
        }

        void updateHeight() {
            m_height = std::max(getHeight(m_left), getHeight(m_right)) + 1;
        }

        AvlNode* next() {
            AvlNode * curr = this;

            if (!curr) {
                return NULL;
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
                while (curr->m_left)
                    curr = curr->m_left;
            }

            return curr;
        }

        AvlNode* previous(bool rootExist) {
            AvlNode * curr = this;

            if (!rootExist)
                return NULL;

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

        operator AvlNode<const value_type, Alloc> () const {
            return AvlNode<const value_type, Alloc>();
        }

    }; // class AvlNode

    template<
            typename T,
            typename Compare = std::less<T>,
            typename Alloc = std::allocator<T>
    >
    class AvlTree {

    public:
        typedef T                                                   value_type;
        typedef AvlNode<value_type, Alloc>                          NodeType;
        typedef Alloc                                               value_allocator;
        typedef typename Alloc::template rebind<NodeType>::other    node_allocator;


        NodeType*               m_root;

    private:
        node_allocator      m_nodeAlloc;
        value_allocator     m_valueAlloc;
        Compare             keyCompare;


    public:
        AvlTree(): m_root(NULL) {

        }

        AvlTree( T const& val ) {
            m_root = makeNode(val);
        }

        AvlTree(AvlTree const& other) {
            m_root = other->m_root;
        }

        AvlTree(NodeType* root) {
            m_root(root);
        }

        ~AvlTree() {

        }

        AvlTree& operator=( AvlTree const& rhs ) {
            m_root = rhs.m_root;
            return *this;
        }

        NodeType* insert( T const& val ) {
            NodeType * new_node = makeNode(val);
            m_root = insertNode(m_root, new_node);
            return new_node;
        }

        NodeType* find(NodeType* current, const value_type& val ) const {
            if (!current || current->m_val->first == val.first) {
                return current;
            }
            if (!keyCompare(val.first, current->m_val->first)) {
                return find(current->m_right, val);
            } else {
                return find(current->m_left, val);
            }
        }

        NodeType* search(value_type const& val ) const {
            return find(m_root, val);
        }

        NodeType* findMin(NodeType* node) const {
            if (!node)
                return NULL;
            NodeType * min = node;
            while (min->m_left)
                min = min->m_left;
            return min;
        }

        NodeType* findMax(NodeType* node) const {
            if (!node)
                return NULL;
            NodeType * max = node;
            while (max->m_right)
                max = max->m_right;
            return max;
        }

        NodeType* del(NodeType* node, value_type const& val, bool& is_found ) {
            if (!node)
                return NULL;

            if (val.first == node->m_val->first) {
                is_found = true;
                // node have only one child right or left
                if (!node->m_right || !node->m_left) {
                    NodeType * tmp = node->m_right ? node->m_right : node->m_left;

                    // node have no child
                    if (!tmp) {
                        tmp = node;
                        node = NULL;
                    } else {
                        // node have one child
                        NodeType * nodeParent = node->m_parent;
                        *node = *tmp;
                        node->m_parent = nodeParent;
                    }
                    m_valueAlloc.deallocate(tmp->m_val, 1);
                    m_nodeAlloc.deallocate(tmp, 1);
                } else {
                    // node has two children
                    NodeType * min = findMin(node->m_right);
                    value_type* tmp = node->m_val;
                    node->m_val = min->m_val;
                    min->m_val = tmp;
                    m_valueAlloc.construct(min->m_val, *(node->m_val));
                    node->m_right = del(node->m_right, *(node->m_val), is_found);
                }
            }  else if (!keyCompare(val.first, node->m_val->first)) {

                node->m_right = del(node->m_right, val, is_found);
            } else {
                node->m_left = del(node->m_left, val, is_found);
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

        Alloc get_allocator() const {
            return m_nodeAlloc;
        }

        NodeType* iter( NodeType* node, value_type min, value_type max, bool isLast, int& n ) {
            if (!node)
                return NULL;

            node->m_left = iter(node->m_left, min, max, isLast, n);
            node->m_right = iter(node->m_right, min, max, isLast, n);

            if (node->m_val->first >= min.first && (isLast || max.first > node->m_val->first)) {
                bool is_found = false;
                node = del(node, *(node->m_val), is_found);
                if (is_found)
                    n++;
            }
            return node;
        }

        void clear(NodeType* node) {
            if (!node)
                return;
            clear(node->m_left);
            m_valueAlloc.deallocate(node->m_val, 1);
            clear(node->m_right);
            m_nodeAlloc.deallocate(node, 1);
            node = NULL;
        }

        void copy( NodeType* node ) {
            if (!node)
                return;
            copy(node->m_left);
            if (node->m_val)
                insert(*(node->m_val));
            copy(node->m_right);
        }

        operator AvlTree<const value_type, Compare, Alloc> () const {
            return AvlTree<const value_type, Compare, Alloc>();
        }

    private:
        NodeType*   makeNode(T const& val ) {
            NodeType * node = m_nodeAlloc.allocate(1);
            m_nodeAlloc.construct(node, val);
            return node;
        }

        NodeType* rotateLeft(NodeType* x ) {
            NodeType* y = x->m_right;

            if (!y)
                return NULL;

            NodeType* z = y->m_left;
            if (z)
                z->m_parent = x;


            y->m_left = x;
            x->m_right = z;

            y->m_parent = x->m_parent;
            x->m_parent = y;

            x->updateHeight();
            y->updateHeight();

            return y;
        }

        NodeType* rotateRight(NodeType* y ) {
            NodeType* x = y->m_left;

            if (!x)
                return NULL;

            NodeType* z = x->m_right;
            if (z)
                z->m_parent = y;

            x->m_right = y;
            y->m_left = z;

            x->m_parent = y->m_parent;
            y->m_parent = x;

            x->updateHeight();
            y->updateHeight();

            return x;
        }

        NodeType* balanceTree(NodeType* current, const value_type& val ) {
            current->updateHeight();

            int balanceFactor = current->getBalanceFactor();
            if (balanceFactor > 1) {
                if (keyCompare(val.first, current->m_left->m_val->first)) {
                    return rotateRight(current);
                } else {
                    current->m_left = rotateLeft(current->m_left);
                    return rotateRight(current);
                }
            } else if (balanceFactor < -1) {
                if (!keyCompare(val.first, current->m_right->m_val->first)) {
                    return rotateLeft(current);
                } else {
                    current->m_right = rotateRight(current->m_right);
                    return rotateLeft(current);
                }
            }

            return current;
        }

        NodeType* insertNode(NodeType* current, NodeType* newNode ) {
            if (!current)
                return newNode;
            if (!keyCompare(newNode->m_val->first, current->m_val->first)) {
                current->m_right = insertNode(current->m_right, newNode);
                if (current->m_right)
                    current->m_right->m_parent = current;
            } else if (keyCompare(newNode->m_val->first, current->m_val->first)) {
                current->m_left = insertNode(current->m_left, newNode);
                if (current->m_left)
                    current->m_left->m_parent = current;
            }

            return balanceTree(current, *(newNode->m_val));
        }
    };// class AvlTree
}// namespace ft
