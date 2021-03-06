//
// Created by Skipjack Adolph on 4/13/21.
//

#pragma once

namespace ft {

	template<class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
						InputIterator2 first2, InputIterator2 last2) {
		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1) return (false);
			else if (*first1 < *first2) return (true);
			++first1; ++first2;
		}
		return (first2 != last2);
	}

	template<class T>
	void swap(T &a, T &b) {
		T tmp;

		tmp = a;
		a = b;
		b = tmp;
	}

	template<class T>
	T const &min(T const &a, T const &b) {
		return (a < b ? a : b);
	}

	template<class T>
	T const &max(T const &a, T const &b) {
		return (a < b ? b : a);
	}

	template<class T>
	bool equal(T const &a, T const &b) {
		return (a == b);
	}

	template<class T>
	bool lower_than(T const &a, T const &b) {
		return (a < b);
	}

	template<class T>
	bool greater_than(T const &a, T const &b) {
		return (a > b);
	}

	template<bool Cond, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> {
		typedef T type;
	};

	template<class T> struct is_const {
			typedef T type;
		};

	template<class T> struct is_const<const T> {
		typedef T type;
	};

	template <class T>
	struct less : public std::binary_function <T, T, bool> {
		bool operator() (const T & x, const T & y) const {
			return x < y;
		}
	};

	template <class T1, class T2>
	struct pair {
	public:
		pair() :
			first(),
			second() {}
		template<class U, class V>
		pair (const pair<U, V> & pr) :
			first(pr.first),
			second(pr.second) {}
		pair (const T1 & a, const T2 & b) :
			first(a),
			second(b) {}
	public:
		T1	first;
		T2	second;
	};

}
