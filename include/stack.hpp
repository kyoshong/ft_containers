// -*- C++ -*-
//===----------------------------- stack ------------------------------------===//

#ifndef STACK_HPP
#define STACK_HPP
#include "vector.hpp"

namespace ft
{
	template <typename Typ, typename Cnt = vector<Typ> >
	class stack {
	public:
		typedef Cnt			container_type;
		typedef Typ			value_type;
		typedef size_t		size_type;

	protected:
		container_type		c;
	public:
	/*
	** ------------------------------- CONSTRUCTOR --------------------------------
	*/
		explicit	stack(const container_type& cnt = container_type()) : c(cnt){};
	/*
	** -------------------------------- DESTRUCTOR --------------------------------
	*/
		~stack(){}

	/*
	** --------------------------------- METHODS ----------------------------------
	*/
		bool				empty() const					{ return (this->c.empty()); }
		size_type			size() const					{ return (this->c.size()); }
		value_type&			top()							{ return (this->c.back()); }
		const value_type&	top() const						{ return (this->c.back()); }
		void				push(const value_type& val) 	{ this->c.push_back(val); }
		void				pop()							{ this->c.pop_back(); }

		friend	bool		operator==(const stack<Typ, Cnt>& s1, const stack<Typ, Cnt>& s2) { return (s1.c == s2.c); }
		friend	bool		operator!=(const stack<Typ, Cnt>& s1, const stack<Typ, Cnt>& s2) { return (s1.c != s2.c); }
		friend	bool		operator>(const stack<Typ, Cnt>& s1, const stack<Typ, Cnt>& s2) { return (s1.c > s2.c); }
		friend	bool		operator<(const stack<Typ, Cnt>& s1, const stack<Typ, Cnt>& s2) { return (s1.c < s2.c); }
		friend	bool		operator>=(const stack<Typ, Cnt>& s1, const stack<Typ, Cnt>& s2) { return (s1.c >= s2.c); }
		friend	bool		operator<=(const stack<Typ, Cnt>& s1, const stack<Typ, Cnt>& s2) { return (s1.c <= s2.c); }

	};




} // namespace ft

#endif
