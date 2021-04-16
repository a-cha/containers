//
// Created by Skipjack Adolph on 4/14/21.
//

#pragma once

#include "ListIterator.hpp"

/**	COPLIEN FORM					**/
#pragma region coplien

	template<typename T, typename T1>
	ListIterator<T, T1>::ListIterator() :
			_point() {}

	template<typename T, typename T1>
	ListIterator<T, T1>::ListIterator(const ListIterator &other) :
			_point(other._point) {}

	template<typename T, typename T1>
	ListIterator<T, T1> &ListIterator<T, T1>::operator=(const ListIterator &other) {
		if (this != other)
			_point = other._point;
		return *this;
	}

#pragma endregion

/**	CONSTRUCTORS					**/
#pragma region constructors

	template<typename T, typename T1>
	ListIterator<T, T1>::ListIterator(ListIterator<T, T1>::node_type *p) :
			_point(p) {}
#pragma endregion

/**	GETTERS							**/
#pragma region getters

	template<typename T, typename T1>
	typename ListIterator<T, T1>::node_type *ListIterator<T, T1>::getPoint() const {
		return _point;
	}
#pragma endregion

/**	OPERATORS						**/
#pragma region operators

	template<typename T, typename T1>
	ListIterator<T, T1> &ListIterator<T, T1>::operator++() {
		this->_point = this->_point->next();
		return *this;
	}

	template<typename T, typename T1>
	ListIterator<T, T1> &ListIterator<T, T1>::operator--() {
		this->_point = this->_point->previous();
		return *this;
	}

	template<typename T, typename T1>
	typename ListIterator<T, T1>::value_type * ListIterator<T, T1>::operator->() {
		return &this->_point->_data();
	}

	template<typename T, typename T1>
	typename ListIterator<T, T1>::value_type & ListIterator<T, T1>::operator*() {
		return this->_point->_data();
	}

	template<typename T, typename T1>
	ListIterator<T, T1> ListIterator<T, T1>::operator+(int n) const {
		ListIterator tmp;

		tmp = *this;
		tmp += n;
		return tmp;
	}

	template<typename T, typename T1>
	void ListIterator<T, T1>::operator+=(int n) {
		for (int i = 0; i < n; i++)
			this->_point = this->_point->next();
	}

	template<typename T, typename T1>
	ListIterator<T, T1> ListIterator<T, T1>::operator-(int n) const {
		ListIterator tmp;

		tmp = *this;
		tmp -= n;
		return tmp;
	}

	template<typename T, typename T1>
	void ListIterator<T, T1>::operator-=(int n) {
		for (int i = 0; i > n; i--)
			this->_point = this->_point->previous();
	}

	template<typename T, typename T1>
	bool ListIterator<T, T1>::operator==(const ListIterator &other) const {
		return this->_point == other._point;
	}

	template<typename T, typename T1>
	bool ListIterator<T, T1>::operator!=(const ListIterator &other) const {
		return this->_point == other._point;
	}

	template<typename T, typename T1>
	bool ListIterator<T, T1>::operator>(const ListIterator &other) const {
		return this->_point > other._point;
	}

	template<typename T, typename T1>
	bool ListIterator<T, T1>::operator<(const ListIterator &other) const {
		return this->_point < other._point;
	}

	template<typename T, typename T1>
	bool ListIterator<T, T1>::operator>=(const ListIterator &other) const {
		return this->_point >= other._point;
	}

	template<typename T, typename T1>
	bool ListIterator<T, T1>::operator<=(const ListIterator &other) const {
		return this->_point <= other._point;
	}

#pragma endregion


//		todo strange method
//		ListIterator operator++(int) {
//			ListIterator tmp(*this);
//			this->_point = this->_point->next();
//			return tmp;
//		}

//		todo strange method
//		ListIterator operator--(int) {
//			ListIterator tmp(*this);
//			this->_point = this->_point->previous();
//			return tmp;
//		}
