//
// Created by Skipjack Adolph on 4/16/21.
//

#pragma once

// todo: #include "utils"
#include "MapIterator.hpp"
#include "RevIterator.hpp"
#include "MapNode.hpp"
#include <limits>
#include <cstddef>
# include <sstream>
# include <typeinfo>
# include <iostream>


namespace ft {

	template < class Key, class T, class Compare = ft::less<Key>,
	        class Alloc = std::allocator<ft::MapNode<ft::pair<const Key,T> > > >

	class Map {

	/*************************************
	**	ALIASES							**
	*************************************/
	public:
		typedef Key															key_type;
		typedef T															mapped_type;
		typedef ft::pair<const Key, T>										value_type;
		typedef ft::MapNode<value_type>										node_type;
		typedef Compare														key_compare;
		typedef ft::less<value_type>										value_compare;
		typedef Alloc														allocator_type;
		typedef typename allocator_type::reference							reference;
		typedef typename allocator_type::const_reference					const_reference;
		typedef typename allocator_type::pointer							pointer;
		typedef typename allocator_type::const_pointer						const_pointer;
		typedef MapIterator<value_type, key_compare>						iterator;
		typedef MapIterator<const value_type, key_compare>					const_iterator;
		typedef ft::reverse_iterator<iterator>								reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		typedef std::ptrdiff_t												difference_type;
		typedef std::size_t													size_type;
		typedef ft::MapNode<typename ft::remove_const<value_type>::type>	node;



	/*************************************
	**	COPLIEN FORM					**
	*************************************/
	public:
		explicit Map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) :
				_alloc(alloc), _comp(comp), _init_node(NULL) {
			_start_node = CreatInit();
			_end_node = CreatInit();
			_length = 0;

			LinkDefaultTree();
		}

		Map (const Map& x): _alloc(x._alloc), _comp(x._comp), _init_node(NULL) {
			_start_node = CreatInit();
			_end_node = CreatInit();
			_length = 0;
			LinkDefaultTree();
			insert(x.begin(), x.end());
		}
		Map& operator= (const Map& x) {
			if (this == &x)
				return *this;
			clear();
			insert(x.begin(), x.end());
			return *this;
		}

		~Map() {
			clear();
			DeleteNode(_start_node);
			DeleteNode(_end_node);
		}


