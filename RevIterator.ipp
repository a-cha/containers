//
// Created by Skipjack Adolph on 4/14/21.
//

#pragma once

#include "RevIterator.hpp"

/**	COPLIEN FORM					**/
#pragma region coplien

template<typename I>
RevIterator<I>::RevIterator() :
		I() {}

template<typename I>
RevIterator<I>::RevIterator(RevIterator const &other) :
		I(other) {}

template<typename I>
RevIterator<I> & RevIterator<I>::operator=(const RevIterator &other)  {
	if (this != other)
		this->p = other.p;
	return *this;
}

#pragma endregion

/**	CONSTRUCTORS					**/
#pragma region constructors

template<typename I>
RevIterator<I>::RevIterator(const I &other) :
		I(other) {}
#pragma endregion

/**	OPERATORS						**/
#pragma region operators

template<typename I>
RevIterator<I> RevIterator<I>::operator++(int) {
	RevIterator tmp;

	tmp = *this;
	return ++tmp;
}

template<typename I>
I & RevIterator<I>::operator++() {
	return this->I::operator--();
}

template<typename I>
RevIterator<I> RevIterator<I>::operator--(int) {
	RevIterator tmp;

	tmp = *this;
	return --tmp;
}

template<typename I>
I &RevIterator<I>::operator--() {
	return (this->It::operator++());
}

template<typename I>
typename RevIterator<I>::ref RevIterator<I>::operator*()  {
	I tmp;

	tmp = *this;
	return *--tmp;
}

template<typename I>
typename RevIterator<I>::const_ref RevIterator<I>::operator*() const  {
	I tmp;

	tmp = *this;
	return *--tmp;
}

template<typename I>
typename RevIterator<I>::pointer RevIterator<I>::operator->()  {
	I tmp;

	tmp = *this;
	return &*--tmp;
}

template<typename I>
typename RevIterator<I>::const_point RevIterator<I>::operator->() const  {
	I tmp;

	tmp = *this;
	return &*--tmp;
}
#pragma endregion
