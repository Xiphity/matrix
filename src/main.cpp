#include <iostream>
#include <cstdlib>
#include "matrix.hpp"
using namespace std;
//#undef matrix_debug
int main() {
	double ans[4][5] = { 1, -3, 0, -5, -7, 3, -12, -2, -27, -33, -2, 10, 2, 24, 29, -1, 6, 1, 14, 17 };
	Matrix::matrix<double,4,5> test(ans);
	cout << test << endl << " det:" << test.det() << endl;
	cout << test.rref(test);
	//cout << (0 == -0);
//29608.625
}

