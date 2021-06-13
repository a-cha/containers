//
// Created by Skipjack Adolph on 4/14/21.
//

#pragma once

namespace ft {

/**	COPLIEN FORM					**/
#pragma region Coplien

	template<typename T, typename C>
	Stack<T, C>::Stack(const container_type &cont) : _cont(cont) {}

	template<typename T, typename C>
	Stack<T, C>::Stack(const Stack &other) : _cont(other._cont) {}

	template<typename T, typename C>
	Stack <T, C> &Stack<T, C>::operator=(const Stack &other) {
		_cont = other._cont;
		return *this;
	}

	template<typename T, typename C>
	Stack<T, C>::~Stack() {}

#pragma endregion

/**	METHODS							**/
#pragma region Member functions

	template<typename T, typename C>
	bool Stack<T, C>::empty() const {
		return this->_cont.empty();
	}

	template<typename T, typename C>
	size_t Stack<T, C>::size() const {
		return this->_cont.size();
	}

	template<typename T, typename C>
	typename Stack<T, C>::reference Stack<T, C>::top() {
		return this->_cont.back();
	}

	template<typename T, typename C>
	typename Stack<T, C>::const_reference Stack<T, C>::top() const {
		return this->_cont.back();
	}

	template<typename T, typename C>
	void Stack<T, C>::push(const_reference val) {
		this->_cont.push_back(val);
	}

	template<typename T, typename C>
	void Stack<T, C>::pop() {
		this->_cont.pop_back();
	}

#pragma endregion

/**	OPERATORS						**/
#pragma region Relational operators

	template<typename stack_type, typename container_type>
	bool operator==(const Stack <stack_type, container_type> &lhs,
					const Stack <stack_type, container_type> &rhs) {
		return lhs._cont == rhs._cont;
	}

	template<typename stack_type, typename container_type>
	bool operator!=(const Stack <stack_type, container_type> &lhs,
					const Stack <stack_type, container_type> &rhs) {
		return lhs._cont != rhs._cont;
	}

	template<typename stack_type, typename container_type>
	bool operator<(const Stack <stack_type, container_type> &lhs,
				   const Stack <stack_type, container_type> &rhs) {
		return lhs._cont < rhs._cont;
	}

	template<typename stack_type, typename container_type>
	bool operator<=(const Stack <stack_type, container_type> &lhs,
					const Stack <stack_type, container_type> &rhs) {
		return lhs._cont <= rhs._cont;
	}

	template<typename stack_type, typename container_type>
	bool operator>(const Stack <stack_type, container_type> &lhs,
				   const Stack <stack_type, container_type> &rhs) {
		return lhs._cont > rhs._cont;
	}

	template<typename stack_type, typename container_type>
	bool operator>=(const Stack <stack_type, container_type> &lhs,
					const Stack <stack_type, container_type> &rhs) {
		return lhs._cont >= rhs._cont;
	}
#pragma endregion

}
