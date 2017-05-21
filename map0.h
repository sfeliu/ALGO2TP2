/**
 * Para describir la complejidad temporal de las operaciones, vamos a llamar:
 *  - \SIZE(\a d): a la cantidad de elementos del diccionario \a d
 *  - \CMP(\a v1, \a v2): al costo de comparar dos valores \a v1 y \a v2
 *  - \CMP(\a d): al maximo costo posible para las comparaciones de elementos en \a d
 *  - \COPY(\a v): al costo de copiar un valor \a v
 *  - \COPY(\a d): a la sumatoria de los costo de copiar todos los elementos de \a d
 *  - \DEL(\a v): al costo de destruir un valor \a v
 *  - \DEL(\a d): a la sumatoria de los costos de destruir todos los elementos de \a d
 */

#ifndef MAP_H_
#define MAP_H_

#include <functional>
#include <iterator>
#include <utility>
#include <cassert>
#include <algorithm>

#ifdef DEBUG
#include <iostream>
#include <iomanip>
#endif

namespace aed2{

template<
  class Key,
  class Meaning,
  class Compare = std::less<Key>
>
class map {

	class Node;
	class InnerNode;

public:

    class iterator;
    class const_iterator;

    using key_type = Key;
    using mapped_type = Meaning;
    using value_type = std::pair<const Key, Meaning>;
    using key_compare = Compare;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using difference_type = std::ptrdiff_t;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;


    explicit map(Compare c = Compare()) {
        lt = c;
        count = 0;
        Node n = Node();
        header = n;
    }

// \complexity{\O(\COPY(\P{other}))}
    map(const map& other) {
    	//completar
    }

    template<class iterator>
    map(iterator first, iterator last, Compare c = Compare()) : lt(c) {
    	auto it = end();
    	while(first != last) {
    		insert(*first, it);
    		++first;
    	}
    }

// \complexity{\O(\DEL(\P{*this}) \PLUS \COPY(\P{other}))}
    map& operator=(map other) {
    	//completar
    }

// \complexity{\O(\DEL(\P{*this}))}
    ~map() {
        //completar
    }

// \complexity{\O(\LOG(\SIZE(\P{*this}) \CDOT \CMP(\P{*this}))}
    const Meaning& at(const Key& key) const {
    	//completar
    }

    Meaning& at(const Key& key) {
    	//completar
    }

// \complexity{\O(\LOG(\SIZE(\P{*this})) \CDOT \CMP(\P{*this}) + \a x) donde
// - \a x = 1 si def?(\a self, \P{key}), y
// - \a x = \a c en caso contrario.}
    Meaning& operator[](const Key& key) {
        iterator it = find(key);
        return it.n->value().second;
    }

    iterator find(const Key& key) {
        iterator it = iterator(header.parent);
        while(it.n != nullptr){
            if(it.n->key() == key){
                return it;
            }else{
                if(it.n->key() < key){
                    it.n = it.n->child[0];
                }else{
                    it.n = it.n->child[1];
                }
            }
        }
        it = iterator(&header);
        return it;
}

    const_iterator find(const Key& key) const {
        iterator it = iterator(header.parent);
        while(it.n != nullptr){
            if(it.n->key() == key){
                return it;
            }else{
                if(it.n->key() < key){
                    it.n = it.n->child[0];
                }else{
                    it.n = it.n->child[1];
                }
            }
        }
        it = iterator(&header);
        return it;
    }

// \complexity{\O(\LOG(\SIZE(\P{*this})) \CDOT \CMP(\P{*this}))}
    const_iterator lower_bound(const Key& key) const {
    	//completar
    }

    iterator lower_bound(const Key& key)  {
        //completar
    }

    bool empty() const {
        return header.parent == nullptr;
    }

    size_t size() const {
        return count;
    }

// \complexity{
//  - Peor caso: \O(\LOG(\SIZE(\P{*this})) \CDOT \CMP(\P{*this}) \PLUS \COPY(\P{value}))
//  - Si \P{hint} apunta al primer valor con clave al menos \P{value}.first (o \P{this}->end() en caso de no existir):
//  \O(\CMP(\P{*this}) \PLUS \COPY(\P{value})) amortizado.
// }
    iterator insert(const_iterator hint, const value_type& value) {
    	//completar
    }

