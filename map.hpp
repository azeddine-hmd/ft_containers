#pragma once

#include "AvlTree.hpp"
#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"

namespace ft {

    template<
            typename T,
            typename Compare,
            typename Alloc
    >
    class MapIter {
    public:
        typedef T                                       value_type;
        typedef ptrdiff_t                               difference_type;
        typedef T*                                      pointer;
        typedef T&                                      reference;
        typedef std::bidirectional_iterator_tag         iterator_category;

    private:
        typedef AvlTree<value_type, Compare, Alloc>     TreeType;
        typedef AvlNode<value_type, Alloc>              NodeType;

    private:
        pointer         m_ptr;
        TreeType const* m_tree;

    public:
        MapIter( pointer ptr, TreeType const* tree = NULL ): m_ptr(ptr) {
            m_tree = tree;
        }

        MapIter() {
            m_ptr = NULL;
        }

        MapIter( MapIter const& copy ) {
            *this = copy;
        }

        ~MapIter() {

        }

        MapIter&    operator=( MapIter const& rhs ) {
            m_ptr = rhs.m_ptr;
            m_tree = rhs.m_tree;

            return *this;
        }

        MapIter&    operator++() {
            NodeType * curr = m_tree->search(*m_ptr);
            if (!curr)
                return *this;

            NodeType * nextNode = curr->next();
            if (nextNode) {
                m_ptr = nextNode->m_val;
            } else {
                m_ptr = NULL;
            }

            return *this;
        }


        operator MapIter<const T, Compare, Alloc> () const {
            return MapIter<const T, Compare, Alloc>(m_ptr, reinterpret_cast<const AvlTree<const T, Compare, Alloc>*>(m_tree));
        }


        MapIter     operator++( int ) {
            MapIter tmp = *this;
            ++(*this);
            return tmp;
        }

        MapIter&    operator--() {
            if (!m_ptr) {
                NodeType * max = m_tree->findMax(m_tree->m_root);
                if (max) {
                    m_ptr = max->m_val;
                }

                return *this;
            }

            NodeType* curr = m_tree->search(*m_ptr);
            if (!curr) {
                return *this;
            }

            NodeType * previousNode = curr->previous(m_tree->m_root);
            if (previousNode) {
                m_ptr = previousNode->m_val;
            } else {
                m_ptr = NULL;
            }

            return *this;
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

        friend bool operator==( MapIter const& lhs, MapIter const& rhs ) {
            return lhs.m_ptr == rhs.m_ptr || (lhs.m_ptr && rhs.m_ptr && lhs.m_ptr->first == rhs.m_ptr->first);
        }

        friend bool operator!=( MapIter const& lhs, MapIter const& rhs ) {
            return !(lhs == rhs);
        }
    }; // class MapIter

    template <
            typename Key,
            typename T,
            typename Compare = std::less<Key>,
            typename Alloc = std::allocator<pair<const Key,T> >
    >
    class map {

    public:
        typedef Key                                                     key_type;
        typedef T                                                       mapped_type;
        typedef Compare                                                 key_compare;
        typedef pair<const key_type, mapped_type>                       value_type;
        typedef std::size_t                                             size_type;
        typedef std::ptrdiff_t                                          difference_type;

        typedef Alloc                                                   allocator_type;
        typedef typename allocator_type::reference                      reference;
        typedef typename allocator_type::const_reference                const_reference;
        typedef typename allocator_type::pointer                        pointer;
        typedef typename allocator_type::const_pointer                  const_pointer;

        typedef ft::MapIter<value_type, Compare, Alloc>                 iterator;
        typedef ft::MapIter<const value_type, Compare, Alloc>           const_iterator;
        typedef ft::reverse_iterator<iterator>                          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;

    private:
        typedef AvlTree<value_type, Compare, Alloc>                     TreeType;
        typedef AvlNode<value_type, Alloc>                              NodeType;

        size_type       m_size;
        size_type       m_capacity;
        allocator_type  m_alloc;
        key_compare     keyCompare;
        TreeType        m_tree;


    public:

        explicit map(
                key_compare const& comp = key_compare(),
                allocator_type const& alloc = allocator_type()
        ) {
            m_size = 0;
            m_alloc = alloc;
            keyCompare = comp;
        }

