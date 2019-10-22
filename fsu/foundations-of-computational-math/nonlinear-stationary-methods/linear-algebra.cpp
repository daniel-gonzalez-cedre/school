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
#include "norms.h"

//adding the g++ directive -DSINGLE=1 at compile time enables single precision
#ifdef SINGLE
typedef float precision;
#else
typedef double precision;
#endif

const precision π = M_PI;

vector<precision> scale(precision α, vector<precision> x){
	for(int i = 0; i < x.size(); i++)
		x[i] = α*x[i];
	return x;
}

vector<vector<precision>> scale(precision α, vector<vector<precision>> X){
	for(int i = 0; i < X.size(); i++)
		for(int j = 0; j < X[0].size(); j++)
			X[i][j] = α*X[i][j];
	return X;
}

precision inner_product(vector<precision> x, vector<precision> y){
	precision sum = 0;
	for(int i = 0; i < x.size(); i++)
		sum = sum + x[i]*y[i];

	return sum;
}

vector<vector<precision>> outer_product(vector<precision> x, vector<precision> y){
	int n = x.size();
	vector<vector<precision>> A(n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			A[i].push_back(x[i]*y[j]);
	return A;
}

vector<precision> product(vector<vector<precision>> A, vector<precision> x){
	int n = x.size();
	vector<precision> y(n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			y[i] = y[i] + A[i][j]*x[j];
	return y;
}

vector<vector<precision>> inverse2x2(vector<vector<precision>> J){
	precision determinant = J[0][0]*J[1][1] - J[0][1]*J[1][0];
	precision temp = J[0][0];
	J[0][0] = J[1][1];
	J[1][1] = temp;
	J[0][1] = -J[0][1];
	J[1][0] = -J[1][0];
	return scale(1/determinant, J);
}

vector<precision> sum(vector<precision> x, vector<precision> y){
	for(int i = 0; i < x.size(); i++)
		x[i] = x[i] + y[i];
	return x;
}

vector<vector<precision>> sum(vector<vector<precision>> X, vector<vector<precision>> Y){
	for(int i = 0; i < X.size(); i++)
		for(int j = 0; j < X[0].size(); j++)
			X[i][j] = X[i][j] + Y[i][j];
	return X;
}

vector<precision> difference(vector<precision> x, vector<precision> y){
	for(int i = 0; i < x.size(); i++)
		x[i] = x[i] - y[i];
	return x;
}

vector<vector<precision>> difference(vector<vector<precision>> X, vector<vector<precision>> Y){
	for(int i = 0; i < X.size(); i++)
		for(int j = 0; j < X[0].size(); j++)
			X[i][j] = X[i][j] - Y[i][j];
	return X;
}
