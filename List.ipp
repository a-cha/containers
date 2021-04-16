//
// Created by Skipjack Adolph on 4/13/21.
//

#pragma once

#include "List.hpp"
#include "Algorithm.hpp"

/**	COPLIEN FORM					**/
#pragma region Coplien

template<typename T, class Alloc>
List<T, Alloc>::List() :
		_beginNode(),
		_endNode(),
		_size(0) {
	this->make_bounds();
}

template<typename T, class Alloc>
List<T, Alloc>::List(const List &other) :
		_beginNode(),
		_endNode(),
		_size(0) {
	this->make_bounds();
	this->assign(other.begin(), other.end());
}

template<typename T, class Alloc>
List<T, Alloc> & List<T, Alloc>::operator=(const List &other) {
	this->assign(other.begin(), other.end());
	return (*this);
}

template<typename T, class Alloc>
List<T, Alloc>::~List() {
	this->clear();
	delete this->_endNode;
}
#pragma endregion

/**	CONSTRUCTORS					**/
#pragma region Constructors

template<typename T, class Alloc>
List<T, Alloc>::List(size_type n, const_ref val) :
		_beginNode(),
		_endNode(),
		_size(0) {
	this->make_bounds();
	this->assign(n, val);
}

template<typename T, class Alloc>
List<T, Alloc>::List(iterator first, iterator last) :
		_beginNode(),
		_endNode(),
		_size(0) {
	this->make_bounds();
	this->assign(first, last);
}
#pragma endregion

/**	METHODS							**/
#pragma region Iterators

template<typename T, class Alloc>
typename List<T, Alloc>::iterator List<T, Alloc>::begin() {
	return (iterator(this->_beginNode));
}

template<typename T, class Alloc>
typename List<T, Alloc>::const_iterator List<T, Alloc>::begin() const {
	return (const_iterator(this->_beginNode));
}

template<typename T, class Alloc>
typename List<T, Alloc>::iterator List<T, Alloc>::end() {
	return (iterator(this->_endNode));
}

template<typename T, class Alloc>
typename List<T, Alloc>::const_iterator List<T, Alloc>::end() const {
	return (const_iterator(this->_endNode));
}

template<typename T, class Alloc>
typename List<T, Alloc>::rev_iterator List<T, Alloc>::rbegin() {
	return (rev_iterator(this->end()));
}

template<typename T, class Alloc>
typename List<T, Alloc>::const_rev_iterator List<T, Alloc>::rbegin() const {
	return (const_rev_iterator(this->end()));
}

template<typename T, class Alloc>
typename List<T, Alloc>::rev_iterator List<T, Alloc>::rend() {
	return (rev_iterator(this->begin()));
}

template<typename T, class Alloc>
typename List<T, Alloc>::const_rev_iterator List<T, Alloc>::rend() const {
	return (const_rev_iterator(this->begin()));
}
#pragma endregion

#pragma region Capacity

template<typename T, class Alloc>
bool List<T, Alloc>::empty() const {
	return (this->_size == 0);
}

template<typename T, class Alloc>
typename List<T, Alloc>::size_type List<T, Alloc>::size() const {
	return (this->_size);
}

template<typename T, class Alloc>
typename List<T, Alloc>::size_type List<T, Alloc>::max_size() const {
	return (ft::min((size_type) std::numeric_limits<difference_type>::max(),
					std::numeric_limits<size_type>::max() / (sizeof(node_type) - sizeof(pointer))));
}
#pragma endregion

#pragma region Element access
template<typename T, class Alloc>
typename List<T, Alloc>::ref List<T, Alloc>::front() {
	return (this->_beginNode->value());
}

template<typename T, class Alloc>
typename List<T, Alloc>::const_ref List<T, Alloc>::front() const {
	return (this->_beginNode->value());
}

template<typename T, class Alloc>
typename List<T, Alloc>::ref List<T, Alloc>::back() {
	return (this->_endNode->previous()->value());
}

template<typename T, class Alloc>
typename List<T, Alloc>::const_ref List<T, Alloc>::back() const {
	return (this->_endNode->previous()->value());
}
#pragma endregion

#pragma region Modifiers
template<typename T, class Alloc>
void List<T, Alloc>::assign(iterator first, iterator last) {
	this->clear();
	while (first != last)
		this->push_back(*first++);
}

template<typename T, class Alloc>
void List<T, Alloc>::assign(const_iterator first, const_iterator last) {
	this->clear();
	while (first != last)
		this->push_back(*first++);
}

