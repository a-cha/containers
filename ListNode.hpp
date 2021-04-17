//
// Created by Skipjack Adolph on 4/13/21.
//

#pragma once

namespace ft {

	template <typename value_type>

	class ListNode {

	/*************************************
	**	COPLIEN FORM					**
	*************************************/
	public:
		ListNode();
		ListNode(ListNode const &other);
		ListNode &operator=(ListNode const &other);
		~ListNode() {}

	/*************************************
	**	CONSTRUCTORS					**
	*************************************/
	public:
		explicit ListNode(value_type const & val);
		ListNode(value_type const &val, ListNode *prev, ListNode *next = nullptr);

	/*************************************
	**	GETTERS							**
	*************************************/
	public:
		value_type & getData();
		const value_type & getData() const;
		ListNode<value_type> * getNext() const;
		ListNode<value_type> * getPrev() const;

	/*************************************
	**	SETTERS							**
	*************************************/
	public:
		void setPrev(ListNode<value_type> *prev);
		void setNext(ListNode<value_type> *next);

	/*************************************
	**	METHODS							**
	*************************************/
	public:
		void pasteBefore(ListNode *n);
		void pasteAfter(ListNode *n);
		void cut(void);
		void swap(ListNode *n);
		void swapValues(ListNode *n);
		void reverse(void);
		void detach(void);

	/*************************************
	**	FIELDS							**
	*************************************/
	private:
		value_type			_data;
		ListNode<value_type> *	_next;
		ListNode<value_type> *	_prev;
	};

#include "ListNode.ipp"

}
