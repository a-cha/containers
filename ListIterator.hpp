//
// Created by Skipjack Adolph on 4/13/21.
//

#pragma once

namespace ft {

	template < typename T, typename T1 >

	class ListIterator {

	/*************************************
	**	ALIASES							**
	*************************************/
	public:
		typedef T 					value_type;
		typedef T1 					node_type;
		typedef std::ptrdiff_t 		difference_type;

	/*************************************
	**	COPLIEN FORM					**
	*************************************/
	public:
		ListIterator();
		ListIterator(ListIterator const &other);
		ListIterator &operator=(ListIterator const &other);
		~ListIterator() {}

	/*************************************
	**	CONSTRUCTORS					**
	*************************************/
	public:
		ListIterator(node_type * p);

	/*************************************
	**	GETTERS							**
	*************************************/
	public:
		const node_type *getPoint() const;

	/*************************************
	**	OPERATORS						**
	*************************************/
	public:


	/*************************************
	**	FIELDS							**
	*************************************/
	private:
		node_type * _point;


	/**	COPLIEN FORM					**/
	template<typename T, typename T1>
	ListIterator::ListIterator() :
		_point() {}

	template<typename T, typename T1>
	ListIterator::ListIterator(const ListIterator &other) :
			_point(other._point) {}

	template<typename T, typename T1>
	ListIterator &ListIterator::operator=(const ListIterator &other) {
		if (this != other)
			_point = other._point;
		return *this;
	}


	/**	CONSTRUCTORS					**/
	template<typename T, typename T1>
	ListIterator::ListIterator(ListIterator::node_type * p) :
		_point(p) {}


	/**	GETTERS							**/
	template<typename T, typename T1>
	const node_type * ListIterator::getPoint() const {
		return _point;
	}


	node_type * &ptr(void) {
		return (this->_point);
	}

	node_type * as_node(void) const {
		return (this->_point);
	}


	/**	OPERATORS						**/

		value_type & operator*() {
			return (this->_point->value());
		}
		const_value_type & operator*() const {
			return (this->_point->value());
		}
		value_type * operator->() {
			return (&this->_point->value());
		}
		value_type const * operator->() const {
			return (&this->_point->value());
		}

		ListIterator &operator++() {
			this->_point = this->_point->next();
			return (*this);
		}
		ListIterator operator++(int) {
			ListIterator tmp(*this);
			this->_point = this->_point->next();
			return (tmp);
		}
		ListIterator &operator--() {
			this->_point = this->_point->previous();
			return (*this);
		}
		ListIterator operator--(int) {
			ListIterator tmp(*this);
			this->_point = this->_point->previous();
			return (tmp);
		}

		ListIterator &operator+=(int value) {
			if (value > 0) {
				for (int i = 0; i < value; i++)
					this->_point = this->_point->next();
			} else {
				for (int i = value; i > 0; i--)
					this->_point = this->_point->previous();
			}
		}
		ListIterator operator+(int value) const {
			ListIterator tmp(*this);
			return (tmp += value);
		}
		ListIterator &operator-=(int value) {
			operator+=(-value);
			return (*this);
		}
		ListIterator operator-(int value) const {
			ListIterator tmp(*this);
			return (tmp -= value);
		}

		bool operator==(ListIterator const &other) const {
			return (this->_point == other._point);
		}
		bool operator!=(ListIterator const &other) const {
			return (this->_point != other._point);
		}
		bool operator<(ListIterator const &other) const {
			return (this->_point < other._point);
		}
		bool operator<=(ListIterator const &other) const {
			return (this->_point <= other._point);
		}
		bool operator>(ListIterator const &other) const {
			return (this->_point > other._point);
		}
		bool operator>=(ListIterator const &other) const {
			return (this->_point >= other._point);
		}

	};

}