//
// Created by Skipjack Adolph on 4/15/21.
//

#pragma once

#include "VectorIterator.hpp"
#include "RevIterator.hpp"
#include <limits>

namespace ft {

	template<typename T>

	class Vector {

	/*************************************
	**	ALIASES							**
	*************************************/
	public:
		typedef T									value_type;
		typedef T *									pointer;
		typedef T const *							const_point;
		typedef T &									ref;
		typedef T const &							const_ref;
		typedef VectorIterator<value_type>			iterator;
		typedef VectorIterator<value_type const>	const_iter;
		typedef ReverseIterator<iterator>			reverse_iter;
		typedef ReverseIterator<const_iter>			const_reverse_iter;
		typedef std::ptrdiff_t						difference_type;
		typedef unsigned long						size_type;

	/*************************************
	**	COPLIEN FORM					**
	*************************************/
	public:
		Vector();
		Vector(Vector const &other);
		Vector &operator=(Vector const &other);
		virtual ~Vector();

	/*************************************
	**	CONSTRUCTORS					**
	*************************************/
	public:
		Vector(size_type n, const_ref val=value_type());
		Vector(iterator first, iterator last);

	/*************************************
	**	METHODS							**
	*************************************/
	public:
		/**	Iterators					*/
		iterator			begin();
		const_iter			begin() const;
		reverse_iter		rbegin();
		const_reverse_iter	rbegin() const;
		iterator			end();
		const_iter			end() const;
		reverse_iter		rend();
		const_reverse_iter	rend() const;

		/**	Capacity					*/
		size_type			size() const;
		size_type			max_size() const;
		void				resize(size_type size, value_type val=value_type());
		size_type			capacity() const;
		bool				empty() const;
		void				reserve(size_type size);

		/**	Element access				*/
		ref					operator[](size_type idx);
		const_ref			operator[](size_type idx) const;
		ref					at(size_type idx);
		const_ref			at(size_type idx) const;
		ref					front();
		const_ref			front() const;
		ref					back();
		const_ref			back() const;

		/**	Modifiers					*/
		void assign(iterator first, iterator last) {
			size_t length = last - first;
			if (length > this->_capacity)
				this->reserve(length);
			size_t i = 0;
			while (first != last) {
				if (i >= this->_size)
					this->copy_construct(i, *first);
				else
					this->_cont[i] = *first;
				++first;
				++i;
			}
			while (i < this->_size)
				this->_cont[i++].value_type::~value_type();
			this->_size = length;
		}

		void assign(const_iter first, const_iter last) {
			size_t length = last - first;
			if (length > this->_capacity)
				this->reserve(length);
			size_t i = 0;
			while (first != last) {
				if (i >= this->_size)
					this->copy_construct(i, *first);
				else
					this->_cont[i] = *first;
				++first;
				++i;
			}
			while (i < this->_size)
				this->_cont[i++].value_type::~value_type();
			this->_size = length;
		}
		void assign(size_type size, const_ref val) {
			if (size > this->_capacity)
				this->reserve(size);
			size_t i = 0;
			while (i < size) {
				if (i >= this->_size)
					this->copy_construct(i, val);
				else
					this->_cont[i] = val;
				++i;
			}
			while (i < this->_size)
				this->_cont[i++].value_type::~value_type();
			this->_size = size;
		}
		void push_back(const_ref val) {
			if (this->_size == this->_capacity)
				this->reserve(this->_capacity * 2);
			new(&this->_cont[this->_size++]) value_type(val);
		}

		void pop_back() {
			this->_cont[--this->_size].value_type::~value_type();
		}
		iterator insert(iterator position, const_ref val) {
			this->insert(position, 1, val);
			return ++position;
		}

		void insert(iterator position, size_type size, const_ref val) {
			iterator it = this->begin();
			if (this->_size + size >= this->_capacity)
				this->reserve(this->_size + size);
			size_type i = 0;
			while (it != position) {
				++it;
				++i;
			}
			// std::memmove
			for (size_type j = this->_size; j >= 1 && j >= i; j--)
				this->copy_construct(i + j + size - 1, this->_cont[j - 1]);
			for (size_type j = 0; j < size; j++)
				this->copy_construct(i + j, val);
			this->_size += size;
		}
		void insert(iterator position, iterator first, iterator last) {
			size_type size = last - first;
			iterator it = this->begin();
			if (this->_size + size >= this->_capacity)
				this->reserve(this->_size + size);
			size_type i = 0;
			while (it != position) {
				++it;
				++i;
			}
			// std::memmove
			for (size_type j = this->_size - 1; j > i + 1; j++)
				this->copy_construct(i + j + size, this->_cont[+ j - 1]);
			for (size_type j = 0; j < size; j++)
				this->copy_construct(i + j, *first++);
			this->_size += size;
		}
		iterator erase(iterator position) {
			iterator tmp(position);
			++tmp;
			return this->erase(position, tmp);
		}

		iterator erase(iterator first, iterator last) {
			iterator it = this->begin();
			size_type i = 0;
			while (it != first) {
				++it;
				++i;
			}
			if (it == this->end())
				return this->end();
			size_type returnPosition = i;
			size_type deletedElements = 0;
			size_type stopPos = i;
			while (first != last) {
				(*first++).value_type::~value_type();
				++deletedElements;
				++stopPos;
			}
			// std::memmove ?
			for ( ; stopPos < this->_size; ++stopPos)
				this->copy_construct(i++, this->_cont[stopPos]);
			this->_size -= deletedElements;
			return iterator(&this->_cont[returnPosition]);
		}
		void swap(Vector &other) {
			ft::swap(this->_cont, other._cont);
			ft::swap(this->_capacity, other._capacity);
			ft::swap(this->_size, other._size);
		}

		void clear() {
			for (size_type i = 0; i < this->_size; i++)
				this->_cont[i].value_type::~value_type();
			this->_size = 0;
		}

	private:
		pointer		_cont;
		size_type	_size;
		size_type	_capacity;

		void copy_construct(size_type idx, const_ref val) {
			new(&this->_cont[idx]) value_type(val);
		}
	};



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
}

#include "Vector.ipp"
