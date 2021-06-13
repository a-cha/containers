//
// Created by Skipjack Adolph on 4/15/21.
//

#pragma once

#include "VectorIterator.hpp"
#include "../utils/RevIterator.hpp"
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
		typedef VectorIterator<value_type const>	const_iterator;
		typedef RevIterator<iterator>				reverse_iterator;
		typedef RevIterator<const_iterator>				const_reverse_iter;
		typedef std::ptrdiff_t						difference_type;
		typedef unsigned long						size_type;

	/*************************************
	**	COPLIEN FORM					**
	*************************************/
	public:
		Vector();
		Vector(Vector const &other);
		Vector & operator=(Vector const &other);
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
		const_iterator		begin() const;
		reverse_iterator	rbegin();
		const_reverse_iter	rbegin() const;
		iterator			end();
		const_iterator		end() const;
		reverse_iterator	rend();
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
		void				assign(iterator first, iterator last);
		void				assign(const_iterator first, const_iterator last);
		void				assign(size_type size, const_ref val);
		void				push_back(const_ref val);
		void				pop_back();
		iterator			insert(iterator pos, const_ref val);
		void				insert(iterator pos, size_type size, const_ref val);
		void				insert(iterator pos, iterator first, iterator last);
		iterator			erase(iterator pos);
		iterator			erase(iterator first, iterator last);
		void				swap(Vector &other);
		void				clear();

	/*************************************
	**	FIELDS							**
	*************************************/
	private:
		pointer				_cont;
		size_type			_size;
		size_type			_capacity;

		void				copy(size_type ind, const_ref data);
	};


	template<typename T>
	bool operator==(Vector<T> const &lhs, Vector<T> const &rhs);

	template<typename T>
	bool operator!=(Vector<T> const &lhs, Vector<T> const &rhs);

	template<typename T>
	bool operator<(Vector<T> const &lhs, Vector<T> const &rhs);

	template<typename T>
	bool operator<=(Vector<T> const &lhs, Vector<T> const &rhs);

	template<typename T>
	bool operator>(Vector<T> const &lhs, Vector<T> const &rhs);

	template<typename T>
	bool operator>=(Vector<T> const &lhs, Vector<T> const &rhs);

	template<typename T>
	void swap(Vector<T> &x, Vector<T> &y);

}

#include "Vector.ipp"
