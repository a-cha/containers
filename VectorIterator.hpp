//
// Created by Skipjack Adolph on 4/15/21.
//

#pragma once

#include "RevIterator.hpp"
#include "Algorithm.hpp"
#include <limits>

namespace ft {

	template<typename T>

	class VectorIterator {

	/*************************************
	**	ALIASES							**
	*************************************/
	public:
		typedef T					value_type;
		typedef value_type *		pointer;
		typedef value_type const *	const_point;
		typedef value_type &		ref;
		typedef value_type const &	const_ref;
		typedef std::ptrdiff_t		difference_type;

	/*************************************
	**	COPLIEN FORM					**
	*************************************/
	public:
		VectorIterator();
		VectorIterator(VectorIterator const &other);
		VectorIterator & operator=(VectorIterator const &other);
		~VectorIterator();

	/*************************************
	**	CONSTRUCTORS					**
	*************************************/
	public:
		VectorIterator(pointer p);

	/*************************************
	**	OPERATORS						**
	*************************************/
	public:
		VectorIterator &	operator++();
		VectorIterator		operator++(int);
		VectorIterator &	operator--();
		VectorIterator		operator--(int);
		const_point			operator->() const;
		ref					operator*();
		const_ref			operator*() const;
		pointer				operator->();
		ref					operator[](int n);
		const_ref			operator[](int n) const;
		VectorIterator &	operator+=(int n);
		VectorIterator		operator+(int n) const;
		VectorIterator &	operator-=(int n);
		VectorIterator		operator-(int n) const;
		difference_type		operator-(VectorIterator const &other) const;
		bool				operator==(VectorIterator const &other) const;
		bool				operator!=(VectorIterator const &other) const;
		bool				operator>(VectorIterator const &other) const;
		bool				operator<(VectorIterator const &other) const;
		bool				operator>=(VectorIterator const &other) const;
		bool				operator<=(VectorIterator const &other) const;

	/*************************************
	**	FIELDS							**
	*************************************/
	private:
		pointer _point;
	};
}

#include "VectorIterator.ipp"
