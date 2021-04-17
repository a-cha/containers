//
// Created by Skipjack Adolph on 4/14/21.
//

#pragma once

namespace ft {

/**	CONSTRUCTORS					**/
#pragma region Constructors

	template<typename I>
	RevIterator<I>::RevIterator() :
			I() {}

	template<typename I>
	RevIterator<I>::RevIterator(const I &other) :
			I(other) {}

#pragma endregion

/**	OPERATORS						**/
#pragma region Operators

	template<typename I>
	RevIterator <I> RevIterator<I>::operator++(int) {
		RevIterator tmp;

		tmp = *this;
		return ++tmp;
	}

	template<typename I>
	I &RevIterator<I>::operator++() {
		return this->I::operator--();
	}

	template<typename I>
	RevIterator <I> RevIterator<I>::operator--(int) {
		RevIterator tmp;

		tmp = *this;
		return --tmp;
	}

	template<typename I>
	I &RevIterator<I>::operator--() {
		return (this->It::operator++());
	}

	template<typename I>
	typename RevIterator<I>::ref RevIterator<I>::operator*() {
		I tmp;

		tmp = *this;
		return *--tmp;
	}

	template<typename I>
	typename RevIterator<I>::const_ref RevIterator<I>::operator*() const {
		I tmp;

		tmp = *this;
		return *--tmp;
	}

	template<typename I>
	typename RevIterator<I>::pointer RevIterator<I>::operator->() {
		I tmp;

		tmp = *this;
		return &*--tmp;
	}

	template<typename I>
	typename RevIterator<I>::const_point RevIterator<I>::operator->() const {
		I tmp;

		tmp = *this;
		return &*--tmp;
	}
#pragma endregion

}
