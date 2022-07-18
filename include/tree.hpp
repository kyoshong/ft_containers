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
		typedef	typename	T::first_type		key_type;
		typedef	typename	T::second_type		mapped_type;
		typedef	size_t							size_type;
	private:
		template <typename T>
		struct Node
		{
			value_type			value;
			Node*				parent;
			Node*				left;
			Node*				right;
		};
	private:
		Node*					root;

	public:
	/*
	** ------------------------------- CONSTRUCTOR --------------------------------
	*/
		tree(T, ){}
	/*
	** -------------------------------- DESTRUCTOR --------------------------------
	*/
		~tree();
	/*
	** --------------------------------- OVERLOAD ---------------------------------
	*/

	/*
	** --------------------------------- METHODS ----------------------------------
	*/
		//--- Node Handler Methods ---//
		Node*	insert_node()
		{

		}
		Node*	delete_node()
		{

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

} // namespace ft

#endif
