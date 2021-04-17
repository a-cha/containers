//
// Created by Skipjack Adolph on 4/13/21.
//

#pragma once

#include "ListNode.hpp"

/**	COPLIEN FORM					**/
#pragma region Coplien

template<typename value_type>
ListNode<value_type>::ListNode() :
		_data(),
		_next(),
		_prev() {}

template<typename value_type>
ListNode<value_type>::ListNode(const ListNode &other) :
		_data(other._data),
		_next(other._next),
		_prev(other._prev) {}

template<typename value_type>
ListNode<value_type> & ListNode<value_type>::operator=(const ListNode &other) {
	if (this != other) {
		_data = other._data;
		_next = other._next;
		_prev = other._prev;
	}
	return (*this);
}
#pragma endregion

/**	CONSTRUCTORS					**/
#pragma region Constructors

template<typename value_type>
ListNode<value_type>::ListNode(const value_type &val) :
		_data(val),
		_next(),
		_prev() {}

template<typename value_type>
ListNode<value_type>::ListNode(value_type const &val, ListNode *prev, ListNode *next) :
		_data(val),
		_prev(prev),
		_next(next) {}
#pragma endregion

/**	GETTERS							**/
#pragma region Getters

template<typename value_type>
value_type & ListNode<value_type>::getData() {
	return _data;
}

template<typename value_type>
const value_type & ListNode<value_type>::getData() const {
	return _data;
}

template<typename value_type>
ListNode<value_type> * ListNode<value_type>::getNext() const {
	return _next;
}

template<typename value_type>
ListNode<value_type> * ListNode<value_type>::getPrev() const {
	return _prev;
}
#pragma endregion

/**	SETTERS							**/
#pragma region Setters

template<typename value_type>
void ListNode<value_type>::setNext(ListNode <value_type> *next) {
	_next = next;
}

template<typename value_type>
void ListNode<value_type>::setPrev(ListNode <value_type> *prev) {
	_prev = prev;
}
#pragma endregion

/**	METHODS							**/
#pragma region Methods

template<typename value_type>
void ListNode<value_type>::pasteBefore(ListNode *n) {
	if (_prev) {
		n->_prev = _prev;
		_prev->_next = n;
	}
	n->_next = this;
	_prev = n;
}

template<typename value_type>
void ListNode<value_type>::pasteAfter(ListNode *n) {
	if (_next) {
		n->_next = _next;
		_next->_prev = n;
	}
	n->_prev = this;
	_next = n;
}

template<typename value_type>
void ListNode<value_type>::cut(void) {
	if (_prev)
		_prev->_next = _next;
	if (_next)
		_next->_prev = _prev;
	delete this;
}

template<typename value_type>
void ListNode<value_type>::swap(ListNode *n) {
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
		ListNode<value_type> *	next = _next;
		ListNode<value_type> *	prev = _prev;

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
void ListNode<value_type>::reverse() {
	ListNode<value_type> *tmp;

	tmp = _prev;
	_prev = _next;
	_next = tmp;
}

template<typename value_type>
void ListNode<value_type>::detach(void)  {
	if (this->_prev)
		this->_prev->_next = this->_next;
	if (this->_next)
		this->_next->_prev = this->_prev;
}

template<typename value_type>
void ListNode<value_type>::swapValues(ListNode *n) {
	value_type tmp;

	std::memmove(static_cast<void *>(&tmp), static_cast<void *>(&n->_data), 1);
	std::memmove(static_cast<void *>(&n->_data), static_cast<void *>(&_data), 1);
	std::memmove(static_cast<void *>(&_data), static_cast<void *>(&tmp), 1);
}

#pragma endregion
