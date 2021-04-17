//
// Created by Skipjack Adolph on 4/14/21.
//

#include "List.hpp"

namespace ft {

	template<typename T, typename C = List<T> >

	class Stack {

	/*************************************
	**	ALIASES							**
	*************************************/
	public:
		typedef T			value_type;
		typedef C			container_type;
		typedef T *			pointer;
		typedef T const *	const_pointer;
		typedef T&			reference;
		typedef T const &	const_reference;
		typedef size_t		size_type;

	/*************************************
	**	COPLIEN FORM					**
	*************************************/
	public:
		Stack(container_type const &cont=container_type());
		Stack(Stack const &other);
		Stack &operator=(Stack const &other);
		virtual ~Stack();

	/*************************************
	**	METHODS							**
	*************************************/
	public:
		bool			empty() const;
		size_t			size() const;
		reference		top();
		const_reference	top() const;
		void			push(const_reference val);
		void			pop();

	/*************************************
	**	OPERATORS						**
	*************************************/
	public:
//		todo: remove friend
		template<typename stack_type, typename container_type>
		friend bool operator==(Stack<stack_type, container_type> const &lhs, Stack<stack_type, container_type> const &rhs);
		template<typename stack_type, typename container_type>
		friend bool operator!=(Stack<stack_type, container_type> const &lhs, Stack<stack_type, container_type> const &rhs);
		template<typename stack_type, typename container_type>
		friend bool operator<(Stack<stack_type, container_type> const &lhs, Stack<stack_type, container_type> const &rhs);
		template<typename stack_type, typename container_type>
		friend bool operator<=(Stack<stack_type, container_type> const &lhs, Stack<stack_type, container_type> const &rhs);
		template<typename stack_type, typename container_type>
		friend bool operator>(Stack<stack_type, container_type> const &lhs, Stack<stack_type, container_type> const &rhs);
		template<typename stack_type, typename container_type>
		friend bool operator>=(Stack<stack_type, container_type> const &lhs, Stack<stack_type, container_type> const &rhs);

	/*************************************
	**	FIELDS							**
	*************************************/
	private:
		container_type _cont;
	};

#include "Stack.ipp"

}
