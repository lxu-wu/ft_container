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
			container_type	c;
		
		public:
		
			//constructor
			explicit stack (const container_type& ctnr = container_type());

			bool empty() const;

			size_type size() const;

			value_type& top();
			const value_type& top() const;

			void push (const value_type& val);

			void pop();

			//explicit stack (const container_type& ctnr = container_type());
	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	
	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	
	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

	template <class T, class Container>
	void swap (stack<T,Container>& x, stack<T,Container>& y) noexcept(noexcept(x.swap(y)));
}

#endif
