#include "matrix.hpp"
#include <iostream>
#include<cmath>
#ifndef SRC_VECTORS_HPP_
#define SRC_VECTORS_HPP_
using namespace Matrix;
namespace Matrix
::Vector{
	template<typename T,int M=3>
	class row_vector : public Matrix::matrix<T,1,M>{
		double norm(){
			double ans{0};
			for(int counter=0;counter<M;++counter){
				ans+=(this->data[0][counter])*(this->data[0][counter]);
			}
			ans=sqrt(ans);
			return ans;
		};
		double dot(colum_vector<T,M> B){
			int ans{0};
			for(int counter=0;counter<M;++counter){
				ans+=(this->data[0][counter])*(B.data[counter][0]);
			}
			return ans;
		};
		double dot(row_vector<T,M> B){
			int ans{0};
			for(int counter=0;counter<M;++counter){
				ans+=(this->data[0][counter])*(B.data[0][counter]);
			}
			return ans;
		};
	};
	template<typename T,int N=3>
	class colum_vector : public Matrix::matrix<T,N,1>{
		double norm(){
			double ans{0};
			for(int counter=0;counter<N;++counter){
				ans+=(this->data[counter][0])*(this->data[counter][0]);
			}
			ans=sqrt(ans);
			return ans;
		}
		double dot(colum_vector<T,N> B){
			int ans{0};
			for(int counter=0;counter<N;++counter){
				ans+=(this->data[counter][0])*(B.data[counter][0]);
			}
			return ans;
		};
		double dot(row_vector<T,N> B){
			int ans{0};
			for(int counter=0;counter<N;++counter){
				ans+=(this->data[counter][0])*(B.data[0][counter]);
			}
			return ans;
		};
	};

}
;
#endif /* SRC_VECTORS_HPP_ */
/*
 * vectors.hpp
 *
 *  Created on: Apr 10, 2019
 *      Author: xiphity
 */