	/*************************************
	**	CONSTRUCTORS					**
	*************************************/
	public:
		template <class InputIterator>
		Map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type&
		alloc = allocator_type(), typename enable_if<is_input_iterator<InputIterator>::value>::type* = NULL):
				_alloc(alloc), _comp(comp), _init_node(NULL) {
			_start_node = CreatInit();
			_end_node = CreatInit();
			_length = 0;
			LinkDefaultTree();
			insert(first, last);
		}

	/*************************************
	**	METHODS							**
	*************************************/
	public:
		/**	Iterators					*/
		iterator begin() { return ++iterator(_start_node);}
		const_iterator begin() const { return  ++const_iterator(_start_node);}

		iterator end() {return iterator (_end_node);}
		const_iterator end() const { return const_iterator(_end_node);}

		reverse_iterator rbegin() {return reverse_iterator(end());}
		const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}

		reverse_iterator rend() {return reverse_iterator (begin());}
		const_reverse_iterator rend() const { return const_reverse_iterator (begin());}

		/**	Capacity					*/
		bool empty() const {return !(_length);}
		size_type size() const {return _length;}
		size_type max_size() const {return std::numeric_limits<size_type>::max() / (sizeof(node));}

		/**	Element access				*/
		mapped_type& operator[] (const key_type& k) {
			node* tmp = FIND(_init_node, k);
			if (tmp == NULL || tmp->_data.first != k) {
				value_type val(k, mapped_type());
				iterator it = insert(val).first;
				return (*it).second;
			}
			iterator res(tmp);
			return (*res).second;
		}

		/**	Modifiers					*/
		ft::pair<iterator,bool> insert (const value_type& val) {
			node* new_node = CreateNode(val);
			node* tmp = AddNewNode(_init_node, new_node);
			if (tmp != new_node)
			{
				_alloc.destroy(new_node);
				_alloc.deallocate(new_node, 1);
				return ft::pair<iterator,bool>(tmp, false);
			}
			++_length;
			return ft::pair<iterator,bool>(iterator(new_node), true);
		}

		iterator insert (iterator position, const value_type& val) {
			if (position._data != _start_node && position._data != _end_node
				&& ((_val_comp(val, position.next_node()->_data) && _val_comp(position.prev_node()->_data, val))))
			{
				node* tmp =  CreateNode(val);
				node* n = AddNewNode(position._data, tmp);
				if (n != tmp)
				{
					_alloc.destroy(tmp);
					_alloc.deallocate(tmp, 1);
					return iterator(n);
				}
				++_length;
				return iterator(tmp);
			}
			else
				return insert(val).first;
		}


		template <class InputIterator>
		void insert (InputIterator first, InputIterator last,
					 typename enable_if<is_input_iterator<InputIterator>::value>::type* = NULL) {
			while (first != last) {
				insert(*first);
				++first;
			}
		}
		void erase (iterator position) {
			erase(position._data->_data.first);
		}

		size_type erase (const key_type& k) {
			if (DeletingNode(k)) {
				--_length;
				return (1);
			} else
				return 0;
		}

		void erase (iterator first, iterator last) {
			iterator tmp;
			while (first != last) {
				tmp = first;
				++first;
				erase(tmp._data->_data.first);
			}
		}

		void swap (Map& x) {
			ft::swap(_alloc, x._alloc);
			ft::swap(_init_node, x._init_node);
			ft::swap(_start_node, x._start_node);
			ft::swap(_end_node, x._end_node);
			ft::swap(_length, x._length);
		}

		void clear() {
			erase(begin(), end());
		}

		/**	Observers					*/
		key_compare key_comp() const {return _comp;}
		value_compare value_comp() const {return _val_comp;}

		/**	Operations					*/
		iterator find (const key_type& k) {
			UnlinkTree();
			node* tmp = FIND(_init_node, k);
			LinkDefaultTree();
			if (tmp == NULL)
				return iterator(end());
			return iterator(tmp);
		}

		const_iterator find (const key_type& k) const {
			UnlinkTree();
			node* tmp = FIND(_init_node, k);
			LinkDefaultTree();
			if (tmp == NULL)
				return const_iterator(end());
			return const_iterator(tmp);
		}

		size_type count (const key_type& k) const {
			return ((find(k) == end()) ? 0 : 1);
		}

		iterator lower_bound (const key_type& k) {
			UnlinkTree();
			node* tmp = FIND_NEAR(_init_node, k);
			LinkDefaultTree();
			if (k > tmp->_data.first)
				return ++iterator(tmp);
			return iterator(tmp);
		}

		const_iterator lower_bound (const key_type& k) const {
			UnlinkTree();
			node* tmp = FIND_NEAR(_init_node, k);
			LinkDefaultTree();
			if (k > tmp->_data.first)
				return ++const_iterator(tmp);
			return const_iterator(tmp);
		}
		iterator upper_bound (const key_type& k) {
			iterator tmp = lower_bound(k);
			if ((*tmp).first <= k)
				++tmp;
			return tmp;
		}
		const_iterator upper_bound (const key_type& k) const {
			const_iterator tmp = lower_bound(k);
			if ((*tmp).first <= k)
				++tmp;
			return tmp;
		}
		ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const {
			return ft::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
		}

		pair<iterator,iterator> equal_range (const key_type& k) {
			return ft::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
		}


	private:
		typedef typename allocator_type::template
		rebind<value_type>::other node_alloc;
		typedef typename node_alloc::pointer _node_pointer;
		allocator_type	_alloc;
		key_compare		_comp;
		node_alloc _node_alloc;
		node*		 	_init_node;
		node*			_start_node;
		node*			_end_node;
		size_type _length;
		value_compare 	_val_comp;
		//		CreateNode
		pointer CreateNode(const value_type& data) {
			node* new_node = _alloc.allocate(1);
			_alloc.construct(new_node, data);
			return (new_node);
		}
//DeleteNode
		void DeleteNode(node* x) {
			_alloc.destroy(x);
			_alloc.deallocate(x, 1);
		}
//		CreateInitNode
		pointer CreatInit(){
			node* new_node = _alloc.allocate(1);
			_alloc.construct(new_node, node_type());
			new_node->_parent = NULL;
			new_node->_left = NULL;
			new_node->_right = NULL;
			new_node->_height = 0;
			return (new_node);
		}
