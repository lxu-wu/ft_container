#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

# include <iostream>
# include "iterator_trait.hpp"
# include "pair.hpp"
# include "node.hpp"

namespace ft {

	template<class Type>
	class map_iterator : public ft::iterator<ft::bidirectional_iterator_tag, Type>
	{
		public:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, Type>::value_type			value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, Type>::iterator_category	iterator_category;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, Type>::difference_type	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, Type>::pointer			pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, Type>::reference			reference;

			typedef typename ft::Node<value_type>														node_type;

		private:

			node_type *_node;

		public:

			map_iterator() : _node(NULL) {}
			map_iterator(node_type *node) : _node(node) {}
			map_iterator(const map_iterator &other) : _node(other._node) {}
			~map_iterator() {}

			node_type *node() const { return this->_node; }
			map_iterator &operator=(const map_iterator &other)
			{
				this->_node = other._node;
				return (*this);
			}

			operator map_iterator<const value_type>() const
			{
				return (this->_node);
			}

			reference operator*() const { return this->_node->data; }
			pointer operator->() const { return &(this->_node->data); }
			
			map_iterator &operator++()
			{
				this->_node = this->_node->next();
				return (*this);
			}
			
			map_iterator operator++(int)
			{
				map_iterator tmp(*this);
				++(*this);
				return tmp;
			}

			map_iterator &operator--()
			{
				this->_node = this->_node->previous();
				return (*this);
			}

			map_iterator operator--(int)
			{
				map_iterator tmp(*this);
				--(*this);
				return tmp;
			}

			friend bool operator==(const map_iterator &lhs, const map_iterator &rhs);
			friend bool operator!=(const map_iterator &lhs, const map_iterator &rhs);
	};

	template<class T1, class T2>
	bool operator==(const map_iterator<T1> &lhs, const map_iterator<T2> &rhs)
	{
		return (lhs._node == rhs._node);
	}

	template<class T1, class T2>
	bool operator!=(const map_iterator<T1> &lhs, const map_iterator<T2> &rhs)
	{
		return (lhs._node != rhs._node);
	}
}

#endif //MAP_ITERATOR_HPP