    iterator insert(const value_type& value) {
    	//completar
    }

// \complexity{
//  - Peor caso: \O(\LOG(\SIZE(\P{*this})) \CDOT \CMP(\P{*this}) \PLUS \COPY(\P{value}))
//  - Si \P{hint} apunta al primer valor con clave al menos \P{value}.first (o \P{this}->end() en caso de no existir):
//  \O(\CMP(\P{*this}) \PLUS \COPY(\P{value})) amortizado.
// }
    iterator insert_or_assign(const_iterator hint, const value_type& value) {
    	//completar
    }

    iterator insert_or_assign(const value_type& value) {
    	//completar
    }

// \complexity{
// - Peor caso: \O(\DEL(\P{*pos}) + \LOG(\SIZE(\P{*this})))
// - Peor caso amortizado: \O(\DEL(\P{*pos}))
// }
    iterator erase(const_iterator pos) {
    	//completar
    }

// \complexity{\O(\DEL(\P{*pos}) + \LOG(\SIZE(\P{*this})) \CDOT \CMP(\P{*this}))}

    void erase(const Key& key) {
    	//completar
    }

// \complexity{\O(\DEL(\P{*this}))}
    void clear() {
        //completar
    }

    void swap(map& other) {
    	using std::swap;
        swap(lt, other.lt);
        swap(count, other.count);

        swap(header.parent, other.header.parent);
        swap(header.child[0], other.header.child[0]);
        swap(header.child[1], other.header.child[1]);
        if(root() != nullptr) root()->parent = &header;
        if(other.root() != nullptr) other.root()->parent = &other.header;

        if(root() == nullptr) header.child[0] = header.child[1] = &header;
        if(other.root() == nullptr) other.header.child[0] = other.header.child[1] = &other.header;
    }

    iterator begin() {
        iterator it = iterator(header.child[0]);
        return it;
    }

    const_iterator begin() const {
        const_iterator it = const_iterator(header.child[0]);
        return it;
    }

    const_iterator cbegin() {
        const_iterator it = const_iterator(header.child[0]);
        return it;
    }

    iterator end() {
        iterator it = iterator(header.child[1]);
        return it;
    }

    const_iterator end() const {
        const_iterator it = const_iterator(header.child[1]);
        return it;
    }

    const_iterator cend() {
        const_iterator it = const_iterator(header.child[1]);
        return it;
    }

    reverse_iterator rbegin() {
        reverse_iterator it = reverse_iterator(header.child[0]);
        return it;
    }

    const_reverse_iterator rbegin() const {
        const_reverse_iterator it = const_reverse_iterator(header.child[0]);
        return it;
    }

    const_reverse_iterator crbegin() {
        const_reverse_iterator it = const_reverse_iterator(header.child[0]);
        return it;
	}

    reverse_iterator rend() {
        reverse_iterator it = reverse_iterator(header.child[1]);
        return it;
    }

    const_reverse_iterator rend() const {
        const_reverse_iterator it = const_reverse_iterator(header.child[1]);
        return it;
    }

    const_reverse_iterator crend() {
        const_reverse_iterator it = const_reverse_iterator(header.child[1]);
        return it;
    }

    class iterator {

        using Node = typename map::Node;
        using InnerNode = typename map::InnerNode;

    public:

        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = map::value_type;
        using reference = map::reference;
        using pointer = map::pointer;
        using difference_type = std::ptrdiff_t;

        iterator() {}

        reference operator*() const {
            return n->value();
        }

        pointer operator->() const {
			return n;
		}

        iterator& operator++() {
            if(n->color == Color::Header){
                n = n->child[0];
            }else if(n->child[1] != nullptr){
                n->child[1].min();
            }else{
                Node* y = n->parent;
                while(y != nullptr and n == y->child[1]){
                    n = y;
                    y = y->parent;
                }
                n = y;
            }
            return this;
        }

        iterator operator++(int) {
            int i = 0;
            while(i < x){
                this++;
                i++;
            }
            return this;
        }

        iterator& operator--() {
            if(n->color == Color::Header){
                n = n->child[1];
            }else if(n->child[0] != nullptr){
                n->child[0].max();
            }else{
                Node* y = n->parent;
                while(y != nullptr and n == y->child[0]){
                    n = y;
                    y = y->parent;
                }
                n = y;
            }
            return this&;
        }

        iterator operator--(int) {
            int i = 0;
            while(i < x){
                this--;
                i++;
            }
            return this;
        }

        bool operator==(iterator other) const {
            return n == other.n;
        }

        bool operator!=(iterator other) const {
            return n != other.n;
        }

    private:

        iterator(Node* pos) : n(pos) {}
        operator Node*() const {return n;}
        Node* n{nullptr};
        friend class map;
    };

