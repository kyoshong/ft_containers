// -*- C++ -*-
//===----------------------------- iterator ------------------------------------===//

#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP
# include <cstddef>
# include "tree.hpp"
namespace ft {

/*
** ------------------------------- TREE ITERATOR --------------------------------
*/
	template <typename Category, typename Typ, typename TypNN = Typ>
	class tree_iterator
	{
	public:
		typedef Category							iterator_category;
		typedef	typename Typ::value_type			value_type;
		typedef	typename Typ::reference				reference;
		typedef	typename Typ::const_reference		const_reference;
		typedef	typename Typ::pointer				pointer;
		typedef	typename Typ::const_pointer			const_pointer;
		typedef	typename Typ::key_type				key_type;
		typedef	typename Typ::mapped_type			mapped_type;
		typedef	typename Typ::key_compare			key_compare;
		typedef typename TypNN::Node				node;
		typedef	ptrdiff_t							difference_type;
	private:
		node*			_ptr;
		node*			_end;
		key_compare		_comp;
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/
	public:
		tree_iterator(){}
		tree_iterator(node* begin, node* end) { this->_ptr = begin; this->_end = end; }
		tree_iterator(const tree_iterator<Category, Typ>& copy) : _ptr(copy.base()), _end(copy.end()) {}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/
		virtual ~tree_iterator() {}

/*
** --------------------------------- METHODS ----------------------------------
*/
		node*		base() const		{ return this->_ptr; }
		node*		end() const			{ return this->_end; }
		key_compare comp() const		{ return this->_comp; }

/*
** --------------------------------- OVERLOAD ---------------------------------
*/
		reference	operator*() const		{ return (this->_ptr->value); }
		pointer		operator->() const		{ return &(operator*()); }

		tree_iterator& operator=(const tree_iterator<Category, Typ>& copy)
		{
			this->_ptr = copy.base();
			this->_end = copy.end();
			this->_comp = copy.comp();
			return (*this);
		}

		tree_iterator& operator++()
		{
			this->_ptr = next_node(this->_ptr);
			return (*this);
		}

		tree_iterator& operator--()
		{
			this->_ptr = prev_node(this->_ptr);
			return (*this);
		}

		tree_iterator operator++(int)
		{
			tree_iterator tem = *this;
			++(*this);
			return (tem);
		}

		tree_iterator operator--(int)
		{
			tree_iterator tem = *this;
			--(*this);
			return (tem);
		}

		friend bool operator==(const tree_iterator& it1, const tree_iterator& it2) { return it1._ptr == it2._ptr; }
		friend bool operator!=(const tree_iterator& it1, const tree_iterator& it2) { return it1._ptr != it2._ptr; }

	};
	
} // namespace ft



#endif
