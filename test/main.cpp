
#include "test.hpp"

#include <fstream>

/**
 * * std tests
 **/
void start_all_std_tests(void) {
	test("List");
	test_List<std::list<int>, int>();
#ifdef FULL
	test_List<std::list<Number>, Number>();
#endif
	end_test("List");

	test("Stack");
	test_Stack<std::stack<int, std::list<int> >, std::list<int> >();
	test_Stack<std::stack<int, std::vector<int> >, std::vector<int> >();
#ifdef FULL
	test_Stack<std::stack<Number>, std::deque<Number> >();
	test_Stack<std::stack<Number, std::vector<Number> >, std::vector<Number> >();
#endif
	end_test("Stack");

	test("Vector");
	test_Vector<std::vector<int> >();
#ifdef FULL
	test_Vector<std::vector<Number> >();
#endif
	end_test("Vector");

	test("Queue");
	test_Queue<std::queue<int, std::list<int> >, std::list<int> >();
#ifdef FULL
	test_Queue<std::queue<Number>, std::deque<Number> >();
	test_Queue<std::queue<Number, std::list<Number> >, std::list<Number> >();
#endif
	end_test("Queue");

	test("Map");
	test_Map<std::Map<int, int> >();
#ifdef FULL
	test_Map<std::Map<char, int> >(48);
	test_Map<std::Map<char, Number> >(48);
	test_Map<std::Map<Number, int> >();
	test_Map<std::Map<Number, Number> >();
#endif
	end_test("Map");

}

/**
 * * ft tests
 **/
void start_all_ft_tests(void) {
	test("List");
	test_List<ft::List<int>, int>();
#ifdef FULL
	test_List<ft::List<Number>, Number>();
#endif
	end_test("List");

	test("Stack");
	test_Stack<ft::Stack<int>, ft::List<int> >();
	test_Stack<ft::Stack<int, ft::Vector<int> >, ft::Vector<int> >();
#ifdef FULL
	test_Stack<ft::Stack<Number>, ft::List<Number> >();
	test_Stack<ft::Stack<Number, ft::Deque<Number> >, ft::Deque<Number> >();
#endif
	end_test("Stack");

	test("Vector");
	test_Vector<ft::Vector<int> >();
#ifdef FULL
	test_Vector<ft::Vector<Number> >();
#endif
	end_test("Vector");

	test("Queue");
	test_Queue<ft::Queue<int>, ft::List<int> >();
#ifdef FULL
	test_Queue<ft::Queue<Number>, ft::List<Number> >();
	test_Queue<ft::Queue<Number, ft::Deque<Number> >, ft::Deque<Number> >();
#endif
	end_test("Queue");

	test("Map");
	test_Map<ft::Map<int, int> >();
#ifdef FULL
	test_Map<ft::Map<char, int> >(48);
	test_Map<ft::Map<char, Number> >(48);
	test_Map<ft::Map<Number, int> >();
	test_Map<ft::Map<Number, Number> >();
#endif
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

	// Check Number count
#ifdef FULL
	std::cout << "Total Number created: " << Number::getCreated() << '\n'
			<< "Total Number destructed: " << Number::getDestructed() << '\n';
	assert(Number::getCreated() == Number::getCreated());
#endif

	return (0);
}
