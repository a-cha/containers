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
		typedef value_type const *	const_pointer;
		typedef value_type &		reference;
		typedef value_type const &	const_reference;
		typedef std::ptrdiff_t		difference_type;

	/*************************************
	**	COPLIEN FORM					**
	*************************************/
	public:
		VectorIterator();
		VectorIterator(VectorIterator const &other);
		VectorIterator &operator=(VectorIterator const &other);
		~VectorIterator();

	/*************************************
	**	CONSTRUCTORS					**
	*************************************/
	public:
		VectorIterator(pointer p): _point(p) {}

	/*************************************
	**	OPERATORS						**
	*************************************/
	public:
		reference operator*() {
			return (*this->_point);
		}

		const_reference operator*() const {
			return (*this->_point);
		}
		pointer operator->() {
			return (this->_point);
		}
		const_pointer operator->() const {
			return (this->_point);
		}
		reference operator[](int val) {
			return (*(this->_point + val));
		}
		const_reference operator[](int val) const {
			return (*(this->_point + val));
		}
		VectorIterator operator++(int) {
			VectorIterator tmp(*this);
			++this->_point;
			return (tmp);
		}

		VectorIterator &operator++() {
			++this->_point;
			return (*this);
		}
		VectorIterator operator--(int) {
			VectorIterator tmp(*this);
			--this->_point;
			return (tmp);
		}
		VectorIterator &operator--() {
			--this->_point;
			return (*this);
		}
		VectorIterator &operator+=(int value) {
			this->_point += value;
			return (*this);
		}

		VectorIterator operator+(int value) const {
			VectorIterator tmp(*this);
			return (tmp += value);
		}
		VectorIterator &operator-=(int value) {
			this->_point -= value;
			return (*this);
		}
		VectorIterator operator-(int value) const {
			VectorIterator tmp(*this);
			return (tmp -= value);
		}
		difference_type operator-(VectorIterator const &other) const {
			return (this->_point - other._point);
		}
		bool operator==(VectorIterator const &other) const {
			return (this->_point == other._point);
		}

		bool operator!=(VectorIterator const &other) const {
			return (this->_point != other._point);
		}
		bool operator<(VectorIterator const &other) const {
			return (this->_point < other._point);
		}
		bool operator<=(VectorIterator const &other) const {
			return (this->_point <= other._point);
		}
		bool operator>(VectorIterator const &other) const {
			return (this->_point > other._point);
		}
		bool operator>=(VectorIterator const &other) const {
			return (this->_point >= other._point);
		}
	private:
		pointer _point;
	};

}
