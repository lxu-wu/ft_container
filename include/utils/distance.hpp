#ifndef DISTANCE_HPP
# define DISTANCE_HPP

#include <iostream>
#include "../iterator/iterator_trait.hpp"

namespace ft {
	
	template < class InputIterator >
	typename iterator_traits<InputIterator>::difference_type __distance(InputIterator _first, InputIterator _last, input_iterator_tag)
	{
		// std::cout << &_first << " ~~~~~~~~~~~~~~~~~~~ " << &_last << std::endl;
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (_first != _last)
		{
			_first++;
			n++;
		}
		return (n);
	}

	template < class RandomAccessIterator >
	typename iterator_traits<RandomAccessIterator>::difference_type __distance(RandomAccessIterator _first, RandomAccessIterator _last, random_access_iterator_tag)
	{
		// std::cout << &_first << " " << &_last << " : " << size_t(_last - _first) << std::endl;
		return (_last - _first);
	}

	template < class InputIterator >
	typename iterator_traits<InputIterator>::difference_type distance(InputIterator& first, InputIterator& last)
	{
		// std::cout << &first << " " << &last << " : " << size_t(last - first) << std::endl;
		return __distance(first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
	}
	
}

#endif