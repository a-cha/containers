//
// Created by Skipjack Adolph on 4/15/21.
//

#pragma once

#include "Algorithm.hpp"

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
	Vector<T>::Vector(Vector::size_type n, const_ref val) :
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
		return iterator(_cont);
	}

	template<typename T>
	typename Vector<T>::const_iterator Vector<T>::begin() const {
		return const_iterator(_cont);
	}

	template<typename T>
	typename Vector<T>::reverse_iterator Vector<T>::rbegin() {
		return reverse_iterator(end());
	}

	template<typename T>
	typename Vector<T>::const_reverse_iter Vector<T>::rbegin() const {
		return const_reverse_iter(end());
	}

	template<typename T>
	typename Vector<T>::iterator Vector<T>::end() {
		return &_cont[_size];
//		return iterator(&(_cont[_size]));
	}

	template<typename T>
	typename Vector<T>::const_iterator Vector<T>::end() const {
		return &_cont[_size];
//		return const_iterator(&(_cont[_size]));
	}

	template<typename T>
	typename Vector<T>::reverse_iterator Vector<T>::rend() {
		return reverse_iterator(begin());
	}

	template<typename T>
	typename Vector<T>::const_reverse_iter Vector<T>::rend() const {
		return const_reverse_iter(begin());
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
				copy(i, val);
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
		return _cont[idx];
	}

	template<typename T>
	typename Vector<T>::const_ref Vector<T>::operator[](Vector::size_type idx) const {
		return _cont[idx];
	}

	template<typename T>
	typename Vector<T>::ref Vector<T>::at(Vector::size_type idx) {
		if (idx >= _size)
			throw std::out_of_range("Index out of vector size");
		return _cont[idx];
	}

	template<typename T>
	typename Vector<T>::const_ref Vector<T>::at(Vector::size_type idx) const {
		if (idx >= _size)
			throw std::out_of_range("Index out of vector size");
		return _cont[idx];
	}

	template<typename T>
	typename Vector<T>::ref Vector<T>::front() {
		return _cont[0];
	}

	template<typename T>
	typename Vector<T>::const_ref Vector<T>::front() const {
		return _cont[0];
	}

	template<typename T>
	typename Vector<T>::ref Vector<T>::back() {
		return _cont[_size - 1];
	}

	template<typename T>
	typename Vector<T>::const_ref Vector<T>::back() const {
		return _cont[_size - 1];
	}
#pragma endregion

