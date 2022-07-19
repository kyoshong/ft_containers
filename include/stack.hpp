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
		container_type		_c;

	/*
	** ------------------------------- CONSTRUCTOR --------------------------------
	*/
		explicit	stack(const container_type& cnt = container_type()) : _c(cnt){};
	/*
	** -------------------------------- DESTRUCTOR --------------------------------
	*/
		~stack(){}

	/*
	** --------------------------------- OVERLOAD ---------------------------------
	*/
		bool				empty() const					{ return (this->_c.empty()); }
		size_type			size() const					{ return (this->_c.size()); }
		value_type&			top()							{ return (this->_c.back()); }
		const value_type&	top() const						{ return (this->_c.back()); }
		void				push(const value_type& val) 	{ this->c.push_back(val); }
		void				pop()							{ this->c.pop_back(); }

		friend	bool		operator==(const stack<Typ, Cnt>& s1, const stack<Typ, Cnt>& s2) { return (s1._c == s2._c); }
		friend	bool		operator!=(const stack<Typ, Cnt>& s1, const stack<Typ, Cnt>& s2) { return (s1._c != s2._c); }
		friend	bool		operator>(const stack<Typ, Cnt>& s1, const stack<Typ, Cnt>& s2) { return (s1._c > s2._c); }
		friend	bool		operator<(const stack<Typ, Cnt>& s1, const stack<Typ, Cnt>& s2) { return (s1._c < s2._c); }
		friend	bool		operator>=(const stack<Typ, Cnt>& s1, const stack<Typ, Cnt>& s2) { return (s1._c >= s2._c); }
		friend	bool		operator<=(const stack<Typ, Cnt>& s1, const stack<Typ, Cnt>& s2) { return (s1._c <= s2._c); }

	};



/*
** --------------------------------- METHODS ----------------------------------
*/

} // namespace ft

#endif
