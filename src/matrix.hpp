#ifndef SRC_MATRIX_HPP_
#define SRC_MATRIX_HPP_
#define matrix_debug
//#define matrix_debug_det
#include <iostream>
#include<cmath>
namespace Matrix {
	enum class product {
		cross, dot
	};
	template <typename T = double, int N = 5, int M = 5>
	class matrix {
		protected:
			T data[N][M];
			double determine;

		public:
			matrix() {
				init();
			}
			;
			matrix(T para[N][M]) {		//copy constructor (from an exist array)
				for (int ocounter = 0; ocounter < N; ++ocounter){
					for (int icounter = 0; icounter < M; ++icounter){
						this->data[ocounter][icounter] = para[ocounter][icounter];
					}
				}
				this->determine = 0;

			}
			;
			matrix(const matrix<T,N,M>& B) {		//copy constructor(from an exist matrix)
				for (int ocounter = 0; ocounter < N; ++ocounter){
					for (int icounter = 0; icounter < M; ++icounter){
						this->data[ocounter][icounter] = B.data[ocounter][icounter];
					}
					this->determine = B.determine;

				}
			}
			;
			virtual ~matrix() {

			}
			;
			std::ostream& show_matrix(std::ostream& strm) const {
				for (int ocounter = 0; ocounter < N; ++ocounter){
					for (int icounter = 0; icounter < M; ++icounter){
						strm << this->data[ocounter][icounter] << "\t";
					}
					strm << "\n";
				};
				return strm;
			}
			;
			void init(void) {
				this->determine = 0;
				for (int ocounter = 0; ocounter < N; ++ocounter){
					for (int icounter = 0; icounter < M; ++icounter){
						this->data[ocounter][icounter] = 0;
					}
				}
			}
			;
			double det(void) {
				double temp[N][M];
				double ans = 1;
				int change = 1;
				for (int i = 0; i < N; ++i){		//copy to a temporary array
					for (int j = 0; j < M; ++j){
						temp[i][j] = data[i][j];
					}
				}

				for (int i = 0; i < N; ++i){			//高斯消去
					for (int a = 0; a < N; ++a){
						for (int b = 0; b < M; ++b){
							if ((temp[a][b] < 0.000000001) && (temp[a][b] > -0.00000000001)){
#ifdef matrix_debug_det
								std::cout << "Catch 0 of (" << a << " , " << b << ")\n";
#endif
								temp[a][b] = 0;
							}
						}
					}
					for (int g = i + 1; g < N; ++g){   //要加到別人身上的那一行開頭是0就跟不為0的對調
						if ((temp[i][i] < 0.000000001) && (temp[i][i] > -0.00000000001)){
							temp[i][i] = 0;
						}
						if (temp[i][i] == 0){
							for (int k = 0; k < M; ++k){
								if ((temp[i][k] < 0.000000001) && (temp[i][k] > -0.00000000001)){
									temp[i][k] = 0;
								}
								double temp_k = temp[i][k];
								temp[i][k] = temp[g][k];
								temp[g][k] = temp_k;
							}
							change *= -1;				//對調行列式值會差-1倍
						}
						else{
							break;
						}

						if (temp[i][i] == 0){
							continue;
						}
					}
					for (int j = i + 1; j < N; ++j){    		//把第i列加到第i+1～n列
						double factor = double(temp[j][i]) / double(temp[i][i]); //倍率
						if (temp[i][i] == 0){
							continue;
						}
						for (int k = 0; k < M; ++k){
							temp[j][k] += (temp[i][k] * factor * -1);
						}
					}

				}
				for (int h = 0; h < N; ++h){		//主對角線一側全為0，只須計算主對角線
					ans *= temp[h][h];
				}

				ans *= double(change);
				this->determine = ans;
				if (ans == -0)
					ans = 0;
				return ans;
			}
			;
			Matrix::matrix<T,N,M> operator+(const matrix<T,N,M>& B) {
				Matrix::matrix<T,N,M> temp;
				for (int ocounter = 0; ocounter < N; ++ocounter){
					for (int icounter = 0; icounter < M; ++icounter){
						temp.data[ocounter][icounter] = this->data[ocounter][icounter] + B.data[ocounter][icounter];
					}
				}
				temp.latest = false;
				return temp;
			}
			;
			Matrix::matrix<T,N,M> operator-(const matrix<T,N,M>& B) {
				Matrix::matrix<T,N,M> temp;
				for (int ocounter = 0; ocounter < N; ++ocounter){
					for (int icounter = 0; icounter < M; ++icounter){
						temp.data[ocounter][icounter] = this->data[ocounter][icounter] - B.data[ocounter][icounter];
					}
				}
				temp.latest = false;
				return temp;
			}
			;
			template <int X = 5, int Y = 5>
			Matrix::matrix<T,N,M> operator*(const matrix<T,X,Y>& B) { //cross and dot product
				Matrix::matrix<T,N,Y> temp { };
				for (int i = 0; i < N; ++i){
					for (int j = 0; j < Y; ++j){
						for (int k = 0; k < M; ++k){
						}
					}
				}
				temp.latest = false;
				return temp;

			}
			;
			void operator=(const matrix<T,N>& B) {				//assignment
				for (int ocounter = 0; ocounter < N; ++ocounter){
					for (int icounter = 0; icounter < N; ++icounter){
						this->data[ocounter][icounter] = B.data[ocounter][icounter];
					}
				}
				this->latest = B.latest;
				this->determine = B.determine;
			}
			;

