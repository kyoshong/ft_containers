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
				if (this->_ptr->right)
				{
					this->_ptr = min_node(this->_ptr->right);
					return (*this);
				}
				else if (this->_ptr->parent)
				{
					// find first previous greater node
					key_type key = this->_ptr->value.first;
					node *tmp = this->_ptr->parent;
					while (tmp && this->_comp(tmp->value.first, key))
						tmp = tmp->parent;
					if (tmp)
					{
						this->_ptr = tmp;
						return *this;
					}
				}
				this->_ptr = this->_end;
				// return (*this);
			// this->_ptr = next_node(this->_ptr);
			// if (this->_ptr == NULL)
			// 	this->_ptr = this->_end;
			return (*this);
		}

		tree_iterator& operator--()
		{
			// this->_ptr = prev_node(this->_ptr);
			 if (this->_ptr == this->_end)
				{
					this->_ptr = this->_ptr->parent;
					return (*this);
				}
				else if (this->_ptr->left)
				{
					this->_ptr = min_node(this->_ptr->left);
					return (*this);
				}
				else if (this->_ptr->parent)
				{
					// find first previous smaller node
					key_type key = this->_ptr->value.first;
					node *tmp = this->_ptr->parent;
					while (tmp && this->_comp(key, tmp->value.first))
						tmp = tmp->parent;
					if (tmp)
					{
						this->_ptr = tmp;
						return (*this);
					}
				}
				return (*this);
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
