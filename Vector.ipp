//
// Created by Skipjack Adolph on 4/15/21.
//

#pragma once

#include "Algorithm.hpp"
#include "Vector.hpp"

namespace ft {

/**	COPLIEN FORM					**/
#pragma region Coplien

	template<typename T>
	Vector<T>::Vector() :
		_cont(),
		_capacity(0),
		_size(0) {}

	template<typename T>
	Vector<T>::Vector(const Vector &other) :
		_cont(),
		_capacity(0),
		_size(other._size) {
			reserve(other._capacity);
			std::memcpy(static_cast<void*>(_cont), static_cast<void*>(other._cont), other._size * sizeof(value_type));
		}

	template<typename T>
	Vector<T> &Vector<T>::operator=(const Vector &other) {
		clear();
		if (_capacity < other._capacity)
			reserve(other._capacity);
		std::memcpy(static_cast<void*>(_cont), static_cast<void*>(other._cont), other._size * sizeof(value_type));
		return *this;
	}

	template<typename T>
	Vector<T>::~Vector() {
		clear();
		if (_cont)
			::operator delete(_cont);
	}
#pragma endregion

/**	CONSTRUCTORS					**/
#pragma region Constructors

	template<typename T>
	Vector<T>::Vector(Vector::size_type n, const_reference val) :
		_cont(),
		_capacity(0),
		_size(0) {
			assign(n, val);
		}

	template<typename T>
	Vector<T>::Vector(Vector::iterator first, Vector::iterator last) :
		_cont(),
		_capacity(0),
		_size(0) {
			assign(first, last);
		}
#pragma endregion

/**	METHODS							**/
#pragma region Iterators

	template<typename T>
	typename Vector<T>::iterator Vector<T>::begin() {
		return iterator(this->_cont);
	}

	template<typename T>
	typename Vector<T>::const_iterator Vector<T>::begin() const {
		return const_iterator(this->_cont);
	}

	template<typename T>
	typename Vector<T>::reverse_iterator Vector<T>::rbegin() {
		return reverse_iterator(this->end());
	}

	template<typename T>
	typename Vector<T>::const_reverse_iterator Vector<T>::rbegin() const {
		return const_reverse_iterator(this->end());
	}

	template<typename T>
	typename Vector<T>::iterator Vector<T>::end() {
		return iterator(&(this->_cont[this->_size]));
	}

	template<typename T>
	typename Vector<T>::const_iterator Vector<T>::end() const {
		return const_iterator(&(this->_cont[this->_size]));
	}

	template<typename T>
	typename Vector<T>::reverse_iterator Vector<T>::rend() {
		return reverse_iterator(this->begin());
	}

	template<typename T>
	typename Vector<T>::const_reverse_iterator Vector<T>::rend() const {
		return const_reverse_iterator(this->begin());
	}
#pragma endregion

#pragma region Capacity

	template<typename T>
	typename Vector<T>::size_type Vector<T>::size() const {
		return _size;
	}

	template<typename T>
	typename Vector<T>::size_type Vector<T>::max_size() const {
		return std::numeric_limits<size_type>::max() / sizeof(value_type);
	}

	template<typename T>
	void Vector<T>::resize(typename Vector<T>::size_type size, value_type val) {
		if (size > _capacity)
			reserve(size);

		if (size > _size) {
			for (size_type i = _size; i < size; ++i)
				copy_construct(i, val);
			_size = size;
		} else if (size < _size) {
			for (size_type i = size; i < _size; ++i)
				_cont[i].value_type::~value_type();
			_size = size;
		}
	}

	template<typename T>
	typename Vector<T>::size_type Vector<T>::capacity() const {
		return _capacity;
	}

	template<typename T>
	bool Vector<T>::empty() const {
		return _size == 0;
	}

	template<typename T>
	void Vector<T>::reserve(Vector::size_type size) {
		if (_capacity == 0) {
			size = (size > 128) ? size : 128;
			_cont = static_cast<value_type*>(::operator new(sizeof(value_type) * size));
			_capacity = size;
		}

		else if (size > _capacity) {
			size = (size > _capacity * 2) ? size : _capacity * 2;
			value_type *tmp = static_cast<value_type*>(::operator new(sizeof(value_type) * size));
			if (_cont) {
				for (size_t i = 0; i < _size; ++i)
					new(&tmp[i]) value_type(_cont[i]);
				::operator delete(_cont);
			}
			_cont = tmp;
			_capacity = size;
		}
	}
#pragma endregion

#pragma region Element access

	template<typename T>
	typename Vector<T>::ref Vector<T>::operator[](Vector::size_type idx) {
		return this->_cont[idx];
	}

	template<typename T>
	typename Vector<T>::const_ref Vector<T>::operator[](Vector::size_type idx) const {
		return this->_cont[idx];
	}

	template<typename T>
	typename Vector<T>::ref Vector<T>::at(Vector::size_type idx) {
		if (idx >= this->_size)
			throw std::out_of_range();
		return this->_cont[idx];
	}

	template<typename T>
	typename Vector<T>::const_ref Vector<T>::at(Vector::size_type idx) const {
		if (idx >= this->_size)
			throw std::out_of_range();
		return this->_cont[idx];
	}

	template<typename T>
	typename Vector<T>::ref Vector<T>::front() {
		return this->_cont[0];
	}

	template<typename T>
	typename Vector<T>::const_ref Vector<T>::front() const {
		return this->_cont[0];
	}

	template<typename T>
	typename Vector<T>::ref Vector<T>::back() {
		return this->_cont[this->_size - 1];
	}

	template<typename T>
	typename Vector<T>::const_ref Vector<T>::back() const {
		return this->_cont[this->_size - 1];
	}
#pragma endregion

#pragma region Modifiers

}
