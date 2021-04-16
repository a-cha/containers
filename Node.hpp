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
		explicit Node(value_type const & val);
		Node(value_type const &val, Node *prev, Node *next = nullptr);

	/*************************************
	**	GETTERS							**
	*************************************/
	public:
		value_type & getData();
		const value_type & getData() const;
		Node<value_type> * getNext() const;
		Node<value_type> * getPrev() const;

	/*************************************
	**	SETTERS							**
	*************************************/
	public:
		void setPrev(Node<value_type> *prev);
		void setNext(Node<value_type> *next);

	/*************************************
	**	METHODS							**
	*************************************/
	public:
		void pasteBefore(Node *n);
		void pasteAfter(Node *n);
		void cut(void);
		void swap(Node *n);
		void swapValues(Node *n);
		void reverse(void);
		void detach(void);

	/*************************************
	**	FIELDS							**
	*************************************/
	private:
		value_type			_data;
		Node<value_type> *	_next;
		Node<value_type> *	_prev;
	};

#include "Node.ipp"

}
