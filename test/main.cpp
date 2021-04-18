
#include "test.hpp"

#include <fstream>

/**
 * * std tests
 **/
void start_all_std_tests(void) {
	test("List");
	test_List<std::list<int>, int>();
	end_test("List");

	test("Stack");
	test_Stack<std::stack<int, std::list<int> >, std::list<int> >();
	test_Stack<std::stack<int, std::vector<int> >, std::vector<int> >();
	end_test("Stack");

	test("Vector");
	test_Vector<std::vector<int> >();
	end_test("Vector");

	test("Queue");
	test_Queue<std::queue<int, std::list<int> >, std::list<int> >();
	end_test("Queue");

	test("Map");
	test_Map_std();
	end_test("Map");

}

/**
 * * ft tests
 **/
void start_all_ft_tests(void) {
	test("List");
	test_List<ft::List<int>, int>();
	end_test("List");

	test("Stack");
	test_Stack<ft::Stack<int>, ft::List<int> >();
	test_Stack<ft::Stack<int, ft::Vector<int> >, ft::Vector<int> >();
	end_test("Stack");

	test("Vector");
	test_Vector<ft::Vector<int> >();
	end_test("Vector");

	test("Queue");
	test_Queue<ft::Queue<int>, ft::List<int> >();
	end_test("Queue");

	test("Map");
	test_Map_ft();
	end_test("Map");

}

int main(void)
{
	std::streambuf *coutbuf = std::cout.rdbuf();

	std::ofstream stdOut("/Users/sadolph/21/containers/std_out");
	std::cout.rdbuf(stdOut.rdbuf());
	start_all_std_tests();
	stdOut.close();

	std::cout.rdbuf(coutbuf);

	std::ofstream ftOut("/Users/sadolph/21/containers/ft_out");
	std::cout.rdbuf(ftOut.rdbuf());
	start_all_ft_tests();
	ftOut.close();

	std::cout.rdbuf(coutbuf);

	return (0);
}
