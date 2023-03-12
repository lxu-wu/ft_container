#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include <iostream>
# include "iterator_trait.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
		public:
		
			typedef Iterator													iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;
			
		protected:

			iterator_type _current;

		public:

			/************************************************/
			/*												*/
			/*				Constructor	/ canonical			*/
			/*												*/
			/************************************************/

			// default constructor
			reverse_iterator() : _current() {}

			// initialization constructor
			explicit reverse_iterator (iterator_type it) : _current(it) {}

			// copy constructor
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) : _current(rev_it.base()) {}

			// standard destuctor
			virtual ~reverse_iterator() {}

			// operator =
			template< class U >
			reverse_iterator& operator=( const reverse_iterator<U>& other )
			{
				if (this != &other)
					this->_current = other.base();
				return (*this);
			}

			/************************************************/
			/*												*/
			/*				operator						*/
			/*												*/
			/************************************************/

			iterator_type base() const { return this->_current; }

			reference operator*() const
			{
				iterator_type tmp = this->_current;
				return *(--tmp);
			}

			reverse_iterator operator+ (difference_type n) const
			{
				return (reverse_iterator(this->_current - n));
			}

			// ++int
			reverse_iterator& operator++()
			{
				--(this->_current);
				return *this;
			}

			// int++
			reverse_iterator  operator++(int)
			{
				reverse_iterator tmp = *this;
				--(this->_current);
				return tmp;
			}

			reverse_iterator& operator+= (difference_type n)
			{
				this->_current -= n;
				return *this;
			}

			reverse_iterator operator- (difference_type n) const
			{
				return (reverse_iterator(this->_current + n));
			}

			// --int
			reverse_iterator& operator--()
			{
				++(this->_current);
				return *this;
			}
			
			// int--
			reverse_iterator  operator--(int)
			{
				reverse_iterator tmp = *this;
				++(this->_current);
				return tmp;
			}

			reverse_iterator& operator-= (difference_type n)
			{
				this->_current += n;
				return *this;
			}

			pointer operator->() const
			{
				return &(this->operator*());
			}

			reference operator[] (difference_type n) const
			{
				return *(*this + n);
			}


	};

	// rational operator

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());
	}
	
	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());
	}
	
	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());
	}
	
	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	
	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());
	}
	
	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}


	// other ope

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it + n);
	}
	
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	}

}


#endif