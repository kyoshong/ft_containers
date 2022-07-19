// -*- C++ -*-
//===----------------------------- utils ------------------------------------===//

#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
	/*
	** ------------------------------- iterator_tags --------------------------------
	*/
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag       : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};


	/*
	** ------------------------------- iterator_traits --------------------------------
	*/
	template <typename Iter>
	class iterator_traits
	{
	public:
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
	};
	
	template <typename Iter>
	class iterator_traits<Iter*>
	{
	public:
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
	};

	template <typename Iter>
	class iterator_traits<const Iter*>
	{
	public:
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
	};
	/*
	** ------------------------------- enable_if --------------------------------
	*/

	template <bool B, typename T = void>
	struct enable_if {};

	template <typename T>
	struct enable_if<true, T> { typedef T type; };

	/*
	** ------------------------------- is_integral --------------------------------
	*/
	template <typename Tp>
	struct is_integral { static const bool value = false; };

	template <> struct is_integral<bool> { static const bool value = true; };
	template <> struct is_integral<char> { static const bool value = true; };
	template <> struct is_integral<wchar_t> { static const bool value = true; };
	template <> struct is_integral<signed char> { static const bool value = true; };
	template <> struct is_integral<short int> { static const bool value = true; };
	template <> struct is_integral<int> { static const bool value = true; };
	template <> struct is_integral<long int> { static const bool value = true; };
	template <> struct is_integral<unsigned char> { static const bool value = true; };
	template <> struct is_integral<unsigned short int> { static const bool value = true; };
	template <> struct is_integral<unsigned int> { static const bool value = true; };
	template <> struct is_integral<unsigned long int> { static const bool value = true; };

	/*
	** ------------------------------- lexicographical_compare --------------------------------
	*/

	template <typename InputIterator1, typename InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, 
							InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1; ++first2;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template <typename Compare, typename InputIterator1, typename InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								 InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || !comp(*first1, *first2))
				return false;
			if (comp(*first1, *first2))
				return true;
			++first1; ++first2;
		}
		return (first1 == last1) && (first2 != last2);
	}

	/*
	** ------------------------------- less --------------------------------
	*/
	template <typename T>
	struct less
	{
		bool operator() (const T& left, const T& right) const
		{
			return (left < right);
		}
	};
	

} // namespace ft

#endif
