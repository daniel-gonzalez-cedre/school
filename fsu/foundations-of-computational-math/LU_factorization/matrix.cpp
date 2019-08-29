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

const precision PI = M_PI;

vector<vector<precision>> transpose(vector<vector<precision>> T)
{
	vector<vector<precision>> TT(T[0].size());
	for(int i = 0; i < T[0].size(); i++)
		for(int j = 0; j < T.size(); j++)
			TT[i].push_back(T[j][i]);
	return TT;
}

/* generates a random n by 1 vector for use in solving linear systems
 *
 * n = the dimension of the vector
 */
vector<precision> generate_random_vector(int n)
{
	srand(time(NULL));//seed the pseudo-random number generator
	vector<precision> x;
	for(int i = 0; i < n; i++)
		x.push_back(((rand()%2000) - 1000)/100.0);
	return x;
}

/* generates a random n by n matrix which is guaranteed to be diagonally-dominant and therefore non-singular
 * off-diagonal elements take values between -100 and +100
 *
 * n = the dimension of the square matrix
 */
vector<vector<precision>> generate_random_nonsingular(int n)
{
	srand(time(NULL));//seed the pseudo-random number generator
	vector<vector<precision>> R(n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			R[i].push_back(((rand()%20000) - 10000)/100.0);
	for(int k = 0; k < n; k++)
	{//make the random matrix diagonally dominant
		precision sum = -abs(R[k][k]);
		for(int j = 0; j < n; j++)
			sum = sum + abs(R[k][j]);
		if(abs(R[k][k]) < sum)
			R[k][k] = sum;
	}
	return R;
}

/* generates a random upper-triangular matrix with values between -10.0 and +10.0
 *
 * n = the dimension of the square matrix
 */
vector<vector<precision>> generate_upper_triangular(int n)
{
	srand(time(NULL));//seed the pseudo-random number generator
	vector<vector<precision>> L(n);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < i; j++)
			L[i].push_back(0);
		for(int j = i; j < n; j++)
			L[i].push_back(((rand()%2000) - 1000)/100.0);
	}
	return L;
}

/* generates a random lower-triangular matrix with values between -1.00 and +1.00
 *
 * n = the dimension of the square matrix
 */
vector<vector<precision>> generate_lower_triangular(int n)
{
	srand(time(NULL));//seed the pseudo-random number generator
	vector<vector<precision>> L(n);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j <= i; j++)
			L[i].push_back(((rand()%200) - 100)/100.0);
		for(int j = i+1; j < n; j++)
			L[i].push_back(0);
	}
	return L;
}

/* generates a random unit lower-triangular matrix with values between -100 and +100
 *
 * n = the dimension of the square matrix
 */
vector<vector<precision>> generate_unit_triangular(int n)
{
	srand(time(NULL));//seed the pseudo-random number generator
	vector<vector<precision>> L(n);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < i; j++)
			L[i].push_back(((rand()%20000) - 10000)/100.0);
		L[i].push_back(1);
		for(int j = i+1; j < n; j++)
			L[i].push_back(0);
	}
	return L;
}

/* finds the product L*U of an LU-factorization written in the condensed square-matrix format
 *
 * LU = the LU-factorization
 */
vector<vector<precision>> product(vector<vector<precision>> LU)
{
	int n = LU[0].size();
	vector<vector<precision>> A(n);
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
		{
			int min = (i > j) ? j + 1 : i;
			A[i].push_back((i > j) ? 0 : LU[i][j]);
			for(int k = 0; k < min; k++)
				A[i][j] = A[i][j] + LU[i][k] * LU[k][j];
		}
	return A;
}

/* finds the matrix-product of two arbitrary matrices with compatible dimensions
 *
 * X = an n by k matrix
 * Y = a k by m matrix
 */
vector<vector<precision>> product(vector<vector<precision>> X, vector<vector<precision>> Y)
{
	vector<vector<precision>> A(X.size());
	for(int i = 0; i < X.size(); i++)
		for(int j = 0; j < Y[0].size(); j++)
		{
			A[i].push_back(0);
			for(int k = 0; k < Y.size(); k++)
				A[i][j] = A[i][j] + X[i][k] * Y[k][j];
		}
	return A;
}

