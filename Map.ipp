//
// Created by Skipjack Adolph on 4/16/21.
//

#pragma once

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
		return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
	}

	template<class Key, class T, class Compare, class Alloc>
	pair <typename Map<Key, T, Compare, Alloc>::const_iterator,
			typename Map<Key, T, Compare, Alloc>::const_iterator>
	Map<Key, T, Compare, Alloc>::equal_range(const key_type &k) const {
		return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
	}
#pragma endregion

/**	OPERATORS						**/
#pragma region Operators

	template <class T1, class T2>
	bool operator==(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs) {
		return lhs.first==rhs.first && lhs.second==rhs.second;
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs) {
		return !(lhs==rhs);
	}

	template <class T1, class T2>
	bool operator<(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs) {
		return lhs.first<rhs.first;
	}

	template <class T1, class T2>
	bool operator<=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs) {
		return !(rhs<lhs);
	}

	template <class T1, class T2>
	bool operator>(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs) {
		return rhs<lhs;
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs) {
		return !(lhs<rhs);
	}
#pragma endregion

/**	UTILS							**/
#pragma region Node

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::pointer Map<Key, T, Compare, Alloc>
	        ::initNode() {
		node * new_node;

		new_node = _alloc.allocate(1);
		_alloc.construct(new_node, node_type());
		new_node->_parent = 0;
		new_node->_left = 0;
		new_node->_right = 0;
		new_node->_height = 0;
		return (new_node);
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::pointer Map<Key, T, Compare, Alloc>
	        ::makeNode(const Map::value_type &data) {
		node * new_node;

		new_node = _alloc.allocate(1);
		_alloc.construct(new_node, data);
		return (new_node);
	}

	template<class Key, class T, class Compare, class Alloc>
	void Map<Key, T, Compare, Alloc>::removeNode(Map::node *other) {
		_alloc.destroy(other);
		_alloc.deallocate(other, 1);
	}
#pragma endregion

#pragma region Tree

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::node *Map<Key, T, Compare, Alloc>
	        ::treeAdd(Map::node *current, Map::node *new_node) {
		if (_val_comp(new_node->_data, current->_data)) {
			if (current->_left)
				new_node = treeAdd(current->_left, new_node);
			else {
				new_node->_parent = current;
				current->_left = new_node;
			}
		} else if (_val_comp(current->_data, new_node->_data)) {
			if (current->_right)
				new_node = treeAdd(current->_right, new_node);
			else {
				new_node->_parent = current;
				current->_right = new_node;
			}
		} else
			return current;
		balance(current);
		return new_node;
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::node *Map<Key, T, Compare, Alloc>
	        ::balance(Map::node *current) {
		treeOverHead(current);
		int  BF_count = BF(current);
		if (BF_count == 2) {
			if (BF(current->_right)<0)
				current->_right = treeRight(current->_right);
			return treeLeft(current);
		}
		if (BF_count == -2) {
			if (BF(current->_left)>0)
				current->_left = treeLeft(current->_left);
			return treeRight(current);
		}
		return current;
	}

	template<class Key, class T, class Compare, class Alloc>
	int Map<Key, T, Compare, Alloc>::BF(Map::node *current) {
		int h_left = 0;
		int h_right = 0;

		h_left = (current->_left ? current->_left->_height : 0);
		h_right = (current->_right ? current->_right->_height : 0);
		return ((h_right) - (h_left));
	}

	template<class Key, class T, class Compare, class Alloc>
	void Map<Key, T, Compare, Alloc>::treeOverHead(Map::node * current) {
		int h_left = 0;
		int h_right = 0;
		if (current->_left)
			h_left = current->_left->_height;
		if (current->_right)
			h_right = current->_right->_height;
		current->_height = ((h_left>h_right) ? h_left : h_right) + 1;
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::node * Map<Key, T, Compare, Alloc>
	        ::treeRight(Map::node * r) {
		node* l = r->_left;
		node* r2 = l->_right;
		if (r->_parent) {
			if (r->_parent->_left == r)
				r->_parent->_left = l;
			else
				r->_parent->_right = l;
		}
		l->_parent = r->_parent;
		l->_right = r;
		r->_parent = l;
		r->_left = r2;
		if (r2)
			r2->_parent = r;
		treeOverHead(r);
		treeOverHead(l);
		return l;
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::node * Map<Key, T, Compare, Alloc>
	        ::treeLeft(Map::node * l) {
		node* r = l->_right;
		node* l2 = r->_left;
		if (l->_parent) {
			if (l->_parent->_left == l)
				l->_parent->_left = r;
			else
				l->_parent->_right = r;
		}
		r->_parent = l->_parent;
		r->_left = l;
		l->_parent = r;
		l->_right = l2;
		if (l2)
			l2->_parent = l;
		treeOverHead(l);
		treeOverHead(r);
		return r;
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::node * Map<Key, T, Compare, Alloc>
	        ::treeGetInit(Map::node * current) {
		while (current->_parent)
			current = current->_parent;
		return (current);
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::node * Map<Key, T, Compare, Alloc>
	        ::treeFindRec(Map::node * current, const key_type k) const {
		if (!current)
			return NULL;
		else if (current->_data.first > k)
			return treeFindRec(current->_left, k);
		else if (current->_data.first < k)
			return treeFindRec(current->_right, k);
		else
			return current;
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::node * Map<Key, T, Compare, Alloc>
	        ::FIND_NEAR(Map::node *current, const key_type &k) const {
		if (!current)
			return NULL;
		else if (_key_comp(current->_data.first, k)) {
			node* tmp = FIND_NEAR(current->_right, k);
			if (tmp) return tmp;
		}
		else if (_key_comp(k, current->_data.first)) {
			node* tmp = FIND_NEAR(current->_left, k);
			if (tmp) return tmp;
		}
		return current;
	}

	template<class Key, class T, class Compare, class Alloc>
	void Map<Key, T, Compare, Alloc>::linkTreeDefault() const {
		if (!_init_node) {
			_begin_node->_parent = _end_node;
			_end_node->_parent =_begin_node;
		} else {
			node* tmp = _init_node;
			while (tmp->_left && (tmp->_left != _begin_node))
				tmp = tmp->_left;
			_begin_node->_parent = tmp;
			tmp->_left = _begin_node;
			tmp = _init_node;
			while (tmp->_right && (tmp->_right != _end_node))
				tmp = tmp->_right;
			_end_node->_parent = tmp;
			tmp->_right = _end_node;
		}
	}

	template<class Key, class T, class Compare, class Alloc>
	void Map<Key, T, Compare, Alloc>::unlinkTree() const {
		if (_init_node) {
			_begin_node->_parent->_left = NULL;
			_end_node->_parent->_right = NULL;
			_begin_node->_parent = _end_node;
			_end_node->_parent = _begin_node;
		}
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::node *Map<Key, T, Compare, Alloc>
	        ::pushNode(Map::node *current, Map::node *new_node) {
		unlinkTree();
		if (!_init_node)
			_init_node = new_node;
		else {
			new_node = treeAdd(current, new_node);
			_init_node = treeGetInit(_init_node);
		}
		linkTreeDefault();
		return new_node;
	}

	template<class Key, class T, class Compare, class Alloc>
	bool Map<Key, T, Compare, Alloc>::DeletingNode(key_type k) {
		unlinkTree();
		ft::pair<node *, bool> res;
		node* finish = deleteNode(_init_node, k, &res);
		_init_node = finish;
		linkTreeDefault();
		return res.second;
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::node * Map<Key, T, Compare, Alloc>
	        ::deleteNode(Map::node *x, const key_type &k, pair<node *, bool> *ret) {
		if (!x)
			return NULL;
		if (k < x->_data.first) {
			x->_left = deleteNode(x->_left, k, ret);
		} else if (x->_data.first < k) {
			x->_right = deleteNode(x->_right, k, ret);
		} else if  (k == x->_data.first) {
			ret->second = true;
			int x_key = x->_data.first;
			node* parent = x->_parent;
			node* l = x->_left;
			node* r = x->_right;
			removeNode(x);
			if (!r) {
				if (parent && l) {
					l->_parent = parent;
					if (x_key < parent->_data.first)
						parent->_left = l;
					else
						parent->_right = l;
				}
				return l;
			}
			node * min = findMin(r);
			min->_left = l;
			if (l)
				l->_parent = min;
			if (parent) {
				r->_parent = parent;
				if (x_key < parent->_data.first)
					parent->_left = x->_right;
				else
					parent->_right = x->_right;
			} else {
				_init_node = r;
				r->_parent = NULL;
				balance(min);
				return balance(_init_node);
			}
			return treeBalance(r);
		}
		return balance(x);
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::node *Map<Key, T, Compare, Alloc>
	        ::findMin(Map::node *x) {
		if (x->_left) return findMin(x->_left);
		else return x;
	}

	template<class Key, class T, class Compare, class Alloc>
	typename Map<Key, T, Compare, Alloc>::node *Map<Key, T, Compare, Alloc>
	        ::treeBalance(Map::node *x) {
		if (x->_left) {
			treeBalance(x->_left);
		}
		return balance(x);
	}
#pragma endregion

}
