// -*- C++ -*-
//===----------------------------- pair ------------------------------------===//

#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft
{
	template <typename T1, typename T2>
	class pair
	{
	public:
		typedef T1	first_type;
		typedef T2	second_type;
		first_type	first;
		second_type	second;
	/*
	** ------------------------------- CONSTRUCTOR --------------------------------
	*/
		pair() : first(), second() {}
		pair(T1 const& t1, T2 const& t2) : first(t1), second(t2) {}
		template <typename U1, typename U2>
		pair(const pair<U1, U2>& copy) : first(copy.first), second(copy.second) {}

	/*
	** -------------------------------- DESTRUCTOR --------------------------------
	*/
		~pair(){}
	/*
	** --------------------------------- OVERLOAD ---------------------------------
	*/
	// OPERATOR: =
		pair&	operator=(pair const& p)
		{
			first = p.first;
			second = p.second;
			return *this;
		}
	//OPERATORS: CONPARISION: ==, !=, <, >, <=, >=
		friend bool	operator==	(const pair<T1, T2>& x, const pair<T1, T2>& y) { return x.first == y.first && x.second == y.second; }
		friend bool	operator!=	(const pair<T1, T2>& x, const pair<T1, T2>& y) { return !(x == y); }
		friend bool	operator<	(const pair<T1, T2>& x, const pair<T1, T2>& y) { return x.first < y.first || (!(y.first < x.first) && x.second < y.second); }
		friend bool	operator>	(const pair<T1, T2>& x, const pair<T1, T2>& y) { return y < x; }
		friend bool	operator>=	(const pair<T1, T2>& x, const pair<T1, T2>& y) { return !(x < y); }
		friend bool	operator<=	(const pair<T1, T2>& x, const pair<T1, T2>& y) { return !(y < x); }
	};

	template <typename T1, typename T2>
	ft::pair<T1, T2> make_pair(const T1& x, const T2& y)
	{
		return ft::pair<T1, T2>(x, y);
	}
} // namespace ft

#endif
