//
// Created by Skipjack Adolph on 4/13/21.
//

#pragma once

#include "ListNode.hpp"
#include "RevIterator.hpp"

namespace ft {

	template < typename T, typename T1 >

	class ListIterator {

	/*************************************
	**	ALIASES							**
	*************************************/
	public:
		typedef T													value_type;
		typedef value_type &										ref;
		typedef value_type const &									const_ref;
		typedef value_type *										pointer;
		typedef value_type const *									const_point;
		typedef T1													node_type;
		typedef node_type *											node_point;
		typedef ListIterator<value_type, node_type>					iterator;
		typedef ListIterator<value_type const, node_type const>		const_iterator;
		typedef RevIterator<iterator>								rev_iterator;
		typedef RevIterator<const_iterator>							const_rev_iterator;
		typedef ptrdiff_t											difference_type;
		typedef size_t												size_type;

	/*************************************
	**	COPLIEN FORM					**
	*************************************/
	public:
		ListIterator();
		ListIterator(ListIterator const &other);
		ListIterator &operator=(ListIterator const &other);
		~ListIterator() {}

	/*************************************
	**	CONSTRUCTORS					**
	*************************************/
	public:
		ListIterator(node_type * p);

	/*************************************
	**	GETTERS							**
	*************************************/
	public:
		node_type *getPoint() const;

//	todo do i need this strange method?
		node_type * &ptr() {
			return this->_point;
		}

	/*************************************
	**	OPERATORS						**
	*************************************/
	public:
		ListIterator &		operator++();
		ListIterator		operator++(int);
		ListIterator &		operator--();
		value_type *		operator->();
		value_type &		operator*();
		ListIterator		operator+(int n) const;
		ListIterator		operator-(int n) const;
		void				operator+=(int n);
		void				operator-=(int n);

		bool				operator==(ListIterator const &other) const;
		bool				operator!=(ListIterator const &other) const;
		bool				operator>(ListIterator const &other) const;
		bool				operator<(ListIterator const &other) const;
		bool				operator>=(ListIterator const &other) const;
		bool				operator<=(ListIterator const &other) const;

	/*************************************
	**	FIELDS							**
	*************************************/
	private:
		node_type * _point;
	};
}

#include "ListIterator.ipp"
