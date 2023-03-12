#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include "iterator_trait.hpp"
# include <iostream>

namespace ft
{
	template< class Type>
	class vector_iterator
	{
		public:
		

			typedef Type													value_type;
			typedef ft::random_access_iterator_tag							iterator_category;
			typedef std::ptrdiff_t											difference_type;
			typedef Type*													pointer;
			typedef Type&													reference;			


			// typedef typename ft::iterator_traits<Type*>::iterator_category	iterator_category;
			// typedef typename ft::iterator_traits<Type*>::value_type			value_type;
			// typedef typename ft::iterator_traits<Type*>::difference_type		difference_type;
			// typedef typename ft::iterator_traits<Type*>::pointer				pointer;
			// typedef typename ft::iterator_traits<Type*>::reference			reference;
		
		protected:
		
			pointer _ptr;

		public:
		
			vector_iterator() : _ptr(NULL) {}
			vector_iterator (pointer ptr) : _ptr(ptr) {}
			vector_iterator (vector_iterator const &rev_it) {}
			virtual ~vector_iterator() {}

			vector_iterator& operator=(vector_iterator<Type> const &other )
			{
				if (this != &other)
					this->_ptr = other._ptr;
				return (*this);
			}
			
			reference operator*() const
			{
				return *(this->_ptr);
			}

			pointer operator->() const
			{
				return (this->_ptr);
			}
			
			vector_iterator& operator++()
			{
        		++(this->_ptr);
        		return *this;
    		}

			vector_iterator operator++(int)
			{
				vector_iterator tmp = *this;
				++(this->_ptr);
				return tmp;
			}

			vector_iterator& operator--()
			{
				--(this->_ptr);
				return *this;
			}

			vector_iterator operator--(int)
			{
				vector_iterator tmp = *this;
				--(this->_ptr);
				return *this;
			}

			vector_iterator operator+(difference_type n) const
			{
				return vector_iterator(this->_ptr + n);
			}

			vector_iterator operator-(difference_type n) const
			{
				return vector_iterator(this->_ptr - n);
			}

			vector_iterator& operator+=(difference_type n)
			{
				this->_ptr += n;
				return *this;
			}

			vector_iterator& operator-=(difference_type n)
			{
				this->_ptr -= n;
				return *this;
			}

			reference operator[](difference_type n) const
			{
				return (this->_ptr)[n];
			}

			bool operator==(const vector_iterator& other) const
			{
				return this->_ptr == other._ptr;
			}

			bool operator!=(const vector_iterator& other) const
			{
				return this->_ptr != other._ptr;
			}

			bool operator<(const vector_iterator& other) const
			{
				return this->_ptr < other._ptr;
			}

			bool operator>(const vector_iterator& other) const
			{
				return this->_ptr > other._ptr;
			}

			bool operator<=(const vector_iterator& other) const
			{
				return this->_ptr <= other._ptr;
			}

			bool operator>=(const vector_iterator& other) const
			{
				return this->_ptr >= other._ptr;
			}

			template<typename T>
			friend typename vector_iterator<T>::difference_type operator-(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs);

	};

	template<typename T>
	vector_iterator<T> operator+(typename vector_iterator<T>::difference_type n, const vector_iterator<T>& it)
	{
		return it + n;
	}

	template<typename T>
	typename vector_iterator<T>::difference_type operator-(const vector_iterator<T>& lhs, const vector_iterator<T>& rhs)
	{
		return lhs._ptr - rhs._ptr;
	}

}

#endif