// -*- C++ -*-
//===----------------------------- utils ------------------------------------===//

#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
	//===------------------ iterator_traits -------------------===//
	template <class Iter>
	class iterator_traits
	{
	public:
		typedef typename Iter::iterator_category		iterator_category;
		typedef typename Iter::value_type				value_type;
		typedef typename Iter::difference_type			difference_type;
		typedef typename Iter::pointer					pointer;
		typedef typename Iter::reference				reference;
	};


	//===------------------ enable_if -------------------===//
	template	<bool B, class T = void>
	struct	enable_if {};
	
	template	<class T>
	struct	enable_if<true, T> { typedef T type; };

} // namespace ft

#endif
