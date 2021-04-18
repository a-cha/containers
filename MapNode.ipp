//
// Created by Skipjack Adolph on 4/16/21.
//

#pragma once

namespace ft {

/**	COPLIEN FORM					**/
#pragma region Coplien

	template<class Pair, class Alloc>
	MapNode<Pair, Alloc>::MapNode() :
			_parent(),
			_right(),
			_left(),
			_height(1),
			_data() {
		_pair_init = _alloc.allocate(1);
		_alloc.construct(_pair_init, _data);
	}

	template<class Pair, class Alloc>
	MapNode<Pair, Alloc>::MapNode(const MapNode & other) :
		_alloc(other._alloc),
		_pair_init(other._pair_init),
		_parent(other._parent),
		_right(other._right),
		_left(other._left),
		_height(other._height),
		_data(other._data) {
			_pair_init = _alloc.allocate(1);
			_alloc.construct(_pair_init, _data);
		}

	template<class Pair, class Alloc>
	const MapNode<Pair, Alloc> & MapNode<Pair, Alloc>::operator=(const MapNode & rhs) {
		if (*this != *rhs) {
			_alloc = rhs._alloc;
			_pair_init = rhs._pair_init;
			_parent = rhs._parent;
			_right = rhs._right;
			_left = rhs._left;
			_height = rhs._height;
			_data = rhs._data;
		}
		return (*this);
	}

	template<class Pair, class Alloc>
	MapNode<Pair, Alloc>::~MapNode() {
		_alloc.destroy(_pair_init);
		_alloc.deallocate(_pair_init, 1);
	}
#pragma endregion

/**	CONSTRUCTORS					**/
#pragma region Constructors

	template<class Pair, class Alloc>
	MapNode<Pair, Alloc>::MapNode(const value_type & data) :
		_parent(),
		_right(),
		_left(),
		_height(1),
		_data(data) {
			_pair_init = _alloc.allocate(1);
			_alloc.construct(_pair_init, _data);
		}
#pragma endregion

}
