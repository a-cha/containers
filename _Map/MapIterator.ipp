//
// Created by Skipjack Adolph on 4/18/21.
//

#pragma once

namespace ft {

/**	COPLIEN FORM					**/
#pragma region Coplien

	template<class T, class Compare>
	MapIterator<T, Compare>::MapIterator() :
		_data(),
		_comp() {}

	template<class T, class Compare>
	MapIterator<T, Compare>::MapIterator(const MapIterator & other) :
		_data(other._data),
		_comp(other._comp) {}

	template<class T, class Compare>
	const MapIterator<T, Compare> & MapIterator<T, Compare>
	        ::operator=(const MapIterator &other) {
		_data = other._data;
		_comp = other._comp;
		return *this;
	}

	template<class T, class Compare>
	MapIterator<T, Compare>::~MapIterator() {}
#pragma endregion

/**	CONSTRUCTORS					**/
#pragma region Constructors

	template<class T, class Compare>
	MapIterator<T, Compare>::MapIterator(MapIterator::node *data) :
		_data(data),
		_comp() {}
#pragma endregion

#pragma region Operators

	template<class T, class Compare>
	typename MapIterator<T, Compare>::ref MapIterator<T, Compare>
	        ::operator*() const {
		return _data->_data;
	}

	template<class T, class Compare>
	typename MapIterator<T, Compare>::pointer MapIterator<T, Compare>
	        ::operator->() const {
		return &_data->_data;
	}

	template<class T, class Compare>
	MapIterator<T, Compare> &MapIterator<T, Compare>::operator++() {
		_data = next_node();
		return *this;
	}

	template<class T, class Compare>
	MapIterator<T, Compare> MapIterator<T, Compare>::operator++(int) {
		MapIterator tmp;

		tmp = *this;
		++(*this);
		return tmp;
	}

	template<class T, class Compare>
	MapIterator<T, Compare> &MapIterator<T, Compare>::operator--() {
		_data = prev_node();
		return *this;
	}

	template<class T, class Compare>
	MapIterator<T, Compare> MapIterator<T, Compare>::operator--(int) {
		MapIterator tmp;

		tmp = *this;
		--(*this);
		return tmp;
	}
#pragma endregion

/** UTILS							**/
#pragma region Utils

	template<class T, class Compare>
	typename MapIterator<T, Compare>::node * MapIterator<T, Compare>::next_node() {
		node * tmp;

		tmp = _data;
		if (tmp->_height == 0) {
			if (tmp->_parent->_right == tmp)
				return tmp;
			return tmp->_parent;
		} else if (tmp->_right) {
			tmp = tmp->_right;
			while (tmp->_left)
				tmp = tmp->_left;
		} else {
			while (!_comp(this->_data->_data.first, tmp->_data.first))
				tmp = tmp->_parent;
		}
		return (tmp);
	}

	template<class T, class Compare>
	typename MapIterator<T, Compare>::node * MapIterator<T, Compare>::prev_node() {
		node * tmp;

		tmp = _data;
		if (tmp->_height == 0) {
			if (tmp->_parent->_left == tmp)
				return tmp;
			return tmp->_parent;
		} else if (tmp->_left) {
			tmp = tmp->_left;
			while (tmp->_right)
				tmp = tmp->_right;
		} else {
			while (!_comp(tmp->_data.first, this->_data->_data.first))
				tmp = tmp->_parent;
		}
		return (tmp);
	}
#pragma endregion

}
