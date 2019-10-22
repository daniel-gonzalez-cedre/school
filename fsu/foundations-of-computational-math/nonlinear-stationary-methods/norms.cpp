/*
 * Daniel Gonzalez
 * Florida State University Dept. of Mathematics
 */
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <math.h>
using namespace std;

//adding the g++ directive -DSINGLE=1 at compile time enables single precision
#ifdef SINGLE
typedef float precision;
#else
typedef double precision;
#endif

const precision π = M_PI;

//the standard L1 norm of a vector
precision norm_L1(vector<precision> x){
	precision sum = 0;
	for(int i = 0; i < x.size(); i++)
		sum = sum + abs(x[i]);
	return sum;
}

//the standard L1 norm of a matrix
precision norm_L1(vector<vector<precision>> X){
	precision max = 0;
	for(int j = 0; j < X[0].size(); j++){
		precision sum = 0;
		for(int i = 0; i < X.size(); i++)
			sum = sum + abs(X[i][j]);
		max = (sum > max) ? sum : max;
	}
	return max;
}

//the standard L2 norm of a vector
precision norm_L2(vector<precision> x){
	precision sum = 0;
	for(int i = 0; i < x.size(); i++)
		sum = sum + x[i]*x[i];
	return sqrt(sum);
}

//the standard infinity norm of a vector
precision norm_inf(vector<precision> x){
	precision max = 0;
	for(int i = 0; i < x.size(); i++)
		max = (abs(x[i]) > max) ? abs(x[i]) : max;
	return max;
}

//the standard infinity norm of a matrix
precision norm_inf(vector<vector<precision>> X){
	precision max = 0;
	for(int i = 0; i < X.size(); i++){
		precision sum = 0;
		for(int j = 0; j < X[0].size(); j++)
			sum = sum + abs(X[i][j]);
		max = (sum > max) ? sum : max;
	}
	return max;
}

//the standard Frobenius norm of a vector
precision norm_F(vector<precision> x){
	precision sum = 0;
	for(int i = 0; i < x.size(); i++)
		sum = sum + x[i] * x[i];
	return sqrt(sum);
}

//the standard Frobenius norm of a matrix
precision norm_F(vector<vector<precision>> X){
	precision sum = 0;
	for(int i = 0; i < X.size(); i++)
		for(int j = 0; j < X[0].size(); j++)
			sum = sum + X[i][j] * X[i][j];
	return sqrt(sum);
}
