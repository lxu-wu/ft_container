#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <memory>
#include "../utils/pair.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/equal.hpp"
#include "../utils/is_integral.hpp"
#include "../utils/lexicographical_compare.hpp"
#include "../utils/distance.hpp"
#include "../iterator/vector_iterator.hpp"
#include "../iterator/reverse_iterator.hpp"

namespace ft
{
	template< class T, class Allocator = std::allocator<T> >
	class vector
	{
		public:
		
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::difference_type	difference_type;
			typedef typename allocator_type::size_type			size_type;
		
			typedef ft::vector_iterator<value_type>				iterator;
            typedef ft::vector_iterator<const value_type>				const_iterator;
            typedef ft::reverse_iterator<iterator>				reverse_iterator;
            typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		protected:

			pointer			_begin;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;

		public:

			/************************************************/
			/*												*/
			/*				Constructor	/ canonical			*/
			/*												*/
			/************************************************/
			
			// default constructor
			explicit vector( const allocator_type& alloc = allocator_type() )
			: _begin(NULL), _size(0), _capacity(0), _alloc(alloc)
			{

			}
			
			// fill constructor
			explicit vector( size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type() )
			: _size(n), _capacity(n), _alloc(alloc)
			{
				this->_begin = this->_alloc.allocate(n);
				for (size_type i = 0; i < n; i++)
					this->_alloc.construct(this->_begin + i, val);
			}
			
