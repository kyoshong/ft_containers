#ifndef PRINT_MAP_HPP
# define PRINT_MAP_HPP

# include "../containers.hpp"

template<class key, class value>
void	print(const ft::map<key, value>& map, int n)
{
	std::cout << n << "#  size: " << map.size() << std::endl << "    ";
	for (typename ft::map<key, value>::const_iterator it = map.begin() ; it != map.end(); ++it)
	{
		std::cout << "(" << it->first << ", " << it->second << ") ";
	}

	if (map.empty() == 1)
	{

		std::cout << "empty map";
	}
	std::cout << std::endl;
}

#endif
