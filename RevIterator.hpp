//
// Created by Skipjack Adolph on 4/14/21.
//

#pragma once

namespace ft
{
	template<typename I>

	class RevIterator: public I {

	/*************************************
	**	ALIASES							**
	*************************************/
	public:
		using typename I::value_type;
		using typename I::ref;
		using typename I::const_ref;
		using typename I::pointer;
		using typename I::const_point;
		using typename I::difference_type;

	/*************************************
	**	CONSTRUCTORS					**
	*************************************/
	public:
		RevIterator();
		RevIterator(I const & other);

	/*************************************
	**	OPERATORS						**
	*************************************/
	public:
		RevIterator		operator++(int);
		I &				operator++();
		RevIterator 	operator--(int);
		I &				operator--();
		ref				operator*();
		const_ref		operator*() const;
		pointer			operator->();
		const_point		operator->() const;
	};
}

#include "RevIterator.ipp"
