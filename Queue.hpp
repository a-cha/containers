//
// Created by Skipjack Adolph on 4/14/21.
//

#pragma once

#include "List.hpp"

namespace ft {

	template<typename T, typename C = List<T> >

	class Queue {

	/*************************************
	**	ALIASES							**
	*************************************/
	public:
		typedef T			value_type;
		typedef C			container_type;
		typedef T *			pointer;
		typedef T const *	const_pointer;
		typedef T &			reference;
		typedef T const &	const_reference;
		typedef size_t		size_type;

	/*************************************
	**	COPLIEN FORM					**
	*************************************/
	public:
		Queue(container_type const &container=container_type());
		Queue(Queue<T, C> const &other);
		Queue &operator=(Queue const &other);
		~Queue();

	/*************************************
	**	METHODS							**
	*************************************/
	public:
		bool empty() const;
		size_t size() const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;
		void push(const_reference val);
		void pop();

	/*************************************
	**	OPERATORS						**
	*************************************/
	public:
//		todo: remove friend
		template<typename queue_type, typename container_type>
		friend bool operator==(Queue<queue_type, container_type> const &lhs, Queue<queue_type, container_type> const &rhs);

		template<typename queue_type, typename container_type>
		friend bool operator!=(Queue<queue_type, container_type> const &lhs, Queue<queue_type, container_type> const &rhs);

		template<typename queue_type, typename container_type>
		friend bool operator<(Queue<queue_type, container_type> const &lhs, Queue<queue_type, container_type> const &rhs);

		template<typename queue_type, typename container_type>
		friend bool operator<=(Queue<queue_type, container_type> const &lhs, Queue<queue_type, container_type> const &rhs);

		template<typename queue_type, typename container_type>
		friend bool operator>(Queue<queue_type, container_type> const &lhs, Queue<queue_type, container_type> const &rhs);

		template<typename queue_type, typename container_type>
		friend bool operator>=(Queue<queue_type, container_type> const &lhs, Queue<queue_type, container_type> const &rhs);

	/*************************************
	**	FIELDS							**
	*************************************/
	private:
		container_type _cont;
	};

#include "Queue.ipp"

}
