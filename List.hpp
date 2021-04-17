//
// Created by Skipjack Adolph on 4/13/21.
//

#pragma once

#include "Node.hpp"
#include "ListIterator.hpp"
#include "RevIterator.hpp"

namespace ft {

	template < typename T, class Alloc = std::allocator<T> >

	class List {

	/*************************************
	**	ALIASES							**
	*************************************/
	public:
		typedef T													value_type;
		typedef value_type &										ref;
		typedef value_type const &									const_ref;
		typedef value_type *										pointer;
		typedef value_type const *									const_point;
		typedef Node<value_type>									node_type;
		typedef node_type *											node_point;
		typedef ListIterator<value_type, node_type>					iterator;
		typedef ListIterator<value_type const, node_type const>		const_iterator;
		typedef RevIterator<iterator>								reverse_iterator;
		typedef RevIterator<const_iterator>							const_rev_iterator;
		typedef ptrdiff_t											difference_type;
		typedef size_t												size_type;

	/*************************************
	**	COPLIEN FORM					**
	*************************************/
	public:
		List();
		List(List const &other);
		List &operator=(List const &other);
		~List();

	/*************************************
	**	CONSTRUCTORS					**
	*************************************/
	public:
		List(size_type n, const_ref val=value_type());
		List(iterator first, iterator last);

	/*************************************
	**	METHODS							**
	*************************************/
	public:
		/**	Iterators					*/
		iterator			begin();
		const_iterator		begin() const;
		iterator			end();
		const_iterator		end() const;
		reverse_iterator		rbegin();
		const_rev_iterator	rbegin() const;
		reverse_iterator		rend();
		const_rev_iterator	rend() const;

		/**	Capacity					*/
		bool				empty() const;
		size_type			size() const;
		size_type			max_size() const;

		/**	Element access				*/
		ref					front();
		const_ref			front() const;
		ref					back();
		const_ref			back() const;

		/**	Modifiers					*/
		void				assign(iterator first, iterator last);
		void				assign(const_iterator first, const_iterator last);
		void				assign(size_type size, const_ref val);
		void				push_front(const_ref val);
		void				pop_front();
		void				push_back(const_ref val);
		void				pop_back();
		iterator			insert(iterator position, const_ref val);
		void				insert(iterator position, size_type size, const_ref val);
		void				insert(iterator position, iterator first, List::iterator last);
		iterator			erase(iterator pos);
		iterator			erase(iterator first, iterator last);
		void				swap(List &other);
		void				resize(size_type n, value_type val=value_type());
		void				clear();

		/**	Operations					*/
		void				splice(iterator position, List &x);
		void				splice(iterator position, List &x, iterator it);
		void				splice(iterator position, List &x, iterator first, iterator last);
		void				remove(const_ref val);
		template<typename Predicate>
		void				remove_if(Predicate pred);
		void				unique();
		template<typename BinaryPredicate>
		void				unique(BinaryPredicate binary_pred);
		void				merge(List &x);
		template<typename Compare>
		void				merge(List &x, Compare comp);
		void				sort();
		template<typename Compare>
		void				sort(Compare comp);
		void				reverse();

	/*************************************
	**	FIELDS							**
	*************************************/
	private:
		size_type			_size;
		node_point			_beginNode;
		node_point			_endNode;

		void make_bounds(void);
		void reset_bounds(void);
	};
}

#include "List.ipp"
