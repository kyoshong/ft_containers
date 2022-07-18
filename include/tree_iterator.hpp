// -*- C++ -*-
//===----------------------------- iterator ------------------------------------===//

#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP
# include <cstddef>

namespace ft {

/*
** ------------------------------- CATEGORY TAGS --------------------------------
*/
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag       : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

/*
** ------------------------------- VECTOR ITERATOR --------------------------------
*/
	template <typename Category,              // iterator::iterator_category
          typename T,                     // iterator::value_type
          typename Distance = ptrdiff_t,  // iterator::difference_type
          typename Pointer = T*,          // iterator::pointer
          typename Reference = T&         // iterator::reference
          >
	class vector_iterator
	{
	public:
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	private:
		T* _ptr;
	/*
	** ------------------------------- CONSTRUCTOR --------------------------------
	*/
	public:
		vector_iterator() {}
		vector_iterator(const ft::vector_iterator<Category, T, Distance, T*, T&> &copy) : _ptr(copy.base()) {}
		vector_iterator(T* copy) : _ptr(copy) {}

	/*
	** -------------------------------- DESTRUCTOR --------------------------------
	*/
		virtual ~vector_iterator() {}

	/*
	** --------------------------------- METHODS ----------------------------------
	*/
		T* base() const { return this->_ptr; }

	/*
	** --------------------------------- OVERLOAD ---------------------------------
	*/
		vector_iterator&	operator=(T* copy)							{ this->base() = copy; return (*this); }
		vector_iterator&	operator=(const vector_iterator &copy)		{ this->_ptr = copy._ptr; return (*this); }
		vector_iterator&	operator+=(difference_type dif)				{ this->_ptr += dif; return (*this); }
		vector_iterator&	operator-=(difference_type dif)				{ this->_ptr -= dif; return (*this); }

		vector_iterator&	operator++()								{ this->_ptr++; return (*this); }
		vector_iterator&	operator--()								{ this->_ptr--; return (*this); }
		vector_iterator		operator++(int)								{ vector_iterator tem = *this; ++*this; return (tem); }
		vector_iterator		operator--(int)								{ vector_iterator tem = *this; --*this; return (tem); }

		friend vector_iterator		operator+(const vector_iterator& itr, difference_type dif)	{ return vector_iterator(itr._ptr + dif); }
		friend vector_iterator		operator+(difference_type dif, const vector_iterator& itr)	{ return vector_iterator(itr._ptr + dif); }
		friend difference_type		operator+(const vector_iterator& it1, const vector_iterator& it2)	{ return (it1._ptr + it2._ptr); }
		friend vector_iterator		operator-(const vector_iterator& itr, difference_type dif)	{ return vector_iterator(itr._ptr - dif); }
		friend vector_iterator		operator-(difference_type dif, const vector_iterator& itr)	{ return vector_iterator(itr._ptr - dif); }
		friend difference_type		operator-(const vector_iterator& it1, const vector_iterator& it2)	{ return (it1._ptr - it2._ptr); }


		reference			operator*() const								{ return (*this->_ptr); }
		T*					operator->() const								{ return (operator*()); }
		reference			operator[](const difference_type &idx) const	{ return (this->_ptr[idx]);}
		
		friend bool				operator==(const vector_iterator& x, const vector_iterator& y)	{ return (x._ptr == y._ptr); }
		friend bool				operator!=(const vector_iterator& x, const vector_iterator& y)	{ return (x._ptr != y._ptr); }
		friend bool				operator<(const vector_iterator& x, const vector_iterator& y)	{ return (x._ptr < y._ptr); }
		friend bool				operator>(const vector_iterator& x, const vector_iterator& y)	{ return (x._ptr > y._ptr); }
		friend bool				operator<=(const vector_iterator& x, const vector_iterator& y)	{ return (x._ptr <= y._ptr); }
		friend bool				operator>=(const vector_iterator& x, const vector_iterator& y)	{ return (x._ptr >= y._ptr); }

	};

/*
** ------------------------------- MAP ITERATOR --------------------------------
*/
	template <typename Category, typename Typ>
	class map_iterator
	{
		public:
			typedef Category		iterator_category;
	};
	
} // namespace ft



#endif
