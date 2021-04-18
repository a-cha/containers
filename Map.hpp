//
// Created by Skipjack Adolph on 4/16/21.
//

#pragma once

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
		typedef Key														key_type;
		typedef T														mapped_type;
		typedef ft::pair<const Key, T>									value_type;
		typedef ft::MapNode<value_type>									node_type;
		typedef Compare													key_compare;
		typedef ft::less<value_type>									value_compare;
		typedef Alloc													allocator_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef MapIterator<value_type, key_compare>					iterator;
		typedef MapIterator<const value_type, key_compare>				const_iterator;
		typedef RevIterator<iterator>									reverse_iterator;
		typedef RevIterator<const_iterator>								const_reverse_iterator;
		typedef std::ptrdiff_t											difference_type;
		typedef std::size_t												size_type;
		typedef ft::MapNode<typename ft::is_const<value_type>::type>	node;

	/*************************************
	**	COPLIEN FORM					**
	*************************************/
	public:
		Map(const Map & other);
		Map & operator=(const Map &other);
		~Map();

	/*************************************
	**	CONSTRUCTORS					**
	*************************************/
	public:
		explicit Map(const key_compare &comp = key_compare(),
			   			const allocator_type &alloc = allocator_type());

		template <class InputIterator>
		Map (InputIterator first, InputIterator last,
	   			const key_compare& comp = key_compare(),
	   				const allocator_type & alloc = allocator_type());

	/*************************************
	**	METHODS							**
	*************************************/
	public:
		/**	Iterators					*/
		iterator				begin();
		const_iterator			begin() const;
		iterator				end();
		const_iterator			end() const;
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;

		/**	Capacity					*/
		bool					empty() const;
		size_type				size() const;
		size_type				max_size() const;

		/**	Element access				*/
		mapped_type &			operator[](const key_type & k);

		/**	Modifiers					*/
		ft::pair<iterator,bool>	insert(const value_type& val);
		iterator				insert(iterator pos, const value_type& val);
		template <class InputIterator>
		void					insert(InputIterator first, InputIterator last);
		void					erase(iterator pos);
		size_type				erase(const key_type& k);
		void					erase(iterator first, iterator last);
		void					swap(Map & x);
		void					clear();

		/**	Observers					*/
		key_compare				key_comp() const;
		value_compare			value_comp() const;

		/**	Operations					*/
		iterator				find(const key_type & k);
		const_iterator			find(const key_type & k) const;
		size_type				count(const key_type & k) const;
		iterator				lower_bound(const key_type& k);
		const_iterator			lower_bound(const key_type& k) const;
		iterator				upper_bound(const key_type& k);
		const_iterator			upper_bound(const key_type& k) const;
		pair<iterator,iterator>	equal_range(const key_type& k);
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const;


	/*************************************
	**	FIELDS							**
	*************************************/
	private:
		typedef typename					allocator_type::
		template rebind<value_type>::other	node_alloc;
		typedef typename					node_alloc::pointer _node_pointer;

		allocator_type			_alloc;
		node_alloc				_node_alloc;
		size_type				_size;
		key_compare				_key_comp;
		value_compare 			_val_comp;
		node *		 			_init_node;
		node *					_begin_node;
		node *					_end_node;

	/*************************************
	**	UTILS							**
	*************************************/
	private:
		pointer makeNode(const value_type& data) {
			node* new_node = _alloc.allocate(1);
			_alloc.construct(new_node, data);
			return (new_node);
		}
		void removeNode(node* x) {
			_alloc.destroy(x);
			_alloc.deallocate(x, 1);
		}
		pointer initNode(){
			node* new_node = _alloc.allocate(1);
			_alloc.construct(new_node, node_type());
			new_node->_parent = NULL;
			new_node->_left = NULL;
			new_node->_right = NULL;
			new_node->_height = 0;
			return (new_node);
		}



		node* treeAdd(node* current, node* new_node) {
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

		node* balance(node* current) {
			OVER_HEAD(current);
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

		int BF (node *current) {
			int h_left = 0;
			int h_right = 0;
			h_left = (current->_left ? current->_left->_height : 0);
			h_right = (current->_right ? current->_right->_height : 0);
			return ((h_right) - (h_left));
		}

		void OVER_HEAD(node *current) {
			int h_left = 0;
			int h_right = 0;
			if (current->_left)
				h_left = current->_left->_height;
			if (current->_right)
				h_right = current->_right->_height;
			current->_height = ((h_left>h_right) ? h_left : h_right) + 1;
		}

		node* treeRight(node *r) {
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

		node* treeLeft(node *l) {
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

		node * treeGetInit(node * current) {
			while (current->_parent)
				current = current->_parent;
			return (current);
		}

		node * treeFindRec(node * current, const key_type k) const {
			if (!current)
				return NULL;
			else if (current->_data.first > k)
				return treeFindRec(current->_left, k);
			else if (current->_data.first < k)
				return treeFindRec(current->_right, k);
			else
				return current;
		}

//		todo: what is this?
		node * FIND_NEAR(node * current, const key_type& k) const {
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

		void linkTreeDefault() const {
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

		void unlinkTree() const {
			if (_init_node) {
				_begin_node->_parent->_left = NULL;
				_end_node->_parent->_right = NULL;
				_begin_node->_parent = _end_node;
				_end_node->_parent = _begin_node;
			}
		}

		node* pushNode(node* current, node* new_node) {
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
		bool DeletingNode(key_type k) {
			unlinkTree();
			ft::pair<node *, bool> res;
//			res = DELETING(_init_node, k);
			node* finish = ___DELETE___(_init_node, k, &res);
			_init_node = finish;
			linkTreeDefault();
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
					balance(min);
					return balance(_init_node);
				}
				return treeBalance(r);
			}
			return balance(x);
		}

		node *SearchMin(node *x)
		{
			if (x->_left) return SearchMin(x->_left);
			else return x;
		}

		node* treeBalance(node* x) {
 			if (x->_left) {
				treeBalance(x->_left);
			}
			return balance(x);
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

#include "Map.ipp"
