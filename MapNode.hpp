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
		MapNode(): _parent(NULL), _right(NULL), _left(NULL), _height(1), _data() {
			_pair_init = _alloc.allocate(1);
			_alloc.construct(_pair_init, _data);
		}
		MapNode(const MapNode &other)
				:_alloc(other._alloc), _pair_init(other._pair_init), _parent(other._parent),
				 _right(other._right), _left(other._left), _height(other._height), _data(other._data) {
			_pair_init = _alloc.allocate(1);
			_alloc.construct(_pair_init, _data);
		}
		const MapNode&operator=(const MapNode &rhs) {
			if (*this == *rhs)
				return (*this);
			_alloc = rhs._alloc;
			_pair_init = rhs._pair_init;
			_parent = rhs._parent;
			_right = rhs._right;
			_left = rhs._left;
			_height = rhs._height;
			_data = rhs._data;
			return (*this);
		}
		~MapNode() {
			_alloc.destroy(_pair_init);
			_alloc.deallocate(_pair_init, 1);
		}

	/*************************************
	**	CONSTRUCTORS					**
	*************************************/
	public:
		MapNode(const value_type &data): _parent(NULL), _right(NULL), _left(NULL), _height(1), _data(data) {
			_pair_init = _alloc.allocate(1);
			_alloc.construct(_pair_init, _data);
		}

	/*************************************
	**	FIELDS							**
	*************************************/
	private:
		typedef typename allocator_type::template
		rebind<value_type>::other pair_alloc;
		typedef typename pair_alloc::pointer _pair_pointer;
		allocator_type 	_alloc;
		_pair_pointer	_pair_init;

//		todo: why these fields are public
	public:
		MapNode*		_parent;
		MapNode*		_right;
		MapNode*		_left;
		int 			_height;
		value_type		_data;
	};
}
