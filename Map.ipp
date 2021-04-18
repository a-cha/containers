//
// Created by Skipjack Adolph on 4/16/21.
//

#pragma once


#include "Map.hpp"

namespace ft {

/**	COPLIEN FORM					**/
#pragma region Coplien

	template<class Key, class T, class Compare, class Alloc>
	Map<Key, T, Compare, Alloc>::Map(const Map & other) :
		_alloc(other._alloc),
		_key_comp(other._key_comp),
		_init_node() {
		_begin_node = initNode();
			_end_node = initNode();
		_size = 0;
		linkTreeDefault();
			insert(other.begin(), other.end());
		}

	template<class Key, class T, class Compare, class Alloc>
	Map<Key, T, Compare, Alloc> & Map<Key, T, Compare, Alloc>::operator=(const Map & other) {
		if (this == &other)
			return *this;
		clear();
		insert(other.begin(), other.end());
		return *this;
	}

	template<class Key, class T, class Compare, class Alloc>
	Map<Key, T, Compare, Alloc>::~Map() {
		clear();
		removeNode(_begin_node);
		removeNode(_end_node);
	}
#pragma endregion

/**	CONSTRUCTORS					**/
#pragma region Constructors

	template<class Key, class T, class Compare, class Alloc>
	Map<Key, T, Compare, Alloc>::Map(const key_compare &comp,
									 const allocator_type &alloc) :
		_alloc(alloc),
		_key_comp(comp),
		_init_node() {
			_begin_node = initNode();
			_end_node = initNode();
			_size = 0;
		linkTreeDefault();
		}