			// range constructor
			template <class InputIterator>
			vector( InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			: _alloc(alloc)
			{
				// std::cout << &first << " " << &last << " : "<< &last - &first << std::endl;
				// difference_type size = &last - &first;
				difference_type size = ft::distance(first, last);
				this->_size = size;
				this->_capacity = size;
				// std::cout << "size: " << size << std::endl;
				this->_begin = this->_alloc.allocate(size);
				for (size_type i = 0; i < size; i++, first++)
					this->_alloc.construct(this->_begin + i, *(first));
				
			}

			// copy constructor
			vector (const vector& other)
			: _begin(NULL), _size(other._size), _capacity(other._capacity), _alloc(other._alloc)
			{
				this->_begin = this->_alloc.allocate(other._size);
				for (size_type i = 0; i < other._size; i++)
					this->_alloc.construct(this->_begin + i, other._begin[i]);
			}

			// Destructor
			~vector()
			{
				this->clear();
				this->_alloc.deallocate(this->_begin, this->_capacity);
			}

			// assignation
			vector& operator=( const vector& x )
			{
				if (this != &x)
					this->assign(x.begin(), x.end());
				return (*this);
			}


			/************************************************/
			/*												*/
			/*				Iterator						*/
			/*												*/
			/************************************************/

			iterator						begin()
			{
				return (iterator(this->_begin));
			}

			const_iterator					begin() const
			{
				return (const_iterator(this->_begin));
			}

			iterator						end()
			{
				return (iterator(this->_begin + this->_size));
			}

			const_iterator					end() const
			{
				return (const_iterator(this->_begin + this->_size));
			}

			reverse_iterator				rbegin()
			{
				return (reverse_iterator(this->end()));
			}

			const_reverse_iterator			rbegin() const
			{
				return (const_reverse_iterator(this->end()));
			}

			reverse_iterator				rend()
			{
				return (reverse_iterator(this->begin()));
			}

			const_reverse_iterator			rend() const
			{
				return (const_reverse_iterator(this->begin()));
			}


			/************************************************/
			/*												*/
			/*				Capacity						*/
			/*												*/
			/************************************************/

			size_type	size() const
			{
				return (this->_size);
			}

			size_type	max_size() const
			{
				return (this->_alloc.max_size());
			}

			void		resize(size_type n, value_type val = value_type())
			{
				if (n > this->_capacity)
				{
					if (n <= (this->_capacity * 2))
						reserve(this->_capacity * 2);
					else
						reserve(n);
				}
				else if (n < this->_size)
				{
					for (size_type i = n; i < this->_size; i++)
						this->_alloc.destroy(this->_begin + i);
				}
				if (n > this->_size)
				{
					for (size_type i = this->_size; i < n; i++)
						this->_alloc.construct(this->_begin + i, val);
				}
				this->_size = n;
			}

			size_type	capacity() const
			{
				return (this->_capacity);
			}

			bool		empty() const
			{
				return (this->_size == 0);
			}

			void		reserve(size_type n)
			{
				if (n > this->max_size())
				{
					throw std::length_error("vector::reserve");
				}
				if (n > this->_capacity)
				{
					// std::cout << "n: " << n << std::endl;
					// std::cout << "Size: " << this->_size << std::endl;
					// std::cout << "Capacity: " << this->_capacity << std::endl;
					pointer tmp = this->_alloc.allocate(n);
					// std::cout << "tmp: " << tmp << std::endl;
					for (size_type i = 0; i < this->_size; i++)
						this->_alloc.construct(tmp + i, this->_begin[i]);
					for (size_type i = 0; i < this->_size; i++)
						this->_alloc.destroy(this->_begin + i);
					this->_alloc.deallocate(this->_begin, this->_capacity);
					this->_begin = tmp;
					this->_capacity = n;
				}
			}


			/************************************************/
			/*												*/
			/*				Element access					*/
			/*												*/
			/************************************************/

			reference			operator[]( size_type n )
			{
				return (this->_begin[n]);
			}

			const_reference		operator[]( size_type n ) const
			{
				return (this->_begin[n]);
			}

			reference			at( size_type n )
			{
				if (n >= this->_size)
					throw std::out_of_range("vector");
				return (this->_begin[n]);
			}

			const_reference		at( size_type n ) const
			{
				if (n >= this->_size)
					throw std::out_of_range("vector");
				return (this->_begin[n]);
			}

			reference			front()
			{
				return (this->_begin[0]);
			}

			const_reference		front() const
			{
				return (this->_begin[0]);
			}

			reference			back()
			{
				return (this->_begin[this->_size - 1]);
			}

			const_reference		back() const
			{
				return (this->_begin[this->_size - 1]);
			}

			value_type*		data()
			{
				return (this->_begin);
			}

			const value_type*	data() const
			{
				return (this->_begin);
			}


			/************************************************/
			/*												*/
			/*				Modifiers						*/
			/*												*/
			/************************************************/
			
			//range
			template <class InputIterator>
			void			assign(InputIterator first, InputIterator last,
            typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			{
				this->clear();
				// std::cout << &first << " " << &last << " : " << last - first << std::endl;
				difference_type size = ft::distance(first, last);
				// difference_type size = last - first;
				// std::cout << "size: " << size << std::endl;
				this->reserve(size);
				// std::cout << "begin: " << this->_begin << std::endl;
				// std::cout << "test" << std::endl;
				for (size_type i = 0; i < size; i++, first++)
				{
					// std::cout << i << ": " << _begin + i  << ": " << *(first) << std::endl;
					this->_alloc.construct(this->_begin + i, *(first));
				}
				this->_size = size;
			}
			
			//fill
			void			assign(size_type n, const value_type& val)
			{
				this->clear();
				this->reserve(n);
				// std::cout << "Size: " << this->_size << std::endl;
				// std::cout << "Capacity :" << this->_capacity << std::endl;
				for (size_type i = 0; i < n; i++)
					this->_alloc.construct(this->_begin + i, val);
				this->_size = n;
			}
	
			void			push_back(const value_type& val)
			{
				if (this->_size < this->_capacity)
				{
					// std::cout << "Size: " << this->_size << std::endl;
					this->_alloc.construct(this->_begin + this->_size, val);
					this->_size++;
				}
				else
				{
					this->resize(this->_size + 1, val);
				}
			}

			void			pop_back()
			{
				if (this->_size)
					this->_alloc.destroy(this->_begin + this->_size - 1);
				this->_size--;
			}
			
			//sigle elem
			iterator		insert(iterator position, const value_type& val)
			{
				difference_type diff = position - this->begin();
				this->insert(position, 1, val);
				return (this->_begin + diff);
			}
			
			//fill
			void			insert(iterator position, size_type n, const value_type& val)
			{
				difference_type diff = position - this->begin();
				if (this->_size + n > this->_capacity)
				{
					
					if (this->_size + n <= (this->_capacity * 2))
						this->reserve(this->_capacity * 2);
					else
						this->reserve(this->_size + n);
				}
				// std::cout << "Size: " << this->_size << std::endl;
				// std::cout << "diff: " << diff << std::endl;
				if (this->_size)
				{
					for (difference_type i = (this->_size - 1); i >= diff; i--)
					{
						// std::cout << "i: " << (i + n) << std::endl;
						this->_alloc.construct(this->_begin + (i + n), this->_begin[i]);
						this->_alloc.destroy(this->_begin + i);
					}
				}
				for (size_type i = 0; i < n; i++)
					this->_alloc.construct(this->_begin + diff + i, val);
				this->_size += n;
			}
			
			//range
			template <class InputIterator>
			void			insert(iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = NULL)
			{
				difference_type size = ft::distance(first, last);
				difference_type diff = position - this->begin();
				if (this->_size + size > this->_capacity)
				{
					if (this->_size + size <= (this->_capacity * 2))
						reserve(this->_capacity * 2);
					else
						reserve(this->_size + size);
				}
				for (difference_type i = (this->_size - 1); i >= diff; i--)
				{
					// std::cout << "i: " << i << std::endl;
					this->_alloc.construct(this->_begin + i + size, this->_begin[i]);
					this->_alloc.destroy(this->_begin + i);
				}
				for (size_type i = 0; i < size; i++, first++)
					this->_alloc.construct(this->_begin + diff + i, *(first));
				this->_size += size;
			}

			iterator		erase(iterator position)
			{
				difference_type diff = position - this->begin();
				this->_alloc.destroy(this->_begin + diff);
				// std::cout << diff << std::endl;
				for (size_type i = diff; i < this->_size - 1; i++)
				{
					this->_alloc.destroy(this->_begin + i);
					this->_alloc.construct(this->_begin + i, this->_begin[i + 1]);
				}
				if (diff < this->_size)
					this->_size--;
				return (this->_begin + diff);
			}

			iterator		erase (iterator first, iterator last)
			{
				difference_type size = ft::distance(first, last);
				difference_type diff = first - this->begin();
				for (size_type i = diff; i < this->_size; i++)
				{
					this->_alloc.destroy(this->_begin + i);
					this->_alloc.construct(this->_begin + i, this->_begin[i + size]);
				}
				for (size_type i = this->_size - size; i < this->_size; i++)
					this->_alloc.destroy(this->_begin + i);
				this->_size -= size;
				return (this->_begin + diff);
			}

			void			swap(vector& x)
			{
				pointer tmp = this->_begin;
				this->_begin = x._begin;
				x._begin = tmp;
				
				size_type tmp_size = this->_size;
				this->_size = x._size;
				x._size = tmp_size;

				size_type tmp_capacity = this->_capacity;
				this->_capacity = x._capacity;
				x._capacity = tmp_capacity;
			}

			void			clear()
			{
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_begin + i);
				this->_size = 0;
			}


		/************************************/
		/*									*/
		/*			Lookup					*/
		/*									*/
		/************************************/

			allocator_type	get_allocator() const
			{
				return (this->_alloc);
			}

	};	//fin de la class vector
	
	/************************************************/
	/*												*/
	/*				Non-members functions			*/
	/*												*/
	/************************************************/

	template <class T, class Alloc>
	bool	operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	
	template <class T, class Alloc>
	bool	operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}	
	
	template <class T, class Alloc>
	bool	operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	
	template <class T, class Alloc>
	bool	operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}
	
	template <class T, class Alloc>
	bool	operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}
	
	template <class T, class Alloc>
	bool	operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template <class T, class Alloc>
	void	swap(vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}

}	//fin de namespace ft


#endif