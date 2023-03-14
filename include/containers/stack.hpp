#ifndef STACK_HPP
# define STACK_HPP

#include <iostream>
// #include <vector>
#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:

			typedef T											value_type;
			typedef Container									container_type;
			typedef typename container_type::reference			reference;
			typedef typename container_type::const_reference	const_reference;
			typedef typename container_type::size_type			size_type;

		private:
			container_type	_c;
		
		public:
		
			//constructor
			explicit stack (const container_type& ctnr = container_type()) : _c(ctnr) {};

			bool empty() const
			{
				return (this->_c.empty());
			}

			size_type size() const
			{
				return (this->_c.size());
			}

			value_type& top()
			{
				return (this->_c.back());
			}

			const value_type& top() const
			{
				return (this->_c.back());
			}

			void push (const value_type& val)
			{
				// std::cout << "push test" << std::endl << std::endl;
				// std::cout << "push: " << val << std::endl;
				// std::cout << "size: " << this->_c.size() << std::endl;
				// std::cout << "capacity: " << this->_c.capacity() << std::endl;
				// for(typename container_type::iterator it = this->_c.begin(); it != this->_c.end(); ++it)
				// {
				// 	std::cout << *it << " ";
				// }
				// std::cout << std::endl;
				this->_c.push_back(val);
			}

			void pop()
			{
				this->_c.pop_back();
			}

			template <class T1, class Container1>
			friend bool operator== (const stack<T1,Container1>& lhs, const stack<T1,Container1>& rhs);
			
			template <class T1, class Container1>
			friend bool operator!= (const stack<T1,Container1>& lhs, const stack<T1,Container1>& rhs);
			
			template <class T1, class Container1>
			friend bool operator<  (const stack<T1,Container1>& lhs, const stack<T1,Container1>& rhs);
			
			template <class T1, class Container1>
			friend bool operator<= (const stack<T1,Container1>& lhs, const stack<T1,Container1>& rhs);
			
			template <class T1, class Container1>
			friend bool operator>  (const stack<T1,Container1>& lhs, const stack<T1,Container1>& rhs);
			
			template <class T1, class Container1>
			friend bool operator>= (const stack<T1,Container1>& lhs, const stack<T1,Container1>& rhs);

	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._c == rhs._c);
	}
	
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._c != rhs._c);
	}
	
	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._c < rhs._c);
	}
	
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._c <= rhs._c);
	}
	
	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._c > rhs._c);
	}
	
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs._c >= rhs._c);
	}

}

#endif