/* finds the matrix-vector product of a compatible pair using the previously implemented matrix-product function
 *
 * X = an n by k matrix
 * x = a k by 1 vector
 */
vector<precision> product(vector<vector<precision>> X, vector<precision> x)
{
	int n = x.size();
	vector<vector<precision>> y;
	y.push_back(x);
	vector<vector<precision>> xT = transpose(y);
	for(int i = 0; i < n; i++)
		xT[i].push_back(x[i]);
	xT = product(X, xT);
	for(int i = 0; i < n; i++)
		x[i] = xT[i][0];
	return x;
}

/* permutes a vector b according to the elementary permutations specified by Pb
 *
 * P = an n by n permutation matrix P = Pn-1 ... P2 P1
 * b = an n by 1 vector
 */
vector<precision> permute_P(vector<precision> P, vector<precision> b)
{
	for(int i = 0; i < P.size(); i++)
	{
		precision swap = b[i];
		b[i] = b[P[i]];
		b[P[i]] = swap;
	}
	return b;
}

/* permutes the rows of a matrix A according to PA
 *
 * P = an n by n permutation matrix
 * A = an n by n matrix
 */
vector<vector<precision>> permute_P(vector<precision> P, vector<vector<precision>> A)
{
	for(int i = 0; i < P.size(); i++)
	{
		vector<precision> swap = A[i];
		A[i] = A[P[i]];
		A[P[i]] = swap;
	}
	return A;
}

/* permutes a vector b according to the elementary permutations specified by Qb
 *
 * P = an n by n permutation matrix Q = Q1 Q2 ... Qn-1
 * b = an n by 1 vector
 */
vector<precision> permute_Q(vector<precision> Q, vector<precision> b)
{
	for(int i = Q.size() - 1; i >= 0; i--)
	{
		precision swap = b[i];
		b[i] = b[Q[i]];
		b[Q[i]] = swap;
	}
	return b;
}

/* permutes the rows of a matrix A according to AQ
 *
 * Q = an n by n permutation matrix
 * A = an n by n matrix
 */
vector<vector<precision>> permute_Q(vector<precision> Q, vector<vector<precision>> A)
{
	for(int i = 0; i < Q.size(); i++)
		for(int j = 0; j < A.size(); j++)
		{
			precision swap = A[j][i];
			A[j][i] = A[j][Q[i]];
			A[j][Q[i]] = swap;
		}
	return A;
}

/* computes the relative error of a computed solution using a specified norm
 *
 * x = given (i.e. analytic) solution
 * tilde_x = computed solution
 * *norm = a vector norm
 */
precision solution_accuracy(vector<precision> x, vector<precision> tilde_x, precision (*norm)(vector<precision>))
{
	for(int i = 0; i < x.size(); i++)
		tilde_x[i] = x[i] - tilde_x[i];
	return (*norm)(tilde_x) / (*norm)(x);
}

/* computes the relative error of a computed LU-factorization using a specified norm
 *
 * PAQ = the unfactored, permuted matrix; equal to A if no pivoting was done
 * LU = the computed LU-factorization of PAQ
 * A = the original matrix which was factored with or without pivoting
 * *norm = a matrix norm
 */
precision factorization_accuracy(vector<vector<precision>> PAQ, vector<vector<precision>> LU, vector<vector<precision>> A, precision (*norm)(vector<vector<precision>>))
{
	LU = product(LU);
	for(int i = 0; i < PAQ.size(); i++)
		for(int j = 0; j < PAQ.size(); j++)
			LU[i][j] = PAQ[i][j] - LU[i][j];
	return (*norm)(LU) / (*norm)(A);
}

/* computes the relative error of a computed solution to the linear system Ax = b using a specified norm
 *
 * b = the vector in the given problem Ax = b
 * A = the matrix in the given problem Ax = b
 * tilde_x = the computed solution to Ax = b
 * *norm = a vector norm
 */
precision residual_accuracy(vector<precision> b, vector<vector<precision>> A, vector<precision> tilde_x, precision (*norm)(vector<precision>))
{
	tilde_x = product(A, tilde_x);
	for(int i = 0; i < b.size(); i++)
		tilde_x[i] = b[i] - tilde_x[i];
	return (*norm)(tilde_x) / (*norm)(b);
}
