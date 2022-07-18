// -*- C++ -*-
//===----------------------------- map ------------------------------------===//

#ifndef MAP_HPP
#define MAP_HPP

<<<<<<< HEAD
#include "tree.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
	template<typename Key, typename T, typename Compare = std::less<Key>,
    typename Allocator = std::allocator<std::pair<const Key, T> > >
	class map {
	public:
		typedef	Key															key_type;
		typedef	T															mapped_type;
		typedef	ft::pair<const Key, T>										value_type;
		typedef	size_t														size_type;
		typedef	ptrdiff_t													difference_type;
		typedef	Compare														key_compare;
		typedef	Allocator													allocator_type;
		typedef	value_type&													reference;
		typedef	const value_type&											const_reference;
		typedef	Allocator::pointer											pointer;
		typedef	Allocator::const_pointer									const_pointer;
		typedef	map_iterator<bidirectional_iterator_tag, tree>				iterator;
		typedef	map_iterator<bidirectional_iterator_tag, const_tree, tree>	const_iterator;
		typedef	reverse_iterator<iteraotr>									reverse_iterator;
		typedef	reverse_iterator<const_iterator>							const_reverse_iterator;
		typedef	typename	iterator_traits<iterator>::difference_type		difference_type;
	public:
		class  value_compare
		{
			friend class map;
		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {};
		public:
			bool	operator()(const value_type& x, const value_type& y) const { return (comp(x.firest, y.first)); }
		};
	private:
		tree _tree;
	public:
	/*
	** ------------------------------- CONSTRUCTOR --------------------------------
	*/
		map() {};
	/*
	** -------------------------------- DESTRUCTOR --------------------------------
	*/
		virtual ~map()
		{

		}
	/*
	** --------------------------------- OVERLOAD ---------------------------------
	*/
		
	/*
	** --------------------------------- METHODS ----------------------------------
	*/

	};
=======
namespace ft
{
	
/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

/*
** --------------------------------- METHODS ----------------------------------
*/

>>>>>>> 7d4204a0e29f0b0d280b16786e3367721c93157e
} // namespace ft

#endif
