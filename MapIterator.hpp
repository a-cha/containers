//
// Created by Skipjack Adolph on 4/16/21.
//

#pragma once

#include "MapNode.hpp"
#include "Algorithm.hpp"

namespace ft {

	template<class T, class Compare = ft::less<typename T::first_type> >

	class MapIterator {

	/*************************************
	**	ALIASES							**
	*************************************/
	public:
		typedef T													value_type;
		typedef value_type &										ref;
		typedef value_type const &									const_ref;
		typedef value_type *										pointer;
		typedef value_type const *									const_point;
		typedef std::ptrdiff_t										difference_type;
		typedef MapNode<typename ft::is_const<value_type>::type>	node;

	/*************************************
	**	COPLIEN FORM					**
	*************************************/
	public:
		MapIterator();
		MapIterator(const MapIterator & other);
		const MapIterator &operator=(const MapIterator & other);
		~MapIterator();

	/*************************************
	**	CONSTRUCTORS					**
	*************************************/
	public:
		MapIterator(node *data);

	/*************************************
	**	OPERATORS						**
	*************************************/
	public:
		ref				operator*() const;
		pointer			operator->() const;
		MapIterator &	operator++();
		MapIterator		operator++(int);
		MapIterator &	operator--();
		MapIterator		operator--(int);

		template<class, class, class, class Alloc>
		friend class Map;
		template<class, class>
		friend class MapIterator;

		friend bool operator==(const MapIterator<T, Compare>& lhs, const MapIterator<T, Compare>& rhs) {
			return lhs._data == rhs._data;
		};
		friend bool operator!=(const MapIterator<T, Compare>& lhs, const MapIterator<T, Compare>& rhs) {
			return !(lhs == rhs);
		}

	/*************************************
	**	FIELDS							**
	*************************************/
	private:
		node *		_data;
		Compare		_comp;

		/**	Utils						*/
		node *next_node();
		node *prev_node();
	};
}

#include "MapIterator.ipp"
