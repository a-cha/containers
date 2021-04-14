//
// Created by Skipjack Adolph on 4/14/21.
//

#pragma once

#include <Node.hpp>

namespace ft
{
	template<typename I>

	class RevIterator: public I {

	/*************************************
	**	ALIASES							**
	*************************************/
	public:
		using typename I::value_type;
		using typename I::reference;
		using typename I::const_ref;
		using typename I::pointer;
		using typename I::const_point;
		using typename I::difference_type;

	/*************************************
	**	COPLIEN FORM					**
	*************************************/
	public:
		RevIterator();
		RevIterator(RevIterator const &other);
		RevIterator &operator=(RevIterator const &other);
		virtual ~RevIterator() {}

	/*************************************
	**	CONSTRUCTORS					**
	*************************************/
	public:
		RevIterator(I const & other);

	/*************************************
	**	OPERATORS						**
	*************************************/
	public:
		RevIterator		operator++();
		I &				operator++();
		RevIterator		operator--();
		I &				operator--();
		reference		operator*();
		const_ref		operator*() const;
		pointer			operator->();
		const_point		operator->() const;
	};

//	TODO .ipp file here
//	 #include <RevIterator.ipp>

	/**	COPLIEN FORM					**/
	#pragma region coplien

	template<typename I>
	RevIterator<I>::RevIterator() :
		I() {}

	template<typename I>
	RevIterator<I>::RevIterator(RevIterator const &other) :
		I(other) {}

	template<typename I>
	RevIterator & RevIterator<I>::operator=(const RevIterator &other)  {
		if (this != other)
			this->p = other.p;
		return *this;
	}

	#pragma endregion

	/**	CONSTRUCTORS					**/
	template<typename I>
	RevIterator<I>::RevIterator(const I &other) :
		I(other) {}


	/**	OPERATORS						**/
	template<typename I>
	RevIterator RevIterator<I>::operator++()  {
		RevIterator tmp;

		tmp = *this;
		return ++tmp;
	}

	template<typename I>
	I & RevIterator<I>::operator++() {
		return this->I::operator--();
	}

	template<typename I>
	RevIterator RevIterator<I>::operator--() {
		RevIterator tmp;

		tmp = *this;
		return --tmp;
	}

	template<typename I>
	I & RevIterator<I>::operator--() {
		return this->I::operator++();
	}

	template<typename I>
	reference RevIterator<I>::operator*()  {
		I tmp;

		tmp = *this;
		return *--tmp;
	}

	template<typename I>
	const_ref RevIterator<I>::operator*() const  {
		I tmp;

		tmp = *this;
		return *--tmp;
	}

	template<typename I>
	pointer RevIterator<I>::operator->()  {
		I tmp;

		tmp = *this;
		return &*--tmp;
	}

	template<typename I>
	const_point RevIterator<I>::operator->() const  {
		I tmp;

		tmp = *this;
		return &*--tmp;
	}

}
