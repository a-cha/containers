
#ifndef TEST_HPP
# define TEST_HPP

# include <iostream>

# include "../_List/List.hpp"
# include "../_Stack/Stack.hpp"
# include "../_Queue/Queue.hpp"
# include "../_Vector/Vector.hpp"
# include "../_Map/Map.hpp"

# include <vector>
# include <list>
# include <stack>
# include <queue>
# include <map>
# include <set>
# include <deque>

# include <cassert>

void test(std::string const &what) {
	std::cout << "######################################## START TEST " << what << std::endl;
}

void end_test(std::string const &what) {
	std::cout << "######################################## END TEST " << what << '\n' << std::endl;
}

template<typename Container>
void display_container(std::string const &header, Container const &ctn)
{
	typename Container::const_iterator it = ctn.begin();
	typename Container::const_iterator ite = ctn.end();
	std::cout << header;
	if (it == ite)
		std::cout << " empty !";
	std::cout << '\n';
	while (it != ite)
	{
		std::cout << *it;
		if (++it == ite)
			std::cout << '\n';
		else
			std::cout <<  ", ";
	}
}

template<typename key_type, typename value_type>
void display_container(std::map<key_type, value_type> const &ctn)
{
	typename std::map<key_type, value_type>::const_iterator it = ctn.begin();
	typename std::map<key_type, value_type>::const_iterator ite = ctn.end();
	if (it == ite)
		std::cout << " empty !";
	std::cout << '\n';
	while (it != ite)
	{
		std::cout << (*it).first << " => " << (*it).second;
		if (++it == ite)
			std::cout << '\n';
		else
			std::cout <<  ", ";
	}
}

template<typename key_type, typename value_type>
void display_container(ft::Map<key_type, value_type> const &ctn)
{
	typename ft::Map<key_type, value_type>::const_iterator it = ctn.begin();
	typename ft::Map<key_type, value_type>::const_iterator ite = ctn.end();
	if (it == ite)
		std::cout << " empty !";
	std::cout << '\n';
	while (it != ite)
	{
		std::cout << (*it).first << " => " << (*it).second;
		if (++it == ite)
			std::cout << '\n';
		else
			std::cout <<  ", ";
	}
}

# include "list_test.hpp"
# include "stack_test.hpp"
# include "queue_test.hpp"
# include "vector_test.hpp"
# include "map_test_std.hpp"
# include "map_test_ft.hpp"

#endif