        template<typename InputIter>
        map(
                InputIter first,
                InputIter last,
                key_compare const& comp = key_compare(),
                allocator_type const& alloc = allocator_type()
        ) {
            m_size = 0;
            insertIters(first, last);
            keyCompare = comp;
            m_alloc = alloc;
        }

        map( map const& other ) {
            *this = other;
        }

        ~map() {
            clear();
        }

        map& operator=( map const& rhs ) {
            clear();
            m_tree.copy(rhs.m_tree.m_root);
            m_size = rhs.m_size;
            return *this;
        }

        pair<iterator, bool> insert( value_type const& val ) {
            pair<iterator, bool> res;
            NodeType * node = m_tree.search(val);
            if (!node) {
                node = m_tree.insert(val);
                res.second = true;
                m_size++;
            }
            res.first = iterator(node->m_val);
            return res;
        }

        iterator insert( iterator position, value_type const& val ) {
            (void)position;
            return insert(val).first;
        }

        template<typename InputIter>
        void insert( InputIter first, InputIter last ) {
            insertIters(first, last);
        }

        size_type   erase( key_type const& key ) {
            return m_tree.erase(ft::make_pair(key, mapped_type())) && m_size--;
        }

        void erase( iterator position ) {
            m_tree.erase(*position) && m_size--;
        }

        void erase( iterator first, iterator last ) {
            if (first == last)
                return;
            value_type min = *first;
            int n = 0;
            if (last != end()) {
                m_tree.m_root = m_tree.iter(m_tree.m_root, min, *last, false, n);
            } else {
                m_tree.m_root = m_tree.iter(m_tree.m_root, min, value_type(), true, n);
            }
            m_size -= n;
        }

        iterator find( key_type const& key ) {
            NodeType * res = m_tree.search(ft::make_pair(key, mapped_type()));
            return iterator(res ? res->m_val : NULL, &m_tree);
        }

        const_iterator find( key_type const& key ) const {
            NodeType * res = m_tree.search(make_pair(key, mapped_type()));
            return const_iterator(res ? res->m_val : NULL, &m_tree);

        }

        size_type count( key_type const& key ) const {
            if (m_tree.search(ft::make_pair(key, mapped_type())) != NULL)
                return 1;
            else
                return 0;
        }

        iterator lower_bound( key_type const& key ) {
            NodeType * bound = NULL;
            bound = findBound2(m_tree.m_root, key, bound);
            return iterator(bound ? bound->m_val : NULL, &m_tree);
        }

        iterator upper_bound( key_type const& key ) {
            NodeType * bound = NULL;
            bound = findBound(m_tree.m_root, key, bound);
            return iterator(bound ? bound->m_val : NULL, &m_tree);
        }

        const_iterator lower_bound( key_type const& key ) const {
            NodeType * bound = NULL;
            bound = findBound2(m_tree.m_root, key, bound);
            return iterator(bound ? bound->m_val : NULL, &m_tree);
        }

        const_iterator upper_bound( key_type const& key ) const {
            NodeType * bound = NULL;
            bound = findBound(m_tree.m_root, key, bound);
            return iterator(bound ? bound->m_val : NULL, &m_tree);
        }

        pair<iterator, iterator> equal_range( key_type const& key ) {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }

        pair<const_iterator, const_iterator> equal_range( key_type const& key ) const {
            return ft::make_pair(lower_bound(key), upper_bound(key));
        }

        void swap( map& other ) {
            map tmp;

            tmp.assignMemberData(*this);
            assignMemberData(other);
            other.assignMemberData(tmp);

            tmp.resetMap();
        }

        struct value_compare {
           typedef bool             result_type;
           typedef value_type       first_argument_type;
           typedef value_type       second_argument_type;

            Compare comp;

            value_compare( Compare c ): comp(c) {

            }

            bool operator()( value_type const& x, value_type const& y ) const {
                return comp(x.first, y.first);
            }
        };

        value_compare value_comp() const {
            return value_compare(keyCompare);
        }

        mapped_type&    operator[]( key_type const& key ) {
            value_type toFind = ft::make_pair(key, mapped_type());

            NodeType * res = m_tree.search(toFind);

            if (!res) {
                m_size++;
                res = m_tree.insert(toFind);
            }

            return res->m_val->second;
        }

        size_type max_size() const {
            return m_tree.get_allocator().max_size();
        }

        size_type size() const {
            return m_size;
        }

        bool empty() const {
            return size() == 0;
        }