template<typename T, class Alloc>
void List<T, Alloc>::assign(size_type size, const_ref val) {
	this->clear();
	for (size_type i = 0; i < size; i++)
		this->push_back(val);
}

template<typename T, class Alloc>
void List<T, Alloc>::push_front(const_ref val) {
	node_pointer tmp = new node_type(val);
	if (this->_size == 0)
		this->_endNode->insert_before(tmp);
	else
		this->_beginNode->insert_before(tmp);
	this->_beginNode = tmp;
	++this->_size;
}

template<typename T, class Alloc>
void List<T, Alloc>::pop_front() {
	if (this->_size == 1) {
		delete this->_beginNode;
		this->_beginNode = this->_endNode;
		this->_endNode->previous() = nullptr;
	} else if (this->_size >= 1) {
		node_pointer tmp = this->_beginNode->next();
		this->_beginNode->disconnect();
		delete this->_beginNode;
		this->_beginNode = tmp;
	}
	--this->_size;
}

template<typename T, class Alloc>
void List<T, Alloc>::push_back(const_ref val) {
	node_pointer tmp = new node_type(val);
	this->_endNode->insert_before(tmp);
	if (this->_size == 0)
		this->_beginNode = tmp;
	++this->_size;
}

template<typename T, class Alloc>
void List<T, Alloc>::pop_back() {
	if (this->_size == 1)
		this->pop_front();
	else if (this->_size >= 1) {
		node_pointer tmp = this->_endNode->previous();
		this->_endNode->previous()->disconnect();
		delete tmp;
		--this->_size;
	}
}

template<typename T, class Alloc>
typename List<T, Alloc>::iterator List<T, Alloc>::insert(iterator position, const_ref val) {
	if (position == this->begin()) {
		this->push_front(val);
		return (this->begin());
	} else if (position == this->end()) {
		this->push_back(val);
		return (this->end());
	}
	node_pointer newNode = new node_type(val);
	position.getPoint()->insert_before(newNode);
	++this->_size;
	return (iterator(newNode));
}

template<typename T, class Alloc>
void List<T, Alloc>::insert(iterator position, size_type size, const_ref val) {
	for (size_type i = 0; i < size; i++)
		this->insert(position, val);
}

template<typename T, class Alloc>
void List<T, Alloc>::insert(iterator position, iterator first, List::iterator last) {
	while (first != last)
		this->insert(position, *first++);
}

template<typename T, class Alloc>
typename List<T, Alloc>::iterator List<T, Alloc>::erase(iterator position) {
	if (position == this->begin()) {
		this->pop_front();
		return (this->begin());
	} else if (position == this->end()) {
		this->pop_back();
		return (this->end());
	}
	node_pointer next = position.getPoint()->next();
	position.getPoint()->disconnect();
	delete position.getPoint();
	--this->_size;
	return (iterator(next));
}

template<typename T, class Alloc>
typename List<T, Alloc>::iterator List<T, Alloc>::erase(iterator first, iterator last) {
	while (first != last)
		this->erase(first++);
	return (first);
}

template<typename T, class Alloc>
void List<T, Alloc>::swap(List &other) {
	ft::swap(this->_beginNode, other._beginNode);
	ft::swap(this->_endNode, other._endNode);
	ft::swap(this->_size, other._size);
}

template<typename T, class Alloc>
void List<T, Alloc>::resize(size_type n, value_type val) {
	if (n == 0)
		this->clear();
	else if (n < this->_size) {
		size_t i = 0;
		iterator first = this->begin();
		while (i < n) {
			++i;
			++first;
		}
		this->erase(first, this->end());
	} else
		this->insert(this->end(), n - this->_size, val);
}

template<typename T, class Alloc>
void List<T, Alloc>::clear() {
	this->erase(this->begin(), this->end());
	this->reset_bounds();
}
#pragma endregion

#pragma region Operations
template<typename T, class Alloc>
void List<T, Alloc>::splice(iterator position, List &x) {
	this->splice(position, x, x.begin(), x.end());
}

template<typename T, class Alloc>
void List<T, Alloc>::splice(iterator position, List &x, iterator it) {
	iterator next = it;
	this->splice(position, x, it, ++next);
}

template<typename T, class Alloc>
void List<T, Alloc>::splice(iterator position, List &x, iterator first, iterator last) {
	while (first != last) {
		node_pointer tmp = first++.getPoint();
		if (tmp == x._beginNode)
			x._beginNode = tmp->next();
		tmp->disconnect();
		position.getPoint()->insert_before(tmp);
		if (position.getPoint() == this->_beginNode)
			this->_beginNode = tmp;
		++this->_size;
		--x._size;
	}
	if (x._size == 0)
		x.reset_bounds();
}

