//
// Created by Skipjack Adolph on 4/13/21.
//

#pragma once

#include "Node.hpp"
#include "RevIterator.hpp"

namespace ft {

	template < typename T, typename T1 >

	class ListIterator {

	/*************************************
	**	ALIASES							**
	*************************************/
	public:
		typedef T 					value_type;
		typedef T1 					node_type;

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
		node_type * &ptr(void) {
			return this->_point;
		}

	/*************************************
	**	OPERATORS						**
	*************************************/
	public:
		ListIterator &		operator++();
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

#include "ListIterator.ipp"

}