        allocator_type get_allocator() const {
            return m_alloc;
        }

        key_compare key_comp() const {
            return keyCompare;
        }

        iterator begin() {
            NodeType * min = m_tree.findMin(m_tree.m_root);
            if (!min)
                return iterator(NULL, &m_tree);
            return iterator(min->m_val, &m_tree);
        }

        const_iterator begin() const {
            NodeType * min = m_tree.findMin(m_tree.m_root);
            if (!min)
                return iterator(NULL, &m_tree);
            return iterator(min->m_val, &m_tree);
        }

        iterator end() {
            return iterator(NULL, &m_tree);
        }

        const_iterator end() const {
            return iterator(NULL, &m_tree);
        }

        reverse_iterator rbegin() {
            return reverse_iterator(iterator(NULL, &m_tree));
        }

        const_reverse_iterator rbegin() const {
            return reverse_iterator(iterator(NULL, &m_tree));
        }

        reverse_iterator rend() {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const {
            NodeType * min = m_tree.findMin(m_tree.m_root);
            if (!min)
                return reverse_iterator(iterator(NULL, &m_tree));
            return reverse_iterator(iterator(min->m_val, &m_tree));
        }

        void clear() {
            m_tree.clear(m_tree.m_root);
            m_tree.m_root = NULL;
            m_size = 0;
        }

    private:

        template<typename InputIter>
        void insertIters( InputIter first, InputIter last ) {
            while (first != last)
                insert(*first++);
        }

        void assignMemberData( map const& other ) {
            m_tree.m_root = other.m_tree.m_root;
            m_size = other.m_size;
            m_alloc = other.m_alloc;
            m_capacity = other.m_capacity;
        }

        void resetMap() {
            m_tree.m_root = NULL;
            m_size = 0;
        }

        NodeType*    findBound(NodeType* node, key_type const& key, NodeType* bound) const {
            if (!node)
                return bound;

            if ( keyCompare(key, node->m_val->first) && (!bound || !keyCompare(bound->m_val->first, node->m_val->first)) ) {
                bound = node;
            }

            if (!keyCompare(key, node->m_val->first))
                return findBound(node->m_right, key, bound);
            else
                return findBound(node->m_left, key, bound);
        }

        NodeType*    findBound2(NodeType* node, key_type const& key, NodeType* bound) const {
            if (!node)
                return bound;

            if (!keyCompare(node->m_val->first, key) && (!bound || !keyCompare(bound->m_val->first, node->m_val->first)) ) {
                bound = node;
            }

            if (!keyCompare(key, node->m_val->first))
                return findBound2(node->m_right, key, bound);
            else
                return findBound2(node->m_left, key, bound);
        }

    }; // class map

    template<typename Key, typename T, typename Compare, typename Alloc>
    bool operator==( map<Key,T,Compare,Alloc> const& lhs, map<Key,T,Compare,Alloc> const& rhs ) {
        if (lhs.size() != rhs.size())
            return false;
        return (equal(lhs.begin(), lhs.end(), rhs.begin()));
    }

    template<typename Key, typename T, typename Compare, typename Alloc>
    bool operator!=( map<Key,T,Compare,Alloc> const& lhs, map<Key,T,Compare,Alloc> const& rhs ) {
        return !(lhs == rhs);
    }

    template<typename Key, typename T, typename Compare, typename Alloc>
    bool operator<( map<Key,T,Compare,Alloc> const& lhs, map<Key,T,Compare,Alloc> const& rhs ) {
        if (rhs == lhs)
            return false;
        return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

    template<typename Key, typename T, typename Compare, typename Alloc>
    bool operator<=( map<Key,T,Compare,Alloc> const& lhs, map<Key,T,Compare,Alloc> const& rhs ) {
        return ((lhs == rhs) || operator<(lhs, rhs));
    }

    template<typename Key, typename T, typename Compare, typename Alloc>
    bool operator>( map<Key,T,Compare,Alloc> const& lhs, map<Key,T,Compare,Alloc> const& rhs ) {
        if (lhs == rhs)
            return false;
        return (!operator<(lhs, rhs));
    }

    template<typename Key, typename T, typename Compare, typename Alloc>
    bool operator>=( map<Key,T,Compare,Alloc> const& lhs, map<Key,T,Compare,Alloc> const& rhs ) {
        return (lhs == rhs || operator>(lhs, rhs));
    }

} // namespace ft