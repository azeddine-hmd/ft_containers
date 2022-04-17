#pragma once

#include "pair.hpp"

namespace ft {

    template<typename T,
            typename Alloc = std::allocator<T>
            >
    class AvlNode {
    public:
        typedef T   value_type;
    private:
        Alloc       m_alloc;
        T           m_val;
        AvlNode     *m_right;
        AvlNode     *m_left;
        int         m_height;

        AvlNode() {}
    public:
        AvlNode( const T& val ) {
            m_val = m_alloc.allocate(1);
            m_alloc.construct(m_val, val);
            m_right = m_left = NULL;
            m_height = 1;
        }

        int balanceFactor() {
            if (!m_left && !m_right) {
                return 0;
            } else if (!m_left) {
                return -m_right->m_height;
            } else if (!m_right) {
                return m_left->m_height;
            } else {
                return m_left->m_height - m_right->m_height;
            }
        }

        int getHeight() const {
            return m_height;
        }

        void updateHeight() {
            if (!m_left && !m_right) {
                m_height = 0;
            } else if (!m_left) {
                m_height = m_right->m_height;
            } else if (!m_right) {
                m_height = m_left->m_height;
            } else {
                return std::max(m_left->m_height, m_right->m_height);
            }
        }

//        void addChildNode(AvlNode* node) const {
//            //TODO: add left node then update height etc...
//            updateHeight();
//        }
    }; // class AvlTree

    template<
            typename T,
            typename Compare = std::less<T>,
            typename Alloc = std::allocator<T>
    >
    class AvlTree {
    public:
        typedef T                                               value_type;
        typedef typename Alloc::template rebind<AvlTree>::other node_allocator;
    private:
        node_allocator      m_nodeAlloc;
        Compare             cmp;
        AvlNode<T, Alloc>*  m_root;
    public:
        AvlTree(): m_root(NULL) {

        }
    };// class AvlTree

}// namespace ft
