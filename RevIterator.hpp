//
// Created by Skipjack Adolph on 4/14/21.
//

#pragma once

#include "Node.hpp"

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
	**	COPLIEN FORM					**
	*************************************/
	public:
		RevIterator();
		RevIterator(RevIterator const &other);
		RevIterator &operator=(RevIterator const &other);
		virtual ~RevIterator() {}

	/*************************************
	**	CONSTRUCTORS					**
	*************************************/
	public:
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

#include "RevIterator.ipp"

}
