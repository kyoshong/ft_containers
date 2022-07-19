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
	template <typename Category, typename Typ>
	class tree_iterator
	{
	public:
		typedef Category					iterator_category;
		typedef	Typ::value_type				value_type;
		typedef	Typ::reference				reference;
		typedef	Typ::const_reference		const_reference;
		typedef	Typ::pointer				pointer;
		typedef	Typ::const_pointer			const_pointer;
		typedef	Typ::key_type				key_type;
		typedef	Typ::mapped_type			mapped_type;
		typedef	Typ::key_compare			key_compare;
		typedef	Typ::Node					node;
		typedef	ptrdiff_t					difference_type;
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
		tree_iterator(const map_iterator<Category, Typ>& copy) : _ptr(copy.base()), _end(copy.end()) {}

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

		tree_iterator& operator++(int)
		{
			tree_iterator tem = this->_ptr;
			this->_ptr++;
			return (tem);
		}

		tree_iterator& operator--(int)
		{
			tree_iterator tem = this->_ptr;
			this->_ptr--;
			return (tem);
		}

		template <typename T>
		bool operator==(const tree_iterator<T, node_type>& copy) const {
			return (this->_ptr == copy.base());
		}

		template <typename T>
		bool operator!=(const tree_iterator<T, node_type>& copy) const {
			return !(*this == copy);
		}

	};
	
} // namespace ft



#endif
