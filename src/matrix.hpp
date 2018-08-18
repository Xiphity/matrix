/*
 * matrix.hpp
 *
 *  Created on: 2018年8月14日
 *      Author: xiphity
 */
#ifndef SRC_MATRIX_HPP_
#define SRC_MATRIX_HPP_
#include <iostream>
namespace Matrix {
	template <typename T = double, int N = 5>
	class matrix {
		private:
			T data[N][N];
			T determine;
		public:
			matrix() {
				init();
			}
			;
			matrix(T para[N][N]) {
				for (int ocounter = 0; ocounter < N; ++ocounter){
					for (int icounter = 0; icounter < N; ++icounter){
						this->data[ocounter][icounter] = para[ocounter][icounter];
					}
				}
				this->determine = 0;
			}
			;
			matrix(const matrix<T,N>& B) {
				for (int ocounter = 0; ocounter < N; ++ocounter){
					for (int icounter = 0; icounter < N; ++icounter){
						this->data[ocounter][icounter] = B.data[ocounter][icounter];
					}
					this->determine = 0;
				}
			}
			;
			std::ostream& show_matrix(std::ostream& strm) const {
				for (int ocounter = 0; ocounter < N; ++ocounter){
					for (int icounter = 0; icounter < N; ++icounter){
						strm << this->data[ocounter][icounter] << " ";
					}
					strm << "\n";
				};
				return strm;
			};
			void init(void) {
				this->determine = 0;
				for (int ocounter = 0; ocounter < N; ++ocounter){
					for (int icounter = 0; icounter < N; ++icounter){
						this->data[ocounter][icounter] = 0;
					}
				}
			}
			;
			double det(void) {
				double temp[N][N];
				double ans = 1;
				int change = 1;
				for (int i = 0; i < N; ++i){		//copy to a temp array
					for (int j = 0; j < N; ++j){
						temp[i][j] = data[i][j];
					}
				}

				for (int i = 0; i < N; ++i){			//高斯消去
					for (int g = i + 1; g < N; ++g){   //要加到別人身上的那一行開頭是0就跟不為0的對調
						if (temp[i][i] == 0){
							for (int k = 0; k < N; ++k){
								double temp_k = temp[i][k];
								temp[i][k] = temp[g][k];
								temp[g][k] = temp_k;
							}
							change *= -1;				//對調行列式值會差-1倍
						}
						else{
							break;
						}
					}
					if (temp[i][i] == 0){
						continue;
					}

					for (int j = i + 1; j < N; ++j){    		//把第i列加到第i+1～n列
						double factor = temp[j][i] / temp[i][i]; 	//倍率
						for (int k = 0; k < N; ++k){
							temp[j][k] += (temp[i][k] * factor * -1);
						}
					}

				}
				for (int h = 0; h < N; ++h){		//主對角線一側全為0，只須計算主對角線
					ans *= temp[h][h];
				}

				ans *= double(change);
				return ans;
			}
			;
			matrix operator+(const matrix<T,N>& B) {
				Matrix::matrix<T,N> temp;
				for (int ocounter = 0; ocounter < N; ++ocounter){
					for (int icounter = 0; icounter < N; ++icounter){
						temp.data[ocounter][icounter] = this->data[ocounter][icounter] + B.data[ocounter][icounter];
					}
				}
				return temp;
			}
			;
			matrix operator-(const matrix<T,N>& B) {
				Matrix::matrix<T,N> temp;
				for (int ocounter = 0; ocounter < N; ++ocounter){
					for (int icounter = 0; icounter < N; ++icounter){
						temp.data[ocounter][icounter] = this->data[ocounter][icounter] - B.data[ocounter][icounter];
					}
				}
				return temp;
			}
			;
			matrix operator*(const matrix<T,N>& B);
			void operator=(const matrix<T,N>& B) {
				for (int ocounter = 0; ocounter < N; ++ocounter){
					for (int icounter = 0; icounter < N; ++icounter){
						this->data[ocounter][icounter] = B.data[ocounter][icounter];
					}
				}

			}
			;


	};
	template <typename T, int N>
	std::ostream& operator<<(std::ostream& strm, const Matrix::matrix<T,N>& B) {
		B.show_matrix(strm);
		return strm;
}
}
;
#endif /* SRC_MATRIX_HPP_ */