    class const_iterator {
        using Node = const typename map::Node;
        using InnerNode = const typename map::InnerNode;
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = map::value_type;
        using reference = map::const_reference;
        using pointer = map::const_pointer;
        using difference_type = std::ptrdiff_t;

        const_iterator() {}

        const_iterator(iterator it) {
            n = it.n;
        }

        reference operator*() const  {
            return n->value();
        }

        pointer operator->() const {
            return n;
        }

        const_iterator& operator++()  {
            if(n->color == Color::Header){
                n = n->child[0];
            }else if(n->child[1] != nullptr){
                n->child[1].min();
            }else{
                Node* y = n->parent;
                while(y != nullptr and n == y->child[1]){
                    n = y;
                    y = y->parent;
                }
                n = y;
            }
            return this&;
        }

        const_iterator operator++(int)  {
            int i = 0;
            while(i < x){
                this++;
                i++;
            }
            return this;
        }

        const_iterator& operator--()  {
            if(n->color == Color::Header){
                n = n->child[1];
            }else if(n->child[0] != nullptr){
                n->child[0].max();
            }else{
                Node* y = n->parent;
                while(y != nullptr and n == y->child[0]){
                    n = y;
                    y = y->parent;
                }
                n = y;
            }
            return this&;
        }

        const_iterator operator--(int)  {
            int i = 0;
            while(i < x){
                this--;
                i++;
            }
            return this;
        }

        bool operator==(const_iterator other) const  {
            return n == other.n;
        }

        bool operator!=(const_iterator other) const  {
            return n != other.n;
        }

    private:
        const_iterator(Node* pos) : n(pos) {}
        operator Node*() const {return n;}
        Node* n{nullptr};
        friend class map;
    };

private:

    friend class iterator;
    friend class const_iterator;

    enum class Color {Red, Black, Header};

    struct Node {
        Node* child[2]{nullptr,nullptr};
        Node* parent{nullptr};
        Color color{Color::Red};

        Node() : color(Color::Header) {
        	child[0] = child[1] = this;
        }

        Node(Node* p, Color c = Color::Red) : parent(p), color(c) {}

        virtual ~Node() {}

        bool is_header() const {
        	return color == Color::Header;
        }

        value_type& value() {
        	assert(not is_header());
        	return static_cast<InnerNode*>(this)->_value;
        }

        const value_type& value() const {
        	assert(not is_header());
        	return static_cast<const InnerNode*>(this)->_value;
        }

        const Key& key() const {
        	assert(not is_header());
        	return value().first;
        }

#ifdef DEBUG

        void print(int tab = 0) const {
        	std::cout << std::string(tab, ' ') << value().first << "->" << value().second << "   (" << (color == Color::Red ? "Red)" : "Black)") << std::endl;
        	if(child[0]) child[0]->print(tab + 2);
        	if(child[1]) child[1]->print(tab + 2);
        }

#endif
    };

    struct InnerNode : public Node {
        value_type _value;
    };

    Compare lt;

    size_t count{0};

    Node header;

    inline InnerNode* root() { return static_cast<InnerNode*>(header.parent); }

    inline const InnerNode* root() const { return static_cast<const InnerNode*>(header.parent); }
	//@}

    inline bool eq(const Key& k1, const Key& k2) const {
        return lt(k1, k2) == lt(k2, k1);
    }
};

template<class K, class V, class C>
bool operator==(const map<K, V, C>& m1, const map<K, V, C>& m2) {
	return m1.size() == m2.size() and std::equal(m1.begin(), m1.end(), m2.begin());
}

template<class K, class V, class C>
bool operator!=(const map<K, V, C>& m1, const map<K, V, C>& m2) {
	return not(m1 == m2);
}

template<class K, class V, class C>
bool operator<(const map<K, V, C>& m1, const map<K, V, C>& m2) {
	//completar.  Vale usar std::lexicographical_compare
}

template<class K, class V, class C>
bool operator>(const map<K, V, C>& m1, const map<K, V, C>& m2) {
	return m2 < m1;
}

template<class K, class V, class C>
bool operator<=(const map<K, V, C>& m1, const map<K, V, C>& m2) {
	return not(m2 < m1);
}

template<class K, class V, class C>
bool operator>=(const map<K, V, C>& m1, const map<K, V, C>& m2) {
	return !(m1 < m2);
}

template<class K, class V, class C>
void swap(map<K, V, C>& m1, map<K, V, C>& m2) {
	m1.swap(m2);
}
}

#endif /* MAP_H_ */