//		BTR_functions
//		ADD
		node* ADD(node* _cur, node* new_node) {
			if (_val_comp(new_node->_data, _cur->_data)) {
				if (_cur->_left)
					new_node = ADD(_cur->_left, new_node);
				else {
					new_node->_parent = _cur;
					_cur->_left = new_node;
				}
			} else if (_val_comp(_cur->_data, new_node->_data)) {
				if (_cur->_right)
					new_node = ADD(_cur->_right, new_node);
				else {
					new_node->_parent = _cur;
					_cur->_right = new_node;
				}
			} else
				return _cur;
			BALANCE(_cur);
			return new_node;
		}

		node* BALANCE(node* _cur) {
			OVER_HEAD(_cur);
			int  BF_count = BF(_cur);
			if (BF_count == 2) {
				if (BF(_cur->_right)<0)
					_cur->_right = RIGHT_SR(_cur->_right);
				return LEFT_SR(_cur);
			}
			if (BF_count == -2) {
				if (BF(_cur->_left)>0)
					_cur->_left = LEFT_SR(_cur->_left);
				return RIGHT_SR(_cur);
			}
			return _cur;
		}

		int BF (node *_cur) {
			int h_left = 0;
			int h_right = 0;
			h_left = (_cur->_left ? _cur->_left->_height : 0);
			h_right = (_cur->_right ? _cur->_right->_height : 0);
			return ((h_right) - (h_left));
		}

		void OVER_HEAD(node *_cur) {
			int h_left = 0;
			int h_right = 0;
			if (_cur->_left)
				h_left = _cur->_left->_height;
			if (_cur->_right)
				h_right = _cur->_right->_height;
			_cur->_height = ((h_left>h_right) ? h_left : h_right) + 1;
		}

		node* RIGHT_SR(node *r) {
			node* l = r->_left;
			node* r2 = l->_right;
			if (r->_parent) {
				if (r->_parent->_left == r)
					r->_parent->_left = l;
				else
					r->_parent->_right = l;
			}
			l->_parent = r->_parent;
//			r->_parent->_left = l;
			l->_right = r;
			r->_parent = l;
			r->_left = r2;
			if (r2)
				r2->_parent = r;
			OVER_HEAD(r);
			OVER_HEAD(l);
			return l;
		}

		node* LEFT_SR(node *l) {
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
			OVER_HEAD(l);
			OVER_HEAD(r);
			return r;
		}

		node * FIND_INIT(node* _cur) {
			while (_cur->_parent)
				_cur = _cur->_parent;
			return (_cur);
		}

		node* FIND(node* _cur, const key_type k) const {
			if (!_cur)
				return NULL;
			else if (_cur->_data.first > k)
				return FIND(_cur->_left, k);
			else if (_cur->_data.first < k)
				return FIND(_cur->_right, k);
			else
				return _cur;
		}

		node* FIND_NEAR(node* _cur, const key_type& k) const {
			if (!_cur)
				return NULL;
			else if (_comp(_cur->_data.first, k)) {
				node* tmp = FIND_NEAR(_cur->_right, k);
				if (tmp) return tmp;
			}
			else if (_comp(k, _cur->_data.first)) {
				node* tmp = FIND_NEAR(_cur->_left, k);
				if (tmp) return tmp;
			}
				return _cur;
		}

		void LinkDefaultTree() const {
			if (!_init_node) {
				_start_node->_parent = _end_node;
				_end_node->_parent =_start_node;
			} else {
				node* tmp = _init_node;
				while (tmp->_left && (tmp->_left != _start_node))
					tmp = tmp->_left;
				_start_node->_parent = tmp;
				tmp->_left = _start_node;
				tmp = _init_node;
				while (tmp->_right && (tmp->_right != _end_node))
					tmp = tmp->_right;
				_end_node->_parent = tmp;
				tmp->_right = _end_node;
			}
		}

		void UnlinkTree() const {
			if (_init_node) {
				_start_node->_parent->_left = NULL;
				_end_node->_parent->_right = NULL;
				_start_node->_parent = _end_node;
				_end_node->_parent = _start_node;
			}
		}

		node* AddNewNode(node* _cur, node* new_node) {
			UnlinkTree();
			if (!_init_node)
				_init_node = new_node;
			else {
				new_node = ADD(_cur, new_node);
				_init_node = FIND_INIT(_init_node);
			}
			LinkDefaultTree();
			return new_node;
		}
		bool DeletingNode(key_type k) {
			UnlinkTree();
			ft::pair<node *, bool> res;
//			res = DELETING(_init_node, k);
			node* finish = ___DELETE___(_init_node, k, &res);
			_init_node = finish;
			LinkDefaultTree();
			return res.second;
		}
		node * ___DELETE___(node* x, const key_type &k, ft::pair<node*, bool> *ret) {
			if (!x)
				return NULL;
			if (k < x->_data.first) {
				x->_left = ___DELETE___(x->_left, k, ret);
			} else if (x->_data.first < k) {
				x->_right = ___DELETE___(x->_right, k, ret);
			} else if  (k == x->_data.first) {
				ret->second = true;
				int x_key = x->_data.first;
				node* parent = x->_parent;
				node* l = x->_left;
				node* r = x->_right;
				DeleteNode(x);
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
				node* min = SearchMin(r);
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
					BALANCE(min);
					return BALANCE(_init_node);
				}
				return RecursiveBalance(r);
			}
			return BALANCE(x);
		}

		node *SearchMin(node *x)
		{
			if (x->_left) return SearchMin(x->_left);
			else return x;
		}

		node* RecursiveBalance(node* x) {
 			if (x->_left) {
				RecursiveBalance(x->_left);
			}
			return BALANCE(x);
		}

	};

		template <class T1, class T2>
		bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first==rhs.first && lhs.second==rhs.second; }

		template <class T1, class T2>
		bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs==rhs); }

		template <class T1, class T2>
		bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first<rhs.first ;}

		template <class T1, class T2>
		bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(rhs<lhs); }

		template <class T1, class T2>
		bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return rhs<lhs; }

		template <class T1, class T2>
		bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return !(lhs<rhs); }

}
