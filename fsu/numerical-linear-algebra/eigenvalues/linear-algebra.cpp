/*
 * Daniel Gonzalez
 * Florida State University Dept. of Mathematics
 */
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <math.h>
#include <time.h>
#include <cmath>
#include <complex>
using namespace std;

#include "norms.h"

//adding the g++ directive -DSINGLE=1 at compile time enables single precision
#ifdef SINGLE
typedef float precision;
#else
typedef double precision;
#endif

const precision π = M_PI;

void print_vector(vector<precision> v){
    for(int i = 0; i < v.size(); i++)
        cout << v[i] << endl;
    cout << endl;
}

void print_matrix(vector<vector<precision>> A){
    for(int i = 0; i < A.size(); i++){
        for(int j = 0; j < A[i].size(); j++)
            cout << A[i][j] << "\t";
        cout << endl;
    }
    cout << endl;
}

vector<precision> scale(precision α, vector<precision> x)
{
	for(int i = 0; i < x.size(); i++)
		x[i] = α*x[i];
	return x;
}

vector<vector<precision>> scale(precision α, vector<vector<precision>> X)
{
	for(int i = 0; i < X.size(); i++)
		for(int j = 0; j <= i; j++)
			X[i][j] = α*X[i][j];
	return X;
}

vector<vector<precision>> transpose(vector<vector<precision>> Q){
    vector<vector<precision>> QT(Q[0].size(), vector<precision>(Q.size()));
    for(int i = 0; i < Q.size(); i++)
        for(int j = 0; j < Q[0].size(); j++)
            QT[j][i] = Q[i][j];
    return QT;
}

vector<precision> sum(vector<precision> x, vector<precision> y)
{
	for(int i = 0; i < x.size(); i++)
		x[i] = x[i] + y[i];
	return x;
}

vector<precision> difference(vector<precision> x, vector<precision> y)
{
	for(int i = 0; i < x.size(); i++)
		x[i] = x[i] - y[i];
	return x;
}

vector<vector<precision>> sum(vector<vector<precision>> A, vector<vector<precision>> B)
{
	int α = A.size();
	int β = B.size();
	int μ = (α < β) ? α : β;
	for(int i = 0; i < μ; i++)
	{
		precision αi = A[α-i-1].size();
		precision βi = B[β-i-1].size();
		precision μi = (αi < βi) ? αi : βi;
		for(int j = 0; j < μi; j++)
			A[α-i-1][α-i-j-1] = A[α-i-1][α-i-j-1] + B[β-i-1][β-i-j-1];
	}
	return A;
}

vector<vector<precision>> dense_sum(vector<vector<precision>> A, vector<vector<precision>> B)
{
	int n = A.size();
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			A[i][j] = A[i][j] + B[i][j];
	return A;
}

precision inner_product(vector<precision> x, vector<precision> y)
{
	int n = x.size();
	precision sum = 0;
	for(int i = 0; i < n; i++)
		sum = sum + x[i]*y[i];
	return sum;
}

vector<vector<precision>> outer_product(vector<precision> x, vector<precision> y)
{
	int n = x.size();
	vector<vector<precision>> xyT(n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j <= i; j++)
			xyT[i].push_back(x[i]*y[j]);
	return xyT;
}

vector<precision> product(vector<vector<precision>> X, vector<precision> x)
{
	vector<precision> y;
	int shift = X.size() - x.size();
	for(int d = shift; d < X.size(); d++)
	{
		vector<precision> row;
		for(int i = shift; i < d; i++)
			row.push_back(X[d][i]);
		for(int j = d; j < X.size(); j++)
			row.push_back(X[j][d]);
		y.push_back(inner_product(row, x));
	}
	return y;
}

vector<vector<precision>> product(vector<vector<precision>> A, vector<vector<precision>> B)
{
	int n = A.size();
	vector<vector<precision>> C(n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			C[i].push_back(0);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			for(int k = 0; k < n; k++)
				C[i][j] = C[i][j] + A[i][k]*B[k][j];
	return C;
}
