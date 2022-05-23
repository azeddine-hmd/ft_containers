#pragma once

#include "AvlTree.hpp"

namespace ft {


    template<
            typename Iter,
            typename Compare,
            typename Alloc
    >
    class MapIter {
    public:
        typedef Iter                                                        iterator_type;
        typedef typename iterator_traits<iterator_type>::iterator_category  iterator_category;
        typedef typename iterator_traits<iterator_type>::value_type         value_type;
        typedef typename iterator_traits<iterator_type>::difference_type    difference_type;
        typedef typename iterator_traits<iterator_type>::pointer            pointer;
        typedef value_type const *                                          const_pointer;
        typedef typename iterator_traits<iterator_type>::reference          reference;
        typedef value_type const &                                          const_reference;

    private:
        typedef AvlTree<value_type, Compare, Alloc>                         AvlTree;
        typedef AvlNode<value_type, Alloc>                                  AvlNode;

    private:
        pointer     m_ptr;
        AvlNode*    m_node;

    public:
        MapIter(): m_ptr(NULL), m_node(NULL) {

        }

        MapIter( pointer ptr, AvlNode* node = NULL ): m_ptr(ptr), m_node(*m_ptr) {

        }

        MapIter( MapIter& copy ) {
            *this = copy;
        }

        ~MapIter() {

        }

        MapIter&    operator=( MapIter const& rhs ) {
            m_ptr = rhs.m_ptr;
            m_node = rhs.m_node;

            return *this;
        }

        MapIter&    operator++() {
            if (!m_node)
                return *this;

            m_node = m_node->next();
            if (m_node) {
                m_ptr = m_node->m_val;
            } else {
                m_ptr = NULL;
            }

            return *this;
        }

        MapIter     operator++( int ) {
            MapIter tmp = *this;
            ++(*this);
            return tmp;
        }

        MapIter&    operator--() {
            if (!m_ptr) {
                AvlNode * max = AvlTree(m_node->getRoot()).findMax();
                if (max) {
                    m_node = max;
                    m_ptr = max->m_val;
                }

                return *this;
            }
        }

        MapIter     operator--( int ) {
            MapIter tmp = *this;
            --(*this);
            return tmp;
        }

        difference_type operator-( MapIter src ) const {
            return m_ptr - src.m_ptr;
        }

        reference operator*() const {
            return *m_ptr;
        }

        pointer operator->() const {
            return m_ptr;
        }

        bool operator==( MapIter const& other) {
            return m_ptr == other.m_ptr || (m_ptr && other.m_ptr && m_ptr->first == other.m_ptr->first);
        }

        bool operator!=( MapIter const& other ) {
            return !(this == other);
        }

    }; // class MapIter

    template <
            typename Key,
            typename T,
            typename Compare = std::less<Key>,
            typename Alloc = std::allocator<ft::pair<Key,T> >
    >
    class Map {
    public:
        typedef Key                                                     key_type;
        typedef T                                                       mapped_type;
        typedef Compare                                                 key_compare;
        typedef pair<key_type, mapped_type>                             value_type;
        typedef std::size_t                                             size_type;
        typedef std::ptrdiff_t                                          difference_type;

        typedef Alloc                                                   allocator_type;
        typedef typename allocator_type::reference                      reference;
        typedef typename allocator_type::const_reference                const_reference;
        typedef typename allocator_type::pointer                        pointer;
        typedef typename allocator_type::const_pointer                  const_pointer;

        typedef typename ft::MapIter<pointer, Compare, Alloc>           iterator;
        typedef typename ft::MapIter<const_pointer, Compare, Alloc>     const_iterator;
        typedef typename ft::reverse_iterator<iterator>                 reverse_iterator;
        typedef typename ft::reverse_iterator<const_iterator>           const_reverse_iterator;

    private:

    }; // class map

} // namespace ft