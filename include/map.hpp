#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include "pair.hpp"
# include "lexicographical_compare.hpp"
# include "reverse_iterator.hpp"
# include "map_iterator.hpp"
# include "tree.hpp"


namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
		public:

			typedef Key											key_type;
			typedef T											mapped_type;
			typedef Alloc										allocator_type;
			typedef Compare										key_compare;
			typedef ft::pair<const key_type, mapped_type>		value_type;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			
			typedef ft::map_iterator<value_type>				iterator;
			typedef ft::map_iterator<const value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		public:

			class value_compare
			{
				friend class map;
				protected:

					Compare comp;
					value_compare(Compare c) : comp(c) {}

				public:

					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
			};

		private:

			allocator_type		_alloc;
			key_compare			_comp;
			Tree<value_type>	_tree;
			Node<value_type>	*_end;

		public:
		
			/********************************************/
			/*											*/
			/*			Constructor/ canonical			*/
			/*											*/
			/********************************************/
			// default
			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _comp(comp), _tree(Tree<value_type>()), _end(_tree.new_node(value_type()))
			{
				this->_tree.root = this->_end;
			}

			// range
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _comp(comp), _tree(Tree<value_type>()), _end(_tree.new_node(value_type()))
			{
				this->insert(first, last);
				if (this->_tree.root == NULL)
					this->_tree.root = this->_end;
				else
				{
					Node<value_type> *last_node = _tree.highest_node();
					this->_end->parent = last_node;
					last_node->right = this->_end;
				}
			}

			// copy
			map(const map& x);
			// destructor
			~map();

			map& operator=(const map& x);


			/********************************************/
			/*											*/
			/*			Iterator						*/
			/*											*/
			/********************************************/

			iterator				begin()
			{
				return iterator(this->_tree.lowest_node());
			}
			const_iterator			begin() const
			{
				return const_iterator(this->begin());
			}

			iterator				end()
			{
				return iterator(this->_end);
			}
			const_iterator			end() const
			{
				return const_iterator(this->end());
			}
			
			reverse_iterator		rbegin()
			{
				return reverse_iterator(this->end());
			}
			const_reverse_iterator	rbegin() const
			{
				return const_reverse_iterator(this->end());
			}

			reverse_iterator		rend()
			{
				return reverse_iterator(this->begin());
			}
			const_reverse_iterator	rend() const
			{
				return const_reverse_iterator(this->begin());
			}


			/********************************************/
			/*											*/
			/*			Capacity						*/
			/*											*/
			/********************************************/

			bool		empty() const
			{
				return this->begin() == this->end();
			}

			size_type	size() const;

			size_type	max_size() const
			{
				return this->_tree.max_size();
			}


			/********************************************/
			/*											*/
			/*			Element access					*/
			/*											*/
			/********************************************/

			mapped_type& operator[](const key_type& k);

			mapped_type& 			at(const key_type& k);
			const mapped_type& 		at(const key_type& k) const;


			/********************************************/
			/*											*/
			/*			Modifier						*/
			/*											*/
			/********************************************/


			// single	
			pair<iterator,bool>	insert(const value_type& val)
			{

				// garde end.parent en memoire et supprime son grand enfant
				Node<value_type> *node = this->_end->parent;
				if (node)
				{
					node->right = NULL;
					this->_end->parent = NULL;
				}
				else
					this->_tree.root = NULL;
				iterator it = iterator(this->_tree.insert(val));

				//remet un lien sur end
				if (node)
				{
					if (node->right)
					{
						node->right->right = this->_end;
						this->_end->parent = node->right;
					}
					else
					{
						node->right = this->_end;
						this->_end->parent = node;
					}
				}
				else
				{
					Node<value_type> *last_node = _tree.highest_node();
					if (last_node)
					{
						this->_end->parent = last_node;
						last_node->right = this->_end;
					}
					else // rien n a ete ajouter
						this->_tree.root = this->_end;
				}
				if (*it == val)
					return (ft::make_pair(it, true));
				return (ft::make_pair(it, false));
			}
			
			// with hint
			iterator			insert(iterator position, const value_type& val)
			{
				(void)position;
				return this->insert(val).first;
			}
			
			// range	
			template <class InputIterator>
			void				insert(InputIterator first, InputIterator last)
			{
				// garde end.parent en memoire et supprime son grand enfant
				Node<value_type> *node = this->_end->parent;
				if (node)
				{
					node->right = NULL;
					this->_end->parent = NULL;
				}
				else
					this->_tree.root = NULL;


				while (first != last)
				{
					this->_tree.insert(*first);
					++first;
				}

				// remet un lien sur end
				if (node)
				{
					if (node->right)
					{
						node->right->right = this->_end;
						this->_end->parent = node->right;
					}
					else
					{
						node->right = this->_end;
						this->_end->parent = node;
					}
				}
				else
				{
					Node<value_type> *last_node = _tree.highest_node();
					if (last_node)
					{
						this->_end->parent = last_node;
						last_node->right = this->_end;
					}
					else // rien n a ete ajouter
						this->_tree.root = this->_end;
				}
			}
			
			void				erase(iterator position);
			
			size_type			erase(const key_type& k);
			
			void				erase(iterator first, iterator last);
		
			void				swap(map& x);

			void				clear()
			{
				this->_tree.clear();
			}


			/************************************/
			/*									*/
			/*			Observers				*/
			/*									*/
			/************************************/
		
			key_compare		key_comp() const;

			value_compare	value_comp() const;
		

			/************************************/
			/*									*/
			/*			Lookup					*/
			/*									*/
			/************************************/
		
			iterator							find(const key_type& k)
			{
				return this->_tree.find(k);
			}
			const_iterator						find(const key_type& k) const
			{
				return this->_tree.find(k);
			}

			size_type							count(const key_type& k) const;

			iterator							lower_bound(const key_type& k);
			const_iterator						lower_bound(const key_type& k) const;

			iterator							upper_bound(const key_type& k);
			const_iterator						upper_bound(const key_type& k) const;

			pair<const_iterator,const_iterator>	equal_range (const key_type& k) const;
			pair<iterator,iterator>				equal_range (const key_type& k);


			/************************************/
			/*									*/
			/*			Allocator				*/
			/*									*/
			/************************************/

			allocator_type	get_allocator() const
			{
				return this->_tree.get_allocator();
			}

	};
	
	template< class Key, class T, class Compare, class Alloc >
	void	swap( map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs );

}// fin namespace;

#endif