
#include "test.hpp"

#include <fstream>

/*
** std tests
*/
void start_all_std_tests(void) {
	test("_List");
	test_List<std::list<int>, int>();
	end_test("_List");

	test("_Stack");
	test_Stack<std::stack<int, std::list<int> >, std::list<int> >();
	test_Stack<std::stack<int, std::vector<int> >, std::vector<int> >();
	end_test("_Stack");

	test("_Vector");
	test_Vector<std::vector<int> >();
	end_test("_Vector");

	test("_Queue");
	test_Queue<std::queue<int, std::list<int> >, std::list<int> >();
	end_test("_Queue");

	test("_Map");
	test_Map_std();
	end_test("_Map");

}

/*
** ft tests
*/
void start_all_ft_tests(void) {
	test("_List");
	test_List<ft::List<int>, int>();
	end_test("_List");

	test("_Stack");
	test_Stack<ft::Stack<int>, ft::List<int> >();
	test_Stack<ft::Stack<int, ft::Vector<int> >, ft::Vector<int> >();
	end_test("_Stack");

	test("_Vector");
	test_Vector<ft::Vector<int> >();
	end_test("_Vector");

	test("_Queue");
	test_Queue<ft::Queue<int>, ft::List<int> >();
	end_test("_Queue");

	test("_Map");
	test_Map_ft();
	end_test("_Map");

}

int main()
{
	std::streambuf *coutbuf = std::cout.rdbuf();

	std::ofstream stdOut("/Users/antoncaparin/21/containers/std_out");
	std::cout.rdbuf(stdOut.rdbuf());
	start_all_std_tests();
	stdOut.close();

	std::cout.rdbuf(coutbuf);

	std::ofstream ftOut("/Users/antoncaparin/21/containers/ft_out");
	std::cout.rdbuf(ftOut.rdbuf());
	start_all_ft_tests();
	ftOut.close();

	std::cout.rdbuf(coutbuf);

	return (0);
}
