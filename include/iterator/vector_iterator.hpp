#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include "iterator_trait.hpp"
# include <iostream>

namespace ft
{
	template< class Type>
	class vector_iterator : public ft::iterator<ft::random_access_iterator_tag, Type>
	{
		public:
		

			// typedef Type													value_type;
			// typedef ft::random_access_iterator_tag							iterator_category;
			// typedef std::ptrdiff_t											difference_type;
			// typedef Type*													pointer;
			// typedef Type&													reference;			


		typedef typename ft::iterator<ft::random_access_iterator_tag, Type>::value_type		value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, Type>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::random_access_iterator_tag, Type>::difference_type	difference_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, Type>::pointer			pointer;
		typedef typename ft::iterator<ft::random_access_iterator_tag, Type>::reference			reference;
		
		protected:
		
			pointer _ptr;

		public:
		
			vector_iterator() : _ptr(NULL) {}
			vector_iterator (pointer ptr) : _ptr(ptr) {}
			vector_iterator (vector_iterator const &other) : _ptr(other._ptr) {}
			virtual ~vector_iterator() {}

			vector_iterator& operator=(vector_iterator<Type> const &other )
			{
				if (this != &other)
					this->_ptr = other._ptr;
				return (*this);
			}
			
			// cast en const
			operator vector_iterator<const Type>() const
			{
				return (this->_ptr);
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
				return tmp;
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

			template<typename Type1, typename Type2>
			friend bool operator==(const vector_iterator<Type1>& lhs, const vector_iterator<Type2>& rhs);

			template<typename Type1, typename Type2>
			friend bool operator!=(const vector_iterator<Type1>& lhs, const vector_iterator<Type2>& rhs);

			template<typename Type1, typename Type2>
			friend bool operator<(const vector_iterator<Type1>& lhs, const vector_iterator<Type2>& rhs);

			template<typename Type1, typename Type2>
			friend bool operator>(const vector_iterator<Type1>& lhs, const vector_iterator<Type2>& rhs);

			template<typename Type1, typename Type2>
			friend bool operator<=(const vector_iterator<Type1>& lhs, const vector_iterator<Type2>& rhs);

			template<typename Type1, typename Type2>
			friend bool operator>=(const vector_iterator<Type1>& lhs, const vector_iterator<Type2>& rhs);

			template<typename Type1, typename Type2>
			friend typename vector_iterator<Type1>::difference_type operator-(const vector_iterator<Type1>& lhs, const vector_iterator<Type2>& rhs);
	

	};

		template<typename Type1, typename Type2>
	bool operator==(const vector_iterator<Type1>& lhs, const vector_iterator<Type2>& rhs)
	{
		return lhs._ptr == rhs._ptr;
	}
	template<typename Type1, typename Type2>
	bool operator!=(const vector_iterator<Type1>& lhs, const vector_iterator<Type2>& rhs)
	{
		return lhs._ptr != rhs._ptr;
	}
	template<typename Type1, typename Type2>
	bool operator<(const vector_iterator<Type1>& lhs, const vector_iterator<Type2>& rhs)
	{
		return lhs._ptr < rhs._ptr;
	}
	template<typename Type1, typename Type2>
	bool operator>(const vector_iterator<Type1>& lhs, const vector_iterator<Type2>& rhs)
	{
		return lhs._ptr > rhs._ptr;
	}
	template<typename Type1, typename Type2>
	bool operator<=(const vector_iterator<Type1>& lhs, const vector_iterator<Type2>& rhs)
	{
		return lhs._ptr <= rhs._ptr;
	}
	template<typename Type1, typename Type2>
	bool operator>=(const vector_iterator<Type1>& lhs, const vector_iterator<Type2>& rhs)
	{
		return lhs._ptr >= rhs._ptr;
	}

	template<typename T>
	vector_iterator<T> operator+(typename vector_iterator<T>::difference_type n, const vector_iterator<T>& it)
	{
		return it + n;
	}

	template<typename Type1, typename Type2>
	typename vector_iterator<Type1>::difference_type operator-(const vector_iterator<Type1>& lhs, const vector_iterator<Type2>& rhs)
	{
		return lhs._ptr - rhs._ptr;
	}

}

#endif