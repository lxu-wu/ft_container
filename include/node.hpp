#ifndef NODE_HPP
#define NODE_HPP

# include <iostream>
# include "pair.hpp"

namespace ft {

	template<class T>
	class Node
	{

		public:
			T data;

			Node<T> *parent;
			Node<T> *left;
			Node<T> *right;
		

		private:

			Node() : data(), parent(NULL), left(NULL), right(NULL) {}

		public:

			Node(T data) : data(data), parent(NULL), left(NULL), right(NULL) {}
			Node(Node<T> const& node) : data(node.data), parent(node.parent), left(node.left), right(node.right) {}
			~Node() {}

			Node<T> &operator=(const Node<T> &node)
			{
				if (this != &node)
				{
					this->data = node.data;
					this->parent = node.parent;
					this->left = node.left;
					this->right = node.right;
				}
				return *this;
			}

			operator Node<const T>() const
			{
				return (Node<const T>(*this));
			}

			typename T::first_type const & key() const { return this->data.first; }
			typename T::second_type & value() const { return this->data.second; }

			void successor_swap(Node<T>* node)
			{
				// node is successor
				Node<T> tmp(*node);
				
				if (node->parent)
				{
					if (node->parent->left == node)
						node->parent->left = this;
					else
						node->parent->right = this;
				}
				if (this->parent)
				{
					if (this->parent->left == this)
						this->parent->left = node;
					else
						this->parent->right = node;
				}

				if (node->left)
					node->left->parent = this;
				if (node->right)
					node->right->parent = this;

				if (this->left)
					this->left->parent = node;
				if (this->right)
					this->right->parent = node;

				if (node->parent != this)
				{
					std::cout << "swap" << std::endl;
					node->parent = this->parent;
					node->left = this->left;
					node->right = this->right;

					this->parent = tmp.parent;
					this->left = tmp.left;
					this->right = tmp.right;
				}
				else
				{
					node->parent = this->parent;
					if (this->left == node)
					{
						node->left = NULL;
						node->right = this->right;
					}
					else
					{
						std::cout << "swap" << std::endl;
						node->left = this->left;
						node->right = NULL;
					}
					std::cout << "swap2" << std::endl;
					this->parent = node;
					this->left = tmp.left;
					this->right = tmp.right;
				}
				std::cout << "data : " << this->data.first << std::endl;
				std::cout << "data : " << this->parent->data.first << std::endl;
			}

			Node<T>* find_successor()
			{
				Node<T> *node = NULL;
				if (this->right)
				{
					node = this->right->lowest_value();
					if (!node)
						node = this->right;
				}
				else if (this->left)
				{
					node = this->left->highest_value();
					if (!node)
						node = this->left;
				}
				if (node)
					return node;
				else
					return NULL;
			}


			Node<T>* lowest_value() const
			{
				Node<T> *current = this->left;
				if (current)
					while (current->left)
						current = current->left;
				return current;
			}

			Node<T>* highest_value() const
			{
				Node<T> *current = this->right;
				if (current)
					while (current->right)
						current = current->right;
				return current;
			}

			Node<T>* next() const
			{
				Node<T> *parent(this->parent);
				
				// std::cout << "data : " << this->data.first << std::endl;
				if (this->right)
				{
					// std::cout << "center" << std::endl;
					Node<T> *lowest = this->right->lowest_value();
					if (lowest)
						return lowest;
					else
						return this->right;
				}
				if (parent && parent->left == this)
				{
					// std::cout << "left" << std::endl;
					return parent;
				}
				if (parent && parent->right == this)
				{
					// std::cout << "right" << std::endl;
					return this->up_right();
				}
				// std::cout << "NULL" << std::endl;
				return NULL;
			}

			Node<T>* previous() const
			{
				Node<T> *parent(this->parent);
				
				if (this->left)
				{
					Node<T> *highest = this->left->highest_value();
					if (highest)
						return highest;
					else
						return this->left;
				}
				if (parent && parent->right == this)
				{
					return parent;
				}
				if (parent && parent->left == this)
				{
					return this->up_left();
				}
				std::cout << "NULL" << std::endl;
				return NULL;
			}

			Node<T> *up_right() const
			{
				Node<T> *parent(this->parent);
				if (parent && parent->right == this)
					return this->parent->up_right();
				if (parent && parent->right != this)
					return this->parent;
				// return this;
				return NULL;
			}

			Node<T> *up_left() const
			{
				Node<T> *parent(this->parent);
				if (parent && parent->left == this)
					return this->parent->up_left();
				if (parent && parent->left != this)
					return this->parent;
				// return this;
				return NULL;
			}


	};

	template<class T>
	bool operator==(const Node<T> &lhs, const Node<T> &rhs)
	{
		return (lhs.data == rhs.data);
	}

	template<class T>
	bool operator!=(const Node<T> &lhs, const Node<T> &rhs)
	{
		return (lhs.data != rhs.data);
	}
	
}

#endif //NODE_HPP
