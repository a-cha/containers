//
// Created by Skipjack Adolph on 4/13/21.
//

#pragma once

#include "Node.hpp"

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
Node<value_type> & Node<value_type>::operator=(const Node &other) {
	if (this != other) {
		_data = other._data;
		_next = other._next;
		_prev = other._prev;
	}
	return (*this);
}


/**	CONSTRUCTORS					**/
template<typename value_type>
Node<value_type>::Node(const value_type &val) :
		_data(val),
		_next(),
		_prev() {}

template<typename value_type>
Node<value_type>::Node(value_type const &val, Node *prev, Node *next) :
		_data(val),
		_prev(prev),
		_next(next) {}


//	TODO have I need more getters?
/**	GETTERS							**/
template<typename value_type>
value_type Node<value_type>::getData() const {
	return _data;
}

template<typename value_type>
Node<value_type> * Node<value_type>::getNext() const {
	return _next;
}

template<typename value_type>
Node<value_type> * Node<value_type>::getPrev() const {
	return _prev;
}


/**	METHODS							**/
template<typename value_type>
void Node<value_type>::pasteBefore(Node *n) {
	if (_prev) {
		n->_prev = _prev;
		_prev->_next = n;
	}
	n->_next = this;
	_prev = n;
}

template<typename value_type>
void Node<value_type>::pasteAfter(Node *n) {
	if (_next) {
		n->_next = _next;
		_next->_prev = n;
	}
	n->_prev = this;
	_next = n;
}

template<typename value_type>
void Node<value_type>::cut(void) {
	if (_prev)
		_prev->_next = _next;
	if (_next)
		_next->_prev = _prev;
	delete this;
}

template<typename value_type>
void Node<value_type>::swap(Node *n) {
	if (_prev == n) {
		if (n->_prev)
			n->_prev->_next = this;
		_prev = n->_prev;
		n->_prev = this;
		if (_next)
			_next->_prev = n;
		n->_next = _next;
		_next = n;
	}

	else if (_next == n) {
		if (_prev)
			_prev->_next = n;
		n->_prev = _prev;
		_prev = n;
		if (n->_next)
			n->_next->_prev = this;
		_next = n->_next;
		n->_next = this;
	}

	else {
		Node<value_type> *	next = _next;
		Node<value_type> *	prev = _prev;

		if (_prev)
			_prev->_next = n;
		if (_next)
			_next->_prev = n;
		_prev = n->_prev;
		_next = n->_next;
		if (n->_prev)
			n->_prev->_next = this;
		if (n->_next)
			n->_next->_prev = this;
		n->_prev = prev;
		n->_next = next;
	}
}

template<typename value_type>
void Node<value_type>::reverse() {
	Node<value_type> *tmp;

	tmp = _prev;
	_prev = _next;
	_next = tmp;
}

template<typename value_type>
void Node<value_type>::swapValues(Node *n) {
	value_type tmp;

	std::memmove(static_cast<void *>(&tmp), static_cast<void *>(&n->_data), 1);
	std::memmove(static_cast<void *>(&n->_data), static_cast<void *>(&_data), 1);
	std::memmove(static_cast<void *>(&_data), static_cast<void *>(&tmp), 1);
}
