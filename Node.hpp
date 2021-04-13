//
// Created by Skipjack Adolph on 4/13/21.
//

#pragma once

namespace ft {

	template <typename value_type>

	class Node {

	/*************************************
	**	COPLIEN FORM					**
	*************************************/
	public:
		Node();
		Node(Node const &other);
		Node &operator=(Node const &other);
		~Node() {}

	/*************************************
	**	CONSTRUCTORS					**
	*************************************/
	public:
		explicit Node(value_type const & value);
		Node(value_type const &val, Node *prev, Node *next= nullptr);

	/*************************************
	**	FIELDS							**
	*************************************/
	private:
		value_type			_data;
		Node<value_type> *	_next;
		Node<value_type> *	_prev;
	};


//	 TODO .ipp file here

	/**	COPLIEN FORM					**/
	template<typename value_type>
	Node<value_type>::Node() :
		_data(),
		_next(),
		_prev() {}

	template<typename value_type>
	Node<value_type>::Node(const Node &other) :
		_data(other._data),
		_next(other._next),
		_prev(other._prev) {}

	template<typename value_type>
	Node &Node<value_type>::operator=(const Node &other) {
		if (this != other) {
			_data = other._data;
			_next = other._next;
			_prev = other._prev;
		}
		return (*this);
	}

	/**	CONSTRUCTORS					**/
	template<typename value_type>
	Node<value_type>::Node(const value_type &value) :
		_data(value),
		_next(),
		_prev() {}

	template<typename value_type>
	Node<value_type>::Node(value_type const &val, Node *prev, Node *next) :
		_data(value),
		_prev(prev),
		_next(next) {}

}

#include <Node.ipp>
