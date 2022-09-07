//===----------------------------- map ------------------------------------===//
// -*- C++ -*-

#ifndef MAP_HPP
#define MAP_HPP

#include "tree.hpp"
#include "reverse_iterator.hpp"
#include "tree_iterator.hpp"

namespace ft
{
	template <typename Key, typename T, typename Compare = ft::less<Key>,
						typename Allocator = std::allocator<ft::pair<const Key, T>>>
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const Key, T> value_type;
		typedef size_t size_type;
		typedef Compare key_compare;

	private:
		typedef tree<const value_type, Compare, Allocator> const_tree;
		typedef tree<value_type, Compare, Allocator> tree;
		typedef typename tree::Node node;

	public:
		typedef Allocator allocator_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef tree_iterator<bidirectional_iterator_tag, const_tree, tree> const_iterator;
		typedef tree_iterator<bidirectional_iterator_tag, tree> iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type difference_type;

	public:
		class value_compare
		{
			friend class map;

		protected:
			Compare _comp;
			value_compare(Compare c) : _comp(c){};

		public:
			bool operator()(const value_type &x, const value_type &y) const { return (_comp(x.first, y.first)); }
		};

	private:
		tree _tree;

	public:
		/*
		** ------------------------------- CONSTRUCTOR --------------------------------
		*/
		explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
				: _tree(comp, alloc) {}
		template <typename Iter>
		map(Iter first, Iter last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
				: _tree(comp, alloc) { this->insert(first, last); }
		map(const map &copy) { *this = copy; }
		/*
		** -------------------------------- DESTRUCTOR --------------------------------
		*/
		~map() {}

		/*
		** --------------------------------- OVERLOAD ---------------------------------
		*/
		map &operator=(const map &copy)
		{
			if (this != &copy)
				this->_tree = copy._tree;
			return (*this);
		}

		/*
		** --------------------------------- METHODS ----------------------------------
		*/

		/*========================== Element access ==========================*/
		mapped_type &operator[](const key_type &k) { return this->_tree[k]; }

		/*============================= Iterators ============================*/
		iterator begin() { return iterator(min_node(this->_tree.get_root()), this->_tree.end_node()); }
		const_iterator begin() const { return const_iterator(min_node(this->_tree.get_root()), this->_tree.end_node()); }
		iterator end() { return iterator(this->_tree.end_node(), this->_tree.end_node()); }
		const_iterator end() const { return const_iterator(this->_tree.end_node(), this->_tree.end_node()); }
		reverse_iterator rbegin() { return reverse_iterator(this->end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }
		reverse_iterator rend() { return reverse_iterator(this->begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }

		/*============================= Capacity =============================*/
		size_type size() const { return this->_tree.size(); }
		size_type max_size() const { return this->_tree.max_size(); }
		bool empty() const { return this->_tree.size() == 0; }

		/*============================ Modifiers =============================*/
		/*
		** pair를 반환, first는 삽입한 element의 iterator이고,
		** second는 bool이다(새로 삽입했다면 true, 이미 존재했다면 false).
		*/
		pair<iterator, bool> insert(const value_type &val)
		{
			size_type n = this->size();
			this->_tree.insert_node(val);
			pair<iterator, bool> res;
			res.first = this->find(val.first);
			res.second = (n != this->size());
			return (res);
		}
		/*
		** 새로 삽입한 요소(이미 있었다면 해당 요소)를 가리키는 iterator를 반환한다.
		*/
		iterator insert(iterator position, const value_type &val)
		{
			iterator iter = position;
			if (value_comp()(*iter, val) && value_comp()(val, *++position))
			{
				this->insert(val);
				return (this->find(val.first));
			}
			return (this->insert(val).first);
		}

		template <typename Iter>
		void insert(Iter first, Iter last)
		{
			for (iterator iter = first; iter != last; iter++)
			{
				this->insert(*iter);
			}
		}

		size_type erase(const key_type &k)
		{
			size_type count = this->size();
			this->_tree.delete_node(k);
			return (count != this->size());
		}

		void erase(iterator pos)
		{
			this->erase((*pos).first);
		}

		void erase(iterator first, iterator last)
		{
			iterator temp;
			while (first != last)
			{
				temp = first++;
				this->erase(temp);
				// ++first;
			}
		}
		void swap(map &x) { this->_tree.swap(x._tree); }
		void clear() { this->_tree.clear(); }

		/*============================== Lookup ==============================*/
		size_type count(const Key &key) const
		{
			return ((this->_tree.find(key)) ? 1 : 0);
		}
		iterator find(const Key &key)
		{
			node *node = this->_tree.find(key);
			if (node)
				return (iterator(node, this->_tree.end_node()));
			return (this->end());
		}

		const_iterator find(const Key &key) const
		{
			node *node = this->_tree.find(key);
			if (node)
				return (const_iterator(node, this->_tree.end_node()));
			return (this->end());
		}
		/*
		** 키 값이 k인 모든 요소를 포함하는 범위를 반환한다.
		** map 컨테이너의 모든 element는 unique하기 때문에 범위는 최대 1이다.
		** 일치하는 항목이 없으면 반환된 범위의 길이는 0이고,
		** 두 반복자는 key_compare에 따라 k 다음에 오는 요소를 가리킨다.
		*/
		ft::pair<iterator, iterator> equal_range(const Key &key)
		{
			for (iterator it = this->begin(); it != this->end(); it++)
			{
				if (!key_comp()(key, it->first) && !key_comp()(it->first, key))
					return pair<iterator, iterator>(it++, it);
			}
			return pair<iterator, iterator>(lower_bound(key), lower_bound(key));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const Key &key) const
		{
			for (const_iterator it = this->begin(); it != this->end(); it++)
			{
				if (!key_comp()(key, it->first) && !key_comp()(it->first, key))
					return pair<const_iterator, const_iterator>(it++, it);
			}
			return pair<const_iterator, const_iterator>(lower_bound(key), lower_bound(key));
		}
		/*
		** 키 값이 k와 같거나 k보다 큰 값 중 가장 작은 element의 iterator를 반환한다.
		*/
		iterator lower_bound(const Key &key)
		{
			for (iterator iter = this->begin(); iter != this->end(); iter++)
			{
				if (!(key_comp()(iter->first, key)))
					return (iter);
			}
			return this->end();
		}

		const_iterator lower_bound(const Key &key) const
		{
			for (const_iterator iter = this->begin(); iter != this->end(); iter++)
			{
				if (!(key_comp()(iter->first, key)))
					return (iter);
			}
			return this->end();
		}
		/*
		** 키 값이 k보다 큰 값 중 가장 작은 element의 iterator를 반환한다.
		*/
		iterator upper_bound(const Key &key)
		{
			for (iterator iter = this->begin(); iter != this->end(); iter++)
			{
				if ((key_comp()(key, iter->first)))
					return (iter);
			}
			return (this->end());
		}

		const_iterator upper_bound(const Key &key) const
		{
			for (const_iterator iter = this->begin(); iter != this->end(); iter++)
			{
				if ((key_comp()(key, iter->first)))
					return (iter);
			}
			return (this->end());
		}

		/*============================ Observers =============================*/
		key_compare key_comp() const { return (this->_tree.get_comp()); }
		value_compare value_comp() const { return value_compare(this->_tree.get_comp()); }
	};

	template <typename Key, typename T, typename Comp, typename Alloc>
	bool operator==(const ft::map<Key, T, Comp, Alloc> &m1, const ft::map<Key, T, Comp, Alloc> &m2)
	{
		if (m1.size() != m2.size())
			return false;
		typename ft::map<Key, T, Comp, Alloc>::const_iterator iter1 = m1.begin();
		for (typename ft::map<Key, T, Comp, Alloc>::const_iterator iter2 = m2.begin(); iter2 != m2.end(); iter2++, iter1++)
		{
			if (*iter1 != *iter2)
				return false;
		}
		return true;
	}

	template <typename Key, typename T, typename Comp, typename Alloc>
	bool operator!=(const ft::map<Key, T, Comp, Alloc> &m1, const ft::map<Key, T, Comp, Alloc> &m2)
	{
		return !(m1 == m2);
	}

	template <typename Key, typename T, typename Comp, typename Alloc>
	bool operator<(const ft::map<Key, T, Comp, Alloc> &m1, const ft::map<Key, T, Comp, Alloc> &m2)
	{
		return (ft::lexicographical_compare(m1.begin(), m1.end(), m2.begin(), m2.end()));
	}

	template <typename Key, typename T, typename Comp, typename Alloc>
	bool operator<=(const ft::map<Key, T, Comp, Alloc> &m1, const ft::map<Key, T, Comp, Alloc> &m2)
	{
		return (!(m2 < m1));
	}

	template <typename Key, typename T, typename Comp, typename Alloc>
	bool operator>(const ft::map<Key, T, Comp, Alloc> &m1, const ft::map<Key, T, Comp, Alloc> &m2)
	{
		return (m2 < m1);
	}

	template <typename Key, typename T, typename Comp, typename Alloc>
	bool operator>=(const ft::map<Key, T, Comp, Alloc> &m1, const ft::map<Key, T, Comp, Alloc> &m2)
	{
		return (!(m1 < m2));
	}

	template <typename Key, typename T, typename Comp, typename Alloc>
	void swap(ft::map<Key, T, Comp, Alloc> &m1, ft::map<Key, T, Comp, Alloc> &m2)
	{
		return (m1.swap(m2));
	}

} // namespace ft

#endif
