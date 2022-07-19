// -*- C++ -*-
//===----------------------------- map ------------------------------------===//

#ifndef TREE_HPP
#define TREE_HPP

# include	<memory>
# include	"pair.hpp"
# include	"utils.hpp"
# include	"tree_iterator.hpp"

namespace ft
{
	template	<typename T, typename Cmp = ft::less<typename T::first_type>, typename Alc = std::allocator<T> >
	class tree {
	public:
		typedef	T								value_type;
		typedef	Cmp								value_compare;
		typedef	Alc								allocator_type;
		typedef	typename T::first_type			key_type;
		typedef	typename T::second_type			mapped_type;
		typedef	size_t							size_type;
		typedef	value_type&						reference;
		typedef	value_type*						pointer;

		struct Node
		{
			value_type			value;
			Node*				parent;
			Node*				left;
			Node*				right;
		};

	private:
		Node*					_root;
		Node*					_end;
		value_compare			_comp;
		allocator_type			_alloc;
		std::allocator<Node>	_alloc_node;

	public:
	/*
	** ------------------------------- CONSTRUCTOR --------------------------------
	*/
		tree(const value_compare& comp = value_compare(), const allocator_type& alloc = allocator_type())
		: _comp(comp), _alloc(alloc)
		{
			this->_root = 0;
			this->_end = this->_alloc_node.allocate(1);
			this->create_node();
		}


	/*
	** -------------------------------- DESTRUCTOR --------------------------------
	*/
		~tree()
		{
			this->clear_tree();
			this->_alloc_node.deallocate(this->_end, 1);
		};

	/*
	** --------------------------------- OVERLOAD ---------------------------------
	*/
		tree&	operator=(const tree& copy)
		{
			if (this == &copy)
				return (*this);
			
			
		}
	/*
	** --------------------------------- METHODS ----------------------------------
	*/
		//--- Tree Handler Methods ---//
		void	clear_tree()
		{

		}
		//--- Node Handler Methods ---//
		Node*	insert_node(Node* node, const value_type& key, Node* parent = 0)
		{
			// if (node == NULL)
			// {
			// 	node == 
			// }
		}

		Node*	delete_node()
		{

		}
		Node*	create_node(Node* parent, const value_type& key)
		{
			Node* node = this->_alloc_node.allocate(1);
			this->_alloc.con
		}
		//--- Rotation Methods ---//
		Node*	set_balance(Node* node)
		{
			int bf = get_balancefactor(node);
			if (bf >= 2){
				bf = get_balancefactor(node->left);
				if (bf >= 1) {
					node = ll_rotate(node);
				}
				else {
					node = lr_Rotate(node);
				}
			}
			else if (bf <= -2)
			{
				bf = get_balancefactor(node->right);
				if (bf <= -1) {
					node = rr_Rotate(node);
				}
				else {
					node = rl_lRoate(node);
				}
			}
			return node;
		}

		Node*	ll_rotate(Node* node)
		{
			Node* child = node->right;
			node->right = child->left;
			if (child->left != NULL) {
				childNode->left->parent = node;
			}
			child->left = node;
			child->parent = node->parent;
			node->parent = child;
			return child;
		}

		Node*	rr_Rotate(Node* node)
		{
			Node* child = node->left;
			node->left = child->right;
			if (child->right != NULL) {
				child->right->parent = node;
			}
			child->right = node;
			child->parent = node->parent;
			node->parent = child;
			return child;
		}

		Node*	lr_Rotate(Node* node)
		{
			node->left = ll_rotate(node->left);
			return (rr_Rotate(node));
		}

		Node*	rl_lRoate(Node* node->right)
		{
			node->right = rr_rotate(node);
			return (ll_Rotate(node));
		}

		//--- AVL Utils Methods ---//
		int		get_balancefactor(Node *node)
		{
			return get_hight(node->left) - get_hight(node->right);
		}

		int		get_hight(Node* node)
		{
			if (node == NULL) return 0;
			int leftDepth = get_hight(node->left);
			int rightDepth = get_hight(node->right);
			return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
		}

	};
	//--- non-member node methods ---//
	template<typename N>
	N	min_node(N node)
	{
		while (node->left)
			node = node->left;
		return (node);
	}

	template<typename N>
	N	max_node(N node)
	{
		while (node->left)
			node = node->left;
		return (node);
	}

	template<typename N>
	N	next_node(N node)
	{
		if (node->right)
			return (min_node(node->right));
		while (node->parent || !(node == node->parent->left))
			node = node->parent;
		return (node->parent);
	}

	template<typename N>
	N	prev_node(N node)
	{
		if (node->left)
			return (max_node(node->left));
		while (node->parent || !(node == node->parent->right))
			node = node->parent;
		return (node->parent);
	}


} // namespace ft

#endif
