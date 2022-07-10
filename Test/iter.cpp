
#include <iostream>

template <typename T>
typename T::type parse(const T &t) {
	std::cout << "type parse" << std::endl;
	return T::type;
}

template <typename T>
void parse(const T &t){
	std::cout << "void parse" << std::endl;
}

int main(int argc, char const *argv[])
{
	parse(10); // Templete
	return 0;
}