			virtual T operator()(int column, int row) {
				return this->data[column][row];
			}
			;

			virtual void replace(int column, int row, T assignment) {
				this->data[column][row] = assignment;

			}
			;

			Matrix::matrix<T,N,M> rref(Matrix::matrix<T,N,M> A) {				//make this matrix as a rref matrix
				for (int i = 0; i < N; ++i){			//高斯消去
					for (int a = 0; a < N; ++a){
						for (int b = 0; b < M; ++b){
							if ((A.data[a][b] < 0.000000001) && (A.data[a][b] > -0.00000000001) && (A.data[a][b] != 0)){
#ifdef matrix_debug
								std::cout << "Catch 0 of (" << a << " , " << b << ")\n";
#endif
								A.data[a][b] = 0;
							}
						}
					}
					for (int g = i + 1; g < N; ++g){   //要加到別人身上的那一行開頭是0就跟不為0的對調
						if ((A.data[i][i] < 0.000000001) && (A.data[i][i] > -0.00000000001)){
#ifdef matrix_debug
							std::cout << "Catch 0 of (" << i << " , " << i << ")\n";
#endif
							A.data[i][i] = 0;
						}
						if (A.data[i][i] == 0){
#ifdef matrix_debug
							std::cout << "\nSwitch R" << i << " R" << g << '\n';
#endif
							for (int k = 0; k < M; ++k){
								if ((A.data[i][k] < 0.000000001) && (A.data[i][k] > -0.00000000001)){
									A.data[i][k] = 0;
								}
								double temp_k = A.data[i][k];
								A.data[i][k] = A.data[g][k];
								A.data[g][k] = temp_k;
							}
#ifdef matrix_debug
							A.show_matrix(std::cout);
							std::cout << '\n';
#endif
						}
						else{
							break;
						}

						if (A.data[i][i] == 0){
							continue;
						}
					}
#ifdef matrix_debug
					std::cout << "Times: " << i << '\n';
#endif
					for (int j = i + 1; j < N; ++j){    		//把第i列加到第i+1～n列
						if (A.data[i][i] == 0){
							continue;
						}
						else{
							double factor = double(A.data[j][i]) / double(A.data[i][i]); //倍率
#ifdef matrix_debug
							std::cout << "R" << i << " to R" << j << '\n';
#endif
							for (int k = 0; k < M; ++k){
								A.data[j][k] += (A.data[i][k] * -1 * factor);
							}
#ifdef matrix_debug
							A.show_matrix(std::cout);
							std::cout << '\n';
#endif
						}
					}

					for (int j = i - 1; j >= 0; --j){    	//把第i列加到第i-1～0列
						if (A.data[i][i] == 0){
							continue;
						}
						else{
							double factor = double(A.data[j][i]) / double(A.data[i][i]); //倍率
#ifdef matrix_debug
							std::cout << "R" << i << " to R" << j << '\n';
#endif
							for (int k = 0; k < M; ++k){
								A.data[j][k] += (A.data[i][k] * -1 * factor);
							}
#ifdef matrix_debug
							A.show_matrix(std::cout);
							std::cout << '\n';
#endif
						}

					}
#ifdef matrix_debug
					std::cout << "End of " << i << '\n';
					A.show_matrix(std::cout);
					std::cout << '\n';
#endif
				}
#ifdef matrix_debug
				std::cout << "Move 0 rows\n";
#endif
				for (int i = 0; i < N - 1; ++i){    	//移動全0列
					bool check = true;
					//int f = 0, where = 0;
					for (int k = 0; k < N; ++k){
						if (A.data[i][k] != 0){
							check = false;
							//	f = A.data[i][k];
							//where = k;
							break;
						}
					}
					if (check){
						for (int k = 0; k < M; ++k){
							T temp = A.data[i][k];
							A.data[i][k] = A.data[i + 1][k];
							A.data[i + 1][k] = temp;
						}
#ifdef matrix_debug
						std::cout << "Move R" << i << "to R" << i + 1 << '\n';
						A.show_matrix(std::cout);
						std::cout << '\n';
#endif
					}
				}
#ifdef matrix_debug
				std::cout << "\nLeader 1\n";
#endif
				for (int i = 0; i < N; ++i){    	//檢查領導1
					bool check = true;
					int where = 0;
					T f = 0;
					for (int k = 0; k < N; ++k){
						if ((A.data[i][k] != 0) && (A.data[i][k] != 1)){
							check = false;
							where = k;
							break;
						}
					}
					if (check){
						continue;
					}
					else{
						f = A.data[i][where];
						for (int k = where; k < M; ++k){
							A.data[i][k] /= f;
#ifdef matrix_debug
							std::cout << "Row:" << i << "  Column:" << k << " Factor:" << f << '\n';
							A.show_matrix(std::cout);
							std::cout << '\n';
#endif
						}

					}
				}
				A.fix_zero(A);
				return A;
			}
			;
			virtual Matrix::matrix<T,N,M> dot(matrix<T,N,M> A, matrix<T,N,M> B) {
				Matrix::matrix<T,N,M> temp { };
				for (int i = 0; i < N; ++i){
					for (int j = 0; j < M; ++j){
						temp.data[i][j] = A.data[i][j] * B.data[i][j];
					}
				}
				return temp;
			}
			void fix_zero(matrix<T,N,M>& A) {
				for (int i = 0; i < N; ++i){
					for (int j = 0; j < M; ++j){
						if (A.data[i][j] == -0){
							A.data[i][j] = 0;
						}
					}
				}
			}
	}
	;
	template <typename T, int N = 5, int M = 5, int X = 5, int Y = 5>
	Matrix::matrix<T,N,M> cross(Matrix::matrix<T,N,M> A, Matrix::matrix<T,X,Y> B) {
		return A.operator*(B);
	}
	;
	template <typename T, int N = 5, int M = 5>
	Matrix::matrix<T,N,M> rref(Matrix::matrix<T,N,M> A) { //make this matrix as a rref matrix
		return A.rref(A);
	}
	;
	template <typename T, int N, int M>
	std::ostream& operator<<(std::ostream& strm, const Matrix::matrix<T,N,M>& B) {
		B.show_matrix(strm);
		return strm;
	}
	;
}
;

#endif /* SRC_MATRIX_HPP_ */
/*
 * matrix.hpp
 *
 *  Created on: 2018年8月14日
 *      Author: xiphity
 */
