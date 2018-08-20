#include <iostream>
#include <cstdlib>
#include "matrix.hpp"
using namespace std;
int main() {
	int ans[3][3] = { 0, 8, 8, 4, 5, 6, 7, 1, 3 };
	int i[3][3] = { 1, 0, 0, 0, 2, 0, 0, 0, 1 };
	Matrix::matrix<int,3> test { ans };
	Matrix::matrix<int,3> I { i };
	std::cout << test << std::endl << I << std::endl;
	test = I * test;

	std::cout << test;

	std::cout << test << std::endl;
	std::cout << test(0, 2);

}