	template<class Key, class T, class Compare, class Alloc>
	template<class InputIterator>
	Map<Key, T, Compare, Alloc>::Map(InputIterator first, InputIterator last,
									 const key_compare &comp,
									 const allocator_type &alloc) :
		_alloc(alloc),
		_key_comp(comp),
		_init_node() {
			_begin_node = initNode();
			_end_node = initNode();
			_size = 0;
		linkTreeDefault();
			insert(first, last);
		}
#pragma endregion

/**	METHODS							**/
#pragma region Iterators

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::iterator Map<Key, T, Compare, Alloc>::begin() {
		return ++iterator(_begin_node);
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::const_iterator Map<Key, T, Compare, Alloc>::begin() const {
		return ++const_iterator(_begin_node);
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::iterator Map<Key, T, Compare, Alloc>::end() {
		return iterator (_end_node);
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::const_iterator Map<Key, T, Compare, Alloc>::end() const {
		return const_iterator(_end_node);
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::reverse_iterator Map<Key, T, Compare, Alloc>::rbegin() {
		return reverse_iterator(end());
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::const_reverse_iterator Map<Key, T, Compare, Alloc>::rbegin() const {
		return const_reverse_iterator(end());
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::reverse_iterator Map<Key, T, Compare, Alloc>::rend() {
		return reverse_iterator (begin());
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::const_reverse_iterator Map<Key, T, Compare, Alloc>::rend() const {
		return const_reverse_iterator (begin());
	}
#pragma endregion

#pragma region Capacity
	template<class Key, class T, class Compare, class Alloc>
	bool Map<Key, T, Compare, Alloc>::empty() const {
		return _size == 0;
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::size_type Map<Key, T, Compare, Alloc>
	        ::size() const {
		return _size;
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::size_type Map<Key, T, Compare, Alloc>
	        ::max_size() const {
		return std::numeric_limits<size_type>::max() / sizeof(node);
	}
#pragma endregion

#pragma region Element access

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::mapped_type & Map<Key, T, Compare, Alloc>
	        ::operator[](const key_type & k) {
		node *	tmp;

		tmp = treeFindRec(_init_node, k);
		if (tmp == NULL || tmp->_data.first != k) {
			value_type val(k, mapped_type());
			iterator it = insert(val).first;
			return (*it).second;
		}
		iterator res(tmp);
		return (*res).second;
	}
#pragma endregion

#pragma region Modifiers

	template<class Key, class T, class Compare, class Alloc>
	ft::pair<typename Map<Key, T, Compare, Alloc>::iterator, bool>
	Map<Key, T, Compare, Alloc>::insert(const Map::value_type &val) {
		node * newNode;
		node * tmp;

		newNode = makeNode(val);
		tmp = pushNode(_init_node, newNode);
		if (tmp != newNode) {
			_alloc.destroy(newNode);
			_alloc.deallocate(newNode, 1);
			return ft::pair<iterator,bool>(tmp, false);
		}
		++_size;
		return ft::pair<iterator,bool>(iterator(newNode), true);
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::iterator Map<Key, T, Compare, Alloc>
	        ::insert(Map::iterator pos, const Map::value_type &val) {
		if (pos._data != _begin_node
			&& pos._data != _end_node
			&& ((_val_comp(val, pos.next_node()->_data)
			&& _val_comp(pos.prev_node()->_data, val))))
		{
			node* tmp = makeNode(val);
			node* newNode = pushNode(pos._data, tmp);
			if (newNode != tmp) {
				_alloc.destroy(tmp);
				_alloc.deallocate(tmp, 1);
				return iterator(newNode);
			}
			++_size;
			return iterator(tmp);
		}
		else
			return insert(val).first;
	}

	template<class Key, class T, class Compare, class Alloc>
	template<class InputIterator>
	void Map<Key, T, Compare, Alloc>
			::insert(InputIterator first, InputIterator last) {
		while (first != last) {
			insert(*first);
			++first;
		}
	}

//	todo: how it works?
	template<class Key, class T, class Compare, class Alloc>
	void Map<Key, T, Compare, Alloc>::erase(Map::iterator pos) {
		erase(pos._data->_data.first);
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::size_type Map<Key, T, Compare, Alloc>
	        ::erase(const key_type & k) {
		if (DeletingNode(k)) {
			--_size;
			return (1);
		} else
			return 0;
	}

	template<class Key, class T, class Compare, class Alloc>
	void Map<Key, T, Compare, Alloc>
	        ::erase(Map::iterator first, Map::iterator last) {
		iterator tmp;
		while (first != last) {
			tmp = first;
			++first;
			erase(tmp._data->_data.first);
		}
	}

	template<class Key, class T, class Compare, class Alloc>
	void Map<Key, T, Compare, Alloc>::swap(Map & x) {
		ft::swap(_alloc, x._alloc);
		ft::swap(_init_node, x._init_node);
		ft::swap(_begin_node, x._begin_node);
		ft::swap(_end_node, x._end_node);
		ft::swap(_size, x._size);
	}

	template<class Key, class T, class Compare, class Alloc>
	void Map<Key, T, Compare, Alloc>::clear() {
		erase(begin(), end());
	}
#pragma endregion

#pragma region Observers

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::key_compare Map<Key, T, Compare, Alloc>
	        ::key_comp() const {
		return _key_comp;
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::value_compare Map<Key, T, Compare, Alloc>
	        ::value_comp() const {
		return _val_comp;
	}
#pragma endregion

#pragma region Operations

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::iterator Map<Key, T, Compare, Alloc>
	        ::find(const key_type &k) {
		node * tmp;

		unlinkTree();
		tmp = treeFindRec(_init_node, k);
		linkTreeDefault();
		if (tmp == NULL)
			return iterator(end());
		return iterator(tmp);
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::const_iterator Map<Key, T, Compare, Alloc>
	        ::find(const key_type &k) const {
		node * tmp;

		unlinkTree();
		tmp = treeFindRec(_init_node, k);
		linkTreeDefault();
		if (tmp == NULL)
			return const_iterator(end());
		return const_iterator(tmp);
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::size_type Map<Key, T, Compare, Alloc>
	        ::count(const key_type &k) const {
		return ((find(k) == end()) ? 0 : 1);
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::iterator Map<Key, T, Compare, Alloc>
	        ::lower_bound(const key_type &k) {
		node * tmp;

		unlinkTree();
		tmp = FIND_NEAR(_init_node, k);
		linkTreeDefault();
		if (k > tmp->_data.first)
			return ++iterator(tmp);
		return iterator(tmp);
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::const_iterator Map<Key, T, Compare, Alloc>
	        ::lower_bound(const key_type &k) const {
		node * tmp;

		unlinkTree();
		tmp = FIND_NEAR(_init_node, k);
		linkTreeDefault();
		if (k > tmp->_data.first)
			return ++const_iterator(tmp);
		return const_iterator(tmp);
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::iterator Map<Key, T, Compare, Alloc>
	        ::upper_bound(const key_type &k) {
		iterator tmp = lower_bound(k);
		if ((*tmp).first <= k)
			++tmp;
		return tmp;
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::const_iterator Map<Key, T, Compare, Alloc>
	        ::upper_bound(const key_type &k) const {
		const_iterator tmp = lower_bound(k);
		if ((*tmp).first <= k)
			++tmp;
		return tmp;
	}

	template<class Key, class T, class Compare, class Alloc>
	pair <typename Map<Key, T, Compare, Alloc>::iterator,
			typename Map<Key, T, Compare, Alloc>::iterator>
	Map<Key, T, Compare, Alloc>::equal_range(const key_type &k) {
		return pair<iterator, iterator>();
	}

	template<class Key, class T, class Compare, class Alloc>
	pair <typename Map<Key, T, Compare, Alloc>::const_iterator,
			typename Map<Key, T, Compare, Alloc>::const_iterator>
	Map<Key, T, Compare, Alloc>::equal_range(const key_type &k) const {
		return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
	}
#pragma endregion

}