#pragma region Modifiers

	template<typename T>
	void Vector<T>::assign(Vector::iterator first, Vector::iterator last) {
		size_t len;
		size_t i;

		len = last - first;
		i = 0;
		if (len > _capacity)
			reserve(len);
		while (first != last) {
			if (i >= _size)
				copy(i, *first);
			else
				_cont[i] = *first;
			++first;
			++i;
		}
		while (i < _size)
			_cont[i++].value_type::~value_type();
		_size = len;
	}

	template<typename T>
	void Vector<T>::assign(Vector::const_iterator first, Vector::const_iterator last) {
		size_t len;
		size_t i;

		len = last - first;
		i = 0;
		if (len > _capacity)
			reserve(len);
		while (first != last) {
			if (i >= _size) copy(i, *first);
			else _cont[i] = *first;
			++first;
			++i;
		}
		while (i < _size)
			_cont[i++].value_type::~value_type();
		_size = len;
	}

	template<typename T>
	void Vector<T>::assign(Vector::size_type size, Vector::const_ref val) {
		size_t i;

		i = 0;
		if (size > _capacity)
			reserve(size);
		while (i < size) {
			if (i >= _size) copy(i, val);
			else _cont[i] = val;
			++i;
		}
		while (i < _size)
			_cont[i++].value_type::~value_type();
		_size = size;
	}

	template<typename T>
	void Vector<T>::push_back(const_ref val) {
		if (_size == _capacity)
			reserve(_capacity * 2);

		new(&_cont[_size++]) value_type(val);
	}

	template<typename T>
	void Vector<T>::pop_back() {
		_cont[--_size].value_type::~value_type();
	}

	template<typename T>
	typename Vector<T>::iterator Vector<T>::insert
						(Vector::iterator pos, const_ref val) {
		insert(pos, 1, val);
		return ++pos;
	}

	template<typename T>
	void Vector<T>::insert(iterator pos, size_type size, const_ref val) {
		iterator it;
		size_type i;

		it = begin();
		i = 0;
		if (_size + size >= _capacity)
			reserve(_size + size);
		while (it != pos) {
			++it;
			++i;
		}
		for (size_type j = _size; j >= 1 && j >= i; j--)
			copy(i + j + size - 1, _cont[j - 1]);
		for (size_type j = 0; j < size; j++)
			copy(i + j, val);
		_size += size;
	}

	template<typename T>
	void Vector<T>::insert(iterator pos, iterator first, iterator last) {
		size_type size;
		iterator it;
		size_type i;

		size = last - first;
		it = begin();
		i = 0;
		if (_size + size >= _capacity)
			reserve(_size + size);
		while (it != pos) {
			++it;
			++i;
		}
		for (size_type j = _size - 1; j > i + 1; j++)
			copy(i + j + size, _cont[+j - 1]);
		for (size_type j = 0; j < size; j++)
			copy(i + j, *first++);
		_size += size;
	}

	template<typename T>
	typename Vector<T>::iterator Vector<T>::erase(Vector::iterator pos)  {
		iterator tmp;

		tmp = pos;
		++tmp;
		return erase(pos, tmp);
	}

	template<typename T>
	typename Vector<T>::iterator Vector<T>::erase
						(Vector::iterator first, Vector::iterator last) {
		iterator start;
		size_type i;
		size_type removed;

		start = begin();
		i = 0;
		removed = 0;
		while (start != first) {
			++start;
			++i;
		}
		if (start == end())
			return (end());
		size_type ret = i;
		size_type finish = i;
		while (first != last) {
			(*first++).value_type::~value_type();
			++removed;
			++finish;
		}
		for ( ; finish < _size; ++finish)
			copy(i++, _cont[finish]);
		_size -= removed;
		return (iterator(&_cont[ret]));
	}

	template<typename T>
	void Vector<T>::swap(Vector &other) {
		ft::swap(_cont, other._cont);
		ft::swap(_capacity, other._capacity);
		ft::swap(_size, other._size);
	}

	template<typename T>
	void Vector<T>::clear() {
		for (size_type i = 0; i < _size; i++)
			_cont[i].value_type::~value_type();
		_size = 0;
	}
#pragma endregion

/**	OPERATORS						**/
#pragma region Operators

	template<typename T>
	bool operator==(Vector<T> const &lhs, Vector<T> const &rhs) {
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}

	template<typename T>
	bool operator!=(Vector<T> const &lhs, Vector<T> const &rhs) {
		return !(lhs == rhs);
	}

	template<typename T>
	bool operator<(Vector<T> const &lhs, Vector<T> const &rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<typename T>
	bool operator<=(Vector<T> const &lhs, Vector<T> const &rhs) {
		return !(rhs < lhs);
	}

	template<typename T>
	bool operator>(Vector<T> const &lhs, Vector<T> const &rhs) {
		return rhs < lhs;
	}

	template<typename T>
	bool operator>=(Vector<T> const &lhs, Vector<T> const &rhs) {
		return !(lhs < rhs);
	}

	template<typename T>
	void swap(Vector<T> &x, Vector<T> &y) {
		x.swap(y);
	}
#pragma endregion

/**	UTILS							**/
#pragma region Utils

	template<typename T>
	void Vector<T>::copy(Vector::size_type ind, const_ref data) {
		new(&_cont[ind]) value_type(data);
	}
#pragma endregion

}
