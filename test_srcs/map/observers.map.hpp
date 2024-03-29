#ifndef OBSERVERS_MAP_HPP
# define OBSERVERS_MAP_HPP

# include "print.map.hpp"

template<class Key, class Value>
void	ft_observers(const ft::map<Key, Value>& map)
{
	ft::map<Key, Value> tmp;
				/* EMPTY */
	heading("empty");
	std::cout << "0#  " << map.empty() << std::endl; // 0#
	std::cout << "1#  " << tmp.empty() << std::endl; // 1#
	
				/* SIZE */
	heading("size");
	std::cout << "0#  " << map.size() << std::endl; // 0#
	std::cout << "1#  " << tmp.size() << std::endl; // 1#
	
				/* MAX_SIZE */
	/* the results will be different because a node in ft::map is
	different from a node in std::map, so have different sizes */
	heading("max_size");
	std::cout << "0#  " << map.max_size() << std::endl; // 0#
	std::cout << "1#  " << tmp.max_size() << std::endl; // 1#
}

#endif
