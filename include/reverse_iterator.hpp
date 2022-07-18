// -*- C++ -*-
//===----------------------------- iterator ------------------------------------===//

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "utils.hpp"

namespace ft {

	template <typename Iter>
	class reverse_iterator 
	{
		typedef Iter														iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::reference			reference;
	private:
		iterator_type	iter;
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
	public:
		reverse_iterator(){}
		explicit reverse_iterator(Iter x) : iter(x) {}
		template <typename Itr>
		reverse_iterator(const reverse_iterator<Itr>& x) : iter(x.base) {}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/
	virtual ~reverse_iterator() {}

/*
** --------------------------------- METHODS ----------------------------------
*/
	iterator_type base() const { return this-> iter; }
	
/*
** --------------------------------- OVERLOAD ---------------------------------
*/
	template <typename Itr>
	reverse_iterator&	operator=(const reverse_iterator<Itr> &rev_iter)		{ this->iter = rev_iter.base(); return (*this); }
	reverse_iterator&	operator+=(difference_type dif)						{ this->iter -= dif; return (*this); }
	reverse_iterator&	operator-=(difference_type dif)						{ this->iter += dif; return (*this); }

	reverse_iterator&	operator++()										{ this->iter--; return (*this); }
	reverse_iterator&	operator--()										{ this->iter++; return (*this); }
	reverse_iterator	operator++(int)										{ reverse_iterator tem = *this; --*this->iter; return (tem); }
	reverse_iterator	operator--(int)										{ reverse_iterator tem = *this; ++*this->iter; return (tem); }
	
	reverse_iterator	operator+(difference_type dif)						{ return (reverse_iterator(*this->iter - dif)); }
	reverse_iterator	operator-(difference_type dif)						{ return (reverse_iterator(*this->iter + dif)); }

	reference			operator*() const									{ iterator_type tem = this->iter; return (*--tem); }
	pointer				operator->() const									{ return &(operator*()); }
	reference			operator[](difference_type dif)						{ return (this->iter[-dif-1]); }

	};

	template <typename Iter1, typename Iter2>
	bool operator==(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() == y.base(); }
	template <typename Iter1, typename Iter2>
	bool operator!=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() != y.base(); }
	template <typename Iter1, typename Iter2>
	bool operator<(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() > y.base(); }
	template <typename Iter1, typename Iter2>
	bool operator>(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() < y.base(); }
	template <typename Iter1, typename Iter2>
	bool operator<=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() >= y.base(); }
	template <typename Iter1, typename Iter2>
	bool operator>=(const reverse_iterator<Iter1>& x, const reverse_iterator<Iter2>& y) { return x.base() <= y.base(); }

	template <typename Iter>
	reverse_iterator<Iter>
		operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& x)
		{ return reverse_iterator<Iter> (x.base() - n); }

	template <typename Iter>
	typename reverse_iterator<Iter>::difference_type 
		operator-(const reverse_iterator<Iter>& x, const reverse_iterator<Iter>& y) 
		{ return y.base() - x.base(); }

} // namespace ft



#endif