template<typename T, class Alloc>
void List<T, Alloc>::remove(const_ref val) {
	iterator first = this->begin();
	iterator last = this->end();

	while (first != last) {
		if (*first == val)
			first = this->erase(first);
		else
			++first;
	}
}


template<typename T, class Alloc>
template<typename Predicate>
void List<T, Alloc>::remove_if(Predicate pred) {
	iterator first = this->begin();
	iterator last = this->end();

	while (first != last) {
		if ((*pred)(*first))
			first = this->erase(first);
		else
			++first;
	}
}

template<typename T, class Alloc>
void List<T, Alloc>::unique() {
	this->unique(&ft::equal<value_type>);
}

template<typename T, class Alloc>
template<typename BinaryPredicate>
void List<T, Alloc>::unique(BinaryPredicate binary_pred) {
	iterator previous = this->begin();
	iterator next = previous;
	iterator last = this->end();

	while (next != last) {
		++next;
		if ((*binary_pred)(*previous, *next)) {
			this->erase(next);
			next = previous;
		} else
			previous = next;
	}
}

template<typename T, class Alloc>
void List<T, Alloc>::merge(List &x) {
	if (&x == this)
		return ;
	this->merge(x, &ft::less_than<value_type>);
}

template<typename T, class Alloc>
template<typename Compare>
void List<T, Alloc>::merge(List &x, Compare comp) {
	if (&x == this)
		return ;
	if (this->_size == 0) {
		this->assign(x.begin(), x.end());
		x.clear();
		return ;
	}
	iterator f1 = this->begin();
	iterator e1 = this->end();
	iterator f2 = x.begin();
	iterator e2 = x.end();

	while (f1 != e1 && f2 != e2) {
		if ((*comp)(*f2, *f1)) {
			x._beginNode = f2.getPoint()->next();
			--x._size;
			f2.getPoint()->disconnect();
			f1.getPoint()->insert_before(f2.getPoint());
			if (f1 == this->begin())
				this->_beginNode = this->_beginNode->previous();
			++this->_size;
			f2 = x.begin();
		} else
			++f1;
	}
	this->splice(e1, x);
}

template<typename T, class Alloc>
void List<T, Alloc>::sort() {
	if (this->_size <= 1)
		return ;
	this->sort(&ft::less_than<value_type>);
}

template<typename T, class Alloc>
template<typename Compare>
void List<T, Alloc>::sort(Compare comp) {
	if (this->_size <= 1)
		return ;
	iterator first = this->begin();
	iterator last = this->end();
	iterator next;
	iterator tmp;

	while (first != last) {
		next = first;
		while (++next != last) {
			if ((*comp)(*next, *first)) {
				if (first.getPoint() == this->_beginNode)
					this->_beginNode = next.getPoint();
				first.getPoint()->swap(next.getPoint());
				tmp = next;
				next = first;
				first = tmp;
			}
		}
		++first;
	}
}

template<typename T, class Alloc>
void List<T, Alloc>::reverse() {
	if (this->_size <= 1)
		return ;
	iterator begin = this->begin();
	iterator end = --this->end();

	size_t limit = this->_size / 2;
	for (size_t i = 0; i < limit; ++i) {
		begin++.getPoint()->swap(end--.getPoint());
	}
	while (end.getPoint()->previous())
		--end;
	this->_beginNode = end.ptr();
}

#pragma endregion

/**	OPERATORS						**/
#pragma region Operators

template<typename T>
bool operator==(List<T> const &l, List<T> const &r) {
	if (l.size() != r.size())
		return (false);

	typename List<T>::const_iterator first1 = l.begin();
	typename List<T>::const_iterator last1 = l.end();
	typename List<T>::const_iterator first2 = r.begin();
	typename List<T>::const_iterator last2 = r.end();

	while (first1 != last1)
		if (*first1++ != *first2++)
			return (false);

	return (true);
}

template<typename T>
bool operator!=(List<T> const &l, List<T> const &r) {
	return (!(l == r));
}

template<typename T>
bool operator<(List<T> const &l, List<T> const &r) {
	return (ft::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end()));
}

template<typename T>
bool operator<=(List<T> const &l, List<T> const &r) {
	return (!(r < l));
}

template<typename T>
bool operator>(List<T> const &l, List<T> const &r) {
	return (r < l);
}

template<typename T>
bool operator>=(List<T> const &l, List<T> const &r) {
	return (!(l < r));
}

template<typename T>
void swap(List<T> &x, List<T> &y) {
	x.swap(y);
}
#pragma endregion