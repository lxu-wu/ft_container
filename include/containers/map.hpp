#ifndef MAP_HPP
# define MAP_HPP

#include <iostream>

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
			/*
				iterator
			*/

		public:

			class value_compare
			{
				friend class map;
				protected:

					Compare comp;
					value_compare(Compare c);

				public:

					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator()(const value_type& x, const value_type& y) const;
			};

		/********************************************/
		/*											*/
		/*			Constructor/ canonical			*/
		/*											*/
		/********************************************/

		// default
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

		// range
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

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

		iterator				begin();
		const_iterator			begin() const;

		iterator				end();
		const_iterator			end() const;
		
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;

		reverse_iterator		rend();
		const_reverse_iterator	rend() const;


		/********************************************/
		/*											*/
		/*			Capacity						*/
		/*											*/
		/********************************************/

		bool		empty() const;

		size_type	size() const;

		size_type	max_size() const;


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
		pair<iterator,bool>	insert(const value_type& val);
		
		// with hint
		iterator			insert(iterator position, const value_type& val);
		
		// range	
		template <class InputIterator>
		void				insert(InputIterator first, InputIterator last);
		
		void				erase(iterator position);
		
		size_type			erase(const key_type& k);
		
		void				erase(iterator first, iterator last);
	
		void				swap(map& x);

		void				clear();


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
	
		iterator							find(const key_type& k);
		const_iterator						find(const key_type& k) const;

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

		llocator_type	get_allocator() const;

	};
	
	template< class Key, class T, class Compare, class Alloc >
	void	swap( std::map<Key,T,Compare,Alloc>& lhs, std::map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const std::map<Key,T,Compare,Alloc>& lhs, const std::map<Key,T,Compare,Alloc>& rhs );

}// fin namespace;

#endif