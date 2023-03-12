#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

#include <type_traits>

namespace ft {

	template<typename T>
	struct is_integral : public std::false_type {};

	template<>
	struct is_integral<int> : public std::true_type {};

	template<>
	struct is_integral<unsigned int> : public std::true_type {};

	template<>
	struct is_integral<long> : public std::true_type {};

	template<>
	struct is_integral<unsigned long> : public std::true_type {};

	template<>
	struct is_integral<long long> : public std::true_type {};

	template<>
	struct is_integral<unsigned long long> : public std::true_type {};

	template<>
	struct is_integral<short> : public std::true_type {};

	template<>
	struct is_integral<unsigned short> : public std::true_type {};

	template<>
	struct is_integral<char> : public std::true_type {};

	template<>
	struct is_integral<unsigned char> : public std::true_type {};

	template<>
	struct is_integral<wchar_t> : public std::true_type {};

}

#endif