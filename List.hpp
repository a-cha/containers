//
// Created by Skipjack Adolph on 4/13/21.
//

#pragma once

#include <Node.hpp>

namespace ft {

	template < typename T, class Alloc = std::allocator<T> >

	class List {

	/*************************************
	**	ALIASES							**
	*************************************/
	public:
		typedef T													value_type;
		typedef value_type &										ref;
		typedef value_type const &									const_ref;
		typedef value_type *										pointer;
		typedef value_type const *									const_pointer;
		typedef Node<value_type>									node_type;
		typedef node_type*											node_pointer;
		typedef ListIterator<value_type, pointer, ref>				iterator;
		typedef ListIterator<value_type, const_pointer, const_ref>	const_iterator;
		typedef ptrdiff_t											difference_type;
		typedef size_t												size_type;


	/*************************************
	**	COPLIEN FORM					**
	*************************************/
	public:
		List();
		List(List const &other);
		List &operator=(List const &other);
		~List();


	/*************************************
	**	CONSTRUCTORS					**
	*************************************/
	public:
		List(size_type n, const_ref val=value_type());
		List(iterator first, iterator last);


	/*************************************
	**	FIELDS							**
	*************************************/
	private:
		size_type               _size;
		node_pointer			_beginNode;
		node_pointer			_endNode;

	};

//	TODO .ipp file here
//	 #include <List.ipp>

	/**	COPLIEN FORM					**/
	template<typename T, class Alloc>
	List<T, Alloc>::List() :
		_beginNode(),
		_endNode(),
		m_size(0) {
			this->make_bounds();
		}

	template<typename T, class Alloc>
	List<T, Alloc>::List(const List &other) :
		_beginNode(),
		_endNode(),
		m_size(0) {
			this->make_bounds();
			this->assign(other.begin(), other.end());
		}

	template<typename T, class Alloc>
	List &List<T, Alloc>::operator=(const List &other) {
		this->assign(other.begin(), other.end());
		return (*this);
	}

	template<typename T, class Alloc>
	List<T, Alloc>::~List() {
		this->clear();
		delete this->_endNode;
	}


	/**	CONSTRUCTORS					**/
	template<typename T, class Alloc>
	List<T, Alloc>::List(size_type n, const_ref val=value_type()) :
		_beginNode(),
		_endNode(),
		m_size(0) {
			this->make_bounds();
			this->assign(n, val);
		}

	template<typename T, class Alloc>
	List<T, Alloc>::List(iterator first, iterator last) :
		_beginNode(),
		_endNode(),
		m_size(0) {
			this->make_bounds();
			this->assign(first, last);
		}


}
