//
// Created by Skipjack Adolph on 4/13/21.
//

#pragma once

#include <Node.hpp>

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
		typedef value_type const *									const_pointer;
		typedef Node<value_type>									node_type;
		typedef node_type*											node_pointer;
		typedef ListIterator<value_type, pointer, ref>				iterator;
		typedef ListIterator<value_type, const_pointer, const_ref>	const_iterator;
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
		iterator				begin();
		const_iterator			begin() const;
		iterator				end();
		const_iterator			end() const;
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;

		bool					empty() const;
		size_type				size() const;
		size_type				max_size() const;
		reference				front();
		const_reference			front() const;
		reference				back();
		const_reference			back() const;
		void					assign(iterator first, iterator last);
		void					assign(const_iterator first, const_iterator last);
		void					assign(size_type size, const_reference val);
		void					push_front(const_reference val);
		void					pop_front();
		void					push_back(const_reference val);
		void					pop_back();
		iterator				insert(iterator position, const_reference val);
		void					insert(iterator position, size_type size, const_reference val);
		void					insert(iterator position, iterator first, List::iterator last);
		iterator				erase(iterator position);
		iterator				erase(iterator first, iterator last);
		void					swap(List &other);
		void					resize(size_type n, value_type val=value_type());
		void					clear();
		void					splice(iterator position, List &x);
		void					splice(iterator position, List &x, iterator it);
		void					splice(iterator position, List &x, iterator first, iterator last);
		void					remove(const_reference val);
		void					remove_if(Predicate pred);
		void					unique();
		void					unique(BinaryPredicate binary_pred);
		void					merge(List &x);
		void					merge(List &x, Compare comp);
		void					sort();
		void					sort(Compare comp);
		void					reverse();
		void					remove_if(Predicate pred);
		void					unique();
		void					unique(BinaryPredicate binary_pred);
		void					merge(List &x);
		void					merge(List &x, Compare comp);
		void					sort();
		void					sort(Compare comp);
		void					reverse();


	/*************************************
	**	FIELDS							**
	*************************************/
	private:
		size_type               _size;
		node_pointer			_beginNode;
		node_pointer			_endNode;

	};

//	TODO .ipp file here
//	 #include <List.ipp>

	/**	COPLIEN FORM					**/
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
	List &List<T, Alloc>::operator=(const List &other) {
		this->assign(other.begin(), other.end());
		return (*this);
	}

	template<typename T, class Alloc>
	List<T, Alloc>::~List() {
		this->clear();
		delete this->_endNode;
	}


	/**	CONSTRUCTORS					**/
	template<typename T, class Alloc>
	List<T, Alloc>::List(size_type n, const_ref val=value_type()) :
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


	/**	METHODS							**/
	#pragma region iterators

	template<typename T, class Alloc>
	iterator List<T, Alloc>::begin() {
		return (iterator(this->_beginNode));
	}

	template<typename T, class Alloc>
	const_iterator List<T, Alloc>::begin() const {
		return (const_iterator(this->_beginNode));
	}

	template<typename T, class Alloc>
	iterator List<T, Alloc>::end() {
		return (iterator(this->_endNode));
	}

	template<typename T, class Alloc>
	const_iterator List<T, Alloc>::end() const {
		return (const_iterator(this->_endNode));
	}

	template<typename T, class Alloc>
	reverse_iterator List<T, Alloc>::rbegin() {
		return (reverse_iterator(this->end()));
	}

	template<typename T, class Alloc>
	const_reverse_iterator List<T, Alloc>::rbegin() const {
		return (const_reverse_iterator(this->end()));
	}

	template<typename T, class Alloc>
	reverse_iterator List<T, Alloc>::rend() {
		return (reverse_iterator(this->begin()));
	}

	template<typename T, class Alloc>
	const_reverse_iterator List<T, Alloc>::rend() const {
		return (const_reverse_iterator(this->begin()));
	}

	#pragma endregion

	template<typename T, class Alloc>
	bool List<T, Alloc>::empty() const {
		return (this->_size == 0);
	}

	template<typename T, class Alloc>
	size_type List<T, Alloc>::size() const {
		return (this->_size);
	}

	template<typename T, class Alloc>
	size_type List<T, Alloc>::max_size() const {
		return (ft::min((size_type) std::numeric_limits<difference_type>::max(),
						std::numeric_limits<size_type>::max() / (sizeof(node_type) - sizeof(pointer))));
	}

	template<typename T, class Alloc>
	reference List<T, Alloc>::front() {
		return (this->_beginNode->value());
	}

	template<typename T, class Alloc>
	const_reference List<T, Alloc>::front() const {
		return (this->_beginNode->value());
	}

	template<typename T, class Alloc>
	reference List<T, Alloc>::back() {
		return (this->_endNode->previous()->value());
	}

	template<typename T, class Alloc>
	const_reference List<T, Alloc>::back() const {
		return (this->_endNode->previous()->value());
	}

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
	void List<T, Alloc>::assign(size_type size, const_reference val) {
		this->clear();
		for (size_type i = 0; i < size; i++)
			this->push_back(val);
	}

	template<typename T, class Alloc>
	void List<T, Alloc>::push_front(const_reference val) {
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
	void List<T, Alloc>::push_back(const_reference val) {
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
	iterator List<T, Alloc>::insert(iterator position, const_reference val) {
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
	void List<T, Alloc>::insert(iterator position, size_type size, const_reference val) {
		for (size_type i = 0; i < size; i++)
			this->insert(position, val);
	}

	template<typename T, class Alloc>
	void List<T, Alloc>::insert(iterator position, iterator first, List::iterator last) {
		while (first != last)
			this->insert(position, *first++);
	}

	template<typename T, class Alloc>
	iterator List<T, Alloc>::erase(iterator position) {
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
	iterator List<T, Alloc>::erase(iterator first, iterator last) {
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
	void List<T, Alloc>::resize(size_type n, value_type val=value_type()) {
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
	void List<T, Alloc>::remove(const_reference val) {
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
		this->unique(&equal<value_type>);
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
		this->merge(x, &less_than<value_type>);
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
		this->sort(&less_than<value_type>);
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


template<typename value_type>
bool operator==(List<value_type> const &lhs, List<value_type> const &rhs) {
if (lhs.size() != rhs.size())
return (false);
typename List<value_type>::const_iterator first1 = lhs.begin();
typename List<value_type>::const_iterator last1 = lhs.end();
typename List<value_type>::const_iterator first2 = rhs.begin();
typename List<value_type>::const_iterator last2 = rhs.end();
while (first1 != last1)
if (*first1++ != *first2++)
return (false);
return (true);
}

template<typename T>
bool operator!=(List<T> const &lhs, List<T> const &rhs) {
return (!(lhs == rhs));
}

template<typename T>
bool operator<(List<T> const &lhs, List<T> const &rhs) {
return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template<typename T>
bool operator<=(List<T> const &lhs, List<T> const &rhs) {
return (!(rhs < lhs));
}

template<typename T>
bool operator>(List<T> const &lhs, List<T> const &rhs) {
return (rhs < lhs);
}

template<typename T>
bool operator>=(List<T> const &lhs, List<T> const &rhs) {
return (!(lhs < rhs));
}

template<typename T>
void swap(List<T> &x, List<T> &y) {
	x.swap(y);
}

}
