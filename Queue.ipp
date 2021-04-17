//
// Created by Skipjack Adolph on 4/14/21.
//

#pragma once

namespace ft {

/**	COPLIEN FORM					**/
#pragma region Coplien

	template<typename T, typename C>
	Queue<T, C>::Queue(const container_type &container) : _cont(container) {}

	template<typename T, typename C>
	Queue<T, C>::Queue(const Queue <T, C> &other) : _cont(other._cont) {}

	template<typename T, typename C>
	Queue <T, C> &Queue<T, C>::operator=(const Queue &other) {
		_cont = other._cont;
		return *this;
	}

	template<typename T, typename C>
	Queue<T, C>::~Queue() {}

#pragma endregion

/**	METHODS							**/
#pragma region Member functions

	template<typename T, typename C>
	bool Queue<T, C>::empty() const {
		return this->_cont.empty();
	}

	template<typename T, typename C>
	size_t Queue<T, C>::size() const {
		return this->_cont.size();
	}

	template<typename T, typename C>
	typename Queue<T, C>::reference Queue<T, C>::front() {
		return this->_cont.front();
	}

	template<typename T, typename C>
	typename Queue<T, C>::const_reference Queue<T, C>::front() const {
		return this->_cont.front();
	}

	template<typename T, typename C>
	typename Queue<T, C>::reference Queue<T, C>::back() {
		return this->_cont.back();
	}

	template<typename T, typename C>
	typename Queue<T, C>::const_reference Queue<T, C>::back() const {
		return this->_cont.back();
	}

	template<typename T, typename C>
	void Queue<T, C>::push(const_reference val) {
		this->_cont.push_back(val);
	}

	template<typename T, typename C>
	void Queue<T, C>::pop() {
		this->_cont.pop_front();
	}

#pragma endregion

/**	OPERATORS						**/
#pragma region Relational operators

	template<typename queue_type, typename container_type>
	bool operator==(const Queue <queue_type, container_type> &lhs,
					const Queue <queue_type, container_type> &rhs) {
		return lhs._cont == rhs._cont;
	}

	template<typename queue_type, typename container_type>
	bool operator!=(const Queue <queue_type, container_type> &lhs,
					const Queue <queue_type, container_type> &rhs) {
		return lhs._cont != rhs._cont;
	}

	template<typename queue_type, typename container_type>
	bool operator<(const Queue <queue_type, container_type> &lhs,
				   const Queue <queue_type, container_type> &rhs) {
		return lhs._cont < rhs._cont;
	}

	template<typename queue_type, typename container_type>
	bool operator<=(const Queue <queue_type, container_type> &lhs,
					const Queue <queue_type, container_type> &rhs) {
		return lhs._cont <= rhs._cont;
	}

	template<typename queue_type, typename container_type>
	bool operator>(const Queue <queue_type, container_type> &lhs,
				   const Queue <queue_type, container_type> &rhs) {
		return lhs._cont > rhs._cont;
	}

	template<typename queue_type, typename container_type>
	bool operator>=(const Queue <queue_type, container_type> &lhs,
					const Queue <queue_type, container_type> &rhs) {
		return lhs._cont >= rhs._cont;
	}
#pragma endregion

}
