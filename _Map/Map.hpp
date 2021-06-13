//
// Created by Skipjack Adolph on 4/16/21.
//

#pragma once

#include "MapIterator.hpp"
#include "../utils/RevIterator.hpp"
#include "MapNode.hpp"

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
		ft::pair<iterator,bool>	insert(const value_type & val);
		iterator				insert(iterator pos, const value_type & val);
		template <class InputIterator>
		void					insert(InputIterator first, InputIterator last);
		void					erase(iterator pos);
		size_type				erase(const key_type & k);
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
		iterator				lower_bound(const key_type & k);
		const_iterator			lower_bound(const key_type & k) const;
		iterator				upper_bound(const key_type & k);
		const_iterator			upper_bound(const key_type & k) const;
		pair<iterator,iterator>	equal_range(const key_type & k);
		pair<const_iterator,const_iterator> equal_range (const key_type & k) const;

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
		/**	Node						*/
		pointer					initNode();
		pointer					makeNode(const value_type & data);
		void					removeNode(node * other);

		/**	Tree						*/
		node *					treeAdd(node * current, node * new_node);
		node *					balance(node * current);
		int						balanceFactor(node * current);
		void					treeOverHead(node * current);
		node *					treeRight(node * r);
		node *					treeLeft(node * l);
		node *					treeGetInit(node * current);
		node *					treeFindRec(node * current, const key_type k) const;
		node *					findNearestValue(node * current, const key_type& k) const;
		void					linkTreeDefault() const;
		void					unlinkTree() const;
		node *					pushNode(node * current, node* new_node);
		bool					DeletingNode(key_type k);
		node *					deleteNode(node * x, const key_type &k, ft::pair<node *, bool> * ret);
		node *					findMin(node * x);
		node *					treeBalance(node * x);
	};

	template <class T1, class T2>
	bool operator==(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs);

	template <class T1, class T2>
	bool operator!=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs);

	template <class T1, class T2>
	bool operator<(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs);

	template <class T1, class T2>
	bool operator<=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs);

	template <class T1, class T2>
	bool operator>(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs);

	template <class T1, class T2>
	bool operator>=(const pair<T1,T2> & lhs, const pair<T1,T2> & rhs);

}

#include "Map.ipp"
