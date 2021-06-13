//
// Created by Skipjack Adolph on 4/15/21.
//

#pragma once

namespace ft {

/**	COPLIEN FORM					**/
#pragma region Coplien

	template<typename T>
	VectorIterator<T>::VectorIterator() :
			_point() {}

	template<typename T>
	VectorIterator<T>::VectorIterator(const VectorIterator &other) :
			_point(other._point) {}

	template<typename T>
	VectorIterator <T> &
	VectorIterator<T>::operator=(const VectorIterator &other) {
		if (this != &other)
			_point = other._point;
		return *this;
	}

	template<typename T>
	VectorIterator<T>::~VectorIterator() {}

#pragma endregion

/**	CONSTRUCTORS					**/
#pragma region Constructors

	template<typename T>
	VectorIterator<T>::VectorIterator(typename VectorIterator<T>::pointer p) :
			_point(p) {}

#pragma endregion

/**	OPERATORS						**/
#pragma region Operators

	template<typename T>
	VectorIterator <T> &VectorIterator<T>::operator++() {
		++_point;
		return *this;
	}

	template<typename T>
	VectorIterator <T> VectorIterator<T>::operator++(int) {
		VectorIterator tmp;

		tmp = *this;
		++_point;
		return tmp;
	}

	template<typename T>
	VectorIterator <T> &VectorIterator<T>::operator--() {
		--_point;
		return *this;
	}

	template<typename T>
	VectorIterator <T> VectorIterator<T>::operator--(int) {
		VectorIterator tmp;

		tmp = *this;
		--_point;
		return tmp;
	}

	template<typename T>
	typename VectorIterator<T>::ref VectorIterator<T>::operator*() {
		return *_point;
	}

	template<typename T>
	typename VectorIterator<T>::const_ref VectorIterator<T>::operator*() const {
		return *_point;
	}

	template<typename T>
	typename VectorIterator<T>::pointer VectorIterator<T>::operator->() {
		return _point;
	}

	template<typename T>
	typename VectorIterator<T>::const_point
	VectorIterator<T>::operator->() const {
		return _point;
	}

	template<typename T>
	typename VectorIterator<T>::ref VectorIterator<T>::operator[](int n) {
		return *(_point + n);
	}

	template<typename T>
	typename VectorIterator<T>::const_ref
	VectorIterator<T>::operator[](int n) const {
		return *(_point + n);
	}

	template<typename T>
	VectorIterator <T> &VectorIterator<T>::operator+=(int n) {
		_point += n;
		return *this;
	}

	template<typename T>
	VectorIterator <T> VectorIterator<T>::operator+(int n) const {
		VectorIterator tmp;

		tmp = *this;
		tmp += n;
		return tmp;
	}

	template<typename T>
	VectorIterator <T> &VectorIterator<T>::operator-=(int n) {
		_point -= n;
		return *this;
	}

	template<typename T>
	VectorIterator <T> VectorIterator<T>::operator-(int n) const {
		VectorIterator tmp;

		tmp = *this;
		return tmp -= n;
	}

	template<typename T>
	typename VectorIterator<T>::difference_type
	VectorIterator<T>::operator-(VectorIterator const &other) const {
		return _point - other._point;
	}

	template<typename T>
	bool VectorIterator<T>::operator==(const VectorIterator &other) const {
		return _point == other._point;
	}

	template<typename T>
	bool VectorIterator<T>::operator!=(const VectorIterator &other) const {
		return _point != other._point;
	}

	template<typename T>
	bool VectorIterator<T>::operator>(const VectorIterator &other) const {
		return _point > other._point;
	}

	template<typename T>
	bool VectorIterator<T>::operator<(const VectorIterator &other) const {
		return _point < other._point;
	}

	template<typename T>
	bool VectorIterator<T>::operator>=(const VectorIterator &other) const {
		return _point >= other._point;
	}

	template<typename T>
	bool VectorIterator<T>::operator<=(const VectorIterator &other) const {
		return _point <= other._point;
	}
#pragma endregion

}
