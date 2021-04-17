//
// Created by Skipjack Adolph on 4/15/21.
//

#pragma once

#include "VectorIterator.hpp"

/**	COPLIEN FORM					**/
#pragma region Coplien

template<typename T>
VectorIterator<T>::VectorIterator() :
		_point() {}

template<typename T, typename T1>
VectorIterator<T>::VectorIterator(const VectorIterator &other) :
		_point(other._point) {}

template<typename T, typename T1>
VectorIterator<T> &VectorIterator<T>::operator=(const VectorIterator &other) {
	if (this != &other)
		_point = other._point;
	return *this;
}
#pragma endregion
