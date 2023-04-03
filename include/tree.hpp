#ifndef TREE_HPP
#define TREE_HPP

# include <iostream>
# include "pair.hpp"
# include <unistd.h>
# include "node.hpp"

namespace ft {
	template<class T, class Alloc = std::allocator< Node<T> > >
	class Tree
	{
		private:
			Alloc _alloc;

		public:
			Node<T> *root;
		public:
			Tree() : root(NULL) {}
			Tree(const Tree &tree) : root(tree.root), _alloc(tree._alloc) {}
			~Tree() {}

			Tree &operator=(const Tree &tree)
			{
				if (this != &tree)
					this->root = tree.root;
				return *this;
			}

			operator Tree<const T>() const
			{
				return (Tree<const T>(*this));
			}

			Node<T> *getroot() const { return root; }
			
			size_t	max_size() const
			{
				return (this->_alloc.max_size());
			}

			Node<T> *insert(T data)
			{
				return this->insert(data, this->root);
			}

			void print(Node<T> *node, int space) const
			{
				usleep(100000);
				if (node == NULL)
						return;
				
				space += 10;
				print(node->right, space);
				std::cout << std::endl;
				for (int i = 10; i < space; i++)
					std::cout << " ";
				std::cout << node->data.first << " : " << node->data.second << "\n";
				print(node->left, space);
			}


			Node<T> *find(typename T::first_type key) const
			{
				return this->find(key, this->root);
			}


			void erase(typename T::first_type key)
			{
				Node<T> *node = this->find(key);
				if (node == NULL)
					return;
				std::cout << "erase " << std::endl;
				Node<T> *successor = node->find_successor();
				std::cout << "successor " << successor->data.first << std::endl;
				if (successor == NULL)
				{
					if (node->parent->left == node)
					{
						if (node->left)
							node->parent->left = node->left;
						else
							node->parent->left = node->right;
					}
					else
					{
						if (node->right)
							node->parent->right = node->right;
						else
							node->parent->right = node->left;
					}
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
				}
				else
				{
					node->swap(successor);
					std::cout << node->data.first << std::endl;
					std::cout << node->parent->data.first << std::endl;
					if (node->parent->right == node)
					{
						node->parent->right = node->left;
						if (node->left)
							node->left->parent = node->parent;
					}
					else if (node->parent->left == node)
					{
						node->parent->left = node->right;
						if (node->right)
							node->right->parent = node->parent;
					}
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
				}	

			}

			Node<T> *lowest_node() const
			{
				Node<T> *node = this->root;
				while (node->left != NULL)
					node = node->left;
				return node;
			}

			Node<T> *highest_node() const
			{
				Node<T> *node = this->root;
				if (node)
					while (node->right != NULL)
						node = node->right;
				return node;
			}

			Node<T>* new_node(T data)
			{
				Node<T> *newnode = _alloc.allocate(1);
				_alloc.construct(newnode, data);
				return newnode;
			}

			void clear()
			{
				this->destroy_tree(this->root);
			}

			Alloc get_allocator() const
			{
				return _alloc;
			}
		private:


			Node<T> *insert(T data, Node<T>* &current)
			{
				if (current == NULL)
				{
					current = this->new_node(data);
					return current;
				}
				else
				{
					if (data.first < current->data.first)
					{
						if (current->left == NULL)
						{
							current->left = this->new_node(data);
							current->left->parent = current;
							return current->left;
						}
						else
							return this->insert(data, current->left);
					}
					else if (data.first > current->data.first)
					{
						if (current->right == NULL)
						{
							current->right = this->new_node(data);
							current->right->parent = current;
							return current->right;
						}
						else
							return this->insert(data, current->right);
					}
					return current;
				}
			}

			Node<T> *find(typename T::first_type key, Node<T> *current) const
			{
				if (current == NULL)
					return NULL;
				if (key < current->data.first)
					return this->find(key, current->left);
				else if (key > current->data.first)
					return this->find(key, current->right);
				else
					return current;
			}

			void destroy_tree(Node<T> *node)
			{
				if (node != NULL)
				{
					if (node->left != NULL)
						destroy_tree(node->left);
					if (node->right != NULL)
						destroy_tree(node->right);
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
				}
				this->root = NULL;
			}




	};
}

#endif //TREE_HPP
