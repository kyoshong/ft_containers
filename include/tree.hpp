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
		typedef	Cmp								key_compare;
		typedef	Alc								allocator_type;
		typedef	typename T::first_type			key_type;
		typedef	typename T::second_type			mapped_type;
		typedef	size_t							size_type;
		typedef	value_type&						reference;
		typedef	const value_type&				const_reference;
		typedef	value_type*						pointer;
		typedef	const value_type*				const_pointer;

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
		bool					_empty;
		key_compare				_comp;
		allocator_type			_alloc;
		std::allocator<Node>	_alloc_node;

	public:
	/*
	** ------------------------------- CONSTRUCTOR --------------------------------
	*/
		tree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: _comp(comp), _alloc(alloc)
		{
			this->_root = 0;
			this->_end = this->_alloc_node.allocate(1);
			this->_empty = 1;
			set_end();
		}
		tree(const Node& node, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: _comp(comp), _alloc(alloc)
		{
			this->_root = &node;
			this->_end = this->_alloc_node.allocate(1);
			if (!this->_root)
				this->_empty = 1;
			set_end();
		}
		tree(const tree& copy) { *this = copy; }

	/*
	** -------------------------------- DESTRUCTOR --------------------------------
	*/
		~tree()
		{
			clear();
			this->_alloc_node.deallocate(this->_end, 1);
		};

	/*
	** --------------------------------- OVERLOAD ---------------------------------
	*/
		tree&			operator=(const tree& copy)
		{
			if (this == &copy)
				return (*this);
			clear();
			this->_root = 0;
			this->_alloc_node.deallocate(this->_end, 1);
			this->_alloc_node = copy._alloc_node;
			this->_alloc = copy._alloc;
			this->_comp = copy._comp;
			this->_empty = copy._empty;
			this->_end = this->_alloc_node.allocate(1);
			this->_root = copy_node(this->_root, copy._root);
			set_end();
			return (*this);
		}

		mapped_type&	operator[] (const key_type& k)
		{
			Node* node = find(k);
			if (node)
				return node->value.second;
			this->_root = insert_node(this->_root, ft::make_pair<const key_type, mapped_type>(k, mapped_type()));
			return find(k)->value.second;
		}
	/*
	** --------------------------------- METHODS ----------------------------------
	*/

	//--------------------------- Tree Handler Methods ---------------------------//

		size_type		size() const		{ return get_size(this->_root); }
		size_type		hight() const		{ return get_hight(this->_root); }
		size_type		max_size() const	{ return this->_alloc.max_size(); }
		Node*			end_node() const	{ return this->_end; }
		Node*			get_root() const	{ return this->_root; }
		key_compare		get_comp() const	{ return this->_comp; }
		Node*			find(const key_type& k) const
		{
			Node* tmp = this->_root;
			while(tmp)
			{
				if (this->_comp(k, tmp->value.first))
					tmp = tmp->left;
				else if (this->_comp(tmp->value.first, k))
					tmp = tmp->right;
				else
					return tmp;
			}
			return NULL;
		}
		void			swap(tree& x)
		{
			Node* tmp = this->_root;
			this->_root = x._root;
			x._root = tmp;
		}
		void			clear()
		{
			destroy_node(this->_root);
		}

		void			set_end()
		{
			if (!this->_empty)
				this->_end->parent = max_node(this->_root);
			else
			{
				this->_root = this->_end;
				this->_end->parent = 0;
			}
			this->_end->right = 0;
			this->_end->left = 0;
		}
	//--------------------------- Node Handler Methods ---------------------------//
		void	insert_node(const value_type& val)
		{
			this->_root = insert_node(this->_root, val);
			set_end();
		}

		void	delete_node(const value_type& val)
		{
			this->_root = delete_node(this->_root, val);
			set_end();
		}

		
		Node*	insert_node(Node* node, const value_type& val, Node* parent = 0)
		{
			if (this->_empty || !node)
			{
				node = create_node(parent, val);
			}
			else if (this->_comp(val.first, node->value.first))
			{
				std::cout << "left : "<< std::endl;
				node->left = insert_node(node->left, val);
				node->left->parent = node;
				node = set_balance(node);
			}
			else if (this->_comp(node->value.first, val.first))
			{
				std::cout << "right : "<< std::endl;
				node->right = insert_node(node->right, val);
				node->right->parent = node;
				node = set_balance(node);
			}
			return node;
		}

		Node*	delete_node(Node* node, const key_type& k)
		{
			if (this->_empty || !node) return NULL;
			if (this->_comp(k, node->value.first))
			{
				node->left = delete_node(node->left, k);
				node = set_balance(node);
			}
			else if (this->_comp(node->value.first, k))
			{
				node->right = delete_node(node->right, k);
				node = set_balance(node);
			}
			else
			{
				Node* del = node;
				if (node->left && !node->right)
				{
					node->left->parent = node->parent;
					node = node->left;
				}
				else if (!node->left && node->right)
				{
					node->right->parent = node->parent;
					node = node->right;
				}
				else if (node->left && node->right)
				{
					//삭제 노드 subtree 중 가장 작은 노드 찾기
					Node* min = min_node(node->right);
					if (min != node->right)
					{
						if (min->right)
						{
							min->parent->left = min->right;
							min->right->parent = min->parent;
						}
						node->right->parent = min;
						min->right = node->right;
					}
					min->parent = node->parent;
					node->left->parent = min;
					min->left = node->left;
					node = min;
				}
				if (del == this->_root)
					this->_empty = 1;
				this->_alloc.destroy(&del->value);
				this->_alloc_node.deallocate(del, 1);
				set_end();
			}
			return node;
		}
		
		Node*	create_node(Node* parent, const value_type& val)
		{
			Node* node = this->_alloc_node.allocate(1);
			this->_alloc.construct(&node->value, val);
			node->parent = parent;
			node->right = 0;
			node->left = 0;
			this->_empty = 0;
			return node;
		}

		void	destroy_node(Node* node)
		{
			if (node)
			{
				destroy_node(node->left);
				destroy_node(node->right);
				this->_alloc.destroy(&node->value);
				this->_alloc_node.deallocate(node, 1);
			}
		}


		//--------------------------- Rotation Methods ---------------------------//
		Node*	set_balance(Node* node)
		{
			int bf = get_balancefactor(node);
			std::cout << "bf : " << bf  << std::endl;
			if (bf >= 2){
				bf = get_balancefactor(node->left);
				if (bf >= 1) {
					node = ll_rotate(node);
				}
				else {
					node = lr_rotate(node);
				}
			}
			else if (bf <= -2)
			{
				bf = get_balancefactor(node->right);
				if (bf <= -1) {
					node = rr_rotate(node);
				}
				else {
					node = rl_rotate(node);
				}
			}
			return node;
		}

		Node*	ll_rotate(Node* node)
		{
			Node* child = node->right;
			node->right = child->left;
			if (child->left != NULL) {
				child->left->parent = node;
			}
			child->left = node;
			child->parent = node->parent;
			node->parent = child;
			return child;
		}

		Node*		rr_rotate(Node* node)
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

		Node*		lr_rotate(Node* node)
		{
			node->left = ll_rotate(node->left);
			return (rr_rotate(node));
		}

		Node*		rl_rotate(Node* node)
		{
			node->right = rr_rotate(node);
			return (ll_rotate(node));
		}

	//--------------------------- AVL Utils Methods ---------------------------//
		int			get_balancefactor(Node *node)
		{
			if (node)
				return get_hight(node->left) - get_hight(node->right);
			return 0;
		}

		size_type	get_size(Node* node) const
		{
			size_type num = 0;
			if (_empty) return 0;
			if (node)
			{
				num += get_size(node->right);
				num += get_size(node->left);
				++num;
			}
			return num;
		}

		int			get_hight(Node* node) const
		{
			if (node == NULL) return 0;
			int leftDepth = get_hight(node->left);
			int rightDepth = get_hight(node->right);
			return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
		}

		Node*	copy_node(Node* ori, Node* copy)
		{
			if (copy)
			{
				ori = copy_node(ori, copy->left);
				ori = copy_node(ori, copy->right);
				ori = insert_node(ori, copy->value);
			}
			return ori;
		}

	};
	//--------------------------- non-member node methods ---------------------------//
	template<typename N>
	N*	min_node(N* node)
	{
		while (node->left)
			node = node->left;
		return (node);
	}

	template<typename N>
	N*	max_node(N* node)
	{
		while (node->right)
			node = node->right;
		return (node);
	}

	template<typename N>
	N*	next_node(N* node)
	{
		std::cout << "start?" << std::endl;
		if (!node)
			return node;
		if (node->right)
			return (min_node(node->right));
		std::cout << "node : " << &node->value.first << std::endl;
		std::cout << "parent : " << &node->parent << std::endl;
		// while (node->parent || !(node == node->parent->left))
		// {
		// 	std::cout << "while" << std::endl;
		// 	node = node->parent;
		// }
		std::cout << "wow?" << std::endl;
		return (node->parent);
	}

	template<typename N>
	N*	prev_node(N* node)
	{
		if (node->left)
			return (max_node(node->left));
		while (node->parent || !(node == node->parent->right))
			node = node->parent;
		return (node->parent);
	}


} // namespace ft

#endif
