//
// Created by Skipjack Adolph on 4/16/21.
//

#pragma once

#include "MapNode.hpp"
// todo #include "utils"

namespace ft {

	template<class T, class Compare = ft::less<typename T::first_type> >

	class MapIterator {

	/*************************************
	**	ALIASES							**
	*************************************/
	public:
		typedef T														value_type;
		typedef value_type &											reference;
		typedef value_type const &										const_reference;
		typedef value_type *											pointer;
		typedef value_type const *										const_pointer;
//		todo what is this tags? (never used)
		typedef ft::bidirectional_iterator_tag							iterator_category;
		typedef std::ptrdiff_t											difference_type;
		typedef MapNode<typename ft::remove_const<value_type>::type>	node;

	/*************************************
	**	COPLIEN FORM					**
	*************************************/
	public:
		MapIterator() : _data(NULL), _comp() {}
		MapIterator(const MapIterator &other) : _data(other._data), _comp(other._comp) {}
		const MapIterator &operator=(const MapIterator &other) {
			_data = other._data;
			_comp = other._comp;
			return *this;
		}
		~MapIterator() {}

	/*************************************
	**	CONSTRUCTORS					**
	*************************************/
	public:
		MapIterator(node *data) : _data(data), _comp() {}


//	todo what is it?
//		You need to add list_node and bidirectional_iterator as a friend for
//		a logical comparison operator

		template<class, class, class, class Alloc>
		friend
		class Map;

		template<class, class>
		friend
		class MapIterator;


	/*************************************
	**	OPERATORS						**
	*************************************/
	public:
		reference operator*() const { return _data->_data; }

		pointer operator->() const { return &_data->_data; }

		template<class U>
		friend bool operator==(const MapIterator<U, Compare> &lhs,
							   const MapIterator<U, Compare> &rhs) {
			return lhs._data == rhs._data;
		}

		MapIterator &operator++() {
			_data = next_node();
			return *this;
		}

		MapIterator operator++(int) {
			MapIterator tmp = *this;
			++(*this);
			return (tmp);
		}

		MapIterator &operator--() {
			_data = prev_node();
			return *this;
		}

		MapIterator operator--(int) {
			MapIterator tmp = *this;
			--(*this);
			return (tmp);
		}


	/*************************************
	**	FIELDS							**
	*************************************/
	private:
		node *		_data;
		Compare		_comp;

		node *next_node() {
			node *tmp = _data;
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

		node *prev_node() {
			node *tmp = _data;
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

	};

	template<class U, class Compare>
	bool operator!=(const MapIterator<U, Compare> &lhs,
					const MapIterator<U, Compare> &rhs) {
		return !(lhs == rhs);
	}
}
