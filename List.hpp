//
// Created by Skipjack Adolph on 4/13/21.
//

#pragma once

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
		typedef Alloc												allocator_type;
		typedef ListIterator<value_type, pointer, ref>				iterator;
		typedef ListIterator<value_type, const_pointer, const_ref>	const_iterator;
		typedef ptrdiff_t											difference_type;
		typedef size_t												size_type;

	/*************************************
	**	FIELDS							**
	*************************************/
	private:
		Node*                   _tail;
		size_type               _size;
		Alloc                   _alloc;
		ft::allocator<Node>     _allocNode;
	};

}
