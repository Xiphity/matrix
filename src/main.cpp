#include <iostream>
#include <cstdlib>
#include "matrix.hpp"
using namespace std;
int main() {
	int ans[3][3] = { 0, 8, 8, 4, 5, 6, 7, 1, 3 };
	Matrix::matrix<int,3> test { ans };
	std::cout << test << std::endl;
	double d = test.det();
	std::cout << d;
}


