//
// Created by Skipjack Adolph on 4/16/21.
//

#pragma once

#include <sstream>
#include <typeinfo>
#include <iostream>
#include <limits>
#include <cstddef>

namespace ft {

	template<class Pair, class Alloc = std::allocator<Pair> >

	class MapNode {

	/*************************************
	**	ALIASES							**
	*************************************/
	public:
		typedef Pair										value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef std::ptrdiff_t								difference_type;
		typedef std::size_t									size_type;

	/*************************************
	**	COPLIEN FORM					**
	*************************************/
	public:
		MapNode();
		MapNode(const MapNode &other);
		const MapNode&operator=(const MapNode &rhs);
		~MapNode();

	/*************************************
	**	CONSTRUCTORS					**
	*************************************/
	public:
		MapNode(const value_type &data);

	/*************************************
	**	FIELDS							**
	*************************************/
	private:
		typedef typename			allocator_type::template
		rebind<value_type>::other	pair_alloc;
		typedef typename			pair_alloc::pointer _pair_pointer;
		allocator_type 	_alloc;
		_pair_pointer	_pair_init;
	public:
		MapNode*		_parent;
		MapNode*		_right;
		MapNode*		_left;
		int 			_height;
		value_type		_data;
	};
}

#include "MapNode.ipp"
