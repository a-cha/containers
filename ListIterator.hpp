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
		node_type *getPoint() const;
//		TODO replace it to getPoint
		node_type * as_node(void) const;

	/*************************************
	**	OPERATORS						**
	*************************************/
	public:
		ListIterator &		operator++();
		ListIterator &		operator--();
		value_type *		operator->();
		value_type const *	operator->();
		value_type &		operator*();
		value_type const &	operator*();
		ListIterator		operator+(int n) const;
		ListIterator		operator-(int n) const;
		void				operator+=(int n);
		void				operator-=(int n);

		bool				operator==(ListIterator const &other) const;
		bool				operator!=(ListIterator const &other) const;
		bool				operator>(ListIterator const &other) const;
		bool				operator<(ListIterator const &other) const;
		bool				operator>=(ListIterator const &other) const;
		bool				operator<=(ListIterator const &other) const;


	/*************************************
	**	FIELDS							**
	*************************************/
	private:
		node_type * _point;

//	TODO .ipp file here
//	 #include <ListIterator.ipp>

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
	node_type * ListIterator::getPoint() const {
		return poin;
	}

//	todo do i need this strange method?
	node_type * &ptr(void) {
		return this->_point;
	}



	/**	OPERATORS						**/
		template<typename T, typename T1>
		ListIterator &ListIterator::operator++() {
			this->_point = this->_point->next();
			return *this;
		}

		template<typename T, typename T1>
		ListIterator &ListIterator::operator--() {
			this->_point = this->_point->previous();
			return *this;
		}

		template<typename T, typename T1>
		value_type * ListIterator::operator->() {
			return &this->_point->_data();
		}

		template<typename T, typename T1>
		value_type const * ListIterator::operator->() {
			return &this->_point->_data();
		}

		template<typename T, typename T1>
		value_type &ListIterator::operator*() {
			return this->_point->_data();
		}

		template<typename T, typename T1>
		value_type const &ListIterator::operator*() {
			return this->_point->_data();
		}

		template<typename T, typename T1>
		ListIterator ListIterator::operator+(int n) const {
			ListIterator tmp;

			tmp = *this;
			return tmp += n;
		}

		template<typename T, typename T1>
		void ListIterator::operator+=(int n) {
			for (int i = 0; i < n; i++)
				this->_point = this->_point->next();
		}

		template<typename T, typename T1>
		ListIterator ListIterator::operator-(int n) const {
			ListIterator tmp;

			tmp = *this;
			return tmp -= n;
		}

		template<typename T, typename T1>
		void ListIterator::operator-=(int n) {
			for (int i = 0; i > n; i--)
				this->_point = this->_point->previous();
		}

		template<typename T, typename T1>
		bool ListIterator::operator==(const ListIterator &other) const {
			return this->_point == other._point;
		}

		template<typename T, typename T1>
		bool ListIterator::operator!=(const ListIterator &other) const {
			return this->_point == other._point;
		}

		template<typename T, typename T1>
		bool ListIterator::operator>(const ListIterator &other) const {
			return this->_point > other._point;
		}

		template<typename T, typename T1>
		bool ListIterator::operator<(const ListIterator &other) const {
			return this->_point < other._point;
		}

		template<typename T, typename T1>
		bool ListIterator::operator>=(const ListIterator &other) const {
			return this->_point >= other._point;
		}

		template<typename T, typename T1>
		bool ListIterator::operator<=(const ListIterator &other) const {
			return this->_point <= other._point;
		}


//		todo strange method
//		ListIterator operator++(int) {
//			ListIterator tmp(*this);
//			this->_point = this->_point->next();
//			return tmp;
//		}

//		todo strange method
//		ListIterator operator--(int) {
//			ListIterator tmp(*this);
//			this->_point = this->_point->previous();
//			return tmp;
//		}

	};


}